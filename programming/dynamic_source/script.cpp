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


   script::script()
   {

      m_bNew = true;

      defer_create_mutex();

      m_pfileError.create_new();

      m_streamError.m_p = m_pfileError;

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

      auto elapsed = m_millisLastVersionCheck.elapsed();

      if(elapsed < 5_s)
      {

         return m_bLastVersionCheck;

      }

      m_millisLastVersionCheck.Now();

      synchronous_lock synchronouslock(mutex());

      bool bMatches = false;

      auto ft = get_filetime_set(m_strSourcePath);

      bMatches = m_ftDs == ft;

      m_bLastVersionCheck = bMatches;
      return bMatches;
   }

   bool ds_script::ShouldBuild()
   {

      synchronous_lock synchronouslock(mutex());

      if (m_bHasFatalError)
      {

         return false;

      }

      bool bManagerShouldBuild = m_pmanager->should_build(m_strSourcePath);

      if (bManagerShouldBuild)
      {

         return true;

      }

      bool bShouldBuild = m_bShouldBuild;

      bool bHasDelayedTempError = HasDelayedTempError();

      bool bDoesntMatchVersion = !DoesMatchVersion();

      return bShouldBuild || bHasDelayedTempError || bDoesntMatchVersion;

   }

   void ds_script::on_start_build()
   {

      synchronous_lock synchronouslock(mutex());

      m_bShouldCalcTempError     = true;

      m_bShouldBuild             = false;

      m_bHasTempOsError          = false;

      m_streamError.m_p->set_size(0);

      m_strError.Empty();

      Unload();

   }

   bool ds_script::HasTimedOutLastBuild()
   {
      synchronous_lock synchronouslock(mutex());
      return (m_millisLastBuildTime.elapsed()) >
             (m_pmanager->m_iBuildTimeWindow + __random(0, m_pmanager->m_iBuildTimeRandomWindow));
   }

   bool ds_script::HasCompileOrLinkError()
   {
      synchronous_lock synchronouslock(mutex());

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

      bool bHasTempError = HasTempError();

      bool bHasTimedOutLastBuild = HasTimedOutLastBuild();

      return bHasTempError && bHasTimedOutLastBuild;

   }


   bool ds_script::HasTempError()
   {
      synchronous_lock synchronouslock(mutex());
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

      synchronous_lock synchronouslock(mutex());

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

      synchronous_lock synchronouslock(mutex());

      auto pcontext = get_context();

      if(!pcontext->m_papexcontext->file().exists(m_strScriptPath))
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


#ifdef WINDOWS_DESKTOP

            u32 dwMessageId = GetLastError();

            if(dwMessageId == 0x139)
            {

               ASSERT(FALSE);

            }

            TRACE("Error Message Id: %d\n", dwMessageId);

            string strError = get_system_error_message(dwMessageId);

            string str;

            str.Format("%d - ", dwMessageId);

            m_streamError << strStagePath << " : LoadLibrary, get_last_error : " << str << dwMessageId;

#endif

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

      synchronous_lock synchronouslock(mutex());

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

      __pointer(::aura::application) papplication = get_application();

      synchronous_lock slCompiler(&papplication->m_semCompiler);

      synchronous_lock synchronouslock(mutex());

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

      pinstance->m_dwCreate = ::millis::now().u32();

      if (m_bNew)
      {

         m_bNew = false;

      }

      return pinstance;

   }


   void ds_script::defer_build()
   {

      synchronous_lock synchronouslock(mutex());

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

         ::parallelization::set_priority(::priority_highest);

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

            sleep((::millis)__random(2000, 4000));

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
      while ((bHasTempError = HasTempError()) && iRetry < 8 && ::task_get_run());

      if (!::task_get_run())
      {

         return;

      }

      m_millisLastBuildTime= ::millis::now();

      //m_ft = get_filetime_set(m_strSourcePath);

      Load();

      if (!::task_get_run())
      {

         return;

      }

      m_bShouldBuild = false;

      {

         synchronous_lock synchronouslock(&m_pmanager->m_mutexShouldBuild);

         m_pmanager->m_mapShouldBuild[m_strSourcePath] = false;

      }

   }


   //::aura::application * ds_script::get_application() const
   //{

   //   return m_pmanager->get_application();

   //}


} // namespace dynamic_source



