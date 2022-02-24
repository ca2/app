#include "framework.h"
#include "_simpledb.h"
#include "storage.h"


namespace simpledb
{


   void thread::run()
   {

      single_lock synchronouslock(mutex());

      __pointer(::axis::application) papp = get_app();

      __pointer(::axis::session) psession = papp->get_session();

      try
      {

         while (true)
         {

            preempt();

            try
            {

               if (psession->m_paccount == nullptr)
               {

                  break;

               }

               if (papp->interactive_get_user() == nullptr)
               {

                  sleep(5000_ms);

                  continue;

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

               sleep(300_ms);

               continue;

            }

            bool bFound = false;

            for (i32 i = 1; i < m_itema.get_size(); i++)
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

            try
            {

               string strKey(pitem->m_strKey);

               string strBase64(pitem->m_memory.to_base64());

               property_set set;

               string strUrl;

               strUrl = "https://ca2.software/api/account/str_set_save?key=";

               auto psystem = m_psystem->m_papexsystem;

               auto purl = psystem->url();

               strUrl += purl->url_encode(strKey);

               strUrl += "&value=";

               strUrl += purl->url_encode(strBase64);

               {

                  synchronous_lock slDatabase(mutex());

                  m_pcontext->m_papexcontext->http().get(strUrl, set);

               }

               if (::failed(set["get_status"]))
               {

                  sleep(500_ms);

                  psystem->m_pdirsystem->m_strApiCc = "";

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

      //return ::success;

   }


   void thread::queue(const ::string & pszKey, block block)
   {

      synchronous_lock synchronouslock(mutex());

      auto pitem = __new(queue_item);

      pitem->m_strKey = pszKey;

      pitem->m_memory = block;

      m_itema.add(pitem);

   }


} // namespace simpledb



