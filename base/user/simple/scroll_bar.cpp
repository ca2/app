#include "framework.h"
#include "scroll_bar.h"
#include "acme/constant/message.h"
#include "acme/handler/item.h"
#include "acme/platform/timer.h"
#include "acme/user/user/content.h"
#include "acme/user/user/drag.h"
#include "acme/user/user/tool.h"
#include "aura/graphics/draw2d/draw2d.h"
#include "aura/graphics/draw2d/pen.h"
#include "aura/graphics/image/image.h"
#include "aura/graphics/image/drawing.h"
#include "aura/message/user.h"
#include "aura/user/user/style.h"


simple_scroll_bar::simple_scroll_bar()
{

   //m_pbrushNull->CreateStockObject(NULL_BRUSH);
   m_flagNonClient.erase(e_non_client_background);
   // m_flagNonClient.erase(e_non_client_focus_rect);
   m_bTracking = false;
   m_scrollinfo.nMin = 0;
   m_scrollinfo.nMax = 100;
   m_scrollinfo.nPage = 10;
   m_scrollinfo.nPos = 0;

   m_iScrollBarWidth = 0;

   m_bDefaultMouseHoverHandling = true;
   m_bDefaultParentMouseMessageHandling = true;

   //m_bDefaultParentMouseMessageHandling = true;

   //m_cr = argb(127,180,80,120);
   //m_colorStrong = argb(150, 150, 150, 150);
   //m_colorBorder = argb(190, 180, 180, 180);
   //m_colorLiteBorder = argb(184,84 + 23,84 + 23,77 + 23);

   //m_colorHover = argb(100,190,180,250);
   //m_colorHoverStrong = argb(130, 190, 180, 250);
   //m_colorHoverBorder = argb(190, 160, 150, 180);
   //m_colorHoverLiteBorder = argb(184,84 + 23 - 23,84 + 23,77 + 23 + 84);

}

simple_scroll_bar::~simple_scroll_bar()
{
}


void simple_scroll_bar::install_message_routing(::channel * pchannel)
{
   ::user::interaction::install_message_routing(pchannel);
   MESSAGE_LINK(MESSAGE_CREATE, pchannel, this, &simple_scroll_bar::on_message_create);
   MESSAGE_LINK(MESSAGE_DESTROY, pchannel, this, &simple_scroll_bar::on_message_destroy);
   MESSAGE_LINK(e_message_show_window, pchannel, this, &simple_scroll_bar::on_message_show_window);
   MESSAGE_LINK(e_message_mouse_move, pchannel, this, &simple_scroll_bar::on_message_mouse_move);
   MESSAGE_LINK(e_message_left_button_down, pchannel, this, &simple_scroll_bar::on_message_left_button_down);
   MESSAGE_LINK(e_message_left_button_up, pchannel, this, &simple_scroll_bar::on_message_left_button_up);
   MESSAGE_LINK(e_message_hscroll, pchannel, this, &simple_scroll_bar::_001OnHScroll);

}


//bool simple_scroll_bar::create_interaction(const ::string & pszClassName, const ::string & pszWindowName, u32 uStyle, ::user::interaction * puiParent, const ::atom & atom, ::request * prequest)
//{
//
//   if(!::user::interaction::create_interaction(pszClassName, pszWindowName, uStyle, puiParent, atom, pcreate))
//   {
//
//      return false;
//
//   }
//
//   return true;
//
//}


//bool simple_scroll_bar::create_interaction(enum_orientation eorientation, u32 uStyle, ::user::interaction * puiParent, ::atom atom)
//{
//
//   if(!::user::scroll_bar::create_interaction(eorientation, uStyle, puiParent, atom))
//   {
//
//      return false;
//
//   }
//
//   return true;
//
//}


void simple_scroll_bar::on_message_mouse_move(::message::message * pmessage)
{

   //auto pmouse = pmessage->m_union.m_pmouse;

   //::point_i32 pointClient;

   //pointClient = pmouse->m_point;

   //screen_to_client()(pointClient);

   //if (m_bTracking)
   //{

   //   auto point = pointClient - m_sizeTrackOffset - get_parent_accumulated_scroll();

   //   queue_graphics_call([this, point](::draw2d::graphics_pointer & pgraphics)
   //      {

   //         SetTrackingPos(point, pgraphics);

   //         post_scroll_message(e_scroll_command_thumb_track);

   //      });

   //   set_need_redraw();

   //   post_redraw();

   //   pmouse->m_lresult = 1;

   //   auto pcursor = get_mouse_cursor(e_cursor_arrow);

   //   pmouse->m_pcursor = pcursor;

   //}
   //else
   //{

   //   auto eelement = hit_test(pmouse, ::user::e_zorder_any);

   //   if (eelement.is_set())
   //   {

   //      auto pcursor = get_mouse_cursor(e_cursor_arrow);

   //      pmouse->m_pcursor = pcursor;

   //   }

   //}


}


bool simple_scroll_bar::scrollbar_action(const ::item * pitem)
{

   if (::is_null(pitem))
   {

      return false;

   }

   switch (pitem->m_item.m_eelement)
   {
   case ::e_element_scrollbar_rectA:
      return scrollbar_lineA();
   case ::e_element_scrollbar_rectB:
      return scrollbar_lineB();
   case ::e_element_scrollbar_pageA:
      return scrollbar_pageA(user_item(pitem)->m_pointClient);
   case ::e_element_scrollbar_pageB:
      return scrollbar_pageB(user_item(pitem)->m_pointClient);
   default:
      return false;
   }

}


void simple_scroll_bar::on_message_left_button_down(::message::message * pmessage)
{

   //auto pmouse = pmessage->m_union.m_pmouse;

   //m_pitemCurrent = hit_test(pmouse, ::user::e_zorder_any);

   //if (!m_pitemCurrent.is_set())
   //{

   //   pmouse->m_bRet = false;

   //   return;

   //}

   //pmouse->m_bRet = true;

   //pmouse->m_lresult = 1;

   //set_mouse_capture();

   //if (!keyboard_focus_is_focusable())
   //{

   //   auto pparent = get_parent();

   //   if (::is_set(pparent))
   //   {

   //      if (pparent->keyboard_focus_is_focusable())
   //      {

   //         pparent->set_keyboard_focus();

   //         set_need_redraw();

   //         post_redraw();

   //      }

   //   }

   //}

   //auto psystem = acmesystem()->m_paurasystem;

   //auto pdraw2d = psystem->draw2d();

   //auto pgraphics = pdraw2d->create_memory_graphics(this);

   //if (::is_set(m_pitemCurrent) && m_pitemCurrent->m_item.m_eelement == ::e_element_scrollbar_trackbar)
   //{

   //   m_bTracking = true;

   //   auto puseritemCurrent = user_item(m_pitemCurrent);

   //   m_pointTrack = puseritemCurrent->m_pointClient;

   //   m_statusrectangleTrack = get_track_rectangle();

   //   m_sizeTrackOffset = m_pointTrack - m_statusrectangleTrack.top_left();

   //}
   //else
   //{

   //   if (scrollbar_action(m_pitemCurrent))
   //   {

   //      SetTimer((uptr)this, 300_ms, nullptr);

   //   }

   //}

}


void simple_scroll_bar::on_message_left_button_up(::message::message * pmessage)
{

   //release_mouse_capture();

   //auto pmouse = pmessage->m_union.m_pmouse;

   //if (!m_pitemCurrent)
   //{

   //   return;

   //}

   //KillTimer(((uptr)this));

   //KillTimer(((uptr)this) + 1);

   //bool bWasTracking = m_bTracking;

   //m_bTracking = false;

   //if (bWasTracking)
   //{

   //   auto point = pmouse->m_point;

   //   screen_to_client()(point);

   //   point = point - m_sizeTrackOffset - get_parent_accumulated_scroll();

   //   //auto psystem = acmesystem()->m_paurasystem;

   //   //auto pdraw2d = psystem->draw2d();

   //   //auto pgraphics = pdraw2d->create_memory_graphics(this);

   //   SetTrackingPos(point);

   //   post_scroll_message(e_scroll_command_thumb_position);

   //   set_need_redraw();

   //   post_redraw();

   //}

   //m_pitemCurrent = nullptr;

   //pmouse->m_bRet = true;

}


