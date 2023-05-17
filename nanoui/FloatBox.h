/**
 * \class FloatBox textbox.h nanoui/textbox.h
 *
 * \brief A specialization of TextBox representing floating point values.

 *  The emplate parametersshould a be floating point type, e.g. ``float`` or
 *  ``double``.
 */
 // From TextBox.h by camilo on 2023-05-16 14:22 <3ThomasBorregaardSorensen!!
#pragma once


#include "TextBox.h"


namespace nanoui
{


   template <typename Scalar> class FloatBox : public TextBox {
   public:
      FloatBox(Widget* parent, Scalar value = (Scalar)0.f) : TextBox(parent) {
         m_number_format = sizeof(Scalar) == sizeof(float) ? "%.4g" : "%.7g";
         set_default_value("0");
         set_format("[-+]?[0-9]*\\.?[0-9]+([e_e][-+]?[0-9]+)?");
         set_value_increment((Scalar)0.1);
         set_minimum_maximum_values(std::numeric_limits<Scalar>::lowest(),
            std::numeric_limits<Scalar>::max());
         set_value(value);
         set_spinnable(false);
      }

      ::string number_format() const { return m_number_format; }

      void number_format(const ::scoped_string& format) { m_number_format = format; }

      Scalar value() const
      {
         Scalar scalar;
         ::from_string(scalar, TextBox::value());
         return scalar;
      }

      void set_value(Scalar value) {
         Scalar clamped_value = std::min(std::max(value, m_min_value), m_max_value);
         char buffer[50];
         std::snprintf(buffer, 50, m_number_format.c_str(), clamped_value);
         TextBox::set_value(buffer);
      }

      void set_callback(const ::function<void(Scalar)>& cb) {
         TextBox::set_callback([cb, this](const ::scoped_string& str) {
            Scalar scalar;
            ::from_string(scalar, str);
            set_value(scalar);
            cb(scalar);
            return true;
            });
      }

      void set_value_increment(Scalar incr) {
         m_value_increment = incr;
      }

      void set_minimum_value(Scalar min_value) {
         m_min_value = min_value;
      }

      void set_maximum_value(Scalar max_value)
      {

         m_max_value = max_value;

      }


      void set_minimum_maximum_values(Scalar min_value, Scalar max_value)
      {

         set_minimum_value(min_value);

         set_maximum_value(max_value);

      }


      bool mouse_button_event(const Vector2i& p, ::user::e_mouse emouse, bool down, bool bDoubleClick, const ::user::e_key& ekeyModifiers) override
      {

         if ((m_bEditable || m_bSpinnable) && down)
         {

            m_mouse_down_value = value();

         }

         SpinArea area = spin_area(p);

         if (m_bSpinnable && area != SpinArea::None && down && !focused())
         {

            if (area == SpinArea::Top)
            {

               set_value(value() + m_value_increment);

               if (m_callback)
               {

                  m_callback(m_strValue);

               }

            }
            else if (area == SpinArea::Bottom)
            {

               set_value(value() - m_value_increment);

               if (m_callback)
               {

                  m_callback(m_strValue);

               }

            }

            return true;

         }

         return TextBox::mouse_button_event(p, emouse, down, bDoubleClick, ekeyModifiers);

      }


      bool mouse_motion_event(const Vector2i& p, const Vector2i& rel, bool bDown, const ::user::e_key& ekeyModifiers) override
      {

         if (TextBox::mouse_motion_event(p, rel, bDown, ekeyModifiers))
         {

            return true;

         }

         if (m_bSpinnable && !focused() && ekeyModifiers & ::user::e_key_right_button && m_pointMouseDown.x() != -1)
         {

            int value_delta = static_cast<int>((p.x() - m_pointMouseDown.x()) / float(10));

            set_value(m_mouse_down_value + value_delta * m_value_increment);

            if (m_callback)
            {

               m_callback(m_strValue);

            }

            return true;

         }

         return false;

      }


      virtual bool scroll_event(const Vector2i& p, const Vector2f& rel) override
      {

         if (Widget::scroll_event(p, rel))
         {

            return true;

         }

         if (m_bSpinnable && !focused())
         {

            int value_delta = (rel.y() > 0) ? 1 : -1;

            set_value(value() + value_delta * m_value_increment);

            if (m_callback)
            {

               m_callback(m_strValue);

            }

            return true;

         }

         return false;

      }

   private:

      ::string m_number_format;

      Scalar m_mouse_down_value;

      Scalar m_value_increment;

      Scalar m_min_value, m_max_value;

   };



} // namespace nanoui



