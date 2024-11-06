#include "framework.h"



namespace draw2d
{


   font::font(::particle * pparticle) :
      ::write_text::font(pparticle),
      m_pfont(e_create)
   {

      m_pDC       = nullptr;
      m_pfontOld  = nullptr;

   }


   font::~font()
   {

   }


   void font::clear()
   {

      m_glyphset.erase_all();

   }


   ::write_text::font * font::GetFont()
   {

      return m_pfont;

   }


   void font::embossed_text_out(::draw2d::graphics_pointer & pgraphics, const ::rectangle_f64 & rectangle, double dRateX, double dHeight, string & str)
   {


      ::auraacmesystem()->draw2d()->api().embossed_text_out(pgraphics, rectangle, dRateX, dHeight, str);

      return;



//      SetDC(pgraphics);
//      SelectFont();
//
//      ::rectangle_f64 rectangleOffset(rectangle);
//      const ::point_i32 & pointOffset(rectangleOffset.top_left());
//
//      glyph * pglyph;

//      strsize iSize = str.length();
//      for(int i = 0; i < iSize; i++)
//      {
//         pglyph = GetGlyph(str[i]);

//         if(pglyph != nullptr)

//         {
//            pointOffset.x() = int(pgraphics->get_text_extent(str.left(i)).cx());
//            pglyph->DrawGlyph(

//               pgraphics,
//               true,
//               (float) dRateX,
//               &pointOffset);
//         }
//      }
//
//
//
//      UnselectFont();
//      ClearDC();

      /*   SetDC(pgraphics);
         SelectFont();

         pgraphics->text_out(x, y, str);
         pgraphics->BeginPath();
         pgraphics->text_out(x, y, str);
         pgraphics->EndPath();
         pgraphics->StrokePath();

         UnselectFont();
         ClearDC();*/

   }

   void font::embossed_text_out(::draw2d::graphics_pointer & pgraphics, const ::rectangle_f64 & rectangle, double dRateX, double dHeight, string & str, LPINT piCharsPositions, int iCharsPositions, int iOffset)

   {

      ::auraacmesystem()->draw2d()->api().embossed_text_out(pgraphics, rectangle, dRateX, dHeight, str, piCharsPositions, iCharsPositions, iOffset);


      return;



//      SetDC(pgraphics);
//      SelectFont();
//
//      const ::rectangle_f64 rectangleOffset(rectangle);
//      const ::point_i32 & pointOffset;
//
//
//      glyph * pglyph;

//      strsize iSize = str.length();
//      for(strsize i = 0; i < iSize; i++)
//      {
//         pglyph = GetGlyph(str[i]);

//         if(pglyph != nullptr)

//         {
//            pointOffset = rectangleOffset.top_left();
//            pointOffset.x() += (long) ((piCharsPositions[iOffset + i] - lpiCharsPositions[iOffset]) * dRateX);

//            pglyph->DrawGlyph(

//               pgraphics,
//               true,
//               (float) dRateX,
//               &pointOffset);
//         }
//      }


      /*   draw2d::api::embossed_text_out(
            pgraphics,
            pcrect,

            floatRateX,
            floatHeight,
            str,
            piCharsPositions,

            iCharsPositions,
            iOffset);*/

//      UnselectFont();
//      ClearDC();
      /*   SetDC(pgraphics);
         SelectFont();

         ::rectangle_f64 clipRect;

         int iOldMapMode = pgraphics->GetMapMode();
         pgraphics->SetMapMode(MM_TEXT);
         pgraphics->text_out(x, y, str);
         pgraphics->BeginPath();
         pgraphics->text_out(x, y, str);
         pgraphics->EndPath();
         pgraphics->StrokePath();

         pgraphics->SetMapMode(iOldMapMode);
         UnselectFont();
         ClearDC();*/
   }

   void font::simple_text_out(::draw2d::graphics_pointer & pgraphics, int x, int y, string & str, LPINT piCharsPositions, int iCharsPositions)


