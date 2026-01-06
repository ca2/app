#include "framework.h"
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
//#include "windowing_win32/window.h"
//#include <glad/glad_wgl.h>

//#include <dwmapi.h>


namespace gpu_opengl
{

   //
   // void approach::on_create_window(::windowing::window* pwindow)
   // {
   //
   //    ::cast < ::gpu_opengl::approach > papproach = m_papplication->get_gpu_approach();
   //    papproach->_on_create_window(pwindow);
   //    //::draw2d_gpu::draw2d::on_create_window(pwindowParam);
   //
   //    //::cast < ::windowing_win32::window > pwindow = pwindowParam;
   //
   //    //auto hwnd = pwindow->m_hwnd;
   //
   //    //HRGN hRgn = CreateRectRgn(0, 0, -1, -1);
   //    //bb.dwFlags = DWM_BB_ENABLE | DWM_BB_BLURREGION;
   //    //bb.hRgnBlur = hRgn;
   //    //bb.fEnable = TRUE;
   //    //DwmEnableBlurBehindWindow(hwnd, &bb);
   //
   // }


   void approach::_on_before_create_window(windowing::window* pwindowParam)
   {

      ::cast < ::gpu_opengl::device_egl > pegldevice = get_gpu_device(pwindowParam);

      pwindowParam->m_lX11NativeVisualId = pegldevice->m_lX11NativeVisualId;


   }


   void approach::_on_create_window(::windowing::window* pwindowParam)
   {

      auto pgpucontextMain = m_pgpudevice->main_context(pwindowParam);

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


} // namespace gpu_opengl



