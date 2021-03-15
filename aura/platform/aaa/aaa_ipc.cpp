#include "framework.h"


namespace aura
{


   namespace ipc
   {



      void rx::receiver::on_ipc_receive(rx * prx, const char * pszMessage)
      {

      }


      void rx::receiver::on_ipc_receive(rx * prx, int message, void * pdata, memsize len)
      {

      }


      void rx::receiver::on_ipc_post(rx * prx, ::i64 a, ::i64 b)
      {

      }


      //ipc::ipc(::context_object * pcontextobject) :
      //   ::object(pobject),
      //   base(pobject),
      //   tx(pobject),
      //   m_rx(pobject)
      //{

      //   m_millisTimeout = (5000) * 11;

      //}


      //ipc::~ipc()
      //{


      //}


      bool ipc::close()
      {

         tx::close();

         m_rx.destroy();

         return true;

      }

      void ipc::restart_aura_ipc()
      {
      }



      // calls restart if confirm_tx failed
      bool ipc::ensure_tx(const char * pszMessage, duration durationTimeout)
      {

         if(!send(pszMessage, durationTimeout))
         {

            restart_aura_ipc();

            return false;

         }

         return true;

      }


      bool ipc::ensure_tx(int message, void * pdata, int len, duration durationTimeout)
      {

         if(message == WM_APP + WM_USER)
         {

            if(!is_tx_ok())
            {

               restart_aura_ipc();

               return false;

            }

         }
         else if(!send(message, pdata, len, durationTimeout))
         {

            restart_aura_ipc();

            return false;

         }

         return true;

      }


      string app_install(string strPlatform)
      {

         return "::ca2::account::ca2_spaboot_install_" + strPlatform + "::7807e510-5579-11dd-ae16-0800200c7784";

      }


   } // namespace ipc


} // namespace aura



