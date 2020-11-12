#include "framework.h"


typedef
LSTATUS
(APIENTRY* LPFN_RegGetValueW) (
   HKEY hkey,
   LPCWSTR pSubKey,

   LPCWSTR pValue,

   u32 dwFlags,
   LPDWORD pdwType,
   PVOID pvData,
   LPDWORD pcbData
   );


LPFN_RegGetValueW g_pfnRegGetValueW = nullptr;


int WinRegGetValueW(HKEY hkey, LPCWSTR pSubKey, LPCWSTR lpValue, ::u32 dwFlags, LPDWORD pdwType, PVOID pvData, LPDWORD pcbData)
{

   if (g_pfnRegGetValueW != nullptr)
   {

      return g_pfnRegGetValueW(hkey, pSubKey, lpValue, dwFlags, pdwType, pvData, pcbData);

   }
   else
   {

      LSTATUS lstatus = RegQueryValueExW(hkey, pSubKey, nullptr, pdwType, (byte*)pvData, pcbData);

      if (lstatus == ERROR_SUCCESS)
      {

         if (pvData != nullptr && (dwFlags & RRF_RT_REG_SZ) != 0 && *pdwType == REG_SZ)
         {
            
            ((WCHAR*)pvData)[*pcbData] = L'\0';

         }

      }

      return lstatus;

   }

}


CLASS_DECL_ACME void reg_delete_tree_dup(HKEY hkey, const char * name)
{
   
   HKEY hkeySub = nullptr;
   
   if (ERROR_SUCCESS == ::RegOpenKeyW(hkey, wstring(name), &hkeySub))
   {
      
      u32 dwAlloc = 1026 * 64;
      
      wchar_t * szKey = (wchar_t *)memory_alloc(dwAlloc * 2);
      
      u32 dwIndex = 0;

      while (ERROR_SUCCESS == ::RegEnumKeyW(hkeySub, dwIndex, szKey, dwAlloc))
      {
         
         reg_delete_tree_dup(hkeySub, string(szKey));
         
         dwIndex++;

      }
      
      memory_free_dbg(szKey, 0);
      
      ::RegCloseKey(hkeySub);

   }

   ::RegDeleteKeyW(hkey, wstring(name));

}


void windows_registry_init()
{

   HMODULE hmoduleAdvApi32 = ::LoadLibraryW(L"AdvApi32");
 
   g_pfnRegGetValueW = (LPFN_RegGetValueW) ::GetProcAddress(hmoduleAdvApi32, "RegGetValueW");

}



