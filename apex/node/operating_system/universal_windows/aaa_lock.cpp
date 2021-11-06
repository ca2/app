#include "framework.h"
//#include "universal_windows.h"
int _c_lock_is_active(const char * pszName)
{

   HANDLE h;

   if(_c_lock(pszName, &h))
   {
      _c_unlock(&h);
      return false;
   }

   return true;

}


int _c_lock(const char * pszName, void ** pdata)
{
#ifdef _UWP
   wstring wstrName(pszName);
   HANDLE hmutex = ::CreateMutexEx(nullptr, wstrName, 0, SYNCHRONIZE);
#else
   HANDLE hmutex = ::CreateMutex(nullptr, false, pszName);
#endif
   if(::GetLastError() == ERROR_ALREADY_EXISTS)
   {
      ::CloseHandle(hmutex);
      return 0;
   }
   if(hmutex == INVALID_HANDLE_VALUE)
      return 0;

   HANDLE * phandle = new HANDLE;
   *phandle = hmutex;
   *pdata = phandle;

   return 1;

}


int _c_unlock(void ** pdata)
{

   HANDLE * phandle = (HANDLE *) *pdata;

   ::CloseHandle(*phandle);

   *phandle = nullptr;

   delete phandle;

   *pdata = nullptr;

   return 1;

}
