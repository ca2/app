#include "framework.h"
#include "core/user/rich_text/_rich_text.h"
#include "core/user/userex/_userex.h"
#include "acme/const/timer.h"


namespace user
{


   namespace rich_text
   {


      edit::edit()
      {

      }


      //edit::edit(::object * pobject) :
      //   ::object(pobject),
      //   ::user::picture(pobject),
      //   ::user::picture_interaction(pobject)
      //{

      //}


      edit::~edit()
      {

      }


      bool edit::update_data(bool bSaveAndValidate)
      {

         if (bSaveAndValidate)
         {

         }
         else
         {

            set_need_layout();

            set_need_redraw();

         }

         return true;

      }


      void edit::assert_valid() const
      {

         ::user::interaction::assert_valid();

      }


      void edit::dump(dump_context & dumpcontext) const
      {

         ::user::interaction::dump(dumpcontext);

      }


      void edit::install_message_routing(::channel * pchannel)
      {

         ::user::interaction::install_message_routing(pchannel);

         MESSAGE_LINK(e_message_create, pchannel, this, &edit::on_message_create);
         MESSAGE_LINK(e_message_destroy, pchannel, this, &edit::_001OnDestroy);
         MESSAGE_LINK(e_message_show_window, pchannel, this, &edit::_001OnShowWindow);
         MESSAGE_LINK(e_message_left_button_down, pchannel, this, &edit::on_message_left_button_down);
         MESSAGE_LINK(e_message_left_button_up, pchannel, this, &edit::on_message_left_button_up);
         MESSAGE_LINK(e_message_mouse_move, pchannel, this, &edit::on_message_mouse_move);
         MESSAGE_LINK(e_message_mouse_leave, pchannel, this, &edit::on_message_mouse_leave);
         MESSAGE_LINK(e_message_key_down, pchannel, this, &edit::_001OnKeyDown);
         MESSAGE_LINK(e_message_key_up, pchannel, this, &edit::_001OnKeyUp);
//         MESSAGE_LINK(e_message_set_focus, pchannel, this, &edit::_001OnSetFocus);
         //MESSAGE_LINK(e_message_kill_focus, pchannel, this, &edit::_001OnKillFocus);
         
#ifdef WINDOWS_DESKTOP

         text_composition_composite::initialize_text_composition_client(pchannel, this);
         
#endif

      }


      void edit::on_message_create(::message::message * pmessage)
      {

         __pointer(::message::create) pcreate(pmessage);

         pcreate->previous();

         if (pcreate->m_bRet)
         {

            return;

         }

         auto psession = get_session();

//#if !defined(APPLE_IOS) && !defined(ANDROID)

  //       psession->keyboard(); // trigger keyboard creationg

//#endif

         SetTimer(100, 100, nullptr);

         SetTimer(e_timer_redraw, 200, nullptr); // Caret

      }


      void edit::_001OnDestroy(::message::message * pmessage)
      {

      }


      void edit::_001OnShowWindow(::message::message * pmessage)
      {

         UNREFERENCED_PARAMETER(pmessage);
         //__pointer(::message::show_window) pshowwindow(pmessage);

      }


      void edit::on_set_keyboard_focus()
      {
         
         //UNREFERENCED_PARAMETER(pmessage);

         //__pointer(::message::set_focus) psetfocus(pmessage);

         if (!is_text_editable())
         {

            return;

         }

         auto pformattool = get_format_tool(true);

         pformattool->show_for_ui(this);

      }


      void edit::on_kill_keyboard_focus()
      {

         //__pointer(::message::kill_focus) pkillfocus(pmessage);

         auto pformattool = get_format_tool(false);

         if (pformattool != nullptr && pformattool->is_showing_for_ui(this))
         {

            auto psession = get_session();

            auto puser = psession->user();

            //auto puserinteractionFocusNew = puser->interaction(pkillfocus->m_oswindowNew);

            ::user::interaction * pinteraction = nullptr;

  /*          if (puserinteractionFocusNew != nullptr)
            {

               pinteraction = puserinteractionFocusNew;

            }*/

            //if (pkillfocus->m_oswindowNew == pformattool->get_oswindow()
            if(pformattool->is_ascendant_or_owner_of(pinteraction, true))
            {

               output_debug_string("Window winning focus is own font format tool");

               return;

            }

            pformattool->hide();

         }

      }


      void edit::on_selection_change()
      {

      }


      void edit::on_message_left_button_down(::message::message * pmessage)
      {

         UNREFERENCED_PARAMETER(pmessage);
         
         //__pointer(::message::mouse) pmouse(pmessage);

      }


      void edit::on_message_left_button_up(::message::message * pmessage)
      {

         UNREFERENCED_PARAMETER(pmessage);
         
         //__pointer(::message::mouse) pmouse(pmessage);

      }


      void edit::on_message_mouse_move(::message::message * pmessage)
      {

         UNREFERENCED_PARAMETER(pmessage);
         
         //__pointer(::message::mouse) pmouse(pmessage);

      }


      ::size_f64 edit::get_size()
      {

         ::rectangle_i32 rectangle;

         get_window_rect(rectangle);

         return rectangle.size();

      }


