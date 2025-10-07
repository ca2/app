// Created by camilo on 2022-04-24 05:22 <3ThomasBorregaardSorensen!! (Thomas likes number 5!!)
#include "framework.h"
#include "acme/filesystem/filesystem/listing.h"

#include "acme/prototype/string/str.h"
////#include "acme/exception/exception.h"


const_char_pointer wildcard_next_stop(const_char_pointer pszCriteria)
{

   if (pszCriteria == nullptr)
      return nullptr;


   const_char_pointer pszAsterisk = ansi_find_string(pszCriteria, "*");
   const_char_pointer pszQuestion = ansi_find_string(pszCriteria, "?");

   if (pszAsterisk == nullptr && pszQuestion == nullptr)
      return nullptr;

   if (pszAsterisk == nullptr)
      return pszQuestion;
   else if (pszQuestion == nullptr)
      return pszAsterisk;
   else if (pszAsterisk < pszQuestion)
      return pszAsterisk;
   else
      return pszQuestion;

}


CLASS_DECL_ACME int_bool matches_wildcard_criteria_dup(const_char_pointer pszCriteriaParam, const_char_pointer pszValue)
{

   string strCriteria(normalize_wildcard_criteria(pszCriteriaParam));

   const_char_pointer pszCriteria = strCriteria;

   const_char_pointer pszFind;
   const_char_pointer pszStop;

   iptr iLen;

   while (true)
   {

      pszFind = wildcard_next_stop(pszCriteria);

      if (pszFind == nullptr)
         break;

      iLen = pszFind - pszCriteria;

      if (*pszFind == '?')
      {

         if (pszFind > pszCriteria)
         {
            if (ansi_count_compare(pszValue, pszCriteria, iLen) != 0)
               return false;
            pszValue += iLen;
            pszCriteria += iLen;
         }

         if (*pszValue == '\0')
            return false;

         pszCriteria++;
         pszValue++;

      }
      else if (*pszFind == '*')
      {

         if (pszFind > pszCriteria)
         {
            if (ansi_count_compare(pszValue, pszCriteria, iLen) != 0)
               return false;
            pszValue += iLen;
            pszCriteria += iLen;
         }

         pszStop = wildcard_next_stop(pszFind + 1);

         if (pszStop == nullptr)
         {
            
            return string_ends(pszValue, pszFind + 1) != 0;

         }

         iLen = pszStop - (pszFind + 1);

         pszValue = ansi_count_find_string(pszValue, pszFind + 1, iLen);

         if (pszValue == nullptr)
            return false;

         pszValue = pszValue + iLen;
         pszCriteria = pszStop;

      }
      else
      {
         throw ::exception(error_bad_argument, "not_expected, check wildcard_next_stop function");
      }


   }

   if (ansi_cmp(pszValue, pszCriteria) != 0)
      return false;

   return true;

}


CLASS_DECL_ACME int_bool case_insensitive_matches_wildcard_criteria(const_char_pointer pszCriteriaParam, const_char_pointer pszValue)
{

   string strCriteria(normalize_wildcard_criteria(pszCriteriaParam));

   const_char_pointer pszCriteria = strCriteria;

   const_char_pointer pszFind;
   const_char_pointer pszStop;

   iptr iLen;

   while (true)
   {

      pszFind = wildcard_next_stop(pszCriteria);

      if (pszFind == nullptr)
         break;

      iLen = pszFind - pszCriteria;

      if (*pszFind == '?')
      {

         if (pszFind > pszCriteria)
         {
            if (case_insensitive_ansi_count_compare(pszValue, pszCriteria, iLen) != 0)
               return false;
            pszValue += iLen;
            pszCriteria += iLen;
         }

         if (*pszValue == '\0')
            return false;

         pszCriteria++;
         pszValue++;

      }
      else if (*pszFind == '*')
      {

         if (pszFind > pszCriteria)
         {
            if (case_insensitive_ansi_count_compare(pszValue, pszCriteria, iLen) != 0)
               return false;
            pszValue += iLen;
            pszCriteria += iLen;
         }

         pszStop = wildcard_next_stop(pszFind + 1);

         if (pszStop == nullptr)
         {

            pszStop = pszFind + ansi_length(pszFind);

         }

         iLen = pszStop - (pszFind + 1);

         if (iLen <= 0)
         {
            pszValue = pszValue + ansi_len(pszValue);
         }
         else
         {
            pszValue = case_insensitive_ansi_count_find_string(pszValue, pszFind + 1, iLen);
         }

         if (pszValue == nullptr)
            return false;

         pszValue = pszValue + iLen;
         pszCriteria = pszStop;

      }
      else
      {
         throw ::exception(error_bad_argument, "not_expected, check wildcard_next_stop function");
      }


   }

   if (case_insensitive_ansi_compare(pszValue, pszCriteria) != 0)
      return false;

   return true;

}


CLASS_DECL_ACME int_bool matches_wildcard_criteria(const_char_pointer pszCriteriaParam, const_char_pointer pszValue)
{

   string strCriteria(normalize_wildcard_criteria(pszCriteriaParam));

   const_char_pointer pszCriteria = strCriteria.c_str();

   const_char_pointer pszFind;
   const_char_pointer pszStop;

   iptr iLen;

   while (true)
   {

      pszFind = wildcard_next_stop(pszCriteria);

      if (pszFind == nullptr)
         break;

      iLen = pszFind - pszCriteria;

      if (*pszFind == '?')
      {

         if (pszFind > pszCriteria)
         {
            if (ansi_count_compare(pszValue, pszCriteria, iLen) != 0)
               return false;
            pszValue += iLen;
            pszCriteria += iLen;
         }

         if (*pszValue == '\0')
            return false;

         pszCriteria++;
         pszValue++;

      }
      else if (*pszFind == '*')
      {

         if (pszFind > pszCriteria)
         {
            if (ansi_count_compare(pszValue, pszCriteria, iLen) != 0)
               return false;
            pszValue += iLen;
            pszCriteria += iLen;
         }

         pszStop = wildcard_next_stop(pszFind + 1);

         if (pszStop == nullptr)
            pszStop = pszFind + ansi_length(pszFind);

         iLen = pszStop - (pszFind + 1);

         pszValue = ansi_count_find_string(pszValue, pszFind + 1, iLen);

         if (pszValue == nullptr)
            return false;

         pszValue = pszValue + iLen;
         pszCriteria = pszStop;

      }
      else
      {
         throw ::exception(error_bad_argument, "not_expected, check wildcard_next_stop function");
      }

   }

   if (ansi_compare(pszValue, pszCriteria) != 0)
      return false;

   return true;

}



