#include "framework.h"

#ifdef WINDOWS


bool demangle(string& str, const char* pszType)
{

   str = pszType;

   if (!str::begins_eat_ci(str, "class "))
   {

      if (!str::begins_eat_ci(str, "struct "))
      {


      }

   }

   return true;

}


//bool demangle(string& str)
//{
//
//   if (!str::begins_eat_ci(str, "class "))
//   {
//
//      if (!str::begins_eat_ci(str, "struct "))
//      {
//
//
//      }
//
//   }
//
//   return true;
//
//}

#else


#include <cxxabi.h>


thread_local char * t_pszDemangle;
thread_local size_t t_sizeDemangle;
//extern critical_section * g_pcsDemangle;


bool demangle (string & str, const char * pszType)
{

   //critical_section_lock cs(g_pcsDemangle);

   int status = -4;

   t_pszDemangle = abi::__cxa_demangle(pszType, t_pszDemangle, &t_sizeDemangle, &status);

   if (status == 0)
   {

      str = t_pszDemangle;

      return true;

   }

   return false;

}


//bool demangle (string & str)
//{
//
//   return demangle(str, str.c_str());
//
//}


#endif






