#include "framework.h"
#include "_.h"


#if defined(LINUX) || defined(APPLEOS)
#if defined(APPLEOS)

#ifndef APPLEOS
#define _DARWIN_C_SOURCE
#endif

#endif
#include <dlfcn.h>
#include <sys/stat.h>
#endif


namespace dynamic_source
{


   script::script() :
      m_streamError(&m_fileError)
   {

      m_bNew = true;

      defer_create_mutex();

   }


   script::~script()
   {

   }


   void script::run(script_instance * pinstance)
   {
      pinstance->run();
   }


   bool script::ShouldBuild()
   {

      return true;

   }


   bool script::HasCompileOrLinkError()
   {

      return false;

   }


   ds_script::ds_script()
   {

      m_bHasFatalError = false;
      m_lpfnCreateInstance       = nullptr;
      m_bShouldBuild             = true;
      m_bShouldCalcTempError     = true;
      m_bHasTempError            = false;
      m_bHasTempOsError          = false;
      m_bUnloading               = false;
      m_evCreationEnabled.SetEvent();



   }





   ds_script::~ds_script()
   {

      Unload();

   }


   bool ds_script::DoesMatchVersion()
   {

      if(m_tickLastVersionCheck.elapsed() < (5000))
      {
         return m_bLastVersionCheck;
      }

      m_tickLastVersionCheck = ::get_tick();

      sync_lock sl(mutex());

      bool bMatches = false;

      auto ft = get_file_time(m_strSourcePath);

      bMatches = m_ft == ft;

      m_bLastVersionCheck = bMatches;
      return bMatches;
   }

   bool ds_script::ShouldBuild()
   {

      sync_lock sl(mutex());

      if (m_bHasFatalError)
      {

         return false;

      }

      bool bManagerShouldBuild = m_pmanager->should_build(m_strSourcePath);

      if (bManagerShouldBuild)
      {

         return true;

      }

      return m_bShouldBuild || HasDelayedTempError() || !DoesMatchVersion();

   }

   void ds_script::on_start_build()
   {

      sync_lock sl(mutex());

      m_bShouldCalcTempError     = true;

      m_bShouldBuild             = false;

      m_bHasTempOsError          = false;

      m_streamError.m_p->set_size(0);

      m_strError.Empty();

      Unload();

   }

   bool ds_script::HasTimedOutLastBuild()
   {
      sync_lock sl(mutex());
      return (m_tickLastBuildTime.elapsed()) >
             (m_pmanager->m_iBuildTimeWindow + __random(0, m_pmanager->m_iBuildTimeRandomWindow));
   }

   bool ds_script::HasCompileOrLinkError()
   {
      sync_lock sl(mutex());

      string str;

      str = m_strError;

      if(str.find(" error(") >= 0)
         return true;
      if(str.find(" error ") >= 0)
         return true;
      if(str.find(" get_last_error ") >= 0)
         return true;
      return false;
   }

   bool ds_script::HasDelayedTempError()
   {

      return HasTempError() && HasTimedOutLastBuild();

   }


   bool ds_script::HasTempError()
   {
      sync_lock sl(mutex());
      // if m_strError is empty, sure there is a error... at least the
      // successfull compilation/linking message ("error message" => m_strError) should exist
      // If it is empty, it is considered a temporary error (due locks or race conditions...)
      if(m_strError.is_empty() || m_bShouldCalcTempError)
      {
         m_bShouldCalcTempError = false;
         m_bHasTempError = CalcHasTempError();
      }
      return m_bHasTempError;
   }

   bool ds_script::CalcHasTempError()
   {

      sync_lock sl(mutex());

      if (m_bHasTempOsError)
         return true;

      string str;

      str = m_strError;

      str.trim();

      if(str.is_empty())
         return true;

      {
         strsize iFind1 = str.find(" C1033:");
         if(iFind1 >= 0)
            return true;
      }
      {
         strsize iFind1 = str.find(" C1083:"); // Permission Denied
         if(iFind1 >= 0)
            return true;
      }
      {
         strsize iFind1 = str.find(" C1041:"); // fatal error C1041: cannot open program database
         if(iFind1 >= 0)
            return true;
      }
      {
         strsize iFind1 = str.find(".dll: does not exist.");
         if(iFind1 >= 0)
         {
            // if dll does not exist
            {
               strsize iFind1 = str.find(" error(");
               strsize iFind2 = str.find(" error ");
               strsize iFind3 = str.find("Linking...");
               // and have compile error (others than the ones above, that are considered temporary as they may be due temporary file locks, for example...).
               if((iFind3 >= 0 && ((iFind1 < iFind3 && iFind1 >= 0) ||
                                   (iFind2 < iFind3 && iFind2 >= 0))))
               {
                  return false;
               }
            }

         }
      }

      {
         strsize iFind1 = str.find("warning LNK4099:");
         if(iFind1 >= 0)
            return true;
      }
      {
         strsize iFind1 = str.find("fatal error LNK1168:");
         if(iFind1 >= 0)
            return true;
      }
      {
         strsize iFind1 = str.find(" error(");
         strsize iFind2 = str.find(" error ");
         strsize iFind3 = str.find("Linking...");
         if(iFind3 >= 0 && (iFind1 > iFind3 || iFind2 > iFind3))
         {
            return true;
         }
      }
      if(str.find(" get_last_error ") >= 0)
         return true;
      return false;
   }


