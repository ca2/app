#include "framework.h"
#include "acme/node/windows/_windows.h"
#include "acme/os/windows_common/cotaskptr.h"


namespace windows
{


   CLASS_DECL_ACME::file::path user_appdata_local()
   {

      return shell_get_special_folder_path(CSIDL_LOCAL_APPDATA);

   }


} // namespace windows








CLASS_DECL_ACME::file::path get_known_folder(REFKNOWNFOLDERID kfid)
{

   ::file::path str;

   ::cotaskptr < PWSTR > pwszPath;

   HANDLE hToken = nullptr;

   ::OpenProcessToken(::GetCurrentProcess(), TOKEN_QUERY | TOKEN_IMPERSONATE | TOKEN_DUPLICATE, &hToken);

   HRESULT hr = SHGetKnownFolderPath(kfid, 0, hToken, &pwszPath);

   return pwszPath;

}



::file::path dir::bookmark()
{

   return ::dir::localconfig() / "bookmark";

}


::file::path dir::home()
{

   return ::get_known_folder(FOLDERID_Profile);

}
