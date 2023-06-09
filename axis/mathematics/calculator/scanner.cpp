/* (C) Copyright 2008 Nick Mudge <mudgen@gmail.com>
 * This code can be freely copied and modified.
 */
#include "framework.h"
#include "token.h"
#include "scanner.h"
#include "acme/primitive/string/str.h"
////#include "acme/exception/exception.h"

/* conversas dos Js Jefferson Dalavechia e Joice sobre calculadora cientifica, financeira e com pilha
mais tipico de calculadora no "command" */

/* o LeoFischer falouu sobre participar do cla(modinha de jogos de conquista de terra na internet) -
para mim sugestao na minha linguagem - para "criar um cla" */

namespace calculator
{


   token::token()
   {

      m_etype = token::type_none;

   }


   token::~token()
   {

   }


   scanner::scanner()
   {

      //m_range.m_begin       = nullptr;

   }


   scanner::~scanner()
   {
   }


   void scanner::initialize(const ::string & str)
   {
      
      //m_range.m_begin          = psz;
      
      m_range        = str;
      
      next_input     = m_range.m_begin;
      
   }


   void scanner::peek()
   {
      const char *beginning;
      if(m_range.m_begin != next_input && next_input != nullptr)
         return;
      beginning = m_range.m_begin;
      look_ahead();
      next_input = m_range.m_begin;
      m_range.m_begin = beginning;
   }

   void scanner::next()
   {
      m_range.m_begin = next_input;
   }

   token * scanner::look_ahead()
   {

      m_ptoken = __new(class token);

      if (m_ptoken.is_null())
      {

         throw ::exception(error_no_memory);

      }

      while (unicode_is_space_char(m_range.m_begin))
      {

         unicode_increment(m_range.m_begin);

      }

      if(*m_range.m_begin == '\0')
      {

         m_ptoken->m_etype = token::type_end;

         return m_ptoken;

      }

      const char * nextinput = unicode_next(m_range.m_begin);

      if((*m_range.m_begin == 'j' || *m_range.m_begin == 'i') && unicode_is_digit(nextinput))
      {

         m_ptoken->m_etype = token::type_imaginary;

         char * endptr;

         strtod(nextinput, &endptr);

         m_ptoken->m_str = string(nextinput, endptr - nextinput);

         m_range.m_begin = endptr;

         return m_ptoken;

      }
      else if(unicode_is_digit(m_range.m_begin))
      {

         m_ptoken->m_etype = token::type_number;

         char * endptr;

         strtod(m_range.m_begin, &endptr);

         m_ptoken->m_str = string(m_range.m_begin, endptr - m_range.m_begin);

         if((*endptr == 'i' || *endptr == 'j') && !(ansi_char_isdigit(*(endptr + 1)) || ansi_char_isalpha(*(endptr + 1))))
         {

            m_ptoken->m_etype = token::type_imaginary;

            endptr++;

         }

         m_range.m_begin = endptr;

         return m_ptoken;

      }
      else if(*m_range.m_begin == '+')
      {
         m_ptoken->m_etype = token::type_addition;
         m_range.m_begin++;
         return m_ptoken;
      }
      else if(*m_range.m_begin == '-')
      {
         m_ptoken->m_etype = token::type_subtraction;
         m_range.m_begin++;
         return m_ptoken;
      }
      else if(*m_range.m_begin == '*')
      {
         m_ptoken->m_etype = token::type_multiplication;
         m_range.m_begin++;
         return m_ptoken;
      }
      else if(*m_range.m_begin == '/')
      {
         m_ptoken->m_etype = token::type_division;
         m_range.m_begin++;
         return m_ptoken;
      }
      else if(*m_range.m_begin == '(')
      {
         m_ptoken->m_etype = token::type_open_paren;
         m_range.m_begin++;
         return m_ptoken;
      }
      else if(*m_range.m_begin == ',')
      {
         m_ptoken->m_etype = token::type_virgula;
         m_range.m_begin++;
         return m_ptoken;
      }
      else if(*m_range.m_begin == ')')
      {
         m_ptoken->m_etype = token::type_close_paren;
         m_range.m_begin++;
         return m_ptoken;
      }
      else
      {

         m_ptoken->m_str = m_range.consume_nc_name();

         while (unicode_is_space_char(m_range.m_begin))
         {

            unicode_increment(m_range.m_begin);

         }
         if(*m_range.m_begin == '(')
         {
            m_ptoken->m_etype = token::type_function;
         }
         else
         {
            m_ptoken->m_etype = token::type_identifier;
         }
         return m_ptoken;
      }
   }


} // namespace calculator
