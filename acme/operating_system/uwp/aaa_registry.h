#pragma once


namespace universal_windows
{

#if false
   class CLASS_DECL_ACME registry :
      virtual public ::matter
   {
   public:


      class CLASS_DECL_ACME Key
      {
      public:


         HKEY m_hkey;


         Key();
         Key(HKEY hkey, const_char_pointer lpcszSubKey, bool bCreate);
         virtual ~Key();
      

         bool OpenKey(HKEY hkey, const_char_pointer lpcszSubKey, bool bCreate);
         void CloseKey();
         
         bool QueryValue(const_char_pointer lpcszValueName, string &strVAlue);

         bool QueryValue(const_char_pointer lpcszValueName, memory & mem);

         bool SetValue(const_char_pointer lpcszValueName, const_char_pointer lpcszValue);

         bool DeleteValue(const_char_pointer lpcszValueName);

         bool DeleteKey();

         ::collection::count EnumKey(string_array_base & stra);

         ::collection::count EnumValueName(string_array_base & stra);
         
         operator HKEY();

      };

      registry();
      virtual ~registry();
      /*bool RegQueryValue(
         HKEY hKey,       // handle to key to query
         const wide_character * lpSubKey,
                      // name of subkey to query
         CWStr &str);*/

      bool RegQueryValue(
         HKEY hKey,       // handle to key to query
         const_char_pointer lpSubKey,
                      // name of subkey to query
         string &str);


      
   };

#endif

} // namespace universal_windows


