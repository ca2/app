﻿/*
    nanoui/window.h -- Top-level window widget

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
 * \class Window window.h nanoui/window.h
 *
 * \brief Top-level window widget.
 */
   class CLASS_DECL_NANOUI Window : public Widget {
   public:

      ::pointer<::user::box>          m_pbox;
      bool                             m_bPendingCentering;
      float                            m_boundsHeader[4];

      Window(Widget * parent, const ::scoped_string & title = "Untitled");

      /// Return the window title
      ::string title() const { return m_title; }
      /// Set the window title
      void set_title(const ::scoped_string & title) { m_title = title; }

      /// Is this a model dialog?
      bool modal() const { return m_modal; }
      /// Set whether or not this is a modal dialog
      void set_modal(bool modal) { m_modal = modal; }

   /// Return the panel used to house window buttons
   Widget * button_panel();

   /// Dispose the window
   void dispose();

   /// Center the window in the current \ref Screen
   void center() { m_bPendingCentering = true; }

   void _center(::nano2d::context * pcontext);

   /// Draw the window
   virtual void draw(::nano2d::context * pcontext) override;
   /// Handle mouse enter/leave events
   virtual bool mouse_enter_event(const Vector2i & p, bool enter, const ::user::e_key & ekeyModifiers) override;
   /// Handle window drag events
   virtual bool mouse_drag_event(const Vector2i & p, const Vector2i & rel, const ::user::e_key & ekeyModifiers) override;
   /// Handle mouse events recursively and bring the current window to the top
   virtual bool mouse_button_event(const Vector2i & p, ::user::e_mouse emouse, bool down, const ::user::e_key & ekeyModifiers) override;
   /// Accept scroll events and propagate them to the widget under the mouse cursor
      
      void on_begin_draw(::nano2d::context * pcontext) override;
            
   virtual bool scroll_event(const Vector2i & p, const Vector2f & rel) override;
   /// Compute the preferred size of the widget
   virtual Vector2i preferred_size(::nano2d::context * pcontext, bool bRecalcTextSize = true) override;
   /// Invoke the associated layout generator to properly place child widgets, if any
   virtual void perform_layout(::nano2d::context * pcontext, bool bRecalcTextSize = true) override;
   //protected:
   /// Internal helper function to maintain nested window position values; overridden in \ref Popup
   virtual void refresh_relative_placement();
      
      
   //protected:
      ::string m_title;
     Widget * m_button_panel;
      bool m_modal;
      bool m_drag;


      //void _nanoui_to_user(::user::interaction * puserinteraction) override;


};



} // namespace nanoui

