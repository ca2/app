#include "framework.h"


#include "acme/_operating_system.h"


//#include "universal_windows.h"
//#include <Shellapi.h>
//#include <string.h>

#ifdef WINDOWS_DESKTOP

CLASS_DECL_BOOT int call_async(
const ::file::path & path,
const ::scoped_string & scopedstrParam,
const ::scoped_string & scopedstrDir,
int iShow)
{

   SHELLEXECUTEINFOA infoa;

   memory_set(&infoa, 0, sizeof(infoa));

   infoa.cbSize         = sizeof(infoa);
   infoa.lpFile         = pszPath;
   infoa.lpParameters   = pszParam;
   infoa.lpDirectory    = pszDir;
   infoa.nShow          = iShow;

   int iOk = ::ShellExecuteExA(&infoa);

   return iOk;

}

#endif

#ifdef WINDOWS_DESKTOP
CLASS_DECL_BOOT unsigned int call_sync(const ::file::path & path, const ::scoped_string & scopedstrParam, const ::scoped_string & scopedstrDir, ::e_display edisplay, const class time & timeTimeout, ::property_set & set)
{

   SHELLEXECUTEINFOA infoa;

   memory_set(&infoa, 0, sizeof(infoa));

   infoa.cbSize         = sizeof(infoa);
   infoa.lpFile         = pszPath;
   infoa.lpParameters   = pszParam;
   infoa.lpDirectory    = pszDir;
   infoa.nShow          = iShow;

   infoa.fMask |= SEE_MASK_NOCLOSEPROCESS | SEE_MASK_NOASYNC | SEE_MASK_FLAG_NO_UI;


   ::ShellExecuteExA(&infoa);

   unsigned int dwExitCode;

   int iTry = 0;

   while(iRetry < 0 || iTry <= iRetry)
   {
      if(!GetExitCodeProcess(infoa.hProcess, &dwExitCode))
         break;
      if(dwExitCode != STILL_ACTIVE)
         break;
      sleep(100_ms);
      if(pfnOnRetry != nullptr)
      {
         if(!pfnOnRetry(iTry, dwParam))
            break;
      }
      iTry++;
   }

   return dwExitCode;

}

#endif

#ifdef WINDOWS_DESKTOP
int get_current_processor_index()
{


   return ::GetCurrentProcessorNumber();


}

#endif


#ifdef WINDOWS_DESKTOP

int get_current_process_maximum_affinity()
{

   dword_ptr dwProcessAffinityMask;
   dword_ptr dwSystemAffinityMask;
   if(!GetProcessAffinityMask(::GetCurrentProcess(), &dwProcessAffinityMask, & dwSystemAffinityMask))
   {
      return 0;
   }
   int iMax = -1;
   dword_ptr dwMask = 1;
   for(int i = 0; i < sizeof(dwProcessAffinityMask) * 8; i++)
   {
      if((dwMask & dwProcessAffinityMask) != 0)
      {
         iMax = i;
      }
      dwMask = dwMask << 1;
   }

   return iMax;

}

#endif


#ifdef WINDOWS_DESKTOP

int get_current_process_affinity_order()
{


   dword_ptr dwProcessAffinityMask;
   dword_ptr dwSystemAffinityMask;
   if(!GetProcessAffinityMask(::GetCurrentProcess(), &dwProcessAffinityMask, & dwSystemAffinityMask))
   {
      return 0;
   }
   int iCount = 0;
   dword_ptr dwMask = 1;
   for(int i = 0; i < sizeof(dwProcessAffinityMask) * 8; i++)
   {
      if((dwMask & dwProcessAffinityMask) != 0)
      {
         iCount++;
      }
      dwMask = dwMask << 1;
   }

   return iCount;


}


#endif


#ifdef WINDOWS_DESKTOP

bool process_modules(string_array & stra, unsigned int processID)
{

   HANDLE hProcess;

   unsigned int cbNeeded;

   unsigned int i;

   hProcess = OpenProcess( PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, false, processID );

   if (nullptr == hProcess)
      return false;

   const int iMaxModuleCount = 1024 * 8;

   HMODULE * hMods = ___new HMODULE[iMaxModuleCount];

   const int iImageSize = MAX_PATH * 8;

   char * szImage = (char *) _ca_alloc(iImageSize);

   if(EnumProcessModules(hProcess, hMods, sizeof(HMODULE) * iMaxModuleCount, &cbNeeded))
   {

      for ( i = 0; i < (cbNeeded / sizeof(HMODULE)); i++ )
      {

         if(GetModuleFileNameEx( hProcess, hMods[i], szImage, iImageSize / sizeof(char)))
         {

            stra.add(szImage);

         }

      }

   }

   _ca_free(szImage, 0);

   delete hMods;

   CloseHandle( hProcess );

   return true;

}

#endif


#ifdef WINDOWS_DESKTOP

bool load_modules_diff(string_array & straOld, string_array & straNew, const ::scoped_string & scopedstrExceptDir)
{

   bool bFound;

   HMODULE hmodule;

   size_t iLenExcept;

   if(pszExceptDir != nullptr)
   {

      iLenExcept = ansi_length(pszExceptDir);

   }
   else
   {

      iLenExcept = 0;

   }

   for(int i = 0; i < straOld.get_count(); i++)
   {

      bFound = false;

      if(iLenExcept > 0)
      {

         if(ansi_length(straOld[i]) > iLenExcept)
         {

            if(_strnicmp(straOld[i], pszExceptDir, iLenExcept) == 0)
            {

               continue;

            }

         }

      }

      for(int j = 0; j < straNew.get_count(); j++)
      {

         if(case_insensitive_ansi_compare(straOld[i], straNew[j]) == 0)
         {

            bFound = true;

            break;

         }

      }

      if(!bFound)
      {

         hmodule = nullptr;

         // double check, ensure, that the module has not been already loaded
         // it may happen by loading a missing module that loads dependencies that satisfies straOld modules state.

         if(::GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, straOld[i], &hmodule) == false || hmodule == nullptr)
         {

            try
            {

               ::LoadLibrary(straOld[i]);

            }
            catch(...)
            {

            }

         }

      }

   }

   return true;

}


#endif



int get_current_process_affinity_order()
{

   return 1;


}


::u64 translate_processor_affinity(int i)
{

   return 1;

}

//#undef ::acmeacmesystem()

//CLASS_DECL_ACME int ui_open_url(const ::scoped_string & scopedstrUrl)
//{
//
//   string strUrl(pszUrl);
//
//   auto uri = ref ___new ::winrt::Windows::Foundation::Uri (strUrl);
//
//   ::winrt::Windows::acmeacmesystem()::Launcher::LaunchUriAsync(uri);
//
//   return 0;
//
//}
//



CLASS_DECL_ACME bool is_shared_library_busy(const string_array & stra)
{

   return true;

}


bool shell_execute_sync(const ::scoped_string & scopedstrFile, const ::scoped_string & scopedstrParams, class time timeTimeout)
{

   return false;

   //return call_sync(pszFile, pszParams, ::file::path(pszFile).folder(), 0, false, (int)timeTimeout.get_total_milliseconds());

}





CLASS_DECL_ACME ::file::path core_app_path(string strApp)
{

   throw ::exception(todo);

   return "";

}



// CLASS_DECL_ACME string xxxget_environment_variable(const ::scoped_string & scopedstrEnvironmentVariable)
// {

//    string str;

//    throw ::exception(todo);

//    return str;

// }


bool set_process_priority(::enum_priority epriority)
{

   //return (::SetPriorityClass(::GetCurrentProcess(), get_os_priority_class(epriority)) != 0);

   return false;


}


