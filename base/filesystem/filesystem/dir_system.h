#pragma once


class CLASS_DECL_AURA dir_system :
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


   dir_system();
   virtual ~dir_system();


   virtual ::estatus initialize(::object * pobjectContext) override;

   virtual ::estatus init_system();



   virtual bool update_module_path();



};



