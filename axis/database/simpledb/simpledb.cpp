#include "framework.h"
#include "_simpledb.h"
#include "storage.h"


namespace simpledb
{


   simpledb::simpledb()
   {

      m_durationRemoteTimeout = 10_s;

      defer_create_mutex();

   }


   simpledb::~simpledb()
   {


   }


   void simpledb::initialize_simpledb(::simpledb::server * pserver)
   {

      //auto estatus = 
      
      ::object::initialize(pserver);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      set_data_server(pserver);

//      return estatus;

   }




   //// true if deleted
   bool simpledb::erase(const ::database::key & key)
   {

      synchronous_lock synchronouslock(mutex());

      class server * pserver = server();

      if (::is_null(pserver) || pserver->m_pstorage.is_null())
      {

         throw ::exception(error_failed);

      }

      auto pstorage = __cast < storage >(pserver->m_pstorage);

      if (!pstorage)
      {

         throw ::exception(error_failed);

      }

      string strKey = key.m_strDataKey;

      strKey.replace_with("/", "\\");

      return pstorage->erase_key(strKey);

   }


   bool simpledb::load(const ::database::key & key, get_memory getmemory)
   {

      synchronous_lock synchronouslock(mutex());

      class server * pserver = server();

      if (::is_null(pserver))
      {

         throw ::exception(error_failed);

      }

      if (pserver->m_pdatabaseUser.is_set())
      {

         string strKey = key.m_strDataKey;

         auto pdatabase = pserver->m_pdatabaseUser;

         try
         {

            return pdatabase->query_blob(getmemory, "SELECT `value` FROM fun_user_str_set WHERE user = '" + pserver->m_strUser + "' AND `key` = '" + pdatabase->escape(strKey) + "'");

         }
         catch (...)
         {

         }

         throw ::exception(error_failed);

      }


      auto pstorage = pserver->m_pstorage;

      if (pstorage.is_null())
      {

         throw ::exception(error_failed);

      }

      string strKey = key.m_strDataKey;

      strKey.replace_with("/", "\\");

      if (!pserver->m_bRemote || key.m_bLocalData)
      {

         auto ppair = pstorage->m_map.plookup(strKey);

         if (ppair != nullptr)
         {

            getmemory.get(ppair->element2().m_memory);

            return ppair->m_element2.m_bData;

         }

         int iTryStatement = 0;

         auto pdatabase = pserver->get_local_database();

         class synchronization_object * pmutex = pdatabase->mutex();

         synchronous_lock slDatabase(pmutex);

      //retry_statement:

         // LOCAL (sqlite)
         //auto estatus = 
         bool bData = pdatabase->get_id_blob(strKey, getmemory);

         {

            item stritem;

            stritem.m_tick.Now();

            stritem.m_bData = bData;

            if(bData)
            {

               stritem.m_memory.assign(getmemory.get_data(), (memsize) getmemory.get_size());

            }
            else
            {

               output_debug_string("");

            }

            pstorage->m_map[strKey] = stritem;

         }

         return bData;

      }
      else
      {

         // Remote

         synchronouslock.unlock();

         __pointer(::axis::application) papp = get_app();

         papp->assert_user_logged_in();

         synchronouslock.lock();

         auto ppair = pstorage->m_map.plookup(strKey);

         if (ppair != nullptr && ppair->element2().m_tick.elapsed() < m_durationRemoteTimeout)
         {

            getmemory.get(ppair->element2().m_memory);

            return ppair->m_element2.m_bData;

         }

         synchronouslock.unlock();

         string strValue;

         {

            property_set set;

            string strUrl;

            string strApi = "/api/account/str_set_load";

            strUrl = "https://ca2.software" + strApi + "?key=";

            auto psystem = m_psystem;

            auto purl = psystem->url();

            strUrl += purl->url_encode(strKey);

            strValue = m_pcontext->m_papexcontext->http().get(strUrl, set);

            if (strValue.is_empty() || ::failed(set["get_status"]))
            {

               return false;

            }

            string strFirstLine = ::str().line(strValue);

            if (!::str().begins_eat_ci(strFirstLine, strApi + ":"))
            {

               return false;

            }

            string strListingTime = strFirstLine;

            auto pdatetime = psystem->datetime();

            auto ptextcontext = get_session()->text_context();

            ::earth::time timeListing(pdatetime->from_string(ptextcontext, strListingTime));

            if (timeListing.abs_diff(e_now) > 5_s)
            {

               return false;

            }

            {

               item stritem;

               stritem.m_tick.Now();

               stritem.m_memory.from_base64(strValue, strValue.get_length());

               synchronouslock.lock();

               pstorage->m_map[strKey] = stritem;

               if (::is_set(getmemory.m_pmemory))
               {

                  getmemory.m_pmemory->assign(stritem.m_memory.get_data(), stritem.m_memory.get_size());

               }
               else
               {

                  getmemory.m_block = stritem.m_memory;

               }

            }

         }

      }

      return true;

   }


