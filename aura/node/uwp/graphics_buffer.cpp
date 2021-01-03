﻿#include "framework.h"
#include "_uwp.h"
#include "aura/os/uwp/_uwp.h"
#include "aura/message.h"
#include "aura/user/_user.h"
#include "buffer.h"
#include <stdio.h>
#include "aura/node/uwp/directx_application.h"


#include "__debug_power.h"


#undef REDRAW_HINTING
//#define REDRAW_HINTING


#ifdef __DEBUG_POWER
#undef SQUARY_HINT
#define SQUARY_HINT
#endif


namespace uwp
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

      auto puwpimpl = pimpl->cast < ::uwp::interaction_impl >();

      m_pframeworkview = puwpimpl->m_pframeworkview;

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

      auto pframeworkview = m_pframeworkview;

      if (!pframeworkview)
      {

         return nullptr;

      }


      auto directx = pframeworkview->m_directx;

      auto pdevicecontext = directx->get_device_context();

      if(pdevicecontext == nullptr)
      {

         return nullptr;

      }

      __defer_construct(m_pdraw2dgraphics);

      m_pdraw2dgraphics->attach(pdevicecontext);

      pdevicecontext->BeginDraw();

      auto colorBackground = m_pframeworkview->m_puisettings->GetColorValue(Windows::UI::ViewManagement::UIColorType::Background);

      D2D1_COLOR_F cr = {};

      cr.a = 1.0f;
      cr.r = colorBackground.R / 255.f;
      cr.g = colorBackground.G / 255.f;
      cr.b = colorBackground.B / 255.f;

      pdevicecontext->Clear(cr);

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


   bool buffer::round_swap_key_buffers()
   {

      bool bOk2 = bitmap_source_buffer::round_swap_key_buffers();

      return bOk2;

   }


} // namespace uwp



