#include "framework.h"
#include "_impl.h"


namespace html
{


   namespace impl
   {


      text::text()
      {

         m_pedit                             = nullptr;

         m_bLink                             = false;

         m_bOnAfterChangeText                = false;

      }


      void text::delete_implementation(html_data * pdocument)
      {

         m_bLink = false;

      }


      void text::implement_phase1(html_data * pdata, ::html::element * pelement)
      {

         sync_lock lock(pdata->m_pcoredata->mutex());

         ::html::impl::element::implement_phase1(pdata, pelement);

         e_tag etag = m_pelemental->m_etag;

         if(etag == tag_a)
         {

            m_bLink = true;

            if(m_strLink.is_empty())
            {

               if(!pelement->m_pparent->m_propertyset.is_new_or_null("href"))
               {

                  m_strLink = pelement->m_pparent->m_propertyset["href"];

               }
               else if(!pelement->m_propertyset.is_new_or_null("href"))
               {

                  m_strLink = pelement->m_propertyset["href"];

               }

            }

         }

         if((!::is_set(m_pedit) || !m_pedit->is_window()) && pdata->m_pcoredata->m_bEdit)
         {

            m_pedit = __new(::user::plain_edit);

            m_pedit->initialize(pdata);

            m_pedit->m_pform = pdata->m_pcoredata->m_pform;

            m_pedit->m_bSendEnterKey = true;

            m_pedit->create_window(pdata->m_pcoredata->m_pform, 1004);

            m_pedit->m_pform = pdata->m_pcoredata->m_pform;

         }

         if (pelement->m_elementalptra.get_size() > 0 || pelement->m_strBody.is_empty())
         {

            return;

         }

         ::draw2d::graphics_pointer & pgraphics = pdata->m_pcoredata->m_pgraphics;

         if(pgraphics == nullptr)
         {

            return;

         }

         font * pfont = pdata->get_font(m_pelemental);

         if(pfont != nullptr)
         {

            pgraphics->set(pfont->m_font);

         }

         string str = m_pelemental->m_strBody;

         if(::is_set(m_pedit) && m_pedit->is_window() && pdata->m_pcoredata->m_bEdit)
         {

            m_pedit->_001SetText(str, ::action_context(::e_source_data) +  ::e_source_load);

         }

         str.trim();

         if (str.has_char())
         {

            m_bHasChar = true;

         }

      }


      void text::layout_phase0(html_data * pdata)
      {

         sync_lock lock(pdata->m_pcoredata->mutex());

         ::html::impl::element::layout_phase0(pdata);

         if (m_pelemental->m_elementalptra.get_size() > 0 || m_pelemental->m_strBody.is_empty())
         {

            return;

         }

//         e_tag etag = m_pelemental->m_etag;

         ::draw2d::graphics_pointer & pgraphics = pdata->m_pcoredata->m_pgraphics;

         if (pgraphics == nullptr)
            return;

         font * pfont = pdata->get_font(m_pelemental);

         if (pfont != nullptr)
         {

            pgraphics->set(pfont->m_font);

         }

         string str = m_pelemental->m_strBody;

         string strMax = str;

         if (!pdata->m_pcoredata->m_bHasChar)
         {

            strMax.trim_left();

         }

         ::sizef size = pgraphics->GetTextExtent(strMax);

         m_cxMax = (float) size.cx;

         strsize iLastSpace = 0;

         uchar uch;

         i32 iSpace = 0;

         string strLine;

         for (i32 i = 0; i < str.get_length();)
         {

            iSpace = 0;

            uch = (uchar)str[i];

            while (i < str.get_length())
            {

               uch = (uchar)str[i];

               if (!isspace(uch))
                  break;

               iSpace++;

               if (iSpace == 1)
               {

                  if (pdata->m_pcoredata->m_bHasChar || strLine.get_length() > 0)
                  {

                     strLine += " ";

                     iLastSpace = strLine.get_length();

                  }

               }

               i++;

            }

            if (strLine.get_length() > 0)
            {

               m_straWordSpace.add(strLine);

               strLine.Empty();

            }

            while (i < str.get_length())
            {

               uch = (uchar)str[i];

               if (isspace(uch))
                  break;

               strLine += str[i];

               i++;

            }

            if (strLine.get_length() > 0)
            {

               m_straWordSpace.add(strLine);

               strLine.Empty();

            }

         }

         m_cxMin = 0;

         for (i32 i = 0; i < m_straWordSpace.get_size(); i++)
         {

            uch = (uchar)m_straWordSpace[i][0];

            if (!isspace(uch))
            {

               size = pgraphics->GetTextExtent(m_straWordSpace[i]);

               if (size.cx > m_cxMin)
               {

                  m_cxMin = (float)size.cx;

               }

            }

         }

         str.trim();

         if (str.has_char())
         {

            m_bHasChar = true;

            pdata->m_pcoredata->m_bHasChar = true;

         }

      }


