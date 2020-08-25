#include "framework.h"
#include "core/user/userex/font_format_tool.h"
#include "aura/const/timer.h"

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

         IGUI_MSG_LINK(WM_CREATE, pchannel, this, &edit::_001OnCreate);
         IGUI_MSG_LINK(WM_DESTROY, pchannel, this, &edit::_001OnDestroy);
         IGUI_MSG_LINK(WM_SHOWWINDOW, pchannel, this, &edit::_001OnShowWindow);
         IGUI_MSG_LINK(WM_LBUTTONDOWN, pchannel, this, &edit::_001OnLButtonDown);
         IGUI_MSG_LINK(WM_LBUTTONUP, pchannel, this, &edit::_001OnLButtonUp);
         IGUI_MSG_LINK(WM_MOUSEMOVE, pchannel, this, &edit::_001OnMouseMove);
         IGUI_MSG_LINK(WM_MOUSELEAVE, pchannel, this, &edit::_001OnMouseLeave);
         IGUI_MSG_LINK(WM_KEYDOWN, pchannel, this, &edit::_001OnKeyDown);
         IGUI_MSG_LINK(WM_KEYUP, pchannel, this, &edit::_001OnKeyUp);
         IGUI_MSG_LINK(WM_SETFOCUS, pchannel, this, &edit::_001OnSetFocus);
         IGUI_MSG_LINK(WM_KILLFOCUS, pchannel, this, &edit::_001OnKillFocus);
         
#ifdef WINDOWS_DESKTOP

         imm_client::install_message_routing(pchannel);
         
