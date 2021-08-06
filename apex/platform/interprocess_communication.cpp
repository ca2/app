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


   void rx::receiver::on_interprocess_receive(rx * prx, const ::string & pszMessage)
   {

   }


   void rx::receiver::on_interprocess_receive(rx * prx, int message, void * pdata, memsize len)
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



      bool tx::open(const ::string & pszKey, launcher * plauncher)
      {

         return true;

      }


      bool tx::close()
      {

         //if (get_hwnd() == nullptr)
         //{

         //   return true;

         //}

         //set_hwnd(nullptr);

         m_strBaseChannel = "";

         return true;

      }


      bool tx::send(const ::string & pszMessage, duration durationTimeout)
      {

         if (!is_tx_ok())
         {

            return false;

         }


         return true;

      }


      bool tx::send(int message, void * pdata, int len, duration durationTimeout)
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


      bool rx::create(const ::string & pszKey)
      {

        return true;

      }


      ::e_status rx::destroy()
      {

         auto estatus = base::destroy();

         return estatus;

      }


      void * rx::on_interprocess_receive(rx * prx, const ::string & pszMessage)
      {

         string strMessage(pszMessage);

         if (::str::begins_ci(strMessage, "synch_"))
         {

            if (m_preceiver != nullptr)
            {

               m_preceiver->on_interprocess_receive(prx, strMessage);

            }

         }
         else
         {

            get_application()->fork([this, prx, strMessage]()
            {

               if (m_preceiver != nullptr)
               {

                  m_preceiver->on_interprocess_receive(prx, strMessage);

               }

            });

         }

         // ODOW - on date of writing : return ignored by this windows implementation

         return nullptr;

      }


      void * rx::on_interprocess_receive(rx * prx, int message, void * pdata, memsize len)
      {

         if (m_preceiver != nullptr)
         {

            m_preceiver->on_interprocess_receive(prx, message, pdata, len);

         }

         // ODOW - on date of writing : return ignored by this windows implementation

         return nullptr;

      }


      void * rx::on_interprocess_post(rx * prx, i64 a, i64 b)
      {

         if (m_preceiver != nullptr)
         {

            m_preceiver->on_interprocess_post(prx, a, b);

         }

         // ODOW - on date of writing : return ignored by this windows implementation

         return nullptr;

      }


      bool rx::on_idle()
      {

         return false;

      }


      bool rx::is_rx_ok()
      {

         return false;

      }


      interprocess_communication::interprocess_communication()
      {

         m_millisTimeout = (5000) * 11;

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