      bool text::layout_phase1(html_data * pdata)
      {

         ::html::impl::element::layout_phase1(pdata);

         e_tag etag = m_pelemental->m_etag;

         if (etag == tag_br)
         {

            ::draw2d::graphics_pointer & pgraphics = pdata->m_pcoredata->m_pgraphics;

            if (pgraphics == nullptr)
            {

               return false;

            }

            if (pdata->m_pcoredata->m_layoutstate1.m_cy <= 0)
            {

               pgraphics->set(pdata->get_font(m_pelemental)->m_font);

               m_box.set_width(0);

               ::draw2d::text_metric textmetric;

               pgraphics->get_text_metrics(&textmetric);

               double dLineSpacing = textmetric.get_line_spacing();

               pdata->m_pcoredata->m_layoutstate1.m_cy = (float) dLineSpacing;

               pdata->m_pcoredata->m_layoutstate1.m_cya.last() = (float) dLineSpacing;

               m_box.set_height((float) dLineSpacing);

            }

            m_box.set_height((float)pdata->m_pcoredata->m_layoutstate1.m_cy);

            return true;

         }


         if (m_pelemental->m_elementalptra.get_size() > 0 || m_pelemental->m_strBody.trimmed().is_empty())
            return false;

         if (etag == tag_table
               || etag == tag_tbody
               || etag == tag_tr)
            return false;

         ::draw2d::graphics_pointer & pgraphics = pdata->m_pcoredata->m_pgraphics;

         if (pgraphics == nullptr)
            return false;

         pgraphics->set(pdata->get_font(m_pelemental)->m_font);

         string str = m_pelemental->m_strBody;

         str.trim();



         m_straLines.remove_all();

         m_sizea.remove_all();

         ::sizef sizeText;

         i32 iSpace;

         string strLine;

         uchar uch;

         strsize iLastSpace = 0;

         auto pointBound = top_left();

         pointBound.x += m_margin.left + m_border.left + m_padding.left;

         float x = pointBound.x;

         ::sizef sizeContent = ::sizef(get_bound_size());

         sizeContent.cx = max(0.f, sizeContent.cx - m_padding.left - m_padding.right - m_border.left - m_border.right - m_margin.left - m_margin.right);

         sizeContent.cy = max(0.f, sizeContent.cy - m_padding.top - m_padding.bottom - m_border.top - m_border.bottom - m_margin.top - m_margin.bottom);

         for (i32 i = 0; i < str.get_length();)
         {

            iSpace = 0;

            uch = (uchar)str[i];

            while (i < str.get_length())
            {

               uch = (uchar)str[i];

               if (!isspace(uch))
                  break;

               iSpace++;

               if (iSpace == 1)
               {

                  if (strLine.get_length() > 0 || pdata->m_pcoredata->m_layoutstate1.m_bHasChar)
                  {

                     strLine += " ";

                     iLastSpace = strLine.get_length();

                  }

               }

               i++;

            }

            while (i < str.get_length())
            {

               uch = (uchar)str[i];

               if (isspace(uch))
                  break;

               strLine += str[i];

               i++;

            }

            sizeText = pgraphics->GetTextExtent(strLine);

            if ((x + sizeText.cx) > pointBound.x + sizeContent.cx)
            {

               if (x > pointBound.x && iLastSpace == 0)
               {

                  m_straLines.add("");

                  sizeText.cx = 0;

               }
               else if (iLastSpace > 0)
               {

                  sizeText = pgraphics->GetTextExtent(strLine.Left(iLastSpace));

                  ::draw2d::text_metric textmetric;

                  pgraphics->get_text_metrics(&textmetric);

                  sizeText.cy = (float) textmetric.get_line_spacing();

                  m_straLines.add(strLine.Left(iLastSpace));

                  strLine = strLine.Mid(iLastSpace);

               }
               else
               {

                  m_straLines.add(strLine);

                  strLine.Empty();

               }

               m_sizea.add(::sizef(sizeText));

               iLastSpace = 0;

               x = pointBound.x;

            }

         }

         if (strLine.get_length() > 0)
         {

            sizeText = pgraphics->GetTextExtent(strLine);

            ::draw2d::text_metric textmetric;

            pgraphics->get_text_metrics(&textmetric);

            sizeText.cy = (float) textmetric.get_line_spacing();

            m_straLines.add(strLine);

            m_sizea.add(::sizef(sizeText));

         }

         if (pdata->m_pcoredata->m_bEdit && m_straLines.get_size() == 0)
         {

            m_straLines.add("");

            m_sizea.add(::sizef(0.f, 0.f));

         }

         if ((m_pelemental->m_bParent && m_pelemental->m_pparent->m_pstyle->m_edisplay != display_table_cell)
               || (!m_pelemental->m_bParent && m_pelemental->m_pstyle->m_edisplay != display_table_cell))
         {

            float cx = 0.f;

            if (m_straLines.get_size() > 1)
            {

               cx = m_sizea.last().cx;

            }
            else if (m_straLines.get_size() > 0)
            {

               cx = m_sizea[0].cx;

            }

            m_box.set_width(cx);

         }

         float cy = 0.f;

         i32 i;

         for (i = 0; i < m_sizea.get_size(); i++)
         {

            cy += m_sizea[i].cy;

         }

         if (m_pelemental->m_pparent == nullptr)
         {

            m_box.set_height(cy);

         }
         else
         {

            m_box.set_height(cy);

         }

         return true;

      }




