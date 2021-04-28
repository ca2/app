//
//  context_cgl.cpp
//  gpu_opengl
//
//  Created by Camilo Sasuke Tsumanuma on 24/07/20.
//  Copyright © 2020 Camilo Sasuke Tsumanuma. All rights reserved.
//

#include "framework.h"
#include "_.h"
#include <OpenGL/OpenGL.h>
#include "context_cgl.h"


namespace opengl
{


   ::gpu::context * create_cgl_context()
   {

      return new context_cgl();

   }


   context_cgl::context_cgl()
   {

      m_emode = e_mode_egl;
      
      m_context = 0;

   }


   context_cgl::~context_cgl()
   {


   }


   ::e_status context_cgl::_create_offscreen_buffer(const ::size_i32 & size)
   {

      auto pgpu = psystem->get_gpu();

      __pointer(opengl) popengl = pgpu;

      if (::is_null(popengl))
      {

         return ::error_failed;

      }
      
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

      CGLPixelFormatAttribute AttribList[] =
      {
         
         kCGLPFANoRecovery,
         kCGLPFAAccelerated,
         kCGLPFAOpenGLProfile,
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
      
      error = CGLChoosePixelFormat(AttribList, &PixelFormat, &NumFormats);
      
      if(error != kCGLNoError)
      {
         
         return ::error_failed;
         
      }

      error = CGLCreateContext(PixelFormat, NULL, &m_context);
      
      if(error != kCGLNoError)
      {
         
         return ::error_failed;
         
      }

      error = CGLDestroyPixelFormat(PixelFormat);
      
      if(error != kCGLNoError)
      {
         
         return ::error_failed;
         
      }

      ::e_status estatus = make_current();

      if(!estatus)
      {
         
         return estatus;
         
      }

      error = CGLSetOffScreen(m_context, m_pimage->width(), m_pimage->height(), m_pimage->m_iScan, m_pimage->get_data()) ;

      if(error != kCGLNoError)
      {
         
         return ::error_failed;
         
      }

      return ::success;

   }


   ::e_status context_cgl::make_current()
   {

      CGLError error = CGLSetCurrentContext(m_context);
      
      bool bMakeCurrentOk = error != kCGLNoError;

      if (!bMakeCurrentOk)
      {

         printf("eglMakeCurrent failed!\n");

         return ::error_failed;

      }

      return ::success;

   }


   ::e_status context_cgl::destroy_offscreen_buffer()
   {

      CGLError error = CGLSetCurrentContext(m_contextOld);
      
      if(error != kCGLNoError)
      {

         return ::error_failed;
         
      }
      
      return ::success;

   }


   string context_cgl::get_shader_version_text()
   {

      return "version 300 es";

   }


   void context_cgl::_translate_shader(string_array & stra)
   {

      strsize iFindPrecision = stra.find_first_begins_ci("precision ");

      if(iFindPrecision >= 0)
      {

         stra[iFindPrecision] = "precision highp float;";

      }
      else
      {

         stra.insert_at(1, "precision highp float;");

         iFindPrecision = 1;

      }

      strsize iFind = stra.find_first_begins_ci("out vec4 ");

      if(iFind >= 0)
      {

         stra[iFind] = "out vec4 fragmentColor;";

      }
      else
      {

         stra.insert_at(iFindPrecision + 1, "out vec4 fragmentColor;");

      }

      stra.replace("gl_FragColor", "fragmentColor");

   }


} // namespace gpu



