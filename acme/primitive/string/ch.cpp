#include "framework.h"


#include "x/x_charcategory_names.h"


/*
* Index into the table below with the first byte of a UTF-8 sequence to
* get the number of trailing bytes that are supposed to follow it.
* Note that *legal* UTF-8 values can't have 4 or 5-bytes. The table is
* left as-is for anyone who may want to do such conversion, which was
* allowed in earlier algorithms.
*/
const char g_trailingBytesForUTF8[256] =
{
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
   1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
   2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2, 3,3,3,3,3,3,3,3,4,4,4,4,5,5,5,5
};


CLASS_DECL_ACME int trailingBytesForUTF8(char ch)
{

    return g_trailingBytesForUTF8[*(byte*) &ch];

}


namespace str
{


   /* --------------------------------------------------------------------- */



   utf8_char::utf8_char(u64 u)
   {

      m_chLen = (char) wd32_to_ansi_char(m_sz, (u32) u);

      m_sz[m_chLen] = '\0';

   }


   i32 utf8_char::parse(const char * psz)
   {
      char chLen =  1 + trailingBytesForUTF8(*psz);
      char ch = 0;
      for(; ch < chLen; ch++)
      {
         if(*psz == 0)
         {
            m_chLen = -1;
            return -1;
         }
         m_sz[ch] = *psz++;
      }
      m_sz[ch]   = '\0';
      m_chLen    = chLen;
      return chLen;
   }


   namespace ch
   {

      void * char_bidi_names_non_usage_warning();

      i32 ref_tables();

      i32 ref_tables()
      {
         return sizeof(char_bidi_names);
      }


      string get_category_name(i32 i)
      {
         if (!is_legal_uni_index(i))
            return "";
         return string(char_category_names[CHAR_CATEGORY(CHAR_PROP(i))]);
      }


      /*
       * Magic values subtracted from a buffer value during UTF8 conversion.
       * This table contains as many values as there might be trailing bytes
       * in a UTF-8 sequence.
       */
      static const u32 offsetsFromUTF8[6] = { 0x00000000UL, 0x00003080UL, 0x000E2080UL,
                                                   0x03C82080UL, 0xFA082080UL, 0x82082080UL
                                                 };



      void * char_bidi_names_non_usage_warning()
      {
         return char_bidi_names;
      }


   } // namespace ch

} // namespace str


/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
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