      void text::layout_phase3(html_data * pdata)
      {

         ::html::impl::element::layout_phase3(pdata);

      }







      void text::_001OnDraw(html_data * pdata)
      {

         ::html::impl::element::_001OnDraw(pdata);

//         if(pdata->is_locked())
//         {
//
//            // I am gonna blink and fail away (deleting?) // isn't new html page ready so you just call new drawing
//            return;
//         }

         ::draw2d::graphics_pointer & pgraphics = pdata->m_pcoredata->m_pgraphics;

         //::rect rectWindow;
         //m_pcheckbox->get_window_rect(rectWindow);
         ::point pointPreviousViewportOrg = pgraphics->GetViewportOrg();

         pgraphics->OffsetViewportOrg((i32) m_box.left, (i32) m_box.top);

         if (::is_set(m_pedit) && m_pedit->is_window() && pdata->m_pcoredata->m_bEdit)
         {

            m_pedit->_000CallOnDraw(pdata->m_pcoredata->m_pgraphics);

         }
         else
         {

            pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

            auto pstyle = m_pelemental->m_pdata->m_pcoredata->m_pform->get_style(pgraphics);
            
            auto colorText = m_pelemental->get_color(pstyle, ::css::color_text);

            pgraphics->set_text_color(colorText);
            
            auto pfont = m_pelemental->get_font();

            pgraphics->set(pfont);

            ::rect rectLine;

            for (index i = 0; i < m_straLines.get_count(); i++)
            {

               string str = m_straLines[i];

               rectLine.top = rectLine.top;

               rectLine.set_size(m_sizea[i]);

               pgraphics->text_out(rectLine.left, rectLine.top, str);

            }


         }

         pgraphics->SetViewportOrg(pointPreviousViewportOrg);

         /*

         ::draw2d::graphics_pointer & pgraphics = pdata->m_pcoredata->m_pgraphics;

         color32_t crBkSel = RGB(120, 240, 150);

         color32_t crSel = RGB(10, 30, 20);

         e_tag etag = m_pelemental->m_etag;

         if(etag == tag_body)
         {

            ::rect rect;

            if(!pdata->m_pcoredata->m_bDrawFirstBody)
            {

               pdata->m_pcoredata->m_bDrawFirstBody = true;

               pdata->m_pcoredata->m_pform->get_client_rect(rect);

            }
            else
            {

               m_box.get(rect);

            }

            pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

            color32_t cr = 0;

            double d;

            if (m_pelemental->m_pstyle->get_alpha("", pdata, m_pelemental, d))
            {
               if(m_bHover && m_pelemental->m_pstyle->get_color("background-color", "hover", pdata, m_pelemental, cr))
               {
                  App(pdata->get_context_application()).imaging().color_blend(
                  pgraphics,
                  rect,
                  cr,
                  max(0, min(255, (byte)(d * 255))));
               }
               else if(has_link() && m_pelemental->m_pstyle->get_color("background-color", "link", pdata, m_pelemental, cr))
               {
                  App(pdata->get_context_application()).imaging().color_blend(
                  pgraphics,
                  rect,
                  cr,
                  max(0, min(255, (byte)(d * 255))));
               }
               else if (m_pelemental->m_pstyle->get_color("background-color", "", pdata, m_pelemental, cr))
               {
                  App(pdata->get_context_application()).imaging().color_blend(
                  pgraphics,
                  rect,
                  cr,
                  max(0, min(255, (byte)(d * 255))));
               }
            }
            else
            {
               if(m_bHover && m_pelemental->m_pstyle->get_color("background-color", "hover", pdata, m_pelemental, cr))
               {
                  pgraphics->fill_rect(rect, cr);
               }
               else if(has_link() && m_pelemental->m_pstyle->get_color("background-color", "link", pdata, m_pelemental, cr))
               {
                  pgraphics->fill_rect(rect, cr);
               }
               else if (m_pelemental->m_pstyle->get_color("background-color", "", pdata, m_pelemental, cr))
               {
                  pgraphics->fill_rect(rect, cr);
               }
            }
         }
         if(m_pelemental->m_elementalptra.get_size() > 0 || m_pelemental->m_strBody.is_empty())
            return;
//       ::draw2d::graphics_pointer & pgraphics = pgraphics;
         ::html::impl::element::_001OnDraw(pdata);


         color32_t cr = 0;
         bool bOpaque;
         color32_t crBkColor;
         if(m_bHover && m_pelemental->m_pstyle->get_color("background-color", "hover", pdata, m_pelemental, cr))
         {
            bOpaque = true;
            //pgraphics->SetBkMode(OPAQUE);
            //pgraphics->SetBkColor(cr);
            crBkColor = cr;
         }
         else if(has_link() && m_pelemental->m_pstyle->get_color("background-color", "link", pdata, m_pelemental, cr))
         {
            bOpaque = true;
            //pgraphics->SetBkMode(OPAQUE);
            //pgraphics->SetBkColor(cr);
            crBkColor = cr;
         }
         else if (m_pelemental->m_pstyle->get_color("background-color", "", pdata, m_pelemental, cr))
         {
            bOpaque = true;
            //pgraphics->SetBkMode(OPAQUE);
            //pgraphics->SetBkColor(cr);
            crBkColor = cr;
         }
         else
         {
            bOpaque = false;
            //pgraphics->SetBkMode(TRANSPARENT);
         }

         ::draw2d::brush_pointer brushText(e_create);

         if(m_bHover && m_pelemental->m_pstyle->get_color("color", "hover", pdata, m_pelemental, cr))
         {
            brushText->create_solid(cr);
         }
         else if(has_link() && m_pelemental->m_pstyle->get_color("color", "link", pdata, m_pelemental, cr))
         {
            brushText->create_solid(cr);
         }
         else if(has_link())
         {
            brushText->create_solid(ARGB(255, 127, 127, 255));
         }
         else if(m_pelemental->m_pstyle->get_color("color", "", pdata, m_pelemental, cr))
         {
            brushText->create_solid(cr);
         }
         else
         {
            brushText->create_solid(ARGB(255, 0, 0, 0));
         }


         bool bCaretOn = ((m_millisFocusStart.elapsed()) % (m_dwCaretTime * 2)) < m_dwCaretTime;

         strsize iSelStart;
         strsize iSelEnd;
         ::sizef size3;
         draw2d::graphics_extension(pdata->m_pcoredata->get_context_application()).GetTextExtent(pgraphics, unitext("gGYIﾍ"), size3);
         i32 maxcy = size3.cy;

         _001GetViewSel(iSelStart, iSelEnd);
         strsize iCursor = iSelEnd;
         sort::sort(iSelStart, iSelEnd);

         ::html::font * pfont = pdata->get_font(m_pelemental);

         if(pfont != nullptr)
         {

            pgraphics->set(pfont->m_font);

         }

         const ::pointf & point = get_content_xy();

         float x = ::pointf.x;

         float y = ::pointf.y;

         if(m_pelemental->m_pparent != nullptr)
         {

            //x += m_pelemental->m_pparent->m_pimpl->m_border.left + //m_pelemental->m_pparent->m_pimpl->m_padding.left + //m_pelemental->m_pparent->m_pimpl->m_margin.left;

            //y += m_pelemental->m_pparent->m_pimpl->m_border.top + //m_pelemental->m_pparent->m_pimpl->m_padding.top + m_pelemental->m_pparent->m_pimpl->m_margin.top;*/

         /*}

         float cy = 0;
         string str1;
         string str2;
         string str3;
         string strExtent1;
         string strExtent2;
         string strExtent3;
         strsize lim = 0;

         ::draw2d::brush_pointer brushBackground(e_create);

         if(!pdata->m_pcoredata->m_bEdit)
         {
//            brushText->create_solid(cr);
            pgraphics->set(brushText);
         }


         if(m_straLines.get_size() == m_sizea.get_size())
         {

            for(i32 i = 0; i < m_straLines.get_size(); i++)
            {
               string strLine = m_straLines[i];
               float left = i == 0 ? x : m_bound.left;
               float top = y + cy;
               if(pdata->m_pcoredata->m_bEdit)
               {
                  float y = top;
                  string_array stra;
                  strsize i1 = iSelStart - lim;
                  strsize i2 = iSelEnd - lim;
                  strsize i3 = iCursor - lim;
                  strsize iStart = max(0,i1);
                  strsize iEnd = min(i2,strLine.get_length());
                  str1 = strLine.Mid(0,iStart);
                  str2 = strLine.Mid(iStart,iEnd - iStart);
                  str3 = strLine.Mid(iEnd);
                  strExtent1 = str1;
                  strExtent2 = str2;
                  strExtent3 = str3;
                  strExtent1.replace("\t","   ");
                  strExtent2.replace("\t","   ");
                  strExtent3.replace("\t","   ");
                  //pgraphics->SetBkMode(TRANSPARENT);
                  brushText->create_solid(cr);
                  pgraphics->set(brushText);
                  //pgraphics->SetBkColor(crBkSel);
                  pgraphics->text_out(left,y,strExtent1);
                  ::sizef size1 = pgraphics->GetTextExtent(strExtent1);

                  brushBackground->create_solid(crBkSel);
                  //pgraphics->SetBkMode(OPAQUE);
                  pgraphics->set(brushBackground);
                  ::sizef size2 = pgraphics->GetTextExtent(strExtent2);
                  pgraphics->fill_solid_rect_dim((i32)(left + size1.cx),(i32)y,size2.cx,size2.cy,crBkSel);

                  //pgraphics->set_text_color(crSel);
                  brushText->create_solid(crSel);
                  pgraphics->set(brushText);
                  pgraphics->text_out(left + size1.cx,y,strExtent2);

                  //            pgraphics->set_text_color(cr);
                  brushText->create_solid(cr);
                  pgraphics->set(brushText);
                  //pgraphics->SetBkColor(RGB(120, 240, 180));
                  //          pgraphics->SetBkMode(TRANSPARENT);
                  pgraphics->text_out(left + size1.cx + size2.cx,y,strExtent3);

                  maxcy = max(size1.cy,size2.cy);
                  maxcy = max(maxcy,size3.cy);
                  if(m_bFocus && bCaretOn && i3 == str1.get_length())
                  {
                     pgraphics->move_to(left + size1.cx,y);
                     pgraphics->line_to(left + size1.cx,y + maxcy);
                  }
                  if(m_bFocus && bCaretOn && i3 == (str1.get_length() + str2.get_length()))
                  {
                     pgraphics->move_to(left + size1.cx + size2.cx,y);
                     pgraphics->line_to(left + size1.cx + size2.cx,y + maxcy);
                  }

               }
               else
               {
                  pgraphics->text_out(left,top,strLine);
                  //pgraphics->fill_rect(left,top,50,50,ARGB(255,0,255,0));
               }

               cy += m_sizea[i].cy;
               lim += strLine.get_length();
            }
         }
         //pgraphics->fill_rect(0, 0, 100, 100, RGB(0, 255, 0));

         */

      }


