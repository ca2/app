//
//  context_cgl.cpp
//  gpu_opengl
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 24/07/20.
//  Copyright (c) 2020 Camilo Sasuke Thomas Borregaard Soerensen. All rights reserved.
//
#include "framework.h"
#include "_gpu_opengl.h"
#include "cpu_buffer.h"
#include "context_cgl.h"
#include "device_cgl.h"
#include "swap_chain.h"
#include "acme/platform/application.h"
#include "acme/windowing/window.h"
#include "aura/graphics/image/image.h"
#include "aura/graphics/image/target.h"
#include "aura/platform/system.h"
#include "bred/gpu/context_lock.h"

namespace opengl
{

void * operating_system_current_context()
{
   
   auto cglcontextobj = CGLGetCurrentContext();
   
   return cglcontextobj;
}

}

namespace gpu_opengl
{


   ::pointer <::gpu::context > allocate_cgl_context(::particle * pparticle)
   {

      return pparticle->øcreate_new < context_cgl >();

   }


   context_cgl::context_cgl()
   {

      //m_emode = e_mode_egl;
      
      m_pbuffer = 0;
      
      m_context = 0;

   }


   context_cgl::~context_cgl()
   {


   }


   void context_cgl::_create_cpu_buffer(const ::int_size & size)
   {

      auto pgpuapproach = m_papplication->get_gpu_approach();

//      ::pointer<opengl>popengl = pgpu;
//
//      if (::is_null(popengl))
//      {
//
//         return;
//
//      }
      
//      //m_itaskGpu = ::current_itask();
//      

//      EGLint attribList[]=
//      {
//
//         EGL_SURFACE_TYPE, EGL_PBUFFER_BIT,
//         EGL_RENDERABLE_TYPE, EGL_OPENGL_BIT,
//         EGL_CONFORMANT, EGL_OPENGL_BIT,
//         EGL_COLOR_BUFFER_TYPE, EGL_RGB_BUFFER,
//         EGL_RED_SIZE, 8,
//         EGL_GREEN_SIZE, 8,
//         EGL_BLUE_SIZE, 8,
//         EGL_ALPHA_SIZE, 8,
//         EGL_LEVEL, 0,
//         EGL_BUFFER_SIZE, 24,
//         EGL_NONE
//
//      };
      //check(InMajorVersion > 3 || (InMajorVersion == 3 && InMinorVersion >= 2));

      
//      CGLPixelFormatAttribute attribs[] =
//      {
//          kCGLPFAOffScreen,
//          kCGLPFAColorSize, 32,
//          NULL
//      } ;
//      CGLPixelFormatObj pixelFormatObj ;
//      long numPixelFormats ;
//      CGLChoosePixelFormat( attribs, &pixelFormatObj, &numPixelFormats ) ;
      
      ::cast < device_cgl > pdevice = m_pgpudevice;
      
      auto error = CGLCreateContext(pdevice->m_cglpixelformat, pdevice->m_cglcontextShare, &m_context);
      
      if(error != kCGLNoError)
      {
         
         throw ::exception(error_wrong_state);
         
         return;
         
      }
      
      if(!pdevice->m_cglcontextShare)
      {
         
         pdevice->m_cglcontextShare = m_context;
         
      }

      ::gpu::context_lock contextlock(this);
      
//      unsigned long target = GL_TEXTURE_2D;
//////
//      unsigned long internalFormat = GL_RGBA;
//////
//      long max_level = 0;
//
//      error = CGLCreatePBuffer(size.cx, size.cy, target, internalFormat, max_level, &m_pbuffer);
//
//      if(error != kCGLNoError)
//      {
//         
//         throw ::exception(error_wrong_state);
//         
//         return;
//         
//      }

      
      m_rectangle.left = 0;
      m_rectangle.top = 0;
      m_rectangle.set_size(size);
      
      _defer_update_render_frame_buffer();

//      defer_make_current();
      //::e_status estatus = make_current();

//      if(!estatus)
//      {
//         
//         //return estatus;
//         
//         return;
//         
//      }
      
      auto pcpubuffer = context::m_pcpubuffer;
      
      if(::is_set(pcpubuffer))
      {
         
         auto pimagetarget = pcpubuffer->m_pimagetarget;
         
         if(::is_set(pimagetarget))
         {
            
            auto pimage = pimagetarget->m_pimage;
            
            if(::is_set(pimage))
            {
               
               auto cx = pimage->width();
               auto cy = pimage->height();
               auto scan = pimage->m_iScan;
               auto data = pimage->data();
               
            }
            
         }
         
         //      error = CGLSetOffScreen(m_context, cx,
         //                              cy, scan, data) ;
         //
         //      if(error != kCGLNoError)
         //      {
         //
         //         //return ::error_failed;
         //
         //         return;
         //
         //      }
         
      }
      
      auto pgpurenderer = get_gpu_renderer();
      
      if(::is_null(pgpurenderer))
      {
         
         throw ::exception(error_failed);
         
      }

      //return ::success;

   }


void context_cgl::_defer_update_render_frame_buffer()
{
   
   ::gpu::context_lock contextlock(this);
   
   _defer_update_render_frame_buffer_unlocked();
   
}


void context_cgl::_defer_update_render_frame_buffer_unlocked()
{
   
   auto size = m_rectangle.size();
   
   if(m_iFbo <= 0 || m_iTex <= 0 || size != m_sizeFbo)
   {
      
      m_sizeFbo = size;
      
      auto w = size.width();
      auto h = size.height();
      
      if(m_iFbo > 0)
      {
         
         GLuint uFbo = m_iFbo;
         
         glDeleteFramebuffers(1, &uFbo);
         ::opengl::check_error("");
         
         m_iFbo = 0;
         
      }
      
      if(m_iTex > 0)
      {
         
         GLuint uTex = m_iTex;
         
         glDeleteTextures(1, &uTex);
         ::opengl::check_error("");
         
         m_iTex = 0;
         
      }
      
      GLuint fbo = 0;
      
      glGenFramebuffers(1, &fbo);
      ::opengl::check_error("");
      m_iFbo = fbo;
      glBindFramebuffer(GL_FRAMEBUFFER, fbo);
      ::opengl::check_error("");
      
      GLuint tex = 0;
      
      glGenTextures(1, &tex);
      ::opengl::check_error("");
      m_iTex = tex;
      glBindTexture(GL_TEXTURE_2D, tex);
      ::opengl::check_error("");
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0,
                   GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
      ::opengl::check_error("");
      
      glFramebufferTexture2D(GL_FRAMEBUFFER,
                             GL_COLOR_ATTACHMENT0,
                             GL_TEXTURE_2D,
                             tex, 0);
      ::opengl::check_error("");
      
      auto status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
      ::opengl::check_error("");
      
      if (status != GL_FRAMEBUFFER_COMPLETE)
      {
         
         ::string strMessage;
         
         strMessage = "context_cgl::_context_lock,Framebuffer not complete!";
         
         warning(strMessage);
         
         throw ::exception(error_failed, strMessage);
         
      }
      
      glBindTexture(GL_TEXTURE_2D, 0);
      ::opengl::check_error("");
      
   }
   
}


