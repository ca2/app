#include "framework.h"
#include "context_win32.h"
#include "opengl.h"
#include "cpu_buffer.h"
#include "aura/graphics/gpu/approach.h"
#include "aura/graphics/image/image.h"
#include "aura/platform/system.h"


namespace opengl
{


   ::pointer < ::gpu::context > allocate_system_context(::particle * pparticle)
   {

      return pparticle->__create_new <context_win32>();

   }


   context_win32::context_win32()
   {

      m_emode = e_mode_system;

      m_estatus = error_not_initialized;

   }


   context_win32::~context_win32()
   {

   }

   
   void context_win32::_create_offscreen_window(const ::size_i32 & size)
   {
      if (::IsWindow(m_hwnd))
      {

         if (!::SetWindowPos(m_hwnd,
            nullptr, 0, 0,
            size.cx()
            , size.cy(), SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE
            | SWP_NOCOPYBITS | SWP_NOSENDCHANGING
            | SWP_NOREPOSITION | SWP_NOREDRAW))
         {

            information() << "SetWindowPos Failed";

         }


         //return m_hwnd;

      }
      else
      {

         LPCTSTR lpClassName = L"draw2d_opengl_offscreen_buffer_window";
         LPCTSTR lpWindowName = L"draw2d_opengl_offscreen_buffer_window";
         //::u32 dwStyle = WS_CAPTION | WS_POPUPWINDOW; // | WS_VISIBLE
         ::u32 dwExStyle = 0;
         ::u32 dwStyle = WS_OVERLAPPEDWINDOW;
         dwStyle |= WS_POPUP;
         //dwStyle |= WS_VISIBLE;
         //dwStyle |= WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;
         dwStyle &= ~WS_CAPTION;
         //dwStyle = 0;
         dwStyle &= ~WS_THICKFRAME;
         dwStyle &= ~WS_BORDER;
         int x = 0;
         int y = 0;
         int nWidth = size.cx();
         int nHeight = size.cy();
         HWND hWndParent = nullptr;
         HMENU hMenu = nullptr;
         HINSTANCE hInstance = ::GetModuleHandleW(L"gpu_opengl.dll");
         LPVOID lpParam = nullptr;

         m_hwnd = CreateWindowExW(dwExStyle, lpClassName, lpWindowName, dwStyle, x, y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);

         if (!m_hwnd)
         {

            informationf("MS GDI - CreateWindow failed");

            informationf("last-error code: %d\n", GetLastError());

            throw ::exception(error_failed);

         }

         //return m_hwnd;

      }


   }



   void context_win32::_create_window_buffer()
   {

      if (!m_hdc || !m_hdc || !m_hrc)
      {


         auto psystem = system()->m_paurasystem;

         auto pgpu = psystem->get_gpu();

         ::pointer < ::opengl::opengl > popengl = pgpu;

         if (!popengl->m_atomClass)
         {

            informationf("MS GDI - RegisterClass failed");

            informationf("last-error code: %d\n", GetLastError());

            throw ::exception(error_failed);

         }

         // create WGL context, make current

         PIXELFORMATDESCRIPTOR pixformat;

         int chosenformat;

         HDC hdc = GetDC(m_hwnd);

         if (!hdc)
         {

            informationf("MS GDI - GetDC failed");

            informationf("last-error code: %d\n", GetLastError());

            throw ::exception(error_failed);

         }

         zero(pixformat);
         pixformat.nSize = sizeof(pixformat);
         pixformat.nVersion = 1;
         pixformat.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
         pixformat.iPixelType = PFD_TYPE_RGBA;
         pixformat.cColorBits = 32;
         pixformat.cRedShift = 16;
         pixformat.cGreenShift = 8;
         pixformat.cBlueShift = 0;
         pixformat.cAlphaShift = 24;
         pixformat.cAlphaBits = 8;
         pixformat.cDepthBits = 24;
         pixformat.cStencilBits = 8;

         chosenformat = ChoosePixelFormat(hdc, &pixformat);

         if (chosenformat == 0)
         {

            informationf("MS GDI - ChoosePixelFormat failed");

            informationf("last-error code: %d\n", GetLastError());

            ReleaseDC(m_hwnd, hdc);

            throw ::exception(error_failed);

         }

         bool spfok = SetPixelFormat(hdc, chosenformat, &pixformat);

         if (!spfok)
         {

            informationf("MS GDI - SetPixelFormat failed");

            informationf("last-error code: %d\n", GetLastError());

            ReleaseDC(m_hwnd, hdc);

            throw ::exception(error_failed);

         }

         HGLRC hglrc = wglCreateContext(hdc);

         if (!hglrc)
         {

            informationf("MS WGL - wglCreateContext failed");

            informationf("last-error code: %d\n", GetLastError());

            ReleaseDC(m_hwnd, hdc);

            throw ::exception(error_failed);

         }

         bool bMakeCurrentOk = wglMakeCurrent(hdc, hglrc);

         if (!bMakeCurrentOk)
         {

            informationf("MS WGL - wglMakeCurrent failed");

            informationf("last-error code: %d\n", GetLastError());

            ReleaseDC(m_hwnd, hdc);

            throw ::exception(error_failed);

         }


         popengl->defer_init_gpu_library();

         auto pszVersion = (const char *)glGetString(GL_VERSION);
         //::e_status estatus = 


         //if (!estatus)
         //{

         //   ReleaseDC(window, hdc);

         //   return estatus;

         //}

         m_hwnd = m_hwnd;
         m_hdc = hdc;
         m_hrc = hglrc;

      }

      RECT rectClient;

      ::GetClientRect(m_hwnd, &rectClient);

      m_size = { rectClient.right - rectClient.left,
         rectClient.bottom - rectClient.top };

      m_itaskGpu = ::current_itask();

      m_estatus = ::success;

      set_ok_flag();
      
   }


