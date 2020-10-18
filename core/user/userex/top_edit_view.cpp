#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/user/userex/_userex.h"
#endif
#include "aura/update.h"


namespace userex
{


   top_edit_view::top_edit_view()
   {

      m_dwDelayedAfterChange = 1000;

      m_ptopview = nullptr;

      m_bEnterKeyPressed = false;

   }


   top_edit_view::~top_edit_view()
   {

   }


   void top_edit_view::install_message_routing(::channel * pchannel)
   {

      ::user::show < ::user::plain_edit >::install_message_routing(pchannel);

      IGUI_MSG_LINK(WM_CREATE, pchannel, this, &top_edit_view::_001OnCreate);
      IGUI_MSG_LINK(WM_KEYDOWN, pchannel, this, &top_edit_view::_001OnKeyDown);

   }


   ::draw2d::font_pointer top_edit_view::get_font(::user::style* pstyle, ::user::e_element eelement, ::user::estate estate) const
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
         return;


      m_ptopview = GetTypedParent < top_view >();


   }


   void top_edit_view::_001OnKeyDown(::message::message * pmessage)
   {

      SCAST_PTR(::message::key, pkey, pmessage);

      ::action action(id_key_down);

      action.m_puserinteraction = this;

      action.m_ekey = pkey->m_ekey;

      get_document()->update_all_views(action);

      if (pkey->m_ekey == ::user::key_return)
      {

         m_bEnterKeyPressed = true;

         SetTimer(5544, m_dwDelayedAfterChange, nullptr);

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

         KillTimer(ptimer->m_nIDEvent);

         bool bEnterKeyPressed = m_bEnterKeyPressed;

         m_bEnterKeyPressed = false;

         auto pdocument = get_document();

         if (::is_set(pdocument))
         {

            ::action action(id_after_change_text_delayed);

            action.m_puserinteraction = this;

            action.value(id_enter_key_pressed) = bEnterKeyPressed;

            pdocument->update_all_views(action);

         }

      }


   }


   void top_edit_view::on_apply(::action * paction)
   {

   }


   void top_edit_view::plain_edit_on_after_change_text(::draw2d::graphics_pointer & pgraphics, const ::action_context & context)
   {


      if (context.is_user_source())
      {

         ::action action(id_after_change_text);

         action.m_psender = this;

         action.m_puserinteraction = this;

         get_document()->update_all_views(action);

         SetTimer(5544, m_dwDelayedAfterChange, nullptr);

      }

   }


   bool top_edit_view::keyboard_focus_is_focusable()
   {

      return is_window_enabled() && is_window_visible();

   }


   //bool top_edit_view::_is_window_visible()
   //{

   //   return ::user::show < ::user::plain_edit >::_is_window_visible() && !GetTopLevel()->frame_is_transparent();

   //}


   /*
   i64 top_edit_view::add_ref()
   {
   return ::object::add_ref(OBJ_REF_DBG_ARGS);
   }
   i64 top_edit_view::dec_ref()
   {
   return ::object::dec_ref(OBJ_REF_DBG_ARGS);
   }


   */
} // namespace userex




