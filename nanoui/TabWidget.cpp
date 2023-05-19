/*
    nanoui/tabwidget.cpp -- Widget for organizing multiple
    sub-widgets into tabs

    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The widget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/
#include "framework.h"
#include "Layout.h"
#include "TabWidget.h"
#include "Screen.h"
#include "Icons.h"
#include "Popup.h"
#include "Button.h"
#include "aura/user/user/interaction.h"
#include "nano2d/context.h"


namespace nanoui
{


TabWidgetBase::TabWidgetBase(Widget* parent, const ::scoped_string& scopedstrFont)
   : Widget(parent), m_font(scopedstrFont), m_background_color(::color::color(0.f, 0.f)) {
   m_tab_offsets.add(0);
}

void TabWidgetBase::remove_tab(int id) {
   int index = tab_index(id);
   bool close_active = index == m_active_tab;
   m_tab_captions.erase(m_tab_captions.begin() + index);
   m_tab_ids.erase(m_tab_ids.begin() + index);
   if (index <= m_active_tab)
      m_active_tab = ::maximum(0, m_active_tab - 1);
   m_callbackLayout = [this](::nano2d::context * pcontext)
   {
      perform_layout(pcontext);
   };
   if (m_close_callback)
      m_close_callback(id);
   if (close_active && m_callback) {
      m_callback(selected_id());
      update_visibility();
   }

   //screen()->m_puserinteraction->set_need_layout();

   set_need_redraw();

   post_redraw();

}

int TabWidgetBase::insert_tab(int index, const ::scoped_string& scopedstrCaption) {
   int id = m_tab_counter++;
   m_tab_captions.insert_at(index, scopedstrCaption);
   m_tab_ids.insert_at(index, id);
   //TabWidgetBase::perform_layout(screen()->::nano2d::_context());
   m_callbackLayout = [this](::nano2d::context * pcontext)
   {
      perform_layout(pcontext);
   };
   if (index < m_active_tab)
      m_active_tab++;
   if (m_tab_ids.size() == 1 && m_callback) {
      m_active_tab = 0;
      m_callback(id);
      update_visibility();
   }

   //screen()->m_puserinteraction->set_need_layout();

   set_need_redraw();

   post_redraw();

   return id;
}

int TabWidgetBase::append_tab(const ::scoped_string & caption) {
   return insert_tab((int)m_tab_captions.size(), caption);
}

int TabWidgetBase::tab_index(int id) const {
   for (::index i = 0; i < m_tab_ids.size(); ++i) {
      if (m_tab_ids[i] == id)
         return (int)i;
   }
   throw std::runtime_error("TabWidgetBase::tab_index(): not found!");
}

void TabWidgetBase::update_visibility() { /* No-op */ }

void TabWidgetBase::perform_layout(::nano2d::context * pcontext, bool bRecalcTextSize) {
   m_tab_offsets.clear();
   pcontext->font_face(m_font.c_str());
   pcontext->font_size(font_size());
   pcontext->text_align(::nano2d::e_align_left | ::nano2d::e_align_top);

   m_tab_offsets.clear();
   int width = 0;
   float unused[4];
   for (const ::scoped_string & label : m_tab_captions) {
      int label_width = (int)pcontext->text_bounds(0.f, 0.f, label.c_str(), unused);
      m_tab_offsets.add(width);
      width += label_width + 2 * m_theme->m_iHorizontalPaddingTabButton;
      if (m_tabs_closeable)
         width += m_close_width;
   }
   m_tab_offsets.add(width);

   pcontext->font_face("icons");
   m_close_width = (int)
      pcontext->text_bounds(0.f, 0.f, get_utf8_character(e_font_awesome_times_circle).data(), unused);
}

