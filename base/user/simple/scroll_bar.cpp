#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "base/user/simple/_simple.h"
#endif


simple_scroll_bar::simple_scroll_bar() :
   m_penDraw(e_create),
   m_brushDraw(e_create),
   m_rgnA(e_create), // região da primeira seta
   m_rgnB(e_create) // região da segunda seta
{

   //m_brushNull->CreateStockObject(NULL_BRUSH);
   m_flagNonClient.remove(non_client_background);
   // m_flagNonClient.remove(non_client_focus_rect);
   m_bTracking          = false;
   m_scrollinfo.nMin    = 0;
   m_scrollinfo.nMax    = 100;
   m_scrollinfo.nPage   = 10;
   m_scrollinfo.nPos    = 0;


   //m_cr = ARGB(127,180,80,120);
   //m_crStrong = ARGB(150, 150, 150, 150);
   //m_crBorder = ARGB(190, 180, 180, 180);
   //m_crLiteBorder = ARGB(184,84 + 23,84 + 23,77 + 23);

   //m_crHover = ARGB(100,190,180,250);
   //m_crHoverStrong = ARGB(130, 190, 180, 250);
   //m_crHoverBorder = ARGB(190, 160, 150, 180);
   //m_crHoverLiteBorder = ARGB(184,84 + 23 - 23,84 + 23,77 + 23 + 84);

}

simple_scroll_bar::~simple_scroll_bar()
{
}


void simple_scroll_bar::install_message_routing(::channel * pchannel)
{
   ::user::interaction::install_message_routing(pchannel);
   MESSAGE_LINK(e_message_create, pchannel, this, &simple_scroll_bar::_001OnCreate);
   MESSAGE_LINK(e_message_destroy, pchannel, this, &simple_scroll_bar::_001OnDestroy);
   MESSAGE_LINK(e_message_show_window, pchannel, this, &simple_scroll_bar::_001OnShowWindow);
   MESSAGE_LINK(e_message_mouse_move, pchannel, this, &simple_scroll_bar::_001OnMouseMove);
   MESSAGE_LINK(e_message_left_button_down, pchannel, this, &simple_scroll_bar::_001OnLButtonDown);
   MESSAGE_LINK(e_message_left_button_up, pchannel, this, &simple_scroll_bar::_001OnLButtonUp);
   MESSAGE_LINK(e_message_hscroll, pchannel, this, &simple_scroll_bar::_001OnHScroll);

}


bool simple_scroll_bar::create_window(const char * pszClassName, const char * pszWindowName, u32 uStyle, ::user::interaction * puiParent, const ::id & id, ::create * pcreate)
{

   if(!::user::interaction::create_window(pszClassName, pszWindowName, uStyle, puiParent, id, pcreate))
   {

      return false;

   }

   return true;

}


bool simple_scroll_bar::create_window(e_orientation eorientation, u32 uStyle, ::user::interaction * puiParent, ::id id)
{

   if(!::user::scroll_bar::create_window(eorientation, uStyle, puiParent, id))
   {

      return false;

   }

   return true;

}


void simple_scroll_bar::_001OnMouseMove(::message::message * pmessage)
{

   SCAST_PTR(::message::mouse, pmouse, pmessage);

   ::point point = screen_to_client(pmouse->m_point);

   if(m_bTracking)
   {

      point -= m_sizeTrackOffset;

      SetTrackingPos(point);

      send_scroll_message(SB_THUMBTRACK);

      pmouse->m_lresult = 1;

      //pmouse->m_bRet = true;

      pmouse->m_ecursor = cursor_arrow;

   }
   else
   {

      auto eelement = hit_test(pmouse);

      if(eelement.is_set())
      {

         pmouse->m_ecursor = cursor_arrow;

      }

   }


}


bool simple_scroll_bar::scrollbar_action(const ::user::item & item)
{

   switch(item.m_eelement)
   {
   case ::user::element_scrollbar_rectA:
      return scrollbar_lineA();
   case ::user::element_scrollbar_rectB:
      return scrollbar_lineB();
   case ::user::element_scrollbar_pageA:
      return scrollbar_pageA(item.m_pointClient);
   case ::user::element_scrollbar_pageB:
      return scrollbar_pageB(item.m_pointClient);
   default:
      return false;
   }

}

void simple_scroll_bar::_001OnLButtonDown(::message::message * pmessage)
{

   SCAST_PTR(::message::mouse, pmouse, pmessage);

   m_itemCurrent = hit_test(pmouse);

   if(!m_itemCurrent.is_set())
   {

      pmouse->m_bRet = false;

      return;

   }

   pmouse->m_bRet = true;

   pmouse->m_lresult = 1;

   SetCapture();

   if(m_itemCurrent == ::user::element_scrollbar_rect)
   {

      m_bTracking = true;

      SetTimer(43212345, 10, nullptr);

      m_pointTrack = m_itemCurrent.m_pointClient;

      GetTrackRect(m_rectTrack);

      m_sizeTrackOffset = m_pointTrack - m_rectTrack.top_left();

   }
   else
   {

      if(scrollbar_action(m_itemCurrent))
      {

         SetTimer((uptr) this,300,nullptr);

      }

   }

}

