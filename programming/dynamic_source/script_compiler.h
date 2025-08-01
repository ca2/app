#pragma once


//#include "acme/prototype/collection/string_array.h"
#include "acme/prototype/collection/string_map.h"
#include "app/programming/programming/compiler.h"
#include "acme/filesystem/watcher/listener.h"


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
      //::file::path                              m_pathProjectFolder;
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
      ::pointer < ::file::watch >                        m_filewatcherid;

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

      void destroy() override;

      bool defer_run_persistent(const ::scoped_string & scopedstr);

      bool is_id(const ::scoped_string & scopedstr, character_count iLen, const ::scoped_string & scopedstrId, character_count iLenId, character_count & iIdLen);
      const_char_pointer next_nonspace(const ::scoped_string & scopedstr);

      void compile(ds_script * pscript);

      void cppize(ds_script * pscript);
      void cppize(const ::file::path & pathSource,const ::file::path & pathDest,ecpptype enum_type);

      void cppize1(ds_script * pscript);
      void cppize1(const ::file::path & pathSource,const ::file::path & pathDest,ecpptype enum_type);

      string cppize2(const ::scoped_string & scopedstrSource,bool bScript,string_array & straId);

      string get_ds_print(const ::scoped_string & scopedstr)   ;

      void folder_watch();

      library & lib(const ::scoped_string & scopedstrLibrary);
      void process_include(const ::scoped_string & scopedstrInclude);

      //    bool library_DoesMatchVersion();


      void operator()(::file::action * paction) override;


      //void prepare1(const ::scoped_string & scopedstrSource, const ::scoped_string & scopedstrDest);


      virtual void parse_pstr_set();

      virtual void pstr_set(const ::atom & atomTopic,atom idLocale,atom idSchema, const ::scoped_string & scopedstr);

   };



} // namespace dynamic_source