   void context_win32::_create_offscreen_buffer(const ::size_i32& size)
   {

      _create_offscreen_window(size);
      
      _create_window_buffer();

   }


   void context_win32::resize_offscreen_buffer(const ::size_i32& size)
   {

      //if (!m_pcpubuffer)
      {

         create_offscreen_buffer(size);

      }

      ///m_pcpubuffer->m_pixmap.create(m_pcpubuffer->m_memory, size);

//#ifdef WINDOWS_DESKTOP
//
//      ::SetWindowPos(m_hwnd, 0, 0, 0, size.cx(), size.cy(), SWP_NOZORDER | SWP_NOMOVE | SWP_HIDEWINDOW);
//
//#else

//      destroy_offscreen_buffer();
//
//      if(!create_offscreen_buffer(size))
//      {
//
//         return error_failed;
//
//      }

//#endif

      make_current();

      glViewport(0, 0, size.cx(), size.cy());
      //glMatrixMode(GL_PROJECTION);
      //glLoadIdentity();
      //glOrtho(0, size.cx(), 0, size.cy(), -10, 10);
      //glMatrixMode(GL_MODELVIEW);
      //glutPostRedisplay();

      //return ::success;

   }


   void context_win32::make_current()
   {

      ASSERT(m_itaskGpu == ::current_itask());

      ::e_status estatus = ::success;

      bool bMakeCurrentOk = wglMakeCurrent(m_hdc, m_hrc);

      if (!bMakeCurrentOk)
      {

         informationf("MS WGL - wglMakeCurrent failed");

         informationf("last-error code: %d\n", GetLastError());

         throw ::exception(error_failed);

      }

      //return estatus;

   }


   void context_win32::destroy_offscreen_buffer()
   {

      ASSERT(m_itaskGpu == ::current_itask());

      ::e_status estatus = ::success;

      if (m_hrc == NULL && m_hdc == NULL && m_hwnd == NULL)
      {

         return;

      }

      wglMakeCurrent(nullptr, nullptr);
      wglDeleteContext(m_hrc);
      ::ReleaseDC(m_hwnd, m_hdc);
      ::DestroyWindow(m_hwnd);
      m_size.set(0, 0);
      m_hrc = NULL;
      m_hwnd = NULL;
      m_hdc = NULL;

      //return estatus;

   }

   void context_win32::render()
   {

      ::opengl::context::render();

      

   }


   void context_win32::swap_buffers()
   {

      SwapBuffers(m_hdc);

   }


   string context_win32::get_shader_version_text()
   {

      return "#version 330 core";

   }


   void context_win32::_translate_shader(string_array& stra)
   {

      context::_translate_shader(stra);

      strsize iFindPrecision = stra.find_first_begins_ci("precision ");

      if (iFindPrecision >= 0)
      {

         stra[iFindPrecision] = "precision highp float;";

      }
      else
      {

         stra.insert_at(1, "precision highp float;");

         iFindPrecision = 1;

      }

   }


} // namespace opengl



