#include "framework.h"
#include "edit.h"
#include "edit_impl.h"
#include "format_tool.h"
#include "document.h"
#include "span.h"
#include "acme/constant/id.h"
#include "acme/platform/timer.h"
#include "acme/constant/message.h"
#include "acme/constant/timer.h"
#include "aura/message/user.h"
#include "aura/user/user/frame.h"
#include "aura/user/user/copydesk.h"
#include "aura/platform/session.h"


namespace user
{


   namespace rich_text
   {


      edit::edit()
      {

      }


      //edit::edit(::particle * pparticle) :
      //   ::object(pparticle),
      //   ::user::picture(pparticle),
      //   ::user::picture_interaction(pparticle)
      //{

      //}


      edit::~edit()
      {

      }


      void edit::update_data(bool bSaveAndValidate)
      {

         if (bSaveAndValidate)
         {

         }
         else
         {

            set_need_layout();

            set_need_redraw();

         }

         //return true;

      }


//      void edit::assert_ok() const
//      {
//
//         ::user::interaction::assert_ok();
//
//      }
//
//
//      void edit::dump(dump_context & dumpcontext) const
//      {
//
//         ::user::interaction::dump(dumpcontext);
//
//      }


      void edit::install_message_routing(::channel * pchannel)
      {

         ::user::interaction::install_message_routing(pchannel);

         MESSAGE_LINK(MESSAGE_CREATE, pchannel, this, &edit::on_message_create);
         MESSAGE_LINK(MESSAGE_DESTROY, pchannel, this, &edit::on_message_destroy);
         MESSAGE_LINK(e_message_show_window, pchannel, this, &edit::on_message_show_window);
         MESSAGE_LINK(e_message_left_button_down, pchannel, this, &edit::on_message_left_button_down);
         MESSAGE_LINK(e_message_left_button_up, pchannel, this, &edit::on_message_left_button_up);
         MESSAGE_LINK(e_message_mouse_move, pchannel, this, &edit::on_message_mouse_move);
         MESSAGE_LINK(e_message_mouse_leave, pchannel, this, &edit::on_message_mouse_leave);
         MESSAGE_LINK(e_message_key_down, pchannel, this, &edit::on_message_key_down);
         MESSAGE_LINK(e_message_key_up, pchannel, this, &edit::on_message_key_up);
//         MESSAGE_LINK(e_message_set_focus, pchannel, this, &edit::on_message_set_focus);
         //MESSAGE_LINK(e_message_kill_focus, pchannel, this, &edit::on_message_kill_focus);
         
#ifdef WINDOWS_DESKTOP

         text_composition_composite::initialize_text_composition_client(pchannel, this);
         
#endif

      }


      void edit::on_message_create(::message::message * pmessage)
      {

         ::pointer<::message::create>pcreate(pmessage);

         pcreate->previous();

         if (pcreate->m_bRet)
         {

            return;

         }

         auto psession = get_session();

//#if !defined(APPLE_IOS) && !defined(ANDROID)

  //       psession->keyboard(); // trigger keyboard creationg

//#endif

         SetTimer(100, 100_ms, nullptr);

         SetTimer(e_timer_redraw, 200_ms, nullptr); // Caret

      }


      void edit::on_message_destroy(::message::message * pmessage)
      {

      }


      void edit::on_message_show_window(::message::message * pmessage)
      {

         __UNREFERENCED_PARAMETER(pmessage);
         //::pointer<::message::show_window>pshowwindow(pmessage);

      }


      void edit::on_set_keyboard_focus()
      {
         
         //__UNREFERENCED_PARAMETER(pmessage);

         //::pointer<::message::set_focus>psetfocus(pmessage);

         if (!is_text_editable())
         {

            return;

         }

         auto pformattool = get_format_tool(true);

         pformattool->show_for_ui(this);

      }


      void edit::on_kill_keyboard_focus()
      {

         //::pointer<::message::kill_focus>pkillfocus(pmessage);

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

         __UNREFERENCED_PARAMETER(pmessage);
         
         //auto pmouse = pmessage->m_union.m_pmouse;

      }


      void edit::on_message_left_button_up(::message::message * pmessage)
      {

         __UNREFERENCED_PARAMETER(pmessage);
         
         //auto pmouse = pmessage->m_union.m_pmouse;

      }


      void edit::on_message_mouse_move(::message::message * pmessage)
      {

         __UNREFERENCED_PARAMETER(pmessage);
         
         //auto pmouse = pmessage->m_union.m_pmouse;

      }


      ::size_f64 edit::get_size()
      {

         ::rectangle_i32 rectangle;

         window_rectangle(rectangle);

         return rectangle.size();

      }


      void edit::do_layout()
      {


      }



      void edit::on_message_mouse_leave(::message::message * pmessage)
      {

         release_mouse_capture();

         set_need_redraw();

      }


      bool edit::get_element_rect(RECTANGLE_I32 * prectangle, index i, enum_element eelement)

