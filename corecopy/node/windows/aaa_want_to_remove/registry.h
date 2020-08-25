#pragma once



#ifdef WINDOWS_DESKTOP


namespace windows
{


   class CLASS_DECL_CORE registry :
      virtual public ::object
   {
   public:


      class CLASS_DECL_CORE key
      {
      public:


         HKEY m_hkey;


         key();
         key(HKEY hkey, const char* pcszSubKey, bool bCreate = false) { _open(hkey, pcszSubKey, bCreate); }
         virtual ~key();

      
         operator HKEY();

         void open(HKEY hkey, const char * pcszSubKey, bool bCreate = false);
         estatus _open(HKEY hkey, const char* pcszSubKey, bool bCreate = false);

         
         void defer_create(HKEY hkey, const char * pcszSubKey);
         inline estatus _defer_create(HKEY hkey, const char* pcszSubKey) { return _open(hkey, pcszSubKey, true); }


         void close();

         
         void value(void * pvalue, const char * pcszValueName, DWORD & dwType, DWORD & cbValue);
         estatus _value(void * pvalue, const char* pcszValueName, DWORD& dwType, DWORD& cbValue);

         estatus _set_value(const void* pvalue, const char* pcszValueName, DWORD dwType, DWORD cbValue);


         void value_type_and_size(const char * pcszValueName, DWORD & dwType, DWORD & cbValue);
         estatus _value_type_and_size(const char* pcszValueName, DWORD& dwType, DWORD& cbValue) { return _value(nullptr, pcszValueName, dwType, cbValue); }


         void get(const char * pcszValueName, DWORD & dwValue);
         estatus _get(const char * pcszValueName, DWORD & dwValue);

         
         void get(const char * pcszValueName, string & strValue);
         estatus _get(const char * pcszValueName, string &strValue);


         void get(const char * pcszValueName, memory & mem);
         estatus _get(const char * pcszValueName, memory & mem);


         inline var get(const char* pcszValueName);


         void set(const char * pcszValueName, DWORD dwValue);
         estatus _set(const char * pcszValueName, DWORD dwValue);


         void set(const char * pcszValueName, const string & strValue);
         estatus _set(const char * pcszValueName, const string & strValue);


         void set(const char * pcszValueName, const char * pszValue);
         estatus _set(const char * pcszValueName, const char * pszValue);


         void set(const char * pcszValueName, const memory & mem);
         estatus _set(const char * pcszValueName, const memory & mem);


         void delete_value(const char * pcszValueName);
         estatus _delete_value(const char * pcszValueName);


         void delete_key();
         estatus _delete_key();

         
         void ls_key(string_array & stra);
         inline auto ls_key() { string_array stra; ls_key(stra); return stra; }
         estatus _ls_key(string_array & stra);


         void ls_value(string_array & stra);
         inline auto ls_value() { string_array stra; ls_value(stra); return stra; }
         estatus _ls_value(string_array & stra);


      };

      registry();
      virtual ~registry();

      


      
   };


} // namespace windows



#endif



