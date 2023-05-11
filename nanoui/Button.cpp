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
#include "_function.h"
#include "aura/user/user/interaction.h"
#include "nano2d/context.h"


namespace nanoui
{


Button::Button(Widget * parent, const ::scoped_string & caption, int icon)
   : Widget(parent), m_caption(caption), m_icon(icon),
   m_icon_position(IconPosition::LeftCentered), m_bMouseDown(false), m_bChecked(false),
   m_flags(NormalButton), m_background_color( ::color::color(0, 0)),
   m_text_color( ::color::color(0, 0)),
   m_tw(-1.f),m_iw(-1.f),m_ih(-1.f)
{


}


Vector2i Button::preferred_size(::nano2d::context * pcontext, bool bRecalcTextSize)
{

   if (bRecalcTextSize || m_tw < 0.f || m_iw < 0.f || m_ih < 0.f)
   {

      int font_size = m_font_size == -1 ? m_theme->m_button_font_size : m_font_size;
      pcontext->font_size((float)font_size);
      pcontext->font_face("sans-bold");
      m_tw = pcontext->text_bounds(0, 0, m_caption, nullptr);
      m_iw = 0.0f;
      m_ih = (float) font_size;

      if (m_icon) {
         if (::nano2d_is_font_icon(m_icon)) {
            pcontext->font_face("icons");
            pcontext->font_size(m_ih * icon_scale());
            m_iw = pcontext->text_bounds(0, 0, get_utf8_character(m_icon), nullptr)
               + m_size.y() * 0.15f;
         }
         else {
            int w, h;
            pcontext->image_size(m_icon, &w, &h);
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


bool Button::mouse_button_event(const Vector2i & p, ::user::e_mouse emouse, bool down, bool bDoubleClick, const ::user::e_key & ekeyModifiers)
{

   Widget::mouse_button_event(p, emouse, down, bDoubleClick, ekeyModifiers);
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

            dynamic_cast<nanoui::PopupButton *>(this)->popup()->request_focus();

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


void Button::draw(::nano2d::context * pcontext)
{
   
   Widget::draw(pcontext);

   ::color::color grad_top = m_theme->m_button_gradient_top_unfocused;
   ::color::color grad_bot = m_theme->m_button_gradient_bot_unfocused;

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

   pcontext->begin_path();

   pcontext->rounded_rectangle(m_pos.x() + 1.f, m_pos.y() + 1.f, m_size.x() - 2.f,
      m_size.y() - 2.f, m_theme->m_button_corner_radius - 1.f);

   if (m_background_color.alpha != 0) {
      pcontext->fill_color( ::color::color(m_background_color.red, m_background_color.green,
         m_background_color.blue, 1.f));
      pcontext->fill();
      if (bPressed) {
         grad_top.set_alpha(grad_bot.set_alpha(0.8f));
      }
      else {
         double v = 1 - m_background_color.fa();
         grad_top.set_alpha(grad_bot.set_alpha((float) (m_enabled ? v : v * .5 + .5)));
      }
   }

   ::nano2d::paint bg = pcontext->linear_gradient((float) m_pos.x(), (float)m_pos.y(), (float)m_pos.x(),
      (float) (m_pos.y() + m_size.y()), grad_top, grad_bot);

   pcontext->fill_paint(bg);
   pcontext->fill();

   pcontext->begin_path();
   pcontext->stroke_width(1.0f);
   pcontext->rounded_rectangle(m_pos.x() + 0.5f, m_pos.y() + (bPressed ? 0.5f : 1.5f), m_size.x() - 1.f,
      m_size.y() - 1.f - (bPressed ? 0.0f : 1.0f), (float) m_theme->m_button_corner_radius);
   pcontext->stroke_color(m_theme->m_border_light);
   pcontext->stroke();

   pcontext->begin_path();
   pcontext->rounded_rectangle((float)m_pos.x() + 0.5f, (float)m_pos.y() + 0.5f, (float)m_size.x() - 1.f,
      (float)m_size.y() - 2.f, (float)m_theme->m_button_corner_radius);
   pcontext->stroke_color(m_theme->m_border_dark);
   pcontext->stroke();

   int font_size = m_font_size == -1 ? m_theme->m_button_font_size : m_font_size;
   pcontext->font_size((float)font_size);
   pcontext->font_face("sans-bold");
   float tw = pcontext->text_bounds(0, 0, m_caption, nullptr);

   Vector2f center = Vector2f(m_pos) + Vector2f(m_size) * 0.5f;
   Vector2f text_pos(center.x() - tw * 0.5f, center.y() - 1);
   ::color::color text_color =
      m_text_color.alpha == 0 ? m_theme->m_text_color : m_text_color;
   if (!m_enabled)
      text_color = m_theme->m_disabled_text_color;

   if (m_icon) {
      auto icon = get_utf8_character(m_icon);

      float iw, ih = (float)font_size;
      if (::nano2d_is_font_icon(m_icon)) {
         ih *= icon_scale();
         pcontext->font_size(ih);
         pcontext->font_face("icons");
         iw = pcontext->text_bounds(0, 0, icon.data(), nullptr);
      }
      else {
         int w, h;
         ih *= 0.9f;
         pcontext->image_size(m_icon, &w, &h);
         iw = w * ih / h;
      }
      if (m_caption != "")
         iw += m_size.y() * 0.15f;
      pcontext->fill_color(text_color);
      pcontext->text_align(::nano2d::e_align_left | ::nano2d::e_align_middle);
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

      if (::nano2d_is_font_icon(m_icon)) {
         pcontext->text(icon_pos.x(), icon_pos.y() + 1, icon.data());
      }
      else {
         ::nano2d::paint img_paint = pcontext->image_pattern(
            icon_pos.x(), icon_pos.y() - ih / 2, iw, ih, 0, m_icon, m_enabled ? 0.5f : 0.25f);

         pcontext->fill_paint(img_paint);
         pcontext->fill();
      }
   }

   pcontext->font_size((float)font_size);
   pcontext->font_face("sans-bold");
   pcontext->text_align(::nano2d::e_align_left | ::nano2d::e_align_middle);
   pcontext->fill_color(m_theme->m_text_color_shadow);
   pcontext->text(text_pos.x(), text_pos.y(), m_caption);
   pcontext->fill_color(text_color);
   pcontext->text(text_pos.x(), text_pos.y() + 1, m_caption);


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
//   //m_pbutton->set_window_text(m_caption.c_str());
//
//   //Widget::_nanoui_to_user(m_pbutton);
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




} // namespace nanoui


