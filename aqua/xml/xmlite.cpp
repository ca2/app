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
   int _tcselen(int escape,char * srt,char * end)
   {
      int len = 0;
      char * pch = srt;
      if(end == nullptr) end = (char *)sizeof(long);
      char * prev_escape = nullptr;
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
   void _tcsecpy(char * psz,int escape, const char * srt, const char * end)
   {
      const char * pch = srt;
      if(end == nullptr) end = (char *)sizeof(long);
      const char * prev_escape = nullptr;
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


//   void _tcsecpy2(::ansi_range & rangeTarget, char escape, const ::const_ansi_range & rangeSource)
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
   //int _tcsenicmp(const ::ansi_character * psz,const char * str,character_count len,int escape)
   //{
   //   char * pch = (char *)psz;
   //   char * prev_escape = nullptr;
   //   char * des = (char *)str;
   //   int i = 0;

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
   //   if(psz[i] > des[i])
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
   //char * _tcsenistr(const ::ansi_character * psz,const char * str,character_count len,int escape)
   //{
   //   char * pch = (char *)psz;
   //   char * prev_escape = nullptr;
   //   //char * des = (char *)str;
   //   //int i = 0;

   //   while(pch && *pch)
   //   {
   //      if(escape != 0 && *pch == escape && prev_escape == nullptr)
   //         prev_escape = pch;
   //      else
   //      {
   //         prev_escape = nullptr;
   //         if(_tcsenicmp(pch,str,len,escape) == 0)
   //            return (char *)pch;
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
   //char * _tcseistr(const ::ansi_character * psz,const char * str,int escape)
   //{
   //   character_count len = strlen(str);
   //   return _tcsenistr(psz,str,len,escape);
   //}

   








} // namespace xml










