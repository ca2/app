#pragma once


#include "acme/filesystem/filesystem/listing.h"



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
      ::file::listing_base                           m_straLibSourcePath;
      ::file::path_array_base                             m_straLibSourceRelPath;
      ::file::path_array_base                             m_straLibCppPath;
      ::file::listing_base                           m_straLibIncludePath;
      ::file::path_array_base                             m_straLibIncludeRelPath;
      ::file::path_array_base                             m_straLibHppPath;
      ::file::path                              m_strLibraryPath;

      class ::time                                    m_timeLastLibraryVersionCheck;
      bool                                      m_bLastLibraryVersionCheck;
      ::pointer<::acme::library>               m_plibraryLib;


      raw_array < class ::time >                    m_ftaLibCreation;
      raw_array < class ::time >                    m_ftaLibAccess;
      raw_array < class ::time >                    m_ftaLibModified;

      
      library(::particle * pparticle);
      ~library() override;


      void load_library();
      void unload_library();


   };


} // namespace dynamic_source



