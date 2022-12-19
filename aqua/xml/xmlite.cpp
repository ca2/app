#include "framework.h"


namespace xml
{



   //========================================================
   // Name   : _tcsechr
   // Desc   : similar with strchr with escape process
   // Param  : escape - will be escape character
   // Return :
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   char * _tcsechr(const scoped_string & str,i32 ch,i32 escape)
   {
      char * pch = (char *)psz;

      while(pch && *pch)
      {
         if(escape != 0 && *pch == escape)
            pch++;
         else
            if(*pch == ch)
               return (char *)pch;
         pch++;
      }
      return pch;
   }

   //========================================================
   // Name   : _tcselen
   // Desc   : similar with strlen with escape process
   // Param  : escape - will be escape character
   // Return :
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   i32 _tcselen(i32 escape,char * srt,char * end)
   {
      i32 len = 0;
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
   void _tcsecpy(char * psz,i32 escape, const char * srt, const char * end)
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


   void _tcsecpy2(char * psz,char escape, const char * srt, const char * * end)
   {
      
      const char * pch = srt;
      
      bool bEscaping = false;

      while(pch < *end)
      {

         if(bEscaping)
         {

            bEscaping = false;

            *psz++ = *pch;

         }
         else if(*pch == escape)
         {

            bEscaping = true;

         }
         else
         {
            
            *psz++ = *pch;

         }

         pch++;

      }

      *psz = '\0';

      *end = psz;

   }


   //========================================================
   // Name   : _tcsepbrk
   // Desc   : similar with ansi_scan with escape process
   // Param  : escape - will be escape character
   // Return :
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   char * _tcsepbrk(const scoped_string & str,const char * chset,i32 escape)
   {
      char * pch = (char *)psz;
      char * prev_escape = nullptr;
      while(pch && *pch)
      {
         if(escape != 0 && *pch == escape && prev_escape == nullptr)
            prev_escape = pch;
         else
         {
            prev_escape = nullptr;
            if(strchr(chset,*pch))
               return (char *)pch;
         }
         pch++;
      }
      return pch;
   }

   //========================================================
   // Name   : _tcsenicmp
   // Desc   : similar with ansi_count_compare_ci with escape process
   // Param  : escape - will be escape character
   // Return :
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   i32 _tcsenicmp(const scoped_string & str,const char * str,strsize len,i32 escape)
   {
      char * pch = (char *)psz;
      char * prev_escape = nullptr;
      char * des = (char *)str;
      i32 i = 0;

      while(pch && *pch && i < len)
      {
         if(escape != 0 && *pch == escape && prev_escape == nullptr)
            prev_escape = pch;
         else
         {
            prev_escape = nullptr;
            if(tolower(*pch) != tolower(des[i]))
               break;
            i++;
         }
         pch ++;
      }

      // find
      if(i == len)
         return 0;
      if(psz[i] > des[i])
         return 1;
      return -1;
   }

   //========================================================
   // Name   : _tcsenistr
   // Desc   : similar with _tcsistr with escape process
   // Param  : escape - will be escape character
   // Return :
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   char * _tcsenistr(const scoped_string & str,const char * str,strsize len,i32 escape)
   {
      char * pch = (char *)psz;
      char * prev_escape = nullptr;
      //char * des = (char *)str;
      //i32 i = 0;

      while(pch && *pch)
      {
         if(escape != 0 && *pch == escape && prev_escape == nullptr)
            prev_escape = pch;
         else
         {
            prev_escape = nullptr;
            if(_tcsenicmp(pch,str,len,escape) == 0)
               return (char *)pch;
         }
         pch++;
      }
      return pch;
   }

   //========================================================
   // Name   : _tcseistr
   // Desc   : similar with _tcsistr with escape process
   // Param  : escape - will be escape character
   // Return :
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   char * _tcseistr(const scoped_string & str,const char * str,i32 escape)
   {
      strsize len = strlen(str);
      return _tcsenistr(psz,str,len,escape);
   }

   








} // namespace xml










