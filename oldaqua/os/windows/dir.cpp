#include "framework.h"
#include "aqua/node/windows/_windows.h"


namespace windows
{


   CLASS_DECL_AQUA::file::path user_appdata_local()
   {

      return shell_get_special_folder_path(CSIDL_LOCAL_APPDATA);

   }


} // namespace windows




