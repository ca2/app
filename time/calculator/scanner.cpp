/* (C) Copyright 2008 Nick Mudge <mudgen@gmail.com>
 * This code can be freely copied and modified.
 */
#include "framework.h"
#include "scanner.h"
#include "token.h"
////#include "acme/exception/exception.h"
#include "acme/prototype/string/international.h"
#include "acme/prototype/text/context.h"


namespace datetime
{

   bool check_end_expression(const ::scoped_string & scopedstrInput, const_char_pointer &scanner)
   {
      scanner = scopedstrInput;
      while(unicode_is_space_char(scanner) && *scanner != '\0')
         scanner++;
      if(*scanner == '\0')
         return true;
      if(!unicode_is_digit(scanner) &&
         !unicode_is_letter(scanner))
         return true;
      return false;
   }

   bool check_expression_separator(const ::scoped_string & scopedstrInput, const_char_pointer &scanner)
   {
      scanner = scopedstrInput;
      while(unicode_is_space_char(scanner) && *scanner != '\0')
         scanner = unicode_next(scanner);
      if(*scanner == '\0')
         return true;
      if(scanner == scopedstrInput)
      {
         if(unicode_is_letter(scanner))
            return true;
         else
            return false;
      }
      else
         return true;
   }

   string check_unit(const ::text::context * pcontext, const ::scoped_string & scopedstrInput, const_char_pointer &scanner)
   {
      static auto idCalendarDays("calendar:days");
      scanner = scopedstrInput;
      while(unicode_is_space_char(scanner) && *scanner != '\0')
         scanner = unicode_next(scanner);
      if(*scanner == '\0')
         return "";
      const_char_pointer start = scanner;
      string strCandidate;
      if(unicode_is_letter(scanner))
      {
         while(unicode_is_letter(scanner))
            scanner = unicode_next(scanner);
         strCandidate = string(start, scanner - start + 1);
         strCandidate.make_lower();
         if(pcontext->matches(idCalendarDays, strCandidate))
         {
            return "days";
         }
      }
      else
      {
         strCandidate = string(scopedstrInput);
         if(pcontext->begins(idCalendarDays, strCandidate))
         {
            return "days";
         }
      }
      if(strCandidate == "sec")
      {
         return strCandidate;
      }
      else if(strCandidate == "second")
      {
         return strCandidate;
      }
      else if(strCandidate == "second")
      {
         return strCandidate;
      }
      else if(strCandidate == "seconds")
      {
         return strCandidate;
      }
      else if(strCandidate == "minimum")
      {
         return strCandidate;
      }
      else if(strCandidate == "mins")
      {
         return strCandidate;
      }
      else if(strCandidate == "minute")
      {
         return strCandidate;
      }
      else if(strCandidate == "minutes")
      {
         return strCandidate;
      }
      else if(strCandidate == "hour")
      {
         return strCandidate;
      }
      else if(strCandidate == "hours")
      {
         return strCandidate;
      }
      else if(strCandidate == "day")
      {
         return strCandidate;
      }
      else if(strCandidate == "days")
      {
         return strCandidate;
      }
      else if(strCandidate == "week")
      {
         return strCandidate;
      }
      else if(strCandidate == "weeks")
      {
         return strCandidate;
      }
      else if(strCandidate == "month")
      {
         return strCandidate;
      }
      else if(strCandidate == "months")
      {
         return strCandidate;
      }
      else if(strCandidate == "year")
      {
         return strCandidate;
      }
      else if(strCandidate == "years")
      {
         return strCandidate;
      }
      else if(strCandidate == "century")
      {
         return strCandidate;
      }
      else if(strCandidate == "centuries")
      {
         return strCandidate;
      }
      return "";
   }

