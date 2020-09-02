/* (C) Copyright 2008 Nick Mudge <mudgen@gmail.com>
 * This code can be freely copied and modified.
 */
#include "framework.h"


namespace datetime
{

   element::element()
   {
      m_pparent   = NULL;
      m_pelement1 = NULL;
      m_pelement2 = NULL;
      m_pelement3 = NULL;
   }

   element::~element()
   {
   }


   value element::get_value(sp(::aura::application) pbaseapp, ::aura::str_context * pcontext, int32_t & iPath, int32_t & iPathCount) const
   {
      if(m_ptoken->value == token::number || m_ptoken->value == token::identifier)
      {
         return strtotime(pbaseapp, pcontext, m_ptoken->m_str, iPath, iPathCount);
      }
      else if(m_ptoken->value == token::addition)
      {
         if(m_pelement2 == NULL)
            return m_pelement1->get_value(pbaseapp, pcontext, iPath, iPathCount);
         else
            return m_pelement1->get_value(pbaseapp, pcontext, iPath, iPathCount) + m_pelement2->get_value(pbaseapp, pcontext, iPath, iPathCount);
      }
      else if(m_ptoken->value == token::subtraction)
      {
         if(m_pelement2 == NULL)
            return value() - m_pelement1->get_value(pbaseapp, pcontext, iPath, iPathCount);
         else
            return m_pelement1->get_value(pbaseapp, pcontext, iPath, iPathCount) - m_pelement2->get_value(pbaseapp, pcontext, iPath, iPathCount);
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
            _throw(simple_exception(get_app(), "unknown function"));
         }*/
      }
      return value();
   }
   
   string element::get_expression(sp(::aura::application) pbaseapp, ::aura::str_context * pcontext, int32_t & iPath, int32_t & iPathCount) const
   {
      if(m_ptoken->value == token::number)
      {
         return to_string(pbaseapp, pcontext, strtotime(pbaseapp,pcontext,m_ptoken->m_str,iPath,iPathCount));
      }
      else if(m_ptoken->value == token::identifier)
      {
         return to_string(pbaseapp,pcontext,strtotime(pbaseapp,pcontext,m_ptoken->m_str,iPath,iPathCount));
      }
      else if(m_ptoken->value == token::addition)
      {
         if(m_pelement2 == NULL)
            return "(" + m_pelement1->get_expression(pbaseapp, pcontext, iPath, iPathCount) + ")";
         else
            return "(" + m_pelement1->get_expression(pbaseapp, pcontext, iPath, iPathCount) + " + " + m_pelement2->get_expression(pbaseapp, pcontext, iPath, iPathCount) + ")";
      }
      else if(m_ptoken->value == token::subtraction)
      {
         if(m_pelement2 == NULL)
            return "( - " + m_pelement1->get_expression(pbaseapp, pcontext, iPath, iPathCount) + ")";
         else
            return "(" + m_pelement1->get_expression(pbaseapp, pcontext, iPath, iPathCount) + " - " + m_pelement2->get_expression(pbaseapp, pcontext, iPath, iPathCount) + ")";
      }
      else if(m_ptoken->value == token::multiplication)
      {
         _throw(not_supported_exception(pbaseapp));
         //return "(" + m_pelement1->get_expression() + " * " + m_pelement2->get_expression() + ")";
      }
      else if(m_ptoken->value == token::division)
      {
         _throw(not_supported_exception(pbaseapp));
         //return "(" + m_pelement1->get_expression() + " / " + m_pelement2->get_expression() + ")";
      }
      else if(m_ptoken->value == token::function)
      {
         _throw(not_supported_exception(pbaseapp));
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
            _throw(simple_exception(get_app(), "unknown function"));
         }*/
      }
      return "not supported operation";
   }



} // namespace calculator