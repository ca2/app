#include "framework.h"
#include "simpledb_socket.h"
#include "simpledb_socket_thread.h"
#include "aura/net/sockets/bsd/basic/sockets_listen_socket.h"


namespace simpledb
{


   socket_thread::socket_thread(::object * pobject) :
      ::object(pobject),
      thread(pobject),
      ::sockets::socket_handler(pobject)
   {

      m_psocket = nullptr;
      m_evCanInit.ResetEvent();
      m_evInitialized.ResetEvent();
      m_bInitialized = false;

   }


   socket_thread::~socket_thread()
   {

   }


   void socket_thread::install_message_routing(::channel * pchannel)
   {

      MESSAGE_LINK(WM_APP, pchannel, this, &socket_thread::OnApp);

   }


   bool socket_thread::init_thread()
   {

      //papplication->::simpledb::application::m_pmanager->LoadEnv();


      /*   STARTUPINFO startupinfo;
      __memset(&startupinfo, 0, sizeof(startupinfo));
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




      /*   m_plistensocket = new netnodeListenSocket(this);
      //sleep(15000_ms);
      if(!m_plistensocket->create(80, SOCK_STREAM))
      {
      u32 dw = ::get_last_error();
      TRACE("error %u", dw);
      return false;
      }
      if(!m_plistensocket->Listen())
      {
      u32 dw = ::get_last_error();
      TRACE("error %u", dw);
      return false;
      }*/
      m_evInitialized.SetEvent();
      return true;
   }


   void socket_thread::OnApp(::message::message * pmessage)
   {
      __pointer(::message::database) pusermessage(pmessage);
      if(pusermessage->m_wparam == 0)
      {

         while(m_pservice->get_run_service())
         {
            try
            {

               EnablePool();
               ::sockets::listen_socket < socket > ll(*this);
               ll.m_bDetach = true;
               while(true)
               {
                  //m_strIp = "127.0.0.1";
                  if(m_iPort == 443)
                  {
                     ll.EnableSSL();
                  }
                  if (ll.Bind(m_strIp, (port_t) m_iPort))
                  {
                     string strMessage;
                     strMessage.Format("could not bind to address %s %d", m_strIp, m_iPort);
                     TRACE(strMessage);
                     //message_box(nullptr, strMessage);
                     return;
                  }
                  ::sockets::socket_handler::add(&ll);
                  while (true)
                  {
                     select(8,0);
                     if(!m_pservice-task_get_run())
                        break;
                  }
                  if(!m_pservice->get_run_service())
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
         m_evInitialized.SetEvent();
      }
      else if(pusermessage->m_wparam == 1)
      {

         throw interface_only_exception();

      }

   }


} // namespace simpledb




