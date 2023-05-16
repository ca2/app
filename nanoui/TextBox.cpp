/*
    src/textbox.cpp -- Fancy text box with builtin regular
    expression-based validation

    The text box widget was contributed by Christian Schueller.

    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The widget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/
#include "framework.h"
#include "TextBox.h"
#include <regex>
#include "acme/constant/message.h"
#include "aura/platform/session.h"
#include "aura/windowing/window.h"
#include "aura/user/user/copydesk.h"
#include "nano2d/context.h"



namespace nanoui
{


   TextBox::TextBox(Widget* parent, const ::scoped_string& value)
      : Widget(parent),
      m_editable(false),
      m_spinnable(false),
      m_committed(true),
      m_value(value),
      m_default_value(""),
      m_alignment(Alignment::Center),
      m_units(""),
      m_format(""),
      m_units_image(-1),
      m_valid_format(true),
      m_value_temp(value),
      m_cursor_pos(-1),
      m_selection_pos(-1),
      m_mouse_pos(Vector2i(-1, -1)),
      m_mouse_down_pos(Vector2i(-1, -1)),
      m_mouse_drag_pos(Vector2i(-1, -1)),
      m_mouse_down_modifier(::user::e_key_none),
      m_text_offset(0) {
      if (m_theme) m_font_size = m_theme->m_text_box_font_size;
      m_icon_extra_scale = .8f;
   }

   void TextBox::set_editable(bool editable) {
      m_editable = editable;
      set_cursor(editable ? Cursor::IBeam : Cursor::Arrow);
   }

   void TextBox::set_theme(Theme* theme) {
      Widget::set_theme(theme);
      if (m_theme)
         m_font_size = m_theme->m_text_box_font_size;
   }


   Vector2i TextBox::preferred_size(::nano2d::context* pcontext, bool bRecalcTextSize)
   {

      Vector2i size(0, (int)(font_size() * 1.4f));

      float uw = 0;
      if (m_units_image > 0) {
         int w, h;
         pcontext->image_size(m_units_image, &w, &h);
         float uh = size[1] * 0.4f;
         uw = w * uh / h;
      }
      else if (m_units.has_char()) {
         uw = pcontext->text_bounds(0, 0, m_units, nullptr);
      }
      float sw = 0;
      if (m_spinnable) {
         sw = 14.f;
      }

      float ts = pcontext->text_bounds(0, 0, m_value, nullptr);
      size[0] = (int)(size[1] + ts + uw + sw);
      return size;
   }


   void TextBox::draw(::nano2d::context* pcontext)
   {

      if (!need_to_draw(pcontext))
      {

         return;

      }

      Widget::draw(pcontext);

      ::nano2d::paint bg = pcontext->box_gradient(
         m_pos.x() + 1.f, m_pos.y() + 1.f + 1.0f, m_size.x() - 2.f, m_size.y() - 2.f,
         3.f, 4.f, ::color::color(255, 32), m_colorBackground);
      ::nano2d::paint fg1 = pcontext->box_gradient(
         m_pos.x() + 1.f, m_pos.y() + 1.f + 1.0f, m_size.x() - 2.f, m_size.y() - 2.f,
         3.f, 4.f, ::color::color(150, 32), m_colorBackground);
      ::nano2d::paint fg2 = pcontext->box_gradient(
         m_pos.x() + 1.f, m_pos.y() + 1.f + 1.0f, m_size.x() - 2.f, m_size.y() - 2.f,
         3.f, 4.f, ::color::RGBA_color(255, 0, 0, 100), m_colorBackground);

      pcontext->begin_path();
      pcontext->rounded_rectangle(m_pos.x() + 1.f, m_pos.y() + 1.f + 1.0f, m_size.x() - 2.f,
         m_size.y() - 2.f, 3);

      if (m_editable && focused())
         m_valid_format ? pcontext->fill_paint(fg1) : pcontext->fill_paint(fg2);
      else if (m_spinnable && m_mouse_down_pos.x() != -1)
         pcontext->fill_paint(fg1);
      else
         pcontext->fill_paint(bg);

      pcontext->fill();

      pcontext->begin_path();
      pcontext->rounded_rectangle(m_pos.x() + 0.5f, m_pos.y() + 0.5f, m_size.x() - 1.f,
         m_size.y() - 1.f, 2.5f);
      pcontext->stroke_color(::color::color(0, 48));
      pcontext->stroke();

      pcontext->font_size(font_size());
      pcontext->font_face("sans");
      Vector2i draw_pos(m_pos.x(), (int)(m_pos.y() + m_size.y() * 0.5f + 1.f));

      float x_spacing = m_size.y() * 0.3f;

      float unit_width = 0;

      if (m_units_image > 0) {
         int w, h;
         pcontext->image_size(m_units_image, &w, &h);
         float unit_height = m_size.y() * 0.4f;
         unit_width = w * unit_height / h;
         ::nano2d::paint img_paint = pcontext->image_pattern(
            m_pos.x() + m_size.x() - x_spacing - unit_width,
            draw_pos.y() - unit_height * 0.5f, unit_width, unit_height, 0,
            m_units_image, m_enabled ? 0.7f : 0.35f);
         pcontext->begin_path();
         pcontext->rectangle(m_pos.x() + m_size.x() - x_spacing - unit_width,
            draw_pos.y() - unit_height * 0.5f, unit_width, unit_height);
         pcontext->fill_paint(img_paint);
         pcontext->fill();
         unit_width += 2;
      }
      else if (m_units.has_char()) {
         unit_width = pcontext->text_bounds(0, 0, m_units, nullptr);
         pcontext->fill_color(::color::color(255, m_enabled ? 64 : 32));
         pcontext->text_align(::nano2d::e_align_right | ::nano2d::e_align_middle);
         pcontext->text(m_pos.x() + m_size.x() - x_spacing, (float)draw_pos.y(), m_units);
         unit_width += 2;
      }

      float spin_arrows_width = 0.f;

      if (m_spinnable && !focused()) {
         spin_arrows_width = 14.f;

         pcontext->font_face("icons");
         pcontext->font_size(((m_font_size < 0) ? m_theme->m_button_font_size : m_font_size) * icon_scale());

         bool spinning = m_mouse_down_pos.x() != -1;

         /* up button */ {
            bool hover = m_mouse_focus && spin_area(m_mouse_pos) == SpinArea::Top;
            pcontext->fill_color((m_enabled && (hover || spinning)) ? m_theme->m_text_color : m_theme->m_disabled_text_color);
            auto icon = get_utf8_character(m_theme->m_text_box_up_icon);
            pcontext->text_align(::nano2d::e_align_left | ::nano2d::e_align_middle);
            Vector2f icon_pos(m_pos.x() + 4.f,
               m_pos.y() + m_size.y() / 2.f - x_spacing / 2.f);
            pcontext->text(icon_pos.x(), icon_pos.y(), icon.data());
         }

         /* down button */ {
            bool hover = m_mouse_focus && spin_area(m_mouse_pos) == SpinArea::Bottom;
            pcontext->fill_color((m_enabled && (hover || spinning)) ? m_theme->m_text_color : m_theme->m_disabled_text_color);
            auto icon = get_utf8_character(m_theme->m_text_box_down_icon);
            pcontext->text_align(::nano2d::e_align_left | ::nano2d::e_align_middle);
            Vector2f icon_pos(m_pos.x() + 4.f,
               m_pos.y() + m_size.y() / 2.f + x_spacing / 2.f + 1.5f);
            pcontext->text(icon_pos.x(), icon_pos.y(), icon.data());
         }

         pcontext->font_size(font_size());
         pcontext->font_face("sans");
      }

      switch (m_alignment) {
      case Alignment::Left:
         pcontext->text_align(::nano2d::e_align_left | ::nano2d::e_align_middle);
         draw_pos.x() += (int)(x_spacing + spin_arrows_width);
         break;
      case Alignment::Right:
         pcontext->text_align(::nano2d::e_align_right | ::nano2d::e_align_middle);
         draw_pos.x() += (int)(m_size.x() - unit_width - x_spacing);
         break;
      case Alignment::Center:
         pcontext->text_align(::nano2d::e_align_center | ::nano2d::e_align_middle);
         draw_pos.x() += (int)(m_size.x() * 0.5f);
         break;
      }

      pcontext->font_size(font_size());
      pcontext->fill_color(m_enabled && (!m_committed || m_value.has_char()) ?
         m_theme->m_text_color :
         m_theme->m_disabled_text_color);

      // clip visible text area
      float clip_x = m_pos.x() + x_spacing + spin_arrows_width - 1.0f;
      float clip_y = m_pos.y() + 1.0f;
      float clip_width = m_size.x() - unit_width - spin_arrows_width - 2 * x_spacing + 2.0f;
      float clip_height = m_size.y() - 3.0f;

      pcontext->save();
      pcontext->intersect_scissor(clip_x, clip_y, clip_width, clip_height);

      Vector2i old_draw_pos(draw_pos);
      draw_pos.x() += (int)(m_text_offset);

      if (m_committed) {
         pcontext->text((float)draw_pos.x(), (float)draw_pos.y(), m_value.is_empty() ? m_placeholder : m_value);
      }
      else {
         const int max_glyphs = 1024;
         ::nano2d::glyphPosition glyphs[max_glyphs];
         float text_bound[4];
         pcontext->text_bounds((float)draw_pos.x(), (float)draw_pos.y(), m_value_temp, text_bound);
         float lineh = text_bound[3] - text_bound[1];

         // find cursor positions
         int nglyphs =
            pcontext->text_glyph_positions((float)draw_pos.x(), (float)draw_pos.y(),
               m_value_temp, glyphs, max_glyphs);
         update_cursor(pcontext, text_bound[2], glyphs, nglyphs);

         // compute text offset
         int prev_cpos = m_cursor_pos > 0 ? m_cursor_pos - 1 : 0;
         int next_cpos = m_cursor_pos < nglyphs ? m_cursor_pos + 1 : nglyphs;
         float prev_cx = cursor_index_to_position(prev_cpos, text_bound[2], glyphs, nglyphs);
         float next_cx = cursor_index_to_position(next_cpos, text_bound[2], glyphs, nglyphs);

         if (next_cx > clip_x + clip_width)
            m_text_offset -= next_cx - (clip_x + clip_width) + 1;
         if (prev_cx < clip_x)
            m_text_offset += clip_x - prev_cx + 1;

         draw_pos.x() = (int)(old_draw_pos.x() + m_text_offset);

         // draw text with offset
         pcontext->text((float)draw_pos.x(), (float)draw_pos.y(), m_value_temp);
         pcontext->text_bounds((float)draw_pos.x(), (float)draw_pos.y(), m_value_temp, text_bound);

         // recompute cursor positions
         nglyphs = pcontext->text_glyph_positions((float)draw_pos.x(), (float)draw_pos.y(),
            m_value_temp, glyphs, max_glyphs);

         if (m_cursor_pos > -1) {
            if (m_selection_pos > -1) {
               float caretx = cursor_index_to_position(m_cursor_pos, text_bound[2],
                  glyphs, nglyphs);
               float selx = cursor_index_to_position(m_selection_pos, text_bound[2],
                  glyphs, nglyphs);

               if (caretx > selx)
                  std::swap(caretx, selx);

               // draw selection
               pcontext->begin_path();
               pcontext->fill_color(::color::RGBA_color(255, 255, 255, 80));
               pcontext->rectangle(caretx, draw_pos.y() - lineh * 0.5f, selx - caretx,
                  lineh);
               pcontext->fill();
            }

            float caretx = cursor_index_to_position(m_cursor_pos, text_bound[2], glyphs, nglyphs);

            // draw cursor
            pcontext->begin_path();
            pcontext->move_to(caretx, draw_pos.y() - lineh * 0.5f);
            pcontext->line_to(caretx, draw_pos.y() + lineh * 0.5f);
            pcontext->stroke_color(::color::RGBA_color(255, 192, 0, 255));
            pcontext->stroke_width(1.0f);
            pcontext->stroke();
         }
      }

      pcontext->restore();

   }


   bool TextBox::mouse_enter_event(const Vector2i& p, bool enter, const ::user::e_key& ekeyModifiers)
   {

      Widget::mouse_enter_event(p, enter, ekeyModifiers);

      return true;

   }


   bool TextBox::mouse_button_event(const Vector2i& p, ::user::e_mouse emouse, bool down, bool bDoubleClick, const ::user::e_key& ekeyModifiers)
   {

      if (emouse == ::user::e_mouse_left_button && down && !m_focused)
      {
         if (!m_spinnable || spin_area(p) == SpinArea::None) /* not on scrolling arrows */
            request_focus();
      }

      if (m_editable && focused()) {
         if (down) {
            m_mouse_down_pos = p;
            m_mouse_down_modifier = ekeyModifiers;

            //if ( m_last_click.elapsed() < 250_ms) {
            if (bDoubleClick) {
               /* Double-click: select all text */
               m_selection_pos = 0;
               m_cursor_pos = (int)m_value_temp.size();
               m_mouse_down_pos = Vector2i(-1, -1);
            }
            m_last_click.Now();
            
            set_need_redraw();
            
            post_redraw();

         }
         else {
            m_mouse_down_pos = Vector2i(-1, -1);
            m_mouse_drag_pos = Vector2i(-1, -1);
         }
         return true;
      }
      else if (m_spinnable && !focused()) {
         if (down) {
            if (spin_area(p) == SpinArea::None) {
               m_mouse_down_pos = p;
               m_mouse_down_modifier = ekeyModifiers;

               if (m_last_click.elapsed() < 250_ms) {
                  /* Double-click: reset to default value */
                  m_value = m_default_value;
                  if (m_callback)
                     m_callback(m_value);

                  set_need_redraw();

                  post_redraw();

                  m_mouse_down_pos = Vector2i(-1, -1);

               }

               m_last_click.Now();

            }
            else {
               m_mouse_down_pos = Vector2i(-1, -1);
               m_mouse_drag_pos = Vector2i(-1, -1);
            }
         }
         else {
            m_mouse_down_pos = Vector2i(-1, -1);
            m_mouse_drag_pos = Vector2i(-1, -1);
         }
         return true;
      }

      return false;
   }


   bool TextBox::mouse_motion_event(const Vector2i& p, const Vector2i& /* rel */, bool bDown, const ::user::e_key& ekeyModifiers)
   {

      m_mouse_pos = p;

      if (!m_editable)
         set_cursor(Cursor::Arrow);
      else if (m_spinnable && !focused() && spin_area(m_mouse_pos) != SpinArea::None) /* scrolling arrows */
         set_cursor(Cursor::Hand);
      else
         set_cursor(Cursor::IBeam);


      if (bDown)
      {

         m_mouse_pos = p;
         m_mouse_drag_pos = p;

         if (m_editable && focused())
         {

            return true;

         }

         return false;

      }

      //return m_editable;
      return false;

   }


   //bool TextBox::mouse_drag_event(const Vector2i& p, const Vector2i&/* rel */, const ::user::e_key& ekeyModifiers)
   //{
   // 
   // 
   //   m_mouse_pos = p;
   //   m_mouse_drag_pos = p;

   //   if (m_editable && focused())
   //   {

   //      return true;

   //   }

   //   return false;


   //}


   bool TextBox::focus_event(bool focused) {
      Widget::focus_event(focused);

      ::string backup = m_value;

      if (m_editable) {
         if (focused) {
            m_value_temp = m_value;
            m_committed = false;
            m_cursor_pos = 0;
         }
         else {
            if (m_valid_format) {
               if (m_value_temp == "")
                  m_value = m_default_value;
               else
                  m_value = m_value_temp;
            }

            if (m_callback && !m_callback(m_value))
               m_value = backup;

            set_need_redraw();

            post_redraw();


            m_valid_format = true;
            m_committed = true;
            m_cursor_pos = -1;
            m_selection_pos = -1;
            m_text_offset = 0;
         }

         m_valid_format = (m_value_temp == "") || check_format(m_value_temp, m_format);
      }

      return true;
   }

   bool TextBox::keyboard_event(::user::enum_key ekey, int /* scancode */, int action, const ::user::e_key& ekeyModifiers, const ::string& strText) {
      if (m_editable && focused()) {

         auto psession = screen()->m_puserinteraction->get_session();

         //if (action == ::e_message_key_down || action == GLFW_REPEAT) {
         if (action == ::e_message_key_down) {
            if (ekey == ::user::e_key_left) {
               if (ekeyModifiers & ::user::e_key_shift) {
                  if (m_selection_pos == -1)
                     m_selection_pos = m_cursor_pos;
               }
               else {
                  m_selection_pos = -1;
               }

               if (m_cursor_pos > 0)
                  m_cursor_pos--;
            }
            else if (ekey == ::user::e_key_right) {
               if (ekeyModifiers & ::user::e_key_shift) {
                  if (m_selection_pos == -1)
                     m_selection_pos = m_cursor_pos;
               }
               else {
                  m_selection_pos = -1;
               }

               if (m_cursor_pos < (int)m_value_temp.length())
                  m_cursor_pos++;
            }
            else if (ekey == ::user::e_key_home) {
               if (ekeyModifiers & ::user::e_key_shift) {
                  if (m_selection_pos == -1)
                     m_selection_pos = m_cursor_pos;
               }
               else {
                  m_selection_pos = -1;
               }

               m_cursor_pos = 0;
            }
            else if (ekey == ::user::e_key_end) {
               if (ekeyModifiers & ::user::e_key_shift) {
                  if (m_selection_pos == -1)
                     m_selection_pos = m_cursor_pos;
               }
               else {
                  m_selection_pos = -1;
               }

               m_cursor_pos = (int)m_value_temp.size();
            }
            else if (ekey == ::user::e_key_back) {
               if (!delete_selection()) {
                  if (m_cursor_pos > 0) {
                     m_value_temp.erase(m_value_temp.begin() + m_cursor_pos - 1);
                     m_cursor_pos--;
                  }
               }
            }
            else if (ekey == ::user::e_key_delete) {
               if (!delete_selection()) {
                  if (m_cursor_pos < (int)m_value_temp.length())
                     m_value_temp.erase(m_value_temp.begin() + m_cursor_pos);
               }
            }
            else if (ekey == ::user::e_key_return) {
               if (!m_committed)
                  focus_event(false);
            }
            else if (ekey == ::user::e_key_a && psession->is_key_pressed(::user::e_key_system_command)) {
               m_cursor_pos = (int)m_value_temp.length();
               m_selection_pos = 0;
            }
            else if (ekey == ::user::e_key_x && psession->is_key_pressed(::user::e_key_system_command)) {
               copy_selection();
               delete_selection();
            }
            else if (ekey == ::user::e_key_c && psession->is_key_pressed(::user::e_key_system_command)) {
               copy_selection();
            }
            else if (ekey == ::user::e_key_v && psession->is_key_pressed(::user::e_key_system_command)) {
               delete_selection();
               paste_from_clipboard();
            }

            m_valid_format =
               (m_value_temp == "") || check_format(m_value_temp, m_format);

            set_need_redraw();

            post_redraw();

         }

         return true;

      }

      return false;

   }

   bool TextBox::keyboard_character_event(unsigned int codepoint) {
      if (m_editable && focused()) {
         if (codepoint <= 16)
         {

            return false;
         }
         if (codepoint == 22)
         {

            return false;

         }
         //std::ostringstream convert;
         ::string strConvert((char)codepoint);

         delete_selection();
         m_value_temp.insert(m_cursor_pos, strConvert);
         m_cursor_pos++;

         m_valid_format = (m_value_temp == "") || check_format(m_value_temp, m_format);

         set_need_redraw();
         
         post_redraw();

         return true;

      }

      return false;
   }

   bool TextBox::check_format(const ::scoped_string& input, const ::scoped_string& format) {
      if (format.is_empty())
         return true;
      try {
         std::regex regex(::std::string(format.begin(), format.end()));
         return std::regex_match(::std::string(input.begin(), input.end()), regex);
      }
      catch (const std::regex_error&) {
         //#if __GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ < 9)
         //      std::cerr << "Warning: cannot validate text field due to lacking regular expression support. please compile with GCC >= 4.9" << std::endl;
         //      return true;
         //#else
         //      throw;
         //#endif
      }
      return true;
   }

   bool TextBox::copy_selection() {
      if (m_selection_pos > -1) {
         Screen* sc = screen();
         if (!sc)
            return false;

         int begin = m_cursor_pos;
         int end = m_selection_pos;

         if (begin > end)
            std::swap(begin, end);

         screen()->m_puserinteraction->window()->copydesk()->set_plain_text(m_value_temp.substr(begin, end).c_str());

         //glfwSetClipboardString(sc->glfw_window(),
         //   m_value_temp.substr(begin, end).c_str());
         return true;
      }

      return false;
   }

   void TextBox::paste_from_clipboard() {
      Screen* sc = screen();
      if (!sc)
         return;
      //const char * cbstr = glfwGetClipboardString(sc->glfw_window());
      string strClipboardText;
      screen()->m_puserinteraction->window()->copydesk()->get_plain_text(strClipboardText);
      if (strClipboardText.has_char())
      {
         m_value_temp.insert(m_cursor_pos, ::string(strClipboardText.c_str()));

      }
   }

   bool TextBox::delete_selection() {
      if (m_selection_pos > -1) {
         int begin = m_cursor_pos;
         int end = m_selection_pos;

         if (begin > end)
            std::swap(begin, end);

         if (begin == end - 1)
            m_value_temp.erase(m_value_temp.begin() + begin);
         else
            m_value_temp.erase(m_value_temp.begin() + begin,
               m_value_temp.begin() + end);

         m_cursor_pos = begin;
         m_selection_pos = -1;
         return true;
      }

      return false;
   }

   void TextBox::update_cursor(::nano2d::context*, float lastx,
      const ::nano2d::glyphPosition* glyphs, int size) {
      // handle mouse cursor events
      if (m_mouse_down_pos.x() != -1) {
         if (m_mouse_down_modifier == ::user::e_key_shift) {
            if (m_selection_pos == -1)
               m_selection_pos = m_cursor_pos;
         }
         else
            m_selection_pos = -1;

         m_cursor_pos =
            position_to_cursor_index((float)m_mouse_down_pos.x(), lastx, glyphs, size);

         m_mouse_down_pos = Vector2i(-1, -1);
      }
      else if (m_mouse_drag_pos.x() != -1) {
         if (m_selection_pos == -1)
            m_selection_pos = m_cursor_pos;

         m_cursor_pos =
            position_to_cursor_index((float)m_mouse_drag_pos.x(), lastx, glyphs, size);
      }
      else {
         // set cursor to last character
         if (m_cursor_pos == -2)
            m_cursor_pos = size;
      }

      if (m_cursor_pos == m_selection_pos)
         m_selection_pos = -1;
   }

   float TextBox::cursor_index_to_position(int index, float lastx,
      const ::nano2d::glyphPosition* glyphs, int size) {
      float pos = 0;
      if (index == size)
         pos = lastx; // last character
      else
         pos = glyphs[index].x;

      return pos;
   }

   int TextBox::position_to_cursor_index(float posx, float lastx,
      const ::nano2d::glyphPosition* glyphs, int size) {

      float caretx = glyphs[0].x;

      if (posx < caretx)
      {

         return 0;

      }

      double dLastX = caretx;

      int cursor = 1;

      for (; cursor <= size; cursor++)
      {

         double dNextX;

         if (cursor >= size)
         {

            dNextX = (dLastX + glyphs[cursor - 1].x) / 2.0;

         }
         else
         {

            dNextX = (glyphs[cursor].x + glyphs[cursor - 1].x) / 2.0;

         }

         if (posx >= dLastX && posx < dNextX)
         {

            return cursor - 1;

         }

         dLastX = dNextX;

      }

      return cursor - 1;

   }


   TextBox::SpinArea TextBox::spin_area(const Vector2i& pos) {
      if (0 <= pos.x() - m_pos.x() && pos.x() - m_pos.x() < 14.f) { /* on scrolling arrows */
         if (m_size.y() >= pos.y() - m_pos.y() && pos.y() - m_pos.y() <= m_size.y() / 2.f) { /* top part */
            return SpinArea::Top;
         }
         else if (0.f <= pos.y() - m_pos.y() && pos.y() - m_pos.y() > m_size.y() / 2.f) { /* bottom part */
            return SpinArea::Bottom;
         }
      }
      return SpinArea::None;
   }



} // namespace nanoui


