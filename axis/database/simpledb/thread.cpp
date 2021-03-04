#include "framework.h"
#include "_simpledb.h"
#include <sqlite3.h>
#include "storage.h"


namespace simpledb
{


   ::e_status thread::run()
   {

      single_lock synchronizationlock(mutex());

      try
      {

         while (thread_get_run())
         {

            try
            {


               if (get_context_application() == nullptr)
               {

                  break;

               }

               if (get_context_application()->get_context_session() == nullptr)
               {

                  break;

               }

               auto psession = Session;

               if (psession->m_paccount == nullptr)
               {

                  break;

               }

               if (Application.interactive_get_user() == nullptr)
               {

                  sleep(5000_ms);

                  continue;

               }

            }
            catch (...)
            {

               break;

            }

            synchronizationlock.lock();

            if (m_itema.is_empty())
            {

               synchronizationlock.unlock();

               sleep(300_ms);

               continue;

            }

            bool bFound = false;

            for (i32 i = 1; i < m_itema.get_size(); i++)
            {

               if (m_itema[i]->m_strKey == m_itema[0]->m_strKey)
               {

                  m_itema.remove_at(0);

                  bFound = true;

                  break;

               }

            }

            if (bFound)
            {

               synchronizationlock.unlock();

               continue;

            }

            auto pitem = m_itema[0];

            m_itema.remove_at(0);

            synchronizationlock.unlock();

            try
            {

               string strKey(pitem->m_strKey);

               string strBase64(pitem->m_block.to_base64());

               property_set set;

               string strUrl;

               strUrl = "https://ca2.cc/api/account/str_set_save?key=";

               strUrl += System->url().url_encode(strKey);

               strUrl += "&value=";

               strUrl += System->url().url_encode(strBase64);

               {

                  synchronization_lock slDatabase(mutex());

                  get_context()->http().get(strUrl, set);

               }

               if (::failed(set["get_status"]))
               {

                  sleep(500_ms);

                  System->m_pdirsystem->m_strApiCc = "";

               }

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

      return ::success;

   }


   void thread::queue(const char * pszKey, block block)
   {

      synchronization_lock synchronizationlock(mutex());

      auto pitem = __new(queue_item);

      pitem->m_strKey = pszKey;

      pitem->m_block = block;

      m_itema.add(pitem);

   }


} // namespace simpledb