   string check_month(const ::scoped_string & scopedstrInput, const_char_pointer &scanner)
   {
      scanner = scopedstrInput;
      while(ansi_char_isspace(*scanner) && *scanner != '\0')
         scanner++;
      if(*scanner == '\0')
         return "";
      const_char_pointer start = scanner;
      while(ansi_char_isalpha(*scanner))
         scanner++;
      ::string strCandidate = scopedstrInput(0, scanner - start);
      strCandidate.make_lower();
      if(strCandidate == "jan")
      {
         return strCandidate;
      }
      else if(strCandidate == "janeiro")
      {
         return strCandidate;
      }
      else if(strCandidate == "fev")
      {
         return strCandidate;
      }
      else if(strCandidate == "fevereiro")
      {
         return strCandidate;
      }
      else if(strCandidate == "mar")
      {
         return strCandidate;
      }
      else if(strCandidate == unitext("marco"))
      {
         return strCandidate;
      }
      else if(strCandidate == "abr")
      {
         return strCandidate;
      }
      else if(strCandidate == "abril")
      {
         return strCandidate;
      }
      else if(strCandidate == "mai")
      {
         return strCandidate;
      }
      else if(strCandidate == "maio")
      {
         return strCandidate;
      }
      else if(strCandidate == "jun")
      {
         return strCandidate;
      }
      else if(strCandidate == "junho")
      {
         return strCandidate;
      }
      else if(strCandidate == "jul")
      {
         return strCandidate;
      }
      else if(strCandidate == "julho")
      {
         return strCandidate;
      }
      else if(strCandidate == "ago")
      {
         return strCandidate;
      }
      else if(strCandidate == "agosto")
      {
         return strCandidate;
      }
      else if(strCandidate == "set")
      {
         return strCandidate;
      }
      else if(strCandidate == "setembro")
      {
         return strCandidate;
      }
      else if(strCandidate == "out")
      {
         return strCandidate;
      }
      else if(strCandidate == "outubro")
      {
         return strCandidate;
      }
      else if(strCandidate == "nov")
      {
         return strCandidate;
      }
      else if(strCandidate == "novembro")
      {
         return strCandidate;
      }
      else if(strCandidate == "dez")
      {
         return strCandidate;
      }
      else if(strCandidate == "dezembro")
      {
         return strCandidate;
      }
      return "";
   }

   string check_lang_date(const ::scoped_string & scopedstrInput, const_char_pointer &scanner)
   {
      scanner = scopedstrInput;
      while(unicode_is_whitespace(scanner) && *scanner != '\0')
         scanner = unicode_next(scanner);
      if(*scanner == '\0')
         return "";
      const_char_pointer start = scanner;
      while(unicode_is_letter(scanner))
         scanner = unicode_next(scanner);
      ::string strCandidate = scopedstrInput(0,  scanner - start);
      strCandidate.make_lower();
      if(strCandidate == "today")
      {
         return strCandidate;
      }
      else if(strCandidate == "tomorrow")
      {
         return strCandidate;
      }
      else if(strCandidate == "yesterday")
      {
         return strCandidate;
      }
      else if(strCandidate == "hoje")
      {
         return strCandidate;
      }
      else if(strCandidate == unitext("amanha"))
      {
         return strCandidate;
      }
      else if(strCandidate == "ontem")
      {
         return strCandidate;
      }
      return "";
   }

   string check_natural(const ::scoped_string & scopedstrInput, const_char_pointer &scanner)
   {
      scanner = scopedstrInput;
      if(*scanner == '\0')
         return "";
      if(!unicode_is_digit(scanner))
         return "";
      const_char_pointer start = scanner;
      scanner = unicode_next(scanner);
      while(unicode_is_digit(scanner))
      {
         scanner = unicode_next(scanner);
      }
      return string(start, scanner - start);
   }


   string check_lang_offset(const ::scoped_string & scopedstrInput, const_char_pointer &scanner)
   {
      if(check_end_expression(scopedstrInput, scanner))
         return "";
      const_char_pointer start = scopedstrInput;
      while(!unicode_is_space_char(scanner) && *scanner != '\0')
         scanner = unicode_next(scanner);
      ::string strCandidate = scopedstrInput(0, scanner - start);
      strCandidate.make_lower();
      if(strCandidate == "ago")
      {
         return strCandidate;
      }
      else if(strCandidate == unitext("atras"))
      {
         return strCandidate;
      }
      return "";
   }