void simple_scroll_bar::_001OnLButtonUp(::message::message * pmessage)
{

   SCAST_PTR(::message::mouse, pmouse, pmessage);

   m_itemCurrent = ::user::element_none;

   KillTimer(((uptr)this));

   KillTimer(((uptr)this)+1);

   ReleaseCapture();

   pmouse->m_bRet = false;

   auto psession = Session;

   simple_scroll_bar * pcapture = psession->GetCapture().cast < simple_scroll_bar >();

   if((pcapture != nullptr && pcapture == this) || m_bTracking)
   {

      KillTimer(43212345);

      bool bWasTracking = m_bTracking;

      m_bTracking = false;

      if(bWasTracking)
      {

         auto point = screen_to_client(pmouse->m_point);

         point -= m_sizeTrackOffset;

         SetTrackingPos(point);

      }

      send_scroll_message(SB_THUMBPOSITION);

      set_need_redraw();

   }

}


bool simple_scroll_bar::GetTrackRect(RECT32 * prect)
{

   ::rect rectClient;

   get_client_rect(rectClient);

   ::size sizeTrack;

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

   if(m_eorientation == orientation_horizontal)
   {

      i32 iWidth = rectClient.width() - GetSystemMetrics(SM_CXHSCROLL) * 2 - sizeTrack.cx;

      prect->top = rectClient.top;


      prect->bottom = rectClient.top + sizeTrack.cy;


      if (m_scrollinfo.nMax - m_scrollinfo.nMin - m_scrollinfo.nPage == 0)
      {

         prect->left = 0;


      }
      else
      {

         prect->left = GetSystemMetrics(SM_CXHSCROLL) + (iPos - m_scrollinfo.nMin) * iWidth / (m_scrollinfo.nMax - m_scrollinfo.nMin - m_scrollinfo.nPage);


      }

      prect->right = prect->left + sizeTrack.cx;


   }
   else if(m_eorientation == orientation_vertical)
   {

      i32 iHeight = rectClient.height() - GetSystemMetrics(SM_CYVSCROLL) * 2 - sizeTrack.cy;

      prect->left = rectClient.left;


      prect->right = prect->left + sizeTrack.cx;


      if (m_scrollinfo.nMax - m_scrollinfo.nMin - m_scrollinfo.nPage == 0)
      {

         prect->top = 0;


      }
      else
      {

         prect->top = GetSystemMetrics(SM_CYVSCROLL) + (iPos - m_scrollinfo.nMin) * iHeight / (m_scrollinfo.nMax - m_scrollinfo.nMin - m_scrollinfo.nPage);


      }

      prect->bottom = prect->top + sizeTrack.cy;


   }

   return true;

}


bool simple_scroll_bar::_001GetScrollInfo(::user::scroll_info * psi)

{
   if(psi->fMask & SIF_PAGE)

   {
      psi->nPage = m_scrollinfo.nPage;

   }
   if(psi->fMask & SIF_POS)

   {
      psi->nPos = m_scrollinfo.nPos ;

   }
   if(psi->fMask & SIF_RANGE)

   {
      psi->nMin = m_scrollinfo.nMin;

      psi->nMax = m_scrollinfo.nMax;

   }
   if(psi->fMask & SIF_TRACKPOS)

   {
      psi->nTrackPos = m_scrollinfo.nTrackPos;

   }
   return TRUE;
}

bool simple_scroll_bar::_001SetScrollInfo(::user::scroll_info * psi, bool bRedraw)

{
   if(psi->fMask & SIF_PAGE)

   {
      m_scrollinfo.nPage = psi->nPage;

   }
   if(psi->fMask & SIF_RANGE)

   {
      m_scrollinfo.nMin = psi->nMin;

      m_scrollinfo.nMax = psi->nMax;

   }
   if(psi->fMask & SIF_POS)

   {
      m_scrollinfo.nPos = psi->nPos ;

      if(m_scrollinfo.nPos < m_scrollinfo.nMin)
      {
         m_scrollinfo.nPos = m_scrollinfo.nMin;
      }
      else if(m_scrollinfo.nPos > m_scrollinfo.nMax - m_scrollinfo.nPage)
      {
         m_scrollinfo.nPos = m_scrollinfo.nMax - m_scrollinfo.nPage;
      }
   }
   if(psi->fMask & SIF_TRACKPOS)

   {
      m_scrollinfo.nTrackPos = psi->nTrackPos;

   }
   if(bRedraw)
   {
      //      set_need_redraw();
   }
   return TRUE;
   m_scrollinfo.fMask = SIF_ALL;
   // trans   ::user::interaction::SetScrollInfo(SB_CTL, &m_scrollinfo);
   return true;
}


bool simple_scroll_bar::GetTrackClientRect(RECT32 * prect)

{

   ::rect rectClient;

   get_client_rect(rectClient);

   if(m_eorientation == orientation_horizontal)
   {
//      i32 iWidth = rectClient.width() - GetSystemMetrics(SM_CXHSCROLL) * 2;
      prect->bottom = rectClient.bottom;

      prect->top = rectClient.top;

      prect->left = rectClient.left + GetSystemMetrics(SM_CXHSCROLL);

      prect->right = rectClient.right - GetSystemMetrics(SM_CXHSCROLL);

   }
   else if(m_eorientation == orientation_vertical)
   {
//      i32 iWidth = rectClient.width() - GetSystemMetrics(SM_CYVSCROLL) * 2;
      prect->top = rectClient.top + GetSystemMetrics(SM_CYVSCROLL);

      prect->bottom = rectClient.bottom - GetSystemMetrics(SM_CYVSCROLL);

      prect->left = rectClient.left + 1;

      prect->right = rectClient.right - 1;

   }

   return true;

}


