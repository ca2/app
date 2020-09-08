#include "framework.h"





























































CLASS_DECL_AQUA void reg_delete_tree_dup(HKEY hkey, const char * name)
{
   HKEY hkeySub = nullptr;
   if (ERROR_SUCCESS == ::RegOpenKeyW(
      hkey,
      wstring(name),
      &hkeySub))
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



