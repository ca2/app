#pragma once


namespace dynamic_source
{


   class CLASS_DECL_APP_PROGRAMMING library :
      virtual public ::object
   {
   public:


      ::pointer < ::mutex >                                     m_pmutex;
      string                                    m_strError;
      ::string_stream                               m_memfileError;
      ::string_stream                               m_memfileLibError;
      ::file::listing                           m_straLibSourcePath;
      ::file::path_array                             m_straLibSourceRelPath;
      ::file::path_array                             m_straLibCppPath;
      ::file::listing                           m_straLibIncludePath;
      ::file::path_array                             m_straLibIncludeRelPath;
      ::file::path_array                             m_straLibHppPath;
      ::file::path                              m_strLibraryPath;

      ::duration                                    m_durationLastLibraryVersionCheck;
      bool                                      m_bLastLibraryVersionCheck;
      ::pointer<::acme::library>               m_plibraryLib;


      raw_array < __time_t >                    m_ftaLibCreation;
      raw_array < __time_t >                    m_ftaLibAccess;
      raw_array < __time_t >                    m_ftaLibModified;

      
      library(::object* pparticle);
      ~library() override;


      void load_library();
      void unload_library();


   };


} // namespace dynamic_source



