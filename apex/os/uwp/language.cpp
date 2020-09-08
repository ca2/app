#include "framework.h"


CLASS_DECL_APEX string load_podata(string strLang, bool bOnlyHeader)
{

   ::file::path path = ::get_context_system()->dir().module() / "po" / (strLang + ".po");

   return file_as_string(path, bOnlyHeader ? 4096 : -1);

}



