/** \file parse.cpp - parse a string
 **
 **   Written: 1999-Feb-10 grymse@alhem.net
 **/

/*
Copyright (C) 1999-2007  Anders Hedstrom

This library is made available under the terms of the GNU GPL.

If you would like to use this library in a closed-source application,
a separate license agreement is available. For information about
the closed-source license agreement for the C++ sockets library,
please visit http://www.alhem.net/Sockets/license.html and/or
email license@alhem.net.

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/
#include "framework.h"
#include "parse.h"
//#include "acme/primitive/collection/string_array.h"
////#include "acme/exception/exception.h"


//namespace str {
//

/* implementation of class parse */

   parse::parse()
   :m_psz(nullptr)
   ,pa_splits("")
   ,m_strWord("")
   ,m_iPos(0)
   ,pa_breakchar(0)
   ,pa_enable(0)
   ,pa_disable(0)
   ,pa_nospace(0)
   ,m_bQuote(false)
   ,m_iLen(0)
   {
   }

   parse::parse(const ::ansi_character * psz, strsize iLen)
      :m_psz(psz)
   ,pa_splits("")
   ,m_strWord("")
   ,m_iPos(0)
   ,pa_breakchar(0)
   ,pa_enable(0)
   ,pa_disable(0)
   ,pa_nospace(0)
   ,m_bQuote(false)
   ,m_iLen(iLen)
   {
   }

   parse::parse(const ::ansi_character * s,strsize iLen, ::range < const ::ansi_character * > splits)
   :m_psz(s)
   ,pa_splits(splits)
   ,m_strWord("")
   ,m_iPos(0)
   ,pa_breakchar(0)
   ,pa_enable(0)
   ,pa_disable(0)
   ,pa_nospace(0)
   ,m_bQuote(false)
   ,m_iLen(iLen)
   {
   }

   parse::parse(const ::ansi_character *s,strsize iLen, ::range < const ::ansi_character * > splits,i16 nospace)
   :m_psz(s)
   ,pa_splits(splits)
   ,m_strWord("")
   ,m_iPos(0)
   ,pa_breakchar(0)
   ,pa_enable(0)
   ,pa_disable(0)
   ,pa_nospace(1)
   ,m_bQuote(false)
   ,m_iLen(iLen)
   {
      __UNREFERENCED_PARAMETER(nospace);
   }


   parse::~parse()
   {
   }

   #define C ((m_iPos<m_iLen) ? m_psz[m_iPos] : 0)
