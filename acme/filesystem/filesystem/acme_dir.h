// Create on 2021-03-20 23:59 <3ThomasBS_
#pragma once


class CLASS_DECL_ACME acme_dir :
   virtual public ::matter
{
public:


   ::PLATFORM_NAMESPACE::acme_dir *          m_pplatformdir;


   ::file::path   m_pathInstallFolder;




   virtual ::file::path install();
   virtual ::file::path default_install();
   virtual ::file::path beforeca2();
   virtual ::file::path module();
   virtual ::file::path relative(::file::path path);
   virtual ::file::path app_relative();
   virtual ::file::path appdata(); // appdata
   virtual ::file::path archive();
   virtual ::file::path tool();
   virtual ::file::path public_system();
   virtual ::file::path system();
   virtual ::file::path config();
   virtual ::file::path local();
   virtual ::file::path sensitive();
   virtual ::file::path localconfig(); // #vcs C:\\Users\\user\\AppData\\Roaming\\ca2\\localconfig
   virtual ::file::path ca2roaming(); // writable root (non-bin, non-exe)
   virtual ::file::path ca2appdata(); // writable root (non-bin, non-exe)
   virtual ::file::path roaming();
   virtual ::file::path program_data();
   virtual ::file::path public_root(); // writable common root (non-bin, non-exe)
   virtual ::file::path bookmark();
   virtual ::file::path home();
   virtual ::file::path pathfind(const string& pszEnv, const string& pszTopic, const string& pszMode);
   virtual ::file::path program_files_x86();
   virtual ::file::path program_files();
   //virtual ::file::path program_data();
   virtual ::file::path stage(string strAppId, string strPlatform, string strConfiguration);
   virtual ::file::path sys_temp();
   virtual ::string dir_root();
   //virtual ::file::path home();
   //virtual ::file::path program_data();
   //virtual ::file::path roaming();
   virtual ::file::path get_memory_map_base_folder_path();
   //virtual ::file::path ca2appdata();
   //virtual ::file::path ca2roaming();
   //virtual ::file::path localconfig();
   virtual string system_short_name();


   //::file::path inplace_install(string strAppId, string strPlatform, string strConfiguration);
   //virtual ::file::path inplace_install(string strAppId, string strPlatform, string strConfiguration);
   virtual ::file::path inplace_install(string strAppId, string strPlatform, string strConfiguration);
   virtual ::file::path inplace_matter_install(string strAppId, string strPlatform, string strConfiguration);


   virtual void set_path_install_folder(const char* pszPath);

   //virtual ::file::path pathfind(const string& pszEnv, const string& pszTopic, const string& pszMode);

   virtual ::file::path machine_event_file_path();

   virtual ::file::path user_appdata_local();


};