   void context_cgl::_context_lock()
   {

      CGLError errorSetCurrentContext = CGLSetCurrentContext(m_context);
      
      bool bMakeCurrentOk = errorSetCurrentContext == kCGLNoError;

      if (!bMakeCurrentOk)
      {
         
         ::string strMessage;
         
         strMessage = "CGLSetCurrentContext Failed to set current context";

         warning(strMessage);

         throw ::exception(error_failed, strMessage);
         
         return;

      }
      
//      if(m_pbuffer)
//      {
//         
//         CGLError errorSetPBuffer = CGLSetPBuffer(m_context, m_pbuffer, 0, 0, 0);
//         
//         bool bSetBufferOk = errorSetPBuffer == kCGLNoError;
//         
//         if (!bSetBufferOk)
//         {
//            
//            ::string strMessage;
//            
//            strMessage = "CGLSetPbuffer Failed to set pbuffer";
//            
//            warning(strMessage);
//            
//            throw ::exception(error_failed, strMessage);
//            
//            return;
//            
//         }
//         
//      }
      
      _defer_update_render_frame_buffer_unlocked();
      
//      GLint drawFbo = 0;
//      glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &drawFbo);
//      ::opengl::check_error("");
//
//      if(drawFbo != gluFbo)
//      {
         
         glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_iFbo);
         ::opengl::check_error("");
         
//      }

      
      //glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_iFbo);
      //::opengl::check_error("");
      
//      auto status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
//
//      if (status != GL_FRAMEBUFFER_COMPLETE)
//      {
//         
//         ::string strMessage;
//         
//         strMessage = "context_cgl::_context_lock,Framebuffer not complete!";
//
//         warning(strMessage);
//         
//         throw ::exception(error_failed, strMessage);
//
//      }

   }


   void context_cgl::_context_unlock()
   {
      
      GLint drawFbo = 0;
      glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &drawFbo);
      if(!glGetError())
      {
         //::opengl::check_error("");
         
         if(drawFbo)
         {
            
            glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
            ::opengl::check_error("");
            
         }
         
      }

      CGLError error = CGLSetCurrentContext(nullptr);
      
      bool bMakeCurrentOk = error == kCGLNoError;

      if (!bMakeCurrentOk)
      {

         ::string strMessage;
         
         strMessage = "CGLSetCurrentContext(nullptr) Failed to clear current context";

         warning(strMessage);

         throw ::exception(error_failed, strMessage);
         
      }
      
      auto cglcontextobj = ::opengl::operating_system_current_context();
      
      if(cglcontextobj)
      {
       
         warning("Shouldn't it return nullptr now?");
         
      }

   }


   void context_cgl::destroy_cpu_buffer()
   {

      CGLError error = CGLSetCurrentContext(m_contextOld);
      
      if(error != kCGLNoError)
      {

         //return ::error_failed;
         
      }
      
      //return ::success;

   }


   string context_cgl::get_shader_version_text()
   {

      return "version 300 es";

   }


   void context_cgl::_translate_shader(string_array_base & stra)
   {

      character_count iFindPrecision = stra.case_insensitive_find_first_begins("precision ");

      if(iFindPrecision >= 0)
      {

         stra[iFindPrecision] = "precision highp float;";

      }
      else
      {

         stra.insert_at(1, "precision highp float;");

         iFindPrecision = 1;

      }

      auto iFind = stra.case_insensitive_find_first_begins("out vec4 ");

      if(::found(iFind))
      {

         stra[iFind] = "out vec4 fragmentColor;";

      }
      else
      {

         stra.insert_at(iFindPrecision + 1, "out vec4 fragmentColor;");

      }

      for(auto & str : stra)
      {
      
         str.find_replace("gl_FragColor", "fragmentColor");
         
      }
   }


void context_cgl::_create_window_context(::acme::windowing::window* pacmewindowingwindow)
{
   
   ::int_rectangle rectangle = pacmewindowingwindow->get_window_rectangle();
   
   m_pacmewindowingwindowWindowSurface = pacmewindowingwindow;
   
   m_pacmewindowingwindowWindowSurface->m_pgpucontextrenderframe = get_swap_chain();
   
   auto size = rectangle.size();
   
   _create_cpu_buffer(size);
   
}

void context_cgl::on_cube_map_face_image(::image::image * pimage)
{

   pimage->vertical_swap();
   
   pimage->image32()->swap_red_blue(pimage->width(),pimage->height());

}

} // namespace gpu_opengl




