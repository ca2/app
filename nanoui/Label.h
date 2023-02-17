/*
    nanoui/label.h -- Text label with an arbitrary font, color, and size

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
 * \class Label label.h nanoui/label.h
 *
 * \brief Text label widget.
 *
 * The font and color can be customized. When \ref Widget::set_fixed_width()
 * is used, the text is wrapped when it surpasses the specified width.
 */
   class CLASS_DECL_NANOUI Label :
      virtual public Widget
   //, virtual public ::appearance::still
   {
   public:


         ::string m_caption;
         ::string m_font;
         Color m_color;
         Vector2i m_sizePreferred;

      Label(Widget * parent, const ::scoped_string & caption,
         const ::scoped_string & font = "sans", int font_size = -1);

      /// Get the label's text caption
      ::string caption() const { return m_caption; }
      /// Set the label's text caption
      void set_caption(const ::scoped_string & caption) { m_caption = caption; }

      /// Set the currently active font (2 are available by default: 'sans' and 'sans-bold')
      void set_font(const ::scoped_string & font) { m_font = font; }
      /// Get the currently active font
      ::string font() const { return m_font; }

      /// Get the label color
      Color color() const { return m_color; }
      /// Set the label color
      void set_color(const Color & color) { m_color = color; }

      /// Set the \ref Theme used to draw this widget
      virtual void set_theme(Theme * theme) override;

      /// Compute the size needed to fully display the label
      virtual Vector2i preferred_size(::nano2d::context * pcontext, bool bRecalcTextSize = true) override;

      /// Draw the label
      virtual void draw(::nano2d::context * pcontext) override;

      //void _nanoui_to_user(::user::interaction * puserinteraction) override;

};



} // namespace nanoui


