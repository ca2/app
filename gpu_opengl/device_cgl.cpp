#include "framework.h"
#include "_gpu_opengl.h"
#include "approach.h"
#include "context.h"
#include "device_cgl.h"
#include "context_cgl.h"
#include "swap_chain.h"
#include "acme/platform/application.h"
#include "acme/windowing/display.h"
#include "acme/windowing/windowing.h"
#include "aura/platform/system.h"
#include "aura/windowing/window.h"

int rotating_cube();

//////#include "_opengl.h"
//////
//extern "C"
//{
//GLAPI int gladLoadCGL(void);
//
//} // extern "C"

//const char* eglErrorString(EGLint error) {
//   switch (error) {
//      case EGL_SUCCESS: return "EGL_SUCCESS";
//      case EGL_NOT_INITIALIZED: return "EGL_NOT_INITIALIZED";
//      case EGL_BAD_ACCESS: return "EGL_BAD_ACCESS";
//      case EGL_BAD_ALLOC: return "EGL_BAD_ALLOC";
//      case EGL_BAD_ATTRIBUTE: return "EGL_BAD_ATTRIBUTE";
//      case EGL_BAD_CONTEXT: return "EGL_BAD_CONTEXT";
//      case EGL_BAD_CONFIG: return "EGL_BAD_CONFIG";
//      case EGL_BAD_CURRENT_SURFACE: return "EGL_BAD_CURRENT_SURFACE";
//      case EGL_BAD_DISPLAY: return "EGL_BAD_DISPLAY";
//      case EGL_BAD_SURFACE: return "EGL_BAD_SURFACE";
//      case EGL_BAD_MATCH: return "EGL_BAD_MATCH";
//      case EGL_BAD_PARAMETER: return "EGL_BAD_PARAMETER";
//      case EGL_BAD_NATIVE_PIXMAP: return "EGL_BAD_NATIVE_PIXMAP";
//      case EGL_BAD_NATIVE_WINDOW: return "EGL_BAD_NATIVE_WINDOW";
//      case EGL_CONTEXT_LOST: return "EGL_CONTEXT_LOST";
//      default: return "Unknown error";
//   }
//}
#include <dlfcn.h>

namespace gpu_opengl
{

//   //bool g_bEglOpened = false;
//   //EGLDisplay g_egldisplay = nullptr;
//   //EGLConfig  g_eglconfig;
//   thread_local bool t_bEglApiBound = false;
//   bool g_bGladGL = false;
//   //critical_section g_criticalsectionEgl;
//
//   bool is_glad_gl_loaded()
//   {
//
//      return g_bGladGL;
//
//   }
//
//// --- Step A: Define a loader function for GLAD ---
//// CGL doesn't have a simple "GetProcAddress" function, so we use
//// dlsym to look up symbols from the OpenGL framework.
//void* GetCGLProcAddress(const char* name) {
//    static void* handle = dlopen("/System/Library/Frameworks/OpenGL.framework/Versions/Current/OpenGL", RTLD_NOW);
//    return dlsym(handle, name);
//}
////
////   // should be called within a currently selected egl context
//   void load_glad_cgl()
//   {
//
//      if (g_bGladGL)
//      {
//
//          return;
//
//      }
//
//      g_bGladGL = true;
//
//      auto gl_version = gladLoadGLLoader((GLADloadproc)GetCGLProcAddress);
//
//      if (!gl_version)
//      {
//
//         printf("Unable to reload GL.\n");
//
//         throw ::exception(::error_failed);
//
//      }
//
//      auto pszGlVersion = glGetString(GL_VERSION);
//
//      auto pszGlRenderer = glGetString(GL_RENDERER);
//
//      printf("GL_VERSION = %s\n", pszGlVersion);
//
//      printf("GL_RENDERER = %s\n", pszGlRenderer);
//
//
//      //printf("has GLES3: %d\n", GLAD_GL_ES_VERSION_3_0);
//
//      //printf("Loaded GL %d.%d after reload.\n",
//      //     GLAD_VERSION_MAJOR(gl_version), GLAD_VERSION_MINOR(gl_version));
//
//   }
//
//
//   // critical_section * egl_critical_section()
//   // {
//   //    return &g_criticalsectionEgl;
//   // }
//
////    EGLDisplay egl_open_display()
////    {
////
////       if (g_bEglOpened)
////       {
////
////          return g_egldisplay;
////
////       }
////
////       g_bEglOpened = true;
////
////       EGLint attribList[]=
////       {
////
////          EGL_SURFACE_TYPE, EGL_PBUFFER_BIT,
//// /// ;;;        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
////          //EGL_CONFORMANT, EGL_OPENGL_BIT,
////          //EGL_COLOR_BUFFER_TYPE, EGL_RGB_BUFFER,
////          EGL_RED_SIZE, 8,
////          EGL_GREEN_SIZE, 8,
////          EGL_BLUE_SIZE, 8,
////          EGL_ALPHA_SIZE, 8,
////          //EGL_LEVEL, 0,
////          //EGL_BUFFER_SIZE, 24,
////          EGL_NONE
////
////       };
////
////       //synchronous_lock synchronouslock(x11_mutex(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
////
////       //xdisplay display(x11_get_display());
////
////       //m_display = eglGetDisplay((EGLNativeDisplayType)display);
////
////       //m_display = eglGetDisplay((EGLNativeDisplayType)0);
////       auto egldisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
////
////       if (egldisplay == EGL_NO_DISPLAY)
////       {
////
////          fprintf(stderr, "Got no EGL display.\n");
////
////          throw ::exception(::error_failed);
////
////       }
////
////       if (!eglInitialize(egldisplay, NULL, NULL))
////       {
////
////          fprintf(stderr, "Unable to initialize EGL\n");
////
////          throw ::exception(::error_failed);
////
////       }
////
////
////
////       // Choose an EGLConfig
////       //EGLConfig config;
////       EGLint numConfigs;
////       EGLint configAttribs[] = {EGL_RENDERABLE_TYPE, EGL_OPENGL_BIT, EGL_NONE};
////       if (!eglChooseConfig(egldisplay, configAttribs, &g_eglconfig, 1, &numConfigs))
////       {
////
////          int iError = eglGetError();
////
////          const ::scoped_string & scopedstrError = eglQueryString(egldisplay, iError);
////
////          fprintf(stderr, "Failed to choose config (eglError: %s : 0x%x)\n", ::string(scopedstrError).c_str(), iError);
////
////          throw ::exception(::error_failed);
////
////       }
////
////       if (numConfigs != 1)
////       {
////
////          fprintf(stderr, "Didn't get just one config, but %d\n", numConfigs);
////
////          throw ::exception(::error_failed);
////
////       }
////
////       g_egldisplay = egldisplay;
////
////       //#if OSMESA_MAJOR_VERSION * 100 + OSMESA_MINOR_VERSION >= 305
////       //   /* specify Z, stencil, accum sizes */
////       //   m_mesacontext = OSMesaCreateContextExt( GL_RGBA, 16, 0, 0, NULL );
////       //#else
////       //   m_mesacontext = OSMesaCreateContext( GL_RGBA, NULL );
////       //#endif
////       //   if (!m_mesacontext)
////       //   {
////       //
////       //      printf("OSMesaCreateContext failed!\n");
////       //
////       //      return 0;
////       //
////       //   }
////       //g_bEglOpened = true;
////
////       return g_egldisplay;
////
////    }
//
//   void defer_bind_egl_api()
//   {
//
//      if (t_bEglApiBound)
//      {
//
//         return;
//
//      }
//
//      t_bEglApiBound=true;
//
////#ifdef LINUX
////
////      eglBindAPI(EGL_OPENGL_API);
////
////#else
////
////      eglBindAPI(EGL_OPENGL_ES_API);
////
////      //  auto egl_version = gladLoadEGL();
////      //  if (!egl_version) {
////      //        printf("Unable to reload EGL.\n");
////      //        throw ::exception(::error_failed);
////      //     }
////      // printf("Loaded EGL %d.%d after reload.\n",
////      //        GLAD_VERSION_MAJOR(egl_version), GLAD_VERSION_MINOR(egl_version));
////
////
////#endif
//
//
//
//   }

   //::pointer <::gpu::context > allocate_egl_context(::particle * pparticle)
   //{

     // return pparticle->øcreate_new < device_cgl >();

   //}


   device_cgl::device_cgl()
{m_cglcontextShare = 0;

      m_cglpixelformat = 0;
      
//      m_egldisplay = EGL_NO_DISPLAY;
//      m_eglconfigPBuffer = EGL_NO_CONFIG_KHR;
//      m_eglconfigWindow = EGL_NO_CONFIG_KHR;
//      //m_eglconfigPrimary = EGL_NO_CONFIG_KHR;
//      //m_eglconfigSwapChainWindow = EGL_NO_CONFIG_KHR;
//      m_eglcontextPrimary = EGL_NO_CONTEXT;
//      m_lX11NativeVisualId = -1;
//      gladLoadGL();

//#if !defined(__ANDROID__)
//
//      if (glewInit() != GLEW_NO_ERROR)
//      {
//         //cout << "Failed to initialize GLEW... " << endl;
//         //return -1;
//
//      }
//
//#endif

      //m_emode = e_mode_egl;

   }