      void edit::do_layout()
      {


      }



      void edit::on_message_mouse_leave(::message::message * pmessage)
      {

         auto psession = get_session();

         auto puser = psession->user();

         auto pwindowing = puser->windowing();

         pwindowing->release_mouse_capture();

         set_need_redraw();

      }


      bool edit::get_element_rect(RECTANGLE_I32 * prectangle, index i, enum_element eelement)

      {

         if (eelement == ::user::e_element_icon)
         {

            if (!get_item_rect(prectangle, i))

            {

               return false;

            }

            return true;

         }
         else if (eelement == ::user::e_element_text)
         {

            if (!get_item_rect(prectangle, i))

            {

               return false;

            }

            return true;


         }

         return false;

      }

      bool edit::get_item_rect(RECTANGLE_I32 * prectangle, index i)

      {

         return true;

      }


      double edit::get_rotate()
      {

         if (is_picture_enabled())
         {

            return m_ppictureimpl->m_dRotate;

         }

         return 0.0;

      }


      void edit::on_hit_test(::user::item & item)
      {

         ::user::interaction::on_hit_test(item);

      }


      void edit::_001GetText(string & str) const
      {

         ::user::interaction::_001GetText(str);

      }


      void edit::_001GetLayoutText(string & str) const
      {

      }


      void edit::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
      {
         
      }


      void edit::draw_impl(::draw2d::graphics_pointer & pgraphics)
      {

      }


      ::user::rich_text::data * edit::get_rich_text_data()
      {

         return nullptr;

      }


      bool edit::set_text_editable(bool bEditable)
      {

         return false;

      }


      bool edit::is_text_editable() const
      {

         return is_window_enabled();

      }


      bool edit::is_text_editor() const
      {

         return true;

      }


      bool edit::_001IsPointInside(const ::point_i32 & pointParam)
      {

         if (is_picture_enabled())
         {

            point_f64 point(pointParam);

            _001ScreenToClient(point);

            ::rectangle_i32 rWindow;
            
            get_window_rect(rWindow);

            rectangle_f64 rectWindow;

            __copy(rectWindow, rWindow);
            
            get_parent()->_001ScreenToClient(rectWindow);

            copy(rectWindow, rectWindow);

            point += rectWindow.top_left();

            _rtransform_point(point);

            point -= rectWindow.top_left();

            auto rectClient = get_client_rect();

            return rectClient.contains(::point_i32(point));

         }

         return ::user::interaction::_001IsPointInside(pointParam);

      }


      bool edit::_001GetItemText(string & str, index iItem)
      {

         return false;

      }


      void edit::on_layout(::draw2d::graphics_pointer & pgraphics)
      {

         auto rectClient = get_client_rect();

         if (rectClient.is_empty())
         {

            return;

         }

      }


      void edit::on_control_event(::user::control_event * pevent)
      {

         return ::user::interaction::on_control_event(pevent);

      }


      __pointer(format_tool) edit::get_format_tool(bool bCreate)
      {

         auto pformattool = top_level_frame()->tool_window(e_tool_font, bCreate);

         return pformattool;

      }


      bool edit::keyboard_focus_is_focusable() const
      {

         return is_window_visible() && is_text_editable();

      }


      void edit::keyboard_focus_OnChar(::message::message * pmessage)
      {

         if (!is_text_editable())
         {

            return;

         }

         _001OnChar(pmessage);

      }


      void edit::_001OnKeyDown(::message::message * pmessage)
      {

         {

            ::user::control_event ev;

            ev.m_puie = this;

            ev.m_eevent = ::user::e_event_key_down;

            ev.m_pmessage = pmessage;

            ev.m_actioncontext = ::e_source_user;

            on_control_event(&ev);

            if (ev.m_bRet)
            {

               return;

            }

         }

         __pointer(::message::key) pkey(pmessage);

         auto psession = get_session();

         if (pkey->m_ekey == ::user::e_key_return)
         {

            if (psession->is_key_pressed(::user::e_key_control) && psession->is_key_pressed(::user::e_key_alt))
            {

               pkey->m_bRet = false;

               return;

            }

         }
         else if (pkey->m_ekey == ::user::e_key_tab)
         {

            if (psession->is_key_pressed(::user::e_key_control) && psession->is_key_pressed(::user::e_key_alt))
            {

               pkey->m_bRet = false;

               return;

            }

         }
         else if (pkey->m_ekey == ::user::e_key_alt)
         {

            pkey->m_bRet = false;

            return;

         }
         else if (pkey->m_ekey == ::user::e_key_escape)
         {

            ::user::control_event ev;

            ev.m_puie = this;

            ev.m_eevent = ::user::e_event_escape;

            ev.m_actioncontext = ::e_source_user;

            on_control_event(&ev);

            if (!ev.m_bRet && ev.m_bOk)
            {

               on_action("escape");

            }

            pmessage->m_bRet = true;

            return;

         }
         else if (pkey->m_ekey == ::user::e_key_c)
         {

            if (psession->is_key_pressed(::user::e_key_control))
            {

               pkey->m_bRet = true;

               string str;

               _001GetSelText(str);

               if (str.is_empty())
               {

                  _001GetSelLineText(str);

               }

               auto pcopydesk = psession->copydesk();

               pcopydesk->set_plain_text(str);

               return;

            }

         }
         else if (pkey->m_ekey == ::user::e_key_v)
         {

            if (psession->is_key_pressed(::user::e_key_control))
            {

               pkey->m_bRet = true;

               if (is_window_enabled())
               {

               }

               return;

            }

         }
         else if (pkey->m_ekey == ::user::e_key_x)
         {

            if (psession->is_key_pressed(::user::e_key_control))
            {

               pkey->m_bRet = true;

               string str;

               _001GetSelText(str);

               auto pcopydesk = psession->copydesk();

               pcopydesk->set_plain_text(str);

               if (is_window_enabled())
               {

                  _001OnDeleteText();

               }

               return;

            }

         }

         pkey->m_bRet = true;

      }


