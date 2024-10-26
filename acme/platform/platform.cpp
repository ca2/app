// Created by camilo on 2022-10-09 21:01 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "platform.h"
#include "acme.h"
#include "simple_log.h"
//#include "acme.h"
#include "acme/exception/library_not_loaded.h"
#include "acme/memory/counter.h"
#include "acme/nano/nano.h"
#include "acme/operating_system/dynamic_library.h"
#include "acme/parallelization/manual_reset_event.h"
#include "acme/parallelization/synchronous_lock.h"
////#include "acme/exception/exception.h"
#include "acme/platform/application.h"
#include "acme/platform/library.h"
//#include "acme/platform/sequencer.h"
#include "acme/platform/system.h"
////#include "acme/exception/exception.h"
#include "acme/parallelization/task.h"
#include "acme/_operating_system.h"
//
//

//#include "acme/include/_acme.h"

CLASS_DECL_ACME void initialize_nano_http(::factory::factory * pfactory);
CLASS_DECL_ACME void initialize_nano_user(::factory::factory * pfactory);

extern bool g_bWindowingOutputDebugString;

void IDENTIFIER_PREFIX_OPERATING_SYSTEM(_factory)(::factory::factory * pfactory);


namespace acme
{
   extern ::array < matter * > * g_paAura;
//
//
//   CLASS_DECL_ACME extern ::acme::acme * g_p;
//
//
} // namespace acme
//#ifdef CUBE
#include "factory_function.h"
//#endif


//namespace mathematics
//{
//
//
//   void initialize_mathematics();
//
//   void finalize_mathematics();
//
//
//} // namespace mathematics


#if REFERENCING_DEBUGGING


extern bool g_bDefaultEnableObjectReferenceCountDebug;


#endif


namespace platform
{


   ::platform::platform * platform::s_p = nullptr;


   platform::platform()
   {

      if (!s_p)
      {

         s_p = this;

      }
      

#if REFERENCING_DEBUGGING

      //disable_referencing_debugging();

#endif


      m_pdynamiclibrary = ::operating_system::new_dynamic_library();

      //factory_initialize();
      
      platform_initialize();


   }


   platform::~platform()
   {

      //if (::is_set(m_papplication))
      //{

      //   if (m_papplication->m_countReference > 0)
      //   {

      //      m_papplication->check

      //   }

      //}

      delete_all_release_on_end();

      factory_terminate();

      {

         array<library_t *> operatingsystemlibrarya;

         for (auto & pair : m_mapLibrary)
         {

            auto plibrary = pair.element2();

            if (plibrary)
            {

               operatingsystemlibrarya.add(plibrary->m_plibrary);

               plibrary->m_plibrary = nullptr;

               plibrary->destroy();

            }

         }

         m_mapLibrary.clear();

         for (auto & poperatingsystemlibrary : operatingsystemlibrarya)
         {

            dynamic_library()->close(poperatingsystemlibrary);

         }

      }

      //finalize_memory_counter();

   }


   bool platform::is_console() const
   {

      return m_bConsole;

   }


   bool platform::is_desktop_system() const
   {

      return IS_DESKTOP_SYSTEM();

   }


   bool platform::is_sandboxed() const
   {

#if defined(APPLE_IOS)
      return true;
#elif defined(ANDROID)
      return true;
#elif defined(UNIVERSAL_WINDOWS)
      return true;
#else
      return false;
#endif

   }



   void platform::platform_initialize()
   {

      //initialize_memory_counter();

      // One of first time to set a main user thread

      //set_main_user_thread();

      factory_initialize();

      //::mathematics::initialize_mathematics();

      ////factory_init();

::acme::g_paAura = __raw_new ::array < matter* > ();

////::task_on_after_new_particle(g_paAura);
#if REFERENCING_DEBUGGING

{

   auto p = ::allocator::task_get_top_track();

   ASSERT(p == nullptr);

}
#endif

      m_bVerboseLog = true;
      m_bConsole = false;
      //m_papplication = nullptr;
      m_pmemorycounter = nullptr;
      m_bOutputDebugString = true;

//#ifdef WINDOWS
//
//      m_strCommandLine = ::GetCommandLineW();
//
//#endif


   }


