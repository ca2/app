#include "framework.h"
#include "edit_impl.h"
#include "format_tool.h"
//#include "document.h"
#include "data.h"
#include "format.h"
#include "acme/constant/id.h"
#include "acme/constant/message.h"
#include "acme/constant/timer.h"
#include "acme/constant/user_key.h"
#include "acme/filesystem/file/memory_file.h"
#include "acme/handler/item.h"
#include "acme/handler/topic.h"
#include "acme/platform/node.h"
#include "acme/platform/timer.h"
#include "acme/prototype/geometry2d/_binary_stream.h"
#include "acme/prototype/string/str.h"
#include "acme/platform/scoped_restore.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/message/user.h"
#include "aura/user/user/frame.h"
#include "aura/user/user/copydesk.h"
#include "base/user/user/user.h"
#include "core/platform/session.h"


namespace user
{


   namespace rich_text
   {


      edit_impl::edit_impl()
      {

         m_bComposing = false;
         m_bEditable2 = true;
         m_bClickThrough = false;
         m_bPendingSelectionChange = false;

      }


      //void edit_impl::initialize_impact(::user::document * pdocument)
      //{

      //   //auto estatus =
      //   
      //   ::user::rich_text::edit::initialize(pdocument);

      //   ::user::impact::initialize_impact(pdocument);


      //}


      edit_impl::~edit_impl()
      {

      }


      void edit_impl::update_data(bool bSaveAndValidate)
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


      //void edit_impl::assert_ok() const
      //{

      //   ::user::interaction::assert_ok();

      //}


      //void edit_impl::dump(dump_context & dumpcontext) const
      //{

      //   ::user::interaction::dump(dumpcontext);

      //}


      void edit_impl::install_message_routing(::channel * pchannel)
      {

         ::user::rich_text::edit::install_message_routing(pchannel);

         MESSAGE_LINK(MESSAGE_CREATE, pchannel, this, &edit_impl::on_message_create);
         MESSAGE_LINK(MESSAGE_DESTROY, pchannel, this, &edit_impl::on_message_destroy);
         MESSAGE_LINK(e_message_show_window, pchannel, this, &edit_impl::on_message_show_window);
         MESSAGE_LINK(e_message_left_button_down, pchannel, this, &edit_impl::on_message_left_button_down);
         MESSAGE_LINK(e_message_left_button_up, pchannel, this, &edit_impl::on_message_left_button_up);
         MESSAGE_LINK(e_message_mouse_move, pchannel, this, &edit_impl::on_message_mouse_move);
         MESSAGE_LINK(e_message_mouse_leave, pchannel, this, &edit_impl::on_message_mouse_leave);
         MESSAGE_LINK(e_message_key_down, pchannel, this, &edit_impl::on_message_key_down);
         MESSAGE_LINK(e_message_key_up, pchannel, this, &edit_impl::on_message_key_up);
         //MESSAGE_LINK(e_message_set_focus, pchannel, this, &edit_impl::on_message_set_focus);
         //MESSAGE_LINK(e_message_kill_focus, pchannel, this, &edit_impl::on_message_kill_focus);


         text_composition_composite::initialize_text_composition_client(pchannel, this);

         //#ifdef WINDOWS_DESKTOP
         //
         //         imm_client::install_message_routing(pchannel);
         //
         //#endif

      }


      void edit_impl::on_message_create(::message::message * pmessage)
      {

         ::pointer<::message::create>pcreate(pmessage);

         pcreate->previous();

         if (pcreate->m_bRet)
         {

            return;

         }

         //auto estatus = 

         //initialize_impact(get_document());

         //if (!estatus)
         //{

         //   pcreate->set_fail();

         //   return;

         //}

         auto psession = get_session();

         //prichtextdata->set_synchronization(synchronization());

         fork([this]()
            {

               top_level_frame()->tool_window(::user::e_tool_font, true);

            });

         //#if !defined(APPLE_IOS) && !defined(ANDROID)
         //         psession->keyboard(); // trigger keyboard creationg
         //#endif


         SetTimer(100, 100_ms, nullptr);

         SetTimer(e_timer_redraw, 200_ms, nullptr); // Caret

      }


      void edit_impl::on_message_destroy(::message::message * pmessage)
      {

      }


      void edit_impl::on_message_show_window(::message::message * pmessage)
      {

         ::pointer<::message::show_window>pshowwindow(pmessage);

         if (pshowwindow->m_bShow)
         {

            if (is_text_editable() && m_bEditable2)
            {

               SetTimer(250, 500_ms, nullptr); // Caret

            }

         }
         else
         {

            auto pformattool = get_format_tool(false);

            if (pformattool != nullptr && pformattool->is_showing_for_ui(this))
            {

               pformattool->hide();

            }

         }

      }


      ::user::rich_text::format_host * edit_impl::get_format_host()
      {

         auto prichtextdata = get_rich_text_data();

         return prichtextdata;

      }


