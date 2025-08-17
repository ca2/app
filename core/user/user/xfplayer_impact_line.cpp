#include "framework.h"
#include "xfplayer_impact_line.h"
#include "xfplayer_impact_lines.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/regular_expression/regular_expression.h"
#include "acme/regular_expression/result.h"
#include "acme/platform/message.h"
#include "aura/graphics/image/context.h"
#include "aura/graphics/image/drawing.h"
#include "aura/graphics/write_text/font.h"
#include "aura/graphics/image/imaging.h"
#include "aura/graphics/draw2d/graphics_extension.h"
#include "aura/graphics/draw2d/brush.h"
#include "aura/graphics/draw2d/pen.h"
#include "acme/platform/hyperlink.h"
#include "aura/windowing/windowing.h"
#include "aura/message/user.h"
#include "aura/user/user/interaction.h"
#include "core/platform/system.h"


const int xfplayer_impact_line::AlignLeft = 1;
const int xfplayer_impact_line::AlignRight = 2;


xfplayer_impact_line::xfplayer_impact_line(::user::interaction * puserinteraction)
{
   initialize(puserinteraction);
   m_pselection = __initialize_new xfplayer_impact_line_selection(puserinteraction);
   m_bColonPrefix = false;
   m_pContainer = nullptr;
   m_bEnhancedEmboss = true;
   m_bCacheEmboss = false;
   m_cr = argb(255, 255, 255, 255);
   m_colorOutline = argb(255, 0, 0, 0);
   m_nFont = 0;
   m_lpBitmapData = nullptr;
   m_bAutoSizeX = false;
   m_bAutoSizeY = false;
   m_iAlign = AlignLeft;
   m_rectangle.left() = 0;
   m_rectangle.top() = 0;
   m_rectangle.right() = 0;
   m_rectangle.bottom() = 0;
   m_bVisible = false;
   m_iAnimateType = AnimateNoAnimate;
   m_iTextEffect = EffectSimple;
   m_dAnimateProgress = 0;
   m_iIndent = 0;
   m_dAnimateProgressIncrement = 1.0;
   m_dXfplayerImpactLineBlend = 1.0;
   m_iIndex = 0;

}


void xfplayer_impact_line::initialize_xfplayer_impact_line(xfplayer_impact_linea * pContainer)
{

   //auto estatus = 
   
   initialize(pContainer);
   
   //if(!estatus)
   //{
   //   
   //   return estatus;
   //   
   //}
   
   øconstruct(m_pfont);

   m_pContainer = pContainer;
   m_bEnhancedEmboss = true;
   m_bCacheEmboss = false;
   m_nFont = 0;
   m_lpBitmapData = nullptr;
   m_bAutoSizeX = false;
   m_bAutoSizeY = false;
   m_iAlign = AlignLeft;
   m_rectangle.left() = 0;
   m_rectangle.top() = 0;
   m_rectangle.right() = 0;
   m_rectangle.bottom() = 0;
   m_bVisible = false;
   m_iAnimateType = AnimateNoAnimate;
   m_iTextEffect = EffectSimple;
   m_dAnimateProgress = 0;
   m_dAnimateProgress = 0;
   m_dAnimateProgressIncrement = 1.0;
   m_iIndex = 0;
   
   //return estatus;
   
}


//xfplayer_impact_line::xfplayer_impact_line(const xfplayer_impact_line & line)
//{
//
//   initialize((object *) &line);
//   
//   m_pfont.create(this);
//
//   operator = (line);
//
//}


xfplayer_impact_line::~xfplayer_impact_line()
{

}


bool xfplayer_impact_line::PrepareLine(::draw2d::graphics_pointer & pgraphics, const ::scoped_string & scopedstr, int flags, const ::int_rectangle & rectangle)
{

   _synchronous_lock synchronouslock(m_pContainer->synchronization());

   __UNREFERENCED_PARAMETER(flags);

   m_straLink.erase_all();
   m_iaLinkStart.erase_all();
   m_iaLinkEnd.erase_all();

   character_count               iChars;
   character_count               iStr;
   character_count               iStrLen;

   ASSERT(pgraphics != nullptr);

   iStrLen = scopedstr.length();

   iChars = -1;

   m_str.empty();

   m_iIndent = 0;

   for (iStr = 0; iStr < iStrLen; iStr++)
   {

      add_char(scopedstr[iStr], iChars);

   }

   CalcCharsPositions(pgraphics, rectangle);


   return true;

}


void xfplayer_impact_line::add_char(::wide_character wch, character_count & index)
{

   _synchronous_lock synchronouslock(m_pContainer->synchronization());

   m_str += wch;

   index = m_str.length() - 1;

   if (m_iaPosition.get_size() < index + 2)
   {

      m_iaPosition.set_size(m_iaPosition.get_size() + 10);

   }

}


void xfplayer_impact_line::add_char(::wide_character wch, character_count & index, ::write_text::font * pFont)
{

   _synchronous_lock synchronouslock(m_pContainer->synchronization());

   __UNREFERENCED_PARAMETER(pFont);
   index++;
   if (m_iaPosition.get_size() < index + 2)
   {
      m_iaPosition.set_size(m_iaPosition.get_size() + 10);
   }
   m_str += wch;
   ASSERT(m_str.length() - 1 == index);

}


void xfplayer_impact_line::GetPlacement(::int_rectangle * prectangle)

{

   _synchronous_lock synchronouslock(m_pContainer->synchronization());

   *prectangle = m_rectangle;

}


