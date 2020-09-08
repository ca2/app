#include "framework.h"
#include "apex/node/windows/_windows.h"


namespace windows
{


   CLASS_DECL_APEX::file::path user_appdata_local()
   {

      return shell_get_special_folder_path(CSIDL_LOCAL_APPDATA);

   }


} // namespace windows