   void platform::platform_finalize()
   {

      //initialize_memory_counter();

      // One of first time to set a main user thread
      //::mathematics::finalize_mathematics();

      //set_main_user_thread();

      factory_initialize();

      m_bVerboseLog = true;
      m_bConsole = false;
      //m_papplication = nullptr;
      m_pmemorycounter = nullptr;
      m_bOutputDebugString = true;

//#ifdef WINDOWS
//
//      m_strCommandLine = ::GetCommandLineW();
//
//#endif

#if REFERENCING_DEBUGGING

      g_bDefaultEnableObjectReferenceCountDebug = true;

#endif

   }


   //::platform::platform * platform::platform() const
   //{

   //   return ((platform *)this);

   //}


#if defined(WINDOWS)  && defined(UNICODE)


   void platform::initialize_system(int argc, wchar_t * args[], wchar_t * envp[])
   {

      m_argc = argc;
      m_wargs = args;
      m_wenvp = envp;

   }


   void platform::initialize_system(hinstance hinstanceThis, hinstance hinstancePrev, wchar_t * pCmdLine, int nCmdShow)
   {

      m_hinstanceThis = hinstanceThis;
      m_hinstancePrev = hinstancePrev;
      //m_strCommandLine = pCmdLine; // pCmdLine lacks the executable file path arg[0]
      m_strCommandLine = ::GetCommandLineW();
      m_nCmdShow = nCmdShow;

      m_argc = __argc;
      m_wargs = __wargv;
      m_wenvp = (wchar_t **)*__p__wenviron();


   }


#else


   void platform::initialize(int argc, platform_char ** args, platform_char ** envp)
   {

      m_argc = argc;
      m_args = args;
      m_envp = envp;

   }


#endif


   //void platform::initialize_memory_counter()
   //{

   //   if (!m_pmemorycounter)
   //   {

   //      m_pmemorycounter = ___new ::memory_counter();

   //   }

   //}


   //void platform::finalize_memory_counter()
   //{

   //   ::acme::del(m_pmemorycounter);

   //}


   //::memory_counter * platform::get_memory_counter()
   //{

   //   return m_pmemorycounter;

   //}



   //::platform * platform::get()
   //{
   //
   //   return g_psub_system;
   //
   //}


   void platform::set_args(int argc, char ** args, wchar_t ** wargs)
   {

      m_argc = argc;

      m_args = args;

#ifdef WINDOWS_DESKTOP

      m_wargs = wargs;

#endif

   }


   ::collection::count platform::get_argc()
   {

      return m_argc;

   }


   string platform::_get_args(::collection::index iArgument) const
   {

      if (iArgument < 0 || iArgument >= _get_argc())
      {

         return "";

      }

#ifdef WINDOWS

      if (m_wargs && m_wargs[iArgument])
      {

         return m_wargs[iArgument];

      }
      else

#endif

         if (m_args && m_args[iArgument])
         {

            return m_args[iArgument];

         }

      return "";

   }


   bool platform::is_verbose_log() const
   {

      return m_bVerboseLog;

   }


   string platform::get_executable() const
   {

      return _get_args(0);

   }


   string_array platform::get_arguments()
   {

      string_array stra;

      for (::collection::index i = 0; i < m_argc; i++)
      {

         string strArgument;

#ifdef WINDOWS

         if (m_wargs && m_wargs[i])
         {

            strArgument = m_wargs[i];

         }
         else

#endif

            if (m_args && m_args[i])
            {

               strArgument = m_args[i];

            }
            else
            {

               break;

            }

         stra.add(strArgument);

      }

      return ::transfer(stra);

   }


   ::string platform::get_argument_begins_eat(const ::scoped_string & scopedstrPrefix)
   {

      auto stra = this->get_arguments();

      ::string str;

      auto find = stra.find_first_begins_eat(str, scopedstrPrefix);

      if(!find)
      {

         return {};

      }

      return str;

   }


