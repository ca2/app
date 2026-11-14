#include "aura/platform.h"
#include "aura/user/user/interaction.h"
#include "aura/user/user/button.h"
#include "aura/user/user/plain_edit.h"
#include "aura/user/user/check_box.h"
#include "aura/message/user.h"
#include "acme/user/user/mouse.h"
#include "acme/platform/application.h"
#include "acme/platform/session.h"
#include "acme/platform/system.h"

namespace
{
   ::user::interaction * focused = nullptr;
   template < class BASE > class tab_node : public BASE
   {
   public:
      ::user::interaction * m_parent = nullptr;
      ::pointer_array<::user::interaction> m_children;
      bool m_bVisible = true;
      bool m_bEnabled = true;
      bool is_this_visible(::user::enum_layout) override { return m_bVisible; }
      bool is_window_enabled() override { return m_bEnabled; }
      ::user::interaction * get_parent() override { return m_parent; }
      ::user::interaction * first_child() override { return m_children.has_element() ? m_children.first().m_p : nullptr; }
      ::user::interaction * next_sibling(::user::interaction * child) override
      {
         for (::collection::index i = 0; i + 1 < m_children.size(); ++i)
            if (m_children[i] == child) return m_children[i + 1];
         return nullptr;
      }
      void set_keyboard_focus() override { focused = this; }
   };
   class tab_button : public tab_node<::user::button>
   {
   public:
      bool m_bHandleClick = false;
      bool on_click(::item *, ::user::mouse *) override { return m_bHandleClick; }
      // Avoid a native windowing backend in this headless test.
      bool keyboard_focus_is_focusable() override { return m_bVisible && m_bEnabled; }
   };
   void reset_key(::message::key & key, ::user::enum_key code = ::user::e_key_tab)
   {
      key.m_union.m_pkey = &key;
      key.m_ekey = code;
      key.m_eusermessage = ::user::e_message_key_down;
      key.m_bRet = false;
   }
}

int main()
{
   ::platform::system runtime;
   ::pointer<::platform::application> app(allocate_t{});
   app->m_papplication = app;
   ::pointer<::platform::session> session(allocate_t{});
   app->m_psession = session;
   ::pointer<tab_node<::user::interaction>> form(allocate_t{}), label(allocate_t{}), row(allocate_t{});
   ::pointer<tab_node<::user::plain_edit>> edit(allocate_t{});
   ::pointer<tab_button> ok(allocate_t{}), cancel(allocate_t{});
   ::pointer<tab_node<::user::check_box>> check(allocate_t{});
   form->m_papplication = label->m_papplication = row->m_papplication = app;
   edit->m_papplication = ok->m_papplication = cancel->m_papplication = check->m_papplication = app;
   form->payload("tab_focus_scope") = true;
   form->m_children.add(label);
   form->m_children.add(edit);
   form->m_children.add(row);
   row->m_children.add(ok);
   row->m_children.add(cancel);
   label->m_parent = edit->m_parent = row->m_parent = form;
   ok->m_parent = cancel->m_parent = row;
   if (!edit->keyboard_focus_is_focusable() || !check->keyboard_focus_is_focusable()) return 1;
   if (form->next_tab_focus(edit) != ok.get() || form->next_tab_focus(ok) != cancel.get()
      || form->next_tab_focus(cancel) != edit.get()) return 2;
   if (form->next_tab_focus(edit, true) != cancel.get() || form->next_tab_focus(cancel, true) != ok.get()) return 3;
   ::message::key key;
   reset_key(key);
   if (!edit->handle_tab_key(&key) || focused != ok.get() || !key.m_bRet) return 4;

   // Exercise real button message routing: Tab must reach the shared interaction handler.
   ok->install_message_routing(ok);
   cancel->install_message_routing(cancel);
   reset_key(key);
   ok->route_message(&key);
   if (!key.m_bRet || focused != cancel.get()) return 5;
   reset_key(key);
   cancel->route_message(&key);
   if (!key.m_bRet || focused != edit.get()) return 6;
   session->set_key_pressed(::user::e_key_shift, true);
   reset_key(key);
   if (!edit->handle_tab_key(&key) || focused != cancel.get()) return 7;
   reset_key(key);
   ok->route_message(&key);
   if (focused != edit.get()) return 8;
   session->set_key_pressed(::user::e_key_shift, false);

   cancel->m_bEnabled = false;
   if (form->next_tab_focus(ok) != edit.get()) return 9;
   cancel->m_bEnabled = true;
   row->m_bVisible = false;
   if (form->next_tab_focus(edit) != edit.get()) return 10;
   row->m_bVisible = true;
   row->m_bEnabled = false;
   if (form->next_tab_focus(edit) != edit.get()) return 11;
   row->m_bEnabled = true;
   form->m_children.add(check);
   check->m_parent = form;
   if (form->next_tab_focus(cancel) != check.get()) return 12;
   reset_key(key);
   if (!check->handle_tab_key(&key) || focused != edit.get()) return 13;
   check->m_bEnabled = false;
   if (check->keyboard_focus_is_focusable() || form->next_tab_focus(cancel) != edit.get()) return 14;
   edit->m_bEnabled = false;
   if (edit->keyboard_focus_is_focusable()) return 15;
   edit->m_bEnabled = true;

   session->set_key_pressed(::user::e_key_control, true);
   reset_key(key);
   if (ok->handle_tab_key(&key) || key.m_bRet) return 16;
   session->set_key_pressed(::user::e_key_control, false);
   reset_key(key, ::user::e_key_space);
   if (ok->handle_tab_key(&key) || key.m_bRet) return 17;
   form->payload("tab_focus_scope") = false;
   reset_key(key);
   if (ok->handle_tab_key(&key) || key.m_bRet) return 18;
   int actions = 0;
   ok->m_callbackOnAction = [&](::user::interaction *, ::item *, ::user::activation_token *) { ++actions; return true; };
   reset_key(key, ::user::e_key_space);
   ok->route_message(&key);
   if (!key.m_bRet || actions != 1) return 19;
   reset_key(key, ::user::e_key_return);
   ok->route_message(&key);
   if (!key.m_bRet || actions != 2) return 20;
   // Mouse callbacks retain precedence; an unhandled click falls through.
   ::user::mouse mouse;
   ok->m_callbackOnClick = [](::user::interaction *, ::item *, ::user::activation_token *) { return true; };
   if (!ok->on_click_generation(nullptr, &mouse) || actions != 2) return 21;
   ok->m_callbackOnClick = [](::user::interaction *, ::item *, ::user::activation_token *) { return false; };
   if (!ok->on_click_generation(nullptr, &mouse) || actions != 3) return 22;
   ok->m_bEnabled = false;
   reset_key(key, ::user::e_key_return);
   ok->route_message(&key);
   if (actions != 3 || ok->on_action()) return 23;
   ok->m_bEnabled = true;
   ok->m_callbackOnClick = {};
   if (!ok->on_click_generation(nullptr, nullptr) || actions != 4) return 24;
   ok->m_bHandleClick = true;
   if (!ok->on_click_generation(nullptr, nullptr) || actions != 4) return 25;
   app->m_psession = nullptr;
   return 0;
}
