#pragma once


//#include "acme/primitive/collection/string_array.h"
#include "acme/primitive/collection/string_map.h"
#include "app/programming/programming/compiler.h"
#include "apex/filesystem/file/listener.h"


namespace dynamic_source
{

   using library_map = string_map < ::pointer<library >>;


   class CLASS_DECL_APP_PROGRAMMING script_compiler :
      virtual public ::programming::compiler,
      virtual public ::file::listener::base
   {
   protected:

      using ::particle::initialize;
         using programming::compiler::initialize_programming_compiler;

   public:


      enum ecpptype
      {
         cpptype_ds,
         cpptype_source,
         cpptype_include,
      };


      library_map m_mapLib;

//#ifdef WINDOWS
//      string                                    m_strVs;
//      string                                    m_strVsTools;
//      string                                    m_strVCVersion;
//#endif
      //::file::path                              m_pathProjectDir;
      //string                                    m_strDynamicSourceConfiguration;
      //::file::path                              m_strDynamicSourceStage;
      //::file::path                              m_strDynamicSourceStageFolder;


      //string      m_strLibPlatform;


      string_array                                   m_straSync;
//      map_string_to_ptr                         m_mapLib;
      string                                    m_strLibsLibs;
      //string                                    m_strEnv;
      ::pointer<script_manager>                       m_pmanager;
      //string                                    m_strSdk1;
      //string                                    m_strPlatform;
      //string                                    m_strStagePlatform;
      ::file::watch_id                        m_filewatcherid;

      //string                                    m_strPlat1;
      //string                                    m_strPlat2;
      //::file::path                              m_strTime;


      ::pointer < ::mutex >                                     m_pmutex;

      ::pointer < ::mutex >                                     m_pmutexLibrary;

      //::pointer < ::integration::context >                        m_pintegrationcontext;


      script_compiler();
      ~script_compiler() override;


      virtual void initialize_dynamic_source_script_compiler(script_manager * pscriptmanager);
      void prepare_compile_and_link_environment() override;

      void run_persistent();

      virtual void init1();

      bool defer_run_persistent(const ::string &psz);

      bool is_id(const ::string & psz, strsize iLen, const ::string & pszId, strsize iLenId, strsize & iIdLen);
      const char * next_nonspace(const ::string & psz);

      void compile(ds_script * pscript);

      void cppize(ds_script * pscript);
      void cppize(const ::file::path & pszSource,const ::file::path & pszDest,ecpptype enum_type);

      void cppize1(ds_script * pscript);
      void cppize1(const ::file::path & pszSource,const ::file::path & pszDest,ecpptype enum_type);

      string cppize2(const string & pszSource,bool bScript,string_array & straId);

      string get_ds_print(const ::string &psz)   ;

      void folder_watch();

      library & lib(const ::string & pszLibrary);
      void process_include(const ::string & pszInclude);

      //    bool library_DoesMatchVersion();


      void operator()(::file::action * paction) override;


      //void prepare1(const ::string & pszSource, const ::string & pszDest);


      virtual void parse_pstr_set();

      virtual void pstr_set(atom pszTopic,atom idLocale,atom idSchema, const ::string & psz);

   };



} // namespace dynamic_source


