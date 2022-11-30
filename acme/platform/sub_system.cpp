// Created by camilo on 2022-10-09 21:01 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "sub_system.h"
#include "acme.h"
#include "simple_log.h"
#include "acme/parallelization/manual_reset_event.h"
////#include "acme/exception/exception.h"
#include "acme/platform/context.h"
#include "acme/platform/library.h"
////#include "acme/exception/exception.h"
#include "acme/parallelization/task.h"


sub_system::sub_system(::acme::acme* pacme) :
   m_pacme(pacme)
{

   m_pacme->m_psubsystem = this;
   
   //__defer_raw_construct_new(m_pmemorycounter);
   
   factory_initialize();

}


sub_system::~sub_system()
{

   //m_pfactory.release();

   //m_pmapFactory.release();

   factory_terminate();

   task_release();

   {

      array<void *> librarya;

      for (auto & plibrary : m_mapLibrary.values())
      {

         if (plibrary)
         {

            librarya.add(plibrary->m_plibrary);

            plibrary->m_plibrary = nullptr;

            plibrary->destroy();

         }

      }

      m_mapLibrary.clear();

      for (auto & p : librarya)
      {


         __node_library_close(p);

      }

   }
   
}


::file::path sub_system::get_module_path()
{
 
   critical_section_lock criticalsectionlock(&m_criticalsection);
   
   if(!m_bModulePath)
   {
      
      
      
   }
   
   return m_pathModule;

}


::file::path sub_system::get_module_folder()
{
 
   critical_section_lock criticalsectionlock(&m_criticalsection);
   
   if(!m_bModuleFolder)
   {
      
      m_pathModuleFolder = get_module_path().folder();
      
   }
   
   return m_pathModuleFolder;

}


//::sub_system * sub_system::get()
//{
//
//   return g_psub_system;
//
//}


void sub_system::set_args(int argc, char ** argv, wchar_t ** wargv)
{

   m_argc = argc;

   m_argv = argv;
   
#ifdef WINDOWS_DESKTOP

   m_wargv = wargv;
   
#endif

}





int sub_system::get_argc()
{

   return m_argc;

}


string sub_system::_get_argv(int iArgument) const
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


string sub_system::get_executable() const
{

   return _get_argv(0);

}


string_array sub_system::get_arguments()
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

   return ::move(stra);

}


string sub_system::get_argument1(int iArgument) const
{

   return _get_argv(iArgument + 1);

}



int * sub_system::get_pargc()
{

   return &m_argc;

}


char *** sub_system::get_pargv()
{

   return &m_argv;

}


char ** sub_system::get_argv()
{

   return *get_pargv();

}


#ifdef WINDOWS


wchar_t *** sub_system::get_pwargv()
{

   return &m_wargv;

}


wchar_t ** sub_system::get_wargv()
{

   return *get_pwargv();

}


#endif


::factory::factory * sub_system::get_factory(const ::atom & atomSource)
{
   
   critical_section_lock criticalsectionlock(&m_criticalsection);

   auto & pfactory = m_factorymap[atomSource];

   if (!pfactory)
   {

      m_pcontext->__construct_new(pfactory);

   }

   return pfactory;

}



string sub_system::get_arg(int i) const
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


string sub_system::get_env(const char * pszVariableName) const
{

#ifdef WINDOWS
   
   if (m_wenvp)
   {

      wstring wstrPrefix(pszVariableName);

      wstrPrefix += "=";

      for (auto p = m_wenvp; p != nullptr; p++)
      {

         wstring wstr(*p);

         if (wstr.begins_eat_ci(wstrPrefix))
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

      string strPrefix(pszVariableName);

      strPrefix += "=";

      for (auto p = m_envp; p != nullptr; p++)
      {

         string str(*p);

         if (str.begins_eat_ci(strPrefix))
         {

            return str;

         }

      }

      return "";

   }

   return "";

}


int sub_system::get_status()
{

   return m_iProcessStatus;

}


void sub_system::set_status(int iStatus)
{

   m_iProcessStatus = iStatus;

}


void sub_system::set_resource_block(const char * pstart, const char * pend)
{

   m_blockMatter = ::block(pstart, pend - pstart);

}



void sub_system::factory_initialize()
{

   //__raw_construct_new(m_pfactorymap);

   //__raw_construct_new(m_pcomponentfactorymap);

   //m_pfactory = __new(::factory::factory());

   m_factory.InitHashTable(16189);

   //::acme::acme::g_pstaticstatic->m_pfactorya = memory_new factory_array();



   ::factory::add_factory_item<manual_reset_event>();
   ::factory::add_factory_item<task>();


   ::factory::add_factory_item<simple_log, logger>();


   //operating_system_initialize_nano();


}


void sub_system::factory_terminate()
{

   critical_section_lock synchronouslock(factory_critical_section());

   m_factory.erase_all();

   m_factorymap.erase_all();

   //m_pfactory.release();

   //m_pmapFactory.release();

}


//void sub_system::factory_term()
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
