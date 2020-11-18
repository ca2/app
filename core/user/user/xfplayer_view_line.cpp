#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/user/user/_user.h"
#endif


const i32 xfplayer_view_line::AlignLeft = 1;
const i32 xfplayer_view_line::AlignRight = 2;


xfplayer_view_line::xfplayer_view_line() :
   m_font(e_create)
{

   m_bColonPrefix = false;
   m_pContainer = nullptr;
   m_bEnhancedEmboss = true;
   m_bCacheEmboss = false;
   m_cr = ARGB(255, 255, 255, 255);
   m_crOutline = ARGB(255, 0, 0, 0);
   m_nFont = 0;
   m_lpBitmapData = nullptr;
   m_bAutoSizeX = false;
   m_bAutoSizeY = false;
   m_iAlign = AlignLeft;
   m_rect.left = 0;
   m_rect.top = 0;
   m_rect.right = 0;
   m_rect.bottom = 0;
   m_bVisible = false;
   m_iAnimateType = AnimateNoAnimate;
   m_iTextEffect = EffectSimple;
   m_dAnimateProgress = 0;
   m_iIndent = 0;
   m_dAnimateProgressIncrement = 1.0;
   m_dXfplayerViewLineBlend = 1.0;
   m_iIndex = 0;

}


xfplayer_view_line::xfplayer_view_line(xfplayer_view_linea * pContainer) :
   object(pContainer),
   m_font(e_create)
{
   m_pContainer = pContainer;
   m_bEnhancedEmboss = true;
   m_bCacheEmboss = false;
   m_nFont = 0;
   m_lpBitmapData = nullptr;
   m_bAutoSizeX = false;
   m_bAutoSizeY = false;
   m_iAlign = AlignLeft;
   m_rect.left = 0;
   m_rect.top = 0;
   m_rect.right = 0;
   m_rect.bottom = 0;
   m_bVisible = false;
   m_iAnimateType = AnimateNoAnimate;
   m_iTextEffect = EffectSimple;
   m_dAnimateProgress = 0;
   m_dAnimateProgress = 0;
   m_dAnimateProgressIncrement = 1.0;
   m_iIndex = 0;
}


xfplayer_view_line::xfplayer_view_line(const xfplayer_view_line & line) :
   object(line.get_context_object()),
   m_font(e_create)
{

   operator = (line);

}


xfplayer_view_line::~xfplayer_view_line()
{

}


bool xfplayer_view_line::PrepareLine(::draw2d::graphics_pointer & pgraphics, string str, i32 flags, const ::rect & rect)

{

   single_lock sl(m_pContainer->mutex());

   UNREFERENCED_PARAMETER(flags);
   m_straLink.remove_all();
   m_iaLinkStart.remove_all();
   m_iaLinkEnd.remove_all();
   strsize               iChars;
   strsize               iStr;
   strsize               iStrLen;
   ASSERT(pgraphics != nullptr);
   iStrLen = str.get_length();
   iChars = -1;
   m_str.Empty();
   m_iIndent = 0;
   for (iStr = 0; iStr < iStrLen; iStr++)
   {
      AddChar(str[iStr], iChars);
   }

   CalcCharsPositions(pgraphics, rect);


   return true;

}


void xfplayer_view_line::AddChar(WCHAR wch, strsize & index)
{

   single_lock sl(m_pContainer->mutex());

   m_str += wch;

   index = m_str.get_length() - 1;

   if (m_iaPosition.get_size() < index + 2)
   {

      m_iaPosition.allocate(m_iaPosition.get_size() + 10);

   }

}


void xfplayer_view_line::AddChar(WCHAR wch, strsize & index, draw2d::font * pFont)
{

   single_lock sl(m_pContainer->mutex());

   UNREFERENCED_PARAMETER(pFont);
   index++;
   if (m_iaPosition.get_size() < index + 2)
   {
      m_iaPosition.allocate(m_iaPosition.get_size() + 10);
   }
   m_str += wch;
   ASSERT(m_str.get_length() - 1 == index);

}


void xfplayer_view_line::GetPlacement(RECT32 * prect)

{

   single_lock sl(m_pContainer->mutex());

   *prect = m_rect;

}


