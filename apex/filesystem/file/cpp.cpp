#include "framework.h"


namespace file
{


   CLASS_DECL_APEX string system_short_name()
   {

#ifdef _UWP

      return "metro";

#else

      ::file::path pathSystemShortName = ::dir::localconfig() / "system_short_name.txt";

      return file_as_string(pathSystemShortName).trimmed();

#endif

   }


} // namespace file