::status < ::rectangle_i32 > simple_scroll_bar::get_track_rectangle()
{

   ::status < ::rectangle_i32 > statusrectangleTrack;

   ::rectangle_i32 rectangleX;

   rectangleX = this->rectangle();

   ::size_i32 sizeTrack;

   GetTrackSize(sizeTrack);

   i32 iPos;

   if (m_bTracking)
   {

      iPos = m_scrollinfo.nTrackPos;

   }
   else
   {

      iPos = m_scrollinfo.nPos;

   }

   auto pstyle = get_style();

   int iScrollBarWidth = scrollbar_width();

   if (m_eorientation == e_orientation_horizontal)
   {

      i32 iWidth = rectangleX.width() - iScrollBarWidth * 2 - sizeTrack.cx();

      statusrectangleTrack.top() = rectangleX.top();

      statusrectangleTrack.bottom() = rectangleX.top() + sizeTrack.cy();

      if (m_scrollinfo.nMax - m_scrollinfo.nMin - m_scrollinfo.nPage == 0)
      {

         statusrectangleTrack.left() = 0;

      }
      else
      {

         statusrectangleTrack.left() = rectangleX.left() + iScrollBarWidth + (iPos - m_scrollinfo.nMin) * iWidth / (m_scrollinfo.nMax - m_scrollinfo.nMin - m_scrollinfo.nPage);

      }

      statusrectangleTrack.right() = statusrectangleTrack.left() + sizeTrack.cx();

   }
   else if (m_eorientation == e_orientation_vertical)
   {

      i32 iHeight = rectangleX.height() - iScrollBarWidth * 2 - sizeTrack.cy();

      statusrectangleTrack.left() = rectangleX.left();

      statusrectangleTrack.right() = statusrectangleTrack.left() + sizeTrack.cx();

      if (m_scrollinfo.nMax - m_scrollinfo.nMin - m_scrollinfo.nPage == 0)
      {

         statusrectangleTrack.top() = 0;

      }
      else
      {

         statusrectangleTrack.top() = rectangleX.top() + iScrollBarWidth + (iPos - m_scrollinfo.nMin) * iHeight / (m_scrollinfo.nMax - m_scrollinfo.nMin - m_scrollinfo.nPage);

      }

      statusrectangleTrack.bottom() = statusrectangleTrack.top() + sizeTrack.cy();

   }

   return statusrectangleTrack;

}


bool simple_scroll_bar::_001GetScrollInfo(::user::scroll_info * psi)
{

   psi->nPage = m_scrollinfo.nPage;
   psi->nPos = m_scrollinfo.nPos;
   psi->nMin = m_scrollinfo.nMin;
   psi->nMax = m_scrollinfo.nMax;
   psi->nTrackPos = m_scrollinfo.nTrackPos;

   return true;

}


bool simple_scroll_bar::_001SetScrollInfo(::user::scroll_info * psi, bool bRedraw)
{

   m_scrollinfo.nPage = psi->nPage;
   m_scrollinfo.nMin = psi->nMin;
   m_scrollinfo.nMax = psi->nMax;
   m_scrollinfo.nPos = psi->nPos;
   m_scrollinfo.nTrackPos = psi->nTrackPos;

   return true;

}


bool simple_scroll_bar::GetTrackClientRect(::rectangle_i32 * prectangle)
{

   auto pstyle = get_style();

   //int iScrollBarWidth = get_int(pstyle, ::user::e_int_scroll_bar_width);

   int iScrollBarWidth = scrollbar_width();

   ::rectangle_i32 rectangleX;

   rectangleX = this->rectangle();

   if (m_eorientation == e_orientation_horizontal)
   {
      //      i32 iWidth = rectangleX.width() - GetSystemMetrics(SM_CXHSCROLL) * 2;
      prectangle->bottom() = rectangleX.bottom() - 1;

      prectangle->top() = rectangleX.top() + 1;

      prectangle->left() = rectangleX.left() + iScrollBarWidth;

      prectangle->right() = rectangleX.right() - iScrollBarWidth;

   }
   else if (m_eorientation == e_orientation_vertical)
   {
      //      i32 iWidth = rectangleX.width() - GetSystemMetrics(SM_CYVSCROLL) * 2;
      prectangle->top() = rectangleX.top() + iScrollBarWidth;

      prectangle->bottom() = rectangleX.bottom() - iScrollBarWidth;

      prectangle->left() = rectangleX.left() + 1;

      prectangle->right() = rectangleX.right() - 1;

   }

   return true;

}


i32 simple_scroll_bar::GetTrackSize(::size_i32 & size)
{

   auto pstyle = get_style();

   //int iScrollBarWidth = get_int(pstyle, ::user::e_int_scroll_bar_width);

   int iScrollBarWidth = scrollbar_width();

   ::rectangle_i32 rectangleX;

   rectangleX = this->rectangle();

   if (m_eorientation == e_orientation_horizontal)
   {

      i32 iWidth = rectangleX.width() - iScrollBarWidth * 2;

      i32 cx = 0;

      if (iWidth > 0)
      {

         i32 iRange = (m_scrollinfo.nMax - m_scrollinfo.nMin);

         if (iRange == 0)
         {

            cx = 0;

         }
         else
         {

            cx = (m_scrollinfo.nPage * iWidth) / iRange;

         }

      }

      if (cx < 5)
      {

         cx = 5;

      }

      size.cx() = cx;

      size.cy() = rectangleX.height();

   }
   else if (m_eorientation == e_orientation_vertical)
   {

      i32 iHeight = rectangleX.height() - iScrollBarWidth * 2;

      i32 cy = 0;

      if (iHeight > 0)
      {

         i32 iRange = (m_scrollinfo.nMax - m_scrollinfo.nMin);

         if (iRange == 0)
         {

            cy = 0;

         }
         else
         {

            cy = (m_scrollinfo.nPage * iHeight) / iRange;

         }

      }

      if (cy < 5)
      {

         cy = 5;

      }

      size.cy() = cy;

      size.cx() = rectangleX.width();

   }

   return true;

}


i32 simple_scroll_bar::SetTrackingPos(const ::point_i32 & point)
{

   i32 nPos = 0;

   ::size_i32 sizeTrack;

   GetTrackSize(sizeTrack);

   ::rectangle_i32 rectangleX;

   rectangleX = this->rectangle();

   auto pstyle = get_style();

   //int iScrollBarWidth = get_int(pstyle, ::user::e_int_scroll_bar_width);

   int iScrollBarWidth = scrollbar_width();

   if (m_eorientation == e_orientation_horizontal)
   {

      i32 iWidth = rectangleX.width() - iScrollBarWidth * 2 - sizeTrack.cx();

      double dRate = (double)point.x() / (double)iWidth;

      dRate = minimum_maximum(dRate, 0.0, 1.0);

      nPos = (i32)(dRate * (m_scrollinfo.nMax - m_scrollinfo.nMin - m_scrollinfo.nPage));

      nPos += m_scrollinfo.nMin;

   }
   else if (m_eorientation == e_orientation_vertical)
   {

      i32 iHeight = rectangleX.height() - iScrollBarWidth * 2 - sizeTrack.cy();

      double dRate = (double)point.y() / (double)iHeight;

      dRate = minimum_maximum(dRate, 0.0, 1.0);

      nPos = (i32)(dRate * (m_scrollinfo.nMax - m_scrollinfo.nMin - m_scrollinfo.nPage));

      nPos += m_scrollinfo.nMin;

   }
   else
   {

      ASSERT(false);

   }

   if (nPos < m_scrollinfo.nMin)
   {

      nPos = m_scrollinfo.nMin;

   }
   else if (nPos > m_scrollinfo.nMax)
   {

      nPos = m_scrollinfo.nMax;

   }

   if (m_bTracking)
   {

      m_scrollinfo.nTrackPos = nPos;

   }
   else
   {

      m_scrollinfo.nPos = nPos;

   }

   update_rectangles();

   return true;

}


