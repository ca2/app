#include "framework.h"


CLASS_DECL_CORE string load_podata(string strLang, bool bOnlyHeader)
{

   ::file::path path = psystem->dir().module() / "po" / (strLang + ".po");

   return m_psystem->m_pacmefile->as_string(path, bOnlyHeader ? 4096 : -1);

}



