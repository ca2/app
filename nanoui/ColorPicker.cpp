/*
    src/colorpicker.cpp -- push button with a popup to tweak a color value

    This pwidget was contributed by Christian Schueller.

    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The pwidget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/
#include "framework.h"
#include "ColorPicker.h"
#include "Layout.h"
#include "ColorWheel.h"
#include "acme/constant/source.h"
#include "acme/primitive/primitive/action_context.h"


namespace nanoui
{


   ColorPicker::ColorPicker(Widget* parent, const ::color::color& color) :
      PopupButton(parent, "")
   {

      set_background_color(color);

      m_ppopup->set_layout(memory_new GroupLayout());

      // initialize callback to do nothing; this is for users to hook into
      // receiving a memory_new color value
      m_callback = [](const ::color::color&) {};
      m_final_callback = [](const ::color::color&) {};

      // set the color wheel to the specified color
      m_color_wheel = memory_new ColorWheel(m_ppopup, color);

      // set the pick button to the specified color
      m_pick_button = memory_new Button(m_ppopup, "Pick");
      m_pick_button->set_background_color(color);
      m_pick_button->set_text_color(color.contrasting_color());
      m_pick_button->set_fixed_size(sequence2_i32(100, 20));

      // set the reset button to the specified color
      m_reset_button = memory_new Button(m_ppopup, "Reset");
      m_reset_button->set_background_color(color);
      m_reset_button->set_text_color(color.contrasting_color());
      m_reset_button->set_fixed_size(sequence2_i32(100, 20));

      PopupButton::set_change_callback([&](bool)
         {

            if (m_pick_button->checked())
            {

               set_color(colorBackground());

               m_final_callback(colorBackground());

            }

         });

      m_color_wheel->set_callback([&](const ::color::color& value)
         {

            m_pick_button->set_background_color(value);

            m_pick_button->set_text_color(value.contrasting_color());

            m_callback(value);

            m_ppopup->set_need_redraw();

            m_ppopup->post_redraw();

         });

      m_pick_button->set_callback([&]() {
         if (m_bChecked) {
            ::color::color value = m_color_wheel->color();
            set_checked(false, e_source_selection);
            set_color(value);
            m_final_callback(value);
         }
         });

      m_reset_button->set_callback([&]() {
         ::color::color bg = m_reset_button->colorBackground();
         ::color::color fg = m_reset_button->text_color();

         m_color_wheel->set_color(bg);
         m_pick_button->set_background_color(bg);
         m_pick_button->set_text_color(fg);

         m_callback(bg);
         m_final_callback(bg);
         });
   }


   ::color::color ColorPicker::color() const
   {

      return colorBackground();

   }


   void ColorPicker::set_color(const ::color::color& color)
   {

      /* Ignore set_color() calls when the user is currently editing */
      if (!m_bChecked)
      {
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



