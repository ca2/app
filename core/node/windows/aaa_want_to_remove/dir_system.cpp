#include "framework.h"
#include "_windows.h"
#include "aura/os/windows_common/cotaskptr.h"
#include "aura/xml/_.h"



CLASS_DECL_CORE::file::path get_known_folder(REFKNOWNFOLDERID kfid)
{

   ::file::path str;

   ::cotaskptr < PWSTR > pwszPath;

   HANDLE hToken = nullptr;

   ::OpenProcessToken(::GetCurrentProcess(), TOKEN_QUERY | TOKEN_IMPERSONATE | TOKEN_DUPLICATE, &hToken);

   HRESULT hr = SHGetKnownFolderPath(kfid, 0, hToken, &pwszPath);

   return pwszPath;

}

namespace windows
{


   dir_system::dir_system()
   {


   }


   dir_system::~dir_system()
   {

   }



   ::estatus dir_system::initialize(::object * pobjectContext)
   {

      auto estatus = ::dir_system::initialize(pobjectContext);

      if (!estatus)
      {

         return estatus;

      }

      m_pathInstall = ::dir::install();

      shell_get_special_folder_path(
         nullptr,
         m_strCommonAppData,
         CSIDL_COMMON_APPDATA,
         FALSE);
      //shell_get_special_folder_path(
      // nullptr,
      //m_pathProfile,
      //CSIDL_PROFILE,
      //FALSE);

      m_pathHome = get_known_folder(FOLDERID_Profile);

      m_pathCa2Config = ::dir::ca2roaming();

      m_strCommonAppData /= "ca2";

      m_strAppData = get_known_folder(FOLDERID_RoamingAppData);

      shell_get_special_folder_path(
         nullptr,
         m_strPrograms,
         CSIDL_PROGRAMS,
         FALSE);
      shell_get_special_folder_path(
         nullptr,
         m_strCommonPrograms,
         CSIDL_COMMON_PROGRAMS,
         FALSE);

      {

         //string strRelative;
         //strRelative = install();
         //index iFind = strRelative.find(':');
         //if (iFind >= 0)
         //{
         //   strsize iFind1 = strRelative.reverse_find("\\", iFind);
         //   strsize iFind2 = strRelative.reverse_find("/", iFind);
         //   strsize iStart = MAX(iFind1 + 1, iFind2 + 1);
         //   strRelative = strRelative.Left(iFind - 1) + "_" + strRelative.Mid(iStart, iFind - iStart) + strRelative.Mid(iFind + 1);
         //}



      }

      if (m_strTimeFolder.is_empty())
      {

         m_strTimeFolder = ::dir::appdata() / "time";

      }

      if (m_strNetSeedFolder.is_empty())
      {

         m_strNetSeedFolder = ::dir::install() / "net";

      }

      ::dir::mk(m_strTimeFolder);
      //xxdebug_box("win_dir::initialize (m_strTimeFolder)", "win_dir::initialize", 0);

      if (!::dir::is(m_strTimeFolder))
         return false;

      ::dir::mk(m_strTimeFolder / "time");

      //xxdebug_box("win_dir::initialize", "win_dir::initialize", 0);

      return ::success;

   }


   ::estatus dir_system::init_system()
   {

      auto estatus = ::dir_system::init_system();

      if (!estatus)
      {

         return estatus;

      }


      return ::success;

   }


} // namespace windows



