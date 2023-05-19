/*
    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The widget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/
/**
 * \file nanoui/combobox.h
 *
 * \brief Simple combo box widget based on a popup button.
 */

#pragma once



#include "PopupButton.h"


//#include <nanoui/popupbutton.h>

namespace nanoui
{


/**
 * \class ComboBox combobox.h nanoui/combobox.h
 *
 * \brief Simple combo box widget based on a popup button.
 */
   class CLASS_DECL_NANOUI ComboBox : public PopupButton {
   public:
      /// Create an empty combo box
      ComboBox(Widget * parent);

      /// Create a memory_new combo box with the given items
      ComboBox(Widget * parent, const ::array<::string> & items);

      /**
       * \brief Create a memory_new combo box with the given items, providing both short and
       * long descriptive labels for each item
       */
      ComboBox(Widget * parent, const ::array<::string> & items,
         const ::array<::string> & items_short);

      /// The current index this ComboBox has selected.
      int selected_index() const { return m_selected_index; }

      /// Sets the current index this ComboBox has selected.
      void set_selected_index(int idx, const ::action_context & actioncontext);

      /// The callback to execute for this ComboBox.
      ::function<void(int)> callback() const { return m_callback; }

      /// Sets the callback to execute for this ComboBox.
      void set_callback(const ::function<void(int)> & callback) { m_callback = callback; }

      /// Sets the items for this ComboBox, providing both short and long descriptive lables for each item.
      void set_items(const ::array<::string> & items, const ::array<::string> & items_short);
      /// Sets the items for this ComboBox.
      void set_items(const ::array<::string> & items) { set_items(items, items); }
      /// The items associated with this ComboBox.
      const ::array<::string> & items() const { return m_items; }
      /// The short descriptions associated with this ComboBox.
      const ::array<::string> & items_short() const { return m_items_short; }

      /// Handles mouse scrolling events for this ComboBox.
      virtual bool scroll_event(const vector2_i32 & p, const vector2_f32 & rel) override;
   protected:
      /// Scroll panel used to store the combo box contents
      VScrollPanel * m_scroll = nullptr;

      /// Container containing the buttons
      Widget * m_container = nullptr;

      /// The items associated with this ComboBox.
      ::array<::string> m_items;

      /// The short descriptions of items associated with this ComboBox.
      ::array<::string> m_items_short;

      /// The callback for this ComboBox.
      ::function<void(int)> m_callback;

      /// The current index this ComboBox has selected.
      int m_selected_index;
};



} // namespace nanoui


