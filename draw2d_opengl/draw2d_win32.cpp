#include "framework.h"
#include "draw2d.h"
#include "windowing_win32/window.h"
#include "glad_wgl.h"
#include <dwmapi.h>

namespace draw2d_opengl
{
   // Helper to create dummy OpenGL context
   HGLRC CreateDummyContext(HDC hdc) {
      PIXELFORMATDESCRIPTOR pfd = {
          sizeof(PIXELFORMATDESCRIPTOR), 1,
          PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
          PFD_TYPE_RGBA, 32,
          0, 0, 0, 0, 0, 0,
          0, 0, 0, 0, 0, 0, 0,
          24, 8, 0,
          PFD_MAIN_PLANE,
          0, 0, 0, 0
      };

      int pixelFormat = ChoosePixelFormat(hdc, &pfd);
      SetPixelFormat(hdc, pixelFormat, &pfd);
      return wglCreateContext(hdc);
   }





   void draw2d::on_create_window(::windowing::window * pwindowParam)
   {

      ::cast < ::windowing_win32::window > pwindow = pwindowParam;

      auto hwnd = pwindow->m_hwnd;

      // OpenGL context setup
      HDC hdc = GetDC(hwnd);

      bool bTransparencyEnabled = true;

      if (bTransparencyEnabled)
      {

         PIXELFORMATDESCRIPTOR pfd = {
    sizeof(PIXELFORMATDESCRIPTOR),
    1,                                // Version Number
    PFD_DRAW_TO_WINDOW |         // Format Must Support Window
    PFD_SUPPORT_OPENGL |         // Format Must Support OpenGL
    PFD_SUPPORT_COMPOSITION |         // Format Must Support Composition
    PFD_DOUBLEBUFFER,                 // Must Support Double Buffering
    PFD_TYPE_RGBA,                    // Request An RGBA Format
    32,                               // Select Our Color Depth
    0, 0, 0, 0, 0, 0,                 // Color Bits Ignored
    8,                                // An Alpha Buffer
    0,                                // Shift Bit Ignored
    0,                                // No Accumulation Buffer
    0, 0, 0, 0,                       // Accumulation Bits Ignored
    24,                               // 16Bit Z-Buffer (Depth Buffer)
    8,                                // Some Stencil Buffer
    0,                                // No Auxiliary Buffer
    PFD_MAIN_PLANE,                   // Main Drawing Layer
    0,                                // Reserved
    0, 0, 0                           // Layer Masks Ignored
         };

      //   HGLRC dummyRC = CreateDummyContext(hdc);
      //   wglMakeCurrent(hdc, dummyRC);
      //   if (!gladLoadWGL(hdc))
      //   {

      //      throw ::exception(error_failed);

      //   }
    

         HDC hdc = GetDC(hwnd);
         int PixelFormat = ChoosePixelFormat(hdc, &pfd);
         if (PixelFormat == 0) {
            throw ::exception(error_failed);
         }

         BOOL bResult = SetPixelFormat(hdc, PixelFormat, &pfd);
         if (bResult == FALSE) {
            throw ::exception(error_failed);
         }

         ::ReleaseDC(hwnd, hdc);
      //   int attribs[] = {
      // WGL_DRAW_TO_WINDOW_ARB, TRUE,
      // WGL_DOUBLE_BUFFER_ARB, TRUE,
      // WGL_SUPPORT_OPENGL_ARB, TRUE,
      // WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
      // WGL_TRANSPARENT_ARB, TRUE,
      // WGL_COLOR_BITS_ARB, 32,
      // WGL_RED_BITS_ARB, 8,
      // WGL_GREEN_BITS_ARB, 8,
      // WGL_BLUE_BITS_ARB, 8,
      // WGL_ALPHA_BITS_ARB, 8,
      // WGL_DEPTH_BITS_ARB, 24,
      // WGL_STENCIL_BITS_ARB, 8,
      // 0, 0
      //   };

      //   INT iPF;
      //   UINT num_formats_choosen;
      //   if (!wglChoosePixelFormatARB(
      //      hdc,
      //      attribs,
      //      NULL,
      //      1,
      //      &iPF,
      //      &num_formats_choosen)) {
      //      fprintf(stderr, "error choosing proper pixel format\n");
      //      throw ::exception(error_failed);
      //   }
      //   if (!num_formats_choosen) {
      //      throw ::exception(error_failed);
      //   }

      //   PIXELFORMATDESCRIPTOR pfd;
      //   memset(&pfd, 0, sizeof(pfd));
      //   /* now this is a kludge; we need to pass something in the PIXELFORMATDESCRIPTOR
      //    * to SetPixelFormat; it will be ignored, mostly. OTOH we want to send something
      //    * sane, we're nice people after all - it doesn't hurt if this fails. */
      //   DescribePixelFormat(hdc, iPF, sizeof(pfd), &pfd);

      //   if (!SetPixelFormat(hdc, iPF, &pfd)) {
      //      fprintf(stderr, "error setting proper pixel format\n");
      //      ReleaseDC(hwnd, hdc);
      //      DestroyWindow(hwnd);

      //      throw ::exception(error_failed);
      //   }

      //}
      //else
      //{


      //   PIXELFORMATDESCRIPTOR pfd = {};
      //   pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
      //   pfd.nVersion = 1;
      //   pfd.dwFlags = PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER | PFD_DRAW_TO_WINDOW;
      //   pfd.iPixelType = PFD_TYPE_RGBA;
      //   pfd.cColorBits = 32;
      //   pfd.cAlphaBits = 8;
      //   pfd.cDepthBits = 24;

      //   int format = ChoosePixelFormat(hdc, &pfd);
      //   SetPixelFormat(hdc, format, &pfd);

      }

      ////if (impl_DwmEnableBlurBehindWindow) {
      //   DWM_BLURBEHIND bb = { 0 };
      //   bb.dwFlags = DWM_BB_ENABLE;
      //   bb.fEnable = TRUE;
      //   bb.hRgnBlur = NULL;
      //   DwmEnableBlurBehindWindow(hwnd, &bb);
      ////}

      ////if (impl_DwmExtendFrameIntoClientArea) {
      //   MARGINS margins = { -1 };
      //   DwmExtendFrameIntoClientArea(hwnd, &margins);
      ////}


      DWM_BLURBEHIND bb = { 0 };
      HRGN hRgn = CreateRectRgn(0, 0, -1, -1);
      bb.dwFlags = DWM_BB_ENABLE | DWM_BB_BLURREGION;
      bb.hRgnBlur = hRgn;
      bb.fEnable = TRUE;
      DwmEnableBlurBehindWindow(hwnd, &bb);

   }



} // namespace draw2d_opengl