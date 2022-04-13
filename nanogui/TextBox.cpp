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
//#include <nanogui/window.h>
//#include <nanogui/screen.h>
//#include <nanogui/textbox.h>
//#include <nanogui/opengl.h>
//#include <nanogui/theme.h>
#include <regex>
//#include <iostream>

NAMESPACE_BEGIN(nanogui)

TextBox::TextBox(Widget * parent, const std::string & value)
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
   m_text_offset(0){
   if (m_theme) m_font_size = m_theme->m_text_box_font_size;
   m_icon_extra_scale = .8f;
}

void TextBox::set_editable(bool editable) {
   m_editable = editable;
   set_cursor(editable ? Cursor::IBeam : Cursor::Arrow);
}

void TextBox::set_theme(Theme * theme) {
   Widget::set_theme(theme);
   if (m_theme)
      m_font_size = m_theme->m_text_box_font_size;
}


Vector2i TextBox::preferred_size(NVGcontext * ctx, bool bRecalcTextSize)
{
   
   Vector2i size(0, (int) (font_size() * 1.4f));

   float uw = 0;
   if (m_units_image > 0) {
      int w, h;
      nvgImageSize(ctx, m_units_image, &w, &h);
      float uh = size[1] * 0.4f;
      uw = w * uh / h;
   }
   else if (!m_units.empty()) {
      uw = nvgTextBounds(ctx, 0, 0, m_units.c_str(), nullptr, nullptr);
   }
   float sw = 0;
   if (m_spinnable) {
      sw = 14.f;
   }

   float ts = nvgTextBounds(ctx, 0, 0, m_value.c_str(), nullptr, nullptr);
   size[0] = (int)(size[1] + ts + uw + sw);
   return size;
}