   ::string_array platform::get_argument_options(const ::scoped_string & scopedstrArgument)
   {

      string strArgument = scopedstrArgument;

      strArgument.trim_right("=");

      strArgument += "=";

      auto strOptions = get_argument_begins_eat(strArgument);

      if(strOptions.is_empty())
      {

         return {};

      }

      ::string_array straOptions;

      straOptions.explode(",", strOptions);

      return straOptions;

   }


   string platform::get_argument1(::collection::index iArgument) const
   {

      return _get_args(iArgument + 1);

   }


   bool platform::has_argument(const ::scoped_string & scopedArgument) const
   {

      bool bHasArgument = false;

      for (::collection::index iArg = 0; iArg < get_argument_count1(); iArg++)
      {

         ::string strArg = get_argument1(iArg);

         if (strArg == scopedArgument)
         {

            bHasArgument = true;

            break;

         }

      }

      return bHasArgument;

   }


   int * platform::get_pargc()
   {

      return &m_argc;

   }


   char *** platform::get_pargs()
   {

      return &m_args;

   }


   char ** platform::get_args()
   {

      return *get_pargs();

   }


#ifdef WINDOWS


   wchar_t *** platform::get_pwargs()
   {

      return &m_wargs;

   }


   wchar_t ** platform::get_wargs()
   {

      return *get_pwargs();

   }


#endif


   ::factory::factory * platform::get_factory(const ::atom & atomSource)
   {

      critical_section_lock criticalsectionlock(&m_criticalsection);

      auto & pfactory = m_factorymap[atomSource];

      if (!pfactory)
      {

         ::system()->__construct_new(pfactory);

      }

      return pfactory;

   }



   string platform::get_arg(::collection::index i) const
   {

#ifdef WINDOWS

      if (m_wargs)
      {

         return string(m_wargs[i]);

      }
      else

#endif

         if (m_args)
         {

            return string(m_args[i]);

         }

      return "";


   }


   string platform::get_env(const ::scoped_string & scopedstrVariableName) const
   {

#ifdef WINDOWS

      if (m_wenvp)
      {

         wstring wstrPrefix(scopedstrVariableName);

         wstrPrefix += "=";

         for (auto p = m_wenvp; p != nullptr; p++)
         {

            wstring wstr(*p);

            if (wstr.case_insensitive_begins_eat(wstrPrefix))
            {

               return wstr;

            }

         }

         return "";

      }
      else

#endif

         if (m_envp)
         {

            string strPrefix(scopedstrVariableName);

            strPrefix += "=";

            for (auto p = m_envp; p != nullptr; p++)
            {

               string str(*p);

               if (str.case_insensitive_begins_eat(strPrefix))
               {

                  return str;

               }

            }

            return "";

         }

      return "";

   }


   int platform::get_status()
   {

      return m_iProcessStatus;

   }


   void platform::set_status(int iStatus)
   {

      m_iProcessStatus = iStatus;

   }


   void platform::set_resource_block(const char * pstart, const char * pend)
   {

      m_blockMatter = ::block(pstart, pend);

   }


   void platform::defer_initialize_platform()
   {

      // if (!m_psystem)
      // {
      //
      //    factory()->__raw_construct(m_psystem);
      //
      //    m_psystem->set_platform();
      //
      //    //initialize(m_psystem);
      //
      //    m_psystem->on_initialize_particle();

	 auto strWindowingDebug = get_argument_begins_eat("--windowing-debug=");

	 if(strWindowingDebug.case_insensitive_equals("true")
|| strWindowingDebug == "1"
|| strWindowingDebug.case_insensitive_equals("yes"))
{
g_bWindowingOutputDebugString = true;
}

      //}

   }


