#pragma once


#define const_char_trigger const ansichar *



namespace str
{


   template < typename TYPE_CHAR >
   class single_char
   {
   public:

      TYPE_CHAR cha[8];

   };


   template < >
   class single_char < ansichar >
   {
   public:

      ansichar cha[6];

   };


   template < >
   class single_char < wd16char >
   {
   public:

      wd16char cha[2];

   };


   template < >
   class single_char < wd32char >
   {
   public:

      wd32char cha[1];

   };


   template < typename TYPE_TARGET, typename TYPE_SOURCE >
   inline strsize utf_to_utf_length(const TYPE_TARGET *, const TYPE_SOURCE * psource, strsize srclen);

   template <  >
   inline strsize utf_to_utf_length(const ansichar *, const ansichar * psource, strsize srclen);

   template <  >
   inline strsize utf_to_utf_length(const wd16char *, const wd16char * psource, strsize srclen);

   template <  >
   inline strsize utf_to_utf_length(const wd16char *, const wd32char * psource, strsize srclen);

   template <  >
   inline strsize utf_to_utf_length(const wd32char *, const wd32char * psource, strsize srclen);

   template <  >
   inline strsize utf_to_utf_length(const wd32char *, const wd16char * psource, strsize srclen);

   template <  >
   inline strsize utf_to_utf_length(const ansichar *, const wd16char * psource, strsize srclen);

   template <  >
   inline strsize utf_to_utf_length(const ansichar *, const wd32char * psource, strsize srclen);

   template <  >
   inline strsize utf_to_utf_length(const wd16char *, const ansichar * psource, strsize srclen);

   template <  >
   inline strsize utf_to_utf_length(const wd32char *, const ansichar * psource, strsize srclen);

   template < typename TYPE_TARGET, typename TYPE_SOURCE >
   inline void utf_to_utf(TYPE_TARGET * ptarget, const TYPE_SOURCE * psource, strsize srclen);

   template <  >
   inline void utf_to_utf(ansichar * ptarget, const ansichar * psource, strsize srclen);

   template <  >
   inline void utf_to_utf(wd16char * ptarget, const wd16char * psource, strsize srclen);

   template <  >
   inline void utf_to_utf(wd16char * ptarget, const wd32char * psource, strsize srclen);

   template <  >
   inline void utf_to_utf(wd32char * ptarget, const wd32char * psource, strsize srclen);

   template <  >
   inline void utf_to_utf(wd32char * ptarget, const wd16char * psource, strsize srclen);

   template <  >
   inline void utf_to_utf(ansichar * ptarget, const wd16char * psource, strsize srclen);

   template <  >
   inline void utf_to_utf(ansichar * ptarget, const wd32char * psource, strsize srclen);

   template <  >
   inline void utf_to_utf(wd16char * ptarget, const ansichar * psource, strsize srclen);

   template <  >
   inline void utf_to_utf(wd32char * ptarget, const ansichar * psource, strsize srclen);

   template < typename TYPE_TARGET, typename TYPE_SOURCE >
   inline strsize utf_to_utf_length(const TYPE_TARGET *, const TYPE_SOURCE * psource);

   template <  >
   inline strsize utf_to_utf_length(const ansichar *, const ansichar * psource);

   template <  >
   inline strsize utf_to_utf_length(const wd16char *, const wd16char * psource);

   template <  >
   inline strsize utf_to_utf_length(const wd16char *, const wd32char * psource);

   template <  >
   inline strsize utf_to_utf_length(const wd16char *, const wd32char * psource);

   template <  >
   inline strsize utf_to_utf_length(const wd32char *, const wd32char * psource);

   template <  >
   inline strsize utf_to_utf_length(const wd32char *, const wd16char * psource);

   template <  >
   inline strsize utf_to_utf_length(const wd32char *, const wd16char * psource);

   template <  >
   inline strsize utf_to_utf_length(const ansichar *, const wd16char * psource);

   template <  >
   inline strsize utf_to_utf_length(const ansichar *, const wd32char * psource);

   template <  >
   inline strsize utf_to_utf_length(const wd16char *, const ansichar * psource);

   template <  >
   inline strsize utf_to_utf_length(const wd32char *, const ansichar * psource);

   template < typename TYPE_TARGET, typename TYPE_SOURCE >
   inline void utf_to_utf(TYPE_TARGET * ptarget, const TYPE_SOURCE * psource);

   template <  >
   inline void utf_to_utf(ansichar * ptarget, const ansichar * psource);

   template <  >
   inline void utf_to_utf(wd16char * ptarget, const wd16char * psource);

   template <  >
   inline void utf_to_utf(wd16char * ptarget, const wd32char * psource);

   template <  >
   inline void utf_to_utf(wd32char * ptarget, const wd32char * psource);

   template <  >
   inline void utf_to_utf(wd32char * ptarget, const wd16char * psource);

   template <  >
   inline void utf_to_utf(ansichar * ptarget, const wd16char * psource);

   template <  >
   inline void utf_to_utf(ansichar * ptarget, const wd32char * psource);

   template <  >
   inline void utf_to_utf(wd16char * ptarget, const ansichar * psource);

   template <  >
   inline void utf_to_utf(wd32char * ptarget, const ansichar * psource);



