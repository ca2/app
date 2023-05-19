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
#include "acme/constant/source.h"
#include "acme/primitive/primitive/action_context.h"


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


void ComboBox::set_selected_index(int idx, const ::action_context& actioncontext)
{
   if (m_items_short.empty())
      return;
   const ::array<Widget *> & children = m_container->children();
   ((Button *)children[m_selected_index])->set_checked(false, e_source_selection);
   ((Button *)children[idx])->set_checked(true, actioncontext);
   m_selected_index = idx;
   set_caption(m_items_short[idx]);
}


void ComboBox::set_items(const ::array<::string> & items, const ::array<::string> & items_short) 
{
   
   ASSERT(items.size() == items_short.size());

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
      m_ppopup->set_layout(memory_new BoxLayout(Orientation::Horizontal, enum_alignment::Middle));
   }

   m_container->set_layout(memory_new GroupLayout(10));

   int index = 0;
   for (const auto & str : items) {
      Button * button = memory_new Button(m_container, str);
      button->set_flags(Button::RadioButton);
      button->set_callback([&, index] {
         m_selected_index = index;
         set_caption(m_items_short[index]);
         set_checked(false, e_source_selection);
         popup()->set_visible(false);
         if (m_callback)
            m_callback(index);
         });
      index++;
   }

   set_selected_index(m_selected_index, e_source_sync);

}


bool ComboBox::scroll_event(const vector2_i32 & p, const vector2_f32 & rel)
{

   set_checked(false, e_source_selection);
   popup()->set_visible(false);
   if (rel.y() < 0) {
      set_selected_index(::minimum(m_selected_index + 1, (int)(items().size() - 1)), e_source_selection);
      if (m_callback)
         m_callback(m_selected_index);
      return true;
   }
   else if (rel.y() > 0) {
      set_selected_index(std::max(m_selected_index - 1, 0), e_source_user);
      if (m_callback)
         m_callback(m_selected_index);
      return true;
   }
   return Widget::scroll_event(p, rel);
}



} // namespace nanoui