   void platform::factory_initialize()
   {

      m_pfactory = { transfer_t{}, __raw_new::factory::factory() };

      //__raw_construct_new(m_pfactorymap);

      //__raw_construct_new(m_pcomponentfactorymap);

      //m_pfactory = __allocate ::factory::factory();

      m_pfactory->InitHashTable(16189);

      //::acme::acme::g_pstaticstatic->m_pfactorya = ___new factory_array();

      __check_refdbg

      factory()->add_factory_item<manual_reset_event>();

      __check_refdbg

      factory()->add_factory_item<task>();


      factory()->add_factory_item<simple_log, ::logger>();
      //factory()->add_factory_item<property>();


      //operating_system_initialize_nano_user();

      //IDENTIFIER_PREFIX_OPERATING_SYSTEM(_factory)(factory());


   }


   ::pointer<::factory::factory_item_interface> & platform::get_factory_item(const ::atom & atom, const ::atom & atomSource)
   {

      critical_section_lock cs(&m_criticalsection);

      return (*get_factory(atomSource))[atom];

   }


   bool platform::has_factory_item(const ::atom & atom)
   {

      critical_section_lock cs(&m_criticalsection);

      auto p = m_pfactory->find_item(atom);

      if (!p)
      {

         return false;

      }

      if (!p->element2())
      {

         return false;

      }

      return true;

   }



   void platform::set_factory(const ::atom & atom, const ::pointer<::factory::factory_item_interface> & pfactory)
   {

      critical_section_lock cs(&m_criticalsection);

      m_pfactory->set_at(atom, pfactory);

   }


   void platform::set_factory_from(const ::atom & atom, const ::atom & atomSource, const ::pointer<::factory::factory_item_interface> & pfactory)
   {

      critical_section_lock cs(&m_criticalsection);

      get_factory(atomSource)->set_at(atom, pfactory);

   }


   ::factory::factory_pointer & platform::factory()
   {

      return m_pfactory;

   }


   ::task* platform::get_task(itask_t itask)
   {

      _synchronous_lock synchronouslock(m_pmutexTask);

      return m_taskmap[itask];

   }


   itask_t platform::get_task_id(const ::task* ptask)
   {

      _synchronous_lock synchronouslock(m_pmutexTask);

      itask_t itask = null_itask;

      if (!m_taskidmap.lookup((::task* const)ptask, itask))
      {

         return 0;

      }

      return itask;

   }


   void platform::set_task(itask_t itask, ::task* ptask)
   {

      _synchronous_lock synchronouslock(m_pmutexTask);

      __refdbg_add_referer_for(ptask);

      m_taskmap[itask] = ptask;

      m_taskidmap[ptask] = itask;

   }


   void platform::unset_task(itask_t itask, ::task* ptask)
   {

      _synchronous_lock synchronouslock(m_pmutexTask);

      if(m_taskmap.has(itask)) m_taskmap.erase_item(itask);

      if(m_taskidmap.has(ptask)) m_taskidmap.erase_item(ptask);

   }


   bool platform::is_task_on(itask_t atom)
   {

      _synchronous_lock synchronouslock(m_pmutexTaskOn);

      return m_mapTaskOn.plookup(atom);

   }


   bool platform::is_active(::task* ptask)
   {

      if (::is_null(ptask))
      {

         return false;

      }

      return is_task_on(ptask->m_itask);

   }


   void platform::set_task_on(itask_t atom)
   {

      _synchronous_lock synchronouslock(m_pmutexTaskOn);

      m_mapTaskOn.set_at(atom, atom);

   }


   void platform::set_task_off(itask_t atom)
   {

      _synchronous_lock synchronouslock(m_pmutexTaskOn);

      m_mapTaskOn.erase_item(atom);

   }


   ::factory::factory_pointer & platform::factory(const ::string & strLibraryRequest)
   {

      critical_section_lock criticalsectionlock(&m_criticalsection);

      string strLibrary;

      strLibrary = library_filter(strLibraryRequest);

      auto & pfactory = m_factorymap[strLibrary];

      if (pfactory)
      {

         return pfactory;

      }

      information() << "system::factory Going to get library \"" << strLibrary << "\".";

      auto & plibrary = library(strLibrary);

      if (!plibrary)
      {

//#ifdef CUBE

         auto pfnFactory = ::factory_function::get(strLibrary);

         if (!pfnFactory)
         {

            throw ::exception(error_resource);


         }

         plibrary = system()->__create_new < ::acme::library >();

         plibrary->m_strName = strLibrary;

         plibrary->m_pfnFactory = pfnFactory;

//#endif

      }

      information() << "system::factory Going to create factory from library \"" << strLibrary << "\".";

      plibrary->create_factory(pfactory);

      if (!pfactory)
      {

         return pfactory;

      }

      return pfactory;

   }


