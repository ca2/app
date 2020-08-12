#include "framework.h"
#include "base/net/net_sockets.h"
#include "simpledb_socket.h"
#include "simpledb_socket_thread.h"


namespace simpledb
{


   socket_thread::socket_thread(::object * pobject) :
      ::object(pobject),
      thread(pobject),
      ::sockets::socket_handler(pobject),
      
      m_evInitialized(pobject)
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
      IGUI_MSG_LINK(WM_APP, pchannel, this, &socket_thread::OnApp);
   }


   bool socket_thread::initialize_thread()
   {
      //Application.::simpledb::application::m_pmanager->LoadEnv();


      /*   STARTUPINFO startupinfo;
      __memset(&startupinfo, 0, sizeof(startupinfo));
      if(!::CreateProcess(nullptr, "netnoderewrite.exe",
      nullptr,
      nullptr,
      TRUE,
      0,
      nullptr,
      ".",
      &startupinfo,
      &m_pi))
      {
      return FALSE;
      }


      WaitForInputIdle(m_pi.hProcess, INFINITE);


      //   m_hChildThreadId = ::OpenThread(THREAD_ALL_ACCESS, TRUE, m_pi.dwThreadId);

      ::post_thread_message(m_pi.dwThreadId, WM_APP, 0, m_nThreadID);

      post_thread_message(WM_APP, 0, 0);*/




      /*   m_plistensocket = new netnodeListenSocket(this);
      //Sleep(15000);
      if(!m_plistensocket->create(80, SOCK_STREAM))
      {
      u32 dw = ::get_last_error();
      TRACE("error %u", dw);
      return FALSE;
      }
      if(!m_plistensocket->Listen())
      {
      u32 dw = ::get_last_error();
      TRACE("error %u", dw);
      return FALSE;
      }*/
      m_evInitialized.SetEvent();
      return true;
   }


   void socket_thread::OnApp(::message::message * pmessage)
   {
      SCAST_PTR(::message::base, pbase, pmessage);
      if(pbase->m_wparam == 0)
      {

         while(m_pservice->thread_get_run())
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
                     //System.message_box(nullptr, strMessage);
                     return;
                  }
                  ::sockets::socket_handler::add(&ll);
                  while (true)
                  {
                     select(8,0);
                     if(!m_pservice-thread_get_run())
                        break;
                  }
                  if(!m_pservice->thread_get_run())
                     break;
               }
            }
            catch(...)
            {
            }
         }
      }
      if(pbase->m_wparam == 0)
      {
         m_bInitialized = true;
         m_evInitialized.SetEvent();
      }
      else if(pbase->m_wparam == 1)
      {


         ::exception::throw_not_implemented();


      }

   }


} // namespace simpledb




