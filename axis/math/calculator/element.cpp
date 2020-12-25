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

   payload element::get_payload()
   {
      if(m_ptoken->m_etype == token::type_identifier)
      {
         class payload payload;
         if(m_ptoken->m_str.compare_ci("pi") == 0)
         {
            payload.m_dR = pi();
         }
         else
         {
            __throw(::exception::exception("unknown identifier"));
         }
         return payload;
      }
      else if(m_ptoken->m_etype == token::type_number)
      {
         class payload payload;
         payload.m_dR = atof(m_ptoken->m_str);
         return payload;
      }
      else if(m_ptoken->m_etype == token::type_imaginary)
      {
         class payload payload;
         payload.m_dI = atof(m_ptoken->m_str);
         return payload;
      }
      else if(m_ptoken->m_etype == token::type_addition)
      {
         if(m_pelement2 == nullptr)
            return m_pelement1->get_payload();
         else
            return m_pelement1->get_payload() + m_pelement2->get_payload();
      }
      else if(m_ptoken->m_etype == token::type_subtraction)
      {

         if(m_pelement2 == nullptr)
         {

            class payload valueZero;

            return valueZero - m_pelement1->get_payload();

         }
         else
         {

            return m_pelement1->get_payload() - m_pelement2->get_payload();

         }

      }
      else if(m_ptoken->m_etype == token::type_multiplication)
      {
         return m_pelement1->get_payload() * m_pelement2->get_payload();
      }
      else if(m_ptoken->m_etype == token::type_division)
      {
         return m_pelement1->get_payload() / m_pelement2->get_payload();
      }
      else if(m_ptoken->m_etype == token::type_function)
      {
         if(m_ptoken->m_str == "sqr")
         {
            return m_pelement1->get_payload() * m_pelement1->get_payload();
         }
         else if(m_ptoken->m_str == "sqrt")
         {
            return sqrt(m_pelement1->get_payload());
         }
         else if(m_ptoken->m_str == "exp")
         {
            return exp(m_pelement1->get_payload());
         }
         else if(m_ptoken->m_str == "ln")
         {
            return log(m_pelement1->get_payload());
         }
         else if(m_ptoken->m_str == "log")
         {
            class payload payload;
            payload.m_dR = 10.0;
            return log(m_pelement1->get_payload()) / log(payload);
         }
         else if(m_ptoken->m_str == "pow")
         {
            return pow(m_pelement1->get_payload(), m_pelement2->get_payload());
         }
         else if(m_ptoken->m_str == "atan")
         {
            return atan(m_pelement1->get_payload());
         }
         else if(m_ptoken->m_str == "asin")
         {
            return asin(m_pelement1->get_payload());
         }
         else if(m_ptoken->m_str == "acos")
         {
            return acos(m_pelement1->get_payload());
         }
         else if(m_ptoken->m_str == "tan")
         {
            return tan(m_pelement1->get_payload());
         }
         else if(m_ptoken->m_str == "sin")
         {
            return sin(m_pelement1->get_payload());
         }
         else if(m_ptoken->m_str == "cos")
         {
            return cos(m_pelement1->get_payload());
         }
         else
         {
            __throw(::exception::exception("unknown function"));
         }
      }

      class payload valueZero;

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
            __throw(::exception::exception("unknown function"));
         }
      }
      return "not supported operation";
   }



} // namespace calculator
