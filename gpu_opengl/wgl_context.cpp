// Recreated by camilo on 2026-02-12 14:30 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "_gpu_opengl.h"
#include "gpu_opengl/approach.h"
#define STB_USE_HUNTER
#include <glad/glad_wgl.h>
#include "acme/platform/application.h"
#include "approach.h"
#include "context_win32.h"
#include "device.h"
#include "device_win32.h"
#include "windowing_win32/window.h"


namespace gpu_opengl
{


   //extern PFNWGLCREATECONTEXTATTRIBSARBPROC loaded_wglCreateContextAttribsARB;
   //extern PFNWGLCHOOSEPIXELFORMATARBPROC loaded_wglChoosePixelFormatARB;

   wgl_context::wgl_context()
   {

      m_hwnd = nullptr;
      m_hdc = nullptr;
      m_hglrc = nullptr;

      m_bDummy = false;
      m_bOwnWindow = false;

   }

   wgl_context::~wgl_context() { destroy(); }


   void wgl_context::create_window_wgl_context(::windowing_win32::window *pwin32windowingwindow) 
   {

      if (m_hwnd || m_hdc || m_hglrc || m_bDummy)
      {

         throw ::exception(error_wrong_state);

      }
      
      m_bOwnWindow = false;

      {

         scoped_dummy_wgl_context wglcontextDummy(this);

         m_hwnd = pwin32windowingwindow->_HWND();

         if (!::IsWindow(m_hwnd))
         {

            warning("IsWindow returned false.");

            throw ::exception(error_wrong_state, "IsWindow returned false.");

         }

         m_hdc = ::GetDC(m_hwnd);

         auto pixelFormatOld = GetPixelFormat(m_hdc);

         if (pixelFormatOld)
         {

            warning("GetPixelFormat before: %d", pixelFormatOld);

            throw ::exception(error_wrong_state, "pixel format is already set");

         }

         int_array_base pixelAttribs;

         pixelAttribs.append({WGL_DRAW_TO_WINDOW_ARB, GL_TRUE});
         pixelAttribs.append({WGL_SUPPORT_OPENGL_ARB, GL_TRUE});
         pixelAttribs.append({WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB});
         pixelAttribs.append({WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB});
         pixelAttribs.append({WGL_DOUBLE_BUFFER_ARB, GL_TRUE}); // must be present
         //pixelAttribs.append({WGL_RED_BITS_ARB, 8});
         //pixelAttribs.append({WGL_GREEN_BITS_ARB, 8});
         //pixelAttribs.append({WGL_BLUE_BITS_ARB, 8});
         pixelAttribs.append({WGL_COLOR_BITS_ARB, 32});
         pixelAttribs.append({WGL_ALPHA_BITS_ARB, 8}); 
         pixelAttribs.append({WGL_DEPTH_BITS_ARB, 24});
         pixelAttribs.append({WGL_STENCIL_BITS_ARB, 8});
         pixelAttribs.add(0);

         for (int i = 0; i < pixelAttribs.size(); i++)
         {

            information("pixelAttribs{}={}", i, pixelAttribs[i]);

         }

         //ASSERT(pixelAttribs.size() == 17);

         int format[64] = {};

         UINT numFormats = 0;

         //auto hglrcDummy = wglGetCurrentContext();

         //if (!hglrcDummy)
         //{

         //   warning("no hglrcDummy");

         //   throw ::exception(error_wrong_state, "no hglrcDummy");

         //}

         //auto hdcDummy = wglGetCurrentDC();

         //if (!hdcDummy)
         //{

         //   warning("no hdcDummy");

         //   throw ::exception(error_wrong_state, "no hdcDummy");

         //}

         if (!wglChoosePixelFormatARB(m_hdc, pixelAttribs.data(), NULL, 1, format, &numFormats))
         {

            warning("wglChoosePixelFormatARB failed");

            throw ::exception(error_failed, "wglChoosePixelFormatARB failed");

         }

         if (numFormats <= 0)
         {

            warning("no Pixel Formats");

            throw ::exception(error_failed, "no Pixel Formats");


         }

         PIXELFORMATDESCRIPTOR pfd{};

         if (!DescribePixelFormat(m_hdc, format[0], sizeof(pfd), &pfd))
         {

            warning("DescribePixelFormat failed");

            throw ::exception(error_failed, "DescribePixelFormat failed");

         }
         
         if (!SetPixelFormat(m_hdc, format[0], &pfd))
         {

            warning("SetPixelFormat failed. SetPixelFormat must be called only once per HDC");

            throw ::exception(error_failed, "SetPixelFormat failed");

         }

         int contextAttribs[] = {
            WGL_CONTEXT_MAJOR_VERSION_ARB,    3, WGL_CONTEXT_MINOR_VERSION_ARB, 3, WGL_CONTEXT_PROFILE_MASK_ARB,
            WGL_CONTEXT_CORE_PROFILE_BIT_ARB, 0};

         _create_wgl_context(contextAttribs);

         pwin32windowingwindow->m_hglrcProto = m_hglrc;

      }

      //select();

   }


