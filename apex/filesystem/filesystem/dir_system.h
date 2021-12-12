#pragma once


class CLASS_DECL_APEX dir_system :
   virtual public ::object
{
public:


   ::file::path                  m_pathCa2;
   ::file::path                  m_pathLocalAppMatterFolder;
   ::file::path                  m_pathLocalAppMatterCacheFolder;

   __pointer(::file::watcher)    m_pfilewatcher;

   ::file::path                  m_pathAppData;
   ::file::path                  m_pathDefaultAppData;

   string                        m_strApiCc;

   ::file::path                  m_pathCa2Config;
   ::file::path                  m_pathCa2Module;
   ::file::path                  m_pathModule;
   ::file::path                  m_pathHome;
   ::file::path                  m_pathInstall;

   bool                          m_bMatterFromHttpCache;
   bool                          m_bMatterFromResource;


   dir_system();
   virtual ~dir_system();


   virtual ::e_status initialize(::object * pobject) override;

   virtual ::e_status init_system();



   //virtual bool update_module_path();

   //virtual ::string dir_root();


   //virtual ::file::path get_memory_map_base_folder_path() const;

   //virtual ::file::path home();


   //virtual ::file::path program_data();

   //virtual ::file::path roaming();
   //virtual ::file::path application_installer_folder(const ::file::path& pathExe, string strAppId, const char* pszPlatform, const char* pszConfiguration, const char* pszLocale, const char* pszSchema);

   //virtual ::file::path get_application_path(string strAppId, const char* pszPlatform, const char* pszConfiguration) ;

   //virtual ::file::path get_last_run_application_path_file(string strAppId);

   //virtual ::file::path get_last_run_application_path(string strAppId);


};



