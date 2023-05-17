/*
    src/label.cpp -- Text label with an arbitrary font, color, and size

    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The widget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/
#include "framework.h"
#include "Label.h"
#include "nano2d/context.h"


namespace nanoui
{


Label::Label(Widget * parent, const ::scoped_string & caption, const ::scoped_string & font, int font_size)
   : Widget(parent), m_caption(caption), m_font(font) {
   if (m_theme) {
      m_font_size = m_theme->m_iStandardFontSize;
      m_color = m_theme->m_colorText;
   }
   if (font_size >= 0) m_font_size = font_size;
}

void Label::set_theme(Theme * theme) {
   Widget::set_theme(theme);
   if (m_theme) {
      m_font_size = m_theme->m_iStandardFontSize;
      m_color = m_theme->m_colorText;
   }
}

Vector2i Label::preferred_size(::nano2d::context * pcontext, bool bRecalcTextSize)
{
   if (bRecalcTextSize)
   {
      if (m_caption == "")
      {
         m_sizePreferred = Vector2i(0);

      }
      else
      {
         pcontext->font_face(m_font.c_str());
         pcontext->font_size(font_size());
         float bounds[4];
         if (m_fixed_size.x() > 0) {
            pcontext->text_align(::nano2d::e_align_left | ::nano2d::e_align_top);
            pcontext->text_box_bounds((float)m_pos.x(), (float)m_pos.y(), (float)m_fixed_size.x(), m_caption, bounds);
            m_sizePreferred = Vector2i(m_fixed_size.x(), (int)(bounds[3] - bounds[1]));
         }
         else {
            pcontext->text_align(::nano2d::e_align_left | ::nano2d::e_align_middle);
            int iSize = (int) pcontext->text_bounds(0.f, 0.f, m_caption, bounds);
            m_sizePreferred = Vector2i(
                iSize +2 ,
               (int)(int)(bounds[3] - bounds[1])
            );
         }
      }
   }
   return m_sizePreferred;
}

void Label::draw(::nano2d::context * pcontext) {
   Widget::draw(pcontext);
   pcontext->font_face(m_font.c_str());
   pcontext->font_size(font_size());
   pcontext->fill_color(m_color);
   if (m_fixed_size.x() > 0) {
      pcontext->text_align(::nano2d::e_align_left | ::nano2d::e_align_top);
      pcontext->text_box((float)m_pos.x(), (float)m_pos.y(), (float)m_fixed_size.x(), m_caption);
   }
   else {
      pcontext->text_align(::nano2d::e_align_left | ::nano2d::e_align_middle);
      pcontext->text((float)m_pos.x(), (float)m_pos.y() + m_size.y() * 0.5f, m_caption);
   }
}


//void Label::_nanoui_to_user(::user::interaction * puserinteraction)
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
//   //Widget::_nanoui_to_user(m_pstill);
//
//}



} // namespace nanoui


