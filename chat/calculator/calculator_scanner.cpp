/* (C) Copyright 2008 Nick Mudge <mudgen@gmail.com>
 * This code can be freely copied and modified.
 */
#include  "framework.h"

/* conversas dos Js Jefferson Dalavechia e Joice sobre calculadora cient凬ica, financeira e com pilha
mais tico de calculadora no command */

/* o LeoFischer falouu sobre participar do cl・(modinha de jogos de conquista de terra na internet) -
para mim sugest縊 na minha linguagem - para "criar um cl・? */

namespace calculator
{

   token::token()
   {

      m_etype = token::type_none;

   }

   token::~token()
   {
   }


   scanner::scanner(::object * pobject) :
      ::object(pobject)
   {
      m_ptoken    = nullptr;
      input       = nullptr;
   }

   scanner::~scanner()
   {
   }


   void scanner::initialize(const ::string & psz)
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
      m_ptoken = look_ahead();
      next_input = input;
      input = beginning;
   }

   void scanner::next()
   {
      input = next_input;
   }

   token * scanner::look_ahead()
   {
      token * token;
      token = memory_new class token;
      if(token == nullptr)
         throw ::exception(error_no_memory);
      while(::str::ch().is_space_char(input))
         ::str().increment(input);
      if(*input == '\0')
      {
         token->m_etype = token::type_end;
         return token;
      }
      const char * nextinput = ::str().next(input);

      if((*input == 'j' || *input == 'i') &&
         ::str::ch().is_digit(nextinput))
      {
         token->m_etype = token::type_imaginary;
         char * endptr;
         strtod(nextinput, &endptr);
         token->m_str = string(nextinput, endptr - nextinput);
         input = endptr;
         return token;
      }
      else if(::str::ch().is_digit(input))
      {
         token->m_etype = token::type_number;
         char * endptr;
         strtod(input, &endptr);
         token->m_str = string(input, endptr - input);
         if((*endptr == 'i' || *endptr == 'j')
            && !(ansi_char_is_digit(*(endptr + 1)) || ansi_char_is_alphabetic(*(endptr + 1))))
         {
            token->m_etype = token::type_imaginary;
            endptr++;
         }
         input = endptr;
         return token;
      }
      else if(*input == '+')
      {
         token->m_etype = token::type_addition;
         input++;
         return token;
      }
      else if(*input == '-')
      {
         token->m_etype = token::type_subtraction;
         input++;
         return token;
      }
      else if(*input == '*')
      {
         token->m_etype = token::type_multiplication;
         input++;
         return token;
      }
      else if(*input == '/')
      {
         token->m_etype = token::type_division;
         input++;
         return token;
      }
      else if(*input == '(')
      {
         token->m_etype = token::type_open_paren;
         input++;
         return token;
      }
      else if(*input == ',')
      {
         token->m_etype = token::type_virgula;
         input++;
         return token;
      }
      else if(*input == ')')
      {
         token->m_etype = token::type_close_paren;
         input++;
         return token;
      }
      else
      {
         token->m_str = ::str().consume_nc_name(input);
         while(::str::ch().is_space_char(input))
            ::str().increment(input);
         if(*input == '(')
         {
            token->m_etype = token::type_function;
         }
         else
         {
            token->m_etype = token::type_identifier;
         }
         return token;
      }
   }


} // namespace calculator