   device_cgl::~device_cgl()
   {

      _destroy_cgl_device();

   }


   void device_cgl::initialize_gpu_device_for_swap_chain(::gpu::approach* papproach, ::windowing::window* pwindow)
   {

      ::gpu::device::initialize_gpu_device_for_swap_chain(papproach, pwindow);

      m_pgpuapproach = papproach;
      m_pwindow = pwindow;
      //m_bAddSwapChainSupport = true;
      //m_hwnd = (HWND) m_pwindow->oswindow();

      //auto size = m_pwindow->get_window_rectangle().size();
      
      pwindow->_lock_window_gpu_context();

      _create_device({});
      
      pwindow->_unlock_window_gpu_context();


   }


   void device_cgl::initialize_gpu_device_for_off_screen(::gpu::approach* papproach, const ::int_rectangle& rectanglePlacement)
   {

      ::gpu::device::initialize_gpu_device_for_off_screen(papproach, rectanglePlacement);

      m_pgpuapproach = papproach;
      m_pwindow = m_papplication->m_pacmeuserinteractionMain->window();
      //m_bAddSwapChainSupport = false;
      //::cast < ::windowing_win32::window > pwin32window = m_pwindow;
      //m_hwnd = pwin32window->m_hwnd;

      _create_device(rectanglePlacement.size());


      // fork([]()
      // {
      //
      //
      //    rotating_cube();
      //
      // });

   }

   void device_cgl::_defer_create_offscreen_window(const ::int_size& size)
   {

   }

   // void device_cgl::_opengl_lock()
   // {
   //    //critical_section_lock lock(egl_critical_section());
   //    // Make the context current
   //    // if (!eglMakeCurrent(m_egldisplay, m_eglsurface, m_eglsurface, m_eglcontext))
   //    // {
   //    //
   //    //    auto error = eglGetError();
   //    //    ::string strMessage;
   //    //
   //    //    strMessage << "eglMakeCurrent failed: " << eglErrorString(error) ;
   //    //    warning() << strMessage;
   //    //    throw ::exception(error_wrong_state,strMessage);
   //    //
   //    // }
   //
   //    //m_itaskGpu = ::current_itask();
   //
   // }
   //
   //
   // void device_cgl::_opengl_unlock()
   // {
   //
   //    //critical_section_lock lock(egl_critical_section());
   //
   //    // if (!eglMakeCurrent(m_egldisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT))
   //    // {
   //    //
   //    //    throw ::exception(error_wrong_state);
   //    //
   //    // }
   //
   // }


   ::pointer < ::gpu::context > device_cgl::allocate_context()
   {

      ::pointer < ::gpu::context > pgpucontext;

      pgpucontext=øcreate_new < ::gpu_opengl::context_cgl>();

      return pgpucontext;

   }


