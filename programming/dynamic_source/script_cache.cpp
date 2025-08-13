#include "framework.h"
#include "script_cache.h"
#include "script_manager.h"
#include "ds_script.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/crypto/rsa.h"
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

      for (auto& pscript : m_map.payloads())
      {

         pscript.defer_destroy();

      }

      m_map.clear();

      ::object::destroy();

   }


   ::pointer<ds_script>script_cache::create_new_ds_script(const ::scoped_string & scopedstrName)
   {

      auto pscript = __create_new< ds_script >();

      pscript->m_pmanager = m_pmanager;

      pscript->m_strName = scopedstrName;

      return ::transfer(pscript);

   }


   script * script_cache::get(const ::scoped_string & scopedstrName)
   {

      string strName(scopedstrName);

#ifdef WINDOWS

      strName.replace_with("\\", "/");

#endif

      synchronous_lock synchronouslock(this->synchronization());

      auto iterator = m_map.find(strName);

      if (::is_set(iterator)
         && iterator->element2().is_set()
         && iterator->element2()->m_strName == strName)
      {

         return iterator->element2();

      }

      return iterator->payload() = create_new_ds_script(strName);

   }


   script * script_cache::register_script(const ::scoped_string & scopedstrName, script * pscript)
   {

      string strName(scopedstrName);

#ifdef WINDOWS

      strName.find_replace("/", "\\");

#endif

      single_lock synchronouslock(synchronization(), true);

      auto iterator = m_map.find(strName);

      if(iterator)
      {

         iterator->payload() = pscript;

         return pscript;

      }

      pscript->m_pmanager = m_pmanager;

      pscript->m_strName = strName;

      return pscript;

   }


   ::pointer<script_instance>script_cache::create_instance(const ::scoped_string & scopedstrName, ::pointer<script> & pscript)
   {

      pscript = nullptr;

      if(string_begins(scopedstrName, "netnode://"))
      {
         
         single_lock synchronouslock(synchronization(), true);

         pscript  = get(scopedstrName);

         synchronouslock.unlock();

         return pscript->create_instance();

      }

      string strName(scopedstrName);
      
      strName = m_pmanager->real_path(scopedstrName);
      
      if (strName.is_empty())
      {

         strName = m_pmanager->real_path(string(scopedstrName) + ".ds");

      }
      
      strName.find_replace("\\", "/");

      m_pmanager->include_has_script(strName);

      pscript = get(strName);

      if (::is_null(pscript))
      {

         return nullptr;

      }

      _single_lock slScript(pscript->synchronization());

      if (!slScript._wait(5_s))
      {
         
         throw ::heating_up_exception("Compiling script " + scopedstrName);

      }

      int iTry = 0;

      while(!pscript->m_bNew && pscript->ShouldBuild())
      {

         slScript.unlock();

         pscript = create_new_ds_script(strName);

         slScript._lock();

         iTry++;

         if (iTry > 5)
         {

            return nullptr;

         }

      }

      return pscript->create_instance();

   }


   //void script_cache::cache(script * pscript)
   //{

   //   single_lock synchronouslock(mutex(), true);

   //   m_map.set_at(pscript->m_strName, pscript);

   //}


   void script_cache::uncache(script * pscript)
   {

      single_lock synchronouslock(synchronization(), true);

      m_map.erase_key(pscript->m_strName);

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

      single_lock synchronouslock(synchronization(), true);

      for (auto & pair : m_map)
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


