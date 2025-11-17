#include "framework.h"
#include "script_cache.h"
#include "script_manager.h"
#include "script_instance.h"
#include "ds_script.h"
#include "acme/crypto/rsa.h"
#include "acme/filesystem/filesystem/file_system.h"
#include "acme/parallelization/synchronous_lock.h"
#include "programming/heating_up_exception.h"


namespace dynamic_source
{


   script_cache::script_cache()
   {

      m_pmanager = nullptr;

      defer_create_synchronization();

   }


   script_cache::~script_cache()
   {

   }


   void script_cache::initialize_script_cache(script_manager* pscriptmanager)
   {

      //auto estatus = 
      
      ::object::initialize(pscriptmanager);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      m_pmanager = pscriptmanager;

      //return estatus;

   }


   void script_cache::destroy()
   {

      //m_pmanager.release();

      for (auto& pscript : m_mapScript.payloads())
      {

         pscript.defer_destroy();

      }

      m_mapScript.clear();

      ::object::destroy();

   }


   //::pointer<ds_script>script_cache::allocate_ds_script(const ::scoped_string & scopedstrName)
   //{

   //   auto pscript = øcreate_new< ds_script >();

   //   pscript->m_pmanager = m_pmanager;

   //   pscript->m_strName = scopedstrName;

   //   return ::transfer(pscript);

   //}


   ::pointer<ds_script>script_cache::allocate_ds_script(const ::file_system_cache_item & pfilesystemcacheitem)
   {

      auto pscript = øcreate_new< ds_script >();

      pscript->set_manager(m_pmanager);

      //pfilesystemcacheitem->m_particlea[m_pmanager->m_iFileSystemScriptSlotIndex] = pscript;

      pscript->m_pfilesystemcacheitem = pfilesystemcacheitem;

      //pscript->m_path1 = pfilesystemcacheitem->path();

      //pscript->m_pfilesystemitem = pfilesystemcacheitem;

      return ::transfer(pscript);

   }

   
   script * script_cache::get(const ::file_system_cache_item & pfilesystemcacheitem, class ::time& timeLockElapsed, class ::time& timeLookUpElapsed)
   {

      class ::time timeStart;

      timeStart.Now();

      //auto pathReal = pfilesystemcacheitem->path();
//      string strName(scopedstrName);
//
//#ifdef WINDOWS
//
//      strName.replace_with("\\", "/");
//
//#endif

      //_synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      critical_section_lock criticalsectionlock(&m_criticalsectionScript);

      class ::time timeLock;

      timeLock.Now();

      timeLockElapsed = timeLock - timeStart;

      //auto & pscript = m_map[pathReal];
      auto& pscript = m_mapScript[pfilesystemcacheitem];

      class ::time timeLookUp;

      timeLookUp.Now();

      timeLookUpElapsed = timeLookUp - timeLock;

      //if (pscript.is_set()
        // && pscript->m_path == pfilesystemcacheitem->path())
      if (pscript.is_set())
      {

         return pscript;

      }

      return pscript = allocate_ds_script(pfilesystemcacheitem);

   }


   script * script_cache::register_script(const ::file_system_cache_item & pfilesystemcacheitem, script * pscript)
   {

//      string strName(scopedstrName);
//
//#ifdef WINDOWS
//
//      strName.find_replace("/", "\\");
//
//#endif

      //_single_lock synchronouslock(this->synchronization(), true);

      critical_section_lock criticalsectionlock(&m_criticalsectionScript);

      //auto iterator = m_map.find(pfilesystemcacheitem->path());

      auto iterator = m_mapScript.find(pfilesystemcacheitem);

      if(iterator)
      {

         iterator->payload() = pscript;

         return pscript;

      }

      pscript->set_manager(m_pmanager);

      pscript->m_pfilesystemcacheitem = pfilesystemcacheitem;

      //pscript->m_path1 = pfilesystemcacheitem->path();

      //pscript->m_pfilesystemitem = pfilesystemcacheitem;

      return pscript;

   }


