#include "framework.h"
#include "core/user/userex/_userex.h"


namespace user
{


   color_combo_box::color_combo_box() 
   {

      m_pview = nullptr;
      m_pdocument = nullptr;
      m_bMouseDown = false;

   }


   color_combo_box::~color_combo_box()
   {

   }


   void color_combo_box::install_message_routing(::channel * psender)
   {

      ::user::interaction::install_message_routing(psender);

      MESSAGE_LINK(e_message_create, psender, this, &::user::color_combo_box::on_message_create);
      MESSAGE_LINK(e_message_left_button_down, psender, this, &::user::color_combo_box::on_message_left_button_down);
      MESSAGE_LINK(e_message_left_button_up, psender, this, &::user::color_combo_box::on_message_left_button_up);
      MESSAGE_LINK(e_message_mouse_move, psender, this, &::user::color_combo_box::_001OnMouseMove);
      MESSAGE_LINK(e_message_mouse_leave, psender, this, &::user::color_combo_box::_001OnMouseLeave);
      MESSAGE_LINK(e_message_show_window, psender, this, &::user::color_combo_box::_001OnShowWindow);

   }


   void color_combo_box::on_message_create(::message::message * pmessage)
   {

      __pointer(::message::create) pcreate(pmessage);

      pcreate->previous();

      //__throw(todo("style"));

      //::rectangle_f64 r(2, 2, 2, 2);

      //create_rect(::user::rect_edit_padding, r, ::draw2d::unit_pixel);


   }


   void color_combo_box::on_message_left_button_down(::message::message * pmessage)
   {

      __pointer(::message::mouse) pmouse(pmessage);

      m_bMouseDown = true;

      set_mouse_capture();

      pmouse->m_bRet = true;

   }


   void color_combo_box::on_message_left_button_up(::message::message * pmessage)
   {

      __pointer(::message::mouse) pmouse(pmessage);

      auto psession = Session;

      auto puser = psession->user();

      auto pwindowing = puser->windowing();

      pwindowing->release_mouse_capture();

      if (m_bMouseDown)
      {

         m_bMouseDown = false;

         if(frame() != nullptr && frame()->is_window_visible())
         {

            frame()->display(e_display_none);

         }
         else
         {


            bool bNew = m_pdocument == nullptr;

            if(bNew)
            {

               auto puser = User;

               puser->will_use_view_hint(COLORSEL_IMPACT);

               m_pdocument = puser->m_mapimpactsystem[COLORSEL_IMPACT]->open_document_file(get_context_application(), ::e_type_null, __visible(false));

               m_pview = m_pdocument->get_typed_view < ::userex::color_view >();

               m_pview->m_bCompact = true;

               auto psession = Session;

               psession->set_bound_ui(COLORSEL_IMPACT, this);

               m_pframewindow = m_pview->top_level_frame()->cast < ::simple_frame_window >();

               m_pframewindow->set_owner(this);

               m_pframewindow->m_ebuttonaHide.add(::experience::e_button_dock);
               m_pframewindow->m_ebuttonaHide.add(::experience::e_button_down);
               m_pframewindow->m_ebuttonaHide.add(::experience::e_button_up);
               m_pframewindow->m_ebuttonaHide.add(::experience::e_button_minimize);

            }

            m_pview->m_hls = m_hls;

            auto pframe = frame();

            if(bNew)
            {

               ::rectangle_i32 rectWindow;

               get_window_rect(rectWindow);

               pframe->m_sizeMinimum.cx = 300;

               pframe->m_sizeMinimum.cy = 150;

               pframe->order(e_zorder_top_most);
               
               pframe->set_dim(rectWindow.left, rectWindow.bottom, 400, 200);
               
               pframe->display();

            }
            else
            {

               pframe->order(e_zorder_top_most);

               pframe->display();

            }

         }

         pmouse->m_bRet = true;

      }


   }


   void color_combo_box::on_control_event(::user::control_event * pevent)
   {

      if(pevent->m_puie == m_pview)
      {

         pevent->m_puie = this;

         pevent->m_id = m_id;

         m_hls = m_pview->m_hls;

      }

      ::user::interaction::on_control_event(pevent);

   }


   void color_combo_box::_001OnMouseMove(::message::message * pmessage)
   {

      //__pointer(::message::mouse) pmouse(pmessage);

      UNREFERENCED_PARAMETER(pmessage);

      if (!m_itemHover.is_set())
      {

         m_itemHover = ::user::e_element_client;

         set_need_redraw();

      }

      track_mouse_leave();

   }


