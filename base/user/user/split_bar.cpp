#include "framework.h"
#include "base/user/user/_user.h"


namespace user
{


   split_bar::split_bar()
   {

      m_pparent                                 = nullptr;
      m_dMinimumRate                            = 0.1;
      m_dMaximumRate                            = 0.9;
      m_dRate                                   = -1.0;
      m_dwPosition                              = 1;
      m_dwMaxPosition                           = (u32) -1;

   }

   split_bar::~split_bar()
   {


   }


//   bool split_bar::create_child(split_layout * pparent)
//   {
//
//      m_pparent = pparent;
////      i32 nClassStyle = 0;
////      const char * pClassName = System.RegisterWndClass(
//
//      //nClassStyle,
//      //0,
//      //0,
//      //0);
//      //   ::rectangle_i32 rectangle(0, 0, 0, 0);
//
//      if(!::user::interaction::create_child(pparent))
//      {
//
//         System.message_box("Could not create Split Bar");
//
//         return false;
//
//      }
//
//      return true;
//
//   }


   void split_bar::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

   }


   void split_bar::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::rectangle_i32 rectClient;

      get_client_rect(rectClient);

      pgraphics->fill_rectangle(rectClient, argb(255, 180, 180, 180));


   }


   bool split_bar::pre_create_window(::user::system * pusersystem)
   {

#ifdef WINDOWS_DESKTOP

      //pusersystem->m_createstruct.style &= ~WS_BORDER;

#endif

      return ::user::interaction::pre_create_window(pusersystem);

   }


   void split_bar::install_message_routing(::channel * pchannel)
   {

      ::user::interaction::install_message_routing(pchannel);

      //MESSAGE_LINK(e_message_create, pchannel, this, &split_bar::_001OnCreate);
      //MESSAGE_LINK(e_message_size, pchannel, this, &split_bar::_001OnSize);
      MESSAGE_LINK(e_message_left_button_down, pchannel, this, &split_bar::_001OnLButtonDown);
      MESSAGE_LINK(e_message_left_button_up, pchannel, this, &split_bar::_001OnLButtonUp);
      MESSAGE_LINK(e_message_mouse_move, pchannel, this, &split_bar::_001OnMouseMove);

   }


   void split_bar::_001OnLButtonDown(::message::message * pmessage)
   {

      __pointer(::message::mouse) pmouse(pmessage);

      sync_lock sl(mutex());

      m_pparent->m_iIndex = m_iIndex;

      if(m_iIndex >= 0 && m_iIndex < m_pparent->m_splitbara.get_count()
            && !m_pparent->m_panea[m_iIndex]->m_bFixedSize)
      {

         m_pparent->m_iState = split_layout::stateDragging;

         set_mouse_capture();

         pmouse->m_bRet = true;

         pmouse->m_lresult = 1;

      }

   }


   void split_bar::_001OnLButtonUp(::message::message * pmessage)
   {

      __pointer(::message::mouse) pmouse(pmessage);

      sync_lock sl(mutex());

      if(m_pparent->m_iIndex == m_iIndex)
      {

         m_pparent->m_iState = split_layout::stateInitial;

         auto psession = Session;

         auto puser = psession->user();

         auto pwindowing = puser->windowing();

         pwindowing->release_mouse_capture();

         pmouse->m_bRet = true;

         pmouse->m_lresult = 1;

      }

   }


   void split_bar::_001OnMouseMove(::message::message * pmessage)
   {

      __pointer(::message::mouse) pmouse(pmessage);

      sync_lock sl(mutex());

      auto point = pmouse->m_point;

      m_pparent->_001ScreenToClient(&point);

      if(m_iIndex >= 0 && m_iIndex < m_pparent->m_splitbara.get_count() && !m_pparent->m_panea[m_iIndex]->m_bFixedSize)
      {

         if(m_pparent->GetSplitOrientation() == e_orientation_horizontal)
         {

            pmouse->m_ecursor = e_cursor_size_vertical;

         }
         else
         {

            pmouse->m_ecursor = e_cursor_size_horizontal;

         }

      }

      if((m_pparent->m_iState == split_layout::stateDragging) && (m_iIndex == m_pparent->m_iIndex))
      {
         i32 nPos;
         bool bMove;
         nPos = m_pparent->GetPos(point.x, point.y);
         if(m_iIndex <= 0)
         {
            bMove = nPos > m_pparent->GetMinPos();
         }
         else
         {
            bMove = nPos > (i32) m_pparent->m_splitbara[m_iIndex - 1]->m_dwPosition;
         }
         if(m_pparent->get_pane_count() >= m_iIndex )
         {
            bMove = bMove && nPos < m_pparent->GetMaxPos();
         }
         else
         {
            bMove = bMove && nPos < (i32) m_pparent->m_splitbara[m_iIndex]->m_dwPosition;
         }
         if(bMove)
         {
            bMove = m_pparent->get_normal_dimension() > 0;
         }
         double dRate = -1.0;
         if(bMove)
         {
            dRate = (double) nPos / (double) m_pparent->get_normal_dimension();
            if(dRate < m_dMinimumRate)
            {
               dRate = m_dMinimumRate;
               nPos = (i32) (m_pparent->get_normal_dimension() * dRate);
            }
            else if(dRate > m_dMaximumRate)
            {

               dRate = m_dMaximumRate;

               nPos = (i32) (m_pparent->get_normal_dimension() * dRate);

            }

         }

         if(bMove)
         {

            bMove = nPos != (i32) m_pparent->m_splitbara[m_iIndex]->m_dwPosition;

         }

         TRACE("split_layout::RelayChildEvent nPos %d\nOldPos", m_pparent->m_splitbara[m_iIndex]->m_dwPosition);

         TRACE("split_layout::RelayChildEvent nPos %d\n", nPos);

         if(bMove)
         {

            m_pparent->m_splitbara[m_iIndex]->m_dwPosition = nPos;

            m_pparent->m_splitbara[m_iIndex]->m_dRate = dRate;

            m_pparent->set_need_layout();

         }

      }

      pmouse->m_bRet = true;

      pmouse->m_lresult = 1;

   }


} // namespace user



