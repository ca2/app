#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "aura/user/_user.h"
#endif


namespace user
{


   scroll_x_base::scroll_x_base()
   {

      m_scrolldataHorz.m_bScroll = false;
      m_scrolldataHorz.m_iPage = 0;
      m_scrolldataHorz.m_iLine = 0;
      m_scrolldataHorz.m_bScrollEnable = true;
      m_scrolldataHorz.m_iWidth = GetSystemMetrics(SM_CXHSCROLL);

   }


   scroll_x_base::~scroll_x_base()
   {


   }


   scroll_bar* scroll_x_base::get_horizontal_scroll_bar()
   {

      return m_pscrollbarHorz;

   }


   scroll_data* scroll_x_base::get_horizontal_scroll_data()
   {

      return &m_scrolldataHorz;

   }


   void scroll_x_base::layout_scroll_bar()
   {

      ::rect rectClient;

      ::user::interaction::get_client_rect(rectClient);

      //i32 ifswp = SWP_SHOWWINDOW | SWP_NOCOPYBITS;

      _001DeferCreateXScrollBar();

      if (m_pscrollbarHorz != nullptr)
      {

         if ( m_scrolldataHorz.m_bScroll)
         {

            _001GetXScrollInfo(m_pscrollbarHorz->m_scrollinfo);

            ::rect rectNewPos;

            rectNewPos.left = rectClient.left;
            rectNewPos.top = rectClient.bottom - GetSystemMetrics(SM_CYHSCROLL);
            rectNewPos.right = rectNewPos.left + rectClient.width() - get_final_y_scroll_bar_width();
            rectNewPos.bottom = rectNewPos.top + GetSystemMetrics(SM_CYHSCROLL);

            m_pscrollbarHorz->order(zorder_top);

            m_pscrollbarHorz->place(rectNewPos);

            m_pscrollbarHorz->display();

            //m_pscrollbarHorz->set_need_redraw();

            //m_pscrollbarHorz->set_need_layout();

         }
         else
         {

            m_pscrollbarHorz->display(display_none);

         }

         set_need_redraw();

      }

   }


   void scroll_x_base::_001OnDeferCreateXScrollBar()
   {

      if (m_scrolldataHorz.m_bScrollEnable)
      {

         if (m_pscrollbarHorz == nullptr)
         {

            create_x_scroll_bar(nullptr);

         }

      }

   }


   void scroll_x_base::_001DeferCreateXScrollBar()
   {

      bool bCreate = false;

      if (m_scrolldataHorz.m_bScrollEnable)
      {

         if (m_pscrollbarHorz == nullptr)
         {

            bCreate = true;

         }

      }


      if (bCreate)
      {

         _001OnDeferCreateXScrollBar();

      }

   }


   void scroll_x_base::_001OnHScroll(::message::message * pmessage)
   {

      SCAST_PTR(::message::scroll, pscroll, pmessage);

      {

         sync_lock slUser(mutex());

         if (pscroll->m_nSBCode == SB_LINELEFT)
         {

            set_viewport_offset_x((LONG) (get_viewport_offset().x - m_scrolldataHorz.m_iLine));

         }
         else if (pscroll->m_nSBCode == SB_PAGELEFT)
         {

            set_viewport_offset_x((LONG) (get_viewport_offset().x - m_scrolldataHorz.m_iPage));

         }
         else if (pscroll->m_nSBCode == SB_PAGERIGHT)
         {

            set_viewport_offset_x((LONG) (get_viewport_offset().x + m_scrolldataHorz.m_iPage));

         }
         else if (pscroll->m_nSBCode == SB_LINERIGHT)
         {

            set_viewport_offset_x((LONG) (get_viewport_offset().x + m_scrolldataHorz.m_iLine));

         }
         else if (pscroll->m_nSBCode == SB_THUMBTRACK)
         {

            set_viewport_offset_x(pscroll->m_nPos);

         }
         else if (pscroll->m_nSBCode == SB_THUMBPOSITION)
         {

            set_viewport_offset_x(pscroll->m_nPos);

         }

      }

   }


