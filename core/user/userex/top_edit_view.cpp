#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/user/userex/_userex.h"
#endif
#include "aura/update.h"


namespace userex
{


   top_edit_view::top_edit_view()
   {

      m_millisDelayedAfterChange = 1000;

      m_ptopview = nullptr;

      m_bEnterKeyPressed = false;

   }


   top_edit_view::~top_edit_view()
   {

   }


   void top_edit_view::install_message_routing(::channel * pchannel)
   {

      ::user::show < ::user::plain_edit >::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create, pchannel, this, &top_edit_view::_001OnCreate);
      MESSAGE_LINK(e_message_key_down, pchannel, this, &top_edit_view::_001OnKeyDown);

   }


   ::draw2d::font_pointer top_edit_view::get_font(::user::style* pstyle, ::user::enum_element eelement, ::user::estate estate) const
   {

      if (m_pfont)
      {

         return m_pfont;

      }

      return ::user::show < ::user::plain_edit >::get_font(pstyle, eelement, estate);

   }


   void top_edit_view::_001OnCreate(::message::message * pmessage)
   {

      SCAST_PTR(::message::create, pcreate, pmessage);

      pcreate->previous();

      if (pcreate->m_bRet)
      {

         return;

      }

      m_ptopview = GetTypedParent < top_view >();

   }


   void top_edit_view::_001OnKeyDown(::message::message * pmessage)
   {

      SCAST_PTR(::message::key, pkey, pmessage);

      auto psubject = subject(id_key_down);

      psubject->m_puserinteraction = this;

      psubject->m_ekey = pkey->m_ekey;

      get_document()->update_all_views(psubject);

      if (pkey->m_ekey == ::user::key_return)
      {

         m_bEnterKeyPressed = true;

         SetTimer(5544, m_millisDelayedAfterChange, nullptr);

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

         if (m_millisLastChange.elapsed() > m_millisDelayedAfterChange)
         {

            KillTimer(ptimer->m_uEvent);

            bool bEnterKeyPressed = m_bEnterKeyPressed;

            m_bEnterKeyPressed = false;

            auto pdocument = get_document();

            if (::is_set(pdocument))
            {

               auto psubject = subject(id_after_change_text_delayed);

               psubject->m_puserinteraction = this;

               psubject->value(id_enter_key_pressed) = bEnterKeyPressed;

               pdocument->update_all_views(psubject);

            }

         }

      }

   }


   void top_edit_view::on_subject(::promise::subject * psubject, ::promise::context * pcontext)
   {

   }


   void top_edit_view::plain_edit_on_after_change_text(::draw2d::graphics_pointer & pgraphics, const ::action_context & context)
   {

      if (context.is_user_source())
      {

         auto psubject = subject(id_after_change_text);

         psubject->m_psender = this;

         psubject->m_puserinteraction = this;

         get_document()->update_all_views(psubject);

         if (m_millisDelayedAfterChange > 0)
         {

            m_millisLastChange.Now();

            SetTimer(5544, m_millisDelayedAfterChange / 5, nullptr);

         }

      }

   }


   bool top_edit_view::keyboard_focus_is_focusable() const
   {

      return is_window_enabled() && is_window_visible();

   }


} // namespace userex



