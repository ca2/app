/*
    src/button.cpp -- [Normal/Toggle/Radio/Popup] Button pwidget

    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The pwidget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/
#include "framework.h"
#include "Button.h"
#include "PopupButton.h"
#include "Screen.h"
#include "_function.h"
#include "aura/user/user/interaction.h"
#include "nano2d/context.h"


namespace nanoui
{


   Button::Button(Widget* parent, const ::scoped_string& caption, int iIcon)
      : Widget(parent), m_strCaption(caption), m_iIcon(iIcon),
      m_icon_position(IconPosition::LeftCentered), m_bChecked(false),
      m_flags(NormalButton), m_colorBackground(::color::color(0, 0)),
      m_colorText(::color::color(0, 0)),
      m_fTextWidth(-1.f), m_sizeImage(-1.f, -1.f)
   {


   }


   size_i32 Button::preferred_size(::nano2d::context* pcontext, bool bRecalcTextSize)
   {

      if (bRecalcTextSize || m_fTextWidth < 0.f || m_sizeImage.cx() < 0.f || m_sizeImage.cy() < 0.f)
      {

         int font_size = m_font_size == -1 ? m_ptheme->m_iButtonFontSize : m_font_size;
         pcontext->font_size((float)font_size);
         pcontext->font_face("sans-bold");
         m_fTextWidth = pcontext->text_bounds(0, 0, m_strCaption, nullptr);
         m_sizeImage.cx() = 0.0f;
         m_sizeImage.cy() = (float)font_size;

         if (m_iIcon) {
            if (::nano2d_is_font_icon(m_iIcon)) {
               pcontext->font_face("icons");
               pcontext->font_size(m_sizeImage.cy() * icon_scale());
               m_sizeImage.cx() = pcontext->text_bounds(0, 0, get_utf8_character(m_iIcon), nullptr)
                  + m_size.cy() * 0.15f;
            }
            else {
               int pwidgetChild, h;
               pcontext->image_size(m_iIcon, &pwidgetChild, &h);
               m_sizeImage.cx() = pwidgetChild * m_sizeImage.cy() / h;
            }
         }

      }
      
      return ::size_i32((int)(m_fTextWidth + m_sizeImage.cx()) + 20, (int)(m_sizeImage.cy() + 11));
      
   }

   //
   //bool Button::mouse_enter_event(const point_i32 & p, bool enter, const ::user::e_key & ekeyModifiers)
   //{
   //   
   //   Widget::mouse_enter_event(p, enter, ekeyModifiers);
   //
   //   return true;
   //
   //}


   bool Button::mouse_button_event(const point_i32& p, ::user::e_mouse emouse, bool down, bool bDoubleClick, const ::user::e_key& ekeyModifiers)
   {

      Widget::mouse_button_event(p, emouse, down, bDoubleClick, ekeyModifiers);
      /* Temporarily increase the reference count of the button in case the
         button causes the parent window to be destructed */
      ::pointer<Button> self = this;

      if (m_bEnabled &&
         (

            (emouse == ::user::e_mouse_left_button && !(m_flags & ContextMenuButton)) ||
            (emouse == ::user::e_mouse_right_button && (m_flags & ContextMenuButton))

            )
         )
      {

         if (down)
         {

            if (m_flags & PopupButton)
            {

               for (auto pwidget : parent()->children())
               {

                  ::pointer < Button > pbutton = pwidget;

                  if (pbutton != this && pbutton && (pbutton->flags() & PopupButton) && pbutton->m_bChecked)
                  {

                     pbutton->set_checked(false, e_source_selection);

                     //if (pbutton->m_change_callback)
                     //{

                     //   pbutton->m_change_callback(false);

                     //}

                  }

               }

               dynamic_cast<nanoui::PopupButton*>(this)->popup()->request_focus();

            }

            if (m_flags & RadioButton)
            {

               if (m_button_group.empty())
               {

                  for (auto pwidget : parent()->children())
                  {

                     ::pointer < Button > pbutton = pwidget;

                     if (pbutton != this && pbutton && (pbutton->flags() & RadioButton) && pbutton->m_bChecked)
                     {

                        pbutton->set_checked(false, e_source_selection);

                        //if (pbutton->m_change_callback)
                        //{

                        //   pbutton->m_change_callback(false);

                        //}

                     }

                  }

               }
               else
               {

                  for (auto pbutton : m_button_group)
                  {

                     if (pbutton != this && (pbutton->flags() & RadioButton) && pbutton->m_bChecked)
                     {

                        pbutton->set_checked(false, e_source_selection);

                        //if (pbutton->m_change_callback)
                        //{

                        //   pbutton->m_change_callback(false);

                        //}

                     }

                  }

               }

               //m_bMouseDown = true;

            }

            screen()->m_pwidgetMouseDown = this;

         }
         else 
         {

            auto pscreen = screen();

            if (pscreen->m_pwidgetMouseDown == this
               && (!pscreen->m_pwidgetDrop
                  || pscreen->m_pwidgetDrop == this))
            {

               bool bChecked = m_bChecked;

               if (m_flags & ToggleButton || m_flags & RadioButton)
               {

                  m_bChecked = !m_bChecked;

               }

               on_click();

               if (::is_different(bChecked, m_bChecked) && m_change_callback)
               {

                  m_change_callback(m_bChecked);

               }

            }

         }

         return true;

      }
      //else
      //{

      //   m_bMouseDown = false;

      //}

      return false;

   }


   /// Sets whether or not this Button is currently pushed.
   void Button::set_checked(bool bChecked, const ::action_context& actioncontext)
   {

      if (::is_different(m_bChecked, bChecked))
      {

         m_bChecked = bChecked;

         if (actioncontext.is_user_source() && m_change_callback)
         {

            m_change_callback(bChecked);

         }

         set_need_redraw();

         post_redraw();

      }

   }


   bool Button::mouse_enter_event(const point_i32& p, bool bEnter, const ::user::e_key& ekeyModifiers)
   {

      Widget::mouse_enter_event(p, bEnter, ekeyModifiers);

      set_need_redraw();

      post_redraw();

      return true;

   }


   void Button::draw(::nano2d::context* pcontext)
   {

      Widget::draw(pcontext);

      ::color::color colorGradientTop = m_ptheme->m_colorButtonGradientUnfocused;
      ::color::color colorGradientBottom = m_ptheme->m_colorButtonGradientBottomUnfocused;

      bool bPressed = false;

      if (m_flags & ToggleButton || m_flags & RadioButton)
      {

         bPressed = m_bChecked;

      }
      else
      {

         bPressed = screen()->m_pwidgetMouseDown == this;

      }

      if (bPressed || (m_bMouseHover && (m_flags & ContextMenuButton)))
      {

         colorGradientTop = m_ptheme->m_colorButtonGradientTopPushed;

         colorGradientBottom = m_ptheme->m_colorButtonGradientBottomPushed;

      }
      else if (m_bMouseHover && m_bEnabled)
      {

         colorGradientTop = m_ptheme->m_colorButtonGradientTopFocused;

         colorGradientBottom = m_ptheme->m_colorButtonGradientBottomFocused;

      }

      pcontext->begin_path();

      pcontext->rounded_rectangle(m_pos.x() + 1.f, m_pos.y() + 1.f, m_size.cx() - 3.f,
         m_size.cy() - 2.f, m_ptheme->m_iButtonCornerRadius - 1.f);

      if (m_colorBackground.has_opacity()) 
      {

         auto colorBackground = m_colorBackground;

         colorBackground.set_opacity(1.f);

         pcontext->fill_color(colorBackground);

         pcontext->fill();

         if (bPressed) 
         {

            colorGradientTop.set_opacity(0.8f);

            colorGradientBottom.set_opacity(0.8f);

         }
         else 
         {
            
            auto opacity = 1.f - m_colorBackground.f32_opacity();

            opacity = m_bEnabled ? opacity : opacity * .5f + .5f;

            colorGradientTop.set_opacity(opacity);

            colorGradientBottom.set_opacity(opacity);

         }

      }

      ::nano2d::paint bg = pcontext->linear_gradient((float)m_pos.x(), (float)m_pos.y(), (float)m_pos.x(),
         (float)(m_pos.y() + m_size.cy()), colorGradientTop, colorGradientBottom);

      pcontext->fill_paint(bg);
      pcontext->fill();

      pcontext->begin_path();
      pcontext->stroke_width(1.0f);
      pcontext->rounded_rectangle(m_pos.x() + 0.5f, m_pos.y() + (bPressed ? 0.5f : 1.5f), m_size.cx() - 2.f,
         m_size.cy() - 1.f - (bPressed ? 0.0f : 1.0f), (float)m_ptheme->m_iButtonCornerRadius);
      pcontext->stroke_color(m_ptheme->m_colorBorderLight);
      pcontext->stroke();

      pcontext->begin_path();
      pcontext->rounded_rectangle((float)m_pos.x() + 0.5f, (float)m_pos.y() + 0.5f, (float)m_size.cx() - 2.f,
         (float)m_size.cy() - 2.f, (float)m_ptheme->m_iButtonCornerRadius);
      pcontext->stroke_color(m_ptheme->m_colorBorderDark);
      pcontext->stroke();

      int font_size = m_font_size == -1 ? m_ptheme->m_iButtonFontSize : m_font_size;
      pcontext->font_size((float)font_size);
      pcontext->font_face("sans-bold");
      pcontext->text_align(::e_align_left);
      
      float text_width = pcontext->text_bounds(0, 0, m_strCaption, nullptr);

      auto center = m_pos + m_size * 0.5f;
      
      auto text_pos = center - ::size_f32(text_width * 0.5f, 1.f);

      ::color::color text_color =
         m_colorText.is_transparent() ? m_ptheme->m_colorText : m_colorText;
      if (!m_bEnabled)
         text_color = m_ptheme->m_colorDisableText;

      if (m_iIcon) {
         auto icon = get_utf8_character(m_iIcon);

         float iw, ih = (float)font_size;
         if (::nano2d_is_font_icon(m_iIcon)) {
            ih *= icon_scale();
            pcontext->font_size(ih);
            pcontext->font_face("icons");
            iw = pcontext->text_bounds(0, 0, icon.data(), nullptr);
         }
         else {
            int pwidgetChild, h;
            ih *= 0.9f;
            pcontext->image_size(m_iIcon, &pwidgetChild, &h);
            iw = pwidgetChild * ih / h;
         }
         if (m_strCaption != "")
            iw += m_size.cy() * 0.15f;
         pcontext->fill_color(text_color);
         pcontext->text_align(::nano2d::e_align_left | ::nano2d::e_align_middle);
         point_f32 icon_pos = center;
         icon_pos.y() -= 1;

         if (m_icon_position == IconPosition::LeftCentered) {
            icon_pos.x() -= (text_width + iw) * 0.5f;
            text_pos.x() += iw * 0.5f;
         }
         else if (m_icon_position == IconPosition::RightCentered) {
            text_pos.x() -= iw * 0.5f;
            icon_pos.x() += text_width * 0.5f;
         }
         else if (m_icon_position == IconPosition::Left) {
            icon_pos.x() = m_pos.x() + 8.f;
         }
         else if (m_icon_position == IconPosition::Right) {
            icon_pos.x() = m_pos.x() + m_size.cx() - iw - 8.f;
         }

         if (::nano2d_is_font_icon(m_iIcon))
         {

            pcontext->text(icon_pos.x(), icon_pos.y() + 1, icon.data());

         }
         else 
         {

            ::nano2d::paint img_paint = pcontext->image_pattern_from_index(
               icon_pos.x(), icon_pos.y() - ih / 2, iw, ih, 0, m_bEnabled ? 0.5f : 0.25f,
               m_iIcon);

            pcontext->fill_paint(img_paint);

            pcontext->fill();

         }

      }

      pcontext->font_size((float)font_size);
      pcontext->font_face("sans-bold");
      pcontext->text_align(::nano2d::e_align_left | ::nano2d::e_align_middle);
      pcontext->fill_color(m_ptheme->m_colorTextShadow);

      pcontext->text(text_pos.x(), text_pos.y(), m_strCaption);

      pcontext->fill_color(text_color);

      pcontext->text(text_pos.x(), text_pos.y() + 1, m_strCaption);
      
      if (m_strCaption == "Load Presets")
      {

         ::information("Drawing Load Presets");

      }

   }


   //bool Button::call_click() 
   //{
   //   
   //   if (!m_callback)
   //   {
   //
   //      return false;
   //
   //   }
   //   
   //   callback()(); 
   //   
   //   return true; 
   //
   //}
   //
   //
   //bool Button::call_check(::enum_check echeck) 
   //{
   //
   //   set_check(echeck == ::e_check_checked);
   //   
   //   if (m_change_callback)
   //   {
   //
   //      change_callback()(checked());
   //
   //   }
   //   
   //   return true; 
   //
   //}

   //
   //void Button::_nanoui_to_user(::user::interaction * puserinteraction)
   //{
   //
   //   return;
   //
   //   //puserinteraction->__construct(m_pbutton);
   //
   //   //m_pbutton->m_pappearance = this;
   //
   //   //m_pbutton->create_control(puserinteraction, (iptr)(void *)this);
   //
   //   //if (flags() & ToggleButton)
   //   //{
   //
   //   //   m_pbutton->set_button_style(::user::button::e_style_push);
   //
   //   //}
   //
   //   //m_pbutton->display();
   //
   //   //m_pbutton->place({ 10, 10, 99, 99 });
   //
   //   //m_pbutton->set_need_layout();
   //
   //   //m_pbutton->set_need_redraw();
   //
   //   //m_pbutton->post_redraw();
   //
   //   //m_pbutton->set_window_text(m_strCaption.c_str());
   //
   //   //Widget::_nanoui_to_user(m_pbutton);
   //
   //}


   void Button::on_click()
   {

      set_need_redraw();

      post_redraw();

      if (m_callback)
      {

         m_callback();

      }

   }


} // namespace nanoui



