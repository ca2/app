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
#include "acme/constant/timer.h"
#include "acme/constant/user_key.h"
#include "aqua/platform/tinyexpr.h"
#include "aura/user/user/interaction.h"


namespace nanoui
{


   template <typename Scalar> class IntBox : public TextBox
   {
   public:


      Scalar m_iMouseDownValue;
      Scalar m_iIncrementValue;
      Scalar m_iMinimumValue;
      Scalar m_iMaximumValue;
      SpinArea m_spingareaMouseDown;


      IntBox(Widget* parent, Scalar value = (Scalar)0) : TextBox(parent) {
         set_default_value("0");
         //set_format(::std::is_signed<Scalar>::value ? "[-]?[0-9]*" : "[0-9]*");
         set_value_increment(1);
         set_minimum_maximum_values(::std::numeric_limits<Scalar>::lowest(), ::std::numeric_limits<Scalar>::max());
         set_value(value, e_source_initialize);
         set_spinnable(false);
      }

      Scalar value() const {
         Scalar value = 0;

         value = calc_dimension(TextBox::value());
         return value;
      }

      Scalar calc_dimension(const ::scoped_string& scopedstr) const
      {
         Scalar res = 0;
         double r = tinyexpr::te_interp(::string(scopedstr), nullptr);
         if (!std::isnan(r))
            res = ::maximum(static_cast<decltype(res)>(r), static_cast<decltype(res)>(0));
         return res;
      }

      void set_value(Scalar value, const ::action_context& actioncontext) {
         Scalar clamped_value = ::minimum(::maximum(value, m_iMinimumValue), m_iMaximumValue);
         TextBox::set_value(::as_string(clamped_value), actioncontext);
      }

      void set_callback(const ::function<void(Scalar)>& cb) {
         TextBox::set_callback(
            [cb, this](const ::scoped_string& str) {
               Scalar value = 0;
               try
               {
                  value = calc_dimension(str);
               }
               catch (...)
               {
                  value = 0;
               }
               set_value(value, e_source_user);
               cb(this->value());
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

      int m_iIncrementStep;

      virtual bool mouse_button_event(const int_point& p, ::user::e_mouse emouse, bool down, bool bDoubleClick, const ::user::e_key& ekeyModifiers) override
      {

         if ((m_bEditable || m_bSpinnable) && down)
         {

            m_iMouseDownValue = value();

         }

         m_spingareaMouseDown = spin_area(p);

         //if (m_bSpinnable && area != SpinArea::None && down && !focused()) 
         if (m_bSpinnable)
         {

            if (down)
            {

               if (m_spingareaMouseDown != SpinArea::None)
               {

                  if (m_spingareaMouseDown == SpinArea::Top)
                  {

                     set_value(value() + m_iIncrementValue, e_source_user);

                     if (m_callback)
                     {

                        m_callback(m_strValue);

                     }

                     screen()->m_puserinteraction->set_timer(((uptr)this) + 10, 600_ms, [this]()
                     {

                        screen()->m_puserinteraction->kill_timer(((uptr)this) + 10);

                        m_iIncrementStep = 0;

                        screen()->m_puserinteraction->set_timer(((uptr)this) + 11, 200_ms, [this]()
                        {

                           if (value() + m_iIncrementValue <= m_iMaximumValue
                              && m_spingareaMouseDown == SpinArea::Top)
                           {

                              m_iIncrementStep++;

                              set_value(value() + m_iIncrementValue, e_source_user);
                              
                              if (m_callback)
                              {

                                 m_callback(m_strValue);
                                 
                              }

                              if (m_iIncrementStep > 5)
                              {

                                 screen()->m_puserinteraction->kill_timer(((uptr)this) + 11);

                                 screen()->m_puserinteraction->set_timer(((uptr)this) + 12, 50_ms, [this]()
                                 {
                                 
                                       if (value() + m_iIncrementValue <= m_iMaximumValue
                                          && m_spingareaMouseDown == SpinArea::Top)
                                       {

                                          m_iIncrementStep++;

                                          set_value(value() + m_iIncrementValue, e_source_user);

                                          if (m_callback)
                                          {

                                             m_callback(m_strValue);

                                          }

                                       }
                                       else
                                       {

                                          screen()->m_puserinteraction->kill_timer(((uptr)this) + 12);

                                       }


                                    });

                                 }
                              
                           }
                           else
                           {
                           
                              screen()->m_puserinteraction->kill_timer(((uptr)this) + 11);
                              
                           }

                       });

                     });

               }
               else if (m_spingareaMouseDown == SpinArea::Bottom)
               {

                  set_value(value() - m_iIncrementValue, e_source_user);

                  if (m_callback)
                  {

                     m_callback(m_strValue);

                  }
                  screen()->m_puserinteraction->set_timer(((uptr)this) + 20, 600_ms, [this]()
                     {

                        screen()->m_puserinteraction->kill_timer(((uptr)this) + 20);
                        m_iIncrementStep = 0;
                        screen()->m_puserinteraction->set_timer(((uptr)this) + 21, 200_ms, [this]()
                           {

                              if (value() - m_iIncrementValue >= m_iMinimumValue
                                 && m_spingareaMouseDown == SpinArea::Bottom)
                              {
                                 m_iIncrementStep++;
                                 set_value(value() - m_iIncrementValue, e_source_user);
                                 if (m_callback)
                                 {
                                    m_callback(m_strValue);
                                 }
                                 if (m_iIncrementStep > 5)
                                 {

                                    screen()->m_puserinteraction->kill_timer(((uptr)this) + 21);
                                    screen()->m_puserinteraction->set_timer(((uptr)this) + 22, 50_ms, [this]()
                                       {

                                          if (value() - m_iIncrementValue >= m_iMinimumValue
                                             && m_spingareaMouseDown == SpinArea::Bottom)
                                          {
                                             m_iIncrementStep++;
                                             set_value(value() - m_iIncrementValue, e_source_user);
                                             if (m_callback)
                                             {
                                                m_callback(m_strValue);
                                             }
                                          }
                                          else
                                          {
                                             screen()->m_puserinteraction->kill_timer(((uptr)this) + 22);
                                          }

                                       });

                                 }

                              }
                              else
                              {
                                 screen()->m_puserinteraction->kill_timer(((uptr)this) + 21);
                              }


                           });

               });
            }

            return true;

         }

      }
            else if (m_spingareaMouseDown != SpinArea::None)
            {

               m_spingareaMouseDown = SpinArea::None;

               screen()->m_puserinteraction->kill_timer(((uptr)this) + 10);
               screen()->m_puserinteraction->kill_timer(((uptr)this) + 11);
               screen()->m_puserinteraction->kill_timer(((uptr)this) + 12);
               screen()->m_puserinteraction->kill_timer(((uptr)this) + 20);
               screen()->m_puserinteraction->kill_timer(((uptr)this) + 21);
               screen()->m_puserinteraction->kill_timer(((uptr)this) + 22);

               }

   }

   return TextBox::mouse_button_event(p, emouse, down, bDoubleClick, ekeyModifiers);

}


virtual bool mouse_motion_event(const int_point& p, const int_size& rel, bool bDown, const ::user::e_key& ekeyModifiers) override
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


virtual bool scroll_event(const int_point& p, const float_size& rel) override
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