i32 simple_scroll_bar::GetTrackSize(::size &size)
{

   ::rect rectClient;

   get_client_rect(rectClient);

   if(m_eorientation == orientation_horizontal)
   {

      i32 iWidth = rectClient.width() - GetSystemMetrics(SM_CXHSCROLL) * 2;

      i32 cx = 0;

      if(iWidth > 0)
      {

         i32 iRange = (m_scrollinfo.nMax - m_scrollinfo.nMin);

         if (iRange == 0)
         {

            cx = 0;

         }
         else
         {

            cx = (m_scrollinfo.nPage  * iWidth) / iRange;

         }

      }

      if (cx < 5)
      {

         cx = 5;

      }

      size.cx = cx;

      size.cy = rectClient.height();

   }
   else if(m_eorientation == orientation_vertical)
   {

      i32 iHeight = rectClient.height() - GetSystemMetrics(SM_CYVSCROLL) * 2;

      i32 cy = 0;

      if(iHeight > 0)
      {

         i32 iRange = (m_scrollinfo.nMax - m_scrollinfo.nMin);

         if (iRange == 0)
         {

            cy = 0;

         }
         else
         {

            cy = (m_scrollinfo.nPage  * iHeight) / iRange;

         }

      }

      if (cy < 5)
      {

         cy = 5;

      }

      size.cy = cy;

      size.cx = rectClient.width();

   }

   return true;

}


i32 simple_scroll_bar::SetTrackingPos(const ::point & point)
{

   i32 nPos = 0;

   ::size sizeTrack;

   GetTrackSize(sizeTrack);

   ::rect rectClient;

   get_client_rect(rectClient);

   if(m_eorientation == orientation_horizontal)
   {

      i32 iWidth = rectClient.width() - GetSystemMetrics(SM_CXHSCROLL) * 2 - sizeTrack.cx;

      double dRate = (double)(point.x - GetSystemMetrics(SM_CXHSCROLL)) / (double)iWidth;

      dRate = min(1.0, dRate);

      nPos = (i32)(dRate * (m_scrollinfo.nMax - m_scrollinfo.nMin - m_scrollinfo.nPage));

      nPos += m_scrollinfo.nMin;

   }
   else if(m_eorientation == orientation_vertical)
   {

      i32 iHeight = rectClient.height() - GetSystemMetrics(SM_CYVSCROLL) * 2 - sizeTrack.cy;

      double dRate = (double)(point.y - GetSystemMetrics(SM_CYVSCROLL)) / (double) iHeight;

      dRate = min(1.0, dRate);

      nPos = (i32) (dRate * (m_scrollinfo.nMax - m_scrollinfo.nMin - m_scrollinfo.nPage));

      nPos += m_scrollinfo.nMin;

   }
   else
   {

      ASSERT(FALSE);

   }

   if (nPos < m_scrollinfo.nMin)
   {

      nPos = m_scrollinfo.nMin;

   }
   else if (nPos > m_scrollinfo.nMax)
   {

      nPos = m_scrollinfo.nMax;

   }

   if(m_bTracking)
   {

      m_scrollinfo.nTrackPos = nPos;

   }
   else
   {

      m_scrollinfo.nPos = nPos;

   }

   m_scrollinfo.fMask = SIF_ALL;

   return true;

}


void simple_scroll_bar::_001OnHScroll(::message::message * pmessage)
{
   SCAST_PTR(::message::scroll, pscroll, pmessage);
   pscroll->m_bRet = false;
}

i32 simple_scroll_bar::_001GetScrollPos()
{
   if(m_bTracking)
      return m_scrollinfo.nTrackPos;
   else
      return m_scrollinfo.nPos;
}



