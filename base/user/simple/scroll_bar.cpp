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
   //m_scrollstateaX[].nMin = 0;
   //m_pscrolllayout->m_scrollstatea[::user::e_layout_sketch].m_iMaximum = 100;
   //m_pscrolllayout->m_scrollstatea[::user::e_layout_sketch].m_iPage = 10;
   //m_pscrolllayout->m_scrollstatea[::user::e_layout_sketch].m_iPosition = 0;

   //m_iScrollBarThickness = 0;

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
   MESSAGE_LINK(e_message_scroll_x, pchannel, this, &simple_scroll_bar::on_message_scroll_x);

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


bool simple_scroll_bar::scrollbar_action(const ::item * pitem, ::user::enum_layout elayout)
{

   if (::is_null(pitem))
   {

      return false;

   }

   switch (pitem->m_item.m_eelement)
   {
   case ::e_element_scrollbar_rectA:
      return scrollbar_lineA(elayout);
   case ::e_element_scrollbar_rectB:
      return scrollbar_lineB(elayout);
   case ::e_element_scrollbar_pageA:
      return scrollbar_pageA(user_item(pitem)->m_pointClient, elayout);
   case ::e_element_scrollbar_pageB:
      return scrollbar_pageB(user_item(pitem)->m_pointClient, elayout);
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

   //auto psystem = system()->m_paurasystem;

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

   //   //auto psystem = system()->m_paurasystem;

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


::status < ::rectangle_f64 > simple_scroll_bar::get_track_rectangle(::user::enum_layout elayout)
{

   ::status < ::rectangle_f64 > statusrectangleTrack;

   ::rectangle_i32 rectangleX;

   rectangleX = this->raw_rectangle(elayout);

   auto parentAccumulatedScroll = get_parent()->get_parent_accumulated_scroll(elayout);

   rectangleX += parentAccumulatedScroll;

   auto sizeTrack = get_track_size(elayout);

   ::f64 dPosition;

   if (m_bTracking)
   {

      dPosition = m_pscrolllayout->m_scrollstatea[elayout].m_dTrackingPosition;

   }
   else
   {

      dPosition = m_pscrolllayout->m_scrollstatea[elayout].m_dPosition;

   }

   //auto pstyle = get_style();

   auto dScrollBarThickness = scroll_bar_thickness();

   if (m_eorientation == e_orientation_horizontal)
   {

      auto dWidth = rectangleX.width() - dScrollBarThickness * 2 - sizeTrack.cx();

      statusrectangleTrack.top() = rectangleX.top();

      statusrectangleTrack.bottom() = rectangleX.top() + sizeTrack.cy();

      if (m_pscrolllayout->m_scrollstatea[elayout].range() <= 0)
      {

         statusrectangleTrack.left() = rectangleX.left() + dPosition;

      }
      else
      {

         statusrectangleTrack.left() = rectangleX.left() + dPosition + dScrollBarThickness + (dPosition - m_pscrolllayout->m_scrollstatea[elayout].m_dMinimum) * dWidth / (m_pscrolllayout->m_scrollstatea[elayout].range());

      }

      statusrectangleTrack.right() = statusrectangleTrack.left() + sizeTrack.cx();

   }
   else if (m_eorientation == e_orientation_vertical)
   {

      auto dHeight = rectangleX.height() - dScrollBarThickness * 2 - sizeTrack.cy();

      statusrectangleTrack.left() = rectangleX.left();

      statusrectangleTrack.right() = statusrectangleTrack.left() + sizeTrack.cx();

      if (m_pscrolllayout->m_scrollstatea[elayout].range() <= 0)
      {

         statusrectangleTrack.top() = rectangleX.top() + dPosition;

      }
      else
      {

         statusrectangleTrack.top() = rectangleX.top() + dPosition + dScrollBarThickness + (dPosition - m_pscrolllayout->m_scrollstatea[elayout].m_dMinimum) * dHeight / (m_pscrolllayout->m_scrollstatea[elayout].range());

      }

      statusrectangleTrack.bottom() = statusrectangleTrack.top() + sizeTrack.cy();

   }

   return statusrectangleTrack;

}


//bool simple_scroll_bar::_001GetScrollState(::user::scroll_state * pscrollstate)
//{
//
//   *pscrollstate = m_scrollstate;
//   pscrollstate->nPos = m_pscrolllayout->m_scrollstatea[::user::e_layout_sketch].m_iPosition;
//   pscrollstate->nMin = m_pscrolllayout->m_scrollstatea[::user::e_layout_sketch].m_iMinimum;
//   pscrollstate->nMax = m_pscrolllayout->m_scrollstatea[::user::e_layout_sketch].m_iMaximum;
//   pscrollstate->nTrackPos = m_scrollinfo.nTrackPos;
//
//   return true;
//
//}
//
//
//bool simple_scroll_bar::_001SetScrollInfo(::user::scroll_state * psi, bool bRedraw)
//{
//
//   m_pscrolllayout->m_scrollstatea[::user::e_layout_sketch].m_iPage = psi->nPage;
//   m_pscrolllayout->m_scrollstatea[::user::e_layout_sketch].m_iMinimum = psi->nMin;
//   m_pscrolllayout->m_scrollstatea[::user::e_layout_sketch].m_iMaximum = psi->nMax;
//   m_pscrolllayout->m_scrollstatea[::user::e_layout_sketch].m_iPosition = psi->nPos;
//   m_scrollinfo.nTrackPos = psi->nTrackPos;
//
//   return true;
//
//}
//

//::rectangle_f64 simple_scroll_bar::get_track_client_rectangle()
//{
//
//   //auto pstyle = get_style();
//
//   //int iScrollBarThickness = get_int(pstyle, ::user::e_int_scroll_bar_thickness);
//
//   auto dScrollBarThickness = scroll_bar_thickness();
//
//   auto rectangle = this->rectangle();
//
//   auto rectangleTrackClient = rectangle;
//
//   if (m_eorientation == e_orientation_horizontal)
//   {
//      //      i32 iWidth = rectangleX.width() - GetSystemMetrics(SM_CXHSCROLL) * 2;
//      //rectangleTrackClient.bottom() = rectangle.bottom() - 1;
//
//      //rectangleTrackClient.top() = rectangle.top() + 1;
//
//      rectangleTrackClient.left() = rectangle.left() + dScrollBarThickness;
//
//      rectangleTrackClient.right() = rectangle.right() - dScrollBarThickness;
//
//   }
//   else if (m_eorientation == e_orientation_vertical)
//   {
//      //      i32 iWidth = rectangleX.width() - GetSystemMetrics(SM_CYVSCROLL) * 2;
//      rectangleTrackClient.top() = rectangle.top() + dScrollBarThickness;
//
//      rectangleTrackClient.bottom() = rectangle.bottom() - dScrollBarThickness;
//
//      //rectangleTrackClient.left() = rectangle.left() + 1;
//
//      //rectangleTrackClient.right() = rectangle.right() - 1;
//
//   }
//
//   return true;
//
//}
//


::size_f64 simple_scroll_bar::get_track_size(::user::enum_layout elayout)
{

   ///auto pstyle = get_style();

   //int iScrollBarThickness = get_int(pstyle, ::user::e_int_scroll_bar_thickness);

   auto dScrollBarThickness = scroll_bar_thickness();

   auto rectangleX = this->rectangle(elayout);

   ::size_f64 size;

   if (m_eorientation == e_orientation_horizontal)
   {

      auto dWidth = rectangleX.width() - dScrollBarThickness * 2.;

      ::f64 cx = 0;

      if (dWidth > 0)
      {

         auto dRange = (m_pscrolllayout->m_scrollstatea[elayout].m_dMaximum - m_pscrolllayout->m_scrollstatea[elayout].m_dMinimum);

         if (dRange <= 0.)
         {

            cx = 0;

         }
         else
         {

            cx = (m_pscrolllayout->m_scrollstatea[elayout].m_dPage * dWidth) / dRange;

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

      auto dHeight = rectangleX.height() - dScrollBarThickness * 2;

      ::f64 cy = 0.;

      if (dHeight > 0)
      {

         auto dRange = (m_pscrolllayout->m_scrollstatea[elayout].m_dMaximum - m_pscrolllayout->m_scrollstatea[elayout].m_dMinimum);

         if (dRange <= 0)
         {

            cy = 0.;

         }
         else
         {

            cy = (m_pscrolllayout->m_scrollstatea[elayout].m_dPage * dHeight) / dRange;

         }

      }

      if (cy < 5)
      {

         cy = 5;

      }

      size.cy() = cy;

      size.cx() = rectangleX.width();

   }

   return size;

}


void simple_scroll_bar::set_scroll_tracking_position(const ::point_f64 & point, ::user::enum_layout elayout)
{

   ::f64 dPos = 0.;

   auto sizeTrack = get_track_size(elayout);

   auto sizeScrollWindow = this->size();

   auto dScrollBarThickness = scroll_bar_thickness();

   if (m_eorientation == e_orientation_horizontal)
   {

      auto dWidth = sizeScrollWindow.cx() - dScrollBarThickness * 2 - sizeTrack.cx();

      double dRate = (point.x() - dScrollBarThickness) / dWidth;

      dRate = minimum_maximum(dRate, 0.0, 1.0);

      dPos = (dRate * (m_pscrolllayout->m_scrollstatea[elayout].range()));

      dPos += m_pscrolllayout->m_scrollstatea[elayout].m_dMinimum;

   }
   else if (m_eorientation == e_orientation_vertical)
   {

      auto dHeight = sizeScrollWindow.cy() - dScrollBarThickness * 2 - sizeTrack.cy();

      double dRate = (point.y() - dScrollBarThickness) / dHeight;

      dRate = minimum_maximum(dRate, 0.0, 1.0);

      dPos = (i32)(dRate * (m_pscrolllayout->m_scrollstatea[elayout].range()));

      dPos += m_pscrolllayout->m_scrollstatea[elayout].m_dMinimum;

   }
   else
   {

      ASSERT(false);

   }

   if (dPos < m_pscrolllayout->m_scrollstatea[elayout].m_dMinimum)
   {

      dPos = m_pscrolllayout->m_scrollstatea[elayout].m_dMinimum;

   }
   else if (dPos > m_pscrolllayout->m_scrollstatea[elayout].m_dMaximum - m_pscrolllayout->m_scrollstatea[elayout].m_dPage)
   {

      dPos = m_pscrolllayout->m_scrollstatea[elayout].m_dMaximum - m_pscrolllayout->m_scrollstatea[elayout].m_dPage;

   }

   //if (m_bTracking)
   //{

   //   m_pscrolllayout->m_scrollstatea[elayout].m_dTrackingPosition = dPos;

   //}
   //else
   //{

   //   m_pscrolllayout->m_scrollstatea[elayout].m_dPosition = dPos;

   //}

   post_scroll_message(e_scroll_command_thumb_track, dPos);

   //m_puserinteractionScrollBase->on_change_context_offset(elayout);

}


void simple_scroll_bar::on_message_scroll_x(::message::message * pmessage)
{

   ::pointer<::message::scroll>pscroll(pmessage);

   pscroll->m_bRet = false;

}


//i32 simple_scroll_bar::_001GetScrollPos()
//{
//
//   if (m_bTracking)
//   {
//
//      return m_pscrolllayout->m_scrollstatea[::user::e_layout_sketch].m_iTrackingPosition;
//
//   }
//   else
//   {
//
//      return m_pscrolllayout->m_scrollstatea[::user::e_layout_sketch].m_iPosition;
//
//   }
//
//}


void simple_scroll_bar::on_layout(::draw2d::graphics_pointer & pgraphics)
{

   ::rectangle_i32 rectangleX;
   
   rectangleX = this->rectangle();

   auto pstyle = get_style();

   m_pscrolllayout->m_scrollstatea[::user::e_layout_design].m_dThickness = (::f64) get_int(pstyle, ::user::e_int_scroll_bar_thickness);

   //::size_i32 size = rectangleX.size();

   //int iArrowForce = 4;
   //int iArrowStability = size.get_normal_dimension(m_eorientation) - 2 - 3 * 2;

   //auto pstyle = get_style(pgraphics);

   //int iScrollBarThickness = get_int(pstyle, ::user::e_int_scroll_bar_thickness);

   if (m_eorientation == e_orientation_horizontal)
   {

      //m_rectangleA.left()   = 0;
      //m_rectangleA.top()    = 0;
      //m_rectangleA.right()  = minimum(iScrollBarThickness,size.cx() / 2);
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

      //m_rectangleB.left()   = maximum(size.cx() - iScrollBarThickness,size.cx() / 2);
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
      //m_rectangleA.bottom() = minimum(iScrollBarThickness,size.cy() / 2);

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
      //m_rectangleB.top()    = maximum(size.cy() - iScrollBarThickness,size.cy() / 2);
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

   update_rectangles(::user::e_layout_design);

   m_pregionA->create_rectangle(get_buttonA_rectangle(rectangleX));

   m_pregionB->create_rectangle(get_buttonB_rectangle(rectangleX));


   //   psize->m_bRet = false;
}


void simple_scroll_bar::_001OnTimer(::timer * ptimer)
{

   ::user::scroll_bar::_001OnTimer(ptimer);

   //auto pointCursor = mouse_cursor_position();

   //host_to_client()(pointCursor);

   if (ptimer->m_uEvent == (uptr)this)
   {

      KillTimer(ptimer->m_uEvent);

      SetTimer(((uptr)this) + 1, 10_ms, nullptr);

   }
   else if (ptimer->m_uEvent == ((uptr)this) + 1)
   {

      auto psystem = system()->m_paurasystem;

      auto pdraw2d = psystem->draw2d();

      auto pgraphics = pdraw2d->create_memory_graphics(this);

      if (!scrollbar_action(main_content().m_pitemCurrent, ::user::e_layout_sketch))
      {

         KillTimer(ptimer->m_uEvent);

      }

   }

}


bool simple_scroll_bar::scrollbar_lineA(::user::enum_layout elayout)
{

   auto dPos = m_pscrolllayout->m_scrollstatea[elayout].m_dPosition;

   dPos -= m_pscrolllayout->m_scrollstatea[elayout].m_dLine;

   if (dPos < m_pscrolllayout->m_scrollstatea[elayout].m_dMinimum)
   {

      dPos = m_pscrolllayout->m_scrollstatea[elayout].m_dMinimum;

   }

   m_pscrolllayout->m_scrollstatea[elayout].m_dPosition = dPos;

   if (m_eorientation == e_orientation_horizontal)
   {

      post_scroll_message(e_scroll_command_line_left);

   }
   else
   {

      post_scroll_message(e_scroll_command_line_up);

   }

   if (m_pscrolllayout->m_scrollstatea[elayout].m_dPosition <= m_pscrolllayout->m_scrollstatea[elayout].m_dMinimum)
   {

      return false;

   }

   return true;

}


bool simple_scroll_bar::scrollbar_lineB(::user::enum_layout elayout)
{

   auto dPos = m_pscrolllayout->m_scrollstatea[elayout].m_dPosition;

   dPos += m_pscrolllayout->m_scrollstatea[elayout].m_dLine;

   if (dPos > m_pscrolllayout->m_scrollstatea[elayout].m_dMaximum - m_pscrolllayout->m_scrollstatea[elayout].m_dPage)
   {

      dPos = m_pscrolllayout->m_scrollstatea[elayout].m_dMaximum - m_pscrolllayout->m_scrollstatea[elayout].m_dPage;

   }

   m_pscrolllayout->m_scrollstatea[elayout].m_dPosition = dPos;

   if (m_eorientation == e_orientation_horizontal)
   {

      post_scroll_message(e_scroll_command_line_right);

   }
   else
   {

      post_scroll_message(e_scroll_command_line_down);

   }

   if (m_pscrolllayout->m_scrollstatea[elayout].m_dPosition >= m_pscrolllayout->m_scrollstatea[elayout].m_dMaximum - m_pscrolllayout->m_scrollstatea[elayout].m_dPage)
   {

      return false;

   }

   return true;

}


bool simple_scroll_bar::scrollbar_pageA(const ::point_i32 & point, ::user::enum_layout elayout)
{

   auto dPos = m_pscrolllayout->m_scrollstatea[elayout].m_dPosition;

   dPos -= m_pscrolllayout->m_scrollstatea[elayout].m_dPage;

   if (dPos < m_pscrolllayout->m_scrollstatea[elayout].m_dMinimum)
   {

      dPos = m_pscrolllayout->m_scrollstatea[elayout].m_dMinimum;

   }

   m_pscrolllayout->m_scrollstatea[elayout].m_dPosition = dPos;

   if (m_eorientation == e_orientation_horizontal)
   {

      post_scroll_message(e_scroll_command_page_left);

   }
   else
   {

      post_scroll_message(e_scroll_command_page_up);

   }

   auto rectangleX = this->rectangle(elayout);

   auto statusrectangleTrack = get_track_rectangle(elayout);

   auto statusrectanglePageA = get_pageA_rectangle(rectangleX, statusrectangleTrack);

   if (!statusrectanglePageA.ok() || !statusrectanglePageA.contains(point))
   {

      return false;

   }

   if (m_pscrolllayout->m_scrollstatea[elayout].m_dPosition <= m_pscrolllayout->m_scrollstatea[elayout].m_dMinimum)
   {

      return false;

   }

   return true;

}


bool simple_scroll_bar::scrollbar_pageB(const ::point_i32 & point, ::user::enum_layout elayout)
{

   auto dPos = m_pscrolllayout->m_scrollstatea[elayout].m_dPosition;

   dPos += m_pscrolllayout->m_scrollstatea[elayout].m_dPage;

   if (dPos > m_pscrolllayout->m_scrollstatea[elayout].m_dMaximum - m_pscrolllayout->m_scrollstatea[elayout].m_dPage)
   {

      dPos = m_pscrolllayout->m_scrollstatea[elayout].m_dMaximum - m_pscrolllayout->m_scrollstatea[elayout].m_dPage;

   }

   m_pscrolllayout->m_scrollstatea[elayout].m_dPosition = dPos;

   if (m_eorientation == e_orientation_horizontal)
   {

      post_scroll_message(e_scroll_command_page_right);

   }
   else
   {

      post_scroll_message(e_scroll_command_page_down);

   }

   auto rectangleX = this->rectangle(elayout);

   auto statusrectangleTrack = get_track_rectangle(elayout);

   auto statusrectanglePageB = get_pageB_rectangle(rectangleX, statusrectangleTrack);

   if (!statusrectanglePageB.ok() || !statusrectanglePageB.contains(point))
   {

      return false;

   }

   if (m_pscrolllayout->m_scrollstatea[elayout].m_dPosition >= m_pscrolllayout->m_scrollstatea[elayout].m_dMaximum - m_pscrolllayout->m_scrollstatea[elayout].m_dPage)
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
i32 nPos = m_pscrolllayout->m_scrollstatea[::user::e_layout_sketch].m_iPosition;
nPos+=m_pscrolllayout->m_scrollstatea[::user::e_layout_sketch].m_iPage;
if(nPos > m_pscrolllayout->m_scrollstatea[::user::e_layout_sketch].m_iMaximum - m_pscrolllayout->m_scrollstatea[::user::e_layout_sketch].m_iPage)
nPos = m_pscrolllayout->m_scrollstatea[::user::e_layout_sketch].m_iMaximum - m_pscrolllayout->m_scrollstatea[::user::e_layout_sketch].m_iPage;
m_pscrolllayout->m_scrollstatea[::user::e_layout_sketch].m_iPosition = nPos;

if(m_eorientation == e_orientation_horizontal)
{
puiParent->SendMessage(e_message_scroll_x, MAKEWPARAM(e_scroll_command_LINERIGHT, m_pscrolllayout->m_scrollstatea[::user::e_layout_sketch].m_iPosition), (LPARAM) this->get_handle());
}
else
{
puiParent->SendMessage(e_message_scroll_y, MAKEWPARAM(e_scroll_command_LINEDOWN, m_pscrolllayout->m_scrollstatea[::user::e_layout_sketch].m_iPosition), (LPARAM) this->get_handle());
}*/

//}


void simple_scroll_bar::on_message_create(::message::message * pmessage)
{

   __construct(m_ppenDraw);
   __construct(m_pbrushDraw);
   __construct(m_pregionA); // regiao da primeira seta
   __construct(m_pregionB); // regiao da segunda seta

   auto pitemScrollbarTrackbar = __allocate< ::item >(::item_t{ e_element_scrollbar_trackbar });

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


::rectangle_f64 simple_scroll_bar::get_buttonA_rectangle(const ::rectangle_f64 & rectangle)
{

   ::rectangle_f64 rectangleButtonA;

   //auto pstyle = get_style();

   //int iScrollBarThickness = get_int(pstyle, ::user::e_int_scroll_bar_thickness);

   auto dScrollBarThickness = scroll_bar_thickness();

   if (m_eorientation == e_orientation_horizontal)
   {

      rectangleButtonA = rectangle;

      rectangleButtonA.right() = rectangleButtonA.left() + dScrollBarThickness;

   }
   else if (m_eorientation == e_orientation_vertical)
   {

      rectangleButtonA = rectangle;

      rectangleButtonA.bottom() = rectangleButtonA.top() + dScrollBarThickness;

   }

   return rectangleButtonA;

}


::rectangle_f64 simple_scroll_bar::get_buttonB_rectangle(const ::rectangle_f64 & rectangle)
{

   ::rectangle_f64 rectangleButtonB;

   //auto pstyle = get_style();

   //int iScrollBarThickness = get_int(pstyle, ::user::e_int_scroll_bar_thickness);

   auto dScrollBarThickness = scroll_bar_thickness();

   if (m_eorientation == e_orientation_horizontal)
   {

      rectangleButtonB = rectangle;

      rectangleButtonB.left() = rectangleButtonB.right() - dScrollBarThickness;

   }
   else if (m_eorientation == e_orientation_vertical)
   {

      rectangleButtonB = rectangle;

      rectangleButtonB.top() = rectangleButtonB.bottom() - dScrollBarThickness;

   }

   return rectangleButtonB;

}


::point_f64_array simple_scroll_bar::get_arrowA(const ::rectangle_f64 & rectangle)
{

   //auto pstyle = get_style(pgraphics);

   //int iScrollBarThickness = get_int(pstyle, ::user::e_int_scroll_bar_thickness);

   //int iScrollBarThickness = scroll_bar_thickness();

   auto rectangleA = get_buttonA_rectangle(rectangle);

   ::size_i32 size = rectangle.size();

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


::point_f64_array simple_scroll_bar::get_arrowB(const ::rectangle_f64 & rectangle)
{

   //auto pstyle = get_style(pgraphics);

   //int iScrollBarThickness = get_int(pstyle, ::user::e_int_scroll_bar_thickness);

   //int iScrollBarThickness = scroll_bar_thickness();

   auto rectangleB = get_buttonB_rectangle(rectangle);

   ::size_i32 size = rectangle.size();

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


::status < ::rectangle_f64 > simple_scroll_bar::get_pageA_rectangle(const ::rectangle_f64 & rectangle, const ::rectangle_f64 & rectangleTrack)
{

   ::status < ::rectangle_f64 > statusrectanglePageA;

   //auto pstyle = get_style();

   //int iScrollBarThickness = get_int(pstyle, ::user::e_int_scroll_bar_thickness);

   auto dScrollBarThickness = scroll_bar_thickness();

   if (m_eorientation == e_orientation_horizontal)
   {

      statusrectanglePageA.left() = rectangle.left() + dScrollBarThickness;

      statusrectanglePageA.top() = rectangleTrack.top();

      statusrectanglePageA.right() = rectangleTrack.left();

      statusrectanglePageA.bottom() = rectangleTrack.bottom();

   }
   else if (m_eorientation == e_orientation_vertical)
   {

      statusrectanglePageA.left() = rectangleTrack.left();

      statusrectanglePageA.top() = rectangle.top() + dScrollBarThickness;

      statusrectanglePageA.right() = rectangleTrack.right();

      statusrectanglePageA.bottom() = rectangleTrack.top();

   }

   return statusrectanglePageA;

}


::status < ::rectangle_f64 > simple_scroll_bar::get_pageB_rectangle(const ::rectangle_f64 & rectangle, const ::rectangle_f64 & rectangleTrack)
{

   ::status < ::rectangle_f64 > statusrectanglePageB;

   ///auto pstyle = get_style();

   //int iScrollBarThickness = get_int(pstyle, ::user::e_int_scroll_bar_thickness);

   auto dScrollBarThickness = scroll_bar_thickness();

   if (m_eorientation == e_orientation_horizontal)
   {

      statusrectanglePageB.left() = rectangleTrack.right();

      statusrectanglePageB.top() = rectangleTrack.top();

      statusrectanglePageB.right() = rectangle.right() - dScrollBarThickness;

      statusrectanglePageB.bottom() = rectangleTrack.bottom();

   }
   else if (m_eorientation == e_orientation_vertical)
   {

      statusrectanglePageB.left() = rectangleTrack.left();

      statusrectanglePageB.top() = rectangleTrack.bottom();

      statusrectanglePageB.right() = rectangleTrack.right();

      statusrectanglePageB.bottom() = rectangle.bottom() - dScrollBarThickness;

   }

   return statusrectanglePageB;

}


//i32 simple_scroll_bar::_001SetScrollPos(i32 iPos)
//{
//
//   m_pscrolllayout->m_scrollstatea[::user::e_layout_sketch].m_iPosition = iPos;
//
//   if (m_pscrolllayout->m_scrollstatea[::user::e_layout_sketch].m_iPosition < m_pscrolllayout->m_scrollstatea[::user::e_layout_sketch].m_iMinimum)
//   {
//
//      m_pscrolllayout->m_scrollstatea[::user::e_layout_sketch].m_iPosition = m_pscrolllayout->m_scrollstatea[::user::e_layout_sketch].m_iMinimum;
//
//   }
//   else if (m_pscrolllayout->m_scrollstatea[::user::e_layout_sketch].m_iPosition > m_pscrolllayout->m_scrollstatea[::user::e_layout_sketch].m_iMaximum - m_pscrolllayout->m_scrollstatea[::user::e_layout_sketch].m_iPage)
//   {
//
//      m_pscrolllayout->m_scrollstatea[::user::e_layout_sketch].m_iPosition = m_pscrolllayout->m_scrollstatea[::user::e_layout_sketch].m_iMaximum - m_pscrolllayout->m_scrollstatea[::user::e_layout_sketch].m_iPage;
//
//   }
//   
//   //set_need_redraw();
//
//   return true;
//
//}


//LRESULT simple_scroll_bar::OnEconoModeChange(WPARAM wParam, LPARAM lParam)
//{
//   __UNREFERENCED_PARAMETER(wParam);
//   __UNREFERENCED_PARAMETER(lParam);
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

      //auto pusersystem = __allocate< ::user::system  >(WS_EX_LAYERED, nullptr, "", WS_VISIBLE);

      //if(create_window_ex(pusersystem))
      //if(create_host())
      //create_host(e_parallelization_synchronous);
      // 
      // 
      create_host();
      //{

      //   informationf("created trw");

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

   //         m_pshapeaClip->add_item(__allocate< rectangle_shape >(rectangleFocus));

   //         m_pshapeaClip->add_item(__allocate< intersect_clip_shape >());

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

   auto statusrectangleTrack = get_track_rectangle(::user::e_layout_design);

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

   __UNREFERENCED_PARAMETER(pmessage);

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


::rectangle_f64 simple_scroll_bar::_user_item_rectangle(::user::item * puseritem, ::user::enum_layout elayout)
{

   auto statusrectangleTrack = get_track_rectangle(elayout);

   if (!statusrectangleTrack)
   {

      return {};

   }

   if(puseritem->m_pitem->m_item.m_eelement == e_element_scrollbar_trackbar)
   {

      return statusrectangleTrack;

   }

   auto rectangleX = this->rectangle(elayout);

   if (puseritem->m_pitem->m_item.m_eelement == e_element_scrollbar_pageA)
   {

      auto rectangle = get_pageA_rectangle(rectangleX, statusrectangleTrack);

      return rectangle;

   }
   else if (puseritem->m_pitem->m_item.m_eelement == e_element_scrollbar_pageB)
   {

      auto rectangle = get_pageB_rectangle(rectangleX, statusrectangleTrack);

      return rectangle;

   }
   else if (puseritem->m_pitem->m_item.m_eelement == e_element_scrollbar_rectA)
   {

      auto rectangle = get_buttonA_rectangle(rectangleX);

      return rectangle;

   }
   else if (puseritem->m_pitem->m_item.m_eelement == e_element_scrollbar_rectB)
   {

      auto rectangle = get_buttonB_rectangle(rectangleX);

      return rectangle;

   }

   return ::user::scroll_bar::_user_item_rectangle(puseritem, elayout);

}


void simple_scroll_bar::update_rectangles(::user::enum_layout elayout)
{

   //auto statusrectangleTrack = get_track_rectangle(elayout);

   //if (!statusrectangleTrack)
   //{

   //   return;

   //}

   {

      auto pitem = tool().item(e_element_scrollbar_trackbar);

      if (pitem)
      {

         auto puseritem = user_item(pitem);

         puseritem->m_euseritemflag += ::user::e_item_flag_rectangle_callback;

//         puseritem->m_rectangle = statusrectangleTrack;

      }

   }

   //auto rectangleX = this->rectangle(elayout);

   //auto statusrectanglePageA = 
   {

      auto pitem = tool().item(e_element_scrollbar_pageA);

      if (pitem)
      {

         auto puseritem = user_item(pitem);

         puseritem->m_euseritemflag += ::user::e_item_flag_rectangle_callback;

         //puseritem->m_rectangle = get_pageA_rectangle(rectangleX, statusrectangleTrack);

      }

   }

   {

      auto pitem = tool().item(e_element_scrollbar_pageB);

      if (pitem)
      {

         auto puseritem = user_item(pitem);

         puseritem->m_euseritemflag += ::user::e_item_flag_rectangle_callback;

         //puseritem->m_rectangle = get_pageB_rectangle(rectangleX, statusrectangleTrack);

      }

   }

   {

      auto pitem = tool().item(e_element_scrollbar_rectA);

      if (pitem)
      {

         auto puseritem = user_item(pitem);

         puseritem->m_euseritemflag += ::user::e_item_flag_rectangle_callback;

         //puseritem->m_rectangle = get_buttonA_rectangle(rectangleX);

      }

   }

   {

      auto pitem = tool().item(e_element_scrollbar_rectB);

      if (pitem)
      {

         auto puseritem = user_item(pitem);

         puseritem->m_euseritemflag += ::user::e_item_flag_rectangle_callback;

         //puseritem->m_rectangle = get_buttonB_rectangle(rectangleX);

      }

   }

}


bool simple_scroll_bar::drag_shift(::item * pitem, ::user::mouse * pmouse)
{

   if (pitem->m_item.m_eelement == e_element_scrollbar_trackbar)
   {

      auto point = drag_point(pitem, pmouse);

      set_scroll_tracking_position(point);

      auto pcursor = get_mouse_cursor(e_cursor_arrow);

      user_mouse_set_cursor(pmouse, pcursor);

      return true;

   }

   return false;

}


bool simple_scroll_bar::on_drag_start(::point_i32 & point, ::item * pitem)
{

   if (pitem->m_item.m_eelement == e_element_scrollbar_trackbar)
   {

      auto puseritem = user_item(pitem);

      auto rectangle = user_item_rectangle(puseritem, ::user::e_layout_sketch);

      auto pointInitial = rectangle.origin();

      auto pointContextOffset = get_parent()->get_accumulated_scroll();

      pointInitial -= pointContextOffset;

      point = pointInitial;

      return true;

   }

   return false;

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
//      informationf("drag_shift resize %d, %d", size.cx(), size.cy());
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

//   return __allocate< ::item >(::e_element_scrollbar_trackbar);

//}
//else
//{

//   auto rectangleX = this->rectangle();

//   auto statusrectanglePageA = get_pageA_rectangle(rectangleX, statusrectangleTrack, pgraphics);

//   if (statusrectanglePageA.contains(point))
//   {

//      return __allocate< ::item >(::e_element_scrollbar_pageA);

//   }

//   auto statusrectanglePageB = get_pageB_rectangle(rectangleX, statusrectangleTrack, pgraphics);

//   if (statusrectanglePageB.contains(point))
//   {

//      return __allocate< ::item >(::e_element_scrollbar_pageB);

//   }

   //if (get_buttonA_rectangle(rectangleX, pgraphics).contains(point))
   //{

   //   return __allocate< ::item >(::e_element_scrollbar_rectA);

   //}

   //if (get_buttonA_rectangle(rectangleX, pgraphics).contains(point))
   //{

   //   return __allocate< ::item >(::e_element_scrollbar_rectB);

   //}

//   auto pitemNone = __allocate< ::item >(e_element_none);

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

   //   return __allocate< ::item >(::e_element_scrollbar_trackbar);

   //}
   //else
   //{

   //   auto rectangleX = this->rectangle();

   //   auto statusrectanglePageA = get_pageA_rectangle(rectangleX, statusrectangleTrack, pgraphics);

   //   if (statusrectanglePageA.contains(point))
   //   {

   //      return __allocate< ::item >(::e_element_scrollbar_pageA);

   //   }

   //   auto statusrectanglePageB = get_pageB_rectangle(rectangleX, statusrectangleTrack, pgraphics);

   //   if (statusrectanglePageB.contains(point))
   //   {

   //      return __allocate< ::item >(::e_element_scrollbar_pageB);

   //   }

   //   if (get_buttonA_rectangle(rectangleX, pgraphics).contains(point))
   //   {

   //      return __allocate< ::item >(::e_element_scrollbar_rectA);

   //   }

   //   if (get_buttonA_rectangle(rectangleX, pgraphics).contains(point))
   //   {

   //      return __allocate< ::item >(::e_element_scrollbar_rectB);

   //   }

   //   auto pitemNone = __allocate< ::item >(e_element_none);

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


::point_i32 simple_scroll_bar::drag_point(::item * pitem, ::user::mouse * pmouse)
{

   return ::user::scroll_bar::drag_point(pitem, pmouse);

   //auto pdrag = drag(pitem);

   //auto point = pdrag->m_pmouse->m_point;

   //screen_to_client()(point);

   //if (m_eorientation == e_orientation_horizontal)
   //{

   //   point.x() -= m_iScrollBarThickness;

   //}
   //else if (m_eorientation == e_orientation_vertical)
   //{

   //   point.y() -= m_iScrollBarThickness;

   //}

   //return point;

}


//::i32 simple_scroll_bar::scroll_bar_thickness()
//{
//
//   return m_pscrolllayout->m_scrollstatea[::user::e_layout_sketch].m_dThickness;
//
//}
//