vector2_i32 TabWidgetBase::preferred_size(::nano2d::context * pcontext, bool bRecalcTextSize)
{
   pcontext->font_face(m_font.c_str());
   pcontext->font_size(font_size());
   pcontext->text_align(::nano2d::e_align_left | ::nano2d::e_align_top);

   int width = 0;
   for (const ::scoped_string & label : m_tab_captions) {
      float unused[4];
      int label_width = (int)pcontext->text_bounds(0, 0, label.c_str(), unused);
      width += label_width + 2 * m_theme->m_iHorizontalPaddingTabButton;
      if (m_tabs_closeable)
         width += m_close_width;
   }

   return vector2_i32(width + 1,
      (int)(font_size() + 2.f * m_theme->m_iVerticalPaddingTabButton + 2.f * m_padding));
}

void TabWidgetBase::draw(::nano2d::context * pcontext) {
   if (m_callbackLayout)
   {
      m_callbackLayout(pcontext);

      m_callbackLayout = nullptr;
      //m_bPendingLayout = false;
      //TabWidgetBase::perform_layout(pcontext);


   }
   if (m_tab_offsets.size() != m_tab_captions.size() + 1)
      throw std::runtime_error("Must run TabWidget::perform_layout() after adding/removing tabs!");

   int tab_height = (int)(font_size() + 2.f * m_theme->m_iVerticalPaddingTabButton);

   if (m_background_color.fa() != 0.f) {
      pcontext->fill_color(m_background_color);
      pcontext->begin_path();
      pcontext->rounded_rectangle(m_pos.x() + .5f, m_pos.y() + .5f + tab_height, (float)m_size.x(),
         m_size.y() - tab_height - 2.f, (float)m_theme->m_iButtonCornerRadius);
      pcontext->fill();
   }

   Widget::draw(pcontext);

   ::nano2d::paint tab_background_color = pcontext->linear_gradient(
      (float)m_pos.x(), m_pos.y() + 1.f, (float)m_pos.x(), (float)m_pos.y() + tab_height,
      m_theme->m_colorButtonGradientTopPushed, m_theme->m_colorButtonGradientBottomPushed);

   pcontext->save();
   pcontext->intersect_scissor((float)m_pos.x(), (float)m_pos.y(), (float)m_size.x(), (float)tab_height);
   pcontext->font_size(font_size());
   pcontext->text_align(::nano2d::e_align_left | ::nano2d::e_align_top);
   for (::index i = 0; i < m_tab_captions.size(); ++i) {
      int x_pos = m_pos.x() + m_tab_offsets[i],
         y_pos = m_pos.y(),
         width = m_tab_offsets[i + 1] - m_tab_offsets[i];

      if (i == (::index)m_active_tab) {
         pcontext->begin_path();
         pcontext->rounded_rectangle(x_pos + 0.5f, y_pos + 1.5f, (float)width,
            tab_height + 4.f, (float)m_theme->m_iButtonCornerRadius);
         pcontext->stroke_color(m_theme->m_colorBorderLight);
         pcontext->stroke();

         pcontext->begin_path();
         pcontext->rounded_rectangle(x_pos + 0.5f, y_pos + 0.5f, (float)width,
            tab_height + 4.f, (float)m_theme->m_iButtonCornerRadius);
         pcontext->stroke_color(m_theme->m_colorBorderDark);
         pcontext->stroke();
      }
      else {
         pcontext->begin_path();
         pcontext->rounded_rectangle(x_pos + 0.5f, y_pos + 1.5f, (float)width,
            tab_height + 4.f, (float)m_theme->m_iButtonCornerRadius);

         pcontext->fill_paint(tab_background_color);
         pcontext->fill();

         pcontext->stroke_color(m_theme->m_colorBorderDark);
         pcontext->stroke();
      }
      x_pos += m_theme->m_iHorizontalPaddingTabButton;
      y_pos += m_theme->m_iVerticalPaddingTabButton + 1;
      pcontext->fill_color(m_theme->m_colorText);
      pcontext->font_face(m_font.c_str());

      pcontext->text((float)x_pos, (float)y_pos, m_tab_captions[i]);

      if (m_tabs_closeable) {
         x_pos = m_pos.x() + m_tab_offsets[i + 1] -
            m_theme->m_iHorizontalPaddingTabButton - m_close_width + 5;
         pcontext->font_face("icons");
         pcontext->fill_color(i == (size_t)m_close_index_pushed ? m_theme->m_colorTextShadow
            : m_theme->m_colorText);
         bool highlight = m_close_index == (int)i;
         auto icon = highlight ? e_font_awesome_times_circle : e_font_awesome_times;
         float fs = font_size() * (highlight ? 1.f : .70f),
            offset_x = highlight ? 0.f : (fs * .40f),
            offset_y = highlight ? 0.f : (fs * .21f);
         pcontext->font_size(fs);
         pcontext->text(x_pos + offset_x, y_pos + offset_y + .5f, get_utf8_character(icon).data());
         pcontext->font_size(font_size());
      }
   }
   if (m_tab_drag_index != -1 && m_tab_drag_start != m_tab_drag_end) {
      int x_pos = m_pos.x() + m_tab_drag_min + m_tab_drag_end - m_tab_drag_start;
      pcontext->begin_path();
      pcontext->rounded_rectangle(x_pos + 0.5f, m_pos.y() + 1.5f, (float)(m_tab_drag_max - m_tab_drag_min),
         tab_height + 4.f, (float)m_theme->m_iButtonCornerRadius);
      pcontext->fill_color(::color::color(255, 255, 255, 30));
      pcontext->fill();
   }
   pcontext->restore();

   int x0 = m_tab_offsets[m_active_tab],
      x1 = m_tab_offsets[m_tab_offsets.size() > 1 ? m_active_tab + 1 : 0];
   for (int i = 1; i >= 0; --i) {
      /* Top border */
      pcontext->begin_path();
      pcontext->move_to(m_pos.x() + .5f, m_pos.y() + tab_height + i + .5f);
      pcontext->line_to(m_pos.x() + x0 + 1.0f, m_pos.y() + tab_height + i + .5f);
      pcontext->move_to((float)(m_pos.x() + x1), m_pos.y() + tab_height + i + .5f);
      pcontext->line_to(m_pos.x() + m_size.x() + .5f, m_pos.y() + tab_height + i + .5f);
      pcontext->stroke_width(1.0f);
      pcontext->stroke_color((i == 0) ? m_theme->m_colorBorderDark : m_theme->m_colorBorderLight);
      pcontext->stroke();

      /* Bottom + side borders */
      pcontext->save();
      pcontext->intersect_scissor((float)m_pos.x(), (float)(m_pos.y() + tab_height), (float)m_size.x(), (float)m_size.y());
      pcontext->begin_path();
      pcontext->rounded_rectangle(m_pos.x() + .5f, m_pos.y() + i + .5f, m_size.x() - 1.f,
         m_size.y() - 2.f, (float)m_theme->m_iButtonCornerRadius);
      pcontext->stroke();
      pcontext->restore();
   }
}

