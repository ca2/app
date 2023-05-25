#pragma once


#include "acme/primitive/string/_str.h"


namespace xml
{

   class document;

   //========================================================
   // Name   : _tcschrs
   // Desc   : same with ansi_scan
   // Param  :
   // Return :
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   CLASS_DECL_AQUA char * _tcschrs( const ::ansi_character * psz, const ::ansi_character * pszchs );

   //========================================================
   // Name   : _tcsskip
   // Desc   : skip space
   // Param  :
   // Return : skiped string
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   //CLASS_DECL_AQUA char * _tcsskip(::const_ansi_range & rangeXml);

   //========================================================
   // Name   : _tcsechr
   // Desc   : similar with strchr with escape process
   // Param  : escape - will be escape character
   // Return :
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   //CLASS_DECL_AQUA char * _tcsechr(::const_ansi_range & rangeXml, i32 ch, i32 escape );

   //========================================================
   // Name   : _tcselen
   // Desc   : similar with strlen with escape process
   // Param  : escape - will be escape character
   // Return :
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   CLASS_DECL_AQUA i32 _tcselen( i32 escape, char * srt, char * end = nullptr ) ;

   //========================================================
   // Name   : _tcsecpy
   // Desc   : similar with _tcscpy with escape process
   // Param  : escape - will be escape character
   // Return :
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   CLASS_DECL_AQUA void _tcsecpy(char * psz, i32 escape, const char * srt, const char * end = nullptr);
   //CLASS_DECL_AQUA void _tcsecpy2(::ansi_range & rangeOut, char escape, const ::const_ansi_range & range);

   
   ////========================================================
   //// Name   : _tcsenicmp
   //// Desc   : similar with ansi_count_compare_ci with escape process
   //// Param  : escape - will be escape character
   //// Return :
   ////--------------------------------------------------------
   //// Coder    Date                      Desc
   //// bro      2002-10-29
   ////========================================================
   //CLASS_DECL_AQUA i32 _tcsenicmp( const ::ansi_character * psz, const char * str, strsize len, i32 escape );

   ////========================================================
   //// Name   : _tcsenistr
   //// Desc   : similar with _tcsistr with escape process
   //// Param  : escape - will be escape character
   //// Return :
   ////--------------------------------------------------------
   //// Coder    Date                      Desc
   //// bro      2002-10-29
   ////========================================================
   //CLASS_DECL_AQUA char * _tcsenistr( const ::ansi_character * psz, const char * str, strsize len, i32 escape );

   //========================================================
   // Name   : _tcseistr
   // Desc   : similar with _tcsistr with escape process
   // Param  : escape - will be escape character
   // Return :
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   CLASS_DECL_AQUA char * _tcseistr( const ::ansi_character * psz, const char * str, i32 escape );

   //========================================================
   // Name   : _SetString
   // Desc   : put string of (psz~end) on ps string
   // Param  : trim - will be trim?
   // Return :
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   inline void _SetString(::const_ansi_range range, string* ps, bool trim, i32 escape);
   inline void _SetString(::const_ansi_range range, string* ps,bool trim); // no escape
   inline void _SetString(::const_ansi_range range, string* ps); // no trim, no escape




} // namespace xml



namespace xml
{


   void _trim(::const_ansi_range & range)
   {

      while (range.has_char() && character_isspace(*range.m_begin))
      {

         range.m_begin++;

      }

      while (range.has_char() && character_isspace(*(range.m_end - 1)))
      {

         range.m_begin--;

      }

   }


   void _defer_escape(string * ps, ::const_ansi_range & range, i32 escape)
   {

      if (escape)
      {

         auto rangeOut = ps->get_range_buffer(range.size());

         rangeOut.escape_copy(escape, range);

         ps->release_range_buffer(rangeOut);

      }
      else
      {

         ps->assign_range(range);

      }

   }

   //========================================================
   // Name   : _SetString
   // Desc   : put string of (psz~end) on ps string
   // Param  : trim - will be trim?
   // Return :
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   inline void _SetString(::const_ansi_range range,string* ps,bool trim,i32 escape)
   {

      if(trim)
      {

         _trim(range);

      }

      if(range.is_empty())
      {

         return;

      }

      _defer_escape(ps, range, escape);

   }


   inline void _SetString(::const_ansi_range range,string* ps,bool trim)
   {

      if(trim)
      {

         _trim(range);

      }

      ps->assign_range(range);

   }


   inline void _SetString(::const_ansi_range range,string* ps)
   {

      ps->assign_range(range);

   }


} // namespace xml







namespace xml
{

//   inline i32 ch_ansi_char_isspace(uchar uch)
//   {
//      return uch == ' ' || uch == '\t' || uch == '\r' || uch == '\n';
//   }


   //========================================================
   // Name   : _tcschrs
   // Desc   : same with ansi_scan
   // Param  :
   // Return :
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   inline char * _tcschrs(const ::ansi_character * psz,const ::ansi_character * pszchs)
   {
      while(*psz)
      {
         if(strchr(pszchs,*psz))
            return (char *)psz;
         psz++;
      }
      return nullptr;
   }

   //========================================================
   // Name   : _tcsskip
   // Desc   : skip space
   // Param  :
   // Return : skiped string
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   //inline char * _tcsskip(const ::ansi_character * psz)
   //{

   //   while(ansi_char_isspace((uchar)*psz)) psz++;

   //   return (char *)psz;

   //}

} // namespace xml



namespace xml
{

   //// ansi_scan(xml," />\t\r\n");

   //inline bool is_end_open_tag_name_char(uchar ch)
   //{
   //   return ch == ' ' || ch == '/' || ch == '>' || ch == '\t' || ch == '\r' || ch == '\n' || ch == '\0';
   //}

   //inline const char * end_open_tag_name(const ::ansi_character * psz)
   //{
   //   while(!is_end_open_tag_name_char(*psz))
   //   {
   //      psz++;
   //   }
   //   return psz;
   //}


} // namespace xml