void simple_scroll_bar::_001OnHScroll(::message::message * pmessage)
{

   ::pointer<::message::scroll>pscroll(pmessage);

   pscroll->m_bRet = false;

}


i32 simple_scroll_bar::_001GetScrollPos()
{

   if (m_bTracking)
   {

      return m_scrollinfo.nTrackPos;

   }
   else
   {

      return m_scrollinfo.nPos;

   }

}


void simple_scroll_bar::on_layout(::draw2d::graphics_pointer & pgraphics)
{

   ::rectangle_i32 rectangleX;
   
   rectangleX = this->rectangle();

   auto pstyle = get_style();

   m_iScrollBarWidth = get_int(pstyle, ::user::e_int_scroll_bar_width);

   //::size_i32 size = rectangleX.size();

   //int iArrowForce = 4;
   //int iArrowStability = size.get_normal_dimension(m_eorientation) - 2 - 3 * 2;

   //auto pstyle = get_style(pgraphics);

   //int iScrollBarWidth = get_int(pstyle, ::user::e_int_scroll_bar_width);

   if (m_eorientation == e_orientation_horizontal)
   {

      //m_rectangleA.left()   = 0;
      //m_rectangleA.top()    = 0;
      //m_rectangleA.right()  = minimum(iScrollBarWidth,size.cx() / 2);
      //m_rectangleA.bottom() = size.cy();

      /*
      m_pointaA[0].x() = 0;
      m_pointaA[0].y() = size.cy() / 2;
      m_pointaA[1].x() = minimum(GetSystemMetrics(SM_CXHSCROLL), size.cx() / 2);
      m_pointaA[1].y() = size.cy() - 1;
      m_pointaA[2].x() = m_pointaA[1].x();
      m_pointaA[2].y() = 1;
      m_pointaA[3].x() = m_pointaA[0].x();
      m_pointaA[3].y() = m_pointaA[0].y();
      */

      //auto rectangleA = get_buttonA_rectangle(rectangleClinet)

      //m_pointaA[0].x() = m_rectangleA.left() + (m_rectangleA.width() + iArrowForce) / 2;
      //m_pointaA[0].y() = m_rectangleA.top() + (m_rectangleA.height() - iArrowStability) / 2;
      //m_pointaA[1].x() = m_rectangleA.left() + (m_rectangleA.width() - iArrowForce) / 2;
      //m_pointaA[1].y() = m_rectangleA.top() + m_rectangleA.height() / 2;
      //m_pointaA[2].x() = m_rectangleA.left() + (m_rectangleA.width() + iArrowForce) / 2;
      //m_pointaA[2].y() = m_rectangleA.top() + (m_rectangleA.height() + iArrowStability) / 2;;

      //m_rectangleB.left()   = maximum(size.cx() - iScrollBarWidth,size.cx() / 2);
      //m_rectangleB.top()    = 0;
      //m_rectangleB.right()  = size.cx();
      //m_rectangleB.bottom() = size.cy();

      /*
      m_pointaB[0].x() = size.cx();
      m_pointaB[0].y() = size.cy() / 2;
      m_pointaB[1].x() = ;
      m_pointaB[1].y() = 1;
      m_pointaB[2].x() = m_pointaB[1].x();
      m_pointaB[2].y() = size.cy() - 1;
      m_pointaB[3].x() = m_pointaB[0].x();
      m_pointaB[3].y() = m_pointaA[0].y();
      */

      //m_pointaB[0].x() = m_rectangleB.left() + (m_rectangleB.width() - iArrowForce) / 2;
      //m_pointaB[0].y() = m_rectangleB.top() + (m_rectangleB.height() - iArrowStability) / 2;
      //m_pointaB[1].x() = m_rectangleB.left() + (m_rectangleB.width() + iArrowForce) / 2;
      //m_pointaB[1].y() = m_rectangleB.top() + m_rectangleB.height() / 2;
      //m_pointaB[2].x() = m_rectangleB.left() + (m_rectangleB.width() - iArrowForce) / 2;
      //m_pointaB[2].y() = m_rectangleB.top() + (m_rectangleB.height() + iArrowStability) / 2;;

   }
   else if (m_eorientation == e_orientation_vertical)
   {

      //m_rectangleA.left()   = 0;
      //m_rectangleA.top()    = 0;
      //m_rectangleA.right()  = size.cx();
      //m_rectangleA.bottom() = minimum(iScrollBarWidth,size.cy() / 2);

      /*
      m_pointaA[0].x() = size.cx() / 2;
      m_pointaA[0].y() = 0;
      m_pointaA[1].x() = 1;
      m_pointaA[1].y() = minimum(GetSystemMetrics(SM_CYVSCROLL), size.cy() / 2);
      m_pointaA[2].x() = size.cx() - 1;
      m_pointaA[2].y() = m_pointaA[1].y();
      m_pointaA[3].x() = m_pointaA[0].x();
      m_pointaA[3].y() = m_pointaA[0].y();
      */

      //m_pointaA[0].x() = m_rectangleA.left() + (m_rectangleA.width() - iArrowStability) / 2;
      //m_pointaA[0].y() = m_rectangleA.top() + (m_rectangleA.height() + iArrowForce) / 2;
      //m_pointaA[1].x() = m_rectangleA.left() + m_rectangleA.width() / 2;
      //m_pointaA[1].y() = m_rectangleA.top() +( m_rectangleA.height() - iArrowForce) / 2;
      //m_pointaA[2].x() = m_rectangleA.left() + (m_rectangleA.width() + iArrowStability) / 2;
      //m_pointaA[2].y() = m_rectangleA.top() + (m_rectangleA.height() + iArrowForce) / 2;;

      //m_rectangleB.left()   = 0;
      //m_rectangleB.top()    = maximum(size.cy() - iScrollBarWidth,size.cy() / 2);
      //m_rectangleB.right()  = size.cx();
      //m_rectangleB.bottom() = size.cy();

      /*
      m_pointaB[0].x() = size.cx() / 2;
      m_pointaB[0].y() = size.cy();
      m_pointaB[1].x() = size.cx() - 1;
      m_pointaB[1].y() = maximum(size.cy() - GetSystemMetrics(SM_CYVSCROLL), size.cy() / 2);
      m_pointaB[2].x() = 1;
      m_pointaB[2].y() = m_pointaB[1].y();
      m_pointaB[3].x() = m_pointaA[0].x();
      m_pointaB[3].y() = m_pointaB[0].y();
      */
      //m_pointaB[0].x() = m_rectangleB.left() + (m_rectangleB.width() - iArrowStability) / 2;
      //m_pointaB[0].y() = m_rectangleB.top() + (m_rectangleB.height() - iArrowForce) / 2;
      //m_pointaB[1].x() = m_rectangleB.left() + m_rectangleB.width() / 2;
      //m_pointaB[1].y() = m_rectangleB.top() + (m_rectangleB.height() + iArrowForce) / 2;
      //m_pointaB[2].x() = m_rectangleB.left() + (m_rectangleB.width() + iArrowStability) / 2;
      //m_pointaB[2].y() = m_rectangleB.top() + (m_rectangleB.height() - iArrowForce) / 2;;
   }
   else
   {
      ASSERT(false);
   }

   update_rectangles();

   m_pregionA->create_rectangle(get_buttonA_rectangle(rectangleX));

   m_pregionB->create_rectangle(get_buttonB_rectangle(rectangleX));


   //   psize->m_bRet = false;
}


void simple_scroll_bar::_001OnTimer(::timer * ptimer)
{

   ::user::scroll_bar::_001OnTimer(ptimer);

   auto pointCursor = get_cursor_position();

   host_to_client()(pointCursor);

   if (ptimer->m_uEvent == (uptr)this)
   {

      KillTimer(ptimer->m_uEvent);

      SetTimer(((uptr)this) + 1, 10_ms, nullptr);

   }
   else if (ptimer->m_uEvent == ((uptr)this) + 1)
   {

      auto psystem = acmesystem()->m_paurasystem;

      auto pdraw2d = psystem->draw2d();

      auto pgraphics = pdraw2d->create_memory_graphics(this);

      if (!scrollbar_action(main_content().m_pitemCurrent))
      {

         KillTimer(ptimer->m_uEvent);

      }

   }

}