   void ds_script::Load()
   {

      sync_lock sl(mutex());

      if(!Context.file().exists(m_strScriptPath))
      {

         if(HasTempError())
         {

            m_streamError << m_strScriptPath << ": does not exist because of \"temp\" error.";

         }
         else
         {

            m_streamError << m_strScriptPath << ": does not exist.";

         }

         m_lpfnCreateInstance = nullptr;

         return;

      }

      if (m_plibrary.is_null() || m_plibrary->is_closed())
      {

         m_plibrary.create(this);

         string strStagePath = m_pmanager->get_full_stage_path(m_strScriptPath);

         ::file_copy_dup(strStagePath, m_strScriptPath, true);

         m_plibrary->open(strStagePath, true);

         if(m_plibrary->is_closed())
         {

#ifdef LINUX

            const char * psz = dlerror();

#endif

            u32 dwMessageId = get_last_error();

            if(dwMessageId == 0x139)
            {

               debug_break();

            }

            TRACE("Error Message Id: %d\n", dwMessageId);

            string strError = get_system_error_message(::get_last_error());

            string str;

            str.Format("%d - ", ::get_last_error());

            m_streamError << strStagePath << " : LoadLibrary, get_last_error : " << str << strError;

         }

      }

      if (m_plibrary.is_set() && !m_plibrary->is_closed())
      {

         m_lpfnCreateInstance = m_plibrary->get < NET_NODE_CREATE_INSTANCE_PROC >("create_dynamic_source_script_instance");

         if (m_lpfnCreateInstance == nullptr)
         {

            TRACE("create_dynamic_source_script_instance error");

         }

      }

   }


   void ds_script::Unload()
   {

      if (m_bUnloading)
      {

         return;

      }

      __keep(m_bUnloading);

      m_evCreationEnabled.ResetEvent();

      sync_lock sl(mutex());

      if(m_plibrary != nullptr && m_plibrary->is_opened())
      {

         m_plibrary->m_bAutoUnload = true;

         m_plibrary->close();

         string strStagePath = m_pmanager->get_stage_path(m_strScriptPath);

         m_lpfnCreateInstance = (NET_NODE_CREATE_INSTANCE_PROC) nullptr;

      }

   }


   __pointer(script_instance) ds_script::create_instance()
   {

      sync_lock slCompiler(&Application.m_semCompiler);

      sync_lock sl(mutex());

      defer_build();

      __pointer(script_instance) pinstance;

      if(m_lpfnCreateInstance == nullptr)
      {

         return nullptr;

      }

      try
      {

         pinstance = ::move_transfer(m_lpfnCreateInstance());

      }
      catch (...)
      {

      }

      pinstance->m_strNote = m_strName;

      pinstance->m_pscript2 = this;

      pinstance->m_dwCreate = ::tick::now().u32();

      if (m_bNew)
      {

         m_bNew = false;

      }

      return pinstance;

   }


   void ds_script::defer_build()
   {

      sync_lock sl(mutex());

      if (m_plibrary.is_set() && !m_plibrary->is_closed())
      {

         return;

      }

      if (m_strSourcePath.find_ci("\\applications\\basic\\") > 0)
      {

         TRACE("/applications/basic/");

      }

      try
      {

         ::multithreading::set_priority(::priority_highest);

      }
      catch (...)
      {

      }

      string str;

      i32 iRetry = 0;

      bool bHasTempError = false;

      do
      {

         if (iRetry > 0)
         {

            Sleep((DWORD)__random(2000, 4000));

         }

         m_pmanager->m_pcompiler->compile(this);

         str = m_strError;

         if (iRetry == 0)
         {

            TRACE("Build: %s\n%s\n", m_strName.c_str(), str.c_str());

         }
         else
         {

            TRACE("Retry(%d): %s\nError: %s\n", iRetry, m_strName.c_str(), str.c_str());

         }

         if (HasCompileOrLinkError())
         {

            m_bHasFatalError = true;

            break;

         }

         iRetry++;

      }
      while ((bHasTempError = HasTempError()) && iRetry < 8 && ::thread_get_run());

      if (!::thread_get_run())
      {

         return;

      }

      m_tickLastBuildTime = ::get_tick();

      m_ft = get_file_time(m_strSourcePath);

      Load();

      if (!::thread_get_run())
      {

         return;

      }

      m_bShouldBuild = false;

      {

         sync_lock sl(&m_pmanager->m_mutexShouldBuild);

         m_pmanager->m_mapShouldBuild[m_strSourcePath] = false;

      }

   }


   //::aura::application * ds_script::get_context_application() const
   //{

   //   return m_pmanager->get_context_application();

   //}


} // namespace dynamic_source



