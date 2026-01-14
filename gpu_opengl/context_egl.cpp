//
//  context_egl.cpp
//  gpu_opengl
//
//  From context_cgl.h by camilo on 2025-12-26 03:30 <3ThomasBorregaardSørensen!!
//  Copyright (c) 2020 Camilo Sasuke Thomas Borregaard Soerensen. All rights reserved.
//

#include <X11/X.h>

#include "framework.h"
#include "_gpu_opengl.h"
#include "device_egl.h"
#include "apex/gpu/approach.h"
#include "bred/gpu/context_lock.h"
#if defined(MACOS)
#include <OpenGL/OpenGL.h>
//#include <glad/glad.h>
//#include <OpenGL/CGLTypes.h>
//////#include <OpenGL/glu.h>
#include <OpenGL/gl3.h>
#include <OpenGL/glext.h>
#endif
#include "cpu_buffer.h"
#include "context_egl.h"
//#include "opengl.h"
#include "acme/platform/application.h"
#include "aura/graphics/image/image.h"
#include "aura/graphics/image/target.h"
#include "aura/platform/system.h"
#include "aura/windowing/window.h"
const char* eglErrorString(EGLint error);
#ifdef WITH_X11
#include <X11/Xlib.h>
#endif

namespace gpu_opengl
{


   void defer_bind_egl_api();
   bool is_glad_gl_loaded();

   // should be called within a currently selected egl context
   void load_glad_gl();



   ::pointer <::gpu::context > allocate_egl_context(::particle * pparticle)
   {

      return pparticle->øcreate_new < context_egl >();

   }


   context_egl::context_egl()
   {

      //m_emode = e_mode_egl;
      m_bEGLWindowSurface = false;
      m_eglcontext = EGL_NO_CONTEXT;
      m_eglsurface = EGL_NO_SURFACE;

   }


   context_egl::~context_egl()
   {


   }


   void context_egl::__create_egl_context()
   {

      auto pgpuapproach = m_papplication->get_gpu_approach();

      ::cast < ::gpu_opengl::device_egl > pegldevice = m_pgpudevice;

      auto egldisplay = pegldevice->m_egldisplay;

      if (egldisplay == EGL_NO_DISPLAY)
      {

         throw ::exception(::error_wrong_state);

      }

      EGLConfig eglconfig = pegldevice->m_eglconfigPrimary;

      if (eglconfig == EGL_NO_CONFIG_KHR)
      {

         throw ::exception(error_wrong_state);

      }

      defer_bind_egl_api();

      EGLint contextAttribs[] = {
         EGL_CONTEXT_MAJOR_VERSION, 3,
         EGL_CONTEXT_MINOR_VERSION, 3,
         EGL_CONTEXT_OPENGL_PROFILE_MASK, EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT,
         // optional debug flag:
         EGL_CONTEXT_FLAGS_KHR, EGL_CONTEXT_OPENGL_DEBUG_BIT_KHR,
         EGL_NONE
      };      // Step 7 - Create a context.

      auto eglcontextPrimary = pegldevice->m_eglcontextPrimary;

      //EGLContext eglContext;
      m_eglcontext = eglCreateContext(egldisplay, eglconfig, eglcontextPrimary, contextAttribs);
      //qDebug() << "egl error" << eglGetError();

      if (m_eglcontext == EGL_NO_CONTEXT)
      {

         int iError = eglGetError();

         const ::scoped_string & scopedstrError = eglQueryString(egldisplay, iError);

         ::string strError;

         strError.formatf("Failed to create context (eglError: %s : 0x%x)", ::string(scopedstrError).c_str(), iError);

         warning() << strError;

         throw ::exception(::error_failed, strError);

      }

      if (!pegldevice->m_eglcontextPrimary)
      {

         pegldevice->m_eglcontextPrimary = m_eglcontext;

      }

   }


   void context_egl::__on_after_egl_context_and_surface_creation()
   {

      if (!is_glad_gl_loaded())
      {

         ::gpu::context_lock contextlock(this);

         //_context_lock();

         load_glad_gl();

         auto pszGlVersion = glGetString(GL_VERSION);

         auto pszGlRenderer = glGetString(GL_RENDERER);

         printf("GL_VERSION = %s\n", pszGlVersion);

         printf("GL_RENDERER = %s\n", pszGlRenderer);

      }

      //m_itaskGpu = ::current_itask();

      //return ::success;



   }