bool simple_scroll_bar::scrollbar_lineA()
{

   i32 nPos = m_scrollinfo.nPos;

   nPos -= 3;

   if (nPos < m_scrollinfo.nMin)
   {

      nPos = m_scrollinfo.nMin;

   }

   m_scrollinfo.nPos = nPos;

   if (m_eorientation == e_orientation_horizontal)
   {

      post_scroll_message(e_scroll_command_line_left);

   }
   else
   {

      post_scroll_message(e_scroll_command_line_up);

   }

   if (m_scrollinfo.nPos == m_scrollinfo.nMin)
   {

      return false;

   }

   return true;

}


bool simple_scroll_bar::scrollbar_lineB()
{

   i32 nPos = m_scrollinfo.nPos;

   nPos += 3;

   if (nPos > m_scrollinfo.nMax - m_scrollinfo.nPage)
   {

      nPos = m_scrollinfo.nMax - m_scrollinfo.nPage;

   }

   m_scrollinfo.nPos = nPos;

   if (m_eorientation == e_orientation_horizontal)
   {

      post_scroll_message(e_scroll_command_line_right);

   }
   else
   {

      post_scroll_message(e_scroll_command_line_down);

   }

   if (m_scrollinfo.nPos == m_scrollinfo.nMax - m_scrollinfo.nPage)
   {

      return false;

   }

   return true;

}


bool simple_scroll_bar::scrollbar_pageA(const ::point_i32 & point)
{

   i32 nPos = m_scrollinfo.nPos;

   nPos -= m_scrollinfo.nPage;

   if (nPos < m_scrollinfo.nMin)
   {

      nPos = m_scrollinfo.nMin;

   }

   m_scrollinfo.nPos = nPos;

   if (m_eorientation == e_orientation_horizontal)
   {

      post_scroll_message(e_scroll_command_page_left);

   }
   else
   {

      post_scroll_message(e_scroll_command_page_up);

   }

   auto rectangleX = this->rectangle();

   auto statusrectangleTrack = get_track_rectangle();

   auto statusrectanglePageA = get_pageA_rectangle(rectangleX, statusrectangleTrack);

   if (!statusrectanglePageA.ok() || !statusrectanglePageA.contains(point))
   {

      return false;

   }

   if (m_scrollinfo.nPos == m_scrollinfo.nMin)
   {

      return false;

   }

   return true;

}


bool simple_scroll_bar::scrollbar_pageB(const ::point_i32 & point)
{

   i32 nPos = m_scrollinfo.nPos;

   nPos += m_scrollinfo.nPage;

   if (nPos > m_scrollinfo.nMax - m_scrollinfo.nPage)
   {

      nPos = m_scrollinfo.nMax - m_scrollinfo.nPage;

   }

   m_scrollinfo.nPos = nPos;

   if (m_eorientation == e_orientation_horizontal)
   {

      post_scroll_message(e_scroll_command_page_right);

   }
   else
   {

      post_scroll_message(e_scroll_command_page_down);

   }

   auto rectangleX = this->rectangle();

   auto statusrectangleTrack = get_track_rectangle();

   auto statusrectanglePageB = get_pageB_rectangle(rectangleX, statusrectangleTrack);

   if (!statusrectanglePageB.ok() || !statusrectanglePageB.contains(point))
   {

      return false;

   }

   if (m_scrollinfo.nPos == m_scrollinfo.nMax - m_scrollinfo.nPage)
   {

      return false;

   }

   return true;

}


//void simple_scroll_bar::OnDraw(::image * pimage)
//{
/*    if(GetExStyle() & WS_EX_TRANSPARENT)
{
return;
}

::pointer<::user::interaction>puiParent = get_parent();
i32 nPos = m_scrollinfo.nPos;
nPos+=m_scrollinfo.nPage;
if(nPos > m_scrollinfo.nMax - m_scrollinfo.nPage)
nPos = m_scrollinfo.nMax - m_scrollinfo.nPage;
m_scrollinfo.nPos = nPos;

if(m_eorientation == e_orientation_horizontal)
{
puiParent->SendMessage(e_message_hscroll, MAKEWPARAM(e_scroll_command_LINERIGHT, m_scrollinfo.nPos), (LPARAM) this->get_handle());
}
else
{
puiParent->SendMessage(e_message_vscroll, MAKEWPARAM(e_scroll_command_LINEDOWN, m_scrollinfo.nPos), (LPARAM) this->get_handle());
}*/

//}


void simple_scroll_bar::on_message_create(::message::message * pmessage)
{

   m_ppenDraw.create(this);
   m_pbrushDraw.create(this);
   m_pregionA.create(this); // regiao da primeira seta
   m_pregionB.create(this); // regiao da segunda seta

   auto pitemScrollbarTrackbar = __new(::item(::item_t{ e_element_scrollbar_trackbar }));

   tool().add_item(pitemScrollbarTrackbar);

   enable_drag(pitemScrollbarTrackbar, ::user::e_zorder_front);

   ::pointer<::message::create>pcreate(pmessage);

   //if (m_puserstyle == nullptr)
   //{

   //   m_puserstyle = get_top_level();

   //}

   //if (m_puserstyle == nullptr)
   //{

   //   m_puserstyle = papp->userstyle();

   //}

   update_drawing_objects();

   pcreate->m_lresult = 0;

}


void simple_scroll_bar::pre_translate_message(::message::message * pmessage)
{

   ::pointer<::user::message>pusermessage(pmessage);

   return ::user::interaction::pre_translate_message(pusermessage);

}


void simple_scroll_bar::UpdateBitmaps()
{

}


::rectangle_i32 simple_scroll_bar::get_buttonA_rectangle(const ::rectangle_i32 & rectangleX)
{

   ::rectangle_i32 rectangleButtonA;

   auto pstyle = get_style();

   //int iScrollBarWidth = get_int(pstyle, ::user::e_int_scroll_bar_width);

   int iScrollBarWidth = scrollbar_width();

   if (m_eorientation == e_orientation_horizontal)
   {

      rectangleButtonA = rectangleX;

      rectangleButtonA.right() = rectangleButtonA.left() + iScrollBarWidth;

   }
   else if (m_eorientation == e_orientation_vertical)
   {

      rectangleButtonA = rectangleX;

      rectangleButtonA.bottom() = rectangleButtonA.top() + iScrollBarWidth;

   }

   return rectangleButtonA;

}


::rectangle_i32 simple_scroll_bar::get_buttonB_rectangle(const ::rectangle_i32 & rectangleX)
{

   ::rectangle_i32 rectangleButtonB;

   auto pstyle = get_style();

   //int iScrollBarWidth = get_int(pstyle, ::user::e_int_scroll_bar_width);

   int iScrollBarWidth = scrollbar_width();

   if (m_eorientation == e_orientation_horizontal)
   {

      rectangleButtonB = rectangleX;

      rectangleButtonB.left() = rectangleButtonB.right() - iScrollBarWidth;

   }
   else if (m_eorientation == e_orientation_vertical)
   {

      rectangleButtonB = rectangleX;

      rectangleButtonB.top() = rectangleButtonB.bottom() - iScrollBarWidth;

   }

   return rectangleButtonB;

}


::point_f64_array simple_scroll_bar::get_arrowA(const ::rectangle_i32 & rectangleX)
{

   //auto pstyle = get_style(pgraphics);

   //int iScrollBarWidth = get_int(pstyle, ::user::e_int_scroll_bar_width);

   int iScrollBarWidth = scrollbar_width();

   auto rectangleA = get_buttonA_rectangle(rectangleX);

   ::size_i32 size = rectangleX.size();

   point_f64_array pointaA;

   int iArrowForce = 4;

   int iArrowStability = size.get_normal_dimension(m_eorientation) - 2 - 3 * 2;

   if (m_eorientation == e_orientation_horizontal)
   {

      pointaA.add(
         rectangleA.left() + (rectangleA.width() + iArrowForce) / 2,
         rectangleA.top() + (rectangleA.height() - iArrowStability) / 2);

      pointaA.add(
         rectangleA.left() + (rectangleA.width() - iArrowForce) / 2,
         rectangleA.top() + rectangleA.height() / 2);

      pointaA.add(
         rectangleA.left() + (rectangleA.width() + iArrowForce) / 2,
         rectangleA.top() + (rectangleA.height() + iArrowStability) / 2);

   }
   else if (m_eorientation == e_orientation_vertical)
   {

      pointaA.add(
         rectangleA.left() + (rectangleA.width() - iArrowStability) / 2,
         rectangleA.top() + (rectangleA.height() + iArrowForce) / 2);

      pointaA.add(
         rectangleA.left() + rectangleA.width() / 2,
         rectangleA.top() + (rectangleA.height() - iArrowForce) / 2);

      pointaA.add(
         rectangleA.left() + (rectangleA.width() + iArrowStability) / 2,
         rectangleA.top() + (rectangleA.height() + iArrowForce) / 2);

   }

   return pointaA;

}


