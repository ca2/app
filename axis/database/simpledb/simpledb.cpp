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
#include "acme/prototype/prototype/url.h"
#include "acme/platform/http.h"
#include "acme/prototype/datetime/datetime.h"
#include "acme/prototype/string/base64.h"
#include "acme/prototype/string/str.h"
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
   bool simpledb::erase(const ::scoped_string & strDataKey)
   {

      _synchronous_lock synchronouslock(this->synchronization());

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

      string strKey = strDataKey;

      strKey.replace_with("/", "\\");

      return pstorage->erase_key(strKey);

   }


   bool simpledb::load(const ::scoped_string & strDataKey, get_memory getmemory)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      class server * pserver = server();

      if (::is_null(pserver))
      {

         throw ::exception(error_failed);

      }

      if (pserver->m_pdatabaseUser.is_set())
      {

         string strKey = strDataKey;

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

      string strKey = strDataKey;

      strKey.replace_with("/", "\\");

      //if (!pserver->m_bRemote || key.m_bLocalData)
      if (!pserver->m_bRemote)
      {

         auto ppair = pstorage->m_map.plookup(strKey);

         if (ppair)
         {

            getmemory.get(ppair->element2().m_memory);

            return ppair->m_element2.m_bData;

         }

         int iTryStatement = 0;

         auto pdatabase = pserver->get_local_database();

         auto pparticleSynchronization = pdatabase->synchronization();

         _synchronous_lock slDatabase(pparticleSynchronization);

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

               informationf("");

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

         synchronouslock._lock();

         auto ppair = pstorage->m_map.plookup(strKey);

         if (ppair && ppair->element2().m_tick.elapsed() < m_timeRemoteTimeout)
         {

            getmemory.get(ppair->element2().m_memory);

            return ppair->m_element2.m_bData;

         }

         synchronouslock.unlock();

         string strValue;

         {

            ::property_set set;

            ::string strApi = "/api/account/str_set_load";

            ::url::parts parts("https://ca2.network" + strApi);

            parts.arguments()["key"] = strKey;

            auto url = parts.as_url();

            strValue = http()->get(url, set);

            if (strValue.is_empty() || set["get_status"].failed())
            {

               return false;

            }

            string strFirstLine = ::str::line(strValue);

            if (!strFirstLine.case_insensitive_begins_eat(strApi + ":"))
            {

               return false;

            }

            string strListingTime = strFirstLine;

            auto pdatetime = datetime();

            auto ptextcontext = session()->text_context();

            ::earth::time timeListing(pdatetime->from_string(ptextcontext, strListingTime));

            if (timeListing.abs_diff(now_t{}) > 5_s)
            {

               return false;

            }

            {

               item stritem;

               stritem.m_tick.Now();

               stritem.m_memory.from_base64(strValue);

               synchronouslock._lock();

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


   void simpledb::save(const ::scoped_string & strDataKey, block block)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      class server * pserver = server();

      if (::is_null(pserver))
      {

         throw ::exception(error_failed);

      }

      if (pserver->m_pdatabaseUser.is_set())
      {

         string strKey = strDataKey;

         strKey.replace_with("/", "\\");

         auto pdatabase = pserver->m_pdatabaseUser;

         string strValue;

         ::base64 base64;

         strValue = base64.encode(block);

         string strSql = "REPLACE INTO fun_user_str_set PAYLOAD('" + pserver->m_strUser + "', '" + pdatabase->escape(strKey) + "', '" + strValue + "')";

         informationf(strSql);

         pdatabase->exec(strSql);

         return;

      }

      storage * pstorage = pserver->m_pstorage;

      if (::is_null(pstorage))
      {

         throw ::exception(error_failed);

      }

      string strKey = strDataKey;

      strKey.replace_with("/", "\\");

      //if (!pserver->m_bRemote || key.m_bLocalData)
      if (!pserver->m_bRemote)
      {

         if (pserver->get_local_database().is_null())
         {

            throw ::exception(error_failed);

         }

         string_map < class item >::iterator iterator{};

         {

            _synchronous_lock synchronouslock(this->synchronization());

            iterator = pstorage->m_map.plookup(strKey);

         }

         string strLoad;

         if (iterator.is_ok())
         {

            _synchronous_lock synchronouslock(this->synchronization());

            if (iterator->element2().m_memory == block)
            {

               return;

            }

         }

         if (pstorage->m_pthreadlocal.is_null())
         {

            pstorage->m_pthreadlocal = __allocate thread_localdatabase();

            pstorage->m_pthreadlocal->initialize(pstorage);

            pstorage->m_pthreadlocal->m_pstorage = pstorage;

            pstorage->m_pthreadlocal->branch();

         }

         pstorage->m_pthreadlocal->queue(strKey, block);

         item stritem;

         stritem.m_tick.Now();

         stritem.m_memory = block;

         stritem.m_bData = true;

         _synchronous_lock synchronouslock(this->synchronization());

         pstorage->m_map.set_at(strKey, stritem);

         return;

      }
      else
      {

         if (pstorage->m_pthread.is_null())
         {

            pstorage->m_pthread = __allocate thread();

            pstorage->m_pthread->m_pstorage = pstorage;

            pstorage->m_pthread->branch();

         }

         pstorage->m_pthread->queue(strKey, block);

         item stritem;

         stritem.m_tick.Now();

         stritem.m_memory = block;

         stritem.m_bData = true;

         _synchronous_lock synchronouslock(this->synchronization());

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



