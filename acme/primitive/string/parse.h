/** \file parse.h - parse a string
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

#pragma once


#include "string.h"

// Splits a string whatever way you want.

class CLASS_DECL_ACME parse
{
public:

   // publicy made(camilo already xpced a good public, so i said first :-)
   const char * m_psz;
   string   pa_splits;
   string   m_strWord;
   strsize  m_iPos;
   char     pa_breakchar;
   char     pa_enable;
   char     pa_disable;
   i16    pa_nospace;
   bool     m_bQuote;
   strsize  m_iLen;

   parse();
   parse(::range < const ::ansi_character * > range) : parse(range.begin(), range.size()) {}
   parse(::range < const ::ansi_character * > range, ::range < const ::ansi_character * > splits):parse(range.begin(), range.size(), splits) {}
   parse(::range < const ::ansi_character * > range, ::range < const ::ansi_character * > splits, i16 nospace):parse(range.begin(), range.size(),splits,nospace) {}
   parse(const ::ansi_character * psz, strsize iLen);
   parse(const ::ansi_character * psz, strsize iLen, ::range < const ::ansi_character * > splits);
   parse(const ::ansi_character * psz, strsize iLen, ::range < const ::ansi_character * > splits, i16);
   ~parse();
   i16 issplit(const char);
   void getsplit();
   void getsplit(string &);
   string getword();
   void getword(string &);
   void getword(string &, string &, i32);
   void getsplitword();
   void getsplitword(string &);
   string getrest();
   void getrest(string &);
   long getvalue();
   void setbreak(const char);
   i32 getwordlen();
   i32 getrestlen();

   inline bool has_char() const { return m_iPos < m_iLen; }
   inline bool is_eostr() const { return !has_char();  }
      

   void enablebreak(const char ca)
   {
      pa_enable = ca;
   }

   void disablebreak(const char ca)
   {
      pa_disable = ca;
   }
   void getline();
   void getline(string &);

   // operational functions that does not store resulting word (pa_the_ord) starts with underscore.
   void _get_expandable_line(strsize & start, strsize & end, bool & bFinal);
   void _get_expandable_line(string &);
   void get_expandable_line();

   strsize get_pos() { return m_iPos; }
   void EnableQuote(bool b) { m_bQuote = b; }

};



