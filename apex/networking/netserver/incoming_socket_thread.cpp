#include "framework.h"
#include "incoming_socket.h"
#include "incoming_socket_thread.h"


namespace netserver
{


   incoming_socket_thread::incoming_socket_thread()
   {

      m_strIp = "0.0.0.0";
      m_iPortMaximum = -1;


      m_iPortMinimum = 10000;
      m_iPortMaximum = 19999;


      m_iCurrentPort = m_iPortMinimum;


      m_iConnectPort = -1;


   }


   incoming_socket_thread::~incoming_socket_thread()
   {

   }


   bool incoming_socket_thread::initialize_listen_socket()
   {

      m_pincomingsocket->set_ssl_catalog(m_strCat);

      if (m_strCipherList.has_char())
      {

         m_pincomingsocket->set_ssl_cipher_list(m_strCipherList);

      }
      else
      {

         m_pincomingsocket->set_ssl_cipher_list("ECDHE-RSA-AES256-SHA384:ECDHE-RSA-AES256-SHA:ECDHE-RSA-AES128-SHA:ECDHE-RSA-RC4-SHA:DHE-RSA-AES256-SHA:DHE-RSA-AES128-SHA:RSA:SHA:3DES:!aNULL:!eNULL:!EXP:!LOW:!MD5:@STRENGTH");

      }

      m_pincomingsocket->SetListeningDetach(true);

      if (m_strCat.has_char())
      {

         m_pincomingsocket->EnableSSL();

      }

      return true;

   }


   ::pointer <::sockets::socket_handler > incoming_socket_thread::create_socket_handler()
   {

      return __create< ::sockets::socket_handler >();

   }

   
   //::pointer < ::sockets::listen_socket > socket_thread::create_listen_socket()
   //{

   //   return __id_create(m_typeatomSocket);

   //}


   void incoming_socket_thread::run()
   {

      if (m_strIp.is_empty() && m_iPortMaximum >= m_iPortMinimum)
      {

         informationf("Invalid address \"%s\" or invalid port range", m_strIp.c_str());

         throw ::exception(error_bad_argument);

      }

      while (task_get_run())
      {

         try
         {

            m_psockethandlerIncoming = create_socket_handler();

            m_psockethandlerIncoming->initialize(this);

            m_psockethandlerIncoming->EnablePool();

            m_pincomingsocket = __id_create(m_typeIncomingSocket);

            //m_pincomingsocket->initialize_listen_socket(m_typeDetachIncomingSocket);

            //m_plistensocket->initialize(this);

            initialize_listen_socket();

            m_iConnectPort = -1;

            while (::task_get_run() && m_iPortMaximum >= m_iPortMinimum)
            {

               for (m_iCurrentPort = m_iPortMinimum; ::task_get_run() && m_iCurrentPort <= m_iPortMaximum; )
               {

                  int iError = m_pincomingsocket->Bind(m_strIp, (::networking::port_t)m_iCurrentPort);

                  if (iError == 0)
                  {

                     string strMessage;

                     strMessage.formatf("\n\nBound to address %s!!\n\n", m_strIp.c_str());

                     information(strMessage);
                  }
                  else
                  {

                     if (m_iCurrentPort < m_iPortMaximum)
                     {

                        preempt(300_ms);

                        m_iCurrentPort++;

                        continue;

                     }

                     informationf("netserver::socket_thread::run Couldn't bind to address %s!!", m_strIp.c_str());

                     break;

                  }

                  m_iConnectPort = m_iCurrentPort;

                  m_pincomingsocket->set_keep_connection_after_last_read_time(0_s);

                  m_pincomingsocket->set_keep_connection_after_last_write_time(0_s);

                  m_psockethandlerIncoming->add(m_pincomingsocket);

                  while (m_psockethandlerIncoming->get_count() > 0 && task_get_run())
                  {

                     m_psockethandlerIncoming->select(0, 200'000);

                  }

                  m_iConnectPort = -1;

               }

               sleep(5000_ms);

            }

         }
         catch (...)
         {

         }

      }

      m_psockethandlerIncoming.release();

      m_pincomingsocket.release();

      information() << "exiting socket::thread";

   }


} // namespace netnode