      float text::get_first_line_height()
      {

         if(m_sizea.get_size() > 0)
         {

            return m_sizea[0].cy;

         }
         else
         {

            return m_box.height();

         }

      }


      float text::get_last_line_height()
      {

         if(m_sizea.get_size() > 0)
         {

            return m_sizea[m_sizea.get_upper_bound()].cy;

         }
         else if(m_pelemental->m_pbase->get_type() == base::type_tag)
         {

            if(m_pelemental->m_elementalptra.get_size() > 0)
            {

               return m_pelemental->m_elementalptra
                      [m_pelemental->m_elementalptra.get_upper_bound()]->m_pimpl->get_last_line_height();
            }
            else
            {

               return m_box.height();

            }

         }
         else
         {

            return m_box.height();

         }

      }


      bool text::get_color(color32_t & cr)
      {

         if(has_link())
         {

            cr =  ARGB(255, 127, 127, 255);

         }
         else
         {

            cr = ARGB(255, 0, 0, 0);

         }

         return true;

      }


      bool text::has_link()
      {

         if(m_bLink)
         {

            return true;

         }
         else
         {

            return ::html::impl::element::has_link();

         }

      }


      string text::link()
      {

         if(m_bLink)
         {

            return m_strLink;

         }
         else
         {

            return ::html::impl::element::link();

         }

      }


