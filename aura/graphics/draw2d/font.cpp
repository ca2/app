#include "framework.h"


namespace draw2d
{


   font_enum_item::font_enum_item()
   {
   }


   font_enum_item::font_enum_item(string strName) :
      m_strName(strName)
   {

      m_mapFileName[0] = strName;

#ifdef WINDOWS

      m_wstrName = strName;

#endif

   }

#ifdef WINDOWS

   font_enum_item::font_enum_item(const widechar * pwideszName) :
      m_wstrName(pwideszName)
   {

      string strName = m_wstrName;

      m_mapFileName[0] = strName;
      m_strName = strName;

   }

#endif

   font_enum_item::font_enum_item(string strFile, string strName) :
      m_strName(strName)
   {

      m_mapFileName[0] = strFile;

#ifdef WINDOWS

      m_wstrName = strName;

#endif

   }


   font_enum_item::~font_enum_item()
   {

   }


   font::font()
   {

      m_strFontFamilyName     = os_font_name(e_font_serif);
      m_dFontSize             = 17.0;
      m_dFontWidth            = 1.0;
      m_eunitFontSize         = ::draw2d::unit_point;
      m_iFontWeight           = 400;
      m_bItalic               = false;
      m_bUnderline            = false;
      m_bStrikeout            = false;
      m_etextrenderinghint    = text_rendering_hint_undefined;
      m_echarset              = char_set_none;

   }


   font::font(const font & font)
   {

      operator = (font);

   }


   font::~font()
   {

   }


   void font::dump(dump_context & dumpcontext) const
   {

      UNREFERENCED_PARAMETER(dumpcontext);

      ::exception::throw_interface_only();

   }


   bool font::create_pixel_font(const char * pszFacename, double dSize, i32 iWeight, bool bItalic, bool bUnderline, bool bStrikeOut, double dWidth)
   {

#ifdef WINDOWS

      if(ansi_compare_ci(pszFacename, os_font_name(e_font_sans)) == 0)

      {

         m_strFontFamilyName = os_font_name(e_font_sans);

      }
      else
      {

         m_strFontFamilyName     = pszFacename;


      }

#else

      m_strFontFamilyName     = pszFacename;


#endif

      m_dFontSize             = dSize;
      m_dFontWidth            = 1.0;
      m_eunitFontSize         = ::draw2d::unit_pixel;
      m_iFontWeight           = iWeight;
      m_bItalic               = bItalic;
      m_bUnderline            = bUnderline;
      m_bStrikeout            = bStrikeOut;
      set_modified();

      return true;

   }


   bool font::create_point_font(const char * pszFacename, double dSize, i32 iWeight, bool bItalic, bool bUnderline, bool bStrikeOut, double dWidth)

   {

      m_strFontFamilyName     = pszFacename;

      if (m_dFontSize == 0.0)
      {

         dSize = 12.0;

      }

      if (dSize != 0.0)
      {
#ifdef MACOS
         m_dFontSize = dSize * 1.2;
#elif defined(ANDROID)
         m_dFontSize = dSize * 1.6;
#else
         m_dFontSize = dSize;
#endif
      }
      m_dFontWidth            = 1.0;
      m_eunitFontSize         = ::draw2d::unit_point;
      m_iFontWeight           = iWeight;
      m_bItalic               = bItalic;
      m_bUnderline            = bUnderline;
      m_bStrikeout            = bStrikeOut;
      set_modified();

      return true;

   }


   font & font::operator = (const font & fontSrc)
   {

      if(this != &fontSrc)
      {

         m_strFontFamilyName     = fontSrc.m_strFontFamilyName;
         m_dFontSize             = fontSrc.m_dFontSize;
         m_dFontWidth            = fontSrc.m_dFontWidth;
         m_eunitFontSize         = fontSrc.m_eunitFontSize;
         m_iFontWeight           = fontSrc.m_iFontWeight;
         m_bItalic               = fontSrc.m_bItalic;
         m_bUnderline            = fontSrc.m_bUnderline;
         m_bStrikeout            = fontSrc.m_bStrikeout;
         m_echarseta             = fontSrc.m_echarseta;
         m_echarset              = fontSrc.m_echarset;
         set_modified();

      }

      return *this;

   }


