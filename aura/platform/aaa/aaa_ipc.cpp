#include "framework.h"


namespace aura
{


   namespace ipc
   {



      void rx::receiver::on_ipc_receive(rx * prx, const ::string & pszMessage)
      {

      }


      void rx::receiver::on_ipc_receive(rx * prx, int message, void * pdata, memsize len)
      {

      }


      void rx::receiver::on_ipc_post(rx * prx, huge_integer a, huge_integer b)
      {

      }


      //ipc::ipc(::particle * pparticle) :
      //   ::object(pparticle),
      //   base(pparticle),
      //   tx(pparticle),
      //   m_rx(pparticle)
      //{

      //   m_durationTimeout = (5000) * 11;

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
      bool ipc::ensure_tx(const ::string & pszMessage, duration durationTimeout)
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

         return "::ca2::account::ca2_installer_install_" + strPlatform + "::7807e510-5579-11dd-ae16-0800200c7784";

      }


   } // namespace ipc


} // namespace aura



