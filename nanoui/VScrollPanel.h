/*
    nanoui/vscrollpanel.h -- Adds a vertical scrollbar around a widget
    that is too big to fit into a certain area

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
 * \class VScrollPanel vscrollpanel.h nanoui/vscrollpanel.h
 *
 * \brief Adds a vertical scrollbar around a widget that is too big to fit into
 *        a certain area.
 */
   class NANOUI_EXPORT VScrollPanel : public Widget {
   public:

      
      bool m_bDrag;


      VScrollPanel(Widget * parent);

      /**
       * Return the current scroll amount as a value between 0 and 1. 0 means
       * scrolled to the top and 1 to the bottom.
       */
      float scroll() const { return m_scroll; }

      /**
       * Set the scroll amount to a value between 0 and 1. 0 means scrolled to
       * the top and 1 to the bottom.
       */
      void set_scroll(float scroll) { m_scroll = scroll; }

      virtual void perform_layout(::nano2d::context * pcontext, bool bRecalcTextSize = true) override;
      virtual Vector2i preferred_size(::nano2d::context * pcontext, bool bRecalcTextSize = true) override;
      virtual bool mouse_button_event(const Vector2i & p, ::user::e_mouse emouse, bool down, const ::user::e_key & ekeyModifiers) override;
      virtual bool mouse_drag_event(const Vector2i & p, const Vector2i & rel, const ::user::e_key & ekeyModifiers) override;
      virtual bool scroll_event(const Vector2i & p, const Vector2f & rel) override;
      virtual void draw(::nano2d::context * pcontext) override;
      virtual float get_y_offset() const;
      virtual float get_track_bar_height() const;
      int m_child_preferred_height;
      float m_scroll;
      bool m_update_layout;
};



} // namespace nanoui


