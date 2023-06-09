/*
    nanoui/label.h -- Text label with an arbitrary font, color, and size

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
 * \class Label label.h nanoui/label.h
 *
 * \brief Text label pwidget.
 *
 * The font and color can be customized. When \::pointer Widget::set_fixed_width()
 * is used, the text is wrapped when it surpasses the specified width.
 */
   class CLASS_DECL_NANOUI Label :
      virtual public Widget
   //, virtual public ::appearance::still
   {
   public:


         ::string m_strCaption;
         ::string m_font;
         ::color::color m_color;
         size_i32 m_sizePreferred;

      Label(Widget * parent, const ::scoped_string & caption,
         const ::scoped_string & font = "sans", int font_size = -1);

      /// Get the label's text caption
      ::string caption() const { return m_strCaption; }
      /// Set the label's text caption
      void set_caption(const ::scoped_string & caption) { m_strCaption = caption; }

      /// Set the currently active font (2 are available by default: 'sans' and 'sans-bold')
      void set_font(const ::scoped_string & font) { m_font = font; }
      /// Get the currently active font
      ::string font() const { return m_font; }

      /// Get the label color
      ::color::color color() const { return m_color; }
      /// Set the label color
      void set_color(const ::color::color & color) { m_color = color; }

      /// Set the \::pointer Theme used to draw this pwidget
      virtual void set_theme(Theme * theme) override;

      /// Compute the size needed to fully display the label
      virtual size_i32 preferred_size(::nano2d::context * pcontext, bool bRecalcTextSize = true) override;

      /// Draw the label
      virtual void draw(::nano2d::context * pcontext) override;

      //void _nanoui_to_user(::user::interaction * puserinteraction) override;

};



} // namespace nanoui


