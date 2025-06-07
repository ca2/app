#include "framework.h"
#include "context_win32.h"
#include "approach.h"
#include "device.h"
#include "cpu_buffer.h"
#include "renderer.h"
#include "aura/graphics/gpu/approach.h"
#include "aura/graphics/gpu/types.h"
#include "aura/graphics/image/image.h"
#include "acme/platform/application.h"
#include "aura/platform/system.h"
#include "windowing_win32/window.h"
#include "glad_wgl.h"


namespace gpu_opengl
{


   ::pointer < ::gpu::context > allocate_system_context(::particle * pparticle)
   {

      return pparticle->__create_new <context_win32>();

   }


   context_win32::context_win32()
   {
      m_fboID = 0;
      m_bMesa = false;

      //m_emode = e_mode_system;

      m_estatus = error_not_initialized;

   }


   context_win32::~context_win32()
   {

   }


   bool context_win32::is_mesa()
   {

      return m_bMesa;

   }


   void context_win32::on_create_context(const ::gpu::start_context_t & startcontext)
   {

      if (startcontext.m_eoutput == ::gpu::e_output_cpu_buffer)
      {

         if (startcontext.m_callbackImage32CpuBuffer
            && !startcontext.m_rectanglePlacement.is_empty())
         {

            ASSERT(startcontext.m_callbackImage32CpuBuffer);
            ASSERT(!startcontext.m_rectanglePlacement.is_empty());

            create_offscreen_buffer(startcontext.m_rectanglePlacement.size());

         }

      }
      else if(startcontext.m_eoutput == ::gpu::e_output_swap_chain)
      {

         defer_create_window_context(startcontext.m_pwindow);

      }
      else 
      {

         auto r = startcontext.m_rectanglePlacement;

         send([this, r]()
            {

               _create_offscreen_buffer(r.size());

               make_current();

               glGenFramebuffers(1, &m_fboID);

            });
      }


   }

   
   void context_win32::_create_offscreen_window(const ::int_size & size)
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
         //unsigned int dwStyle = WS_CAPTION | WS_POPUPWINDOW; // | WS_VISIBLE
         unsigned int dwExStyle = 0;
         unsigned int dwStyle = WS_OVERLAPPEDWINDOW;
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

      if (!m_hdc || !m_hrc)
      {

         ::cast < device > pgpudevice = m_pgpudevice;

         ::cast < approach > pgpuapproach = pgpudevice->m_pgpuapproach;

         if (!pgpuapproach->m_atomClass)
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

         pgpuapproach->defer_init_gpu_library();

         auto pszVersion = (const char *)glGetString(GL_VERSION);
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
         m_hrc = hglrc;

      }

      RECT rectClient;

      ::GetClientRect(m_hwnd, &rectClient);

      m_size = { rectClient.right - rectClient.left,
         rectClient.bottom - rectClient.top };

      get_renderer()->set_placement({0, 0, m_size.cx(), m_size.cy()});

      m_itaskGpu = ::current_itask();

      m_estatus = ::success;

