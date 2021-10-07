#include "framework.h"
#include "core/user/simple_ui/_simple_ui.h"

namespace simple_ui
{




   password::password()
   {
      m_bPassword = true;
   }

   password::~password()
   {
   }




   void password::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      pgraphics->set_text_rendering_hint(::write_text::e_rendering_anti_alias);

      status < ::color::color > crBk;
      status < ::color::color > crBkSel;
      status < ::color::color > crSel;
      status < ::color::color > color32;

      auto pstyle = get_style(pgraphics);

      color32          = get_color(pstyle, ::e_element_text);
      crBk        = get_color(pstyle, ::e_element_background);
      crSel       = get_color(pstyle, ::e_element_text, ::user::e_state_selected);
      crBkSel     = get_color(pstyle, ::e_element_background, ::user::e_state_selected);


      //::job * pjob = pgraphics->m_pjob;

   /*   ::user::print_task * pprinttask = nullptr;
      if(pjob != nullptr)
         pprinttask = dynamic_cast < ::user::print_task * > (pjob);
      else
         pprinttask = nullptr;*/


      ::rectangle_i32 rectangleClient;
      get_client_rect(rectangleClient);

 /*     if(pprinttask != nullptr)
      {
         TRACE("Print Job Is Printing page %d",pprinttask->m_iPrintingPage);
      }*/

      bool bCaretOn = m_durationFocusStart.on_off(m_durationCaretPeriod);


      //rectangleClient.deflate(0, 0, 1, 1);

      //

      //if(pprinttask == nullptr)
      {

         ::user::interaction::_001OnDraw(pgraphics);

      }

      /*else if(!psession->savings().is_trying_to_save(::e_resource_processing)
      && !psession->savings().is_trying_to_save(::e_resource_blur_background))
      {

      pgraphics->blur(true, 4, rectangleClient);
      //class imaging & imaging = psystem->imaging();
      //::rectangle_i32 rectangleClient;
      //         get_window_rect(rectangleClient);
      //       rectangleClient.offset(rectangleClient.top_left());
      if(rectangleClient.size() != m_pimage->size())
      {
      m_pimageBk = create_image(rectangleClient->size());
      m_pimage->Fill(184, 184, 170);
      HMODULE hmodule = ::LoadLibrary("ca2performance.dll");
      ::draw2d::fastblur *( *pfnNew )(__pointer(::aura::application)) = (::draw2d::fastblur *(*)(__pointer(::aura::application))) ::GetProcAddress(hmodule, "new_fastblur");*/
//                  m_fastblur.create(this);
//      m_fastblur.initialize(rectangleClient.size(), 2);
//      }
//      if(m_fastblur.is_set() && m_fastblur->get_graphics() != nullptr)
//      {
//      m_fastblur->get_graphics()->BitBlt(0, 0, rectangleClient.width(), rectangleClient.height(), pgraphics, 0, 0);
//      m_fastblur.blur();
//      imaging.bitmap_blend(
//      m_fastblur->get_graphics(),
//      nullptr,
//      rectangleClient.size(),
/*      m_pimage->get_graphics(),
      nullptr,
      49);
      pgraphics->from(rectangleClient.size(),
      m_fastblur->get_graphics(),
      nullptr,
      SRCCOPY);
      }*/
      /*}
      else
      {
      class imaging & imaging = psystem->imaging();
      //_001DrawBackground(pgraphics, rectangleClipBox);
      imaging.color_blend(
      pgraphics,
      rectangleClient,
      rgb(200, 255, 255),
      127);
      }*/

      ::color::color color;
      color.set_rgb(rgb(227,227,210));
      color.hls_rate(0.0,-0.33,-0.23);
//      color32_t crBorder = ca.get_rgb() | (0xff << 24);
      //pgraphics->draw3d_rect(rectangleClient,crBorder,crBorder);

      if(m_ptree == nullptr)
         return;

      /*if(m_iLineHeight == 0)
      {
         pgraphics->OffsetViewportOrg(-m_scrolldata.m_pointScroll.x,m_scrolldata.m_pointScroll.y);
      }
      else
      {
         pgraphics->OffsetViewportOrg(-m_scrolldata.m_pointScroll.x,-(m_scrolldata.m_pointScroll.y % m_iLineHeight));
      }*/


      ::draw2d::region_pointer rgn(e_create);

      rectangleClient.deflate(2,2);

      //client_to_screen(rectangleClient);
      rgn->create_rect(rectangleClient);

      double left = rectangleClient.left;

      //   pgraphics->SelectClipRgn(&rgn);

      bool bFocus;

      if(has_keyboard_focus())
      {
         bFocus = keyboard_focus_is_focusable();
      }
      else
      {
         bFocus = false;
      }