      i32 text::hit_test(html_data * pdocument, const ::pointf & point)
      {

         UNREFERENCED_PARAMETER(pdocument);

         float x = left();
         float cy = 0.f;
         float x1;
         float x2;

         for(i32 i = 0; i < m_straLines.get_size(); i++)
         {

            x1 = i == 0 ? x : m_bound.left;

            x2 = x1 + m_sizea[i].cx;

            if(point.x > x1 && point.x < x2)
            {

               if(point.y > m_box.top + cy  && point.y < m_box.top + cy + m_sizea[i].cy)
               {

                  return 1;

               }

            }

            cy += m_sizea[i].cy;

         }

         return 0;

      }


      void text::OnLButtonDown(::message::message * pmessage)
      {

         __pointer(::html::message) phtml(pmessage);

         if(m_pelemental->m_pdata->m_pcoredata->m_bEdit)
         {

            if(m_pelemental->m_elementalptra.get_size() == 1)
            {

               m_pelemental->m_elementalptra.first()->m_pimpl->OnLButtonDown(pmessage);

            }
            else
            {

               m_pedit->_002OnLButtonDown(phtml->m_psignal);

            }

         }
         else
         {

            ::html::impl::element::OnLButtonDown(pmessage);

         }

      }


      void text::OnLButtonUp(::message::message * pmessage)
      {

         __pointer(::html::message) phtml(pmessage);

         if(m_pelemental->m_pdata->m_pcoredata->m_bEdit)
         {

            if(m_pelemental->m_elementalptra.get_size() == 1)
            {

               m_pelemental->m_elementalptra.first()->m_pimpl->OnLButtonUp(pmessage);

            }
            else
            {

               m_pedit->_002OnLButtonUp(phtml->m_psignal);

            }

         }
         else
         {

            ::html::impl::element::OnLButtonUp(pmessage);

         }

      }


