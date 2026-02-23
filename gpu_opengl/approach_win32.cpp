#include "framework.h"
#include "gpu_opengl/_gpu_opengl.h"
#include "gpu_opengl/wgl_context.h"
#include "approach.h"
#include "context_win32.h"
#include "device.h"
#include "acme/filesystem/file/file.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "acme/platform/application.h"
#include "acme/platform/system.h"
#include "bred/gpu/context.h"
#include "windowing_win32/window.h"
#include <glad/glad_wgl.h>

#include <dwmapi.h>


CLASS_DECL_ACME HINSTANCE hinstance_from_function(void *pFunc);


namespace gpu_opengl
{



   

    void approach::gpu_on_before_create_window(::acme::windowing::window* pwindow)
       {
          //::cast < ::gpu_opengl::approach > papproach = m_papplication->get_gpu_approach();
          //papproach->_on_before_create_window(pwindow);
   // #if defined(WINDOWS_DESKTOP)
          //defer_load_wgl_extensions(this);
   // #endif
   //
       }

       void approach::gpu_on_create_window(::acme::windowing::window *pacmewindowingwindow)
       {

          ::gpu::bred_approach::gpu_on_create_window(pacmewindowingwindow);
       }



   // void opengl_on_create_window(HWND hwnd, HINSTANCE hInstance, HGLRC* outRC, HDC* outDC)
   void opengl_on_create_window(HWND hwnd, HINSTANCE hInstance)
   {


      // HDC dc = GetDC(hwnd);

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

      // int format;
      // UINT numFormats;
      // loaded_wglChoosePixelFormatARB(dc, pixelAttribs, NULL, 1, &format, &numFormats);
      // PIXELFORMATDESCRIPTOR pfd;
      // DescribePixelFormat(dc, format, sizeof(pfd), &pfd);
      // SetPixelFormat(dc, format, &pfd);

      // int contextAttribs[] = {
      //     WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
      //     WGL_CONTEXT_MINOR_VERSION_ARB, 3,
      //     WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
      //     0
      // };

      ///*HGLRC rc = wglCreateContextAttribsARB(dc, 0, contextAttribs);
      // wglMakeCurrent(dc, rc);

      //*outRC = rc;
      //*outDC = dc;*/
      //::ReleaseDC(hwnd, dc);
   }


   void approach::_gpu_on_create_window(::acme::windowing::window *pwindowParam)
   {

//#if defined(WINDOWS_DESKTOP)

   

      ::cast < ::windowing_win32::window > pwindow = pwindowParam;

      auto hwnd = pwindow->_HWND();

      opengl_on_create_window(hwnd, (HINSTANCE) ::system()->m_hinstanceThis);

      DWM_BLURBEHIND bb = { 0 };
      HRGN hRgn = CreateRectRgn(0, 0, -1, -1);
      bb.dwFlags = DWM_BB_ENABLE | DWM_BB_BLURREGION;
      bb.hRgnBlur = hRgn;
      bb.fEnable = TRUE;
      DwmEnableBlurBehindWindow(hwnd, &bb);

//#endif

   }

} // namespace gpu_opengl



