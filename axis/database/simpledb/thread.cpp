#include "framework.h"
#include "_simpledb.h"
#include <sqlite3.h>
#include "storage.h"


namespace simpledb
{


   ::estatus thread::run()
   {

      single_lock sl(mutex());

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

                  sleep(5000);

                  continue;

               }

            }
            catch (...)
            {

               break;

            }

            sl.lock();

            if (m_itema.is_empty())
            {

               sl.unlock();

               sleep(300);

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

               sl.unlock();

               continue;

            }

            auto pitem = m_itema[0];

            m_itema.remove_at(0);

            sl.unlock();

            try
            {

               string strKey(pitem->m_strKey);

               string strBase64(pitem->m_block.to_base64());

               property_set set;

               string strUrl;

               strUrl = "https://ca2.cc/api/account/str_set_save?key=";

               strUrl += System.url().url_encode(strKey);

               strUrl += "&value=";

               strUrl += System.url().url_encode(strBase64);

               {

                  sync_lock slDatabase(mutex());

                  Context.http().get(strUrl, set);

               }

               if (::failed(set["get_status"]))
               {

                  sleep(500);

                  System.m_pdirsystem->m_strApiCc = "";

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

      sync_lock sl(mutex());

      auto pitem = __new(queue_item);

      pitem->m_strKey = pszKey;

      pitem->m_block = block;

      m_itema.add(pitem);

   }


} // namespace simpledb



