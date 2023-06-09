/*
    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The pwidget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/
/**
 * \file nanoui/combobox.h
 *
 * \brief Simple combo box pwidget based on a popup button.
 */

#pragma once



#include "PopupButton.h"


 //#include <nanoui/popupbutton.h>

namespace nanoui
{


   /**
    * \class ComboBox combobox.h nanoui/combobox.h
    *
    * \brief Simple combo box pwidget based on a popup button.
    */
   class CLASS_DECL_NANOUI ComboBox : public PopupButton
   {
   public:


      /// Scroll panel used to store the combo box contents
      VScrollPanel* m_scroll = nullptr;

      /// Container containing the buttons
      Widget* m_container = nullptr;

      /// The items associated with this ComboBox.
      ::string_array m_straItems;

      /// The short descriptions of items associated with this ComboBox.
      ::string_array m_straItemsShort;

      /// The callback for this ComboBox.
      ::function<void(::index)> m_callback;

      /// The current iIndex this ComboBox has selected.
      ::index m_iSelectedIndex;


      /// Create an empty combo box
      ComboBox(Widget* parent);

      /// Create a memory_new combo box with the given items
      ComboBox(Widget* parent, const ::string_array& items);

      /**
       * \brief Create a memory_new combo box with the given items, providing both short and
       * long descriptive labels for each item
       */
      ComboBox(Widget* parent, const ::string_array& items,
         const ::string_array& items_short);

      /// The current iIndex this ComboBox has selected.
      ::index selected_index() const { return m_iSelectedIndex; }

      /// Sets the current iIndex this ComboBox has selected.
      void set_selected_index(::index iIndex, const ::action_context& actioncontext);

      /// The callback to execute for this ComboBox.
      ::function<void(::index)> callback() const { return m_callback; }

      /// Sets the callback to execute for this ComboBox.
      void set_callback(const ::function<void(::index)>& callback) { m_callback = callback; }

      /// Sets the items for this ComboBox, providing both short and long descriptive lables for each item.
      void set_items(const ::string_array& items, const ::string_array& items_short);
      /// Sets the items for this ComboBox.
      void set_items(const ::string_array& items) { set_items(items, items); }
      /// The items associated with this ComboBox.
      const ::string_array& items() const { return m_straItems; }
      /// The short descriptions associated with this ComboBox.
      const ::string_array& items_short() const { return m_straItemsShort; }

      /// Handles mouse scrolling events for this ComboBox.
      virtual bool scroll_event(const point_i32& p, const size_f32& rel) override;

   };



} // namespace nanoui


