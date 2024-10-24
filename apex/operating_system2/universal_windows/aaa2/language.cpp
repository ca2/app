#include "framework.h"


CLASS_DECL_APEX string load_podata(string strLang, bool bOnlyHeader)
{

   ::file::path path = ::apexacmesystem()->directory()->module() / "po" / (strLang + ".po");

   return file_system()->as_string(path, bOnlyHeader ? 4096 : -1);

}



