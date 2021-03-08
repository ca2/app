#include "framework.h"


CLASS_DECL_APEX ::file::path get_resource_path()
{

   ::file::path pathFolder = ::apex::get_system()->dir().module();

   pathFolder -= 1;

   ::file::path path = pathFolder / "Resources";

   return path;

}


CLASS_DECL_APEX ::file::path get_resource_path(string strRelative)
{

   ::file::path path = get_resource_path() / strRelative;

   return path;

}


CLASS_DECL_APEX string load_podata(string strLang, bool bOnlyHeader)
{

   ::file::path path = get_resource_path("po/" + strLang + ".po");

   return file_as_string(path, bOnlyHeader ? 4096 : -1);

}