   // void context_egl::swap_buffers()
   // {
   //
   //    ::cast < ::gpu_opengl::device_egl > pegldevice = m_pgpudevice;
   //
   //    pegldevice->_swap_buffers();
   //
   // }


   void context_egl::__create_egl_window_surface(::acme::windowing::window * pacmewindowingwindow)
   {

      ::cast < ::gpu_opengl::device_egl > pegldevice = m_pgpudevice;

      auto egldisplay = pegldevice->m_egldisplay;

      if (egldisplay == EGL_NO_DISPLAY)
      {

         throw ::exception(::error_wrong_state);

      }

      EGLConfig eglconfig = pegldevice->m_eglconfigPrimary;

      if (eglconfig == EGL_NO_CONFIG_KHR)
      {

         throw ::exception(error_wrong_state);

      }

      auto window = (EGLNativeWindowType) pacmewindowingwindow->__x11_Window();

      if (window == None)
      {

         throw ::exception(error_wrong_state);

      }

#if WITH_X11

      // Get the visual ID from the EGL config
      EGLint visualId;
      eglGetConfigAttrib(egldisplay, eglconfig, EGL_NATIVE_VISUAL_ID, &visualId);
      information("EGL config visual ID: {}", visualId);

      // Get the X11 window's visual
      auto display = (Display*)pacmewindowingwindow->__x11_Display();
      XWindowAttributes attrs;
      XGetWindowAttributes(display, window, &attrs);
      information("X11 window visual ID: {}", attrs.visual->visualid);

      // They should match!
      if (visualId != (EGLint)attrs.visual->visualid) {
         warning("Visual ID mismatch! EGL={} X11={}", visualId, attrs.visual->visualid);
      }

#endif

      // Step 6 - Create a surface to draw to.
      m_eglsurface = eglCreateWindowSurface(egldisplay, eglconfig, window,nullptr);

      if (m_eglsurface == EGL_NO_SURFACE)
      {

         int iError = eglGetError();

         const ::scoped_string & scopedstrError = eglQueryString(egldisplay, iError);

         ::string strError;

         strError.formatf("Failed to create windwo surface (eglError: %s : 0x%x)", ::string(scopedstrError).c_str(), iError);

         warning() << strError;

         throw ::exception(::error_failed, strError);

      }

      m_bEGLWindowSurface = true;

   }


   void context_egl::_create_window_context(::acme::windowing::window* pacmewindowingwindow)
   {

      __create_egl_context();

      __create_egl_window_surface(pacmewindowingwindow);

      __on_after_egl_context_and_surface_creation();

   }