   ::factory::factory_pointer & platform::factory(const ::string & strComponent, const ::string & strImplementation)
   {

      critical_section_lock criticalsectionlock(&m_criticalsection);

      //informationf("platform::factory(\"%s\", \"%s\");\n", strComponent.c_str(), strImplementation.c_str());

      auto strImplementationName = implementation_name(strComponent, strImplementation);

      auto & pfactory = m_componentfactorymap[strComponent][strImplementationName];

      if (pfactory)
      {

         debugf("Returning existing factory \"%s\" - \"%s\".\n", strComponent.c_str(), strImplementation.c_str());

         return pfactory;

      }
      
      // if(strImplementation == "(built-in)")
      // {
      //
      //    if(strComponent == "nano_http")
      //    {
      //
      //       pfactory = system()->__create_new < ::factory::factory >();
      //
      //       initialize_nano_http(pfactory);
      //
      //       return pfactory;
      //
      //    }
      //    else if(strComponent == "nano_user")
      //    {
      //
      //       pfactory = system()->__create_new < ::factory::factory >();
      //
      //       initialize_nano_user(pfactory);
      //
      //       return pfactory;
      //
      //    }
      //    else
      //    {
      //
      //       informationf("Not known built-in component: \"%s\".\n", strComponent.c_str());
      //
      //       //pfactory = (const ::extended::status&)plibrary;
      //       throw ::exception(error_resource, strComponent + " factory not found!!");
      //
      //    }
      //
      // }

      string strLibrary;

      //strLibrary = library_name(strComponent, strImplementation);
      strLibrary = strComponent + "_" + strImplementation;

      //informationf("Getting library \"%s\".", strLibrary.c_str());

      auto & plibrary = library(strLibrary);

      if (!plibrary)
      {

//#ifdef CUBE

         auto pfnFactory = ::factory_function::get(strLibrary);

         if (pfnFactory)
         {

            pfactory = system()->__create_new < ::factory::factory >();

            pfnFactory(pfactory);

            return pfactory;

         }

//#endif

         informationf("Library not found : \"%s\".\n", strLibrary.c_str());

         //pfactory = (const ::extended::status&)plibrary;
         throw ::exception(error_resource, strComponent + "_" + strImplementation + "_factory not found!!");

      }

      plibrary->create_factory(pfactory);

      return pfactory;

   }


   //::factory::factory_pointer& platform::_factory(const ::string& strLibraryRequest)
   ////{
   ////
   ////   critical_section_lock criticalsectionlock(&m_criticalsection);
   ////
   ////   string strLibrary;
   ////
   ////   strLibrary = library_filter(strLibraryRequest);
   ////
   ////   auto& pfactory = m_factorymap[strLibrary];
   ////
   ////   if (pfactory)
   ////   {
   ////
   ////      return pfactory;
   ////
   ////   }
   ////
   ////   information() << "system::factory Going to get library \"" << strLibrary << "\".";
   ////
   ////   auto& plibrary = library(strLibrary);
   ////
   ////   if (!plibrary)
   ////   {
   ////
   ////#ifdef CUBE
   ////
   ////      auto pfnFactory = ::system_setup::get_factory_function(strLibrary);
   ////
   ////      if (!pfnFactory)
   ////      {
   ////
   ////         throw ::exception(error_resource);
   ////
   ////
   ////      }
   ////
   ////      plibrary = system()->__create_new < ::acme::library >();
   ////
   ////      plibrary->m_strName = strLibrary;
   ////
   ////      plibrary->m_pfnFactory = pfnFactory;
   ////
   ////#endif
   ////
   ////   }
   ////
   ////   information() << "system::factory Going to create factory from library \"" << strLibrary << "\".";
   ////
   ////   pfactory = plibrary->create_factory();
   ////
   ////   if (!pfactory)
   ////   {
   ////
   ////      return pfactory;
   ////
   ////   }
   ////
   ////   return pfactory;
   ////
   ////}