bool xfplayer_impact_line::_001OnDraw(::draw2d::graphics_pointer & pgraphics, bool bDraw, const ::int_rectangle & rectangle, int_rectangle_array_base & rectaModified, bool bRecalcLayout)
{

   _synchronous_lock synchronouslock(m_pContainer->synchronization());

   string strFinal(m_str);

   double dBlend;

   if (m_dXfplayerImpactLineBlend <= 0.0)
      return true;
   if (m_dXfplayerImpactLineBlend >= 1.0)
      dBlend = 1.0;
   else
      dBlend = m_dXfplayerImpactLineBlend;

   pgraphics->set(m_pfont);

   //   pgraphics->SetBkMode(TRANSPARENT);

   int_point iMargin;
   iMargin.x() = 3;
   iMargin.y() = 3;

   if (!IsVisible())
   {

      return true;

   }

   if (bRecalcLayout || m_rectangleX != rectangle)
   {

      m_bCacheEmboss = false;

      CalcCharsPositions(pgraphics, rectangle);

   }

   ::int_rectangle rectangleTextOut;

   GetPlacement(&rectangleTextOut);

   switch (m_iAnimateType)
   {
   case AnimateNoAnimate:
   {
      if (bDraw)
      {
         character_count iLink = 0;
         character_count iChar = 0;
         while (true)
         {
            pgraphics->set(m_pfont);
            if (iChar >= strFinal.length())
               break;
            if (iLink >= m_iaLinkStart.get_size())
            {
               const ::int_size & size = pgraphics->get_text_extent(strFinal.left(iChar));
               embossed_text_out(pgraphics, strFinal.substr(iChar), rectangleTextOut.left() + size.cx(), rectangleTextOut.top(), 0, m_cr, m_colorOutline, strFinal.length() - iChar, dBlend);
               break;
            }
            else if (m_iaLinkStart[iLink] > iChar)
            {
               const ::int_size & size = pgraphics->get_text_extent(strFinal.left(iChar));
               embossed_text_out(pgraphics, strFinal.substr(iChar), rectangleTextOut.left() + size.cx(), rectangleTextOut.top(), 0, m_cr, m_colorOutline, m_iaLinkStart[iLink], dBlend);
            }
            pgraphics->set(m_pfontLink);
            const ::int_size & size = pgraphics->get_text_extent(strFinal.left(m_iaLinkStart[iLink]));

            embossed_text_out(pgraphics, strFinal.substr(m_iaLinkStart[iLink]), rectangleTextOut.left() + size.cx(), rectangleTextOut.top(), 0, m_cr, m_colorOutline, m_iaLinkEnd[iLink] - m_iaLinkStart[iLink] + 1, dBlend);
            iChar = m_iaLinkEnd[iLink] + 1;
            iLink++;
         }
         if (GetSelection().m_iCharStartSource >= 0)
         {
            ::collection::index iStart;
            ::collection::index iLineStart;
            ::collection::index iLineEnd;
            character_count iCharStart;
            character_count iCharEnd;
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
            ::collection::index iEnd;
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
               
               ::int_rectangle rectanglePlacement;
               
               GetPlacement(&rectanglePlacement);
               
               ::int_rectangle rectangle = rectanglePlacement;
               int_size size1 = pgraphics->get_text_extent(strFinal.left(iStart));
               int_size size2 = pgraphics->get_text_extent(strFinal.left(iEnd + 1));
               rectangle.left() = rectanglePlacement.left() + size1.cx();
               rectangle.right() = rectanglePlacement.left() + size2.cx();
               ::image::image_pointer pimage;
               if (rectangle.area() > 0)
               {
                  pimage = image()->create_image(rectangle.size());
                  pimage->clear(::color::white);
                  pimage->get_graphics()->set_alpha_mode(::draw2d::e_alpha_mode_blend);
                  pgraphics->flush();

                  //const ::int_point & point = pgraphics->get_origin();
                  //pimage->from(nullptr, pgraphics, int_point + rectangle.top_left(), rectangle.size());

                  {

                     ::image::image_source imagesource(pgraphics, rectangle);

                     ::double_rectangle rectangleTarget(rectangle.size());

                     ::image::image_drawing_options imagedrawingoptions(rectangleTarget);

                     ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

                     pimage->g()->draw(imagedrawing);

                  }

                  //pimage->get_graphics()->fill_rectangle(0, 0, 16, 16, argb(255, 255, 0, 255));
                  pimage->invert();
                  //pimage->fill_channel(0, ::color::e_channel_blue);
                  pimage->fill_channel(255, ::color::e_channel_opacity);

                  {

                     ::image::image_source imagesource(pimage);

                     double_rectangle rectangleTarget(rectangle);

                     ::image::image_drawing_options imagedrawingoptions(rectangleTarget);

                     ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

                     pgraphics->draw(imagedrawing);

                  }

               }

            }

         }

      }

   }
   break;
   case AnimateRHL:
   {
      int iLeft = m_iaPosition.element_at(0);
      int iLeftDiff = 0;
      int iLastLeftDiff = 0;
      int i;
      for (i = 0; i < m_iaPosition.get_size(); i++)
      {
         iLastLeftDiff = iLeftDiff;
         iLeftDiff = m_iaPosition.element_at(i) - iLeft;
         if ((int)m_dAnimateProgress <= iLeftDiff)
         {
            //i--;
            break;
         }
      }

      ::draw2d::region_pointer prgn(this);

      string strFinal(m_str);
      string strLeft = strFinal.right(strFinal.length() - i);
      
      int iLeftOffset;
      
      iLeftOffset = iLastLeftDiff - (int)m_dAnimateProgress;
      
      ::int_rectangle rectangleTextOut;
      
      GetPlacement(&rectangleTextOut);
      
      rectangleTextOut.left() += iLeftOffset;
      
      if (bDraw)
      {
         
         embossed_text_out(pgraphics, strLeft, rectangleTextOut.left(), rectangleTextOut.top(),
                         0,
                         m_cr,
                         m_colorOutline,
                         strFinal.length(),
                         dBlend);
         
      }
      int iMaxCounter = maximum((int)m_iaPosition.element_at(m_str.length()) - m_iaPosition.element_at(0) + 100, m_rectangle.right() - m_rectangle.left());
      int iRight = iMaxCounter - (int)m_dAnimateProgress;
      if (iRight < m_rectangle.right())
      {
         int iRightEnd;
         int i;
         for (i = 0; i < m_iaPosition.get_size(); i++)
         {
            iRightEnd = iRight + m_iaPosition.element_at(i) - iLeft;
            if (iRightEnd >= m_rectangle.right())
            {
               break;
            }
         }
         string strRight = strFinal.left(i);
         rectangleTextOut.left() = iRight;
         if (bDraw)
         {
            embossed_text_out(pgraphics, strRight, rectangleTextOut.left(), rectangleTextOut.top(), 0, m_cr, m_colorOutline, strFinal.length(), dBlend);
         }
      }

      if (rectaModified.has_element())
      {
         ::int_rectangle baserect;
         prgn->get_bounding_box(baserect);
         rectaModified.add(baserect);

      }
   }
   break;
   default:
      ASSERT(false);
   }

   return true;

}


