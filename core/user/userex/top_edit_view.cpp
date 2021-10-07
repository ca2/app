#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/user/userex/_userex.h"
#endif

#include "aura/update.h"


namespace userex
{


   top_edit_view::top_edit_view()
   {

      m_durationDelayedAfterChange = 1_s;

      m_ptopview = nullptr;

      m_bEnterKeyPressed = false;

   }


   top_edit_view::~top_edit_view()
   {

   }


   void top_edit_view::install_message_routing(::channel * pchannel)
   {

      ::user::show < ::user::plain_edit >::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create, pchannel, this, &top_edit_view::on_message_create);
      MESSAGE_LINK(e_message_key_down, pchannel, this, &top_edit_view::on_message_key_down);

   }


   ::write_text::font_pointer top_edit_view::get_font(::user::style* pstyle, ::enum_element eelement, ::user::enum_state estate) const
   {

      if (m_pfont)
      {

         return m_pfont;

      }

      return ::user::show < ::user::plain_edit >::get_font(pstyle, eelement, estate);

   }


   void top_edit_view::on_message_create(::message::message * pmessage)
   {

      __pointer(::message::create) pcreate(pmessage);

      pcreate->previous();

      if (pcreate->m_bRet)
      {

         return;

      }

      m_ptopview = GetTypedParent < top_view >();

   }


   void top_edit_view::on_message_key_down(::message::message * pmessage)
   {

      auto pkey = pmessage->m_pkey;

      ::subject subject(id_key_down);

      subject.m_puserelement = this;

      subject.m_ekey = pkey->m_ekey;

      get_document()->update_all_views(&subject);

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


   void top_edit_view::_001OnTimer(::timer * ptimer)
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

               auto psubject = create_subject(id_after_change_text_delayed);

               psubject->m_puserelement = this;

               psubject->payload(id_enter_key_pressed) = bEnterKeyPressed;

               pdocument->update_all_views(psubject);

            }

         }

      }

   }


   void top_edit_view::handle(::subject * psubject, ::context * pcontext)
   {

   }


   void top_edit_view::plain_edit_on_after_change_text(::draw2d::graphics_pointer & pgraphics, const ::action_context & context)
   {

      if (context.is_user_source())
      {

         auto ptopeditview = this;

         auto psubject = create_subject(id_after_change_text);

         psubject->m_psender = this;

         psubject->m_puserelement = this;

         get_document()->update_all_views(psubject);

         if (m_durationDelayedAfterChange > 0_s)
         {

            m_durationLastChange.Now();

            SetTimer(5544, m_durationDelayedAfterChange / 5, nullptr);

         }

      }

   }


   bool top_edit_view::keyboard_focus_is_focusable() const
   {

      return is_window_enabled() && is_window_visible();

   }


} // namespace userex