      void text::OnMouseMove(::message::message * pmessage)
      {

         ::html::impl::element::OnMouseMove(pmessage);

         if (m_pelemental->m_pdata->m_pcoredata->m_bEdit)
         {

            __pointer(::html::message) phtml(pmessage);

            m_pedit->_002OnMouseMove(phtml->m_psignal);

         }

      }


      strsize text::char_hit_test(::draw2d::graphics_pointer & pgraphics, i32 px, i32 py)
      {

         ::rect rect(m_box);

         pgraphics->set(m_pelemental->m_pdata->get_font(m_pelemental)->m_font);

         float x = left();

         float y = top();

         float cy = 0;

         if(py < y)
         {

            return 0;

         }

         strsize iFind = 0;

         strsize iLen = 0;

         for(i32 i = 0; i < m_straLines.get_size(); i++)
         {

            string str = m_straLines[i];

            const char * pszStart = str;

            const char * pszEnd = pszStart;

            float cur_x = i == 0 ? x : m_bound.left;
//            i32 cur_y = y + cy;
            if(py >= (y + cy) && py < (y + m_sizea[i].cy))
            {

               ::sizef size;

               strsize iChar = 0;

               while(true)
               {

                  if(px < cur_x + size.cx)
                  {

                     return iLen + iChar;

                  }

                  size = pgraphics->GetTextExtent(string(pszStart, pszEnd - pszStart));

                  if(*pszEnd == '\0')
                  {

                     break;

                  }

                  pszEnd = ::str::utf8_inc(pszEnd);

                  iChar++;
               }

               iFind = iChar;

            }
            else
            {

               iLen += str.get_length();

            }

            cy += m_sizea[i].cy;

         }

         return iFind + iLen;

      }


      void text::_001OnGetText()
      {

      }


      void text::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
      {

         UNREFERENCED_PARAMETER(pgraphics);

      }


      void text::_001OnAfterChangeText(const ::action_context & context)
      {

         __task_guard(m_bOnAfterChangeText);

         string strText;

         m_pedit->_001GetText(strText);

         m_pelemental->_001SetText(strText, context);

         m_pelemental->m_pdata->m_pcoredata->m_pform->set_need_layout();

      }


   } // namespace impl


} // namespace html


