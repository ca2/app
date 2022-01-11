/* (C) Copyright 2008 Nick Mudge <mudgen@gmail.com>
 * This code can be freely copied and modified.
 */
#include "framework.h"
#include "acme/primitive/text/context.h"


namespace datetime
{


   parser::parser()
   {

   }


   parser::~parser()
   {
   }


   ::e_status parser::initialize_datetime_parse(::text::context* ptextcontext)
   {

      auto estatus = ::object::initialize(ptextcontext);

      if (!estatus)
      {

         return estatus;

      }

      estatus = __construct_new(m_pscanner);

      if (!estatus)
      {

         return estatus;

      }

      estatus = m_pscanner->initialize_datetime_scanner(ptextcontext);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   element * parser::new_node()
   {

      auto pelement = __new(::datetime::element);
      
      m_elementa.add(pelement);

      return pelement;

   }

   //element * parser::parse(const ::string & psz)
/********************************************/
/* Parsing functions */

/*
   Grammer:
   expr   -> term + expr | term - expr | term
   term   -> func * term | func / term | func
   factor -> NUM | (expr) | term(expr) | -(factor) | +(factor)
   NUM    -> 1|2|3|4|5 ...
*/


element * parser::parse(const ::string & psz)
{

   ::datetime::element *node;

   m_pscanner->initialize_scanner(psz);

   node = expr(term(factor()));

   if (m_pscanner->m_ptoken->m_etoken != e_token_end)
   {

      syntax_error("Possible errors: illegal character, missing beginning parenthesis or missing operation");

   }

   return node;

}


element * parser::expr(::datetime::element * pelement1)
{
   ::datetime::element * top_node;
   m_pscanner->peek();
   if(m_pscanner->m_ptoken->m_etoken == e_token_addition || m_pscanner->m_ptoken->m_etoken == e_token_subtraction)
   {
      m_pscanner->next();
      top_node = new_node();
      top_node->m_ptoken      = m_pscanner->m_ptoken;
      top_node->m_pelement1   = pelement1;
      top_node->m_pelement2   = expr(term(factor()));
      return top_node;
   }
   return pelement1;
}

   element *parser::term(::datetime::element *m_pelement1)
   {
      ::datetime::element *top_node;
      m_pscanner->peek();
      if(m_pscanner->m_ptoken->m_etoken == e_token_multiplication || m_pscanner->m_ptoken->m_etoken == e_token_division)
      {
         m_pscanner->next();
         top_node                = new_node();
         top_node->m_ptoken      = m_pscanner->m_ptoken;
         top_node->m_pelement1   = m_pelement1;
         top_node->m_pelement2   = term(factor());
         return top_node;
      }
      return m_pelement1;
   }


   element *parser::factor()
   {
      ::datetime::element *node;
      m_pscanner->peek();
      if(m_pscanner->m_ptoken->m_etoken == e_token_identifier)
      {
         m_pscanner->next();
         node = new_node();
         node->m_ptoken = m_pscanner->m_ptoken;
         return node;
      }
      else if(m_pscanner->m_ptoken->m_etoken == e_token_addition)
      {
         m_pscanner->next();
         node                = new_node();
         node->m_ptoken      = m_pscanner->m_ptoken;
         node->m_pelement1   = factor();
         return node;
      }
      else if(m_pscanner->m_ptoken->m_etoken == e_token_subtraction)
      {
         m_pscanner->next();
         node                = new_node();
         node->m_ptoken      = m_pscanner->m_ptoken;
         node->m_pelement1   = factor();
         return node;
      }
      else if(m_pscanner->m_ptoken->m_etoken == e_token_open_paren)
      {
         m_pscanner->next();
         node = expr(term(factor()));
         expect(e_token_close_paren);
         return node;
      }
      else if(m_pscanner->m_ptoken->m_etoken == e_token_number)
      {
         m_pscanner->next();
         node = new_node();
         node->m_ptoken = m_pscanner->m_ptoken;
         return node;
      }
      else if(m_pscanner->m_ptoken->m_etoken == e_token_function)
      {
         m_pscanner->next();
         node                = new_node();
         node->m_ptoken      = m_pscanner->m_ptoken;
         int32_t iCount;
         if(node->m_ptoken->m_str == "sqr")
         {
            iCount = 1;
         }
         else if(node->m_ptoken->m_str == "sqrt")
         {
            iCount = 1;
         }
         else if(node->m_ptoken->m_str == "exp")
         {
            iCount = 1;
         }
         else if(node->m_ptoken->m_str == "ln")
         {
            iCount = 1;
         }
         else if(node->m_ptoken->m_str == "log")
         {
            iCount = 1;
         }
         else if(node->m_ptoken->m_str == "pow")
         {
            iCount = 2;
         }
         else
         {
            
            throw ::exception(error_failed, "unknown function");

         }
         expect(e_token_open_paren);
         int32_t iElem = 1;
         if(iCount > 0)
         {
            while(true)
            {
               if(iElem == 1)
               {
                    node->m_pelement1   = expr(term(factor()));
               }
               else if(iElem == 2)
               {
                  node->m_pelement2   = expr(term(factor()));
               }
               else
               {
                  node->m_pelement3  = expr(term(factor()));
               }
               iCount--;
               if(iCount <= 0)
                  break;
               iElem++;
               expect(e_token_comma);
            }
         }
         expect(e_token_close_paren);
         return node;
      }

      syntax_error("missing number or ending parenthesis");
      return NULL;
   }


   void parser::expect(char value)
   {

      char error_msg[11] = "expected ";
      error_msg[9] = value;
      error_msg[10] = '\0';
      m_pscanner->peek();
      if (m_pscanner->m_ptoken->m_etoken == (enum_token) value)
      {
         m_pscanner->next();

      }
      else
         syntax_error(error_msg);
   }


   


   void parser::syntax_error(const ::string & psz)
   {
      error(string("syntax") + psz);
   }
   void parser::error(const ::string & psz)
   {
      string str;
      str = "error: ";
      str += psz;
      throw_datetime_parsing_exception(str);

   }


} // namespace datetime
