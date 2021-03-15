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


   ::payload element::get_result(const ::apex::str_context * pcontext, int32_t & iPath, int32_t & iPathCount) const
   {

      if(m_ptoken->m_etoken == e_token_number || m_ptoken->m_etoken == e_token_identifier)
      {

         return ::datetime::time(psystem->datetime().strtotime(pcontext, m_ptoken->m_str, iPath, iPathCount));

      }
      else if(m_ptoken->m_etoken == e_token_addition)
      {

         if (m_pelement2 == NULL)
         {

            return m_pelement1->get_result(pcontext, iPath, iPathCount);
            
         }
         else
         {

            return m_pelement1->get_result(pcontext, iPath, iPathCount) + m_pelement2->get_result(pcontext, iPath, iPathCount);

         }

      }
      else if(m_ptoken->m_etoken == e_token_subtraction)
      {

         if (m_pelement2 == NULL)
         {

            return get_result(pcontext, iPath, iPathCount) - m_pelement1->get_result(pcontext, iPath, iPathCount);

         }
         else
         {

            return m_pelement1->get_result(pcontext, iPath, iPathCount) - m_pelement2->get_result(pcontext, iPath, iPathCount);

         }
      }
      else if(m_ptoken->m_etoken == e_token_multiplication)
      {

         throw_datetime_parser_exception("multiplication of datetime not supported (yet? meaningful?)");

      }
      else if(m_ptoken->m_etoken == e_token_division)
      {

         throw_datetime_parser_exception("division of datetime not supported (yet? meaningful?)");

      }
      else if(m_ptoken->m_etoken == e_token_function)
      {

         throw_datetime_parser_exception("\"" +m_ptoken->m_str + "\" function applied to datetime not supported (yet? meaningful?)");

         /*if(m_ptoken->m_str == "sqr")
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
            return log(m_pelement1->get_result()) / log(10.0);
         }
         else if(m_ptoken->m_str == "pow")
         {
            return pow(m_pelement1->get_result(), m_pelement2->get_result());
         }
         else
         {
            _throw(simple_exception(get_app(), "unknown function"));
         }*/

      }

      return get_result(pcontext, iPath, iPathCount);

   }
   

   string element::get_expression(const ::apex::str_context * pcontext, int32_t & iPath, int32_t & iPathCount) const
   {

      if(m_ptoken->m_etoken == e_token_number)
      {

         return psystem->datetime().international().get_gmt_date_time(::datetime::time((psystem->datetime().strtotime(pcontext,m_ptoken->m_str,iPath,iPathCount))));

      }
      else if(m_ptoken->m_etoken == e_token_identifier)
      {

         return psystem->datetime().international().get_gmt_date_time(::datetime::time((psystem->datetime().strtotime(pcontext,m_ptoken->m_str,iPath,iPathCount))));

      }
      else if(m_ptoken->m_etoken == e_token_addition)
      {

         if (m_pelement2 == NULL)
         {

            return "(" + m_pelement1->get_expression(pcontext, iPath, iPathCount) + ")";

         }
         else
         {

            return "(" + m_pelement1->get_expression(pcontext, iPath, iPathCount) + " + " + m_pelement2->get_expression(pcontext, iPath, iPathCount) + ")";

         }

      }
      else if(m_ptoken->m_etoken == e_token_subtraction)
      {

         if (m_pelement2 == NULL)
         {

            return "( - " + m_pelement1->get_expression(pcontext, iPath, iPathCount) + ")";

         }
         else
         {

            return "(" + m_pelement1->get_expression(pcontext, iPath, iPathCount) + " - " + m_pelement2->get_expression(pcontext, iPath, iPathCount) + ")";

         }

      }
      else if(m_ptoken->m_etoken == e_token_multiplication)
      {

         __throw(error_not_supported);

         //return "(" + m_pelement1->get_expression() + " * " + m_pelement2->get_expression() + ")";

      }
      else if(m_ptoken->m_etoken == e_token_division)
      {

         __throw(error_not_supported);

         //return "(" + m_pelement1->get_expression() + " / " + m_pelement2->get_expression() + ")";

      }
      else if(m_ptoken->m_etoken == e_token_function)
      {

         __throw(error_not_supported);

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