      void edit::_001OnKeyUp(::message::message * pmessage)
      {

         __pointer(::message::key) pkey(pmessage);

         auto psession = get_session();

         if (pkey->m_ekey == ::user::e_key_return)
         {

            if (psession->is_key_pressed(::user::e_key_control) && psession->is_key_pressed(::user::e_key_alt))
            {
               pkey->m_bRet = false;
               return;
            }
         }
         else if (pkey->m_ekey == ::user::e_key_alt)
         {

            pkey->m_bRet = false;

         }

      }


      void edit::_001OnTimer(::timer * ptimer)
      {

         ::user::interaction::_001OnTimer(ptimer);

         if (ptimer->m_uEvent >= 100 && ptimer->m_uEvent <= 200)
         {

         }
         else if (ptimer->m_uEvent == 500 || ptimer->m_uEvent == 501)
         {

            if (ptimer->m_uEvent == 500)
            {

               KillTimer(500);

               SetTimer(501, 300, nullptr);

            }

         }
         else if (ptimer->m_uEvent == e_timer_redraw)
         {

            // Caret

            if (is_text_editable() && is_window_visible() && has_keyboard_focus())
            {

               set_need_redraw();

            }

         }

      }


      void edit::key_to_char(::message::key * pkey)
      {

         ::message::key & key = *pkey;

         if (key.m_ekey == ::user::e_key_shift || key.m_ekey == ::user::e_key_lshift || key.m_ekey == ::user::e_key_rshift
            || key.m_ekey == ::user::e_key_control || key.m_ekey == ::user::e_key_lcontrol || key.m_ekey == ::user::e_key_rcontrol
            || key.m_ekey == ::user::e_key_alt || key.m_ekey == ::user::e_key_lalt || key.m_ekey == ::user::e_key_ralt
            )
         {

            return;

         }

         if (key.m_ekey == ::user::e_key_right || key.m_ekey == ::user::e_key_up
            || key.m_ekey == ::user::e_key_left || key.m_ekey == ::user::e_key_down)
         {

            _001OnChar(&key);

            return;

         }

         auto psession = get_session();

         bool bShift = psession->is_key_pressed(::user::e_key_shift);

         if (key.m_nChar < 256 && isalpha((i32)key.m_nChar))
         {

            if (bShift)
            {

               key.m_nChar = toupper((i32)key.m_nChar);

            }
            else
            {

               key.m_nChar = tolower((i32)key.m_nChar);

            }

         }

         _001OnChar(&key);

      }


      void edit::_001OnDeleteText()
      {

         on_reset_focus_start_tick();

      }


      void edit::_001OnChar(::message::message * pmessage)
      {

      }


      void edit::on_after_change(::user::enum_event eevent)
      {

      }


      strsize edit::_001GetTextLength() const
      {

         return 0;

      }


      void edit::_001GetSel(strsize & iBeg, strsize & iEnd) const
      {

      }


      void edit::_001GetSelLineText(string & strText) const
      {

      }




      void edit::update_placement()
      {

         if (m_ppictureimpl == nullptr)
         {

            return;

         }

         place(m_ppictureimpl->m_rectangle);

      }


      stream & edit::write(::stream & stream) const
      {

         return ::user::picture::write(stream);

      }


      stream & edit::read(::stream & stream)
      {

         return ::user::picture::read(stream);

      }


      void edit::get_text_composition_area(::rectangle_i32 & r)
      {

      }


      void edit::on_text_composition(string str)
      {

      }


      void edit::on_text_composition_done()
      {

      }


      bool edit::edit_undo()
      {

         return false;

      }


      bool edit::has_text_input()
      {

         return is_window_enabled() && is_text_editor() && is_text_editable();

      }


   } // namespace rich_text


} // namespace user




bool __rich_text_initialize()
{

   create_factory < ::user::rich_text::edit_impl, ::user::rich_text::edit >();
   //create_factory <::user::rich_text::format >();
   create_factory <::user::rich_text::span >();
   create_factory <::user::rich_text::document >();

   create_factory < ::user::rich_text::edit_impact >("rich_text_impact");

   return true;

}