bool xfplayer_impact_line::_001OnDraw(::draw2d::graphics_pointer & pgraphics, bool bDraw, const ::int_rectangle & rectangle, int_rectangle_array_base & rectaModified, ::collection::count * count, bool bRecalcLayout, ::color::color crColor, ::draw2d::pen_pointer sppen)
{

   _synchronous_lock synchronouslock(m_pContainer->synchronization());

   ::int_rectangle rectanglePlacement;

   GetPlacement(&rectanglePlacement);

   pgraphics->set(m_pfont);

   //   pgraphics->SetBkMode(TRANSPARENT);

   int_point iMargin;
   {
      iMargin.x() = (int)(sppen->m_dWidth / 2.0);
      iMargin.y() = (int)(sppen->m_dWidth / 2.0);
   }

   if (!IsVisible())
   {

      ::int_rectangle rectangle(m_rectangleInvalidate);

      if (rectaModified.has_element())
      {
         ::int_rectangle baserect(rectangle);
         rectaModified.add(baserect);
      }

      Validate(rectangle);

      return true;
   }

   if (bRecalcLayout)
   {

      CalcCharsPositions(pgraphics, rectangle);

      pgraphics->set(m_pfont);

   }

   switch (m_iAnimateType)
   {
   case AnimateNoAnimate:
   {
      string strFinal;
      strFinal = m_str;
      pgraphics->set(sppen);

      auto pbrushText = øcreate < ::draw2d::brush > ();

      pbrushText->create_solid(

      crColor);

      pgraphics->set(pbrushText);

      //pgraphics->set_text_color(crColor);

      ::int_rectangle rectangleTextOut;
      
      GetPlacement(&rectangleTextOut);
      
      if (bDraw)
      {
         
         pgraphics->_DrawText(
         strFinal,
         rectangleTextOut,
         e_align_bottom_left);
         
      }
      
   }
   break;
   case AnimateRHL:
   {
      if (m_iaPosition.get_size() <= 0)
         break;
      //         int iLeft = m_iaPosition.element_at(0);
      int iLeftDiff = 0;
      //int iLastLeftDiff = 0;
      int i = 0;
      /*            for(int i = 0; i < m_iaPosition.get_size(); i++)
                  {
                      iLastLeftDiff = iLeftDiff;
                      iLeftDiff = m_iaPosition.element_at(i) - iLeft;
                      if(iLeftDiff >= (int) m_dAnimateProgress)
                      {
                          break;
                      }
                  }*/

      string strFinal(m_str);
      string strLeft = strFinal.right(strFinal.length() - i);
      int iLeftOffset;
      iLeftOffset = iLeftDiff - (int)m_dAnimateProgress;

      pgraphics->set(sppen);
      auto pbrushText = øcreate < ::draw2d::brush > ();

      pbrushText->create_solid(crColor);

      pgraphics->set(pbrushText);

      pgraphics->set(m_pfont);
      
      ::int_rectangle rectangleTextOut;
      
      GetPlacement(&rectangleTextOut);
      
      rectangleTextOut.left() += iLeftOffset;
      if (bDraw)
      {
         
         pgraphics->_DrawText(strLeft, rectangleTextOut, e_align_bottom_left);

      }
      /*           pFont->TextOutEx(
                      pdcForeground,
                    rectangleTextOut,
                  1.0,
                  rectangleTextOut.height(),
                    strLeft,
                    m_iaPosition.get_data(),
                      m_iaPosition.get_size(),
                    0,
                      MapToFontEffect(m_iTextEffect));   */
      int iSpacing = 100;
      int iMaxCounter = maximum(
                            (int)m_iaPosition.element_at(m_str.length())
                            - m_iaPosition.element_at(0) + iSpacing, m_rectangle.right() - m_rectangle.left());
      int iRight = iMaxCounter - (int)m_dAnimateProgress;
      if (iRight < m_rectangle.right())
      {
         /*    int iRightEnd;
             for(int i = 0; i < m_iaPosition.get_size(); i++)
             {
                 iRightEnd = iRight + m_iaPosition.element_at(i) - iLeft;
                 if(iRightEnd >= m_rectangle.right())
                 {
                     break;
                 }
             }*/
         //string strRight = strFinal.left(i);
         string strRight = strFinal;
         rectangleTextOut.left() = iRight;
         if (bDraw)
         {

            pgraphics->_DrawText(strRight, rectangleTextOut, e_align_bottom_left);

         }
         /*               pFont->TextOutEx(
                             pdcForeground,
                           rectangleTextOut,
                        1.0,
                        rectangleTextOut.height(),
                           strRight,
                           m_iaPosition.get_data(),
                             m_iaPosition.get_size(),
                           0,
                             MapToFontEffect(m_iTextEffect));   */
      }

   }
   break;
   default:
      ASSERT(false);
   }

   return true;

}



/*void xfplayer_impact_line::CalcCharsPositions(
::draw2d::graphics * pdcForeground,
   ref_array <  ::write_text::font > * pFonts,
   const ::int_rectangle & rectangle)
{
   m_bCacheEmboss = false;
   //::write_text::font * pFont;
//    ::draw2d::graphics * pdcForeground = m_ptwi->TwiGetDC();
   if(m_str.length() <= 0)
      return;
   if(pFonts->get_size() > 0)
   {
      int i, nFont, iFontFound, iMaxExtent, iLeft;
      ::int_size size;
      ::int_rectangle clientRect;
      nFont = 0;
      iFontFound = -1;
      for(nFont = 0; nFont < pFonts->get_size(); nFont++)
      {
         pdcForeground->set(pFonts->get_at(nFont)->GetFont());
         GetTextExtentPoint32W(
            pdcForeground->get_os_data(),
            m_str,
            m_str.length(),
            &size);
         if((m_iAlign & AlignLeft) > 0)
         {
            if(size.cx() + m_rectangle.left() <= rectangle.right())

            {
               iFontFound = nFont;
               break;
            }
         }
         else if((m_iAlign & AlignRight) > 0)
         {
            if(m_rectangle.right() - size.cx() >= 0)
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
         m_iaPosition[0] = m_rectangle.left() + m_iIndent;
         for(i = 1; i <= m_str.length(); i++)
         {
            GetTextExtentPoint32W(
               pdcForeground->get_os_data(),
               m_str,
               i,
               &size);
            m_iaPosition[i] = size.cx() + m_rectangle.left()  + m_iIndent;
         }
         if(m_bAutoSizeX)
         {
            m_rectangle.right() = m_rectangle.left()  + m_iIndent + size.cx();
            }
         if(m_bAutoSizeY)
         {
            m_rectangle.bottom() = m_rectangle.top() + size.cy();
         }
      }
      else if(m_iAlign == AlignRight)
      {
         GetTextExtentPoint32W(
            pdcForeground->get_os_data(),
            m_str,
            m_str.length(),
            &size);
         iMaxExtent = size.cx();
         iLeft = m_rectangle.right() - iMaxExtent;
         m_iaPosition[0] = iLeft;
         for(i = 1; i <= m_str.length(); i++)
         {
            GetTextExtentPoint32W(
               pdcForeground->get_os_data(),
               m_str,
               i,
               &size);
            m_iaPosition[i] = size.cx() + iLeft;
         }
         if(m_bAutoSizeX)
         {
            m_rectangle.left() = m_rectangle.right() - size.cx();
            }
            if(m_bAutoSizeY)
            {
            m_rectangle.bottom() = m_rectangle.top() + size.cy();
         }
      }

   }

   else
   {
      int i; //, width;
      ::int_size size;
         m_iaPosition[0] = m_rectangle.left();
         for(i = 1; i <= m_str.length(); i++)
         {
            GetTextExtentPoint32W(
               pdcForeground->get_os_data(),
               m_str,
               i ,
               &size);
            m_iaPosition[i] = m_rectangle.left() + size.cx();
         }
      if(m_bAutoSizeX)
      {
         m_rectangle.right() = m_rectangle.left() + size.cx();
        }
      if(m_bAutoSizeY)
      {
         m_rectangle.bottom() = m_rectangle.top() + size.cy();
      }
   }
//    m_ptwi->TwiReleaseDC(pdcForeground);

}*/