   void wgl_context::_create_wgl_context(int * contextAttribs)
   {

      ::cast<approach> pgpuapproach = m_papplication->get_gpu_approach();

      auto hglrc = wglCreateContextAttribsARB(m_hdc, pgpuapproach->m_hglrcShare, contextAttribs);

      if (!hglrc)
      {

         throw ::exception(error_failed, "Failed to create wgl context");

      }

      m_hglrc = hglrc;

      if (!pgpuapproach->m_hglrcShare)
      {

         pgpuapproach->m_hglrcShare = hglrc;

      }

   }


   void wgl_context::create_offscreen_wgl_context()
   {

      if (m_hwnd || m_hdc || m_hglrc || m_bDummy)
      {

         throw ::exception(error_wrong_state);
      }

      {

         scoped_dummy_wgl_context wglcontextDummy(this);

         m_bOwnWindow = true;

         m_hwnd = create_hidden_gl_window();

         m_hdc = GetDC(m_hwnd);

         // int pixelAttribs[] = {
         //     WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
         //     WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
         //     WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
         //     WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
         //     WGL_COLOR_BITS_ARB, 32,
         //     WGL_DEPTH_BITS_ARB, 24,
         //     WGL_STENCIL_BITS_ARB, 8,
         //     0
         // };
         auto pixelFormatOld = GetPixelFormat(m_hdc);

         if (pixelFormatOld)
         {

            warning("GetPixelFormat before: %d", pixelFormatOld);

            throw ::exception(error_wrong_state, "pixel format is already set");
         }


         int_array_base pixelAttribs;


         pixelAttribs.append({WGL_DRAW_TO_WINDOW_ARB, GL_TRUE});
         pixelAttribs.append({WGL_SUPPORT_OPENGL_ARB, GL_TRUE});
         pixelAttribs.append({WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB});
         // if (pdevice->m_bAddSwapChainSupport)
         //{
         //    pixelAttribs.append({WGL_DOUBLE_BUFFER_ARB, GL_TRUE}); // <-- double buffering
         // }
         pixelAttribs.append({WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB});
         // pixelAttribs.append({WGL_COLOR_BITS_ARB, 32}); // total color bits
         pixelAttribs.append({WGL_COLOR_BITS_ARB, 24});
         //pixelAttribs.append({WGL_ALPHA_BITS_ARB, 8});
         //pixelAttribs.append({WGL_RED_BITS_ARB, 8});
         //pixelAttribs.append({WGL_GREEN_BITS_ARB, 8});
         //pixelAttribs.append({WGL_BLUE_BITS_ARB, 8});
         pixelAttribs.append({WGL_ALPHA_BITS_ARB, 8}); // <-- alpha support
         pixelAttribs.append({WGL_DEPTH_BITS_ARB, 24}); // optional, for depth buffer
         pixelAttribs.append({WGL_STENCIL_BITS_ARB, 8}); // optional, for stencil
         pixelAttribs.add(0); // terminator

         int format = 0;

         UINT numFormats = 0;

         if (!wglChoosePixelFormatARB(m_hdc, pixelAttribs.data(), NULL, 1, &format, &numFormats))
         {

            warning("wglChoosePixelFormatARB failed");

            throw ::exception(error_failed, "wglChoosePixelFormatARB failed");

         }

         PIXELFORMATDESCRIPTOR pfd{};

         if (!DescribePixelFormat(m_hdc, format, sizeof(pfd), &pfd))
         {

            warning("DescribePixelFormat failed");

            throw ::exception(error_failed, "DescribePixelFormat failed");
         }

         /// SetPixelFormat must be called only once per HDC
         if (!SetPixelFormat(m_hdc, format, &pfd))
         {

            warning("SetPixelFormat failed");

            throw ::exception(error_failed, "SetPixelFormat failed");
         }

         int contextAttribs[] = {
            WGL_CONTEXT_MAJOR_VERSION_ARB,    3, WGL_CONTEXT_MINOR_VERSION_ARB, 3, WGL_CONTEXT_PROFILE_MASK_ARB,
            WGL_CONTEXT_CORE_PROFILE_BIT_ARB, 0};

         _create_wgl_context(contextAttribs);

      }

      //select();
      //// wglMakeCurrent(dc, rc);
      ////
      ////*outRC = rc;
      ////*outDC = dc;*/
      //////::ReleaseDC(hwnd, dc);

      //bool bMakeCurrentOk = wglMakeCurrent(hdc, hglrc);

      //if (!bMakeCurrentOk)
      //{

      //   informationf("MS WGL - wglMakeCurrent failed");

      //   informationf("last-error code: %d\n", GetLastError());

      //   ReleaseDC(hwnd, hdc);

      //   throw ::exception(error_failed);
      //}

   }


