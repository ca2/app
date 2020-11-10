#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/user/simple_ui/_simple_ui.h"
#endif


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

      pgraphics->set_text_rendering_hint(::draw2d::text_rendering_hint_anti_alias);

      color32_t crBk;
      color32_t crBkSel;
      color32_t crSel;
      color32_t cr;

      auto pstyle = get_style(pgraphics);

      cr          = get_color(pstyle, ::user::element_text);
      crBk        = get_color(pstyle, ::user::element_background);
      crSel       = get_color(pstyle, ::user::element_text, ::user::e_state_selected);
      crBkSel     = get_color(pstyle, ::user::element_background, ::user::e_state_selected);


      //::job * pjob = pgraphics->m_pjob;

   /*   ::user::print_task * pprinttask = nullptr;
      if(pjob != nullptr)
         pprinttask = dynamic_cast < ::user::print_task * > (pjob);
      else
         pprinttask = nullptr;*/


      ::rect rectClient;
      get_client_rect(rectClient);

 /*     if(pprinttask != nullptr)
      {
         TRACE("Print Job Is Printing page %d",pprinttask->m_iPrintingPage);
      }*/

      bool bCaretOn = m_tickFocusStart.on_off(m_tickCaretPeriod);


      //rectClient.deflate(0, 0, 1, 1);

      //

      //if(pprinttask == nullptr)
      {

         ::user::interaction::_001OnDraw(pgraphics);

      }

      /*else if(!psession->savings().is_trying_to_save(::e_resource_processing)
      && !psession->savings().is_trying_to_save(::e_resource_blur_background))
      {

      pgraphics->blur(true, 4, rectClient);
      //class imaging & imaging = System.imaging();
      //::rect rectClient;
      //         get_window_rect(rectClient);
      //       rectClient.offset(rectClient.top_left());
      if(rectClient.size() != m_pimage->size())
      {
      m_pimageBk = create_image(rectClient->size());
      m_pimage->Fill(184, 184, 170);
      HMODULE hmodule = ::LoadLibrary("ca2performance.dll");
      ::draw2d::fastblur *( *pfnNew )(__pointer(::aura::application)) = (::draw2d::fastblur *(*)(__pointer(::aura::application))) ::GetProcAddress(hmodule, "new_fastblur");*/
//                  m_fastblur.create(this);
//      m_fastblur.initialize(rectClient.size(), 2);
//      }
//      if(m_fastblur.is_set() && m_fastblur->get_graphics() != nullptr)
//      {
//      m_fastblur->get_graphics()->BitBlt(0, 0, rectClient.width(), rectClient.height(), pgraphics, 0, 0, SRCCOPY);
//      m_fastblur.blur();
//      imaging.bitmap_blend(
//      m_fastblur->get_graphics(),
//      nullptr,
//      rectClient.size(),
/*      m_pimage->get_graphics(),
      nullptr,
      49);
      pgraphics->from(rectClient.size(),
      m_fastblur->get_graphics(),
      nullptr,
      SRCCOPY);
      }*/
      /*}
      else
      {
      class imaging & imaging = System.imaging();
      //_001DrawBackground(pgraphics, rectClipBox);
      imaging.color_blend(
      pgraphics,
      rectClient,
      RGB(200, 255, 255),
      127);
      }*/

      color ca;
      ca.set_rgb(RGB(227,227,210));
      ca.hls_rate(0.0,-0.33,-0.23);
//      color32_t crBorder = ca.get_rgb() | (0xff << 24);
      //pgraphics->draw3d_rect(rectClient,crBorder,crBorder);

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

      rectClient.deflate(2,2);

      //_001ClientToScreen(rectClient);
      rgn->create_rect(rectClient);

      double left = rectClient.left;

      //   pgraphics->SelectClipRgn(&rgn);

      bool bFocus;

      if(has_focus())
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

      ::draw2d::pen_pointer penCaret(e_create);

      ::draw2d::brush_pointer brushText(e_create);

      penCaret->create_solid(1.0,ARGB(255,0,0,0));


      /*   rectClient.top = m_point.y;
      rectClient.left = m_point.x;
      rectClient.bottom = rectClient.top + m_size.cy;
      rectClient.right = rectClient.left + m_size.cx;*/
      //      pgraphics->fill_rect(rectClient, crBk);

//

      double y = rectClient.top;
      _001GetViewSel(iSelStart,iSelEnd);
      strsize iCursor = iSelEnd;
      __sort(iSelStart,iSelEnd);
      pgraphics->set(get_font(pstyle));
      //size size3;
      ::draw2d::text_metric metric;
       pgraphics->get_text_metrics(&metric);
      i32 iLineHeight = metric.tmHeight;
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
      iLineEnd = min(iLineEnd,straLines.get_upper_bound());
      for(index i = iLineStart; i <= iLineEnd; i++)
      {
         straLineFeed.remove_all();
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
         strsize iStart = max(0,i1);
         strsize iEnd = min(i2,strLine.get_length());
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

         brushText->create_solid(cr);
         pgraphics->set(brushText);
         pgraphics->text_out(left,y,strExtent1);

         sized size1(0.0,0.0);
         pgraphics->GetTextExtent(size1,strLine,(i32)strLine.length(),(i32)iStart);
         sized sizeb(0.0,0.0);
         pgraphics->GetTextExtent(sizeb,strLine,iEnd);
         sized size2(0.0,0.0);
         pgraphics->GetTextExtent(size2,strLine,(i32)strLine.length(),(i32)iEnd);
         size2.cx -= size1.cx;

         if(iEnd > iStart)
         {
            pgraphics->fill_solid_rect_dim((i32)(left + size1.cx),(i32)y,(i32)size2.cx,(i32)size2.cy,ARGB(255,120,240,180));
            brushText->create_solid(crSel);
            pgraphics->set(brushText);
            pgraphics->text_out(left + size1.cx,y,strExtent2);
         }

         brushText->create_solid(cr);
         pgraphics->set(brushText);
         pgraphics->text_out(left + size1.cx + size2.cx,y,strExtent3);

         //maxcy = max(size1.cy, size2.cy);
         //maxcy = max(maxcy, size3.cy);
         if(bFocus && bCaretOn && i3 == str1.get_length())
         {
            pgraphics->set(penCaret);
            pgraphics->move_to(left + size1.cx,y);
            pgraphics->line_to(left + size1.cx,y + iLineHeight);
         }
         else if(bFocus && bCaretOn && i3 == (str1.get_length() + str2.get_length()))
         {
            pgraphics->set(penCaret);
            pgraphics->move_to(left + size2.cx + size1.cx,y);
            pgraphics->line_to(left + size2.cx + size1.cx,y + iLineHeight);
         }
         y += iLineHeight;
         lim += straLines[i].get_length();
         //ASSERT(FALSE);
      }

   }










} // namespace simple_ui



