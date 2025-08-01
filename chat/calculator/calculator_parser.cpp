/* (C) Copyright 2008 Nick Mudge <mudgen@gmail.com>
 * This code can be freely copied and modified.
 */
#include "framework.h"

namespace calculator
{

   parser::parser(::particle * pparticle) :
      ::object(pparticle),
      m_scanner(pparticle)
   {
   }

   parser::~parser()
   {
   }

   ::calculator::matter * parser::new_node()
   {
      return m_elementa.add(__allocate ::calculator::matter());
   }

   //::calculator::matter * parser::parse(const ::scoped_string & scopedstr)
   /********************************************/
   /* Parsing functions */

   /*
      Grammer:
      expr   -> term + expr | term - expr | term
      term   -> func * term | func / term | func
      factor -> NUM | (expr) | term(expr) | -(factor) | +(factor)
      NUM    -> 1|2|3|4|5 ...
   */


   ::calculator::matter * parser::parse(const ::scoped_string & scopedstr)
   {
      ::calculator::matter *node;
      m_scanner.initialize(scopedstr);
      node = expr(term(factor()));
      if(m_scanner.m_ptoken->m_etype != token::type_end)
         syntax_error("Possible errors: illegal character, missing beginning parenthesis or missing operation");
      return node;
   }

   ::calculator::matter * parser::expr(::calculator::matter * pelement1)
   {
      ::calculator::matter * top_node;
      m_scanner.peek();
      if(m_scanner.m_ptoken->m_etype == token::type_addition || m_scanner.m_ptoken->m_etype == token::type_subtraction)
      {
         m_scanner.next();
         top_node = new_node();
         top_node->m_ptoken      = m_scanner.m_ptoken;
         top_node->m_pelement1   = pelement1;
         top_node->m_pelement2   = expr(term(factor()));
         return top_node;
      }
      return pelement1;
   }

   ::calculator::matter *parser::term(::calculator::matter *m_pelement1)
   {
      ::calculator::matter *top_node;
      m_scanner.peek();
      if(m_scanner.m_ptoken->m_etype == token::type_multiplication || m_scanner.m_ptoken->m_etype == token::type_division)
      {
         m_scanner.next();
         top_node                = new_node();
         top_node->m_ptoken      = m_scanner.m_ptoken;
         top_node->m_pelement1   = m_pelement1;
         top_node->m_pelement2   = term(factor());
         return top_node;
      }
      return m_pelement1;
   }


   ::calculator::matter *parser::factor()
   {
      ::calculator::matter *node;
      m_scanner.peek();
      if(m_scanner.m_ptoken->m_etype == token::type_addition)
      {
         m_scanner.next();
         node                = new_node();
         node->m_ptoken      = m_scanner.m_ptoken;
         node->m_pelement1   = factor();
         return node;
      }
      else if(m_scanner.m_ptoken->m_etype == token::type_subtraction)
      {
         m_scanner.next();
         node                = new_node();
         node->m_ptoken      = m_scanner.m_ptoken;
         node->m_pelement1   = factor();
         return node;
      }
      else if(m_scanner.m_ptoken->m_etype == token::type_open_paren)
      {
         m_scanner.next();
         node = expr(term(factor()));
         expect(token::type_close_paren);
         return node;
      }
      else if(m_scanner.m_ptoken->m_etype == token::type_number || m_scanner.m_ptoken->m_etype == token::type_imaginary)
      {
         m_scanner.next();
         node = new_node();
         node->m_ptoken = m_scanner.m_ptoken;
         return node;
      }
      else if(m_scanner.m_ptoken->m_etype == token::type_identifier)
      {
         m_scanner.next();
         node = new_node();
         node->m_ptoken = m_scanner.m_ptoken;
         return node;
      }
      else if(m_scanner.m_ptoken->m_etype == token::type_function)
      {
         m_scanner.next();
         node                = new_node();
         node->m_ptoken      = m_scanner.m_ptoken;
         int iCount;
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
         else if(node->m_ptoken->m_str == "atan")
         {
            iCount = 1;
         }
         else if(node->m_ptoken->m_str == "asin")
         {
            iCount = 1;
         }
         else if(node->m_ptoken->m_str == "acos")
         {
            iCount = 1;
         }
         else if(node->m_ptoken->m_str == "tan")
         {
            iCount = 1;
         }
         else if(node->m_ptoken->m_str == "sin")
         {
            iCount = 1;
         }
         else if(node->m_ptoken->m_str == "cos")
         {
            iCount = 1;
         }
         else
         {
            throw ::exception(::exception("unknown function"));
         }
         expect(token::type_open_paren);
         int iElem = 1;
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
               expect(token::type_virgula);
            }
         }
         expect(token::type_close_paren);
         return node;
      }

      syntax_error("missing number or ending parenthesis");
      return nullptr;
   }

   void parser::expect(char value)
   {
      char error_msg[11] = "expected ";
      error_msg[9] = value;
      error_msg[10] = '\0';
      m_scanner.peek();
      if(m_scanner.m_ptoken->m_etype == (::calculator::token::enum_type) value)
         m_scanner.next();
      else
         syntax_error(error_msg);
   }


   void parser::syntax_error(const ::scoped_string & scopedstr)
   {
      error(string("syntax") + psz);
   }



   void parser::error(const ::scoped_string & scopedstr)
   {
      string str;
      str = "error: ";
      str += psz;

      throw_numeric_parsing_exception(str);

   }


} // namespace calculator



