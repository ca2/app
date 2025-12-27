#include "framework.h"
#include "_gpu_opengl.h"
#include "approach.h"
#include "context.h"
#include "device_egl.h"

#include "context_egl.h"
#include "swap_chain.h"
#include "acme/platform/application.h"
#include "acme/windowing/display.h"
#include "acme/windowing/windowing.h"
#include "aura/platform/system.h"
#include "aura/windowing/window.h"
#include <X11/Xlib.h>

int rotating_cube();

//#include "_opengl.h"
//
extern "C"
{
GLAPI int gladLoadEGL(void);

} // extern "C"

const char* eglErrorString(EGLint error) {
   switch (error) {
      case EGL_SUCCESS: return "EGL_SUCCESS";
      case EGL_NOT_INITIALIZED: return "EGL_NOT_INITIALIZED";
      case EGL_BAD_ACCESS: return "EGL_BAD_ACCESS";
      case EGL_BAD_ALLOC: return "EGL_BAD_ALLOC";
      case EGL_BAD_ATTRIBUTE: return "EGL_BAD_ATTRIBUTE";
      case EGL_BAD_CONTEXT: return "EGL_BAD_CONTEXT";
      case EGL_BAD_CONFIG: return "EGL_BAD_CONFIG";
      case EGL_BAD_CURRENT_SURFACE: return "EGL_BAD_CURRENT_SURFACE";
      case EGL_BAD_DISPLAY: return "EGL_BAD_DISPLAY";
      case EGL_BAD_SURFACE: return "EGL_BAD_SURFACE";
      case EGL_BAD_MATCH: return "EGL_BAD_MATCH";
      case EGL_BAD_PARAMETER: return "EGL_BAD_PARAMETER";
      case EGL_BAD_NATIVE_PIXMAP: return "EGL_BAD_NATIVE_PIXMAP";
      case EGL_BAD_NATIVE_WINDOW: return "EGL_BAD_NATIVE_WINDOW";
      case EGL_CONTEXT_LOST: return "EGL_CONTEXT_LOST";
      default: return "Unknown error";
   }
}
namespace gpu_opengl
{

   //bool g_bEglOpened = false;
   //EGLDisplay g_egldisplay = nullptr;
   //EGLConfig  g_eglconfig;
   thread_local bool t_bEglApiBound = false;
   bool g_bGladGL = false;
   //critical_section g_criticalsectionEgl;

   bool is_glad_gl_loaded()
   {

      return g_bGladGL;

   }

   // should be called within a currently selected egl context
   void load_glad_gl()
   {

      if (g_bGladGL)
      {

          return;

      }

      g_bGladGL = true;

      auto gl_version = gladLoadGLLoader((GLADloadproc)eglGetProcAddress);

      if (!gl_version)
      {

         printf("Unable to reload GL.\n");

         throw ::exception(::error_failed);

      }

      auto pszGlVersion = glGetString(GL_VERSION);

      auto pszGlRenderer = glGetString(GL_RENDERER);

      printf("GL_VERSION = %s\n", pszGlVersion);

      printf("GL_RENDERER = %s\n", pszGlRenderer);


      //printf("has GLES3: %d\n", GLAD_GL_ES_VERSION_3_0);

      //printf("Loaded GL %d.%d after reload.\n",
      //     GLAD_VERSION_MAJOR(gl_version), GLAD_VERSION_MINOR(gl_version));

   }


