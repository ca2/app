// Created by camilo on 2022-04-24 05:22 <3ThomasBorregaardSørensen!! (Thomas likes number 5!!)
#include "framework.h"


const char* wildcard_next_stop(const char* pszCriteria)
{

   if (pszCriteria == nullptr)
      return nullptr;


   const char* pszAsterisk = ansi_find_string(pszCriteria, "*");
   const char* pszQuestion = ansi_find_string(pszCriteria, "?");

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


CLASS_DECL_ACME int_bool matches_wildcard_criteria_dup(const char* pszCriteriaParam, const char* pszValue)
{

   string strCriteria(normalize_wildcard_criteria(pszCriteriaParam));

   const char* pszCriteria = strCriteria;

   const char* pszFind;
   const char* pszStop;

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
            return ::str().ends(pszValue, pszFind + 1);
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


CLASS_DECL_ACME int_bool matches_wildcard_criteria_ci(const ansichar * pszCriteriaParam, const ansichar * pszValue)
{

   string strCriteria(normalize_wildcard_criteria(pszCriteriaParam));

   const char* pszCriteria = strCriteria;

   const char* pszFind;
   const char* pszStop;

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


CLASS_DECL_ACME int_bool matches_wildcard_criteria(const ansichar * pszCriteriaParam, const ansichar * pszValue)
{

   string strCriteria(normalize_wildcard_criteria(pszCriteriaParam));

   const char* pszCriteria = strCriteria;

   const char* pszFind;
   const char* pszStop;

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