bool xfplayer_view_line::_001OnDraw(::draw2d::graphics_pointer & pgraphics, bool bDraw, const ::rect & rect, rect_array & rectaModified, bool bRecalcLayout)
{

   single_lock sl(m_pContainer->mutex());

   string strFinal(m_str);

   double dBlend;

   if (m_dXfplayerViewLineBlend <= 0.0)
      return true;
   if (m_dXfplayerViewLineBlend >= 1.0)
      dBlend = 1.0;
   else
      dBlend = m_dXfplayerViewLineBlend;

   pgraphics->set(m_font);

   //   pgraphics->SetBkMode(TRANSPARENT);

   point iMargin;
   iMargin.x = 3;
   iMargin.y = 3;

   if (!IsVisible())
   {

      return true;

   }

   if (bRecalcLayout || m_rectClient != rect)
   {

      m_bCacheEmboss = false;

      CalcCharsPositions(pgraphics, &rect);

   }

   ::rect rectTextOut;
   GetPlacement(rectTextOut);

   switch (m_iAnimateType)
   {
   case AnimateNoAnimate:
   {
      if (bDraw)
      {
         strsize iLink = 0;
         strsize iChar = 0;
         while (true)
         {
            pgraphics->set(m_font);
            if (iChar >= strFinal.get_length())
               break;
            if (iLink >= m_iaLinkStart.get_size())
            {
               const ::size & size = pgraphics->GetTextExtent(strFinal.Left(iChar));
               EmbossedTextOut(pgraphics, strFinal.Mid(iChar), rectTextOut.left + size.cx, rectTextOut.top, 0, m_cr, m_crOutline, strFinal.get_length() - iChar, dBlend);
               break;
            }
            else if (m_iaLinkStart[iLink] > iChar)
            {
               const ::size & size = pgraphics->GetTextExtent(strFinal.Left(iChar));
               EmbossedTextOut(pgraphics, strFinal.Mid(iChar), rectTextOut.left + size.cx, rectTextOut.top, 0, m_cr, m_crOutline, m_iaLinkStart[iLink], dBlend);
            }
            pgraphics->set(m_fontLink);
            const ::size & size = pgraphics->GetTextExtent(strFinal.Left(m_iaLinkStart[iLink]));

            EmbossedTextOut(pgraphics, strFinal.Mid(m_iaLinkStart[iLink]), rectTextOut.left + size.cx, rectTextOut.top, 0, m_cr, m_crOutline, m_iaLinkEnd[iLink] - m_iaLinkStart[iLink] + 1, dBlend);
            iChar = m_iaLinkEnd[iLink] + 1;
            iLink++;
         }
         if (GetSelection().m_iCharStartSource >= 0)
         {
            index iStart;
            index iLineStart;
            index iLineEnd;
            strsize iCharStart;
            strsize iCharEnd;
            GetSelection().GetNormalSelection(iLineStart, iCharStart, iLineEnd, iCharEnd);
            if (iLineStart < m_iIndex)
            {
               iStart = 0;
            }
            else if (iLineStart > m_iIndex)
            {
               iStart = m_iaPosition.get_count();
            }
            else
            {
               iStart = iCharStart;
            }
            index iEnd;
            if (iLineEnd < m_iIndex)
            {
               iEnd = -1;
            }
            else if (iLineEnd > m_iIndex)
            {
               iEnd = m_iaPosition.get_upper_bound();
            }
            else
            {
               iEnd = iCharEnd;
            }
            if (iStart < iEnd)
            {
               ::rect rectPlacement;
               GetPlacement(rectPlacement);
               ::rect rect = rectPlacement;
               size size1 = pgraphics->GetTextExtent(strFinal.Left(iStart));
               size size2 = pgraphics->GetTextExtent(strFinal.Left(iEnd + 1));
               rect.left = rectPlacement.left + size1.cx;
               rect.right = rectPlacement.left + size2.cx;
               ::image_pointer pimage;
               if (rect.area() > 0)
               {
                  pimage = create_image(rect.size());
                  pimage->fill(255, 255, 255, 255);
                  pimage->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_blend);
                  pgraphics->flush();

                  //const ::point & point = pgraphics->GetViewportOrg();
                  //pimage->from(nullptr, pgraphics, point + rect.top_left(), rect.size());
                  pimage->g()->draw(::point(), pgraphics, rect);
                  //pimage->get_graphics()->fill_rect(0, 0, 16, 16, ARGB(255, 255, 0, 255));
                  pimage->invert();
                  //pimage->fill_channel(0, ::color::channel_blue);
                  pimage->fill_channel(255, ::color::channel_alpha);
                  pgraphics->draw(rect.top_left(), pimage, ::rect(rect.size()));
               }
            }
         }

      }
   }
   break;
   case AnimateRHL:
   {
      i32 iLeft = m_iaPosition.element_at(0);
      i32 iLeftDiff = 0;
      i32 iLastLeftDiff = 0;
      i32 i;
      for (i = 0; i < m_iaPosition.get_size(); i++)
      {
         iLastLeftDiff = iLeftDiff;
         iLeftDiff = m_iaPosition.element_at(i) - iLeft;
         if ((i32)m_dAnimateProgress <= iLeftDiff)
         {
            //i--;
            break;
         }
      }

      ::draw2d::region_pointer prgn(this);

      string strFinal(m_str);
      string strLeft = strFinal.Right(strFinal.get_length() - i);
      i32 iLeftOffset;
      iLeftOffset = iLastLeftDiff - (i32)m_dAnimateProgress;
      ::rect rectTextOut;
      GetPlacement(rectTextOut);
      rectTextOut.left += iLeftOffset;
      if (bDraw)
      {
         EmbossedTextOut(pgraphics, strLeft, rectTextOut.left, rectTextOut.top,
                         0,
                         m_cr,
                         m_crOutline,
                         strFinal.get_length(),
                         dBlend);
      }
      i32 iMaxCounter = max((i32)m_iaPosition.element_at(m_str.get_length()) - m_iaPosition.element_at(0) + 100, m_rect.right - m_rect.left);
      i32 iRight = iMaxCounter - (i32)m_dAnimateProgress;
      if (iRight < m_rect.right)
      {
         i32 iRightEnd;
         i32 i;
         for (i = 0; i < m_iaPosition.get_size(); i++)
         {
            iRightEnd = iRight + m_iaPosition.element_at(i) - iLeft;
            if (iRightEnd >= m_rect.right)
            {
               break;
            }
         }
         string strRight = strFinal.Left(i);
         rectTextOut.left = iRight;
         if (bDraw)
         {
            EmbossedTextOut(pgraphics, strRight, rectTextOut.left, rectTextOut.top, 0, m_cr, m_crOutline, strFinal.get_length(), dBlend);
         }
      }

      if (is_set_ref(rectaModified))
      {
         ::rect baserect;
         prgn->get_bounding_box(baserect);
         rectaModified.add(baserect);

      }
   }
   break;
   default:
      ASSERT(FALSE);
   }

   return true;

}


