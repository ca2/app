/*
    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The pwidget drawing code is based on the NanoVG demo application
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
    * \brief Push button with a popup to tweak a ::color::color value.
    */
   class CLASS_DECL_NANOUI ColorPicker :
      public PopupButton
   {
   public:


      /// The "fast" callback executed when the ColorWheel has changed.
      ::function<void(const ::color::color&)> m_callback;

      /**
       * The callback to execute when a memory_new ::color::color is selected on the ColorWheel
       * **and** the user clicks the \::pointer nanoui::ColorPicker::m_pick_button or
       * \::pointer nanoui::ColorPicker::m_reset_button.
       */
      ::function<void(const ::color::color&)> m_final_callback;

      /// The ColorWheel for this ColorPicker (the actual pwidget allowing selection).
      ColorWheel* m_color_wheel;

      /**
       * The Button used to signal that the current value on the ColorWheel is the
       * desired ::color::color to be chosen.  The default value for the caption of this
       * Button is ``"Pick"``.  You can change it using
       * \::pointer nanoui::ColorPicker::set_pick_button_caption if you need.
       *
       * The ::color::color of this Button will not affect \::pointer nanoui::ColorPicker::color::color
       * until the user has actively selected by clicking this pick button.
       * Similarly, the \::pointer nanoui::ColorPicker::m_callback function is only
       * called when a user selects a memory_new ::color::color using by clicking this Button.
       */
      Button* m_pick_button;

      /**
       * Remains the ::color::color of the active ::color::color selection, until the user picks a
       * memory_new ::color::color on the ColorWheel **and** selects the
       * \::pointer nanoui::ColorPicker::m_pick_button.  The default value for the
       * caption of this Button is ``"Reset"``.  You can change it using
       * \::pointer nanoui::ColorPicker::set_reset_button_caption if you need.
       */
      Button* m_reset_button;



      /**
       * Attaches a ColorPicker to the specified parent.
       *
       * \param parent
       *     The Widget to add this ColorPicker to.
       *
       * \param color
       *     The color initially selected by this ColorPicker (default: Red).
       */

      ColorPicker(Widget* parent, const ::color::color& color = ::argb(1.f, 0.f, 0.f, 1.f));

      /// The callback executed when the ColorWheel changes.
      std::function<void(const ::color::color&)> callback() const { return m_callback; }

      /**
       * Sets the callback is executed as the ColorWheel itself is changed.  Set
       * this callback if you need to receive updates for the ColorWheel changing
       * before the user clicks \::pointer nanoui::ColorPicker::mPickButton or
       * \::pointer nanoui::ColorPicker::mPickButton.
       */
      void set_callback(const std::function<void(const ::color::color&)>& callback) {
         m_callback = callback;
         m_callback(colorBackground());
      }

      /**
       * The callback to execute when a memory_new ::color::color is selected on the ColorWheel
       * **and** the user clicks the \::pointer nanoui::ColorPicker::m_pick_button or
       * \::pointer nanoui::ColorPicker::m_reset_button.
       */
      std::function<void(const ::color::color&)> final_callback() const { return m_final_callback; }

      /**
       * The callback to execute when a memory_new ::color::color is selected on the ColorWheel
       * **and** the user clicks the \::pointer nanoui::ColorPicker::m_pick_button or
       * \::pointer nanoui::ColorPicker::m_reset_button.
       */
      void set_final_callback(const std::function<void(const ::color::color&)>& callback) { m_final_callback = callback; }

      /// Get the current ::color::color
      ::color::color color() const;
      /// Set the current ::color::color
      void set_color(const ::color::color& color);

      /// The current caption of the \::pointer nanoui::ColorPicker::m_pick_button.
      ::string pick_button_caption() { return m_pick_button->caption(); }

      /// Sets the current caption of the \::pointer nanoui::ColorPicker::m_pick_button.
      void set_pick_button_caption(const ::scoped_string& caption) { m_pick_button->set_caption(caption); }

      /// The current caption of the \::pointer nanoui::ColorPicker::m_reset_button.
      ::string reset_button_caption() { return m_reset_button->caption(); }

      /// Sets the current caption of the \::pointer nanoui::ColorPicker::m_reset_button.
      void set_reset_button_caption(const ::scoped_string& caption) { m_reset_button->set_caption(caption); }
   };



} // namespace nanoui