   void simpledb::save(const ::database::key & key, block block)
   {

      synchronous_lock synchronouslock(mutex());

      class server * pserver = server();

      if (::is_null(pserver))
      {

         throw ::exception(error_failed);

      }

      if (pserver->m_pdatabaseUser.is_set())
      {

         string strKey = key.m_strDataKey;

         strKey.replace_with("/", "\\");

         auto pdatabase = pserver->m_pdatabaseUser;

         string strValue;

         strValue = block.to_base64();

         string strSql = "REPLACE INTO fun_user_str_set VALUE('" + pserver->m_strUser + "', '" + pdatabase->escape(strKey) + "', '" + strValue + "')";

         TRACE(strSql);

         pdatabase->exec(strSql);

         return;

      }

      storage * pstorage = pserver->m_pstorage;

      if (::is_null(pstorage))
      {

         throw ::exception(error_failed);

      }

      string strKey = key.m_strDataKey;

      strKey.replace_with("/", "\\");

      if (!pserver->m_bRemote || key.m_bLocalData)
      {

         if (pserver->get_local_database().is_null())
         {

            throw ::exception(error_failed);

         }

         string_map < class item >::pair * pitem = nullptr;

         {

            synchronous_lock synchronouslock(mutex());

            pitem = pstorage->m_map.plookup(strKey);

         }

         string strLoad;

         if (pitem != nullptr)
         {

            synchronous_lock synchronouslock(mutex());

            if (pitem->element2().m_memory == block)
            {

               return;

            }

         }

         if (pstorage->m_pthreadlocal.is_null())
         {

            pstorage->m_pthreadlocal = __new(thread_localdatabase);

            pstorage->m_pthreadlocal->initialize(pstorage);

            __refer(pstorage->m_pthreadlocal->m_pstorage, pstorage);

            pstorage->m_pthreadlocal->branch();

         }

         pstorage->m_pthreadlocal->queue(strKey, block);

         item stritem;

         stritem.m_tick.Now();

         stritem.m_memory = block;

         stritem.m_bData = true;

         synchronous_lock synchronouslock(mutex());

         pstorage->m_map.set_at(strKey, stritem);

         return;

      }
      else
      {

         if (pstorage->m_pthread.is_null())
         {

            pstorage->m_pthread = __new(thread);

            pstorage->m_pthread->m_pstorage = pstorage;

            pstorage->m_pthread->branch();

         }

         pstorage->m_pthread->queue(strKey, block);

         item stritem;

         stritem.m_tick.Now();

         stritem.m_memory = block;

         stritem.m_bData = true;

         synchronous_lock synchronouslock(mutex());

         pstorage->m_map.set_at(strKey, stritem);

         return;

      }

   }




   class server * simpledb::server()
   {

      if (::is_null(m_pdataserver))
      {

         return nullptr;

      }

      return dynamic_cast < class server * > (m_pdataserver);

   }


} // namespace simpledb