bool xfplayer_view_line::_001OnDraw(::draw2d::graphics_pointer & pgraphics, bool bDraw, const ::rect & rect, rect_array & rectaModified, ::count * count, bool bRecalcLayout, color32_t crColor, ::draw2d::pen_pointer sppen)
{

   single_lock sl(m_pContainer->mutex());

   ::rect rectPlacement;

   GetPlacement(rectPlacement);

   pgraphics->set(m_font);

   //   pgraphics->SetBkMode(TRANSPARENT);

   point iMargin;
   {
      iMargin.x = (::i32)(sppen->m_dWidth / 2.0);
      iMargin.y = (::i32)(sppen->m_dWidth / 2.0);
   }

   if (!IsVisible())
   {

      ::rect rect(m_rectInvalidate);

      if (!is_null_ref(rectaModified))
      {
         ::rect baserect(rect);
         rectaModified.add(baserect);
      }

      Validate(rect);

      return true;
   }

   if (bRecalcLayout)
   {

      CalcCharsPositions(pgraphics, &rect);

      pgraphics->set(m_font);

   }


   switch (m_iAnimateType)
   {
   case AnimateNoAnimate:
   {
      string strFinal;
      strFinal = m_str;
      pgraphics->set(sppen);

      ::draw2d::brush_pointer brushText(e_create);

      brushText->create_solid(

      crColor);

      pgraphics->set(brushText);

      //pgraphics->set_text_color(crColor);

      ::rect rectTextOut;
      GetPlacement(rectTextOut);
      if (bDraw)
      {
         pgraphics->_DrawText(
         strFinal,
         rectTextOut,
         e_align_bottom_left);
      }
   }
   break;
   case AnimateRHL:
   {
      if (m_iaPosition.get_size() <= 0)
         break;
      //         i32 iLeft = m_iaPosition.element_at(0);
      i32 iLeftDiff = 0;
      //i32 iLastLeftDiff = 0;
      i32 i = 0;
      /*            for(i32 i = 0; i < m_iaPosition.get_size(); i++)
                  {
                      iLastLeftDiff = iLeftDiff;
                      iLeftDiff = m_iaPosition.element_at(i) - iLeft;
                      if(iLeftDiff >= (i32) m_dAnimateProgress)
                      {
                          break;
                      }
                  }*/

      string strFinal(m_str);
      string strLeft = strFinal.Right(strFinal.get_length() - i);
      i32 iLeftOffset;
      iLeftOffset = iLeftDiff - (i32)m_dAnimateProgress;

      pgraphics->set(sppen);
      ::draw2d::brush_pointer brushText(e_create);

      brushText->create_solid(crColor);

      pgraphics->set(brushText);

      pgraphics->set(m_font);
      ::rect rectTextOut;
      GetPlacement(rectTextOut);
      rectTextOut.left += iLeftOffset;
      if (bDraw)
      {
         
         pgraphics->_DrawText(strLeft, rectTextOut, e_align_bottom_left);

      }
      /*           pFont->TextOutEx(
                      pdcForeground,
                    rectTextOut,
                  1.0,
                  rectTextOut.height(),
                    strLeft,
                    m_iaPosition.get_data(),
                      m_iaPosition.get_size(),
                    0,
                      MapToFontEffect(m_iTextEffect));   */
      i32 iSpacing = 100;
      i32 iMaxCounter = max(
                            (i32)m_iaPosition.element_at(m_str.get_length())
                            - m_iaPosition.element_at(0) + iSpacing, m_rect.right - m_rect.left);
      i32 iRight = iMaxCounter - (i32)m_dAnimateProgress;
      if (iRight < m_rect.right)
      {
         /*    i32 iRightEnd;
             for(i32 i = 0; i < m_iaPosition.get_size(); i++)
             {
                 iRightEnd = iRight + m_iaPosition.element_at(i) - iLeft;
                 if(iRightEnd >= m_rect.right)
                 {
                     break;
                 }
             }*/
         //string strRight = strFinal.Left(i);
         string strRight = strFinal;
         rectTextOut.left = iRight;
         if (bDraw)
         {

            pgraphics->_DrawText(strRight, rectTextOut, e_align_bottom_left);

         }
         /*               pFont->TextOutEx(
                             pdcForeground,
                           rectTextOut,
                        1.0,
                        rectTextOut.height(),
                           strRight,
                           m_iaPosition.get_data(),
                             m_iaPosition.get_size(),
                           0,
                             MapToFontEffect(m_iTextEffect));   */
      }

   }
   break;
   default:
      ASSERT(FALSE);
   }

   return true;

}



/*void xfplayer_view_line::CalcCharsPositions(
::draw2d::graphics * pdcForeground,
   ref_array <  draw2d::font > * pFonts,
   const ::rect & rect)
{
   m_bCacheEmboss = false;
   //draw2d::font * pFont;
//    ::draw2d::graphics * pdcForeground = m_ptwi->TwiGetDC();
   if(m_str.get_length() <= 0)
      return;
   if(pFonts->get_size() > 0)
   {
      i32 i, nFont, iFontFound, iMaxExtent, iLeft;
      ::size size;
      ::rect clientRect;
      nFont = 0;
      iFontFound = -1;
      for(nFont = 0; nFont < pFonts->get_size(); nFont++)
      {
         pdcForeground->set(pFonts->get_at(nFont)->GetFont());
         GetTextExtentPoint32W(
            pdcForeground->get_os_data(),
            m_str,
            m_str.get_length(),
            &size);
         if((m_iAlign & AlignLeft) > 0)
         {
            if(size.cx + m_rect.left <= rect.right)

            {
               iFontFound = nFont;
               break;
            }
         }
         else if((m_iAlign & AlignRight) > 0)
         {
            if(m_rect.right - size.cx >= 0)
            {
               iFontFound = nFont;
               break;
            }
         }
      }
      if(iFontFound < 0)
      {
         m_nFont = pFonts->get_size() - 1;
      }
      else
      {
         m_nFont = iFontFound;
      }
      pdcForeground->set(pFonts->get_at(m_nFont)->GetFont());
      if(m_iAlign == AlignLeft)
      {
         m_iaPosition[0] = m_rect.left + m_iIndent;
         for(i = 1; i <= m_str.get_length(); i++)
         {
            GetTextExtentPoint32W(
               pdcForeground->get_os_data(),
               m_str,
               i,
               &size);
            m_iaPosition[i] = size.cx + m_rect.left  + m_iIndent;
         }
         if(m_bAutoSizeX)
         {
            m_rect.right = m_rect.left  + m_iIndent + size.cx;
            }
         if(m_bAutoSizeY)
         {
            m_rect.bottom = m_rect.top + size.cy;
         }
      }
      else if(m_iAlign == AlignRight)
      {
         GetTextExtentPoint32W(
            pdcForeground->get_os_data(),
            m_str,
            m_str.get_length(),
            &size);
         iMaxExtent = size.cx;
         iLeft = m_rect.right - iMaxExtent;
         m_iaPosition[0] = iLeft;
         for(i = 1; i <= m_str.get_length(); i++)
         {
            GetTextExtentPoint32W(
               pdcForeground->get_os_data(),
               m_str,
               i,
               &size);
            m_iaPosition[i] = size.cx + iLeft;
         }
         if(m_bAutoSizeX)
         {
            m_rect.left = m_rect.right - size.cx;
            }
            if(m_bAutoSizeY)
            {
            m_rect.bottom = m_rect.top + size.cy;
         }
      }

   }

   else
   {
      i32 i; //, width;
      ::size size;
         m_iaPosition[0] = m_rect.left;
         for(i = 1; i <= m_str.get_length(); i++)
         {
            GetTextExtentPoint32W(
               pdcForeground->get_os_data(),
               m_str,
               i ,
               &size);
            m_iaPosition[i] = m_rect.left + size.cx;
         }
      if(m_bAutoSizeX)
      {
         m_rect.right = m_rect.left + size.cx;
        }
      if(m_bAutoSizeY)
      {
         m_rect.bottom = m_rect.top + size.cy;
      }
   }
//    m_ptwi->TwiReleaseDC(pdcForeground);

}*/


