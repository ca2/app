#include "framework.h"
#include "_uwp.h"
#include "aura/os/universal_windows/_uwp.h"
#include "aura/message.h"
////#include "aura/user/user/_component.h"
#include "buffer.h"
#include <stdio.h>
#include "aura/node/universal_windows/directx_application.h"
#include "aura/os/windows_common/draw2d_direct2d_global.h"


#include "__debug_power.h"


#undef REDRAW_HINTING
//#define REDRAW_HINTING


#ifdef __DEBUG_POWER
#undef SQUARY_HINT
#define SQUARY_HINT
#endif


namespace universal_windows
{


   buffer::buffer()
   {

   }


   buffer::~buffer()
   {

   }


   void buffer::initialize_graphics_graphics(::user::interaction_impl* pimpl)
   {

      ::e_status estatus = ::graphics::bitmap_source_buffer::initialize_graphics_graphics(pimpl);

      if (!estatus)
      {

         return estatus;

      }

      auto puwpimpl = pimpl->cast < ::universal_windows::interaction_impl >();

      m_pframeworkview = puwpimpl->m_pframeworkview;

      return estatus;

   }


   bool buffer::create_os_buffer(const ::size_i32& size, int iStrideParam)
   {




      return true;

   }


   void buffer::destroy_os_buffer()
   {



   }


   ::draw2d::graphics* buffer::on_begin_draw()
   {

      auto pframeworkview = m_pframeworkview;

      if (!pframeworkview)
      {

         return nullptr;

      }

      if (!pframeworkview->m_directx->m_bCoreWindowVisible
         || pframeworkview->m_directx->m_ephase != ::universal_windows::e_phase_draw)
      {

         return nullptr;

      }

      auto directx = m_pframeworkview->m_directx;

      auto pdevicecontext = directx->get_device_context();

      if (pdevicecontext == nullptr)
      {

         return false;

      }

      __defer_construct(m_pdraw2dgraphics);

      if (m_pd2d1devicecontext.Get() != pdevicecontext)
      {

         //m_pdraw2dgraphics->set_direct2d_plugin(pframeworkview->m_directx->m_pplugin);

         m_pdraw2dgraphics->attach(pdevicecontext);

         m_pd2d1devicecontext = pdevicecontext;

      }

      if (!m_pd2d1devicecontext.Get())
      {

         return nullptr;

      }

      m_pd2d1devicecontext->BeginDraw();

      auto colorBackground = m_pframeworkview->m_puisettings->GetColorValue(::winrt::Windows::UI::ViewManagement::UIColorType::Background);

      D2D1_COLOR_F color32 = {};

      color32.a = 1.0f;
      color32.r = colorBackground.R / 255.f;
      color32.g = colorBackground.G / 255.f;
      color32.b = colorBackground.B / 255.f;

      m_pd2d1devicecontext->Clear(color32);

      m_pd2d1devicecontext->SetTransform(D2D1::Matrix3x2F::Identity());

      return m_pdraw2dgraphics;

   }


   void buffer::on_end_draw()
   {

      //auto pdevicecontext = (ID2D1DeviceContext*)m_pdraw2dgraphics->detach();

      if (m_pd2d1devicecontext)
      {

         HRESULT hr = m_pd2d1devicecontext->EndDraw();

         if (SUCCEEDED(hr))
         {
            
            m_pframeworkview->m_directx->m_ephase = ::universal_windows::e_phase_present;

         }
         else
         {

            output_debug_string("finished drawing with errors");

         }

      }

   }


   bool buffer::create_buffer(const ::size_i32& size, int iStrideParam)
   {

      return true;

   }


   void buffer::destroy_buffer()
   {

   }


   bool buffer::update_window()
   {

      //if (m_bNewBuffer)
      //{

         m_pframeworkview->m_directx->Present();

         //m_bNewBuffer = false;

      //}

      return true;

   }


   bool buffer::update_window(::image* pimage)
   {

      if (m_bNewBuffer)
      {

         m_pframeworkview->m_directx->Present();

      }

      return true;

   }


   bool buffer::buffer_lock_round_swap_key_buffers()
   {

      bool bOk2 = bitmap_source_buffer::buffer_lock_round_swap_key_buffers();

      return bOk2;

   }


} // namespace universal_windows



