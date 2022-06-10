#pragma once


#include "acme/primitive/string/x/x_charcategory.h"
#include "acme/primitive/string/x/x_defines.h"
#include "acme/primitive/string/x/x_tables.h"


inline i32 __uni_index(const ansichar * pszChar);
inline i32 __uni_index(const wd16char * pszChar);
inline i32 __uni_index(const wd32char * pszChar);


/** Character information class.
    \par Basic features:
    - All Unicode information is generated into tables by scripts
      xcharsets.pl  and  xtables_gen.pl
      They are using UnicodeData.txt file and some codepage files, available
      from <a href="http://www.unicode.org/">http://www.unicode.org/</a>
    - Character class supports most Unicode character properties, except for
      Bidirectional char class, and Decomposition information.
      Most of these methods works like Java Character class methods.

    \par Todo:
    - retrieving of bidirectional class information,
    - retrieving of character decomposition mappings (and normalization
      process information),
    - character 'Digit', 'Decimal Digit' properties. You can retrieve
      only 'Number' value property from digit characters.
    - No explicit surrogate characters support. Surrogate pairs are treated as distinct characters.

    @ingroup unicode
*/

inline int ch_uni_len(int c)
{

   return trailingBytesForUTF8(c) + 1;

}


inline int str_uni_len(const char * pszUtf8)
{

   return ch_uni_len(*pszUtf8);

}


/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are topic to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is the Colorer Library.
 *
 * The Initial Developer of the Original Code is
 * Cail Lomecb <cail@nm.ru>.
 * Portions created by the Initial Developer are Copyright (C) 1999-2005
 * the Initial Developer.
 *
 * Contributor(s):
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */


inline i32 parse_unicode(const ansichar * pszChar);
inline i32 __uni_index(const ansichar * pszChar);
inline i32 __uni_len(const ansichar * pszChar);
inline i32 __uni_index_len(const ansichar * pszChar, i32 & len);


inline i32 parse_unicode(const wd16char * pszChar);
inline i32 __uni_index(const wd16char * pszChar);
inline i32 __uni_len(const wd16char * pszChar);
inline i32 __uni_index_len(const wd16char * pszChar, i32 & len);


inline i32 parse_unicode(const wd32char * pszChar);
inline i32 __uni_index(const wd32char * pszChar);
inline i32 __uni_len(const wd32char * pszChar);
inline i32 __uni_index_len(const wd32char * pszChar, i32 & len);



template < typename CHAR_STRING >
inline bool is_trimmed_string_empty(CHAR_STRING p);


inline bool is_trimmed_empty(const ansichar * p) { return is_trimmed_string_empty(p); }
inline bool is_trimmed_empty(const wd16char * p) { return is_trimmed_string_empty(p); }
inline bool is_trimmed_empty(const wd32char * p) { return is_trimmed_string_empty(p); }

