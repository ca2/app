#include "framework.h"


CLASS_DECL_ACME string load_podata(string strLang, bool bOnlyHeader)
{

   ::file::path pathFolder = ::acme::get_system()->dir().module();

   pathFolder -= 1;

   ::file::path path = pathFolder / "Resources/po" / (strLang + ".po");

   return m_psystem->m_pacmefile->as_string(path, bOnlyHeader ? 4096 : -1);

}