   //void device_cgl::create_context()
   void device_cgl::_create_device(const ::int_size & size)
   {

//      if (m_egldisplay != EGL_NO_DISPLAY)
//      {
//
//         return;
//
//      }

      auto psystem = system();

      auto pgpu = application()->gpu_approach();

      ::pointer<::gpu_opengl::approach> papproach = pgpu;

      if (::is_null(papproach))
      {

         throw ::exception(::error_failed);

      }

      //defer_bind_egl_api();

//    critical_section_lock lockEgl(egl_critical_section());


//    m_egldisplay = egl_open_display();


//    EGLint attribList[]=
//       {
//
//          EGL_SURFACE_TYPE, EGL_PBUFFER_BIT,
// /// ;;;        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
//          //EGL_CONFORMANT, EGL_OPENGL_BIT,
//          //EGL_COLOR_BUFFER_TYPE, EGL_RGB_BUFFER,
//          EGL_RED_SIZE, 8,
//          EGL_GREEN_SIZE, 8,
//          EGL_BLUE_SIZE, 8,
//          EGL_ALPHA_SIZE, 8,
//          //EGL_LEVEL, 0,
//          //EGL_BUFFER_SIZE, 24,
//          EGL_NONE
//
//       };

      //synchronous_lock synchronouslock(x11_mutex(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      //xdisplay display(x11_get_display());

      //m_display = eglGetDisplay((EGLNativeDisplayType)display);

      
      
      CGLPixelFormatAttribute AttribList[] =
      {
         
         kCGLPFANoRecovery,
         //kCGLPFAAccelerated,
         //kCGLPFAOffScreen,
         kCGLPFAOpenGLProfile,
         (CGLPixelFormatAttribute)kCGLOGLPVersion_3_2_Core,
         kCGLPFAColorSize, (CGLPixelFormatAttribute)32,
         kCGLPFADepthSize, (CGLPixelFormatAttribute)16,
         (CGLPixelFormatAttribute)0
         
      };

      GLint NumFormats = 0;
      
      auto error = CGLChoosePixelFormat(AttribList, &m_cglpixelformat, &NumFormats);
      
      if(error != kCGLNoError)
      {
         
         //return ::error_failed;
         
         return;
         
      }

//      auto pwindowing = psystem->acme_windowing();
//
//      auto pdisplay = pwindowing->acme_display();
//
//      auto pDisplay = (Display *) pdisplay->_get_x11_display();
//
//      //m_display = eglGetDisplay((EGLNativeDisplayType)0);
//      //auto egldisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
//      auto egldisplay = eglGetDisplay(pDisplay);
//
//      if (egldisplay == EGL_NO_DISPLAY)
//      {
//
//         ::warning("Got no EGL display.");
//
//         throw ::exception(::error_failed);
//
//      }
//
//      EGLint eglMajor = 0;
//
//      EGLint eglMinor = 0;
//
//      if (!eglInitialize(egldisplay, &eglMajor, &eglMinor))
//      {
//
//         ::warning("Unable to initialize EGL");
//
//         throw ::exception(::error_failed);
//
//      }
//
//      information("eglInitialize Succeeded: major={}, minor={}", eglMajor, eglMinor);
//
//      m_egldisplay = egldisplay;
//

//       // Choose an EGLConfig
//       //EGLConfig config;
//       EGLint numConfigs2;
//       EGLint configAttribs2[] = {EGL_RENDERABLE_TYPE, EGL_OPENGL_BIT,
//
//          EGL_RED_SIZE,   8,
// EGL_GREEN_SIZE, 8,
// EGL_BLUE_SIZE,  8,
// EGL_ALPHA_SIZE, 8,  // IMPORTANT
//          EGL_DEPTH_SIZE, 24,
//          EGL_NONE};
//       if (!eglChooseConfig(egldisplay, configAttribs2, &m_eglconfigPrimary, 1, &numConfigs2))
//       {
//
//          int iError = eglGetError();
//
//          const ::scoped_string & scopedstrError = eglQueryString(egldisplay, iError);
//
//          fprintf(stderr, "Failed to choose config (eglError: %s : 0x%x)\n", ::string(scopedstrError).c_str(), iError);
//
//          throw ::exception(::error_failed);
//
//       }
//
//       if (numConfigs2 != 1)
//       {
//
//          fprintf(stderr, "Didn't get just one config, but %d\n", numConfigs2);
//
//          throw ::exception(::error_failed);
//
//       }


      // // Choose an EGLConfig
      // // EGLConfig config;
      // // EGLint numConfigs2;
      // EGLint configAttribs2[] =
      // {
      //    EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
      //    EGL_RENDERABLE_TYPE, EGL_OPENGL_BIT,
      //    EGL_RED_SIZE,   8,
      //    EGL_GREEN_SIZE, 8,
      //    EGL_BLUE_SIZE,  8,
      //    EGL_ALPHA_SIZE, 8,  // IMPORTANT
      //    EGL_DEPTH_SIZE, 24,
      //    EGL_NONE
      // };
      //
      // EGLint numWindowConfig = 0;
      //
      // if (!eglChooseConfig(egldisplay, configAttribs2, &m_eglconfigWindow, 1, &numWindowConfig))
      // {
      //
      //    int iError = eglGetError();
      //
      //    const ::scoped_string & scopedstrError = eglQueryString(egldisplay, iError);
      //
      //    fprintf(stderr, "Failed to choose config (eglError: %s : 0x%x)\n", ::string(scopedstrError).c_str(), iError);
      //
      //    throw ::exception(::error_failed);
      //
      // }
      //
      // if (numWindowConfig != 1)
      // {
      //
      //    fprintf(stderr, "Didn't get just one config, but %d\n", numWindowConfig);
      //
      //    throw ::exception(::error_failed);
      //
      // }
      //
      // EGLint visualid = -1;
      //
      // if (!eglGetConfigAttrib(egldisplay, m_eglconfigWindow, EGL_NATIVE_VISUAL_ID, &visualid))
      // {
      //
      //    int iError = eglGetError();
      //
      //    const ::scoped_string & scopedstrError = eglQueryString(egldisplay, iError);
      //
      //    fprintf(stderr, "Failed to get X11 Native Visual Id(eglError: %s : 0x%x)\n", ::string(scopedstrError).c_str(), iError);
      //
      //    throw ::exception(::error_failed);
      //
      // }
      //
      // m_lX11NativeVisualId = visualid;

      //long l = -1;

//      if (!_find_config_for_pbuffer(m_eglconfigPBuffer, false))
//      {
//
//         warning("Couldn't find p-buffer config with transparent visual");
//
//         if (_find_config_for_pbuffer(m_eglconfigPBuffer, true))
//         {
//
//            warning("An couldn't find p-buffer config with opaque visual");
//
//            throw ::exception(::error_failed);
//
//         }
//
//      }

//      if (m_eglconfigPBuffer == EGL_NO_CONFIG_KHR)
//      {
//
//         throw ::exception(::error_failed);
//
//      }

      // defer_bind_egl_api();
      //
      //
      // EGLint pbufferAttribs[5];
      // pbufferAttribs[0] = EGL_WIDTH;
      // pbufferAttribs[1] = size.cx;
      // pbufferAttribs[2] = EGL_HEIGHT;
      // pbufferAttribs[3] = size.cy;
      // pbufferAttribs[4] = EGL_NONE;
      //
      // // Step 6 - Create a surface to draw to.
      // m_eglsurface = eglCreatePbufferSurface(m_egldisplay, g_eglconfig, pbufferAttribs);
      //
      // if (m_eglsurface == EGL_NO_SURFACE)
      // {
      //
      //    int iError = eglGetError();
      //
      //    const ::scoped_string & scopedstrError = eglQueryString(m_egldisplay, iError);
      //
      //    fprintf(stderr, "Failed to create pbuffer surface (eglError: %s : 0x%x)\n", ::string(scopedstrError).c_str(), iError);
      //
      //    throw ::exception(::error_failed);
      //
      // }
      //
      // EGLint contextAttribs[] =
      // {
      //     EGL_CONTEXT_MAJOR_VERSION, 3, // Specifies OpenGL ES 3.0.
      //     EGL_CONTEXT_MINOR_VERSION, 3, // Specifies OpenGL ES 3.0.
      //     EGL_NONE
      // };
      // // Step 7 - Create a context.
      // //EGLContext eglContext;
      // m_eglcontext = eglCreateContext(m_egldisplay, g_eglconfig, NULL, contextAttribs);
      // //qDebug() << "egl error" << eglGetError();
      //
      // if (m_eglcontext == EGL_NO_CONTEXT)
      // {
      //
      //    int iError = eglGetError();
      //
      //    const ::scoped_string & scopedstrError = eglQueryString(m_egldisplay, iError);
      //
      //    fprintf(stderr, "Failed to create context (eglError: %s : 0x%x)\n", ::string(scopedstrError).c_str(), iError);
      //
      //    throw ::exception(::error_failed);
      //
      // }
      //
      // // Make the context current
      // if (!eglMakeCurrent(m_egldisplay, m_eglsurface, m_eglsurface, m_eglcontext))
      // {
      //    throw ::exception(error_wrong_state);
      //
      //
      // }
      //
      // m_itaskGpu = ::current_itask();

      //gladLoadGL();
      
      
      
      
      //load_glad_cgl();

      // auto gl_version = gladLoadGL();
      // if (!gl_version) {
      //    printf("Unable to reload GL.\n");
      //    throw ::exception(::error_failed);
      // }
      // //printf("Loaded GL %d.%d after reload.\n",
      // //     GLAD_VERSION_MAJOR(gl_version), GLAD_VERSION_MINOR(gl_version));

      // if (!eglMakeCurrent(m_egldisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT))
      // {
      //
      //    throw ::exception(error_wrong_state);
      //
      // }

      // return ::success;

   }



//   bool device_cgl::_simplified_find_config_for_x11_window2(EGLConfig & eglconfig, long lX11VisualId, bool bOpaque)
//   {
//
//      auto psystem = system();
//
//      auto pwindowing = psystem->acme_windowing();
//
//      auto pdisplay = pwindowing->acme_display();
//
//      auto pDisplay = (Display *) pdisplay->_get_x11_display();
//
//      auto egldisplay = m_egldisplay;
//
//      if (egldisplay == EGL_NO_DISPLAY)
//      {
//
//         throw ::exception(error_wrong_state);
//
//      }
//
//      // XVisualInfo argbVisual = {};
//      //
//      // XMatchVisualInfo(pDisplay, DefaultScreen(pDisplay), 32, TrueColor, &argbVisual);
//      //
//      information("_simplified_find_config_for_x11_window2 X11 visual id = {}", lX11VisualId);
//
//      int depthFind;
//
//      if (bOpaque)
//      {
//
//         depthFind = 24;
//
//      }
//      else
//      {
//
//         depthFind = 32;
//
//      }
//
//      EGLint cfg_attribs[] = {
//         EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
//         EGL_RENDERABLE_TYPE, EGL_OPENGL_BIT,
//
//         EGL_RED_SIZE,   8,
//         EGL_GREEN_SIZE, 8,
//         EGL_BLUE_SIZE,  8,
//         EGL_ALPHA_SIZE, 8,
//         EGL_DEPTH_SIZE, 24,
//         EGL_STENCIL_SIZE, 8,
//
//         //EGL_NATIVE_VISUAL_ID, argbVisual.visualid,
//         EGL_NATIVE_VISUAL_ID, (EGLint) lX11VisualId,
//         EGL_NONE
//     };
//
//      //EGLConfig configs[64];
//
//      //EGLint count = 0;
//
//      EGLConfig config{};
//      EGLint num = 0;
//      if (!eglChooseConfig(egldisplay, cfg_attribs, &config, 1, &num) || num != 1)
//      {
//         ::string strError("eglChooseConfig failed");
//         information(strError);
//         throw ::exception(::error_failed, strError);
//         return false;
//      }
//      EGLint visualid{};
//      if (!eglGetConfigAttrib(egldisplay, config, EGL_NATIVE_VISUAL_ID, &visualid))
//      {
//
//         throw ::exception(::error_failed);
//
//      }
//      // Step 4 below
//      EGLint configId = EGL_NONE;
//      if (! eglGetConfigAttrib(egldisplay, config, EGL_CONFIG_ID, &configId))
//      {
//
//         throw ::exception(::error_failed);
//      }
//
//      eglconfig = config;
//
//      //lX11VisualId = argbVisual.visualid;
//
//      return true;
//
//   }
//
//
//   bool device_cgl::_simplified_find_config_for_x11_window4(EGLConfig & eglconfig, long lX11VisualId, bool bOpaque)
//   {
//
//      auto psystem = system();
//
//      auto pwindowing = psystem->acme_windowing();
//
//      auto pdisplay = pwindowing->acme_display();
//
//      auto pDisplay = (Display *) pdisplay->_get_x11_display();
//
//      auto egldisplay = m_egldisplay;
//
//      if (egldisplay == EGL_NO_DISPLAY)
//      {
//
//         throw ::exception(error_wrong_state);
//
//      }
//
//      information("_find_config_for_x11_window X11 visual id = {}", m_lX11NativeVisualId);
//
//      int depthFind;
//
//      if (bOpaque)
//      {
//
//         depthFind = 24;
//
//      }
//      else
//      {
//
//         depthFind = 32;
//
//      }
//
//      EGLint configAttributes[] = {
//         EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
//         //EGL_RENDERABLE_TYPE, EGL_OPENGL_BIT,
//         //EGL_COLOR_BUFFER_TYPE, EGL_RGB_BUFFER,
//         //EGL_NATIVE_VISUAL_ID, (EGLint) argbVisual.visualid,
//         EGL_RED_SIZE,   8,
//         EGL_GREEN_SIZE, 8,
//         EGL_BLUE_SIZE,  8,
//         EGL_ALPHA_SIZE, 8,  // IMPORTANT
//         //EGL_DEPTH_SIZE, 24,
//         EGL_NONE
//      };
//
//      EGLConfig configs[64];
//
//      EGLint count = 0;
//
//      if (!eglChooseConfig(egldisplay, configAttributes, configs, 64, &count))
//      {
//
//         throw ::exception(::error_failed);
//
//      }
//
//      information("eglChooseConfig found {} of up to {} configs", count, 64);
//
//      EGLConfig eglconfigBest = EGL_NO_CONFIG_KHR;
//
//      EGLint bestId = INT_MAX;
//
//      //int iBestVisualId = -1;
//
//      for (int i = 0; i < count; ++i)
//      {
//
//         EGLint surfacetype = 0;
//         EGLint renderabletype = 0;
//         EGLint red = 0;
//         EGLint green = 0;
//         EGLint blue = 0;
//         EGLint alpha = 0;
//         EGLint depth = 0;
//         EGLint stencil = 0;
//         EGLint visualid = 0;
//         EGLint conformant = 0;
//         EGLint colorbuffertype = 0;
//         EGLint level = 0;
////         EGLint visualtype = 0;
//
//         EGLConfig config = configs[i];
//
//         if (!eglGetConfigAttrib(egldisplay, config, EGL_SURFACE_TYPE, &surfacetype))
//         {
//
//            throw ::exception(::error_failed);
//
//         }
//         if (!eglGetConfigAttrib(egldisplay, config, EGL_CONFORMANT, &conformant))
//         {
//
//            throw ::exception(::error_failed);
//
//         }
//         if (!eglGetConfigAttrib(egldisplay, config, EGL_RENDERABLE_TYPE, &renderabletype))
//          {
//
//             throw ::exception(::error_failed);
//
//          }
//         if (!eglGetConfigAttrib(egldisplay, config, EGL_LEVEL, &level))
//         {
//
//            throw ::exception(::error_failed);
//
//         }
//         if (!eglGetConfigAttrib(egldisplay, config, EGL_COLOR_BUFFER_TYPE, &colorbuffertype))
//         {
//
//            throw ::exception(::error_failed);
//
//         }
//         if (!eglGetConfigAttrib(egldisplay, config, EGL_RED_SIZE, &red))
//         {
//
//            throw ::exception(::error_failed);
//
//         }
//         if (!eglGetConfigAttrib(egldisplay, config, EGL_GREEN_SIZE, &green))
//         {
//
//            throw ::exception(::error_failed);
//
//         }
//         if (!eglGetConfigAttrib(egldisplay, config, EGL_BLUE_SIZE, &blue))
//         {
//
//            throw ::exception(::error_failed);
//
//         }
//         if (!eglGetConfigAttrib(egldisplay, config, EGL_ALPHA_SIZE, &alpha))
//         {
//
//            throw ::exception(::error_failed);
//
//         }
//         if (!eglGetConfigAttrib(egldisplay, config, EGL_DEPTH_SIZE, &depth))
//         {
//
//            throw ::exception(::error_failed);
//
//         }
//         if (!eglGetConfigAttrib(egldisplay, config, EGL_STENCIL_SIZE, &stencil))
//         {
//
//            throw ::exception(::error_failed);
//
//         }
//         if (!eglGetConfigAttrib(egldisplay, config, EGL_NATIVE_VISUAL_ID, &visualid))
//         {
//
//            throw ::exception(::error_failed);
//
//         }
//         // Step 4 below
//         EGLint configId = EGL_NONE;
//         if (! eglGetConfigAttrib(egldisplay, config, EGL_CONFIG_ID, &configId))
//         {
//
//            throw ::exception(::error_failed);
//         }
//         information("");
//         information("configs[{}] visualid={} configid={}", i, visualid, configId);
//
//         // if (!eglGetConfigAttrib(egldisplay, config, EGL_NATIVE_VISUAL_TYPE, &vid))
//         // {
//         //
//         //    throw ::exception(::error_failed);
//         //
//         // }
//
//         //if (visualid != argbVisual.visualid)
//         //{
//           // continue;
//
//         //}
//
//
//         if (alpha != 8)
//            continue;
//         if (red != 8)
//            continue;
//         if (green != 8)
//            continue;
//         if (blue != 8)
//            continue;
//         information("r={}, g={}, b={}, a={}, depth={}", red, green, blue, alpha, depth);
//         if (depth != 24)
//         {
//            information("Bad EGLConfig? Depth size isn't 24?!");
//
//            continue;
//         }
//         if (stencil != 8)
//         {
//            information("Bad EGLConfig? Stencil size isn't 8?!");
//
//            continue;
//         }
//         if (!(renderabletype & EGL_OPENGL_BIT))
//         {
//            information("Bad EGLConfig? Renderable Type Not OpenGL?!");
//            continue;
//         }
//         if (!(conformant & EGL_OPENGL_BIT))
//         {
//            information("Bad EGLConfig? Not OpenGL Conformant?!");
//            continue;
//         }
//         if (level != 0)
//         {
//            information("Bad EGLConfig? Expect level 0?!");
//            continue;
//         }
//         if (colorbuffertype != EGL_RGB_BUFFER)
//         {
//            information("Bad EGLConfig? Not EGL_RGB_BUFFER?!");
//            continue;
//
//         }
//
//
//         //if (bForWindow)
//         {
//            if ((surfacetype &(EGL_WINDOW_BIT))!= (EGL_WINDOW_BIT))
//            {
//               information("Bad EGLConfig? No EGL_WINDOW_BIT");
//               continue;
//            }
//         }
//         // else
//         // {
//         //    if ((surfacetype &(EGL_PBUFFER_BIT))!= (EGL_PBUFFER_BIT))
//         //       continue;
//         // }
//         // //if (visualtype != EGL_X11_VISUAL_TYPE)
//         //   // continue;
//         //
//         // if (bForWindow)
//         // {
//
//            EGLint caveat = EGL_NONE;
//         if (!eglGetConfigAttrib(egldisplay, config, EGL_CONFIG_CAVEAT, &caveat))
//         {
//
//            throw ::exception(::error_failed);
//
//         }
//            if (caveat != EGL_NONE)
//            {
//               information("Bad EGLConfig? there's some EGL_CONFIG_CAVEAT");
//               continue; // reject slow / non-conformant
//            }
//
//            EGLint surfaceType = EGL_NONE;
//         if (!eglGetConfigAttrib(egldisplay, config, EGL_SURFACE_TYPE, &surfaceType))
//         {
//
//            throw ::exception(::error_failed);
//
//         }
//            if (!(surfaceType & EGL_WINDOW_BIT))
//            {
//               information("Bad EGLConfig? No EGL_WINDOW_BIT");
//               continue;
//            }
//
//            EGLint bindRGBA = EGL_NONE;
//         if (!eglGetConfigAttrib(egldisplay, config, EGL_BIND_TO_TEXTURE_RGBA, &bindRGBA))
//         {
//
//            throw ::exception(::error_failed);
//
//         }
//            if (!bindRGBA)
//            {
//               information("Bad EGLConfig? No EGL_BIND_TO_TEXTURE_RGBA");
//               continue;
//            }
//
//            EGLint maxW = 0;
//            EGLint maxH = 0;
//            if (!eglGetConfigAttrib(egldisplay, config, EGL_MAX_PBUFFER_WIDTH, &maxW))
//            {
//
//               information("Couldn't get max width");
//
//               maxW = INT_MAX;
//
//            }
//            if (!eglGetConfigAttrib(egldisplay, config, EGL_MAX_PBUFFER_HEIGHT, &maxH))
//            {
//
//               information("Couldn't get max height");
//
//               maxH = INT_MAX;
//
//            }
//            if (maxW < 1920)
//            {
//
//               information("Bad EGLConfig? maximum width lesser than 1920");
//               continue; // reject slow / non-conformant
//
//
//            }
//         if (maxW < 1080)
//         {
//
//            information("Bad EGLConfig? maximum height lesser than 1080");
//            continue; // reject slow / non-conformant
//
//
//         }
//
//
//         //}
//
//         //if (0)
//         {
//            XVisualInfo visualinfoTemplate = {};
//            visualinfoTemplate.visualid = visualid;
//
//            int n = 0;
//            XVisualInfo* pvisualinfo = XGetVisualInfo(
//                pDisplay,
//                VisualIDMask,
//                &visualinfoTemplate,
//                &n
//            );
//
//            if (!pvisualinfo || n <= 0)
//            {
//
//               continue;
//
//            }
//
//            int iDepth =pvisualinfo->depth;
//            XFree(pvisualinfo);
//            pvisualinfo = nullptr;
//
//            if (iDepth != depthFind)
//            {
//
//               information("depth is {}, expect {}", iDepth, depthFind);
//
//               continue;
//
//            }
//            information("Depth is {}, it is a match.", iDepth);
//         }
//
//               ///eglconfig = config;
//
//               //lX11VisualId = visualid;
//
//         if (visualid != lX11VisualId)
//         {
//            information("visualid {} doesn't match {}", visualid, lX11VisualId);
//
//            continue;
//
//         }
//
//         information("visualid {} matches expected.", visualid);
//
//               if (configId >= bestId)
//               {
//                  information("configid {} isn't lower than best id so far {}", configId, bestId);
//                  continue;
//               }
//
//         if (bestId == INT_MAX)
//         {
//
//            information("found first match with id {}", configId);
//
//         }
//         else
//         {
//
//            information("found a better id {} than {}", configId, bestId);
//
//         }
//
//
//                  eglconfigBest = config;
//                  bestId = configId;
//                  //iBestVisualId = visualid;
//
//
////               XFree(pvisualinfo);
//
//  //             return true;
//
//            //}
//
//
//         //}
//         // else
//         // {
//         //
//         //    eglconfig = config;
//         //
//         //    lX11VisualId = -1;
//         //
//         //    return true;
//         //
//         // }
//
//      }
//
//      if (bestId == INT_MAX)
//      {
//
//         return false;
//
//      }
//
//      information("Best found id is {} with visual id {}", bestId, lX11VisualId);
//
//      eglconfig = eglconfigBest;
//
//      //lX11VisualId = iBestVisualId;
//
//      return true;
//
//   }

//
//   bool device_cgl::_simplified_find_config_for_x11_window1(EGLConfig & eglconfig, long & lX11VisualId, bool bOpaque)
//   {
//
//      auto psystem = system();
//
//      auto pwindowing = psystem->acme_windowing();
//
//      auto pdisplay = pwindowing->acme_display();
//
//      auto pDisplay = (Display *) pdisplay->_get_x11_display();
//
//      auto egldisplay = m_egldisplay;
//
//      if (egldisplay == EGL_NO_DISPLAY)
//      {
//
//         throw ::exception(error_wrong_state);
//
//      }
//
//      XVisualInfo argbVisual = {};
//
//      XMatchVisualInfo(pDisplay, DefaultScreen(pDisplay), 32, TrueColor, &argbVisual);
//
//      information("_simplified_find_config_for_x11_window X11 visual id = {}", argbVisual.visualid);
//
//      int depthFind;
//
//      if (bOpaque)
//      {
//
//         depthFind = 24;
//
//      }
//      else
//      {
//
//         depthFind = 32;
//
//      }
//
//      EGLint cfg_attribs[] = {
//         EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
//         EGL_RENDERABLE_TYPE, EGL_OPENGL_BIT,
//
//         EGL_RED_SIZE,   8,
//         EGL_GREEN_SIZE, 8,
//         EGL_BLUE_SIZE,  8,
//         EGL_ALPHA_SIZE, 8,
//
//         EGL_NATIVE_VISUAL_ID, argbVisual.visualid,
//         EGL_NONE
//     };
//
//      //EGLConfig configs[64];
//
//      //EGLint count = 0;
//
//      EGLConfig cfg{};
//      EGLint num = 0;
//      if (!eglChooseConfig(egldisplay, cfg_attribs, &cfg, 1, &num) || num != 1)
//      {
//         ::string strError("eglChooseConfig failed");
//         information(strError);
//         throw ::exception(::error_failed, strError);
//         return false;
//      }
//
//      eglconfig = cfg;
//
//      lX11VisualId = argbVisual.visualid;
//
//      return true;
//
//   }
//
//
//   bool device_cgl::_find_config_for_x11_window1(EGLConfig & eglconfig, long & lX11VisualId, bool bOpaque)
//   {
//
//      auto psystem = system();
//
//      auto pwindowing = psystem->acme_windowing();
//
//      auto pdisplay = pwindowing->acme_display();
//
//      auto pDisplay = (Display *) pdisplay->_get_x11_display();
//
//      auto egldisplay = m_egldisplay;
//
//      if (egldisplay == EGL_NO_DISPLAY)
//      {
//
//         throw ::exception(error_wrong_state);
//
//      }
//
//      XVisualInfo argbVisual = {};
//
//      {
//
//#if 1
//
//         // XVisualInfo visualinfo2={};
//
//         XMatchVisualInfo(pDisplay, DefaultScreen(pDisplay), 32, TrueColor, &argbVisual);
//
//#else
//
//         XVisualInfo vtemplate = {};
//         vtemplate.screen = DefaultScreen(pDisplay);
//         vtemplate.depth  = 32;
//         vtemplate.c_class  = TrueColor;
//
//         int nvis = 0;
//         XVisualInfo* visuals = XGetVisualInfo(
//             pDisplay,
//             VisualScreenMask | VisualDepthMask | VisualClassMask,
//             &vtemplate,
//             &nvis
//         );
//
//         if (!visuals || nvis == 0)
//         {
//            // No ARGB visual → compositor transparency not possible
//            return false;
//         }
//
//         argbVisual = visuals[0];
//
//         XFree(visuals);
//
//#endif
//
//      }
//
//      information("_find_config_for_x11_window X11 visual id = {}", argbVisual.visualid);
//
//      int depthFind;
//
//      if (bOpaque)
//      {
//
//         depthFind = 24;
//
//      }
//      else
//      {
//
//         depthFind = 32;
//
//      }
//
//      EGLint configAttributes[] = {
//         EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
//         //EGL_RENDERABLE_TYPE, EGL_OPENGL_BIT,
//         //EGL_COLOR_BUFFER_TYPE, EGL_RGB_BUFFER,
//         //EGL_NATIVE_VISUAL_ID, (EGLint) argbVisual.visualid,
//         EGL_RED_SIZE,   8,
//         EGL_GREEN_SIZE, 8,
//         EGL_BLUE_SIZE,  8,
//         EGL_ALPHA_SIZE, 8,  // IMPORTANT
//         //EGL_DEPTH_SIZE, 24,
//         EGL_NONE
//      };
//
//      EGLConfig configs[64];
//
//      EGLint count = 0;
//
//      if (!eglChooseConfig(egldisplay, configAttributes, configs, 64, &count))
//      {
//
//         throw ::exception(::error_failed);
//
//      }
//
//      information("eglChooseConfig found {} of up to {} configs", count, 64);
//
//      EGLConfig eglconfigBest = EGL_NO_CONFIG_KHR;
//
//      EGLint bestId = INT_MAX;
//
//      int iBestVisualId = -1;
//
//      for (int i = 0; i < count; ++i)
//      {
//
//         EGLint surfacetype = 0;
//         EGLint renderabletype = 0;
//         EGLint red = 0;
//         EGLint green = 0;
//         EGLint blue = 0;
//         EGLint alpha = 0;
//         EGLint depth = 0;
//         EGLint stencil = 0;
//         EGLint visualid = 0;
//         EGLint conformant = 0;
//         EGLint colorbuffertype = 0;
//         EGLint level = 0;
////         EGLint visualtype = 0;
//
//         EGLConfig config = configs[i];
//
//         if (!eglGetConfigAttrib(egldisplay, config, EGL_SURFACE_TYPE, &surfacetype))
//         {
//
//            throw ::exception(::error_failed);
//
//         }
//         if (!eglGetConfigAttrib(egldisplay, config, EGL_CONFORMANT, &conformant))
//         {
//
//            throw ::exception(::error_failed);
//
//         }
//         if (!eglGetConfigAttrib(egldisplay, config, EGL_RENDERABLE_TYPE, &renderabletype))
//          {
//
//             throw ::exception(::error_failed);
//
//          }
//         if (!eglGetConfigAttrib(egldisplay, config, EGL_LEVEL, &level))
//         {
//
//            throw ::exception(::error_failed);
//
//         }
//         if (!eglGetConfigAttrib(egldisplay, config, EGL_COLOR_BUFFER_TYPE, &colorbuffertype))
//         {
//
//            throw ::exception(::error_failed);
//
//         }
//         if (!eglGetConfigAttrib(egldisplay, config, EGL_RED_SIZE, &red))
//         {
//
//            throw ::exception(::error_failed);
//
//         }
//         if (!eglGetConfigAttrib(egldisplay, config, EGL_GREEN_SIZE, &green))
//         {
//
//            throw ::exception(::error_failed);
//
//         }
//         if (!eglGetConfigAttrib(egldisplay, config, EGL_BLUE_SIZE, &blue))
//         {
//
//            throw ::exception(::error_failed);
//
//         }
//         if (!eglGetConfigAttrib(egldisplay, config, EGL_ALPHA_SIZE, &alpha))
//         {
//
//            throw ::exception(::error_failed);
//
//         }
//         if (!eglGetConfigAttrib(egldisplay, config, EGL_DEPTH_SIZE, &depth))
//         {
//
//            throw ::exception(::error_failed);
//
//         }
//         if (!eglGetConfigAttrib(egldisplay, config, EGL_STENCIL_SIZE, &stencil))
//         {
//
//            throw ::exception(::error_failed);
//
//         }
//         if (!eglGetConfigAttrib(egldisplay, config, EGL_NATIVE_VISUAL_ID, &visualid))
//         {
//
//            throw ::exception(::error_failed);
//
//         }
//         // Step 4 below
//         EGLint configId = EGL_NONE;
//         if (! eglGetConfigAttrib(egldisplay, config, EGL_CONFIG_ID, &configId))
//         {
//
//            throw ::exception(::error_failed);
//         }
//         information("");
//         information("configs[{}] visualid={} configid={}", i, visualid, configId);
//
//         // if (!eglGetConfigAttrib(egldisplay, config, EGL_NATIVE_VISUAL_TYPE, &vid))
//         // {
//         //
//         //    throw ::exception(::error_failed);
//         //
//         // }
//
//         //if (visualid != argbVisual.visualid)
//         //{
//           // continue;
//
//         //}
//
//
//         if (alpha != 8)
//            continue;
//         if (red != 8)
//            continue;
//         if (green != 8)
//            continue;
//         if (blue != 8)
//            continue;
//         information("r={}, g={}, b={}, a={}, depth={}", red, green, blue, alpha, depth);
//         if (depth != 24)
//         {
//            information("Bad EGLConfig? Depth size isn't 24?!");
//
//            continue;
//         }
//         if (stencil != 8)
//         {
//            information("Bad EGLConfig? Stencil size isn't 8?!");
//
//            continue;
//         }
//         if (!(renderabletype & EGL_OPENGL_BIT))
//         {
//            information("Bad EGLConfig? Renderable Type Not OpenGL?!");
//            continue;
//         }
//         if (!(conformant & EGL_OPENGL_BIT))
//         {
//            information("Bad EGLConfig? Not OpenGL Conformant?!");
//            continue;
//         }
//         if (level != 0)
//         {
//            information("Bad EGLConfig? Expect level 0?!");
//            continue;
//         }
//         if (colorbuffertype != EGL_RGB_BUFFER)
//         {
//            information("Bad EGLConfig? Not EGL_RGB_BUFFER?!");
//            continue;
//
//         }
//
//
//         //if (bForWindow)
//         {
//            if ((surfacetype &(EGL_WINDOW_BIT))!= (EGL_WINDOW_BIT))
//            {
//               information("Bad EGLConfig? No EGL_WINDOW_BIT");
//               continue;
//            }
//         }
//         // else
//         // {
//         //    if ((surfacetype &(EGL_PBUFFER_BIT))!= (EGL_PBUFFER_BIT))
//         //       continue;
//         // }
//         // //if (visualtype != EGL_X11_VISUAL_TYPE)
//         //   // continue;
//         //
//         // if (bForWindow)
//         // {
//
//            EGLint caveat = EGL_NONE;
//         if (!eglGetConfigAttrib(egldisplay, config, EGL_CONFIG_CAVEAT, &caveat))
//         {
//
//            throw ::exception(::error_failed);
//
//         }
//            if (caveat != EGL_NONE)
//            {
//               information("Bad EGLConfig? there's some EGL_CONFIG_CAVEAT");
//               continue; // reject slow / non-conformant
//            }
//
//            EGLint surfaceType = EGL_NONE;
//         if (!eglGetConfigAttrib(egldisplay, config, EGL_SURFACE_TYPE, &surfaceType))
//         {
//
//            throw ::exception(::error_failed);
//
//         }
//            if (!(surfaceType & EGL_WINDOW_BIT))
//            {
//               information("Bad EGLConfig? No EGL_WINDOW_BIT");
//               continue;
//            }
//
//            EGLint bindRGBA = EGL_NONE;
//         if (!eglGetConfigAttrib(egldisplay, config, EGL_BIND_TO_TEXTURE_RGBA, &bindRGBA))
//         {
//
//            throw ::exception(::error_failed);
//
//         }
//            if (!bindRGBA)
//            {
//               information("Bad EGLConfig? No EGL_BIND_TO_TEXTURE_RGBA");
//               continue;
//            }
//
//            EGLint maxW = 0;
//            EGLint maxH = 0;
//            if (!eglGetConfigAttrib(egldisplay, config, EGL_MAX_PBUFFER_WIDTH, &maxW))
//            {
//
//               information("Couldn't get max width");
//
//               maxW = INT_MAX;
//
//            }
//            if (!eglGetConfigAttrib(egldisplay, config, EGL_MAX_PBUFFER_HEIGHT, &maxH))
//            {
//
//               information("Couldn't get max height");
//
//               maxH = INT_MAX;
//
//            }
//            if (maxW < 1920)
//            {
//
//               information("Bad EGLConfig? maximum width lesser than 1920");
//               continue; // reject slow / non-conformant
//
//
//            }
//         if (maxW < 1080)
//         {
//
//            information("Bad EGLConfig? maximum height lesser than 1080");
//            continue; // reject slow / non-conformant
//
//
//         }
//
//
//         //}
//
//         //if (0)
//         {
//            XVisualInfo visualinfoTemplate = {};
//            visualinfoTemplate.visualid = visualid;
//
//            int n = 0;
//            XVisualInfo* pvisualinfo = XGetVisualInfo(
//                pDisplay,
//                VisualIDMask,
//                &visualinfoTemplate,
//                &n
//            );
//
//            if (!pvisualinfo || n <= 0)
//            {
//
//               continue;
//
//            }
//
//            int iDepth =pvisualinfo->depth;
//            XFree(pvisualinfo);
//            pvisualinfo = nullptr;
//
//            if (iDepth != depthFind)
//            {
//
//               information("depth is {}, expect {}", iDepth, depthFind);
//
//               continue;
//
//            }
//            information("Depth is {}, it is a match.", iDepth);
//         }
//
//               ///eglconfig = config;
//
//               //lX11VisualId = visualid;
//
//         if (visualid != argbVisual.visualid)
//         {
//            information("visualid {} doesn't match {}", visualid, argbVisual.visualid);
//
//            continue;
//
//         }
//
//         information("visualid {} matches expected.", visualid);
//
//               if (configId >= bestId)
//               {
//                  information("configid {} isn't lower than best id so far {}", configId, bestId);
//                  continue;
//               }
//
//         if (bestId == INT_MAX)
//         {
//
//            information("found first match with id {}", configId);
//
//         }
//         else
//         {
//
//            information("found a better id {} than {}", configId, bestId);
//
//         }
//
//
//                  eglconfigBest = config;
//                  bestId = configId;
//                  iBestVisualId = visualid;
//
//
////               XFree(pvisualinfo);
//
//  //             return true;
//
//            //}
//
//
//         //}
//         // else
//         // {
//         //
//         //    eglconfig = config;
//         //
//         //    lX11VisualId = -1;
//         //
//         //    return true;
//         //
//         // }
//
//      }
//
//      if (bestId == INT_MAX)
//      {
//
//         return false;
//
//      }
//
//      information("Best found id is {} with visual id {}", bestId, iBestVisualId);
//
//      eglconfig = eglconfigBest;
//
//      lX11VisualId = iBestVisualId;
//
//      return true;
//
//   }
//
//
//   bool device_cgl::_find_config_for_pbuffer(EGLConfig & eglconfig, bool bOpaque)
//   {
//
//      int depthFind;
//
//      if (bOpaque)
//      {
//
//         depthFind = 24;
//
//      }
//      else
//      {
//
//         depthFind = 32;
//
//      }
//
//      auto psystem = system();
//
//      auto pwindowing = psystem->acme_windowing();
//
//      auto pdisplay = pwindowing->acme_display();
//
//      auto pDisplay = (Display *) pdisplay->_get_x11_display();
//
//      auto egldisplay = m_egldisplay;
//
//      if (egldisplay == EGL_NO_DISPLAY)
//      {
//
//         throw ::exception(error_wrong_state);
//
//      }
//
//      EGLint configAttributes[] = {
//         EGL_SURFACE_TYPE, EGL_PBUFFER_BIT,
//         EGL_RENDERABLE_TYPE, EGL_OPENGL_BIT,
//         EGL_COLOR_BUFFER_TYPE, EGL_RGB_BUFFER,
//         EGL_RED_SIZE,   8,
//         EGL_GREEN_SIZE, 8,
//         EGL_BLUE_SIZE,  8,
//         EGL_ALPHA_SIZE, 8,  // IMPORTANT
//         EGL_DEPTH_SIZE, 24,
//         EGL_STENCIL_SIZE, 8,
//         EGL_NONE
//      };
//
//      EGLConfig configs[64];
//      EGLint count = 0;
//
//      if (!eglChooseConfig(egldisplay, configAttributes, configs, 64, &count))
//      {
//
//         throw ::exception(::error_failed);
//
//      }
//
//      information("eglChooseConfig found {} of up to {} configs", count, 64);
//
//      for (int i = 0; i < count; ++i)
//      {
//
//         EGLint surfacetype = 0;
//         //EGLint renderabletype = 0;
//         EGLint red = 0;
//         EGLint green = 0;
//         EGLint blue = 0;
//         EGLint alpha = 0;
//         EGLint visualid = 0;
//         EGLint depth = 0;
//         EGLint stencil = 0;
////         EGLint visualtype = 0;
//
//         EGLConfig config = configs[i];
//
//         if (!eglGetConfigAttrib(egldisplay, config, EGL_SURFACE_TYPE, &surfacetype))
//         {
//
//            throw ::exception(::error_failed);
//
//         }
//         // if (!eglGetConfigAttrib(egldisplay, config, EGL_RENDERABLE_TYPE, &renderabletype))
//         // {
//         //
//         //    throw ::exception(::error_failed);
//         //
//         // }
//         if (!eglGetConfigAttrib(egldisplay, config, EGL_RED_SIZE, &red))
//         {
//
//            throw ::exception(::error_failed);
//
//         }
//         if (!eglGetConfigAttrib(egldisplay, config, EGL_GREEN_SIZE, &green))
//         {
//
//            throw ::exception(::error_failed);
//
//         }
//         if (!eglGetConfigAttrib(egldisplay, config, EGL_BLUE_SIZE, &blue))
//         {
//
//            throw ::exception(::error_failed);
//
//         }
//         if (!eglGetConfigAttrib(egldisplay, config, EGL_ALPHA_SIZE, &alpha))
//         {
//
//            throw ::exception(::error_failed);
//
//         }
//         if (!eglGetConfigAttrib(egldisplay, config, EGL_DEPTH_SIZE, &depth))
//         {
//
//            throw ::exception(::error_failed);
//
//         }
//         if (!eglGetConfigAttrib(egldisplay, config, EGL_STENCIL_SIZE, &stencil))
//         {
//
//            throw ::exception(::error_failed);
//
//         }
//         if (!eglGetConfigAttrib(egldisplay, config, EGL_NATIVE_VISUAL_ID, &visualid))
//         {
//
//            throw ::exception(::error_failed);
//
//         }
//         // if (!eglGetConfigAttrib(egldisplay, config, EGL_NATIVE_VISUAL_TYPE, &vid))
//         // {
//         //
//         //    throw ::exception(::error_failed);
//         //
//         // }
//
//         if (alpha != 8)
//            continue;
//         if (red != 8)
//            continue;
//         if (green != 8)
//            continue;
//         if (blue != 8)
//            continue;
//         if (depth != 24)
//            continue;
//         if (stencil != 8)
//            continue;
//         // if (!(renderabletype & EGL_OPENGL_BIT))
//         //    continue;
//         // if (bForWindow)
//         // {
//         //    if ((surfacetype &(EGL_WINDOW_BIT))!= (EGL_WINDOW_BIT))
//         //       continue;
//         // }
//         // else
//         // {
//            if ((surfacetype &(EGL_PBUFFER_BIT))!= (EGL_PBUFFER_BIT))
//               continue;
////         }
//         //if (visualtype != EGL_X11_VISUAL_TYPE)
//           // continue;
//
//         // if (bForWindow)
//         // {
//         //
//         //    EGLint caveat;
//         //    eglGetConfigAttrib(egldisplay, c, EGL_CONFIG_CAVEAT, &caveat);
//         //    if (caveat != EGL_NONE)
//         //       continue; // reject slow / non-conformant
//         //
//         //    EGLint surfaceType;
//         //    eglGetConfigAttrib(egldisplay, c, EGL_SURFACE_TYPE, &surfaceType);
//         //    if (!(surfaceType & EGL_WINDOW_BIT))
//         //       continue;
//         //
//         //    EGLint bindRGBA;
//         //    eglGetConfigAttrib(egldisplay, c, EGL_BIND_TO_TEXTURE_RGBA, &bindRGBA);
//         //    if (!bindRGBA)
//         //       continue;
//         //
//         //    EGLint maxW, maxH;
//         //    eglGetConfigAttrib(egldisplay, c, EGL_MAX_PBUFFER_WIDTH, &maxW);
//         //    eglGetConfigAttrib(egldisplay, c, EGL_MAX_PBUFFER_HEIGHT, &maxH);
//         //    if (maxW < 1024 || maxH < 1024)
//         //       continue;
//         //
//         //    // Step 4 below
//         //    EGLint configId;
//         //    eglGetConfigAttrib(egldisplay, c, EGL_CONFIG_ID, &configId);
//         //
//         //    if (configId < bestId)
//         //    {
//         //       best = c;
//         //       bestId = configId;
//         //    }
//         // }
//         //    XVisualInfo visualinfoTemplate = {};
//         //    visualinfoTemplate.visualid = visualid;
//         //
//         //    int n = 0;
//         //    XVisualInfo* pvisualinfo = XGetVisualInfo(
//         //        pDisplay,
//         //        VisualIDMask,
//         //        &visualinfoTemplate,
//         //        &n
//         //    );
//         //
//         //    if (!pvisualinfo || n <= 0)
//         //    {
//         //
//         //       continue;
//         //
//         //    }
//         //
//         //    if (pvisualinfo->depth == depthFind)
//         //    {
//         //
//         //       eglconfig = config;
//         //
//         //       lX11VisualId = visualid;
//         //
//         //       XFree(pvisualinfo);
//         //
//         //       return true;
//         //
//         //    }
//         //
//         //    XFree(pvisualinfo);
//         //
//         // }
//         // else
//         {
//
//            eglconfig = config;
//
////            lX11VisualId = -1;
//
//            return true;
//
//         }
//
//      }
//
//      return false;
//
//   }
//

//   void device_cgl::_create_offscreen_buffer(const ::int_size & size)
//   {
//
//      auto psystem = system();
//
//      auto pgpu = application()->get_gpu();
//
//      ::pointer<opengl>popengl = pgpu;
//
//      if (::is_null(popengl))
//      {
//
//         throw ::exception(::error_failed);
//
//      }
//
//      EGLint attribList[]=
//      {
//
//         EGL_SURFACE_TYPE, EGL_PBUFFER_BIT,
//         EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
//         //EGL_CONFORMANT, EGL_OPENGL_BIT,
//         //EGL_COLOR_BUFFER_TYPE, EGL_RGB_BUFFER,
//         EGL_RED_SIZE, 8,
//         EGL_GREEN_SIZE, 8,
//         EGL_BLUE_SIZE, 8,
//         EGL_ALPHA_SIZE, 8,
//         //EGL_LEVEL, 0,
//         //EGL_BUFFER_SIZE, 24,
//         EGL_NONE
//
//      };
//
//      //synchronous_lock synchronouslock(x11_mutex(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
//
//      //xdisplay display(x11_get_display());
//
//      //m_display = eglGetDisplay((EGLNativeDisplayType)display);
//
//      m_display = eglGetDisplay((EGLNativeDisplayType)0);
//
//      if (m_display == EGL_NO_DISPLAY)
//      {
//
//         fprintf(stderr, "Got no EGL display.\n");
//
//         throw ::exception(::error_failed);
//
//      }
//
//      if (!eglInitialize(m_display, NULL, NULL))
//      {
//
//         fprintf(stderr, "Unable to initialize EGL\n");
//
//         throw ::exception(::error_failed);
//
//      }
//
//      eglBindAPI(EGL_OPENGL_ES_API);
//
//      int iConfigCount = 0;
//
//      if (!eglChooseConfig(m_display, attribList, &m_config, 1, &iConfigCount))
//      {
//
//         int iError = eglGetError();
//
//         const ::scoped_string & scopedstrError = eglQueryString(m_display, iError);
//
//         fprintf(stderr, "Failed to choose config (eglError: %s : 0x%x)\n", ::string(scopedstrError).c_str(), iError);
//
//         throw ::exception(::error_failed);
//
//      }
//
//      if (iConfigCount != 1)
//      {
//
//         fprintf(stderr, "Didn't get just one config, but %d\n", iConfigCount);
//
//         throw ::exception(::error_failed);
//
//      }
//
//      //#if OSMESA_MAJOR_VERSION * 100 + OSMESA_MINOR_VERSION >= 305
//      //   /* specify Z, stencil, accum sizes */
//      //   m_mesacontext = OSMesaCreateContextExt( GL_RGBA, 16, 0, 0, NULL );
//      //#else
//      //   m_mesacontext = OSMesaCreateContext( GL_RGBA, NULL );
//      //#endif
//      //   if (!m_mesacontext)
//      //   {
//      //
//      //      printf("OSMesaCreateContext failed!\n");
//      //
//      //      return 0;
//      //
//      //   }
//
//      EGLint pbufferAttribs[5];
//      pbufferAttribs[0] = EGL_WIDTH;
//      pbufferAttribs[1] = size.cx;
//      pbufferAttribs[2] = EGL_HEIGHT;
//      pbufferAttribs[3] = size.cy;
//      pbufferAttribs[4] = EGL_NONE;
//
//      // Step 6 - Create a surface to draw to.
//      m_surface = eglCreatePbufferSurface(m_display, m_config, pbufferAttribs);
//
//      if (m_surface == EGL_NO_SURFACE)
//      {
//
//         throw ::exception(::error_failed);
//
//      }
//
//      EGLint contextAttribs[] =
//      {
//          EGL_CONTEXT_MAJOR_VERSION, 3, // Specifies OpenGL ES 3.0.
//          EGL_CONTEXT_MINOR_VERSION, 0, // Specifies OpenGL ES 3.0.
//          EGL_NONE
//      };
//      // Step 7 - Create a context.
//      //EGLContext eglContext;
//      m_context = eglCreateContext(m_display, m_config, NULL, contextAttribs);
//      //qDebug() << "egl error" << eglGetError();
//
//      if (m_context == EGL_NO_CONTEXT)
//      {
//
//         //qDebug() << "context issue";
//         throw ::exception(::error_failed);
//
//      }
//
//      m_itaskGpu = ::current_itask();
//
//      //return ::success;
//
//   }



