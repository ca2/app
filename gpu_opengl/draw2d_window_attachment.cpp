// Created by camilo on 2026-08-03 17:56 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
#include "framework.h"
#include "bred/gpu/bred_approach.h"
#include "bred/gpu/context.h"
#include "bred/gpu/device.h"
#include "draw2d_window_attachment.h"
#include "aura/graphics/graphics/graphics.h"
#include "aura/windowing/window.h"


#ifdef WINDOWS_DESKTOP
#include <dwmapi.h>
#pragma comment(lib, "Dwmapi.lib")
#endif


namespace gpu_opengl
{


   draw2d_window_attachment::draw2d_window_attachment()
   {

   }


   draw2d_window_attachment::~draw2d_window_attachment()
   {


   }


   void draw2d_window_attachment::initialize_window_attachment(::windowing::window * pwindow)
   {

      if (m_papplication->m_gpu.m_bUseSwapChainWindow)
      {
         //::direct2d::get() -> d2d1_factory1()->CreateHwndRenderTarget(rendertargetproperties,
           // hwndrendertargetproperties)
      }

      if (m_papplication->m_bGpu)
      {

         auto pgpuapproach = m_papplication->get_gpu_approach();

         //pgpuapproach->gpu_on_create_window(pwindow);

         ::string strType;

         strType = ::type(pwindow->m_pacmeuserinteraction).name();

         const_char_pointer pszType = strType.c_str();

         information("gpu::approach::gpu_on_create_window for type {}", pszType);

         auto pgpudevice = pgpuapproach->get_gpu_device(pwindow);

         m_pgpucontextWindow = pgpudevice->allocate_gpu_context();

         ::gpu::enum_output eoutput = ::gpu::e_output_none;

         if (m_papplication->m_gpu.m_bUseSwapChainWindow)
         {

            eoutput = ::gpu::e_output_swap_chain;

         }
         else
         {

            eoutput = ::gpu::e_output_gpu_buffer;

         }

         auto sizeWindow = pwindow->m_sizeWindow;

         ::gpu::enum_scene escene = ::gpu::e_scene_2d;

         m_pgpucontextWindow->create_window_gpu_context(pgpudevice, eoutput, escene, pwindow, sizeWindow);

         //::cast<::gpu_opengl::approach> papproach = m_papplication->get_gpu_approach();
         //_gpu_on_create_window(pacmewindowingwindow);
         //::draw2d_gpu::draw2d::on_create_window(pwindowParam);


         //void approach::_gpu_on_create_window(::acme::windowing::window * pwindowParam)
         //{

#if defined(WINDOWS_DESKTOP)



         auto hwnd = ::as_HWND(pwindow->operating_system_window());

         //auto pHWND = pwin32window->_HWND();

         //opengl_on_create_window(hwnd, (HINSTANCE) ::system()->m_hinstanceThis);

         DWM_BLURBEHIND bb = { 0 };
         HRGN hRgn = CreateRectRgn(0, 0, -1, -1);
         bb.dwFlags = DWM_BB_ENABLE | DWM_BB_BLURREGION;
         bb.hRgnBlur = hRgn;
         bb.fEnable = TRUE;
         DwmEnableBlurBehindWindow((HWND)hwnd, &bb);

#endif

         //         }

                  //::cast < ::windowing_win32::window > pwindow = pwindowParam;

                  // auto hwnd = pwindow->m_hwnd;

                  // HRGN hRgn = CreateRectRgn(0, 0, -1, -1);
                  // bb.dwFlags = DWM_BB_ENABLE | DWM_BB_BLURREGION;
                  // bb.hRgnBlur = hRgn;
                  // bb.fEnable = TRUE;
                  // DwmEnableBlurBehindWindow(hwnd, &bb);


      }

   }


   ::i32 draw2d_window_attachment::get_frame_index3()
   {

      return 0;
      //return ::gpu::device::get_frame_index3();


   }


   ::i32 draw2d_window_attachment::get_frame_count()
   {

      return 1;

   }



} // namespace gpu_opengl



