#include "framework.h"
#include "base/net/net_sockets.h"
#include "simpledb_socket.h"
#include "simpledb_socket_thread.h"


namespace simpledb
{


   socket_thread::socket_thread(::particle * pparticle) :
      ::object(pparticle),
      thread(pparticle),
      ::sockets::socket_handler(pparticle),
      
      m_evInitialized(pparticle)
   {
      m_psocket = nullptr;
      m_evCanInit.reset_happening();
      m_evInitialized.reset_happening();
      m_bInitialized = false;

   }

   socket_thread::~socket_thread()
   {
   }

   void socket_thread::install_message_routing(::channel * pchannel)
   {
      MESSAGE_LINK(WM_APP, pchannel, this, &socket_thread::OnApp);
   }


   bool socket_thread::initialize_thread()
   {
      //papp->::simpledb::application::m_pmanager->LoadEnv();


      /*   STARTUPINFO startupinfo;
      memory_set(&startupinfo, 0, sizeof(startupinfo));
      if(!::CreateProcess(nullptr, "netnoderewrite.exe",
      nullptr,
      nullptr,
      true,
      0,
      nullptr,
      ".",
      &startupinfo,
      &m_pi))
      {
      return false;
      }


      WaitForInputIdle(m_pi.hProcess, U32_INFINITE_TIMEOUT);


      //   m_hChildThreadId = ::OpenThread(THREAD_ALL_ACCESS, true, m_pi.dwThreadId);

      ::post_thread_message(m_pi.dwThreadId, WM_APP, 0, m_nThreadID);

      post_thread_message(WM_APP, 0, 0);*/




      /*   m_plistensocket = ___new netnodeListenSocket(this);
      //sleep(15000_ms);
      if(!m_plistensocket->create(80, SOCK_STREAM))
      {
      unsigned int dw = ::get_last_error();
      informationf("error %u", dw);
      return false;
      }
      if(!m_plistensocket->Listen())
      {
      unsigned int dw = ::get_last_error();
      informationf("error %u", dw);
      return false;
      }*/
      m_evInitialized.set_happening();
      return true;
   }


   void socket_thread::OnApp(::message::message * pmessage)
   {
      ::pointer<::user::message>pusermessage(pmessage);
      if(pusermessage->m_wparam == 0)
      {

         while(m_pservice->task_get_run())
         {
            try
            {

               EnablePool();
               ::sockets::listen_socket < socket > hi(*this);
               hi.m_bDetach = true;
               while(true)
               {
                  //m_strIp = "127.0.0.1";
                  if(m_iPort == 443)
                  {
                     hi.EnableSSL();
                  }
                  if (hi.Bind(m_strIp, (port_t) m_iPort))
                  {
                     string strMessage;
                     strMessage.formatf("could not bind to address %s %d", m_strIp, m_iPort);
                     information(strMessage);
                     //message_box(nullptr, strMessage);
                     return;
                  }
                  ::sockets::socket_handler::add(&hi);
                  while (true)
                  {
                     select(8,0);
                     if(!m_pservice-task_get_run())
                        break;
                  }
                  if(!m_pservice->task_get_run())
                     break;
               }
            }
            catch(...)
            {
            }
         }
      }
      if(pusermessage->m_wparam == 0)
      {
         m_bInitialized = true;
         m_evInitialized.set_happening();
      }
      else if(pusermessage->m_wparam == 1)
      {


         throw ::interface_only();


      }

   }


} // namespace simpledb




