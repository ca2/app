#pragma once


#include "string_base.inl"


template < >
inline void std_string_assign(stdstring < wstring > & t, const bstring * pbstr)
{
   t = ::str::ch().international::utf8_to_unicode(string((const char *)pbstr->get_data(), min(pbstr->get_length(), natural(strlen_s_dup((const char *)pbstr->get_data(), pbstr->get_length())))));
}


template < >
inline void std_string_assign(string_base & t, const bstring * pbstr)
{
   t = string((const char *)pbstr->get_data(), min(pbstr->get_length(), natural(strlen_s_dup((const char *)pbstr->get_data(), pbstr->get_length()))));
}




template < >
inline void std_string_assign(stdstring < memory > & t, const ::scoped_string & scopedstr)
{
   t.assign(psz);
}

template < >
inline void std_string_assign(stdstring < memory > & t, const unichar * psz)
{
   t.assign(::str::ch().international::unicode_to_utf8(psz));
}

template < >
inline void std_string_bassign(stdstring < memory > & t, const ::u8 * psz, strsize nsize)
{
   t.assign(string((const char *)psz, min(nsize, strlen_s_dup((const char *)psz, nsize))));
}

template < >
inline void std_string_assign(stdstring < memory > & t, const string * pstr)
{
   t = (const char *)*pstr;
}

template < >
inline void std_string_assign(stdstring < memory > & t, const wstring * pwstr)
{
   t = (const char *) ::str::ch().international::unicode_to_utf8(*pwstr);
}

template < >
inline void std_string_assign(stdstring < memory > & t, const bstring * pbstr)
{
   t = *pbstr;
}







