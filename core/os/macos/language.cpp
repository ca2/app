#include "framework.h"


CLASS_DECL_CORE string load_podata(string strLang, bool bOnlyHeader)
{

   ::file::path pathFolder = ::aura::system::g_p->dir().module();

   pathFolder -= 1;

   ::file::path path = pathFolder / "Resources/po" / (strLang + ".po");

   return file_as_string(path, bOnlyHeader ? 4096 : -1);

}



