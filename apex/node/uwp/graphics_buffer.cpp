#include "framework.h"
#include "_uwp.h"
#include "apex/os/uwp/_uwp.h"
#include "apex/message.h"
#include "apex/user/_user.h"
#include "buffer.h"
#include <stdio.h>


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


   ::estatus buffer::initialize_graphics_graphics(::user::interaction_impl* pimpl)
   {

      ::estatus estatus = ::graphics::bitmap_source_buffer::initialize_graphics_graphics(pimpl);

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

      auto colorBackground = m_frameworkview->m_puisettings->GetColorValue(Windows::UI::ViewManagement::UIColorType::Background);

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


} // namespace uwp



