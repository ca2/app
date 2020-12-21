#include "framework.h"
//#include "acme/platform/app_core.h"

#ifdef ANDROID
extern os_local* g_poslocal;
#endif
#ifdef WINDOWS_DESKTOP


// namespace windows
// {


   CLASS_DECL_ACME ::file::path get_known_folder(REFKNOWNFOLDERID kfid);


// } // namespace windows

#endif



::file::path dir::appdata()
{

   return ::dir::ca2roaming() / "appdata" / app_relative();

}


::file::path dir::public_system()
{

   return public_root() / "system";

}


::file::path dir::system()
{

   return ca2roaming() / "system";

}


::file::path dir::config()
{

   return ca2roaming() / "config";

}


::file::path dir::local()
{

   return ca2roaming() / "local";

}


::file::path dir::sensitive()
{

#ifdef WINDOWS
   
   return "C:\\sensitive\\sensitive";

#else

   return "/sensitive/sensitive";

#endif

}


::file::path dir::localconfig()
{

   return ca2roaming() / "localconfig";

}


::file::path dir::program_data()
{

#ifdef WINDOWS_DESKTOP

   return ::get_known_folder(FOLDERID_ProgramData);

#else

   return ca2roaming() / "program_data";

#endif

}


::file::path dir::roaming()
{

   ::file::path path;

#ifdef WINDOWS_DESKTOP

   path = ::get_known_folder(FOLDERID_RoamingAppData);

#elif defined(_UWP)

   path = begin(::Windows::Storage::ApplicationData::Current->LocalFolder->Path);

#elif defined(ANDROID)

   path = oslocal()->m_pathCacheDir;

#elif defined(__APPLE__)

   path = ::file::path(getenv("HOME")) / "Library/Application Support";

#else

   path = ::file::path(getenv("HOME")) / ".config";

#endif

   //if (::get_context_system() != nullptr)
   //{

   //   sync_lock sl(System.mutex());

   //  System.m_pathConfig = path;

   //}

   return path;

}


::file::path dir::ca2roaming()
{

   return roaming() / "ca2";

}


::file::path dir::ca2appdata()
{

   return ca2roaming() / "appdata";

}


::file::path dir::public_root()
{

   return program_data() / "ca2";

}


::file::path dir::relative(::file::path path)
{

   path.replace(":", "");

   ::str::ends_eat_ci(path, ".exe");

   return path;

}

#ifdef _UWP


::file::path dir::app_relative()
{

   return "";

}


#else


::file::path dir::app_relative()
{

   ::file::path path = ::file::app_module();

   path = relative(path);

   return path;

}


#endif
