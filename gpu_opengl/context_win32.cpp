#include "framework.h"
#include "_.h"
#include "context_win32.h"
#include "aura/graphics/draw2d/image.h"


namespace opengl
{


   ::gpu::context * create_system_context()
   {

      return new context_win32();

   }


   context_win32::context_win32()
   {

      m_emode = e_mode_system;

   }


   context_win32::~context_win32()
   {

   }



   void context_win32::_create_offscreen_buffer(const ::size_i32& size)
   {

      auto psystem = get_system()->m_paurasystem;

      auto pgpu = psystem->get_gpu();

      auto popengl = pgpu->cast < ::opengl::opengl >();

      if (!popengl->m_atomClass)
      {

         TRACE("MS GDI - RegisterClass failed\n");

         FORMATTED_TRACE("last-error code: %d\n", GetLastError());

         return ::error_failed;

      }

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
      int nWidth = size.cx;
      int nHeight = size.cy;
      HWND hWndParent = nullptr;
      HMENU hMenu = nullptr;
      HINSTANCE hInstance = ::GetModuleHandleW(L"gpu_opengl.dll");
      LPVOID lpParam = nullptr;

      HWND window = CreateWindowExW(dwExStyle, lpClassName, lpWindowName, dwStyle, x, y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);

      if (!window)
      {

         TRACE("MS GDI - CreateWindow failed\n");

         FORMATTED_TRACE("last-error code: %d\n", GetLastError());

         return ::error_failed;

      }

      // create WGL context, make current

      PIXELFORMATDESCRIPTOR pixformat;

      int chosenformat;

      HDC hdc = GetDC(window);

      if (!hdc)
      {
         
         TRACE("MS GDI - GetDC failed\n");

         FORMATTED_TRACE("last-error code: %d\n", GetLastError());

         return ::error_failed;

      }

      __zero(pixformat);
      pixformat.nSize = sizeof(pixformat);
      pixformat.nVersion = 1;
      pixformat.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
      pixformat.iPixelType = PFD_TYPE_RGBA;
      pixformat.cColorBits = 32;
      //pixformat.cGreenBits = 8;
      //pixformat.cRedBits = 8;
      //pixformat.cBlueBits = 8;
      pixformat.cAlphaBits = 8;
      pixformat.cDepthBits = 24;
      pixformat.cStencilBits = 8;

      chosenformat = ChoosePixelFormat(hdc, &pixformat);

      if (chosenformat == 0)
      {
         
         TRACE("MS GDI - ChoosePixelFormat failed\n");

         FORMATTED_TRACE("last-error code: %d\n", GetLastError());

         ReleaseDC(window, hdc);

         return ::error_failed;

      }

      bool spfok = SetPixelFormat(hdc, chosenformat, &pixformat);

      if (!spfok)
      {

         TRACE("MS GDI - SetPixelFormat failed\n");

         FORMATTED_TRACE("last-error code: %d\n", GetLastError());

         ReleaseDC(window, hdc);

         return ::error_failed;

      }

      HGLRC hglrc = wglCreateContext(hdc);

      if (!hglrc)
      {

         TRACE("MS WGL - wglCreateContext failed\n");

         FORMATTED_TRACE("last-error code: %d\n", GetLastError());

         ReleaseDC(window, hdc);

         return ::error_failed;

      }

      bool bMakeCurrentOk = wglMakeCurrent(hdc, hglrc);

      if (!bMakeCurrentOk)
      {
         
         TRACE("MS WGL - wglMakeCurrent failed\n");

         FORMATTED_TRACE("last-error code: %d\n", GetLastError());
         
         ReleaseDC(window, hdc);

         return false;

      }

      ::e_status3 estatus = popengl->defer_init_glew();

      if (!estatus)
      {

         ReleaseDC(window, hdc);

         return estatus;

      }

      m_hwnd = window;
      m_hdc = hdc;
      m_hrc = hglrc;
      m_size = size;

      return ::success;

   }


   void context_win32::resize_offscreen_buffer(const ::size_i32& size)
   {

      if (!m_pbuffer)
      {

         return create_offscreen_buffer(size);

      }

      m_pbuffer->m_pimage->create(size);

#ifdef WINDOWS_DESKTOP

      ::SetWindowPos(m_hwnd, 0, 0, 0, size.cx, size.cy, SWP_NOZORDER | SWP_NOMOVE | SWP_HIDEWINDOW);

#else

//      destroy_offscreen_buffer();
//
//      if(!create_offscreen_buffer(size))
//      {
//
//         return error_failed;
//
//      }

#endif

      make_current();

      glViewport(0, 0, size.cx, size.cy);
      //glMatrixMode(GL_PROJECTION);
      //glLoadIdentity();
      //glOrtho(0, size.cx, 0, size.cy, -10, 10);
      //glMatrixMode(GL_MODELVIEW);
      //glutPostRedisplay();

      return ::success;

   }


   void context_win32::make_current()
   {

      ::e_status3 estatus = ::success;

      bool bMakeCurrentOk = wglMakeCurrent(m_hdc, m_hrc);

      if (!bMakeCurrentOk)
      {

         TRACE("MS WGL - wglMakeCurrent failed\n");

         FORMATTED_TRACE("last-error code: %d\n", GetLastError());

         estatus = error_failed;

      }

      return estatus;

   }


   void context_win32::destroy_offscreen_buffer()
   {

      ::e_status3 estatus = ::success;

      if (m_hrc == NULL && m_hdc == NULL && m_hwnd == NULL)
      {

         return true;

      }

      wglMakeCurrent(nullptr, nullptr);
      wglDeleteContext(m_hrc);
      ::ReleaseDC(m_hwnd, m_hdc);
      ::DestroyWindow(m_hwnd);
      m_size.set(0, 0);
      m_hrc = NULL;
      m_hwnd = NULL;
      m_hdc = NULL;

      return estatus;

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