   void scroll_x_base::on_change_viewport_offset()
   {

      sync_lock sl(mutex());

      if (m_pscrollbarHorz.is_set())
      {

         m_pscrollbarHorz->m_scrollinfo.nPos = m_pointScroll.x;

      }

   }


   bool scroll_x_base::validate_viewport_offset(point & point)
   {

      if (point.x < 0)
      {

         point.x = 0;

      }
      else
      {

         auto sizeTotal = get_total_size();

         auto sizePage = get_page_size();

         if (point.x > max(0, sizeTotal.cx - sizePage.cx))
         {

            point.x = (LONG) max(0, sizeTotal.cx - sizePage.cx);

         }

      }

      return true;

   }


   void scroll_x_base::install_message_routing(::channel * pchannel)
   {

      MESSAGE_LINK(WM_HSCROLL, pchannel, this, &scroll_x_base::_001OnHScroll);

   }


   void scroll_x_base::on_change_view_size()
   {

      auto sizeTotal = get_total_size();

      m_scrolldataHorz.m_iWidth = GetSystemMetrics(SM_CXHSCROLL);

      ::rect rectClient;

      get_client_rect(rectClient);

      LONG iTotalHeight = (LONG) sizeTotal.cy;

      LONG iTotalWidth = (LONG) sizeTotal.cx;

      LONG iClientHeight = rectClient.height();

      LONG iClientWidth = rectClient.width();

      //LONG iScrollHeight = iClientHeight - GetSystemMetrics(SM_CYHSCROLL);

      LONG iScrollWidth = iClientWidth - GetSystemMetrics(SM_CXVSCROLL);

      m_scrolldataHorz.m_bScroll = false;

      if (iTotalWidth > iClientWidth)
      {

         m_scrolldataHorz.m_bScroll = true;

      }
      else if (iTotalHeight > iClientHeight)
      {

         if (iTotalWidth > iScrollWidth)
         {

            m_scrolldataHorz.m_bScroll = true;

         }

      }

      m_scrolldataHorz.m_bScroll = m_scrolldataHorz.m_bScrollEnable && m_scrolldataHorz.m_bScroll;

      ::rect rectScroll;

      get_client_rect(rectScroll);

      m_scrolldataHorz.m_iPage = rectScroll.width();

      if (validate_viewport_offset(m_pointScroll))
      {

         layout_scroll_bar();

         on_change_viewport_offset();

      }

   }


   int scroll_x_base::get_final_x_scroll_bar_width()
   {

      return m_scrolldataHorz.m_bScroll && m_scrolldataHorz.m_bScrollEnable ? m_scrolldataHorz.m_iWidth : 0;

   }











   scroll_y_base::scroll_y_base()
   {

      m_iWheelDeltaScroll = 3;
      m_scrolldataVert.m_bScroll = false;
      m_scrolldataVert.m_iPage = 0;
      m_scrolldataVert.m_iLine = 0;
      m_scrolldataVert.m_bScrollEnable = true;
      m_scrolldataVert.m_iWidth = GetSystemMetrics(SM_CYVSCROLL);

   }

   scroll_y_base::~scroll_y_base()
   {

   }


   scroll_bar* scroll_y_base::get_vertical_scroll_bar()
   {

      return m_pscrollbarVert;

   }


   scroll_data* scroll_y_base::get_vertical_scroll_data()
   {

      return &m_scrolldataVert;

   }


   void scroll_y_base::layout_scroll_bar()
   {

      ::rect rectClient = get_client_rect();

      //scroll_bar_get_client_rect(rectClient);

//      i32 ifswp = SWP_SHOWWINDOW | SWP_NOCOPYBITS;

      _001DeferCreateYScrollBar();

      if (m_pscrollbarVert != nullptr)
      {

         if (m_scrolldataVert.m_bScroll)
         {

            _001GetYScrollInfo(m_pscrollbarVert->m_scrollinfo);

            ::rect rectNewPos;

            rectNewPos.left = rectClient.right - GetSystemMetrics(SM_CXVSCROLL);
            rectNewPos.top = rectClient.top;
            rectNewPos.right = rectNewPos.left + GetSystemMetrics(SM_CXVSCROLL);
            rectNewPos.bottom = rectNewPos.top+ rectClient.height() - get_final_x_scroll_bar_width();

            m_pscrollbarVert->order(zorder_top);

            m_pscrollbarVert->place(rectNewPos);

            m_pscrollbarVert->display();

         }
         else
         {

            m_pscrollbarVert->display(display_none);

         }

         set_need_redraw();

      }

   }