   // critical_section * egl_critical_section()
   // {
   //    return &g_criticalsectionEgl;
   // }

//    EGLDisplay egl_open_display()
//    {
//
//       if (g_bEglOpened)
//       {
//
//          return g_egldisplay;
//
//       }
//
//       g_bEglOpened = true;
//
//       EGLint attribList[]=
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
//
//       //synchronous_lock synchronouslock(x11_mutex(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
//
//       //xdisplay display(x11_get_display());
//
//       //m_display = eglGetDisplay((EGLNativeDisplayType)display);
//
//       //m_display = eglGetDisplay((EGLNativeDisplayType)0);
//       auto egldisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
//
//       if (egldisplay == EGL_NO_DISPLAY)
//       {
//
//          fprintf(stderr, "Got no EGL display.\n");
//
//          throw ::exception(::error_failed);
//
//       }
//
//       if (!eglInitialize(egldisplay, NULL, NULL))
//       {
//
//          fprintf(stderr, "Unable to initialize EGL\n");
//
//          throw ::exception(::error_failed);
//
//       }
//
//
//
//       // Choose an EGLConfig
//       //EGLConfig config;
//       EGLint numConfigs;
//       EGLint configAttribs[] = {EGL_RENDERABLE_TYPE, EGL_OPENGL_BIT, EGL_NONE};
//       if (!eglChooseConfig(egldisplay, configAttribs, &g_eglconfig, 1, &numConfigs))
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
//       if (numConfigs != 1)
//       {
//
//          fprintf(stderr, "Didn't get just one config, but %d\n", numConfigs);
//
//          throw ::exception(::error_failed);
//
//       }
//
//       g_egldisplay = egldisplay;
//
//       //#if OSMESA_MAJOR_VERSION * 100 + OSMESA_MINOR_VERSION >= 305
//       //   /* specify Z, stencil, accum sizes */
//       //   m_mesacontext = OSMesaCreateContextExt( GL_RGBA, 16, 0, 0, NULL );
//       //#else
//       //   m_mesacontext = OSMesaCreateContext( GL_RGBA, NULL );
//       //#endif
//       //   if (!m_mesacontext)
//       //   {
//       //
//       //      printf("OSMesaCreateContext failed!\n");
//       //
//       //      return 0;
//       //
//       //   }
//       //g_bEglOpened = true;
//
//       return g_egldisplay;
//
//    }

   void defer_bind_egl_api()
   {

      if (t_bEglApiBound)
      {

         return;

      }

      t_bEglApiBound=true;

#ifdef LINUX

      eglBindAPI(EGL_OPENGL_API);

#else

      eglBindAPI(EGL_OPENGL_ES_API);

      //  auto egl_version = gladLoadEGL();
      //  if (!egl_version) {
      //        printf("Unable to reload EGL.\n");
      //        throw ::exception(::error_failed);
      //     }
      // printf("Loaded EGL %d.%d after reload.\n",
      //        GLAD_VERSION_MAJOR(egl_version), GLAD_VERSION_MINOR(egl_version));


#endif



   }

   //::pointer <::gpu::context > allocate_egl_context(::particle * pparticle)
   //{

     // return pparticle->øcreate_new < device_egl >();

   //}