void xfplayer_impact_line::CalcCharsPositions(::draw2d::graphics_pointer & pgraphics, const ::int_rectangle & rectangle)

{

   _synchronous_lock synchronouslock(m_pContainer->synchronization());

   m_bCacheEmboss = false;

   if (m_str.length() <= 0)
   {

      return;

   }

   int i;
   
   ::double_size size;
   
   ::int_rectangle rectangleX(rectangle);

   m_rectangleX = rectangleX;
   
   ::int_rectangle rectanglePlacement;
   
   GetPlacement(&rectanglePlacement);

   string strMain = m_str;

   m_pfont->m_dFontWidth = 1.0;

   m_pfont->set_modified();

   pgraphics->set(m_pfont);

   size = pgraphics->get_text_extent(strMain);

   if ((size.cx() * 1.2) > rectangleX.width())
   {

      m_fRateX = (double) rectangleX.width() / ((double) size.cx() * 1.2);

   }
   else
   {

      m_fRateX = 1.0;

   }

   ::write_text::text_metric tm;

   pgraphics->get_text_metrics(&tm);

   m_pfont->m_dFontWidth = m_fRateX;

   m_pfont->set_modified();

   if (m_straLink.get_size() > 0)
   {
      
      *m_pfontLink = *m_pfont;
      
      m_pfontLink->set_underline();
      
   }

   if (m_bColonPrefix)
   {

      øconstruct(m_pfontPrefix);

      *m_pfontPrefix = *m_pfont;

      m_pfontPrefix->m_fontsize *= 0.5;


   }

   m_str.truncate(minimum(100, m_str.length()));

   if (m_bColonPrefix)
   {

      m_strPrefix = m_str.left(maximum(0, m_str.find_index(":")));

      m_strRoot = m_str.substr(maximum(0, m_str.find_index(":") + 1));

      m_strRoot.trim_left();

      pgraphics->set(m_pfontPrefix);

      m_iaPosition[0] = 0;
      
      for (i = 1; i <= m_strPrefix.length(); i++)
      {

         m_pgraphicsextension->get_text_extent(
                                                pgraphics,
                                                m_strPrefix(0, i),
                                                size);

         m_iaPosition.add((int) size.cx());

      }
      
      int iSize = (int) size.cx();
      
      m_pgraphicsextension->get_text_extent(
                                            pgraphics,
                                            " ",
                                            size);

      m_iaPosition.add((int) (iSize + size.cx()));
      
      pgraphics->set(m_pfont);

      for (i = 1; i <= m_strRoot.length(); i++)
      {

         m_pgraphicsextension->get_text_extent(
         pgraphics,
         m_strRoot(0, i),
         size);

         m_iaPosition.add((int) (iSize + size.cx()));

      }

   }
   else
   {

      pgraphics->set(m_pfont);

      m_iaPosition[0] = 0;

      for (i = 1; i <= m_str.length(); i++)
      {

         m_pgraphicsextension->get_text_extent(
         pgraphics,
         m_str(0, i),
         size);

         m_iaPosition[i] = (int) (size.cx());

      }

   }

   /*if(m_iAlign == AlignLeft)
   {
      m_iaPosition[0] = m_rectangle.left() + m_iIndent;
      iRight = 0;
      for(i = 1; i <= m_str.length(); i++)
      {
         GetTextExtentPoint32W(
            (HDC)pgraphics->get_os_data(),
            m_str,
            i,
            &size);
         m_iaPosition[i] = iRight = size.cx() + m_rectangle.left() + m_iIndent;
      }
      if(m_bAutoSizeX)
      {
         m_rectangle.right() = iRight;
        }
      if(m_bAutoSizeY)
      {
         m_rectangle.bottom() = m_rectangle.top() + size.cy();
      }
   }
   else if(m_iAlign == AlignRight)
   {
      GetTextExtentPoint32W(
         (HDC)pgraphics->get_os_data(),
         m_str,
         m_str.length(),
         &size);
      iMaxExtent = size.cx();
      iLeft = m_rectangle.right() - iMaxExtent;
      m_iaPosition[0] = iLeft;
      for(i = 1; i <= m_str.length(); i++)
      {
         GetTextExtentPoint32W(
            (HDC)pgraphics->get_os_data(),
            m_str,
            i,
            &size);
         m_iaPosition[i] = size.cx() + iLeft;
      }
      if(m_bAutoSizeX)
      {
         m_rectangle.left() = iLeft;
        }
      if(m_bAutoSizeY)
      {
         m_rectangle.bottom() = m_rectangle.top() + size.cy();
      }
   }
   pgraphics->set(pfontOld);*/
}