   void font::set_family_name(const char * pszFamilyName)
   {

      m_strFontFamilyName  = pszFamilyName;
      
      set_modified();

   }


   void font::set_size(double dSize, enum_unit eunit)
   {

      m_dFontSize       = dSize;
      m_eunitFontSize   = eunit;
      set_modified();

   }


   void font::set_bold(bool bBold)
   {

      if(bBold)
      {

         m_iFontWeight  = e_font_weight_bold;

      }
      else
      {

         m_iFontWeight  = e_font_weight_normal;

      }

      set_modified();

   }


   void font::set_italic(bool bItalic)
   {

      m_bItalic      = bItalic;
      set_modified();

   }


   void font::set_underline(bool bUnderline)
   {

      m_bUnderline   = bUnderline;
      set_modified();

   }


   void font::set_strikeout(bool bStrikeout)
   {

      m_bStrikeout   = bStrikeout;
      set_modified();

   }


   ::e_char_set font::get_char_set(::draw2d::graphics * pgraphics)
   {

      if (m_echarset == char_set_none)
      {

         m_echarset = calc_char_set(pgraphics);

      }

      return m_echarset;

   }


   ::e_char_set font::calc_char_set(graphics * pgraphics)
   {

      if (m_echarseta.get_count() == 1)
      {

         return m_echarseta[0];

      }

      return char_set_default;

   }


   string font::get_sample_text(e_char_set echarset)
   {

      if (echarset == char_set_chinesebig5)
      {

         return unitext("示例文本");

      }
      else if (echarset == char_set_gb2312)
      {

         return unitext("示例文本");

      }
      else if (echarset == char_set_shiftjis)
      {

         return unitext("サンプルテキスト");

      }
      else if (echarset == char_set_hebrew)
      {

         return unitext("טקסט לדוגמה");

      }
      else if (echarset == char_set_arabic)
      {

         return unitext("نص بسيط");

      }
      else if (echarset == char_set_greek)
      {

         return unitext("Δείγμα κειμένου");

      }
      else if (echarset == char_set_turkish)
      {

         return unitext("Örnek yazı");

      }
      else if (echarset == char_set_vietnamese)
      {

         return unitext("văn bản mẫu");

      }
      else if (echarset == char_set_thai)
      {

         return unitext("ตัวอย่างข้อความ");

      }
      else if (echarset == char_set_easteurope)
      {

         return unitext("Sample Text");

      }
      else if (echarset == char_set_russian)
      {

         return unitext("Образец текста");

      }
      else if (echarset == char_set_johab)
      {

         return unitext("샘플 텍스트");

      }
      else if (echarset == char_set_hangul)
      {

         return unitext("샘플 텍스트");

      }

      return "";

   }


   string font::get_sample_text(::draw2d::graphics * pgraphics)
   {

      auto ecs = get_char_set(pgraphics);

      string str = get_sample_text(ecs);

      if (str.has_char())
      {

         return str;

      }

      return m_strFontFamilyName;

   }


//#ifdef WINDOWS
//
//
//   bool font::GetLogFont(LOGFONTW * pfontw)
//   {
//
//      return false;
//
//   }
//
//
//#endif // WINDOWS



   double font::get_pixel_font_height(::draw2d::graphics * pgraphics)
   {

      if (m_eunitFontSize == unit_point)
      {

         return m_dFontSize * pgraphics->get_dpiy() / 72.0;

      }

      return m_dFontSize;

   }


   //void font::clear()
   //{

   //   m_glyphset.remove_all();

