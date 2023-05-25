/*
    nanoui/vscrollpanel.h -- Adds a vertical scrollbar around a pwidget
    that is too big to fit into a certain area

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
    * \class VScrollPanel vscrollpanel.h nanoui/vscrollpanel.h
    *
    * \brief Adds a vertical scrollbar around a pwidget that is too big to fit into
    *        a certain area.
    */
   class CLASS_DECL_NANOUI VScrollPanel : public Widget {
   public:


      bool        m_bDrag;
      float       m_fTotalHeight;
      float       m_fScroll;
      bool        m_update_layout;


      VScrollPanel(Widget* parent);

      /**
       * Return the current scroll amount as a value between 0 and 1. 0 means
       * scrolled to the top and 1 to the bottom.
       */
      float scroll() const { return m_fScroll; }

      /**
       * Set the scroll amount to a value between 0 and 1. 0 means scrolled to
       * the top and 1 to the bottom.
       */
      void set_scroll(float fScroll) { m_fScroll = fScroll; }


      virtual float y_coordinate_vertical_scroll(int y);

      virtual void perform_layout(::nano2d::context* pcontext, bool bRecalcTextSize = true) override;
      virtual vector2_i32 preferred_size(::nano2d::context* pcontext, bool bRecalcTextSize = true) override;
      virtual bool mouse_button_event(const vector2_i32& p, ::user::e_mouse emouse, bool down, bool bDoubleClick, const ::user::e_key& ekeyModifiers) override;
      virtual bool mouse_motion_event(const vector2_i32& p, const vector2_i32& rel, bool bDown, const ::user::e_key& ekeyModifiers) override;
      //virtual bool mouse_drag_event(const vector2_i32 & p, const vector2_i32 & rel, const ::user::e_key & ekeyModifiers) override;
      virtual bool scroll_event(const vector2_i32& p, const vector2_f32& rel) override;
      virtual void draw(::nano2d::context* pcontext) override;
      vector2_i32 get_scroll_offset() const override;

      virtual float get_track_bar_height() const;


   };



} // namespace nanoui


