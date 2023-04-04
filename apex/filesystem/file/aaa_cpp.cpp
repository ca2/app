#include "framework.h"


namespace file
{


   CLASS_DECL_APEX string system_short_name()
   {

#ifdef UNIVERSAL_WINDOWS

      return "metro";

#else

      ::file::path pathSystemShortName =          auto psystem = acmesystem();

         auto pacmedirectory = psystem->m_pacmedirectory;

pacmedirectory->localconfig() / "system_short_name.txt";

      return acmefile()->as_string(pathSystemShortName).trimmed();

#endif

   }


} // namespace file



