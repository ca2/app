/**********************************************************************
 * Copyright (ca) 2002, Leo Seib, Hannover
 *
 * Project:SQLiteDataset C++ Dynamic Library
 * Module: StringHelper class realisation file
 * Author: Leo Seib      E-Mail: lev@almaty.pointstrike.net
 * begin: 5/04/2002
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 **********************************************************************/
#include "framework.h"

str_helper::str_helper() {work_str = "";}

str_helper::str_helper(const char *s){work_str = s;}

string str_helper::get_str() {return work_str;} 

void str_helper::set_str(const char *s) {work_str = s; };


string str_helper::before(string s, bool &is_found)
{
    
   is_found = false;
   
   strsize pos = work_str.find(s);
   
   strsize idx = pos + s.get_length();
    
   is_found = pos >= 0;
   
   if (idx == work_str.get_length()) 
   {
      return work_str.Mid(0,pos); 
   }
   else
   {
      if ((pos >= 0) && (!( (work_str[idx]>48 && work_str[idx]<58) || (work_str[idx]>64 && work_str[idx]<91) || (work_str[idx]>97 && work_str[idx]<123) || work_str[idx]==95 )))
         return work_str.Mid(0,pos); 
      else //return (string)nullptr;
      {
         string tmp(""); 
         return tmp;
      }
   }

}

string str_helper::after(string s) {return work_str.Mid(work_str.find(s)+s.get_length(),work_str.get_length());}

string str_helper::replace(string pattern, string by_what) {
    bool is_found;
    string bf = before(pattern,is_found);
    string aft("");
    string result("");
    while (is_found) {
      aft = after(pattern);
      result = bf + by_what + aft;
      work_str = result;
      bf = before(pattern,is_found);
    }
    if (result.is_empty()) result = work_str;
    return result;
}


