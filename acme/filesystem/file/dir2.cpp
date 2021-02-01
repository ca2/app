#include "framework.h"

//#include "acme/platform/app_core.h"

#ifdef ANDROID
extern os_local* g_poslocal;
#endif
#ifdef WINDOWS_DESKTOP


// namespace windows
// {




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
