#include "framework.h"
#include "aura/graphics/draw2d/_draw2d.h"
#if !BROAD_PRECOMPILED_HEADER
#include "_impl.h"
#endif



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

         synchronous_lock lock(pdata->m_pcoredata->mutex());

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

            m_pedit->create_child(pdata->m_pcoredata->m_pform);

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

            pgraphics->set(pfont->m_pfont);

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

         synchronous_lock lock(pdata->m_pcoredata->mutex());

         ::html::impl::element::layout_phase0(pdata);

         if (m_pelemental->m_elementalptra.get_size() > 0 || m_pelemental->m_strBody.is_empty())
         {

            return;

         }

//         e_tag etag = m_pelemental->m_etag;

         ::draw2d::graphics_pointer & pgraphics = pdata->m_pcoredata->m_pgraphics;

         if (pgraphics == nullptr)
            return;

         pgraphics->m_puserinteraction = pdata->m_pcoredata->m_puserinteraction;

         font * pfont = pdata->get_font(m_pelemental);

         if (pfont != nullptr)
         {

            pgraphics->set(pfont->m_pfont);

         }

         string str = m_pelemental->m_strBody;

         string strMax = str;

         if (!pdata->m_pcoredata->m_bHasChar)
         {

            strMax.trim_left();

         }

         ::size_f32 size = pgraphics->get_text_extent(strMax);

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

               size = pgraphics->get_text_extent(m_straWordSpace[i]);

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

               pgraphics->set(pdata->get_font(m_pelemental)->m_pfont);

               m_box.set_width(0);

               ::write_text::text_metric textmetric;

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

         pgraphics->set(pdata->get_font(m_pelemental)->m_pfont);

         string str = m_pelemental->m_strBody;

         str.trim();



         m_straLines.erase_all();

         m_sizea.erase_all();

         ::size_f32 sizeText;

         i32 iSpace;

         string strLine;

         uchar uch;

         strsize iLastSpace = 0;

         auto pointBound = top_left();

         pointBound.x += m_margin.left + m_border.left + m_padding.left;

         float x = pointBound.x;

         ::size_f32 sizeContent = ::size_f32(get_bound_size());

         sizeContent.cx = maximum(0.f, sizeContent.cx - m_padding.left - m_padding.right - m_border.left - m_border.right - m_margin.left - m_margin.right);

         sizeContent.cy = maximum(0.f, sizeContent.cy - m_padding.top - m_padding.bottom - m_border.top - m_border.bottom - m_margin.top - m_margin.bottom);

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

            sizeText = pgraphics->get_text_extent(strLine);

            if ((x + sizeText.cx) > pointBound.x + sizeContent.cx)
            {

               if (x > pointBound.x && iLastSpace == 0)
               {

                  m_straLines.add("");

                  sizeText.cx = 0;

               }
               else if (iLastSpace > 0)
               {

                  sizeText = pgraphics->get_text_extent(strLine.Left(iLastSpace));

                  ::write_text::text_metric textmetric;

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

               m_sizea.add(::size_f32(sizeText));

               iLastSpace = 0;

               x = pointBound.x;

            }

         }

         if (strLine.get_length() > 0)
         {

            sizeText = pgraphics->get_text_extent(strLine);

            ::write_text::text_metric textmetric;

            pgraphics->get_text_metrics(&textmetric);

            sizeText.cy = (float) textmetric.get_line_spacing();

            m_straLines.add(strLine);

            m_sizea.add(::size_f32(sizeText));

         }

         if (pdata->m_pcoredata->m_bEdit && m_straLines.get_size() == 0)
         {

            m_straLines.add("");

            m_sizea.add(::size_f32(0.f, 0.f));

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

         //::rectangle_i32 rectangleWindow;
         //m_pcheckbox->get_window_rect(rectangleWindow);
         ::point_i32 pointPreviousViewportOrg = pgraphics->GetViewportOrg();

         pgraphics->OffsetViewportOrg((i32) m_box.left, (i32) m_box.top);

         if (::is_set(m_pedit) && m_pedit->is_window() && pdata->m_pcoredata->m_bEdit)
         {

            m_pedit->_000CallOnDraw(pdata->m_pcoredata->m_pgraphics);

         }
         else
         {

            pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

            auto pstyle = m_pelemental->m_pdata->m_pcoredata->m_pform->get_style(pgraphics);
            
            auto colorText = m_pelemental->get_color(pstyle, ::css::color_text);

            pgraphics->set_text_color(colorText);
            
            auto pfont = m_pelemental->get_font();

            pgraphics->set(pfont);

            ::rectangle_i32 rectangleLine;

            for (index i = 0; i < m_straLines.get_count(); i++)
            {

               string str = m_straLines[i];

               rectangleLine.top = rectangleLine.top;

               rectangleLine.set_size(m_sizea[i]);

               pgraphics->text_out(rectangleLine.left, rectangleLine.top, str);

            }


         }

         pgraphics->SetViewportOrg(pointPreviousViewportOrg);

         /*

         ::draw2d::graphics_pointer & pgraphics = pdata->m_pcoredata->m_pgraphics;

         ::color::color crBkSel = rgb(120, 240, 150);

         ::color::color crSel = rgb(10, 30, 20);

         e_tag etag = m_pelemental->m_etag;

         if(etag == tag_body)
         {

            ::rectangle_i32 rectangle;

            if(!pdata->m_pcoredata->m_bDrawFirstBody)
            {

               pdata->m_pcoredata->m_bDrawFirstBody = true;

               pdata->m_pcoredata->m_pform->get_client_rect(rectangle);

            }
            else
            {

               m_box.get(rectangle);

            }

            pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

            ::color32_t color32 = 0;

            double d;

            if (m_pelemental->m_pstyle->get_alpha("", pdata, m_pelemental, d))
            {
               if(m_bHover && m_pelemental->m_pstyle->get_color("background-color", "hover", pdata, m_pelemental, color32))
               {
                  App(pdata->get_app()).imaging().color_blend(
                  pgraphics,
                  rectangle,
                  color32,
                  maximum(0, minimum(255, (byte)(d * 255))));
               }
               else if(has_link() && m_pelemental->m_pstyle->get_color("background-color", "link", pdata, m_pelemental, color32))
               {
                  App(pdata->get_app()).imaging().color_blend(
                  pgraphics,
                  rectangle,
                  color32,
                  maximum(0, minimum(255, (byte)(d * 255))));
               }
               else if (m_pelemental->m_pstyle->get_color("background-color", "", pdata, m_pelemental, color32))
               {
                  App(pdata->get_app()).imaging().color_blend(
                  pgraphics,
                  rectangle,
                  color32,
                  maximum(0, minimum(255, (byte)(d * 255))));
               }
            }
            else
            {
               if(m_bHover && m_pelemental->m_pstyle->get_color("background-color", "hover", pdata, m_pelemental, color32))
               {
                  pgraphics->fill_rectangle(rectangle, color32);
               }
               else if(has_link() && m_pelemental->m_pstyle->get_color("background-color", "link", pdata, m_pelemental, color32))
               {
                  pgraphics->fill_rectangle(rectangle, color32);
               }
               else if (m_pelemental->m_pstyle->get_color("background-color", "", pdata, m_pelemental, color32))
               {
                  pgraphics->fill_rectangle(rectangle, color32);
               }
            }
         }
         if(m_pelemental->m_elementalptra.get_size() > 0 || m_pelemental->m_strBody.is_empty())
            return;
//       ::draw2d::graphics_pointer & pgraphics = pgraphics;
         ::html::impl::element::_001OnDraw(pdata);


         ::color32_t color32 = 0;
         bool bOpaque;
         ::color::color crBkColor;
         if(m_bHover && m_pelemental->m_pstyle->get_color("background-color", "hover", pdata, m_pelemental, color32))
         {
            bOpaque = true;
            //pgraphics->SetBkMode(OPAQUE);
            //pgraphics->SetBkColor(color32);
            crBkColor = color32;
         }
         else if(has_link() && m_pelemental->m_pstyle->get_color("background-color", "link", pdata, m_pelemental, color32))
         {
            bOpaque = true;
            //pgraphics->SetBkMode(OPAQUE);
            //pgraphics->SetBkColor(color32);
            crBkColor = color32;
         }
         else if (m_pelemental->m_pstyle->get_color("background-color", "", pdata, m_pelemental, color32))
         {
            bOpaque = true;
            //pgraphics->SetBkMode(OPAQUE);
            //pgraphics->SetBkColor(color32);
            crBkColor = color32;
         }
         else
         {
            bOpaque = false;
            //pgraphics->SetBkMode(TRANSPARENT);
         }

         auto pbrushText = __create < ::draw2d::brush > ();

         if(m_bHover && m_pelemental->m_pstyle->get_color("color", "hover", pdata, m_pelemental, color32))
         {
            pbrushText->create_solid(color32);
         }
         else if(has_link() && m_pelemental->m_pstyle->get_color("color", "link", pdata, m_pelemental, color32))
         {
            pbrushText->create_solid(color32);
         }
         else if(has_link())
         {
            pbrushText->create_solid(argb(255, 127, 127, 255));
         }
         else if(m_pelemental->m_pstyle->get_color("color", "", pdata, m_pelemental, color32))
         {
            pbrushText->create_solid(color32);
         }
         else
         {
            pbrushText->create_solid(argb(255, 0, 0, 0));
         }


         bool bCaretOn = ((m_durationFocusStart.elapsed()) % (m_dwCaretTime * 2)) < m_dwCaretTime;

         strsize iSelStart;
         strsize iSelEnd;
         ::size_f32 size3;
         draw2d::graphics_extension(pdata->m_pcoredata->get_app()).get_text_extent(pgraphics, unitext("gGYIﾍ"), size3);
         i32 maxcy = size3.cy;

         _001GetImpactSel(iSelStart, iSelEnd);
         strsize iCursor = iSelEnd;
         sort::sort(iSelStart, iSelEnd);

         ::html::font * pfont = pdata->get_font(m_pelemental);

         if(pfont != nullptr)
         {

            pgraphics->set(pfont->m_pfont);

         }

         const ::point_f32 & point = get_content_xy();

         float x = ::point_f32.x;

         float y = ::point_f32.y;

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

         auto pbrushBackground = __create < ::draw2d::brush > ();

         if(!pdata->m_pcoredata->m_bEdit)
         {
//            pbrushText->create_solid(color32);
            pgraphics->set(pbrushText);
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
                  strsize iStart = maximum(0,i1);
                  strsize iEnd = minimum(i2,strLine.get_length());
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
                  pbrushText->create_solid(color32);
                  pgraphics->set(pbrushText);
                  //pgraphics->SetBkColor(crBkSel);
                  pgraphics->text_out(left,y,strExtent1);
                  ::size_f32 size1 = pgraphics->get_text_extent(strExtent1);

                  pbrushBackground->create_solid(crBkSel);
                  //pgraphics->SetBkMode(OPAQUE);
                  pgraphics->set(pbrushBackground);
                  ::size_f32 size2 = pgraphics->get_text_extent(strExtent2);
                  pgraphics->fill_solid_rect_dim((i32)(left + size1.cx),(i32)y,size2.cx,size2.cy,crBkSel);

                  //pgraphics->set_text_color(crSel);
                  pbrushText->create_solid(crSel);
                  pgraphics->set(pbrushText);
                  pgraphics->text_out(left + size1.cx,y,strExtent2);

                  //            pgraphics->set_text_color(color32);
                  pbrushText->create_solid(color32);
                  pgraphics->set(pbrushText);
                  //pgraphics->SetBkColor(rgb(120, 240, 180));
                  //          pgraphics->SetBkMode(TRANSPARENT);
                  pgraphics->text_out(left + size1.cx + size2.cx,y,strExtent3);

                  maxcy = maximum(size1.cy,size2.cy);
                  maxcy = maximum(maxcy,size3.cy);
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
                  //pgraphics->fill_rectangle(left,top,50,50,argb(255,0,255,0));
               }

               cy += m_sizea[i].cy;
               lim += strLine.get_length();
            }
         }
         //pgraphics->fill_rectangle(0, 0, 100, 100, rgb(0, 255, 0));

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


      bool text::get_color(::color::color & color32)
      {

         if(has_link())
         {

            color32 =  argb(255, 127, 127, 255);

         }
         else
         {

            color32 = argb(255, 0, 0, 0);

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


      i32 text::hit_test(html_data * pdocument, const ::point_f32 & point)
      {

         __UNREFERENCED_PARAMETER(pdocument);

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

               m_pedit->route_message(phtml->m_pmessage);

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

               m_pedit->route_message(phtml->m_pmessage);

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

            m_pedit->route_message(phtml->m_pmessage);

         }

      }


      strsize text::char_hit_test(::draw2d::graphics_pointer & pgraphics, i32 px, i32 py)
      {

         ::rectangle_i32 rectangle(m_box);

         pgraphics->set(m_pelemental->m_pdata->get_font(m_pelemental)->m_pfont);

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

               ::size_f32 size;

               strsize iChar = 0;

               while(true)
               {

                  if(px < cur_x + size.cx)
                  {

                     return iLen + iChar;

                  }

                  size = pgraphics->get_text_extent(string(pszStart, pszEnd - pszStart));

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

         __UNREFERENCED_PARAMETER(pgraphics);

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


