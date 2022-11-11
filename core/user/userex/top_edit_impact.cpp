#include "framework.h"
#include "acme/platform/timer.h"
#include "top_edit_impact.h"
#include "top_impact.h"
#include "acme/constant/id.h"
#include "acme/constant/message.h"
#include "aura/message/user.h"
#include "base/user/user/document.h"


namespace userex
{


   top_edit_impact::top_edit_impact()
   {

      m_durationDelayedAfterChange = 1_s;

      m_ptopview = nullptr;

      m_bEnterKeyPressed = false;

   }


   top_edit_impact::~top_edit_impact()
   {

   }


   void top_edit_impact::install_message_routing(::channel * pchannel)
   {

      ::user::show < ::user::plain_edit >::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create, pchannel, this, &top_edit_impact::on_message_create);
      MESSAGE_LINK(e_message_key_down, pchannel, this, &top_edit_impact::on_message_key_down);

   }


   ::write_text::font_pointer top_edit_impact::get_font(::user::style* pstyle, ::enum_element eelement, ::user::enum_state estate)
   {

      if (m_pfont)
      {

         return m_pfont;

      }

      return ::user::show < ::user::plain_edit >::get_font(pstyle, eelement, estate);

   }


   void top_edit_impact::on_message_create(::message::message * pmessage)
   {

      ::pointer<::message::create>pcreate(pmessage);

      pcreate->previous();

      if (pcreate->m_bRet)
      {

         return;

      }

      m_ptopview = get_typed_parent < top_impact >();

   }


   void top_edit_impact::on_message_key_down(::message::message * pmessage)
   {

      auto pkey = pmessage->m_union.m_pkey;

      auto ptopic = create_topic(id_key_down);

      ptopic->m_puserelement = this;

      ptopic->m_ekey = pkey->m_ekey;

      get_document()->update_all_impacts(ptopic);

      if (pkey->m_ekey == ::user::e_key_return)
      {

         m_bEnterKeyPressed = true;

         SetTimer(5544, m_durationDelayedAfterChange, nullptr);

      }
      else
      {

         m_bEnterKeyPressed = false;

      }

   }


   void top_edit_impact::_001OnTimer(::timer * ptimer)
   {

      ::user::show < ::user::plain_edit >::_001OnTimer(ptimer);

      if (ptimer->m_etimer == 5544)
      {

         if (m_durationLastChange.elapsed() > m_durationDelayedAfterChange)
         {

            KillTimer(ptimer->m_uEvent);

            bool bEnterKeyPressed = m_bEnterKeyPressed;

            m_bEnterKeyPressed = false;

            auto pdocument = get_document();

            if (::is_set(pdocument))
            {

               auto pextendedtopic = create_topic(id_after_change_text_delayed);

               pextendedtopic->m_puserelement = this;

               pextendedtopic->payload(id_enter_key_pressed) = bEnterKeyPressed;

               pdocument->update_all_impacts(pextendedtopic);

            }

         }

      }

   }


   void top_edit_impact::handle(::topic * ptopic, ::context * pcontext)
   {

   }


   void top_edit_impact::plain_edit_on_after_change_text(::draw2d::graphics_pointer & pgraphics, const ::action_context & context)
   {

      if (context.is_user_source())
      {

         auto ptopeditview = this;

         auto pextendedtopic = create_topic(id_after_change_text);

         pextendedtopic->m_psender = this;

         pextendedtopic->m_puserelement = this;

         get_document()->update_all_impacts(pextendedtopic);

         if (m_durationDelayedAfterChange > 0_s)
         {

            m_durationLastChange.Now();

            SetTimer(5544, m_durationDelayedAfterChange / 5, nullptr);

         }

      }

   }


   bool top_edit_impact::keyboard_focus_is_focusable()
   {

      return is_window_enabled() && is_window_visible();

   }


} // namespace userex



