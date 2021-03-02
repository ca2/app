/* (C) Copyright 2008 Nick Mudge <mudgen@gmail.com>
 * This code can be freely copied and modified.
 */
#include  "framework.h"

/* conversas dos Js Jefferson Dalavechia e Joice sobre calculadora científica, financeira e com pilha
mais típico de calculadora no "command" */

/* o LeoFischer falouu sobre participar do clã(modinha de jogos de conquista de terra na internet) -
para mim sugestão na minha linguagem - para "criar um clã" */

namespace calculator
{


   token::token()
   {

      m_etype = token::type_none;

   }


   token::~token()
   {

   }


   scanner::scanner(::layered * pobjectContext) :
      ::object(pobjectContext)
   {

      input       = nullptr;

   }


   scanner::~scanner()
   {
   }


   void scanner::initialize(const char * psz)
   {
      input          = psz;
      next_input     = input;
   }


   void scanner::peek()
   {
      const char *beginning;
      if(input != next_input && next_input != nullptr)
         return;
      beginning = input;
      look_ahead();
      next_input = input;
      input = beginning;
   }

   void scanner::next()
   {
      input = next_input;
   }

   token * scanner::look_ahead()
   {

      m_ptoken = __new(class token);

      if (m_ptoken.is_null())
      {

         __throw(error_no_memory);

      }

      while (::str::ch::is_space_char(input))
      {

         input = ::str::utf8_inc(input);

      }

      if(*input == '\0')
      {

         m_ptoken->m_etype = token::type_end;

         return m_ptoken;

      }

      const char * nextinput = ::str::utf8_inc(input);

      if((*input == 'j' || *input == 'i') && ::str::ch::is_digit(nextinput))
      {

         m_ptoken->m_etype = token::type_imaginary;

         char * endptr;

         strtod(nextinput, &endptr);

         m_ptoken->m_str = string(nextinput, endptr - nextinput);

         input = endptr;

         return m_ptoken;

      }
      else if(::str::ch::is_digit(input))
      {

         m_ptoken->m_etype = token::type_number;

         char * endptr;

         strtod(input, &endptr);

         m_ptoken->m_str = string(input, endptr - input);

         if((*endptr == 'i' || *endptr == 'j') && !(ansi_char_is_digit(*(endptr + 1)) || ansi_char_is_alphabetic(*(endptr + 1))))
         {

            m_ptoken->m_etype = token::type_imaginary;

            endptr++;

         }

         input = endptr;

         return m_ptoken;

      }
      else if(*input == '+')
      {
         m_ptoken->m_etype = token::type_addition;
         input++;
         return m_ptoken;
      }
      else if(*input == '-')
      {
         m_ptoken->m_etype = token::type_subtraction;
         input++;
         return m_ptoken;
      }
      else if(*input == '*')
      {
         m_ptoken->m_etype = token::type_multiplication;
         input++;
         return m_ptoken;
      }
      else if(*input == '/')
      {
         m_ptoken->m_etype = token::type_division;
         input++;
         return m_ptoken;
      }
      else if(*input == '(')
      {
         m_ptoken->m_etype = token::type_open_paren;
         input++;
         return m_ptoken;
      }
      else if(*input == ',')
      {
         m_ptoken->m_etype = token::type_virgula;
         input++;
         return m_ptoken;
      }
      else if(*input == ')')
      {
         m_ptoken->m_etype = token::type_close_paren;
         input++;
         return m_ptoken;
      }
      else
      {

         m_ptoken->m_str = ::str::consume_nc_name(input);

         while (::str::ch::is_space_char(input))
         {

            input = ::str::utf8_inc(input);

         }
         if(*input == '(')
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
