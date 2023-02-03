/*
    src/button.cpp -- [Normal/Toggle/Radio/Popup] Button widget

    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The widget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/
#include "framework.h"
#include "Button.h"
#include "PopupButton.h"
#include "Screen.h"
#include "aura/user/user/interaction.h"


NAMESPACE_BEGIN(nanogui)

Button::Button(Widget * parent, const ::scoped_string & caption, int icon)
   : Widget(parent), m_caption(caption), m_icon(icon),
   m_icon_position(IconPosition::LeftCentered), m_bMouseDown(false), m_bChecked(false),
   m_flags(NormalButton), m_background_color(Color(0, 0)),
   m_text_color(Color(0, 0)),
   m_tw(-1.f),m_iw(-1.f),m_ih(-1.f)
{


}


Vector2i Button::preferred_size(NVGcontext * ctx, bool bRecalcTextSize)
{

   if (bRecalcTextSize || m_tw < 0.f || m_iw < 0.f || m_ih < 0.f)
   {

      int font_size = m_font_size == -1 ? m_theme->m_button_font_size : m_font_size;
      nvgFontSize(ctx, (float)font_size);
      nvgFontFace(ctx, "sans-bold");
      m_tw = nvgTextBounds(ctx, 0, 0, m_caption.c_str(), nullptr, nullptr);
      m_iw = 0.0f;
      m_ih = (float) font_size;

      if (m_icon) {
         if (nvg_is_font_icon(m_icon)) {
            nvgFontFace(ctx, "icons");
            nvgFontSize(ctx, m_ih * icon_scale());
            m_iw = nvgTextBounds(ctx, 0, 0, get_utf8_character(m_icon).data(), nullptr, nullptr)
               + m_size.y() * 0.15f;
         }
         else {
            int w, h;
            nvgImageSize(ctx, m_icon, &w, &h);
            m_iw = w * m_ih / h;
         }
      }

   }
   return Vector2i((int)(m_tw + m_iw) + 20, (int) (m_ih + 10));
}

//
//bool Button::mouse_enter_event(const Vector2i & p, bool enter, const ::user::e_key & ekeyModifiers)
//{
//   
//   Widget::mouse_enter_event(p, enter, ekeyModifiers);
//
//   return true;
//
//}


bool Button::mouse_button_event(const Vector2i & p, ::user::e_mouse emouse, bool down, const ::user::e_key & ekeyModifiers)
{

   Widget::mouse_button_event(p, emouse, down, ekeyModifiers);
   /* Temporarily increase the reference count of the button in case the
      button causes the parent window to be destructed */
   ref<Button> self = this;

   if (m_enabled == 1 &&
      ((emouse == ::user::e_mouse_left_button && !(m_flags & MenuButton)) ||
         (emouse == ::user::e_mouse_right_button && (m_flags & MenuButton))))
   {

      bool bChecked = m_bChecked;

      if (down) 
      {

         if (m_flags & PopupButton) 
         {

            for (auto widget : parent()->children())
            {
               
               Button * b = dynamic_cast<Button *>(widget);
               
               if (b != this && b && (b->flags() & PopupButton) && b->m_bChecked) 
               {
                  
                  b->m_bChecked = false;

                  if (b->m_change_callback)
                  {

                     b->m_change_callback(false);

                  }

               }

            }

            dynamic_cast<nanogui::PopupButton *>(this)->popup()->request_focus();

         }

         m_bMouseDown = true;

      }
      else 
      {

         if (m_bMouseDown || (m_flags & MenuButton))
         {

            if (contains(p))
            {

               if (m_flags & RadioButton) 
               {

                  if (m_button_group.empty())
                  {

                     for (auto widget : parent()->children()) 
                     {

                        Button * b = dynamic_cast<Button *>(widget);

                        if (b != this && b && (b->flags() & RadioButton) && b->m_bChecked) 
                        {
                        
                           b->m_bChecked = false;

                           if (b->m_change_callback)
                           {

                              b->m_change_callback(false);

                           }

                        }

                     }

                  }
                  else
                  {

                     for (auto b : m_button_group) 
                     {

                        if (b != this && (b->flags() & RadioButton) && b->m_bChecked) 
                        {

                           b->m_bChecked = false;

                           if (b->m_change_callback)
                           {

                              b->m_change_callback(false);

                           }

                        }

                     }

                  }

               }

               if (m_flags & ToggleButton || m_flags & RadioButton)
               {

                  m_bChecked = !m_bChecked;

               }

               on_click();

            }

         }

         m_bMouseDown = false;

      }

      if (::is_different(bChecked, m_bChecked) && m_change_callback)
      {

         m_change_callback(m_bChecked);

      }

      return true;

   }

   return false;

}


