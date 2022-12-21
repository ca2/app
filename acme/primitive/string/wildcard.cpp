// Created by camilo on 2022-04-24 05:22 <3ThomasBorregaardSørensen!! (Thomas likes number 5!!)
#include "framework.h"
#include "acme/filesystem/filesystem/listing.h"
#include "acme/primitive/string/string.h"
#include "acme/primitive/string/str.h"
////#include "acme/exception/exception.h"


const char* wildcard_next_stop(const ::ansi_character * pszCriteria)
{

   if (pszCriteria == nullptr)
      return nullptr;


   const ::ansi_character * pszAsterisk = ansi_find_string(pszCriteria, "*");
   const ::ansi_character * pszQuestion = ansi_find_string(pszCriteria, "?");

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


CLASS_DECL_ACME int_bool matches_wildcard_criteria_dup(const ::ansi_character * pszCriteriaParam, const ::ansi_character * pszValue)
{

   string strCriteria(normalize_wildcard_criteria(pszCriteriaParam));

   const ::ansi_character * pszCriteria = strCriteria;

   const ::ansi_character * pszFind;
   const ::ansi_character * pszStop;

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

   if (strcmp(pszValue, pszCriteria) != 0)
      return false;

   return true;

}


CLASS_DECL_ACME int_bool matches_wildcard_criteria_ci(const ::ansi_character * pszCriteriaParam, const ::ansi_character * pszValue)
{

   string strCriteria(normalize_wildcard_criteria(pszCriteriaParam));

   const ::ansi_character * pszCriteria = strCriteria;

   const ::ansi_character * pszFind;
   const ::ansi_character * pszStop;

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
            if (ansi_count_compare_ci(pszValue, pszCriteria, iLen) != 0)
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
            if (ansi_count_compare_ci(pszValue, pszCriteria, iLen) != 0)
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

         pszValue = ansi_count_find_string_ci(pszValue, pszFind + 1, iLen);

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

   if (ansi_compare_ci(pszValue, pszCriteria) != 0)
      return false;

   return true;

}


CLASS_DECL_ACME int_bool matches_wildcard_criteria(const ::ansi_character * pszCriteriaParam, const ::ansi_character * pszValue)
{

   string strCriteria(normalize_wildcard_criteria(pszCriteriaParam));

   const ::ansi_character * pszCriteria = strCriteria.c_str();

   const ::ansi_character * pszFind;
   const ::ansi_character * pszStop;

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



