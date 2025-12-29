#include "framework.h"
#include "approach.h"
#include "acme/filesystem/file/file.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "acme/platform/application.h"
#include "bred/gpu/context.h"
#include "windowing_win32/window.h"
#include <glad/glad_wgl.h>

#include <dwmapi.h>


namespace gpu_opengl
{



   void approach::_on_create_window(::windowing::window* pwindowParam)
   {

//#if defined(WINDOWS_DESKTOP)

      ::cast < ::windowing_win32::window > pwindow = pwindowParam;

      auto hwnd = pwindow->m_hwnd;

      opengl_on_create_window(hwnd, (HINSTANCE) system()->m_hinstanceThis);

      DWM_BLURBEHIND bb = { 0 };
      HRGN hRgn = CreateRectRgn(0, 0, -1, -1);
      bb.dwFlags = DWM_BB_ENABLE | DWM_BB_BLURREGION;
      bb.hRgnBlur = hRgn;
      bb.fEnable = TRUE;
      DwmEnableBlurBehindWindow(hwnd, &bb);

//#endif

   }

} // namespace gpu_opengl