::point_f64_array simple_scroll_bar::get_arrowB(const ::rectangle_i32 & rectangleX)
{

   //auto pstyle = get_style(pgraphics);

   //int iScrollBarWidth = get_int(pstyle, ::user::e_int_scroll_bar_width);

   int iScrollBarWidth = scrollbar_width();

   auto rectangleB = get_buttonB_rectangle(rectangleX);

   ::size_i32 size = rectangleX.size();

   point_f64_array pointaB;

   int iArrowForce = 4;

   int iArrowStability = size.get_normal_dimension(m_eorientation) - 2 - 3 * 2;

   if (m_eorientation == e_orientation_horizontal)
   {

      pointaB.add(
         rectangleB.left() + (rectangleB.width() - iArrowForce) / 2,
         rectangleB.top() + (rectangleB.height() - iArrowStability) / 2);

      pointaB.add(
         rectangleB.left() + (rectangleB.width() + iArrowForce) / 2,
         rectangleB.top() + rectangleB.height() / 2);

      pointaB.add(
         rectangleB.left() + (rectangleB.width() - iArrowForce) / 2,
         rectangleB.top() + (rectangleB.height() + iArrowStability) / 2);

   }
   else if (m_eorientation == e_orientation_vertical)
   {

      pointaB.add(
         rectangleB.left() + (rectangleB.width() - iArrowStability) / 2,
         rectangleB.top() + (rectangleB.height() - iArrowForce) / 2);

      pointaB.add(
         rectangleB.left() + rectangleB.width() / 2,
         rectangleB.top() + (rectangleB.height() + iArrowForce) / 2);

      pointaB.add(
         rectangleB.left() + (rectangleB.width() + iArrowStability) / 2,
         rectangleB.top() + (rectangleB.height() - iArrowForce) / 2);

   }

   return pointaB;

}


::status < ::rectangle_i32 > simple_scroll_bar::get_pageA_rectangle(const ::rectangle_i32 & rectangleX, const ::rectangle_i32 & rectangleTrack)
{

   ::status < ::rectangle_i32 > statusrectanglePageA;

   auto pstyle = get_style();

   //int iScrollBarWidth = get_int(pstyle, ::user::e_int_scroll_bar_width);

   int iScrollBarWidth = scrollbar_width();

   if (m_eorientation == e_orientation_horizontal)
   {

      statusrectanglePageA.left() = rectangleX.left() + iScrollBarWidth;

      statusrectanglePageA.top() = rectangleTrack.top();

      statusrectanglePageA.right() = rectangleTrack.left();

      statusrectanglePageA.bottom() = rectangleTrack.bottom();

   }
   else if (m_eorientation == e_orientation_vertical)
   {

      statusrectanglePageA.left() = rectangleTrack.left();

      statusrectanglePageA.top() = rectangleX.top() + iScrollBarWidth;

      statusrectanglePageA.right() = rectangleTrack.right();

      statusrectanglePageA.bottom() = rectangleTrack.top();

   }

   return statusrectanglePageA;

}


::status < ::rectangle_i32 > simple_scroll_bar::get_pageB_rectangle(const ::rectangle_i32 & rectangleX, const ::rectangle_i32 & rectangleTrack)
{

   ::status < ::rectangle_i32 > statusrectanglePageB;

   auto pstyle = get_style();

   //int iScrollBarWidth = get_int(pstyle, ::user::e_int_scroll_bar_width);

   int iScrollBarWidth = scrollbar_width();

   if (m_eorientation == e_orientation_horizontal)
   {

      statusrectanglePageB.left() = rectangleTrack.right();

      statusrectanglePageB.top() = rectangleTrack.top();

      statusrectanglePageB.right() = rectangleX.right() - iScrollBarWidth;

      statusrectanglePageB.bottom() = rectangleTrack.bottom();

   }
   else if (m_eorientation == e_orientation_vertical)
   {

      statusrectanglePageB.left() = rectangleTrack.left();

      statusrectanglePageB.top() = rectangleTrack.bottom();

      statusrectanglePageB.right() = rectangleTrack.right();

      statusrectanglePageB.bottom() = rectangleX.bottom() - iScrollBarWidth;

   }

   return statusrectanglePageB;

}


i32 simple_scroll_bar::_001SetScrollPos(i32 iPos)
{

   m_scrollinfo.nPos = iPos;

   if (m_scrollinfo.nPos < m_scrollinfo.nMin)
   {

      m_scrollinfo.nPos = m_scrollinfo.nMin;

   }
   else if (m_scrollinfo.nPos > m_scrollinfo.nMax - m_scrollinfo.nPage)
   {

      m_scrollinfo.nPos = m_scrollinfo.nMax - m_scrollinfo.nPage;

   }
   
   //set_need_redraw();

   return true;

}


//LRESULT simple_scroll_bar::OnEconoModeChange(WPARAM wParam, LPARAM lParam)
//{
//   UNREFERENCED_PARAMETER(wParam);
//   UNREFERENCED_PARAMETER(lParam);
//   update_drawing_objects();
//   //set_need_redraw();
//
//   return true;
//}


void simple_scroll_bar::update_drawing_objects()
{

}


class trw :
   virtual public ::user::interaction
{
public:

   ::point_i32 point1;
   ::point_i32 point2;


   trw()
   {

      //auto pusersystem = __new(::user::system (WS_EX_LAYERED, nullptr, "", WS_VISIBLE));

      //if(create_window_ex(pusersystem))
      //if(create_host())
      create_host();
      //{

      //   information("created trw");

      //}

      best_monitor(nullptr, {}, true);

   }

   virtual ~trw()
   {

   }


   virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {
      pgraphics->set_current_point(point1);
      pgraphics->line_to(point2);
   }
};


// Important:
//
// The default _001OnClip implemenstation clips the current window
// to all ascending windows client area intersection.
// The client area of a window excludes its children scroll bars
// region.
// For the scroll bar, this algorithm would clip scroll bar child
// window from its drawing.
// This overload for this scroll bar overcomes this issue.
void simple_scroll_bar::_001OnClip(::draw2d::graphics_pointer & pgraphics)
{

   //pgraphics->reset_clip();

   //return;

   if (!m_bClipRectangle)
   {

      ::user::scroll_bar::_001OnClip(pgraphics);

   }
   else
   {

      ::user::scroll_bar::_001OnClip(pgraphics);

   }

   //try
   //{

      //pgraphics->reset_clip();

      //return;

      //::aura::draw_context * pdrawcontext = pgraphics->::aura::simple_chain < ::aura::draw_context >::get_last();

      //bool bFirst = true;
      //
      //if (pdrawcontext != nullptr)
      //{

      //   ::rectangle_i32 rectangleX;

      //   rectangleX = pdrawcontext->m_rectangleWindow;

      //   screen_to_client(rectangleX);

      //   rectangleX.bottom()++;
      //   rectangleX.right()++;

      //   rectangleClip = rectangleX;

      //   bFirst = false;

      //}

      //auto pinteractiondraw2d = get_draw2d();

   //   if(!m_pshapeaClip)
   //   {

   //      __construct_new(m_pshapeaClip);

   //      ::user::interaction * pinteraction = this;

   //      ::rectangle_i32 rectangleFocus;

   //      index i = 0;

   //      while (pinteraction != nullptr)
   //      {

   //         if (i == 1)
   //         {

   //            pinteraction->::user::interaction::this->rectangle(rectangleFocus);

   //         }
   //         else
   //         {

   //            pinteraction->rectangle(rectangleFocus);

   //         }

   //         pinteraction->client_to_screen(rectangleFocus);

   //         screen_to_client(rectangleFocus);

   //         m_pshapeaClip->add_item(__new(rectangle_shape(rectangleFocus)));

   //         m_pshapeaClip->add_item(__new(intersect_clip_shape()));

   //         i++;

   //         pinteraction = pinteraction->get_parent();

   //      }

   //   }

   //   pgraphics->reset_clip();

   //   pgraphics->m_pointAddShapeTranslate.Null();

   //   pgraphics->add_shapes(*m_pshapeaClip);

   //}
   //catch (...)
   //{

   //   throw ::exception("no more a window");

   //}

}


