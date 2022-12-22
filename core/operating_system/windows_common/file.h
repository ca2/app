#pragma once




template < typename STRING >
bool windows_get_alternate_path(STRING & str)
{

   if (str.case_insensitive_begins(::str().windows_bbqb(str)))
   {

      return false;

   }

   if (str.case_insensitive_begins(::str().windows_bb(str)))
   {

      str = ::str().windows_bbqbunc(str) + str.substr(1);

   }
   else
   {

      str = ::str().windows_bbqb(str) + str;

   }

   return true;

}