void xfplayer_view_line::CalcCharsPositions(::draw2d::graphics_pointer & pgraphics, const ::rect & rect)

{

   single_lock sl(m_pContainer->mutex());

   m_bCacheEmboss = false;

   if (m_str.get_length() <= 0)
   {

      return;

   }

   i32 i;
   ::size size;
   ::rect rectClient(rect);

   m_rectClient = rectClient;
   ::rect rectPlacement;
   GetPlacement(rectPlacement);

   string strMain = m_str;

   m_font->m_dFontWidth = 1.0;

   m_font->set_modified();

   pgraphics->set(m_font);

   size = pgraphics->GetTextExtent(strMain);

   if ((size.cx * 1.2) > rectClient.width())
   {

      m_floatRateX = (double) rectClient.width() / ((double) size.cx * 1.2);

   }
   else
   {

      m_floatRateX = 1.0;

   }

   ::draw2d::text_metric tm;

   pgraphics->get_text_metrics(&tm);

   m_font->m_dFontWidth = m_floatRateX;

   m_font->set_modified();

   if (m_straLink.get_size() > 0)
   {
      *m_fontLink = *m_font;
      m_fontLink->set_underline();
   }


   if (m_bColonPrefix)
   {

      m_fontPrefix.create(this);

      *m_fontPrefix = *m_font;

      m_fontPrefix->m_dFontSize *= 0.5;


   }

   m_str.truncate(min(100, m_str.length()));

   if (m_bColonPrefix)
   {

      m_strPrefix = m_str.Left(max(0, m_str.find(":")));

      m_strRoot = m_str.Mid(max(0, m_str.find(":") + 1));

      m_strRoot.trim_left();

      pgraphics->set(m_fontPrefix);

      m_iaPosition[0] = 0;
      for (i = 1; i <= m_strPrefix.get_length(); i++)
      {
         m_dcextension.GetTextExtent(
         pgraphics,
         m_strPrefix,
         i,
         size);
         m_iaPosition.add(size.cx);
      }
      int iSize = size.cx;
      m_dcextension.GetTextExtent(
      pgraphics,
      " ",
      1,
      size);
      m_iaPosition.add(iSize + size.cx);
      pgraphics->set(m_font);
      for (i = 1; i <= m_strRoot.get_length(); i++)
      {
         m_dcextension.GetTextExtent(
         pgraphics,
         m_strRoot,
         i,
         size);
         m_iaPosition.add(iSize + size.cx);
      }
   }
   else
   {

      pgraphics->set(m_font);

      m_iaPosition[0] = 0;
      for (i = 1; i <= m_str.get_length(); i++)
      {
         m_dcextension.GetTextExtent(
         pgraphics,
         m_str,
         i,
         size);
         m_iaPosition[i] = size.cx;
      }

   }

   /*if(m_iAlign == AlignLeft)
   {
      m_iaPosition[0] = m_rect.left + m_iIndent;
      iRight = 0;
      for(i = 1; i <= m_str.get_length(); i++)
      {
         GetTextExtentPoint32W(
            (HDC)pgraphics->get_os_data(),
            m_str,
            i,
            &size);
         m_iaPosition[i] = iRight = size.cx + m_rect.left + m_iIndent;
      }
      if(m_bAutoSizeX)
      {
         m_rect.right = iRight;
        }
      if(m_bAutoSizeY)
      {
         m_rect.bottom = m_rect.top + size.cy;
      }
   }
   else if(m_iAlign == AlignRight)
   {
      GetTextExtentPoint32W(
         (HDC)pgraphics->get_os_data(),
         m_str,
         m_str.get_length(),
         &size);
      iMaxExtent = size.cx;
      iLeft = m_rect.right - iMaxExtent;
      m_iaPosition[0] = iLeft;
      for(i = 1; i <= m_str.get_length(); i++)
      {
         GetTextExtentPoint32W(
            (HDC)pgraphics->get_os_data(),
            m_str,
            i,
            &size);
         m_iaPosition[i] = size.cx + iLeft;
      }
      if(m_bAutoSizeX)
      {
         m_rect.left = iLeft;
        }
      if(m_bAutoSizeY)
      {
         m_rect.bottom = m_rect.top + size.cy;
      }
   }
   pgraphics->set(pfontOld);*/
}

/*void xfplayer_view_line::CalcCharsPositions(
   ::draw2d::graphics *             pdcForeground,
   draw2d::font *     pFont,
   const rect &           rect)

{
   m_bCacheEmboss = false;
   if(m_str.get_length() <= 0)
      return;
    ::draw2d::font * pfontOriginal = pdcForeground->get_current_font();
   pdcForeground->set(pFont->GetFont());
   i32 i, iLeft, iRight, iMaxExtent;
   ::size size;
   ::rect rectClient(rect);

   m_rectClient = rectClient;
   draw2d::font * pfont = pFont;
   ::draw2d::graphics_pointer & pgraphics = pdcForeground;
   ASSERT(pfont != nullptr);
   ::rect rectPlacement;
   GetPlacement(rectPlacement);
   string strMain = m_str;
   GetTextExtentPoint32W(
      (HDC)pgraphics->get_os_data(),
      strMain,
      strMain.get_length(),
      &size);
   pgraphics->set(pfont->GetFont());
   if(size.cx > rectClient.width())
   {
      m_floatRateX =
         (float)
         rectClient.width()/
         size.cx;
   }
   else
   {
      m_floatRateX = 1.0;
   }

   m_font->delete_object();
   LOGFONTW lf;
   pfont->GetFont()->GetLogFont(&lf);
   pgraphics->set(pfont->GetFont());
   TEXTMETRICW tm;
   pgraphics->GetTextMetrics(&tm);
   lf.lfWidth = (long) (tm.tmAveCharWidth * m_floatRateX - 1);
   m_font->CreateFontIndirect(&lf);





   pgraphics->set(m_font);
   if(m_iAlign == AlignLeft)
   {
      m_iaPosition[0] = m_rect.left + m_iIndent;
      iRight = 0;
      for(i = 1; i <= m_str.get_length(); i++)
      {
         GetTextExtentPoint32W(
            pdcForeground->get_os_data(),
            m_str,
            i,
            &size);
         m_iaPosition[i] = iRight = size.cx + m_rect.left + m_iIndent;
      }
      if(m_bAutoSizeX)
      {
         m_rect.right = iRight;
        }
      if(m_bAutoSizeY)
      {
         m_rect.bottom = m_rect.top + size.cy;
      }
   }
   else if(m_iAlign == AlignRight)
   {
      GetTextExtentPoint32W(
         pdcForeground->get_os_data(),
         m_str,
         m_str.get_length(),
         &size);
      iMaxExtent = size.cx;
      iLeft = m_rect.right - iMaxExtent;
      m_iaPosition[0] = iLeft;
      for(i = 1; i <= m_str.get_length(); i++)
      {
         GetTextExtentPoint32W(
            pdcForeground->get_os_data(),
            m_str,
            i,
            &size);
         m_iaPosition[i] = size.cx + iLeft;
      }
      if(m_bAutoSizeX)
      {
         m_rect.left = iLeft;
        }
      if(m_bAutoSizeY)
      {
         m_rect.bottom = m_rect.top + size.cy;
      }
   }
   pdcForeground->set(pfontOriginal);
}*/