   ::pointer<script_instance>script_cache::create_instance_2025(const ::file_system_cache_item& pfilesystemcacheitem, ::pointer<script>& pscript)
   {

      pscript = pfilesystemcacheitem->m_particlea[m_pmanager->m_iFileSystemScriptSlotIndex];

      //if(string_begins(scopedstrName, "netnode://"))
      //{
      //   
      //   single_lock synchronouslock(synchronization(), true);

      //   pscript  = get(scopedstrName);

      //   synchronouslock.unlock();

      //   return pscript->create_instance();

      //}

      class ::time timeShouldBuild;

      class ::time timeCreateInstance;

      item_n40585 itemN40585;

      itemN40585.m_strPath = pfilesystemcacheitem.m_strName2;

      if (!pscript)
      {

         auto pathNetnode = m_pmanager->m_pathNetnodePath;

         if (itemN40585.m_strPath.case_insensitive_begins_eat(pathNetnode))
         {

            itemN40585.m_strPath.case_insensitive_begins_eat("/net/");

         }

         pscript = get(pfilesystemcacheitem, itemN40585.m_timeLockElapsed, itemN40585.m_timeLookUpElapsed);

         if (::is_null(pscript))
         {

            return nullptr;

         }

      }

      class ::time timeLock2;

      timeLock2.Now();

      {

         _single_lock slScript(pscript->synchronization());

         if (!slScript._wait(5_s))
         {

            throw ::heating_up_exception("Compiling script " + pfilesystemcacheitem->path());

         }

      }

      itemN40585.m_timeLock2Elapsed = timeLock2.elapsed();

      if (!pscript->m_bShouldBuild)
      {

         timeShouldBuild.Now();

         if (pscript->ShouldBuild())
         {

            pscript = allocate_ds_script(pfilesystemcacheitem);

            //_synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

            //m_map[pfilesystemcacheitem->path()] = pscript;

            {

               critical_section_lock criticalsectionlock(&m_criticalsectionScript);

               m_mapScript[pfilesystemcacheitem] = pscript;

            }

            return pscript->create_instance();

         }

         itemN40585.m_timeShouldBuildElapsed = timeShouldBuild.elapsed();

      }

      timeCreateInstance.Now();

      auto pscriptinstance = pscript->create_instance();

      if (pscriptinstance)
      {

         itemN40585.m_timeCreateInstanceElapsed = timeCreateInstance.elapsed();

         //s      itemN40585.m_timeRealPathMapAllocationElapsed = pscriptinstance->m_timeRealPathMapAllocationElapsed;

         pscriptinstance->m_itemN40585 = itemN40585;

         //pscriptinstance->m_timeLockElapsed = timeLockElapsed;

         //pscriptinstance->m_timeLookUpElapsed = timeLookUpElapsed;

         //pscriptinstance->m_timeLock2Elapsed = timeLock2Elapsed;

         //pscriptinstance->m_timeShouldBuildElapsed = timeShouldBuildElapsed;

      }

      return pscriptinstance;

   }


