#include "framework.h"
#include "aura/node/windows/_windows.h"


namespace windows
{


   CLASS_DECL_AURA::file::path user_appdata_local()
   {

      return shell_get_special_folder_path(CSIDL_LOCAL_APPDATA);

   }


} // namespace windows




