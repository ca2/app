// Created by camilo on 2022-10-09 21:01 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "platform.h"
#include "acme.h"
#include "simple_log.h"
//#include "acme.h"
#include "acme/memory/counter.h"
#include "acme/parallelization/manual_reset_event.h"
////#include "acme/exception/exception.h"
#include "acme/platform/context.h"
#include "acme/platform/library.h"
#include "acme/platform/sequencer.h"
#include "acme/platform/system.h"
////#include "acme/exception/exception.h"
#include "acme/parallelization/task.h"
#include "acme/_operating_system.h"
//
//
//namespace acme
//{
//
//
//   CLASS_DECL_ACME extern ::acme::acme * g_p;
//
//
//} // namespace acme
#ifdef CUBE
#include "factory_function.h"
#endif


namespace platform
{


   ::platform::platform * platform::s_pplatform = nullptr;


   platform::platform()
   {

      s_pplatform = this;

      m_timeStart.Now();


      initialize_memory_counter();


      // One of first time to set a main user thread

      set_main_user_thread();

      factory_initialize();



      m_bConsole = false;
      //m_pacmeapplication = nullptr;
      m_pmemorycounter = nullptr;
      m_bOutputDebugString = true;

#ifdef WINDOWS

      ::platform::get()->m_strCommandLine = ::GetCommandLineW();

#endif

   }


   platform::~platform()
   {

      m_pacmeapplication.release();

      delete_all_release_on_end();

      factory_terminate();

      {

         array<void *> operatingsystemlibrarya;

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

            system()->operating_system_library_close(poperatingsystemlibrary);

         }

      }

      finalize_memory_counter();