void xfplayer_view_line::SetAutoSize(bool bAutoSize)
{

   single_lock sl(m_pContainer->mutex());

   m_bAutoSizeX = bAutoSize;
   m_bAutoSizeY = bAutoSize;
}

void xfplayer_view_line::SetAlign(i32 iAlign)
{

   single_lock sl(m_pContainer->mutex());

   m_iAlign = iAlign;
}

xfplayer_view_line & xfplayer_view_line::operator = (const xfplayer_view_line & src)
{
   m_pContainer = src.m_pContainer;
   m_bAutoSizeX = src.m_bAutoSizeX;
   m_bAutoSizeY = src.m_bAutoSizeY;
   m_str = src.m_str;
   m_iaPosition = src.m_iaPosition;
   m_iAlign = src.m_iAlign;
   m_rect.bottom = src.m_rect.bottom;
   m_rect.left = src.m_rect.left;
   m_rect.right = src.m_rect.right;
   m_rect.top = src.m_rect.top;
   m_lpBitmapData = src.m_lpBitmapData;
   m_nFont = src.m_nFont;
   m_iAnimateType = src.m_iAnimateType;
   m_iTextEffect = src.m_iTextEffect;
   m_dAnimateProgress = src.m_dAnimateProgress;
   m_dAnimateProgressIncrement = src.m_dAnimateProgressIncrement;
//   m_logfont = src.m_logfont;
   m_font = src.m_font;
   m_bEnhancedEmboss = src.m_bEnhancedEmboss;
   m_bCacheEmboss = false;
   m_dXfplayerViewLineBlend = src.m_dXfplayerViewLineBlend;
   m_iIndex = src.m_iIndex;
   return *this;
}

void xfplayer_view_line::Show(bool bShow)
{

   single_lock sl(m_pContainer->mutex());

   if (bShow && !m_bVisible)
   {
      m_bVisible = true;
      Invalidate();
      if (m_pContainer != nullptr)
      {
         m_pContainer->OnChildSetVisible(this, m_bVisible);
      }

   }
   else if (!bShow && m_bVisible)
   {
      m_bVisible = false;
      Invalidate();
      if (m_pContainer != nullptr)
      {
         m_pContainer->OnChildSetVisible(this, m_bVisible);
      }
   }
}


void xfplayer_view_line::OnTimerAnimate(::draw2d::graphics_pointer& pgraphics, rect_array &  rectaModified)
{

   single_lock sl(m_pContainer->mutex());

   if (IsVisible())
   {

      switch (m_iAnimateType)
      {
      case AnimateNoAnimate:
         break;
      case AnimateRHL:
      {
         m_dAnimateProgress += m_dAnimateProgressIncrement;
         if (m_iaPosition.get_size() > 0)
         {
            if ((i32)m_dAnimateProgress > max(m_iaPosition.element_at(m_str.get_length()) - m_iaPosition.element_at(0) + 100, m_rect.right - m_rect.left))
               m_dAnimateProgress = 0.0;
            ::rect rect;
            GetPlacement(rect);
            Invalidate();
            rectaModified.add(rect);
            /*to(
                pdcForeground,
                false,
                rect, rectaModified,
                false);*/
         }
      }
      break;
      default:
         ASSERT(FALSE);
      }
   }
}

void xfplayer_view_line::SetAnimateType(i32 iAnimateType)
{

   single_lock sl(m_pContainer->mutex());

   m_iAnimateType = iAnimateType;
   m_dAnimateProgress = 0.0;

}

void xfplayer_view_line::SetTextEffect(i32 iTextEffect)
{

   single_lock sl(m_pContainer->mutex());

   m_iTextEffect = iTextEffect;
}

void xfplayer_view_line::SetEmbossPen(::draw2d::pen *pPen)

{

   single_lock sl(m_pContainer->mutex());

   m_lpPenEmboss = pPen;


}

void xfplayer_view_line::SetForegroundColor(color32_t cr)
{

   single_lock sl(m_pContainer->mutex());

   m_crForeground = cr;
}

/*ref_array <  draw2d::font > * xfplayer_view_line::GetFonts()
{
    return &m_fonts;
}
*/
i32 xfplayer_view_line::MapToFontEffect(i32 iLineEffect)
{

   single_lock sl(m_pContainer->mutex());

   switch (iLineEffect)
   {
   case EffectSimple:
      return EffectSimple;
   case EffectEmbossed:
      return EffectEmbossed;
   }
   ASSERT(FALSE);
   return -1;
}

void xfplayer_view_line::SetAnimateIncrement(double dIncrement)
{

   single_lock sl(m_pContainer->mutex());

   m_dAnimateProgressIncrement = dIncrement;
}

//void xfplayer_view_line::SetRedrawMode(i32 iMode)
//{
//  m_iRedrawMode = iMode;
//}

//void xfplayer_view_line::SetRenderWindow(::user::interaction_impl * pwindow)
//{
//  m_pRenderWnd = pwindow;
//}