void TextBox::draw(NVGcontext * ctx) {
   Widget::draw(ctx);

   NVGpaint bg = nvgBoxGradient(ctx,
      m_pos.x() + 1.f, m_pos.y() + 1.f + 1.0f, m_size.x() - 2.f, m_size.y() - 2.f,
      3.f, 4.f, Color(255, 32), Color(32, 32));
   NVGpaint fg1 = nvgBoxGradient(ctx,
      m_pos.x() + 1.f, m_pos.y() + 1.f + 1.0f, m_size.x() - 2.f, m_size.y() - 2.f,
      3.f, 4.f, Color(150, 32), Color(32, 32));
   NVGpaint fg2 = nvgBoxGradient(ctx,
      m_pos.x() + 1.f, m_pos.y() + 1.f + 1.0f, m_size.x() - 2.f, m_size.y() - 2.f,
      3.f, 4.f, nvgRGBA(255, 0, 0, 100), nvgRGBA(255, 0, 0, 50));

   nvgBeginPath(ctx);
   nvgRoundedRect(ctx, m_pos.x() + 1.f, m_pos.y() + 1.f + 1.0f, m_size.x() - 2.f,
      m_size.y() - 2.f, 3);

   if (m_editable && focused())
      m_valid_format ? nvgFillPaint(ctx, fg1) : nvgFillPaint(ctx, fg2);
   else if (m_spinnable && m_mouse_down_pos.x() != -1)
      nvgFillPaint(ctx, fg1);
   else
      nvgFillPaint(ctx, bg);

   nvgFill(ctx);

   nvgBeginPath(ctx);
   nvgRoundedRect(ctx, m_pos.x() + 0.5f, m_pos.y() + 0.5f, m_size.x() - 1.f,
      m_size.y() - 1.f, 2.5f);
   nvgStrokeColor(ctx, Color(0, 48));
   nvgStroke(ctx);

   nvgFontSize(ctx, font_size());
   nvgFontFace(ctx, "sans");
   Vector2i draw_pos(m_pos.x(), (int) (m_pos.y() + m_size.y() * 0.5f + 1.f));

   float x_spacing = m_size.y() * 0.3f;

   float unit_width = 0;

   if (m_units_image > 0) {
      int w, h;
      nvgImageSize(ctx, m_units_image, &w, &h);
      float unit_height = m_size.y() * 0.4f;
      unit_width = w * unit_height / h;
      NVGpaint img_paint = nvgImagePattern(
         ctx, m_pos.x() + m_size.x() - x_spacing - unit_width,
         draw_pos.y() - unit_height * 0.5f, unit_width, unit_height, 0,
         m_units_image, m_enabled ? 0.7f : 0.35f);
      nvgBeginPath(ctx);
      nvgRect(ctx, m_pos.x() + m_size.x() - x_spacing - unit_width,
         draw_pos.y() - unit_height * 0.5f, unit_width, unit_height);
      nvgFillPaint(ctx, img_paint);
      nvgFill(ctx);
      unit_width += 2;
   }
   else if (!m_units.empty()) {
      unit_width = nvgTextBounds(ctx, 0, 0, m_units.c_str(), nullptr, nullptr);
      nvgFillColor(ctx, Color(255, m_enabled ? 64 : 32));
      nvgTextAlign(ctx, NVG_ALIGN_RIGHT | NVG_ALIGN_MIDDLE);
      nvgText(ctx, m_pos.x() + m_size.x() - x_spacing, (float) draw_pos.y(),
         m_units.c_str(), nullptr);
      unit_width += 2;
   }

   float spin_arrows_width = 0.f;

   if (m_spinnable && !focused()) {
      spin_arrows_width = 14.f;

      nvgFontFace(ctx, "icons");
      nvgFontSize(ctx, ((m_font_size < 0) ? m_theme->m_button_font_size : m_font_size) * icon_scale());

      bool spinning = m_mouse_down_pos.x() != -1;

      /* up button */ {
         bool hover = m_mouse_focus && spin_area(m_mouse_pos) == SpinArea::Top;
         nvgFillColor(ctx, (m_enabled && (hover || spinning)) ? m_theme->m_text_color : m_theme->m_disabled_text_color);
         auto icon = get_utf8_character(m_theme->m_text_box_up_icon);
         nvgTextAlign(ctx, NVG_ALIGN_LEFT | NVG_ALIGN_MIDDLE);
         Vector2f icon_pos(m_pos.x() + 4.f,
            m_pos.y() + m_size.y() / 2.f - x_spacing / 2.f);
         nvgText(ctx, icon_pos.x(), icon_pos.y(), icon.data(), nullptr);
      }

      /* down button */ {
         bool hover = m_mouse_focus && spin_area(m_mouse_pos) == SpinArea::Bottom;
         nvgFillColor(ctx, (m_enabled && (hover || spinning)) ? m_theme->m_text_color : m_theme->m_disabled_text_color);
         auto icon = get_utf8_character(m_theme->m_text_box_down_icon);
         nvgTextAlign(ctx, NVG_ALIGN_LEFT | NVG_ALIGN_MIDDLE);
         Vector2f icon_pos(m_pos.x() + 4.f,
            m_pos.y() + m_size.y() / 2.f + x_spacing / 2.f + 1.5f);
         nvgText(ctx, icon_pos.x(), icon_pos.y(), icon.data(), nullptr);
      }

      nvgFontSize(ctx, font_size());
      nvgFontFace(ctx, "sans");
   }

   switch (m_alignment) {
   case Alignment::Left:
      nvgTextAlign(ctx, NVG_ALIGN_LEFT | NVG_ALIGN_MIDDLE);
      draw_pos.x() += (int) ( x_spacing + spin_arrows_width);
      break;
   case Alignment::Right:
      nvgTextAlign(ctx, NVG_ALIGN_RIGHT | NVG_ALIGN_MIDDLE);
      draw_pos.x() += (int) ( m_size.x() - unit_width - x_spacing);
      break;
   case Alignment::Center:
      nvgTextAlign(ctx, NVG_ALIGN_CENTER | NVG_ALIGN_MIDDLE);
      draw_pos.x() += (int) (m_size.x() * 0.5f);
      break;
   }

   nvgFontSize(ctx, font_size());
   nvgFillColor(ctx, m_enabled && (!m_committed || !m_value.empty()) ?
      m_theme->m_text_color :
      m_theme->m_disabled_text_color);

   // clip visible text area
   float clip_x = m_pos.x() + x_spacing + spin_arrows_width - 1.0f;
   float clip_y = m_pos.y() + 1.0f;
   float clip_width = m_size.x() - unit_width - spin_arrows_width - 2 * x_spacing + 2.0f;
   float clip_height = m_size.y() - 3.0f;

   nvgSave(ctx);
   nvgIntersectScissor(ctx, clip_x, clip_y, clip_width, clip_height);

   Vector2i old_draw_pos(draw_pos);
   draw_pos.x() += (int) (m_text_offset);

   if (m_committed) {
      nvgText(ctx, (float) draw_pos.x(), (float)draw_pos.y(), m_value.empty() ? m_placeholder.c_str() : m_value.c_str(), nullptr);
   }
   else {
      const int max_glyphs = 1024;
      NVGglyphPosition glyphs[max_glyphs];
      float text_bound[4];
      nvgTextBounds(ctx, (float)draw_pos.x(), (float)draw_pos.y(), m_value_temp.c_str(),
         nullptr, text_bound);
      float lineh = text_bound[3] - text_bound[1];

      // find cursor positions
      int nglyphs =
         nvgTextGlyphPositions(ctx, (float)draw_pos.x(), (float)draw_pos.y(),
            m_value_temp.c_str(), nullptr, glyphs, max_glyphs);
      update_cursor(ctx, text_bound[2], glyphs, nglyphs);

      // compute text offset
      int prev_cpos = m_cursor_pos > 0 ? m_cursor_pos - 1 : 0;
      int next_cpos = m_cursor_pos < nglyphs ? m_cursor_pos + 1 : nglyphs;
      float prev_cx = cursor_index_to_position(prev_cpos, text_bound[2], glyphs, nglyphs);
      float next_cx = cursor_index_to_position(next_cpos, text_bound[2], glyphs, nglyphs);

      if (next_cx > clip_x + clip_width)
         m_text_offset -= next_cx - (clip_x + clip_width) + 1;
      if (prev_cx < clip_x)
         m_text_offset += clip_x - prev_cx + 1;

      draw_pos.x() = (int) (old_draw_pos.x() + m_text_offset);

      // draw text with offset
      nvgText(ctx, (float)draw_pos.x(), (float)draw_pos.y(), m_value_temp.c_str(), nullptr);
      nvgTextBounds(ctx, (float)draw_pos.x(), (float)draw_pos.y(), m_value_temp.c_str(),
         nullptr, text_bound);

      // recompute cursor positions
      nglyphs = nvgTextGlyphPositions(ctx, (float)draw_pos.x(), (float)draw_pos.y(),
         m_value_temp.c_str(), nullptr, glyphs, max_glyphs);

      if (m_cursor_pos > -1) {
         if (m_selection_pos > -1) {
            float caretx = cursor_index_to_position(m_cursor_pos, text_bound[2],
               glyphs, nglyphs);
            float selx = cursor_index_to_position(m_selection_pos, text_bound[2],
               glyphs, nglyphs);

            if (caretx > selx)
               std::swap(caretx, selx);

            // draw selection
            nvgBeginPath(ctx);
            nvgFillColor(ctx, nvgRGBA(255, 255, 255, 80));
            nvgRect(ctx, caretx, draw_pos.y() - lineh * 0.5f, selx - caretx,
               lineh);
            nvgFill(ctx);
         }

         float caretx = cursor_index_to_position(m_cursor_pos, text_bound[2], glyphs, nglyphs);

         // draw cursor
         nvgBeginPath(ctx);
         nvgMoveTo(ctx, caretx, draw_pos.y() - lineh * 0.5f);
         nvgLineTo(ctx, caretx, draw_pos.y() + lineh * 0.5f);
         nvgStrokeColor(ctx, nvgRGBA(255, 192, 0, 255));
         nvgStrokeWidth(ctx, 1.0f);
         nvgStroke(ctx);
      }
   }
   nvgRestore(ctx);
}


