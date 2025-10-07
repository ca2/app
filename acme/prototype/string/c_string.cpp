//
// Created by camilo on 2025-08-05 05:08 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "c_string.h"
#include <stdlib.h>
#include <string.h>

namespace c
{


   int string::find_replace(const_char_pointer search, const_char_pointer replace)
   {

      const_char_pointer orig = m_psz;

      if (!orig || !search || !replace) return 0;
      size_t orig_len = strlen(orig);
      size_t search_len = strlen(search);
      size_t replace_len = strlen(replace);

      if (search_len == 0) return 0; // avoid infinite loop

// Count occurrences
      size_t count = 0;
      const char * tmp = orig;
      while ((tmp = strstr(tmp, search))) {
         count++;
         tmp += search_len;
      }

      if (count == 0) {
// No matches, return a copy of the original
         char * result = (char *) ::malloc(orig_len + 1);
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
      char * result = (char *) ::malloc(new_len + 1);
      if (!result)
      {

         throw error_no_memory;

      }

// Build the new string
      char * dst = result;
      const char * current = orig;
      const char * match;
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


   int string::find_replace(char search, char replace)
   {

      auto p = m_psz;

      int count = 0;

      while (*p) {

         if (*p == search) {

            *p = replace;

            count++;

         }
         p++;

      }
   return count;
   }


   int string::size() const
   {

      return string_safe_length(m_psz);

   }


   string & string::operator += (const_char_pointer p)
   {

      auto pNew  = (char *)  ::malloc(this->size() + string_safe_length(p) + 1);

      strcpy(pNew, m_psz);
      strcat(pNew, p);

      this->destroy();

      m_psz = pNew;

      return *this;

   }


} // namespace c