   void platform::factory_terminate()
   {

      critical_section_lock synchronouslock(factory_critical_section());

      m_pfactory->erase_all();

      m_factorymap.erase_all();

      m_componentfactorymap.erase_all();

   }


   ::pointer<::factory::factory> & platform::impact_factory(const ::string & strComponent, const ::string & strImplementation)
   {

      critical_section_lock criticalsectionlock(&m_criticalsection);

      auto & pfactory = m_componentfactorymap[strComponent][implementation_name(strComponent, strImplementation)];

      try
      {

         return factory(strComponent, strImplementation);

      }
      catch (const ::exception & exception)
      {

         string strMessage = "Library couldn't be opened : " + exception.m_strMessage;

         string strDetails = exception.get_consolidated_details(this);

         auto pmessagebox = __initialize_new_with(this) ::message_box(strMessage, "Library Loading Failure", e_message_box_ok | e_message_box_icon_warning,
            strDetails);

         pmessagebox->async();

         throw exception;

      }

      return pfactory;

   }

   
   ::pointer<::acme::library> platform::create_library_dynamically(const ::string & strLibrary)
   {

      //::allocator::add_referer(REFERENCING_DEBUGGING_THIS_FUNCTION_FILE_LINE);

      auto plibrary = __create_new < ::acme::library >();

      __check_refdbg
      //plibrary->initialize_matter(this);

      //auto estatus = plibrary->open(strLibrary);

      debugf("platform::create_library Going to open library \"%s\".", strLibrary.c_str());

      //information() << "platform::create_library Going to open library \"" << strLibrary << "\".";

      plibrary->open(strLibrary);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      if (!plibrary->is_opened())
      {

         string strMessage = plibrary->m_strMessage;

         warning() << "Library wasn't opened (\"" << strLibrary << "\") : " << strMessage;

         throw ::exception(error_failed, "Library wasn't opened (\"" + strLibrary + "\")", strMessage);

      }

      return plibrary;

   }


   ::pointer<::acme::library> platform::create_library_statically(const ::string & strLibrary)
   {

      auto pfnFactory = ::factory_function::get(strLibrary);

      if (!pfnFactory)
      {

         return nullptr;

      }

      auto plibrary = __create_new < ::acme::library >();

      plibrary->m_strName = strLibrary;

      plibrary->m_pfnFactory = pfnFactory;

      return plibrary;

   }



   ::pointer<::acme::library> platform::create_library(const ::string & strLibrary)
   {

#ifdef CUBE

      return create_library_statically(strLibrary);

#else

      ::pointer<::acme::library> plibrary;

      try
      {

         plibrary = create_library_dynamically(strLibrary);

      }
      catch (library_not_loaded& librarynotloaded)
      {

         auto pmessagebox = __initialize_new_with(this) ::message_box(librarynotloaded.get_message(),
            "Library not loaded", e_message_box_icon_error, librarynotloaded.m_strDetails);

         pmessagebox->async();

      }
      catch (...)
      {


      }

      if (!plibrary)
      {

         plibrary = create_library_statically(strLibrary);

      }

      return plibrary;

#endif

   }