bool TextBox::mouse_enter_event(const Vector2i & p, bool enter, const ::user::e_key & ekeyModifiers)
{

   Widget::mouse_enter_event(p, enter, ekeyModifiers);

   return true;

}


bool TextBox::mouse_button_event(const Vector2i & p, int button, bool down, const ::user::e_key & ekeyModifiers) 
{


   if (button == __MOUSE_LEFT_BUTTON && down && !m_focused) 
   {
      if (!m_spinnable || spin_area(p) == SpinArea::None) /* not on scrolling arrows */
         request_focus();
   }

   if (m_editable && focused()) {
      if (down) {
         m_mouse_down_pos = p;
         m_mouse_down_modifier = ekeyModifiers;

         if ( m_last_click.elapsed() < 250_ms) {
            /* Double-click: select all text */
            m_selection_pos = 0;
            m_cursor_pos = (int)m_value_temp.size();
            m_mouse_down_pos = Vector2i(-1, -1);
         }
         m_last_click.Now();
         screen()->m_puserinteraction->set_need_redraw();
         screen()->m_puserinteraction->post_redraw();
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

               screen()->m_puserinteraction->set_need_redraw();
               screen()->m_puserinteraction->post_redraw();

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

bool TextBox::mouse_motion_event(const Vector2i & p, const Vector2i & /* rel */, const ::user::e_key & ekeyModifiers) 
{

   m_mouse_pos = p;

   if (!m_editable)
      set_cursor(Cursor::Arrow);
   else if (m_spinnable && !focused() && spin_area(m_mouse_pos) != SpinArea::None) /* scrolling arrows */
      set_cursor(Cursor::Hand);
   else
      set_cursor(Cursor::IBeam);

   return m_editable;
}


bool TextBox::mouse_drag_event(const Vector2i & p, const Vector2i &/* rel */, const ::user::e_key & ekeyModifiers) 
{

   m_mouse_pos = p;
   m_mouse_drag_pos = p;

   if (m_editable && focused())
   {

      return true;

   }

   return false;

}


bool TextBox::focus_event(bool focused) {
   Widget::focus_event(focused);

   std::string backup = m_value;

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

         screen()->m_puserinteraction->set_need_redraw();
         screen()->m_puserinteraction->post_redraw();


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

bool TextBox::keyboard_event(::user::enum_key ekey, int /* scancode */, int action, const ::user::e_key & ekeyModifiers) {
   if (m_editable && focused()) {
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
         else if (ekey == ::user::e_key_a && ekeyModifiers == ::user::e_key_system_command) {
            m_cursor_pos = (int)m_value_temp.length();
            m_selection_pos = 0;
         }
         else if (ekey == ::user::e_key_x && ekeyModifiers == ::user::e_key_system_command) {
            copy_selection();
            delete_selection();
         }
         else if (ekey == ::user::e_key_c && ekeyModifiers == ::user::e_key_system_command) {
            copy_selection();
         }
         else if (ekey == ::user::e_key_v && ekeyModifiers == ::user::e_key_system_command) {
            delete_selection();
            paste_from_clipboard();
         }

         m_valid_format =
            (m_value_temp == "") || check_format(m_value_temp, m_format);

         screen()->m_puserinteraction->set_need_redraw();
         screen()->m_puserinteraction->post_redraw();

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
      std::ostringstream convert;
      convert << (char)codepoint;

      delete_selection();
      m_value_temp.insert(m_cursor_pos, convert.str());
      m_cursor_pos++;

      m_valid_format = (m_value_temp == "") || check_format(m_value_temp, m_format);

      screen()->m_puserinteraction->set_need_redraw();
      screen()->m_puserinteraction->post_redraw();

      return true;

   }

   return false;
}

bool TextBox::check_format(const std::string & input, const std::string & format) {
   if (format.empty())
      return true;
   try {
      std::regex regex(format);
      return regex_match(input, regex);
   }
   catch (const std::regex_error &) {
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
      Screen * sc = screen();
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
   Screen * sc = screen();
   if (!sc)
      return;
   //const char * cbstr = glfwGetClipboardString(sc->glfw_window());
   string strClipboardText;
   screen()->m_puserinteraction->window()->copydesk()->get_plain_text(strClipboardText);
   if (strClipboardText.has_char())
   {
      m_value_temp.insert(m_cursor_pos, std::string(strClipboardText.c_str()));

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

void TextBox::update_cursor(NVGcontext *, float lastx,
   const NVGglyphPosition * glyphs, int size) {
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
   const NVGglyphPosition * glyphs, int size) {
   float pos = 0;
   if (index == size)
      pos = lastx; // last character
   else
      pos = glyphs[index].x;

   return pos;
}

int TextBox::position_to_cursor_index(float posx, float lastx,
   const NVGglyphPosition * glyphs, int size) {

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

         dNextX = (dLastX + glyphs[cursor-1].x) / 2.0;

      }
      else
      {

         dNextX = (glyphs[cursor].x + glyphs[cursor-1].x) / 2.0;

      }
      
      if (posx >= dLastX && posx < dNextX) 
      {

         return cursor - 1;

      }

      dLastX = dNextX;

   }

   return cursor - 1;

}


TextBox::SpinArea TextBox::spin_area(const Vector2i & pos) {
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

NAMESPACE_END(nanogui)