      {

         if (eelement == ::e_element_icon)
         {

            if (!get_item_rect(prectangle, i))

            {

               return false;

            }

            return true;

         }
         else if (eelement == ::e_element_text)
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


      ::item_pointer edit::on_hit_test(const ::point_i32 &point, ::user::e_zorder ezorder)
      {

         return ::user::interaction::on_hit_test(point, ezorder);

      }


      void edit::_001GetText(string & str)
      {

         ::user::interaction::_001GetText(str);

      }


      void edit::_001GetLayoutText(string & str)
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


      bool edit::_001IsPointInside(const ::point_i32 & pointParam)
      {

         if (is_picture_enabled())
         {

            point_f64 point(pointParam);

            screen_to_client()(point);

            ::rectangle_i32 rWindow;
            
            window_rectangle(rWindow);

            rectangle_f64 rectangleWindow;

            copy(rectangleWindow, rWindow);
            
            get_parent()->screen_to_client()(rectangleWindow);

            copy(rectangleWindow, rectangleWindow);

            point += rectangleWindow.top_left();

            _rtransform_point(point);

            point -= rectangleWindow.top_left();

            auto rectangleClient = client_rectangle();

            return rectangleClient.contains(::point_i32(point));

         }

         return ::user::interaction::_001IsPointInside(pointParam);

      }


      bool edit::_001GetItemText(string & str, index iItem)
      {

         return false;

      }


      void edit::on_layout(::draw2d::graphics_pointer & pgraphics)
      {

         auto rectangleClient = client_rectangle();

         if (rectangleClient.is_empty())
         {

            return;

         }

      }


      void edit::handle(::topic * ptopic, ::context * pcontext)
      {

         return ::user::interaction::handle(ptopic, pcontext);

      }


      ::pointer<format_tool>edit::get_format_tool(bool bCreate)
      {

         auto pformattool = top_level_frame()->tool_window(e_tool_font, bCreate);

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

         on_message_character(pmessage);

      }


      void edit::on_message_key_down(::message::message * pmessage)
      {

         {

            auto ptopic = create_topic(::id_key_down);

            ptopic->m_puserelement = this;

            ptopic->m_actioncontext.m_pmessage = pmessage;

            ptopic->m_actioncontext = ::e_source_user;

            route(ptopic);

            if (ptopic->m_bRet)
            {

               return;

            }

         }

         auto pkey = pmessage->m_union.m_pkey;

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

            auto ptopic = create_topic(::id_escape);

            ptopic->m_puserelement = this;

            ptopic->m_atom = ::id_escape;

            ptopic->m_actioncontext = ::e_source_user;

            route(ptopic);

            if (!ptopic->m_bRet && ptopic->m_bOk)
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

               auto pcopydesk = copydesk();

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

               auto pcopydesk = copydesk();

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


      void edit::on_message_key_up(::message::message * pmessage)
      {

         auto pkey = pmessage->m_union.m_pkey;

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

               SetTimer(501, 300_ms, nullptr);

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

         if (key.m_ekey == ::user::e_key_shift || key.m_ekey == ::user::e_key_left_shift || key.m_ekey == ::user::e_key_right_shift
            || key.m_ekey == ::user::e_key_control || key.m_ekey == ::user::e_key_left_control || key.m_ekey == ::user::e_key_right_control
            || key.m_ekey == ::user::e_key_alt || key.m_ekey == ::user::e_key_left_alt || key.m_ekey == ::user::e_key_right_alt
            )
         {

            return;

         }

         if (key.m_ekey == ::user::e_key_right || key.m_ekey == ::user::e_key_up
            || key.m_ekey == ::user::e_key_left || key.m_ekey == ::user::e_key_down)
         {

            on_message_character(&key);

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

         on_message_character(&key);

      }


      void edit::_001OnDeleteText()
      {

         on_reset_focus_start_tick();

      }


      void edit::on_message_character(::message::message * pmessage)
      {

      }


      void edit::on_after_change(const ::atom & atom)
      {

      }


      strsize edit::_001GetTextLength()
      {

         return 0;

      }


      void edit::_001GetSel(strsize & iBeg, strsize & iEnd)
      {

      }


      void edit::_001GetSelLineText(string & strText)
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


      //void edit::write(::binary_stream < FILE > & stream) const
      //{

      //   return ::user::picture::write(stream);

      //}


      //void edit::read(::binary_stream < FILE > & stream)
      //{

      //   return ::user::picture::read(stream);

      //}


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


void rich_text_factory_exchange(::factory::factory * pfactory)
{

   pfactory->add_factory_item < ::user::rich_text::edit_impl, ::user::rich_text::edit >();
   //add_factory_item <::user::rich_text::format >();
   pfactory->add_factory_item <::user::rich_text::span >();
   pfactory->add_factory_item <::user::rich_text::document >();

   pfactory->add_factory_item < ::user::rich_text::edit_impl >("rich_text_impact");

}