void simple_scroll_bar::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
{

   ::draw2d::save_context savecontext(pgraphics);

   //auto pointOffset = get_parent()->get_context_offset();

   //pgraphics->offset_origin(pointOffset.x(), pointOffset.y());

   //::user::style_context style(this);

   auto pstyle = get_style(pgraphics);

   if (pstyle)
   {

      if (pstyle->_001DrawSimpleScrollBar(pgraphics, this))
      {

         return;

      }

      //style.next();

   }

   //style = this;

   if (pstyle)
   {

      if (pstyle->_001DrawScrollBar(pgraphics, this))
      {

         return;

      }

      //   style.next();

   }

   _001OnVerisimpleDraw(pgraphics);

}


void simple_scroll_bar::_001OnVerisimpleDraw(::draw2d::graphics_pointer & pgraphics)
{

   //pgraphics->reset_clip();

   pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

   auto pstyle = get_style(pgraphics);

   auto colorBackground = get_color(pstyle, ::e_element_scrollbar);

   ::rectangle_i32 rectangleX;

   rectangleX = this->rectangle();

   pgraphics->fill_rectangle(rectangleX, colorBackground);

   auto statusrectangleTrack = get_track_rectangle();

   ::rectangle_i32 rectangleWindow;

   window_rectangle(rectangleWindow);

   auto colorRectStrong = scrollbar_color_strong(pstyle, ::e_element_scrollbar_trackbar);

   m_pbrushDraw->create_solid(colorRectStrong);

   pgraphics->set(m_pbrushDraw);

   pgraphics->fill_rectangle(statusrectangleTrack);

   //if (m_bTracking || (bool)prop("tracking_on"))
   //{

   //   ::u32 tickFadeIn = 300;

   //   ::u32 tickFadeOut = 300;

   //   ::u8 uchAlpha = maximum(0, minimum(255, prop("tracking_alpha").u32()));

   //   if (m_bTracking)
   //   {

   //      if (!(bool)prop("tracking_on"))
   //      {

   //         prop("tracking_on") = true;

   //         prop("tracking_start") = (u32)(::get_tick() + uchAlpha * tickFadeIn / 255);

   //         prop("tracking_fade_in") = true;

   //         prop("tracking_fade_out") = false;

   //         prop("tracking_type") = random(1, 2);

   //         if (prop("tracking_simple").i32() == 2)
   //         {

   //            int iDeflate = rectangleTrack.size().get_normal(m_eorientation);

   //            iDeflate /= 2;

   //            ::rectangle_i32 rectangleConstraint(m_statusrectangleTrack);

   //            rectangleConstraint.deflate(iDeflate, iDeflate);

   //            constraint(m_pointTrack, rectangleConstraint);

   //            m_sizeTrackOffset = m_pointTrack - m_statusrectangleTrack.top_left();

   //         }

   //      }

   //   }
   //   else
   //   {

   //      if (!(bool)prop("tracking_fade_out"))
   //      {

   //         prop("tracking_fade_in") = false;

   //         prop("tracking_fade_out") = true;

   //         prop("tracking_start") = (u32)(::get_tick() + (255 - uchAlpha) * tickFadeOut / 255);

   //      }

   //   }

   //   const ::point_i32 & point1 = rectangleTrack.top_left() + m_sizeTrackOffset;

   //   client_to_screen(point1);

   //   ::point_i32 point2;

   //   psession->get_cursor_position(&point2);

   //   client_to_screen(point1);

   //   if ((bool)prop("tracking_fade_in"))
   //   {

   //      ::u32 dwFade = prop("tracking_start").u32().elapsed();

   //      if (dwFade < tickFadeIn)
   //      {

   //         uchAlpha = (::u8)minimum(255, maximum(0, (dwFade * 255 / tickFadeIn)));

   //      }
   //      else
   //      {

   //         uchAlpha = 255;

   //         prop("tracking_fade_in") = false;

   //      }

   //   }
   //   else if ((bool)prop("tracking_fade_out"))
   //   {

   //      ::u32 dwFade = prop("tracking_start").u32().elapsed();

   //      if (dwFade < tickFadeOut)
   //      {

   //         uchAlpha = (::u8)(255 - minimum(255, maximum(0, (dwFade * 255 / tickFadeOut))));

   //      }
   //      else
   //      {

   //         uchAlpha = 0;

   //         prop("tracking_on") = false;

   //         prop("tracking_fade_out") = false;

   //      }

   //   }
   //   else
   //   {
   //      uchAlpha = 255;
   //   }

   //   ::rectangle_i32 rectangleMachineThumb;

   //   i32 iType = prop("tracking_type").i32();

   //   if (iType == 1)
   //   {

   //      int iSize = rectangleTrack.size().get_normal(m_eorientation);

   //      rectangleMachineThumb.top_left() = rectangleTrack.top_left() + m_sizeTrackOffset - size_i32(iSize / 2, iSize / 2);

   //      rectangleMachineThumb.bottom_right() = rectangleMachineThumb.top_left() + size(iSize, iSize);

   //      ::rectangle_i32 rectangleIntersect;

   //      rectangleIntersect.intersect(rectangleMachineThumb, rectangleTrack);

   //      i32 iArea = (i32)(maximum(1, rectangleIntersect.area()));

   //      rectangleMachineThumb.inflate(1 + iSize * (iSize * iSize) * 4 / (iArea * 5), 1 + iSize * (iSize * iSize) * 2 / (iArea * 3));

   //      draw_mac_thumb_simple(pgraphics, rectangleMachineThumb, rectangleTrack, uchAlpha);

   //   }
   //   else
   //   {

   //      int iSize = rectangleTrack.size().get_normal(m_eorientation);

   //      rectangleMachineThumb.top_left() = rectangleTrack.top_left() + m_sizeTrackOffset - size_i32(iSize / 2, iSize / 2);

   //      rectangleMachineThumb.set_size(iSize, iSize);

   //      rectangleMachineThumb.assign_normal(rectangleTrack, m_eorientation);

   //      draw_mac_thumb_dots(pgraphics, rectangleMachineThumb, rectangleTrack, uchAlpha);

   //   }

   //   prop("tracking_alpha") = uchAlpha;

   //}

   {

      auto color = scrollbar_color(pstyle, ::e_element_scrollbar_rectA);

      m_pbrushDraw->create_solid(color);

      pgraphics->set(m_pbrushDraw);

      auto rectangleA = get_buttonA_rectangle(rectangleX);

      pgraphics->fill_rectangle(rectangleA);

   }

   {

      auto color = scrollbar_color(pstyle, ::e_element_scrollbar_rectB);

      m_pbrushDraw->create_solid(color);

      pgraphics->set(m_pbrushDraw);

      auto rectangleB = get_buttonB_rectangle(rectangleX);

      pgraphics->fill_rectangle(rectangleB);

   }

   if (::is_element(main_content().m_pitemCurrent, ::e_element_scrollbar_pageA) || ::is_element(m_pitemHover, ::e_element_scrollbar_pageA))
   {

      auto statusrectanglePageA = get_pageA_rectangle(rectangleX, statusrectangleTrack);

      auto color = scrollbar_color(pstyle, ::e_element_scrollbar_pageA);

      m_pbrushDraw->create_solid(color);

      pgraphics->set(m_pbrushDraw);

      pgraphics->fill_rectangle(statusrectanglePageA);

   }
   else if (::is_element(main_content().m_pitemCurrent, ::e_element_scrollbar_pageB) || ::is_element(m_pitemHover, ::e_element_scrollbar_pageB))
   {

      auto statusrectanglePageB = get_pageB_rectangle(rectangleX, statusrectangleTrack);

      auto color = scrollbar_color(pstyle, ::e_element_scrollbar_pageB);

      m_pbrushDraw->create_solid(color);

      pgraphics->set(m_pbrushDraw);

      pgraphics->fill_rectangle(statusrectanglePageB);

   }

   {

      auto ppenArrow = __create < ::draw2d::pen >();

      ppenArrow->m_elinecapBeg = ::draw2d::e_line_cap_round;

      ppenArrow->m_elinecapEnd = ::draw2d::e_line_cap_round;

      ppenArrow->m_elinejoin = ::draw2d::e_line_join_round;

      {

         auto pointaA = get_arrowA(rectangleX);

         auto color = scrollbar_draw_color(pstyle, ::e_element_scrollbar_rectA);

         ppenArrow->create_solid(1.0, color);

         pgraphics->set(ppenArrow);

         pgraphics->polyline(pointaA);

      }

      {

         auto pointaB = get_arrowB(rectangleX);

         auto color = scrollbar_draw_color(pstyle, ::e_element_scrollbar_rectB);

         ppenArrow->create_solid(1.0, color);

         pgraphics->set(ppenArrow);

         pgraphics->polyline(pointaB);

      }

   }

}