   // void device_cgl::initialize_gpu_device_for_off_screen(::gpu::approach* papproach, const ::int_rectangle& rectanglePlacement)
   // {
   //
   //    auto psystem = system();
   //
   //    auto pgpu = application()->get_gpu();
   //
   //    ::pointer<opengl>popengl = pgpu;
   //
   //    if (::is_null(popengl))
   //    {
   //
   //       throw ::exception(::error_failed);
   //
   //    }
   //
   //    EGLint attribList[]=
   //    {
   //
   //       EGL_SURFACE_TYPE, EGL_PBUFFER_BIT,
   //       EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
   //       //EGL_CONFORMANT, EGL_OPENGL_BIT,
   //       //EGL_COLOR_BUFFER_TYPE, EGL_RGB_BUFFER,
   //       EGL_RED_SIZE, 8,
   //       EGL_GREEN_SIZE, 8,
   //       EGL_BLUE_SIZE, 8,
   //       EGL_ALPHA_SIZE, 8,
   //       //EGL_LEVEL, 0,
   //       //EGL_BUFFER_SIZE, 24,
   //       EGL_NONE
   //
   //    };
   //
   //    //synchronous_lock synchronouslock(x11_mutex(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
   //
   //    //xdisplay display(x11_get_display());
   //
   //    //m_display = eglGetDisplay((EGLNativeDisplayType)display);
   //
   //    m_display = eglGetDisplay((EGLNativeDisplayType)0);
   //
   //    if (m_display == EGL_NO_DISPLAY)
   //    {
   //
   //       errorf("Got no EGL display.");
   //
   //       throw ::exception(::error_failed);
   //
   //    }
   //
   //    if (!eglInitialize(m_display, NULL, NULL))
   //    {
   //
   //       errorf("Unable to initialize EGL");
   //
   //       throw ::exception(::error_failed);
   //
   //    }
   //
   //    eglBindAPI(EGL_OPENGL_ES_API);
   //
   //    int iConfigCount = 0;
   //
   //    if (!eglChooseConfig(m_display, attribList, &m_config, 1, &iConfigCount))
   //    {
   //
   //       int iError = eglGetError();
   //
   //       const ::scoped_string & scopedstrError = eglQueryString(m_display, iError);
   //
   //       errorf("Failed to choose config (eglError: %s : 0x%x)", ::string(scopedstrError).c_str(), iError);
   //
   //       throw ::exception(::error_failed);
   //
   //    }
   //
   //    if (iConfigCount != 1)
   //    {
   //
   //       errorf("Didn't get just one config, but %d", iConfigCount);
   //
   //       throw ::exception(::error_failed);
   //
   //    }
   //
   //    //#if OSMESA_MAJOR_VERSION * 100 + OSMESA_MINOR_VERSION >= 305
   //    //   /* specify Z, stencil, accum sizes */
   //    //   m_mesacontext = OSMesaCreateContextExt( GL_RGBA, 16, 0, 0, NULL );
   //    //#else
   //    //   m_mesacontext = OSMesaCreateContext( GL_RGBA, NULL );
   //    //#endif
   //    //   if (!m_mesacontext)
   //    //   {
   //    //
   //    //      printf("OSMesaCreateContext failed!\n");
   //    //
   //    //      return 0;
   //    //
   //    //   }
   //
   //    EGLint pbufferAttribs[5];
   //    pbufferAttribs[0] = EGL_WIDTH;
   //    pbufferAttribs[1] = size.cx;
   //    pbufferAttribs[2] = EGL_HEIGHT;
   //    pbufferAttribs[3] = size.cy;
   //    pbufferAttribs[4] = EGL_NONE;
   //
   //    // Step 6 - Create a surface to draw to.
   //    m_surface = eglCreatePbufferSurface(m_display, m_config, pbufferAttribs);
   //
   //    if (m_surface == EGL_NO_SURFACE)
   //    {
   //
   //       throw ::exception(::error_failed);
   //
   //    }
   //
   //    EGLint contextAttribs[] =
   //    {
   //        EGL_CONTEXT_MAJOR_VERSION, 3, // Specifies OpenGL ES 3.0.
   //        EGL_CONTEXT_MINOR_VERSION, 0, // Specifies OpenGL ES 3.0.
   //        EGL_NONE
   //    };
   //    // Step 7 - Create a context.
   //    //EGLContext eglContext;
   //    m_context = eglCreateContext(m_display, m_config, NULL, contextAttribs);
   //    //qDebug() << "egl error" << eglGetError();
   //
   //    if (m_context == EGL_NO_CONTEXT)
   //    {
   //
   //       //qDebug() << "context issue";
   //       throw ::exception(::error_failed);
   //
   //    }
   //
   //    m_itaskGpu = ::current_itask();
   //
   //    //return ::success;
   //
   // }