/*void xfplayer_impact_line::CalcCharsPositions(
   ::draw2d::graphics *             pdcForeground,
   ::write_text::font *     pFont,
   const int_rectangle &           int_rectangle)

{
   m_bCacheEmboss = false;
   if(m_str.length() <= 0)
      return;
    ::write_text::font * pfontOriginal = pdcForeground->get_current_font();
   pdcForeground->set(pFont->GetFont());
   int i, iLeft, iRight, iMaxExtent;
   ::int_size size;
   ::int_rectangle rectangleX(rectangle);

   m_rectangleX = rectangleX;
   ::write_text::font * pfont = pFont;
   ::draw2d::graphics_pointer & pgraphics = pdcForeground;
   ASSERT(pfont != nullptr);
   ::int_rectangle rectanglePlacement;
   GetPlacement(rectanglePlacement);
   string strMain = m_str;
   GetTextExtentPoint32W(
      (HDC)pgraphics->get_os_data(),
      strMain,
      strMain.length(),
      &size);
   pgraphics->set(pfont->GetFont());
   if(size.cx() > rectangleX.width())
   {
      m_fRateX =
         (float)
         rectangleX.width()/
         size.cx();
   }
   else
   {
      m_fRateX = 1.0;
   }

   m_pfont->delete_object();
   LOGFONTW lf;
   pfont->GetFont()->GetLogFont(&lf);
   pgraphics->set(pfont->GetFont());
   TEXTMETRICW tm;
   pgraphics->GetTextMetrics(&tm);
   lf.lfWidth = (long) (tm.tmAveCharWidth * m_fRateX - 1);
   m_pfont->CreateFontIndirect(&lf);





   pgraphics->set(m_pfont);
   if(m_iAlign == AlignLeft)
   {
      m_iaPosition[0] = m_rectangle.left() + m_iIndent;
      iRight = 0;
      for(i = 1; i <= m_str.length(); i++)
      {
         GetTextExtentPoint32W(
            pdcForeground->get_os_data(),
            m_str,
            i,
            &size);
         m_iaPosition[i] = iRight = size.cx() + m_rectangle.left() + m_iIndent;
      }
      if(m_bAutoSizeX)
      {
         m_rectangle.right() = iRight;
        }
      if(m_bAutoSizeY)
      {
         m_rectangle.bottom() = m_rectangle.top() + size.cy();
      }
   }
   else if(m_iAlign == AlignRight)
   {
      GetTextExtentPoint32W(
         pdcForeground->get_os_data(),
         m_str,
         m_str.length(),
         &size);
      iMaxExtent = size.cx();
      iLeft = m_rectangle.right() - iMaxExtent;
      m_iaPosition[0] = iLeft;
      for(i = 1; i <= m_str.length(); i++)
      {
         GetTextExtentPoint32W(
            pdcForeground->get_os_data(),
            m_str,
            i,
            &size);
         m_iaPosition[i] = size.cx() + iLeft;
      }
      if(m_bAutoSizeX)
      {
         m_rectangle.left() = iLeft;
        }
      if(m_bAutoSizeY)
      {
         m_rectangle.bottom() = m_rectangle.top() + size.cy();
      }
   }
   pdcForeground->set(pfontOriginal);
}*/

void xfplayer_impact_line::SetAutoSize(bool bAutoSize)
{

   _synchronous_lock synchronouslock(m_pContainer->synchronization());

   m_bAutoSizeX = bAutoSize;
   m_bAutoSizeY = bAutoSize;
}

void xfplayer_impact_line::SetAlign(int iAlign)
{

   _synchronous_lock synchronouslock(m_pContainer->synchronization());

   m_iAlign = iAlign;
}

xfplayer_impact_line & xfplayer_impact_line::operator = (const xfplayer_impact_line & src)
{
   m_pContainer = src.m_pContainer;
   m_bAutoSizeX = src.m_bAutoSizeX;
   m_bAutoSizeY = src.m_bAutoSizeY;
   m_str = src.m_str;
   m_iaPosition = src.m_iaPosition;
   m_iAlign = src.m_iAlign;
   m_rectangle.bottom() = src.m_rectangle.bottom();
   m_rectangle.left() = src.m_rectangle.left();
   m_rectangle.right() = src.m_rectangle.right();
   m_rectangle.top() = src.m_rectangle.top();
   m_lpBitmapData = src.m_lpBitmapData;
   m_nFont = src.m_nFont;
   m_iAnimateType = src.m_iAnimateType;
   m_iTextEffect = src.m_iTextEffect;
   m_dAnimateProgress = src.m_dAnimateProgress;
   m_dAnimateProgressIncrement = src.m_dAnimateProgressIncrement;
//   m_logfont = src.m_logfont;
   m_pfont = src.m_pfont;
   m_bEnhancedEmboss = src.m_bEnhancedEmboss;
   m_bCacheEmboss = false;
   m_dXfplayerImpactLineBlend = src.m_dXfplayerImpactLineBlend;
   m_iIndex = src.m_iIndex;
   return *this;
}

void xfplayer_impact_line::Show(bool bShow)
{

   _synchronous_lock synchronouslock(m_pContainer->synchronization());

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


void xfplayer_impact_line::OnTimerAnimate(::draw2d::graphics_pointer& pgraphics, int_rectangle_array_base &  rectaModified)
{

   _synchronous_lock synchronouslock(m_pContainer->synchronization());

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
            if ((int)m_dAnimateProgress > maximum(m_iaPosition.element_at(m_str.length()) - m_iaPosition.element_at(0) + 100, m_rectangle.right() - m_rectangle.left()))
               m_dAnimateProgress = 0.0;
            
            ::int_rectangle rectangle;
            
            GetPlacement(&rectangle);
            
            Invalidate();
            
            rectaModified.add(rectangle);
            
            /*to(
                pdcForeground,
                false,
                rectangle, rectaModified,
                false);*/
         }
      }
      break;
      default:
         ASSERT(false);
      }
   }
}

void xfplayer_impact_line::SetAnimateType(int iAnimateType)
{

   _synchronous_lock synchronouslock(m_pContainer->synchronization());

   m_iAnimateType = iAnimateType;
   m_dAnimateProgress = 0.0;

}

void xfplayer_impact_line::SetTextEffect(int iTextEffect)
{

   _synchronous_lock synchronouslock(m_pContainer->synchronization());

   m_iTextEffect = iTextEffect;
}

void xfplayer_impact_line::SetEmbossPen(::draw2d::pen *pPen)

{

   _synchronous_lock synchronouslock(m_pContainer->synchronization());

   m_lpPenEmboss = pPen;


}

void xfplayer_impact_line::SetForegroundColor(::color32_t color32)
{

   _synchronous_lock synchronouslock(m_pContainer->synchronization());

   m_colorForeground = color32;
}

/*ref_array <  ::write_text::font > * xfplayer_impact_line::GetFonts()
{
    return &m_fonts;
}
*/
int xfplayer_impact_line::MapToFontEffect(int iLineEffect)
{

   _synchronous_lock synchronouslock(m_pContainer->synchronization());

   switch (iLineEffect)
   {
   case EffectSimple:
      return EffectSimple;
   case EffectEmbossed:
      return EffectEmbossed;
   }
   ASSERT(false);
   return -1;
}

void xfplayer_impact_line::SetAnimateIncrement(double dIncrement)
{

   _synchronous_lock synchronouslock(m_pContainer->synchronization());

   m_dAnimateProgressIncrement = dIncrement;
}

//void xfplayer_impact_line::SetRedrawMode(int iMode)
//{
//  m_iRedrawMode = iMode;
//}

//void xfplayer_impact_line::SetRenderWindow(::windowing::window * pwindow)
//{
//  m_pRenderWnd = pwindow;
//}

void xfplayer_impact_line::SetRenderCriticalSection(critical_section * pcs)
{
   __UNREFERENCED_PARAMETER(pcs);
   //    m_pcsRender =   pcs;
}

int xfplayer_impact_line::SetLyricPens(::draw2d::pen * ppenLeft, ::draw2d::pen * ppenRight)
{

   _synchronous_lock synchronouslock(m_pContainer->synchronization());

   m_ppenLyricLeft = ppenLeft;
   m_ppenLyricRight = ppenRight;
   return true;
}

