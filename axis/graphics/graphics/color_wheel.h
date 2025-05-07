// From nanoui by camilo on 2025-03-11 22:20 <3ThomasBorregaardSorensen!!
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


#include "axis/graphics/graphics/color_selector.h"
#include "nano2d/font_sink.h"


namespace graphics
{


   /**
    * \class ColorWheel colorwheel.h nanoui/colorwheel.h
    *
    * \brief Fancy analog pwidget to select a color::color value.  This pwidget was
    *        contributed by Dmitriy Morozov.
    */
   class CLASS_DECL_AXIS color_wheel : 
      virtual public ::graphics::color_selector
   {
   public:

      //::pointer<::nano2d::font_sink>      m_pfontsink;
      ::image::image_pointer m_pimageCircle;
      // Used to describe where the mouse is interacting
      enum enum_hit_test
      {
         e_hit_test_none = 0,
         e_hit_test_inner_triangle = 1,
         e_hit_test_outer_circle = 2,
         e_hit_test_both = 3,
         e_hit_test_client_area = 4
      };

      ::float_rectangle m_rectangle;

      /// The current hue in the HSV color::color model.
      //float m_hue;

      /**
       * The 'V' (value) component of the HSV color::color model.  See implementation \::pointer
       * nanoui::ColorWheel::color::color for its usage.  Valid values are in the range
       * ``[0, 1]``.
       */
      //float m_white;

      /**
       * The 'S' (satration) component of the HSV color::color model.  See implementation
       * \::pointer nanoui::ColorWheel::color::color for its usage.  Valid values are in the
       * range ``[0, 1]``.
       */
      //float m_black;

      /// The current region the mouse is interacting with.
      enum_hit_test m_ehittestDrag;

      /// The current callback to execute when the color::color value has changed.
      ::function<void(const color::hls &)> m_callback;

      color_wheel();
      ~color_wheel() override;

      /// The callback to execute when a user changes the ColorWheel value.
      ::function<void(const color::hls &)> callback() const { return m_callback; }

      /// Sets the callback to execute when a user changes the ColorWheel value.
      void set_callback(const ::function<void(const color::hls &)> & callback) { m_callback = callback; }

      /// The current color::color this ColorWheel has selected.
      //color::color color() const;

      /// Sets the current color::color this ColorWheel has selected.
      //void set_color(const color::color & color);



      /// The preferred size of this ColorWheel.
      //int_size preferred_size(::nano2d::context  * pcontext, bool bRecalcTextSize = true) override;

      /// Draws the ColorWheel.
      virtual void on_draw(::draw2d::graphics * pgraphics);
      virtual void _on_draw(::nano2d::context  * pcontext);

      //virtual void _on_draw(::nano2d::context  * pcontext);

      /// Handles mouse button click happenings for the ColorWheel.
      virtual bool on_mouse_down(const int_point & p);
      virtual bool on_mouse_up(const int_point & p);
      virtual bool on_mouse_motion(const int_point & p);
      /// Handles mouse drag happenings for the ColorWheel.
      //bool mouse_drag_event(const sequence2_int & p, const sequence2_int & rel, const ::user::e_key & ekeyModifiers) override;

      // Converts a specified hue (with saturation = value = 1) to RGB space.
      //color::color hue2rgb(float h) const;

      // Manipulates the positioning of the different regions of the ColorWheel.
      enum_hit_test adjust_position_and_hit_test(const int_point & p);

   };


} // namespace graphics



