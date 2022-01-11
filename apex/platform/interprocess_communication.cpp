#include "framework.h"


namespace interprocess_communication
{


   base::~base()
   {


   }


   tx::~tx()
   {


   }



   rx::~rx()
   {


   }


   void rx::receiver::on_interprocess_receive(rx * prx, __pointer(class dispatch_item) && pdispatchitem)
   {

      if (pdispatchitem->is_text_message())
      {

         on_interprocess_receive(prx, ::move(pdispatchitem->m_strMessage));

      }
      else
      {

         on_interprocess_receive(
            prx,
            (int) pdispatchitem->m_uData, 
            ::move(pdispatchitem->m_memory));

      }

   }


   void rx::receiver::on_interprocess_receive(rx * prx, ::string && strMessage)
   {

   }


   void rx::receiver::on_interprocess_receive(rx * prx, int message, ::memory && memory)
   {

   }


   void rx::receiver::on_interprocess_post(rx * prx, ::i64 a, ::i64 b)
   {

   }


   bool interprocess_communication::close()
   {

      m_ptx->close();

      m_prx->destroy();

      return true;

   }


   void interprocess_communication::restart_apex_ipc()
   {
   }


   // calls restart if confirm_tx failed
   bool interprocess_communication::ensure_tx(const ::string & pszMessage, duration durationTimeout)
   {

      if(!m_ptx->send(pszMessage, durationTimeout))
      {

         restart_apex_ipc();

         return false;

      }

      return true;

   }


   bool interprocess_communication::ensure_tx(int message, void * pdata, int len, duration durationTimeout)
   {

      if(message == WM_APP + WM_USER)
      {

         if(!m_ptx->is_tx_ok())
         {

            restart_apex_ipc();

            return false;

         }

      }
      else if(!m_ptx->send(message, pdata, len, durationTimeout))
      {

         restart_apex_ipc();

         return false;

      }

      return true;

   }


   string app_install(string strPlatform)
   {

      return "::ca2::account::ca2_installer_install_" + strPlatform + "::7807e510-5579-11dd-ae16-0800200c7784";

   }




   // typedef int (WINAPI * LPFN_ChangeWindowMessageFilter)(const ::id & id, ::u32 dwFlag);


   //extern LPFN_ChangeWindowMessageFilter g_pfnChangeWindowMessageFilter;


   //namespace apex
   //{



      base::base()
      {

         //set_hwnd(nullptr);

      }


    


      tx::tx()
      {

      }



      void tx::open(const ::string & strChannel, launcher * plauncher)
      {

         return true;

      }


      void tx::close()
      {

         //if (get_hwnd() == nullptr)
         //{

         //   return true;

         //}

         //set_hwnd(nullptr);

         m_strBaseChannel = "";

         return true;

      }


      void tx::send(const ::string & pszMessage, const duration & durationTimeout)
      {

         if (!is_tx_ok())
         {

            return error_failed;

         }

         return ::success;

      }


      void tx::send(int message, void * pdata, int len, const duration & durationTimeout)
      {

         if (message == 0x80000000)
         {

            return false;

         }

         if (!is_tx_ok())
         {

            return false;

         }


         return true;

      }


      bool tx::is_tx_ok()
      {

         return false;

      }


      rx::rx()
      {

         m_preceiver = nullptr;

      }


      void rx::on_initialize_object()
      {

         fork([this]()
            {

               task_dispatch();

            });

         return ::success;

      }


      void rx::create(const ::string & strChannel)
      {

        return true;

      }


      void rx::destroy()
      {

         auto estatus = base::destroy();

         return estatus;

      }


      void rx::on_interprocess_receive(::string && strMessage)
      {

         if (::str::begins_ci(strMessage, "synch_"))
         {

            if (m_preceiver != nullptr)
            {

               m_preceiver->on_interprocess_receive(this, ::move(strMessage));

            }

         }
         else
         {

            dispatch_message(::move(strMessage));
            //get_application()->fork([this, prx, strMessage]()
            //{

            //   if (m_preceiver != nullptr)
            //   {

            //      m_preceiver->on_interprocess_receive(prx, strMessage);

            //   }

            //});

         }

         // ODOW - on date of writing : return ignored by this windows implementation

         //return nullptr;

      }


      void rx::on_interprocess_receive(int message, ::memory && memory)
      {

         ///memory memory(pdata, len);

         dispatch_message(message, ::move(memory));

         //if (m_preceiver != nullptr)
         //{

           // m_preceiver->on_interprocess_receive(prx, message, pdata, len);

         //}

         // ODOW - on date of writing : return ignored by this windows implementation

         //return nullptr;

      }


      void rx::on_interprocess_post(i64 a, i64 b)
      {

         if (m_preceiver != nullptr)
         {

            m_preceiver->on_interprocess_post(this, a, b);

         }

         // ODOW - on date of writing : return ignored by this windows implementation

         //return nullptr;

      }


      bool rx::on_idle()
      {

         return false;

      }


      bool rx::is_rx_ok()
      {

         return false;

      }

      
      void rx::dispatch_message(::string && strMessage)
      {

         auto pdispatchitem = __new(class dispatch_item(::move(strMessage)));

         dispatch_item(::move(pdispatchitem));

      }


      void rx::dispatch_message(::u64 uData, ::memory && memory)
      {

         auto pdispatchitem = __new(class dispatch_item(uData, ::move(memory)));

         dispatch_item(::move(pdispatchitem));

      }


      void rx::dispatch_item(__pointer(class dispatch_item) && pdispatchitem)
      {

         synchronous_lock synchronouslock(&m_mutexDispatch);

         bool bWasEmpty = m_dispatchitema.is_empty();

         m_dispatchitema.add(::move(pdispatchitem));

         if (bWasEmpty)
         {

            m_evDispatchItemNew.SetEvent();

         }

      }


      void rx::task_dispatch()
      {

         auto ptask = ::get_task();

         single_lock singlelock(&m_mutexDispatch);

         while (ptask->task_get_run())
         {

            if (m_evDispatchItemNew.wait(1_s).succeeded())
            {

               singlelock.lock();

               while (m_dispatchitema.has_element()
                  && ptask->task_get_run())
               {

                  {

                     auto pdispatchitem = m_dispatchitema.pick_first();

                     singlelock.unlock();

                     try
                     {

                        m_preceiver->on_interprocess_receive(this, ::move(pdispatchitem));

                     }
                     catch (...)
                     {

                     }

                  }

                  singlelock.lock();

               }

               m_evDispatchItemNew.ResetEvent();

               singlelock.unlock();

            }

         }

      }


      interprocess_communication::interprocess_communication()
      {

         m_durationTimeout = (5000) * 11;

      }


      interprocess_communication::~interprocess_communication()
      {


      }


//#ifdef WINDOWS
//
//
//      bool interprocess_communication::open_ab(const ::string & pszKey, const ::string & pszModule, launcher * plauncher)
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

     /* bool interprocess_communication::open_ba(const ::string & pszKey, const ::string & pszModule, launcher * plauncher)
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


      bool interprocess_communication::open_ab(const ::string & pszKey, launcher * plauncher)
      {

         m_strChannel = pszKey;

         m_prx->m_preceiver = this;

         string strChannelRx = m_strChannel + "-a";

         string strChannelTx = m_strChannel + "-b";

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


      bool interprocess_communication::open_ba(const ::string & pszKey, launcher * plauncher)
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


//#endif


      bool interprocess_communication::is_rx_tx_ok()
      {

         return m_prx->is_rx_ok() && m_ptx->is_tx_ok();
         //return false;

      }


   //} // namespace interprocess_communication


} // namespace windows



