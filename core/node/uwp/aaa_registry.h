#pragma once


namespace uwp
{

#if false
   class CLASS_DECL_CORE registry :
      virtual public ::object
   {
   public:


      class CLASS_DECL_CORE Key
      {
      public:


         HKEY m_hkey;


         Key();
         Key(HKEY hkey, const ::string & lpcszSubKey, bool bCreate);
         virtual ~Key();
      

         bool OpenKey(HKEY hkey, const ::string & lpcszSubKey, bool bCreate);
         void CloseKey();
         
         bool QueryValue(const ::string & lpcszValueName, string &strVAlue);

         bool QueryValue(const ::string & lpcszValueName, memory & mem);

         bool SetValue(const ::string & lpcszValueName, const ::string & lpcszValue);

         bool DeleteValue(const ::string & lpcszValueName);

         bool DeleteKey();

         ::count EnumKey(string_array & stra);

         ::count EnumValueName(string_array & stra);
         
         operator HKEY();

      };

      registry();
      virtual ~registry();
      /*bool RegQueryValue(
         HKEY hKey,       // handle to key to query
         const unichar * lpSubKey,
                      // name of subkey to query
         CWStr &str);*/

      bool RegQueryValue(
         HKEY hKey,       // handle to key to query
         const char * lpSubKey,
                      // name of subkey to query
         string &str);


      
   };

#endif

} // namespace uwp


