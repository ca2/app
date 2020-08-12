#include "framework.h"
#include "aura/platform/app_core.h"


#ifdef WINDOWS_DESKTOP


// namespace windows
// {


   CLASS_DECL_AURA ::file::path get_known_folder(REFKNOWNFOLDERID kfid);


// } // namespace windows

#elif defined(ANDROID)

#include "aura/os/android/_os_local.h"

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

   if (::aura::system::g_p != nullptr)
   {

      sync_lock sl(::aura::system::g_p->mutex());

      if (::aura::system::g_p->m_pathConfig.has_char())
      {

         return ::aura::system::g_p->m_pathConfig;

      }

      if (::aura::system::g_p->m_pathCacheDir.has_char())
      {

         return ::aura::system::g_p->m_pathCacheDir;

      }


   }

   ::file::path path;

#ifdef WINDOWS_DESKTOP

   path = ::get_known_folder(FOLDERID_RoamingAppData);

#elif defined(_UWP)

   path = begin(::Windows::Storage::ApplicationData::Current->LocalFolder->Path);

#elif defined(ANDROID)

   if (is_null(::aura::system::g_p, 65535))
   {

      output_debug_string("dir::config(err1)\n");

   }
   else if (is_null(::aura::system::g_p->m_poslocal, 65535))
   {

      output_debug_string("dir::config(err3)\n");

   }

#elif defined(__APPLE__)

   path = ::file::path(getenv("HOME")) / "Library/Application Support";

#else

   path = ::file::path(getenv("HOME")) / ".config";

#endif

   if (::aura::system::g_p != nullptr)
   {

      sync_lock sl(::aura::system::g_p->mutex());

     ::aura::system::g_p->m_pathConfig = path;

   }

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
