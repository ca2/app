#include "framework.h"
//
//////#include "acid/exception/exception.h"


namespace file
{




} // namespace file




CLASS_DECL_ACID string file_friendly_transform(string str, bool bTransformSlashes)
{

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



