//
//  context_fbo.cpp
//  gpu_opengl
//
//  Created by Camilo Sasuke Tsumanuma on 25/07/20.
//  Copyright © 2020 Camilo Sasuke Tsumanuma. All rights reserved.
//
#include "framework.h"
#include "_.h"
#include <OpenGL/OpenGL.h>
#include "context_fbo.h"


namespace opengl
{


   ::gpu::context * create_fbo_context()
   {

      return new context_fbo();

   }


   context_fbo::context_fbo()
   {

      m_emode = e_mode_fbo;
      
      m_context = 0;
      
      m_renderbuffer = 0;
      
      m_framebuffer = 0;
      
   }


   context_fbo::~context_fbo()
   {


   }


   ::e_status context_fbo::_create_offscreen_buffer(const ::size_i32 & size)
   {

      auto pgpu = System->get_gpu();

      __pointer(opengl) popengl = pgpu;

      if (::is_null(popengl))
      {

         return ::error_failed;

      }
      
      CGLPixelFormatAttribute AttribList[] =
      {

         kCGLPFADisplayMask,(CGLPixelFormatAttribute) 0,
         kCGLPFANoRecovery,
         kCGLPFADoubleBuffer,
         kCGLPFAAccelerated,(CGLPixelFormatAttribute)1,
         kCGLPFAOpenGLProfile, (CGLPixelFormatAttribute)kCGLOGLPVersion_GL3_Core,
         kCGLPFAColorSize, (CGLPixelFormatAttribute)24,
         kCGLPFADepthSize, (CGLPixelFormatAttribute)24,
         kCGLPFAAlphaSize,(CGLPixelFormatAttribute)8,
         kCGLPFAStencilSize,(CGLPixelFormatAttribute)8,
         (CGLPixelFormatAttribute)0
         
      };

      CGDirectDisplayID display = CGMainDisplayID();

      AttribList[1] = (CGLPixelFormatAttribute)CGDisplayIDToOpenGLDisplayMask (display);
      
      CGLPixelFormatObj PixelFormat;
      
      GLint NumFormats = 0;
      
      CGLError error = CGLChoosePixelFormat(AttribList, &PixelFormat, &NumFormats);
      
      if(error != kCGLNoError)
      {
         
         return ::error_failed;
         
      }
      
      for(int iFormat = 0; iFormat < NumFormats; iFormat++)
      {
         
         output_debug_string("\nFormat " + __str(iFormat) + "\n");
         
#define DUMP_FORMAT(x)                                                        \
         {                                                                    \
                                                                              \
            GLint value = 0;                                                  \
            CGLDescribePixelFormat(PixelFormat, iFormat, x, &value);          \
            output_debug_string(string(#x) + ": " + __str(value) + "\n");     \
                                                                              \
         }
         
         DUMP_FORMAT(kCGLPFAAllRenderers);
         DUMP_FORMAT(kCGLPFADoubleBuffer);
         DUMP_FORMAT(kCGLPFAStereo);
         DUMP_FORMAT(kCGLPFAAuxBuffers);
         DUMP_FORMAT(kCGLPFAColorSize);
         DUMP_FORMAT(kCGLPFAAlphaSize);
         DUMP_FORMAT(kCGLPFADepthSize);
         DUMP_FORMAT(kCGLPFAStencilSize);
         DUMP_FORMAT(kCGLPFAAccumSize);
         DUMP_FORMAT(kCGLPFAMinimumPolicy);
         DUMP_FORMAT(kCGLPFAMaximumPolicy);
         DUMP_FORMAT(kCGLPFAOffScreen);
         DUMP_FORMAT(kCGLPFAFullScreen);
         DUMP_FORMAT(kCGLPFARendererID);
         DUMP_FORMAT(kCGLPFASingleRenderer);
         DUMP_FORMAT(kCGLPFANoRecovery);
         DUMP_FORMAT(kCGLPFAAccelerated);
         DUMP_FORMAT(kCGLPFAClosestPolicy);
         DUMP_FORMAT(kCGLPFARobust);
         DUMP_FORMAT(kCGLPFABackingStore);
         DUMP_FORMAT(kCGLPFAMPSafe);
         DUMP_FORMAT(kCGLPFAWindow);
         DUMP_FORMAT(kCGLPFAMultiScreen);
         DUMP_FORMAT(kCGLPFACompliant);
         DUMP_FORMAT(kCGLPFADisplayMask);
         DUMP_FORMAT(kCGLPFAVirtualScreenCount);
         
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
      
      error = CGLEnable(m_context, kCGLCEMPEngine);
      
      if(error != kCGLNoError)
      {
         
         return ::error_failed;
         
      }
      
      ::e_status estatus = make_current();

      if(!estatus)
      {
         
         return estatus;
         
      }
      
      ::gpu::context_lock lock(this);

      // Set the width and height appropriately for your image
      GL::u32 imageWidth = size.cx;
      GL::u32 imageHeight = size.cy;
      
      //Set up a FBO with one renderbuffer attachment
      glGenFramebuffersEXT(1, &m_framebuffer);
      glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, m_framebuffer);
      glGenRenderbuffersEXT(1, &m_renderbuffer);
      glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, m_renderbuffer);
      glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_RGBA8, imageWidth, imageHeight);
      glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_RENDERBUFFER_EXT, m_renderbuffer);
      