      void edit_impl::on_set_keyboard_focus()
      {

         information() << "on_set_keyboard_focus";

         information() << node()->get_call_stack_trace();

         //__UNREFERENCED_PARAMETER(pmessage);

         //::pointer<::message::set_focus>psetfocus(pmessage);

         if (!is_text_editable())
         {

            return;

         }

         auto pformattool = get_format_tool(true);

         ::user::rich_text::selection * pselection = this;

         pformattool->show_for_ui(this, pselection);

         //::user::rich_text::edit::on_set_keyboard_focus();

      }


      void edit_impl::on_kill_keyboard_focus()
      {

         auto pformattool = get_format_tool(false);

         if (pformattool != nullptr && pformattool->is_showing_for_ui(this))
         {

            auto psession = get_session();

            auto puser = psession->user();

            //auto puserinteractionFocusNew = puser->interaction(pkillfocus->m_oswindowNew);

            ::user::interaction * pinteraction = nullptr;

            /*if (puserinteractionFocusNew != nullptr)
            {

               pinteraction = puserinteractionFocusNew;

            }*/

            if (pformattool->is_ascendant_or_owner_of(pinteraction, true))
            {

               informationf("Window winning focus is own font format tool");

               return;

            }

            pformattool->hide();

         }

         ::user::rich_text::edit::on_kill_keyboard_focus();

      }


      void edit_impl::insert_text(const ::scoped_string & scopedstr, bool bForceNewStep, const ::action_context & context)
      {

         _001InsertText(scopedstr);

      }


      void edit_impl::on_selection_change()
      {

         auto pformattool = get_format_tool(false);

         if (pformattool.is_set())
         {

            pformattool->m_pformat = get_selection_common_format();

            pformattool->update_data(false);

         }

      }


      ::pointer<format>edit_impl::get_selection_common_format()
      {

         auto prichtextdata = get_rich_text_data();

         _synchronous_lock synchronouslock(prichtextdata->synchronization());

         auto pformatSelectionCommon = __create_new < format >();

         pformatSelectionCommon->initialize_user_rich_text_format(prichtextdata);

         on_selection_change(pformatSelectionCommon);

         return pformatSelectionCommon;

      }


      void edit_impl::on_message_left_button_down(::message::message * pmessage)
      {

         auto pmouse = pmessage->m_union.m_pmouse;

         if (!is_text_editable())
         {

            return;

         }

         auto psession = get_session();

         auto pitem = hit_test(pmouse, ::user::e_zorder_any);

         auto prichtextdata = get_rich_text_data();

         if (pitem)
         {

            auto pformattool = get_format_tool(true);

            ::user::rich_text::selection * pselection = this;

            pformattool->show_for_ui(this, pselection);

            m_bSelDrag = true;

            m_timeStartDrag.Now();

            if (psession->is_key_pressed(e_key_shift))
            {

               if (pitem->m_item.m_iItem < minimum(m_iSelBeg, m_iSelEnd))
               {

                  m_iSelBeg = maximum(m_iSelBeg, m_iSelEnd);

               }
               else if (pitem->m_item.m_iItem > maximum(m_iSelBeg, m_iSelEnd))
               {

                  m_iSelBeg = minimum(m_iSelBeg, m_iSelEnd);

               }

            }
            else
            {

               m_iSelBeg = pitem->m_item.m_iItem;

            }

            m_iSelEnd = pitem->m_item.m_iItem;

            internal_update_sel_char();

            set_mouse_capture();

            set_keyboard_focus();

            psession->user()->set_mouse_focus_LButtonDown(this);

            pmouse->m_bRet = true;

            m_bPendingSelectionChange = true;

            set_need_redraw();

            post_redraw();

         }
         else if (m_bClickThrough)
         {

            auto pformattool = get_format_tool(false);

            if (pformattool->is_window_visible())
            {

               pformattool->hide();

            }

         }
         else
         {

            pmouse->m_bRet = true;

         }

      }


      void edit_impl::on_message_left_button_up(::message::message * pmessage)
      {

         auto pmouse = pmessage->m_union.m_pmouse;

         defer_release_mouse_capture();

         if (!is_text_editable())
         {

            return;

         }

         m_bSelDrag = false;

         auto pitem = hit_test(pmouse, ::user::e_zorder_any);

         auto psession = get_session();

         auto prichtextdata = get_rich_text_data();

         if (pitem && psession->user()->get_mouse_focus_LButtonDown() == this)
         {

            m_iSelEnd = pitem->m_item.m_iItem;

            internal_update_sel_char();

            pmouse->m_bRet = true;

            on_reset_focus_start_tick();

            m_bPendingSelectionChange = true;

            set_need_redraw();

            post_redraw();

         }
         else if (!m_bClickThrough)
         {

            pmouse->m_bRet = true;

         }

      }