int xfplayer_impact_line::SetLyricColors(::color::color colorLeft, ::color::color colorRight)
{

   _synchronous_lock synchronouslock(m_pContainer->synchronization());

   m_colorLyricLeft = colorLeft;
   m_colorLyricRight = colorRight;
   return true;

}


void xfplayer_impact_line::SetPlacement(const ::int_rectangle & rectangle)
{

   _synchronous_lock synchronouslock(m_pContainer->synchronization());

   m_rectangle = rectangle;

   m_bPendingLayoutUpdate = true;

}


//int xfplayer_impact_line::GetVmsFontCount()
/*{
   return m_fonts.get_size();
}

void xfplayer_impact_line::AddVmsFont(::write_text::font * pfont)
{
   m_fonts.add(pfont);
}*/

void xfplayer_impact_line::Invalidate(const int_rectangle & rectangleParam)
{

   _synchronous_lock synchronouslock(m_pContainer->synchronization());

   ::int_rectangle rectanglePlacement;

   GetPlacement(&rectanglePlacement);

   ::int_rectangle rectangleInvalidate;

   if (is_empty(rectangleParam))
   {

      rectangleInvalidate = rectanglePlacement;

   }
   else
   {

      rectangleInvalidate = rectangleParam;

   }

   m_rectangleInvalidate.unite(m_rectangleInvalidate, rectangleInvalidate);

   m_rectangleInvalidate.intersect(m_rectangleInvalidate, rectanglePlacement);

}


void xfplayer_impact_line::Validate(const int_rectangle & rectangleParam)
{

   _synchronous_lock synchronouslock(m_pContainer->synchronization());

   ::int_rectangle rectanglePlacement;

   GetPlacement(&rectanglePlacement);

   ::int_rectangle rectangleValidate;

   if (is_empty(rectangleParam))
   {

      rectangleValidate = rectanglePlacement;

   }
   else
   {

      rectangleValidate = rectangleParam;

   }

   m_rectangleInvalidate -= rectangleValidate;

   m_rectangleInvalidate.intersect(m_rectangleInvalidate, rectanglePlacement);

}


bool xfplayer_impact_line::IsVisible()
{

   _synchronous_lock synchronouslock(m_pContainer->synchronization());

   return m_bVisible;

}


void xfplayer_impact_line::embossed_text_out(::draw2d::graphics_pointer & pgraphics, const ::scoped_string & scopedstr, int iLeft, int iTop, int iWidth, ::color32_t color32, ::color::color crOutline, character_count iLen, double dBlend)
{

   _synchronous_lock synchronouslock(m_pContainer->synchronization());

   embossed_text_out(
   pgraphics,
   m_pimageMain,
   scopedstr,

   iLeft,
   iTop,
   iWidth,
   color32,
   crOutline,
   iLen,
   dBlend);

}


void xfplayer_impact_line::embossed_text_out(::draw2d::graphics_pointer & pgraphics, ::image::image *pimageCache, const ::scoped_string & scopedstr, int iLeft, int iTop, int iWidth, ::color32_t color32, ::color::color crOutline, character_count iLen, double dBlend)
{

   _synchronous_lock synchronouslock(m_pContainer->synchronization());

   __UNREFERENCED_PARAMETER(pimageCache);

   bool bSaveProcessing = !m_bEnhancedEmboss;

   if (bSaveProcessing)
   {

      pgraphics->begin_path();

      pgraphics->text_out(iLeft, iTop, scopedstr(0, iLen));

      pgraphics->end_path();

      ::draw2d::pen_pointer ppen;

      øconstruct(ppen);

      ppen->create_solid(iWidth * 2, crOutline);

      pgraphics->set(ppen);

      pgraphics->stroke_path();

      auto pbrushText = øcreate < ::draw2d::brush > ();

      pbrushText->create_solid(color32);

      pgraphics->set(pbrushText);

      pgraphics->text_out(iLeft, iTop, scopedstr(0, iLen));


   }
   else
   {

      if (m_bEnhancedEmboss)
      {

         if (!m_bCacheEmboss || m_strCache != scopedstr)

         {

            CacheEmboss(pgraphics, m_str, m_pimageMain);

         }

      }

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      ::int_point point;

      point.x() = (int) (iLeft - ((maximum(2.0, m_fRateX * 8.0)) / 2));

      point.y() = (int) (iTop - ((maximum(2.0, m_fRateX * 8.0)) / 2));

      {

         ::image::image_source imagesource(m_pimageMain);

         double_rectangle rectangleTarget(point, m_pimageMain->get_size());

         ::image::image_drawing_options imagedrawingoptions(rectangleTarget);

         imagedrawingoptions.opacity(dBlend);

         ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

         pgraphics->draw(imagedrawing);

      }

      if (m_bColonPrefix)
      {

         pgraphics->set(m_pfontPrefix);

         ::int_size size;

         size = pgraphics->get_text_extent(m_strPrefix);

        /* auto psystem = system();

         psystem->*/imaging()->AlphaTextOut(pgraphics, iLeft, iTop + m_rectangle.height() - size.cy(), m_strPrefix, color32, dBlend);

         pgraphics->set(m_pfont);

         int iOffset;

         if (m_strPrefix.length() <= 0)
         {

            iOffset = 0;

         }
         else
         {

            iOffset = (int) (size.cx() + size.cx() / m_strPrefix.length());

         }

         imaging()->AlphaTextOut(pgraphics, iLeft + iOffset, iTop, m_strRoot, color32, dBlend);



      }
      else
      {

         pgraphics->set(m_pfont);

         /*auto psystem = system();

         psystem->*/imaging()->AlphaTextOut(pgraphics, iLeft, iTop, scopedstr, color32, dBlend);


      }


   }


}



void xfplayer_impact_line::SetColors(::color32_t color32, ::color::color crOutline)
{

   _synchronous_lock synchronouslock(m_pContainer->synchronization());

   m_cr = color32;
   m_colorOutline = crOutline;
}


//#ifdef WINDOWS_DESKTOP
//
//
//void xfplayer_impact_line::GetLogFont(LOGFONTW &lf)
//{
//
//   _synchronous_lock synchronouslock(m_pContainer->mutex());
//
//   //lf = m_logfont;
//}
//
//
//#endif


