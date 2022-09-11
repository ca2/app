#include "framework.h"
#include "_netserver.h"


namespace netserver
{


   socket_thread_base::socket_thread_base()
   {

      m_strIp = "0.0.0.0";
      m_iPortMaximum = -1;


      m_iPortMinimum = 10000;
      m_iPortMaximum = 19999;


      m_iCurrentPort = m_iPortMinimum;


      m_iConnectPort = -1;


   }


   socket_thread_base::~socket_thread_base()
   {

   }




   bool socket_thread_base::initialize_listen_socket()
   {

      //m_plistensocket->m_strCat = m_strCat;

      //m_plistensocket->m_strCipherList = m_strCipherList;

      //m_plistensocket->m_bDetach = true;

      //if (m_plistensocket->m_strCat.has_char())
      //{

      //   m_plistensocket->EnableSSL();

      //}

      return true;

   }


   ::netserver::socket_handler * socket_thread_base::new_socket_handler()
   {

      return new netserver::socket_handler;

   }

   
   ::sockets::listen_socket_base * socket_thread_base::new_listen_socket()
   {

      return nullptr;

   }


   void socket_thread_base::run()
   {

      if (m_strIp.is_empty() && m_iPortMaximum >= m_iPortMinimum)
      {

         string strMessage;

         strMessage.format("Invalid address \"%s\" or invalid port range", m_strIp.c_str());

         TRACE(strMessage);

         throw ::exception(error_bad_argument);

      }

      while (task_get_run())
      {

         try
         {

            m_psockethandler = ::move_transfer(new_socket_handler());

            m_psockethandler->initialize(this);

            m_psockethandler->EnablePool();

            m_plistensocket = ::move_transfer(new_listen_socket());

            m_plistensocket->initialize(this);

            initialize_listen_socket();

            m_iConnectPort = -1;

            while (::task_get_run() && m_iPortMaximum >= m_iPortMinimum)
            {

               for (m_iCurrentPort = m_iPortMinimum; ::task_get_run() && m_iCurrentPort <= m_iPortMaximum; )
               {

                  int iError = m_plistensocket->Bind(m_strIp, (::networking::port_t)m_iCurrentPort);

                  if (iError != 0)
                  {

                     if (m_iCurrentPort < m_iPortMaximum)
                     {

                        preempt(300_ms);

                        m_iCurrentPort++;

                        continue;

                     }

                     string strMessage;

                     strMessage.format("\n\netserver::socket_thread_base::run Couldn't bind to address %s!!\n\n", m_strIp.c_str());

                     TRACE(strMessage);

                     break;

                  }

                  m_iConnectPort = m_iCurrentPort;

                  m_plistensocket->set_maximum_time(0_s);

                  m_psockethandler->add(m_plistensocket);

                  while (m_psockethandler->get_count() > 0 && task_get_run())
                  {

                     m_psockethandler->select(1, 0);

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

      m_psockethandler.release();

      m_plistensocket.release();

      //return ::success;

   }


} // namespace netnode



