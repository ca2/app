/*++

Copyright (c) Microsoft Corporation  All rights reserved.

Module Name:

    winnls.h

Abstract:

    Procedure declarations, constant definitions, and macros for the
    NLS component.

--*/


#ifndef _WINNLS_
#define _WINNLS_


#ifdef __cplusplus
extern "C" {
#endif



#ifndef NONLS

#ifdef _MAC
#include <macwin32.h>
#endif

#if !defined(_NORMALIZE_)
#define WINNORMALIZEAPI DECLSPEC_IMPORT
#else
#define WINNORMALIZEAPI
#endif



////////////////////////////////////////////////////////////////////////////
//
//  Constants
//
//  Define all constants for the NLS component here.
//
////////////////////////////////////////////////////////////////////////////

//
//  String Length Maximums.
//
#define MAX_LEADBYTES             12          // 5 ranges, 2 bytes ea., 0 term.
#define MAX_DEFAULTCHAR           2           // single or double byte

//
//  Surrogate pairs
//
//  Conversion examples:
//
//  A) The first character in the Surrogate range (D800, DC00) as UTF-32:
//
//  1.  D800: binary 1101100000000000  (lower ten bits: 0000000000)
//  2.  DC00: binary 1101110000000000  (lower ten bits: 0000000000)
//  3.  Concatenate 0000000000+0000000000 = 0x0000
//  4.  Add 0x10000
//
//  Result: U+10000. This is correct, since the first character in the Supplementary character
//  range immediately follows the last code point in the 16-bit UTF-16 range (U+FFFF)
//
//  B) A UTF-32 code point such as U+2040A (this a CJK character in CJK Extension B), and wish
//  to convert it in UTF-16:
//
//  1.  Subtract 0x10000 - Result: 0x1040A
//  2.  Split into two ten-bit pieces: 0001000001 0000001010
//  3.  Add 1101100000000000 (0xD800) to the high 10 bits piece (0001000001) - Result: 1101100001000001 (0xD841)
//  4.  Add 1101110000000000 (0xDC00) to the low 10 bits piece (0000001010) - Result: 1101110000001010 (0xDC0A)
//
//  RESULT: The surrogate pair: U+D841, U+DC0A
//
//  Special Unicode code point values, for use with UTF-16 surrogate pairs.
//
#define HIGH_SURROGATE_START  0xd800
#define HIGH_SURROGATE_END    0xdbff
#define LOW_SURROGATE_START   0xdc00
#define LOW_SURROGATE_END     0xdfff


//
//  MBCS and Unicode Translation Flags.
//
#define MB_PRECOMPOSED            0x00000001  // use precomposed chars
#define MB_COMPOSITE              0x00000002  // use reference chars
#define MB_USEGLYPHCHARS          0x00000004  // use glyph chars, not ctrl chars
#define MB_ERR_INVALID_CHARS      0x00000008  // error for invalid chars

#define WC_COMPOSITECHECK         0x00000200  // convert reference to precomposed
#define WC_DISCARDNS              0x00000010  // discard non-spacing chars
#define WC_SEPCHARS               0x00000020  // generate separate chars
#define WC_DEFAULTCHAR            0x00000040  // replace w/ default char
#if (WINVER >= 0x0600)
#define WC_ERR_INVALID_CHARS      0x00000080  // error for invalid chars
#endif

#if(WINVER >= 0x0500)
#define WC_NO_BEST_FIT_CHARS      0x00000400  // do not use best fit chars
#endif /* WINVER >= 0x0500 */


//
//  Character Type Flags.
//
#define CT_CTYPE1                 0x00000001  // ctype 1 information
#define CT_CTYPE2                 0x00000002  // ctype 2 information
#define CT_CTYPE3                 0x00000004  // ctype 3 information

//
//  CType 1 Flag Bits.
//
#define C1_UPPER                  0x0001      // upper case
#define C1_LOWER                  0x0002      // lower case
#define C1_DIGIT                  0x0004      // decimal digits
#define C1_SPACE                  0x0008      // spacing characters
#define C1_PUNCT                  0x0010      // punctuation characters
#define C1_CNTRL                  0x0020      // control characters
#define C1_BLANK                  0x0040      // blank characters
#define C1_XDIGIT                 0x0080      // other digits
#define C1_ALPHA                  0x0100      // any linguistic character
#define C1_DEFINED                0x0200      // defined character

//
//  CType 2 Flag Bits.
//
#define C2_LEFTTORIGHT            0x0001      // left to right
#define C2_RIGHTTOLEFT            0x0002      // right to left

#define C2_EUROPENUMBER           0x0003      // European number, digit
#define C2_EUROPESEPARATOR        0x0004      // European numeric separator
#define C2_EUROPETERMINATOR       0x0005      // European numeric terminator
#define C2_ARABICNUMBER           0x0006      // Arabic number
#define C2_COMMONSEPARATOR        0x0007      // common numeric separator

#define C2_BLOCKSEPARATOR         0x0008      // block separator
#define C2_SEGMENTSEPARATOR       0x0009      // segment separator
#define C2_WHITESPACE             0x000A      // white space
#define C2_OTHERNEUTRAL           0x000B      // other neutrals

#define C2_NOTAPPLICABLE          0x0000      // no implicit directionality

//
//  CType 3 Flag Bits.
//
#define C3_NONSPACING             0x0001      // nonspacing character
#define C3_DIACRITIC              0x0002      // diacritic mark
#define C3_VOWELMARK              0x0004      // vowel mark
#define C3_SYMBOL                 0x0008      // symbols

#define C3_KATAKANA               0x0010      // katakana character
#define C3_HIRAGANA               0x0020      // hiragana character
#define C3_HALFWIDTH              0x0040      // half width character
#define C3_FULLWIDTH              0x0080      // full width character
#define C3_IDEOGRAPH              0x0100      // ideographic character
#define C3_KASHIDA                0x0200      // Arabic kashida character
#define C3_LEXICAL                0x0400      // lexical character
#define C3_HIGHSURROGATE          0x0800      // high surrogate code unit
#define C3_LOWSURROGATE           0x1000      // low surrogate code unit

#define C3_ALPHA                  0x8000      // any linguistic char (C1_ALPHA)

#define C3_NOTAPPLICABLE          0x0000      // ctype 3 is not applicable


//
//  String Flags.
//
#define NORM_IGNORECASE           0x00000001  // ignore case
#define NORM_IGNORENONSPACE       0x00000002  // ignore nonspacing chars
#define NORM_IGNORESYMBOLS        0x00000004  // ignore symbols

#define LINGUISTIC_IGNORECASE     0x00000010  // linguistically appropriate 'ignore case'
#define LINGUISTIC_IGNOREDIACRITIC 0x00000020  // linguistically appropriate 'ignore nonspace'

#define NORM_IGNOREKANATYPE       0x00010000  // ignore kanatype
#define NORM_IGNOREWIDTH          0x00020000  // ignore width
#define NORM_LINGUISTIC_CASING    0x08000000  // use linguistic rules for casing


//
//  Locale Independent Mapping Flags.
//
#define MAP_FOLDCZONE             0x00000010  // fold compatibility zone chars
#define MAP_PRECOMPOSED           0x00000020  // convert to precomposed chars
#define MAP_COMPOSITE             0x00000040  // convert to reference chars
#define MAP_FOLDDIGITS            0x00000080  // all digits to ASCII 0-9

#if(WINVER >= 0x0500)
#define MAP_EXPAND_LIGATURES      0x00002000  // expand all ligatures
#endif /* WINVER >= 0x0500 */

//
//  Locale Dependent Mapping Flags.
//
#define LCMAP_LOWERCASE           0x00000100  // lower case letters
#define LCMAP_UPPERCASE           0x00000200  // UPPER CASE LETTERS
#if (WINVER >= _WIN32_WINNT_WIN7)
#define LCMAP_TITLECASE           0x00000300  // Title Case Letters
#endif // (WINVER >= _WIN32_WINNT_WIN7)

#define LCMAP_SORTKEY             0x00000400  // WC sort key (normalize)
#define LCMAP_BYTEREV             0x00000800  // byte reversal

#define LCMAP_HIRAGANA            0x00100000  // map katakana to hiragana
#define LCMAP_KATAKANA            0x00200000  // map hiragana to katakana
#define LCMAP_HALFWIDTH           0x00400000  // map double byte to single byte
#define LCMAP_FULLWIDTH           0x00800000  // map single byte to double byte

#define LCMAP_LINGUISTIC_CASING   0x01000000  // use linguistic rules for casing

#define LCMAP_SIMPLIFIED_CHINESE  0x02000000  // map traditional chinese to simplified chinese
#define LCMAP_TRADITIONAL_CHINESE 0x04000000  // map simplified chinese to traditional chinese


//
//  Search Flags
//
#define FIND_STARTSWITH           0x00100000  // see if value is at the beginning of source
#define FIND_ENDSWITH             0x00200000  // see if value is at the end of source
#define FIND_FROMSTART            0x00400000  // look for value in source, starting at the beginning
#define FIND_FROMEND              0x00800000  // look for value in source, starting at the end


//
//  Language Group Enumeration Flags.
//
#define LGRPID_INSTALLED          0x00000001  // installed language group ids
#define LGRPID_SUPPORTED          0x00000002  // supported language group ids


//
//  Locale Enumeration Flags.
//
#define LCID_INSTALLED            0x00000001  // installed locale ids
#define LCID_SUPPORTED            0x00000002  // supported locale ids
#define LCID_ALTERNATE_SORTS      0x00000004  // alternate sort locale ids


#if (WINVER >= _WIN32_WINNT_VISTA)
//
//  Named based enumeration flags.
//
#define LOCALE_ALL                  0                     // enumerate all named based locales
#define LOCALE_WINDOWS              0x00000001            // shipped locales and/or replacements for them
#define LOCALE_SUPPLEMENTAL         0x00000002            // supplemental locales only
#define LOCALE_ALTERNATE_SORTS      0x00000004            // alternate sort locales
#define LOCALE_REPLACEMENT          0x00000008            // locales that replace shipped locales (callback flag only)
#endif // (WINVER >= _WIN32_WINNT_VISTA)
#if (WINVER >= _WIN32_WINNT_WIN7)
#define LOCALE_NEUTRALDATA          0x00000010            // Locales that are "neutral" (language only, region data is default)
#define LOCALE_SPECIFICDATA         0x00000020            // Locales that contain language and region data
#endif // (WINVER >= _WIN32_WINNT_WIN7)

//
//  Code Page Enumeration Flags.
//
#define CP_INSTALLED              0x00000001  // installed code page ids
#define CP_SUPPORTED              0x00000002  // supported code page ids


//
//  Sorting Flags.
//
//    WORD Sort:    culturally correct sort
//                  hyphen and apostrophe are special cased
//                  example: "coop" and "co-op" will sort together in a list
//
//                        co_op     <-------  underscore (symbol)
//                        coat
//                        comb
//                        coop
//                        co-op     <-------  hyphen (punctuation)
//                        cork
//                        went
//                        were
//                        we're     <-------  apostrophe (punctuation)
//
//
//    STRING Sort:  hyphen and apostrophe will sort with all other symbols
//
//                        co-op     <-------  hyphen (punctuation)
//                        co_op     <-------  underscore (symbol)
//                        coat
//                        comb
//                        coop
//                        cork
//                        we're     <-------  apostrophe (punctuation)
//                        went
//                        were
//
#define SORT_STRINGSORT           0x00001000  // use string sort method

//  Sort digits as numbers (ie: 2 comes before 10)
#if (WINVER >= _WIN32_WINNT_WIN7)
#define SORT_DIGITSASNUMBERS      0x00000008  // use digits as numbers sort method
#endif // (WINVER >= _WIN32_WINNT_WIN7)


//
//  Compare String Return Values.
//
#define CSTR_LESS_THAN            1           // string 1 less than string 2
#define CSTR_EQUAL                2           // string 1 equal to string 2
#define CSTR_GREATER_THAN         3           // string 1 greater than string 2


//
//  Code Page Default Values.
//
#define CP_ACP                    0           // default to ANSI code page
#define CP_OEMCP                  1           // default to OEM  code page
#define CP_MACCP                  2           // default to MAC  code page
#define CP_THREAD_ACP             3           // current thread's ANSI code page
#define CP_SYMBOL                 42          // SYMBOL translations

#define CP_UTF7                   65000       // UTF-7 translation
#define CP_UTF8                   65001       // UTF-8 translation


//
//  Country/Region Codes.
//
#define CTRY_DEFAULT              0

#define CTRY_ALBANIA              355         // Albania
#define CTRY_ALGERIA              213         // Algeria
#define CTRY_ARGENTINA            54          // Argentina
#define CTRY_ARMENIA              374         // Armenia
#define CTRY_AUSTRALIA            61          // Australia
#define CTRY_AUSTRIA              43          // Austria
#define CTRY_AZERBAIJAN           994         // Azerbaijan
#define CTRY_BAHRAIN              973         // Bahrain
#define CTRY_BELARUS              375         // Belarus
#define CTRY_BELGIUM              32          // Belgium
#define CTRY_BELIZE               501         // Belize
#define CTRY_BOLIVIA              591         // Bolivia
#define CTRY_BRAZIL               55          // Brazil
#define CTRY_BRUNEI_DARUSSALAM    673         // Brunei Darussalam
#define CTRY_BULGARIA             359         // Bulgaria
#define CTRY_CANADA               2           // Canada
#define CTRY_CARIBBEAN            1           // Caribbean
#define CTRY_CHILE                56          // Chile
#define CTRY_COLOMBIA             57          // Colombia
#define CTRY_COSTA_RICA           506         // Costa Rica
#define CTRY_CROATIA              385         // Croatia
#define CTRY_CZECH                420         // Czech Republic
#define CTRY_DENMARK              45          // Denmark
#define CTRY_DOMINICAN_REPUBLIC   1           // Dominican Republic
#define CTRY_ECUADOR              593         // Ecuador
#define CTRY_EGYPT                20          // Egypt
#define CTRY_EL_SALVADOR          503         // El Salvador
#define CTRY_ESTONIA              372         // Estonia
#define CTRY_FAEROE_ISLANDS       298         // Faeroe Islands
#define CTRY_FINLAND              358         // Finland
#define CTRY_FRANCE               33          // France
#define CTRY_GEORGIA              995         // Georgia
#define CTRY_GERMANY              49          // Germany
#define CTRY_GREECE               30          // Greece
#define CTRY_GUATEMALA            502         // Guatemala
#define CTRY_HONDURAS             504         // Honduras
#define CTRY_HONG_KONG            852         // Hong Kong S.A.R., P.R.C.
#define CTRY_HUNGARY              36          // Hungary
#define CTRY_ICELAND              354         // Iceland
#define CTRY_INDIA                91          // India
#define CTRY_INDONESIA            62          // Indonesia
#define CTRY_IRAN                 981         // Iran
#define CTRY_IRAQ                 964         // Iraq
#define CTRY_IRELAND              353         // Ireland
#define CTRY_ISRAEL               972         // Israel
#define CTRY_ITALY                39          // Italy
#define CTRY_JAMAICA              1           // Jamaica
#define CTRY_JAPAN                81          // Japan
#define CTRY_JORDAN               962         // Jordan
#define CTRY_KAZAKSTAN            7           // Kazakstan
#define CTRY_KENYA                254         // Kenya
#define CTRY_KUWAIT               965         // Kuwait
#define CTRY_KYRGYZSTAN           996         // Kyrgyzstan
#define CTRY_LATVIA               371         // Latvia
#define CTRY_LEBANON              961         // Lebanon
#define CTRY_LIBYA                218         // Libya
#define CTRY_LIECHTENSTEIN        41          // Liechtenstein
#define CTRY_LITHUANIA            370         // Lithuania
#define CTRY_LUXEMBOURG           352         // Luxembourg
#define CTRY_MACAU                853         // Macau S.A.R., PRC
#define CTRY_MACEDONIA            389         // Former Yugoslav Republic of Macedonia
#define CTRY_MALAYSIA             60          // Malaysia
#define CTRY_MALDIVES             960         // Maldives
#define CTRY_MEXICO               52          // Mexico
#define CTRY_MONACO               33          // Principality of Monaco
#define CTRY_MONGOLIA             976         // Mongolia
#define CTRY_MOROCCO              212         // Morocco
#define CTRY_NETHERLANDS          31          // Netherlands
#define CTRY_NEW_ZEALAND          64          // New Zealand
#define CTRY_NICARAGUA            505         // Nicaragua
#define CTRY_NORWAY               47          // Norway
#define CTRY_OMAN                 968         // Oman
#define CTRY_PAKISTAN             92          // Islamic Republic of Pakistan
#define CTRY_PANAMA               507         // Panama
#define CTRY_PARAGUAY             595         // Paraguay
#define CTRY_PERU                 51          // Peru
#define CTRY_PHILIPPINES          63          // Republic of the Philippines
#define CTRY_POLAND               48          // Poland
#define CTRY_PORTUGAL             351         // Portugal
#define CTRY_PRCHINA              86          // People's Republic of China
#define CTRY_PUERTO_RICO          1           // Puerto Rico
#define CTRY_QATAR                974         // Qatar
#define CTRY_ROMANIA              40          // Romania
#define CTRY_RUSSIA               7           // Russia
#define CTRY_SAUDI_ARABIA         966         // Saudi Arabia
#define CTRY_SERBIA               381         // Serbia
#define CTRY_SINGAPORE            65          // Singapore
#define CTRY_SLOVAK               421         // Slovak Republic
#define CTRY_SLOVENIA             386         // Slovenia
#define CTRY_SOUTH_AFRICA         27          // South Africa
#define CTRY_SOUTH_KOREA          82          // Korea
#define CTRY_SPAIN                34          // Spain
#define CTRY_SWEDEN               46          // Sweden
#define CTRY_SWITZERLAND          41          // Switzerland
#define CTRY_SYRIA                963         // Syria
#define CTRY_TAIWAN               886         // Taiwan
#define CTRY_TATARSTAN            7           // Tatarstan
#define CTRY_THAILAND             66          // Thailand
#define CTRY_TRINIDAD_Y_TOBAGO    1           // Trinidad y Tobago
#define CTRY_TUNISIA              216         // Tunisia
#define CTRY_TURKEY               90          // Turkey
#define CTRY_UAE                  971         // U.A.E.
#define CTRY_UKRAINE              380         // Ukraine
#define CTRY_UNITED_KINGDOM       44          // United Kingdom
#define CTRY_UNITED_STATES        1           // United States
#define CTRY_URUGUAY              598         // Uruguay
#define CTRY_UZBEKISTAN           7           // Uzbekistan
#define CTRY_VENEZUELA            58          // Venezuela
#define CTRY_VIET_NAM             84          // Viet Nam
#define CTRY_YEMEN                967         // Yemen
#define CTRY_ZIMBABWE             263         // Zimbabwe


//
//  Locale Types.
//
//  These types are used for the GetLocaleInfo NLS API routine.
//  Some of these types are also used for the SetLocaleInfo NLS API routine.
//

//
//  The following LCTypes may be used in combination with any other LCTypes.
//
//    LOCALE_NOUSEROVERRIDE is also used in GetTimeFormat and
//    GetDateFormat.
//
//    LOCALE_USE_CP_ACP is used in many of the A (Ansi) apis that need
//    to do string translation.
//
//    LOCALE_RETURN_NUMBER will return the result from GetLocaleInfo as a
//    number instead of a string.  This flag is only valid for the LCTypes
//    beginning with LOCALE_I.
//
#define LOCALE_NOUSEROVERRIDE         0x80000000   // do not use user overrides
#define LOCALE_USE_CP_ACP             0x40000000   // use the system ACP

//#if(WINVER >= 0x0400)
#define LOCALE_RETURN_NUMBER          0x20000000   // return number instead of string
//#endif /* WINVER >= 0x0400 */

#if (WINVER >= _WIN32_WINNT_WIN7)
#define LOCALE_RETURN_GENITIVE_NAMES  0x10000000   //Flag to return the Genitive forms of month names
#define LOCALE_ALLOW_NEUTRAL_NAMES    0x08000000   //Flag to allow returning neutral names/lcids for name conversion
#endif //(WINVER >= _WIN32_WINNT_WIN7)

//
//  The following LCTypes are mutually exclusive in that they may NOT
//  be used in combination with each other.
//

//
// These are the various forms of the name of the locale:
//
#define LOCALE_SLOCALIZEDDISPLAYNAME  0x00000002   // localized name of locale, eg "German (Germany)" in UI language
#if (WINVER >= _WIN32_WINNT_WIN7)
#define LOCALE_SENGLISHDISPLAYNAME    0x00000072   // Display name (language + country usually) in English, eg "German (Germany)"
#define LOCALE_SNATIVEDISPLAYNAME     0x00000073   // Display name in native locale language, eg "Deutsch (Deutschland)
#endif //(WINVER >= _WIN32_WINNT_WIN7)

#if (WINVER >= _WIN32_WINNT_VISTA)
#define LOCALE_SLOCALIZEDLANGUAGENAME 0x0000006f   // Language Display Name for a language, eg "German" in UI language
#endif //(WINVER >= _WIN32_WINNT_VISTA)
#define LOCALE_SENGLISHLANGUAGENAME   0x00001001   // English name of language, eg "German"
#define LOCALE_SNATIVELANGUAGENAME    0x00000004   // native name of language, eg "Deutsch"

#define LOCALE_SLOCALIZEDCOUNTRYNAME  0x00000006   // localized name of country, eg "Germany" in UI language
#define LOCALE_SENGLISHCOUNTRYNAME    0x00001002   // English name of country, eg "Germany"
#define LOCALE_SNATIVECOUNTRYNAME     0x00000008   // native name of country, eg "Deutschland"

//
// Legacy labels for the locale name values
//
#define LOCALE_SLANGUAGE              0x00000002   // localized name of locale, eg "German (Germany)" in UI language
#if (WINVER >= _WIN32_WINNT_VISTA)
#define LOCALE_SLANGDISPLAYNAME       0x0000006f   // Language Display Name for a language, eg "German" in UI language
#endif //(WINVER >= _WIN32_WINNT_VISTA)
#define LOCALE_SENGLANGUAGE           0x00001001   // English name of language, eg "German"
#define LOCALE_SNATIVELANGNAME        0x00000004   // native name of language, eg "Deutsch"
#define LOCALE_SCOUNTRY               0x00000006   // localized name of country, eg "Germany" in UI language
#define LOCALE_SENGCOUNTRY            0x00001002   // English name of country, eg "Germany"
#define LOCALE_SNATIVECTRYNAME        0x00000008   // native name of country, eg "Deutschland"

// Additional LCTypes
#define LOCALE_ILANGUAGE              0x00000001   // language id, LOCALE_SNAME preferred

#define LOCALE_SABBREVLANGNAME        0x00000003   // arbitrary abbreviated language name, LOCALE_SISO639LANGNAME preferred

#define LOCALE_ICOUNTRY               0x00000005   // country code, eg 1, LOCALE_SISO3166CTRYNAME may be more useful.
#define LOCALE_SABBREVCTRYNAME        0x00000007   // arbitrary abbreviated country name, LOCALE_SISO3166CTRYNAME preferred
#define LOCALE_IGEOID                 0x0000005B   // geographical location id, eg "244"

#define LOCALE_IDEFAULTLANGUAGE       0x00000009   // default language id, deprecated
#define LOCALE_IDEFAULTCOUNTRY        0x0000000A   // default country code, deprecated
#define LOCALE_IDEFAULTCODEPAGE       0x0000000B   // default oem code page (use of Unicode is recommended instead)
#define LOCALE_IDEFAULTANSICODEPAGE   0x00001004   // default ansi code page (use of Unicode is recommended instead)
#define LOCALE_IDEFAULTMACCODEPAGE    0x00001011   // default mac code page (use of Unicode is recommended instead)

#define LOCALE_SLIST                  0x0000000C   // list item separator, eg "," for "1,2,3,4"
#define LOCALE_IMEASURE               0x0000000D   // 0 = metric, 1 = US measurement system

#define LOCALE_SDECIMAL               0x0000000E   // decimal separator, eg "." for 1,234.00
#define LOCALE_STHOUSAND              0x0000000F   // thousand separator, eg "," for 1,234.00
#define LOCALE_SGROUPING              0x00000010   // digit grouping, eg "3;0" for 1,000,000
#define LOCALE_IDIGITS                0x00000011   // number of fractional digits eg 2 for 1.00
#define LOCALE_ILZERO                 0x00000012   // leading zeros for decimal, 0 for .97, 1 for 0.97
#define LOCALE_INEGNUMBER             0x00001010   // negative number mode, 0-4, see documentation
#define LOCALE_SNATIVEDIGITS          0x00000013   // native digits for 0-9, eg "0123456789"

#define LOCALE_SCURRENCY              0x00000014   // local monetary symbol, eg "$"
#define LOCALE_SINTLSYMBOL            0x00000015   // intl monetary symbol, eg "USD"
#define LOCALE_SMONDECIMALSEP         0x00000016   // monetary decimal separator, eg "." for $1,234.00
#define LOCALE_SMONTHOUSANDSEP        0x00000017   // monetary thousand separator, eg "," for $1,234.00
#define LOCALE_SMONGROUPING           0x00000018   // monetary grouping, eg "3;0" for $1,000,000.00
#define LOCALE_ICURRDIGITS            0x00000019   // # local monetary digits, eg 2 for $1.00
#define LOCALE_IINTLCURRDIGITS        0x0000001A   // # intl monetary digits, eg 2 for $1.00
#define LOCALE_ICURRENCY              0x0000001B   // positive currency mode, 0-3, see documenation
#define LOCALE_INEGCURR               0x0000001C   // negative currency mode, 0-15, see documentation

#define LOCALE_SDATE                  0x0000001D   // date separator (derived from LOCALE_SSHORTDATE, use that instead)
#define LOCALE_STIME                  0x0000001E   // time separator (derived from LOCALE_STIMEFORMAT, use that instead)
#define LOCALE_SSHORTDATE             0x0000001F   // short date format string, eg "MM/dd/yyyy"
#define LOCALE_SLONGDATE              0x00000020   // long date format string, eg "dddd, MMMM dd, yyyy"
#define LOCALE_STIMEFORMAT            0x00001003   // time format string, eg "HH:mm:ss"
#define LOCALE_IDATE                  0x00000021   // short date format ordering (derived from LOCALE_SSHORTDATE, use that instead)
#define LOCALE_ILDATE                 0x00000022   // long date format ordering (derived from LOCALE_SLONGDATE, use that instead)
#define LOCALE_ITIME                  0x00000023   // time format specifier (derived from LOCALE_STIMEFORMAT, use that instead)
#define LOCALE_ITIMEMARKPOSN          0x00001005   // time marker position (derived from LOCALE_STIMEFORMAT, use that instead)
#define LOCALE_ICENTURY               0x00000024   // century format specifier (short date, LOCALE_SSHORTDATE is preferred)
#define LOCALE_ITLZERO                0x00000025   // leading zeros in time field (derived from LOCALE_STIMEFORMAT, use that instead)
#define LOCALE_IDAYLZERO              0x00000026   // leading zeros in day field (short date, LOCALE_SSHORTDATE is preferred)
#define LOCALE_IMONLZERO              0x00000027   // leading zeros in month field (short date, LOCALE_SSHORTDATE is preferred)
#define LOCALE_S1159                  0x00000028   // AM designator, eg "AM"
#define LOCALE_S2359                  0x00000029   // PM designator, eg "PM"

#define LOCALE_ICALENDARTYPE          0x00001009   // type of calendar specifier, eg CAL_GREGORIAN
#define LOCALE_IOPTIONALCALENDAR      0x0000100B   // additional calendar types specifier, eg CAL_GREGORIAN_US
#define LOCALE_IFIRSTDAYOFWEEK        0x0000100C   // first day of week specifier, 0-6, 0=Monday, 6=Sunday
#define LOCALE_IFIRSTWEEKOFYEAR       0x0000100D   // first week of year specifier, 0-2, see documentation

#define LOCALE_SDAYNAME1              0x0000002A   // long name for Monday
#define LOCALE_SDAYNAME2              0x0000002B   // long name for Tuesday
#define LOCALE_SDAYNAME3              0x0000002C   // long name for Wednesday
#define LOCALE_SDAYNAME4              0x0000002D   // long name for Thursday
#define LOCALE_SDAYNAME5              0x0000002E   // long name for Friday
#define LOCALE_SDAYNAME6              0x0000002F   // long name for Saturday
#define LOCALE_SDAYNAME7              0x00000030   // long name for Sunday
#define LOCALE_SABBREVDAYNAME1        0x00000031   // abbreviated name for Monday
#define LOCALE_SABBREVDAYNAME2        0x00000032   // abbreviated name for Tuesday
#define LOCALE_SABBREVDAYNAME3        0x00000033   // abbreviated name for Wednesday
#define LOCALE_SABBREVDAYNAME4        0x00000034   // abbreviated name for Thursday
#define LOCALE_SABBREVDAYNAME5        0x00000035   // abbreviated name for Friday
#define LOCALE_SABBREVDAYNAME6        0x00000036   // abbreviated name for Saturday
#define LOCALE_SABBREVDAYNAME7        0x00000037   // abbreviated name for Sunday
#define LOCALE_SMONTHNAME1            0x00000038   // long name for January
#define LOCALE_SMONTHNAME2            0x00000039   // long name for February
#define LOCALE_SMONTHNAME3            0x0000003A   // long name for March
#define LOCALE_SMONTHNAME4            0x0000003B   // long name for April
#define LOCALE_SMONTHNAME5            0x0000003C   // long name for May
#define LOCALE_SMONTHNAME6            0x0000003D   // long name for June
#define LOCALE_SMONTHNAME7            0x0000003E   // long name for July
#define LOCALE_SMONTHNAME8            0x0000003F   // long name for August
#define LOCALE_SMONTHNAME9            0x00000040   // long name for September
#define LOCALE_SMONTHNAME10           0x00000041   // long name for October
#define LOCALE_SMONTHNAME11           0x00000042   // long name for November
#define LOCALE_SMONTHNAME12           0x00000043   // long name for December
#define LOCALE_SMONTHNAME13           0x0000100E   // long name for 13th month (if exists)
#define LOCALE_SABBREVMONTHNAME1      0x00000044   // abbreviated name for January
#define LOCALE_SABBREVMONTHNAME2      0x00000045   // abbreviated name for February
#define LOCALE_SABBREVMONTHNAME3      0x00000046   // abbreviated name for March
#define LOCALE_SABBREVMONTHNAME4      0x00000047   // abbreviated name for April
#define LOCALE_SABBREVMONTHNAME5      0x00000048   // abbreviated name for May
#define LOCALE_SABBREVMONTHNAME6      0x00000049   // abbreviated name for June
#define LOCALE_SABBREVMONTHNAME7      0x0000004A   // abbreviated name for July
#define LOCALE_SABBREVMONTHNAME8      0x0000004B   // abbreviated name for August
#define LOCALE_SABBREVMONTHNAME9      0x0000004C   // abbreviated name for September
#define LOCALE_SABBREVMONTHNAME10     0x0000004D   // abbreviated name for October
#define LOCALE_SABBREVMONTHNAME11     0x0000004E   // abbreviated name for November
#define LOCALE_SABBREVMONTHNAME12     0x0000004F   // abbreviated name for December
#define LOCALE_SABBREVMONTHNAME13     0x0000100F   // abbreviated name for 13th month (if exists)

#define LOCALE_SPOSITIVESIGN          0x00000050   // positive sign, eg ""
#define LOCALE_SNEGATIVESIGN          0x00000051   // negative sign, eg "-"
#define LOCALE_IPOSSIGNPOSN           0x00000052   // positive sign position (derived from INEGCURR)
#define LOCALE_INEGSIGNPOSN           0x00000053   // negative sign position (derived from INEGCURR)
#define LOCALE_IPOSSYMPRECEDES        0x00000054   // mon sym precedes pos amt (derived from ICURRENCY)
#define LOCALE_IPOSSEPBYSPACE         0x00000055   // mon sym sep by space from pos amt (derived from ICURRENCY)
#define LOCALE_INEGSYMPRECEDES        0x00000056   // mon sym precedes neg amt (derived from INEGCURR)
#define LOCALE_INEGSEPBYSPACE         0x00000057   // mon sym sep by space from neg amt (derived from INEGCURR)

//#if(WINVER >= 0x0400)
#define LOCALE_FONTSIGNATURE          0x00000058   // font signature
#define LOCALE_SISO639LANGNAME        0x00000059   // ISO abbreviated language name, eg "en"
#define LOCALE_SISO3166CTRYNAME       0x0000005A   // ISO abbreviated country name, eg "US"
//#endif /* WINVER >= 0x0400 */

//#if(WINVER >= 0x0500)
#define LOCALE_IDEFAULTEBCDICCODEPAGE 0x00001012   // default ebcdic code page (use of Unicode is recommended instead)
#define LOCALE_IPAPERSIZE             0x0000100A   // 1 = letter, 5 = legal, 8 = a3, 9 = a4
#define LOCALE_SENGCURRNAME           0x00001007   // english name of currency, eg "Euro"
#define LOCALE_SNATIVECURRNAME        0x00001008   // native name of currency, eg "euro"
#define LOCALE_SYEARMONTH             0x00001006   // year month format string, eg "MM/yyyy"
#define LOCALE_SSORTNAME              0x00001013   // sort name, usually "", eg "Dictionary" in UI Language
#define LOCALE_IDIGITSUBSTITUTION     0x00001014   // 0 = action_context, 1 = none, 2 = national

//#endif /* WINVER >= 0x0500 */

//#if (WINVER >= 0x0600)
#define LOCALE_SNAME                  0x0000005c   // locale name (ie: en-us)
#define LOCALE_SDURATION              0x0000005d   // time duration format, eg "hh:mm:ss"
#define LOCALE_SKEYBOARDSTOINSTALL    0x0000005e   // Used internally, see GetKeyboardLayoutName() function
#define LOCALE_SSHORTESTDAYNAME1      0x00000060   // Shortest day name for Monday
#define LOCALE_SSHORTESTDAYNAME2      0x00000061   // Shortest day name for Tuesday
#define LOCALE_SSHORTESTDAYNAME3      0x00000062   // Shortest day name for Wednesday
#define LOCALE_SSHORTESTDAYNAME4      0x00000063   // Shortest day name for Thursday
#define LOCALE_SSHORTESTDAYNAME5      0x00000064   // Shortest day name for Friday
#define LOCALE_SSHORTESTDAYNAME6      0x00000065   // Shortest day name for Saturday
#define LOCALE_SSHORTESTDAYNAME7      0x00000066   // Shortest day name for Sunday
#define LOCALE_SISO639LANGNAME2       0x00000067   // 3 character ISO abbreviated language name, eg "eng"
#define LOCALE_SISO3166CTRYNAME2      0x00000068   // 3 character ISO country name, eg "USA"
#define LOCALE_SNAN                   0x00000069   // Not a Number, eg "NaN"
#define LOCALE_SPOSINFINITY           0x0000006a   // + Infinity, eg "infinity"
#define LOCALE_SNEGINFINITY           0x0000006b   // - Infinity, eg "-infinity"
#define LOCALE_SSCRIPTS               0x0000006c   // Typical scripts in the locale: ; delimited script codes, eg "Latn;"
#define LOCALE_SPARENT                0x0000006d   // Fallback name for resources, eg "en" for "en-US"
#define LOCALE_SCONSOLEFALLBACKNAME   0x0000006e   // Fallback name for within the console for Unicode Only locales, eg "en" for bn-IN
//#endif //(WINVER >= 0x0600)

//#if (WINVER >= _WIN32_WINNT_WIN7)
#define LOCALE_IREADINGLAYOUT         0x00000070   // Returns one of the following 4 reading on_layout values:
// 0 - Left to right (eg en-US)
// 1 - Right to left (eg arabic locales)
// 2 - Vertical top to bottom with columns to the left and also left to right (ja-JP locales)
// 3 - Vertical top to bottom with columns proceeding to the right
#define LOCALE_INEUTRAL               0x00000071   // Returns 0 for specific cultures, 1 for neutral cultures.
#define LOCALE_INEGATIVEPERCENT       0x00000074   // Returns 0-11 for the negative percent format
#define LOCALE_IPOSITIVEPERCENT       0x00000075   // Returns 0-3 for the positive percent formatIPOSITIVEPERCENT
#define LOCALE_SPERCENT               0x00000076   // Returns the percent symbol
#define LOCALE_SPERMILLE              0x00000077   // Returns the permille (U+2030) symbol
#define LOCALE_SMONTHDAY              0x00000078   // Returns the preferred month/day format
#define LOCALE_SSHORTTIME             0x00000079   // Returns the preferred short time format (ie: no seconds, just h:mm)
#define LOCALE_SOPENTYPELANGUAGETAG   0x0000007a   // Open type language tag, eg: "latn" or "dflt"
#define LOCALE_SSORTLOCALE            0x0000007b   // Name of locale to use for sorting/collation/casing behavior.
//#endif //(WINVER >= _WIN32_WINNT_WIN7)

//
//  Time Flags for GetTimeFormat.
//
#define TIME_NOMINUTESORSECONDS   0x00000001  // do not use minutes or seconds
#define TIME_NOSECONDS            0x00000002  // do not use seconds
#define TIME_NOTIMEMARKER         0x00000004  // do not use time marker
#define TIME_FORCE24HOURFORMAT    0x00000008  // always use 24 hour format


#define LOCALE_IDEFAULTUNIXCODEPAGE   0x1030 /* Wine extension */ // win_nls.h

//
//  Date Flags for GetDateFormat.
//
#define DATE_SHORTDATE            0x00000001  // use short date picture
#define DATE_LONGDATE             0x00000002  // use long date picture
#define DATE_USE_ALT_CALENDAR     0x00000004  // use alternate calendar (if any)

#if(WINVER >= 0x0500)
#define DATE_YEARMONTH            0x00000008  // use year month picture
#define DATE_LTRREADING           0x00000010  // add marks for left to right reading order on_layout
#define DATE_RTLREADING           0x00000020  // add marks for right to left reading order on_layout
#endif /* WINVER >= 0x0500 */

#if (WINVER >= _WIN32_WINNT_WIN7)
#define DATE_AUTOLAYOUT             0x00000040  // add appropriate marks for left-to-right or right-to-left reading order on_layout
#endif //(WINVER >= _WIN32_WINNT_WIN7)

//
//  Calendar Types.
//
//  These types are used for the EnumCalendarInfo and GetCalendarInfo
//  NLS API routines.
//  Some of these types are also used for the SetCalendarInfo NLS API
//  routine.
//

//
//  The following CalTypes may be used in combination with any other CalTypes.
//
//    CAL_NOUSEROVERRIDE
//
//    CAL_USE_CP_ACP is used in the A (Ansi) apis that need to do string
//    translation.
//
//    CAL_RETURN_NUMBER will return the result from GetCalendarInfo as a
//    number instead of a string.  This flag is only valid for the CalTypes
//    beginning with CAL_I.
//
#if(WINVER >= 0x0500)
#define CAL_NOUSEROVERRIDE        LOCALE_NOUSEROVERRIDE         // do not use user overrides
#define CAL_USE_CP_ACP            LOCALE_USE_CP_ACP             // use the system ACP
#define CAL_RETURN_NUMBER         LOCALE_RETURN_NUMBER          // return number instead of string
#endif /* WINVER >= 0x0500 */

#if (WINVER >= _WIN32_WINNT_WIN7)
#define CAL_RETURN_GENITIVE_NAMES LOCALE_RETURN_GENITIVE_NAMES  // return genitive forms of month names
#endif // winver >= windows 7

//
//  The following CalTypes are mutually exclusive in that they may NOT
//  be used in combination with each other.
//
#define CAL_ICALINTVALUE          0x00000001  // calendar type
#define CAL_SCALNAME              0x00000002  // native name of calendar
#define CAL_IYEAROFFSETRANGE      0x00000003  // starting years of eras
#define CAL_SERASTRING            0x00000004  // era name for IYearOffsetRanges, eg A.D.
#define CAL_SSHORTDATE            0x00000005  // short date format string
#define CAL_SLONGDATE             0x00000006  // long date format string
#define CAL_SDAYNAME1             0x00000007  // native name for Monday
#define CAL_SDAYNAME2             0x00000008  // native name for Tuesday
#define CAL_SDAYNAME3             0x00000009  // native name for Wednesday
#define CAL_SDAYNAME4             0x0000000a  // native name for Thursday
#define CAL_SDAYNAME5             0x0000000b  // native name for Friday
#define CAL_SDAYNAME6             0x0000000c  // native name for Saturday
#define CAL_SDAYNAME7             0x0000000d  // native name for Sunday
#define CAL_SABBREVDAYNAME1       0x0000000e  // abbreviated name for Mon
#define CAL_SABBREVDAYNAME2       0x0000000f  // abbreviated name for Tue
#define CAL_SABBREVDAYNAME3       0x00000010  // abbreviated name for Wed
#define CAL_SABBREVDAYNAME4       0x00000011  // abbreviated name for Thu
#define CAL_SABBREVDAYNAME5       0x00000012  // abbreviated name for Fri
#define CAL_SABBREVDAYNAME6       0x00000013  // abbreviated name for Sat
#define CAL_SABBREVDAYNAME7       0x00000014  // abbreviated name for Sun
// Note that in the hebrew calendar the leap month name is always returned as the 7th month
#define CAL_SMONTHNAME1           0x00000015  // native name for January
#define CAL_SMONTHNAME2           0x00000016  // native name for February
#define CAL_SMONTHNAME3           0x00000017  // native name for March
#define CAL_SMONTHNAME4           0x00000018  // native name for April
#define CAL_SMONTHNAME5           0x00000019  // native name for May
#define CAL_SMONTHNAME6           0x0000001a  // native name for June
#define CAL_SMONTHNAME7           0x0000001b  // native name for July
#define CAL_SMONTHNAME8           0x0000001c  // native name for August
#define CAL_SMONTHNAME9           0x0000001d  // native name for September
#define CAL_SMONTHNAME10          0x0000001e  // native name for October
#define CAL_SMONTHNAME11          0x0000001f  // native name for November
#define CAL_SMONTHNAME12          0x00000020  // native name for December
#define CAL_SMONTHNAME13          0x00000021  // native name for 13th month (if any)
#define CAL_SABBREVMONTHNAME1     0x00000022  // abbreviated name for Jan
#define CAL_SABBREVMONTHNAME2     0x00000023  // abbreviated name for Feb
#define CAL_SABBREVMONTHNAME3     0x00000024  // abbreviated name for Mar
#define CAL_SABBREVMONTHNAME4     0x00000025  // abbreviated name for Apr
#define CAL_SABBREVMONTHNAME5     0x00000026  // abbreviated name for May
#define CAL_SABBREVMONTHNAME6     0x00000027  // abbreviated name for Jun
#define CAL_SABBREVMONTHNAME7     0x00000028  // abbreviated name for July
#define CAL_SABBREVMONTHNAME8     0x00000029  // abbreviated name for Aug
#define CAL_SABBREVMONTHNAME9     0x0000002a  // abbreviated name for Sep
#define CAL_SABBREVMONTHNAME10    0x0000002b  // abbreviated name for Oct
#define CAL_SABBREVMONTHNAME11    0x0000002c  // abbreviated name for Nov
#define CAL_SABBREVMONTHNAME12    0x0000002d  // abbreviated name for Dec
#define CAL_SABBREVMONTHNAME13    0x0000002e  // abbreviated name for 13th month (if any)

#if(WINVER >= 0x0500)
#define CAL_SYEARMONTH            0x0000002f  // year month format string
#define CAL_ITWODIGITYEARMAX      0x00000030  // two digit year max
#endif /* WINVER >= 0x0500 */

#if (WINVER >= 0x0600)
#define CAL_SSHORTESTDAYNAME1     0x00000031  // Shortest day name for Mo
#define CAL_SSHORTESTDAYNAME2     0x00000032  // Shortest day name for Tu
#define CAL_SSHORTESTDAYNAME3     0x00000033  // Shortest day name for We
#define CAL_SSHORTESTDAYNAME4     0x00000034  // Shortest day name for Th
#define CAL_SSHORTESTDAYNAME5     0x00000035  // Shortest day name for Fr
#define CAL_SSHORTESTDAYNAME6     0x00000036  // Shortest day name for Sa
#define CAL_SSHORTESTDAYNAME7     0x00000037  // Shortest day name for Su
#endif //(WINVER >= 0x0600)

#if (WINVER >= _WIN32_WINNT_WIN7)
#define CAL_SMONTHDAY             0x00000038  // Month/day format
#define CAL_SABBREVERASTRING      0x00000039  // Abbreviated era string (eg: AD)
#endif // winver >= windows 7

//
//  Calendar Enumeration Value.
//
#define ENUM_ALL_CALENDARS        0xffffffff  // enumerate all calendars


//
//  Calendar ID Values.
//
#define CAL_GREGORIAN                  1      // Gregorian (localized) calendar
#define CAL_GREGORIAN_US               2      // Gregorian (U.S.) calendar
#define CAL_JAPAN                      3      // Japanese Emperor Era calendar
#define CAL_TAIWAN                     4      // Taiwan calendar
#define CAL_KOREA                      5      // Korean Tangun Era calendar
#define CAL_HIJRI                      6      // Hijri (Arabic Lunar) calendar
#define CAL_THAI                       7      // Thai calendar
#define CAL_HEBREW                     8      // Hebrew (Lunar) calendar
#define CAL_GREGORIAN_ME_FRENCH        9      // Gregorian Middle East French calendar
#define CAL_GREGORIAN_ARABIC           10     // Gregorian Arabic calendar
#define CAL_GREGORIAN_XLIT_ENGLISH     11     // Gregorian Transliterated English calendar
#define CAL_GREGORIAN_XLIT_FRENCH      12     // Gregorian Transliterated French calendar
#define CAL_UMALQURA                   23     // UmAlQura Hijri (Arabic Lunar) calendar


//
//  Language Group ID Values.
//
#define LGRPID_WESTERN_EUROPE        0x0001   // Western Europe & U.S.
#define LGRPID_CENTRAL_EUROPE        0x0002   // Central Europe
#define LGRPID_BALTIC                0x0003   // Baltic
#define LGRPID_GREEK                 0x0004   // Greek
#define LGRPID_CYRILLIC              0x0005   // Cyrillic
#define LGRPID_TURKIC                0x0006   // Turkic
#define LGRPID_TURKISH               0x0006   // Turkish
#define LGRPID_JAPANESE              0x0007   // Japanese
#define LGRPID_KOREAN                0x0008   // Korean
#define LGRPID_TRADITIONAL_CHINESE   0x0009   // Traditional Chinese
#define LGRPID_SIMPLIFIED_CHINESE    0x000a   // Simplified Chinese
#define LGRPID_THAI                  0x000b   // Thai
#define LGRPID_HEBREW                0x000c   // Hebrew
#define LGRPID_ARABIC                0x000d   // Arabic
#define LGRPID_VIETNAMESE            0x000e   // Vietnamese
#define LGRPID_INDIC                 0x000f   // Indic
#define LGRPID_GEORGIAN              0x0010   // Georgian
#define LGRPID_ARMENIAN              0x0011   // Armenian


#if (WINVER >= 0x0600)
//
//  MUI function flag values
//
#define MUI_LANGUAGE_ID                     0x4      // Use traditional language ID convention
#define MUI_LANGUAGE_NAME                   0x8      // Use ISO language (culture) name convention
#define MUI_MERGE_SYSTEM_FALLBACK           0x10     // GetThreadPreferredUILanguages merges in parent and acme languages
#define MUI_MERGE_USER_FALLBACK             0x20     // GetThreadPreferredUILanguages merges in user preferred languages
#define MUI_UI_FALLBACK                     MUI_MERGE_SYSTEM_FALLBACK | MUI_MERGE_USER_FALLBACK
#define MUI_THREAD_LANGUAGES                0x40     // GetThreadPreferredUILanguages merges in user preferred languages
#define MUI_CONSOLE_FILTER                  0x100    // SetThreadPreferredUILanguages takes on console specific behavior
#define MUI_COMPLEX_SCRIPT_FILTER           0x200    // SetThreadPreferredUILanguages takes on complex script specific behavior
#define MUI_RESET_FILTERS                   0x001    // Reset MUI_CONSOLE_FILTER and MUI_COMPLEX_SCRIPT_FILTER
#define MUI_USER_PREFERRED_UI_LANGUAGES     0x10     // GetFileMUIPath returns the MUI files for the languages in the fallback list
#define MUI_USE_INSTALLED_LANGUAGES         0x20     // GetFileMUIPath returns all the MUI files installed in the machine
#define MUI_USE_SEARCH_ALL_LANGUAGES        0x40     // GetFileMUIPath returns all the MUI files irrespective of whether language is installed
#define MUI_LANG_NEUTRAL_PE_FILE            0x100    // GetFileMUIPath returns target file with .mui extension
#define MUI_NON_LANG_NEUTRAL_FILE           0x200    // GetFileMUIPath returns target file with same name as source
#define MUI_MACHINE_LANGUAGE_SETTINGS       0x400
#define MUI_FILETYPE_NOT_LANGUAGE_NEUTRAL   0x001   // GetFileMUIInfo found a non-split resource file
#define MUI_FILETYPE_LANGUAGE_NEUTRAL_MAIN  0x002   // GetFileMUIInfo found a LN main module resource file
#define MUI_FILETYPE_LANGUAGE_NEUTRAL_MUI   0x004   // GetFileMUIInfo found a LN MUI module resource file
#define MUI_QUERY_TYPE                      0x001   // GetFileMUIInfo will look for the type of the resource file
#define MUI_QUERY_CHECKSUM                  0x002   // GetFileMUIInfo will look for the checksum of the resource file
#define MUI_QUERY_LANGUAGE_NAME             0x004   // GetFileMUIInfo will look for the culture of the resource file
#define MUI_QUERY_RESOURCE_TYPES            0x008   // GetFileMUIInfo will look for the resource types of the resource file
#define MUI_FILEINFO_VERSION                0x001   // Version of FILEMUIINFO structure used with GetFileMUIInfo

#define MUI_FULL_LANGUAGE               0x01
#define MUI_PARTIAL_LANGUAGE            0x02
#define MUI_LIP_LANGUAGE                0x04
#define MUI_LANGUAGE_INSTALLED          0x20
#define MUI_LANGUAGE_LICENSED           0x40

//
// MUI_CALLBACK_FLAG defines are duplicated in rtlmui.h
//

#define MUI_CALLBACK_ALL_FLAGS                        MUI_CALLBACK_FLAG_UPGRADED_INSTALLATION // OR all other flags when defined.

//
// MUI_CALLBACK_ flags are duplicated in rtlmui.h
//

#endif

////////////////////////////////////////////////////////////////////////////
//
//  Typedefs
//
//  Define all types for the NLS component here.
//
////////////////////////////////////////////////////////////////////////////

//
//  Language Group ID.
//
typedef DWORD LGRPID;


//
//  Locale type constant.
//
typedef DWORD LCTYPE;


//
//  Calendar type constant.
//
typedef DWORD CALTYPE;


//
//  Calendar ID.
//
typedef DWORD CALID;


//
//  CP Info.
//

typedef struct _cpinfo
{
   UINT    MaxCharSize;                    // max length (in bytes) of a char
   BYTE    DefaultChar[MAX_DEFAULTCHAR];   // default character
   BYTE    LeadByte[MAX_LEADBYTES];        // lead byte ranges
} CPINFO, *LPCPINFO;

typedef struct _cpinfoexA
{
   UINT    MaxCharSize;                    // max length (in bytes) of a char
   BYTE    DefaultChar[MAX_DEFAULTCHAR];   // default character (MB)
   BYTE    LeadByte[MAX_LEADBYTES];        // lead byte ranges
   WCHAR   UnicodeDefaultChar;             // default character (Unicode)
   UINT    CodePage;                       // code page id
   CHAR    CodePageName[MAX_PATH];         // code page name (Unicode)
} CPINFOEXA, *LPCPINFOEXA;
typedef struct _cpinfoexW
{
   UINT    MaxCharSize;                    // max length (in bytes) of a char
   BYTE    DefaultChar[MAX_DEFAULTCHAR];   // default character (MB)
   BYTE    LeadByte[MAX_LEADBYTES];        // lead byte ranges
   WCHAR   UnicodeDefaultChar;             // default character (Unicode)
   UINT    CodePage;                       // code page id
   WCHAR   CodePageName[MAX_PATH];         // code page name (Unicode)
} CPINFOEXW, *LPCPINFOEXW;
#ifdef UNICODE
typedef CPINFOEXW CPINFOEX;
typedef LPCPINFOEXW LPCPINFOEX;
#else
typedef CPINFOEXA CPINFOEX;
typedef LPCPINFOEXA LPCPINFOEX;
#endif // UNICODE


//
//  Number format.
//

typedef struct _numberfmtA
{
   UINT    NumDigits;                 // number of decimal digits
   UINT    LeadingZero;               // if leading zero in decimal fields
   UINT    Grouping;                  // group size left of decimal
   LPSTR   lpDecimalSep;              // ptr to decimal separator string
   LPSTR   lpThousandSep;             // ptr to thousand separator string
   UINT    NegativeOrder;             // negative number ordering
} NUMBERFMTA, *LPNUMBERFMTA;
typedef struct _numberfmtW
{
   UINT    NumDigits;                 // number of decimal digits
   UINT    LeadingZero;               // if leading zero in decimal fields
   UINT    Grouping;                  // group size left of decimal
   LPWSTR  lpDecimalSep;              // ptr to decimal separator string
   LPWSTR  lpThousandSep;             // ptr to thousand separator string
   UINT    NegativeOrder;             // negative number ordering
} NUMBERFMTW, *LPNUMBERFMTW;
#ifdef UNICODE
typedef NUMBERFMTW NUMBERFMT;
typedef LPNUMBERFMTW LPNUMBERFMT;
#else
typedef NUMBERFMTA NUMBERFMT;
typedef LPNUMBERFMTA LPNUMBERFMT;
#endif // UNICODE


//
//  Currency format.
//

typedef struct _currencyfmtA
{
   UINT    NumDigits;                 // number of decimal digits
   UINT    LeadingZero;               // if leading zero in decimal fields
   UINT    Grouping;                  // group size left of decimal
   LPSTR   lpDecimalSep;              // ptr to decimal separator string
   LPSTR   lpThousandSep;             // ptr to thousand separator string
   UINT    NegativeOrder;             // negative currency ordering
   UINT    PositiveOrder;             // positive currency ordering
   LPSTR   lpCurrencySymbol;          // ptr to currency symbol string
} CURRENCYFMTA, *LPCURRENCYFMTA;
typedef struct _currencyfmtW
{
   UINT    NumDigits;                 // number of decimal digits
   UINT    LeadingZero;               // if leading zero in decimal fields
   UINT    Grouping;                  // group size left of decimal
   LPWSTR  lpDecimalSep;              // ptr to decimal separator string
   LPWSTR  lpThousandSep;             // ptr to thousand separator string
   UINT    NegativeOrder;             // negative currency ordering
   UINT    PositiveOrder;             // positive currency ordering
   LPWSTR  lpCurrencySymbol;          // ptr to currency symbol string
} CURRENCYFMTW, *LPCURRENCYFMTW;
#ifdef UNICODE
typedef CURRENCYFMTW CURRENCYFMT;
typedef LPCURRENCYFMTW LPCURRENCYFMT;
#else
typedef CURRENCYFMTA CURRENCYFMT;
typedef LPCURRENCYFMTA LPCURRENCYFMT;
#endif // UNICODE

//
//  NLS function capabilities
//

enum SYSNLS_FUNCTION
{
   COMPARE_STRING    =  0x0001,
};
typedef DWORD NLS_FUNCTION;


//
//  NLS version structure.
//

typedef struct _nlsversioninfo
{
   DWORD dwNLSVersionInfoSize;     // 12 bytes
   DWORD dwNLSVersion;
   DWORD dwDefinedVersion;
} NLSVERSIONINFO, *LPNLSVERSIONINFO;

// This is to be deprecated, please use the NLSVERSIONINFO
// structure above in the future.  The difference is that
// the effective ID is more robust.
typedef struct _nlsversioninfoex
{
   DWORD dwNLSVersionInfoSize;     // sizeof(NLSVERSIONINFOEX) == 32 bytes
   DWORD dwNLSVersion;
   DWORD dwDefinedVersion;
   DWORD dwEffectiveId;            // Use NLSVERSIONINFO instead
//xxx linux    GUID  guidCustomVersion;
} NLSVERSIONINFOEX, *LPNLSVERSIONINFOEX;

//
//  GEO defines
//

typedef LONG    GEOID;
typedef DWORD   GEOTYPE;
typedef DWORD   GEOCLASS;

#define GEOID_NOT_AVAILABLE -1

//
//  GEO information types for clients to query
//

enum SYSGEOTYPE
{
   GEO_NATION      =       0x0001,
   GEO_LATITUDE    =       0x0002,
   GEO_LONGITUDE   =       0x0003,
   GEO_ISO2        =       0x0004,
   GEO_ISO3        =       0x0005,
   GEO_RFC1766     =       0x0006,
   GEO_LCID        =       0x0007,
   GEO_FRIENDLYNAME=       0x0008,
   GEO_OFFICIALNAME=       0x0009,
   GEO_TIMEZONES   =       0x000A,
   GEO_OFFICIALLANGUAGES = 0x000B,
};

//
//  More GEOCLASS defines will be listed here
//

enum SYSGEOCLASS
{
   GEOCLASS_NATION  = 16,
   GEOCLASS_REGION  = 14,
};

#if (WINVER >= 0x0600)
//
//  Normalization forms
//

typedef enum _NORM_FORM
{
   NormalizationOther  = 0,       // Not supported
   NormalizationC      = 0x1,     // Each acme plus combining characters to the canonical precomposed equivalent.
   NormalizationD      = 0x2,     // Each precomposed character to its canonical decomposed equivalent.
   NormalizationKC     = 0x5,     // Each acme plus combining characters to the canonical precomposed
   //   equivalents and all compatibility characters to their equivalents.
   NormalizationKD     = 0x6      // Each precomposed character to its canonical decomposed equivalent
                         //   and all compatibility characters to their equivalents.
} NORM_FORM;

//
// IDN (International Domain Name) Flags
//
#define IDN_ALLOW_UNASSIGNED        0x01  // Allow unassigned "query" behavior per RFC 3454
#define IDN_USE_STD3_ASCII_RULES    0x02  // Enforce STD3 ASCII restrictions for legal characters

#define VS_ALLOW_LATIN              0x0001  // Allow Latin in test script even if not present in locale script

#define GSS_ALLOW_INHERITED_COMMON  0x0001  // Output script ids for inherited and common character types if present
#endif //(WINVER >= 0x0600)

//
//  Enumeration function constants.
//

#ifdef STRICT

typedef WINBOOL (CALLBACK* LANGUAGEGROUP_ENUMPROCA)(LGRPID, LPSTR, LPSTR, DWORD, iptr);
//xxx linux typedef WINBOOL (CALLBACK* LANGGROUPLOCALE_ENUMPROCA)(LGRPID, LCID, LPSTR, long_ptr);
typedef WINBOOL (CALLBACK* UILANGUAGE_ENUMPROCA)(LPSTR, iptr);
typedef WINBOOL (CALLBACK* LOCALE_ENUMPROCA)(LPSTR);
typedef WINBOOL (CALLBACK* CODEPAGE_ENUMPROCA)(LPSTR);
typedef WINBOOL (CALLBACK* DATEFMT_ENUMPROCA)(LPSTR);
typedef WINBOOL (CALLBACK* DATEFMT_ENUMPROCEXA)(LPSTR, CALID);
typedef WINBOOL (CALLBACK* TIMEFMT_ENUMPROCA)(LPSTR);
typedef WINBOOL (CALLBACK* CALINFO_ENUMPROCA)(LPSTR);
typedef WINBOOL (CALLBACK* CALINFO_ENUMPROCEXA)(LPSTR, CALID);

typedef WINBOOL (CALLBACK* LANGUAGEGROUP_ENUMPROCW)(LGRPID, LPWSTR, LPWSTR, DWORD, iptr);
//xxx linux typedef WINBOOL (CALLBACK* LANGGROUPLOCALE_ENUMPROCW)(LGRPID, LCID, LPWSTR, long_ptr);
typedef WINBOOL (CALLBACK* UILANGUAGE_ENUMPROCW)(LPWSTR, iptr);
typedef WINBOOL (CALLBACK* LOCALE_ENUMPROCW)(LPWSTR);
typedef WINBOOL (CALLBACK* CODEPAGE_ENUMPROCW)(LPWSTR);
typedef WINBOOL (CALLBACK* DATEFMT_ENUMPROCW)(LPWSTR);
typedef WINBOOL (CALLBACK* DATEFMT_ENUMPROCEXW)(LPWSTR, CALID);
typedef WINBOOL (CALLBACK* TIMEFMT_ENUMPROCW)(LPWSTR);
typedef WINBOOL (CALLBACK* CALINFO_ENUMPROCW)(LPWSTR);
typedef WINBOOL (CALLBACK* CALINFO_ENUMPROCEXW)(LPWSTR, CALID);
typedef WINBOOL (CALLBACK* GEO_ENUMPROC)(GEOID);

#else // !STRICT

typedef FARPROC LANGUAGEGROUP_ENUMPROCA;
typedef FARPROC LANGGROUPLOCALE_ENUMPROCA;
typedef FARPROC UILANGUAGE_ENUMPROCA;
typedef FARPROC LOCALE_ENUMPROCA;
typedef FARPROC CODEPAGE_ENUMPROCA;
typedef FARPROC DATEFMT_ENUMPROCA;
typedef FARPROC DATEFMT_ENUMPROCEXA;
typedef FARPROC TIMEFMT_ENUMPROCA;
typedef FARPROC CALINFO_ENUMPROCA;
typedef FARPROC CALINFO_ENUMPROCEXA;
typedef FARPROC GEO_ENUMPROC;

typedef FARPROC LANGUAGEGROUP_ENUMPROCW;
typedef FARPROC LANGGROUPLOCALE_ENUMPROCW;
typedef FARPROC UILANGUAGE_ENUMPROCW;
typedef FARPROC LOCALE_ENUMPROCW;
typedef FARPROC CODEPAGE_ENUMPROCW;
typedef FARPROC DATEFMT_ENUMPROCW;
typedef FARPROC DATEFMT_ENUMPROCEXW;
typedef FARPROC TIMEFMT_ENUMPROCW;
typedef FARPROC CALINFO_ENUMPROCW;
typedef FARPROC CALINFO_ENUMPROCEXW;

#endif // !STRICT

#ifdef UNICODE

#define LANGUAGEGROUP_ENUMPROC    LANGUAGEGROUP_ENUMPROCW
#define LANGGROUPLOCALE_ENUMPROC  LANGGROUPLOCALE_ENUMPROCW
#define UILANGUAGE_ENUMPROC       UILANGUAGE_ENUMPROCW
#define LOCALE_ENUMPROC           LOCALE_ENUMPROCW
#define CODEPAGE_ENUMPROC         CODEPAGE_ENUMPROCW
#define DATEFMT_ENUMPROC          DATEFMT_ENUMPROCW
#define DATEFMT_ENUMPROCEX        DATEFMT_ENUMPROCEXW
#define TIMEFMT_ENUMPROC          TIMEFMT_ENUMPROCW
#define CALINFO_ENUMPROC          CALINFO_ENUMPROCW
#define CALINFO_ENUMPROCEX        CALINFO_ENUMPROCEXW

#else

#define LANGUAGEGROUP_ENUMPROC    LANGUAGEGROUP_ENUMPROCA
#define LANGGROUPLOCALE_ENUMPROC  LANGGROUPLOCALE_ENUMPROCA
#define UILANGUAGE_ENUMPROC       UILANGUAGE_ENUMPROCA
#define LOCALE_ENUMPROC           LOCALE_ENUMPROCA
#define CODEPAGE_ENUMPROC         CODEPAGE_ENUMPROCA
#define DATEFMT_ENUMPROC          DATEFMT_ENUMPROCA
#define DATEFMT_ENUMPROCEX        DATEFMT_ENUMPROCEXA
#define TIMEFMT_ENUMPROC          TIMEFMT_ENUMPROCA
#define CALINFO_ENUMPROC          CALINFO_ENUMPROCA
#define CALINFO_ENUMPROCEX        CALINFO_ENUMPROCEXA

#endif // !UNICODE

//
// Information about a MUI file, used as input/output in GetFileMUIInfo
// All offsets are relative to start of the structure. Offsets with value 0 mean empty field.
//

typedef struct _FILEMUIINFO
{
   DWORD       dwSize;                 // Size of the structure including buffer size [in]
   DWORD       dwVersion;              // Version of the structure [in]
   DWORD       dwFileType;             // Type of the file [out]
   BYTE        pChecksum[16];          // Checksum of the file [out]
   BYTE        pServiceChecksum[16];   // Checksum of the file [out]
   DWORD       dwLanguageNameOffset;   // Language name of the file [out]
   DWORD       dwTypeIDMainSize;       // Number of TypeIDs in main module [out]
   DWORD       dwTypeIDMainOffset;     // Array of TypeIDs (DWORD) in main module [out]
   DWORD       dwTypeNameMainOffset;   // Multistring array of TypeNames in main module [out]
   DWORD       dwTypeIDMUISize;        // Number of TypeIDs in MUI module [out]
   DWORD       dwTypeIDMUIOffset;      // Array of TypeIDs (DWORD) in MUI module [out]
   DWORD       dwTypeNameMUIOffset;    // Multistring array of TypeNames in MUI module [out]
   BYTE        abBuffer[8];             // Buffer for extra data [in] (Size 4 is for padding)
} FILEMUIINFO, *PFILEMUIINFO;



////////////////////////////////////////////////////////////////////////////
//
//  Macros
//
//  Define all macros for the NLS component here.
//
////////////////////////////////////////////////////////////////////////////

//
//  Macros to determine whether a character is a high or low surrogate,
//  and whether two code points make up a surrogate pair (a high surrogate
//  and a low surrogate).
//
#define IS_HIGH_SURROGATE(wch) (((wch) >= HIGH_SURROGATE_START) && ((wch) <= HIGH_SURROGATE_END))
#define IS_LOW_SURROGATE(wch)  (((wch) >= LOW_SURROGATE_START) && ((wch) <= LOW_SURROGATE_END))
#define IS_SURROGATE_PAIR(hs, ls) (IS_HIGH_SURROGATE(hs) && IS_LOW_SURROGATE(ls))

// ----------------------------------------------------------------------
// The following macros retrieve information from a MUIFILEINFO structure
//
// Gets the culture name (LPWSTR), nullptr if not initialized
#define FILEMUIINFO_GET_CULTURE(pInfo)          \
    ((LPWSTR)((pInfo->dwLanguageNameOffset>0)?(ulong_ptr)pInfo+pInfo->dwLanguageNameOffset:nullptr))
//
// Gets the main module types array (DWORD[]), nullptr if not initialized
#define FILEMUIINFO_GET_MAIN_TYPEIDS(pInfo)       \
    ((DWORD*)((pInfo->dwTypeIDMainOffset>0)?(ulong_ptr)pInfo+pInfo->dwTypeIDMainOffset:nullptr))
//
// Gets the main module type array element iType (DWORD), the array is not initialized or index is out of bounds
#define FILEMUIINFO_GET_MAIN_TYPEID(pInfo,iType)  \
    (((iType<pInfo->dwTypeIDMainSize)&&(pInfo->dwTypeIDMainOffset>0))?*((DWORD*)((ulong_ptr)pInfo+pInfo->dwTypeIDMainOffset)+iType):0)
//
// Gets the main module names multistring array (LPWSTR), nullptr if not initialized
#define FILEMUIINFO_GET_MAIN_TYPENAMES(pInfo)       \
    ((LPWSTR)((pInfo->dwTypeNameMainOffset>0)?(ulong_ptr)pInfo+pInfo->dwTypeNameMainOffset:nullptr))
//
// Gets the mui module types array (DWORD[]), nullptr if not initialized
#define FILEMUIINFO_GET_MUI_TYPEIDS(pInfo)        \
    ((DWORD*)((pInfo->dwTypeIDMUIOffset>0)?(ulong_ptr)pInfo+pInfo->dwTypeIDMUIOffset:nullptr))
//
// Gets the mui module type array element iType (DWORD), the array is not initialized or index is out of bounds
#define FILEMUIINFO_GET_MUI_TYPEID(pInfo,iType)   \
    (((iType<pInfo->dwTypeIDMUISize)&&(pInfo->dwTypeIDMUIOffset>0))?*((DWORD*)((ulong_ptr)pInfo+pInfo->dwTypeIDMUIOffset)+iType):0)
//
// Gets the mui module names multistring array (LPWSTR), nullptr if not initialized
#define FILEMUIINFO_GET_MUI_TYPENAMES(pInfo)        \
    ((LPWSTR)((pInfo->dwTypeNameMUIOffset>0)?(ulong_ptr)pInfo+pInfo->dwTypeNameMUIOffset:nullptr))
// ------------------------------------------------------------------------


////////////////////////////////////////////////////////////////////////////
//
//  Function Prototypes
//
//  Only prototypes for the NLS APIs should go here.
//
////////////////////////////////////////////////////////////////////////////

//
//  Code Page Dependent APIs.
//

//xxx linux WINAXISAPI
WINBOOL
WINAPI
IsValidCodePage(
UINT  CodePage);

//xxx linux WINAXISAPI
UINT
WINAPI
GetACP(void);

//xxx linux WINAXISAPI
UINT
WINAPI
GetOEMCP(void);

//xxx linux WINAXISAPI
WINBOOL
WINAPI
GetCPInfo(
UINT       CodePage,
LPCPINFO  lpCPInfo);

//xxx linux WINAXISAPI
WINBOOL
WINAPI
GetCPInfoExA(
UINT          CodePage,
DWORD         dwFlags,
LPCPINFOEXA  lpCPInfoEx);
//xxx linux WINAXISAPI
WINBOOL
WINAPI
GetCPInfoExW(
UINT          CodePage,
DWORD         dwFlags,
LPCPINFOEXW  lpCPInfoEx);
#ifdef UNICODE
#define GetCPInfoEx  GetCPInfoExW
#else
#define GetCPInfoEx  GetCPInfoExA
#endif // !UNICODE

//xxx linux WINAXISAPI
WINBOOL
WINAPI
IsDBCSLeadByte(
BYTE  TestChar);

//xxx linux WINAXISAPI
WINBOOL
WINAPI
IsDBCSLeadByteEx(
UINT  CodePage,
BYTE  TestChar);

//xxx linux WINAXISAPI



//
//  Locale Dependent APIs.
//

// For Windows Vista and above CompareStringEx is preferred
//xxx linux WINAXISAPI
i32
WINAPI
CompareStringA(
LCID     Locale,
DWORD    dwCmpFlags,
PCNZCH lpString1,
i32      cchCount1,
PCNZCH  lpString2,
i32      cchCount2);

//xxx linux WINAXISAPI
i32
WINAPI
CompareStringW(
LCID     Locale,
DWORD    dwCmpFlags,
PCNZWCH lpString1,
i32      cchCount1,
PCNZWCH  lpString2,
i32      cchCount2);

#ifdef UNICODE
#define CompareString  CompareStringW
#else
#define CompareString  CompareStringA
#endif // !UNICODE

#if defined(_M_CEE)
#undef CompareString
__inline
i32
CompareString(
LCID     Locale,
DWORD    dwCmpFlags,
LPCTSTR  lpString1,
i32      cchCount1,
LPCTSTR  lpString2,
i32      cchCount2
)
{
#ifdef UNICODE
   return CompareStringW(
#else
   return CompareStringA(
#endif
          Locale,
          dwCmpFlags,
          lpString1,
          cchCount1,
          lpString2,
          cchCount2
          );
}
#endif	/* _M_CEE */

#if (WINVER >= 0x0600)

// For Windows Vista and above FindNLSStringEx is preferred
WINAXISAPI
i32
WINAPI
FindNLSString(
LCID Locale,
DWORD dwFindNLSStringFlags,
LPCWSTR lpStringSource,
i32 cchSource,
LPCWSTR lpStringValue,
i32 cchValue,
LPINT pcchFound);

#endif //(WINVER >= 0x0600)

#if (WINVER >= _WIN32_WINNT_WIN7)

//xxx linux WINAXISAPI
i32
WINAPI
FindStringOrdinal(
DWORD dwFindStringOrdinalFlags,
LPCWSTR lpStringSource,
i32 cchSource,
LPCWSTR lpStringValue,
i32 cchValue,
WINBOOL bIgnoreCase);

#endif //(WINVER >= _WIN32_WINNT_WIN7)

// For Windows Vista and above LCMapStringEx is preferred
//xxx linux WINAXISAPI
i32
WINAPI
LCMapStringA(
LCID     Locale,
DWORD    dwMapFlags,
LPCSTR  lpSrcStr,
i32      cchSrc,
LPSTR  lpDestStr,
i32      cchDest);
// For Windows Vista and above LCMapStringEx is preferred
//xxx linux WINAXISAPI
i32
WINAPI
LCMapStringW(
LCID     Locale,
DWORD    dwMapFlags,
LPCWSTR  lpSrcStr,
i32      cchSrc,
LPWSTR  lpDestStr,
i32      cchDest);
#ifdef UNICODE
#define LCMapString  LCMapStringW
#else
#define LCMapString  LCMapStringA
#endif // !UNICODE

// For Windows Vista and above GetLocaleInfoEx is preferred
//xxx linux WINAXISAPI
i32
WINAPI
GetLocaleInfoA(
LCID     Locale,
LCTYPE   LCType,
LPSTR  lpLCData,
i32      cchData);
// For Windows Vista and above GetLocaleInfoEx is preferred
//xxx linux WINAXISAPI
i32
WINAPI
GetLocaleInfoW(
LCID     Locale,
LCTYPE   LCType,
LPWSTR  lpLCData,
i32      cchData);
#ifdef UNICODE
#define GetLocaleInfo  GetLocaleInfoW
#else
#define GetLocaleInfo  GetLocaleInfoA
#endif // !UNICODE

//xxx linux WINAXISAPI
WINBOOL
WINAPI
SetLocaleInfoA(
LCID     Locale,
LCTYPE   LCType,
LPCSTR  lpLCData);
//xxx linux WINAXISAPI
WINBOOL
WINAPI
SetLocaleInfoW(
LCID     Locale,
LCTYPE   LCType,
LPCWSTR  lpLCData);
#ifdef UNICODE
#define SetLocaleInfo  SetLocaleInfoW
#else
#define SetLocaleInfo  SetLocaleInfoA
#endif // !UNICODE

#if (WINVER >= 0x040A)
// For Windows Vista and above GetCalendarInfoEx is preferred
WINAXISAPI
i32
WINAPI
GetCalendarInfoA(
LCID     Locale,
CALID    Calendar,
CALTYPE  CalType,
LPSTR   lpCalData,
i32      cchData,
LPDWORD  lpValue);
// For Windows Vista and above GetCalendarInfoEx is preferred
WINAXISAPI
i32
WINAPI
GetCalendarInfoW(
LCID     Locale,
CALID    Calendar,
CALTYPE  CalType,
LPWSTR   lpCalData,
i32      cchData,
LPDWORD  lpValue);
#ifdef UNICODE
#define GetCalendarInfo  GetCalendarInfoW
#else
#define GetCalendarInfo  GetCalendarInfoA
#endif // !UNICODE

WINAXISAPI
WINBOOL
WINAPI
SetCalendarInfoA(
LCID     Locale,
CALID    Calendar,
CALTYPE  CalType,
LPCSTR  lpCalData);
WINAXISAPI
WINBOOL
WINAPI
SetCalendarInfoW(
LCID     Locale,
CALID    Calendar,
CALTYPE  CalType,
LPCWSTR  lpCalData);
#ifdef UNICODE
#define SetCalendarInfo  SetCalendarInfoW
#else
#define SetCalendarInfo  SetCalendarInfoA
#endif // !UNICODE
#endif

#if (WINVER >= 0x0600)
WINAXISAPI
i32
WINAPI
LCIDToLocaleName(
LCID     Locale,
__out_ecount_opt(cchName) LPWSTR  lpName,
i32      cchName,
DWORD    dwFlags);

WINAXISAPI
LCID
WINAPI
LocaleNameToLCID(
LPCWSTR lpName,
DWORD dwFlags);

#endif  // (WINVER >= 0x0600)

// For Windows Vista and above GetTimeFormatEx is preferred
//xxx linux WINAXISAPI
i32
WINAPI
GetTimeFormatA(
LCID             Locale,
DWORD            dwFlags,
CONST SYSTEMTIME *lpTime,
LPCSTR          lpFormat,
LPSTR          lpTimeStr,
i32              cchTime);
// For Windows Vista and above GetTimeFormatEx is preferred
//xxx linux WINAXISAPI
i32
WINAPI
GetTimeFormatW(
LCID             Locale,
DWORD            dwFlags,
CONST SYSTEMTIME *lpTime,
LPCWSTR          lpFormat,
LPWSTR          lpTimeStr,
i32              cchTime);
#ifdef UNICODE
#define GetTimeFormat  GetTimeFormatW
#else
#define GetTimeFormat  GetTimeFormatA
#endif // !UNICODE


// For Windows Vista and above GetDurationFormatEx is preferred
#if (WINVER >= 0x0600)
WINAXISAPI
i32
WINAPI
GetDurationFormat(
LCID             Locale,
DWORD            dwFlags,
CONST SYSTEMTIME *lpDuration,
ULONGLONG ullDuration,
LPCWSTR          lpFormat,
__out_ecount_opt(cchDuration) LPWSTR          lpDurationStr,
i32              cchDuration);
#endif //(WINVER >= 0x0600)

// For Windows Vista and above GetDateFormatEx is preferred
//xxx linux WINAXISAPI
i32
WINAPI
GetDateFormatA(
LCID             Locale,
DWORD            dwFlags,
CONST SYSTEMTIME *lpDate,
LPCSTR          lpFormat,
LPSTR          lpDateStr,
i32              cchDate);
// For Windows Vista and above GetDateFormatEx is preferred
//xxx linux WINAXISAPI
i32
WINAPI
GetDateFormatW(
LCID             Locale,
DWORD            dwFlags,
CONST SYSTEMTIME *lpDate,
LPCWSTR          lpFormat,
LPWSTR          lpDateStr,
i32              cchDate);
#ifdef UNICODE
#define GetDateFormat  GetDateFormatW
#else
#define GetDateFormat  GetDateFormatA
#endif // !UNICODE

// For Windows Vista and above GetNumberFormatEx is preferred
//xxx linux WINAXISAPI
i32
WINAPI
GetNumberFormatA(
LCID             Locale,
DWORD            dwFlags,
LPCSTR          lpValue,
CONST NUMBERFMTA *lpFormat,
LPSTR          lpNumberStr,
i32              cchNumber);
// For Windows Vista and above GetNumberFormatEx is preferred
//xxx linux WINAXISAPI
i32
WINAPI
GetNumberFormatW(
LCID             Locale,
DWORD            dwFlags,
LPCWSTR          lpValue,
CONST NUMBERFMTW *lpFormat,
LPWSTR          lpNumberStr,
i32              cchNumber);
#ifdef UNICODE
#define GetNumberFormat  GetNumberFormatW
#else
#define GetNumberFormat  GetNumberFormatA
#endif // !UNICODE

// For Windows Vista and above GetCurrencyFormatEx is preferred
//xxx linux WINAXISAPI
i32
WINAPI
GetCurrencyFormatA(
LCID               Locale,
DWORD              dwFlags,
LPCSTR            lpValue,
CONST CURRENCYFMTA *lpFormat,
LPSTR            lpCurrencyStr,
i32                cchCurrency);
// For Windows Vista and above GetCurrencyFormatEx is preferred
//xxx linux WINAXISAPI
i32
WINAPI
GetCurrencyFormatW(
LCID               Locale,
DWORD              dwFlags,
LPCWSTR            lpValue,
CONST CURRENCYFMTW *lpFormat,
LPWSTR            lpCurrencyStr,
i32                cchCurrency);
#ifdef UNICODE
#define GetCurrencyFormat  GetCurrencyFormatW
#else
#define GetCurrencyFormat  GetCurrencyFormatA
#endif // !UNICODE

// For Windows Vista and above EnumCalendarInfoExEx is preferred
//xxx linux WINAXISAPI
WINBOOL
WINAPI
EnumCalendarInfoA(
CALINFO_ENUMPROCA lpCalInfoEnumProc,
LCID              Locale,
CALID             Calendar,
CALTYPE           CalType);
// For Windows Vista and above EnumCalendarInfoExEx is preferred
//xxx linux WINAXISAPI
WINBOOL
WINAPI
EnumCalendarInfoW(
CALINFO_ENUMPROCW lpCalInfoEnumProc,
LCID              Locale,
CALID             Calendar,
CALTYPE           CalType);
#ifdef UNICODE
#define EnumCalendarInfo  EnumCalendarInfoW
#else
#define EnumCalendarInfo  EnumCalendarInfoA
#endif // !UNICODE

#if(WINVER >= 0x0500)
// For Windows Vista and above EnumCalendarInfoExEx is preferred
WINAXISAPI
WINBOOL
WINAPI
EnumCalendarInfoExA(
CALINFO_ENUMPROCEXA lpCalInfoEnumProcEx,
LCID                Locale,
CALID               Calendar,
CALTYPE             CalType);
// For Windows Vista and above EnumCalendarInfoExEx is preferred
WINAXISAPI
WINBOOL
WINAPI
EnumCalendarInfoExW(
CALINFO_ENUMPROCEXW lpCalInfoEnumProcEx,
LCID                Locale,
CALID               Calendar,
CALTYPE             CalType);
#ifdef UNICODE
#define EnumCalendarInfoEx  EnumCalendarInfoExW
#else
#define EnumCalendarInfoEx  EnumCalendarInfoExA
#endif // !UNICODE
#endif /* WINVER >= 0x0500 */

// For Windows Vista and above EnumTimeFormatsEx is preferred
//xxx linux WINAXISAPI
WINBOOL
WINAPI
EnumTimeFormatsA(
TIMEFMT_ENUMPROCA lpTimeFmtEnumProc,
LCID              Locale,
DWORD             dwFlags);
// For Windows Vista and above EnumTimeFormatsEx is preferred
//xxx linux WINAXISAPI
WINBOOL
WINAPI
EnumTimeFormatsW(
TIMEFMT_ENUMPROCW lpTimeFmtEnumProc,
LCID              Locale,
DWORD             dwFlags);
#ifdef UNICODE
#define EnumTimeFormats  EnumTimeFormatsW
#else
#define EnumTimeFormats  EnumTimeFormatsA
#endif // !UNICODE

// For Windows Vista and above EnumDateFormatsExEx is preferred
//xxx linux WINAXISAPI
WINBOOL
WINAPI
EnumDateFormatsA(
DATEFMT_ENUMPROCA lpDateFmtEnumProc,
LCID              Locale,
DWORD             dwFlags);
// For Windows Vista and above EnumDateFormatsExEx is preferred
//xxx linux WINAXISAPI
WINBOOL
WINAPI
EnumDateFormatsW(
DATEFMT_ENUMPROCW lpDateFmtEnumProc,
LCID              Locale,
DWORD             dwFlags);
#ifdef UNICODE
#define EnumDateFormats  EnumDateFormatsW
#else
#define EnumDateFormats  EnumDateFormatsA
#endif // !UNICODE

#if(WINVER >= 0x0500)
// For Windows Vista and above EnumDateFormatsExEx is preferred
WINAXISAPI
WINBOOL
WINAPI
EnumDateFormatsExA(
DATEFMT_ENUMPROCEXA lpDateFmtEnumProcEx,
LCID                Locale,
DWORD               dwFlags);
// For Windows Vista and above EnumDateFormatsExEx is preferred
WINAXISAPI
WINBOOL
WINAPI
EnumDateFormatsExW(
DATEFMT_ENUMPROCEXW lpDateFmtEnumProcEx,
LCID                Locale,
DWORD               dwFlags);
#ifdef UNICODE
#define EnumDateFormatsEx  EnumDateFormatsExW
#else
#define EnumDateFormatsEx  EnumDateFormatsExA
#endif // !UNICODE
#endif /* WINVER >= 0x0500 */

#if(WINVER >= 0x0500)
WINAXISAPI
WINBOOL
WINAPI
IsValidLanguageGroup(
LGRPID  LanguageGroup,
DWORD   dwFlags);
#endif /* WINVER >= 0x0500 */

// For Windows Vista and above GetNLSVersionEx is preferred
//xxx linux WINAXISAPI
WINBOOL
WINAPI
GetNLSVersion(
NLS_FUNCTION     Function,
LCID             Locale,
LPNLSVERSIONINFO lpVersionInformation);

//xxx linux WINAXISAPI
WINBOOL
WINAPI
IsNLSDefinedString(
NLS_FUNCTION     Function,
DWORD            dwFlags,
LPNLSVERSIONINFO lpVersionInformation,
LPCWSTR          lpString,
INT              cchStr);

// For Windows Vista and above IsValidLocaleName is preferred
//xxx linux WINAXISAPI
WINBOOL
WINAPI
IsValidLocale(
LCID   Locale,
DWORD  dwFlags);

//xxx linux WINAXISAPI
i32
WINAPI
GetGeoInfoA(
GEOID       Location,
GEOTYPE     GeoType,
LPSTR     lpGeoData,
i32         cchData,
LANGID      LangId);
//xxx linux WINAXISAPI
i32
WINAPI
GetGeoInfoW(
GEOID       Location,
GEOTYPE     GeoType,
LPWSTR     lpGeoData,
i32         cchData,
LANGID      LangId);
#ifdef UNICODE
#define GetGeoInfo  GetGeoInfoW
#else
#define GetGeoInfo  GetGeoInfoA
#endif // !UNICODE

//xxx linux WINAXISAPI
WINBOOL
WINAPI
EnumSystemGeoID(
GEOCLASS        GeoClass,
GEOID           ParentGeoId,
GEO_ENUMPROC    lpGeoEnumProc);

//xxx linux WINAXISAPI
GEOID
WINAPI
GetUserGeoID(
GEOCLASS    GeoClass);

//xxx linux WINAXISAPI
WINBOOL
WINAPI
SetUserGeoID(
GEOID       GeoId);

//xxx linux WINAXISAPI
LCID
WINAPI
ConvertDefaultLocale(
LCID   Locale);

//xxx linux WINAXISAPI
LCID
WINAPI
GetThreadLocale(void);

//xxx linux WINAXISAPI
WINBOOL
WINAPI
SetThreadLocale(
LCID  Locale
);

#if(WINVER >= 0x0500)
WINAXISAPI
LANGID
WINAPI
GetSystemDefaultUILanguage(void);

WINAXISAPI
LANGID
WINAPI
GetUserDefaultUILanguage(void);
#endif /* WINVER >= 0x0500 */

//xxx linux WINAXISAPI
LANGID
WINAPI
GetSystemDefaultLangID(void);

//xxx linux WINAXISAPI
LANGID
WINAPI
GetUserDefaultLangID(void);

//xxx linux WINAXISAPI
LCID
WINAPI
GetSystemDefaultLCID(void);

//xxx linux WINAXISAPI
LCID
WINAPI
GetUserDefaultLCID(void);



//xxx linux WINAXISAPI
LANGID
WINAPI
SetThreadUILanguage(LANGID LangId);


#if (WINVER >= 0x0600)

WINAXISAPI
LANGID
WINAPI
GetThreadUILanguage(void);

WINAXISAPI
WINBOOL
WINAPI
GetProcessPreferredUILanguages(
DWORD dwFlags,
PWINULONG pulNumLanguages,
__out_ecount_opt(*pcchLanguagesBuffer) PZZWSTR pwszLanguagesBuffer,
PWINULONG pcchLanguagesBuffer
);


WINAXISAPI
WINBOOL
WINAPI
SetProcessPreferredUILanguages(
DWORD dwFlags,
PCZZWSTR pwszLanguagesBuffer,
PWINULONG pulNumLanguages
);


WINAXISAPI
WINBOOL
WINAPI
GetUserPreferredUILanguages (
DWORD dwFlags,
PWINULONG pulNumLanguages,
__out_ecount_opt(*pcchLanguagesBuffer) PZZWSTR pwszLanguagesBuffer,
PWINULONG pcchLanguagesBuffer
);


WINAXISAPI
WINBOOL
WINAPI
GetSystemPreferredUILanguages (
DWORD dwFlags,
PWINULONG pulNumLanguages,
__out_ecount_opt(*pcchLanguagesBuffer) PZZWSTR pwszLanguagesBuffer,
PWINULONG pcchLanguagesBuffer
);


WINAXISAPI
WINBOOL
WINAPI
GetThreadPreferredUILanguages(
DWORD dwFlags,
PWINULONG pulNumLanguages,
__out_ecount_opt(*pcchLanguagesBuffer) PZZWSTR pwszLanguagesBuffer,
PWINULONG pcchLanguagesBuffer
);


WINAXISAPI
WINBOOL
WINAPI
SetThreadPreferredUILanguages(
DWORD dwFlags,
PCZZWSTR pwszLanguagesBuffer,
PWINULONG pulNumLanguages
);

WINAXISAPI
__success(return==1)
WINBOOL
WINAPI
GetFileMUIInfo(
DWORD           dwFlags,
PCWSTR          pcwszFilePath,
__inout_bcount_part_opt(*pcbFileMUIInfo,*pcbFileMUIInfo) PFILEMUIINFO    pFileMUIInfo,
DWORD*          pcbFileMUIInfo);

WINAXISAPI
WINBOOL
WINAPI
GetFileMUIPath(
DWORD      dwFlags,
PCWSTR     pcwszFilePath,
__inout_ecount_opt    (*pcchLanguage)   PWSTR pwszLanguage,
PWINULONG  pcchLanguage,
__out_ecount_opt    (*pcchFileMUIPath) PWSTR pwszFileMUIPath,
PWINULONG pcchFileMUIPath,
PULONGLONG pululEnumerator
);


WINAXISAPI
WINBOOL
WINAPI
GetUILanguageInfo(
DWORD dwFlags,
PCZZWSTR pwmszLanguage,
__out_ecount_opt(*pcchFallbackLanguages) PZZWSTR pwszFallbackLanguages,
__inout_opt PDWORD pcchFallbackLanguages,
PDWORD pAttributes
);


WINAXISAPI
WINBOOL
WINAPI
NotifyUILanguageChange(
DWORD dwFlags,
PCWSTR pcwstrNewLanguage,
PCWSTR pcwstrPreviousLanguage,
DWORD dwReserved,
PDWORD pdwStatusRtrn
);

#endif

//
//  Locale Independent APIs.
//

//xxx linux WINAXISAPI
WINBOOL
WINAPI
GetStringTypeExA(
LCID       Locale,
DWORD      dwInfoType,
LPCSTR   lpSrcStr,
i32        cchSrc,
LPWORD     lpCharType);
//xxx linux WINAXISAPI
WINBOOL
WINAPI
GetStringTypeExW(
LCID       Locale,
DWORD      dwInfoType,
LPCWSTR   lpSrcStr,
i32        cchSrc,
LPWORD     lpCharType);
#ifdef UNICODE
#define GetStringTypeEx  GetStringTypeExW
#else
#define GetStringTypeEx  GetStringTypeExA
#endif // !UNICODE

//
//  NOTE: The parameters for GetStringTypeA and GetStringTypeW are
//        NOT the same.  The W version was shipped in NT 3.1.  The
//        A version was then shipped in 16-bit OLE with the wrong
//        parameters (ported from Win95).  To be compatible, we
//        must break the relationship between the A and W versions
//        of GetStringType.  There will be NO function call for the
//        element GetStringType.
//
//        GetStringTypeEx (above) should be used instead.
//
//xxx linux WINAXISAPI
WINBOOL
WINAPI
GetStringTypeA(
LCID     Locale,
DWORD    dwInfoType,
LPCSTR   lpSrcStr,
i32      cchSrc,
LPWORD  lpCharType);

//xxx linux WINAXISAPI
WINBOOL
WINAPI
GetStringTypeW(
DWORD    dwInfoType,
LPCWSTR  lpSrcStr,
i32      cchSrc,
LPWORD  lpCharType);


//xxx linux WINAXISAPI
i32
WINAPI
FoldStringA(
DWORD    dwMapFlags,
LPCSTR  lpSrcStr,
i32      cchSrc,
LPSTR  lpDestStr,
i32      cchDest);
//xxx linux WINAXISAPI
i32
WINAPI
FoldStringW(
DWORD    dwMapFlags,
LPCWSTR  lpSrcStr,
i32      cchSrc,
LPWSTR  lpDestStr,
i32      cchDest);
#ifdef UNICODE
#define FoldString  FoldStringW
#else
#define FoldString  FoldStringA
#endif // !UNICODE

#if(WINVER >= 0x0500)
WINAXISAPI
WINBOOL
WINAPI
EnumSystemLanguageGroupsA(
LANGUAGEGROUP_ENUMPROCA lpLanguageGroupEnumProc,
DWORD                   dwFlags,
long_ptr                lParam);
WINAXISAPI
WINBOOL
WINAPI
EnumSystemLanguageGroupsW(
LANGUAGEGROUP_ENUMPROCW lpLanguageGroupEnumProc,
DWORD                   dwFlags,
long_ptr                lParam);
#ifdef UNICODE
#define EnumSystemLanguageGroups  EnumSystemLanguageGroupsW
#else
#define EnumSystemLanguageGroups  EnumSystemLanguageGroupsA
#endif // !UNICODE

WINAXISAPI
WINBOOL
WINAPI
EnumLanguageGroupLocalesA(
LANGGROUPLOCALE_ENUMPROCA lpLangGroupLocaleEnumProc,
LGRPID                    LanguageGroup,
DWORD                     dwFlags,
long_ptr                  lParam);
WINAXISAPI
WINBOOL
WINAPI
EnumLanguageGroupLocalesW(
LANGGROUPLOCALE_ENUMPROCW lpLangGroupLocaleEnumProc,
LGRPID                    LanguageGroup,
DWORD                     dwFlags,
long_ptr                  lParam);
#ifdef UNICODE
#define EnumLanguageGroupLocales  EnumLanguageGroupLocalesW
#else
#define EnumLanguageGroupLocales  EnumLanguageGroupLocalesA
#endif // !UNICODE

WINAXISAPI
WINBOOL
WINAPI
EnumUILanguagesA(
UILANGUAGE_ENUMPROCA lpUILanguageEnumProc,
DWORD                dwFlags,
long_ptr             lParam);
WINAXISAPI
WINBOOL
WINAPI
EnumUILanguagesW(
UILANGUAGE_ENUMPROCW lpUILanguageEnumProc,
DWORD                dwFlags,
long_ptr             lParam);
#ifdef UNICODE
#define EnumUILanguages  EnumUILanguagesW
#else
#define EnumUILanguages  EnumUILanguagesA
#endif // !UNICODE
#endif /* WINVER >= 0x0500 */

//xxx linux WINAXISAPI
WINBOOL
WINAPI
EnumSystemLocalesA(
LOCALE_ENUMPROCA lpLocaleEnumProc,
DWORD            dwFlags);
//xxx linux WINAXISAPI
WINBOOL
WINAPI
EnumSystemLocalesW(
LOCALE_ENUMPROCW lpLocaleEnumProc,
DWORD            dwFlags);
#ifdef UNICODE
#define EnumSystemLocales  EnumSystemLocalesW
#else
#define EnumSystemLocales  EnumSystemLocalesA
#endif // !UNICODE

//xxx linux WINAXISAPI
WINBOOL
WINAPI
EnumSystemCodePagesA(
CODEPAGE_ENUMPROCA lpCodePageEnumProc,
DWORD              dwFlags);
//xxx linux WINAXISAPI
WINBOOL
WINAPI
EnumSystemCodePagesW(
CODEPAGE_ENUMPROCW lpCodePageEnumProc,
DWORD              dwFlags);
#ifdef UNICODE
#define EnumSystemCodePages  EnumSystemCodePagesW
#else
#define EnumSystemCodePages  EnumSystemCodePagesA
#endif // !UNICODE


#if (WINVER >= 0x0600)
//
// Windows API Normalization Functions
//

WINNORMALIZEAPI
i32
WINAPI NormalizeString(                          NORM_FORM NormForm,
      __in_ecount(cwSrcLength)      LPCWSTR   lpSrcString,
      i32       cwSrcLength,
      __out_ecount_opt(cwDstLength) LPWSTR    lpDstString,
      i32       cwDstLength );

WINNORMALIZEAPI
WINBOOL
WINAPI IsNormalizedString(                   NORM_FORM NormForm,
      __in_ecount(cwLength)  LPCWSTR   lpString,
      i32       cwLength );

//
// IDN (International Domain Name) Functions
//
WINNORMALIZEAPI
i32
WINAPI IdnToAscii(                          DWORD    dwFlags,
      __in_ecount(cchUnicodeChar) 	 LPCWSTR  lpUnicodeCharStr,
      i32      cchUnicodeChar,
      __out_ecount_opt(cchASCIIChar) LPWSTR   lpASCIICharStr,
      i32      cchASCIIChar);

WINNORMALIZEAPI
i32
WINAPI IdnToNameprepUnicode(                           	DWORD   dwFlags,
      __in_ecount(cchUnicodeChar)     	LPCWSTR lpUnicodeCharStr,
      i32     cchUnicodeChar,
      __out_ecount_opt(cchNameprepChar)   LPWSTR  lpNameprepCharStr,
      i32     cchNameprepChar);

WINNORMALIZEAPI
i32
WINAPI IdnToUnicode(                        	 DWORD   dwFlags,
      __in_ecount(cchASCIIChar)    	 LPCWSTR lpASCIICharStr,
      i32     cchASCIIChar,
      __out_ecount_opt(cchUnicodeChar) LPWSTR  lpUnicodeCharStr,
      i32     cchUnicodeChar);

WINAXISAPI
WINBOOL
WINAPI VerifyScripts(
DWORD   dwFlags,            // optional behavior flags
LPCWSTR lpLocaleScripts,    // Locale list of scripts string
i32     cchLocaleScripts,   // size of locale script list string
LPCWSTR lpTestScripts,      // test scripts string
i32     cchTestScripts);    // size of test list string

WINAXISAPI
i32
WINAPI GetStringScripts(
DWORD   dwFlags,        // optional behavior flags
LPCWSTR lpString,       // Unicode character input string
i32     cchString,      // size of input string
__out_ecount_opt(cchScripts) LPWSTR  lpScripts,      // Script list output string
i32     cchScripts);    // size of output string

#endif //(WINVER >= 0x0600)

#if (WINVER >= 0x0600)
//
// String based NLS APIs
//

#define LOCALE_NAME_USER_DEFAULT            nullptr
#define LOCALE_NAME_INVARIANT               L""
#define LOCALE_NAME_SYSTEM_DEFAULT          L"!x-sys-default-locale"

WINAXISAPI
i32
WINAPI
GetLocaleInfoEx(
LPCWSTR lpLocaleName,
LCTYPE LCType,
LPWSTR lpLCData,
i32 cchData
);

WINAXISAPI
i32
WINAPI
GetCalendarInfoEx(
LPCWSTR lpLocaleName,
CALID Calendar,
LPCWSTR lpReserved,
CALTYPE CalType,
LPWSTR lpCalData,
i32 cchData,
LPDWORD lpValue
);


WINAXISAPI
i32
WINAPI
GetTimeFormatEx(
LPCWSTR lpLocaleName,
DWORD dwFlags,
CONST SYSTEMTIME *lpTime,
LPCWSTR lpFormat,
LPWSTR lpTimeStr,
i32 cchTime
);

WINAXISAPI
i32
WINAPI
GetDateFormatEx(
LPCWSTR lpLocaleName,
DWORD dwFlags,
CONST SYSTEMTIME *lpDate,
LPCWSTR lpFormat,
LPWSTR lpDateStr,
i32 cchDate,
LPCWSTR lpCalendar
);

WINAXISAPI
i32
WINAPI
GetDurationFormatEx(
LPCWSTR lpLocaleName,
DWORD dwFlags,
CONST SYSTEMTIME *lpDuration,
ULONGLONG ullDuration,
LPCWSTR lpFormat,
__out_ecount_opt(cchDuration) LPWSTR lpDurationStr,
i32 cchDuration
);

WINAXISAPI
i32
WINAPI
GetNumberFormatEx(
LPCWSTR lpLocaleName,
DWORD dwFlags,
LPCWSTR lpValue,
CONST NUMBERFMTW *lpFormat,
LPWSTR lpNumberStr,
i32 cchNumber
);

WINAXISAPI
i32
WINAPI
GetCurrencyFormatEx(
LPCWSTR lpLocaleName,
DWORD dwFlags,
LPCWSTR lpValue,
CONST CURRENCYFMTW *lpFormat,
LPWSTR lpCurrencyStr,
i32 cchCurrency
);

WINAXISAPI
i32
WINAPI
GetUserDefaultLocaleName(
__out_ecount(cchLocaleName) LPWSTR lpLocaleName,
i32 cchLocaleName
);

WINAXISAPI
i32
WINAPI
GetSystemDefaultLocaleName(
__out_ecount(cchLocaleName) LPWSTR lpLocaleName,
i32 cchLocaleName
);

WINAXISAPI
WINBOOL
WINAPI
GetNLSVersionEx(
NLS_FUNCTION function,
LPCWSTR lpLocaleName,
LPNLSVERSIONINFOEX lpVersionInformation
);

WINAXISAPI
i32
WINAPI
CompareStringEx(
LPCWSTR lpLocaleName,
DWORD dwCmpFlags,
LPCWSTR lpString1,
i32 cchCount1,
LPCWSTR lpString2,
i32 cchCount2,
LPNLSVERSIONINFO lpVersionInformation,
LPVOID lpReserved,
LPARAM lParam
);

WINAXISAPI
i32
WINAPI
FindNLSStringEx(
LPCWSTR lpLocaleName,
DWORD dwFindNLSStringFlags,
__in_ecount(cchSource) LPCWSTR lpStringSource,
i32 cchSource,
__in_ecount(cchValue) LPCWSTR lpStringValue,
i32 cchValue,
LPINT pcchFound,
LPNLSVERSIONINFO lpVersionInformation,
LPVOID lpReserved,
LPARAM lParam
);


WINAXISAPI
i32
WINAPI
LCMapStringEx(
LPCWSTR lpLocaleName,
DWORD dwMapFlags,
LPCWSTR lpSrcStr,
i32 cchSrc,
LPWSTR lpDestStr,
i32 cchDest,
LPNLSVERSIONINFO lpVersionInformation,
LPVOID lpReserved,
LPARAM lParam
);

WINAXISAPI
i32
WINAPI
CompareStringOrdinal(
LPCWSTR lpString1,
i32     cchCount1,
LPCWSTR lpString2,
i32     cchCount2,
WINBOOL    bIgnoreCase
);

WINAXISAPI
WINBOOL
WINAPI
IsValidLocaleName(
LPCWSTR lpLocaleName
);

typedef WINBOOL (CALLBACK* CALINFO_ENUMPROCEXEX)(LPWSTR, CALID, LPWSTR, LPARAM);

WINAXISAPI
WINBOOL
WINAPI
EnumCalendarInfoExEx(
CALINFO_ENUMPROCEXEX pCalInfoEnumProcExEx,
LPCWSTR lpLocaleName,
CALID Calendar,
LPCWSTR lpReserved,
CALTYPE CalType,
LPARAM lParam
);

typedef WINBOOL (CALLBACK* DATEFMT_ENUMPROCEXEX)(LPWSTR, CALID, LPARAM);

WINAXISAPI
WINBOOL
WINAPI
EnumDateFormatsExEx(
DATEFMT_ENUMPROCEXEX lpDateFmtEnumProcExEx,
LPCWSTR lpLocaleName,
DWORD dwFlags,
LPARAM lParam
);

typedef WINBOOL (CALLBACK* TIMEFMT_ENUMPROCEX)(LPWSTR, LPARAM);

WINAXISAPI
WINBOOL
WINAPI
EnumTimeFormatsEx(
TIMEFMT_ENUMPROCEX lpTimeFmtEnumProcEx,
LPCWSTR lpLocaleName,
DWORD dwFlags,
LPARAM lParam
);

typedef WINBOOL (CALLBACK* LOCALE_ENUMPROCEX)(LPWSTR, DWORD, LPARAM);

WINAXISAPI
WINBOOL
WINAPI
EnumSystemLocalesEx(
LOCALE_ENUMPROCEX lpLocaleEnumProcEx,
DWORD dwFlags,
LPARAM lParam,
LPVOID lpReserved
);


#endif //(WINVER >= 0x0600)

#if (WINVER >= _WIN32_WINNT_WIN7)
//xxx linux //xxx linux WINAXISAPI
i32
WINAPI
ResolveLocaleName(
LPCWSTR lpNameToResolve,
LPWSTR  lpLocaleName,
i32     cchLocaleName
);
#endif // (WINVER >= _WIN32_WINNT_WIN7)


#endif // NONLS


#ifdef __cplusplus
}
#endif

#endif // _WINNLS_


