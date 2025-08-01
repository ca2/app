#include "framework.h"
#include "thread_localdatabase.h"
#include "storage.h"
#include "queue_item.h"
#include "server.h"
#include "acme/parallelization/synchronous_lock.h"
#include "axis/database/database/database.h"


namespace simpledb
{


   thread_localdatabase::thread_localdatabase()
   {

      defer_create_synchronization();

   }


   thread_localdatabase::~thread_localdatabase()
   {
   
   }


   void thread_localdatabase::run()
   {

      ::task_set_name("localdb");

      auto pstorage = m_pstorage;

      auto pserver = m_pstorage->m_pserver;

      auto pdatabase = pserver->get_local_database();

      single_lock synchronouslock(this->synchronization());

      try
      {

         while (task_get_run())
         {

            try
            {

               if (get_app() == nullptr)
               {

                  break;

               }

            }
            catch (...)
            {

               break;

            }

            synchronouslock.lock();

            if (m_itema.is_empty())
            {

               synchronouslock.unlock();

               ::preempt(300_ms);

               continue;

            }

            bool bFound = false;

            for (int i = 1; i < m_itema.get_size(); i++)
            {

               if (m_itema[i]->m_strKey == m_itema[0]->m_strKey)
               {

                  m_itema.erase_at(0);

                  bFound = true;

                  break;

               }

            }

            if (bFound)
            {

               synchronouslock.unlock();

               continue;

            }

            auto pitem = m_itema[0];

            m_itema.erase_at(0);

            synchronouslock.unlock();



            //auto estatus = pdatabase->set_id_blob(pitem->m_strKey, pitem->m_block);

            try
            {

               //string strKey(pitem->m_strKey);

               ///string strBase64(pitem->m_block.to_base64());

               //::property_set set;

               //auto pstorage = m_pstorage;

               //auto pserver = m_pstorage->m_pserver;

               //auto pdatabase = pserver->get_local_database();

               //if (!pdatabase)
               //{

               //   return ::success;

               //}

               //string strSql;

               //string str;

               //synchronous_lock slDatabase(pdatabase->synchronization());

               if(pitem)
               {

                  pdatabase->set_id_blob(pitem->m_strKey, pitem->m_memory);

               }

//               {
//
//                  if (pstorage->m_pstmtReplace == nullptr)
//                  {
//
//                     int iResult = sqlite3_prepare_v2(
//                        (sqlite3 *)pdatabase->get_handle(),
//                        "REPLACE INTO blobtable (atom, value) values (:atom, :value);",
//                        -1,
//                        &pstorage->m_pstmtReplace, nullptr);
//
//                     string strError = sqlite3_errmsg((sqlite3 *)pdatabase->get_handle());
//
//                     pdatabase->set_error_code(iResult);
//
//                     if (iResult != SQLITE_OK)
//                     {
//
//                        pstorage->m_pstmtReplace = nullptr;
//
//                        continue;
//
//                     }
//
//                     pstorage->m_iReplaceId = sqlite3_bind_parameter_index(pstorage->m_pstmtReplace, ":atom");
//
//                     pstorage->m_iReplaceValue = sqlite3_bind_parameter_index(pstorage->m_pstmtReplace, ":value");
//
//                  }
//                  else
//                  {
//
//                     sqlite3_reset(pstorage->m_pstmtReplace);
//
//                  }
//
//                  character_count iLength = strKey.length();
//
//                  int res = sqlite3_bind_text(pstorage->m_pstmtReplace, pstorage->m_iReplaceId, strKey, (int)iLength, SQLITE_TRANSIENT);
//
//                  if (res != SQLITE_OK)
//                  {
//
//                     informationf("failure to bind text");
//
//                     continue;
//
//                  }
//
//                  res = sqlite3_bind_blob(pstorage->m_pstmtReplace, pstorage->m_iReplaceValue, pitem->m_block.get_data(), (int)pitem->m_block.get_size(), SQLITE_TRANSIENT);
//
//                  if (res != SQLITE_OK)
//                  {
//
//                     informationf("failure to bind blob");
//
//                     continue;
//
//                  }
//
//
//                  res = sqlite3_step(pstorage->m_pstmtReplace);
//
//               }

            }
            catch (...)
            {

            }

         }

      }
      catch (...)
      {

      }

      if (::is_set(m_pstorage))
      {

         m_pstorage->m_pthread.release();

      }

      //return ::success;

   }


   void thread_localdatabase::queue(const ::scoped_string & scopedstrKey, block block)
   {

      synchronous_lock synchronouslock(this->synchronization());

      auto pitem(__allocate queue_item());

      pitem->m_strKey = scopedstrKey;
      pitem->m_memory = block;

      m_itema.add(pitem);

   }


} // namespace simpledb



