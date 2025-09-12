// Created from _unicode by camilo on 2022-11-07 09:21 <3ThomasBorregaardSorensen!!
#pragma once


//CLASS_DECL_ACME const_char_pointer unicode_next(const_char_pointer psz);
//CLASS_DECL_ACME const ::wd16_character *unicode_next(const ::wd16_character *psz);
//CLASS_DECL_ACME const ::wd32_character *unicode_next(const ::wd32_character *psz);


//CLASS_DECL_ACME const_char_pointer unicode_prior(const_char_pointer psz, const_char_pointer pszBeg);
//CLASS_DECL_ACME const ::wd16_character * unicode_prior(const ::wd16_character *psz, const ::wd16_character *pszBeg);
//CLASS_DECL_ACME const ::wd32_character * unicode_prior(const ::wd32_character *psz, const ::wd32_character *pszBeg);


// 1 char char
CLASS_DECL_ACME character_count utf_to_utf_length1(const ::ansi_character*, const ::ansi_character* psource, character_count srclen);

// 2 wd16 wd16
CLASS_DECL_ACME character_count utf_to_utf_length1(const ::wd16_character*, const ::wd16_character* psource, character_count srclen);

// 3 wd32 wd32
CLASS_DECL_ACME character_count utf_to_utf_length1(const ::wd32_character*, const ::wd32_character* psource, character_count srclen);

// 4 wd16 wd32
CLASS_DECL_ACME character_count utf_to_utf_length1(const ::wd16_character *, const ::wd32_character * psource, character_count srclen);

// 5 wd32 wd16
CLASS_DECL_ACME character_count utf_to_utf_length1(const ::wd32_character *, const ::wd16_character * psource, character_count srclen);

// 6 char wd16
CLASS_DECL_ACME character_count utf_to_utf_length1(const_char_pointer ,const ::wd16_character * psource, character_count srclen);

// 7 wd16 char
CLASS_DECL_ACME character_count utf_to_utf_length1(const ::wd16_character *, const_char_pointer psource, character_count srclen);

// 8 char wd32
CLASS_DECL_ACME character_count utf_to_utf_length1(const_char_pointer ,const ::wd32_character * psource, character_count srclen);

// 9 wd32 char
CLASS_DECL_ACME character_count utf_to_utf_length1(const ::wd32_character *, const_char_pointer psource, character_count srclen);

// 1 char char
CLASS_DECL_ACME character_count utf_to_utf_length2(const ::ansi_character *, const ::ansi_character *psource,
                                                   character_count & srclen);

// 2 wd16 wd16
CLASS_DECL_ACME character_count utf_to_utf_length2(const ::wd16_character *, const ::wd16_character *psource,
                                                  character_count & srclen);

// 3 wd32 wd32
CLASS_DECL_ACME character_count utf_to_utf_length2(const ::wd32_character *, const ::wd32_character *psource,
                                                  character_count & srclen);

// 4 wd16 wd32
CLASS_DECL_ACME character_count utf_to_utf_length2(const ::wd16_character *, const ::wd32_character *psource,
                                                  character_count & srclen);

// 5 wd32 wd16
CLASS_DECL_ACME character_count utf_to_utf_length2(const ::wd32_character *, const ::wd16_character *psource,
                                                  character_count & srclen);

// 6 char wd16
CLASS_DECL_ACME character_count utf_to_utf_length2(const_char_pointer, const ::wd16_character *psource,
                                                  character_count & srclen);

// 7 wd16 char
CLASS_DECL_ACME character_count utf_to_utf_length2(const ::wd16_character *, const_char_pointer psource,
                                                  character_count & srclen);

// 8 char wd32
CLASS_DECL_ACME character_count utf_to_utf_length2(const_char_pointer, const ::wd32_character *psource,
                                                  character_count & srclen);

// 9 wd32 char
CLASS_DECL_ACME character_count utf_to_utf_length2(const ::wd32_character *, const_char_pointer psource,
                                                  character_count & srclen);


CLASS_DECL_ACME character_count utf_to_utf_length(const_char_pointer ,const_char_pointer psource);


CLASS_DECL_ACME character_count utf_to_utf_length(const ::wd16_character *, const ::wd16_character * psource);


CLASS_DECL_ACME character_count utf_to_utf_length(const ::wd16_character *, const ::wd32_character * psource);


CLASS_DECL_ACME character_count utf_to_utf_length(const ::wd32_character *, const ::wd32_character * psource);


CLASS_DECL_ACME character_count utf_to_utf_length(const ::wd32_character *, const ::wd16_character * psource);


CLASS_DECL_ACME character_count utf_to_utf_length(const_char_pointer ,const ::wd16_character * psource);


CLASS_DECL_ACME character_count utf_to_utf_length(const_char_pointer ,const ::wd32_character * psource);


CLASS_DECL_ACME character_count utf_to_utf_length(const ::wd16_character *, const_char_pointer psource);


CLASS_DECL_ACME character_count utf_to_utf_length(const ::wd32_character *, const_char_pointer psource);


CLASS_DECL_ACME void utf_to_utf(::ansi_character * ptarget, const_char_pointer psource, character_count srclen);


CLASS_DECL_ACME void utf_to_utf(::wd16_character * ptarget, const ::wd16_character * psource, character_count srclen);


CLASS_DECL_ACME void utf_to_utf(::wd16_character * ptarget, const ::wd32_character * psource, character_count srclen);


CLASS_DECL_ACME void utf_to_utf(::wd32_character * ptarget, const ::wd32_character * psource, character_count srclen);


CLASS_DECL_ACME void utf_to_utf(::wd32_character * ptarget, const ::wd16_character * psource, character_count srclen);


CLASS_DECL_ACME void utf_to_utf(::ansi_character * ptarget, const ::wd16_character * psource, character_count srclen);


CLASS_DECL_ACME void utf_to_utf(::ansi_character * ptarget, const ::wd32_character * psource, character_count srclen);


CLASS_DECL_ACME void utf_to_utf(::wd16_character * ptarget, const_char_pointer psource, character_count srclen);


CLASS_DECL_ACME void utf_to_utf(::wd32_character * ptarget, const_char_pointer psource, character_count srclen);


CLASS_DECL_ACME void utf_to_utf(::ansi_character * ptarget, const_char_pointer psource);


CLASS_DECL_ACME void utf_to_utf(::wd16_character * ptarget, const ::wd16_character * psource);


CLASS_DECL_ACME void utf_to_utf(::wd32_character * ptarget, const ::wd16_character * psource);


CLASS_DECL_ACME void utf_to_utf(::wd32_character * ptarget, const ::wd32_character * psource);


CLASS_DECL_ACME void utf_to_utf(::wd16_character * ptarget, const ::wd32_character * psource);


CLASS_DECL_ACME void utf_to_utf(::ansi_character * ptarget, const ::wd16_character * psource);


CLASS_DECL_ACME void utf_to_utf(::ansi_character * ptarget, const ::wd32_character * psource);


CLASS_DECL_ACME void utf_to_utf(::wd16_character * ptarget, const_char_pointer psource);


CLASS_DECL_ACME void utf_to_utf(::wd32_character * ptarget, const_char_pointer psource);