   void context_egl::__create_egl_pbuffer_surface(const ::int_size & size)
   {

      if (size.is_empty())
      {

         throw ::exception(error_bad_argument);

      }

      //__create_egl_context();

      //  auto pgpuapproach = m_papplication->get_gpu_approach();
      //
      ::cast < ::gpu_opengl::device_egl > pegldevice = m_pgpudevice;

      auto egldisplay = pegldevice->m_egldisplay;

      if (egldisplay == EGL_NO_DISPLAY)
      {

         throw ::exception(::error_wrong_state);

      }

      EGLConfig eglconfig = pegldevice->m_eglconfigPrimary;

      if (eglconfig == EGL_NO_CONFIG_KHR)
      {

         throw ::exception(error_wrong_state);

      }

      //
      //  defer_bind_egl_api();
      //
      //
      //  EGLint contextAttribs[] = {
      //     EGL_CONTEXT_MAJOR_VERSION, 3,
      //     EGL_CONTEXT_MINOR_VERSION, 3,
      //     //EGL_CONTEXT_OPENGL_PROFILE_MASK, EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT,
      //     // optional debug flag:
      //     //EGL_CONTEXT_FLAGS_KHR, EGL_CONTEXT_OPENGL_DEBUG_BIT_KHR,
      //     EGL_NONE
      // };      // Step 7 - Create a context.
      //  //EGLContext eglContext;
      //  m_eglcontext = eglCreateContext(egldisplay, eglconfig, pegldevice->m_eglcontextPrimary, contextAttribs);
      //  //qDebug() << "egl error" << eglGetError();
      //
      //  if (m_eglcontext == EGL_NO_CONTEXT)
      //  {
      //
      //     int iError = eglGetError();
      //
      //     const ::scoped_string & scopedstrError = eglQueryString(egldisplay, iError);
      //
      //     ::string strError;
      //
      //     strError.formatf("Failed to create context (eglError: %s : 0x%x)", ::string(scopedstrError).c_str(), iError);
      //
      //     warning() << strError;
      //
      //     throw ::exception(::error_failed, strError);
      //
      //  }
      //
      //  if (!pegldevice->m_eglcontextPrimary)
      //  {
      //
      //     pegldevice->m_eglcontextPrimary = m_eglcontext;
      //
      //  }

      EGLint pbufferAttribs[5];
      pbufferAttribs[0] = EGL_WIDTH;
      pbufferAttribs[1] = size.cx;
      pbufferAttribs[2] = EGL_HEIGHT;
      pbufferAttribs[3] = size.cy;
      pbufferAttribs[4] = EGL_NONE;

      // Step 6 - Create a surface to draw to.
      m_eglsurface = eglCreatePbufferSurface(egldisplay, eglconfig, pbufferAttribs);

      if (m_eglsurface == EGL_NO_SURFACE)
      {

         int iError = eglGetError();

         const ::scoped_string & scopedstrError = eglQueryString(egldisplay, iError);

         ::string strError;

         strError.formatf("Failed to create pbuffer surface (eglError: %s : 0x%x)", ::string(scopedstrError).c_str(), iError);

         warning() << strError;

         throw ::exception(::error_failed, strError);

      }

      // _on_after_context_and_surface_creation();

      // if (!is_glad_gl_loaded())
      // {
      //
      //    ::gpu::context_lock contextlock(this);
      //
      //    //_context_lock();
      //
      //    load_glad_gl();
      //
      //    auto pszGlVersion = glGetString(GL_VERSION);
      //
      //    auto pszGlRenderer = glGetString(GL_RENDERER);
      //
      //    printf("GL_VERSION = %s\n", pszGlVersion);
      //
      //    printf("GL_RENDERER = %s\n", pszGlRenderer);
      //
      // }
      //
      // //m_itaskGpu = ::current_itask();
      //
      // //return ::success;

   }



   // void context_egl::_create_window_buffer()
   // {
   //
   //    _create_egl_context(m_rectangle.size());
   //
   // }


