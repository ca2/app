#pragma once



#ifdef WINDOWS_DESKTOP


namespace windows
{


   class CLASS_DECL_ACME registry :
      virtual public ::matter
   {
   public:


      class CLASS_DECL_ACME key
      {
      public:


         HKEY m_hkey;


         key();
         key(HKEY hkey, const char* pcszSubKey, bool bCreate = false) { _open(hkey, pcszSubKey, bCreate); }
         virtual ~key();

      
         operator HKEY();

         void open(HKEY hkey, const char * pcszSubKey, bool bCreate = false);
         ::e_status _open(HKEY hkey, const char* pcszSubKey, bool bCreate = false);

         
         void defer_create(HKEY hkey, const char * pcszSubKey);
         inline ::e_status _defer_create(HKEY hkey, const char* pcszSubKey) { return _open(hkey, pcszSubKey, true); }


         void close();

         
         void value(void * pvalue, const char * pcszValueName, ::u32 & dwType, ::u32 & cbValue);
         ::e_status _value(void * pvalue, const char* pcszValueName, ::u32& dwType, ::u32& cbValue);

         ::e_status _set_value(const void* pvalue, const char* pcszValueName, ::u32 dwType, ::u32 cbValue);


         void value_type_and_size(const char * pcszValueName, ::u32 & dwType, ::u32 & cbValue);
         ::e_status _value_type_and_size(const char* pcszValueName, ::u32& dwType, ::u32& cbValue) { return _value(nullptr, pcszValueName, dwType, cbValue); }


         void get(const char * pcszValueName, ::u32 & dwValue);
         ::e_status _get(const char * pcszValueName, ::u32 & dwValue);

         
         void get(const char * pcszValueName, string & strValue);
         ::e_status _get(const char * pcszValueName, string &strValue);


         void get(const char * pcszValueName, memory & mem);
         ::e_status _get(const char * pcszValueName, memory & mem);


         inline ::payload get(const char* pcszValueName);


         void set(const char * pcszValueName, ::u32 dwValue);
         ::e_status _set(const char * pcszValueName, ::u32 dwValue);


         void set(const char * pcszValueName, const string & strValue);
         ::e_status _set(const char * pcszValueName, const string & strValue);


         void set(const char * pcszValueName, const char * pszValue);
         ::e_status _set(const char * pcszValueName, const char * pszValue);


         void set(const char * pcszValueName, const memory & mem);
         ::e_status _set(const char * pcszValueName, const memory & mem);


         void delete_value(const char * pcszValueName);
         ::e_status _delete_value(const char * pcszValueName);


         void delete_key();
         ::e_status _delete_key();

         
         void ls_key(string_array & stra);
         inline auto ls_key() { string_array stra; ls_key(stra); return stra; }
         ::e_status _ls_key(string_array & stra);


         void ls_value(string_array & stra);
         inline auto ls_value() { string_array stra; ls_value(stra); return stra; }
         ::e_status _ls_value(string_array & stra);


      };

      registry();
      virtual ~registry();

      


      
   };


} // namespace windows



#endif



