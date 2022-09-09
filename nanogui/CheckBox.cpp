/*
    src/m_pcheckbox.cpp -- Two-state check box widget

    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The widget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/
#include "framework.h"
#include "CheckBox.h"
#include "Screen.h"
#include "aura/user/user/interaction.h"


NAMESPACE_BEGIN(nanogui)

CheckBox::CheckBox(Widget * parent, const std::string & caption,
   const ::function<void(bool) > & callback)
   : Widget(parent), m_caption(caption), m_bMouseDown(false), m_checked(false),
   m_callback(callback) {
   m_icon_extra_scale = 1.2f; // widget override
}

bool CheckBox::mouse_button_event(const Vector2i & p, int button, bool down, const ::user::e_key & ekeyModifiers) 
{
   Widget::mouse_button_event(p, button, down, ekeyModifiers);
   if (!m_enabled)
      return false;

   if (button == ::user::e_mouse_left_button) {
      if (down) {
         m_bMouseDown = true;
         screen()->m_puserinteraction->set_need_redraw();
         screen()->m_puserinteraction->post_redraw();
      }
      else if (m_bMouseDown) {
         if (contains(p)) {
            m_checked = !m_checked;
            screen()->m_puserinteraction->set_need_redraw();
            screen()->m_puserinteraction->post_redraw();
            screen()->m_puserinteraction->fork([this]()
               {
                  if (m_callback)
                     m_callback(m_checked);

               });
         }
         m_bMouseDown = false;
      }
      return true;
   }
   return false;
}

Vector2i CheckBox::preferred_size(NVGcontext * ctx, bool bRecalcTextSize)
{

   if(bRecalcTextSize)
   {

      if (m_fixed_size != Vector2i(0))
      {
         m_sizePreferred = m_fixed_size;

      }
      else
      {
         nvgFontSize(ctx, font_size());
         nvgFontFace(ctx, "sans");
         m_sizePreferred = Vector2i(
            (int)(nvgTextBounds(ctx, 0, 0, m_caption.c_str(), nullptr, nullptr) +
               1.8f * font_size()),
            (int)(font_size() * 1.3f));
      }
   }

   return m_sizePreferred;

}

void CheckBox::draw(NVGcontext * ctx) {
   Widget::draw(ctx);

   nvgFontSize(ctx, font_size());
   nvgFontFace(ctx, "sans");
   nvgFillColor(ctx,
      m_enabled ? m_theme->m_text_color : m_theme->m_disabled_text_color);
   nvgTextAlign(ctx, NVG_ALIGN_LEFT | NVG_ALIGN_MIDDLE);
   nvgText(ctx, m_pos.x() + 1.6f * font_size(), m_pos.y() + m_size.y() * 0.5f,
      m_caption.c_str(), nullptr);

   NVGpaint bg = nvgBoxGradient(ctx, m_pos.x() + 1.5f, m_pos.y() + 1.5f,
      m_size.y() - 2.0f, m_size.y() - 2.0f, 3, 3,
      m_bMouseDown ? Color(0, 100) : Color(0, 32),
      Color(0, 0, 0, 180));

   nvgBeginPath(ctx);
   nvgRoundedRect(ctx, m_pos.x() + 1.0f, m_pos.y() + 1.0f, m_size.y() - 2.0f,
      m_size.y() - 2.0f, 3);
   nvgFillPaint(ctx, bg);
   nvgFill(ctx);

   if (m_checked) {
      nvgFontSize(ctx, icon_scale() * m_size.y());
      nvgFontFace(ctx, "icons");
      nvgFillColor(ctx, m_enabled ? m_theme->m_icon_color
         : m_theme->m_disabled_text_color);
      nvgTextAlign(ctx, NVG_ALIGN_CENTER | NVG_ALIGN_MIDDLE);
      nvgText(ctx, m_pos.x() + m_size.y() * 0.5f + 1,
         m_pos.y() + m_size.y() * 0.5f, get_utf8_character(m_theme->m_check_box_icon).data(),
         nullptr);
   }
}

NAMESPACE_END(nanogui)
