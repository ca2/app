#include "framework.h"


namespace xml
{




   //========================================================
   // Name   : _tcselen
   // Desc   : similar with strlen with escape process
   // Param  : escape - will be escape character
   // Return :
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   ::i32 _tcselen(::i32 escape,char_pointer srt,char_pointer end)
   {
      ::i32 len = 0;
      char_pointer pch = srt;
      if(end == nullptr) end = (char_pointer )sizeof(long);
      char_pointer prev_escape = nullptr;
      while(pch && *pch && pch < end)
      {
         if(escape != 0 && *pch == escape && prev_escape == nullptr)
            prev_escape = pch;
         else
         {
            prev_escape = nullptr;
            len++;
         }
         pch++;
      }
      return len;
   }

   //========================================================
   // Name   : _tcsecpy
   // Desc   : similar with _tcscpy with escape process
   // Param  : escape - will be escape character
   // Return :
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   void _tcsecpy(char_pointer psz,::i32 escape, const_char_pointer srt, const_char_pointer end)
   {
      const_char_pointer pch = srt;
      if(end == nullptr) end = (char_pointer )sizeof(long);
      const_char_pointer prev_escape = nullptr;
      while(pch && *pch && pch < end)
      {
         if(escape != 0 && *pch == escape && prev_escape == nullptr)
            prev_escape = pch;
         else
         {
            prev_escape = nullptr;
            *psz++ = *pch;
         }

         pch++;
      }

      *psz = '\0';

   }


//   void _tcsecpy2(::ansi_range & rangeTarget, ::i8 escape, const ::const_ansi_range & rangeSource)
//   {
//
//      auto pTarget = rangeTarget.m_begin;
//
//      auto pSource = rangeSource.m_begin;
//
//      bool bEscaping = false;
//
//      while(pSource < rangeSource.m_end && pTarget < rangeTarget.m_end)
//      {
//
//         if(bEscaping)
//         {
//
//            bEscaping = false;
//
//            *pTarget++ = *pSource;
//
//         }
//         else if(*pSource == escape)
//         {
//
//            bEscaping = true;
//
//         }
//         else
//         {
//
//            *pTarget++ = *pSource;
//
//         }
//
//         pSource++;
//
//      }
//
//      *pTarget = '\0';
//
//      rangeTarget.m_end = pTarget;
//
//   }


   
   ////========================================================
   //// Name   : _tcsenicmp
   //// Desc   : similar with case_insensitive_ansi_count_compare with escape process
   //// Param  : escape - will be escape character
   //// Return :
   ////--------------------------------------------------------
   //// Coder    Date                      Desc
   //// bro      2002-10-29
   ////========================================================
   //::i32 _tcsenicmp(const_char_pointer psz,const_char_pointer str,character_count len,::i32 escape)
   //{
   //   char_pointer pch = (char_pointer )psz;
   //   char_pointer prev_escape = nullptr;
   //   char_pointer des = (char_pointer )str;
   //   ::i32 i = 0;

   //   while(pch && *pch && i < len)
   //   {
   //      if(escape != 0 && *pch == escape && prev_escape == nullptr)
   //         prev_escape = pch;
   //      else
   //      {
   //         prev_escape = nullptr;
   //         if(tolower(*pch) != tolower(des[i]))
   //            break;
   //         i++;
   //      }
   //      pch ++;
   //   }

   //   // find
   //   if(i == len)
   //      return 0;
   //   if(scopedstr[i] > des[i])
   //      return 1;
   //   return -1;
   //}

   ////========================================================
   //// Name   : _tcsenistr
   //// Desc   : similar with _tcsistr with escape process
   //// Param  : escape - will be escape character
   //// Return :
   ////--------------------------------------------------------
   //// Coder    Date                      Desc
   //// bro      2002-10-29
   ////========================================================
   //char_pointer _tcsenistr(const_char_pointer psz,const_char_pointer str,character_count len,::i32 escape)
   //{
   //   char_pointer pch = (char_pointer )psz;
   //   char_pointer prev_escape = nullptr;
   //   //char_pointer des = (char_pointer )str;
   //   //::i32 i = 0;

   //   while(pch && *pch)
   //   {
   //      if(escape != 0 && *pch == escape && prev_escape == nullptr)
   //         prev_escape = pch;
   //      else
   //      {
   //         prev_escape = nullptr;
   //         if(_tcsenicmp(pch,str,len,escape) == 0)
   //            return (char_pointer )pch;
   //      }
   //      pch++;
   //   }
   //   return pch;
   //}

   //========================================================
   // Name   : _tcseistr
   // Desc   : similar with _tcsistr with escape process
   // Param  : escape - will be escape character
   // Return :
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   //char_pointer _tcseistr(const_char_pointer psz,const_char_pointer str,::i32 escape)
   //{
   //   character_count len = strlen(str);
   //   return _tcsenistr(scopedstr,str,len,escape);
   //}

   








} // namespace xml