   void color_combo_box::_001OnMouseLeave(::message::message * pmessage)
   {

      //__pointer(::message::mouse) pmouse(pmessage);

      UNREFERENCED_PARAMETER(pmessage);

      m_itemHover = ::user::e_element_none;

      set_need_redraw();

   }


   void color_combo_box::_001OnShowWindow(::message::message * pmessage)
   {

      __pointer(::message::show_window) pshowwindow(pmessage);

      if(!pshowwindow->m_bShow)
      {

         auto pframe = frame();

         if(pframe && pframe->is_window_visible())
         {

            pframe->display(e_display_none);

         }

      }

   }


   void color_combo_box::on_layout(::draw2d::graphics_pointer & pgraphics)
   {


   }


   void color_combo_box::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::draw2d::brush_pointer br(e_create);

      //::user::e_::color::color colorDropDown = color_button_background_disabled;

      auto estate = get_state();

      auto pstyle = get_style(pgraphics);

      //if (m_pdrawcontext != nullptr)
      //{

      //   if (m_pdrawcontext->is_control_selected())
      //   {

      //      if (m_pdrawcontext->is_control_hover())
      //      {

      //         colorDropDown = color_action_hover_border_color;

      //      }
      //      else
      //      {

      //         colorDropDown = color_action_hover_border_color;

      //      }

      //   }
      //   else
      //   {

      //      if (m_pdrawcontext->is_control_hover())
      //      {

      //         colorDropDown = color_action_hover_border_color;

      //      }
      //      else
      //      {

      //         colorDropDown = color_button_background_disabled;

      //      }

      //   }

      //}
      //else if (!is_window_enabled())
      //{

      //   colorDropDown = color_button_background_disabled;

      //}
      //else
      //{

      //   if (psession->get_focus_ui() == this)
      //   {

      //      if (m_itemHover)
      //      {

      //         colorDropDown = color_action_hover_border_color;

      //      }
      //      else
      //      {

      //         colorDropDown = color_action_hover_border_color;

      //      }

      //   }
      //   else
      //   {

      //      if (m_itemHover)
      //      {

      //         colorDropDown = color_action_hover_border_color;

      //      }
      //      else
      //      {

      //         colorDropDown = color_button_background;

      //      }

      //   }

      //}

      {

         ::color::color color(m_hls);

         color.alpha = 255;

         ::draw2d::brush_pointer pbrush(e_create);

         if (!is_window_enabled())
         {

            color.hls_rate(0.0, 0.4, -0.7);

         }

         pbrush->create_solid(color);

         ::rectangle_i32 rEdit;

         get_element_rect(rEdit, e_element_combo_edit);

         {

            auto colorBackground = get_color(pstyle, ::user::e_element_background, estate);

            if (!colorBackground.is_ok())
            {

               colorBackground = argb(210, 230, 230, 230);

            }

            colorBackground.m_result.hls_rate(0.0, 0.6, -0.3);

            pgraphics->fill_rectangle(rEdit, colorBackground);

         }

         {


            auto color2 = get_color(pstyle, estate);

            if (!color2.is_ok())
            {

               color2 = argb(210, 230, 230, 230);

            }

            color2.m_result.hls_rate(0.0, 0.3, 0.5);

            pgraphics->draw_rectangle(rEdit, color2);

         }

         auto rectPadding = get_padding(pstyle);

         rEdit.deflate(rectPadding.m_result);

         pgraphics->fill_rectangle(rEdit, color.get_rgba());

      }

      ::rectangle_i32 rectDropDown;

      get_element_rect(rectDropDown, e_element_drop_down);

      ::rectangle_i32 rectDropIn(rectDropDown);

      ::color::color color(get_color(pstyle, estate));

      if (!color)
      {

         color = argb(210, 230, 230, 230);

      }

      color.hls_rate(0.0, 0.5, 0.1);

      br->create_solid(color);

      pgraphics->set(br);

      pgraphics->fill_rectangle(rectDropIn);

      ::draw2d::path_pointer path(e_create);

      point_f64_array pointa;

      get_simple_drop_down_open_arrow_polygon(pointa);

      br->create_solid(argb(210, 0, 0, 0));

      pgraphics->set(br);

      pgraphics->fill_polygon(pointa);

   }


} //  namespace user