std::pair<int, bool> TabWidgetBase::tab_at_position(const vector2_i32& p, bool test_vertical) const {
   int tab_height = (int)font_size() + 2 * m_theme->m_iVerticalPaddingTabButton;
   if (test_vertical && (p.y() <= m_pos.y() || p.y() > m_pos.y() + tab_height))
      return { -1, false };

   int x = p.x() - m_pos.x();
   for (::index i = 0; i < m_tab_offsets.size() - 1; ++i) {
      if (x >= m_tab_offsets[i] && x < m_tab_offsets[i + 1]) {
         int r = m_tab_offsets[i + 1] - x;
         return {
             (int)i, m_tabs_closeable &&
                r < m_theme->m_iHorizontalPaddingTabButton + m_close_width - 4 &&
                r > m_theme->m_iHorizontalPaddingTabButton - 4 &&
                p.y() - m_pos.y() > m_theme->m_iVerticalPaddingTabButton &&
                p.y() - m_pos.y() <= tab_height - m_theme->m_iVerticalPaddingTabButton
         };
      }
   }
   return { -1, false };
}

bool TabWidgetBase::mouse_button_event(const vector2_i32& p, ::user::e_mouse emouse, bool down, bool bDoubleClick, const ::user::e_key& ekeyModifiers)
{
   int index; bool close;
   std::tie(index, close) = tab_at_position(p);
   bool handled = false;

   Screen* screen = this->screen();
   if (m_popup) {
      m_popup->mouse_button_event(
         p - m_pos + absolute_position() - m_popup->absolute_position() + m_popup->position(),emouse, down, bDoubleClick, ekeyModifiers);
      screen->update_focus(this);
      screen->remove_child(m_popup);
      m_popup = nullptr;
      handled = true;
   }

   bool drag_in_progress = m_tab_drag_index != -1 && m_tab_drag_start != m_tab_drag_end;
   if (m_popup_callback && emouse == ::user::e_mouse_right_button && down && index != -1 &&
      !drag_in_progress) {
      m_popup = m_popup_callback(tab_id(index), screen);
      m_popup->set_position(p + vector2_i32(8, -6));
      m_popup->set_anchor_offset(8);
      m_popup->set_anchor_size(8);
      if (m_popup->layout() == nullptr)
         m_popup->set_layout(memory_new GroupLayout(5, 3));
      for (Widget* w : m_popup->children()) {
         Button* b = dynamic_cast<Button*>(w);
         if (!b)
            continue;
         b->set_icon_position(Button::IconPosition::Right);
         b->set_flags(Button::ContextMenuButton);
      }
      m_popup->m_callbackLayout = [this](::nano2d::context * pcontext)
      {
         m_popup->set_size(m_popup->preferred_size(pcontext) + vector2_i32(40, 0));
         m_popup->perform_layout(pcontext);
      };

      set_need_layout();

      set_need_redraw();

      post_redraw();

      //m_bPendingSizing = true;
      //m_bPendingLayout = true;
      handled = true;
   }

   if (emouse == ::user::e_mouse_left_button && m_popup == nullptr) {
      if (index >= 0) {
         if (close && m_tab_drag_index == -1) {
            if (down) {
               m_close_index_pushed = index;
            }
            else if (m_close_index == m_close_index_pushed) {
               remove_tab(tab_id(index));
               mouse_motion_event(p, vector2_i32(0), false, ::user::e_key_none);
            }
         }
         else {
            if (down) {
               bool tab_changed = m_active_tab != index;
               m_active_tab = index;
               m_tab_drag_index = m_tabs_draggable ? index : -1;
               m_tab_drag_start = m_tab_drag_end = p.x();
               m_tab_drag_min = m_tab_offsets[index];
               m_tab_drag_max = m_tab_offsets[index + 1];
               m_close_index_pushed = -1;
               if (tab_changed && m_callback) {
                  m_callback(selected_id());
                  update_visibility();
               }
            }
            else if (m_tab_drag_index != -1) {
               m_tab_drag_index = -1;
               mouse_motion_event(p, vector2_i32(0), false, ::user::e_key_none);
            }
         }
         handled = true;
      }

      if (!down) {
         handled = m_close_index_pushed != -1 || m_tab_drag_index != -1;
         m_close_index_pushed = -1;
         m_tab_drag_index = -1;
      }

      handled = true;
   }

   handled |= Widget::mouse_button_event(p, emouse, down, bDoubleClick, ekeyModifiers);

   return handled;

}