   void scroll_y_base::_001OnDeferCreateYScrollBar()
   {

      if (m_scrolldataVert.m_bScrollEnable)
      {

         if (m_pscrollbarVert == nullptr)
         {

            create_y_scroll_bar(nullptr);

         }

      }

   }


   void scroll_y_base::_001DeferCreateYScrollBar()
   {

      bool bCreate = false;

      if (m_scrolldataVert.m_bScrollEnable)
      {

         if (m_pscrollbarVert == nullptr)
         {

            bCreate = true;

         }

      }

      if (bCreate)
      {

         _001OnDeferCreateYScrollBar();

      }

   }


   void scroll_y_base::_001OnVScroll(::message::message * pmessage)
   {


      SCAST_PTR(::message::scroll, pscroll, pmessage);


      if (pscroll->m_nSBCode == SB_LINEUP)
      {

         set_viewport_offset_y((LONG) (get_viewport_offset().y - m_scrolldataVert.m_iLine));

      }
      else if (pscroll->m_nSBCode == SB_PAGEUP)
      {

         set_viewport_offset_y((LONG) (get_viewport_offset().y - m_scrolldataVert.m_iPage));

      }
      else if (pscroll->m_nSBCode == SB_PAGEDOWN)
      {

         set_viewport_offset_y((LONG) (get_viewport_offset().y + m_scrolldataVert.m_iPage));

      }
      else if (pscroll->m_nSBCode == SB_LINEDOWN)
      {

         set_viewport_offset_y((LONG) (get_viewport_offset().y + m_scrolldataVert.m_iLine));

      }
      else if (pscroll->m_nSBCode == SB_THUMBTRACK)
      {

         set_viewport_offset_y(pscroll->m_nPos);

      }
      else if (pscroll->m_nSBCode == SB_THUMBPOSITION)
      {

         set_viewport_offset_y(pscroll->m_nPos);

      }
   }



   i32 scroll_y_base::get_wheel_scroll_delta()
   {

      return m_iWheelDeltaScroll;

   }



   void scroll_y_base::on_change_viewport_offset()
   {

      sync_lock sl(mutex());

      if (m_pscrollbarVert.is_set())
      {

         m_pscrollbarVert->m_scrollinfo.nPos = m_pointScroll.y;

      }

   }


   void scroll_y_base::_001OnMouseWheel(::message::message * pmessage)
   {

      if (!m_scrolldataVert.m_bScroll || !m_scrolldataVert.m_bScrollEnable)
      {

         return;

      }

      SCAST_PTR(::message::mouse_wheel, pmousewheel, pmessage);

      if (pmousewheel->GetDelta() > 0)
      {
         if (m_iWheelDelta > 0)
         {
            m_iWheelDelta += pmousewheel->GetDelta();
         }
         else
         {
            m_iWheelDelta = pmousewheel->GetDelta();
         }
      }
      else if (pmousewheel->GetDelta() < 0)
      {
         if (m_iWheelDelta < 0)
         {
            m_iWheelDelta += pmousewheel->GetDelta();
         }
         else
         {
            m_iWheelDelta = pmousewheel->GetDelta();
         }
      }

      index iDelta = m_iWheelDelta / WHEEL_DELTA;

      m_iWheelDelta -= (i16)(WHEEL_DELTA * iDelta);

      index nPos = m_pscrollbarVert->m_scrollinfo.nPos - iDelta * get_wheel_scroll_delta();

      if (nPos < m_pscrollbarVert->m_scrollinfo.nMin)
         nPos = m_pscrollbarVert->m_scrollinfo.nMin;
      else if (nPos > m_pscrollbarVert->m_scrollinfo.nMax - m_pscrollbarVert->m_scrollinfo.nPage)
         nPos = m_pscrollbarVert->m_scrollinfo.nMax - m_pscrollbarVert->m_scrollinfo.nPage;

      m_pscrollbarVert->m_scrollinfo.nPos =  (i32) nPos;

      m_pscrollbarVert->send_scroll_message(SB_THUMBPOSITION);

      pmousewheel->m_lresult = 0;

      pmousewheel->m_bRet = true;

   }