   void context_egl::_create_cpu_buffer(const ::int_size & size)
   {

      if (size.is_empty())
      {

         throw ::exception(error_bad_argument);

      }

      __create_egl_context();

      __create_egl_pbuffer_surface(size);

      __on_after_egl_context_and_surface_creation();

//       auto pgpuapproach = m_papplication->get_gpu_approach();
//
// //      ::pointer<opengl>popengl = pgpu;
// //
// //      if (::is_null(popengl))
// //      {
// //
// //         return;
// //
// //      }
//
//       //m_itaskGpu = ::current_itask();
//
// //      unsigned long target = GL_TEXTURE_2D;
// //
// //      unsigned long internalFormat = GL_RGBA;
// //
// //      long max_level = 0;
// //
// //      CGLError error = CGLCreatePBuffer(size.cx, size.cy, target, internalFormat, max_level, &m_pbuffer);
// //
// //      if(error != kCGLNoError)
// //      {
// //
// //         return ::error_failed;
// //
// //      }
//
// //      EGLint attribList[]=
// //      {
// //
// //         EGL_SURFACE_TYPE, EGL_PBUFFER_BIT,
// //         EGL_RENDERABLE_TYPE, EGL_OPENGL_BIT,
// //         EGL_CONFORMANT, EGL_OPENGL_BIT,
// //         EGL_COLOR_BUFFER_TYPE, EGL_RGB_BUFFER,
// //         EGL_RED_SIZE, 8,
// //         EGL_GREEN_SIZE, 8,
// //         EGL_BLUE_SIZE, 8,
// //         EGL_ALPHA_SIZE, 8,
// //         EGL_LEVEL, 0,
// //         EGL_BUFFER_SIZE, 24,
// //         EGL_NONE
// //
// //      };
//       //check(InMajorVersion > 3 || (InMajorVersion == 3 && InMinorVersion >= 2));
//
// //       CGLPixelFormatAttribute AttribList[] =
// //       {
// //
// //          kCGLPFANoRecovery,
// //          //kCGLPFAAccelerated,
// //          //kCGLPFAOffScreen,
// //          kCGLPFAOpenGLProfile,
// //          (CGLPixelFormatAttribute)kCGLOGLPVersion_3_2_Core,
// //          kCGLPFAColorSize, (CGLPixelFormatAttribute)32,
// //          kCGLPFADepthSize, (CGLPixelFormatAttribute)16,
// //          (CGLPixelFormatAttribute)0
// //
// //       };
// //
// //
// // //      CGLPixelFormatAttribute attribs[] =
// // //      {
// // //          kCGLPFAOffScreen,
// // //          kCGLPFAColorSize, 32,
// // //          NULL
// // //      } ;
// // //      CGLPixelFormatObj pixelFormatObj ;
// // //      long numPixelFormats ;
// // //      CGLChoosePixelFormat( attribs, &pixelFormatObj, &numPixelFormats ) ;
// //
// //       CGLPixelFormatObj PixelFormat;
// //
// //       GLint NumFormats = 0;
// //
// //       auto error = CGLChoosePixelFormat(AttribList, &PixelFormat, &NumFormats);
// //
// //       if(error != kCGLNoError)
// //       {
// //
// //          //return ::error_failed;
// //
// //          return;
// //
// //       }
// //
// //       error = CGLCreateContext(PixelFormat, NULL, &m_context);
// //
// //       if(error != kCGLNoError)
// //       {
// //
// //          //return ::error_failed;
// //
// //          return;
// //
// //       }
// //
// //       error = CGLDestroyPixelFormat(PixelFormat);
// //
// //       if(error != kCGLNoError)
// //       {
// //
// //          //return ::error_failed;
// //
// //          return;
// //
// //       }
// //
// //       defer_make_current();
// //       //::e_status estatus = make_current();
// //
// // //      if(!estatus)
// // //      {
// // //
// // //         //return estatus;
// // //
// // //         return;
// // //
// // //      }
// //
// //       auto cx = context::m_pcpubuffer->m_pimagetarget->m_pimage->width();
// //       auto cy = context::m_pcpubuffer->m_pimagetarget->m_pimage->height();
// //       auto scan = context::m_pcpubuffer->m_pimagetarget->m_pimage->m_iScan;
// //       auto data=context::m_pcpubuffer->m_pimagetarget->m_pimage->data();
// //
// //       error = CGLSetOffScreen(m_context, cx,
// //                               cy, scan, data) ;
// //
// //       if(error != kCGLNoError)
// //       {
// //
// //          //return ::error_failed;
// //
// //          return;
// //
// //       }
//
//       ::cast < ::gpu_opengl::device_egl > pegldevice = m_pgpudevice;
//
//       auto egldisplay = pegldevice->m_egldisplay;
//
//       auto & eglconfig = pegldevice->m_eglconfig;
//
//       defer_bind_egl_api();
//
//
//       EGLint pbufferAttribs[5];
//       pbufferAttribs[0] = EGL_WIDTH;
//       pbufferAttribs[1] = size.cx;
//       pbufferAttribs[2] = EGL_HEIGHT;
//       pbufferAttribs[3] = size.cy;
//       pbufferAttribs[4] = EGL_NONE;
//
//       // Step 6 - Create a surface to draw to.
//       m_eglsurface = eglCreatePbufferSurface(egldisplay, eglconfig, pbufferAttribs);
//
//       if (m_eglsurface == EGL_NO_SURFACE)
//       {
//
//          int iError = eglGetError();
//
//          const ::scoped_string & scopedstrError = eglQueryString(egldisplay, iError);
//
//          fprintf(stderr, "Failed to create pbuffer surface (eglError: %s : 0x%x)\n", ::string(scopedstrError).c_str(), iError);
//
//          throw ::exception(::error_failed);
//
//       }
//
//       EGLint contextAttribs[] =
//       {
//          EGL_CONTEXT_MAJOR_VERSION, 3, // Specifies OpenGL ES 3.0.
//          EGL_CONTEXT_MINOR_VERSION, 3, // Specifies OpenGL ES 3.0.
//          EGL_NONE
//      };
//       // Step 7 - Create a context.
//       //EGLContext eglContext;
//       m_eglcontext = eglCreateContext(egldisplay, eglconfig, NULL, contextAttribs);
//       //qDebug() << "egl error" << eglGetError();
//
//       if (m_eglcontext == EGL_NO_CONTEXT)
//       {
//
//          int iError = eglGetError();
//
//          const ::scoped_string & scopedstrError = eglQueryString(egldisplay, iError);
//
//          fprintf(stderr, "Failed to create context (eglError: %s : 0x%x)\n", ::string(scopedstrError).c_str(), iError);
//
//          throw ::exception(::error_failed);
//
//       }
//
//       // Make the context current
//       if (!eglMakeCurrent(egldisplay, m_eglsurface, m_eglsurface, m_eglcontext))
//       {
//          throw ::exception(error_wrong_state);
//
//
//       }
//
//       //m_itaskGpu = ::current_itask();
//
//       //return ::success;

   }


