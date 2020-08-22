#include "framework.h"


void string2a::add_csv(string str)
{

   string_array stra;

   stra.add_lines(str, false);

   set_size(stra.get_size());

   index i = 0;

   for (auto & strLine : stra)
   {

      ::add_csv(element_at(i), strLine);

      i++;

   }

}


CLASS_DECL_AURA bool next_csv(string & str, const char * & psz)
{

   if (psz == nullptr || *psz == '\0')
   {

      return false;

   }

   str.Empty();

   char chStart = *psz;

   if (chStart == '\"')
   {
      int iQuoteCount = 0;

      while (true)
      {
         psz++;

         if (*psz == '\"')
         {

            if (iQuoteCount == 0)
            {

               iQuoteCount = 1;

            }
            else if (iQuoteCount == 1)
            {

               iQuoteCount = 0;

               str+='\"';


            }

         }
         else if (iQuoteCount == 1 && *psz == ',')
         {

            psz++;

            return true;

         }
         else if (iQuoteCount == 1 && *psz == '\0')
         {

            return true;

         }
         else
         {

            str += *psz;

         }

      }


   }
   else
   {

      while (true)
      {

         if (*psz == ',')
         {

            psz++;

            return true;

         }
         else if (*psz == '\0')
         {

            return true;

         }

         str += *psz;

         psz++;

      }


   }




}




void add_csv(string_array & stra, const string & str)
{

   const char * psz = str;

   string strValue;

   while (next_csv(strValue, psz))
   {

      stra.add(strValue);

   }

}