   string check_natural_separator(const ::scoped_string & scopedstrInput, const_char_pointer &scanner)
   {
      scanner = scopedstrInput;
      if(*scanner == '\0')
         return "";
      if(*scanner == '/')
      {
         scanner++;
         return "/";
      }
      else if(*scanner == '-')
      {
         scanner++;
         return "/";
      }
      else if(*scanner == '.')
      {
         scanner++;
         return ".";
      }
      else
      {
         return "";
      }
   }

   string check_date(const_char_pointer input, const_char_pointer &scanner)
   {
      if(check_end_expression(input, scanner))
         return "";
      const_char_pointer start = input;
      string strNat1 = check_natural(input, scanner);
      if(strNat1.has_character())
      {
         input = scanner;
         string strSep1 = check_natural_separator(input, scanner);
         if(strSep1.has_character())
         {
            input = scanner;
            string strNat2 = check_natural(input, scanner);
            if(strNat2.has_character())
            {
               input = scanner;
               string strSep2 = check_natural_separator(input, scanner);
               if(strSep2.has_character() && strSep2 == strSep1)
               {
                  input = scanner;
                  string strNat3 = check_natural(input, scanner);
                  if(strNat3.has_character())
                  {
                     
                     input = scanner;
                     
                     if(!check_expression_separator(input, scanner))
                     {
                     
                        throw ::exception(error_failed, "invalid date");

                     }

                     return string(start, scanner - start);

                  }

               }
               else if(strSep1 == strSep2)
               {
                  input = scanner;
                  string strMonth = check_month(input, scanner);
                  if(strMonth.has_character())
                  {
                     
                     input = scanner;
                     
                     if(!check_expression_separator(input, scanner))
                     {
                     
                        throw ::exception(error_failed, "invalid date");

                     }

                     return string(start, scanner - start);

                  }
                  else
                  {
                     
                     throw ::exception(error_failed, "invalid date");

                  }

               }
               else if(!strSep2.has_character())
               {

                  input = scanner;

                  if(!check_expression_separator(input, scanner))
                  {

                     throw ::exception(error_failed, "invalid date");

                  }

                  return string(start, scanner - start);

               }
               else
               {
               
                  throw ::exception(error_failed, "invalid date");

               }

            }
            else
            {
               input = scanner;
               string strMonth = check_month(input, scanner);
               if(strMonth.has_character())
               {
                  input = scanner;
                  string strSep2 = check_natural_separator(input, scanner);
                  if(strSep2.has_character() && strSep2 == strSep1)
                  {
                     input = scanner;
                     string strNat3 = check_natural(input, scanner);
                     if(strNat3.has_character())
                     {
                        
                        input = scanner;

                        if(!check_expression_separator(input, scanner))
                        {
                           
                           throw ::exception(error_failed, "invalid date");

                        }

                        return string(start, scanner - start);

                     }

                  }
                  else if(strSep2 == strSep1)
                  {
                     input = scanner;
                     string strNat2 = check_natural(input, scanner);
                     if(strNat2.has_character())
                     {

                        input = scanner;

                        if(!check_expression_separator(input, scanner))
                        {
                        
                           throw ::exception(error_failed, "invalid date");

                        }

                        return string(start, scanner - start);

                     }
                     else
                     {

                        throw ::exception(error_failed, "invalid date");

                     }

                  }
                  else
                  {

                     throw ::exception(error_failed, "invalid date");

                  }

               }

            }

         }
         else
         {

            return "";

         }

         return "";

      }
      else
      {

         return "";

      }

   }


   string check_offset(const ::text::context * pcontext, const_char_pointer input, const_char_pointer &scanner)
   {

      if (check_end_expression(input, scanner))
      {

         return "";

      }

      const_char_pointer start = input;

      int32_t iCount = 0;

      while(true)
      {

         input = scanner;

         string strNat = check_natural(input, scanner);

         if(!strNat.has_character())
         {

            if (iCount > 0)
            {

               break;

            }

            return "";

         }

         input = scanner;

         string strUnit = check_unit(pcontext, input, scanner);

         if(!strNat.has_character())
         {

            return "";

         }

         iCount++;

      }

      string strOff = check_lang_offset(input, scanner);

      return string(start, scanner - start);

   }