   device_egl::device_egl()
   {

      m_egldisplay = EGL_NO_DISPLAY;
      m_eglconfig = EGL_NO_CONFIG_KHR;
      m_eglcontextPrimary = EGL_NO_CONTEXT;
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


   device_egl::~device_egl()
   {


   }


   void device_egl::initialize_gpu_device_for_swap_chain(::gpu::approach* papproach, ::windowing::window* pwindow)
   {

      ::gpu::device::initialize_gpu_device_for_swap_chain(papproach, pwindow);

      m_pgpuapproach = papproach;
      m_pwindow = pwindow;
      //m_bAddSwapChainSupport = true;
      //m_hwnd = (HWND) m_pwindow->oswindow();

      auto size = m_pwindow->get_window_rectangle().size();

      _create_device(size);

      auto pcontext = main_context();

      pcontext->m_pgpudevice = this;

      pcontext->_send([this, pcontext]()
         {

            pcontext->initialize_gpu_context(this,
               ::gpu::e_output_gpu_buffer,
               m_pwindow,
               m_pwindow->get_window_rectangle().size());

            auto pswapchain = pcontext->get_swap_chain();

            pswapchain->initialize_swap_chain_window(pcontext, m_pwindow);

         });

   }


   void device_egl::initialize_gpu_device_for_off_screen(::gpu::approach* papproach, const ::int_rectangle& rectanglePlacement)
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

   void device_egl::_defer_create_offscreen_window(const ::int_size& size)
   {

   }

   void device_egl::_opengl_lock()
   {
      //critical_section_lock lock(egl_critical_section());
      // Make the context current
      // if (!eglMakeCurrent(m_egldisplay, m_eglsurface, m_eglsurface, m_eglcontext))
      // {
      //
      //    auto error = eglGetError();
      //    ::string strMessage;
      //
      //    strMessage << "eglMakeCurrent failed: " << eglErrorString(error) ;
      //    warning() << strMessage;
      //    throw ::exception(error_wrong_state,strMessage);
      //
      // }

      //m_itaskGpu = ::current_itask();

   }


   void device_egl::_opengl_unlock()
   {

      //critical_section_lock lock(egl_critical_section());

      // if (!eglMakeCurrent(m_egldisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT))
      // {
      //
      //    throw ::exception(error_wrong_state);
      //
      // }

   }


   ::pointer < ::gpu::context > device_egl::allocate_context()
   {

      ::pointer < ::gpu::context > pgpucontext;

      pgpucontext=øcreate_new < ::gpu_opengl::context_egl>();

      return pgpucontext;

   }


   //void device_egl::create_context()
   void device_egl::_create_device(const ::int_size & size)
   {

      if (m_egldisplay)
      {

         return;

      }

      auto psystem = system();

      auto pgpu = application()->gpu_approach();

      ::pointer<::gpu_opengl::approach>papproach = pgpu;

      if (::is_null(papproach))
      {

         throw ::exception(::error_failed);

      }


      defer_bind_egl_api();


//      critical_section_lock lockEgl(egl_critical_section());


//      m_egldisplay = egl_open_display();


      EGLint attribList[]=
      {

         EGL_SURFACE_TYPE, EGL_PBUFFER_BIT,
/// ;;;        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
         //EGL_CONFORMANT, EGL_OPENGL_BIT,
         //EGL_COLOR_BUFFER_TYPE, EGL_RGB_BUFFER,
         EGL_RED_SIZE, 8,
         EGL_GREEN_SIZE, 8,
         EGL_BLUE_SIZE, 8,
         EGL_ALPHA_SIZE, 8,
         //EGL_LEVEL, 0,
         //EGL_BUFFER_SIZE, 24,
         EGL_NONE

      };

      //synchronous_lock synchronouslock(x11_mutex(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      //xdisplay display(x11_get_display());

      //m_display = eglGetDisplay((EGLNativeDisplayType)display);

      auto pwindowing = psystem->acme_windowing();

      auto pdisplay = pwindowing->acme_display();

      ::Display * pDisplay = nullptr;

      pdisplay->get_os_display_handle(&pDisplay, sizeof(pDisplay));

      //m_display = eglGetDisplay((EGLNativeDisplayType)0);
      //auto egldisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
      auto egldisplay = eglGetDisplay(pDisplay);

      if (egldisplay == EGL_NO_DISPLAY)
      {

         fprintf(stderr, "Got no EGL display.\n");

         throw ::exception(::error_failed);

      }

      if (!eglInitialize(egldisplay, NULL, NULL))
      {

         fprintf(stderr, "Unable to initialize EGL\n");

         throw ::exception(::error_failed);

      }



      // Choose an EGLConfig
      //EGLConfig config;
      EGLint numConfigs;
      EGLint configAttribs[] = {EGL_RENDERABLE_TYPE, EGL_OPENGL_BIT, EGL_NONE};
      if (!eglChooseConfig(egldisplay, configAttribs, &m_eglconfig, 1, &numConfigs))
      {

         int iError = eglGetError();

         const ::scoped_string & scopedstrError = eglQueryString(egldisplay, iError);

         fprintf(stderr, "Failed to choose config (eglError: %s : 0x%x)\n", ::string(scopedstrError).c_str(), iError);

         throw ::exception(::error_failed);

      }

      if (numConfigs != 1)
      {

         fprintf(stderr, "Didn't get just one config, but %d\n", numConfigs);

         throw ::exception(::error_failed);

      }

      m_egldisplay = egldisplay;



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

      //return ::success;

   }


//   void device_egl::_create_offscreen_buffer(const ::int_size & size)
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



   // void device_egl::initialize_gpu_device_for_off_screen(::gpu::approach* papproach, const ::int_rectangle& rectanglePlacement)
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


   // void device_egl::make_current()
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


//    void device_egl::resize_offscreen_buffer(const ::int_size& size)
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
//    void device_egl::destroy_offscreen_buffer()
//    {
//
//       //::e_status estatus = error_failed;
//
//       //return estatus;
//
//       //throw ::exception(error_failed);
//
//    }


//    string device_egl::get_shader_version_text()
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
//    void device_egl::_translate_shader(string_array_base & stra)
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


   void device_egl::_swap_buffers()
   {

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

} // namespace gpu_opengl



