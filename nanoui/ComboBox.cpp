/*
    src/combobox.cpp -- simple combo box widget based on a popup button

    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The widget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/
#include "framework.h"
#include "ComboBox.h"
#include "VScrollPanel.h"
#include "Layout.h"


namespace nanoui
{


ComboBox::ComboBox(Widget * parent)
   : PopupButton(parent), m_container(popup()), m_selected_index(0) {
}

ComboBox::ComboBox(Widget * parent, const ::array<::string> & items)
   : PopupButton(parent), m_container(popup()), m_selected_index(0) {
   set_items(items);
}

ComboBox::ComboBox(Widget * parent, const ::array<::string> & items, const ::array<::string> & items_short)
   : PopupButton(parent), m_container(popup()), m_selected_index(0) {
   set_items(items, items_short);
}

void ComboBox::set_selected_index(int idx) {
   if (m_items_short.empty())
      return;
   const ::array<Widget *> & children = m_container->children();
   ((Button *)children[m_selected_index])->set_check(false);
   ((Button *)children[idx])->set_check(true);
   m_selected_index = idx;
   set_caption(m_items_short[idx]);
}

void ComboBox::set_items(const ::array<::string> & items, const ::array<::string> & items_short) {
   assert(items.size() == items_short.size());
   m_items = items;
   m_items_short = items_short;

   if (m_selected_index < 0 || m_selected_index >= (int)items.size())
      m_selected_index = 0;
   while (m_container->child_count() != 0)
      m_container->remove_child_at(m_container->child_count() - 1);

   if (m_scroll == nullptr && items.size() > 8) {
      m_scroll = memory_new VScrollPanel(m_ppopup);
      m_scroll->set_fixed_height(300);
      m_container = memory_new Widget(m_scroll);
      m_ppopup->set_layout(memory_new BoxLayout(e_orientation_horizontal, e_alignment_middle));
   }

   m_container->set_layout(memory_new GroupLayout(10));

   int index = 0;
   for (const auto & str : items) {
      Button * button = memory_new Button(m_container, str);
      button->set_flags(Button::RadioButton);
      button->set_callback([&, index] {
         m_selected_index = index;
         set_caption(m_items_short[index]);
         set_check(false);
         popup()->set_visible(false);
         if (m_callback)
            m_callback(index);
         });
      index++;
   }
   set_selected_index(m_selected_index);
}

bool ComboBox::scroll_event(const Vector2i & p, const Vector2f & rel) {
   set_check(false);
   popup()->set_visible(false);
   if (rel.y() < 0) {
      set_selected_index(std::min(m_selected_index + 1, (int)(items().size() - 1)));
      if (m_callback)
         m_callback(m_selected_index);
      return true;
   }
   else if (rel.y() > 0) {
      set_selected_index(std::max(m_selected_index - 1, 0));
      if (m_callback)
         m_callback(m_selected_index);
      return true;
   }
   return Widget::scroll_event(p, rel);
}



} // namespace nanoui


