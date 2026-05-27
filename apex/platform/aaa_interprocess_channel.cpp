#include "framework.h"


namespace interprocess_channel
{


   base::~base()
   {


   }


   caller::~caller()
   {


   }



   handler::~handler()
   {


   }


   //void listener::on_interprocess_receive(handler * prx, ::pointer<class dispatch_item> && pdispatchitem)
   //{

   //   if (pdispatchitem->is_text_message())
   //   {

   //      on_interprocess_receive(prx, ::transfer(pdispatchitem->m_strMessage));

   //   }
   //   else
   //   {

   //      on_interprocess_receive(
   //         prx,
   //         (::i32) pdispatchitem->m_uData, 
   //         ::transfer(pdispatchitem->m_memory));

   //   }

   //}


   bool listener::on_interprocess_handle(handler * phandler, const ::scoped_string & scopedstrUri)
   {

      return true;

   }


   //void listener::on_interprocess_receive(handler * prx, ::i32 message, ::memory & memory)
   //{

   //}


   //void listener::on_interprocess_post(handler * prx, ::i64 a, ::i64 b)
   //{

   //}


   bool interprocess_channel::close()
   {

      m_ptx->close();

      m_prx->destroy();

      return true;

   }


   void interprocess_channel::restart_apex_ipc()
   {
   }


   // calls restart if confirm_tx failed
   bool interprocess_channel::ensure_tx(const ::scoped_string & scopedstrMessage, duration durationTimeout)
   {

      try
      {

         m_ptx->send(scopedstrMessage, durationTimeout);

      }
      catch (...)
      {

         return false;

      }

      return true;

   }


   bool interprocess_channel::ensure_tx(::i32 message, void * pdata, ::i32 len, duration durationTimeout)
   {

      if (message == WM_APP + WM_USER)
      {

         if (!m_ptx->is_tx_ok())
         {

            restart_apex_ipc();

            return false;

         }

      }
      else
      {

         try
         {

            m_ptx->send(message, pdata, len, durationTimeout);

         }
         catch (...)
         {

            restart_apex_ipc();

            return false;

         }

      }

      return true;

   }


   string app_install(string strPlatform)
   {

      return "::ca2::account::ca2_installer_install_" + strPlatform + "::7807e510-5579-11dd-ae16-0800200c7784";

   }




   // typedef ::i32 (WINAPI * LPFN_ChangeWindowMessageFilter)(const ::atom & atom, ::u32 dwFlag);


   //extern LPFN_ChangeWindowMessageFilter g_pfnChangeWindowMessageFilter;


   //namespace apex
   //{



   base::base()
   {

      //set_hwnd(nullptr);

   }





   caller::caller()
   {

   }



   void caller::open(const ::scoped_string & scopedstrChannel, launcher * plauncher)
   {

      //return true;

   }


   void caller::close()
   {

      //if (get_hwnd() == nullptr)
      //{

      //   return true;

      //}

      //set_hwnd(nullptr);

      m_strBaseChannel = "";

      //return true;

   }


   void caller::send(const ::scoped_string & scopedstrMessage, const duration & durationTimeout)
   {

      if (!is_tx_ok())
      {

         return;

      }

      //return ::success;

   }


   void caller::send(::i32 message, void * pdata, ::i32 len, const duration & durationTimeout)
   {

      if (message == I32_MINIMUM)
      {

         //return false;

         return;

      }

      if (!is_tx_ok())
      {

         //return false;

         return;

      }


      //return true;

   }


   bool caller::is_tx_ok()
   {

      return false;

   }


   handler::handler()
   {

      m_preceiver = nullptr;

   }


   void handler::on_initialize_particle()
   {

      //fork([this]()
      //   {

      //      task_dispatch();

      //   });

      //return ::success;

   }


   void handler::create(const ::scoped_string & scopedstrChannel)
   {

      //return true;

   }


   void handler::destroy()
   {

      //auto estatus = 
      base::destroy();

      //return estatus;

   }


   bool handler::on_interprocess_receive(const ::scoped_string & scopedstrMessage)
   {

      //if (case_insensitive_string_begins(strMessage, "synch_"))
      //{

      //   if (m_preceiver != nullptr)
      //   {

      return m_preceiver->on_interprocess_receive(this, ::transfer(strMessage));

      //   }

      //}
      //else
      //{

      //   dispatch_message(::transfer(strMessage));
      //   //get_app()->fork([this, prx, strMessage]()
      //   //{

      //   //   if (m_preceiver != nullptr)
      //   //   {

      //   //      m_preceiver->on_interprocess_receive(prx, strMessage);

      //   //   }

      //   //});

      //}

      //// ODOW - on date of writing : return ignored by this windows implementation

      ////return nullptr;

   }


   //void handler::on_interprocess_receive(::i32 message, ::memory && memory)
   //{

   //   ///memory memory(pdata, len);

   //   dispatch_message(message, ::transfer(memory));

   //   //if (m_preceiver != nullptr)
   //   //{