   //}


//   ::draw2d::font * font::GetFont()
//   {
//
//      return m_pfont;
//
//   }
//
//
//   void font::embossed_text_out(::draw2d::graphics * pgraphics, const ::rectangle_i32 & rectangle, double dRateX, double dHeight, string & str)
//   {
//
//
//      System.draw2d().api().embossed_text_out(pgraphics, rectangle_i32, dRateX, dHeight, str);
//
//      return;
//
//
//
//      //      SetDC(pgraphics);
//      //      SelectFont();
//      //
//      //      ::rectangle_i32 rectOffset(rectangle);
//      //      const ::point_i32 & pointOffset(rectOffset.top_left());
//      //
//      //      glyph * pglyph;

//      //      strsize iSize = str.get_length();
//      //      for(i32 i = 0; i < iSize; i++)
//      //      {
//      //         pglyph = GetGlyph(str[i]);

//      //         if(pglyph != nullptr)

//      //         {
//      //            pointOffset.x = ::i32(pgraphics->GetTextExtent(str.Left(i)).cx);
//      //            pglyph->DrawGlyph(

//      //               pgraphics,
//      //               true,
//      //               (float) dRateX,
//      //               &pointOffset);
//      //         }
//      //      }
//      //
//      //
//      //
//      //      UnselectFont();
//      //      ClearDC();
//
//      /*   SetDC(pgraphics);
//         SelectFont();
//
//         pgraphics->text_out(x, y, str);
//         pgraphics->BeginPath();
//         pgraphics->text_out(x, y, str);
//         pgraphics->EndPath();
//         pgraphics->StrokePath();
//
//         UnselectFont();
//         ClearDC();*/
//
//   }
//
//   void font::embossed_text_out(::draw2d::graphics * pgraphics, const ::rectangle_i32 & rectangle, double dRateX, double dHeight, string & str, LPINT piCharsPositions, i32 iCharsPositions, i32 iOffset)

//   {
//
//      System.draw2d().api().embossed_text_out(pgraphics, rectangle_i32, dRateX, dHeight, str, piCharsPositions, iCharsPositions, iOffset);

//
//      return;
//
//
//
//      //      SetDC(pgraphics);
//      //      SelectFont();
//      //
//      //      const ::rectangle_i32 rectOffset(rectangle);
//      //      ::point_i32 pointOffset;
//      //
//      //
//      //      glyph * pglyph;

//      //      strsize iSize = str.get_length();
//      //      for(strsize i = 0; i < iSize; i++)
//      //      {
//      //         pglyph = GetGlyph(str[i]);

//      //         if(pglyph != nullptr)

//      //         {
//      //            pointOffset = rectOffset.top_left();
//      //            pointOffset.x += (long) ((piCharsPositions[iOffset + i] - lpiCharsPositions[iOffset]) * dRateX);

//      //            pglyph->DrawGlyph(

//      //               pgraphics,
//      //               true,
//      //               (float) dRateX,
//      //               &pointOffset);
//      //         }
//      //      }
//
//
//      /*   draw2d::api::embossed_text_out(
//            pgraphics,
//            pcrect,

//            floatRateX,
//            floatHeight,
//            str,
//            piCharsPositions,

//            iCharsPositions,
//            iOffset);*/
//
//      //      UnselectFont();
//      //      ClearDC();
//      /*   SetDC(pgraphics);
//         SelectFont();
//
//         rectangle_i32 clipRect;
//
//         i32 iOldMapMode = pgraphics->GetMapMode();
//         pgraphics->SetMapMode(MM_TEXT);
//         pgraphics->text_out(x, y, str);
//         pgraphics->BeginPath();
//         pgraphics->text_out(x, y, str);
//         pgraphics->EndPath();
//         pgraphics->StrokePath();
//
//         pgraphics->SetMapMode(iOldMapMode);
//         UnselectFont();
//         ClearDC();*/
//   }
//
//   void font::simple_text_out(::draw2d::graphics * pgraphics, i32 x, i32 y, string & str, LPINT piCharsPositions, i32 iCharsPositions)

//
//   {
//
//
//      UNREFERENCED_PARAMETER(piCharsPositions);

//      UNREFERENCED_PARAMETER(iCharsPositions);
//      SetDC(pgraphics);
//      SelectFont();
//
//      rectangle_i32 clipRect;
//
//      pgraphics->text_out(x, y, str);
//
//      UnselectFont();
//
//      ClearDC();
//
//   }
//
//
//   bool font::AddGlyph(WCHAR wchar)
//   {
//
//      return AddGlyph((::u32)wchar);
//
//   }
//
//
//   bool font::AddGlyph(char tch)
//   {
//
//      return AddGlyph((::u32)tch);
//
//   }
//
//
//   bool font::AddGlyph(::u32 user)
//   {
//
//      //   single_lock sl(&m_mutex);
//      //   sl.lock(U32_INFINITE_TIMEOUT);
//
//      return true;
//
//#ifdef WINDOWS_DESKTOP
//
//      if (m_glyphset.find_first(user) >= 0)
//         return true;
//
//      glyph glyph;
//      glyph.m_ui = user;
//      //m_glyphArray.add(pGlyph);
//      MAT2 mat2;
//      mat2.eM11.value = 1;
//      mat2.eM11.fract = 0;
//      mat2.eM12.value = 0;
//      mat2.eM12.fract = 0;
//      mat2.eM21.value = 0;
//      mat2.eM21.fract = 0;
//      mat2.eM22.value = 1;
//      mat2.eM22.fract = 0;
//      GLYPHMETRICS gm;
//
//      u32 cbBuffer = m_pDC->GetGlyphOutline(user, GGO_NATIVE, &glyph.m_gm, 0, nullptr, &mat2);
//
//      if (cbBuffer == GDI_ERROR)
//         return FALSE;
//
//      if (cbBuffer == 0)
//      {
//
//         m_glyphset.add(glyph);
//
//         return true;
//
//      }
//
//      LPTTPOLYGONHEADER pPH = (LPTTPOLYGONHEADER)malloc(cbBuffer);

//
//      if (pPH == nullptr)

//         return FALSE;
//
//      m_pDC->GetGlyphOutline(user, GGO_NATIVE, &gm, cbBuffer, pPH, &mat2);

//
//      glyph.Initialize(pPH, cbBuffer, m_iFontHiHeight);

//
//      free(pPH);

//
//      m_glyphset.add(glyph);
//
//      return true;
//
//#endif
//
//   }
//
//   void font::SetDC(::draw2d::graphics * pgraphics)
//   {
//      ASSERT(m_pDC == nullptr);
//      ASSERT(pgraphics != nullptr);
//      m_pDC = pgraphics;
//   }
//
//   void font::SelectFont()
//   {
//      m_pfontOld = m_pDC->set(m_pfont);
//   }
//
//   void font::ClearDC()
//   {
//      m_pDC = nullptr;
//   }
//
//   void font::UnselectFont()
//   {
//      ASSERT(m_pfontOld != nullptr);
//      m_pDC->set(m_pfontOld);
//      m_pfontOld = nullptr;
//   }
//
//
//
//   glyph * font::GetGlyph(char ch)
//   {
//      return GetGlyph((::u32)ch);
//   }
//
//   glyph * font::GetGlyph(WCHAR wch)
//   {
//      return GetGlyph((::u32)wch);
//   }
//
//   glyph * font::GetGlyph(::u32 user)
//   {
//      return m_glyphset.GetGlyph(user);
//   }
//
//
//   void font::AddXFGlyphs(string2a  & str2aTokens)
//   {
//      char           ch;
//      string         str;
//      i32        i, j, k;
//      bool           forceInsertion = FALSE;
//
//      SelectFont();
//      for (i = 0; i < str2aTokens.get_size(); i++)
//      {
//         string_array & straTokens = str2aTokens[i];
//         for (j = 0; j < straTokens.get_size(); j++)
//         {
//            str = straTokens[j];
//            for (k = 0; k < str.get_length(); k++)
//            {
//               ch = str.operator[](k);
//               if (forceInsertion)
//               {
//                  forceInsertion = FALSE;
//                  AddGlyph(ch);
//               }
//               else if (ch == '\\')
//               {
//                  forceInsertion = true;
//               }
//               else if (ch == '^')
//               {
//                  AddGlyph(' ');
//               }
//               else if (ch == '/')
//               {
//               }
//               else if (ch == '%')
//               {
//               }
//               else if (ch == '<')
//               {
//               }
//               else if (ch == '>')
//               {
//               }
//               else
//               {
//                  AddGlyph(ch);
//               }
//            }
//         }
//      }
//      UnselectFont();
//   }
//
//   void font::AddGlyphs(const char * pStr)

//   {
//      string str(pStr);

//      SelectFont();
//      for (i32 i = 0; i < str.get_length(); i++)
//      {
//         AddGlyph(str[i]);
//      }
//
//   }
//
//   void font::TextOutEx(
//   ::draw2d::graphics * pgraphics,
//   const rectangle_i32 &               rectangle_i32,
//   double               dRateX,
//   double               dHeight,
//   string                 &str,
//   LPINT                piCharsPositions,

//   i32                     iCharsPositions,
//   i32                  iOffset,
//   i32                     iEffect)
//   {
//
//      switch (iEffect)
//      {
//      case EffectSimple:
//         simple_text_out(pgraphics, rectangle.left, rectangle.top, str, piCharsPositions, iCharsPositions);

//         break;
//      case EffectEmbossed:
//         embossed_text_out(
//         pgraphics,
//         rectangle_i32,
//         dRateX,
//         dHeight,
//         str,
//         piCharsPositions,

//         iCharsPositions,
//         iOffset);
//         break;
//      default:
//         ASSERT(FALSE);
//
//      }
//
//   }
//
//
//   i32 font::GetMegaHeight()
//   {
//
//      return m_tm.tmHeight +
//             m_tm.tmInternalLeading +
//             m_tm.tmExternalLeading;
//
//   }
//
//
//
//   void font::OnSetFont()
//   {
//      OnUpdateFont();
//   }
//
//   void font::OnUpdateFont()
//   {
//
//      ::draw2d::graphics_pointer spgraphics(e_create);
//
//      spgraphics->CreateCompatibleDC(nullptr);
//
//      ::draw2d::font * pFontOld = spgraphics->set(m_pfont);
//
//      spgraphics->get_text_metrics(&m_tm);
//
//      m_iFontHiHeight = m_tm.tmAscent + m_tm.tmDescent;
//
//      spgraphics->set(pFontOld);
//      spgraphics->DeleteDC();
//
//   }

void font::destroy()
{

   for (auto& text : m_mapText.values())
   {

      text.m_bSize = false;

   }

   }

