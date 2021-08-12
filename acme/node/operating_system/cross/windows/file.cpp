#include "framework.h"
#include "acme/node/operating_system/_const_console.h"
#include "acme/node/operating_system/console.h"
#ifdef LINUX
#include "acme/node/operating_system/ansi/binreloc.h"
#endif
#if defined(LINUX) || defined(MACOS)
#include <sys/stat.h>
#endif

//
//namespace file
//{
//
//
//
//
//   ::file::path module()
//   {
//
//      char * pszModuleFilePath = nullptr;
//
//#if defined(__APPLE__)
//
//      pszModuleFilePath = ns_get_executable_path();
//
//#else
//
//      pszModuleFilePath = br_find_exe("app");
//
//#endif
//
//      if (pszModuleFilePath == nullptr)
//      {
//
//         return "";
//
//      }
//
//      string strModuleFileName(pszModuleFilePath);
//
//      free(pszModuleFilePath);
//
//      return strModuleFileName;
//
//   }
//
//
//
//}



//::file::path dir::program_data()
//{
//
//#ifdef WINDOWS_DESKTOP
//
//   return ::get_known_folder(FOLDERID_ProgramData);
//
//#else
//
//   return ca2roaming() / "program_data";
//
//#endif
//
//}



int_bool file_exists_raw(const char * path1)
{

   // dedicaverse stat -> Sir And Arthur - Cesar Serenato

   struct stat st;

   if (stat(path1, &st))
   {

      return false;

   }

   if ((st.st_mode & S_IFDIR))
   {

      return false;

   }

   return true;

}


void std_out_buffer::write(const void * pdata, memsize nCount)
{

#ifdef WINDOWS

   DWORD dw;

   WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), pdata, (::u32)nCount, &dw, nullptr);

#else

   fwrite(pdata, nCount, 1, stdout);


#endif

}
