//
// Created by camilo on 2025-08-05 05:08 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "c_string.h"
#include <stdlib.h>
#include <string.h>

namespace c
{


   ::i32 string::find_replace(const_char_pointer search, const_char_pointer replace)
   {

      const_char_pointer orig = m_psz;

      if (!orig || !search || !replace) return 0;
      size_t orig_len = strlen(orig);
      size_t search_len = strlen(search);
      size_t replace_len = strlen(replace);

      if (search_len == 0) return 0; // avoid infinite loop

// Count occurrences
      size_t count = 0;
      const_char_pointer tmp = orig;
      while ((tmp = strstr(tmp, search))) {
         count++;
         tmp += search_len;
      }

      if (count == 0) {
// No matches, return a copy of the original
         char_pointer result = (char_pointer ) ::malloc(orig_len + 1);
         if(!result)
         {
            throw error_no_memory;

         }
         strcpy(result, orig);
         m_psz = result;
         return count;
      }

// Allocate memory for the new string
      size_t new_len = orig_len + count * (replace_len - search_len);
      char_pointer result = (char_pointer ) ::malloc(new_len + 1);
      if (!result)
      {

         throw error_no_memory;

      }

// Build the new string
      char_pointer dst = result;
      const_char_pointer current = orig;
      const_char_pointer match;
      while ((match = strstr(current, search))) {
         size_t segment_len = match - current;
         memcpy(dst, current, segment_len);
         dst += segment_len;
         memcpy(dst, replace, replace_len);
         dst += replace_len;
         current = match + search_len;
      }
// Copy the rest
      strcpy(dst, current);
m_psz = result;
      return count;
   }


   ::i32 string::find_replace(::i8 search, ::i8 replace)
   {

      auto p = m_psz;

      ::i32 count = 0;

      while (*p) {

         if (*p == search) {

            *p = replace;

            count++;

         }
         p++;

      }
   return count;
   }


   ::i32 string::size() const
   {

      return string_safe_length(m_psz);

   }


   string & string::operator += (const_char_pointer p)
   {

      auto pNew  = (char_pointer )  ::malloc(this->size() + string_safe_length(p) + 1);

      strcpy(pNew, m_psz);
      strcat(pNew, p);

      this->destroy();

      m_psz = pNew;

      return *this;

   }


} // namespace c