      s_pplatform = nullptr;

   }


   void platform::initialize_memory_counter()
   {

      if (!m_pmemorycounter)
      {

         m_pmemorycounter = new ::memory_counter();

      }

   }


   void platform::finalize_memory_counter()
   {

      ::acme::del(m_pmemorycounter);

   }


   ::memory_counter * platform::get_memory_counter()
   {

      return m_pmemorycounter;

   }



   //::platform * platform::get()
   //{
   //
   //   return g_psub_system;
   //
   //}


   void platform::set_args(int argc, char ** argv, wchar_t ** wargv)
   {

      m_argc = argc;

      m_argv = argv;

#ifdef WINDOWS_DESKTOP

      m_wargv = wargv;

#endif

   }


   ::count platform::get_argc()
   {

      return m_argc;

   }


   string platform::_get_argv(::index iArgument) const
   {

      if (iArgument < 0 || iArgument >= _get_argc())
      {

         return "";

      }

#ifdef WINDOWS

      if (m_wargv && m_wargv[iArgument])
      {

         return m_wargv[iArgument];

      }
      else

#endif

         if (m_argv && m_argv[iArgument])
         {

            return m_argv[iArgument];

         }

      return "";

   }


   string platform::get_executable() const
   {

      return _get_argv(0);

   }


   string_array platform::get_arguments()
   {

      string_array stra;

      for (::index i = 0; i < m_argc; i++)
      {

         string strArgument;

#ifdef WINDOWS

         if (m_wargv && m_wargv[i])
         {

            strArgument = m_wargv[i];

         }
         else

#endif

            if (m_argv && m_argv[i])
            {

               strArgument = m_argv[i];

            }
            else
            {

               break;

            }

         stra.add(strArgument);

      }

      return ::transfer(stra);

   }


   string platform::get_argument1(::index iArgument) const
   {

      return _get_argv(iArgument + 1);

   }


   bool platform::has_argument1(const ::scoped_string & scopedArgument) const
   {

      bool bHasArgument = false;

      for (index iArg = 0; iArg < get_argument_count1(); iArg++)
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


   char *** platform::get_pargv()
   {

      return &m_argv;

   }


   char ** platform::get_argv()
   {

      return *get_pargv();

   }


#ifdef WINDOWS


   wchar_t *** platform::get_pwargv()
   {

      return &m_wargv;

   }


   wchar_t ** platform::get_wargv()
   {

      return *get_pwargv();

   }


#endif


   ::factory::factory * platform::get_factory(const ::atom & atomSource)
   {

      critical_section_lock criticalsectionlock(&m_criticalsection);

      auto & pfactory = m_factorymap[atomSource];

      if (!pfactory)
      {

         m_pcontext->__construct_new(pfactory);

      }

      return pfactory;

   }



   string platform::get_arg(::index i) const
   {

#ifdef WINDOWS

      if (m_wargv)
      {

         return string(m_wargv[i]);

      }
      else

#endif

         if (m_argv)
         {

            return string(m_argv[i]);

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

      if (!m_psystem)
      {

         __raw_construct(m_psystem);

         initialize(m_psystem);

         m_psystem->m_pplatform = this;

      }

   }


   void platform::factory_initialize()
   {

      __construct_new(m_pfactory);

      //__raw_construct_new(m_pfactorymap);

      //__raw_construct_new(m_pcomponentfactorymap);

      //m_pfactory = __new(::factory::factory());

      m_pfactory->InitHashTable(16189);

      //::acme::acme::g_pstaticstatic->m_pfactorya = memory_new factory_array();



      factory()->add_factory_item<manual_reset_event>();
      factory()->add_factory_item<task>();


      factory()->add_factory_item<simple_log, ::logger>();


      //operating_system_initialize_nano();


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


   ::factory::factory_pointer & platform::factory(const ::string & strLibraryRequest)
   {

      critical_section_lock synchronouslock(&m_criticalsection);

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

#ifdef CUBE

         auto pfnFactory = ::factory_function::get(strLibrary);

         if (!pfnFactory)
         {

            throw ::exception(error_resource);


         }

         plibrary = system()->__create_new < ::acme::library >();

         plibrary->m_strName = strLibrary;

         plibrary->m_pfnFactory = pfnFactory;

#endif

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

      critical_section_lock synchronouslock(&m_criticalsection);

      auto & pfactory = m_componentfactorymap[strComponent][implementation_name(strComponent, strImplementation)];

      if (pfactory)
      {

         return pfactory;

      }

      string strLibrary;

      //strLibrary = library_name(strComponent, strImplementation);
      strLibrary = strComponent + "_" + strImplementation;

      auto & plibrary = library(strLibrary);

      if (!plibrary)
      {

#ifdef CUBE

         auto pfnFactory = ::factory_function::get(strLibrary);

         if (pfnFactory)
         {

            pfactory = system()->__create_new < ::factory::factory >();

            pfnFactory(pfactory);

            return pfactory;

         }

#endif

         //pfactory = (const ::extended::status&)plibrary;
         throw ::exception(error_resource, strComponent + "_" + strImplementation + "_factory not found!!");

      }

      plibrary->create_factory(pfactory);

      return pfactory;

   }


   //::factory::factory_pointer& platform::_factory(const ::string& strLibraryRequest)
   ////{
   ////
   ////   critical_section_lock synchronouslock(&m_criticalsection);
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

      critical_section_lock synchronouslock(&m_criticalsection);

      auto & pfactory = m_componentfactorymap[strComponent][implementation_name(strComponent, strImplementation)];

      try
      {

         return factory(strComponent, strImplementation);

      }
      catch (const ::exception & exception)
      {

         string strMessage = "Library couldn't be opened : " + exception.m_strMessage;

         string strDetails = exception.get_consolidated_details();

         auto psequencer = message_box(strMessage, "Library Loading Failure", e_message_box_ok | e_message_box_icon_warning,
            strDetails);

         psequencer->do_asynchronously();

         throw exception;

      }

      return pfactory;

   }


   ::pointer<::acme::library> platform::create_library(const ::string & strLibrary)
   {

#ifdef CUBE

      auto pfnFactory = ::factory_function::get(strLibrary);

      if (!pfnFactory)
      {

         return nullptr;

      }

      auto plibrary = __create_new < ::acme::library >();

      plibrary->m_strName = strLibrary;

      plibrary->m_pfnFactory = pfnFactory;

      return plibrary;


#else

      auto plibrary = __create_new < ::acme::library >();

      //plibrary->initialize_matter(this);

      //auto estatus = plibrary->open(strLibrary);

      information() << "system::create_library Going to open library \"" << strLibrary << "\".";

      plibrary->open(strLibrary);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      if (!plibrary->is_opened())
      {

         string strMessage = plibrary->m_strMessage;

         information() << "Library wasn't opened (\"" << strLibrary << "\") : " << strMessage;

         throw ::exception(error_failed, "Library wasn't opened (\"" + strLibrary + "\")", strMessage);

      }

#endif

      return plibrary;

   }


   ::pointer<::acme::library> & platform::library(const ::string & str)
   {

      // Ex. "audio" (library)

      if (str.is_empty())
      {

         throw ::exception(error_bad_argument);

      }

      critical_section_lock synchronouslock(&m_criticalsection);

      string strLibrary = library_filter(str);

      auto & plibrary = m_mapLibrary[strLibrary];

      if (plibrary)
      {

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

   class ::time platform::start_nanosecond()
   {

      return m_timeStart;

   }



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


CLASS_DECL_ACME::factory::factory * get_system_factory()
{

   return ::platform::get()->m_pfactory;

}