void simple_scroll_bar::on_message_show_window(::message::message * pmessage)
{
   
   ::pointer<::message::show_window>pshowwindow(pmessage);
   
   pshowwindow->m_bRet = false;

   // xxx   TwiOnShowWindow(bShow, nStatus);

}


void simple_scroll_bar::on_message_destroy(::message::message * pmessage)
{

   UNREFERENCED_PARAMETER(pmessage);

}


void simple_scroll_bar::draw_mac_thumb_simple(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangleDrawParam, const ::rectangle_i32 & lpcrectClip, ::u8 uchAlpha)
{

   ::draw2d::save_context savecontext(pgraphics);

   pgraphics->reset_clip();

   ::rectangle_i32 rectangleDraw(rectangleDrawParam);

   rectangleDraw.deflate(1, 1);

   auto ppen = __create < ::draw2d::pen >();

   ppen->create_solid(2.0, argb(150 * uchAlpha / 255, 108, 108, 100));

   pgraphics->set(ppen);

   pgraphics->draw_ellipse(rectangleDraw);

   auto pbrush = __create < ::draw2d::brush >();

   ::rectangle_i32 rectangleDotto(0, 0, 5, 5);

   pbrush->create_solid(argb(150 * uchAlpha / 255, 108, 108, 100));

   pgraphics->set(pbrush);

   rectangleDotto.Align(e_align_center, rectangleDraw);

   pgraphics->fill_ellipse(rectangleDotto);

}


void simple_scroll_bar::draw_mac_thumb_dots(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangleDrawParam, const ::rectangle_i32 & lpcrectClip, ::u8 uchAlpha)
{

   ::rectangle_f64 rectangleDraw(rectangleDrawParam);

   rectangleDraw.bottom()--;

   rectangleDraw.right()--;

   double iDiv = 10;

   if (m_pimageDots->is_null())
   {

      //auto estatus = 

      __construct(m_pimageDots);

      //if (!estatus)
      //{

      //   return;

      //}

      //estatus =

      ::size_i32 size((::i32)(rectangleDraw.width() * iDiv), (::i32)(rectangleDraw.height() * iDiv));

      if (size.has_area())
      {

         m_pimageDots->create(size);

      }

      //if (!estatus)
      //{

      //   return;

      //}

      if (m_pimageDots.ok())
      {

         m_pimageDots->fill_byte(0);

         if (!m_pimageDots->g())
         {

            return;

         }

         m_pimageDots->g()->set_alpha_mode(::draw2d::e_alpha_mode_blend);

         double iDiv2 = iDiv / 2;

         double iDiv3 = iDiv2 / 2;

         double x = m_pimageDots->width() / (iDiv * 2);

         double iSize = iDiv3;

         for (int i = 0; i <= iDiv2; i++)
         {

            double y = m_pimageDots->height() / (iDiv * 2);

            for (int j = 0; j <= iDiv2; j++)
            {

               iSize = maximum(abs(m_pimageDots->width() / 2 - x), abs(m_pimageDots->width() / 2 - y));

               iSize = (m_pimageDots->width() / 2) - iSize;

               iSize = pow(iSize, 0.55);

               rectangle_f64 r(x - iSize, y - iSize, x + iSize, y + iSize);

               m_pimageDots->g()->fill_rectangle(r, argb(80, 0, 0, 0));

               y += m_pimageDots->height() / (iDiv2 + 1.0);

            }

            x += m_pimageDots->width() / (iDiv2 + 1.0);

         }

      }

   }

   pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

   pgraphics->set_interpolation_mode(::draw2d::e_interpolation_mode_high_quality_bicubic);

   auto rectangleTarget = rectangleDraw;

   auto pointSrc = ::point_f64(iDiv, iDiv);

   auto sizeSrc = m_pimageDots->get_size() - ::size_f64(iDiv * 2, iDiv * 2);

   auto rectangleSource = ::rectangle_f64(pointSrc, sizeSrc);

   image_source imagesource(m_pimageDots, rectangleSource);

   image_drawing_options imagedrawingoptions(rectangleTarget);

   image_drawing imagedrawing(imagedrawingoptions, imagesource);

   imagedrawing.opacity(uchAlpha);

   pgraphics->draw(imagedrawing);

}


void simple_scroll_bar::update_rectangles()
{

   auto statusrectangleTrack = get_track_rectangle();

   if (!statusrectangleTrack)
   {

      return;

   }

   {

      auto pitem = tool().item(e_element_scrollbar_trackbar);

      if (pitem)
      {

         auto puseritem = user_item(pitem);

         puseritem->m_rectangle = statusrectangleTrack;

      }

   }

   auto rectangleX = this->rectangle();

   //auto statusrectanglePageA = 
   {

      auto pitem = tool().item(e_element_scrollbar_pageA);

      if (pitem)
      {

         auto puseritem = user_item(pitem);

         puseritem->m_rectangle = get_pageA_rectangle(rectangleX, statusrectangleTrack);

      }

   }

   {

      auto pitem = tool().item(e_element_scrollbar_pageB);

      if (pitem)
      {

         auto puseritem = user_item(pitem);

         puseritem->m_rectangle = get_pageB_rectangle(rectangleX, statusrectangleTrack);

      }

   }

   {

      auto pitem = tool().item(e_element_scrollbar_rectA);

      if (pitem)
      {

         auto puseritem = user_item(pitem);

         puseritem->m_rectangle = get_buttonA_rectangle(rectangleX);

      }

   }

   {

      auto pitem = tool().item(e_element_scrollbar_rectB);

      if (pitem)
      {

         auto puseritem = user_item(pitem);

         puseritem->m_rectangle = get_buttonB_rectangle(rectangleX);

      }

   }

}


bool simple_scroll_bar::drag_shift(::item * pitem)
{

   if (pitem->m_item.m_eelement == e_element_scrollbar_trackbar)
   {

      auto pdrag = drag(pitem);

      auto pmouse = pdrag->m_pmouse;

      //auto point = pmouse->m_point - m_sizeTrackOffset - get_parent_accumulated_scroll();

      auto point = drag_point(pitem);

      //screen_to_client()(point);

      //queue_graphics_call([this, point](::draw2d::graphics_pointer & pgraphics)
        // {

      SetTrackingPos(point);

      post_scroll_message(e_scroll_command_thumb_track);

         //});

      set_need_redraw();

      post_redraw();

      //pmouse->m_lresult = 1;

      auto pcursor = get_mouse_cursor(e_cursor_arrow);

      pmouse->m_pcursor = pcursor;

      return true;

   }

   return false;

}


