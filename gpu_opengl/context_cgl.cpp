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
#include "acme/platform/application.h"
#include "aura/graphics/image/image.h"
#include "aura/graphics/image/target.h"
#include "aura/platform/system.h"
#include "bred/gpu/context_lock.h"


namespace gpu_opengl
{


   ::pointer <::gpu::context > allocate_cgl_context(::particle * pparticle)
   {

      return pparticle->øcreate_new < context_cgl >();

   }


   context_cgl::context_cgl()
   {

      //m_emode = e_mode_egl;
      
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
      
      //m_itaskGpu = ::current_itask();
      
//      unsigned long target = GL_TEXTURE_2D;
//
//      unsigned long internalFormat = GL_RGBA;
//
//      long max_level = 0;
//
//      CGLError error = CGLCreatePBuffer(size.cx, size.cy, target, internalFormat, max_level, &m_pbuffer);
//
//      if(error != kCGLNoError)
//      {
//
//         return ::error_failed;
//
//      }

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
      
      auto error = CGLCreateContext(pdevice->m_cglpixelformat, NULL, &m_context);
      
      if(error != kCGLNoError)
      {
         
         return;
         
      }

      ::gpu::context_lock contextlock(this);

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
      
      auto cx = context::m_pcpubuffer->m_pimagetarget->m_pimage->width();
      auto cy = context::m_pcpubuffer->m_pimagetarget->m_pimage->height();
      auto scan = context::m_pcpubuffer->m_pimagetarget->m_pimage->m_iScan;
      auto data=context::m_pcpubuffer->m_pimagetarget->m_pimage->data();

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

      //return ::success;

   }


   void context_cgl::_context_lock()
{

      CGLError error = CGLSetCurrentContext(m_context);
      
      bool bMakeCurrentOk = error == kCGLNoError;

      if (!bMakeCurrentOk)
      {

         printf("cglMakeCurrent failed!\n");

         //return ::error_failed;
         
         return;

      }

      //return ::success;

   }

void context_cgl::_context_unlock()
{

   CGLError error = CGLSetCurrentContext(nullptr);
   
   bool bMakeCurrentOk = error == kCGLNoError;

   if (!bMakeCurrentOk)
   {

      printf("cglMakeCurrent(null) failed!\n");

      //return ::error_failed;
      
      return;

   }

   //return ::success;

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


} // namespace gpu_opengl



