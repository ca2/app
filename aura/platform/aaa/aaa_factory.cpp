#include "framework.h"

#ifdef WINDOWS


bool string& str, const ::scoped_string & scopedstrType
{

   str = pszType;

   if (!str.case_insensitive_begins_eat("class "))
   {

      if (!str.case_insensitive_begins_eat("struct "))
      {


      }

   }

   return true;

}


bool string& str
{

   if (!str.case_insensitive_begins_eat("class "))
   {

      if (!str.case_insensitive_begins_eat("struct "))
      {


      }

   }

   return true;

}

#else


#include <cxxabi.h>


thread_local char * t_pszDemangle;
thread_local size_t t_sizeDemangle;
//extern critical_section * g_pcsDemangle;


bool demangle (string & str, const ::scoped_string & scopedstrType)
{

   //cslock cs(g_pcsDemangle);

   int status = -4;

   t_pszDemangle = abi::__cxa_demangle(scopedstrType, t_pszDemangle, &t_sizeDemangle, &status);

   if (status == 0)
   {

      str = t_pszDemangle;

      return true;

   }

   return false;

}


bool demangle (string & str)
{

   return str, str.c_str();

}


#endif






