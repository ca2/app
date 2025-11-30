// Created by camilo on 2022-10-09 20:55 <3ThomasBorregaardSorensen!!
#pragma once



//#include "acme/constant/windowing.h"
#include "acme/parallelization/mutex.h"
#include "acme/parallelization/task.h"
#include "acme/parallelization/types.h"
#include "acme/platform/library.h"
#include "acme/platform/release_time_for_project.h"
#include "acme/prototype/collection/atom_map.h"
#include "acme/prototype/collection/string_map.h"
#include "acme/user/user/activation.h"


#ifdef LINUX


#endif


class main;


namespace acme
{


   using library_map = string_map_base < ::pointer < ::acme::library > >;

   class acme;

} // namespace acme


namespace factory
{

   using factory_pointer = ::pointer < ::factory::factory >;
   using factory_map = ::string_map_base < factory_pointer >;
   using component_factory_map = ::string_map_base < factory_map >;

} // namespace factory


namespace platform
{
   

   class CLASS_DECL_ACME platform :
      virtual public ::acme::acme,
      virtual public ::particle
   {
   public:


      bool                                            m_bConsole : 1;


      static ::platform::platform *                   s_pplatform;

      //::acme::acme *                                m_pacme;

      ::critical_section                              m_criticalsection;

      ::e_display                                     m_edisplay;
      ::user::e_activation                            m_eactivation;
      int                                             m_argc = 0;
      char **                                         m_args = nullptr;
      char **                                         m_envp = nullptr;
      ::platform::system *                            m_psystem;
      //int m_iExitCode;

#ifdef WINDOWS

      wchar_t **                                      m_wargs = nullptr;
      wchar_t **                                      m_wenvp = nullptr;

      hinstance                                       m_hinstanceThis = nullptr;
      hinstance                                       m_hinstancePrev = nullptr;
      int                                             m_nCmdShow = -1;

#endif

#ifdef LINUX

      ::locale_t                                      m_localeC;

#endif

#ifdef __APPLE__

      void *                                          m_pApplicationDelegate = nullptr;

#endif



#if defined(LINUX) || defined(__APPLE__) || defined(__ANDROID__) || defined(__BSD__)

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


#ifdef __ANDROID__


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


      ::memory_counter *                                    m_pmemorycounter;


      bool                                                  m_bOutputDebugString;

      bool                                                  m_bCommandLineCalculated = false;
      string                                                m_strCommandLineCalculated;
      bool                                                  m_bCommandLineSystemNative = false;
      string                                                m_strCommandLineSystemNative;


      //::critical_section                                    m_criticalsectionTask;
      //::critical_section                                    m_criticalsectionTaskOn;


      ::block                                               m_blockMatter;
      ::acme::library_map                                   m_mapLibrary;
      ::factory::factory_pointer                            m_pfactory;
      ::factory::factory_map                                m_factorymap;
      ::factory::component_factory_map                      m_componentfactorymap;
      ::pointer < ::operating_system::dynamic_library >     m_pdynamiclibrary;
      int                                                   m_iProcessStatus = 0;
      //::interlocked_long_long                            m_iNewTaskIndex;
      //::comparable_array < itask >                        m_itaska;
      bool                                                  m_bVerboseLog;
      ::windowing::enum_windowing                           m_ewindowing;
      ::windowing::enum_operating_ambient                   m_edesktop;
      ::windowing::enum_toolkit                             m_etoolkit;
      
      
      ::critical_section   m_criticalsectionSystemHeap;


      ::critical_section   m_criticalsectionChannel;
      ::critical_section   m_criticalsectionSequence;
      ::critical_section   m_criticalsectionMessageDispatch;




      platform();
      ~platform() override;

      virtual bool is_console() const;

      virtual bool is_desktop_system() const;

      virtual bool is_sandboxed() const;

         virtual ::string command_line() const;

         virtual void calculate_command_line();


      ::critical_section * channel_critical_section()
      {

         return &m_criticalsectionChannel;

      }


      ::critical_section * message_dispatch_critical_section()
      {

         return &m_criticalsectionMessageDispatch;

      }


      ::critical_section* sequence_critical_section()
      {

         return &m_criticalsectionSequence;

      }

   

      //using particle::initialize;

#if defined(WINDOWS) && defined(UNICODE)

      void initialize_system(int argc, wchar_t * args[], wchar_t * envp[]) override;

      void initialize_system(hinstance hinstanceThis, hinstance hinstancePrev, wchar_t * pCmdLine, int nCmdShow) override;

#endif

      void initialize_system(int argc, char ** args, char ** envp) override;


      void platform_initialize();
      void platform_finalize();


      void set_args(int argc, char ** args, wchar_t ** wargs);

      string _get_args(::collection::index iArg) const;
      ::collection::count get_argc();
      int * get_pargc();
      char *** get_pargs();
      char ** get_args();

#ifdef WINDOWS

      wchar_t *** get_pwargs();
      wchar_t ** get_wargs();

#endif

      bool is_verbose_log() const;

      inline ::collection::count _get_argc() const { return m_argc; }

      string get_executable() const;

      string get_argument1(::collection::index iArgument) const;

      string arguments_from1(::collection::index iArgument) const;

      bool has_argument(const ::scoped_string & scopedArgument) const;

      inline ::collection::count get_argument_count1() const { return _get_argc() - 1; }

      string_array_base get_arguments();

      ::string get_argument_begins_eat(const ::scoped_string & scopedstrPrefix);

      ::string_array_base get_argument_options(const ::scoped_string & scopedstrArgument);

      string get_arg(::collection::index i) const;
      string get_env(const ::scoped_string & scopedstrVariableName) const;


      int get_status();
      void set_status(int iStatus);



      virtual void set_resource_block(const_char_pointer pstart, const_char_pointer pend);

      void defer_initialize_platform();

      void factory_initialize();
      void factory_terminate();


      void delete_all_release_on_end();


      //::acme::acme * acme() const { return ((platform *)this)->m_pacme; }


      ::factory::factory_pointer & factory();
      ::factory::factory_pointer & factory(const ::scoped_string & scopedstrLibrary);
      ::factory::factory_pointer & factory(const ::scoped_string & scopedstrComponent, const ::scoped_string & scopedstrImplementation);
      ::factory::factory* component_factory(const ::scoped_string & scopedstrComponent);
      virtual ::string component_factory_implementation_name(const ::scoped_string & scopedstrComponent);


      //::factory::factory_item_interface* get_factory_item_by_type_index(const ::std::type_index & typeindex);
      //::factory::factory_item_interface* get_factory_item_by_custom_id(const ::type_custom_id & typecustomid);
      ::factory::factory_item_interface* get_factory_item(const ::platform::type & type);


      //::factory::factory_item_interface * get_factory_item_by_type_index(const ::std::type_index & typeindex, const ::atom & atomFactory);
      //::factory::factory_item_interface * get_factory_item_by_custom_id(const ::type_custom_id & typecustomid, const ::atom & atomFactory);
      ::factory::factory_item_interface * get_factory_item(const ::platform::type & type, const ::atom & atomFactory);


      //bool has_factory_item_by_type_index(const ::std::type_index & typeindex);
      //bool has_factory_item_by_custom_id(const ::type_custom_id & typecustomid);
      bool has_factory_item(const ::platform::type & type);


      //void set_factory_item_by_type(const ::platform::type & type, const ::pointer<::factory::factory_item_interface> & pfactoryitem);
      //void set_factory_item_by_custom_id(const ::type_custom_id & typecustomid, const ::pointer<::factory::factory_item_interface>& pfactoryitem);


      //void set_factory_item_by_type_for_factory(const ::platform::type & type, const ::atom & atomFactory, const ::pointer<::factory::factory_item_interface> & pfactoryitem);
      //void set_factory_item_by_custom_id_for_factory(const ::type_custom_id & typecustomid, const ::atom& atomFactory, const ::pointer<::factory::factory_item_interface>& pfactoryitem);


      //template < typename TYPE, typename BASE >
      //void add_factory_item_by_custom_id(const ::type_custom_id & typecustomid)
      //{
         
      //   set_factory_item_by_custom_id(typecustomid, øallocate ::factory::factory_item < TYPE, BASE > ());

      //}


      ::factory::factory * get_factory(const ::atom & atomFactory);



      //virtual void set_factory_global(const ::scoped_string & scopedstrComponent, const ::scoped_string & scopedstrImplementation);

      //virtual ::pointer<::acme::library> open_component_library(const ::scoped_string & scopedstrComponent, const ::scoped_string & scopedstrImplementation);

      virtual ::pointer<::acme::library> create_library(const ::scoped_string & scopedstrLibrary);
      virtual ::pointer<::acme::library> create_library_dynamically(const ::scoped_string & scopedstrLibrary);
      virtual ::pointer<::acme::library> create_library_statically(const ::scoped_string & scopedstrLibrary);

      virtual ::pointer<::acme::library> & library(const ::scoped_string & scopedstr);

      //virtual ::pointer<::acme::library>& library(const ::scoped_string & scopedstrComponent, const ::scoped_string & scopedstrImplementation);

      virtual ::pointer<::factory::factory> & impact_factory(const ::scoped_string & scopedstrComponent, const ::scoped_string & scopedstrImplementation);

      //void initialize_memory_counter();
      //void finalize_memory_counter();

      //::memory_counter * get_memory_counter();



      //virtual ::platform::system * __get_system() = 0;
      //class ::time start_nanosecond();



      ::particle * ui_destroyed_synchronization();



#if defined(LINUX) || defined(__APPLE__) || defined(__ANDROID__) || defined(__BSD__)

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


#ifdef __ANDROID__


      ::critical_section * output_debum_strinm_a_critical_section() { return &m_criticalsectionOutputDebugStringA; }

#endif

#ifdef __APPLE__


      //::critical_section m_criticalsectionCvt;


      ::critical_section * cvt_critical_section();

#endif

      //pass_through_function m_passthroughfunction;


      ////::collection::index task_index(itask itask, bool bAddIfNotInList = false);
      ////::collection::index new_task_index();
      //::thread_storage * thread_storage(const ::task_index & taskindex);
      //::thread_storage * _thread_storage_unlocked(const ::task_index & taskindex);



      //pass_through_function &  __call_allocate_pass_through_function() { return m_passthroughfunction; }


      //platform * __call__add_referer2(const ::reference_referer & referer) const;
      release_time_for_project as_release_time_for_project(const_char_pointer pszStatic);

      //::platform::system* system() { return m_psystem; }
      ::operating_system::dynamic_library* dynamic_library() { return m_pdynamiclibrary; }
       
//       // [HERE]
//       //  __node_library should be here at acme
//       //
//       //  -- e.g. cannot lie inside a plugin,
//       // because it is used to load a plugin
//       //
//       virtual void* operating_system_library_open(const ::file::path & path, string& strMessage);
//
// #if defined FREEBSD || defined(OPENBSD)
//       virtual string operating_system_library_is_loaded(const ::file::path &path);
// #endif // FREEBSD
//
//       virtual void* operating_system_library_touch(const ::file::path & path, string& strMessage);
//       virtual void* operating_system_library_open_ca2(const ::file::path & path, string& strMessage);
//       virtual bool operating_system_library_close(void* plibrary);
//       virtual void* operating_system_library_raw_get(void* plibrary, const ::scoped_string & scopedstrEntryName);


   };


   //template < typename SYSTEM >
   //class platform_impl :
   //   virtual public ::platform::platform
   //{
   //public:


   //   SYSTEM      m_system;

   //   ::platform::system * __get_system() override { return &m_system; }


   //};


   //namespace platform
   //{


   inline ::platform::platform * get() { return ::platform::platform::s_pplatform; }
   


} // namespace platform


//inline ::platform::system* system() 
//{ 
//   
//   auto pplatform = ::platform::get();
//   
//   return pplatform ? pplatform->system() : nullptr;
//
//}


inline ::operating_system::dynamic_library * dynamic_library()
{

   auto pplatform = ::platform::get();

   return pplatform ? pplatform->dynamic_library() : nullptr;

}


CLASS_DECL_ACME ::string as_string(const ::release_time_for_project& releasetimeforproject);