void simple_scroll_bar::on_layout(::draw2d::graphics_pointer & pgraphics)
{

   ::rect rectClient;
   get_client_rect(rectClient);
   ::size size = rectClient.size();

   int iArrowForce = 4;
   int iArrowStability = size.get_orthogonal_dimension(m_eorientation) - 2 - 3 * 2;

   if(m_eorientation == orientation_horizontal)
   {

      m_rectA.left   = 0;
      m_rectA.top    = 0;
      m_rectA.right  = min(GetSystemMetrics(SM_CXHSCROLL),size.cx / 2);
      m_rectA.bottom = size.cy;

      /*
      m_ptaA[0].x = 0;
      m_ptaA[0].y = size.cy / 2;
      m_ptaA[1].x = min(GetSystemMetrics(SM_CXHSCROLL), size.cx / 2);
      m_ptaA[1].y = size.cy - 1;
      m_ptaA[2].x = m_ptaA[1].x;
      m_ptaA[2].y = 1;
      m_ptaA[3].x = m_ptaA[0].x;
      m_ptaA[3].y = m_ptaA[0].y;
      */

      m_ptaA[0].x = m_rectA.left + (m_rectA.width() + iArrowForce) / 2;
      m_ptaA[0].y = m_rectA.top + (m_rectA.height() - iArrowStability) / 2;
      m_ptaA[1].x = m_rectA.left + (m_rectA.width() - iArrowForce) / 2;
      m_ptaA[1].y = m_rectA.top + m_rectA.height() / 2;
      m_ptaA[2].x = m_rectA.left + (m_rectA.width() + iArrowForce) / 2;
      m_ptaA[2].y = m_rectA.top + (m_rectA.height() + iArrowStability) / 2;;

      m_rectB.left   = max(size.cx - GetSystemMetrics(SM_CXHSCROLL),size.cx / 2);
      m_rectB.top    = 0;
      m_rectB.right  = size.cx;
      m_rectB.bottom = size.cy;

      /*
      m_ptaB[0].x = size.cx;
      m_ptaB[0].y = size.cy / 2;
      m_ptaB[1].x = ;
      m_ptaB[1].y = 1;
      m_ptaB[2].x = m_ptaB[1].x;
      m_ptaB[2].y = size.cy - 1;
      m_ptaB[3].x = m_ptaB[0].x;
      m_ptaB[3].y = m_ptaA[0].y;
      */

      m_ptaB[0].x = m_rectB.left + (m_rectB.width() - iArrowForce) / 2;
      m_ptaB[0].y = m_rectB.top + (m_rectB.height() - iArrowStability) / 2;
      m_ptaB[1].x = m_rectB.left + (m_rectB.width() + iArrowForce) / 2;
      m_ptaB[1].y = m_rectB.top + m_rectB.height() / 2;
      m_ptaB[2].x = m_rectB.left + (m_rectB.width() - iArrowForce) / 2;
      m_ptaB[2].y = m_rectB.top + (m_rectB.height() + iArrowStability) / 2;;

   }
   else if(m_eorientation == orientation_vertical)
   {

      m_rectA.left   = 0;
      m_rectA.top    = 0;
      m_rectA.right  = size.cx;
      m_rectA.bottom = min(GetSystemMetrics(SM_CYVSCROLL),size.cy / 2);

      /*
      m_ptaA[0].x = size.cx / 2;
      m_ptaA[0].y = 0;
      m_ptaA[1].x = 1;
      m_ptaA[1].y = min(GetSystemMetrics(SM_CYVSCROLL), size.cy / 2);
      m_ptaA[2].x = size.cx - 1;
      m_ptaA[2].y = m_ptaA[1].y;
      m_ptaA[3].x = m_ptaA[0].x;
      m_ptaA[3].y = m_ptaA[0].y;
      */

      m_ptaA[0].x = m_rectA.left + (m_rectA.width() - iArrowStability) / 2;
      m_ptaA[0].y = m_rectA.top + (m_rectA.height() + iArrowForce) / 2;
      m_ptaA[1].x = m_rectA.left + m_rectA.width() / 2;
      m_ptaA[1].y = m_rectA.top +( m_rectA.height() - iArrowForce) / 2;
      m_ptaA[2].x = m_rectA.left + (m_rectA.width() + iArrowStability) / 2;
      m_ptaA[2].y = m_rectA.top + (m_rectA.height() + iArrowForce) / 2;;

      m_rectB.left   = 0;
      m_rectB.top    = max(size.cy - GetSystemMetrics(SM_CYVSCROLL),size.cy / 2);
      m_rectB.right  = size.cx;
      m_rectB.bottom = size.cy;

      /*
      m_ptaB[0].x = size.cx / 2;
      m_ptaB[0].y = size.cy;
      m_ptaB[1].x = size.cx - 1;
      m_ptaB[1].y = max(size.cy - GetSystemMetrics(SM_CYVSCROLL), size.cy / 2);
      m_ptaB[2].x = 1;
      m_ptaB[2].y = m_ptaB[1].y;
      m_ptaB[3].x = m_ptaA[0].x;
      m_ptaB[3].y = m_ptaB[0].y;
      */
      m_ptaB[0].x = m_rectB.left + (m_rectB.width() - iArrowStability) / 2;
      m_ptaB[0].y = m_rectB.top + (m_rectB.height() - iArrowForce) / 2;
      m_ptaB[1].x = m_rectB.left + m_rectB.width() / 2;
      m_ptaB[1].y = m_rectB.top + (m_rectB.height() + iArrowForce) / 2;
      m_ptaB[2].x = m_rectB.left + (m_rectB.width() + iArrowStability) / 2;
      m_ptaB[2].y = m_rectB.top + (m_rectB.height() - iArrowForce) / 2;;
   }
   else
   {
      ASSERT(FALSE);
   }

   m_rgnA->create_rect(m_rectA);
   m_rgnB->create_rect(m_rectB);


//   psize->m_bRet = false;
}

void simple_scroll_bar::_001OnTimer(::timer * ptimer)
{

   ::user::scroll_bar::_001OnTimer(ptimer);

   auto psession = Session;

   auto point = psession->get_cursor_pos();

   _001ScreenToClient(point);

   if(ptimer->m_uEvent == (uptr) this)
   {

      KillTimer(ptimer->m_uEvent);

      SetTimer(((uptr) this) + 1,10,nullptr);

   }
   else if(ptimer->m_uEvent == ((uptr) this) + 1)
   {

      if(!scrollbar_action(m_itemCurrent))
      {

         KillTimer(ptimer->m_uEvent);

      }

   }
   //else if (ptimer->m_uEvent == 43212345)
   //{

   //   set_need_redraw();

   //}

}


bool simple_scroll_bar::scrollbar_lineA()
{

   i32 nPos = m_scrollinfo.nPos;

   nPos-=3;

   if(nPos < m_scrollinfo.nMin)
      nPos = m_scrollinfo.nMin;

   m_scrollinfo.nPos = nPos;

   if(m_eorientation == orientation_horizontal)
   {
      send_scroll_message(SB_LINELEFT);
   }
   else
   {
      send_scroll_message(SB_LINEUP);
   }

   if(m_scrollinfo.nPos == m_scrollinfo.nMin)
      return false;

   return true;

}


bool simple_scroll_bar::scrollbar_lineB()
{

   i32 nPos = m_scrollinfo.nPos;

   nPos+=3;

   if(nPos > m_scrollinfo.nMax - m_scrollinfo.nPage)
      nPos = m_scrollinfo.nMax - m_scrollinfo.nPage;

   m_scrollinfo.nPos = nPos;

   if(m_eorientation == orientation_horizontal)
   {
      send_scroll_message(SB_LINERIGHT);
   }
   else
   {
      send_scroll_message(SB_LINEDOWN);
   }

   if(m_scrollinfo.nPos == m_scrollinfo.nMax - m_scrollinfo.nPage)
      return false;

   return true;

}


