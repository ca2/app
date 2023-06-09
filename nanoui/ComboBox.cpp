/*
    src/combobox.cpp -- simple combo box pwidget based on a popup button

    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The pwidget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/
#include "framework.h"
#include "ComboBox.h"
#include "VScrollPanel.h"
#include "Layout.h"
#include "acme/constant/source.h"
#include "acme/primitive/primitive/action_context.h"


namespace nanoui
{


   ComboBox::ComboBox(Widget* parent)
      : PopupButton(parent), m_container(popup()), m_iSelectedIndex(0) {
   }

   ComboBox::ComboBox(Widget* parent, const ::string_array& items)
      : PopupButton(parent), m_container(popup()), m_iSelectedIndex(0) {
      set_items(items);
   }

   ComboBox::ComboBox(Widget* parent, const ::string_array& items, const ::string_array& items_short)
      : PopupButton(parent), m_container(popup()), m_iSelectedIndex(0) {
      set_items(items, items_short);
   }


   void ComboBox::set_selected_index(::index iIndex, const ::action_context& actioncontext)
   {

      if (m_straItemsShort.empty())
      {

         return;

      }

      auto& children = m_container->children();

      ::pointer < Button > pbutton = children[m_iSelectedIndex];

      pbutton->set_checked(false, e_source_selection);

      pbutton->set_checked(true, actioncontext);

      m_iSelectedIndex = iIndex;

      set_caption(m_straItemsShort[iIndex]);

   }


   void ComboBox::set_items(const ::string_array& items, const ::string_array& items_short)
   {

      ASSERT(items.size() == items_short.size());

      m_straItems = items;
      m_straItemsShort = items_short;

      if (m_iSelectedIndex < 0 || m_iSelectedIndex >= (int)items.size())
         m_iSelectedIndex = 0;
      while (m_container->child_count() != 0)
         m_container->erase_child_at(m_container->child_count() - 1);

      if (m_scroll == nullptr && items.size() > 8) {
         m_scroll = memory_new VScrollPanel(m_ppopup);
         m_scroll->set_fixed_height(300);
         m_container = memory_new Widget(m_scroll);
         m_ppopup->set_layout(memory_new BoxLayout(e_orientation_horizontal, e_alignment_middle));
      }

      m_container->set_layout(memory_new GroupLayout(10));

      ::index iIndex = 0;
      for (const auto& str : items) {
         Button* button = memory_new Button(m_container, str);
         button->set_flags(Button::RadioButton);
         button->set_callback([&, iIndex] {
            m_iSelectedIndex = iIndex;
            set_caption(m_straItemsShort[iIndex]);
            set_checked(false, e_source_selection);
            popup()->set_visible(false);
            if (m_callback)
               m_callback(iIndex);
            });
         iIndex++;
      }

      set_selected_index(m_iSelectedIndex, e_source_sync);

   }


   bool ComboBox::scroll_event(const point_i32& p, const size_f32& rel)
   {

      set_checked(false, e_source_selection);
      popup()->set_visible(false);
      if (rel.cy() < 0) {
         set_selected_index(::minimum(m_iSelectedIndex + 1, (int)(items().size() - 1)), e_source_selection);
         if (m_callback)
            m_callback(m_iSelectedIndex);
         return true;
      }
      else if (rel.cy() > 0) {
         set_selected_index(::maximum(m_iSelectedIndex - 1, 0), e_source_user);
         if (m_callback)
            m_callback(m_iSelectedIndex);
         return true;
      }
      return Widget::scroll_event(p, rel);
   }



} // namespace nanoui