void xfplayer_view_line::SetRenderCriticalSection(critical_section * pcs)
{
   UNREFERENCED_PARAMETER(pcs);
   //    m_pcsRender =   pcs;
}

i32 xfplayer_view_line::SetLyricPens(::draw2d::pen * ppenLeft, ::draw2d::pen * ppenRight)
{

   single_lock sl(m_pContainer->mutex());

   m_ppenLyricLeft = ppenLeft;
   m_ppenLyricRight = ppenRight;
   return true;
}

i32 xfplayer_view_line::SetLyricColors(color32_t crLeft, color32_t crRight)
{

   single_lock sl(m_pContainer->mutex());

   m_crLyricLeft = crLeft;
   m_crLyricRight = crRight;
   return true;

}


void xfplayer_view_line::SetPlacement(const ::rect & rect)
{

   single_lock sl(m_pContainer->mutex());

   m_rect = rect;

   m_bPendingLayoutUpdate = true;

}


//i32 xfplayer_view_line::GetVmsFontCount()
/*{
   return m_fonts.get_size();
}

void xfplayer_view_line::AddVmsFont(draw2d::font * pfont)
{
   m_fonts.add(pfont);
}*/

void xfplayer_view_line::Invalidate(const rect & rectParam)
{

   single_lock sl(m_pContainer->mutex());

   ::rect rectPlacement;

   GetPlacement(rectPlacement);

   ::rect rectInvalidate;

   if (IsRectEmpty(&rectParam))
   {

      rectInvalidate = rectPlacement;

   }
   else
   {

      rectInvalidate = rectParam;

   }

   m_rectInvalidate.unite(m_rectInvalidate, rectInvalidate);

   m_rectInvalidate.intersect(m_rectInvalidate, rectPlacement);

}


void xfplayer_view_line::Validate(const rect & rectParam)
{

   single_lock sl(m_pContainer->mutex());

   ::rect rectPlacement;

   GetPlacement(rectPlacement);

   ::rect rectValidate;

   if (IsRectEmpty(&rectParam))
   {

      rectValidate = rectPlacement;

   }
   else
   {

      rectValidate = rectParam;

   }

   m_rectInvalidate -= rectValidate;

   m_rectInvalidate.intersect(m_rectInvalidate, rectPlacement);

}


bool xfplayer_view_line::IsVisible()
{

   single_lock sl(m_pContainer->mutex());

   return m_bVisible;

}


void xfplayer_view_line::EmbossedTextOut(::draw2d::graphics_pointer & pgraphics, const char * pcsz, i32 iLeft, i32 iTop, i32 iWidth, color32_t cr, color32_t crOutline, strsize iLen, double dBlend)

{

   single_lock sl(m_pContainer->mutex());

   EmbossedTextOut(
   pgraphics,
   m_pimageMain,
   pcsz,

   iLeft,
   iTop,
   iWidth,
   cr,
   crOutline,
   iLen,
   dBlend);

}


void xfplayer_view_line::EmbossedTextOut(::draw2d::graphics_pointer & pgraphics, ::image * pimageCache, const char * pcsz, i32 iLeft, i32 iTop, i32 iWidth, color32_t cr, color32_t crOutline, strsize iLen, double dBlend)
{

   single_lock sl(m_pContainer->mutex());

   UNREFERENCED_PARAMETER(pimageCache);

   bool bSaveProcessing = !m_bEnhancedEmboss;

   if (bSaveProcessing)
   {

      pgraphics->begin_path();

      pgraphics->text_out(iLeft, iTop, string(pcsz, iLen));


      pgraphics->end_path();

      ::draw2d::pen_pointer pen;

      pen->create_solid(iWidth * 2, crOutline);

      pgraphics->set(pen);

      pgraphics->stroke_path();

      ::draw2d::brush_pointer brushText(e_create);

      brushText->create_solid(cr);

      pgraphics->set(brushText);

      pgraphics->text_out(iLeft, iTop, string(pcsz, iLen));


   }
   else
   {

      if (m_bEnhancedEmboss)
      {

         if (!m_bCacheEmboss || m_strCache != pcsz)

         {

            CacheEmboss(pgraphics, m_str, m_str.get_length(), m_pimageMain);

         }

      }

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

      ::point point;

      point.x = (::i32) (iLeft - ((max(2.0, m_floatRateX * 8.0)) / 2));

      point.y = (::i32) (iTop - ((max(2.0, m_floatRateX * 8.0)) / 2));

      System.imaging().color_blend(pgraphics, point, m_pimageMain->get_size(), m_pimageMain->g(), ::point(), dBlend);

      if (m_bColonPrefix)
      {

         pgraphics->set(m_fontPrefix);

         ::size size;

         size = pgraphics->GetTextExtent(m_strPrefix);

         System.imaging().AlphaTextOut(pgraphics, iLeft, iTop + m_rect.height() - size.cy, m_strPrefix, (i32)m_strPrefix.get_length(), cr, dBlend);

         pgraphics->set(m_font);

         int iOffset;

         if (m_strPrefix.get_length() <= 0)
         {

            iOffset = 0;

         }
         else
         {

            iOffset = (int) (size.cx + size.cx / m_strPrefix.get_length());

         }

         System.imaging().AlphaTextOut(pgraphics, iLeft + iOffset, iTop, m_strRoot, (i32)m_strRoot.get_length(), cr, dBlend);



      }
      else
      {

         pgraphics->set(m_font);

         System.imaging().AlphaTextOut(pgraphics, iLeft, iTop, pcsz, (i32)iLen, cr, dBlend);


      }


   }


}



void xfplayer_view_line::SetColors(color32_t cr, color32_t crOutline)
{

   single_lock sl(m_pContainer->mutex());

   m_cr = cr;
   m_crOutline = crOutline;
}




void xfplayer_view_line::GetLogFont(LOGFONTW &lf)
{

   single_lock sl(m_pContainer->mutex());

   //lf = m_logfont;
}