   inline i32 uni_index(const ansichar *& pszChar, strsize * psrclen);
   inline i32 uni_index(const wd16char *& pszChar, strsize * psrclen);
   inline i32 uni_index(const wd32char *& pszChar, strsize * psrclen);


   inline const ansichar * windows_bbqbunc(const ansistring &);
   inline const ansichar * windows_bbqb(const ansistring &);
   inline const ansichar * windows_bb(const ansistring &);


   inline const widechar * windows_bbqbunc(const widestring &);
   inline const widechar * windows_bbqb(const widestring &);
   inline const widechar * windows_bb(const widestring &);


   inline const ansichar * unichar_inc(const ansichar * psz);
   inline const wd16char * unichar_inc(const wd16char * psz);
   inline const wd32char * unichar_inc(const wd32char * psz);


   inline strsize unichar_count(const ansichar * pstr);
   inline strsize unichar_count(const wd16char * pstr);
   inline strsize unichar_count(const wd32char* pstr);


   inline strsize copy_string_len(wd16char *, const ansichar * pszSrc, strsize srclen);
   inline strsize copy_string_len(wd32char *, const ansichar * pszSrc, strsize srclen);
   inline strsize copy_string_len(ansichar *, const wd16char * pszSrc, strsize srclen);
   inline strsize copy_string_len(ansichar *, const wd32char * pszSrc, strsize srclen);


   inline void copy_string(wd16char * pszDst, const ansichar * pszSrc, strsize srclen);
   inline void copy_string(wd32char * pszDst, const ansichar * pszSrc, strsize srclen);
   inline void copy_string(ansichar * pszDst, const wd16char * pszSrc, strsize srclen);
   inline void copy_string(ansichar * pszDst, const wd32char * pszSrc, strsize srclen);


   template < typename TYPE_CHAR >
   inline string_base < TYPE_CHAR > & assign(string_base < TYPE_CHAR > & strDst, const string_base < TYPE_CHAR > & strSrc);


   template < typename TYPE_CHAR1, typename TYPE_CHAR2 >
   inline string_base < TYPE_CHAR1 > & assign(string_base < TYPE_CHAR1 > & strDst, const TYPE_CHAR2 * pszSrc, strsize len);


   template < typename TYPE_CHAR1, typename TYPE_CHAR2 >
   inline string_base < TYPE_CHAR1 > & assign(string_base < TYPE_CHAR1 > & strDst, const TYPE_CHAR2 * pszSrc);


   template < typename TYPE_CHAR >
   inline string_base < TYPE_CHAR > & assign(string_base < TYPE_CHAR > & strDst, const TYPE_CHAR * pszSrc);


   inline wd16string & assign(wd16string & wstrDst, const ansistring & strSrc);

   inline wd32string & assign(wd32string & wstrDst, const ansistring& strSrc);

   inline ansistring & assign(ansistring & strDst, const wd16string & wstrSrc);

   inline ansistring & assign(ansistring & strDst, const wd32string& wstrSrc);

   inline ansistring & assign(ansistring & ansistrDst, const atom & atom);

   inline wd16string & assign(wd16string & widestrDst, const atom & atom);

   inline wd32string & assign(wd32string & widestrDst, const atom & atom);

   inline ansistring & assign(ansistring & ansistrDst, ansichar ansich);

   inline wd16string & assign(wd16string & widestrDst, ansichar ansich);

   inline wd32string & assign(wd32string & widestrDst, ansichar ansich);

   inline ansistring & assign(ansistring & ansistrDst, wd16char wd16ch);

   inline wd16string & assign(wd16string & widestrDst, wd16char wd16ch);

   inline wd32string & assign(wd32string & widestrDst, wd16char wd16ch);

   inline ansistring & assign(ansistring & ansistrDst, wd32char wd32ch);

   inline wd16string & assign(wd16string & widestrDst, wd32char wd32ch);

   inline wd32string & assign(wd32string & widestrDst, wd32char wd32ch);

   inline ansistring & assign(ansistring & ansistrDst, const ::payload & payload);

   inline wd16string & assign(wd16string & widestrDst, const ::payload & payload);

   inline wd32string & assign(wd32string & widestrDst, const ::payload & payload);

   inline ansistring & assign(ansistring & ansistrDst, const property & property);

   inline wd16string & assign(wd16string & widestrDst, const property & property);

   inline wd32string & assign(wd32string & widestrDst, const property & property);

   inline ansistring & assign(ansistring & ansistrDst, const wd16char * pwidesz);

   inline ansistring & assign(ansistring & ansistrDst, const wd32char* pwidesz);

   inline wd16string & assign(wd16string & widestrDst, const ansichar * pansisz);

   inline wd16string & assign(wd16string & widestrDst, const wd16char* pansisz);

   inline wd16string & assign(wd16string & widestrDst, const wd32char* pansisz);

   inline wd32string & assign(wd32string & widestrDst, const ansichar* pansisz);

   inline wd32string & assign(wd32string & widestrDst, const wd16char* pansisz);

   inline wd32string & assign(wd32string & widestrDst, const wd32char* pansisz);


   inline ansistring & assign(ansistring & ansistrDst, const ::type & type);

   inline widestring & assign(widestring & widestrDst, const ::type & type);


} // namespace str



