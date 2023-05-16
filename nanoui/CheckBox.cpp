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
#include "nano2d/context.h"


namespace nanoui
{


   CheckBox::CheckBox(Widget* parent, const ::scoped_string& caption, const ::function<void(bool) >& callback)
      : Widget(parent), m_caption(caption), m_bMouseDown(false), m_checked(false), m_callback(callback) 
   {
   
      m_icon_extra_scale = 1.2f; // widget override

   }


   bool CheckBox::mouse_button_event(const Vector2i& p, ::user::e_mouse emouse, bool down, bool bDoubleClick, const ::user::e_key& ekeyModifiers)
   {

      Widget::mouse_button_event(p, emouse, down, bDoubleClick, ekeyModifiers);

      if (!m_enabled)
      {

         return false;

      }

      if (emouse == ::user::e_mouse_left_button) 
      {

         if (down) 
         {

            m_bMouseDown = true;

            set_need_redraw();

            post_redraw();

         }
         else if (m_bMouseDown) 
         {

            if (contains(p)) 
            {

               m_checked = !m_checked;

               set_need_redraw();

               post_redraw();

               screen()->m_puserinteraction->fork([this]()
               {

                  if (m_callback)
                     m_callback(m_checked);

               });

            }

            m_bMouseDown = false;

            set_need_redraw();

            post_redraw();

         }

         return true;

      }

      return false;

   }


   Vector2i CheckBox::preferred_size(::nano2d::context* pcontext, bool bRecalcTextSize)
   {

      if (bRecalcTextSize)
      {

         if (m_fixed_size != Vector2i(0))
         {
            m_sizePreferred = m_fixed_size;

         }
         else
         {
            pcontext->font_size(font_size());
            pcontext->font_face("sans");
            m_sizePreferred = Vector2i(
               (int)(pcontext->text_bounds(0, 0, m_caption, nullptr) +
                  1.8f * font_size()),
               (int)(font_size() * 1.3f));
         }
      }

      return m_sizePreferred;

   }

   void CheckBox::draw(::nano2d::context* pcontext) {
      Widget::draw(pcontext);

      pcontext->font_size(font_size());
      pcontext->font_face("sans");
      pcontext->fill_color(
         m_enabled ? m_theme->m_text_color : m_theme->m_disabled_text_color);
      pcontext->text_align(::nano2d::e_align_left | ::nano2d::e_align_middle);
      pcontext->text(m_pos.x() + 1.6f * font_size(), m_pos.y() + m_size.y() * 0.5f,
         m_caption);

      ::nano2d::paint bg = pcontext->box_gradient(m_pos.x() + 1.5f, m_pos.y() + 1.5f,
         m_size.y() - 2.0f, m_size.y() - 2.0f, 3, 3,
         m_bMouseDown ? ::color::color(0, 100) :  ::color::color(0, 32),
                                                  ::color::color(0, 0, 0, 180));

      pcontext->begin_path();
      pcontext->rounded_rectangle(m_pos.x() + 1.0f, m_pos.y() + 1.0f, m_size.y() - 2.0f,
         m_size.y() - 2.0f, 3);
      pcontext->fill_paint(bg);
      pcontext->fill();

      if (m_checked) {
         pcontext->font_size(icon_scale() * m_size.y());
         pcontext->font_face("icons");
         pcontext->fill_color(m_enabled ? m_theme->m_icon_color
            : m_theme->m_disabled_text_color);
         pcontext->text_align(::nano2d::e_align_center | ::nano2d::e_align_middle);
         pcontext->text(m_pos.x() + m_size.y() * 0.5f + 1,
            m_pos.y() + m_size.y() * 0.5f, get_utf8_character(m_theme->m_check_box_icon).data());
      }
   }



} // namespace nanoui


