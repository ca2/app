// Recreated by camilo on 2026-01-12 03:02 <3ThomasBorregaardSørensen!!
#include "framework.h"
#define STB_USE_HUNTER
#include "_gpu_opengl.h"
#include "approach.h"
#include "context_win32.h"
#include "device.h"
#include "device_win32.h"
#include "acme/platform/application.h"
#include "windowing_win32/window.h"
#include <glad/glad_wgl.h>


namespace gpu_opengl
{
   
   
   extern PFNWGLCREATECONTEXTATTRIBSARBPROC loaded_wglCreateContextAttribsARB;
   extern PFNWGLCHOOSEPIXELFORMATARBPROC loaded_wglChoosePixelFormatARB;

   context_win32::context_win32()
   {
   
      m_hdc = nullptr;
      m_hglrc = nullptr;
      m_hwnd = nullptr;
   
   } 


   context_win32::~context_win32()
   {


   }


   void context_win32::_create_cpu_buffer(const ::int_size &size)
   {

       if (!m_pgpudevice)
       {

          throw ::exception(error_wrong_state);

       }
       if (!m_pgpudevice->m_pwindow)
       {

          throw ::exception(error_wrong_state);
       }
       //_create_offscreen_window(size);

      //_create_window_buffer();



      //void device_win32::_create_device(const ::int_size &size)
      //{

         if (m_hdc && m_hglrc)
         {

            return;
         }

         ::cast<approach> pgpuapproach = ::system()->m_papplication->gpu_approach();

         if (!pgpuapproach->m_atomClass)
         {

            informationf("MS GDI - RegisterClass failed");

            informationf("last-error code: %d\n", GetLastError());

            throw ::exception(error_failed);
         }

         //// create WGL context, make current

         // PIXELFORMATDESCRIPTOR pixformat;

         // int chosenformat;

         // HDC hdc;

         // if (m_hdc)
         //{

         //   hdc = m_hdc;

         //}
         // else
         //{

         //   hdc = GetDC(m_hwnd);

         //   if (!hdc)
         //   {

         //      informationf("MS GDI - GetDC failed");

         //      informationf("last-error code: %d\n", GetLastError());

         //      throw ::exception(error_failed);

         //   }

         //}

         // zero(pixformat);
         // pixformat.nSize = sizeof(pixformat);
         // pixformat.nVersion = 1;
         // pixformat.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
         // pixformat.iPixelType = PFD_TYPE_RGBA;
         // pixformat.cColorBits = 32;
         // pixformat.cRedShift = 16;
         // pixformat.cGreenShift = 8;
         // pixformat.cBlueShift = 0;
         // pixformat.cAlphaShift = 24;
         // pixformat.cAlphaBits = 8;
         // pixformat.cDepthBits = 24;
         // pixformat.cStencilBits = 8;

         // chosenformat = ChoosePixelFormat(hdc, &pixformat);

         // if (chosenformat == 0)
         //{

         //   informationf("MS GDI - ChoosePixelFormat failed");

         //   informationf("last-error code: %d\n", GetLastError());

         //   ReleaseDC(m_hwnd, hdc);

         //   throw ::exception(error_failed);

         //}

         // bool spfok = SetPixelFormat(hdc, chosenformat, &pixformat);

         // if (!spfok)
         //{

         //   informationf("MS GDI - SetPixelFormat failed");

         //   informationf("last-error code: %d\n", GetLastError());

         //   ReleaseDC(m_hwnd, hdc);

         //   throw ::exception(error_failed);

         //}

         // HGLRC hglrc = wglCreateContext(hdc);

         // if (!hglrc)
         //{

         //   informationf("MS WGL - wglCreateContext failed");

         //   informationf("last-error code: %d\n", GetLastError());

         //   ReleaseDC(m_hwnd, hdc);

         //   throw ::exception(error_failed);

         //}

         // bool bMakeCurrentOk = wglMakeCurrent(hdc, hglrc);

         // if (!bMakeCurrentOk)
         //{

         //   informationf("MS WGL - wglMakeCurrent failed");

         //   informationf("last-error code: %d\n", GetLastError());

         //   ReleaseDC(m_hwnd, hdc);

         //   throw ::exception(error_failed);

         //}

         // pgpuapproach->defer_init_gpu_library();

         // auto pszVersion = (const_char_pointer )glGetString(GL_VERSION);
         ////::e_status estatus =

         //::string strVersion(scopedstrVersion);

         // if (strVersion.case_insensitive_contains("mesa"))
         //{

         //   m_bMesa = true;

         //}

         ////if (!estatus)
         ////{

         ////   ReleaseDC(window, hdc);

         ////   return estatus;

         ////}

         // m_hwnd = m_hwnd;
         // m_hdc = hdc;
         // m_hrc = hglrc;

         // wglMakeCurrent(nullptr, nullptr);

         // m_itaskCurrentGpuContext = {};

         // RECT rectClient;

         //::GetClientRect(m_hwnd, &rectClient);

         // m_rectangleWin32 = rectClient;

         // m_estatus = ::success;

         // set_ok_flag();
         ::cast<::gpu_opengl::device_win32> pdevice = m_pgpudevice;
         ::cast<::win32::acme::windowing::window> pwindow = m_pgpudevice->m_pwindow;

         HWND hwnd = pwindow->m_hwnd;

         HDC hdc = GetDC(hwnd);

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

         int_array_base pixelAttribs;


         pixelAttribs.append({WGL_DRAW_TO_WINDOW_ARB, GL_TRUE});
         pixelAttribs.append({WGL_SUPPORT_OPENGL_ARB, GL_TRUE});
         if (pdevice->m_bAddSwapChainSupport)
         {
            pixelAttribs.append({WGL_DOUBLE_BUFFER_ARB, GL_TRUE}); // <-- double buffering
         }
         pixelAttribs.append({WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB});
         pixelAttribs.append({WGL_COLOR_BITS_ARB, 32}); // total color bits
         pixelAttribs.append({WGL_RED_BITS_ARB, 8});
         pixelAttribs.append({WGL_GREEN_BITS_ARB, 8});
         pixelAttribs.append({WGL_BLUE_BITS_ARB, 8});
         pixelAttribs.append({WGL_ALPHA_BITS_ARB, 8}); // <-- alpha support
         pixelAttribs.append({WGL_DEPTH_BITS_ARB, 24}); // optional, for depth buffer
         pixelAttribs.append({WGL_STENCIL_BITS_ARB, 8}); // optional, for stencil
         pixelAttribs.add(0); // terminator

         int format = 0;
         UINT numFormats = 0;
         loaded_wglChoosePixelFormatARB(hdc, pixelAttribs.data(), NULL, 1, &format, &numFormats);
         PIXELFORMATDESCRIPTOR pfd;
         DescribePixelFormat(hdc, format, sizeof(pfd), &pfd);
         SetPixelFormat(hdc, format, &pfd);

         int contextAttribs[] = {
            WGL_CONTEXT_MAJOR_VERSION_ARB,    3, WGL_CONTEXT_MINOR_VERSION_ARB, 3, WGL_CONTEXT_PROFILE_MASK_ARB,
            WGL_CONTEXT_CORE_PROFILE_BIT_ARB, 0};

         HGLRC hglrc = loaded_wglCreateContextAttribsARB(hdc, pgpuapproach->m_hglrcShare, contextAttribs);

         if (!pgpuapproach->m_hglrcShare)
         {

            pgpuapproach->m_hglrcShare = hglrc;

         }
         // wglMakeCurrent(dc, rc);
         //
         //*outRC = rc;
         //*outDC = dc;*/
         ////::ReleaseDC(hwnd, dc);

         bool bMakeCurrentOk = wglMakeCurrent(hdc, hglrc);

         if (!bMakeCurrentOk)
         {

            informationf("MS WGL - wglMakeCurrent failed");

            informationf("last-error code: %d\n", GetLastError());

            ReleaseDC(hwnd, hdc);

            throw ::exception(error_failed);
         }

         pgpuapproach->defer_init_gpu_library();

         auto pszVersion = (const_char_pointer)glGetString(GL_VERSION);
         //::e_status estatus =

         ::string strVersion(pszVersion);

         if (strVersion.case_insensitive_contains("mesa"))
         {

            m_bMesa = true;
         }

         // if (!estatus)
         //{

         //   ReleaseDC(window, hdc);

         //   return estatus;

         //}

         // m_hwnd = m_hwnd;
         m_hdc = hdc;
         m_hglrc = hglrc;

         wglMakeCurrent(nullptr, nullptr);

         //m_itaskCurrentGpuContext = {};

         RECT rectClient;

         ::GetClientRect(hwnd, &rectClient);

         //m_rectangleWin32 = rectClient;

         m_estatus = ::success;

         set_ok_flag();
//    }


   }


//    //void context::_create_b
//
//   void context::_create_offscreen_window(const ::int_size &size)
//   {
//
////#if defined(WINDOWS_DESKTOP)
//
//      //::cast<device_win32> pdevice = m_pgpudevice;
//
//      //pdevice->_defer_create_offscreen_window(size);
//
////#elif defined(LINUX)
////
////      ::cast<device_egl> pdevice = m_pgpudevice;
////
////      pdevice->_defer_create_offscreen_window(size);
////
////#endif
//
//      // if (::IsWindow(m_hwnd))
//      //{
//
//      //   if (!::SetWindowPos(m_hwnd,
//      //      nullptr, 0, 0,
//      //      size.cx
//      //      , size.cy, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE
//      //      | SWP_NOCOPYBITS | SWP_NOSENDCHANGING
//      //      | SWP_NOREPOSITION | SWP_NOREDRAW))
//      //   {
//
//      //      information() << "SetWindowPos Failed";
//
//      //   }
//
//
//      //   //return m_hwnd;
//
//      //}
//      // else
//      //{
//
//      //   LPCTSTR lpClassName = L"draw2d_opengl_offscreen_buffer_window";
//      //   LPCTSTR lpWindowName = L"draw2d_opengl_offscreen_buffer_window";
//      //   //unsigned int dwStyle = WS_CAPTION | WS_POPUPWINDOW; // | WS_VISIBLE
//      //   unsigned int dwExStyle = 0;
//      //   unsigned int dwStyle = WS_OVERLAPPEDWINDOW;
//      //   dwStyle |= WS_POPUP;
//      //   //dwStyle |= WS_VISIBLE;
//      //   //dwStyle |= WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;
//      //   dwStyle &= ~WS_CAPTION;
//      //   //dwStyle = 0;
//      //   dwStyle &= ~WS_THICKFRAME;
//      //   dwStyle &= ~WS_BORDER;
//      //   int x = 0;
//      //   int y = 0;
//      //   int nWidth = size.cx;
//      //   int nHeight = size.cy;
//      //   HWND hWndParent = nullptr;
//      //   HMENU hMenu = nullptr;
//      //   HINSTANCE hInstance = ::GetModuleHandleW(L"gpu_opengl.dll");
//      //   LPVOID lpParam = nullptr;
//
//      //   m_hwnd = CreateWindowExW(dwExStyle, lpClassName, lpWindowName, dwStyle, x, y, nWidth, nHeight, hWndParent,
//      //   hMenu, hInstance, lpParam);
//
//      //   if (!m_hwnd)
//      //   {
//
//      //      informationf("MS GDI - CreateWindow failed");
//
//      //      informationf("last-error code: %d\n", GetLastError());
//
//      //      throw ::exception(error_failed);
//
//      //   }
//
//      //   //return m_hwnd;
//
//      //}
//   }

   
   void context_win32::_context_lock()
   {

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

      if (wglGetCurrentContext() != m_hglrc || wglGetCurrentDC() != m_hdc)
      {

         bool bMakeCurrentOk = wglMakeCurrent(m_hdc, m_hglrc);

         if (!bMakeCurrentOk)
         {

            informationf("MS WGL - wglMakeCurrent failed");

            int iLastError = GetLastError();

            informationf("last-error code: %d\n", iLastError);

            throw ::exception(error_failed);
         }

               m_taskindex = current_task_index();
         m_itask = current_itask();
         m_htask = current_htask();

                  m_bContextSelected = true;


         // bMadeCurrentNow = true;
      }
   }