::point_i32 simple_scroll_bar::on_drag_start(::item * pitem)
{

   if (pitem->m_item.m_eelement == e_element_scrollbar_trackbar)
   {

      auto puseritem = user_item(pitem);

      auto pointInitial = puseritem->m_rectangle.origin();

      auto pointContextOffset = get_parent()->get_accumulated_scroll();

      pointInitial -= pointContextOffset;

      return pointInitial;

      //retu

   }

   throw exception(::error_unexpected);

}


//bool simple_scroll_bar::drag_shift(::item * pitem)
//{
//
//   if (pitem->m_item.m_eelement == e_element_client)
//   {
//
//      auto pdrag = drag(pitem);
//
//      pdrag->m_ecursor = e_cursor_move;
//
//      set_position(pdrag->point());
//
//      set_reposition();
//
//      //set_need_redraw();
//
//      post_redraw();
//
//      return true;
//
//   }
//   else if (pitem->m_item.m_eelement == e_element_resize)
//   {
//
//      auto pdrag = drag(pitem);
//
//      pdrag->m_ecursor = e_cursor_size_bottom_right;
//
//      auto Δ = pdrag->point() - pdrag->m_pointLButtonDown;
//
//      auto pointBottomRight = pdrag->m_pointInitial + Δ;
//
//      auto size = pointBottomRight - layout().window().origin();
//
//      auto sizeMinimum = get_window_minimum_size();
//
//      size = size.maximum(sizeMinimum);
//
//      information("drag_shift resize %d, %d", size.cx(), size.cy());
//
//      //auto rectanglePrevious = layout().window().raw_rectangle();
//
//      //layout().sketch().m_size = size;
//
//      set_size(size);
//
//      //set_need_layout();
//
//      //on_size_change_request(rectanglePrevious);
//
//      return true;
//
//   }
//
//   return false;
//
//}


//auto statusrectangleTrack = get_track_rectangle(pgraphics);

//if (statusrectangleTrack.contains(point))
//{

//   return __new(::item(::e_element_scrollbar_trackbar));

//}
//else
//{

//   auto rectangleX = this->rectangle();

//   auto statusrectanglePageA = get_pageA_rectangle(rectangleX, statusrectangleTrack, pgraphics);

//   if (statusrectanglePageA.contains(point))
//   {

//      return __new(::item(::e_element_scrollbar_pageA));

//   }

//   auto statusrectanglePageB = get_pageB_rectangle(rectangleX, statusrectangleTrack, pgraphics);

//   if (statusrectanglePageB.contains(point))
//   {

//      return __new(::item(::e_element_scrollbar_pageB));

//   }

   //if (get_buttonA_rectangle(rectangleX, pgraphics).contains(point))
   //{

   //   return __new(::item(::e_element_scrollbar_rectA));

   //}

   //if (get_buttonA_rectangle(rectangleX, pgraphics).contains(point))
   //{

   //   return __new(::item(::e_element_scrollbar_rectB));

   //}

//   auto pitemNone = __new(::item(e_element_none));

//   return pitemNone;

//}

//}


::item_pointer simple_scroll_bar::on_hit_test(const ::point_i32 & point, ::user::e_zorder ezorder)
{

   return ::user::interaction::on_hit_test(point, ezorder);

   ////::point_i32 point = pointClient - get_parent_accumulated_scroll();

   //auto pgraphics = get_internal_draw2d_graphics();

   //auto statusrectangleTrack = get_track_rectangle(pgraphics);

   //if (statusrectangleTrack.contains(point))
   //{

   //   return __new(::item(::e_element_scrollbar_trackbar));

   //}
   //else
   //{

   //   auto rectangleX = this->rectangle();

   //   auto statusrectanglePageA = get_pageA_rectangle(rectangleX, statusrectangleTrack, pgraphics);

   //   if (statusrectanglePageA.contains(point))
   //   {

   //      return __new(::item(::e_element_scrollbar_pageA));

   //   }

   //   auto statusrectanglePageB = get_pageB_rectangle(rectangleX, statusrectangleTrack, pgraphics);

   //   if (statusrectanglePageB.contains(point))
   //   {

   //      return __new(::item(::e_element_scrollbar_pageB));

   //   }

   //   if (get_buttonA_rectangle(rectangleX, pgraphics).contains(point))
   //   {

   //      return __new(::item(::e_element_scrollbar_rectA));

   //   }

   //   if (get_buttonA_rectangle(rectangleX, pgraphics).contains(point))
   //   {

   //      return __new(::item(::e_element_scrollbar_rectB));

   //   }

   //   auto pitemNone = __new(::item(e_element_none));

   //   return pitemNone;

   //}

}


::color::color simple_scroll_bar::scrollbar_color_strong(::user::style * pstyle, ::enum_element eelement)
{

   if (::is_element(main_content().m_pitemCurrent, eelement) || ::is_element(m_pitemHover, eelement))
   {

      auto color = get_color(pstyle, ::e_element_scrollbar_strong, ::user::e_state_hover);

      return color.is_ok() ? color : argb(130, 190, 180, 250);

   }
   else
   {

      auto color = get_color(pstyle, ::e_element_scrollbar_strong);

      return color.is_ok() ? color : argb(150, 150, 150, 150);

   }

}


::color::color simple_scroll_bar::scrollbar_color(::user::style * pstyle, ::enum_element eelement)
{

   if (::is_element(main_content().m_pitemCurrent, eelement) || ::is_element(m_pitemHover, eelement))
   {

      auto color = get_color(pstyle, eelement, ::user::e_state_hover);

      return color.is_ok() ? color : argb(100, 190, 180, 250);

   }
   else
   {

      auto color = get_color(pstyle, eelement);

      return color.is_ok() ? color : argb(150, 150, 150, 150);

   }

}


::color::color simple_scroll_bar::scrollbar_border_color(::user::style * pstyle, ::enum_element eelement)
{

   if (::is_element(main_content().m_pitemCurrent, eelement) || ::is_element(m_pitemHover, eelement))
   {

      auto color = get_color(pstyle, ::e_element_border, ::user::e_state_hover);

      return color.is_ok() ? color : argb(190, 180, 180, 180);

   }
   else
   {

      auto color = get_color(pstyle, ::e_element_border);

      return color.is_ok() ? color : argb(190, 160, 160, 160);

   }

}


::color::color simple_scroll_bar::scrollbar_lite_border_color(::user::style * pstyle, ::enum_element eelement)
{

   if (::is_element(main_content().m_pitemCurrent, eelement) || ::is_element(m_pitemHover, eelement))
   {

      auto color = get_color(pstyle, ::e_element_lite_border, ::user::e_state_hover);

      return color.is_ok() ? color : argb(190, 90, 110, 180);

   }
   else
   {

      auto color = get_color(pstyle, ::e_element_lite_border);

      return color.is_ok() ? color : argb(190, 110, 110, 100);

   }

}


::color::color simple_scroll_bar::scrollbar_draw_color(::user::style * pstyle, ::enum_element eelement)
{

   if (::is_element(main_content().m_pitemCurrent, eelement) || ::is_element(m_pitemHover, eelement))
   {

      auto color = get_color(pstyle, ::e_element_scrollbar_draw, ::user::e_state_hover);

      return color.is_ok() ? color : argb(127, 90, 90, 90);

   }
   else
   {

      auto color = get_color(pstyle, ::e_element_scrollbar_draw);

      return color.is_ok() ? color : argb(127, 65, 65, 65);

   }

}


::point_i32 simple_scroll_bar::drag_point(::item * pitem)
{

   return ::user::scroll_bar::drag_point(pitem);

   //auto pdrag = drag(pitem);

   //auto point = pdrag->m_pmouse->m_point;

   //screen_to_client()(point);

   //if (m_eorientation == e_orientation_horizontal)
   //{

   //   point.x() -= m_iScrollBarWidth;

   //}
   //else if (m_eorientation == e_orientation_vertical)
   //{

   //   point.y() -= m_iScrollBarWidth;

   //}

   //return point;

}


::i32 simple_scroll_bar::scrollbar_width()
{

   return m_iScrollBarWidth;

}



