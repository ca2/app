#include "framework.h"
//
//////#include "acme/exception/exception.h"


namespace file
{




} // namespace file




CLASS_DECL_ACME string file_friendly_transform(const ::scoped_string & scopedstr, bool bTransformSlashes)
{

   ::string str(scopedstr);

   str.replace_with("_", ":");
   str.replace_with("_", "\\");
   str.replace_with("_", "/");
   str.replace_with("_", "<");
   str.replace_with("_", ">");
   str.replace_with("_", "\"");
   str.replace_with("_", "\'");
   str.replace_with("_", "|");
   str.replace_with("_", "?");
   str.replace_with("_", "*");

   for (::collection::index i = 0; i < str.length(); i++)
   {

      if (str[i] <= 31)
      {

         str.set_at(i, '_');

      }

   }

   return str;

}



