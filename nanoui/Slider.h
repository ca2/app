/*
    nanoui/slider.h -- Fractional slider widget with mouse control

    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The widget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/
/** \file */
#pragma once


#include "Widget.h"


namespace nanoui
{


/**
 * \class Slider slider.h nanoui/slider.h
 *
 * \brief Fractional slider widget with mouse control.
 */
   class CLASS_DECL_NANOUI Slider : public Widget {
   public:
      Slider(Widget * parent);

      float value() const { return m_value; }
      void set_value(float value) { m_value = value; }

      const ::color::color & highlight_color() const { return m_highlight_color; }
      void set_highlight_color(const ::color::color & highlight_color) { m_highlight_color = highlight_color; }

      std::pair<float, float> range() const { return m_range; }
      void set_range(std::pair<float, float> range) { m_range = range; }

      std::pair<float, float> highlighted_range() const { return m_highlighted_range; }
      void set_highlighted_range(std::pair<float, float> highlighted_range) { m_highlighted_range = highlighted_range; }

      ::function<void(float)> callback() const { return m_callback; }
      void set_callback(const ::function<void(float)> & callback) { m_callback = callback; }

      ::function<void(float)> final_callback() const { return m_final_callback; }
      void set_final_callback(const ::function<void(float)> & callback) { m_final_callback = callback; }

      virtual Vector2i preferred_size(::nano2d::context * pcontext, bool bRecalcTextSize = true) override;
      virtual bool mouse_drag_event(const Vector2i & p, const Vector2i & rel, const ::user::e_key & ekeyModifiers) override;
      virtual bool mouse_button_event(const Vector2i & p, ::user::e_mouse emouse, bool down, bool bDoubleClick, const ::user::e_key & ekeyModifiers) override;
      virtual void draw(::nano2d::context * pcontext) override;

   protected:
      float m_value;
      ::function<void(float)> m_callback;
      ::function<void(float)> m_final_callback;
      std::pair<float, float> m_range;
      std::pair<float, float> m_highlighted_range;
      ::color::color m_highlight_color;
      
   };



} // namespace nanoui


