#include "framework.h"


CLASS_DECL_AXIS int framework_is_basis()
{
#if CA2_PLATFORM_VERSION == CA2_BASIS
   return TRUE;
#else
   return FALSE;
#endif
}


CLASS_DECL_AXIS int framework_is_stage()
{
#if CA2_PLATFORM_VERSION == CA2_STAGE
   return TRUE;
#else
   return FALSE;
#endif
}


namespace version
{


   CLASS_DECL_AXIS int compare(string str1, string str2)
   {


      string_array stra1;

      string_array stra2;

      string_array straSep;

      straSep.add(".");
      straSep.add("_");

      stra1.add_smallest_tokens(str1, straSep);

      stra2.add_smallest_tokens(str2, straSep);

      int iCmp = 0;

      for (int i = 0; i < max(stra1.get_size(), stra2.get_size()); i++)
      {

         int iVersion1 = 0;

         int iVersion2 = 0;

         if(i < stra1.get_size())
         {

            iVersion1 = atoi(stra1[i]);

         }

         if(i < stra2.get_size())
         {

            iVersion2 = atoi(stra2[i]);

         }

         iCmp = iVersion1 - iVersion2;

         if(iCmp != 0)
         {

            return iCmp;

         }

      }

      return iCmp;

   }


} // namespace version



