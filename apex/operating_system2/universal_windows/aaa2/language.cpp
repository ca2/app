#include "framework.h"


CLASS_DECL_APEX string load_podata(string strLang, bool bOnlyHeader)
{

   ::file::path path = ::apexacmesystem()->dir()->module() / "po" / (strLang + ".po");

   return acmefile()->as_string(path, bOnlyHeader ? 4096 : -1);

}



