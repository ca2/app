#include "framework.h"


CLASS_DECL_AURA string load_podata(string strLang, bool bOnlyHeader)
{

   ::file::path path = ::aura::get_system()->dir().module() / "po" / (strLang + ".po");

   return acmefile()->as_string(path, bOnlyHeader ? 4096 : -1);

}