      void edit_impl::on_message_mouse_move(::message::message * pmessage)
      {

         auto pmouse = pmessage->m_union.m_pmouse;

         if (!is_text_editable())
         {

            return;

         }

         m_pitemHover = hit_test(pmouse, ::user::e_zorder_any);

         if (::is_set(m_pitemHover))
         {

            auto pcursor = get_mouse_cursor(e_cursor_text_select);

            user_mouse_set_cursor(pmouse, pcursor);

            pmouse->m_bRet = true;

         }

         auto prichtextdata = get_rich_text_data();

         if (m_bSelDrag && m_timeStartDrag.elapsed() > 300_ms)
         {

            if (!::is_item(m_pitemHover, m_iSelEnd))
            {

               m_iSelEnd = m_pitemHover->m_item.m_iItem;

               internal_update_sel_char();

               pmouse->m_bRet = true;

               m_bPendingSelectionChange = true;

               set_need_redraw();

               post_redraw();

            }

         }

         if (!m_bClickThrough)
         {

            auto pcursor = get_mouse_cursor(e_cursor_text_select);

            user_mouse_set_cursor(pmouse, pcursor);

            pmouse->m_bRet = true;

         }

      }


      ::size_f64 edit_impl::get_size()
      {

         if (is_picture_enabled())
         {

            return m_ppictureimpl->m_rectangle.size();

         }
         else
         {

            ::rectangle_i32 rectangle;

            window_rectangle(rectangle);

            return rectangle.size();

         }

      }



      void edit_impl::on_message_mouse_leave(::message::message * pmessage)
      {

         defer_release_mouse_capture();

         set_need_redraw();

      }


      bool edit_impl::get_element_rectangle(::rectangle_i32 * prectangle, ::collection::index i, enum_element eelement)
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

      bool edit_impl::get_item_rect(::rectangle_i32 * prectangle, ::collection::index i)

      {

         return false;

      }


      //::pointer<span>edit_impl::add_span2()
      //{

      //   return prichtextdata->add_span2();

      //}


      ::pointer<span>edit_impl::add_span(::e_align ealignNewLine, bool bEndOfLine)
      {

         auto prichtextdata = get_rich_text_data();

         return prichtextdata->add_span(ealignNewLine, bEndOfLine);

      }


      double edit_impl::get_rotate()
      {

         if (is_picture_enabled())
         {

            return m_ppictureimpl->m_dRotate;

         }

         return 0.0;

      }



      ::item_pointer edit_impl::on_hit_test(const ::point_i32 & point, ::user::e_zorder ezorder)
      {

         auto r = this->raw_rectangle();

         if (!r.contains(point))
         {

            auto pitem = ::place(new ::item(e_element_none));

            return pitem;

         }

         //::point_f64 pointHit = item.m_pointHitTest;

         //if (is_picture_enabled())
         //{
         //
         //   //pointHit -= get_rect_for_picture().origin();

         //   // 1. += get_rect_for_picture();

         //   _001ClientToParent(pointHit);

         //   // 2. += get_rect_for_picture();

         //   drag_rtransform_point(pointHit);

         //   // 3. += get_rect_for_picture();

         //   //_001ParentToClient(pointHit);

         //   // 4. += get_rect_for_picture();

         //   //m_ppictureimpl->m_dZoom

         //}

         //return prichtextdata->hit_test(point);

         auto pitem = ::place(new ::item(e_element_item));

         auto prichtextdata = get_rich_text_data();

         pitem->m_item.m_iItem = _hit_test(point);

         return pitem;

      }


      //void edit_impl::get_text(string & str)
      //{

      //   auto prichtextdata = get_rich_text_data();

      //   prichtextdata->get_text(str);

      //}


      void edit_impl::_001GetLayoutText(string & str) const
      {

         ::user::rich_text::edit::_001GetLayoutText(str);

      }


      void edit_impl::draw_control_background(::draw2d::graphics_pointer & pgraphics)
      {

         //return;

         //::aura::draw_context* pdrawcontext = pgraphics->::aura::simple_chain < ::aura::draw_context >::get_last();

         //::rectangle_i32 rectangleX;

         //if (pdrawcontext != nullptr)
         //{

         //   rectangleX = pdrawcontext->m_rectangleX;

         //}
         //else
         //{

         //   this->rectangle(rectangleX);

         //}

         //if (_001IsBackgroundBypass())
         //{

         //}
         //else if (_001IsTranslucent())
         //{

         //   pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

         //   ::color::color crBackground = _001GetColor(::user::color_background, argb(128, 255, 255, 255));

         //   //if (color32_u8_red(crBackground) != 255)
         //   //{

         //   //   informationf("no full red");

         //   //}

         //   //crBackground = argb(255, 100, 200, 255);

         //   if (crBackground != 0)
         //   {

         //      pgraphics->fill_rectangle(rectangleX, crBackground);

         //   }

         //}
         //else
         //{

         //   pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

         //   ::color::color crBackground = _001GetColor(m_ecolorBackground, argb(200, 255, 255, 255));

         //   //if (color32_u8_red(crBackground) != 255)
         //   //{

         //   //   informationf("no full red");

         //   //}

         //   //crBackground = argb(255, 255, 200, 100);

         //   pgraphics->fill_rectangle(rectangleX, crBackground);

         //}

         //::user::rich_text::edit::draw_control_background(pgraphics);

      }


      void edit_impl::_001OnNcPostDraw(::draw2d::graphics_pointer & pgraphics)
      {

         ::user::rich_text::edit::_001OnNcPostDraw(pgraphics);

      }


