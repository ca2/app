/* (C) Copyright 2008 Nick Mudge <mudgen@gmail.com>
 * This code can be freely copied and modified.
 */
#include "framework.h"


namespace datetime
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


   value element::get_value(::object * pobject, const ::aura::str_context * pcontext, i32 & iPath, i32 & iPathCount) const
   {

      if(m_ptoken->value == token::number || m_ptoken->value == token::identifier)
      {

         return strtotime(pobject, pcontext, m_ptoken->m_str, iPath, iPathCount);

      }
      else if(m_ptoken->value == token::addition)
      {

         if (m_pelement2 == nullptr)
         {

            return m_pelement1->get_value(pobject, pcontext, iPath, iPathCount);

         }
         else
         {

            return m_pelement1->get_value(pobject, pcontext, iPath, iPathCount) + m_pelement2->get_value(pobject, pcontext, iPath, iPathCount);

         }

      }
      else if(m_ptoken->value == token::subtraction)
      {

         if (m_pelement2 == nullptr)
         {

            return ::datetime::value() - m_pelement1->get_value(pobject, pcontext, iPath, iPathCount);

         }
         else
         {

            return m_pelement1->get_value(pobject, pcontext, iPath, iPathCount) - m_pelement2->get_value(pobject, pcontext, iPath, iPathCount);

         }

      }
      else if(m_ptoken->value == token::multiplication)
      {
         throw_datetime_parser_exception("multiplication of datetime not supported (yet? meaningful?)");
      }
      else if(m_ptoken->value == token::division)
      {
         throw_datetime_parser_exception("division of datetime not supported (yet? meaningful?)");
      }
      else if(m_ptoken->value == token::function)
      {
         throw_datetime_parser_exception("\"" +m_ptoken->m_str + "\" function applied to datetime not supported (yet? meaningful?)");
         /*if(m_ptoken->m_str == "sqr")
         {
            return m_pelement1->get_value() * m_pelement1->get_value();
         }
         else if(m_ptoken->m_str == "sqrt")
         {
            return sqrt(m_pelement1->get_value());
         }
         else if(m_ptoken->m_str == "exp")
         {
            return exp(m_pelement1->get_value());
         }
         else if(m_ptoken->m_str == "ln")
         {
            return log(m_pelement1->get_value());
         }
         else if(m_ptoken->m_str == "log")
         {
            return log(m_pelement1->get_value()) / log(10.0);
         }
         else if(m_ptoken->m_str == "pow")
         {
            return pow(m_pelement1->get_value(), m_pelement2->get_value());
         }
         else
         {
            __throw(::exception::exception("unknown function"));
         }*/
      }
      return ::datetime::value();
   }


   string element::get_expression(::object * pobject, const ::aura::str_context * pcontext, i32 & iPath, i32 & iPathCount) const
   {

      if(m_ptoken->value == token::number)
      {

         return ::datetime::to_string(pobject, pcontext, strtotime(pobject,pcontext,m_ptoken->m_str,iPath,iPathCount));

      }
      else if(m_ptoken->value == token::identifier)
      {
         return ::datetime::to_string(pobject,pcontext,strtotime(pobject,pcontext,m_ptoken->m_str,iPath,iPathCount));
      }
      else if(m_ptoken->value == token::addition)
      {

         if (m_pelement2 == nullptr)
         {

            return "(" + m_pelement1->get_expression(pobject, pcontext, iPath, iPathCount) + ")";

         }
         else
         {

            return "(" + m_pelement1->get_expression(pobject, pcontext, iPath, iPathCount) + " + " + m_pelement2->get_expression(pobject, pcontext, iPath, iPathCount) + ")";

         }

      }
      else if(m_ptoken->value == token::subtraction)
      {

         if (m_pelement2 == nullptr)
         {

            return "( - " + m_pelement1->get_expression(pobject, pcontext, iPath, iPathCount) + ")";

         }
         else
         {

            return "(" + m_pelement1->get_expression(pobject, pcontext, iPath, iPathCount) + " - " + m_pelement2->get_expression(pobject, pcontext, iPath, iPathCount) + ")";

         }

      }
      else if(m_ptoken->value == token::multiplication)
      {

         __throw(not_supported_exception());

      }
      else if(m_ptoken->value == token::division)
      {

         __throw(not_supported_exception());

      }
      else if(m_ptoken->value == token::function)
      {

         __throw(not_supported_exception());

         /*if(m_ptoken->m_str == "sqr")
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
         }*/

      }

      return "not supported operation";

   }


} // namespace calculator