      strsize iSelStart;
      strsize iSelEnd;
      strsize lim = 0;

      auto ppenCaret = __create < ::draw2d::pen > ();

      auto pbrushText = __create < ::draw2d::brush > ();

      ppenCaret->create_solid(1.0,argb(255,0,0,0));


      /*   rectangleClient.top = m_point.y;
      rectangleClient.left = m_point.x;
      rectangleClient.bottom = rectangleClient.top + m_size.cy;
      rectangleClient.right = rectangleClient.left + m_size.cx;*/
      //      pgraphics->fill_rectangle(rectangleClient, crBk);

//

      double y = rectangleClient.top;
      _001GetViewSel(iSelStart,iSelEnd);
      strsize iCursor = iSelEnd;
      __sort(iSelStart,iSelEnd);
      pgraphics->set(get_font(pstyle));
      //size_i32 size3;
      ::write_text::text_metric metric;
       pgraphics->get_text_metrics(&metric);
      double dLineHeight = metric.get_line_spacing();
//      string_array & straLines = m_plines->lines;
      string_array & straLines = m_straLines;
      string_array straLineFeed;
      string strLine;
      string str1;
      string str2;
      string str3;
      string strExtent1;
      string strExtent2;
      string strExtent3;
      index iLineStart = should_load_full_file() ? m_iLineOffset : 0;
      index iLineEnd = should_load_full_file() ? m_iLineCount - 1 : straLines.get_size() - 1;
      iLineEnd = minimum(iLineEnd,straLines.get_upper_bound());
      for(index i = iLineStart; i <= iLineEnd; i++)
      {
         straLineFeed.erase_all();
         straLineFeed.add_lines(straLines[i], false);
         if(straLineFeed.get_size() > 0)
         {
            strLine = straLineFeed[0];
         }
         else
         {
            strLine.Empty();
         }
         string_array stra;
         strsize i1 = iSelStart - lim;
         strsize i2 = iSelEnd - lim;
         strsize i3 = iCursor - lim;
         strsize iStart = maximum(0,i1);
         strsize iEnd = minimum(i2,strLine.get_length());
         ::str::fill(strLine,'*');
         str1 = strLine.Mid(0,iStart);
         str2 = strLine.Mid(iStart,iEnd - iStart);
         str3 = strLine.Mid(iEnd);
         strExtent1 = str1;
         strExtent2 = str2;
         strExtent3 = str3;
         strExtent1.replace("\t","   ");
         strExtent2.replace("\t","   ");
         strExtent3.replace("\t","   ");
         ::str::fill(strExtent1,'*');
         ::str::fill(strExtent2,'*');
         ::str::fill(strExtent3,'*');

         pbrushText->create_solid(color32);
         pgraphics->set(pbrushText);
         pgraphics->text_out(left,y,strExtent1);

         size_f64 size1(0.0,0.0);
         pgraphics->get_text_extent(size1,strLine,(i32)strLine.length(),(i32)iStart);
         size_f64 sizeb(0.0,0.0);
         pgraphics->get_text_extent(sizeb,strLine,iEnd);
         size_f64 size2(0.0,0.0);
         pgraphics->get_text_extent(size2,strLine,(i32)strLine.length(),(i32)iEnd);
         size2.cx -= size1.cx;

         if(iEnd > iStart)
         {

            auto rectangleFill = ::rectangle_f64_dimension((i32)(left + size1.cx), (i32)y, (i32)size2.cx, (i32)size2.cy);
            pgraphics->fill_rectangle(rectangleFill,argb(255,120,240,180));
            pbrushText->create_solid(crSel);
            pgraphics->set(pbrushText);
            pgraphics->text_out(left + size1.cx,y,strExtent2);
         }

         pbrushText->create_solid(color32);
         pgraphics->set(pbrushText);
         pgraphics->text_out(left + size1.cx + size2.cx,y,strExtent3);

         //maxcy = maximum(size1.cy, size2.cy);
         //maxcy = maximum(maxcy, size3.cy);
         if(bFocus && bCaretOn && i3 == str1.get_length())
         {
            
            pgraphics->set(ppenCaret);
            pgraphics->move_to(left + size1.cx,y);
            pgraphics->line_to(left + size1.cx,y + dLineHeight);

         }
         else if(bFocus && bCaretOn && i3 == (str1.get_length() + str2.get_length()))
         {
            
            pgraphics->set(ppenCaret);
            pgraphics->move_to(left + size2.cx + size1.cx,y);
            pgraphics->line_to(left + size2.cx + size1.cx,y + dLineHeight);

         }

         y += dLineHeight;
         lim += straLines[i].get_length();

         //ASSERT(false);

      }

   }










} // namespace simple_ui