      void edit_impl::_001CallOnDraw(::draw2d::graphics_pointer & pgraphics)
      {

         ::user::rich_text::edit::_001CallOnDraw(pgraphics);

      }


      ::point_f64 edit_impl::get_point_transform()
      {

         // auto pointD = m_ppictureimpl->m_rectangleDrawing.center();

         auto pointD = ::point_f64(m_ppictureimpl->m_rectangleDrawing.size() / 2.0);

         return pointD;

      }


      void edit_impl::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
      {

         //return;

         //return;

       //  if (!is_picture_enabled())
       //  {

       /////     picture::_001OnDraw(pgraphics);

       //  }
       //  else
       //  {

         //auto rectangleX = this->rectangle();

         //pgraphics->fill_rectangle(rectangleX, argb(40, 255, 255, 255));

         //draw_impl(pgraphics);
         ::user::rich_text::edit::_001OnDraw(pgraphics);
         // 
         //
           //       }

      }


      void edit_impl::draw_impl(::draw2d::graphics_pointer & pgraphics)
      {

         _synchronous_lock synchronouslock(this->synchronization());

         //pgraphics->offset_origin(m_pointScroll.x(), m_pointScroll.y());

         //::rectangle_i32 r(25, 25, 150, 150);

         //pgraphics->fill_solid_rectangle(r, ::color::red);

         at_end_of_scope
         {

            m_bShouldDrawOverride = false;

         };

         m_bShouldDrawOverride = true;

         _000OnDraw(pgraphics);

      }


      void edit_impl::_000DrawImpl(::draw2d::graphics_pointer & pgraphics)
      {

         if (m_ppictureimpl)
         {

            return;

         }

         return _000OnDraw(pgraphics);

         //_synchronous_lock synchronouslock(this->synchronization());

         ////pgraphics->offset_origin(m_pointScroll.x(), m_pointScroll.y());

         //::rectangle_i32 r(25, 25, 150, 150);

         //pgraphics->fill_solid_rectangle(r, ::color::red);

         //at_end_of_scope
         //{

         //   m_bShouldDrawOverride = false;

         //};

         //m_bShouldDrawOverride = true;

         //_000OnDraw(pgraphics);

      }


      bool edit_impl::set_text_editable(bool bEditable)
      {

         m_bEditable2 = bEditable;

         if (bEditable)
         {

            if(is_text_editable())
            {

               //if (!is_window_visible())
               //{

               //   display();

               //}

               auto pformattool = get_format_tool(true);

               ::user::rich_text::selection * pselection = this;

               //if (!ptool->is_window_visible() || !ptool->is_showing_for_ui(this))
               {

                  on_selection_change(pformattool->m_pformat);

                  pformattool->show_for_ui(this, pselection);

               }

               SetTimer(250, 500_ms, nullptr); // Caret

            }

         }
         else
         {

            //if (is_window_visible())
            //{

            //   hide();

            //}

            auto pformattool = get_format_tool(false);

            if (pformattool != nullptr && pformattool->is_showing_for_ui(this))
            {

               pformattool->hide();

            }

            if (has_keyboard_focus())
            {

               keyboard_set_focus_next();

            }

         }


         return m_bEditable2;

      }


      bool edit_impl::is_text_editable()
      {

         return is_window_enabled() && m_bEditable2;

      }


      bool edit_impl::is_text_editor()
      {

         return true;

      }


      bool edit_impl::_001IsPointInside(const ::point_i32 & pointParam)
      {

         if (is_picture_enabled())
         {

            point_f64 point(pointParam);

            screen_to_client()(point);

            ::rectangle_i32 rWindow;

            window_rectangle(rWindow);

            rectangle_f64 rectangleWindow;

            rectangleWindow = rWindow;

            get_parent()->screen_to_client()(rectangleWindow);

            //rectangleWindow = rectangleWindow;

            point += rectangleWindow.top_left();

            _rtransform_sequence(point);

            point -= rectangleWindow.top_left();

            auto rectangleX = this->rectangle();

            return rectangleX.contains(::point_i32(point));

         }

         return ::user::interaction::_001IsPointInside(pointParam);

      }


      bool edit_impl::_001GetItemText(string & str, ::collection::index iItem)
      {

         return false;

      }


      void edit_impl::on_layout(::draw2d::graphics_pointer & pgraphics)
      {

         do_layout(pgraphics);

      }


