#include "framework.h"
#include "calculator.h"


namespace calculator
{


   plain_edit_impact::plain_edit_impact()
   {

      m_pcallback = nullptr;

      m_val.m_dR = 0.0;
      m_val.m_dI = 0.0;

   }


   plain_edit_impact::~plain_edit_impact()
   {

   }




   bool plain_edit_impact::keyboard_focus_is_focusable()
   {

      return is_window_enabled() && is_window_visible();

   }


   ::payload plain_edit_impact::get_ex_value()
   {

      ::payload v;

      v["real"] = m_val.m_dR;
      v["imaginary"] = m_val.m_dI;
      v["text"] = ::user::plain_edit::get_ex_value();

      return v;

   }


   void plain_edit_impact::set_format(const string& strFormat)
   {

      m_strFormat = strFormat;

   }


   void plain_edit_impact::set_callback(callback* pcallback)
   {

      m_pcallback = pcallback;

   }


} // namespace calculator


::user::plain_edit* new_calculator_plain_edit()
{

   return new ::calculator::plain_edit_impact();

}