   void wgl_context::create_dummy_wgl_context()
   {

      if (m_hwnd || m_hdc || m_hglrc || m_bDummy)
      {

         throw ::exception(error_wrong_state);
      }

      m_bDummy = true;

      m_bOwnWindow = true;

      m_hwnd = create_hidden_gl_window();

      m_hdc = GetDC(m_hwnd);

      PIXELFORMATDESCRIPTOR pixelformatdescriptor{};
      pixelformatdescriptor.nSize = sizeof(PIXELFORMATDESCRIPTOR);
      pixelformatdescriptor.nVersion = 1;
      pixelformatdescriptor.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
      pixelformatdescriptor.iPixelType = PFD_TYPE_RGBA;
      pixelformatdescriptor.cColorBits = 32;

      int iPixelFormat = ChoosePixelFormat(m_hdc, &pixelformatdescriptor);

      SetPixelFormat(m_hdc, iPixelFormat, &pixelformatdescriptor);

      m_hglrc = wglCreateContext(m_hdc);

   }


   void wgl_context::destroy()
   {

      m_bDummy = false;

      if (m_hglrc)
      {

         ::wglDeleteContext(m_hglrc);

         m_hglrc = nullptr;
      }

      if (m_hdc)
      {

         ::ReleaseDC(m_hwnd, m_hdc);

         m_hdc = nullptr;
      }

      if (m_hwnd)
      {

         if (m_bOwnWindow)
         {

            ::DestroyWindow(m_hwnd);

            m_bOwnWindow = false;

         }

         m_hwnd = nullptr;
      }
   }


   void wgl_context::select()
   {

      if (!m_hwnd || !m_hdc || !m_hglrc)
      {

         throw ::exception(error_wrong_state);
      }

      if (m_taskindex)
      {

         throw ::exception(error_wrong_state, "context already selected in this or other thread");
      }

      if (m_itask.is_set())
      {

         throw ::exception(error_wrong_state, "context already selected in this or other thread");
      }

      if (m_htask.is_set())
      {

         throw ::exception(error_wrong_state, "context already selected in this or other thread");
      }

      if (m_bContextSelected)
      {

         throw ::exception(error_wrong_state, "context already selected in this or other thread");
      }

      auto hglrcCurrent = ::wglGetCurrentContext();

      auto hdcCurrent = ::wglGetCurrentDC();

      if (hglrcCurrent)
      {

         wglMakeCurrent(nullptr, nullptr);
      }

      if (hglrcCurrent != m_hglrc || hdcCurrent != m_hdc)
      {

         bool bMakeCurrentOk = wglMakeCurrent(m_hdc, m_hglrc);

         if (!bMakeCurrentOk)
         {

            informationf("MS WGL - wglMakeCurrent failed");

            int iLastError = GetLastError();

            informationf("last-error code: %d\n", iLastError);

            throw ::exception(error_failed);
         }
      }

      m_taskindex = current_task_index();
      m_itask = current_itask();
      m_htask = current_htask();

      m_bContextSelected = true;
   }


