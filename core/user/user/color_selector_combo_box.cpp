#include "framework.h"
#include "color_selector_combo_box.h"
#include "color_selector_popup.h"
#include "acme/constant/message.h"
#include "acme/handler/item.h"
#include "acme/handler/topic.h"
#include "acme/platform/system.h"
#include "aura/graphics/draw2d/brush.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/draw2d/path.h"
#include "aura/message/user.h"
#include "aura/user/user/frame_interaction.h"
#include "berg/user/user/document.h"
#include "berg/user/user/impact_system.h"
#include "berg/user/simple/frame_window.h"
#include "core/platform/application.h"
#include "core/platform/session.h"
#include "core/user/user/user.h"
#include "core/user/user/color_selector_impact.h"


namespace user
{


   color_combo_box::color_combo_box() 
   {

      //m_pimpact = nullptr;
      //m_pdocument = nullptr;
      m_bMouseDown = false;

   }


   color_combo_box::~color_combo_box()
   {

   }


   // ::core::application* color_combo_box::get_app()
   // {
   //
   //    auto papplication = application();
   //
   //    return ::is_set(papplication) ? papplication : nullptr;
   //
   // }
   //
   //
   // ::core::session* color_combo_box::get_session()
   // {
   //
   //    auto pacmesession = session();
   //
   //    return ::is_set(pacmesession) ? pacmesession : nullptr;
   //
   // }
   //
   //
   // ::core::system* color_combo_box::get_system()
   // {
   //
   //    auto pacmesystem = system();
   //
   //    return ::is_set(pacmesystem) ? pacmesystem : nullptr;
   //
   // }

   void color_combo_box::install_message_routing(::channel * psender)
   {

      ::user::interaction::install_message_routing(psender);

      MESSAGE_LINK(::user::e_message_create, psender, this, &::user::color_combo_box::on_message_create);
      MESSAGE_LINK(::user::e_message_left_button_down, psender, this, &::user::color_combo_box::on_message_left_button_down);
      MESSAGE_LINK(::user::e_message_left_button_up, psender, this, &::user::color_combo_box::on_message_left_button_up);
      MESSAGE_LINK(::user::e_message_mouse_move, psender, this, &::user::color_combo_box::on_message_mouse_move);
      MESSAGE_LINK(::user::e_message_mouse_leave, psender, this, &::user::color_combo_box::on_message_mouse_leave);
      MESSAGE_LINK(::user::e_message_show_window, psender, this, &::user::color_combo_box::on_message_show_window);

   }


   void color_combo_box::on_message_create(::message::message * pmessage)
   {

      ::pointer<::message::create>pcreate(pmessage);

      pcreate->previous();

      //throw ::exception(todo("style"));

      //::double_rectangle r(2, 2, 2, 2);

      //create_rect(::user::rect_edit_padding, r, ::draw2d::e_unit_pixel);


   }


   void color_combo_box::on_message_left_button_down(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      m_bMouseDown = true;

      set_mouse_capture();

      pmouse->m_bRet = true;

   }


   void color_combo_box::on_message_left_button_up(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      defer_release_mouse_capture();

      if (m_bMouseDown)
      {

         m_bMouseDown = false;

         if(frame() != nullptr && frame()->is_window_visible())
         {

            frame()->display(e_display_none);

         }
         else
         {



         }

         pmouse->m_bRet = true;

      }


   }


   void color_combo_box::handle(::topic * ptopic, ::handler_context * phandlercontext)
   {

      if(ptopic->m_puserelement == m_pcolorselectorpopup)
      {

         ptopic->m_puserelement = this;

         //ptopic->user_interaction_id() = id();

         m_hls = m_pcolorselectorpopup->m_hls;

      }

      ::user::interaction::handle(ptopic, phandlercontext);

   }


   void color_combo_box::on_message_mouse_move(::message::message * pmessage)
   {

      //auto pmouse = pmessage->m_union.m_pmouse;

      __UNREFERENCED_PARAMETER(pmessage);

      if (!::is_set(m_pitemHover))
      {

         m_pitemHover = øallocate ::item(::e_element_client);

         set_need_redraw();

      }

      track_mouse_leave();

   }


   void color_combo_box::on_message_mouse_leave(::message::message * pmessage)
   {

      //auto pmouse = pmessage->m_union.m_pmouse;

      __UNREFERENCED_PARAMETER(pmessage);

      m_pitemHover = nullptr;

      set_need_redraw();

   }


   void color_combo_box::on_message_show_window(::message::message * pmessage)
   {

      ::pointer<::message::show_window>pshowwindow(pmessage);

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

      auto pbrush = øcreate < ::draw2d::brush > ();

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

      //      if (m_pitemHover)
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

      //      if (m_pitemHover)
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

         color.set_opaque();

         ::draw2d::brush_pointer pbrush(e_create, this);

         if (!is_window_enabled())
         {

            color.hls_rate(0.0, 0.4, -0.7);

         }

         pbrush->create_solid(color);

         ::int_rectangle rEdit;

         get_element_rectangle(rEdit, e_element_combo_edit);

         {

            auto colorBackground = get_color(pstyle, ::e_element_background, estate);

            if (!colorBackground.is_ok())
            {

               colorBackground = argb(210, 230, 230, 230);

            }

            colorBackground.hls_rate(0.0, 0.6, -0.3);

            pgraphics->fill_rectangle(rEdit, colorBackground);

         }

         {


            auto color2 = get_color(pstyle, estate);

            if (!color2.is_ok())
            {

               color2 = argb(210, 230, 230, 230);

            }

            color2.hls_rate(0.0, 0.3, 0.5);

            pgraphics->draw_inset_rectangle(rEdit, color2, 1.0);

         }

         auto rectanglePadding = get_padding(pstyle);

         rEdit.deflate(rectanglePadding);

         pgraphics->fill_rectangle(rEdit, color);

      }

      ::int_rectangle rectangleDropDown;

      get_element_rectangle(rectangleDropDown, e_element_drop_down);

      ::int_rectangle rectangleDropIn(rectangleDropDown);

      ::color::color color(get_color(pstyle, estate));

      if (color.is_transparent())
      {

         color = argb(210, 230, 230, 230);

      }

      color.hls_rate(0.0, 0.5, 0.1);

      pbrush->create_solid(color);

      pgraphics->set(pbrush);

      pgraphics->fill_rectangle(rectangleDropIn);

      auto ppath = øcreate < ::draw2d::path > ();

      double_point_array pointa;

      get_simple_drop_down_open_arrow_polygon(pointa);

      pbrush->create_solid(argb(210, 0, 0, 0));

      pgraphics->set(pbrush);

      pgraphics->fill_polygon(pointa);

   }


} //  namespace user