      void edit_impl::handle(::topic * ptopic, ::context * pcontext)
      {

         if (ptopic->m_atom == ::id_after_change_cur_sel)
         {

            auto pformattool = get_format_tool(false);

            if (ptopic->user_interaction() == pformattool)
            {

               auto prichtextdata = get_rich_text_data();

               _synchronous_lock synchronouslock(prichtextdata->synchronization());

               if (pformattool->m_eattribute & e_attribute_align)
               {

                  box_align(prichtextdata->m_spana, find_span(prichtextdata->m_spana, m_iSelEnd), pformattool->m_pformat->m_ealign);

               }

               _001SetSelFontFormat(pformattool->m_pformat, pformattool->m_eattribute);

               pformattool->m_eattribute.clear();

               set_need_layout();

               set_need_redraw();

               post_redraw();

               //set_keyboard_focus();

               //ptopic->Ret();

               //return;

            }

         }
         else if (ptopic->m_atom == ID_INCOMING_DOCUMENT)
         {

            auto puserdocument = ptopic->m_pparticle.cast < ::user::document >();

            puserdocument->m_strSaveFileExtension = "rtf";

            auto prichtextdata = get_rich_text_data();

            if (prichtextdata->is_new_data())
            {
               //if (!estatus)
   //{

   //   return estatus;

   //}

               m_bComposing = false;

               //estatus = 

               //prichtextdata->initialize_data(pdocument);

               //if (!estatus)
               //{

               //   return estatus;

               //}

               m_bPendingSelectionChange = false;

               m_bEditable2 = true;

               m_bKeyPressed = false;

               m_bSelDrag = false;

               m_bClickThrough = false;

               //return estatus;

            }

         }


         return ::user::interaction::handle(ptopic, pcontext);

      }


      ::pointer<format_tool>edit_impl::get_format_tool(bool bCreate)
      {

         auto pframe = top_level_frame();

         if (::is_null(pframe))
         {

            return nullptr;

         }

         auto pformattool = pframe->tool_window(::user::e_tool_font, bCreate);

         return pformattool;

      }


      bool edit_impl::keyboard_focus_is_focusable()
      {

         return is_window_visible() && is_text_editable();

      }


      void edit_impl::keyboard_focus_OnChar(::message::message * pmessage)
      {

         if (!is_text_editable())
         {

            return;

         }

         on_message_character(pmessage);

      }


      void edit_impl::on_message_key_down(::message::message * pmessage)
      {

         //_synchronous_lock synchronouslock(this->synchronization());

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

               str = get_selection_text();

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

                  string str;

                  auto pcopydesk = copydesk();

                  pcopydesk->get_plain_text(str);

                  _001InsertText(str);

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

               str = get_selection_text();

               auto pcopydesk = copydesk();

               pcopydesk->set_plain_text(str);

               if (is_window_enabled())
               {

                  _001OnDeleteText();

               }

               return;

            }

         }

         m_pkeymessageLast = pkey;

         m_bKeyPressed = true;

         key_to_char(m_pkeymessageLast);

