// Created some path constructors by camilo on 2022-10-09 03:24 <3ThomasBorregaardSorensen!!
#include "framework.h"
//#include "path.h"
////#include "acme/prototype/prototype/payload.h"
////#include "acme/prototype/collection/numeric_array.h"
//

//CLASS_DECL_ACME string ::url::decode(const ::scoped_string & scopedstr);

//CLASS_DECL_ACME::file::path __xxxnode_full_file_path(file::path path);


namespace file
{


} // namespace file


CLASS_DECL_ACME bool path_begins_eat(::string& strUri, const ::scoped_string& scopedstrPrefix)
{

   if (strUri.begins_eat(scopedstrPrefix + "/"))
   {

      return true;

   }
   else if (strUri == scopedstrPrefix)
   {

      strUri.empty();

      return true;

   }

   return false;

}

