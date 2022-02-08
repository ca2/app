#include "framework.h"
#include "base/user/user/_user.h"
#include "split_pane.h"
#include "aura/graphics/draw2d/_draw2d.h"


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
////      const char * pClassName = psystem->RegisterWndClass(
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
//         output_error_message("Could not create Split Bar");
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

      auto pframeTopLevel = top_level_frame();

      if (pframeTopLevel)
      {

         if (pframeTopLevel->frame_is_transparent())
         {

            return;

         }

      }

      ::rectangle_i32 rectangleClient;

      get_client_rect(rectangleClient);

      pgraphics->fill_rectangle(rectangleClient, argb(255, 180, 180, 180));

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

      MESSAGE_LINK(e_message_create, pchannel, this, &split_bar::on_message_create);
      //MESSAGE_LINK(e_message_size, pchannel, this, &split_bar::on_message_size);
      MESSAGE_LINK(e_message_left_button_down, pchannel, this, &split_bar::on_message_left_button_down);
      MESSAGE_LINK(e_message_left_button_up, pchannel, this, &split_bar::on_message_left_button_up);
      MESSAGE_LINK(e_message_mouse_move, pchannel, this, &split_bar::on_message_mouse_move);

   }


   void split_bar::on_message_create(::message::message* pmessage)
   {

      auto pparent = get_parent();

      m_pparent = dynamic_cast < split_layout * >(pparent);

   }


   void split_bar::on_message_left_button_down(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      synchronous_lock synchronouslock(mutex());

      m_pparent->m_iIndex = m_iIndex;

      if(m_iIndex >= 0 && m_iIndex < m_pparent->m_splitbara.get_count()
            && !m_pparent->m_splitpanecompositea[m_iIndex]->m_bFixedSize)
      {

         m_pparent->m_iState = split_layout::stateDragging;

         set_mouse_capture();

         pmouse->m_bRet = true;

         pmouse->m_lresult = 1;

      }

   }


   void split_bar::on_message_left_button_up(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      synchronous_lock synchronouslock(mutex());

      if(m_pparent->m_iIndex == m_iIndex)
      {

         m_pparent->m_iState = split_layout::stateInitial;

         auto psession = get_session();

         auto puser = psession->user();

         auto pwindowing = puser->windowing();

         pwindowing->release_mouse_capture();

         pmouse->m_bRet = true;

         pmouse->m_lresult = 1;

      }

   }


   void split_bar::on_message_mouse_move(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      synchronous_lock synchronouslock(mutex());

      auto point = m_pparent->_001ScreenToClient(pmouse->m_point);

      if(m_iIndex >= 0 && m_iIndex < m_pparent->m_splitbara.get_count() && !m_pparent->m_splitpanecompositea[m_iIndex]->m_bFixedSize)
      {

         auto psession = get_session();

         auto puser = psession->user();

         auto pwindowing = puser->windowing();

         if(m_pparent->GetSplitOrientation() == e_orientation_horizontal)
         {

            auto pcursor = pwindowing->get_cursor(e_cursor_size_vertical);

            pmouse->m_pcursor = pcursor;

         }
         else
         {

            auto pcursor = pwindowing->get_cursor(e_cursor_size_horizontal);

            pmouse->m_pcursor = pcursor;

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

         FORMATTED_TRACE("split_layout::RelayChildEvent nPos %d\nOldPos", m_pparent->m_splitbara[m_iIndex]->m_dwPosition);

         FORMATTED_TRACE("split_layout::RelayChildEvent nPos %d\n", nPos);

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