bool TabWidgetBase::mouse_enter_event(const vector2_i32&/* p */, bool /* enter */, const ::user::e_key&)
{

   if (m_tabs_closeable && m_close_index >= 0)
   {
      m_close_index = -1;
      m_close_index_pushed = -1;
      return true;
   }
   return false;

}


bool TabWidgetBase::mouse_motion_event(const vector2_i32& p, const vector2_i32& rel, bool bDown, const ::user::e_key& ekeyModifiers)
{

   auto [index, close] = tab_at_position(p, false);

   if (m_tab_drag_index != -1) {
      m_tab_drag_end = p.x();
      if (index != -1 && m_tab_drag_index != index) {
         int i0 = std::min(m_tab_drag_index, index),
            i1 = std::max(m_tab_drag_index, index);
         int mid = (m_tab_offsets[i0] + m_tab_offsets[i1 + 1]) / 2;
         if ((m_tab_drag_index < index && p.x() - m_pos.y() > mid) ||
            (m_tab_drag_index > index && p.x() - m_pos.y() < mid)) {
            std::swap(m_tab_captions[index], m_tab_captions[m_tab_drag_index]);
            std::swap(m_tab_ids[index], m_tab_ids[m_tab_drag_index]);
            //TabWidgetBase::perform_layout(screen()->::nano2d::_context());
            m_callbackLayout = [this](::nano2d::context * pcontext)
            {

               TabWidgetBase::perform_layout(pcontext);

            };
            m_tab_drag_index = index;
            m_active_tab = index;

            set_need_layout();

            set_need_redraw();

            post_redraw();

         }

      }

      return true;

   }

   if (!close)
      index = -1;

   if (index != m_close_index) {
      m_close_index = index;
      m_close_index_pushed = -1;
      return true;
   }

   return Widget::mouse_motion_event(p, rel, bDown, ekeyModifiers);

}


