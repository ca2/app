#include "framework.h"


//::file::path dir::roaming()
//{
//
//   ::file::path path;
//
//#ifdef WINDOWS_DESKTOP
//
//   path = ::get_known_folder(FOLDERID_RoamingAppData);
//
//#elif defined(_UWP)
//
//   path = begin(::winrt::Windows::Storage::ApplicationData::Current->LocalFolder->Path);
//
//#elif defined(ANDROID)
//
//   path = oslocal()->m_pathCacheDirectory;
//
//#elif defined(__APPLE__)
//
//   path = ::file::path(getenv("HOME")) / "Library/papplication Support";
//
//#else
//
//   path = ::file::path(getenv("HOME")) / ".config";
//
//#endif
//
//   //if (::get_context_system() != nullptr)
//   //{
//
//   //   synchronous_lock synchronouslock(get_system()->mutex());
//
//   //  get_system()->m_pathConfig = path;
//
//   //}
//
//   return path;
//
//}