bool Button::mouse_enter_event(const Vector2i &p, bool enter, const ::user::e_key & ekeyModifiers)
{

   Widget::mouse_enter_event(p, enter, ekeyModifiers);

   screen()->m_puserinteraction->set_need_redraw();
   screen()->m_puserinteraction->post_redraw();

   return true;

}


void Button::draw(NVGcontext * ctx)
{
   
   Widget::draw(ctx);

   NVGcolor grad_top = m_theme->m_button_gradient_top_unfocused;
   NVGcolor grad_bot = m_theme->m_button_gradient_bot_unfocused;

   bool bPressed = false;

   if (m_flags & ToggleButton || m_flags & RadioButton)
   {

      bPressed = m_bChecked;

   }
   else
   {

      bPressed = m_bMouseDown;

   }

   if (bPressed || (m_mouse_focus && (m_flags & MenuButton))) {
      grad_top = m_theme->m_button_gradient_top_pushed;
      grad_bot = m_theme->m_button_gradient_bot_pushed;
   }
   else if (m_mouse_focus && m_enabled) {
      grad_top = m_theme->m_button_gradient_top_focused;
      grad_bot = m_theme->m_button_gradient_bot_focused;
   }

   nvgBeginPath(ctx);

   nvgRoundedRect(ctx, m_pos.x() + 1.f, m_pos.y() + 1.f, m_size.x() - 2.f,
      m_size.y() - 2.f, m_theme->m_button_corner_radius - 1.f);

   if (m_background_color.w() != 0) {
      nvgFillColor(ctx, Color(m_background_color[0], m_background_color[1],
         m_background_color[2], 1.f));
      nvgFill(ctx);
      if (bPressed) {
         grad_top.a = grad_bot.a = 0.8f;
      }
      else {
         double v = 1 - m_background_color.w();
         grad_top.a = grad_bot.a = (float) (m_enabled ? v : v * .5 + .5);
      }
   }

   NVGpaint bg = nvgLinearGradient(ctx, (float) m_pos.x(), (float)m_pos.y(), (float)m_pos.x(),
      (float) (m_pos.y() + m_size.y()), grad_top, grad_bot);

   nvgFillPaint(ctx, bg);
   nvgFill(ctx);

   nvgBeginPath(ctx);
   nvgStrokeWidth(ctx, 1.0f);
   nvgRoundedRect(ctx, m_pos.x() + 0.5f, m_pos.y() + (bPressed ? 0.5f : 1.5f), m_size.x() - 1.f,
      m_size.y() - 1.f - (bPressed ? 0.0f : 1.0f), (float) m_theme->m_button_corner_radius);
   nvgStrokeColor(ctx, m_theme->m_border_light);
   nvgStroke(ctx);

   nvgBeginPath(ctx);
   nvgRoundedRect(ctx, (float)m_pos.x() + 0.5f, (float)m_pos.y() + 0.5f, (float)m_size.x() - 1.f,
      (float)m_size.y() - 2.f, (float)m_theme->m_button_corner_radius);
   nvgStrokeColor(ctx, m_theme->m_border_dark);
   nvgStroke(ctx);

   int font_size = m_font_size == -1 ? m_theme->m_button_font_size : m_font_size;
   nvgFontSize(ctx, (float)font_size);
   nvgFontFace(ctx, "sans-bold");
   float tw = nvgTextBounds(ctx, 0, 0, m_caption.c_str(), nullptr, nullptr);

   Vector2f center = Vector2f(m_pos) + Vector2f(m_size) * 0.5f;
   Vector2f text_pos(center.x() - tw * 0.5f, center.y() - 1);
   NVGcolor text_color =
      m_text_color.w() == 0 ? m_theme->m_text_color : m_text_color;
   if (!m_enabled)
      text_color = m_theme->m_disabled_text_color;

   if (m_icon) {
      auto icon = get_utf8_character(m_icon);

      float iw, ih = (float)font_size;
      if (nvg_is_font_icon(m_icon)) {
         ih *= icon_scale();
         nvgFontSize(ctx, ih);
         nvgFontFace(ctx, "icons");
         iw = nvgTextBounds(ctx, 0, 0, icon.data(), nullptr, nullptr);
      }
      else {
         int w, h;
         ih *= 0.9f;
         nvgImageSize(ctx, m_icon, &w, &h);
         iw = w * ih / h;
      }
      if (m_caption != "")
         iw += m_size.y() * 0.15f;
      nvgFillColor(ctx, text_color);
      nvgTextAlign(ctx, NVG_ALIGN_LEFT | NVG_ALIGN_MIDDLE);
      Vector2f icon_pos = center;
      icon_pos.y() -= 1;

      if (m_icon_position == IconPosition::LeftCentered) {
         icon_pos.x() -= (tw + iw) * 0.5f;
         text_pos.x() += iw * 0.5f;
      }
      else if (m_icon_position == IconPosition::RightCentered) {
         text_pos.x() -= iw * 0.5f;
         icon_pos.x() += tw * 0.5f;
      }
      else if (m_icon_position == IconPosition::Left) {
         icon_pos.x() = m_pos.x() + 8.f;
      }
      else if (m_icon_position == IconPosition::Right) {
         icon_pos.x() = m_pos.x() + m_size.x() - iw - 8.f;
      }

      if (nvg_is_font_icon(m_icon)) {
         nvgText(ctx, icon_pos.x(), icon_pos.y() + 1, icon.data(), nullptr);
      }
      else {
         NVGpaint img_paint = nvgImagePattern(ctx,
            icon_pos.x(), icon_pos.y() - ih / 2, iw, ih, 0, m_icon, m_enabled ? 0.5f : 0.25f);

         nvgFillPaint(ctx, img_paint);
         nvgFill(ctx);
      }
   }

   nvgFontSize(ctx, (float)font_size);
   nvgFontFace(ctx, "sans-bold");
   nvgTextAlign(ctx, NVG_ALIGN_LEFT | NVG_ALIGN_MIDDLE);
   nvgFillColor(ctx, m_theme->m_text_color_shadow);
   nvgText(ctx, text_pos.x(), text_pos.y(), m_caption.c_str(), nullptr);
   nvgFillColor(ctx, text_color);
   nvgText(ctx, text_pos.x(), text_pos.y() + 1, m_caption.c_str(), nullptr);
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
//void Button::_nanogui_to_user(::user::interaction * puserinteraction)
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
//   //m_pbutton->set_window_text(m_caption.c_str());
//
//   //Widget::_nanogui_to_user(m_pbutton);
//
//}


void Button::on_click()
{

   auto pscreen = screen();

   if (::is_set(pscreen))
   {

      pscreen->m_puserinteraction->set_need_redraw();

      pscreen->m_puserinteraction->post_redraw();

   }

   if (m_callback)
   {

      m_callback();

   }

}


NAMESPACE_END(nanogui)