void xfplayer_view_line::CacheEmboss(::draw2d::graphics_pointer & pgraphics, const char * pcsz, strsize iLen, ::image_pointer & pimageCache)
{

   single_lock sl(m_pContainer->mutex());

   if (!m_bEnhancedEmboss)
   {

      return;

   }

   if (m_bCacheEmboss && m_strCache == pcsz)

      return;

   m_strCache = pcsz;

   m_bCacheEmboss = true;

   //TRACE("CLyricViewLine::CacheEmboss: %s\n", pcsz);

   ::size size;

   pgraphics->set(m_font);

   m_dcextension.GetTextExtent(pgraphics, pcsz, iLen, size);

   size.cx += (::i32)(2 * (max(2.0, m_floatRateX * 8.0)));
   size.cy += (::i32)(2 * (max(2.0, m_floatRateX * 8.0)));


   pimageCache = create_image(size);

   if (!pimageCache)
      return;

   pimageCache->fill(0, 0, 0, 0);

   ::draw2d::graphics_pointer pdcCache = pimageCache->get_graphics();

   pdcCache->set(m_font);

   pdcCache->set_alpha_mode(::draw2d::alpha_mode_set);

   pdcCache->set_alpha_mode(::draw2d::alpha_mode_blend);

   draw2d::brush_pointer brushText(e_create);

   brushText->create_solid(ARGB(96, 96, 96, 96));

   pdcCache->set(brushText);

   ::size s;

   if (m_bColonPrefix)
   {

      pdcCache->set(m_fontPrefix);
      const ::size & size = pdcCache->GetTextExtent(m_strPrefix);
      m_dcextension.text_out(pdcCache, (i32)(i32)((max(2.0, m_floatRateX * 4.0)) / 2), (i32)1 * (i32)((max(2.0, m_floatRateX * 4.0)) / 2) + m_rect.height() - size.cy, m_strPrefix, m_strPrefix.get_length(), s);
      pdcCache->set(m_font);

      int x = (i32) (s.cx + (s.cx / m_strPrefix.get_length()) + (i32)(i32)((max(2.0, m_floatRateX * 8.0)) / 2));

      int y = (i32) (1 * (i32)((max(2.0, m_floatRateX * 8.0)) / 2));

      m_dcextension.text_out(pdcCache, x, y, m_strRoot, m_strRoot.get_length(), s);

   }
   else
   {

      m_dcextension.text_out(pdcCache, (i32)(i32)((max(2.0, m_floatRateX * 8.0)) / 2), (i32)1 * (i32)((max(2.0, m_floatRateX * 8.0)) / 2), pcsz, iLen, s);


   }


   System.imaging().channel_spread_set_color(pdcCache, nullptr, size, pdcCache, nullptr, 0, i32(max(1.0, m_floatRateX * 2.0 + 2)), ARGB(23, 23, 20, 23));

   pdcCache->set_alpha_mode(::draw2d::alpha_mode_blend);
   System.imaging().channel_alpha_gray_blur(pdcCache, nullptr, size, pdcCache, nullptr, 0, i32(max(1.0, m_floatRateX * 2.5)));
   System.imaging().channel_alpha_gray_blur(pdcCache, nullptr, size, pdcCache, nullptr, 0, i32(max(1.0, m_floatRateX * 2.5)));

   pimageCache->set_rgb(0, 0, 0);

}


void xfplayer_view_line::SetFont(::draw2d::font * pfont)
{

   single_lock sl(m_pContainer->mutex());

   m_font = pfont;

}


void xfplayer_view_line::PrepareURLLinks()
{

   single_lock sl(m_pContainer->mutex());

   string str;

   auto pregex = System.create_pcre("/^|\\s|([;\"()]+))(((((http|https)://))|(www\\.))[0-9a-zA-Z./\\-_?=]+)(([;\"()]+)|\\s|$/");

   auto prangea = pregex->matches_ranges(m_str);

   for(auto & range : *prangea)
   {

      m_straLink.add(m_str.Mid(range.begin(), range.count()));
      m_iaLinkStart.add(range.begin());
      m_iaLinkEnd.add(range.upper_bound());

   }


}

bool xfplayer_view_line::CharHasLink(strsize iChar)
{

   single_lock sl(m_pContainer->mutex());

   return GetCharLink(iChar) > -1;
}

bool xfplayer_view_line::GetCharLink(string & str, strsize iChar)
{

   single_lock sl(m_pContainer->mutex());

   index iLink = GetCharLink(iChar);
   if (iLink < 0)
      return false;
   str = m_straLink[iLink];
   return true;
}

::user::e_line_hit xfplayer_view_line::get_link(string & strUrl, const ::point & pointCursor)
{

   single_lock sl(m_pContainer->mutex());

   strsize iChar;
   ::user::e_line_hit etest = hit_test(pointCursor, iChar);
   if (etest == ::user::line_hit_link)
   {
      GetCharLink(strUrl, iChar);
   }
   return etest;
}

index xfplayer_view_line::GetCharLink(strsize iChar)
{

   single_lock sl(m_pContainer->mutex());

   for (index i = 0; i < m_iaLinkStart.get_size(); i++)
   {
      if (iChar >= m_iaLinkStart[i] &&
            iChar <= m_iaLinkEnd[i])
      {
         return i;
      }
   }
   return -1;
}

::user::e_line_hit xfplayer_view_line::hit_test(const point &pointCursorParam, strsize &iChar)
{

   single_lock sl(m_pContainer->mutex());

   bool bInside;
   const ::point & pointCursor = pointCursorParam;
   ::rect rectPlacement;
   GetPlacement(rectPlacement);
   bInside = rectPlacement.contains(pointCursor) != 0;
   if (!bInside)
   {
      iChar = -1;
      return ::user::line_hit_none;
   }
   else
   {
      if (CalcChar(pointCursor, iChar))
      {
         if (CharHasLink(iChar))
         {
            return ::user::line_hit_link;
         }
         else
         {
            return ::user::line_hit_normal;
         }
      }
      else
      {
         iChar = -1;
         return ::user::line_hit_none;
      }
   }

}

bool xfplayer_view_line::CalcChar(const ::point & point, strsize &iChar)
{

   single_lock sl(m_pContainer->mutex());

   ::rect rectPlacement;
   GetPlacement(rectPlacement);
   bool bInside = rectPlacement.contains(point) != 0;
   if (!bInside)
      return false;

   int x = point.x - rectPlacement.left;

   for (i32 i = 0; i < m_iaPosition.get_size() - 1; i++)
   {

      int iL = m_iaPosition[i];

      int iR = m_iaPosition[i + 1];

      int iM = (iR + iL) / 2;

      if (x >= iL && x < iM)
      {
         iChar = i;
         return true;
      }
      if (x >= iM && x < iR)
      {
         iChar = i + 1;
         return true;
      }
   }
   return false;
}