#endif

      }


      void edit::_001OnCreate(::message::message * pmessage)
      {

         SCAST_PTR(::message::create, pcreate, pmessage);

         pcreate->previous();

         if (pcreate->m_bRet)
         {

            return;

         }

#if !defined(APPLE_IOS) && !defined(ANDROID)

         Session.keyboard(); // trigger keyboard creationg

#endif

         SetTimer(100, 100, nullptr);

         SetTimer(timer_redraw, 200, nullptr); // Caret

      }


      void edit::_001OnDestroy(::message::message * pmessage)
      {

      }


      void edit::_001OnShowWindow(::message::message * pmessage)
      {

         UNREFERENCED_PARAMETER(pmessage);
         //SCAST_PTR(::message::show_window, pshowwindow, pmessage);

      }


      void edit::_001OnSetFocus(::message::message * pmessage)
      {
         
         UNREFERENCED_PARAMETER(pmessage);

         //SCAST_PTR(::message::set_focus, psetfocus, pmessage);

         if (!is_text_editable())
         {

            return;

         }

         auto pformattool = get_font_format_tool(true);

         pformattool->show_for_ui(this);

      }


      void edit::_001OnKillFocus(::message::message * pmessage)
      {

         SCAST_PTR(::message::kill_focus, pkillfocus, pmessage);

         auto pformattool = get_font_format_tool(false);

         if (pformattool != nullptr && pformattool->is_showing_for_ui(this))
         {

            ::user::primitive_impl * pimplNew = oswindow_interaction_impl(pkillfocus->m_oswindowNew);

            ::user::interaction * pinteraction = nullptr;

            if (pimplNew != nullptr)
            {

               pinteraction = pimplNew->m_puserinteraction;

            }

            if (pkillfocus->m_oswindowNew == pformattool->get_safe_handle()
               || pformattool->is_ascendant_or_owner_of(pinteraction, true))
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


      void edit::_001OnLButtonDown(::message::message * pmessage)
      {

         UNREFERENCED_PARAMETER(pmessage);
         
         //SCAST_PTR(::message::mouse, pmouse, pmessage);

      }


      void edit::_001OnLButtonUp(::message::message * pmessage)
      {

         UNREFERENCED_PARAMETER(pmessage);
         
         //SCAST_PTR(::message::mouse, pmouse, pmessage);

      }


      void edit::_001OnMouseMove(::message::message * pmessage)
      {

         UNREFERENCED_PARAMETER(pmessage);
         
         //SCAST_PTR(::message::mouse, pmouse, pmessage);

      }


      ::sized edit::get_size()
      {

         ::rect rect;

         get_window_rect(rect);

         return rect.size();

      }


      void edit::do_layout()
      {


      }



      void edit::_001OnMouseLeave(::message::message * pmessage)
      {

         ReleaseCapture();

         set_need_redraw();

      }


      bool edit::get_element_rect(RECT * prect, index i, e_element eelement)

      {

         if (eelement == ::user::element_icon)
         {

            if (!get_item_rect(prect, i))

            {

               return false;

            }

            return true;

         }
         else if (eelement == ::user::element_text)
         {

            if (!get_item_rect(prect, i))

            {

               return false;

            }

            return true;


         }

         return false;

      }

      bool edit::get_item_rect(RECT * prect, index i)

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


      bool edit::is_text_editable()
      {

         return is_window_enabled();

      }


      bool edit::is_text_editor()
      {

         return true;

      }


      bool edit::_001IsPointInside(::point pointParam)
      {

         if (is_picture_enabled())
         {

            pointd point(pointParam);

            _001ScreenToClient(point);

            ::rect rWindow;
            
            get_window_rect(rWindow);

            rectd rectWindow;

            __copy(rectWindow, rWindow);
            
            GetParent()->_001ScreenToClient(rectWindow);

            copy(rectWindow, rectWindow);

            point += rectWindow.top_left();

            _rtransform_point(point);

            point -= rectWindow.top_left();

            auto rectClient = get_client_rect();

            return rectClient.contains(::point(point));

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


      __pointer(::userex::font_format_tool) edit::get_font_format_tool(bool bCreate)
      {

         auto pformattool = GetTopLevelFrame()->font_format_tool(bCreate);

         return pformattool;

      }


      bool edit::keyboard_focus_is_focusable()
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

            ev.m_eevent = ::user::event_key_down;

            ev.m_pmessage = pmessage;

            ev.m_actioncontext = ::source_user;

            on_control_event(&ev);

            if (ev.m_bRet)
            {

               return;

            }

         }

         SCAST_PTR(::message::key, pkey, pmessage);

         if (pkey->m_ekey == ::user::key_return)
         {

            if (Session.is_key_pressed(::user::key_control) && Session.is_key_pressed(::user::key_alt))
            {

               pkey->m_bRet = false;

               return;

            }

         }
         else if (pkey->m_ekey == ::user::key_tab)
         {

            if (Session.is_key_pressed(::user::key_control) && Session.is_key_pressed(::user::key_alt))
            {

               pkey->m_bRet = false;

               return;

            }

         }
         else if (pkey->m_ekey == ::user::key_alt)
         {

            pkey->m_bRet = false;

            return;

         }
         else if (pkey->m_ekey == ::user::key_escape)
         {

            ::user::control_event ev;

            ev.m_puie = this;

            ev.m_eevent = ::user::event_escape;

            ev.m_actioncontext = ::source_user;

            on_control_event(&ev);

            if (!ev.m_bRet && ev.m_bOk)
            {

               on_action("escape");

            }

            pmessage->m_bRet = true;

            return;

         }
         else if (pkey->m_ekey == ::user::key_c)
         {

            if (Session.is_key_pressed(::user::key_control))
            {

               pkey->m_bRet = true;

               string str;

               _001GetSelText(str);

               if (str.is_empty())
               {

                  _001GetSelLineText(str);

               }

               Session.copydesk().set_plain_text(str);

               return;

            }

         }
         else if (pkey->m_ekey == ::user::key_v)
         {

            if (Session.is_key_pressed(::user::key_control))
            {

               pkey->m_bRet = true;

               if (is_window_enabled())
               {

               }

               return;

            }

         }
         else if (pkey->m_ekey == ::user::key_x)
         {

            if (Session.is_key_pressed(::user::key_control))
            {

               pkey->m_bRet = true;

               string str;

               _001GetSelText(str);

               Session.copydesk().set_plain_text(str);

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

         SCAST_PTR(::message::key, pkey, pmessage);

         if (pkey->m_ekey == ::user::key_return)
         {

            if (Session.is_key_pressed(::user::key_control) && Session.is_key_pressed(::user::key_alt))
            {
               pkey->m_bRet = false;
               return;
            }
         }
         else if (pkey->m_ekey == ::user::key_alt)
         {

            pkey->m_bRet = false;

         }

      }


      void edit::_001OnTimer(::timer * ptimer)
      {

         ::user::interaction::_001OnTimer(ptimer);

         if (ptimer->m_nIDEvent >= 100 && ptimer->m_nIDEvent <= 200)
         {

         }
         else if (ptimer->m_nIDEvent == 500 || ptimer->m_nIDEvent == 501)
         {

            if (ptimer->m_nIDEvent == 500)
            {

               KillTimer(500);

               SetTimer(501, 300, nullptr);

            }

         }
         else if (ptimer->m_nIDEvent == timer_redraw)
         {

            // Caret

            if (is_text_editable() && is_window_visible() && has_focus())
            {

               set_need_redraw();

            }

         }

      }


      void edit::key_to_char(::message::key * pkey)
      {

         ::message::key & key = *pkey;

         if (key.m_ekey == ::user::key_shift || key.m_ekey == ::user::key_lshift || key.m_ekey == ::user::key_rshift
            || key.m_ekey == ::user::key_control || key.m_ekey == ::user::key_lcontrol || key.m_ekey == ::user::key_rcontrol
            || key.m_ekey == ::user::key_alt || key.m_ekey == ::user::key_lalt || key.m_ekey == ::user::key_ralt
            )
         {

            return;

         }

         if (key.m_ekey == ::user::key_right || key.m_ekey == ::user::key_up
            || key.m_ekey == ::user::key_left || key.m_ekey == ::user::key_down)
         {

            _001OnChar(&key);

            return;

         }

         bool bShift = Session.is_key_pressed(::user::key_shift);

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


      void edit::on_after_change(::user::e_event eevent)
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

         set_window_pos(zorder_none, ::rect(m_ppictureimpl->m_rect), SWP_NOZORDER);

      }


      stream & edit::write(::stream & stream) const
      {

         return ::user::picture::write(stream);

      }


      stream & edit::read(::stream & stream)
      {

         return ::user::picture::read(stream);

      }


      void edit::get_text_composition_area(::rect & r)
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





