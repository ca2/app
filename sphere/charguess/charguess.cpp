/*
   libcharguess   -  Guess the encoding/charset of a string
    Copyright (C) 2003  Stephane Corbe <noubi@users.sourceforge.net>
   Based on Mozilla sources

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include "framework.h"
#include "universal.h"



extern "C" charguess_det CharGuessInit()
{

   nsUniversalDetector* det = ___new nsUniversalDetector();

   if (det != nullptr)
      return (charguess_det) det;
   else
      return nullptr;

}

const_char_pointer GuessChardet(charguess_det p, const ::scoped_string & scopedstr)
{

   nsUniversalDetector* det = (nsUniversalDetector*) p;

   det->Reset();
   det->HandleData(str, (PRunsigned int) str.length());
   det->DataEnd();

   return det->GetCharset();

}

extern "C" const_char_pointer GuessChardet(charguess_det p, const ::scoped_string & scopedstr)
{

   return GuessChardet(p,(const string &)str);

}

extern "C" void CharGuessDestroy(charguess_det p)
{

   try
   {

      nsUniversalDetector* det = (nsUniversalDetector*)p;

      if(det != nullptr)
         delete det;

   }
   catch(...)
   {

   }

}



unsigned int charguess::get_code_page(const ::scoped_string & scopedstr)
{
   if(str.is_empty())
   {
      return 0;
   }
   else if(!str.case_insensitive_order("Shift_JIS"))
   {
      return 932;
   }
   else if(!str.case_insensitive_order("Big5"))
   {
      return 950;
   }
   else if(!str.case_insensitive_order("gb18030"))
   {
      return 936;
   }
   else if(!str.case_insensitive_order("windows-1252"))
   {
      return 1252;
   }
   else if(!str.case_insensitive_order("UTF-8"))
   {
      return CP_UTF8;
   }
   else
   {
      return 0;
   }
}
