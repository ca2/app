#include "framework.h"
//#include "uwp.h"


namespace uwp
{

#if FALSE
   registry::registry()
   {

   }

   registry::~registry()
   {

   }

   bool registry::RegQueryValue(
   HKEY hKey,
   const char * lpSubKey,
   string &str)
   {
      ::u32 cbValue;
      ::u32 dwType;
      if(ERROR_SUCCESS != ::RegQueryValueEx(hKey, lpSubKey, nullptr, &dwType, nullptr, &cbValue))
         return false;
      if(dwType != REG_SZ)
         return false;
      char * lpsz = str.GetBuffer(cbValue);
      if(ERROR_SUCCESS != ::RegQueryValueEx(hKey, lpSubKey, nullptr, &dwType, (LPBYTE) lpsz, &cbValue))
      {
         str.ReleaseBuffer();
         return false;
      }
      str.ReleaseBuffer();
      return true;

   }


   registry::Key::Key()
   {
      m_hkey = nullptr;
   }

   registry::Key::Key(HKEY hkey, const char * lpcszSubKey, bool bCreate)
   {
      m_hkey = nullptr;
      OpenKey(hkey, lpcszSubKey, bCreate);
   }

   registry::Key::~Key()
   {
      if(m_hkey != nullptr)
      {
         CloseKey();
      }
   }

   bool registry::Key::OpenKey(HKEY hkey, const char * lpcszSubKey, bool bCreate)
   {
      if(bCreate)
      {
         return ERROR_SUCCESS == ::RegCreateKey(
                hkey,
                lpcszSubKey,
                &m_hkey);

      }
      else
      {
         return ERROR_SUCCESS == ::RegOpenKey(
                hkey,
                lpcszSubKey,
                &m_hkey);
      }
   }

   void registry::Key::CloseKey()
   {
      if(m_hkey != nullptr)
      {
         if(ERROR_SUCCESS == ::RegCloseKey(
               m_hkey))
         {
            m_hkey = nullptr;
         }
      }
   }

   bool registry::Key::QueryValue(
   const char * lpcszValueName,
   string &str)
   {
      ::u32 cbValue;
      ::u32 dwType;
      if(ERROR_SUCCESS != ::RegQueryValueEx(m_hkey, lpcszValueName, nullptr, &dwType, nullptr, &cbValue))
         return false;
      if(dwType != REG_SZ)
         return false;
      char * lpsz = str.GetBuffer(cbValue);
      if(ERROR_SUCCESS != ::RegQueryValueEx(m_hkey, lpcszValueName, nullptr, &dwType, (LPBYTE) lpsz, &cbValue))
      {
         str.ReleaseBuffer();
         return false;
      }
      str.ReleaseBuffer();
      return true;

   }

   bool registry::Key::QueryValue(const char * lpcszValueName, memory & mem)
   {
      ::u32 cbValue;
      ::u32 dwType;
      if(ERROR_SUCCESS != ::RegQueryValueEx(m_hkey, lpcszValueName, nullptr, &dwType, nullptr, &cbValue))
         return false;
      if(dwType != REG_BINARY)
         return false;
      mem.set_size(cbValue);
      if(ERROR_SUCCESS != ::RegQueryValueEx(m_hkey, lpcszValueName, nullptr, &dwType, (LPBYTE) mem.get_data(), &cbValue))
      {
         mem.set_size(0);
         return false;
      }
      return true;

   }

   bool registry::Key::SetValue(
   const char * lpcszValueName,
   const char * lpcszValue)
   {
      return ERROR_SUCCESS ==
             RegSetValueEx(m_hkey, lpcszValueName, nullptr, REG_SZ,
                           (LPBYTE)lpcszValue, (lstrlen(lpcszValue)+1)*sizeof(char));
   }


   bool registry::Key::DeleteValue(
   const char * lpcszValueName)
   {
      return ERROR_SUCCESS ==
             ::RegDeleteValue(m_hkey, (char *)lpcszValueName);
   }

   bool registry::Key::DeleteKey()
   {
      ASSERT(FALSE);
      // please verify if
      // using nullptr for the value parameter
      // deletes the key.
      return ERROR_SUCCESS ==
             ::RegDeleteKey(m_hkey, nullptr);
   }

   ::count registry::Key::EnumKey(string_array & stra)
   {
      ::u32 dwMaxSubKeyLen;
      RegQueryInfoKey(
      m_hkey,
      nullptr,
      nullptr,
      nullptr,
      nullptr,
      &dwMaxSubKeyLen,
      nullptr,
      nullptr,
      nullptr,
      nullptr,
      nullptr,
      nullptr);
      int iSize = max(dwMaxSubKeyLen, 1024);
      char *buf = (char *) malloc(iSize);
      int iKey = 0;
      while(::RegEnumKey(m_hkey, iKey, buf, iSize) == ERROR_SUCCESS)
      {
         stra.add(buf);
         iKey++;
      }
      free(buf);
      return iKey;
   }


   registry::Key::operator HKEY()
   {
      return m_hkey;
   }

   ::count registry::Key::EnumValueName(string_array & stra)
   {
      ::u32 dwMaxValueNameLen = 16384;
      char * pszBuf = (char *) malloc(dwMaxValueNameLen);
      ::i32 l;
      ::u32 dwIndex = 0;
      ::u32 dwLen = dwMaxValueNameLen;
      while(ERROR_SUCCESS == (l = RegEnumValue(
                                  m_hkey,
                                  dwIndex,
                                  pszBuf,
                                  &dwLen,
                                  nullptr,
                                  nullptr,
                                  nullptr,
                                  nullptr)))
      {
         stra.add(pszBuf);
         dwIndex++;
         dwLen = dwMaxValueNameLen;
      }
      free(pszBuf);
      return stra.get_count();
   }
#endif

} // namespace uwp


