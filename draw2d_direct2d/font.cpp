#include "framework.h"


namespace draw2d_direct2d
{


   font::font()
   {

      m_pthis = this;

   }


   font::~font()
   {

   }


   void font::dump(dump_context & dumpcontext) const
   {

      ::draw2d::object::dump(dumpcontext);

   }


   bool font::create(::draw2d::graphics* pgraphics)
   {

      if(m_pformat == nullptr || is_modified())
      {

         if(m_pformat)
         {

            destroy();

         }

         IDWriteFactory * pfactory = global_draw_get_write_factory();

         DWRITE_FONT_STYLE style;

         if (m_bItalic)
         {

            style = DWRITE_FONT_STYLE_ITALIC;

         }
         else
         {

            style = DWRITE_FONT_STYLE_NORMAL;

         }

         DWRITE_FONT_STRETCH stretch;

         stretch = DWRITE_FONT_STRETCH_NORMAL;

         float fFontSize;

         if(m_eunitFontSize == ::draw2d::unit_point)
         {

            fFontSize = point_dpi(pgraphics->get_window_handle(), (float)m_dFontSize);

         }
         else
         {

            fFontSize = dpiy(pgraphics->get_window_handle(), (float)m_dFontSize);

         }

         fFontSize *= (float) pgraphics->m_dFontFactor;

         if (fFontSize <= 0.000001)
         {

            return nullptr;

         }

         HRESULT hr = pfactory->CreateTextFormat(
            wstring(m_strFontFamilyName),
            nullptr,
            (DWRITE_FONT_WEIGHT) m_iFontWeight,
            style,
            stretch,
            fFontSize,
            L"",
            &m_pformat);

         if(FAILED(hr) || m_pformat == nullptr)
         {

            trace_hr("font::get_os_font", hr);

            return nullptr;

         }

      }

      if(m_pformat != nullptr)
      {

         set_updated();

      }

      m_osdata[0] = m_pformat.Get();

      return (IDWriteTextFormat *) m_pformat.Get();

   }


   void font::destroy()
   {

      ::draw2d::font::destroy();

      if (m_pformat == nullptr)
      {

         return;

      }

      m_pformat = nullptr;

   }


} // namespace draw2d_direct2d


