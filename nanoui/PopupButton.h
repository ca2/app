/*
    nanoui/popupbutton.h -- Button which launches a popup widget

    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The widget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/
/** \file */

#pragma once


#include "Button.h"
#include "Popup.h"


namespace nanoui
{


/**
 * \class PopupButton popupbutton.h nanoui/popupbutton.h
 *
 * \brief Button which launches a popup widget.
 *
 * \remark
 *     This class overrides \ref nanoui::Widget::mIconExtraScale to be ``0.8f``,
 *     which affects all subclasses of this Widget.  Subclasses must explicitly
 *     set a different value if needed (e.g., in their constructor).
 */
   class NANOUI_EXPORT PopupButton : public Button {
   public:
      
      ::write_text::font_pointer     m_pfontIcons;
      
      PopupButton(Widget * parent, const ::scoped_string & caption = "Untitled",
         int button_icon = 0);

      void set_chevron_icon(int icon) { m_chevron_icon = icon; }
      int chevron_icon() const { return m_chevron_icon; }

      void set_side(Popup::Side popup_side);
      Popup::Side side() const { return m_popup->side(); }

      Popup * popup() { return m_popup; }
      const Popup * popup() const { return m_popup; }

      virtual void draw(::nano2d::context * pcontext) override;
      virtual Vector2i preferred_size(::nano2d::context * pcontext, bool bRecalcTextSize = true) override;
      virtual void perform_layout(::nano2d::context * pcontext, bool bRecalcTextSize = true) override;
   protected:
      Popup * m_popup;
      int m_chevron_icon;
};



} // namespace nanoui


