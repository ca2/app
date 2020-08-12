/* (C) Copyright 2008 Nick Mudge <mudgen@gmail.com>
 * This code can be freely copied and modified.
 */
#include  "framework.h"
#include  "aura/platform/str_context.h"

namespace datetime
{

   bool check_end_expression(const char * m_pszInput, const char * & scanner)
   {
      scanner = m_pszInput;
      while(::str::ch::is_space_char(scanner) && *scanner != '\0')
         scanner++;
      if(*scanner == '\0')
         return true;
      if(!::str::ch::is_digit(scanner) &&
         !::str::ch::is_letter(scanner))
         return true;
      return false;
   }

   bool check_expression_separator(const char * m_pszInput, const char * & scanner)
   {
      scanner = m_pszInput;
      while(::str::ch::is_space_char(scanner) && *scanner != '\0')
         scanner  =::str::utf8_inc(scanner);
      if(*scanner == '\0')
         return true;
      if(scanner == m_pszInput)
      {
         if(::str::ch::is_letter(scanner))
            return true;
         else
            return false;
      }
      else
         return true;
   }

   string check_unit(const ::aura::str_context * pcontext, const char * m_pszInput, const char * & scanner)
   {
      static id idCalendarDays("calendar:days");
      scanner = m_pszInput;
      while(::str::ch::is_space_char(scanner) && *scanner != '\0')
         scanner = ::str::utf8_inc(scanner);
      if(*scanner == '\0')
         return "";
      const char * start = scanner;
      string strCandidate;
      if(::str::ch::is_letter(scanner))
      {
         while(::str::ch::is_letter(scanner))
            scanner = ::str::utf8_inc(scanner);
         strCandidate = string(start, scanner - start + 1);
         strCandidate.make_lower();
         if(pcontext->matches(idCalendarDays, strCandidate))
         {
            return "days";
         }
      }
      else
      {
         strCandidate = string(m_pszInput);
         if(pcontext->begins(idCalendarDays, strCandidate))
         {
            return "days";
         }
      }
      if(strCandidate == "sec")
      {
         return strCandidate;
      }
      else if(strCandidate == "secs")
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
      else if(strCandidate == "MIN")
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

   string check_month(const char * m_pszInput, const char * & scanner)
   {
      scanner = m_pszInput;
      while(ansi_char_is_space(*scanner) && *scanner != '\0')
         scanner++;
      if(*scanner == '\0')
         return "";
      const char * start = scanner;
      while(ansi_char_is_alphabetic(*scanner))
         scanner++;
      string strCandidate = string(m_pszInput, scanner - start);
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
      else if(strCandidate == unitext("março"))
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

   string check_lang_date(const char * m_pszInput, const char * & scanner)
   {
      scanner = m_pszInput;
      while(::str::ch::is_whitespace(scanner) && *scanner != '\0')
         scanner = ::str::utf8_inc(scanner);
      if(*scanner == '\0')
         return "";
      const char * start = scanner;
      while(::str::ch::is_letter(scanner))
         scanner = ::str::utf8_inc(scanner);
      string strCandidate = string(m_pszInput, scanner - start);
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
      else if(strCandidate == unitext("amanhã"))
      {
         return strCandidate;
      }
      else if(strCandidate == "ontem")
      {
         return strCandidate;
      }
      return "";
   }

   string check_natural(const char * m_pszInput, const char * & scanner)
   {
      scanner = m_pszInput;
      if(*scanner == '\0')
         return "";
      if(!::str::ch::is_digit(scanner))
         return "";
      const char * start = scanner;
      scanner = ::str::utf8_inc(scanner);
      while(::str::ch::is_digit(scanner))
      {
         scanner = ::str::utf8_inc(scanner);
      }
      return string(start, scanner - start);
   }


   string check_lang_offset(const char * m_pszInput, const char * & scanner)
   {
      if(check_end_expression(m_pszInput, scanner))
         return "";
      const char * start = m_pszInput;
      while(!::str::ch::is_space_char(scanner) && *scanner != '\0')
         scanner = ::str::utf8_inc(scanner);
      string strCandidate = string(m_pszInput, scanner - start);
      strCandidate.make_lower();
      if(strCandidate == "ago")
      {
         return strCandidate;
      }
      else if(strCandidate == unitext("atrás"))
      {
         return strCandidate;
      }
      return "";
   }

   string check_natural_separator(const char * m_pszInput, const char * & scanner)
   {
      scanner = m_pszInput;
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

   string check_date(const char * m_pszInput, const char * & scanner)
   {
      if(check_end_expression(m_pszInput, scanner))
         return "";
      const char * start = m_pszInput;
      string strNat1 = check_natural(m_pszInput, scanner);
      if(strNat1.has_char())
      {
         m_pszInput = scanner;
         string strSep1 = check_natural_separator(m_pszInput, scanner);
         if(strSep1.has_char())
         {
            m_pszInput = scanner;
            string strNat2 = check_natural(m_pszInput, scanner);
            if(strNat2.has_char())
            {
               m_pszInput = scanner;
               string strSep2 = check_natural_separator(m_pszInput, scanner);
               if(strSep2.has_char() && strSep2 == strSep1)
               {
                  m_pszInput = scanner;
                  string strNat3 = check_natural(m_pszInput, scanner);
                  if(strNat3.has_char())
                  {
                     m_pszInput = scanner;
                     if(!check_expression_separator(m_pszInput, scanner))
                     {
                        __throw(::exception::exception("invalid date"));
                     }
                     return string(start, scanner - start);
                  }

               }
               else if(strSep1 == strSep2)
               {
                  m_pszInput = scanner;
                  string strMonth = check_month(m_pszInput, scanner);
                  if(strMonth.has_char())
                  {
                     m_pszInput = scanner;
                     if(!check_expression_separator(m_pszInput, scanner))
                     {
                        __throw(::exception::exception("invalid date"));
                     }
                     return string(start, scanner - start);
                  }
                  else
                  {
                     __throw(::exception::exception("invalid date"));
                  }
               }
               else if(!strSep2.has_char())
               {
                  m_pszInput = scanner;
                  if(!check_expression_separator(m_pszInput, scanner))
                  {
                     __throw(::exception::exception("invalid date"));
                  }
                  return string(start, scanner - start);
               }
               else
               {
                  __throw(::exception::exception("invalid date"));
               }
            }
            else
            {
               m_pszInput = scanner;
               string strMonth = check_month(m_pszInput, scanner);
               if(strMonth.has_char())
               {
                  m_pszInput = scanner;
                  string strSep2 = check_natural_separator(m_pszInput, scanner);
                  if(strSep2.has_char() && strSep2 == strSep1)
                  {
                     m_pszInput = scanner;
                     string strNat3 = check_natural(m_pszInput, scanner);
                     if(strNat3.has_char())
                     {
                        m_pszInput = scanner;
                        if(!check_expression_separator(m_pszInput, scanner))
                        {
                           __throw(::exception::exception("invalid date"));
                        }
                        return string(start, scanner - start);
                     }

                  }
                  else if(strSep2 == strSep1)
                  {
                     m_pszInput = scanner;
                     string strNat2 = check_natural(m_pszInput, scanner);
                     if(strNat2.has_char())
                     {
                        m_pszInput = scanner;
                        if(!check_expression_separator(m_pszInput, scanner))
                        {
                           __throw(::exception::exception("invalid date"));
                        }
                        return string(start, scanner - start);
                     }
                     else
                     {
                        __throw(::exception::exception("invalid date"));
                     }
                  }
                  else
                  {
                     __throw(::exception::exception("invalid date"));
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

   string check_offset(const ::aura::str_context * pcontext, const char * m_pszInput, const char * & scanner)
   {
      if(check_end_expression(m_pszInput, scanner))
         return "";
      const char * start = m_pszInput;
      i32 iCount = 0;
      while(true)
      {
         m_pszInput = scanner;
         string strNat = check_natural(m_pszInput, scanner);
         if(!strNat.has_char())
         {
            if(iCount > 0)
               break;
            return "";
         }
         m_pszInput = scanner;
         string strUnit = check_unit(pcontext, m_pszInput, scanner);
         if(!strNat.has_char())
         {
            return "";
         }
         iCount++;
      }
      string strOff = check_lang_offset(m_pszInput, scanner);
      return string(start, scanner - start);
   }

   string consume_date_expression(const ::aura::str_context * pcontext, const char * & m_pszInput)
   {
      const char * scanner;
      if(check_end_expression(m_pszInput, scanner))
         return "";
      const char * start = m_pszInput;
      string strDate = check_date(m_pszInput, scanner);
      if(strDate.has_char())
      {
         m_pszInput = scanner;
         string strOffset = check_offset(pcontext, m_pszInput, scanner);
         if(strOffset.has_char())
         {
            m_pszInput = scanner;
            if(check_end_expression(m_pszInput, scanner))
               return string(start, scanner - start);
            else
            {
               __throw(::exception::exception("invalid date expression"));
            }
         }
         else
         {
            m_pszInput = scanner;
            if(check_end_expression(m_pszInput, scanner))
               return string(start, scanner - start);
            else
            {
               __throw(::exception::exception("invalid date expression"));
            }
         }
      }
      else
      {
         string strLangDate = check_lang_date(m_pszInput, scanner);
         if(strLangDate.has_char())
         {
            m_pszInput = scanner;
            string strOffset = check_offset(pcontext, m_pszInput, scanner);
            if(strOffset.has_char())
            {
               m_pszInput = scanner;
               if(check_end_expression(m_pszInput, scanner))
                  return string(start, scanner - start);
               else
               {
                  __throw(::exception::exception("invalid date expression"));
               }
            }
            else
            {
               m_pszInput = scanner;
               if(check_end_expression(m_pszInput, scanner))
                  return string(start, scanner - start);
               else
               {
                  __throw(::exception::exception("invalid date expression"));
               }
            }
         }
         else
         {
            m_pszInput = scanner;
            string strOffset = check_offset(pcontext, m_pszInput, scanner);
            if(strOffset.has_char())
            {
               m_pszInput = scanner;
               if(check_end_expression(m_pszInput, scanner))
                  return string(start, scanner - start);
               else
               {
                  __throw(::exception::exception("invalid date expression"));
               }
            }
            else
            {
               m_pszInput = scanner;
               if(check_end_expression(m_pszInput, scanner))
                  return string(start, scanner - start);
               else
               {
                  __throw(::exception::exception("invalid date expression"));
               }
            }
         }
      }
   }

   scanner::scanner(::object * pobject, const ::aura::str_context * pcontext)
   {
      m_pstrcontext     = pcontext;
      m_ptoken          = nullptr;
      m_pszInput        = nullptr;
   }

   scanner::~scanner()
   {
   }


   void scanner::initialize(const char * psz)
   {
      m_pszInput          = psz;
      m_pszNextInput     = m_pszInput;
   }


   void scanner::peek()
   {
      const char *beginning;
      if(m_pszInput != m_pszNextInput && m_pszNextInput != nullptr)
         return;
      beginning = m_pszInput;
      m_ptoken = look_ahead();
      m_pszNextInput = m_pszInput;
      m_pszInput = beginning;
   }

   void scanner::next()
   {
      m_pszInput = m_pszNextInput;
   }

   token * scanner::look_ahead()
   {
      token * token;
      token = new class token;
      if(token == nullptr)
         __throw(memory_exception());
      while(ansi_char_is_space(*m_pszInput))
         m_pszInput++;
      if(*m_pszInput == '\0')
      {
         token->value = token::end;
         return token;
      }
      if(*m_pszInput == '+')
      {
         token->value = token::addition;
         m_pszInput++;
         return token;
      }
      else if(*m_pszInput == '-')
      {
         token->value = token::subtraction;
         m_pszInput++;
         return token;
      }
      else if(*m_pszInput == '*')
      {
         token->value = token::multiplication;
         m_pszInput++;
         return token;
      }
      else if(*m_pszInput == '/')
      {
         token->value = token::division;
         m_pszInput++;
         return token;
      }
      else if(*m_pszInput == '(')
      {
         token->value = token::open_paren;
         m_pszInput++;
         return token;
      }
      else if(*m_pszInput == ',')
      {
         token->value = token::virgula;
         m_pszInput++;
         return token;
      }
      else if(*m_pszInput == ')')
      {
         token->value = token::close_paren;
         m_pszInput++;
         return token;
      }
      else
      {
         token->m_str = consume_date_expression(m_pstrcontext, m_pszInput);
         while(::str::ch::is_space_char(m_pszInput))
            m_pszInput = ::str::utf8_inc(m_pszInput);
         if(*m_pszInput == '(')
         {
            token->value = token::function;
         }
         else
         {
            token->value = token::identifier;
         }
         return token;
      }
   }


} // namespace datetime
