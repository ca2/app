#include "framework.h"





namespace draw2d_gdiplus
{


   font::font()
   {
      m_pthis = this;
      m_pfont = nullptr;

   }




   font::~font()
   {
      
      destroy();

      //::acme::del(m_pfontcollection);

   }



   bool font::GetLogFont(LOGFONTW * pfontw)
   {

      bool bOk = false;

      defer_update(nullptr, 0);

      if (m_pfont != nullptr)
      {

         HDC hdc = ::GetDC(nullptr);

         Gdiplus::Status status;
         {
            Gdiplus::Graphics g(hdc);

            status = m_pfont->GetLogFontW(&g, pfontw);

         }

         bOk = status == Gdiplus::Ok;

         ::ReleaseDC(nullptr, hdc);




      }


      return bOk;


   }


#ifdef DEBUG

   void font::dump(dump_context & dumpcontext) const
   {
      ::draw2d::object::dump(dumpcontext);

   }

#endif

   
   void font::destroy()
   {

      ::acme::del(m_pfont);

      ::write_text::font::destroy();

   }


   bool font::create(::draw2d::graphics * pgraphics, ::i8 iCreate)
   {

      if (m_pfont != nullptr)
      {

         return true;

      }

      i32 iStyle = 0;

      if(m_iFontWeight >= 600)
      {
         iStyle |= (i32) Gdiplus::FontStyleBold;
      }

      if(m_bItalic)
      {
         iStyle |= (i32) Gdiplus::FontStyleItalic;
      }

      if(m_bUnderline)
      {
         iStyle |= (i32) Gdiplus::FontStyleUnderline;
      }

      if(m_bStrikeout)
      {
         iStyle |= (i32) Gdiplus::FontStyleStrikeout;
      }

      Gdiplus::Unit unit;

      switch(m_eunitFontSize)
      {
      case ::draw2d::e_unit_pixel:
         unit = Gdiplus::UnitPixel;
         break;
      case ::draw2d::e_unit_point:
         unit = Gdiplus::UnitPoint;
         break;
      default:
         unit = Gdiplus::UnitPoint;
         break;
      };

      //retry_single_lock slGdiplus(psystem->s_mutexGdiplus, ::duration(1), ::duration(1));

      /*if (m_strFontFamilyName.begins_ci("matter://"))
      {

         ::acme::del(m_pfontcollection);

         m_pfontcollection = memory_new FontCollection();

         m_pfontcollection->AddFontFile(pcontext->m_papexcontext->dir().matter(m_strFontFamilyName));

      }*/

      ////...
      //CString szFontFile = szExePath + L"SkiCargo.ttf";

      //
      //Here is how to use the font we have just added to the PrivateFontCollection object, m_fontcollection.

      //   Hide   Copy Code
      //   // When painting the text
      //   FontFamily pfontFamily;
      //int nNumFound = 0;
      //m_fontcollection.GetFamilies(1, &pfontFamily, &nNumFound);

      //if (nNumFound > 0)
      //{
      //   Font font(&pfontFamily, 28, FontStyleRegular, UnitPixel);

      //   StringFormat strformat;
      //   wchar_t buf[] = L"The quick brown fox jumps over the lazy dog!";
      //   graphics.DrawString(buf, wcslen(buf), &font,
      //                       PointF(10.0f, 10.0f), &strformat, &brush);
      //}

      m_pfont = normal_new Gdiplus::Font(
      utf8_to_unicode(m_strFontFamilyName),
      (Gdiplus::REAL) m_dFontSize,
      iStyle,
      unit);

      m_osdata[0] = m_pfont;

      return true;

   }


   //void * font::get_os_data() const
   //{

   //   defer_update(pgraphics);

   //   return m_pfont;

   //}


   ::enum_character_set font::calculate_character_set(::draw2d::graphics * pgraphics)
   {

      //Gdiplus::Font * pfont = (Gdiplus::Font *) get_os_data();

      //LOGFONTA lf;

      //__zero(lf);

      //pfont->GetLogFontA((::Gdiplus::Graphics *) pgraphics->get_os_data(), &lf);

      //return ::draw2d::wingdi_get_cs(lf.lfCharSet);

      return ::write_text::font::calculate_character_set(pgraphics);

   }


} // namespace draw2d_gdiplus
