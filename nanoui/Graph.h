/*
    nanoui/graph.h -- Simple graph pwidget for showing a function plot

    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The pwidget drawing code is based on the NanoVG demo application
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
 * \class Graph graph.h nanoui/graph.h
 *
 * \brief Simple graph pwidget for showing a function plot.
 */
   class CLASS_DECL_NANOUI Graph : public Widget {
   public:
      Graph(Widget * parent, const ::scoped_string & caption = "Untitled");

      ::string caption() const { return m_caption; }
      void set_caption(const ::scoped_string & caption) { m_caption = caption; }

      ::string header() const { return m_header; }
      void set_header(const ::scoped_string & header) { m_header = header; }

      ::string footer() const { return m_footer; }
      void set_footer(const ::scoped_string & footer) { m_footer = footer; }

      const ::color::color & colorBackground() const { return m_colorBackground; }
      void set_background_color(const ::color::color & colorBackground) { m_colorBackground = colorBackground; }

      const ::color::color & stroke_color() const { return m_stroke_color; }
      void set_stroke_color(const ::color::color & stroke_color) { m_stroke_color = stroke_color; }

      const ::color::color & fill_color() const { return m_fill_color; }
      void set_fill_color(const ::color::color & fill_color) { m_fill_color = fill_color; }

      const ::color::color & text_color() const { return m_colorText; }
      void set_text_color(const ::color::color & text_color) { m_colorText = text_color; }

      const ::f32_array & values() const { return m_values; }
      ::f32_array & values() { return m_values; }
      void set_values(const ::f32_array & values) { m_values = values; }

      virtual vector2_i32 preferred_size(::nano2d::context * pcontext, bool bRecalcTextSize = true) override;
      virtual void draw(::nano2d::context * pcontext) override;
   protected:
      ::string m_caption, m_header, m_footer;
      ::color::color m_colorBackground, m_fill_color, m_stroke_color, m_colorText;
      ::f32_array m_values;
};



} // namespace nanoui


