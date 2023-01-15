#include "framework.h"
#include "script_cache.h"
#include "script_manager.h"
#include "ds_script.h"
#include "acme/parallelization/synchronous_lock.h"
#include "apex/crypto/rsa.h"


namespace dynamic_source
{


   script_cache::script_cache()
   {

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


   ::pointer<ds_script>script_cache::create_new_ds_script(const ::string & strName)
   {

      auto pscript = __create_new< ds_script >();

      pscript->m_pmanager = m_pmanager;

      pscript->m_strName = strName;

      return ::transfer(pscript);

   }


   script * script_cache::get(const ::string & lpcszName)
   {

      string strName(lpcszName);

#ifdef WINDOWS

      strName.replace_with("\\", "/");

#endif

      synchronous_lock synchronouslock(this->synchronization());

      auto passoc = m_map.get_item(strName);

      if (::is_set(passoc)
         && passoc->element2().is_set()
         && passoc->element2()->m_strName == strName)
      {

         return passoc->element2();

      }

      return passoc->payload() = create_new_ds_script(strName);

   }


   script * script_cache::register_script(const ::string & lpcszName, script * pscript)
   {

      string strName(lpcszName);

#ifdef WINDOWS

      strName.find_replace("/", "\\");

#endif

      single_lock synchronouslock(synchronization(), true);

      auto ppair = m_map.find_item(strName);

      if(ppair)
      {

         ppair->payload() = pscript;

         return pscript;

      }

      pscript->m_pmanager = m_pmanager;

      pscript->m_strName = strName;

      return pscript;

   }

   ::pointer<script_instance>script_cache::create_instance(const ::string & lpcszName, ::pointer<script> & pscript)
   {

      pscript = nullptr;

      if(string_begins(lpcszName, "netnode://"))
      {
         
         single_lock synchronouslock(synchronization(), true);

         pscript  = get(lpcszName);

         synchronouslock.unlock();

         return pscript->create_instance();

      }

      string strName(lpcszName);
      
      strName = m_pmanager->real_path(lpcszName);
      
      if (strName.is_empty())
      {

         strName = m_pmanager->real_path(string(lpcszName) + ".ds");

      }
      
      strName.find_replace("\\", "/");

      m_pmanager->include_has_script(strName);

      pscript = get(strName);

      if (::is_null(pscript))
      {

         return nullptr;

      }

      synchronous_lock slScript(pscript->synchronization());

      if(!pscript->m_bNew && pscript->ShouldBuild())
      {

         pscript = create_new_ds_script(strName);

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

      m_map.erase_item(pscript->m_strName);

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


   void script_cache::set_out_of_date(string str)
   {

      if (str.is_empty())
      {

         return;

      }

      ::file::path pathChanged = str;

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