      GLenum status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
      
      if (status != GL_FRAMEBUFFER_COMPLETE_EXT)
      {
         
         return ::error_failed;
         
      }
      
      glViewport(0, 0, size.cx, size.cy);
      
      return ::success;

   }


   ::e_status context_fbo::lock_context()
   {
      
      if(!m_context)
      {
         
         return ::error_failed;
         
      }
   
      CGLError error = CGLLockContext(m_context);
      
      if(error != kCGLNoError)
      {
         
         return ::error_failed;
         
      }
      
      return ::success;
   
   }


   ::e_status context_fbo::unlock_context()
   {
      
      if(!m_context)
      {
         
         return ::error_failed;
         
      }
   
      CGLError error = CGLUnlockContext(m_context);
      
      if(error != kCGLNoError)
      {
         
         return ::error_failed;
         
      }
      
      return ::success;
   
   }


   ::e_status context_fbo::make_current()
   {

      CGLError error = CGLSetCurrentContext(m_context);
      
      bool bMakeCurrentOk = error == kCGLNoError;

      if (!bMakeCurrentOk)
      {

         printf("eglMakeCurrent failed!\n");

         return ::error_failed;

      }

      return ::success;

   }


   ::e_status context_fbo::destroy_offscreen_buffer()
   {

      make_current();
      
      glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
      
      glDeleteRenderbuffersEXT(1, &m_renderbuffer);
      
      return ::success;

   }


   string context_fbo::get_shader_version_text()
   {

      return "#version 330 core";

   }


   void context_fbo::_translate_shader(string_array & stra)
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


   ::e_status context_fbo::render()
   {
      
      ::e_status estatus = context::render();
      
      if(!estatus)
      {
       
         return estatus;
         
      }
      
      return estatus;
   
   }


   ::e_status context_fbo::start()
   {
      
      ::e_status estatus = context::start();
      
      return estatus;
   
   }


   ::e_status context_fbo::resize_offscreen_buffer(const ::size_i32& size)
   {
      
      auto estatus = context::resize_offscreen_buffer(size);
      
      if(!estatus)
      {
         
         return estatus;
         
      }
      
      glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_RGBA8, size.cx, size.cy);

      glViewport(0, 0, size.cx, size.cy);
      
      return ::success;

   }


   ::e_status context_fbo::prepare_for_gpu_read()
   {
   
      return ::success;
      
   }


} // namespace gpu



