﻿#include "framework.h"
#include "_uwp.h"
#include "acme/node/operating_system/universal_windows/_uwp.h"
#include "acme/message.h"
#include "acme/user/_user.h"
#include "buffer.h"
#include <stdio.h>


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


   ::e_status buffer::initialize_graphics_graphics(::user::interaction_impl* pimpl)
   {

      ::e_status estatus = ::graphics::bitmap_source_buffer::initialize_graphics_graphics(pimpl);

      if (!estatus)
      {

         return estatus;

      }

      m_frameworkview = psession->m_frameworkview;

      return estatus;

   }


   bool buffer::create_os_buffer(const ::size& size, int iStrideParam)
   {

      return true;

   }


   void buffer::destroy_os_buffer()
   {



   }


   ::draw2d::graphics* buffer::on_begin_draw()
   {

      auto directxapplication = m_frameworkview;

      auto directx = directxapplication->m_directx;

      auto pdevicecontext = directx->get_device_context();

      if(pdevicecontext == nullptr)
      {

         return nullptr;

      }

      __defer_construct(m_pdraw2dgraphics);

      m_pdraw2dgraphics->attach(pdevicecontext);

      pdevicecontext->BeginDraw();

      auto colorBackground = m_frameworkview->m_puisettings->GetColorValue(::winrt::Windows::UI::ViewManagement::UIColorType::Background);

      D2D1_COLOR_F color32 = {};

      color32.a = 1.0f;
      color32.r = colorBackground.R / 255.f;
      color32.g = colorBackground.G / 255.f;
      color32.b = colorBackground.B / 255.f;

      pdevicecontext->Clear(color32);

      pdevicecontext->SetTransform(D2D1::Matrix3x2F::Identity());

      return m_pdraw2dgraphics;

   }


   void buffer::on_end_draw()
   {

      auto pdevicecontext = (ID2D1DeviceContext*)m_pdraw2dgraphics->detach();

      if (pdevicecontext)
      {

         HRESULT hr = pdevicecontext->EndDraw();

         if (FAILED(hr))
         {

            output_debug_string("finished drawing with errors");

         }

      }

   }


   bool buffer::create_buffer(const ::size& size, int iStrideParam)
   {

      return true;

   }


   void buffer::destroy_buffer()
   {

   }


   bool buffer::update_window()
   {

      if (m_bNewBuffer)
      {

         m_frameworkview->m_directx->Present();

         m_bNewBuffer = false;

      }

      return true;

   }


   bool buffer::update_window(::image* pimage)
   {

      if (m_bNewBuffer)
      {

         m_frameworkview->m_directx->Present();

      }

      return true;

   }


   bool buffer::round_swap_key_buffers()
   {

      bool bOk2 = bitmap_source_buffer::round_swap_key_buffers();

      return bOk2;

   }


} // namespace universal_windows



