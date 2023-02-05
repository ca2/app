/*
    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The widget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/
/**
 * \file nanoui/colorwheel.h
 *
 * \brief Fancy analog widget to select a color value.  This widget was
 *        contributed by Dmitriy Morozov.
 */

#pragma once


#include "Widget.h"


namespace nanoui
{


/**
 * \class ColorWheel colorwheel.h nanoui/colorwheel.h
 *
 * \brief Fancy analog widget to select a color value.  This widget was
 *        contributed by Dmitriy Morozov.
 */
   class NANOUI_EXPORT ColorWheel : public Widget {
   public:
      /**
       * Adds a ColorWheel to the specified parent.
       *
       * \param parent
       *     The Widget to add this ColorWheel to.
       *
       * \param color
       *     The initial color of the ColorWheel (default: Red).
       */
      ColorWheel(Widget * parent, const Color & color = Color(1.0f, 0.0f, 0.0f, 1.0f));

      /// The callback to execute when a user changes the ColorWheel value.
      ::function<void(const Color &)> callback() const { return m_callback; }

      /// Sets the callback to execute when a user changes the ColorWheel value.
      void set_callback(const ::function<void(const Color &)> & callback) { m_callback = callback; }

      /// The current Color this ColorWheel has selected.
      Color color() const;

      /// Sets the current Color this ColorWheel has selected.
      void set_color(const Color & color);

      /// The preferred size of this ColorWheel.
      Vector2i preferred_size(::nano2d::context * pcontext, bool bRecalcTextSize = true) override;

      /// Draws the ColorWheel.
      void draw(::nano2d::context * pcontext) override;

      /// Handles mouse button click events for the ColorWheel.
      bool mouse_button_event(const Vector2i & p, ::user::e_mouse emouse, bool down, const ::user::e_key & ekeyModifiers) override;

      /// Handles mouse drag events for the ColorWheel.
      bool mouse_drag_event(const Vector2i & p, const Vector2i & rel, const ::user::e_key & ekeyModifiers) override;
   private:
      // Used to describe where the mouse is interacting
      enum Region {
         None = 0,
         InnerTriangle = 1,
         OuterCircle = 2,
         Both = 3
      };

      // Converts a specified hue (with saturation = value = 1) to RGB space.
      Color hue2rgb(float h) const;

      // Manipulates the positioning of the different regions of the ColorWheel.
      Region adjust_position(const Vector2i & p, Region considered_regions = Both);

   protected:
      /// The current hue in the HSV color model.
      float m_hue;

      /**
       * The 'V' (value) component of the HSV color model.  See implementation \ref
       * nanoui::ColorWheel::color for its usage.  Valid values are in the range
       * ``[0, 1]``.
       */
      float m_white;

      /**
       * The 'S' (satration) component of the HSV color model.  See implementation
       * \ref nanoui::ColorWheel::color for its usage.  Valid values are in the
       * range ``[0, 1]``.
       */
      float m_black;

      /// The current region the mouse is interacting with.
      Region m_drag_region;

      /// The current callback to execute when the color value has changed.
      ::function<void(const Color &)> m_callback;
};



} // namespace nanoui


