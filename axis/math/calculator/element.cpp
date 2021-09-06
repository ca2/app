#include "framework.h"



namespace calculator
{

   element::element()
   {
      m_pparent   = nullptr;
      m_pelement1 = nullptr;
      m_pelement2 = nullptr;
      m_pelement3 = nullptr;
   }

   element::~element()
   {
   }


   double pi();


   result element::get_result()
   {

      if(m_ptoken->m_etype == token::type_identifier)
      {

         class result result;

         if(m_ptoken->m_str.compare_ci("pi") == 0)
         {
            result.m_dR = pi();
         }
         else
         {
            throw ::exception::exception(error_failed, "unknown identifier");
         }
         return result;
      }
      else if(m_ptoken->m_etype == token::type_number)
      {
         class result result;
         result.m_dR = atof(m_ptoken->m_str);
         return result;
      }
      else if(m_ptoken->m_etype == token::type_imaginary)
      {
         class result result;
         result.m_dI = atof(m_ptoken->m_str);
         return result;
      }
      else if(m_ptoken->m_etype == token::type_addition)
      {
         if(m_pelement2 == nullptr)
            return m_pelement1->get_result();
         else
            return m_pelement1->get_result() + m_pelement2->get_result();
      }
      else if(m_ptoken->m_etype == token::type_subtraction)
      {

         if(m_pelement2 == nullptr)
         {

            class result valueZero;

            return valueZero - m_pelement1->get_result();

         }
         else
         {

            return m_pelement1->get_result() - m_pelement2->get_result();

         }

      }
      else if(m_ptoken->m_etype == token::type_multiplication)
      {
         return m_pelement1->get_result() * m_pelement2->get_result();
      }
      else if(m_ptoken->m_etype == token::type_division)
      {
         return m_pelement1->get_result() / m_pelement2->get_result();
      }
      else if(m_ptoken->m_etype == token::type_function)
      {
         if(m_ptoken->m_str == "sqr")
         {
            return m_pelement1->get_result() * m_pelement1->get_result();
         }
         else if(m_ptoken->m_str == "sqrt")
         {
            return sqrt(m_pelement1->get_result());
         }
         else if(m_ptoken->m_str == "exp")
         {
            return exp(m_pelement1->get_result());
         }
         else if(m_ptoken->m_str == "ln")
         {
            return log(m_pelement1->get_result());
         }
         else if(m_ptoken->m_str == "log")
         {
            class result result;
            result.m_dR = 10.0;
            return log(m_pelement1->get_result()) / log(result);
         }
         else if(m_ptoken->m_str == "pow")
         {
            return pow(m_pelement1->get_result(), m_pelement2->get_result());
         }
         else if(m_ptoken->m_str == "atan")
         {
            return atan(m_pelement1->get_result());
         }
         else if(m_ptoken->m_str == "asin")
         {
            return asin(m_pelement1->get_result());
         }
         else if(m_ptoken->m_str == "acos")
         {
            return acos(m_pelement1->get_result());
         }
         else if(m_ptoken->m_str == "tan")
         {
            return tan(m_pelement1->get_result());
         }
         else if(m_ptoken->m_str == "sin")
         {
            return sin(m_pelement1->get_result());
         }
         else if(m_ptoken->m_str == "cos")
         {
            return cos(m_pelement1->get_result());
         }
         else
         {
            throw ::exception::exception(error_failed, "unknown function");
         }
      }

      class result valueZero;

      return valueZero;

   }


   string element::get_expression()
   {
      if(m_ptoken->m_etype == token::type_number || m_ptoken->m_etype == token::type_identifier)
      {
         return m_ptoken->m_str;
      }
      else if(m_ptoken->m_etype == token::type_imaginary)
      {
         return "i" + m_ptoken->m_str;
      }
      else if(m_ptoken->m_etype == token::type_addition)
      {
         if(m_pelement2 == nullptr)
            return "(" + m_pelement1->get_expression() + ")";
         else
            return "(" + m_pelement1->get_expression() + " + " + m_pelement2->get_expression() + ")";
      }
      else if(m_ptoken->m_etype == token::type_subtraction)
      {
         if(m_pelement2 == nullptr)
            return "( - " + m_pelement1->get_expression() + ")";
         else
            return "(" + m_pelement1->get_expression() + " - " + m_pelement2->get_expression() + ")";
      }
      else if(m_ptoken->m_etype == token::type_multiplication)
      {
         return "(" + m_pelement1->get_expression() + " * " + m_pelement2->get_expression() + ")";
      }
      else if(m_ptoken->m_etype == token::type_division)
      {
         return "(" + m_pelement1->get_expression() + " / " + m_pelement2->get_expression() + ")";
      }
      else if(m_ptoken->m_etype == token::type_function)
      {
         if(m_ptoken->m_str == "sqr")
         {
            return "sqr(" + m_pelement1->get_expression() + ")";
         }
         else if(m_ptoken->m_str == "sqrt")
         {
            return "sqrt(" + m_pelement1->get_expression() + ")";
         }
         else if(m_ptoken->m_str == "exp")
         {
            return "exp(" + m_pelement1->get_expression() + ")";
         }
         else if(m_ptoken->m_str == "ln")
         {
            return "ln(" + m_pelement1->get_expression() + ")";
         }
         else if(m_ptoken->m_str == "log")
         {
            return "log(" + m_pelement1->get_expression() + ")";
         }
         else if(m_ptoken->m_str == "pow")
         {
            return "pow(" + m_pelement1->get_expression() + ", "
                + m_pelement2->get_expression() + ")";
         }
         else
         {

            throw ::exception::exception(error_failed, "unknown function");

         }

      }

      return "not supported operation";

   }



} // namespace calculator