   // void device_cgl::make_current()
   // {
   //
   //    bool bMakeCurrentOk = eglMakeCurrent(
   //          m_display,
   //          m_surface,
   //          m_surface,
   //          m_context);
   //
   //    if (!bMakeCurrentOk)
   //    {
   //
   //       errorf("eglMakeCurrent failed!");
   //
   //       //return ::error_failed;
   //
   //       throw ::exception(::error_failed);
   //
   //    }
   //
   //    //return ::success;
   //
   // }


//    void device_cgl::resize_offscreen_buffer(const ::int_size& size)
//    {
//
//       //auto estatus =
//       //
//       ::gpu::context::resize_offscreen_buffer(size);
//
// //      if(!estatus)
// //      {
// //
// //         return estatus;
// //
// //      }
//
//       EGLint pbufferAttribs[5];
//       pbufferAttribs[0] = EGL_WIDTH;
//       pbufferAttribs[1] = size.cx;
//       pbufferAttribs[2] = EGL_HEIGHT;
//       pbufferAttribs[3] = size.cy;
//       pbufferAttribs[4] = EGL_NONE;
//
//       // Step 6 - Create a surface to draw to.
//       auto surface = eglCreatePbufferSurface(m_display, m_config, pbufferAttribs);
//
//       if (surface == EGL_NO_SURFACE)
//       {
//
//          throw ::exception(error_failed);
//
//       }
//
//       auto surfaceOld = m_surface;
//
//       m_surface = surface;
//
//       eglDestroySurface(m_display, surfaceOld);
//
//       //return ::success_none;
//
//    }
//
//
//    void device_cgl::destroy_offscreen_buffer()
//    {
//
//       //::e_status estatus = error_failed;
//
//       //return estatus;
//
//       //throw ::exception(error_failed);
//
//    }


//    string device_cgl::get_shader_version_text()
//    {
//
// #if defined(__ANDROID__)
//
//       return "#version 300 es";
//
// #else
//
//       return "#version 300 es";
//
// #endif
//
//    }
//
//
//    void device_cgl::_translate_shader(string_array_base & stra)
//    {
//
//       character_count iFindPrecision = stra.case_insensitive_find_first_begins("precision ");
//
//       if(iFindPrecision >= 0)
//       {
//
//          stra[iFindPrecision] = "precision highp float;";
//
//       }
//       else
//       {
//
//          stra.insert_at(1, "precision highp float;");
//
//          iFindPrecision = 1;
//
//       }
//
//       auto iFind = stra.case_insensitive_find_first_begins("out vec4 ");
//
//       if(::found(iFind))
//       {
//
//          stra[iFind] = "out vec4 fragmentColor;";
//
//       }
//       else
//       {
//
//          stra.insert_at(iFindPrecision + 1, "out vec4 fragmentColor;");
//
//       }
//
//       stra.replace_with("fragmentColor", "gl_FragColor");
//
//    }


//    void context::copy(::gpu::texture* pgputextureTarget, ::gpu::texture* pgputextureSource)
//    {
//
//       //::cast < texture > ptextureDst = player->texture();
//
//       //::cast < texture > ptextureSrc = m_pgpurendertarget->current_texture();
//
//       ::cast < texture > ptextureDst = pgputextureTarget;
//
//       ::cast < texture > ptextureSrc = pgputextureSource;
//
//       auto textureSrc = ptextureSrc->m_gluTextureID;
//
//       auto textureDst = ptextureDst->m_gluTextureID;
//
//       glFlush();
//       GLCheckError("");
//
//       GLuint fboSrc, fboDst;
//       glGenFramebuffers(1, &fboSrc);
//       GLCheckError("");
//       glGenFramebuffers(1, &fboDst);
//       GLCheckError("");
//
//       // Attach source texture to fboSrc
//       glBindFramebuffer(GL_READ_FRAMEBUFFER, fboSrc);
//       GLCheckError("");
//       glFramebufferTexture2D(GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
//          GL_TEXTURE_2D, textureSrc, 0);
//       GLCheckError("");
//
//       // Attach dest texture to fboDst
//       glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fboDst);
//       GLCheckError("");
//       glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
//          GL_TEXTURE_2D, textureDst, 0);
//       GLCheckError("");
//
//       auto sizeSrc = ptextureSrc->size();
//       auto sizeDst = ptextureDst->size();
//
//       // Blit from source to destination
//       glBlitFramebuffer(
//          0, 0, sizeSrc.cx, sizeSrc.cy,
//          0, 0, sizeDst.cx, sizeDst.cy,
//          GL_COLOR_BUFFER_BIT, GL_NEAREST
//       );
//       GLCheckError("");
// #ifdef SHOW_DEBUG_DRAWING
//       {
//
//          //glBindFramebuffer(GL_FRAMEBUFFER, 0);
//
//
//          glEnable(GL_BLEND);
//          glBlendFunc(GL_ONE, GL_ZERO); // Source Copy mode
//          //glBlendEquation(GL_FUNC_ADD); // default, can be omitted if unchanged
//
//          {
//             float fOpacity = 0.5;
//             float fRed = 0.5;
//             float fGreen = 0.75;
//             float fBlue = 0.95;
//             auto f32Opacity = (float)fOpacity;
//             auto f32Red = (float)(fRed * fOpacity);
//             auto f32Green = (float)(fGreen * fOpacity);
//             auto f32Blue = (float)(fBlue * fOpacity);
//             ::glColor4f(f32Red, f32Green, f32Blue, f32Opacity);
//          }
//
//          ::double_polygon polygon;
//
//          ::double_rectangle rectangle(300, 300, 400, 400);
//
//          polygon = rectangle;
//
//          glBegin(GL_QUADS);
//
//
//          vertex2f(polygon, 0.f);
//
//          glEnd();
//
//       }
// #endif
//
//       // Cleanup
//       glBindFramebuffer(GL_FRAMEBUFFER, 0);
//       GLCheckError("");
//       glDeleteFramebuffers(1, &fboSrc);
//       GLCheckError("");
//       glDeleteFramebuffers(1, &fboDst);
//       GLCheckError("");
//
//
//    }


    void device_cgl::__cgl_swap_buffers()
    {
   
   
       m_pgpucontextMain->swap_buffers();
       //eglSwapBuffers(m_egldisplay, nullptr);
       // auto pDisplay = m_pwindow->__x11_Display();
       //
       // auto lWindow = m_pwindow->__x11_Window();
       //
       // if (pDisplay && lWindow)
       // {
       //
       //    __egl_x11_swap_buffers(pDisplay, lWindow);
       //
       // }
   
   
    }

   void device_cgl::_destroy_cgl_device()
   {
      
      if(m_cglpixelformat)
      {
         
         auto error = CGLDestroyPixelFormat(m_cglpixelformat);
         
         if(error != kCGLNoError)
         {
            
            warning("error while trying to destroy cgl pixel format");
            
         }
         
      }

      
   }


} // namespace gpu_opengl



