/*
    src/m_pcheckbox.cpp -- Two-state check box pwidget

    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The pwidget drawing code is based on the NanoVG demo application
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
      : Widget(parent), m_strCaption(caption), m_bChecked(false), m_callback(callback) 
   {
   
      m_icon_extra_scale = 1.2f; // pwidget override

   }


   bool CheckBox::mouse_button_event(const vector2_i32& p, ::user::e_mouse emouse, bool down, bool bDoubleClick, const ::user::e_key& ekeyModifiers)
   {

      Widget::mouse_button_event(p, emouse, down, bDoubleClick, ekeyModifiers);

      if (!m_bEnabled)
      {

         return false;

      }

      if (emouse == ::user::e_mouse_left_button) 
      {

         auto pscreen = screen();

         if (down) 
         {

            pscreen->m_pwidgetMouseDown = this;

         }
         else
         {

            if (pscreen->m_pwidgetMouseDown == this)
            {

               bool bChecked = checked();

               set_checked (!bChecked, e_source_user);

            }

         }

         return true;

      }

      return false;

   }


   vector2_i32 CheckBox::preferred_size(::nano2d::context* pcontext, bool bRecalcTextSize)
   {

      if (bRecalcTextSize)
      {

         if (m_fixed_size != vector2_i32(0))
         {
            m_sizePreferred = m_fixed_size;

         }
         else
         {
            pcontext->font_size(font_size());
            pcontext->font_face("sans");
            m_sizePreferred = vector2_i32(
               (int)(pcontext->text_bounds(0, 0, m_strCaption, nullptr) +
                  1.8f * font_size()),
               (int)(font_size() * 1.3f));
         }
      }

      return m_sizePreferred;

   }


   /// Sets whether or not this CheckBox is currently pushed.
   void CheckBox::set_checked(bool bChecked, const ::action_context& actioncontext)
   {

      if (::is_different(m_bChecked, bChecked))
      {

         m_bChecked = bChecked;

         if (m_strAnnotation == "SnakeCheckbox1")
         {

            if (m_bChecked)
            {

               INFORMATION("SnakeCheckbox1 Checked");

            }
            else
            {

               INFORMATION("SnakeCheckbox1 Checked");

            }

         }

         if (actioncontext.is_user_source() && m_callback)
         {

            m_callback(bChecked);

         }

         set_need_redraw();

         post_redraw();

      }

   }


   void CheckBox::draw(::nano2d::context* pcontext) 
   {

      Widget::draw(pcontext);

      pcontext->font_size(font_size());

      pcontext->font_face("sans");

      auto colorFill = m_bEnabled ? m_ptheme->m_colorText : m_ptheme->m_colorDisableText;

      pcontext->fill_color(colorFill);

      pcontext->text_align(::nano2d::e_align_left | ::nano2d::e_align_middle);

      pcontext->text(m_pos.x() + 1.6f * font_size(), m_pos.y() + m_size.y() * 0.5f,
         m_strCaption);

      ::nano2d::paint bg = pcontext->box_gradient(m_pos.x() + 1.5f, m_pos.y() + 1.5f,
         m_size.y() - 2.0f, m_size.y() - 2.0f, 3, 3,
         is_mouse_down() ? ::color::color(0, 100) : ::color::color(0, 32),
                                                  ::color::color(0, 0, 0, 180));

      pcontext->begin_path();

      pcontext->rounded_rectangle(m_pos.x() + 1.0f, m_pos.y() + 1.0f, m_size.y() - 2.0f,
         m_size.y() - 2.0f, 3);

      pcontext->fill_paint(bg);

      pcontext->fill();

      if (m_bChecked) 
      {

         FORMATTED_INFORMATION("draw \"%s\" Checked!!", m_strAnnotation.c_str());

         pcontext->font_size(icon_scale() * m_size.y());
         
         pcontext->font_face("icons");

         auto colorFill = m_bEnabled ? m_ptheme->m_colorIcon : m_ptheme->m_colorDisableText;
         
         pcontext->fill_color(colorFill);
         
         pcontext->text_align(::nano2d::e_align_center | ::nano2d::e_align_middle);

         vector2_f32 pointText(m_pos.x() + m_size.y() * 0.5f + 1.f, m_pos.y() + m_size.y() * 0.5f);
         
         pcontext->text(pointText.x(), pointText.y(), get_utf8_character(m_ptheme->m_efontawesomeCheckBox).data());

      }
      else
      {

         FORMATTED_INFORMATION("no draw \"%s\" Not checked!!", m_strAnnotation.c_str());

      }

   }


} // namespace nanoui