void xfplayer_impact_line::CacheEmboss(::draw2d::graphics_pointer & pgraphics, const ::scoped_string & scopedstr, ::image::image_pointer & pimageCache)
{

   _synchronous_lock synchronouslock(m_pContainer->synchronization());

   if (!m_bEnhancedEmboss)
   {

      return;

   }

   if (m_bCacheEmboss && m_strCache == scopedstr)
   {

      return;

   }

   m_strCache = scopedstr;

   m_bCacheEmboss = true;

   //informationf("CLyricImpactLine::CacheEmboss: %s\n", pcsz);

   ::double_size size;

   pgraphics->set(m_pfont);

   m_pgraphicsextension->get_text_extent(pgraphics, scopedstr, size);

   size.cx() += (int)(2 * (maximum(2.0, m_fRateX * 8.0)));
   
   size.cy() += (int)(2 * (maximum(2.0, m_fRateX * 8.0)));

   pimageCache = image()->create_image(size);

   if (!pimageCache)
   {
      
      return;
      
   }

   pimageCache->clear(::color::transparent);

   ::draw2d::graphics_pointer pdcCache = pimageCache->get_graphics();

   pdcCache->set(m_pfont);

   pdcCache->set_alpha_mode(::draw2d::e_alpha_mode_set);

   pdcCache->set_alpha_mode(::draw2d::e_alpha_mode_blend);

   draw2d::brush_pointer pbrushText(e_create, this);

   pbrushText->create_solid(argb(96, 96, 96, 96));

   pdcCache->set(pbrushText);

   ::double_size s;

   if (m_bColonPrefix)
   {

      pdcCache->set(m_pfontPrefix);
      
      const ::int_size & size = pdcCache->get_text_extent(m_strPrefix);
      
      m_pgraphicsextension->text_out(pdcCache, (int)(int)((maximum(2.0, m_fRateX * 4.0)) / 2), (int)1 * (int)((maximum(2.0, m_fRateX * 4.0)) / 2) + m_rectangle.height() - size.cy(), m_strPrefix, s);
      
      pdcCache->set(m_pfont);

      int x = (int) (s.cx() + (s.cx() / m_strPrefix.length()) + (int)(int)((maximum(2.0, m_fRateX * 8.0)) / 2));

      int y = (int) (1 * (int)((maximum(2.0, m_fRateX * 8.0)) / 2));

      m_pgraphicsextension->text_out(pdcCache, x, y, m_strRoot, s);

   }
   else
   {

      m_pgraphicsextension->text_out(pdcCache, (int)(int)((maximum(2.0, m_fRateX * 8.0)) / 2), (int)1 * (int)((maximum(2.0, m_fRateX * 8.0)) / 2), scopedstr, s);

   }

   auto psystem = system();

   imaging()->channel_spread_set_color(pdcCache, {}, size, pdcCache, {}, 0, int(maximum(1.0, m_fRateX * 2.0 + 2)), argb(23, 23, 20, 23));

   pdcCache->set_alpha_mode(::draw2d::e_alpha_mode_blend);
   imaging()->channel_alpha_gray_blur(pdcCache, {}, size, pdcCache, {}, 0, int(maximum(1.0, m_fRateX * 2.5)));
   imaging()->channel_alpha_gray_blur(pdcCache, {}, size, pdcCache, {}, 0, int(maximum(1.0, m_fRateX * 2.5)));

   pimageCache->clear(::color::transparent);

}


void xfplayer_impact_line::SetFont(::write_text::font * pfont)
{

   _synchronous_lock synchronouslock(m_pContainer->synchronization());

   m_pfont = pfont;

}


void xfplayer_impact_line::PrepareURLLinks()
{

   _synchronous_lock synchronouslock(m_pContainer->synchronization());

   string str;

   auto psystem = system();

   auto pregex = psystem->compile_pcre("/^|\\s|([;\"()]+))(((((http|https)://))|(www\\.))[0-9a-zA-Z./\\-_?=]+)(([;\"()]+)|\\s|$/");

   auto ptopic = pregex->run(m_str);

   auto & rangea = ptopic->get_range_array();

   for(auto & range : rangea)
   {

      m_straLink.add(m_str.substr(range.begin(), range.count()));
      m_iaLinkStart.add(range.begin());
      m_iaLinkEnd.add(range.upper_bound());

   }


}

bool xfplayer_impact_line::CharHasLink(character_count iChar)
{

   _synchronous_lock synchronouslock(m_pContainer->synchronization());

   return GetCharLink(iChar) > -1;
}

bool xfplayer_impact_line::GetCharLink(string & str, character_count iChar)
{

   _synchronous_lock synchronouslock(m_pContainer->synchronization());

   ::collection::index iLink = GetCharLink(iChar);
   if (iLink < 0)
      return false;
   str = m_straLink[iLink];
   return true;
}

::user::enum_line_hit xfplayer_impact_line::get_link(string & strUrl, const ::int_point & pointCursor)
{

   _synchronous_lock synchronouslock(m_pContainer->synchronization());

   character_count iChar;
   ::user::enum_line_hit etest = hit_test(pointCursor, iChar);
   if (etest == ::user::e_line_hit_link)
   {
      GetCharLink(strUrl, iChar);
   }
   return etest;
}

::collection::index xfplayer_impact_line::GetCharLink(character_count iChar)
{

   _synchronous_lock synchronouslock(m_pContainer->synchronization());

   for (::collection::index i = 0; i < m_iaLinkStart.get_size(); i++)
   {
      if (iChar >= m_iaLinkStart[i] &&
            iChar <= m_iaLinkEnd[i])
      {
         return i;
      }
   }
   return -1;
}

::user::enum_line_hit xfplayer_impact_line::hit_test(const int_point &pointCursorParam, character_count &iChar)
{

   _synchronous_lock synchronouslock(m_pContainer->synchronization());

   bool bInside;
   
   const ::int_point & pointCursor = pointCursorParam;
   
   ::int_rectangle rectanglePlacement;
   
   GetPlacement(&rectanglePlacement);
   
   bInside = rectanglePlacement.contains(pointCursor) != 0;
   
   if (!bInside)
   {
      
      iChar = -1;
      
      return ::user::e_line_hit_none;
      
   }
   else
   {
      
      if (CalcChar(pointCursor, iChar))
      {
         
         if (CharHasLink(iChar))
         {
            
            return ::user::e_line_hit_link;
            
         }
         else
         {
            
            return ::user::e_line_hit_normal;
            
         }
         
      }
      else
      {
         
         iChar = -1;
         
         return ::user::e_line_hit_none;
         
      }
      
   }

}