   // void context_egl::defer_make_current()
   // {
   //
   //
   //    //
   //    //
   //    // CGLError error = CGLSetCurrentContext(m_context);
   //    //
   //    // bool bMakeCurrentOk = error == kCGLNoError;
   //    //
   //    // if (!bMakeCurrentOk)
   //    // {
   //    //
   //    //    printf("eglMakeCurrent failed!\n");
   //    //
   //    //    //return ::error_failed;
   //    //
   //    //    return;
   //    //
   //    // }
   //    //
   //    // //return ::success;
   //
   //    auto psystem = system();
   //
   //    auto papproach = psystem->m_papplicationMain->gpu_approach();
   //
   //    auto pgpudevice = papproach->get_gpu_device();
   //
   //    ::cast < ::gpu_opengl::device_egl > pegldevice = pgpudevice;
   //
   //    auto egldisplay = pegldevice->m_egldisplay;
   //
   //    if (egldisplay == EGL_NO_DISPLAY)
   //    {
   //
   //       throw ::exception(error_wrong_state);
   //
   //    }
   //
   //    if (m_eglcontext && m_eglsurface)
   //    {
   //
   //       //auto & eglconfig = pegldevice->m_eglconfig;
   //
   //       if (!eglMakeCurrent(egldisplay, m_eglsurface, m_eglsurface, m_eglcontext))
   //       {
   //
   //          auto error = eglGetError();
   //          ::string strMessage;
   //
   //          strMessage << "eglMakeCurrent failed: " << eglErrorString(error) ;
   //          warning() << strMessage;
   //          throw ::exception(error_wrong_state,strMessage);
   //
   //       }
   //
   //    }
   //
   //
   // }


//   void context_egl::_create_offscreen_window(const int_size& size)
//   {

//      _create_egl_context(size);

//   }


   void context_egl::destroy_cpu_buffer()
   {

      ::cast < ::gpu_opengl::device_egl > pegldevice = m_pgpudevice;

      auto egldisplay = pegldevice->m_egldisplay;
      //
      //
      // CGLError error = CGLSetCurrentContext(m_contextOld);
      //
      // if(error != kCGLNoError)
      // {
      //
      //    //return ::error_failed;
      //
      // }
      
      //return ::success;

      if (!eglMakeCurrent(egldisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT))
      {

         throw ::exception(error_wrong_state);

      }


   }


   string context_egl::get_shader_version_text()
   {

      return "version 300 es";

   }


   void context_egl::_translate_shader(string_array_base & stra)
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