   bool scroll_y_base::validate_viewport_offset(point & point)
   {

      if (point.y < 0)
      {

         point.y = 0;

      }
      else
      {

         auto sizeTotal = get_total_size();

         auto sizePage = get_page_size();

         if (point.y > max(0, sizeTotal.cy - sizePage.cy))
         {

            point.y = (LONG) max(0, sizeTotal.cy - sizePage.cy);

         }

      }

      return true;

   }




   void scroll_y_base::install_message_routing(::channel * pchannel)
   {

      interaction::install_message_routing(pchannel);

      MESSAGE_LINK(WM_VSCROLL, pchannel, this, &scroll_y_base::_001OnVScroll);
      MESSAGE_LINK(WM_MOUSEWHEEL, pchannel, this, &scroll_y_base::_001OnMouseWheel);

   }


   void scroll_y_base::on_change_view_size()
   {

      auto sizeTotal = get_total_size();

      m_scrolldataVert.m_iWidth = GetSystemMetrics(SM_CXVSCROLL);

      ::rect rectClient;

      get_client_rect(rectClient);

      LONG iTotalHeight = (LONG) sizeTotal.cy;

      LONG iTotalWidth = (LONG) sizeTotal.cx;

      LONG iClientHeight = rectClient.height();

      LONG iClientWidth = rectClient.width();

      LONG iScrollHeight = iClientHeight - GetSystemMetrics(SM_CYHSCROLL);

      //LONG iscrollWidth = iClientWidth - GetSystemMetrics(SM_CXVSCROLL);

      m_scrolldataVert.m_bScroll = false;

      if (iTotalWidth > iClientWidth)
      {

         if (iTotalHeight > iScrollHeight)
         {

            m_scrolldataVert.m_bScroll = true;

         }

      }
      else if (iTotalHeight > iClientHeight)
      {

         m_scrolldataVert.m_bScroll = true;

      }

      m_scrolldataVert.m_bScroll = m_scrolldataVert.m_bScrollEnable && m_scrolldataVert.m_bScroll;

      ::rect rectScroll;

      get_client_rect(rectScroll);

      m_scrolldataVert.m_iPage = rectScroll.height();

      if (validate_viewport_offset(m_pointScroll))
      {

         layout_scroll_bar();

         on_change_viewport_offset();

      }

   }



   int scroll_y_base::get_final_y_scroll_bar_width()
   {

      return m_scrolldataVert.m_bScroll && m_scrolldataVert.m_bScrollEnable ? m_scrolldataVert.m_iWidth : 0;

   }

   //
   //void scroll_y_base::on_layout(::draw2d::graphics_pointer & pgraphics)
   //{

   //   BASE::on_layout(pgraphics);

   //   on_change_view_size();

   //}


   scroll_base::scroll_base()
   {

   }


   scroll_base::~scroll_base()
   {

   }


   void scroll_base::install_message_routing(::channel * pchannel)
   {
      scroll_x_base::install_message_routing(pchannel);
      scroll_y_base::install_message_routing(pchannel);
   }

   void scroll_base::on_change_viewport_offset()
   {
      scroll_x_base::on_change_viewport_offset();
      scroll_y_base::on_change_viewport_offset();
      ::user::interaction::on_change_viewport_offset();
   }


