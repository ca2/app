#include "framework.h"
#include "font.h"
#include "fonts.h"
#include "internal_font.h"
#include "acme/exception/bad_unit_exception.h"
#include "acme/exception/interface_only.h"
#include "acme/platform/application.h"
#include "acme/platform/node.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/draw2d/draw2d.h"


namespace write_text
{


   font::font() :
      m_fontsize(12_pt)
   {

      m_bCacheLayout = true;
      m_dFontWidth = 1.0;
      m_fontweight = e_font_weight_normal;
      m_bItalic = false;
      m_bUnderline = false;
      m_bStrikeout = false;
      //m_erendering = e_rendering_undefined;
      m_echaracterset = e_character_set_none;

   }


   font::font(const font & font)
   {

      operator = (font);

   }


   font::~font()
   {

   }


//   void font::dump(dump_context & dumpcontext) const
//   {
//
//      __UNREFERENCED_PARAMETER(dumpcontext);
//
//      throw ::interface_only();
//
//   }


   void font::create_text_metrics(::draw2d::graphics * pgraphics)
   {


   }


   bool font::create_font(
      const font_family_pointer & pfontfamily, 
      const font_size & fontsize, 
      const font_weight & fontweight,
      bool bItalic, 
      bool bUnderline, 
      bool bStrikeOut, 
      double dWidth)
   {

      m_pfontfamily = pfontfamily;
      m_fontsize = fontsize;
      m_fontweight = fontweight;
      m_dFontWidth = 1.0;
      m_bItalic = bItalic;
      m_bUnderline = bUnderline;
      m_bStrikeout = bStrikeOut;

      set_modified();

      return true;

   }


//   bool font::create_point_font(const ::scoped_string & scopedstrFacename, double dSize, int iWeight, bool bItalic, bool bUnderline, bool bStrikeOut, double dWidth)
//   {
//
//      m_strFontFamilyName = pszFacename;
//
//      if (m_dFontSize == 0.0)
//      {
//
//         dSize = 12.0;
//
//      }
//
//      if (dSize != 0.0)
//      {
//#ifdef MACOS
//         m_dFontSize = dSize * 1.2;
//#elif defined(__ANDROID__)
//         m_dFontSize = dSize * 1.6;
//#else
//         m_dFontSize = dSize;
//#endif
//      }
//      m_dFontWidth = 1.0;
//      m_eunitFontSize = ::draw2d::e_unit_point;
//      m_iFontWeight = iWeight;
//      m_bItalic = bItalic;
//      m_bUnderline = bUnderline;
//      m_bStrikeout = bStrikeOut;
//      set_modified();
//
//      return true;
//
//   }


   font & font::operator = (const font & font)
   {

      if (this != &font)
      {

         m_pfontfamily = font.m_pfontfamily->clone();
         m_path = font.m_path;
         m_fontsize = font.m_fontsize;
         m_dFontWidth = font.m_dFontWidth;
         //m_eunitFontSize = font.m_eunitFontSize;
         m_fontweight = font.m_fontweight;
         m_bItalic = font.m_bItalic;
         m_bUnderline = font.m_bUnderline;
         m_bStrikeout = font.m_bStrikeout;
         m_echaracterseta = font.m_echaracterseta;
         m_echaracterset = font.m_echaracterset;

         set_modified();

      }

      return *this;

   }


   void font::set_family_name(const ::scoped_string & scopedstrFamilyName)
   {

      m_pfontfamily = font_family_pointer(scopedstrFamilyName);

      set_modified();

   }


   void font::set_size(const font_size & fontsize)
   {

      m_fontsize = fontsize;
      //m_eunitFontSize = eunit;
      set_modified();

   }


   void font::set_bold(bool bBold)
   {

      if (bBold)
      {

         m_fontweight = e_font_weight_bold;

      }
      else
      {

         m_fontweight = e_font_weight_normal;

      }

      set_modified();

   }


   void font::set_italic(bool bItalic)
   {

      m_bItalic = bItalic;
      set_modified();

   }