   string consume_date_expression(const ::text::context * pcontext, const_char_pointer &input)
   {

      const_char_pointer scanner;

      if (check_end_expression(input, scanner))
      {

         return "";

      }

      const_char_pointer start = input;

      string strDate = check_date(input, scanner);

      if(strDate.has_character())
      {

         input = scanner;

         string strOffset = check_offset(pcontext, input, scanner);

         if(strOffset.has_character())
         {

            input = scanner;

            if (check_end_expression(input, scanner))
            {

               return string(start, scanner - start);

            }
            else
            {

               throw ::exception(error_failed, "invalid date expression");

            }

         }
         else
         {

            input = scanner;

            if (check_end_expression(input, scanner))
            {
             
               return string(start, scanner - start);

            }
            else
            {
               
               throw ::exception(error_failed, "invalid date expression");

            }

         }

      }
      else
      {

         string strLangDate = check_lang_date(input, scanner);

         if(strLangDate.has_character())
         {

            input = scanner;

            string strOffset = check_offset(pcontext, input, scanner);

            if(strOffset.has_character())
            {

               input = scanner;

               if (check_end_expression(input, scanner))
               {

                  return string(start, scanner - start);

               }
               else
               {

                  throw ::exception(error_failed, "invalid date expression");

               }

            }
            else
            {

               input = scanner;

               if (check_end_expression(input, scanner))
               {
                
                  return string(start, scanner - start);

               }
               else
               {

                  throw ::exception(error_failed, "invalid date expression");

               }

            }

         }
         else
         {

            input = scanner;

            string strOffset = check_offset(pcontext, input, scanner);

            if(strOffset.has_character())
            {

               input = scanner;

               if (check_end_expression(input, scanner))
               {
                
                  return string(start, scanner - start);

               }
               else
               {

                  throw ::exception(error_failed, "invalid date expression");

               }

            }
            else
            {

               input = scanner;

               if (check_end_expression(input, scanner))
               {

                  return string(start, scanner - start);

               }
               else
               {
                  
                  throw ::exception(error_failed, "invalid date expression");

               }

            }

         }

      }

   }


   scanner::scanner()
   {

      m_ptoken          = NULL;

      input             = NULL;

   }


   scanner::~scanner()
   {

   }


   void scanner::initialize_datetime_scanner(::text::context* ptextcontext)
   {

      //auto estatus = 
      
      ::particle::initialize(ptextcontext);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      m_ptextcontext = ptextcontext;

      //return estatus;

   }


   void scanner::initialize_scanner(const ::scoped_string & scopedstrInput)
   {

      input          = scopedstrInput;

      next_input     = input;

   }


   void scanner::peek()
   {

      const_char_pointer beginning;

      if (input != next_input && next_input != NULL)
      {

         return;

      }

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
      token = __raw_new class token;
      if(token == NULL)
         throw ::exception(error_no_memory);
      while(ansi_char_isspace(*input))
         input++;
      if(*input == '\0')
      {
         token->m_etoken = e_token_end;
         return token;
      }
      if(*input == '+')
      {
         token->m_etoken = e_token_addition;
         input++;
         return token;
      }
      else if(*input == '-')
      {
         token->m_etoken = e_token_subtraction;
         input++;
         return token;
      }
      else if(*input == '*')
      {
         token->m_etoken = e_token_multiplication;
         input++;
         return token;
      }
      else if(*input == '/')
      {
         token->m_etoken = e_token_division;
         input++;
         return token;
      }
      else if(*input == '(')
      {
         token->m_etoken = e_token_open_paren;
         input++;
         return token;
      }
      else if(*input == ',')
      {
         token->m_etoken = e_token_comma;
         input++;
         return token;
      }
      else if(*input == ')')
      {
         token->m_etoken = e_token_close_paren;
         input++;
         return token;
      }
      else
      {
         token->m_str = consume_date_expression(m_ptextcontext, input);
         while(unicode_is_space_char(input))
            unicode_next(input);
         if(*input == '(')
         {
            token->m_etoken = e_token_function;
         }
         else
         {
            token->m_etoken = e_token_identifier;
         }
         return token;
      }
   }


} // namespace datetime
