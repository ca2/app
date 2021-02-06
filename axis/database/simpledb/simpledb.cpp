#include "framework.h"
#include "_simpledb.h"
#include "axis/database/sqlitedb/_.h"
#include <sqlite3.h>
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




   ::e_status simpledb::initialize_simpledb(::simpledb::server * pserver)
   {

      auto estatus = ::object::initialize(pserver);

      if (!estatus)
      {

         return estatus;

      }

      set_data_server(pserver);

      return estatus;

   }




   //// true if deleted
   bool simpledb::remove(const ::database::key & key)
   {

      sync_lock sl(mutex());

      class server * pserver = server();

      if (::is_null(pserver) || pserver->m_pstorage.is_null())
      {

         return false;

      }

      auto pstorage = __cast < storage >(pserver->m_pstorage);

      if (!pstorage)
      {

         return false;

      }

      string strKey = key.m_strDataKey;

      strKey.replace("\\", "/");

      return pstorage->remove_key(strKey);

   }


   bool simpledb::load(const ::database::key & key, get_memory getmemory)
   {

      sync_lock sl(mutex());

      class server * pserver = server();

      if (::is_null(pserver))
      {

         return false;

      }

      if (pserver->m_pdatabaseUser.is_set())
      {

         string strKey = key.m_strDataKey;

         auto pdatabase = pserver->m_pdatabaseUser;

         try
         {

            return pdatabase->memory_query_item(getmemory, "SELECT `value` FROM fun_user_str_set WHERE user = '" + pserver->m_strUser + "' AND `key` = '" + pdatabase->escape(strKey) + "'");

         }
         catch (...)
         {

         }

         return false;

      }


      auto pstorage = pserver->m_pstorage;

      if (pstorage.is_null())
      {

         return false;

      }

      string strKey = key.m_strDataKey;

      strKey.replace("\\", "/");

      if (!pserver->m_bRemote || key.m_bLocalData)
      {

         auto ppair = pstorage->m_map.plookup(strKey);

         if (ppair != nullptr)
         {

            return getmemory.get(ppair->element2().m_block);

         }

         int iTryStatement = 0;

         __pointer(::sqlite::database) pdatabase = pserver->get_local_database();

         class sync * pmutex = pdatabase->mutex();

         sync_lock slDatabase(pmutex);

      retry_statement:

         // LOCAL (sqlite)

         if (pstorage->m_pstmtSelect == nullptr)
         {

            i32 iResult = sqlite3_prepare_v2(
               (sqlite3 *)pdatabase->get_handle(),
               "select `value` FROM `blobtable` WHERE `id` = :id;",
               -1,
               &pstorage->m_pstmtSelect, nullptr);

            string strError = sqlite3_errmsg((sqlite3 *)pdatabase->get_handle());

            pdatabase->set_error_code(iResult);

            if (iResult != SQLITE_OK)
            {

               pstorage->m_pstmtSelect = nullptr;

               return false;

            }

            pstorage->m_iSelectId = sqlite3_bind_parameter_index(pstorage->m_pstmtSelect, ":id");

         }
         else
         {

            try
            {

               sqlite3_reset(pstorage->m_pstmtSelect);

            }
            catch (...)
            {

               pstorage->m_pstmtSelect = nullptr;

               if (iTryStatement >= 3)
               {

                  return false;

               }

               iTryStatement++;

               goto retry_statement;

            }

         }

         int iLength = (int)strKey.get_length();

         int res = sqlite3_bind_text(pstorage->m_pstmtSelect, pstorage->m_iSelectId, strKey, (int)iLength, SQLITE_TRANSIENT);

         if (res != SQLITE_OK)
         {

            return false;

         }

         res = sqlite3_step(pstorage->m_pstmtSelect);

         if (res != SQLITE_ROW)
         {

            //string strSql = "select `value` FROM stringtable WHERE `id` = '" + pdatabase->escape(strKey) + "'";

            //::payload payload = pdatabase->query_item(strSql);

            //if (!(bool)payload)
            //{

            //   return false;

            //}

            //return payload.get_string();

            return false;

         }

         const char * psz = (const char *)sqlite3_column_blob(pstorage->m_pstmtSelect, 0);

         strsize iLen = sqlite3_column_bytes(pstorage->m_pstmtSelect, 0);

         if (!getmemory.get(psz, iLen))
         {

            return false;

         }

         {

            item stritem;

            stritem.m_tick.Now();

            stritem.m_block.assign(psz, iLen);

            pstorage->m_map[strKey] = stritem;

         }



      }
      else
      {

         // Remote

         sl.unlock();

         Application.assert_user_logged_in();

         sl.lock();

         auto ppair = pstorage->m_map.plookup(strKey);

         if (ppair != nullptr && ppair->element2().m_tick.elapsed() < m_durationRemoteTimeout)
         {

            return getmemory.get(ppair->element2().m_block);

         }

         sl.unlock();

         string strValue;

         {

            property_set set;

            string strUrl;

            string strApi = "/api/account/str_set_load";

            strUrl = "https://ca2.cc" + strApi + "?key=";

            strUrl += System.url().url_encode(strKey);

            strValue = get_context()->http().get(strUrl, set);

            if (strValue.is_empty() || ::failed(set["get_status"]))
            {

               return false;

            }

            string strFirstLine = ::str::line(strValue);

            if (!str::begins_eat_ci(strFirstLine, strApi + ":"))
            {

               return false;

            }

            string strListingTime = strFirstLine;

            ::datetime::time timeListing(System.datetime().from_gmt(strListingTime));

            if (timeListing.abs_diff(::datetime::now) > 5_s)
            {

               return false;

            }

            {

               item stritem;

               stritem.m_tick.Now();

               stritem.m_block.from_base64(strValue, strValue.get_length());

               sl.lock();

               pstorage->m_map[strKey] = stritem;

               if (::is_set(getmemory.m_pmemory))
               {

                  getmemory.m_pmemory->assign(stritem.m_block.get_data(), stritem.m_block.get_size());

               }
               else
               {

                  getmemory.m_block = stritem.m_block;

               }

            }

         }

      }

      return true;

   }


   bool simpledb::save(const ::database::key & key, block block)
   {

      sync_lock sl(mutex());

      class server * pserver = server();

      if (::is_null(pserver))
      {

         return false;

      }

      if (pserver->m_pdatabaseUser.is_set())
      {

         string strKey = key.m_strDataKey;

         strKey.replace("\\", "/");

         auto pdatabase = pserver->m_pdatabaseUser;

         string strValue;

         strValue = block.to_base64();

         string strSql = "REPLACE INTO fun_user_str_set VALUE('" + pserver->m_strUser + "', '" + pdatabase->escape(strKey) + "', '" + strValue + "')";

         TRACE(strSql);

         return pdatabase->exec(strSql);

      }

      storage * pstorage = pserver->m_pstorage;

      if (::is_null(pstorage))
      {

         return false;

      }

      string strKey = key.m_strDataKey;

      strKey.replace("\\", "/");

      if (!pserver->m_bRemote || key.m_bLocalData)
      {

         if (pserver->get_local_database().is_null())
         {

            return false;

         }

         string_map < class item >::pair * pitem = nullptr;

         {

            sync_lock sl(mutex());

            pitem = pstorage->m_map.plookup(strKey);

         }

         string strLoad;

         if (pitem != nullptr)
         {

            sync_lock sl(mutex());

            if (pitem->element2().m_block == block)
            {

               return true;

            }

         }



         if (pstorage->m_pthreadlocal.is_null())
         {

            pstorage->m_pthreadlocal = __new(thread_localdatabase);

            pstorage->m_pthreadlocal->initialize(pstorage);

            __refer(pstorage->m_pthreadlocal->m_pstorage, pstorage);

            pstorage->m_pthreadlocal->begin();

         }

         pstorage->m_pthreadlocal->queue(strKey, block);

         item stritem;

         stritem.m_tick.Now();

         stritem.m_block = block;

         sync_lock sl(mutex());

         pstorage->m_map.set_at(strKey, stritem);

         return true;

      }
      else
      {

         if (pstorage->m_pthread.is_null())
         {

            pstorage->m_pthread = __new(thread);

            pstorage->m_pthread->m_pstorage = pstorage;

            pstorage->m_pthread->begin();

         }

         pstorage->m_pthread->queue(strKey, block);

         item stritem;

         stritem.m_tick.Now();

         stritem.m_block = block;

         sync_lock sl(mutex());

         pstorage->m_map.set_at(strKey, stritem);

         return true;

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



