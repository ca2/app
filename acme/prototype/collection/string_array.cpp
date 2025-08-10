#include "framework.h"
//#include "string_array.h"
//#include "acme/filesystem/filesystem/path.h"
//#ifdef
//#include <memory.h>
#include <stdlib.h>


void string_array_array_base::add_csv(const ::scoped_string & scopedstr)
{

   string_array_base stra;

   stra.add_lines(scopedstr, false);

   set_size(stra.get_size());

   ::collection::index i = 0;

   for (auto & strLine : stra)
   {

      ::add_csv(element_at(i), strLine);

      i++;

   }

}


CLASS_DECL_ACME bool next_csv(string & str, const_char_pointer &psz)
{

   if (psz == nullptr || *psz == '\0')
   {

      return false;

   }

   str.empty();

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




void add_csv(string_array_base & stra, const ::scoped_string & scopedstr)
{

   const_char_pointer psz = scopedstr.c_str();

   string strValue;

   while (next_csv(strValue, psz))
   {

      stra.add(strValue);

   }

}




CLASS_DECL_ACME char * const * alloc_c_string_array(const string_array_base & stra)
{

   auto iCount = stra.get_count();

   char ** p = (char**) malloc(iCount * sizeof(char**));

   for(int i = 0; i < iCount; i++)
   {

      p[i] = ansi_dup(stra[i].c_str());

   }

   return p;

}


CLASS_DECL_ACME void free_c_string_array(char * const * ppszList, int iCount)
{

   if(::is_null(ppszList))
   {

      return;

   }

   for(int i = 0; i < iCount; i++)
   {

      if(::is_set(ppszList[i]))
      {

         ::free((void*)ppszList[i]);

      }

   }


   ::free((void*)ppszList);



}

//namespace file
//{
//
//string_array_base path::ascendants_name() const { string_array_base patha; return ascendants_name(patha); }
//////   inline path path::folder() const { return ::file_path_folder(*this); }
////inline bool path::operator == (const ::payload & payload) const { return operator == (payload.file_path()); }
////inline bool path::operator != (const ::payload & payload) const { return operator != (payload.file_path()); }
////
//
//} // namespace file
//




CLASS_DECL_ACME string_array_base string_array_from_strdup_count(const_char_pointer *pszaUrl, long lCount)
{
   
   if(::is_null(pszaUrl))
   {
    
      return {};
      
   }
   
   ::string_array_base stra;
   
   for(long l = 0; l < lCount; l++)
   {
      
      stra.add(pszaUrl[l]);
      
      ::free((void *) pszaUrl[l]);
      
   }
   
   ::free((void *) pszaUrl);
   
   return stra;
   
}
