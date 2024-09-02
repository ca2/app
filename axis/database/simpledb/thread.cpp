#include "framework.h"
#include "thread.h"
#include "storage.h"
#include "queue_item.h"
#include "acme/filesystem/filesystem/dir_context.h"
#include "acme/filesystem/filesystem/dir_system.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/system.h"
#include "acme/primitive/primitive/url.h"
#include "apex/networking/http/context.h"
#include "apex/platform/system.h"
#include "axis/platform/application.h"
#include "axis/platform/session.h"


namespace simpledb
{


   void thread::run()
   {

      single_lock synchronouslock(this->synchronization());

      ::pointer<::axis::application>papp = get_app();

      ::pointer<::axis::session>psession = papp->get_session();

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

               // property_set set;

               ::url::parts parts("https://ca2.software/api/account/str_set_save");

               parts.arguments()["key"] = strKey;

               parts.arguments()["value"] = strBase64;

               auto url = parts.as_url();

               //strUrl = "https://ca2.software/api/account/str_set_save?key=";

               //auto psystem = system()->m_papexsystem;

               //auto purl = psystem->url();

               //strUrl += ::url::encode(strKey);

               //strUrl += "&value=";

               //strUrl += ::url::encode(strBase64);

               {

                  synchronous_lock slDatabase(synchronization());

                  m_pcontext->m_papexcontext->http().get(url, set);

               }

               if (set["get_status"].failed())
               {

                  sleep(500_ms);

                  system()->dirsystem()->m_strApiCc = "";

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

      synchronous_lock synchronouslock(this->synchronization());

      auto pitem = ::place(new queue_item());

      pitem->m_strKey = pszKey;

      pitem->m_memory = block;

      m_itema.add(pitem);

   }


} // namespace simpledb