   {


      __UNREFERENCED_PARAMETER(piCharsPositions);

      __UNREFERENCED_PARAMETER(iCharsPositions);
      SetDC(pgraphics);
      SelectFont();

      ::rectangle_f64 clipRect;

      pgraphics->text_out(x, y, str);

      UnselectFont();

      ClearDC();

   }


   bool font::AddGlyph(WCHAR wchar)
   {

      return AddGlyph((unsigned int) wchar);

   }


   bool font::AddGlyph(char tch)
   {

      return AddGlyph((unsigned int) tch);

   }


   bool font::AddGlyph(unsigned int user)
   {

      //   single_lock synchronouslock(m_pmutex);
      //   synchronouslock.lock(U32_INFINITE_TIMEOUT);

      return true;

#ifdef WINDOWS_DESKTOP

      if(m_glyphset.find_first(user) >= 0)
         return true;

      glyph glyph;
      glyph.m_ui = user;
      //m_glyphArray.add(pGlyph);
      MAT2 mat2;
      mat2.eM11.value = 1;
      mat2.eM11.fract = 0;
      mat2.eM12.value = 0;
      mat2.eM12.fract = 0;
      mat2.eM21.value = 0;
      mat2.eM21.fract = 0;
      mat2.eM22.value = 1;
      mat2.eM22.fract = 0;
      GLYPHMETRICS gm;

      unsigned int cbBuffer = m_pDC->GetGlyphOutline(user, GGO_NATIVE, &glyph.m_gm, 0, nullptr, &mat2);

      if(cbBuffer == GDI_ERROR)
         return false;

      if(cbBuffer == 0)
      {

         m_glyphset.add(glyph);

         return true;

      }

      LPTTPOLYGONHEADER pPH = (LPTTPOLYGONHEADER) malloc(cbBuffer);


      if(pPH == nullptr)

         return false;

      m_pDC->GetGlyphOutline(user, GGO_NATIVE, &gm, cbBuffer, pPH, &mat2);


      glyph.Initialize(pPH, cbBuffer, m_iFontHiHeight);


      free(pPH);


      m_glyphset.add(glyph);

      return true;

#endif

   }

   void font::SetDC(::draw2d::graphics_pointer & pgraphics)
   {
      ASSERT(m_pDC == nullptr);
      ASSERT(pgraphics != nullptr);
      m_pDC = pgraphics;
   }

   void font::SelectFont()
   {
      m_pfontOld = m_pDC->SelectObject(m_pfont);
   }

   void font::ClearDC()
   {
      m_pDC = nullptr;
   }

   void font::UnselectFont()
   {
      ASSERT(m_pfontOld != nullptr);
      m_pDC->SelectObject(m_pfontOld);
      m_pfontOld = nullptr;
   }



   glyph * font::GetGlyph(char ch)
   {
      return GetGlyph((unsigned int) ch);
   }

   glyph * font::GetGlyph(WCHAR wch)
   {
      return GetGlyph((unsigned int) wch);
   }

   glyph * font::GetGlyph(unsigned int user)
   {
      return m_glyphset.GetGlyph(user);
   }


   void font::AddXFGlyphs(string_array_array  & straaTokens)
   {
      char           ch;
      string         str;
      int        i, j, k;
      bool           forceInsertion = false;

      SelectFont();
      for(i = 0; i < straaTokens.get_size(); i++)
      {
         string_array & straTokens = straaTokens[i];
         for(j = 0; j < straTokens.get_size(); j++)
         {
            str = straTokens[j];
            for(k = 0; k < str.length(); k++)
            {
               ch = str.operator[](k);
               if(forceInsertion)
               {
                  forceInsertion = false;
                  AddGlyph(ch);
               }
               else if(ch == '\\')
               {
                  forceInsertion = true;
               }
               else if(ch == '^')
               {
                  AddGlyph(' ');
               }
               else if(ch == '/')
               {
               }
               else if(ch == '%')
               {
               }
               else if(ch == '<')
               {
               }
               else if(ch == '>')
               {
               }
               else
               {
                  AddGlyph(ch);
               }
            }
         }
      }
      UnselectFont();
   }