   bool font::get_text_metric(::draw2d::graphics * pgraphics, text_metric & tm)
   {
      
      if(is_modified())
      {
         
         m_bTextMetric = false;
         
         defer_update(pgraphics, 0);
         
      }
      
      if(!m_bTextMetric)
      {
         
         m_bTextMetric = _get_text_metric(pgraphics, m_textmetric);

      }
      
      if(!m_bTextMetric)
      {
         
         return false;
         
      }
      
      tm = m_textmetric;
         
      return true;
      
   }
   
   double font::get_ascent(::draw2d::graphics * pgraphics)
   {
      
      text_metric tm;
      
      if(!get_text_metric(pgraphics, tm))
      {
       
         return false;
         
      }
      
      return tm.m_dAscent;
      
   }

   
   double font::get_height(::draw2d::graphics * pgraphics)
   {
      
      text_metric tm;
      
      if(!get_text_metric(pgraphics, tm))
      {
         
         return false;
         
      }
      
      return tm.m_dHeight;
      
   }
   
   
   double font::get_leading(::draw2d::graphics * pgraphics)
   {
      
      text_metric tm;
      
      if(!get_text_metric(pgraphics, tm))
      {
         
         return false;
         
      }
      
      return tm.m_dInternalLeading + tm.m_dExternalLeading;
      
   }
   
   
   double font::get_descent(::draw2d::graphics * pgraphics)
   {
      
      text_metric tm;
      
      if(!get_text_metric(pgraphics, tm))
      {
         
         return false;
         
      }
      
      return tm.m_dDescent;
         
   }
   
   
   bool font::_get_text_metric(::draw2d::graphics * pgraphics, text_metric & tm)
   {

      if (::is_null(pgraphics))
      {

         return false;

      }
   
      pgraphics->set(this);
   
      return pgraphics->get_text_metrics(&tm);
      
   }
   

} // namespace draw2d