TabWidget::TabWidget(Widget* parent, const ::scoped_string & font)
   : TabWidgetBase(parent, font) { }

void TabWidget::perform_layout(::nano2d::context * pcontext, bool bRecalcTextSize) {
   TabWidgetBase::perform_layout(pcontext, bRecalcTextSize);

   int tab_height = (int)font_size() + 2 * m_theme->m_iVerticalPaddingTabButton;

   for (Widget* child : m_children) {
      child->set_position(vector2_i32(m_padding, m_padding + tab_height + 1));
      child->set_size(m_size - vector2_i32(2 * m_padding, 2 * m_padding + tab_height + 1));
      child->perform_layout(pcontext, bRecalcTextSize);
   }
}

void TabWidget::update_visibility() {
   if (tab_count() == 0)
      return;
   for (Widget* child : m_children)
      child->set_visible(false);
   auto it = m_widgets.find(selected_id());
   if (it != m_widgets.end())
      it->second->set_visible(true);
}

vector2_i32 TabWidget::preferred_size(::nano2d::context * pcontext, bool bRecalcTextSize) {
   vector2_i32 base_size = TabWidgetBase::preferred_size(pcontext, bRecalcTextSize),
      content_size = vector2_i32(0);
   for (Widget* child : m_children)
      content_size = max(content_size, child->preferred_size(pcontext, bRecalcTextSize));

   return vector2_i32(
      std::max(base_size.x(), content_size.x() + 2 * m_padding),
      base_size.y() + content_size.y() + 2 * m_padding
   );
}

int TabWidget::insert_tab(int index, const ::scoped_string & caption, Widget* widget) {
   int id = TabWidgetBase::insert_tab(index, caption);
   m_widgets[id] = widget;
   update_visibility();
   return id;
}

int TabWidget::append_tab(const ::scoped_string & caption, Widget* widget) {
   widget->set_visible(false);
   int id = TabWidgetBase::append_tab(caption);
   m_widgets[id] = widget;
   update_visibility();
   return id;
}

void TabWidget::remove_tab(int id) {
   TabWidgetBase::remove_tab(id);
   Widget* widget = m_widgets[id];
   m_widgets.erase(id);
   if (m_remove_children)
      remove_child(widget);
}



} // namespace nanoui


