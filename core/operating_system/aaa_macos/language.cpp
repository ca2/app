#include "framework.h"


CLASS_DECL_CORE string load_podata(string strLang, bool bOnlyHeader)
{

   ::file::path pathFolder = psystem->dir()->module();

   pathFolder -= 1;

   ::file::path path = pathFolder / "Resources/po" / (strLang + ".po");

   return acmefile()->as_string(path, bOnlyHeader ? 4096 : -1);

}



