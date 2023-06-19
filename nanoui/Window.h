/*
    nanoui/window.h -- Top-level window pwidget

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
 * \class Window window.h nanoui/window.h
 *
 * \brief Top-level window pwidget.
 */
   class CLASS_DECL_NANOUI Window :
      public Widget
   {
   public:

      
      ::pointer<::user::box>           m_pbox;
      bool                             m_bPendingCentering;
      float                            m_boundsHeader[4];
      ::string                         m_title;
      Widget *                         m_button_panel;
      bool                             m_bModal;
      bool                             m_bDrag;
      ::point_i32                      m_pointDragStartCursor;
      ::point_i32                      m_pointDragStartPosition;
      ::point_i32                      m_pointLastDragPosition;
      

      Window(Widget * parent, const ::scoped_string & title = "Untitled");

      /// Return the window title
      ::string title() const { return m_title; }
      /// Set the window title
      void set_title(const ::scoped_string & title) { m_title = title; }

      /// Is this a model dialog?
      bool modal() const { return m_bModal; }
      /// Set whether or not this is a modal dialog
      void set_modal(bool bModal) { m_bModal = bModal; }

   /// Return the panel used to house window buttons
   Widget * button_panel();

   /// Dispose the window
   void dispose();

   /// Center the window in the current \::pointer Screen
   void center() { m_bPendingCentering = true; }

   void _center(::nano2d::context * pcontext);

   /// Draw the window
   virtual void draw(::nano2d::context * pcontext) override;
   /// Handle mouse enter/leave events
   virtual bool mouse_enter_event(const point_i32 & p, bool enter, const ::user::e_key & ekeyModifiers) override;
   /// Handle window drag events
   //virtual bool mouse_drag_event(const sequence2_i32 & p, const sequence2_i32 & rel, const ::user::e_key & ekeyModifiers) override;
   virtual bool mouse_motion_event(const point_i32& p, const size_i32& rel, bool bDown, const ::user::e_key& ekeyModifiers) override;
   /// Handle mouse events recursively and bring the current window to the top
   virtual bool mouse_button_event(const point_i32 & p, ::user::e_mouse emouse, bool down, bool bDoubleClick, const ::user::e_key & ekeyModifiers) override;
   /// Accept scroll events and propagate them to the pwidget under the mouse cursor
      
      void on_begin_draw(::nano2d::context * pcontext) override;
            
   virtual bool scroll_event(const point_i32 & p, const size_f32 & rel) override;
   /// Compute the preferred size of the pwidget
   virtual size_i32 preferred_size(::nano2d::context * pcontext, bool bRecalcTextSize = true) override;
   /// Invoke the associated layout generator to properly place pwidgetChild widgets, if any
   virtual void perform_layout(::nano2d::context * pcontext, bool bRecalcTextSize = true) override;
   //protected:
   /// Internal helper function to maintain nested window position values; overridden in \::pointer Popup
   virtual void refresh_relative_placement();
      
      
   //protected:


      //void _nanoui_to_user(::user::interaction * puserinteraction) override;


   };


} // namespace nanoui



