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
      m_bEditable(false),
      m_bSpinnable(false),
      m_bCommitted(true),
      m_strValue(value),
      m_strDefaultValue(""),
      m_ealignment(TextBox::e_alignment_center),
      m_strUnit(""),
      m_strFormat(""),
      m_iUnitImage(-1),
      m_bValidFormat(true),
      m_strValueTemp(value),
      m_iSelectionEnd(-1),
      m_iSelectionStart(-1),
      m_mouse_pos(Vector2i(-1, -1)),
      m_pointMouseDown(Vector2i(-1, -1)),
      m_pointMouseDrag(Vector2i(-1, -1)),
      m_ekeyMouseDownModifier(::user::e_key_none),
      m_fTextOffset(0)
   {
      if (m_theme) m_font_size = m_theme->m_iTextBoxFontSize;
      m_icon_extra_scale = .8f;

      m_bMouseDown = false;

   }

   void TextBox::set_editable(bool editable) {
      m_bEditable = editable;
      set_cursor(editable ? Cursor::IBeam : Cursor::Arrow);
   }

   void TextBox::set_theme(Theme* theme) {
      Widget::set_theme(theme);
      if (m_theme)
         m_font_size = m_theme->m_iTextBoxFontSize;
   }


   void TextBox::set_value(const ::scoped_string& value) {
      m_strValue = value;

      set_need_redraw();

      post_redraw();

   }


   Vector2i TextBox::preferred_size(::nano2d::context* pcontext, bool bRecalcTextSize)
   {

      Vector2i size(0, (int)(font_size() * 1.4f));

      float uw = 0;
      if (m_iUnitImage > 0) {
         int w, h;
         pcontext->image_size(m_iUnitImage, &w, &h);
         float uh = size[1] * 0.4f;
         uw = w * uh / h;
      }
      else if (m_strUnit.has_char()) {
         uw = pcontext->text_bounds(0, 0, m_strUnit, nullptr);
      }
      float sw = 0;
      if (m_bSpinnable) {
         sw = 14.f;
      }

      float ts = pcontext->text_bounds(0, 0, m_strValue, nullptr);
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

      if (m_bEditable && focused())
         m_bValidFormat ? pcontext->fill_paint(fg1) : pcontext->fill_paint(fg2);
      else if (m_bSpinnable && m_pointMouseDown.x() != -1)
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
      Vector2f draw_pos((float)m_pos.x(), (float)(m_pos.y() + m_size.y() * 0.5f + 1.f));

      float x_spacing = m_size.y() * 0.3f;

      float unit_width = 0;

      if (m_iUnitImage > 0) {
         int w, h;
         pcontext->image_size(m_iUnitImage, &w, &h);
         float unit_height = m_size.y() * 0.4f;
         unit_width = w * unit_height / h;
         ::nano2d::paint img_paint = pcontext->image_pattern(
            m_pos.x() + m_size.x() - x_spacing - unit_width,
            draw_pos.y() - unit_height * 0.5f, unit_width, unit_height, 0,
            m_iUnitImage, m_enabled ? 0.7f : 0.35f);
         pcontext->begin_path();
         pcontext->rectangle(m_pos.x() + m_size.x() - x_spacing - unit_width,
            draw_pos.y() - unit_height * 0.5f, unit_width, unit_height);
         pcontext->fill_paint(img_paint);
         pcontext->fill();
         unit_width += 2;
      }
      else if (m_strUnit.has_char()) {
         unit_width = pcontext->text_bounds(0, 0, m_strUnit, nullptr);
         pcontext->fill_color(::color::color(255, m_enabled ? 64 : 32));
         pcontext->text_align(::nano2d::e_align_right | ::nano2d::e_align_middle);
         pcontext->text(m_pos.x() + m_size.x() - x_spacing, (float)draw_pos.y(), m_strUnit);
         unit_width += 2;
      }

      float spin_arrows_width = 0.f;

      if (m_bSpinnable && !focused()) {
         spin_arrows_width = 14.f;

         pcontext->font_face("icons");
         pcontext->font_size(((m_font_size < 0) ? m_theme->m_iButtonFontSize : m_font_size) * icon_scale());

         bool spinning = m_pointMouseDown.x() != -1;

         /* up button */ {
            bool hover = m_mouse_focus && spin_area(m_mouse_pos) == SpinArea::Top;
            pcontext->fill_color((m_enabled && (hover || spinning)) ? m_theme->m_colorText : m_theme->m_colorDisableText);
            auto icon = get_utf8_character(m_theme->m_efontawesomeTextBoxUp);
            pcontext->text_align(::nano2d::e_align_left | ::nano2d::e_align_middle);
            Vector2f icon_pos(m_pos.x() + 4.f,
               m_pos.y() + m_size.y() / 2.f - x_spacing / 2.f);
            pcontext->text(icon_pos.x(), icon_pos.y(), icon.data());
         }

         /* down button */ {
            bool hover = m_mouse_focus && spin_area(m_mouse_pos) == SpinArea::Bottom;
            pcontext->fill_color((m_enabled && (hover || spinning)) ? m_theme->m_colorText : m_theme->m_colorDisableText);
            auto icon = get_utf8_character(m_theme->m_efontawesomeTextBoxDown);
            pcontext->text_align(::nano2d::e_align_left | ::nano2d::e_align_middle);
            Vector2f icon_pos(m_pos.x() + 4.f,
               m_pos.y() + m_size.y() / 2.f + x_spacing / 2.f + 1.5f);
            pcontext->text(icon_pos.x(), icon_pos.y(), icon.data());
         }

         pcontext->font_size(font_size());
         pcontext->font_face("sans");
      }

      switch (m_ealignment) {
      case e_alignment_left:
         pcontext->text_align(::nano2d::e_align_left | ::nano2d::e_align_middle);
         draw_pos.x() += (int)(x_spacing + spin_arrows_width);
         break;
      case e_alignment_right:
         pcontext->text_align(::nano2d::e_align_right | ::nano2d::e_align_middle);
         draw_pos.x() += (int)(m_size.x() - unit_width - x_spacing);
         break;
      case e_alignment_center:
         pcontext->text_align(::nano2d::e_align_center | ::nano2d::e_align_middle);
         draw_pos.x() += (int)(m_size.x() * 0.5f);
         break;
      }

      pcontext->font_size(font_size());
      pcontext->fill_color(m_enabled && (!m_bCommitted || m_strValue.has_char()) ?
         m_theme->m_colorText :
         m_theme->m_colorDisableText);

      // clip visible text area
      float clip_x = m_pos.x() + x_spacing + spin_arrows_width - 1.0f;
      float clip_y = m_pos.y() + 1.0f;
      float clip_width = m_size.x() - unit_width - spin_arrows_width - 2 * x_spacing + 2.0f;
      float clip_height = m_size.y() - 3.0f;

      pcontext->save();
      pcontext->intersect_scissor(clip_x, clip_y, clip_width, clip_height);

      Vector2f old_draw_pos(draw_pos);

      draw_pos.x() += m_fTextOffset;

      if (m_bCommitted) {
         pcontext->text(draw_pos.x(), draw_pos.y(), m_strValue.is_empty() ? m_strPlaceHolder : m_strValue);
      }
      else {
         const int max_glyphs = 1024;
         ::nano2d::glyphPosition glyphs[max_glyphs];
         float text_bound[4];
         pcontext->text_bounds(draw_pos.x(), draw_pos.y(), m_strValueTemp, text_bound);
         float lineh = text_bound[3] - text_bound[1];

         // find cursor positions
         int nglyphs =
            pcontext->text_glyph_positions(draw_pos.x(), draw_pos.y(),
               m_strValueTemp, glyphs, max_glyphs);
         update_cursor(pcontext, text_bound[2], glyphs, nglyphs);

         // compute text offset
         int prev_cpos = m_iSelectionEnd > 0 ? m_iSelectionEnd - 1 : 0;
         int next_cpos = m_iSelectionEnd < nglyphs ? m_iSelectionEnd + 1 : nglyphs;
         float prev_cx = cursor_index_to_position(prev_cpos, text_bound[2], glyphs, nglyphs);
         float next_cx = cursor_index_to_position(next_cpos, text_bound[2], glyphs, nglyphs);

         if (next_cx > clip_x + clip_width)
            m_fTextOffset -= next_cx - (clip_x + clip_width) + 1;
         if (prev_cx < clip_x)
            m_fTextOffset += clip_x - prev_cx + 1;

         draw_pos.x() = old_draw_pos.x() + m_fTextOffset;

         // draw text with offset
         pcontext->text(draw_pos.x(), draw_pos.y(), m_strValueTemp);
         pcontext->text_bounds(draw_pos.x(), draw_pos.y(), m_strValueTemp, text_bound);

         // recompute cursor positions
         nglyphs = pcontext->text_glyph_positions(draw_pos.x(), draw_pos.y(),
            m_strValueTemp, glyphs, max_glyphs);

         if (m_iSelectionEnd > -1) {
            if (m_iSelectionStart > -1) {
               float caretx = cursor_index_to_position(m_iSelectionEnd, text_bound[2],
                  glyphs, nglyphs);
               float selx = cursor_index_to_position(m_iSelectionStart, text_bound[2],
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

            float caretx = cursor_index_to_position(m_iSelectionEnd, text_bound[2], glyphs, nglyphs);

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
         if (!m_bSpinnable || spin_area(p) == SpinArea::None) /* not on scrolling arrows */
            request_focus();
      }

      if (!down)
      {

         if (m_bMouseDown)
         {

            release_mouse_capture();

            m_pointMouseDown = Vector2i(-1, -1);

            m_pointMouseDrag = Vector2i(-1, -1);

            return true;

         }

      }

      if (m_bEditable && focused())
      {

         if (down)
         {

            if (bDoubleClick)
            {

               /* Double-click: select all text */

               m_iSelectionStart = 0;

               m_iSelectionEnd = (int)m_strValueTemp.size();

               m_pointMouseDown = Vector2i(-1, -1);

            }
            else
            {

               m_bMouseDown = true;

               set_mouse_capture();

               m_pointMouseDown = p;

               m_ekeyMouseDownModifier = ekeyModifiers;

               //m_last_click.Now();

            }

            set_need_redraw();

            post_redraw();

         }

         return true;

      }
      else if (m_bSpinnable && !focused()) 
      {

         if (down) 
         {

            if (spin_area(p) == SpinArea::None) 
            {

               m_pointMouseDown = p;

               m_ekeyMouseDownModifier = ekeyModifiers;

               if (bDoubleClick)
               {

                  /* Double-click: reset to default value */

                  m_strValue = m_strDefaultValue;

                  if (m_callback)
                  {

                     m_callback(m_strValue);

                  }

                  set_need_redraw();

                  post_redraw();

                  m_pointMouseDown = Vector2i(-1, -1);

               }

               //m_last_click.Now();

            }
            else 
            {

               m_pointMouseDown = Vector2i(-1, -1);
               
               m_pointMouseDrag = Vector2i(-1, -1);

            }

         }
         else
         {

            m_pointMouseDown = Vector2i(-1, -1);

            m_pointMouseDrag = Vector2i(-1, -1);

         }

         return true;

      }

      return false;

   }


   bool TextBox::mouse_motion_event(const Vector2i& p, const Vector2i& /* rel */, bool bDown, const ::user::e_key& ekeyModifiers)
   {

      m_mouse_pos = p;

      if (!m_bEditable)
         set_cursor(Cursor::Arrow);
      else if (m_bSpinnable && !focused() && spin_area(m_mouse_pos) != SpinArea::None) /* scrolling arrows */
         set_cursor(Cursor::Hand);
      else
         set_cursor(Cursor::IBeam);


      if (bDown)
      {

         m_mouse_pos = p;
         m_pointMouseDrag = p;

         if (m_bEditable && focused())
         {

            return true;

         }

         return false;

      }

      //return m_bEditable;
      return false;

   }





   //bool TextBox::mouse_drag_event(const Vector2i& p, const Vector2i&/* rel */, const ::user::e_key& ekeyModifiers)
   //{
   // 
   // 
   //   m_mouse_pos = p;
   //   m_pointMouseDrag = p;

   //   if (m_bEditable && focused())
   //   {

   //      return true;

   //   }

   //   return false;


   //}


   bool TextBox::focus_event(bool focused) {
      Widget::focus_event(focused);

      ::string backup = m_strValue;

      if (m_bEditable) {
         if (focused) {
            m_strValueTemp = m_strValue;
            m_bCommitted = false;
            m_iSelectionEnd = 0;
         }
         else {
            if (m_bValidFormat) {
               if (m_strValueTemp == "")
                  m_strValue = m_strDefaultValue;
               else
                  m_strValue = m_strValueTemp;
            }

            if (m_callback && !m_callback(m_strValue))
               m_strValue = backup;

            set_need_redraw();

            post_redraw();


            m_bValidFormat = true;
            m_bCommitted = true;
            m_iSelectionEnd = -1;
            m_iSelectionStart = -1;
            m_fTextOffset = 0;
         }

         m_bValidFormat = (m_strValueTemp == "") || check_format(m_strValueTemp, m_strFormat);
      }

      return true;
   }

   bool TextBox::keyboard_event(::user::enum_key ekey, int /* scancode */, int action, const ::user::e_key& ekeyModifiers, const ::string& strText) {
      if (m_bEditable && focused()) {

         auto psession = screen()->m_puserinteraction->get_session();

         //if (action == ::e_message_key_down || action == GLFW_REPEAT) {
         if (action == ::e_message_key_down) {
            if (ekey == ::user::e_key_left) {
               if (ekeyModifiers & ::user::e_key_shift) {
                  if (m_iSelectionStart == -1)
                     m_iSelectionStart = m_iSelectionEnd;
               }
               else {
                  m_iSelectionStart = -1;
               }

               if (m_iSelectionEnd > 0)
                  m_iSelectionEnd--;
            }
            else if (ekey == ::user::e_key_right) {
               if (ekeyModifiers & ::user::e_key_shift) {
                  if (m_iSelectionStart == -1)
                     m_iSelectionStart = m_iSelectionEnd;
               }
               else {
                  m_iSelectionStart = -1;
               }

               if (m_iSelectionEnd < (int)m_strValueTemp.length())
                  m_iSelectionEnd++;
            }
            else if (ekey == ::user::e_key_home) {
               if (ekeyModifiers & ::user::e_key_shift) {
                  if (m_iSelectionStart == -1)
                     m_iSelectionStart = m_iSelectionEnd;
               }
               else {
                  m_iSelectionStart = -1;
               }

               m_iSelectionEnd = 0;
            }
            else if (ekey == ::user::e_key_end) {
               if (ekeyModifiers & ::user::e_key_shift) {
                  if (m_iSelectionStart == -1)
                     m_iSelectionStart = m_iSelectionEnd;
               }
               else {
                  m_iSelectionStart = -1;
               }

               m_iSelectionEnd = (int)m_strValueTemp.size();
            }
            else if (ekey == ::user::e_key_back) {
               if (!delete_selection()) {
                  if (m_iSelectionEnd > 0) {
                     m_strValueTemp.erase(m_strValueTemp.begin() + m_iSelectionEnd - 1);
                     m_iSelectionEnd--;
                  }
               }
            }
            else if (ekey == ::user::e_key_delete) {
               if (!delete_selection()) {
                  if (m_iSelectionEnd < (int)m_strValueTemp.length())
                     m_strValueTemp.erase(m_strValueTemp.begin() + m_iSelectionEnd);
               }
            }
            else if (ekey == ::user::e_key_return) {
               if (!m_bCommitted)
                  focus_event(false);
            }
            else if (ekey == ::user::e_key_a && psession->is_key_pressed(::user::e_key_system_command)) {
               m_iSelectionEnd = (int)m_strValueTemp.length();
               m_iSelectionStart = 0;
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

            m_bValidFormat =
               (m_strValueTemp == "") || check_format(m_strValueTemp, m_strFormat);

            set_need_redraw();

            post_redraw();

         }

         return true;

      }

      return false;

   }

   bool TextBox::keyboard_character_event(unsigned int codepoint) {
      if (m_bEditable && focused()) {
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
         m_strValueTemp.insert(m_iSelectionEnd, strConvert);
         m_iSelectionEnd++;

         m_bValidFormat = (m_strValueTemp == "") || check_format(m_strValueTemp, m_strFormat);

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
      if (m_iSelectionStart > -1) {
         Screen* sc = screen();
         if (!sc)
            return false;

         int begin = m_iSelectionEnd;
         int end = m_iSelectionStart;

         if (begin > end)
            std::swap(begin, end);

         screen()->m_puserinteraction->window()->copydesk()->set_plain_text(m_strValueTemp.substr(begin, end).c_str());

         //glfwSetClipboardString(sc->glfw_window(),
         //   m_strValueTemp.substr(begin, end).c_str());
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
         m_strValueTemp.insert(m_iSelectionEnd, ::string(strClipboardText.c_str()));

      }
   }

   bool TextBox::delete_selection() {
      if (m_iSelectionStart > -1) {
         int begin = m_iSelectionEnd;
         int end = m_iSelectionStart;

         if (begin > end)
            std::swap(begin, end);

         if (begin == end - 1)
            m_strValueTemp.erase(m_strValueTemp.begin() + begin);
         else
            m_strValueTemp.erase(m_strValueTemp.begin() + begin,
               m_strValueTemp.begin() + end);

         m_iSelectionEnd = begin;
         m_iSelectionStart = -1;
         return true;
      }

      return false;
   }

   void TextBox::update_cursor(::nano2d::context*, float lastx, const ::nano2d::glyphPosition* glyphs, int size)
   {

      // handle mouse cursor events
      if (m_pointMouseDown.x() != -1)
      {

         //if (m_ekeyMouseDownModifier == ::user::e_key_shift) 
         {

            //if (m_iSelectionStart == -1)
            {

               m_iSelectionStart = m_iSelectionEnd;

            }

         }
         //else
         //{

           // m_iSelectionStart = -1;

         //}

         m_iSelectionEnd = position_to_cursor_index((float)m_pointMouseDown.x(), lastx, glyphs, size);

         m_pointMouseDown = Vector2i(-1, -1);

      }
      else if (m_pointMouseDrag.x() != -1)
      {

         if (m_iSelectionStart == -1)
         {

            m_iSelectionStart = m_iSelectionEnd;

         }

         m_iSelectionEnd = position_to_cursor_index((float)m_pointMouseDrag.x(), lastx, glyphs, size);

      }
      else {
         // set cursor to last character
         if (m_iSelectionEnd == -2)
            m_iSelectionEnd = size;
      }

      if (m_iSelectionEnd == m_iSelectionStart)
         m_iSelectionStart = -1;
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


