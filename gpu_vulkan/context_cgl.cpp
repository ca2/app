//
//  context_cgl.cpp
//  gpu_vulkan
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 24/07/20.
//  Copyright (c) 2020 Camilo Sasuke Thomas Borregaard Soerensen. All rights reserved.
//

#include "framework.h"
#include "cpu_buffer.h"
#include "context_cgl.h"
#include "vulkan.h"
#include "aura/graphics/image/image.h"
#include "aura/platform/system.h"


namespace vulkan
{


   ::pointer <::gpu::context > allocate_cgl_context(::particle * pparticle)
   {

      return pparticle->__create_new < context_cgl >();

   }


   context_cgl::context_cgl()
   {

      m_emode = e_mode_egl;
      
      m_context = 0;

   }


   context_cgl::~context_cgl()
   {


   }


   void context_cgl::_create_offscreen_buffer(const ::int_size & size)
   {

      auto pgpu = system()->get_gpu();

      ::pointer<vulkan>pvulkan = pgpu;

      if (::is_null(pvulkan))
      {

         return;

      }
      
      m_itaskGpu = ::current_itask();
      
//      unsigned long target = GL_TEXTURE_2D;
//
//      unsigned long internalFormat = GL_RGBA;
//
//      long max_level = 0;
//
//      CGLError error = CGLCreatePBuffer(size.cx(), size.cy(), target, internalFormat, max_level, &m_pbuffer);
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
//         EGL_RENDERABLE_TYPE, EGL_VULKAN_BIT,
//         EGL_CONFORMANT, EGL_VULKAN_BIT,
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

      CGLPixelFormatAttribute AttribList[] =
      {
         
         kCGLPFANoRecovery,
         //kCGLPFAAccelerated,
         //kCGLPFAOffScreen,
         kCGLPFAVulkanProfile,
         (CGLPixelFormatAttribute)kCGLOGLPVersion_3_2_Core,
         kCGLPFAColorSize, (CGLPixelFormatAttribute)32,
         kCGLPFADepthSize, (CGLPixelFormatAttribute)16,
         (CGLPixelFormatAttribute)0
         
      };

      
//      CGLPixelFormatAttribute attribs[] =
//      {
//          kCGLPFAOffScreen,
//          kCGLPFAColorSize, 32,
//          NULL
//      } ;
//      CGLPixelFormatObj pixelFormatObj ;
//      long numPixelFormats ;
//      CGLChoosePixelFormat( attribs, &pixelFormatObj, &numPixelFormats ) ;
      
      CGLPixelFormatObj PixelFormat;
      
      GLint NumFormats = 0;
      
      auto error = CGLChoosePixelFormat(AttribList, &PixelFormat, &NumFormats);
      
      if(error != kCGLNoError)
      {
         
         //return ::error_failed;
         
         return;
         
      }

      error = CGLCreateContext(PixelFormat, NULL, &m_context);
      
      if(error != kCGLNoError)
      {
         
         //return ::error_failed;
         
         return;
         
      }

      error = CGLDestroyPixelFormat(PixelFormat);
      
      if(error != kCGLNoError)
      {
         
         //return ::error_failed;
         
         return;
         
      }

      make_current();
      //::e_status estatus = make_current();

//      if(!estatus)
//      {
//         
//         //return estatus;
//         
//         return;
//         
//      }
      
      auto cx = context::m_pcpubuffer->m_pixmap.width();
      auto cy = context::m_pcpubuffer->m_pixmap.height();
      auto scan = context::m_pcpubuffer->m_pixmap.m_iScan;
      auto data=context::m_pcpubuffer->m_pixmap.m_pimage32;

      error = CGLSetOffScreen(m_context, cx,
                              cy, scan, data) ;

      if(error != kCGLNoError)
      {
         
         //return ::error_failed;
         
         return;
         
      }

      //return ::success;

   }


   void context_cgl::make_current()
   {

      CGLError error = CGLSetCurrentContext(m_context);
      
      bool bMakeCurrentOk = error == kCGLNoError;

      if (!bMakeCurrentOk)
      {

         printf("eglMakeCurrent failed!\n");

         //return ::error_failed;
         
         return;

      }

      //return ::success;

   }


   void context_cgl::destroy_offscreen_buffer()
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


   void context_cgl::_translate_shader(string_array & stra)
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


} // namespace gpu



