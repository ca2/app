#pragma once


//inline i32 parse_unicode(const ansichar * pszChar) { return unicode_parse_unicode(pszChar); }
//inline i32 __unicode_index(const ansichar * pszChar) { return unicode_unicode_index(pszChar); }
//inline i32 __unicode_len(const ansichar * pszChar) { return unicode_unicode_len(pszChar); }
//inline i32 __unicode_index_len(const ansichar * pszChar, i32 & len) { return unicode_unicode_index_len(pszChar, len); }
//
//
//inline i32 parse_unicode(const wd16char * pszChar) { return unicode_parse_unicode(pszChar); }
//inline i32 __unicode_index(const wd16char * pszChar) { return unicode_unicode_index(pszChar); }
//inline i32 __unicode_len(const wd16char * pszChar) { return unicode_unicode_len(pszChar); }
//inline i32 __unicode_index_len(const wd16char * pszChar, i32 & len) { return unicode_unicode_index_len(pszChar, len); }
//
//
//inline i32 parse_unicode(const wd32char * pszChar) { return unicode_parse_unicode(pszChar); }
//inline i32 __unicode_index(const wd32char * pszChar) { return unicode_unicode_index(pszChar); }
//inline i32 __unicode_len(const wd32char * pszChar) { return unicode_unicode_len(pszChar); }
//inline i32 __unicode_index_len(const wd32char * pszChar, i32 & len) { return unicode_unicode_index_len(pszChar, len); }


template < typename CHAR_STRING >
inline bool is_trimmed_string_empty(CHAR_STRING p)
{

   if(::is_null(p))
   {

      return true;

   }

   while(*p)
   {

      if(!unicode_is_whitespace(p))
      {

         return false;

      }

      unicode_increment(p);

   }

   return true;

}


