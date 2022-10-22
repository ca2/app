#pragma once


class CLASS_DECL_APEX dir_system :
   virtual public ::object
{
public:


   ::file::path                  m_pathLocalAppMatterFolder;
   ::file::path                  m_pathLocalAppMatterCacheFolder;

   ::pointer<::file::watcher>   m_pfilewatcher;

   ::file::path                  m_pathAppData;
   ::file::path                  m_pathDefaultAppData;

   string                        m_strApiCc;

   ::file::path                  m_pathCa2Config;
   ::file::path                  m_pathModule;
   ::file::path                  m_pathHome;
   ::file::path                  m_pathInstall;

   bool                          m_bMatterFromHttpCache;
   bool                          m_bMatterFromResource;


   ::file::path                  m_pathUpload;


   dir_system();
   ~dir_system() override;


   virtual void initialize(::object * pobject) override;

   virtual void init_system();

   virtual ::file::path compute_default_app_data_path();


};



