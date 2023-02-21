/*
    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The widget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/
/** \file */

#pragma once


#include "PopupButton.h"


namespace nanoui
{


/**
 * \class ColorPicker colorpicker.h nanoui/colorpicker.h
 *
 * \brief Push button with a popup to tweak a color value.
 */
   class CLASS_DECL_NANOUI ColorPicker : public PopupButton {
   public:
      /**
       * Attaches a ColorPicker to the specified parent.
       *
       * \param parent
       *     The Widget to add this ColorPicker to.
       *
       * \param color
       *     The color initially selected by this ColorPicker (default: Red).
       */

      ColorPicker(Widget * parent, const Color & color = Color(1.f, 0.f, 0.f, 1.f));

      /// The callback executed when the ColorWheel changes.
      std::function<void(const Color &)> callback() const { return m_callback; }

      /**
       * Sets the callback is executed as the ColorWheel itself is changed.  Set
       * this callback if you need to receive updates for the ColorWheel changing
       * before the user clicks \ref nanoui::ColorPicker::mPickButton or
       * \ref nanoui::ColorPicker::mPickButton.
       */
      void set_callback(const std::function<void(const Color &)> & callback) {
         m_callback = callback;
         m_callback(background_color());
      }

      /**
       * The callback to execute when a memory_new Color is selected on the ColorWheel
       * **and** the user clicks the \ref nanoui::ColorPicker::m_pick_button or
       * \ref nanoui::ColorPicker::m_reset_button.
       */
      std::function<void(const Color &)> final_callback() const { return m_final_callback; }

      /**
       * The callback to execute when a memory_new Color is selected on the ColorWheel
       * **and** the user clicks the \ref nanoui::ColorPicker::m_pick_button or
       * \ref nanoui::ColorPicker::m_reset_button.
       */
      void set_final_callback(const std::function<void(const Color &)> & callback) { m_final_callback = callback; }

      /// Get the current color
      Color color() const;
      /// Set the current color
      void set_color(const Color & color);

      /// The current caption of the \ref nanoui::ColorPicker::m_pick_button.
      ::string pick_button_caption() { return m_pick_button->caption(); }

      /// Sets the current caption of the \ref nanoui::ColorPicker::m_pick_button.
      void set_pick_button_caption(const ::scoped_string & caption) { m_pick_button->set_caption(caption); }

      /// The current caption of the \ref nanoui::ColorPicker::m_reset_button.
      ::string reset_button_caption() { return m_reset_button->caption(); }

      /// Sets the current caption of the \ref nanoui::ColorPicker::m_reset_button.
      void set_reset_button_caption(const ::scoped_string & caption) { m_reset_button->set_caption(caption); }
   protected:
      /// The "fast" callback executed when the ColorWheel has changed.
      std::function<void(const Color &)> m_callback;

      /**
       * The callback to execute when a memory_new Color is selected on the ColorWheel
       * **and** the user clicks the \ref nanoui::ColorPicker::m_pick_button or
       * \ref nanoui::ColorPicker::m_reset_button.
       */
      std::function<void(const Color &)> m_final_callback;

      /// The ColorWheel for this ColorPicker (the actual widget allowing selection).
      ColorWheel * m_color_wheel;

      /**
       * The Button used to signal that the current value on the ColorWheel is the
       * desired color to be chosen.  The default value for the caption of this
       * Button is ``"Pick"``.  You can change it using
       * \ref nanoui::ColorPicker::set_pick_button_caption if you need.
       *
       * The color of this Button will not affect \ref nanoui::ColorPicker::color
       * until the user has actively selected by clicking this pick button.
       * Similarly, the \ref nanoui::ColorPicker::m_callback function is only
       * called when a user selects a memory_new Color using by clicking this Button.
       */
      Button * m_pick_button;

      /**
       * Remains the Color of the active color selection, until the user picks a
       * memory_new Color on the ColorWheel **and** selects the
       * \ref nanoui::ColorPicker::m_pick_button.  The default value for the
       * caption of this Button is ``"Reset"``.  You can change it using
       * \ref nanoui::ColorPicker::set_reset_button_caption if you need.
       */
      Button * m_reset_button;
};



} // namespace nanoui


