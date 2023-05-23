/*
    nanoui/popupbutton.h -- Button which launches a popup pwidget

    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The pwidget drawing code is based on the NanoVG demo application
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
    * \brief Button which launches a popup pwidget.
    *
    * \remark
    *     This class overrides \ref nanoui::Widget::mIconExtraScale to be ``0.8f``,
    *     which affects all subclasses of this Widget.  Subclasses must explicitly
    *     set a different value if needed (e.g., in their constructor).
    */
   class CLASS_DECL_NANOUI PopupButton :
      public Button
   {
   public:


      ::write_text::font_pointer       m_pfontIcons;
      Popup *                          m_ppopup;
      enum_font_awesome                m_efontawesomeChevron;


      PopupButton(Widget* parent, const ::scoped_string& caption = "Untitled", int button_icon = 0);


      void set_chevron_icon(enum_font_awesome efontawesome) { m_efontawesomeChevron = efontawesome; }
      int chevron_icon() const { return m_efontawesomeChevron; }

      void set_side(Popup::Side popup_side);
      Popup::Side side() const { return m_ppopup->side(); }

      Popup* popup() { return m_ppopup; }
      const Popup* popup() const { return m_ppopup; }

      virtual void draw(::nano2d::context* pcontext) override;
      virtual vector2_i32 preferred_size(::nano2d::context* pcontext, bool bRecalcTextSize = true) override;
      virtual void perform_layout(::nano2d::context* pcontext, bool bRecalcTextSize = true) override;


   };



} // namespace nanoui


