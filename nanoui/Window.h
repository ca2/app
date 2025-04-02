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
      ::pointer_array<PopupButton>     m_popupbuttona;
      bool                             m_bPendingCentering;
      ::float_rectangle                  m_boundsHeader;
      ::string                         m_title;
      ::pointer< Widget >              m_button_panel;
      bool                             m_bModal;
      bool                             m_bDrag;
      ::int_point                      m_pointDragStartCursor;
      ::int_point                      m_pointDragStartPosition;
      ::int_point                      m_pointLastDragPosition;
      

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

   void _center(::nano2d::context  * pcontext);

   /// Draw the window
   virtual void draw(::nano2d::context  * pcontext) override;
   /// Handle mouse enter/leave happenings
   virtual bool mouse_enter_event(const int_point & p, bool enter, const ::user::e_key & ekeyModifiers) override;
   /// Handle window drag happenings
   //virtual bool mouse_drag_event(const sequence2_int & p, const sequence2_int & rel, const ::user::e_key & ekeyModifiers) override;
   virtual bool mouse_motion_event(const int_point& p, const int_size& rel, bool bDown, const ::user::e_key& ekeyModifiers) override;
   /// Handle mouse happenings recursively and bring the current window to the top
   virtual bool mouse_button_event(const int_point & p, ::user::e_mouse emouse, bool down, bool bDoubleClick, const ::user::e_key & ekeyModifiers) override;
   /// Accept scroll happenings and propagate them to the pwidget under the mouse cursor
      
      void on_begin_draw(::nano2d::context  * pcontext) override;
            
   virtual bool scroll_event(const int_point & p, const float_size & rel) override;
   /// Compute the preferred size of the pwidget
   virtual int_size preferred_size(::nano2d::context  * pcontext, bool bRecalcTextSize = true) override;
   /// Invoke the associated layout generator to properly place pwidgetChild widgets, if any
   virtual void perform_layout(::nano2d::context  * pcontext, bool bRecalcTextSize = true) override;
   //protected:
   /// Internal helper function to maintain nested window position values; overridden in \::pointer Popup
   virtual void refresh_relative_placement();
      
      void on_destroy_window() override;
   //protected:


      //void _nanoui_to_user(::user::interaction * puserinteraction) override;


   };


} // namespace nanoui



