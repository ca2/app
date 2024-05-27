// Created by camilo on 2022-10-09 20:55 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/parallelization/mutex.h"
#include "acme/platform/library.h"
#include "acme/platform/release_time_for_project.h"
#include "acme/primitive/collection/atom_map.h"
#include "acme/primitive/collection/string_map.h"
//#include "acme/primitive/primitive/pointer.h"


#ifdef LINUX


#endif


class main;


namespace acme
{


   using library_map = string_map < ::pointer < ::acme::library > >;

   class acme;

} // namespace acme


namespace factory
{

   using factory_pointer = ::pointer < ::factory::factory >;
   using factory_map = ::string_map < factory_pointer >;
   using component_factory_map = ::string_map < factory_map >;

} // namespace factory


namespace platform
{


   class CLASS_DECL_ACME platform :
      virtual public ::particle
   {
   public:


      //static platform * s_pplatform;

      ::acme::acme *                                  m_pacme;

      ::critical_section                              m_criticalsection;

      ::e_display                                     m_edisplay;
      ::e_activation                                  m_eactivativation;
      int                                             m_argc = 0;
      char ** m_args = nullptr;
      char ** m_envp = nullptr;

#ifdef WINDOWS

      wchar_t ** m_wargs = nullptr;
      wchar_t ** m_wenvp = nullptr;

      hinstance                                       m_hinstanceThis = nullptr;
      hinstance                                       m_hinstancePrev = nullptr;
      int                                             m_nCmdShow = -1;

#endif

#ifdef LINUX

      ::locale_t                                      m_localeC;

#endif

#ifdef __APPLE__

      void * m_pApplicationDelegate = nullptr;

#endif

      ::block                                         m_blockMatter;
      ::acme::library_map                             m_mapLibrary;
      ::factory::factory_pointer                      m_pfactory;
      ::factory::factory_map                          m_factorymap;
      ::factory::component_factory_map                m_componentfactorymap;
      ::pointer < ::acme::system >                    m_psystem;

      int                                             m_iProcessStatus = 0;

      ::critical_section                              m_criticalsectionTask;
      ::index_array                                   m_iaTaskIndex;
      bool                                            m_bVerboseLog;


      ::acme::application * m_pacmeapplication;


      ::critical_section m_criticalsectionSystemHeap;


      ::critical_section m_criticalsectionChannel;
      ::critical_section m_criticalsectionSequence;

      bool m_bConsole;



      ::critical_section * channel_critical_section()
      {

         return &m_criticalsectionChannel;

      }


      ::critical_section m_criticalsectionMessageDispatch;


      ::critical_section * message_dispatch_critical_section()
      {

         return &m_criticalsectionMessageDispatch;

      }


      ::critical_section* sequence_critical_section()
      {

         return &m_criticalsectionSequence;

      }

#if defined(LINUX) || defined(__APPLE__) || defined(ANDROID) || defined(FREEBSD) || defined(OPENBSD)

      ::critical_section m_criticalsectionTz;

      ::critical_section m_criticalsectionThreadHandleLock;

#endif // defined(LINUX) || defined(__APPLE__)


      ::critical_section m_criticalsectionGlobals;


      ::critical_section m_criticalsectionFactory;



#if !defined(WINDOWS)

      ::critical_section m_criticalsectionDemangle;


#endif


      //::critical_section m_criticalsectionSystemHeap;


#ifdef WINDOWS


      ::critical_section m_criticalsectionSymDbgHelp;


#endif


      //::critical_section m_criticalsectionMessageDispatch;
      //
      //
      //::critical_section * message_dispatch_critical_section() { return &m_criticalsectionMessageDispatch; }
      //




#ifdef ANDROID

      ::critical_section m_criticalsectionOutputDebugStringA;


#endif


      //#ifdef __APPLE__
      //
      //
      //      ::critical_section m_criticalsectionCvt;
      //
      //
      //      ::critical_section* cvt_critical_section() { return &m_criticalsectionCvt; }
      //
      //#endif




      class ::time                        m_timeStart;

      ::memory_counter *                  m_pmemorycounter;


      bool                                m_bOutputDebugString;

      string                                          m_strCommandLine;


      platform(::acme::acme * pacme);
      ~platform();


      using particle::initialize;

#if defined(WINDOWS) && defined(UNICODE)

      void initialize(int argc, wchar_t * argv[], wchar_t * envp[]);

      void initialize(hinstance hinstanceThis, hinstance hinstancePrev, wchar_t * pCmdLine, int nCmdShow);

#else

      void initialize(int argc, platform_char ** argv, platform_char ** envp);

#endif


      void platform_initialize();
      void platform_finalize();


      void set_args(int argc, char ** argv, wchar_t ** wargv);

      string _get_argv(::collection::index iArg) const;
      ::collection::count get_argc();
      int * get_pargc();
      char *** get_pargv();
      char ** get_argv();

#ifdef WINDOWS

      wchar_t *** get_pwargv();
      wchar_t ** get_wargv();

#endif

      bool is_verbose_log() const;

      inline ::collection::count _get_argc() const { return m_argc; }

      string get_executable() const;

      string get_argument1(::collection::index iArgument) const;

      bool has_argument(const ::scoped_string & scopedArgument) const;

      inline ::collection::count get_argument_count1() const { return _get_argc() - 1; }

      string_array get_arguments();

      ::string get_argument_begins_eat(const ::scoped_string & scopedstrPrefix);

      ::string_array get_argument_options(const ::scoped_string & scopedstrArgument);

      string get_arg(::collection::index i) const;
      string get_env(const ::scoped_string & scopedstrVariableName) const;


      int get_status();
      void set_status(int iStatus);


      virtual void set_resource_block(const char * pstart, const char * pend);

      void defer_initialize_platform();

      void factory_initialize();
      void factory_terminate();


      void delete_all_release_on_end();


      ::acme::acme * acme() const { return ((platform *)this)->m_pacme; }


      ::factory::factory_pointer & factory();
      ::factory::factory_pointer & factory(const ::string & strLibrary);
      ::factory::factory_pointer & factory(const ::string & strComponent, const ::string & strImplementation);


      ::pointer<::factory::factory_item_interface> & get_factory_item(const ::atom & atom, const ::atom & atomSource);


      bool has_factory_item(const ::atom & atom);


      void set_factory(const ::atom & atom, const ::pointer<::factory::factory_item_interface> & pfactory);


      void set_factory_from(const ::atom & atom, const ::atom & atomSource, const ::pointer<::factory::factory_item_interface> & pfactory);


      template < typename TYPE, typename BASE >
      void add_factory_item(const ::atom & atom)
      {

         set_factory(atom, __allocate< ::factory::factory_item < TYPE, BASE > >());

      }


      ::factory::factory * get_factory(const ::atom & atomSource);



      //virtual void set_factory_global(const ::string &pszComponent, const ::string &pszImplementation);

      //virtual ::pointer<::acme::library> open_component_library(const ::string &pszComponent, const ::string &pszImplementation);

      virtual ::pointer<::acme::library> create_library(const ::string & strLibrary);

      virtual ::pointer<::acme::library> & library(const ::string & str);

      //virtual ::pointer<::acme::library>& library(const ::string& strComponent, const ::string& strImplementation);

      virtual ::pointer<::factory::factory> & impact_factory(const ::string & strComponent, const ::string & strImplementation);

      //void initialize_memory_counter();
      //void finalize_memory_counter();

      //::memory_counter * get_memory_counter();



      //virtual ::acme::system * __get_system() = 0;
      class ::time start_nanosecond();



      ::particle * ui_destroyed_synchronization();



#if defined(LINUX) || defined(__APPLE__) || defined(ANDROID) || defined(FREEBSD) || defined(OPENBSD)

      ::critical_section * tz_critical_section() { return &m_criticalsectionTz; }

      ::critical_section * thread_handle_lock_critical_section() { return &m_criticalsectionThreadHandleLock; }


#endif // defined(LINUX) || defined(__APPLE__)

      critical_section * globals_critical_section() { return &m_criticalsectionGlobals; }



      critical_section * factory_critical_section() { return &m_criticalsectionFactory; }




#if !defined(WINDOWS)

      ::critical_section * demangle_critical_section() { return &m_criticalsectionDemangle; }


#endif

      //::critical_section* system_heap_critical_section() { return &m_criticalsectionSystemHeap; }

#ifdef WINDOWS



      ::critical_section * sym_dbg_help_critical_section() { return &m_criticalsectionSymDbgHelp; }


#endif


#ifdef ANDROID


      ::critical_section * output_debum_strinm_a_critical_section() { return &m_criticalsectionOutputDebugStringA; }

#endif

#ifdef __APPLE__


      //::critical_section m_criticalsectionCvt;


      ::critical_section * cvt_critical_section();

#endif

      //pass_through_function m_passthroughfunction;


      ::collection::index task_index(itask_t itask, bool bAddIfNotInList = false);


      //pass_through_function &  __call__new_pass_through_function() { return m_passthroughfunction; }


      //platform * __call__add_referer2(const ::reference_referer & referer) const;
      release_time_for_project as_release_time_for_project(const char* pszStatic);

       
       
       
       // [HERE]
       //  __node_library should be here at acme
       //
       //  -- e.g. cannot lie inside a plugin,
       // because it is used to load a plugin
       //
       virtual void* operating_system_library_open(const ::file::path & path, string& strMessage);

 #if defined FREEBSD || defined(OPENBSD)
       virtual string operating_system_library_is_loaded(const ::file::path &path);
 #endif // FREEBSD
    virtual void* operating_system_library_touch(const ::file::path & path, string& strMessage);
       virtual void* operating_system_library_open_ca2(const ::file::path & path, string& strMessage);
       virtual bool operating_system_library_close(void* plibrary);
       virtual void* operating_system_library_raw_get(void* plibrary, const ::scoped_string & scopedstrEntryName);


   };


   //template < typename SYSTEM >
   //class platform_impl :
   //   virtual public ::platform::platform
   //{
   //public:


   //   SYSTEM      m_system;

   //   ::acme::system * __get_system() override { return &m_system; }


   //};


   //namespace platform
   //{


   inline ::platform::platform * get() { return ::acme::get() ? ::acme::get()->platform() : nullptr; }


} // namespace platform


CLASS_DECL_ACME ::string as_string(const ::release_time_for_project& releasetimeforproject);



