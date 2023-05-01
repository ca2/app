/*
    src/colorpicker.cpp -- push button with a popup to tweak a color value

    This widget was contributed by Christian Schueller.

    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The widget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/
#include "framework.h"
#include "ColorPicker.h"
#include "Layout.h"
#include "ColorWheel.h"


namespace nanoui
{


ColorPicker::ColorPicker(Widget * parent, const ::color::color & color) : PopupButton(parent, "") {
   set_background_color(color);
   Popup * popup = this->popup();
   popup->set_layout(memory_new GroupLayout());

   // initialize callback to do nothing; this is for users to hook into
   // receiving a memory_new color value
   m_callback = [](const ::color::color &) {};
   m_final_callback = [](const ::color::color &) {};

   // set the color wheel to the specified color
   m_color_wheel = memory_new ColorWheel(popup, color);

   // set the pick button to the specified color
   m_pick_button = memory_new Button(popup, "Pick");
   m_pick_button->set_background_color(color);
   m_pick_button->set_text_color(color.contrasting_color());
   m_pick_button->set_fixed_size(Vector2i(100, 20));

   // set the reset button to the specified color
   m_reset_button = memory_new Button(popup, "Reset");
   m_reset_button->set_background_color(color);
   m_reset_button->set_text_color(color.contrasting_color());
   m_reset_button->set_fixed_size(Vector2i(100, 20));

   PopupButton::set_change_callback([&](bool) {
      if (m_pick_button->checked()) {
         set_color(background_color());
         m_final_callback(background_color());
      }
      });

   m_color_wheel->set_callback([&](const ::color::color & value) {
      m_pick_button->set_background_color(value);
      m_pick_button->set_text_color(value.contrasting_color());
      m_callback(value);
      });

   m_pick_button->set_callback([&]() {
      if (m_bChecked) {
         ::color::color value = m_color_wheel->color();
         set_check(false);
         set_color(value);
         m_final_callback(value);
      }
      });

   m_reset_button->set_callback([&]() {
      ::color::color bg = m_reset_button->background_color();
      ::color::color fg = m_reset_button->text_color();

      m_color_wheel->set_color(bg);
      m_pick_button->set_background_color(bg);
      m_pick_button->set_text_color(fg);

      m_callback(bg);
      m_final_callback(bg);
      });
}

::color::color ColorPicker::color() const {
   return background_color();
}

void ColorPicker::set_color(const ::color::color & color) {
   /* Ignore set_color() calls when the user is currently editing */
   if (!m_bChecked) {
      ::color::color fg = color.contrasting_color();
      set_background_color(color);
      set_text_color(fg);
      m_color_wheel->set_color(color);

      m_pick_button->set_background_color(color);
      m_pick_button->set_text_color(fg);

      m_reset_button->set_background_color(color);
      m_reset_button->set_text_color(fg);
   }
}



} // namespace nanoui


