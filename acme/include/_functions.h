// Created by camilo on 2022-11-01 23:14 <3ThomasBorregaardSorensen!!
#pragma once


CLASS_DECL_ACME enum_dialog_result message_box_for_console(const char * psz, const char * pszTitle, const ::e_message_box & emessagebox);


inline ::u64 make64_from32(::u32 l, ::u32 h)
{

   return ((::u64)l) | (((::u64)h) << 32);

}


inline bool __is_valid_address(const void * p, memsize size, bool bReadWrite = true)
{

#ifdef DEEP_DEBUG

   byte * pbyte = (byte *)p;

   if (bReadWrite)
   {

      for (::index i = 0; i < size; i++)
      {

         ::byte & b = *pbyte;

         b++; // tests read/write of byte b

         b--; // restablish it

      }

   }
   else
   {

      ::i32 sum = 0;

      for (::index i = 0; i < size; i++)
      {

         ::byte & b = *pbyte;

         sum += b; // tests read of byte b

      }

   }

#endif // DEEP_DEBUG

   return ::is_set(p);

}


inline bool __is_valid_string(const widechar * pwsz, memsize nMaxLength = INT_MAX)
{

   return ::__is_valid_address(pwsz, nMaxLength);

}


inline bool __is_valid_string(const char * psz, memsize nMaxLength = UINT_MAX)
{

   return ::__is_valid_address(psz, nMaxLength);

}



CLASS_DECL_ACME void copy(::string & str, const particle & particle);



inline int_bool address_overlaps(const void * pszDst, const void * pszSrc, strsize srclen)
{

   return (((byte *)pszSrc) <= ((byte *)pszDst) && ((byte *)pszSrc) + srclen > ((byte *)pszDst))
      || (((byte *)pszDst) <= ((byte *)pszSrc) && ((byte *)pszDst) + srclen > ((byte *)pszSrc));

}