      set_ok_flag();
      
   }


   void context_win32::_create_window_context(::windowing::window * pwindowParam)
   {

      ::cast < ::windowing_win32::window > pwindow = pwindowParam;

      if (!m_hdc || !m_hrc)
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

            auto pszVersion = (const char *)glGetString(GL_VERSION);
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
            m_hrc = pwindow->m_hglrcProto;

            wglMakeCurrent(nullptr, nullptr);

         }

      }

      RECT rectClient;

      ::GetClientRect(m_hwnd, &rectClient);

      ::int_size sizeNew = { rectClient.right - rectClient.left,
   rectClient.bottom - rectClient.top };
      
      if (m_size != sizeNew)
      {
         m_size = sizeNew;

         m_sizeHost = sizeNew;
         //HDC pdcDIB;                      // контекст устройства в памяти
         //HBITMAP hbmpDIB;                 // и его текущий битмапvoid *pBitsDIB(NULL);            // содержимое битмапаint cxDIB(200); int cyDIB(300);  // его размеры (например для окна 200х300)
         //auto &BIH=pwindow->m_bitmapinfoheaderProto;            // и заголовок// …// создаем DIB section// создаем структуру BITMAPINFOHEADER, описывающую наш DIBint iSize = sizeof(BITMAPINFOHEADER);  // размер
         //memset(&BIH, 0, sizeof(pwindow->m_bitmapinfoheaderProto));

         //BIH.biSize = sizeof(pwindow->m_bitmapinfoheaderProto);        // размер структуры
         //BIH.biWidth = m_size.cx();       // геометрия
         //BIH.biHeight = m_size.cy();      // битмапа
         //BIH.biPlanes = 1;          // один план
         //BIH.biBitCount = 32;       // 24 bits per pixel
         //BIH.biCompression = BI_RGB;// без сжатия// создаем новый DC в памяти
         ////pdcDIB = CreateCompatibleDC(NULL);
         ////void * pBits = nullptr;
         //// создаем DIB-секцию
         //pwindow->m_hbitmapProto = CreateDIBSection(
         //  m_hdc,                  // контекст устройства
         //  (BITMAPINFO *)&BIH,       // информация о битмапе
         //  DIB_RGB_COLORS,          // параметры цвета
         //  &pwindow->m_pbitsProto,               // местоположение буфера (память выделяет система)
         //  NULL,                    // не привязываемся к отображаемым в память файлам
         //  0);

         //// выберем новый битмап (DIB section) для контекста устройства в памяти
         //SelectObject(m_hdc, pwindow->m_hbitmapProto);
         //pwindow->m_hdcProto = m_hdc;
      }

      m_itaskGpu = ::current_itask();

      m_estatus = ::success;

      set_ok_flag();

   }


   void context_win32::_create_offscreen_buffer(const ::int_size& size)
   {

      _create_offscreen_window(size);
      
      _create_window_buffer();

   }


   void context_win32::defer_create_window_context(::windowing::window * pwindow)
   {

      if (m_hrc)
      {

         return;

      }

      ::gpu_opengl::context::defer_create_window_context(pwindow);

   }


   void context_win32::_defer_create_window_context(::windowing::window * pwindow)
   {

      _create_window_context(pwindow);

   }


   void context_win32::resize_offscreen_buffer(const ::int_size& sizeParam)
   {

       if (m_papplication->m_bUseSwapChainWindow)
       {

           return;

       }

      auto size(sizeParam);

      send([this, size]()
         {
            //if (!m_pcpubuffer)

            create_offscreen_buffer(size);


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
            });


   }


   void context_win32::make_current()
   {

      if (m_itaskGpu != ::current_itask())
      {

         ASSERT(FALSE);

      }

      ::e_status estatus = ::success;

      bool bMadeCurrentNow = false;

      if (wglGetCurrentContext() != m_hrc || wglGetCurrentDC() != m_hdc)
      {

         bool bMakeCurrentOk = wglMakeCurrent(m_hdc, m_hrc);

         if (!bMakeCurrentOk)
         {

            informationf("MS WGL - wglMakeCurrent failed");

            informationf("last-error code: %d\n", GetLastError());

            throw ::exception(error_failed);

         }

         bMadeCurrentNow = true;

      }

      GLint drawFboId = 0, readFboId = 0;

      glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &drawFboId);
      glGetIntegerv(GL_READ_FRAMEBUFFER_BINDING, &readFboId);

      if (drawFboId != m_fboID)
      {

         glBindFramebuffer(GL_FRAMEBUFFER, m_fboID);

      }

      if(drawFboId != m_fboID || bMadeCurrentNow)
      {
         glViewport(0, 0, m_size.cx(), m_size.cy());
      }
      //glBindFramebuffer(GL_FRAMEBUFFER, m_fboID);

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

      ::gpu_opengl::context::render();

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

      character_count iFindPrecision = stra.case_insensitive_find_first_begins("precision ");

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


} // namespace gpu_opengl