         pkey->m_bRet = true;

      }


      void edit_impl::on_message_key_up(::message::message * pmessage)
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
         m_bKeyPressed = false;
      }


      void edit_impl::_001OnTimer(::timer * ptimer)
      {

         ::user::interaction::_001OnTimer(ptimer);

         if (ptimer->m_uEvent >= 100 && ptimer->m_uEvent <= 200)
         {
            if (has_keyboard_focus())
            {

               //_001OnKeyboardFocusTimer(ptimer->m_uEvent - 100);

            }
         }
         else if (ptimer->m_uEvent == 500 || ptimer->m_uEvent == 501)
         {

            if (ptimer->m_uEvent == 500)
            {

               KillTimer(500);

               SetTimer(501, 300_ms, nullptr);

            }

            key_to_char(m_pkeymessageLast);

         }
         else if (ptimer->m_uEvent == e_timer_redraw)
         {

            // Caret

            //if (is_text_editable() && is_window_visible() && has_keyboard_focus())
            {

               //xxx set_need_redraw();

               //xxx post_redraw();

            }

         }

      }


      void edit_impl::key_to_char(::message::key * pkey)
      {

         ::message::key & key = *pkey;

         auto psession = get_session();

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

         bool bShift = psession->is_key_pressed(::user::e_key_shift);

         if (key.m_nChar < 256 && character_isalpha((char)key.m_nChar))
         {

            if (bShift)
            {

               key.m_nChar = character_toupper((char)key.m_nChar);

            }
            else
            {

               key.m_nChar = character_tolower((char)key.m_nChar);

            }

         }

         on_message_character(&key);

      }


      void edit_impl::_001OnDeleteText()
      {

         on_reset_focus_start_tick();

         {

            auto prichtextdata = get_rich_text_data();

            _synchronous_lock synchronouslock(prichtextdata->synchronization());

            strsize i1 = get_sel_beg();

            strsize i2 = get_sel_end();

            if (i1 != i2)
            {

               prichtextdata->_001Delete(i1, i2);

               m_iSelBeg = m_iSelEnd = i1;

               //::collection::index i = find_span(prichtextdata->m_spana, i1);

               on_after_change(::id_after_change_text);

               set_need_redraw();

            }
            else if (i1 >= 0 && i1 < _001GetLayoutTextLength())
            {

               string str;

               _001GetLayoutText(str);

               strsize iIncLen = ::str::utf8_inc_len(&str[i1]);

               prichtextdata->_001Delete(i1, i1 + iIncLen);

               m_iSelBeg = m_iSelEnd = i1;

               //::collection::index i = find_span(prichtextdata->m_spana, i1);

               on_after_change(::id_after_change_text);

               set_need_redraw();

            }

         }


      }


      void edit_impl::on_message_character(::message::message * pmessage)
      {

         auto pkey = pmessage->m_union.m_pkey;

         string strChar;

         auto psession = get_session();

         if (pkey->m_ekey == ::user::e_key_s)
         {

            if (psession->is_key_pressed(::user::e_key_control))
            {

               return;

            }

         }
         else if (pkey->m_ekey == ::user::e_key_a)
         {

            if (psession->is_key_pressed(::user::e_key_control))
            {

               set_text_selection(0, _001GetLayoutTextLength(), e_source_user);

               return;

            }

         }
         else if (pkey->m_ekey == ::user::e_key_z)
         {

            if (psession->is_key_pressed(::user::e_key_control))
            {

               if (is_window_enabled())
               {

                  //Undo();

               }

               return;

            }

         }
         else if (pkey->m_ekey == ::user::e_key_y)
         {

            if (psession->is_key_pressed(::user::e_key_control))
            {

               if (is_window_enabled())
               {

                  //Redo();

               }

               return;

            }

         }
         else if (psession->is_key_pressed(::user::e_key_control))
         {

            if (pkey->m_ekey == ::user::e_key_home)
            {

            }
            else if (pkey->m_ekey == ::user::e_key_end)
            {

            }
            else
            {

               return;
            }

         }

         {

            _synchronous_lock synchronouslock(this->synchronization());

            bool bControl = psession->is_key_pressed(::user::e_key_control);

            bool bShift = psession->is_key_pressed(::user::e_key_shift);

            if (pkey->m_ekey == ::user::e_key_page_up)
            {

               //on_reset_focus_start_tick();

               //i32 x;
               //index iLine = SelToLineX(m_iSelEnd, x);

               //::rectangle_i32 rectangleX;

               //GetFocusRect(rectangleX);

               //iLine -= rectangleX.height() / m_iLineHeight;

               //if (iLine < 0)
               //{

               //   iLine = 0;

               //}

               //m_iSelEnd = LineXToSel(iLine, m_iColumnX);

               //if (!bShift)
               //{

               //   m_iSelBeg = m_iSelEnd;

               //}

               //_001EnsureVisibleLine(iLine);

            }
            else if (pkey->m_ekey == ::user::e_key_page_down)
            {

               //on_reset_focus_start_tick();

               //i32 x;

               //index iLine = SelToLineX(m_iSelEnd, x);

               //::rectangle_i32 rectangleX;

               //GetFocusRect(rectangleX);

               //iLine += rectangleX.height() / m_iLineHeight;

               //if (iLine >= m_iaLineStart.get_size())
               //{

               //   iLine = m_iaLineStart.get_upper_bound();

               //}

               //m_iSelEnd = LineXToSel(iLine, m_iColumnX);

               //if (!bShift)
               //{

               //   m_iSelBeg = m_iSelEnd;

               //}

               //_001EnsureVisibleLine(iLine);

            }
            else if (pkey->m_ekey == ::user::e_key_back)
            {

               if (is_window_enabled())
               {

                  on_reset_focus_start_tick();

                  auto prichtextdata = get_rich_text_data();

                  {

                     _synchronous_lock synchronouslock(prichtextdata->synchronization());

                     strsize i1 = get_sel_beg();

                     strsize i2 = get_sel_end();

                     if (i1 > 0)
                     {

                        if (i1 != i2)
                        {

                           prichtextdata->_001Delete(i1, i2);

                           m_iSelBeg = m_iSelEnd = i1;

                           on_after_change(::id_after_change_text);

                           set_need_redraw();

                        }
                        else
                        {

                           string str;

                           _001GetLayoutText(str);

                           strsize iDecLen = ::str::utf8_dec_len(str, &str[i1]);

                           prichtextdata->_001Delete(i1, i1 - iDecLen);

                           m_iSelBeg = m_iSelEnd = i1 - iDecLen;

                           on_after_change(::id_after_change_text);

                           set_need_redraw();

                        }

                     }

                  }

               }

            }
            else if (pkey->m_ekey == ::user::e_key_delete)
            {

               if (is_window_enabled())
               {

                  _001OnDeleteText();

               }

               return;

            }
            else if (pkey->m_ekey == ::user::e_key_up)
            {

               on_reset_focus_start_tick();

               auto prichtextdata = get_rich_text_data();

               _synchronous_lock synchronouslock(prichtextdata->synchronization());

               double x;

               auto plinea = m_plinea;

               ::collection::index iLine = line_caret_x(*plinea, m_iSelEnd, x);

               iLine--;

               if (iLine >= 0)
               {

                  m_iSelEnd = _hit_test_line_x(iLine, x);

                  if (!bShift)
                  {

                     m_iSelBeg = m_iSelEnd;

                  }

                  //_001EnsureVisibleLine(iLine);

                  internal_update_sel_char();

               }

               pkey->m_bRet = true;

            }
            else if (pkey->m_ekey == ::user::e_key_down)
            {

               on_reset_focus_start_tick();

               auto prichtextdata = get_rich_text_data();

               _synchronous_lock synchronouslock(prichtextdata->synchronization());

               double x;

               auto plinea = m_plinea;

               ::collection::index iLine = line_caret_x(*plinea, m_iSelEnd, x);

               iLine++;

               if (iLine < plinea->get_count())
               {

                  m_iSelEnd = _hit_test_line_x(iLine, x);

                  if (!bShift)
                  {

                     m_iSelBeg = m_iSelEnd;

                  }


                  //_001EnsureVisibleLine(iLine);

                  internal_update_sel_char();

               }

            }
            else if (pkey->m_ekey == ::user::e_key_right)
            {

               on_reset_focus_start_tick();

               auto prichtextdata = get_rich_text_data();

               if (!bShift && m_iSelBeg > m_iSelEnd)
               {

                  _synchronous_lock synchronouslock(prichtextdata->synchronization());

                  m_iSelEnd = m_iSelBeg;

                  internal_update_sel_char();

               }
               else if (!bShift && m_iSelEnd > m_iSelBeg)
               {

                  auto prichtextdata = get_rich_text_data();

                  _synchronous_lock synchronouslock(prichtextdata->synchronization());

                  m_iSelBeg = m_iSelEnd;

                  internal_update_sel_char();

               }
               else
               {

                  auto prichtextdata = get_rich_text_data();

                  _synchronous_lock synchronouslock(prichtextdata->synchronization());

                  if (m_iSelEnd < _001GetLayoutTextLength())
                  {

                     string strText;

                     _001GetLayoutText(strText);

                     const char * psz = strText.c_str();

                     const char * end = &psz[m_iSelEnd];

                     const char * inc = unicode_next(end);

                     m_iSelEnd += inc - end;

                     if (!bShift)
                     {

                        m_iSelBeg = m_iSelEnd;

                     }

                     internal_update_sel_char();

                  }

               }

            }
            else if (pkey->m_ekey == ::user::e_key_left)
            {

               on_reset_focus_start_tick();

               auto prichtextdata = get_rich_text_data();

               if (!bShift && m_iSelBeg < m_iSelEnd)
               {

                  _synchronous_lock synchronouslock(prichtextdata->synchronization());

                  m_iSelEnd = m_iSelBeg;

                  internal_update_sel_char();

               }
               else if (!bShift && m_iSelEnd < m_iSelBeg)
               {

                  auto prichtextdata = get_rich_text_data();

                  _synchronous_lock synchronouslock(prichtextdata->synchronization());

                  m_iSelBeg = m_iSelEnd;

                  internal_update_sel_char();

               }
               else if (m_iSelEnd > 0)
               {

                  auto prichtextdata = get_rich_text_data();

                  _synchronous_lock synchronouslock(prichtextdata->synchronization());

                  string strText;

                  _001GetLayoutText(strText);

                  const ::ansi_character * psz = strText.c_str();

                  const char * end = &psz[m_iSelEnd];

                  const char * dec = unicode_prior(end, psz);

                  m_iSelEnd -= end - dec;

                  if (!bShift)
                  {

                     m_iSelBeg = m_iSelEnd;

                  }

                  internal_update_sel_char();

               }

            }
            else if (pkey->m_ekey == ::user::e_key_home)
            {

               on_reset_focus_start_tick();

               auto prichtextdata = get_rich_text_data();

               _synchronous_lock synchronouslock(prichtextdata->synchronization());

               if (bControl)
               {

                  m_iSelEnd = 0;

                  //   _001EnsureVisibleLine(0);

               }
               else
               {

                  ::collection::index iLine = SelToLine(m_iSelEnd);

                  m_iSelEnd = LineColumnToSel(iLine, 0);

               }

               if (!bShift)
               {

                  m_iSelBeg = m_iSelEnd;

               }

               internal_update_sel_char();

            }
            else if (pkey->m_ekey == ::user::e_key_end)
            {

               on_reset_focus_start_tick();

               auto prichtextdata = get_rich_text_data();

               _synchronous_lock synchronouslock(prichtextdata->synchronization());

               if (bControl)
               {

                  m_iSelEnd = _001GetLayoutTextLength();

                  //   _001EnsureVisibleLine(iLine);

               }
               else
               {

                  ::collection::index iLine = SelToLine(m_iSelEnd);

                  m_iSelEnd = LineColumnToSel(iLine, -1);

               }

               if (!bShift)
               {

                  m_iSelBeg = m_iSelEnd;

               }

               internal_update_sel_char();

            }
            else if (pkey->m_ekey == ::user::e_key_escape)
            {

            }
            else if (pkey->m_ekey == ::user::e_key_return)
            {

               //                if(m_bMultiLine)
               {

                  insert_text("\n", true, e_source_user);

               }

            }
            else if (is_window_enabled())
            {

#if defined(WINDOWS_DESKTOP) || defined(LINUX) || defined(MACOS)

               return;

#else

               on_reset_focus_start_tick();

               string str;

               char ch = 0;

               if (pkey->m_ekey == ::user::e_key_tab)
               {

                  str = "   ";

               }
               else if (pkey->m_ekey == ::user::e_key_refer_to_text_member)
               {

                  str = pkey->m_strText;

               }
               else
               {

                  ch = (char)pkey->m_nChar;

                  if (ch == '\r')
                  {

                     ch = '\n';

                  }

                  i32 iChar = (i32)pkey->m_nChar;

                  if (iChar == '\r')
                  {

                     iChar = '\n';

                  }

                  if (bShift)
                  {

                     iChar |= I32_MINIMUM;

                  }

                  //i32 iCode = pkey->m_nFlags & 0xff;

                  //if (bShift)
                  //{

                  //   iCode |= I32_MINIMUM;

                  //}

                  //str = psession->keyboard().process_key(pkey);
                                       //str = psession->keyboard().process_key(pkey);
                  throw ::exception(todo, "keyboard");


               }

               //auto prichtextdata = get_rich_text_data();

               //prichtextdata->_001InsertText(str);
               
               _001InsertText(str);


#endif

            }


         }


      }


      void edit_impl::on_after_change(const ::atom & atom)
      {

         auto prichtextdata = get_rich_text_data();

         prichtextdata->optimize_data();

         auto ptopic = create_topic(atom);

         //topic.m_atom = eevent;

         //topic.m_atom = m_atom;

         ptopic->m_puserelement = this;

         route(ptopic);

         set_need_layout();

         set_need_redraw();

         post_redraw();

      }


      //strsize edit_impl::get_text_length()
      //{

      //   auto prichtextdata = get_rich_text_data();

      //   return prichtextdata->get_text_length();

      //}


      void edit_impl::get_text_selection(strsize & iBeg, strsize & iEnd) const
      {

         //auto prichtextdata = get_rich_text_data();

         iBeg = m_iSelBeg;

         iEnd = m_iSelEnd;

      }


      void edit_impl::_001GetSelLineText(string & strText)
      {

         //         double x;

         auto prichtextdata = get_rich_text_data();

         ::collection::index iLine = SelToLine(m_iSelBeg);

         ::collection::index iLineEnd = SelToLine(m_iSelEnd);

         if (iLine != iLineEnd)
         {

            return;

         }

         ::collection::index iBeg = LineColumnToSel(iLine, 0);

         ::collection::index iEnd = LineColumnToSel(iLine, -1);

         ::string strFullText = prichtextdata->as_text();

         strText = strFullText(iBeg, iEnd);

      }


      void edit_impl::update_placement()
      {

         if (m_ppictureimpl == nullptr)
         {

            return;

         }

         place(m_ppictureimpl->m_rectangle);

      }


      //document * edit_impl::get_document()
      //{

      //   return m_pdocument.cast < document >();

      //}


      //void edit_impl::write(::binary_stream & stream) const
      //{

      //   ::user::picture::write(stream);

      //   prichtextdata->write(stream);

      //   ::rectangle_i32 rectangleWindow;

      //   ((edit_impl *)this)->window_rectangle(rectangleWindow);

      //   if (get_parent() != nullptr)
      //   {

      //      get_parent()->screen_to_client()(rectangleWindow);

      //   }

      //   stream << rectangleWindow;

      //   //return stream;

      //}


      //void edit_impl::read(::binary_stream & stream)
      //{

      //   ::user::picture::read(stream);

      //   prichtextdata->read(stream);

      //   ::rectangle_i32 rectangleWindow;

      //   stream >> rectangleWindow;

      //   place(rectangleWindow);

      //   display(e_display_normal);

      //   set_need_layout();

      //   //return stream;

      //}


      void edit_impl::get_text_composition_area(::rectangle_i32 & r)
      {

      }


      void edit_impl::on_text_composition(string str)
      {

         if (!m_bComposing)
         {

            m_bComposing = true;

         }
         else
         {

            edit_undo();

         }

         _001InsertText(str);

      }


      void edit_impl::on_text_composition_done()
      {

      }


      bool edit_impl::edit_undo()
      {

         return false;


      }


      void edit_impl::read_from_stream(::binary_stream & binarystream)
      {

         ::user::picture::read_from_stream(binarystream);

         auto prichtextdata = get_rich_text_data();

         ::string strRtf;

         binarystream >> strRtf;

         auto pmemoryfile = create_memory_file(strRtf);

         ::binary_stream binarystreamRtf(pmemoryfile);

         prichtextdata->read_from_stream(binarystreamRtf);

      }


      void edit_impl::write_to_stream(::binary_stream & binarystream)
      {

         ::user::picture::write_to_stream(binarystream);

         //m_ppictureimpl->write_to_stream(binarystream);

         auto prichtextdata = get_rich_text_data();

         auto pmemoryfile = create_memory_file();

         ::binary_stream binarystreamRtf(pmemoryfile);

         prichtextdata->write_to_stream(binarystreamRtf);

         binarystream << pmemoryfile->as_string();

      }


      ::user::rich_text::data * edit_impl::get_rich_text_data()
      {

         return ::user::rich_text::edit::get_rich_text_data();

      }


   } // namespace rich_text


} // namespace user