   bool scroll_base::validate_viewport_offset(point & point)
   {

      bool xValidated = scroll_x_base::validate_viewport_offset(point);

      bool yValidated = scroll_y_base::validate_viewport_offset(point);

      bool iValidated = ::user::interaction::validate_viewport_offset(point);

      return (xValidated || yValidated) && iValidated;

   }


   void scroll_base::layout_scroll_bar()
   {

      scroll_x_base::layout_scroll_bar();

      scroll_y_base::layout_scroll_bar();

   }


   void scroll_base::on_change_view_size()
   {

      m_scrolldataHorz.m_bScroll = false;

      m_scrolldataVert.m_bScroll = false;

      auto sizeTotal = get_total_size();

      ::rect rectClient;

      get_client_rect(rectClient);

      if(rectClient.area() <= 0)
      {

         return;

      }

      LONG iTotalHeight = (LONG) sizeTotal.cy;

      LONG iTotalWidth = (LONG) sizeTotal.cx;

      LONG iClientHeight = rectClient.height();

      LONG iClientWidth = rectClient.width();

      LONG iScrollHeight = iClientHeight - GetSystemMetrics(SM_CYHSCROLL);

      LONG iscrollWidth = iClientWidth - GetSystemMetrics(SM_CXVSCROLL);

      if (iTotalWidth > iClientWidth)
      {

         m_scrolldataHorz.m_bScroll = true;

         if (iTotalHeight > iScrollHeight)
         {

            m_scrolldataVert.m_bScroll = true;

         }

      }
      else if (iTotalHeight > iClientHeight)
      {

         m_scrolldataVert.m_bScroll = true;

         if (iTotalWidth > iscrollWidth)
         {

            m_scrolldataHorz.m_bScroll = true;

         }

      }

      m_scrolldataHorz.m_bScroll = m_scrolldataHorz.m_bScrollEnable && m_scrolldataHorz.m_bScroll;

      m_scrolldataVert.m_bScroll = m_scrolldataVert.m_bScrollEnable && m_scrolldataVert.m_bScroll;

      if (!m_scrolldataHorz.m_bScroll)
      {

         m_pointScroll.x = 0;

      }


      if (!m_scrolldataVert.m_bScroll)
      {

         m_pointScroll.y = 0;

      }


      ::rect rectScroll;

      get_client_rect(rectScroll);

      m_scrolldataHorz.m_iPage = rectScroll.width();

      m_scrolldataVert.m_iPage = rectScroll.height();

      if (validate_viewport_offset(m_pointScroll))
      {

         layout_scroll_bar();

         on_change_viewport_offset();

      }
      else
      {

         layout_scroll_bar();

      }

   }


   void scroll_x_base::send_xscroll_message(int nSBCode)
   {

      auto pscroll = __new(::message::scroll);

      pscroll->m_nSBCode = nSBCode;

      if (m_pscrollbarHorz.is_set())
      {

         pscroll->m_nPos = m_pscrollbarHorz->m_scrollinfo.nPos;

      }
      else
      {

         pscroll->m_nPos = (i32) get_viewport_offset().x;

      }

      pscroll->m_id = WM_HSCROLL;

      send(pscroll);

   }


   void scroll_x_base::create_x_scroll_bar(const ::rect & rect)
   {

      if (m_pscrollbarHorz != nullptr)
         return;

      auto pbar = __create<scroll_bar>();

      if (!pbar->create_window(::orientation_horizontal, WS_CHILD | WS_VISIBLE, this, 7000 + 1))
      {
         delete pbar;
         return;
      }

      m_pscrollbarHorz = pbar;

   }


   void scroll_x_base::scroll_left_line()
   {

      send_xscroll_message(SB_LINELEFT);

   }


   void scroll_x_base::scroll_right_line()
   {

      send_xscroll_message(SB_LINERIGHT);

   }


   void scroll_x_base::scroll_left_page()
   {

      send_xscroll_message(SB_PAGELEFT);

   }


   void scroll_x_base::scroll_right_page()
   {

      send_xscroll_message(SB_PAGERIGHT);

   }


   void scroll_x_base::scroll_horz(int nPos)
   {

      set_viewport_offset_x(nPos);

   }


