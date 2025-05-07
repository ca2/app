/*
    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The pwidget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/
/**
 * \file nanoui/colorwheel.h
 *
 * \brief Fancy analog pwidget to select a color::color value.  This pwidget was
 *        contributed by Dmitriy Morozov.
 */

#pragma once


#include "nanoui/Widget.h"
#include "axis/graphics/graphics/color_wheel.h"


namespace nanoui
{


/**
 * \class ColorWheel colorwheel.h nanoui/colorwheel.h
 *
 * \brief Fancy analog pwidget to select a color::color value.  This pwidget was
 *        contributed by Dmitriy Morozov.
 */
   class CLASS_DECL_NANOUI ColorWheel : public Widget,
   virtual public ::graphics::color_wheel{
   public:

      //// Used to describe where the mouse is interacting
      //enum Region {
      //   None = 0,
      //   InnerTriangle = 1,
      //   OuterCircle = 2,
      //   Both = 3,
      //   ClientArea = 4
      //};

      ///// The current hue in the HSV color::color model.
      //float m_hue;

      ///**
      // * The 'V' (value) component of the HSV color::color model.  See implementation \::pointer
      // * nanoui::ColorWheel::color::color for its usage.  Valid values are in the range
      // * ``[0, 1]``.
      // */
      //float m_white;

      ///**
      // * The 'S' (satration) component of the HSV color::color model.  See implementation
      // * \::pointer nanoui::ColorWheel::color::color for its usage.  Valid values are in the
      // * range ``[0, 1]``.
      // */
      //float m_black;

      ///// The current region the mouse is interacting with.
      //Region m_regionDrag;

      ///// The current callback to execute when the color::color value has changed.
      //::function<void(const color::hls&)> m_callback;

      /**
       * Adds a ColorWheel to the specified parent.
       *
       * \param parent
       *     The Widget to add this ColorWheel to.
       *
       * \param hls
       *     The initial color of the ColorWheel (default: Red).
       */
      ColorWheel(Widget * parent, const color::hls & hls = argb(1.0f, 0.0f, 0.0f, 1.0f));

      /// The callback to execute when a user changes the ColorWheel value.
      ::function<void(const color::hls &)> callback() const { return m_callback; }

      /// Sets the callback to execute when a user changes the ColorWheel value.
      void set_callback(const ::function<void(const color::hls &)> & callback) { m_callback = callback; }

      /// The current color::color this ColorWheel has selected.
      //color::color color() const;

      /// Sets the current color::color this ColorWheel has selected.
      //void set_color(const color::color & color);

      /// The preferred size of this ColorWheel.
      int_size preferred_size(::nano2d::context  * pcontext, bool bRecalcTextSize = true) override;

      /// Draws the ColorWheel.
      void draw(::nano2d::context  * pcontext) override;

      /// Handles mouse button click happenings for the ColorWheel.
      bool mouse_button_event(const int_point & p, ::user::e_mouse emouse, bool down, bool bDoubleClick, const ::user::e_key & ekeyModifiers) override;

      bool mouse_motion_event(const int_point& p, const int_size& rel, bool bDown, const ::user::e_key& ekeyModifiers) override;
      /// Handles mouse drag happenings for the ColorWheel.
      //bool mouse_drag_event(const sequence2_int & p, const sequence2_int & rel, const ::user::e_key & ekeyModifiers) override;

      // Converts a specified hue (with saturation = value = 1) to RGB space.
      // color::color hue2rgb(float h) const;

      // Manipulates the positioning of the different regions of the ColorWheel.
      //Region adjust_position(const int_point & p);

      virtual void graphics_set_mouse_capture() override;
      virtual void graphics_release_mouse_capture() override;
      virtual void graphics_redraw() override;


   };


} // namespace nanoui