   //     // m_preceiver->on_interprocess_receive(prx, message, pdata, len);

   //   //}

   //   // ODOW - on date of writing : return ignored by this windows implementation

   //   //return nullptr;

   //}


   void handler::on_interprocess_post(::i64 a, ::i64 b)
   {

      if (m_preceiver != nullptr)
      {

         m_preceiver->on_interprocess_post(this, a, b);

      }

      // ODOW - on date of writing : return ignored by this windows implementation

      //return nullptr;

   }


   bool handler::on_idle()
   {

      return false;

   }


   bool handler::is_rx_ok()
   {

      return false;

   }


   //void handler::dispatch_message(::string && strMessage)
   //{

   //   auto pdispatchitem = allocateø class dispatch_item (::transfer(strMessage));

   //   dispatch_item(::transfer(pdispatchitem));

   //}


   //void handler::dispatch_message(::u64 uData, ::memory && memory)
   //{

   //   auto pdispatchitem = allocateø class dispatch_item (uData, ::transfer(memory));

   //   dispatch_item(::transfer(pdispatchitem));

   //}


   //void handler::dispatch_item(::pointer<class dispatch_item> && pdispatchitem)
   //{

   //   synchronous_lock synchronouslock(m_pmutexDispatch, DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

   //   bool bWasEmpty = m_dispatchitema.is_empty();

   //   m_dispatchitema.add(::transfer(pdispatchitem));

   //   if (bWasEmpty)
   //   {

   //      m_happeningDispatchItemNew.set_happening();

   //   }

   //}


   //void handler::task_dispatch()
   //{

   //   auto ptask = ::get_task();

   //   single_lock singlelock(m_pmutexDispatch);

   //   while (ptask->should_run())
   //   {

   //      if (m_happeningDispatchItemNew._wait(1_s))
   //      {

   //         singlelock.lock();

   //         while (m_dispatchitema.has_element()
   //            && ptask->should_run())
   //         {

   //            {

   //               auto pdispatchitem = m_dispatchitema.pick_first();

   //               singlelock.unlock();

   //               try
   //               {

   //                  m_preceiver->on_interprocess_receive(this, ::transfer(pdispatchitem));

   //               }
   //               catch (...)
   //               {

   //               }

   //            }

   //            singlelock.lock();

   //         }

   //         m_happeningDispatchItemNew.reset_happening();

   //         singlelock.unlock();

   //      }

   //   }

   //}


   interprocess_channel::interprocess_channel()
   {

      m_durationTimeout = (5000) * 11;

   }


   interprocess_channel::~interprocess_channel()
   {


   }


   //#ifdef WINDOWS
   //
   //
   //      bool interprocess_channel::open_ab(const ::scoped_string & scopedstrKey, const ::scoped_string & scopedstrModule, launcher * plauncher)
   //      {
   //
   //         m_strChannel = pszKey;
   //
   //         m_prx->m_preceiver = this;
   //
   //         string strChannelRx = m_strChannel + "-a";
   //
   //         string strChannelTx = m_strChannel + "-b";
   //
   //         if (!m_prx->create(strChannelRx.c_str()))
   //         {
   //
   //            return false;
   //
   //         }
   //
   //         if (!m_ptx->open(strChannelTx.c_str(), plauncher))
   //         {
   //
   //            return false;
   //
   //         }
   //
   //         return true;
   //
   //      }
   //

        /* bool interprocess_channel::open_ba(const ::scoped_string & scopedstrKey, const ::scoped_string & scopedstrModule, launcher * plauncher)
         {

            m_strChannel = pszKey;

            m_prx->m_preceiver = this;

            string strChannelRx = m_strChannel + "-b";

            string strChannelTx = m_strChannel + "-a";

            if (!m_prx->create(strChannelRx.c_str()))
            {

               return false;

            }

            if (!m_ptx->open(strChannelTx.c_str(), plauncher))
            {

               return false;

            }

            return true;

         }

   #else*/


   bool interprocess_channel::open_ab(const ::scoped_string & scopedstrKey, launcher * plauncher)
   {

      m_strChannel = pszKey;

      m_prx->m_preceiver = this;

      string strChannelRx = m_strChannel + "-a";

      string strChannelTx = m_strChannel + "-b";

      m_prx->create(strChannelRx.c_str());

      m_ptx->open(strChannelTx.c_str(), plauncher);

      return true;

   }


   bool interprocess_channel::open_ba(const ::scoped_string & scopedstrKey, launcher * plauncher)
   {

      m_strChannel = pszKey;

      m_prx->m_preceiver = this;

      string strChannelRx = m_strChannel + "-b";

      string strChannelTx = m_strChannel + "-a";

      m_prx->create(strChannelRx.c_str());

      m_ptx->open(strChannelTx.c_str(), plauncher);

      return true;

   }


   //#endif


   bool interprocess_channel::is_rx_tx_ok()
   {

      return m_prx->is_rx_ok() && m_ptx->is_tx_ok();
      //return false;

   }


} // namespace interprocess_channel