   void font::AddGlyphs(const ::string & pStr)

   {
      string str(pStr);

      SelectFont();
      for(int i = 0; i < str.length(); i++)
      {
         AddGlyph(str[i]);
      }

   }

   void font::TextOutEx(
   ::draw2d::graphics_pointer & pgraphics,
   const rectangle &               rectangle,
   double               dRateX,
   double               dHeight,
   string                 &str,
   LPINT                piCharsPositions,

   int                     iCharsPositions,
   int                  iOffset,
   int                     iEffect)
   {

      switch(iEffect)
      {
      case EffectSimple:
         simple_text_out(pgraphics, rectangle.left(), rectangle.top(), str, piCharsPositions, iCharsPositions);

         break;
      case EffectEmbossed:
         embossed_text_out(
         pgraphics,
         rectangle,
         dRateX,
         dHeight,
         str,
         piCharsPositions,

         iCharsPositions,
         iOffset);
         break;
      default:
         ASSERT(false);

      }

   }


   int font::GetMegaHeight()
   {

      return m_tm.tmHeight +
             m_tm.tmInternalLeading +
             m_tm.tmExternalLeading;

   }



   void font::OnSetFont()
   {
      OnUpdateFont();
   }

   void font::OnUpdateFont()
   {

      ::draw2d::graphics_pointer spgraphics(e_create);

      spgraphics->CreateCompatibleDC(nullptr);

      ::write_text::font * pFontOld = spgraphics->SelectObject(m_pfont);

      spgraphics->get_text_metrics(&m_tm);

      m_iFontHiHeight = m_tm.tmAscent + m_tm.tmDescent;

      spgraphics->SelectObject(pFontOld);
      spgraphics->DeleteDC();

   }


} // namespace draw2d


bool CLASS_DECL_AURA TextOutU(HDC hdc, int x, int y, const ::string & pString, int ca)

{

#ifdef WINDOWS_DESKTOP

   if(pString == nullptr)

   {
      return ::TextOutW(hdc, x, y, nullptr, ca) != false;

   }

   wstring wstr = utf8_to_unicode(pString, ca);


   bool bRet = ::TextOutW(hdc, x, y, wstr, (int) wstr.get_length()) != false;

   return bRet;

#else

   throw ::exception(todo);

   /*

      if(pString == nullptr)

      {
         return ::text_out(hdc, x, y, nullptr, 0) != false;
      }

      return ::text_out(hdc, x, y, wstr, (int) wstr.get_length()) != false;
   */

#endif

}


CLASS_DECL_AURA bool GetTextExtentPoint32U(HDC hdc, const ::string & pString, int ca, LPSIZE32 psizl)

{

#ifdef WINDOWS_DESKTOP

   if(pString == nullptr)

   {

      return ::GetTextExtentPoint32W(hdc, nullptr, ca, psizl) != false;

   }

   wstring wstr = utf8_to_unicode(pString, ca);


   bool bRet = ::GetTextExtentPoint32W(hdc, wstr, (int) wstr.get_length(), psizl) != false;

   return bRet;

#else

   throw ::exception(todo);

#endif

}


CLASS_DECL_AURA int  DrawTextU(HDC hdc, const ::string & pchText, int cchText, RECT32 * lprc, unsigned int format)

{

#ifdef WINDOWS_DESKTOP

   if(pchText == nullptr)

   {

      return ::DrawTextW(hdc, nullptr, cchText, prc, format);


   }

   wstring wstr = utf8_to_unicode(pchText, cchText);


   bool bRet = ::DrawTextW(hdc, wstr, (int) wcslen(wstr), prc, format) != false;


   return bRet;

#else

   throw ::exception(todo);

#endif

}


