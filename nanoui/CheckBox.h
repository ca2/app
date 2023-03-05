﻿/*
    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The widget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/
/**
 * \file nanoui/m_pcheckbox.h
 *
 * \brief Two-state check box Widget.
 */
#pragma once


#include "Widget.h"


namespace nanoui
{


/**
 * \class CheckBox m_pcheckbox.h nanoui/m_pcheckbox.h
 *
 * \brief Two-state check box widget.
 *
 * \remark
 *     This class overrides \ref nanoui::Widget::mIconExtraScale to be ``1.2f``,
 *     which affects all subclasses of this Widget.  Subclasses must explicitly
 *     set a different value if needed (e.g., in their constructor).
 */
   class CLASS_DECL_NANOUI CheckBox : public Widget {
   public:

      /// The caption text of this CheckBox.
      ::string m_caption;
      /**
       * Internal tracking variable to distinguish between mouse click and release.
       * \ref nanoui::CheckBox::m_callback is only called upon release.  See
       * \ref nanoui::CheckBox::mouse_button_event for specific conditions.
       */
      bool m_bMouseDown;

      /// Whether or not this CheckBox is currently checked or unchecked.
      bool m_checked;

      /// The function to execute when \ref nanoui::CheckBox::m_checked is changed.
      ::function<void(bool)> m_callback;

      Vector2i m_sizePreferred;

      /**
       * Adds a CheckBox to the specified ``parent``.
       *
       * \param parent
       *     The Widget to add this CheckBox to.
       *
       * \param caption
       *     The caption text of the CheckBox (default ``"Untitled"``).
       *
       * \param callback
       *     If provided, the callback to execute when the CheckBox is checked or
       *     unchecked.  Default parameter function does nothing.  See
       *     \ref nanoui::CheckBox::mPushed for the difference between "pushed"
       *     and "checked".
       */
      CheckBox(Widget * parent, const ::scoped_string & caption = "Untitled",
         const ::function<void(bool)> & callback = ::function<void(bool)>());

      /// The caption of this CheckBox.
      ::string caption() const { return m_caption; }

      /// Sets the caption of this CheckBox.
      void set_caption(const ::scoped_string & caption) { m_caption = caption; }

      /// Whether or not this CheckBox is currently checked.
      bool checked() const { return m_checked; }

      /// Sets whether or not this CheckBox is currently checked.
      void set_checked(bool bChecked) { m_checked = bChecked; }

      /// Whether or not this CheckBox is currently pushed.  See \ref nanoui::CheckBox::m_pushed.
      bool is_mouse_down() const { return m_bMouseDown; }
      void set_mouse_down(bool bMouseDown) { m_bMouseDown = bMouseDown; }

      /// Returns the current callback of this CheckBox.
      ::function<void(bool)> callback() const { return m_callback; }

      /// Sets the callback to be executed when this CheckBox is checked / unchecked.
      void set_callback(const ::function<void(bool)> & callback) { m_callback = callback; }

      /// Mouse button event processing for this check box
      virtual bool mouse_button_event(const Vector2i & p, ::user::e_mouse emouse, bool down, const ::user::e_key & ekeyModifiers) override;

      /// The preferred size of this CheckBox.
      virtual Vector2i preferred_size(::nano2d::context * pcontext, bool bRecalcTextSize = true) override;

      /// Draws this CheckBox.
      virtual void draw(::nano2d::context * pcontext) override;
};



} // namespace nanoui

