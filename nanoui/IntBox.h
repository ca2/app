/**
 * \class IntBox textbox.h nanoui/textbox.h
 *
 * \brief A specialization of TextBox for representing integral values.
 *
 * Template parameters should be integral types, e.g. ``int``, ``long``,
 * ``uint32_t``, etc.
 */
// From TextBox.h by camilo on 2023-05-16 14:21 <3ThomasBorregaardSorensen!!
#pragma once


#include "TextBox.h"


namespace nanoui
{


   template <typename Scalar> class IntBox : public TextBox 
   {
   public:


      Scalar m_iMouseDownValue;
      Scalar m_iIncrementValue;
      Scalar m_iMinimumValue;
      Scalar m_iMaximumValue;


      IntBox(Widget* parent, Scalar value = (Scalar)0) : TextBox(parent) {
         set_default_value("0");
         set_format(::std::is_signed<Scalar>::value ? "[-]?[0-9]*" : "[0-9]*");
         set_value_increment(1);
         set_minimum_maximum_values(::std::numeric_limits<Scalar>::lowest(), ::std::numeric_limits<Scalar>::max());
         set_value(value, e_source_initialize);
         set_spinnable(false);
      }

      Scalar value() const {
         Scalar value = 0;
         from_string(value, TextBox::value());
         return value;
      }

      void set_value(Scalar value, const ::action_context & actioncontext) {
         Scalar clamped_value = ::minimum(::maximum(value, m_iMinimumValue), m_iMaximumValue);
         TextBox::set_value(::as_string(clamped_value), actioncontext);
      }

      void set_callback(const ::function<void(Scalar)>& cb) {
         TextBox::set_callback(
            [cb, this](const ::scoped_string& str) {
               Scalar value = 0;
               from_string(value, str);
               set_value(value, e_source_sync);
               cb(value);
               return true;
            }
         );
      }

      void set_value_increment(Scalar iIncrementValue) {
         m_iIncrementValue = iIncrementValue;
      }

      void set_minimum_value(Scalar iMinimumValue) {
         m_iMinimumValue = iMinimumValue;
      }

      void set_maximum_value(Scalar iMaximumValue) {
         m_iMaximumValue = iMaximumValue;
      }

      void set_minimum_maximum_values(Scalar min_value, Scalar max_value) 
      {

         set_minimum_value(min_value);

         set_maximum_value(max_value);

      }


      virtual bool mouse_button_event(const point_i32& p, ::user::e_mouse emouse, bool down, bool bDoubleClick, const ::user::e_key& ekeyModifiers) override
      {

         if ((m_bEditable || m_bSpinnable) && down)
         {

            m_iMouseDownValue = value();

         }

         SpinArea area = spin_area(p);

         if (m_bSpinnable && area != SpinArea::None && down && !focused()) 
         {

            if (area == SpinArea::Top) 
            {
            
               set_value(value() + m_iIncrementValue, e_source_user);

               if (m_callback)
               {

                  m_callback(m_strValue);

               }

            }
            else if (area == SpinArea::Bottom) 
            {
            
               set_value(value() - m_iIncrementValue, e_source_user);

               if (m_callback)
               {

                  m_callback(m_strValue);

               }

            }
            
            return true;

         }

         return TextBox::mouse_button_event(p, emouse, down, bDoubleClick, ekeyModifiers);

      }


      virtual bool mouse_motion_event(const point_i32& p, const size_i32& rel, bool bDown, const ::user::e_key& ekeyModifiers) override
      {

         if (TextBox::mouse_motion_event(p, rel, bDown, ekeyModifiers))
         {

            return true;

         }

         if (bDown && m_bSpinnable && !focused() && ekeyModifiers & ::user::e_key_right_button && is_mouse_down())
         {

            int value_delta = static_cast<int>((p.x() - m_pointMouseDown.x()) / float(10));

            set_value(m_iMouseDownValue + value_delta * m_iIncrementValue, e_source_user);

            if (m_callback)
            {

               m_callback(m_strValue);

            }

            return true;

         }

         return false;

      }


      virtual bool scroll_event(const point_i32& p, const size_f32& rel) override
      {

         if (Widget::scroll_event(p, rel))
         {

            return true;

         }

         if (m_bSpinnable && !focused())
         {

            int value_delta = (rel.cy() > 0) ? 1 : -1;

            set_value(value() + value_delta * m_iIncrementValue, e_source_user);

            if (m_callback)
            {

               m_callback(m_strValue);

            }

            return true;

         }

         return false;

      }

   };


} // namespace nanoui



