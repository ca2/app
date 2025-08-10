#include "framework.h"

//#include "acme/prototype/collection/string_array.h"


CLASS_DECL_ACME int framework_is_basis()
{
#if CA2_PLATFORM_VERSION == CA2_BASIS
   return true;
#else
   return false;
#endif
}


CLASS_DECL_ACME int framework_is_stage()
{
#if CA2_PLATFORM_VERSION == CA2_STAGE
   return true;
#else
   return false;
#endif
}


namespace version
{


   CLASS_DECL_ACME int compare(const ::scoped_string & scopedstr1, const ::scoped_string & scopedstr2)
   {


      string_array_base stra1;

      string_array_base stra2;

      string_array_base straSep;

      straSep.add(".");
      straSep.add("_");

      stra1.add_smallest_tokens(scopedstr1, straSep);

      stra2.add_smallest_tokens(scopedstr2, straSep);

      int iCmp = 0;

      for (int i = 0; i < maximum(stra1.get_size(), stra2.get_size()); i++)
      {

         int iVersion1 = 0;

         int iVersion2 = 0;

         if(i < stra1.get_size())
         {

            iVersion1 = atoi(stra1[i].c_str());

         }

         if(i < stra2.get_size())
         {

            iVersion2 = atoi(stra2[i].c_str());

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