//#define CPREV ((m_iPos-1 >=0)&&(m_iPos-1<m_str.length()) ? (m_str.get_at(m_iPos-1) : 0)

   i16 parse::issplit(const char ca)
   {
      for (i32 i = 0; i < pa_splits.length(); i++)
         if (pa_splits[i] == ca)
            return 1;
      return 0;
   }

   void parse::getsplitword()
   {
      index x;
      i32 disabled = 0;
      i32 quote = 0;
      i32 rem = 0;

      if (C == '=')
      {
         x = m_iPos++;
         if (x == m_iPos && C == '=')
            m_iPos++;
      }
      else if (pa_nospace)
      {
         while (C && issplit(C))
            m_iPos++;
         x = m_iPos;
         while (C && !issplit(C) && C != '=' && (C != pa_breakchar || !pa_breakchar || disabled))
         {
            if (pa_breakchar && C == pa_disable)
               disabled = 1;
            if (pa_breakchar && C == pa_enable)
               disabled = 0;
            if (m_bQuote && C == '"')
               quote = 1;
            m_iPos++;
            while (quote && C && C != '"')
            {
               m_iPos++;
            }
            if (m_bQuote && C == '"')
            {
               m_iPos++;
            }
            quote = 0;
         }
         if (x == m_iPos && C == '=')
            m_iPos++;
      }
      else
      {
         if (C == pa_breakchar && pa_breakchar)
         {
            x = m_iPos++;
            rem = 1;
         }
         else
         {
            while (C && (C == ' ' || C == 9 || C == 13 || C == 10 || issplit(C)))
               m_iPos++;
            x = m_iPos;
            while (C && C != ' ' && C != 9 && C != 13 && C != 10 && !issplit(C) && C != '=' &&
               (C != pa_breakchar || !pa_breakchar || disabled))
            {
               if (pa_breakchar && C == pa_disable)
                  disabled = 1;
               if (pa_breakchar && C == pa_enable)
                  disabled = 0;
               if (m_bQuote && C == '"')
               {
                  quote = 1;
                  m_iPos++;
                  while (quote && C && C != '"')
                  {
                     m_iPos++;
                  }
                  if (m_bQuote && C == '"')
                  {
                     m_iPos++;
                  }
               }
               else
                  m_iPos++;
               quote = 0;
            }
            if (C != '=')
            {
               m_iPos++;
               rem = 1;
            }
         }
         if (x == m_iPos && ((C == pa_breakchar && pa_breakchar) || C == '='))
            m_iPos++;
      }

      if(x < m_iLen)
      {

         m_strWord.assign(&m_psz[x],m_iPos - x - rem);

      }
      else
      {

         m_strWord.empty();

      }

   }

   void parse::getsplit()
   {
      index x;

      if (C == '=')
      {
         x = m_iPos++;
      } else
      {
         while (C && (issplit(C)))
            m_iPos++;
         x = m_iPos;
         while (C && !issplit(C) && C != '=')
            m_iPos++;
      }
      if (x == m_iPos && C == '=')
         m_iPos++;

      if(x < m_iLen)
      {

         m_strWord.assign(m_psz + x,m_iPos - x);

      }
      else
      {

         m_strWord.empty();

      }

   }

   string parse::getword()
   {
      index x;
      i32 disabled = 0;
      i32 quote = 0;
      i32 rem = 0;

      if (pa_nospace)
      {
         while (C && issplit(C))
            m_iPos++;
         x = m_iPos;
         while (C && !issplit(C) && (C != pa_breakchar || !pa_breakchar || disabled))
         {
            if (pa_breakchar && C == pa_disable)
               disabled = 1;
            if (pa_breakchar && C == pa_enable)
               disabled = 0;
            if (m_bQuote && C == '"')
               quote = 1;
            m_iPos++;
            while (quote && C && C != '"')
            {
               m_iPos++;
            }
            if (m_bQuote && C == '"')
            {
               m_iPos++;
            }
            quote = 0;
         }
      } else
      {
         if (C == pa_breakchar && pa_breakchar)
         {
            x = m_iPos++;
            rem = 1;
         } else
         {
            while (C && (C == ' ' || C == 9 || C == 13 || C == 10 || issplit(C)))
               m_iPos++;
            x = m_iPos;
            while (C && C != ' ' && C != 9 && C != 13 && C != 10 && !issplit(C) &&
             (C != pa_breakchar || !pa_breakchar || disabled))
            {
               if (pa_breakchar && C == pa_disable)
                  disabled = 1;
               if (pa_breakchar && C == pa_enable)
                  disabled = 0;
               if (m_bQuote && C == '"')
               {
                  quote = 1;
               m_iPos++;
               while (quote && C && C != '"')
               {
                  m_iPos++;
               }
               if (m_bQuote && C == '"')
               {
                  m_iPos++;
               }
               }
               else
                  m_iPos++;
               quote = 0;
            }
            m_iPos++;
            rem = 1;
         }
         if (x == m_iPos && C == pa_breakchar && pa_breakchar)
            m_iPos++;
      }
      if(x < m_iLen)
      {

         m_strWord.assign(&m_psz[x],m_iPos - x - rem);

      }
      else
      {

         m_strWord.empty();

      }
      return m_strWord;
   }

   void parse::getword(string &s)
   {
      s = parse::getword();
   }

   void parse::getsplit(string &s)
   {
      parse::getsplit();
      s = m_strWord;
   }


   void parse::getsplitword(string & s)
   {

      parse::getsplitword();

      s = m_strWord;

   }


   void parse::getword(string &s,string &fill,i32 l)
   {
      parse::getword();
      s = "";
      while (s.length() + m_strWord.length() < (index)l)
         s += fill;
      s += m_strWord;
   }

   string parse::getrest()
   {
      string s;
		   getrest(s);  //--**\/\/\!!??
      return s;
   }

   void parse::getrest(string &s)
   {
      while (C && (C == ' ' || C == 9 || issplit(C)))
         m_iPos++;
      if(m_iPos < m_iLen)
      {

         s.assign(&m_psz[m_iPos],m_iLen - m_iPos);

      }
      else
      {

         s.empty();

      }

   }

   long parse::getvalue()
   {
      parse::getword();
      return atol(m_strWord);
   }

   void parse::setbreak(const char ca)
   {
      pa_breakchar = ca;
   }

   i32 parse::getwordlen()
   {
      index x,y = m_iPos,len;

      if (C == pa_breakchar && pa_breakchar)
      {
         x = m_iPos++;
      } else
      {
         while (C && (C == ' ' || C == 9 || C == 13 || C == 10 || issplit(C)))
            m_iPos++;
         x = m_iPos;
         while (C && C != ' ' && C != 9 && C != 13 && C != 10 && !issplit(C) && (C != pa_breakchar || !pa_breakchar))
            m_iPos++;
      }
      if (x == m_iPos && C == pa_breakchar && pa_breakchar)
         m_iPos++;
      len = m_iPos - x;
      m_iPos = y;
      return (i32)maximum(0,len);
   }

   i32 parse::getrestlen()
   {
      index y = m_iPos;
      index len;

      while (C && (C == ' ' || C == 9 || issplit(C)))
         m_iPos++;
      len = m_iLen - m_iPos;
      m_iPos = y;
      return (i32)maximum(0, len);
   }




   void parse::getline()
   {
      index x;

      x = m_iPos;
      while (C && C != 13 && C != 10)
         m_iPos++;

      if(x < m_iLen)
      {

         m_strWord.assign(&m_psz[x],m_iPos - x);

      }
      else
      {

         m_strWord.empty();

      }


      if (C == 13)
         m_iPos++;
      if (C == 10)
         m_iPos++;
   }


   void parse::getline(string &s)
   {
      getline();
      s = m_strWord;
   }

   void parse::_get_expandable_line(strsize & start, strsize & end, bool & bFinal)
   {

      start = m_iPos;

      while(m_iPos < m_iLen && m_psz[m_iPos] != '\r' && m_psz[m_iPos] != '\n')
         m_iPos+=utf8_unicode_length(m_psz[m_iPos]);

      end = m_iPos;

      bFinal = m_iPos >= m_iLen || m_iPos < 1 || m_psz[m_iPos - 1] != '\\';

      if(m_iPos < m_iLen &&  m_psz[m_iPos] == '\r')
         m_iPos++;

      if(m_iPos < m_iLen &&  m_psz[m_iPos] == '\n')
         m_iPos++;

   }


   void parse::_get_expandable_line(string & s)
   {
      strsize start;
      strsize end;
      bool bFinal;
      while(has_char())
      {
         _get_expandable_line(start,end,bFinal);

         s += string(&m_psz[start],end - start);
         if(bFinal)
            break;
      }

   }

   void parse::get_expandable_line()
   {

      m_strWord.empty();
      _get_expandable_line(m_strWord);

   }
//
//} // namespace str
//




   CLASS_DECL_ACME string consume_token(::string & str, const ::string_array & straSeparator)
   {

      ::index iFind = -1;

      ::index iSeparator = -1;

      for (::index i = 0; i < straSeparator.get_size(); i++)
      {

         if (straSeparator[i].is_empty())
         {

            throw exception(error_bad_argument);

         }

         ::index iFindSeparator = str.find_index(straSeparator[i]);

         if (::not_found(iFind) || (iFindSeparator > 0 && iFindSeparator < iFind))
         {

            iFind = iFindSeparator;

            iSeparator = i;

         }

      }

      ::string strToken;

      if (::found(iFind))
      {

         strToken = str(0, iFind);

         str = str.substr(iFind + straSeparator[iSeparator].length());

      }

      return strToken;

   }
