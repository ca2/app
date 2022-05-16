/*
    src/label.cpp -- Text label with an arbitrary font, color, and size

    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The widget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/
#include "framework.h"
//#include <nanogui/label.h>
//#include <nanogui/theme.h>
//#include <nanogui/opengl.h>

NAMESPACE_BEGIN(nanogui)

Label::Label(Widget * parent, const std::string & caption, const std::string & font, int font_size)
   : Widget(parent), m_caption(caption), m_font(font) {
   if (m_theme) {
      m_font_size = m_theme->m_standard_font_size;
      m_color = m_theme->m_text_color;
   }
   if (font_size >= 0) m_font_size = font_size;
}

void Label::set_theme(Theme * theme) {
   Widget::set_theme(theme);
   if (m_theme) {
      m_font_size = m_theme->m_standard_font_size;
      m_color = m_theme->m_text_color;
   }
}

Vector2i Label::preferred_size(NVGcontext * ctx, bool bRecalcTextSize)
{
   if (bRecalcTextSize)
   {
      if (m_caption == "")
      {
         m_sizePreferred = Vector2i(0);

      }
      else
      {
         nvgFontFace(ctx, m_font.c_str());
         nvgFontSize(ctx, font_size());
         float bounds[4];
         if (m_fixed_size.x() > 0) {
            nvgTextAlign(ctx, NVG_ALIGN_LEFT | NVG_ALIGN_TOP);
            nvgTextBoxBounds(ctx, (float)m_pos.x(), (float)m_pos.y(), (float)m_fixed_size.x(), m_caption.c_str(), nullptr, bounds);
            m_sizePreferred = Vector2i(m_fixed_size.x(), (int)(bounds[3] - bounds[1]));
         }
         else {
            nvgTextAlign(ctx, NVG_ALIGN_LEFT | NVG_ALIGN_MIDDLE);
            int iSize = (int) nvgTextBounds(ctx, 0.f, 0.f, m_caption.c_str(), nullptr, bounds);
            m_sizePreferred = Vector2i(
                iSize +2 ,
               (int)(int)(bounds[3] - bounds[1])
            );
         }
      }
   }
   return m_sizePreferred;
}

void Label::draw(NVGcontext * ctx) {
   Widget::draw(ctx);
   nvgFontFace(ctx, m_font.c_str());
   nvgFontSize(ctx, font_size());
   nvgFillColor(ctx, m_color);
   if (m_fixed_size.x() > 0) {
      nvgTextAlign(ctx, NVG_ALIGN_LEFT | NVG_ALIGN_TOP);
      nvgTextBox(ctx, (float)m_pos.x(), (float)m_pos.y(), (float)m_fixed_size.x(), m_caption.c_str(), nullptr);
   }
   else {
      nvgTextAlign(ctx, NVG_ALIGN_LEFT | NVG_ALIGN_MIDDLE);
      nvgText(ctx, (float)m_pos.x(), (float)m_pos.y() + m_size.y() * 0.5f, m_caption.c_str(), nullptr);
   }
}


//void Label::_nanogui_to_user(::user::interaction * puserinteraction)
//{
//
//   return;
//
//   //puserinteraction->__construct(m_pstill);
//
//   //m_pstill->m_pappearance = this;
//
//   //m_pstill->create_control(puserinteraction, (iptr)(void *)this);
//
//   //m_pstill->display();
//
//   //m_pstill->place({ 10, 10, 99, 99 });
//
//   //m_pstill->set_need_layout();
//
//   //m_pstill->set_need_redraw();
//
//   //m_pstill->post_redraw();
//
//   //m_pstill->set_window_text(m_caption.c_str());
//
//   //Widget::_nanogui_to_user(m_pstill);
//
//}

NAMESPACE_END(nanogui)
