#pragma once


////#include "acme/prototype/prototype/object.h"
//#include "acme/filesystem/filesystem/path.h"


class CLASS_DECL_ACME directory_system :
   virtual public ::object
{
public:


   ::file::path                  m_pathLocalAppMatterFolder;
   ::file::path                  m_pathLocalAppMatterCacheFolder;

   //::pointer<::file::watcher>   m_pfilewatcher;

   ::file::path                  m_pathAppData;
   ::file::path                  m_pathDefaultAppData;

   string                        m_strApiCc;

   ::file::path                  m_pathCa2Config;
   //::file::path                  m_pathModule;
   ::file::path                  m_pathHome;
   ::file::path                  m_pathInstall;

   bool                          m_bMatterFromHttpCache;
   bool                          m_bMatterFromResource;


   ::file::path                  m_pathUpload;


   directory_system();
   ~directory_system() override;


   virtual void initialize(::particle * pparticle) override;

   virtual void init_system();

   virtual void term_system();

   void finalize() override;

   virtual ::file::path compute_default_app_data_path();


};



