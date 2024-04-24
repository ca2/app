#pragma once

/*
#include <sys/stat.h>


#if defined(APPLEOS)


#if defined(_LP64)


#define stat64 stat


#endif


#endif
*/


namespace dynamic_source
{


   class CLASS_DECL_APP_PROGRAMMING library_class :
      virtual public ::object
   {
   public:


      ::string_stream                            m_memfileError;
      string                                 m_strName;
      string_array                                m_straSourcePath;
      string_array                                m_straCppPath;
      string                                 m_strLibraryPath;
      ::pointer<::acme::library>                      m_plibrary;

      array < __time_t, __time_t & >         m_ftaCreation;
      array < __time_t, __time_t & >         m_ftaAccess;
      array < __time_t, __time_t & >         m_ftaModified;

      ::pointer<script_manager>                    m_pmanager;



      library_class(::particle * pparticle);
      ~library_class();





      bool DoesMatchVersion();
      void Load();
      void Unload();


      //virtual ::aura::application * get_app() const override;


   };


} // namespace dynamic_source