   ::pointer<script_instance>script_cache::create_instance(const ::file_system_cache_item & pfilesystemcacheitem, ::pointer<script> & pscript)
   {

      critical_section_lock criticalsectionlock(&file_system()->m_criticalsectionaFileSystemItemSlot[m_pmanager->m_iFileSystemScriptSlotIndex]);

      const char* pszReal = pfilesystemcacheitem->m_pathReal1.c_str();

      const char* pszLogical = pfilesystemcacheitem->m_pathLogical1.c_str();

      auto & pparticleFileSystemItem = pfilesystemcacheitem->m_particlea[m_pmanager->m_iFileSystemScriptSlotIndex];

      pscript = pparticleFileSystemItem;

      criticalsectionlock.unlock();

      //if(string_begins(scopedstrName, "netnode://"))
      //{
      //   
      //   single_lock synchronouslock(synchronization(), true);

      //   pscript  = get(scopedstrName);

      //   synchronouslock.unlock();

      //   return pscript->create_instance();

      //}

      //class ::time timeShouldBuild;

      class ::time timeCreateInstance;

      item_n40585 itemN40585;

      itemN40585.m_strPath = pfilesystemcacheitem.m_strName2;

      auto pathNetnode = m_pmanager->m_pathNetnodePath;

      if (itemN40585.m_strPath.case_insensitive_begins_eat(pathNetnode))
      {

         itemN40585.m_strPath.case_insensitive_begins_eat("/net/");

      }

      if (itemN40585.m_strPath.case_insensitive_contains("monitor"))
      {

         information() << "monitor";

      }

      if (!pscript)
      {

         auto pscriptNew = get(pfilesystemcacheitem, itemN40585.m_timeLockElapsed, itemN40585.m_timeLookUpElapsed);

         if (::is_null(pscriptNew))
         {

            return nullptr;

         }

         criticalsectionlock.lock();

         pscript = pscriptNew;

         pparticleFileSystemItem = pscript;

         criticalsectionlock.unlock();

      }


      //class ::time timeStart;

      //timeStart.Now();

      //{

      //   _single_lock slScript(pscript->synchronization());

      //   if (!slScript._wait(5_s))
      //   {

      //      throw ::heating_up_exception("Compiling script " + pfilesystemcacheitem->path());

      //   }

      //}

      //class ::time timeLock2;

      //timeLock2.Now();

      //itemN40585.m_timeLock2Elapsed = timeLock2 - timeStart;

      if (pscript->m_bShouldBuild)
      {

         _single_lock slScript(pscript->synchronization());

         if (!slScript._wait(5_s))
         {

            throw ::heating_up_exception("script couldn't be locked in 5s");

            return nullptr;

         }

         if (pscript->m_bBuilding)
         {

            throw ::heating_up_exception("script is building");

            return nullptr;

         }

         pscript->m_bBuilding = true;

         slScript.unlock();

         try
         {

            if (pfilesystemcacheitem.m_strName2.case_insensitive_contains("monitor"))
            {

               information() << "monitor";

            }
            else if (pfilesystemcacheitem.m_strName2.case_insensitive_contains("cc/ca2"))
            {

               information() << "cc/ca2";

            }

            pscript->defer_build();

            pscript->m_bBuilding = false;

            pscript->m_bShouldBuild = false;

         }
         catch (const heating_up_exception& exception)
         {

            slScript._lock();

            pscript->m_bBuilding = false;

            throw exception;

         }
         catch (const ::exception& exception)
         {

            slScript._lock();

            pscript->m_bBuilding = false;

            return nullptr;

         }
         catch (...)
         {

            slScript._lock();

            pscript->m_bBuilding = false;

            return nullptr;

         }

         //slScript._lock();

         //pscript->m_bBuilding = false;

         //   if (pscript->ShouldBuild())
         //   {

         //      pscript = allocate_ds_script(pfilesystemcacheitem);

         //      //_synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

         //      //m_map[pfilesystemcacheitem->path()] = pscript;

         //      {

         //         critical_section_lock criticalsectionlock(&m_criticalsectionScript);

         //         m_mapScript[pfilesystemcacheitem] = pscript;

         //      }

         //      return pscript->create_instance();

         //   }

         //   //timeShouldBuild.Now();

         //   //itemN40585.m_timeShouldBuildElapsed = timeShouldBuild - timeLock2;

         //}
         //else
         //{

         //   timeShouldBuild = timeLock2;

         //}

      }

      timeCreateInstance.Now();

      auto pscriptinstance = pscript->create_instance();

      if (pscriptinstance)
      {

         //itemN40585.m_timeCreateInstanceElapsed = timeCreateInstance - timeShouldBuild;

         itemN40585.m_timeCreateInstanceElapsed = timeCreateInstance.elapsed();

         itemN40585.m_timeCreateInstanceStrictElapsed = pscriptinstance->m_timeCreateInstanceElapsed;

         itemN40585.m_timeInit1Elapsed = pscriptinstance->m_timeInit1Elapsed;

         itemN40585.m_timeInit2Elapsed = pscriptinstance->m_timeInit2Elapsed;

         //s      itemN40585.m_timeRealPathMapAllocationElapsed = pscriptinstance->m_timeRealPathMapAllocationElapsed;

         pscriptinstance->m_itemN40585 = itemN40585;

         //pscriptinstance->m_timeLockElapsed = timeLockElapsed;

         //pscriptinstance->m_timeLookUpElapsed = timeLookUpElapsed;

         //pscriptinstance->m_timeLock2Elapsed = timeLock2Elapsed;

         //pscriptinstance->m_timeShouldBuildElapsed = timeShouldBuildElapsed;

      }

      return pscriptinstance;

   }


   //void script_cache::cache(script * pscript)
   //{

   //   single_lock synchronouslock(mutex(), true);

   //   m_map.set_at(pscript->m_strName, pscript);

   //}


   void script_cache::uncache(script * pscript)
   {

      //_single_lock synchronouslock(synchronization(), true);

      critical_section_lock criticalsectionlock(&m_criticalsectionScript);

      //m_map.erase(pscript->m_path);
      //m_map.erase(pscript->m_pfilesystemitem);
      //m_mapScript.erase(pscript->m_pfilesystemitem)
      m_mapScript.erase(pscript->m_pfilesystemcacheitem);

   }


   void script_cache::set_all_out_of_date()
   {
      return;
//   single_lock synchronouslock(mutex(), true);
//   ::pointer<script>pscript;
//   string strName;
//   POSITION pos = m_map.get_start_position();
//   while(pos != nullptr)
//   {
//      m_map.get_next_assoc(pos, strName, pscript);
//
//      ds_script * pdsscript = dynamic_cast < ds_script * > (pscript.m_p);
//      if(pdsscript != nullptr)
//      {
//         pdsscript->m_bShouldBuild = true;
//      }
//
//   }
   }


   void script_cache::set_out_of_date(const ::scoped_string & scopedstr)
   {

      if (scopedstr.is_empty())
      {

         return;

      }

      ::file::path pathChanged = scopedstr;

      //single_lock synchronouslock(synchronization(), true);

      critical_section_lock criticalsectionlock(&m_criticalsectionScript);

      for (auto & pair : m_mapScript)
      {

         ::pointer<ds_script>pdsscript = pair.element2();

         if (pdsscript != nullptr)
         {

            ::file::path path = pdsscript->m_strSourcePath;

            if (path.case_insensitive_ends(pathChanged))
            {

               pdsscript->m_bShouldBuild = true;

            }

         }

      }

   }


} // namespace dynamic_source