   ::pointer<::acme::library> & platform::library(const ::string & str)
   {

      // Ex. "audio" (library)

      //informationf("platform::library \"%s\".", str.c_str());

      if (str.is_empty())
      {

         throw ::exception(error_bad_argument);

      }

      critical_section_lock criticalsectionlock(&m_criticalsection);

      string strLibrary = library_filter(str);

      auto & plibrary = m_mapLibrary[strLibrary];

      if (plibrary)
      {

         informationf("platform::library Returning existing library \"%s\".", strLibrary.c_str());

         return plibrary;

      }

      plibrary = create_library(strLibrary);

      return plibrary;

   }

   
   void platform::delete_all_release_on_end()
   {

      critical_section_lock criticalsectionlock(globals_critical_section());

      //m_pelementaddraReleaseOnEnd->erase_all();

     // ::acme::del(m_pelementaddraReleaseOnEnd);

      //if (is_set(::acme::g_pelementaddraReleaseOnEnd))
   //   {
   //
   //      for (auto pmatter : ::acme::g_elementaddraReleaseOnEnd)
   //      {
   //
   //         ::acme::del(pmatter);
   //
   //      }
   //
   //      ::acme::del(::acme::g_pelementaddraReleaseOnEnd);
   //
   //   }

   }

   //class ::time platform::start_nanosecond()
   //{

   //   return m_timeStart;

   //}


   //::particle * platform::__call__add_referer2(const ::reference_referer & referer) const
   //{

   //   ::allocator::defer_add_referer(referer);

   //   return (::particle *)this;

   //}


   release_time_for_project platform::as_release_time_for_project(const char* pszStaticText)
   {

      release_time_for_project releasetimeforproject;

      releasetimeforproject.m_pszStatic = pszStaticText;

      // 0123-56-89-12-45-78

      auto len = ansi_length(pszStaticText);

      if (len >= 10
         && ::character_isdigit(pszStaticText[0])
         && ::character_isdigit(pszStaticText[1])
         && ::character_isdigit(pszStaticText[2])
         && ::character_isdigit(pszStaticText[3])
         && !::character_isalnum(pszStaticText[4])
         && ::character_isdigit(pszStaticText[5])
         && ::character_isdigit(pszStaticText[6])
         && !::character_isalnum(pszStaticText[7])
         && ::character_isdigit(pszStaticText[8])
         && ::character_isdigit(pszStaticText[9])
         )
      {

         releasetimeforproject.m_iYear = ::as_i32(scoped_ansi_string(pszStaticText + 0, 4));
         releasetimeforproject.m_iMonth = ::as_i32(scoped_ansi_string(pszStaticText + 5, 2));
         releasetimeforproject.m_iDay = ::as_i32(scoped_ansi_string(pszStaticText + 8, 2));

         if (len >= 19
            && !::character_isalnum(pszStaticText[10])
            && ::character_isdigit(pszStaticText[11])
            && ::character_isdigit(pszStaticText[12])
            && !::character_isalnum(pszStaticText[13])
            && ::character_isdigit(pszStaticText[14])
            && ::character_isdigit(pszStaticText[15])
            && !::character_isalnum(pszStaticText[16])
            && ::character_isdigit(pszStaticText[17])
            && ::character_isdigit(pszStaticText[18])
            )
         {

            releasetimeforproject.m_iHour = ::as_i32(scoped_ansi_string(pszStaticText + 11, 2));
            releasetimeforproject.m_iMinute = ::as_i32(scoped_ansi_string(pszStaticText + 14, 2));
            releasetimeforproject.m_iSecond = ::as_i32(scoped_ansi_string(pszStaticText + 17, 2));

         }

      }

      return releasetimeforproject;

   }



   //::operating_system::dynamic_library* platform::dynamic_library()
   //{

   //   return m_pdynamiclibrary;

   //}


} // namespace platform


   //void platform::factory_term()
   //{
   //
   //   critical_section_lock synchronouslock(factory_critical_section());
   //
   //   m_pfactory.release();
   //
   //   //::acme::del(::acme::acme::g_pstaticstatic->m_pfactorya);
   //
   //   //::acme::del(::acme::acme::g_pstaticstatic->m_pfactory);
   //
   //}


//CLASS_DECL_ACME::factory::factory * get_system_factory()
//{
//
//   return this->platform()->m_pfactory;
//
//}


CLASS_DECL_ACME::string as_string(const ::release_time_for_project& releasetimeforproject)
{

   return releasetimeforproject.m_pszStatic;

}



CLASS_DECL_ACME ::subparticle* refdbg_this()
{ 
   
   return (::subparticle*)::platform::get(); 

}