void xfplayer_view_line::OnMouseMove(::message::message * pmessage)
{

   single_lock sl(m_pContainer->mutex());

   SCAST_PTR(::message::mouse, pmouse, pmessage);
   strsize iChar;
   if (CalcChar(pmouse->m_point, iChar))
   {
      if (CharHasLink(iChar))
      {
         pmouse->m_ecursor = cursor_hand;
      }
   }
   /*
   lyric_view_line_selection & selection = GetSelection();

   if(selection.GetState() == lyric_view_line_selection::StateTracking)
   {

      bool bInside;
      i32 iToken;
      i32 iChar;
      ::rect rectPlacement;

      GetPlacement(rectPlacement);
      bInside = rectPlacement.contains(point) != 0;

      if(!bInside)
      {
         if(point.y < rectPlacement.top
            || (point.y <= rectPlacement.bottom &&
            point.x < rectPlacement.left))
         {
            selection.SetSelBefore(*this);
            GetWndRender()->Redraw(rectPlacement);
         }
         else
         {
            selection.SetSelAfter(*this);
            GetWndRender()->Redraw(rectPlacement);
         }
         return false;
      }
      else // bInside == true
      {
         u32 fwKeys = user; // key flags
         if(m_tokenaMain.get_size() <= 0)
            return false;
         if(CalcChar(point, iToken, iChar))
         {
            selection.m_item.SetTokenEnd(iToken);
            selection.m_item.SetCharEnd(iChar);
            GetWndRender()->Redraw(rectPlacement);
         }
         else
         {
            if(point.x < m_tokenaMain.element_at(0).get_position())
            {
               selection.SetSelBefore(*this);
            }
            else
            {
               selection.SetSelAfter(*this);
            }
            GetWndRender()->Redraw(rectPlacement);
         }
         return true;
      }
   }
   else
   {
      if(is_hover())
      {
         update_hover(point);
      }
      else
      {
         bool bInside;
         ::rect rectPlacement;

         GetPlacement(rectPlacement);
         bInside = rectPlacement.contains(point);
         if(bInside)
         {
            update_hover(point);
         }
      }

   }*/

   if (GetSelection().OnMouseMove(*this, (::u32)pmouse->m_nFlags, pmouse->m_point))
   {

      pmouse->m_bRet = true;

      pmouse->m_lresult = 1;

   }

}


void xfplayer_view_line::OnSetCursor(::message::message * pmessage)
{

   UNREFERENCED_PARAMETER(pmessage);

   //if(is_hover())
   //{
   //
   //    pmouse->m_ecursor = cursor_hand;
   //
   //    return TRUE;
   //
   //}

}


void xfplayer_view_line::OnLButtonDown(::message::message * pmessage)
{

   single_lock sl(m_pContainer->mutex());

   SCAST_PTR(::message::mouse, pmouse, pmessage);

   if (GetSelection().OnLButtonDown(*this, (::u32)pmouse->m_nFlags, pmouse->m_point))
   {

      pmouse->m_bRet = true;

      pmouse->m_lresult = 1;

   }

}


void xfplayer_view_line::OnLButtonUp(::message::message * pmessage)
{

   single_lock sl(m_pContainer->mutex());

   SCAST_PTR(::message::mouse, pmouse, pmessage);

   strsize iChar;

   if (CalcChar(pmouse->m_point, iChar))
   {

      if (CharHasLink(iChar))
      {

         string str;

         str = m_straLink[GetCharLink(iChar)];

         ASSERT(m_oswindow->is_window());

         ::hyperlink hyperlink;

         hyperlink.open_link(str, "", "");

      }

   }

   if (GetSelection().OnLButtonUp(*this, (::u32)pmouse->m_nFlags, pmouse->m_point))
   {

      pmouse->m_bRet = true;

      pmouse->m_lresult = 1;

   }

}


void xfplayer_view_line::_001OnTimer(::timer * ptimer)
{

   UNREFERENCED_PARAMETER(ptimer);

   //if(GetSelection().OnTimer(*this, user))
   //{
   //
   //    return true;
   //
   //}

}


::draw2d::font * xfplayer_view_line::GetFont()
{

   single_lock sl(m_pContainer->mutex());

   return m_font;

}


void xfplayer_view_line::set_blend(double d)
{

   single_lock sl(m_pContainer->mutex());

   ASSERT(d >= 0.0);

   ASSERT(d <= 1.0);

   if (d < 0.0 || d > 1.0)
   {

      return;

   }

   m_dXfplayerViewLineBlend = d;

}


void xfplayer_view_line::update_hover(point &pointCursor)
{

   single_lock sl(m_pContainer->mutex());

   ::index iLine = m_iIndex;

   strsize iChar;

   ::user::e_line_hit etest = hit_test(pointCursor, iChar);

   if (etest == ::user::line_hit_link)
   {

      if (m_iLinkHoverIndex != GetLinkIndex(iLine, iChar))
      {

         m_iLinkHoverIndex = GetLinkIndex(iLine, iChar);

         ::rect rect;

         GetPlacement(rect);

         get_interaction()->set_need_redraw();

      }

   }
   else
   {

      if (m_iLinkHoverIndex != -1)
      {

         m_iLinkHoverIndex = -1;

         ::rect rect;

         GetPlacement(rect);

         get_interaction()->set_need_redraw();

      }

   }

}


bool xfplayer_view_line::is_hover()
{

   if (m_iLinkHoverIndex >= 0)
   {

      return true;

   }
   else
   {

      return false;

   }

}


index xfplayer_view_line::GetLinkIndex(index iLine, strsize iChar)
{

   single_lock sl(m_pContainer->mutex());

   if (!has_link())
   {

      return -1;

   }

   if (iLine != m_iIndex)
   {

      return -1;

   }

   return GetCharLink(iChar);

}


bool xfplayer_view_line::has_link()
{

   single_lock sl(m_pContainer->mutex());

   return m_iaLinkStart.get_count() > 0;

}


::user::interaction * xfplayer_view_line::get_interaction()
{

   return m_pContainer->m_pinteraction;

}


inline XfplayerViewLineSelection & xfplayer_view_line::GetSelection()
{

   single_lock sl(m_pContainer->mutex());

   if (m_pContainer == nullptr)
      return m_selection;
   else
      return m_pContainer->GetSelection();
}