bool xfplayer_impact_line::CalcChar(const ::int_point & point, character_count &iChar)
{

   _synchronous_lock synchronouslock(m_pContainer->synchronization());

   ::int_rectangle rectanglePlacement;
   
   GetPlacement(&rectanglePlacement);
   
   bool bInside = rectanglePlacement.contains(point) != 0;
   
   if (!bInside)
   {
      
      return false;
      
   }

   int x = point.x() - rectanglePlacement.left();

   for (int i = 0; i < m_iaPosition.get_size() - 1; i++)
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


void xfplayer_impact_line::OnMouseMove(::message::message * pmessage)
{

   _synchronous_lock synchronouslock(m_pContainer->synchronization());

   auto pmouse = pmessage->m_union.m_pmouse;

   character_count iChar;

   auto point = pmouse->m_pointHost;

   m_pContainer->m_puserinteraction->host_to_client()(point);

   if (CalcChar(point, iChar))
   {

      if (CharHasLink(iChar))
      {

         auto pwindowing = m_puserinteraction->windowing();

         auto pcursor = pwindowing->get_cursor(e_cursor_hand);

         m_pContainer->m_puserinteraction->user_mouse_set_cursor(pmouse, pcursor);

      }

   }


   /*
   lyric_impact_line_selection & selection = GetSelection();

   if(selection.GetState() == lyric_impact_line_selection::StateTracking)
   {

      bool bInside;
      int iToken;
      int iChar;
      ::int_rectangle rectanglePlacement;

      GetPlacement(rectanglePlacement);
      bInside = rectanglePlacement.contains(point) != 0;

      if(!bInside)
      {
         if(point.y() < rectanglePlacement.top()
            || (point.y() <= rectanglePlacement.bottom() &&
            point.x() < rectanglePlacement.left()))
         {
            selection.SetSelBefore(*this);
            GetWndRender()->Redraw(rectanglePlacement);
         }
         else
         {
            selection.SetSelAfter(*this);
            GetWndRender()->Redraw(rectanglePlacement);
         }
         return false;
      }
      else // bInside == true
      {
         unsigned int fwKeys = user; // key flags
         if(m_tokenaMain.get_size() <= 0)
            return false;
         if(CalcChar(point, iToken, iChar))
         {
            selection.m_item.SetTokenEnd(iToken);
            selection.m_item.SetCharEnd(iChar);
            GetWndRender()->Redraw(rectanglePlacement);
         }
         else
         {
            if(point.x() < m_tokenaMain.element_at(0).get_position())
            {
               selection.SetSelBefore(*this);
            }
            else
            {
               selection.SetSelAfter(*this);
            }
            GetWndRender()->Redraw(rectanglePlacement);
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
         ::int_rectangle rectanglePlacement;

         GetPlacement(rectanglePlacement);
         bInside = rectanglePlacement.contains(point);
         if(bInside)
         {
            update_hover(point);
         }
      }

   }*/

   //auto point = pmouse->m_pointHost;

   //m_pContainer->m_puserinteraction->host_to_client()(point);

   if (GetSelection().OnMouseMove(*this, pmouse->m_ebuttonstate, point))
   {

      pmouse->m_bRet = true;

      pmouse->m_lresult = 1;

   }

}


void xfplayer_impact_line::OnSetCursor(::message::message * pmessage)
{

   __UNREFERENCED_PARAMETER(pmessage);

   //if(is_hover())
   //{
   //
   //    pmouse->m_ecursor = cursor_hand;
   //
   //    return true;
   //
   //}

}


void xfplayer_impact_line::OnLButtonDown(::message::message * pmessage)
{

   _synchronous_lock synchronouslock(m_pContainer->synchronization());

   auto pmouse = pmessage->m_union.m_pmouse;

   auto point = pmouse->m_pointHost;

   m_pContainer->m_puserinteraction->host_to_client()(point);

   if (GetSelection().OnLButtonDown(*this, pmouse->m_ebuttonstate, point))
   {

      pmouse->m_bRet = true;

      pmouse->m_lresult = 1;

   }

}


void xfplayer_impact_line::OnLButtonUp(::message::message * pmessage)
{

   _synchronous_lock synchronouslock(m_pContainer->synchronization());

   auto pmouse = pmessage->m_union.m_pmouse;

   character_count iChar;

   auto point = pmouse->m_pointHost;

   m_pContainer->m_puserinteraction->host_to_client()(point);

   if (CalcChar(point, iChar))
   {

      if (CharHasLink(iChar))
      {

         string str;

         str = m_straLink[GetCharLink(iChar)];

         ASSERT(m_puserinteraction->is_window());

         auto phyperlink = øcreate_new < ::hyperlink >();

         phyperlink->m_strLink = str;

         phyperlink->run();

      }

   }

   if (GetSelection().OnLButtonUp(*this, pmouse->m_ebuttonstate, point))
   {

      pmouse->m_bRet = true;

      pmouse->m_lresult = 1;

   }

}


void xfplayer_impact_line::on_timer(::timer * ptimer)
{

   __UNREFERENCED_PARAMETER(ptimer);

   //if(GetSelection().OnTimer(*this, user))
   //{
   //
   //    return true;
   //
   //}

}


::write_text::font * xfplayer_impact_line::GetFont()
{

   _synchronous_lock synchronouslock(m_pContainer->synchronization());

   return m_pfont;

}


void xfplayer_impact_line::set_blend(double d)
{

   _synchronous_lock synchronouslock(m_pContainer->synchronization());

   ASSERT(d >= 0.0);

   ASSERT(d <= 1.0);

   if (d < 0.0 || d > 1.0)
   {

      return;

   }

   m_dXfplayerImpactLineBlend = d;

}


void xfplayer_impact_line::update_hover(int_point &pointCursor)
{

   _synchronous_lock synchronouslock(m_pContainer->synchronization());

   ::collection::index iLine = m_iIndex;

   character_count iChar;

   ::user::enum_line_hit etest = hit_test(pointCursor, iChar);

   if (etest == ::user::e_line_hit_link)
   {

      if (m_iLinkHoverIndex != GetLinkIndex(iLine, iChar))
      {

         m_iLinkHoverIndex = GetLinkIndex(iLine, iChar);

         ::int_rectangle rectangle;

         GetPlacement(&rectangle);

         get_interaction()->set_need_redraw();

      }

   }
   else
   {

      if (m_iLinkHoverIndex != -1)
      {

         m_iLinkHoverIndex = -1;

         ::int_rectangle rectangle;

         GetPlacement(&rectangle);

         get_interaction()->set_need_redraw();

      }

   }

}


bool xfplayer_impact_line::is_hover()
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


::collection::index xfplayer_impact_line::GetLinkIndex(::collection::index iLine, character_count iChar)
{

   _synchronous_lock synchronouslock(m_pContainer->synchronization());

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


bool xfplayer_impact_line::has_link()
{

   _synchronous_lock synchronouslock(m_pContainer->synchronization());

   return m_iaLinkStart.get_count() > 0;

}


::user::interaction * xfplayer_impact_line::get_interaction()
{

   return m_pContainer->m_puserinteraction;

}


inline xfplayer_impact_line_selection & xfplayer_impact_line::GetSelection()
{

   _synchronous_lock synchronouslock(m_pContainer->synchronization());

   if (m_pContainer == nullptr)
   {

      return *m_pselection;

   }

   return m_pContainer->GetSelection();

}



