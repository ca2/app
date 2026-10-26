#include "platform.h"
#include "device_egl.h"
#include "bred/gpu/device.h"
#if defined(MACOS)
#include <OpenGL/OpenGL.h>
//#include <glad/glad.h>
//#include <OpenGL/CGLTypes.h>
//////#include <OpenGL/glu.h>
#include <OpenGL/gl3.h>
#include <OpenGL/glext.h>
#endif
#include "approach.h"
#include "acme/filesystem/file/file.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "acme/platform/application.h"
#include "bred/gpu/context.h"
#include "aura/windowing/window.h"


namespace gpu_opengl
{


   void approach::gpu_on_before_create_window(::acme::windowing::window* pwindowParam)
   {

      ::gpu::bred_approach::gpu_on_before_create_window(pwindowParam);


   }


   void approach::gpu_on_create_window(::acme::windowing::window* pacmewindowingwindow)
   {

      ::gpu::bred_approach::gpu_on_create_window(pacmewindowingwindow);

      // if (!pgpudevice->m_pgpucontextMain)
      // {
      //
      //    pgpudevice->m_pgpucontextMain = pgpudevice->allocate_context();
      //
      //    auto & pgpucontextMain = pgpudevice->m_pgpucontextMain;
      //
      //    pgpucontextMain->create_window_context(pgpudevice, pwindowParam);
      //
      // }


      // //#if defined(WINDOWS_DESKTOP)
      //
      // ::cast < ::windowing_win32::window > pwindow = pwindowParam;
      //
      // auto hwnd = pwindow->m_hwnd;
      //
      // opengl_on_create_window(hwnd, (HINSTANCE) system()->m_hinstanceThis);
      //
      // DWM_BLURBEHIND bb = { 0 };
      // HRGN hRgn = CreateRectRgn(0, 0, -1, -1);
      // bb.dwFlags = DWM_BB_ENABLE | DWM_BB_BLURREGION;
      // bb.hRgnBlur = hRgn;
      // bb.fEnable = TRUE;
      // DwmEnableBlurBehindWindow(hwnd, &bb);
      //
      // //#endif

   }


   void approach::_gpu_on_create_window(::acme::windowing::window* pacmewindowingwindow)
   {

   }


} // namespace gpu_opengl



