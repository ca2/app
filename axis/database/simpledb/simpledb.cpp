#include "framework.h"
#include "simpledb.h"
#include "item.h"
#include "server.h"
#include "storage.h"
#include "thread.h"
#include "thread_localdatabase.h"
#include "queue_item.h"
////#include "acme/exception/exception.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/primitive/primitive/url.h"
#include "acme/platform/system.h"
#include "acme/primitive/datetime/datetime.h"
#include "acme/primitive/string/base64.h"
#include "acme/primitive/string/str.h"
#include "apex/networking/http/context.h"
#include "apex/platform/session.h"
#include "axis/database/database/database.h"
#include "axis/platform/application.h"


namespace simpledb
{


   simpledb::simpledb()
   {

      m_timeRemoteTimeout = 10_s;

      defer_create_synchronization();

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

      initialize_data_client(pserver);

//      return estatus;

   }




   //// true if deleted
   bool simpledb::erase(const ::database::key & key)
   {

      synchronous_lock synchronouslock(this->synchronization());

      class server * pserver = server();

      if (::is_null(pserver) || pserver->m_pstorage.is_null())
      {

         throw ::exception(error_failed);

      }

      ::pointer < storage > pstorage = pserver->m_pstorage;

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

      synchronous_lock synchronouslock(this->synchronization());

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

         auto pparticleSynchronization = pdatabase->synchronization();

         synchronous_lock slDatabase(pparticleSynchronization);

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

               stritem.m_memory.assign(getmemory.data(), (memsize) getmemory.size());

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

         ::pointer<::axis::application>papp = get_app();

         papp->assert_user_logged_in();

         synchronouslock.lock();

         auto ppair = pstorage->m_map.plookup(strKey);

         if (ppair != nullptr && ppair->element2().m_tick.elapsed() < m_timeRemoteTimeout)
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

            auto psystem = acmesystem();

            auto purl = psystem->url();

            strUrl += ::url::encode(strKey);

            strValue = m_pcontext->m_papexcontext->http().get(strUrl, set);

            if (strValue.is_empty() || ::failed(set["get_status"]))
            {

               return false;

            }

            string strFirstLine = ::str().line(strValue);

            if (!strFirstLine.case_insensitive_begins_eat(strApi + ":"))
            {

               return false;

            }

            string strListingTime = strFirstLine;

            auto pdatetime = psystem->datetime();

            auto ptextcontext = acmesession()->text_context();

            ::earth::time timeListing(pdatetime->from_string(ptextcontext, strListingTime));

            if (timeListing.abs_diff(e_now) > 5_s)
            {

               return false;

            }

            {

               item stritem;

               stritem.m_tick.Now();

               stritem.m_memory.from_base64(strValue, strValue.length());

               synchronouslock.lock();

               pstorage->m_map[strKey] = stritem;

               if (::is_set(getmemory.m_pmemory))
               {

                  getmemory.m_pmemory->assign(stritem.m_memory.data(), stritem.m_memory.size());

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

      synchronous_lock synchronouslock(this->synchronization());

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

         ::base64 base64;

         strValue = base64.encode(block);

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

         string_map < class item >::iterator iterator{};

         {

            synchronous_lock synchronouslock(this->synchronization());

            iterator = pstorage->m_map.plookup(strKey);

         }

         string strLoad;

         if (iterator.is_ok())
         {

            synchronous_lock synchronouslock(this->synchronization());

            if (iterator->element2().m_memory == block)
            {

               return;

            }

         }

         if (pstorage->m_pthreadlocal.is_null())
         {

            pstorage->m_pthreadlocal = __new(thread_localdatabase);

            pstorage->m_pthreadlocal->initialize(pstorage);

            pstorage->m_pthreadlocal->m_pstorage = pstorage;

            pstorage->m_pthreadlocal->branch();

         }

         pstorage->m_pthreadlocal->queue(strKey, block);

         item stritem;

         stritem.m_tick.Now();

         stritem.m_memory = block;

         stritem.m_bData = true;

         synchronous_lock synchronouslock(this->synchronization());

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

         synchronous_lock synchronouslock(this->synchronization());

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



