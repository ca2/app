#include "framework.h"
#include "_.h"


namespace netserver
{


   socket_thread::socket_thread()
   {

      m_iPort = 80;
      m_iSsl = -1;
      m_strIp = "0.0.0.0";

   }


   socket_thread::~socket_thread()
   {

   }


   ::netserver::socket_handler * socket_thread::new_socket_handler()
   {

      return new netserver::socket_handler(get_context_object());


   }


   ::sockets::listen_socket_base * socket_thread::new_listen_socket()
   {

      return new ::sockets::listen_socket < socket > (*m_psockethandler);

   }


   bool socket_thread::initialize_listen_socket()
   {

      m_plistensocket->m_strCat = m_strCat;

      m_plistensocket->m_strCipherList = m_strCipherList;

      m_plistensocket->m_bDetach = true;

      if (m_plistensocket->m_strCat.has_char() &&
            (m_iSsl > 0 || (m_iSsl < 0 && (m_iPort == 443 || ::str::ends(__str(m_iPort), "443")))))
      {

         m_plistensocket->EnableSSL();

      }

      return true;

   }


   ::estatus socket_thread::run()
   {

      if (m_strIp.is_empty() || m_iPort <= 0)
      {

         string strMessage;

         strMessage.Format("Invalid address \"%s\" or invalid port %d", m_strIp.c_str(), m_iPort);

         TRACE(strMessage);

         return error_invalid_argument;

      }

      while (thread_get_run())
      {

         try
         {

            m_psockethandler = ::move_transfer(new_socket_handler());

            m_psockethandler->initialize(this);

            m_psockethandler->EnablePool();

            m_plistensocket = ::move_transfer(new_listen_socket());

            m_plistensocket->initialize(this);

            initialize_listen_socket();

            while (::thread_get_run())
            {

               int iError = m_plistensocket->Bind(m_strIp, (port_t)m_iPort);

               if(iError != 0)
               {

                  string strMessage;

                  strMessage.Format("\n\netserver::socket_thread::run Couldn't bind to address %s:%d!!\n\n", m_strIp.c_str(), m_iPort);

                  TRACE(strMessage);

                  millis_sleep(5000);

                  continue;

               }

               m_psockethandler->add(m_plistensocket);

               while (m_psockethandler->get_count() > 0 && thread_get_run())
               {

                  m_psockethandler->select(1, 0);

               }

            }

         }
         catch (...)
         {

         }

      }

      m_psockethandler.release();

      m_plistensocket.release();

      return ::success;

   }


} // namespace netnode