   void context_egl::_context_lock()
   {

      ::cast < ::gpu_opengl::device_egl > pegldevice = m_pgpudevice;

      _synchronous_lock synchronouslock(pegldevice->synchronization());

      auto egldisplay = pegldevice->m_egldisplay;

      //auto eglcontextCurrent = eglGetCurrentContext();

      //if (eglcontextCurrent != m_eglcontext)
      //{

        // defer_bind_egl_api();

         // Make the context current
         if (!eglMakeCurrent(egldisplay, m_eglsurface, m_eglsurface, m_eglcontext))
         {

            int iError = eglGetError();

            auto pszError = eglQueryString(egldisplay, iError);

            ::string strError;

            strError.formatf("Failed to set current egl context/surface (eglError: %s : 0x%x)", pszError, iError);

            warning() << strError;

            throw ::exception(error_wrong_state, strError);

         }

//      load_glad_gl();



         // load_glad_gl();

      //}
      // else
      // {
      //
      //    information() << "Context is already current";
      //
      // }

   }


   void context_egl::_context_unlock()
   {

      ::cast < ::gpu_opengl::device_egl > pegldevice = m_pgpudevice;

      _synchronous_lock synchronouslock(pegldevice->synchronization());

      auto egldisplay = pegldevice->m_egldisplay;

      if (!eglMakeCurrent(egldisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT))
      {

         int iError = eglGetError();

         const ::scoped_string & scopedstrError = eglQueryString(egldisplay, iError);

         ::string strError;

         strError.formatf("Failed to clear current egl context/surface (eglError: %s : 0x%x)", ::string(scopedstrError).c_str(), iError);

         warning() << strError;

         throw ::exception(error_wrong_state, strError);

      }

   }


   void context_egl::assert_there_is_current_context()
   {

      auto eglcontextCurrent = eglGetCurrentContext();

      if (eglcontextCurrent == EGL_NO_CONTEXT)
      {

         throw ::exception(error_wrong_state);

      }

   }


   void context_egl::swap_buffers()
   {

      if (m_eoutput != ::gpu::e_output_swap_chain)
      {

         throw ::exception(error_wrong_state);

      }

      ::cast < ::gpu_opengl::device_egl > pegldevice = m_pgpudevice;

      auto egldisplay = pegldevice->m_egldisplay;

      EGLint width, height;
      eglQuerySurface(egldisplay, m_eglsurface, EGL_WIDTH, &width);
      eglQuerySurface(egldisplay, m_eglsurface, EGL_HEIGHT, &height);
      debug("EGL surface created: {}x{}", width, height);

      // Check what framebuffer is currently bound
      GLint currentFB = 0;
      glGetIntegerv(GL_FRAMEBUFFER_BINDING, &currentFB);
      debug("Current framebuffer bound: {}", currentFB);

      // Read a pixel from the center to see what's actually there
      GLubyte pixel[4];
      glReadPixels(width/2, height/2, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, pixel);
      debug("Center pixel color: R={} G={} B={} A={}", pixel[0], pixel[1], pixel[2], pixel[3]);

      // Check for GL errors
      GLenum glError = glGetError();
      if (glError != GL_NO_ERROR) {
         warning("OpenGL error before swap: 0x{:x}", glError);
      }

      if (!eglSwapBuffers(egldisplay, m_eglsurface))
      {

         int iError = eglGetError();

         const ::scoped_string & scopedstrError = eglQueryString(egldisplay, iError);

         ::string strError;

         strError.formatf("Failed to clear current egl context/surface (eglError: %s : 0x%x)", ::string(scopedstrError).c_str(), iError);

         warning() << strError;

         throw ::exception(error_wrong_state, strError);

      }

#if 0
#if WITH_X11

      auto pacmewindowingwindow = m_pgpudevice->m_pwindow;
      // Force X11 to update
      auto display = (Display*)pacmewindowingwindow->__x11_Display();
      auto window = (Window)pacmewindowingwindow->__x11_Window();
      XFlush(display);
      XSync(display, False);

      XWindowAttributes attrs;
      XGetWindowAttributes(display, window, &attrs);
      debug("Window map state: {}", attrs.map_state); // Should be 2 (IsViewable)

#endif
#endif

      // if (m_bEGLWindowSurface)
      // {
      //
      //    information() << "seems this is the swap chain context";
      //
      // }

   }


} // namespace gpu_opengl



