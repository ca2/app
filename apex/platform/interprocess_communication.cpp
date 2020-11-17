#include "framework.h"


//namespace apex
//{


   namespace interprocess_communication
   {



      void rx::receiver::on_interprocess_receive(rx * prx, const char * pszMessage)
      {

      }


      void rx::receiver::on_interprocess_receive(rx * prx, int message, void * pdata, memsize len)
      {

      }


      void rx::receiver::on_interprocess_post(rx * prx, ::i64 a, ::i64 b)
      {

      }


      //interprocess_communication::interprocess_communication(::layered * pobjectContext) :
      //   ::object(pobject),
      //   base(pobject),
      //   tx(pobject),
      //   m_rx(pobject)
      //{

      //   m_millisTimeout = (5000) * 11;

      //}


      //interprocess_communication::~interprocess_communication()
      //{


      //}


      bool interprocess_communication::close()
      {

         tx::close();

         m_rx.destroy();

         return true;

      }

      void interprocess_communication::restart_apex_ipc()
      {
      }



      // calls restart if confirm_tx failed
      bool interprocess_communication::ensure_tx(const char * pszMessage, duration durationTimeout)
      {

         if(!send(pszMessage, durationTimeout))
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

            if(!is_tx_ok())
            {

               restart_apex_ipc();

               return false;

            }

         }
         else if(!send(message, pdata, len, durationTimeout))
         {

            restart_apex_ipc();

            return false;

         }

         return true;

      }


      string app_install(string strPlatform)
      {

         return "::ca2::account::ca2_spaboot_install_" + strPlatform + "::7807e510-5579-11dd-ae16-0800200c7784";

      }


   } // namespace interprocess_communication


//} // namespace apex