//#if 0
//
//
//bool CLASS_DECL_AURA TextOutU(hdc hdc, i32 x, i32 y, const char * pString, i32 ca)
//
//{
//
//   //#ifdef WINDOWS_DESKTOP
//   //
//   //   if (pString == nullptr)
//   //
//   //   {
//   //      return ::TextOutW(hdc, x, y, nullptr, ca) != FALSE;
//   //
//   //   }
//   //
//   //   wstring wstr = ::str::international::utf8_to_unicode(pString, ca);
//   //
//   //
//   //   bool bRet = ::TextOutW(hdc, x, y, wstr, (i32)wstr.get_length()) != FALSE;
//   //
//   //   return bRet;
//   //
//   //#else
//
//   __throw(todo());
//
//   /*
//
//      if(pString == nullptr)
//
//      {
//         return ::text_out(hdc, x, y, nullptr, 0) != FALSE;
//      }
//
//      return ::text_out(hdc, x, y, wstr, (i32) wstr.get_length()) != FALSE;
//   */
//
//   //#endif
//
//}
//
//
//CLASS_DECL_AURA bool GetTextExtentPoint32U(HDC hdc, const char * pString, i32 ca, LPSIZE32 psizl)
//
//{
//   //
//   //#ifdef WINDOWS_DESKTOP
//   //
//   //   if (pString == nullptr)
//   //
//   //   {
//   //
//   //      return ::GetTextExtentPoint32W(hdc, nullptr, ca, psizl) != FALSE;
//   //
//   //   }
//   //
//   //   wstring wstr = ::str::international::utf8_to_unicode(pString, ca);
//   //
//   //
//   //   bool bRet = ::GetTextExtentPoint32W(hdc, wstr, (i32)wstr.get_length(), psizl) != FALSE;
//   //
//   //   return bRet;
//   //
//   //#else
//
//   __throw(todo());
//
//   //#endif
//
//}
//
//
//CLASS_DECL_AURA i32  DrawTextU(HDC hdc, const char * pchText, i32 cchText, RECTANGLE_I32 * prectangle, ::u32 format)
//
//{
//
//   //#ifdef WINDOWS_DESKTOP
//   //
//   //   if (pchText == nullptr)
//   //
//   //   {
//   //
//   //      return ::DrawTextW(hdc, nullptr, cchText, prectangle, format);
//   //
//   //
//   //   }
//   //
//   //   wstring wstr = ::str::international::utf8_to_unicode(pchText, cchText);
//   //
//   //
//   //   bool bRet = ::DrawTextW(hdc, wstr, (i32)wcslen(wstr), prectangle, format) != FALSE;
//   //
//   //
//   //   return bRet;
//   //
//   //#else
//
//   __throw(todo());
//
//   //#endif
//
//} // namespace draw2d
//
//
//#endif
