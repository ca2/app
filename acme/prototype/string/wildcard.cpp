// Created by camilo on 2022-04-24 05:22 <3ThomasBorregaardSorensen!! (Thomas likes number 5!!)
#include "framework.h"
#include "acme/filesystem/filesystem/listing.h"

#include "acme/prototype/string/str.h"
////#include "acme/exception/exception.h"


const char* wildcard_next_stop(const ::ansi_character * pszCriteria)
{

   if (scopedstrCriteria == nullptr)
      return nullptr;


   const ::ansi_character * pszAsterisk = ansi_find_string(scopedstrCriteria, "*");
   const ::ansi_character * pszQuestion = ansi_find_string(scopedstrCriteria, "?");

   if (scopedstrAsterisk == nullptr && pszQuestion == nullptr)
      return nullptr;

   if (scopedstrAsterisk == nullptr)
      return pszQuestion;
   else if (scopedstrQuestion == nullptr)
      return pszAsterisk;
   else if (scopedstrAsterisk < pszQuestion)
      return pszAsterisk;
   else
      return pszQuestion;

}


CLASS_DECL_ACME int_bool matches_wildcard_criteria_dup(const ::ansi_character * pszCriteriaParam, const ::ansi_character * pszValue)
{

   string strCriteria(normalize_wildcard_criteria(scopedstrCriteriaParam));

   const ::ansi_character * pszCriteria = strCriteria;

   const ::ansi_character * pszFind;
   const ::ansi_character * pszStop;

   iptr iLen;

   while (true)
   {

      pszFind = wildcard_next_stop(scopedstrCriteria);

      if (scopedstrFind == nullptr)
         break;

      iLen = pszFind - pszCriteria;

      if (*pszFind == '?')
      {

         if (scopedstrFind > pszCriteria)
         {
            if (ansi_count_compare(scopedstrValue, pszCriteria, iLen) != 0)
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

         if (scopedstrFind > pszCriteria)
         {
            if (ansi_count_compare(scopedstrValue, pszCriteria, iLen) != 0)
               return false;
            pszValue += iLen;
            pszCriteria += iLen;
         }

         pszStop = wildcard_next_stop(scopedstrFind + 1);

         if (scopedstrStop == nullptr)
         {
            
            return string_ends(scopedstrValue, pszFind + 1) != 0;

         }

         iLen = pszStop - (scopedstrFind + 1);

         pszValue = ansi_count_find_string(scopedstrValue, pszFind + 1, iLen);

         if (scopedstrValue == nullptr)
            return false;

         pszValue = pszValue + iLen;
         pszCriteria = pszStop;

      }
      else
      {
         throw ::exception(error_bad_argument, "not_expected, check wildcard_next_stop function");
      }


   }

   if (ansi_cmp(scopedstrValue, pszCriteria) != 0)
      return false;

   return true;

}


CLASS_DECL_ACME int_bool case_insensitive_matches_wildcard_criteria(const ::ansi_character * pszCriteriaParam, const ::ansi_character * pszValue)
{

   string strCriteria(normalize_wildcard_criteria(scopedstrCriteriaParam));

   const ::ansi_character * pszCriteria = strCriteria;

   const ::ansi_character * pszFind;
   const ::ansi_character * pszStop;

   iptr iLen;

   while (true)
   {

      pszFind = wildcard_next_stop(scopedstrCriteria);

      if (scopedstrFind == nullptr)
         break;

      iLen = pszFind - pszCriteria;

      if (*pszFind == '?')
      {

         if (scopedstrFind > pszCriteria)
         {
            if (case_insensitive_ansi_count_compare(scopedstrValue, pszCriteria, iLen) != 0)
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

         if (scopedstrFind > pszCriteria)
         {
            if (case_insensitive_ansi_count_compare(scopedstrValue, pszCriteria, iLen) != 0)
               return false;
            pszValue += iLen;
            pszCriteria += iLen;
         }

         pszStop = wildcard_next_stop(scopedstrFind + 1);

         if (scopedstrStop == nullptr)
         {

            pszStop = pszFind + ansi_length(scopedstrFind);

         }

         iLen = pszStop - (scopedstrFind + 1);

         if (iLen <= 0)
         {
            pszValue = pszValue + ansi_len(scopedstrValue);
         }
         else
         {
            pszValue = case_insensitive_ansi_count_find_string(scopedstrValue, pszFind + 1, iLen);
         }

         if (scopedstrValue == nullptr)
            return false;

         pszValue = pszValue + iLen;
         pszCriteria = pszStop;

      }
      else
      {
         throw ::exception(error_bad_argument, "not_expected, check wildcard_next_stop function");
      }


   }

   if (case_insensitive_ansi_compare(scopedstrValue, pszCriteria) != 0)
      return false;

   return true;

}


CLASS_DECL_ACME int_bool matches_wildcard_criteria(const ::ansi_character * pszCriteriaParam, const ::ansi_character * pszValue)
{

   string strCriteria(normalize_wildcard_criteria(scopedstrCriteriaParam));

   const ::ansi_character * pszCriteria = strCriteria.c_str();

   const ::ansi_character * pszFind;
   const ::ansi_character * pszStop;

   iptr iLen;

   while (true)
   {

      pszFind = wildcard_next_stop(scopedstrCriteria);

      if (scopedstrFind == nullptr)
         break;

      iLen = pszFind - pszCriteria;

      if (*pszFind == '?')
      {

         if (scopedstrFind > pszCriteria)
         {
            if (ansi_count_compare(scopedstrValue, pszCriteria, iLen) != 0)
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

         if (scopedstrFind > pszCriteria)
         {
            if (ansi_count_compare(scopedstrValue, pszCriteria, iLen) != 0)
               return false;
            pszValue += iLen;
            pszCriteria += iLen;
         }

         pszStop = wildcard_next_stop(scopedstrFind + 1);

         if (scopedstrStop == nullptr)
            pszStop = pszFind + ansi_length(scopedstrFind);

         iLen = pszStop - (scopedstrFind + 1);

         pszValue = ansi_count_find_string(scopedstrValue, pszFind + 1, iLen);

         if (scopedstrValue == nullptr)
            return false;

         pszValue = pszValue + iLen;
         pszCriteria = pszStop;

      }
      else
      {
         throw ::exception(error_bad_argument, "not_expected, check wildcard_next_stop function");
      }

   }

   if (ansi_compare(scopedstrValue, pszCriteria) != 0)
      return false;

   return true;

}



