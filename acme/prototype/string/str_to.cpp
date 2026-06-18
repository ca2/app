// Created by camilo on 2022-06-07 07:39 <3ThomasBorregaardSorense!! Mummi and bilbo!!
#include "framework.h"
#include "str.h"
#include "string.h"


bool str::to(::i64 & i, const ::scoped_string & scopedstr)
{

   const_char_pointer pszEnd = nullptr;

   ::i64 iConversion = ::ansi_to_i64(scopedstr, &pszEnd);

   if (pszEnd == scopedstr.data())
   {

      return false;

   }

   i = iConversion;

   return true;

}


bool str::to(::i32 & i, const ::scoped_string & scopedstr)
{

   const_char_pointer pszEnd = nullptr;

   i = ::ansi_to_int(scopedstr, &pszEnd, 10);

   if (pszEnd == scopedstr.data())
   {

      return false;

   }

   return true;

}


bool str::to(::i64 & i, ::i32 iBase, const ::scoped_string & scopedstr)
{

   if (iBase < 0 || iBase == 1 || iBase > 36)
   {

      return false;

   }

   char_pointer pszEnd;

#ifdef WINDOWS

   ::i64 iConversion = ::_strtoi64(scopedstr, &pszEnd, iBase);

#else

   ::i64 iConversion = ::ansi_to_i64(scopedstr, (const_char_pointer *) & pszEnd, iBase);

#endif

   if (pszEnd == scopedstr.data())
   {

      return false;

   }

   i = iConversion;

   return true;

}

bool str::to(::i32 & i, ::i32 iBase, const ::scoped_string & scopedstr)
{

   if (iBase < 0 || iBase == 1 || iBase > 36)
      return false;

   char_pointer pszEnd;

#ifdef WINDOWS

   ::i64 iConversion = ::_strtoi64(scopedstr, &pszEnd, iBase);

#else

   ::i64 iConversion = ::ansi_to_i64(scopedstr, (const_char_pointer *) & pszEnd, iBase);

#endif

   if (pszEnd == scopedstr.data())
   {

      return false;

   }

   if (iConversion > numeric_info< ::i32 >::maximum())
   {

      return false;

   }

   i = (::i32)iConversion;

   return true;

}

bool str::to(::u64 & u, const ::scoped_string & scopedstr)
{

   const_char_pointer pszEnd = nullptr;

   ::u64 uiConversion = ::ansi_to_i64(scopedstr, &pszEnd);

   if (pszEnd == scopedstr.data())
   {

      return false;

   }

   u = uiConversion;

   return true;

}

bool str::to(::u32 & u, const ::scoped_string & scopedstr)
{

   const_char_pointer pszEnd = nullptr;

   ::i64 uiConversion = ::ansi_to_u32(scopedstr, &pszEnd);

   if (pszEnd == scopedstr.data())
   {

      return false;

   }

   if (uiConversion > numeric_info < ::u32 > ::maximum())
   {

      return false;

   }

   u = (::u32)uiConversion;

   return true;

}


bool str::to(::u64 & u, ::i32 iBase, const ::scoped_string & scopedstr)
{

   if (iBase < 0 || iBase == 1 || iBase > 36)
   {

      return false;

   }

   const_char_pointer pszEnd = nullptr;

   ::u64 uiConversion = ::ansi_to_u64(scopedstr, &pszEnd, iBase);

   if (pszEnd == scopedstr.data())
   {

      return false;

   }

   u = uiConversion;

   return true;

}


bool str::to(::u32 & u, ::i32 iBase, const ::scoped_string & scopedstr)
{

   if (iBase < 0 || iBase == 1 || iBase > 36)
   {

      return false;

   }

   const_char_pointer pszEnd = nullptr;

   ::u32 uiConversion = ::ansi_to_u32(scopedstr, &pszEnd, iBase);

   if (pszEnd == scopedstr.as_string().c_str())
   {

      return false;

   }

   if (uiConversion > numeric_info< ::u32 >::maximum())
   {

      return false;

   }

   u = uiConversion;

   return true;

}

iptr str::to_iptr(const ::scoped_string & scopedstr)
{

#if defined(_LP64) || defined(_AMD64_)

   return to_i64(scopedstr);

#else
   return to_int(scopedstr);

#endif

}