   void font::set_underline(bool bUnderline)
   {

      m_bUnderline = bUnderline;
      set_modified();

   }


   void font::set_strikeout(bool bStrikeout)
   {

      m_bStrikeout = bStrikeout;
      set_modified();

   }


   ::enum_character_set font::get_character_set(::draw2d::graphics * pgraphics)
   {

      if (m_echaracterset == e_character_set_none)
      {

         m_echaracterset = calculate_character_set(pgraphics);

      }

      return m_echaracterset;

   }


   ::enum_character_set font::calculate_character_set(::draw2d::graphics * pgraphics)
   {

      if (m_echaracterseta.get_count() == 1)
      {

         return m_echaracterseta[0];

      }

      return e_character_set_default;

   }


   string font::get_sample_text(::draw2d::graphics * pgraphics)
   {

      auto echaracterset = get_character_set(pgraphics);

      string strSampleText = node()->get_character_set_default_sample_text(echaracterset);

      if (strSampleText.has_character())
      {

         return strSampleText;

      }

      return m_pfontfamily->family_name(pgraphics);

   }


   string font::get_font_descriptor_face()
   {
      
      return system()->draw2d()->write_text()->get_font_descriptor_face(m_fontdescriptor);
      
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

      if (m_fontsize.eunit() == ::e_unit_point)
      {

         return m_fontsize.as_double() * pgraphics->get_dpiy() / 72.0;

      }
      else if (m_fontsize.eunit() == ::e_unit_pixel)
      {

         return m_fontsize.as_double();

      }
      else
      {

         throw ::bad_unit_exception< enum_unit >(m_fontsize.eunit());

      }

   }


   //void font::clear()
   //{

   //   m_glyphset.erase_all();

