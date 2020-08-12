#include "framework.h"
#include "core/user/userex/_userex.h"


namespace user
{


   color_combo_box::color_combo_box() 
   {

      m_pview = nullptr;
      m_pframe = nullptr;
      m_pdocument = nullptr;
      m_bMouseDown = false;

   }


   color_combo_box::~color_combo_box()
   {

   }


   void color_combo_box::install_message_routing(::channel * psender)
   {

      ::user::control::install_message_routing(psender);

      IGUI_MSG_LINK(WM_CREATE, psender, this, &::user::color_combo_box::_001OnCreate);
      IGUI_MSG_LINK(WM_LBUTTONDOWN, psender, this, &::user::color_combo_box::_001OnLButtonDown);
      IGUI_MSG_LINK(WM_LBUTTONUP, psender, this, &::user::color_combo_box::_001OnLButtonUp);
      IGUI_MSG_LINK(WM_MOUSEMOVE, psender, this, &::user::color_combo_box::_001OnMouseMove);
      IGUI_MSG_LINK(WM_MOUSELEAVE, psender, this, &::user::color_combo_box::_001OnMouseLeave);
      IGUI_MSG_LINK(WM_SHOWWINDOW, psender, this, &::user::color_combo_box::_001OnShowWindow);

   }


   void color_combo_box::_001OnCreate(::message::message * pmessage)
   {

      SCAST_PTR(::message::create, pcreate, pmessage);

      pcreate->previous();

      //__throw(todo("style"));

      //::rectd r(2, 2, 2, 2);

      //create_rect(::user::rect_edit_padding, r, ::draw2d::unit_pixel);


   }


   void color_combo_box::_001OnLButtonDown(::message::message * pmessage)
   {

      SCAST_PTR(::message::mouse, pmouse, pmessage);

      m_bMouseDown = true;

      SetCapture();

      pmouse->m_bRet = true;

   }


   void color_combo_box::_001OnLButtonUp(::message::message * pmessage)
   {

      SCAST_PTR(::message::mouse, pmouse, pmessage);

      ReleaseCapture();

      if (m_bMouseDown)
      {

         m_bMouseDown = false;

         if(m_pframe != nullptr && m_pframe->is_window_visible())
         {

            m_pframe->display(display_none);

         }
         else
         {


            bool bNew = m_pdocument == nullptr;

            if(bNew)
            {

               User.will_use_view_hint(COLORSEL_IMPACT);

               m_pdocument = User.m_mapimpactsystem[COLORSEL_IMPACT]->open_document_file(get_context_application(), ::type_null, __visible(false));

               m_pview = m_pdocument->get_typed_view < ::userex::color_view >();

               m_pview->m_bCompact = true;

               Session.set_bound_ui(COLORSEL_IMPACT, this);

               m_pframe = m_pview->GetTopLevelFrame()->cast < ::simple_frame_window >();

               m_pframe->SetOwner(this);

               m_pframe->m_ebuttonaHide.add(::experience::button_dock);
               m_pframe->m_ebuttonaHide.add(::experience::button_down);
               m_pframe->m_ebuttonaHide.add(::experience::button_up);
               m_pframe->m_ebuttonaHide.add(::experience::button_minimize);

            }

            m_pview->m_hls = m_hls;

            if(bNew)
            {

               ::rect rectWindow;

               get_window_rect(rectWindow);

               m_pframe->m_sizeMinimum.cx = 300;

               m_pframe->m_sizeMinimum.cy = 150;

               m_pframe->set_window_pos(zorder_top_most, rectWindow.left, rectWindow.bottom, 400, 200, SWP_SHOWWINDOW);

            }
            else
            {

               m_pframe->set_window_pos(zorder_top_most, 0, 0, 0, 0,
                                      SWP_NOSIZE | SWP_NOMOVE | SWP_SHOWWINDOW);

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

      ::user::control::on_control_event(pevent);

   }


   void color_combo_box::_001OnMouseMove(::message::message * pmessage)
   {

      //SCAST_PTR(::message::mouse, pmouse, pmessage);

      UNREFERENCED_PARAMETER(pmessage);

      if (!m_itemHover)
      {

         m_itemHover = ::user::element_client;

         set_need_redraw();

      }

      track_mouse_leave();

   }


   void color_combo_box::_001OnMouseLeave(::message::message * pmessage)
   {

      //SCAST_PTR(::message::mouse, pmouse, pmessage);

      UNREFERENCED_PARAMETER(pmessage);

      m_itemHover = ::user::element_none;

      set_need_redraw();

   }


   void color_combo_box::_001OnShowWindow(::message::message * pmessage)
   {

      SCAST_PTR(::message::show_window, pshowwindow, pmessage);

      if(!pshowwindow->m_bShow)
      {

         if(m_pframe && m_pframe->is_window_visible())
         {

            m_pframe->display(display_none);

         }

      }


   }




   void color_combo_box::on_layout(::draw2d::graphics_pointer & pgraphics)
   {


   }


   void color_combo_box::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::draw2d::brush_pointer br(e_create);

      //::user::e_color colorDropDown = color_button_background_disabled;

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

      //   if (Session.get_focus_ui() == this)
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

         color c(m_hls);

         c.m_iA = 255;

         ::draw2d::brush_pointer b(e_create);

         if (!is_window_enabled())
         {

            c.hls_rate(0.0, 0.4, -0.7);

         }

         b->create_solid(c);

         ::rect rEdit;

         get_element_rect(rEdit, element_combo_edit);

         {

            auto colorBackground = get_color(pstyle, ::user::element_background, estate);

            if (!colorBackground)
            {

               colorBackground = ARGB(210, 230, 230, 230);

            }

            colorBackground.hls_rate(0.0, 0.6, -0.3);

            pgraphics->fill_solid_rect(rEdit, colorBackground);

         }

         {


            auto color2 = get_color(pstyle, estate);

            if (!color2)
            {

               color2 = ARGB(210, 230, 230, 230);

            }

            color2.hls_rate(0.0, 0.3, 0.5);

            pgraphics->draw3d_rect(rEdit, color2);

         }

         ::rect rectPadding = get_padding(pstyle);

         rEdit.deflate(rectPadding);

         pgraphics->fill_solid_rect(rEdit, c.get_rgba());

      }

      ::rect rectDropDown;

      get_element_rect(rectDropDown, element_drop_down);

      ::rect rectDropIn(rectDropDown);

      color c(get_color(pstyle, estate));

      if (!c)
      {

         c = ARGB(210, 230, 230, 230);

      }

      c.hls_rate(0.0, 0.5, 0.1);

      br->create_solid(c);

      pgraphics->set(br);

      pgraphics->fill_rect(rectDropIn);

      ::draw2d::path_pointer path(e_create);

      point_array pointa;

      get_simple_drop_down_open_arrow_polygon(pointa);

      br->create_solid(ARGB(210, 0, 0, 0));

      pgraphics->set(br);

      pgraphics->fill_polygon(pointa);

   }


} //  namespace user