   void wgl_context::unselect()
   {

      if (!m_hwnd || !m_hdc || !m_hglrc)
      {

         throw ::exception(error_wrong_state);
      }

      if (!m_taskindex)
      {

         throw ::exception(error_wrong_state, "context not selected");
      }
      if (!m_itask)
      {

         throw ::exception(error_wrong_state, "context not selected");
      }
      if (!m_htask)
      {

         throw ::exception(error_wrong_state, "context not selected");
      }

      auto taskindexCurrent = ::current_task_index();
      auto itaskCurrent = ::current_itask();
      auto htaskCurrent = ::current_htask();
      if (m_taskindex != taskindexCurrent)
      {

         throw ::exception(error_wrong_state, "context already selected on other thread");
      }
      if (m_itask != itaskCurrent)
      {

         throw ::exception(error_wrong_state, "context already selected on other thread");
      }
      if (m_htask != htaskCurrent)
      {

         throw ::exception(error_wrong_state, "context already selected on other thread");
      }

      if (!m_bContextSelected)
      {

         throw ::exception(error_wrong_state, "context is not currently selected");
      }


      if (wglGetCurrentContext() != m_hglrc || wglGetCurrentDC() != m_hdc)
      {

         throw ::exception(error_wrong_state, "wrong state");
      }

      bool bReleaseOk = wglMakeCurrent(nullptr, nullptr);

      if (!bReleaseOk)
      {

         informationf("MS WGL - wglMakeCurrent failed");

         informationf("last-error code: %d\n", GetLastError());

         throw ::exception(error_failed);
      }
      m_bContextSelected = false;
      m_taskindex = 0;
      m_itask = nullptr;
      m_htask = nullptr;
   }


      ATOM g_atomGlWindowClass = 0;


   static LRESULT CALLBACK hidden_gl_window_procedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
   {

      return DefWindowProcW(hwnd, msg, wParam, lParam);
   }


   LPCWSTR hidden_gl_window_class_name() { return L"hidden_gl_window_class"; }


   ATOM defer_register_hidden_gl_window_class()
   {

      if (g_atomGlWindowClass)
      {

         return g_atomGlWindowClass;
      }

      WNDCLASSW windowclass{};

      windowclass.style = CS_OWNDC; // IMPORTANT for OpenGL
      windowclass.lpfnWndProc = hidden_gl_window_procedure;
      windowclass.hInstance = ::hinstance_from_function(hidden_gl_window_procedure);
      windowclass.lpszClassName = hidden_gl_window_class_name();
      windowclass.cbWndExtra = 40;

      auto atom = RegisterClassW(&windowclass);

      g_atomGlWindowClass = atom;

      return atom;
   }


   //PFNWGLCREATECONTEXTATTRIBSARBPROC loaded_wglCreateContextAttribsARB = NULL;
   //PFNWGLCHOOSEPIXELFORMATARBPROC loaded_wglChoosePixelFormatARB = NULL;
   //// Load only required WGL extensions
   //void load_wgl_extensions()
   //{
   //   loaded_wglCreateContextAttribsARB =
   //      (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");
   //   loaded_wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)wglGetProcAddress("wglChoosePixelFormatARB");
   //}


   void defer_load_wgl_extensions(::particle * pparticle)
   {

      if (wglCreateContextAttribsARB && wglChoosePixelFormatARB)
      {

         return;

      }

      //scoped_dummy_wgl_context wglcontextDummy(pparticle);

      ::cast < ::gpu_opengl::approach > pgpuapproach = pparticle->m_papplication->gpu_approach();

//      load_wgl_extensions();

      if (!gladLoadWGL(pgpuapproach->dummy_wgl_context()->m_hdc))
      {

         throw ::exception(error_failed, "Failed to load glad using WGL");
      }

      if (!gladLoadGL())
      {

         throw ::exception(error_failed, "Failed to load glad using OpenGL");

      }

   }


   HWND create_hidden_gl_window()
   {

      defer_register_hidden_gl_window_class();

      auto pszClassName = hidden_gl_window_class_name();

      auto hinstance = ::hinstance_from_function(hidden_gl_window_procedure);

      HWND hwnd =
         CreateWindowExW(0, pszClassName, L"", WS_OVERLAPPED, 0, 0, 1, 1, nullptr, nullptr, hinstance, nullptr);

      return hwnd;

   }


   //dummy_wgl_context::dummy_wgl_context()
   //{

   //   create_dummy_wgl_context();

   //}


   //dummy_wgl_context::~dummy_wgl_context()
   //{



   //}


   scoped_dummy_wgl_context::scoped_dummy_wgl_context(::particle * pparticle) :
      m_pparticle(pparticle)
   {

      ::cast<::gpu_opengl::approach> pgpuapproach = m_pparticle->m_papplication->gpu_approach();

      pgpuapproach->dummy_wgl_context()->select();

      defer_load_wgl_extensions(pparticle);
         
   }


   scoped_dummy_wgl_context::~scoped_dummy_wgl_context()
   {

      ::cast<::gpu_opengl::approach> pgpuapproach = m_pparticle->m_papplication->gpu_approach();

      pgpuapproach->dummy_wgl_context()->unselect();


   }


} // namespace gpu_opengl