   //}


//   ::draw2d::font * font::GetFont()
//   {
//
//      return m_pfont;
//
//   }
//
//
//   void font::embossed_text_out(::draw2d::graphics * pgraphics, const ::double_rectangle & rectangle, double dRateX, double dHeight, string & str)
//   {
//
//
//      psystem->draw2d().api().embossed_text_out(pgraphics, rectangle, dRateX, dHeight, str);
//
//      return;
//
//
//
//      //      SetDC(pgraphics);
//      //      SelectFont();
//      //
//      //      ::double_rectangle rectangleOffset(rectangle);
//      //      const ::int_point & pointOffset(rectangleOffset.top_left());
//      //
//      //      glyph * pglyph;

//      //      character_count iSize = str.length();
//      //      for(int i = 0; i < iSize; i++)
//      //      {
//      //         pglyph = GetGlyph(str[i]);

//      //         if(pglyph != nullptr)

//      //         {
//      //            pointOffset.x() = int(pgraphics->get_text_extent(str.left(i)).cx());
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
//   void font::embossed_text_out(::draw2d::graphics * pgraphics, const ::double_rectangle & rectangle, double dRateX, double dHeight, string & str, LPINT piCharsPositions, int iCharsPositions, int iOffset)

//   {
//
//      psystem->draw2d().api().embossed_text_out(pgraphics, rectangle, dRateX, dHeight, str, piCharsPositions, iCharsPositions, iOffset);

//
//      return;
//
//
//
//      //      SetDC(pgraphics);
//      //      SelectFont();
//      //
//      //      const ::double_rectangle rectangleOffset(rectangle);
//      //      ::int_point pointOffset;
//      //
//      //
//      //      glyph * pglyph;

//      //      character_count iSize = str.length();
//      //      for(character_count i = 0; i < iSize; i++)
//      //      {
//      //         pglyph = GetGlyph(str[i]);

//      //         if(pglyph != nullptr)

//      //         {
//      //            pointOffset = rectangleOffset.top_left();
//      //            pointOffset.x() += (long) ((piCharsPositions[iOffset + i] - lpiCharsPositions[iOffset]) * dRateX);

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
//         rectangle clipRect;
//
//         int iOldMapMode = pgraphics->GetMapMode();
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
//   void font::simple_text_out(::draw2d::graphics * pgraphics, int x, int y, string & str, LPINT piCharsPositions, int iCharsPositions)

//
//   {
//
//
//      __UNREFERENCED_PARAMETER(piCharsPositions);

//      __UNREFERENCED_PARAMETER(iCharsPositions);
//      SetDC(pgraphics);
//      SelectFont();
//
//      rectangle clipRect;
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
//      return AddGlyph((unsigned int)wchar);
//
//   }
//
//
//   bool font::AddGlyph(char tch)
//   {
//
//      return AddGlyph((unsigned int)tch);
//
//   }
//
//
//   bool font::AddGlyph(unsigned int user)
//   {
//
//      //   single_lock synchronouslock(m_pmutex);
//      //   synchronouslock.lock(U32_INFINITE_TIMEOUT);
//
//      return TRUE;
//
//#ifdef WINDOWS_DESKTOP
//
//      if (m_glyphset.find_first(user) >= 0)
//         return TRUE;
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
//      unsigned int cbBuffer = m_pDC->GetGlyphOutline(user, GGO_NATIVE, &glyph.m_gm, 0, nullptr, &mat2);
//
//      if (cbBuffer == GDI_ERROR)
//         return FALSE;
//
//      if (cbBuffer == 0)
//      {
//
//         m_glyphset.add(glyph);
//
//         return TRUE;
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
//      return TRUE;
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
//      return GetGlyph((unsigned int)ch);
//   }
//
//   glyph * font::GetGlyph(WCHAR wch)
//   {
//      return GetGlyph((unsigned int)wch);
//   }
//
//   glyph * font::GetGlyph(unsigned int user)
//   {
//      return m_glyphset.GetGlyph(user);
//   }
//
//
//   void font::AddXFGlyphs(string_array_array  & straaTokens)
//   {
//      char           ch;
//      string         str;
//      int        i, j, k;
//      bool           forceInsertion = FALSE;
//
//      SelectFont();
//      for (i = 0; i < straaTokens.get_size(); i++)
//      {
//         string_array & straTokens = straaTokens[i];
//         for (j = 0; j < straTokens.get_size(); j++)
//         {
//            str = straTokens[j];
//            for (k = 0; k < str.length(); k++)
//            {
//               ch = str.operator[](k);
//               if (forceInsertion)
//               {
//                  forceInsertion = FALSE;
//                  AddGlyph(ch);
//               }
//               else if (ch == '\\')
//               {
//                  forceInsertion = TRUE;
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
//   void font::AddGlyphs(const ::scoped_string & scopedstrStr)

//   {
//      string str(pStr);

//      SelectFont();
//      for (int i = 0; i < str.length(); i++)
//      {
//         AddGlyph(str[i]);
//      }
//
//   }
//
//   void font::TextOutEx(
//   ::draw2d::graphics * pgraphics,
//   const rectangle &               rectangle,
//   double               dRateX,
//   double               dHeight,
//   string                 &str,
//   LPINT                piCharsPositions,

//   int                     iCharsPositions,
//   int                  iOffset,
//   int                     iEffect)
//   {
//
//      switch (iEffect)
//      {
//      case EffectSimple:
//         simple_text_out(pgraphics, rectangle.left(), rectangle.top(), str, piCharsPositions, iCharsPositions);

//         break;
//      case EffectEmbossed:
//         embossed_text_out(
//         pgraphics,
//         rectangle,
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
//   int font::GetMegaHeight()
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


   ::string font::family_name()
   {
      
      if(!m_pfontfamily)
      {
         
         return {};
         
      }
      
      return m_pfontfamily->family_name(this);
      
   }


   bool font::defer_load_internal_font(::draw2d::graphics * pgraphics)
   {

      if (m_path.has_character())
      {

         if (m_pfontfamily && m_pfontfamily->m_strBranch.has_character())
         {

            write_text()->fonts()->enumeration(m_pfontfamily->m_strBranch)->defer_download_font(m_path);

         }

         auto pinternalfont = write_text()->internal_font_from_file(pgraphics->m_papplication, m_path);

         if (pinternalfont)
         {

            on_create_internal_font(pgraphics, pinternalfont);

         }

         return true;

      }

      return false;

   }