   void scroll_y_base::send_yscroll_message(int nSBCode)
   {

      auto pscroll = __new(::message::scroll);

      pscroll->m_nSBCode = nSBCode;

      if (m_pscrollbarVert.is_set())
      {

         pscroll->m_nPos = m_pscrollbarVert->m_scrollinfo.nPos;

      }
      else
      {

         pscroll->m_nPos = (i32) get_viewport_offset().y;

      }

      pscroll->m_id = WM_VSCROLL;

      send(pscroll);

   }


   void scroll_y_base::create_y_scroll_bar(const ::rect & rect)
   {

      if (m_pscrollbarVert != nullptr)
         return;

      auto pbar = __create< scroll_bar >();

      if (!pbar->create_window(::orientation_vertical, WS_CHILD | WS_VISIBLE, this, 7002))
      {
         delete pbar;
         return;
      }

      m_pscrollbarVert = pbar;

   }


   void scroll_y_base::scroll_down_line()
   {

      send_yscroll_message(SB_LINEDOWN);

   }


   void scroll_y_base::scroll_up_line()
   {

      send_yscroll_message(SB_LINEUP);

   }


   void scroll_y_base::scroll_up_page()
   {

      send_yscroll_message(SB_PAGEUP);

   }


   void scroll_y_base::scroll_down_page()
   {

      send_yscroll_message(SB_PAGEDOWN);

   }


   void scroll_y_base::scroll_vert(int nPos)
   {

      set_viewport_offset_y(nPos);

   }

   bool scroll_base::GetActiveClientRect(RECT * prect)
   {

      ::user::interaction::get_client_rect(prect);

      auto sizeTotal = get_total_size();

      auto pointOffset = get_viewport_offset();

      prect->right = (LONG) (prect->left + min(::width(prect), sizeTotal.cx - m_scrolldataHorz.m_iPage - pointOffset.x));

      prect->bottom = (LONG) (prect->top + min(::height(prect), sizeTotal.cy - m_scrolldataVert.m_iPage - pointOffset.y));

      return true;

   }


   //bool scroll_base::get_client_rect(RECT * prect)
   //{

   //   ::user::interaction::get_client_rect(prect);

   //   prect->right -= get_final_y_scroll_bar_width();

   //   prect->bottom -= get_final_x_scroll_bar_width();

   //   return true;

   //}


   bool scroll_base::GetFocusRect(RECT * prect)
   {

      prect->left = 0;
      prect->top = 0;
      prect->right = layout().sketch().size().cx;
      prect->bottom = layout().sketch().size().cy;

      return true;

   }


   ::sized scroll_base::get_total_size()
   {

      return m_sizeTotal;

   }


   ::estatus scroll_base::set_total_size(const ::sized& size)
   {

      m_sizeTotal.cx = size.cx;

      m_sizeTotal.cy = size.cy;

      return ::success;

   }


   ::estatus scroll_base::set_page_size(const ::sized& size)
   {

      return ::error_interface_only;

   }



   void scroll_base::defer_draw_scroll_gap(::draw2d::graphics_pointer & pgraphics)
   {

      if (m_scrolldataHorz.m_bScrollEnable && m_scrolldataHorz.m_bScroll
            && m_pscrollbarHorz.is_set() && m_pscrollbarHorz->m_pimpl.is_set()
            && m_scrolldataVert.m_bScrollEnable && m_scrolldataVert.m_bScroll
            && m_pscrollbarVert.is_set() && m_pscrollbarVert->m_pimpl.is_set())
      {

         ::rect rectClient;

         get_client_rect(rectClient);

         ::rect rect;

         rect.top = rectClient.bottom;
         rect.left = rectClient.right;
         rect.right = (LONG) (rect.left + m_pscrollbarVert->layout().design().size().cx);
         rect.bottom = (LONG) (rect.top + m_pscrollbarHorz->layout().design().size().cy);

         pgraphics->fill_rect(rect, ARGB(127, 127, 127, 127));

      }

   }


}  // namespace aura



