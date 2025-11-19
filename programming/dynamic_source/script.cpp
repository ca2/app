#include "framework.h"
#include "fallback_script_instance.h"
#include "script.h"
#include "script_instance.h"
#include "ds_script.h"
#include "script_manager.h"
#include "script_compiler.h"
#include "acme/filesystem/file/memory_file.h"
#include "acme/filesystem/filesystem/file_system.h"
#include "acme/parallelization/mutex.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/keep.h"
#include "acme/platform/node.h"
#include "acme/platform/system.h"
#include "acme/prototype/mathematics/_random.h"
#include "acme/prototype/prototype/prototype.h"
#include "acme/platform/library.h"
#include "acme/crypto/rsa.h"
#include "acme/filesystem/filesystem/directory_context.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "aura/platform/application.h"


#include "acme/_operating_system.h"


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

      m_bBuilding = false;

      //m_pfilesystemitem = nullptr;

      //m_pscriptmanager1 = nullptr;

      m_bShouldBuild = true;

      //m_bShouldRunOnAfterCreate = true;


   }


   script::~script()
   {

   }



   void script::on_initialize_particle()
   {

      //auto estatus = 

      defer_create_synchronization();

      
      ::object::on_initialize_particle();

      //if(!estatus)
      //{

      //   return estatus;

      //}

      øconstruct_new(m_pfileError);

      m_textstreamError.m_pfile = m_pfileError;

      //return estatus;

   }


   void script::destroy()
   {

      //m_pmanager.release();

      m_pfileError.defer_destroy();

      m_textstreamError.m_pfile.release();

      ::object::destroy();

   }


   void script::defer_build()
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


   void script::set_manager(script_manager* pscriptmanager1)
   {

      m_pscriptmanager1 = pscriptmanager1;

      //m_pfilesysteminterface = pscriptmanager1;

   }


   void script::load_stringtable(const ::scoped_string& scopedstrLoad)
   {


   }

   ::file_system_cache_item script::netnode_file_path(const ::scoped_string& scopedstrName, ::file_system_interface * pfilesysteminterface)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      auto & pfilesystemcacheitem = m_mapScriptPath[scopedstrName];

      if (!pfilesystemcacheitem.is_ok())
      {

         pfilesystemcacheitem = m_pscriptmanager1->netnode_file_path(scopedstrName, pfilesysteminterface);

      }

      return pfilesystemcacheitem;

   }


   void script::folder_enumerate(::file::listing& listing, int iId, const ::file::path& pathFolder, const ::function < void(::file::listing& listing) >& procedureListing)
   {

      if(!m_pmutexFolderEnumerate)
      {

         _synchronous_lock synchronouslock(m_pscriptmanager1->synchronization());

         if (!m_pmutexFolderEnumerate)
         {

            m_pmutexFolderEnumerate = node()->create_mutex();

         }

      }

      _synchronous_lock synchronouslock(this->m_pmutexFolderEnumerate);

      auto& pfolderlisting = m_mapFolderEnumerate[iId][pathFolder];

      if (!pfolderlisting || pfolderlisting->m_timeLastEnumeration.elapsed() > 1_hour)
      {

         ødefer_construct_new(pfolderlisting);

         pfolderlisting->m_listing.initialize(this);

         //pfolderlisting->m_listing.set_file_listing(pathFolder, edepth);

         procedureListing(pfolderlisting->m_listing);

         directory()->enumerate(pfolderlisting->m_listing);

      }

      listing = pfolderlisting->m_listing;

   }


   //::file_system_cache_item script::real_path2(const ::scoped_string& scopedstrBase, const ::scoped_string& scopedstr)
   //{

   //   _synchronous_lock synchronouslock(this->synchronization());

   //   auto& pfilesystemcacheitem = m_mapRealPath2[scopedstrBase][scopedstr];

   //   if (!pfilesystemcacheitem.is_ok())
   //   {

   //      pfilesystemcacheitem = m_pscriptmanager1->_real_path2(scopedstrBase, scopedstr);

   //   }

   //   return pfilesystemcacheitem;

   //}

   ds_script::ds_script()
   {

      m_bHasFatalError = false;
      m_lpfnCreateInstance       = nullptr;
      m_bShouldBuild             = true;
      m_bShouldCalcTempError     = true;
      m_bHasTempError            = false;
      m_bHasTempOsError          = false;
      m_bUnloading               = false;
      m_happeningCreationEnabled.set_happening();



   }





   ds_script::~ds_script()
   {

      Unload();

   }


   bool ds_script::DoesMatchVersion()
   {

      auto elapsed = m_timeLastVersionCheck.elapsed();

      if(elapsed < 5_s)
      {

         return m_bLastVersionCheck;

      }

      m_timeLastVersionCheck.Now();

      synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      bool bMatches = false;

      auto ft = get_file_time_set(m_strSourcePath);

      bMatches = m_ftDs == ft;

      m_bLastVersionCheck = bMatches;

      return bMatches;

   }


   bool ds_script::ShouldBuild()
   {

      _synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      if (m_bHasFatalError)
      {

         return false;

      }

      if (m_strSourcePath.is_empty())
      {

         return true;

      }

      if (m_timeLastShouldBuildCheck.is_time_out_ok_with_update(2_s))
      {

         return false;

      }

      bool bManagerShouldBuild = m_pscriptmanager1->should_build(m_strSourcePath);

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

      _synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      m_bShouldCalcTempError     = true;

      m_bShouldBuild             = false;

      m_bHasTempOsError          = false;

      m_textstreamError.m_pfile->set_size(0);

      m_strError.empty();

      Unload();

   }


   bool ds_script::HasTimedOutLastBuild()
   {

      _synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      auto psystem = system();

      auto pprimitive = psystem->prototype();

      return (m_timeLastBuildTime.elapsed()) > 
         m_pscriptmanager1->m_timeBuildInterval +
         pprimitive->random(0_s, m_pscriptmanager1->m_timeTimeRandomInterval);
   }


   bool ds_script::HasCompileOrLinkError()
   {

      _synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      string str;

      str = m_strError;

      if(str.contains(" errorf("))
         return true;
      if(str.contains(" error "))
         return true;
      if(str.contains(" get_last_error "))
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

      _synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
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

      _synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      if (m_bHasTempOsError)
      {

         return true;

      }

      string str;

      str = m_strError;

      str.trim();

      if(str.is_empty())
         return true;

      {
         character_count iFind1 = str.find_index(" C1033:");
         if(iFind1 >= 0)
            return true;
      }
      {
         character_count iFind1 = str.find_index(" C1083:"); // Permission Denied
         if(iFind1 >= 0)
            return true;
      }
      {
         character_count iFind1 = str.find_index(" C1041:"); // fatal error C1041: cannot open program database
         if(iFind1 >= 0)
            return true;
      }
      {
         character_count iFind1 = str.find_index(".dll: does not exist.");
         if(iFind1 >= 0)
         {
            // if dll does not exist
            {
               character_count iFind1 = str.find_index(" errorf(");
               character_count iFind2 = str.find_index(" error ");
               character_count iFind3 = str.find_index("Linking...");
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
         character_count iFind1 = str.find_index("warning LNK4099:");
         if(iFind1 >= 0)
            return true;
      }
      {
         character_count iFind1 = str.find_index("fatal error LNK1168:");
         if(iFind1 >= 0)
            return true;
      }
      {
         character_count iFind1 = str.find_index(" errorf(");
         character_count iFind2 = str.find_index(" error ");
         character_count iFind3 = str.find_index("Linking...");
         if(iFind3 >= 0 && (iFind1 > iFind3 || iFind2 > iFind3))
         {
            return true;
         }
      }
      if(str.contains(" get_last_error "))
         return true;
      return false;
   }


   void ds_script::Load()
   {

      synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      // auto pcontext = get_context();

      if(!file()->exists(m_strScriptPath))
      {

         if(HasTempError())
         {

            m_textstreamError << m_strScriptPath << ": does not exist because of \"temp\" error.";

         }
         else
         {

            m_textstreamError << m_strScriptPath << ": does not exist.";

         }

         m_lpfnCreateInstance = nullptr;

         return;

      }

      if (m_plibrary.is_null() || m_plibrary->is_closed())
      {

         øconstruct(m_plibrary);

         string strStagePath = m_pscriptmanager1->get_full_stage_path(m_strScriptPath);

         file_system()->copy(strStagePath, m_strScriptPath, true);

         m_plibrary->open(strStagePath);

         if(m_plibrary->is_closed())
         {

#ifdef LINUX

            const ::scoped_string & scopedstr = dlerror();

#endif


#ifdef WINDOWS_DESKTOP

            unsigned int dwMessageId = GetLastError();

            if(dwMessageId == 0x139)
            {

               ASSERT(FALSE);

            }

            informationf("Error Message Id: %d\n", dwMessageId);

            string strError = ::windows::last_error_message(dwMessageId);

            string str;

            str.formatf("%d - ", dwMessageId);

            m_textstreamError << strStagePath << " : LoadLibrary, get_last_error : " << str << dwMessageId;

#endif

         }

      }

      if (m_plibrary.is_set() && !m_plibrary->is_closed())
      {

         m_lpfnCreateInstance = m_plibrary->get < NET_NODE_CREATE_INSTANCE_PROC >("create_dynamic_source_script_instance");

         if (m_lpfnCreateInstance == nullptr)
         {

            informationf("create_dynamic_source_script_instance error");

         }

      }

   }


   void ds_script::Unload()
   {

      if (m_bUnloading)
      {

         return;

      }

      KEEP(m_bUnloading);

      m_happeningCreationEnabled.reset_happening();

      synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      if(m_plibrary != nullptr && m_plibrary->is_opened())
      {

         //m_plibrary->m_bAutoUnload = true;

         m_plibrary->close();

         string strStagePath = m_pscriptmanager1->get_stage_path(m_strScriptPath);

         m_lpfnCreateInstance = (NET_NODE_CREATE_INSTANCE_PROC) nullptr;

      }

   }


   ::pointer<script_instance>ds_script::create_instance()
   {

      if (m_bShouldBuild)
      {

         return {};

      }

      auto timeCreateInstance = ::time::now();

      ::pointer<script_instance>pinstance;

      try
      {

         if (m_lpfnCreateInstance)
         {

            pinstance = ::pointer_transfer(m_lpfnCreateInstance());

         }

      }
      catch (...)
      {

      }


      auto timeInit1 = ::time::now();

      if (!pinstance)
      {

         pinstance = øcreate_new<fallback_script_instance>();

      }

      pinstance->m_strNote = m_pfilesystemcacheitem->path();





      // this call is expensive... trying to not call it...
      //pinstance->initialize(this);


      // surgical initialization after profiling/measurements hard work...
      pinstance->m_papplication = m_papplication;
      // netnode::script_interface app_consumer m_papp should be initialized where
      // netnode is accessible...
      //pinstance->initialize_script_instance_script(this);:
      pinstance->m_pscriptmanager1 = m_pscriptmanager1;
      pinstance->m_pscript1 = this;


      auto timeInit2 = ::time::now();

      //pinstance->initialize_script_instance(this, pscriptinterfaceParent1);

      //pinstance->m_timeInit2Elapsed = timeInit2.elapsed();

      pinstance->m_timeInit1Elapsed = timeInit2 - timeInit1;

      pinstance->m_timeCreateInstanceElapsed = timeInit1 - timeCreateInstance;

      pinstance->m_prealpathinterfacecache = this;

      pinstance->m_timeCreate.Now();

      //if (m_bNew)
      //{

      //   m_bNew = false;

      //}

      return pinstance;

   }


   void ds_script::destroy()
   {

      Unload();

      script::destroy();


   }


   void ds_script::defer_build()
   {

      _synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      if (m_plibrary.is_set() && !m_plibrary->is_closed())
      {

         return;

      }

      if (!ShouldBuild())
      {

         return;

      }

      if (m_strSourcePath.case_insensitive_find_index("\\applications\\basic\\") > 0)
      {

         informationf("/applications/basic/");

      }

      try
      {

         ::parallelization::set_priority(::e_priority_highest);

      }
      catch (...)
      {

      }

      string str;

      int iRetry = 0;

      bool bHasTempError = false;

      do
      {

         if (iRetry > 0)
         {

            synchronouslock.unlock();

            preempt(system()->prototype()->random(2._s, 4._s));

            synchronouslock._lock();

         }

         if (m_strSourcePath.case_insensitive_contains("monitor"))
         {

            information() << "monitor";

         }

         m_pscriptmanager1->m_pcompiler->compile(this);

         str = m_strError;

         if (iRetry == 0)
         {

            information() << "Build: " << m_pfilesystemcacheitem->path();
            informationf(str);

         }
         else
         {

            information() << "Retry("<<iRetry<<"): "<< m_pfilesystemcacheitem->path() <<"\nError: " << str.c_str();

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

      m_timeLastBuildTime= ::time::now();

      //m_ft = get_file_time_set(m_strSourcePath);

      Load();

      if (!::task_get_run())
      {

         return;

      }

      m_bShouldBuild = false;

      {

         _synchronous_lock synchronouslock(m_pscriptmanager1->m_pmutexShouldBuild, DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

         m_pscriptmanager1->m_mapShouldBuild2[m_strSourcePath] = false;

      }

   }


   //::aura::application * ds_script::get_app() const
   //{

   //   return m_pmanager->get_app();

   //}


} // namespace dynamic_source



