#pragma once


inline i32 parse_unicode(const ansichar * pszChar) { return ::str::ch().parse_unicode(pszChar); }
inline i32 __uni_index(const ansichar * pszChar) { return ::str::ch().uni_index(pszChar); }
inline i32 __uni_len(const ansichar * pszChar) { return ::str::ch().uni_len(pszChar); }
inline i32 __uni_index_len(const ansichar * pszChar, i32 & len) { return ::str::ch().uni_index_len(pszChar, len); }


inline i32 parse_unicode(const wd16char * pszChar) { return ::str::ch().parse_unicode(pszChar); }
inline i32 __uni_index(const wd16char * pszChar) { return ::str::ch().uni_index(pszChar); }
inline i32 __uni_len(const wd16char * pszChar) { return ::str::ch().uni_len(pszChar); }
inline i32 __uni_index_len(const wd16char * pszChar, i32 & len) { return ::str::ch().uni_index_len(pszChar, len); }


inline i32 parse_unicode(const wd32char * pszChar) { return ::str::ch().parse_unicode(pszChar); }
inline i32 __uni_index(const wd32char * pszChar) { return ::str::ch().uni_index(pszChar); }
inline i32 __uni_len(const wd32char * pszChar) { return ::str::ch().uni_len(pszChar); }
inline i32 __uni_index_len(const wd32char * pszChar, i32 & len) { return ::str::ch().uni_index_len(pszChar, len); }


template < typename CHAR_STRING >
inline bool is_trimmed_string_empty(CHAR_STRING p)
{

   if(::is_null(p))
   {

      return true;

   }

   while(*p)
   {

      if(!::str::ch().is_whitespace(p))
      {

         return false;

      }

      ::str::ch().inc(p);

   }

   return true;

}