   void context_win32::_context_unlock()
   {


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


   void context_win32::assert_there_is_current_context()
   {

      HGLRC hglrcContext = wglGetCurrentContext();
      if (!hglrcContext)
      {
         printf("NO CURRENT CONTEXT\n");
      }
   }

   
   void context_win32::swap_buffers()
   {

      ::SwapBuffers(m_hdc);

   }


   void context_win32::_create_window_context(::acme::windowing::window *pwindowParam)
   {

         ::cast < ::windowing_win32::window > pwindow = pwindowParam;

         if (!m_hdc || !m_hglrc)
         {

            ::cast < approach > pgpuapproach = m_pgpudevice->m_pgpuapproach;

            //if (!popengl->m_atomClass)
            //{

            //   informationf("MS GDI - RegisterClass failed");

            //   informationf("last-error code: %d\n", GetLastError());

            //   throw ::exception(error_failed);

            //}

            if (!m_hwnd)
            {

               auto hwnd = pwindow->m_hwnd;


               m_hwnd = hwnd;


               //// create WGL context, make current

               //PIXELFORMATDESCRIPTOR pixformat;

               //int chosenformat;

               HDC hdc = GetDC(m_hwnd);

               //if (!hdc)
               //{

               //   informationf("MS GDI - GetDC failed");

               //   informationf("last-error code: %d\n", GetLastError());

               //   throw ::exception(error_failed);

               //}

               //zero(pixformat);
               //pixformat.nSize = sizeof(pixformat);
               //pixformat.nVersion = 1;
               //pixformat.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
               //pixformat.iPixelType = PFD_TYPE_RGBA;
               //pixformat.cColorBits = 32;
               //pixformat.cRedShift = 16;
               //pixformat.cGreenShift = 8;
               //pixformat.cBlueShift = 0;
               //pixformat.cAlphaShift = 24;
               //pixformat.cAlphaBits = 8;
               //pixformat.cDepthBits = 24;
               //pixformat.cStencilBits = 8;

               //chosenformat = ChoosePixelFormat(hdc, &pixformat);

               //if (chosenformat == 0)
               //{

               //   informationf("MS GDI - ChoosePixelFormat failed");

               //   informationf("last-error code: %d\n", GetLastError());

               //   ReleaseDC(m_hwnd, hdc);

               //   throw ::exception(error_failed);

               //}

               //bool spfok = SetPixelFormat(hdc, chosenformat, &pixformat);

               //if (!spfok)
               //{

               //   informationf("MS GDI - SetPixelFormat failed");

               //   informationf("last-error code: %d\n", GetLastError());

               //   ReleaseDC(m_hwnd, hdc);

               //   throw ::exception(error_failed);

               //}

               auto hglrc = wglCreateContext(hdc);

               pwindow->m_hglrcProto = hglrc;

               //         int context_attribs[] = {
               //WGL_CONTEXT_MAJOR_VERSION_ARB, 2,
               //WGL_CONTEXT_MINOR_VERSION_ARB, 1,
               //0, 0
               //         };
               //         auto hglrc = wglCreateContextAttribsARB(hdc, NULL, context_attribs);
               //         if (!hglrc) {
               //            //ReleaseDC(hWnd, hDC);
               //            //DestroyWindow(hWnd);

               //            throw ::exception(error_failed);
               //         }
               //         //ReleaseDC(hWnd, hDC);

               if (!pwindow->m_hglrcProto)
               {

                  informationf("MS WGL - wglCreateContext failed");

                  informationf("last-error code: %d\n", GetLastError());

                  ReleaseDC(m_hwnd, hdc);

                  throw ::exception(error_failed);

               }

               auto hglrcProto = pwindow->m_hglrcProto;

               bool bMakeCurrentOk = wglMakeCurrent(hdc, hglrcProto);

               if (!bMakeCurrentOk)
               {

                  informationf("MS WGL - wglMakeCurrent failed");

                  informationf("last-error code: %d\n", GetLastError());

                  ReleaseDC(m_hwnd, hdc);

                  throw ::exception(error_failed);

               }

               m_pgpudevice->m_pgpuapproach->defer_init_gpu_library();

               auto pszVersion = (const_char_pointer )glGetString(GL_VERSION);
               //::e_status estatus =

               ::string strVersion(pszVersion);

               if (strVersion.case_insensitive_contains("mesa"))
               {

                  m_bMesa = true;

               }

               //if (!estatus)
               //{

               //   ReleaseDC(window, hdc);

               //   return estatus;

               //}

               m_hwnd = m_hwnd;
               m_hdc = hdc;
               m_hglrc = pwindow->m_hglrcProto;

               wglMakeCurrent(nullptr, nullptr);

            }

         }

         RECT rectClient;

         ::GetClientRect(m_hwnd, &rectClient);

       //  ::int_size sizeNew = { rectClient.right - rectClient.left,
       //rectClient.bottom - rectClient.top };

       //  if (m_size != sizeNew)
       //  {
       //     m_size = sizeNew;

       //     m_sizeHost = sizeNew;
       //     //HDC pdcDIB;                      // контекст устройства в памяти
       //     //HBITMAP hbmpDIB;                 // и его текущий битмапvoid *pBitsDIB(NULL);            // содержимое
       //     битмапаint cxDIB(200); int cyDIB(300);  // его размеры (например для окна 200х300)
       //     //auto &BIH=pwindow->m_bitmapinfoheaderProto;            // и заголовок// …// создаем DIB section//
       //     создаем структуру BITMAPINFOHEADER, описывающую наш DIBint iSize = sizeof(BITMAPINFOHEADER);  // размер
       //     //memset(&BIH, 0, sizeof(pwindow->m_bitmapinfoheaderProto));

       //     //BIH.biSize = sizeof(pwindow->m_bitmapinfoheaderProto);        // размер структуры
       //     //BIH.biWidth = m_size.cx;       // геометрия
       //     //BIH.biHeight = m_size.cy;      // битмапа
       //     //BIH.biPlanes = 1;          // один план
       //     //BIH.biBitCount = 32;       // 24 bits per pixel
       //     //BIH.biCompression = BI_RGB;// без сжатия// создаем новый DC в памяти
       //     ////pdcDIB = create_compatible_graphics(NULL);
       //     ////void * pBits = nullptr;
       //     //// создаем DIB-секцию
       //     //pwindow->m_hbitmapProto = CreateDIBSection(
       //     //  m_hdc,                  // контекст устройства
       //     //  (BITMAPINFO *)&BIH,       // информация о битмапе
       //     //  DIB_RGB_COLORS,          // параметры цвета
       //     //  &pwindow->m_pbitsProto,               // местоположение буфера (память выделяет система)
       //     //  NULL,                    // не привязываемся к отображаемым в память файлам
       //     //  0);

       //     //// выберем новый битмап (DIB section) для контекста устройства в памяти
       //     //SelectObject(m_hdc, pwindow->m_hbitmapProto);
       //     //pwindow->m_hdcProto = m_hdc;
       //  }

         //m_itaskGpu = ::current_itask();

         m_estatus = ::success;

         set_ok_flag();
   }


   void context_win32::_create_window_buffer()
   {

#if defined(WINDOWS_DESKTOP)

      //::cast<device_win32> pdevice = m_pgpudevice;

      //pdevice->_create_device(m_rectangle.size());

#elif defined(LINUX)

      ::cast<device_egl> pdevice = m_pgpudevice;

      pdevice->_create_device(m_rectangle.size());

#endif

      //if (!m_hdc || !m_hrc)
      //{

      //   ::cast < device > pgpudevice = m_pgpudevice;

      //   ::cast < approach > pgpuapproach = pgpudevice->m_pgpuapproach;

      //   if (!pgpuapproach->m_atomClass)
      //   {

      //      informationf("MS GDI - RegisterClass failed");

      //      informationf("last-error code: %d\n", GetLastError());

      //      throw ::exception(error_failed);

      //   }

      //   // create WGL context, make current

      //   PIXELFORMATDESCRIPTOR pixformat;

      //   int chosenformat;

      //   HDC hdc = GetDC(m_hwnd);

      //   if (!hdc)
      //   {

      //      informationf("MS GDI - GetDC failed");

      //      informationf("last-error code: %d\n", GetLastError());

      //      throw ::exception(error_failed);

      //   }

      //   zero(pixformat);
      //   pixformat.nSize = sizeof(pixformat);
      //   pixformat.nVersion = 1;
      //   pixformat.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
      //   pixformat.iPixelType = PFD_TYPE_RGBA;
      //   pixformat.cColorBits = 32;
      //   pixformat.cRedShift = 16;
      //   pixformat.cGreenShift = 8;
      //   pixformat.cBlueShift = 0;
      //   pixformat.cAlphaShift = 24;
      //   pixformat.cAlphaBits = 8;
      //   pixformat.cDepthBits = 24;
      //   pixformat.cStencilBits = 8;

      //   chosenformat = ChoosePixelFormat(hdc, &pixformat);

      //   if (chosenformat == 0)
      //   {

      //      informationf("MS GDI - ChoosePixelFormat failed");

      //      informationf("last-error code: %d\n", GetLastError());

      //      ReleaseDC(m_hwnd, hdc);

      //      throw ::exception(error_failed);

      //   }

      //   bool spfok = SetPixelFormat(hdc, chosenformat, &pixformat);

      //   if (!spfok)
      //   {

      //      informationf("MS GDI - SetPixelFormat failed");

      //      informationf("last-error code: %d\n", GetLastError());

      //      ReleaseDC(m_hwnd, hdc);

      //      throw ::exception(error_failed);

      //   }

      //   HGLRC hglrc = wglCreateContext(hdc);

      //   if (!hglrc)
      //   {

      //      informationf("MS WGL - wglCreateContext failed");

      //      informationf("last-error code: %d\n", GetLastError());

      //      ReleaseDC(m_hwnd, hdc);

      //      throw ::exception(error_failed);

      //   }

      //   bool bMakeCurrentOk = wglMakeCurrent(hdc, hglrc);

      //   if (!bMakeCurrentOk)
      //   {

      //      informationf("MS WGL - wglMakeCurrent failed");

      //      informationf("last-error code: %d\n", GetLastError());

      //      ReleaseDC(m_hwnd, hdc);

      //      throw ::exception(error_failed);

      //   }

      //   pgpuapproach->defer_init_gpu_library();

      //   auto pszVersion = (const_char_pointer )glGetString(GL_VERSION);
      //   //::e_status estatus =

      //   ::string strVersion(scopedstrVersion);

      //   if (strVersion.case_insensitive_contains("mesa"))
      //   {

      //      m_bMesa = true;

      //   }

      //   //if (!estatus)
      //   //{

      //   //   ReleaseDC(window, hdc);

      //   //   return estatus;

      //   //}

      //   m_hwnd = m_hwnd;
      //   m_hdc = hdc;
      //   m_hrc = hglrc;

      //}

      //RECT rectClient;

      //::GetClientRect(m_hwnd, &rectClient);

      //m_size = { rectClient.right - rectClient.left,
      //   rectClient.bottom - rectClient.top };

      //get_renderer()->set_placement({ 0, 0, m_size.cx, m_size.cy });

      //m_itaskGpu = ::current_itask();

      //m_estatus = ::success;

      //set_ok_flag();

   }


} // namespace gpu_opengl



