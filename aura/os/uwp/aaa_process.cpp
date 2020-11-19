#include "framework.h"
//#include "uwp.h"
//#include <Shellapi.h>
//#include <string.h>

#ifdef WINDOWS_DESKTOP

CLASS_DECL_BOOT int call_async(
const char * pszPath,
const char * pszParam,
const char * pszDir,
int iShow)
{

   SHELLEXECUTEINFOA infoa;

   __memset(&infoa, 0, sizeof(infoa));

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
CLASS_DECL_BOOT u32 call_sync(const char * pszPath, const char * pszParam, const char * pszDir, ::edisplay edisplay, const ::duration & durationTimeout, ::property_set & set)
{

   SHELLEXECUTEINFOA infoa;

   __memset(&infoa, 0, sizeof(infoa));

   infoa.cbSize         = sizeof(infoa);
   infoa.lpFile         = pszPath;
   infoa.lpParameters   = pszParam;
   infoa.lpDirectory    = pszDir;
   infoa.nShow          = iShow;

   infoa.fMask |= SEE_MASK_NOCLOSEPROCESS | SEE_MASK_NOASYNC | SEE_MASK_FLAG_NO_UI;


   ::ShellExecuteExA(&infoa);

   ::u32 dwExitCode;

   int iTry = 0;

   while(iRetry < 0 || iTry <= iRetry)
   {
      if(!GetExitCodeProcess(infoa.hProcess, &dwExitCode))
         break;
      if(dwExitCode != STILL_ACTIVE)
         break;
      millis_sleep(100);
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

bool process_modules(string_array & stra, ::u32 processID)
{

   HANDLE hProcess;

   ::u32 cbNeeded;

   unsigned int i;

   hProcess = OpenProcess( PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processID );

   if (nullptr == hProcess)
      return false;

   const int iMaxModuleCount = 1024 * 8;

   HMODULE * hMods = new HMODULE[iMaxModuleCount];

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

bool load_modules_diff(string_array & straOld, string_array & straNew, const char * pszExceptDir)
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

         if(ansi_compare_ci(straOld[i], straNew[j]) == 0)
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

         if(::GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, straOld[i], &hmodule) == FALSE || hmodule == nullptr)
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



#undef System

CLASS_DECL_AURA int ui_open_url(const char * pszUrl)
{

   string strUrl(pszUrl);

   auto uri = ref new Windows::Foundation::Uri(strUrl);

   Windows::System::Launcher::LaunchUriAsync(uri);

   return 0;

}




CLASS_DECL_AURA bool is_shared_library_busy(const string_array & stra)
{

   return true;

}




bool shell_execute_sync(const char * pszFile, const char * pszParams, ::duration durationTimeout)
{

   return false;

   //return call_sync(pszFile, pszParams, ::file::path(pszFile).folder(), 0, false, (int)durationTimeout.get_total_milliseconds());

}





CLASS_DECL_AURA ::file::path core_app_path(string strApp)
{

   throw todo();

}

