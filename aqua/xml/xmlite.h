#pragma once


#include "acme/prototype/string/_str.h"


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
   CLASS_DECL_AQUA char_pointer _tcschrs( const_char_pointer psz, const_char_pointer pszchs );

   //========================================================
   // Name   : _tcsskip
   // Desc   : skip space
   // Param  :
   // Return : skiped string
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   //CLASS_DECL_AQUA char_pointer _tcsskip(::const_ansi_range & rangeXml);

   //========================================================
   // Name   : _tcsechr
   // Desc   : similar with strchr with escape process
   // Param  : escape - will be escape character
   // Return :
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   //CLASS_DECL_AQUA char_pointer _tcsechr(::const_ansi_range & rangeXml, ::i32 ch, ::i32 escape );

   //========================================================
   // Name   : _tcselen
   // Desc   : similar with strlen with escape process
   // Param  : escape - will be escape character
   // Return :
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   CLASS_DECL_AQUA ::i32 _tcselen( ::i32 escape, char_pointer srt, char_pointer end = nullptr ) ;

   //========================================================
   // Name   : _tcsecpy
   // Desc   : similar with _tcscpy with escape process
   // Param  : escape - will be escape character
   // Return :
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   CLASS_DECL_AQUA void _tcsecpy(char_pointer psz, ::i32 escape, const_char_pointer srt, const_char_pointer end = nullptr);
   //CLASS_DECL_AQUA void _tcsecpy2(::ansi_range & rangeOut, ::i8 escape, const ::const_ansi_range & range);

   
   ////========================================================
   //// Name   : _tcsenicmp
   //// Desc   : similar with case_insensitive_ansi_count_compare with escape process
   //// Param  : escape - will be escape character
   //// Return :
   ////--------------------------------------------------------
   //// Coder    Date                      Desc
   //// bro      2002-10-29
   ////========================================================
   //CLASS_DECL_AQUA ::i32 _tcsenicmp( const_char_pointer psz, const_char_pointer str, character_count len, ::i32 escape );

   ////========================================================
   //// Name   : _tcsenistr
   //// Desc   : similar with _tcsistr with escape process
   //// Param  : escape - will be escape character
   //// Return :
   ////--------------------------------------------------------
   //// Coder    Date                      Desc
   //// bro      2002-10-29
   ////========================================================
   //CLASS_DECL_AQUA char_pointer _tcsenistr( const_char_pointer psz, const_char_pointer str, character_count len, ::i32 escape );

   //========================================================
   // Name   : _tcseistr
   // Desc   : similar with _tcsistr with escape process
   // Param  : escape - will be escape character
   // Return :
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   CLASS_DECL_AQUA char_pointer _tcseistr( const_char_pointer psz, const_char_pointer str, ::i32 escape );

   //========================================================
   // Name   : _SetString
   // Desc   : put string of (scopedstr~end) on ps string
   // Param  : trim - will be trim?
   // Return :
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   inline void _SetString(::const_ansi_range range, string* ps, bool trim, ::i32 escape);
   inline void _SetString(::const_ansi_range range, string* ps,bool trim); // no escape
   inline void _SetString(::const_ansi_range range, string* ps); // no trim, no escape




} // namespace xml



namespace xml
{


   void _trim(::const_ansi_range & range)
   {

      while (range.has_character() && character_isspace(*range.m_begin))
      {

         range.m_begin++;

      }

      while (range.has_character() && character_isspace(*(range.m_end - 1)))
      {

         range.m_begin--;

      }

   }


   void _defer_escape(string * ps, ::const_ansi_range & range, ::i32 escape)
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
   // Desc   : put string of (scopedstr~end) on ps string
   // Param  : trim - will be trim?
   // Return :
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   inline void _SetString(::const_ansi_range range,string* ps,bool trim,::i32 escape)
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

//   inline ::i32 ch_ansi_char_isspace(uchar uch)
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
   inline char_pointer _tcschrs(const_char_pointer psz,const_char_pointer pszchs)
   {
      while(*psz)
      {
         if(ansi_chr(pszchs,*psz))
            return (char_pointer )psz;
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
   //inline char_pointer _tcsskip(const_char_pointer psz)
   //{

   //   while(ansi_char_isspace((uchar)*psz)) psz++;

   //   return (char_pointer )psz;

   //}

} // namespace xml



namespace xml
{

   //// ansi_scan(xml," />\t\r\n");

   //inline bool is_end_open_tag_name_char(uchar ch)
   //{
   //   return ch == ' ' || ch == '/' || ch == '>' || ch == '\t' || ch == '\r' || ch == '\n' || ch == '\0';
   //}

   //inline const_char_pointer end_open_tag_name(const_char_pointer psz)
   //{
   //   while(!is_end_open_tag_name_char(*psz))
   //   {
   //      psz++;
   //   }
   //   return psz;
   //}


} // namespace xml