bool simple_scroll_bar::scrollbar_pageA(const ::point & point)
{

   i32 nPos = m_scrollinfo.nPos;

   nPos-=m_scrollinfo.nPage ;

   if(nPos < m_scrollinfo.nMin)
      nPos = m_scrollinfo.nMin;

   m_scrollinfo.nPos = nPos;

   if(m_eorientation == orientation_horizontal)
   {
      send_scroll_message(SB_PAGELEFT);
   }
   else
   {
      send_scroll_message(SB_PAGEUP);
   }

   ::rect rectClient;

   ::rect rectTrack;

   ::rect rect;

   get_client_rect(rectClient);

   GetTrackRect(rectTrack);

   GetPageARect(rectClient,rectTrack,rect);

   if(!rect.contains(point))
      return false;

   if(m_scrollinfo.nPos == m_scrollinfo.nMin)
      return false;

   return true;

}


bool simple_scroll_bar::scrollbar_pageB(const ::point & point)
{

   i32 nPos = m_scrollinfo.nPos;

   nPos+=m_scrollinfo.nPage ;

   if(nPos > m_scrollinfo.nMax - m_scrollinfo.nPage)
      nPos = m_scrollinfo.nMax - m_scrollinfo.nPage;

   m_scrollinfo.nPos = nPos;

   if(m_eorientation == orientation_horizontal)
   {
      send_scroll_message(SB_PAGERIGHT);
   }
   else
   {
      send_scroll_message(SB_PAGEDOWN);
   }

   ::rect rectClient;

   ::rect rectTrack;

   ::rect rect;

   get_client_rect(rectClient);

   GetTrackRect(rectTrack);

   GetPageBRect(rectClient,rectTrack,rect);

   if(!rect.contains(point))
      return false;

   if(m_scrollinfo.nPos == m_scrollinfo.nMax - m_scrollinfo.nPage)
      return false;

   return true;

}


//void simple_scroll_bar::OnDraw(::image * pimage)
//{
/*    if(GetExStyle() & WS_EX_TRANSPARENT)
{
return;
}

__pointer(::user::interaction) puiParent = GetParent();
i32 nPos = m_scrollinfo.nPos;
nPos+=m_scrollinfo.nPage;
if(nPos > m_scrollinfo.nMax - m_scrollinfo.nPage)
nPos = m_scrollinfo.nMax - m_scrollinfo.nPage;
m_scrollinfo.nPos = nPos;

if(m_eorientation == orientation_horizontal)
{
puiParent->SendMessage(e_message_hscroll, MAKEWPARAM(SB_LINERIGHT, m_scrollinfo.nPos), (LPARAM) this->get_handle());
}
else
{
puiParent->SendMessage(e_message_vscroll, MAKEWPARAM(SB_LINEDOWN, m_scrollinfo.nPos), (LPARAM) this->get_handle());
}*/

//}


void simple_scroll_bar::_001OnCreate(::message::message * pmessage)
{


   SCAST_PTR(::message::create, pcreate, pmessage);


   //if (m_puserstyle == nullptr)
   //{

   //   m_puserstyle = GetTopLevel();

   //}

   //if (m_puserstyle == nullptr)
   //{

   //   m_puserstyle = Application.userstyle();

   //}

   update_drawing_objects();

   pcreate->m_lresult = 0;



}


void simple_scroll_bar::pre_translate_message(::message::message * pmessage)
{

   SCAST_PTR(::message::base, pbase, pmessage);

   return ::user::interaction::pre_translate_message(pbase);

}


void simple_scroll_bar::UpdateBitmaps()
{

}

bool simple_scroll_bar::GetPageARect(RECT32 * prectClient,RECT32 * prectTrack, RECT32 * prect)

{

   if(m_eorientation == orientation_horizontal)
   {
      prect->left = prectClient->left + GetSystemMetrics(SM_CXHSCROLL);

      prect->top = prectTrack->top;

      prect->right = prectTrack->left;

      prect->bottom = prectTrack->bottom;

   }
   else if(m_eorientation == orientation_vertical)
   {
      prect->left = prectTrack->left;

      prect->top = prectClient->top + GetSystemMetrics(SM_CYVSCROLL);

      prect->right = prectTrack->right;

      prect->bottom = prectTrack->top;

   }

   return true;

}


bool simple_scroll_bar::GetPageBRect(RECT32 * prectClient,RECT32 * prectTrack, RECT32 * prect)

{
   if(m_eorientation == orientation_horizontal)
   {
      prect->left = prectTrack->right;

      prect->top = prectTrack->top;

      prect->right = prectClient->right - GetSystemMetrics(SM_CXHSCROLL);

      prect->bottom = prectTrack->bottom;

   }
   else if(m_eorientation == orientation_vertical)
   {
      prect->left = prectTrack->left;

      prect->top = prectTrack->bottom;

      prect->right = prectTrack->right;

      prect->bottom = prectClient->bottom - GetSystemMetrics(SM_CYVSCROLL);

   }

   return true;

}



