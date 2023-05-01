/*
    src/popupbutton.cpp -- Button which launches a popup widget

    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The widget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/
#include "framework.h"
#include "PopupButton.h"
#include "Popup.h"
#include "Screen.h"
#include "nano2d/context.h"


namespace nanoui
{


PopupButton::PopupButton(Widget * parent, const ::scoped_string & caption, int button_icon)
   : Button(parent, caption, button_icon) {

   m_chevron_icon = m_theme->m_popup_chevron_right_icon;

   set_flags(Flags::ToggleButton | Flags::PopupButton);

   m_popup = memory_new Popup(screen(), window());
   m_popup->set_size(Vector2i(320, 250));
   m_popup->set_visible(false);

   m_icon_extra_scale = 0.8f; // widget override
}


Vector2i PopupButton::preferred_size(::nano2d::context * pcontext, bool bRecalcTextSize)
{
   
   return Button::preferred_size(pcontext) + Vector2i(15, 0);
   
}


void PopupButton::draw(::nano2d::context * pcontext) {
   if (!m_enabled && m_bChecked)
      m_bChecked = false;

   m_popup->set_visible(m_bChecked);
   Button::draw(pcontext);

   if (m_chevron_icon) {
      auto icon = get_utf8_character(m_chevron_icon);
      ::color::color text_color =
         m_text_color.alpha == 0 ? m_theme->m_text_color : m_text_color;

      pcontext->font_size((m_font_size < 0 ? m_theme->m_button_font_size : m_font_size) * icon_scale());
      pcontext->font_face("icons");
      pcontext->fill_color(m_enabled ? text_color : ::color::color(m_theme->m_disabled_text_color));
      pcontext->text_align(::nano2d::e_align_left | ::nano2d::e_align_middle);

      float iw = pcontext->text_bounds(0, 0, icon.data(), nullptr);
      Vector2f icon_pos(0, m_pos.y() + m_size.y() * 0.5f - 1);

      if (m_popup->side() == Popup::Right)
         icon_pos[0] = m_pos.x() + m_size.x() - iw - 8.f;
      else
         icon_pos[0] = m_pos.x() + 8.f;

      pcontext->text(icon_pos.x(), icon_pos.y(), icon.data());
   }
}

void PopupButton::perform_layout(::nano2d::context * pcontext, bool bRecalcTextSize) {
   Widget::perform_layout(pcontext);

   const Window * parent_window = window();

   int anchor_size = m_popup->anchor_size();

   if (parent_window) {
      int pos_y = absolute_position().y() - parent_window->position().y() + m_size.y() / 2;
      if (m_popup->side() == Popup::Right)
         m_popup->set_anchor_pos(Vector2i(parent_window->width() + anchor_size, pos_y));
      else
         m_popup->set_anchor_pos(Vector2i(-anchor_size, pos_y));
   }
   else {
      m_popup->set_position(absolute_position() + Vector2i(width() + anchor_size + 1, m_size.y() / 2 - anchor_size));
   }
}

void PopupButton::set_side(Popup::Side side) {
   if (m_popup->side() == Popup::Right &&
      m_chevron_icon == m_theme->m_popup_chevron_right_icon)
      set_chevron_icon(m_theme->m_popup_chevron_left_icon);
   else if (m_popup->side() == Popup::Left &&
      m_chevron_icon == m_theme->m_popup_chevron_left_icon)
      set_chevron_icon(m_theme->m_popup_chevron_right_icon);
   m_popup->set_side(side);
}



} // namespace nanoui


