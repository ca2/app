#include "framework.h"


namespace file
{


   CLASS_DECL_APEX string system_short_name()
   {

#ifdef _UWP

      return "metro";

#else

      ::file::path pathSystemShortName =          auto psystem = m_psystem;

         auto pacmedir = psystem->m_pacmedir;

pacmedir->localconfig() / "system_short_name.txt";

      return m_psystem->m_pacmefile->as_string(pathSystemShortName).trimmed();

#endif

   }


} // namespace file