i32 simple_scroll_bar::_001SetScrollPos(i32 iPos)
{
   m_scrollinfo.nPos = iPos ;
   if(m_scrollinfo.nPos < m_scrollinfo.nMin)
   {
      m_scrollinfo.nPos = m_scrollinfo.nMin;
   }
   else if(m_scrollinfo.nPos > m_scrollinfo.nMax - m_scrollinfo.nPage)
   {
      m_scrollinfo.nPos = m_scrollinfo.nMax - m_scrollinfo.nPage;
   }
   //set_need_redraw();
   return true;
}


LRESULT simple_scroll_bar::OnEconoModeChange(WPARAM wParam, LPARAM lParam)
{
   UNREFERENCED_PARAMETER(wParam);
   UNREFERENCED_PARAMETER(lParam);
   update_drawing_objects();
   //set_need_redraw();

   return true;
}

void simple_scroll_bar::update_drawing_objects()
{

}


class trw:
   virtual public ::user::interaction
{
public:

   ::point point1;
   ::point point2;


   trw()
   {

      ::user::create_struct createstruct(WS_EX_LAYERED, nullptr, "", WS_VISIBLE);

      if(create_window_ex(createstruct))
      {

         TRACE("created trw");

      }

      best_monitor(nullptr,nullptr,true);

   }

   virtual ~trw()
   {

   }


   virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {
      pgraphics->move_to(point1);
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

   try
   {

      //::aura::draw_context * pdrawcontext = pgraphics->::aura::simple_chain < ::aura::draw_context >::get_last();

      //bool bFirst = true;
      //
      //if (pdrawcontext != nullptr)
      //{

      //   ::rect rectClient;

      //   rectClient = pdrawcontext->m_rectWindow;

      //   _001ScreenToClient(rectClient);

      //   rectClient.bottom++;
      //   rectClient.right++;

      //   rectClip = rectClient;

      //   bFirst = false;

      //}
      
      if(!m_pshapeaClip)
      {
         
         __construct_new(m_pshapeaClip);

         ::user::interaction * pinteraction = this;

         ::rect rectFocus;

         index i = 0;

         while (pinteraction != nullptr)
         {

            if (i == 1)
            {

               pinteraction->::user::interaction::get_client_rect(rectFocus);

            }
            else
            {

               pinteraction->get_client_rect(rectFocus);

            }

            pinteraction->_001ClientToScreen(rectFocus);

            _001ScreenToClient(rectFocus);
            
            m_pshapeaClip->add_item(__new(rect_shape(rectFocus)));

            m_pshapeaClip->add_item(__new(intersect_clip_shape()));

            i++;

            pinteraction = pinteraction->GetParent();

         }
         
      }
      
      pgraphics->reset_clip();

      pgraphics->m_pointAddShapeTranslate.Null();

      pgraphics->add_shapes(*m_pshapeaClip);

   }
   catch (...)
   {

      __throw(::exception::exception("no more a window"));

   }

}


void simple_scroll_bar::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
{

   //::user::style_context style(this);

   auto pstyle = get_style(pgraphics);

   if(pstyle)
   {

      if (pstyle->_001DrawSimpleScrollBar(pgraphics, this))
      {

         return;

      }

      //style.next();

   }

   //style = this;

   if(pstyle)
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

   auto pstyle = get_style(pgraphics);

   color32_t crBackground = get_color(pstyle, ::user::element_background);

   ::rect rectClient;

   get_client_rect(rectClient);

   if ((crBackground & ARGB(255, 0, 0, 0)) != 0)
   {

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

      auto psession = Session;

      if (psession->savings().is_trying_to_save(::e_resource_processing))
      {

         pgraphics->fill_rect(rectClient, RGB(255, 255, 255));

      }
      else
      {

         pgraphics->fill_rect(rectClient, ARGB(255, 240, 240, 240));

      }

   }

   ::rect rectTrack;

   GetTrackRect(rectTrack);

   ::rect rectWindow;

   get_window_rect(rectWindow);

   m_brushDraw->create_solid(scrollbar_color_strong(pstyle, ::user::element_scrollbar_rect));

   pgraphics->set(m_brushDraw);

   pgraphics->fill_rect(rectTrack);

   //if (m_bTracking || (bool)prop("tracking_on"))
   //{

   //   ::u32 tickFadeIn = 300;

   //   ::u32 tickFadeOut = 300;

   //   byte uchAlpha = max(0, min(255, prop("tracking_alpha").u32()));

   //   if (m_bTracking)
   //   {

   //      if (!(bool)prop("tracking_on"))
   //      {

   //         prop("tracking_on") = true;

   //         prop("tracking_start") = (u32)(::get_tick() + uchAlpha * tickFadeIn / 255);

   //         prop("tracking_fade_in") = true;

   //         prop("tracking_fade_out") = false;

   //         prop("tracking_type") = __random(1, 2);

   //         if (prop("tracking_simple").i32() == 2)
   //         {

   //            int iDeflate = rectTrack.size().get_normal(m_eorientation);

   //            iDeflate /= 2;

   //            ::rect rectConstraint(m_rectTrack);

   //            rectConstraint.deflate(iDeflate, iDeflate);

   //            constraint(m_pointTrack, rectConstraint);

   //            m_sizeTrackOffset = m_pointTrack - m_rectTrack.top_left();

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

   //   const ::point & point1 = rectTrack.top_left() + m_sizeTrackOffset;

   //   _001ClientToScreen(point1);

   //   ::point point2;

   //   psession->get_cursor_pos(&point2);

   //   _001ClientToScreen(point1);

   //   if ((bool)prop("tracking_fade_in"))
   //   {

   //      ::u32 dwFade = prop("tracking_start").u32().elapsed();

   //      if (dwFade < tickFadeIn)
   //      {

   //         uchAlpha = (byte)min(255, max(0, (dwFade * 255 / tickFadeIn)));

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

   //         uchAlpha = (byte)(255 - min(255, max(0, (dwFade * 255 / tickFadeOut))));

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

   //   ::rect rectMachineThumb;

   //   i32 iType = prop("tracking_type").i32();

   //   if (iType == 1)
   //   {

   //      int iSize = rectTrack.size().get_normal(m_eorientation);

   //      rectMachineThumb.top_left() = rectTrack.top_left() + m_sizeTrackOffset - size(iSize / 2, iSize / 2);

   //      rectMachineThumb.bottom_right() = rectMachineThumb.top_left() + size(iSize, iSize);

   //      ::rect rectIntersect;

   //      rectIntersect.intersect(rectMachineThumb, rectTrack);

   //      i32 iArea = (i32)(max(1, rectIntersect.area()));

   //      rectMachineThumb.inflate(1 + iSize * (iSize * iSize) * 4 / (iArea * 5), 1 + iSize * (iSize * iSize) * 2 / (iArea * 3));

   //      draw_mac_thumb_simple(pgraphics, rectMachineThumb, rectTrack, uchAlpha);

   //   }
   //   else
   //   {

   //      int iSize = rectTrack.size().get_normal(m_eorientation);

   //      rectMachineThumb.top_left() = rectTrack.top_left() + m_sizeTrackOffset - size(iSize / 2, iSize / 2);

   //      rectMachineThumb.set_size(iSize, iSize);

   //      rectMachineThumb.assign_normal(rectTrack, m_eorientation);

   //      draw_mac_thumb_dots(pgraphics, rectMachineThumb, rectTrack, uchAlpha);

   //   }

   //   prop("tracking_alpha") = uchAlpha;

   //}

   color32_t cr = scrollbar_color(pstyle, ::user::element_scrollbar_rectA);

   m_brushDraw->create_solid(cr);

   pgraphics->set(m_brushDraw);

   pgraphics->fill_rect(m_rectA);

   cr = scrollbar_color(pstyle, ::user::element_scrollbar_rectB);

   m_brushDraw->create_solid(cr);

   pgraphics->set(m_brushDraw);

   pgraphics->fill_rect(m_rectB);

   ::rect rect;

   if (m_itemCurrent == ::user::element_scrollbar_pageA || m_itemHover== ::user::element_scrollbar_pageA)
   {

      GetPageARect(rectClient, rectTrack, rect);

      cr = scrollbar_color(pstyle, ::user::element_scrollbar_pageA);

      m_brushDraw->create_solid(cr);

      pgraphics->set(m_brushDraw);

      pgraphics->fill_rect(rect);

   }
   else if (m_itemCurrent == ::user::element_scrollbar_pageB || m_itemHover== ::user::element_scrollbar_pageB)
   {

      GetPageBRect(rectClient, rectTrack, rect);

      cr = scrollbar_color(pstyle, ::user::element_scrollbar_pageB);

      m_brushDraw->create_solid(cr);

      pgraphics->set(m_brushDraw);

      pgraphics->fill_rect(rect);

   }

   ::draw2d::pen_pointer penArrow(e_create);

   penArrow->m_elinecapBeg = ::draw2d::e_line_cap_round;

   penArrow->m_elinecapEnd = ::draw2d::e_line_cap_round;

   penArrow->m_elinejoin = ::draw2d::e_line_join_round;

   cr = scrollbar_draw_color(pstyle, ::user::element_scrollbar_rectA);

   penArrow->create_solid(1.0, cr);

   pgraphics->set(penArrow);

   pgraphics->Polyline(m_ptaA, 3);

   cr = scrollbar_draw_color(pstyle, ::user::element_scrollbar_rectB);

   penArrow->create_solid(1.0, cr);

   pgraphics->set(penArrow);

   pgraphics->Polyline(m_ptaB, 3);

}


void simple_scroll_bar::_001OnShowWindow(::message::message * pmessage)
{
   SCAST_PTR(::message::show_window, pshowwindow, pmessage);
   pshowwindow->m_bRet = false;

   // xxx   TwiOnShowWindow(bShow, nStatus);
}

void simple_scroll_bar::_001OnDestroy(::message::message * pmessage)
{
   UNREFERENCED_PARAMETER(pmessage);
}


void simple_scroll_bar::draw_mac_thumb_simple(::draw2d::graphics_pointer & pgraphics,const ::rect & rectDrawParam,const ::rect & lpcrectClip,byte uchAlpha)
{

   ::draw2d::savedc dc(pgraphics);

   pgraphics->reset_clip();

   ::rect rectDraw(rectDrawParam);

   rectDraw.deflate(1,1);

   ::draw2d::pen_pointer pen(e_create);

   pen->create_solid(2.0,ARGB(150 * uchAlpha / 255,108, 108, 100));

   pgraphics->set(pen);

   pgraphics->draw_ellipse(rectDraw);

   ::draw2d::brush_pointer brush(e_create);

   ::rect rectDotto(0,0,5,5);

   brush->create_solid(ARGB(150 * uchAlpha / 255,108,108,100));

   pgraphics->set(brush);

   rectDotto.Align(e_align_center, rectDraw);

   pgraphics->fill_ellipse(rectDotto);

}



void simple_scroll_bar::draw_mac_thumb_dots(::draw2d::graphics_pointer & pgraphics, const ::rect & rectDrawParam, const ::rect & lpcrectClip,byte uchAlpha)
{

   ::rect rectDraw(rectDrawParam);

   rectDraw.bottom--;

   rectDraw.right--;

   double iDiv = 10;

   if (m_pimageDots->is_null())
   {

      auto estatus = __construct(m_pimageDots);

      if (!estatus)
      {

         return;

      }

      estatus = m_pimageDots->create({ (int)(rectDraw.width() * iDiv), (int)(rectDraw.height() * iDiv) });

      if (!estatus)
      {

         return;

      }

      m_pimageDots->fill_byte(0);

      if (!m_pimageDots->g())
      {

         return;

      }

      m_pimageDots->g()->set_alpha_mode(::draw2d::alpha_mode_blend);

      double iDiv2 = iDiv / 2;

      double iDiv3 = iDiv2 / 2;

      double x = m_pimageDots->width() / (iDiv * 2);

      double iSize = iDiv3;

      for (int i = 0; i <= iDiv2; i++)
      {

         double y = m_pimageDots->height() / (iDiv * 2);

         for (int j = 0; j <= iDiv2; j++)
         {

            iSize = max(abs(m_pimageDots->width() / 2 - x), abs(m_pimageDots->width() / 2 - y));

            iSize = (m_pimageDots->width() / 2) - iSize;

            iSize = pow(iSize, 0.55);

            rectd r(x - iSize, y - iSize, x + iSize, y + iSize);

            m_pimageDots->g()->fill_rect(r, ARGB(80, 0, 0, 0));

            y += m_pimageDots->height() / (iDiv2 + 1.0);

         }

         x += m_pimageDots->width() / (iDiv2 + 1.0);

      }

   }

   pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

   pgraphics->set_interpolation_mode(::draw2d::e_interpolation_mode_high_quality_bicubic);

   pgraphics->alpha_blend(rectDraw.top_left(), rectDraw.size(), m_pimageDots->g(), point((::i32)iDiv, (::i32)iDiv), m_pimageDots->get_size() - ::size((::i32)(iDiv * 2), (::i32)(iDiv * 2)), uchAlpha / 255.0);

}


void simple_scroll_bar::on_hit_test(::user::item & item)
{

   ::rect rectTrack;

   GetTrackRect(rectTrack);

   if(rectTrack.contains(item.m_pointClient))
   {

      item = ::user::element_scrollbar_rect;

   }
   else
   {

      ::rect rect;

      ::rect rectClient;

      get_client_rect(rectClient);

      GetPageARect(rectClient, rectTrack, rect);

      if (rect.contains(item.m_pointClient))
      {

         item = ::user::element_scrollbar_pageA;

         return;

      }


      GetPageBRect(rectClient, rectTrack, rect);

      if (rect.contains(item.m_pointClient))
      {

         item = ::user::element_scrollbar_pageB;

         return;

      }

      if (m_rectA.contains(item.m_pointClient))
      {

         item = ::user::element_scrollbar_rectA;

         return;

      }

      if (m_rectB.contains(item.m_pointClient))
      {

         item = ::user::element_scrollbar_rectB;

         return;

      }

      item = ::user::element_none;

   }

}


::color simple_scroll_bar::scrollbar_color_strong(::user::style * pstyle, ::user::e_element eelement)
{

   if (m_itemCurrent == eelement || m_itemHover== eelement)
   {

      auto color = get_color(pstyle, ::user::element_scrollbar_strong, ::user::e_state_hover);

      return color ? color : __acolor(130, 190, 180, 250);

   }
   else
   {

      auto color = get_color(pstyle, ::user::element_scrollbar_strong);

      return color ? color : __acolor(150, 150, 150, 150);

   }

}


::color simple_scroll_bar::scrollbar_color(::user::style* pstyle, ::user::e_element eelement)
{

   if(m_itemCurrent == eelement || m_itemHover== eelement)
   {

      auto color = get_color(pstyle, eelement, ::user::e_state_hover);

      return color ? color : __acolor(100, 190, 180, 250);

   }
   else
   {

      auto color = get_color(pstyle, eelement);

      return color ? color : __acolor(150, 150, 150, 150);

   }

}


::color simple_scroll_bar::scrollbar_border_color(::user::style* pstyle, ::user::e_element eelement)
{

   if(m_itemCurrent == eelement || m_itemHover== eelement)
   {

      auto color = get_color(pstyle, ::user::element_border, ::user::e_state_hover);

      return color ? color : __acolor(190, 180, 180, 180);

   }
   else
   {

      auto color = get_color(pstyle, ::user::element_border);

      return color ? color : __acolor(190, 160, 160, 160);

   }

}


::color simple_scroll_bar::scrollbar_lite_border_color(::user::style* pstyle, ::user::e_element eelement)
{

   if(m_itemCurrent == eelement || m_itemHover== eelement)
   {

      auto color = get_color(pstyle, ::user::element_lite_border, ::user::e_state_hover);

      return color ? color : __acolor(190, 90, 110, 180);

   }
   else
   {

      auto color = get_color(pstyle, ::user::element_lite_border);

      return color ? color : __acolor(190, 110, 110, 100);

   }

}


::color simple_scroll_bar::scrollbar_draw_color(::user::style* pstyle, ::user::e_element eelement)
{

   if (m_itemCurrent == eelement || m_itemHover == eelement)
   {

      auto color = get_color(pstyle, ::user::element_scrollbar_draw, ::user::e_state_hover);

      return color ? color : __acolor(127, 90, 90, 90);

   }
   else
   {

      auto color = get_color(pstyle, ::user::element_scrollbar_draw);

      return color ? color : __acolor(127, 65, 65, 65);

   }

}



