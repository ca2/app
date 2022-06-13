#pragma once




template < typename STRING >
bool windows_get_alternate_path(STRING & str)
{

   if (str.begins_ci(::str().windows_bbqb(str)))
   {

      return false;

   }

   if (str.begins_ci(::str().windows_bb(str)))
   {

      str = ::str().windows_bbqbunc(str) + str.Mid(1);

   }
   else
   {

      str = ::str().windows_bbqb(str) + str;

   }

   return true;

}

