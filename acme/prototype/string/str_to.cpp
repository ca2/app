// Created by camilo on 2022-06-07 07:39 <3ThomasBorregaardSorense!! Mummi and bilbo!!
#include "framework.h"
#include "str.h"
#include "string.h"


bool str::to(long long & i, const ::scoped_string & scopedstr)
{

   const_char_pointer pszEnd = nullptr;

   long long iConversion = ::ansi_to_long_long(scopedstr, &pszEnd);

   if (pszEnd == scopedstr.data())
   {

      return false;

   }

   i = iConversion;

   return true;

}


bool str::to(int & i, const ::scoped_string & scopedstr)
{

   const_char_pointer pszEnd = nullptr;

   i = ::ansi_to_int(scopedstr, &pszEnd, 10);

   if (pszEnd == scopedstr.data())
   {

      return false;

   }

   return true;

}


bool str::to(long long & i, int iBase, const ::scoped_string & scopedstr)
{

   if (iBase < 0 || iBase == 1 || iBase > 36)
   {

      return false;

   }

   char * pszEnd;

#ifdef WINDOWS

   long long iConversion = ::_strtoi64(scopedstr, &pszEnd, iBase);

#else

   long long iConversion = ::ansi_to_long_long(scopedstr, (const_char_pointer *) & pszEnd, iBase);

#endif

   if (pszEnd == scopedstr.data())
   {

      return false;

   }

   i = iConversion;

   return true;

}

bool str::to(int & i, int iBase, const ::scoped_string & scopedstr)
{

   if (iBase < 0 || iBase == 1 || iBase > 36)
      return false;

   char * pszEnd;

#ifdef WINDOWS

   long long iConversion = ::_strtoi64(scopedstr, &pszEnd, iBase);

#else

   long long iConversion = ::ansi_to_long_long(scopedstr, (const_char_pointer *) & pszEnd, iBase);

#endif

   if (pszEnd == scopedstr.data())
   {

      return false;

   }

   if (iConversion > numeric_info< int >::maximum())
   {

      return false;

   }

   i = (int)iConversion;

   return true;

}

bool str::to(unsigned long long & u, const ::scoped_string & scopedstr)
{

   const_char_pointer pszEnd = nullptr;

   unsigned long long uiConversion = ::ansi_to_long_long(scopedstr, &pszEnd);

   if (pszEnd == scopedstr.data())
   {

      return false;

   }

   u = uiConversion;

   return true;

}

bool str::to(unsigned int & u, const ::scoped_string & scopedstr)
{

   const_char_pointer pszEnd = nullptr;

   long long uiConversion = ::ansi_to_unsigned_int(scopedstr, &pszEnd);

   if (pszEnd == scopedstr.data())
   {

      return false;

   }

   if (uiConversion > numeric_info < unsigned int > ::maximum())
   {

      return false;

   }

   u = (unsigned int)uiConversion;

   return true;

}


bool str::to(unsigned long long & u, int iBase, const ::scoped_string & scopedstr)
{

   if (iBase < 0 || iBase == 1 || iBase > 36)
   {

      return false;

   }

   const_char_pointer pszEnd = nullptr;

   unsigned long long uiConversion = ::ansi_to_unsigned_long_long(scopedstr, &pszEnd, iBase);

   if (pszEnd == scopedstr.data())
   {

      return false;

   }

   u = uiConversion;

   return true;

}


bool str::to(unsigned int & u, int iBase, const ::scoped_string & scopedstr)
{

   if (iBase < 0 || iBase == 1 || iBase > 36)
   {

      return false;

   }

   const_char_pointer pszEnd = nullptr;

   unsigned int uiConversion = ::ansi_to_unsigned_int(scopedstr, &pszEnd, iBase);

   if (pszEnd == scopedstr.as_string().c_str())
   {

      return false;

   }

   if (uiConversion > numeric_info< unsigned int >::maximum())
   {

      return false;

   }

   u = uiConversion;

   return true;

}

iptr str::to_iptr(const ::scoped_string & scopedstr)
{

#if defined(_LP64) || defined(_AMD64_)

   return to_long_long(scopedstr);

#else
   return to_int(scopedstr);

#endif

}