   void font::on_create_internal_font(::draw2d::graphics * pgraphics, ::write_text::internal_font * pinternalfont)
   {

      pinternalfont->on_create_font(pgraphics, this);

   }


   void font::destroy()
   {

   }


   void font::get_text_metric(::draw2d::graphics * pgraphics, text_metric & tm)
   {

      if (!has_text_metric())
      {

         _get_text_metric(pgraphics, m_textmetric2);

         set_has_text_metric();

      }

      tm = *get_text_metric_struct();

   }


   double font::get_ascent(::draw2d::graphics * pgraphics)
   {

      text_metric tm;

      get_text_metric(pgraphics, tm);

      return tm.m_dAscent;

   }


   double font::get_height(::draw2d::graphics * pgraphics)
   {

      text_metric tm;

      get_text_metric(pgraphics, tm);

      return tm.m_dHeight;

   }


   double font::get_leading(::draw2d::graphics * pgraphics)
   {

      text_metric tm;

      get_text_metric(pgraphics, tm);

      return tm.m_dInternalLeading + tm.m_dExternalLeading;

   }


   double font::get_descent(::draw2d::graphics * pgraphics)
   {

      text_metric tm;

      get_text_metric(pgraphics, tm);

      return tm.m_dDescent;

   }


   void font::_get_text_metric(::draw2d::graphics * pgraphics, text_metric & tm)
   {

      if (::is_null(pgraphics))
      {

         throw ::exception(error_null_pointer);

      }

      pgraphics->set(this);

      pgraphics->get_text_metrics(&tm);

   }


} // namespace write_text


//bool CLASS_DECL_AURA TextOutU(HDC hdc, int x, int y, const ::scoped_string & scopedstrString, int ca)
//
//{
//
//#ifdef WINDOWS_DESKTOP
//
//   if (pString == nullptr)
//
//   {
//      return ::TextOutW(hdc, x, y, nullptr, ca) != FALSE;
//
//   }
//
//   wstring wstr = utf8_to_unicode(pString, ca);
//
//
//   bool bRet = ::TextOutW(hdc, x, y, wstr, (int)wstr.get_length()) != FALSE;
//
//   return bRet;
//
//#else
//
//   throw ::exception(todo);
//
//   /*
//
//      if(pString == nullptr)
//
//      {
//         return ::text_out(hdc, x, y, nullptr, 0) != FALSE;
//      }
//
//      return ::text_out(hdc, x, y, wstr, (int) wstr.get_length()) != FALSE;
//   */
//
//#endif
//
//}
//
//
//CLASS_DECL_AURA bool GetTextExtentPoint32U(HDC hdc, const ::scoped_string & scopedstrString, int ca, LPSIZE32 psizl)
//
//{
//
//#ifdef WINDOWS_DESKTOP
//
//   if (pString == nullptr)
//
//   {
//
//      return ::GetTextExtentPoint32W(hdc, nullptr, ca, psizl) != FALSE;
//
//   }
//
//   wstring wstr = utf8_to_unicode(pString, ca);
//
//
//   bool bRet = ::GetTextExtentPoint32W(hdc, wstr, (int)wstr.get_length(), psizl) != FALSE;
//
//   return bRet;
//
//#else
//
//   throw ::exception(todo);
//
//#endif
//
//}
//
//
//CLASS_DECL_AURA int  DrawTextU(HDC hdc, const ::scoped_string & scopedstrchText, int cchText, RECT32 * prect, unsigned int format)
//
//{
//
//#ifdef WINDOWS_DESKTOP
//
//   if (pchText == nullptr)
//
//   {
//
//      return ::DrawTextW(hdc, nullptr, cchText, prect, format);
//
//
//   }
//
//   wstring wstr = utf8_to_unicode(pchText, cchText);
//
//
//   bool bRet = ::DrawTextW(hdc, wstr, (int)wcslen(wstr), prect, format) != FALSE;
//
//
//   return bRet;
//
//#else
//
//   throw ::exception(todo);
//
//#endif
//
//
//} // namespace write_text
//


