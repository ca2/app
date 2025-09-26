#include "framework.h"
#include "stream_socket.h"
#include "socket_handler.h"
#include "acme/exception/interface_only.h"


namespace sockets_bsd
{


   stream_socket::stream_socket() : 
      //::object(&h)
      //,
      //base_socket(h)
      //,socket(h)
      //,
      m_bConnecting(false)
      //,m_secsConnectionTimeout(5)
      ,m_bFlushBeforeClose(true)
      ,m_iMaximumConnectionRetryCount(0)
      ,m_iConnectionRetryCount(0)
      ,m_bCallOnConnect(false)
      ,m_bRetryClientConnect(false)
      ,m_iShutdownStatus(0)
   {

   }


   stream_socket::~stream_socket()
   {

   }


   void stream_socket::set_connecting(bool bConnecting)
   {

      if (::is_different(bConnecting, m_bConnecting))
      {

         m_bConnecting = bConnecting;

         if (bConnecting)
         {

            set_connection_start_time();

         }
         else
         {

            set_start_time();

         }

      }

   }


   bool stream_socket::is_connecting()
   {

      return m_bConnecting;

   }


   bool stream_socket::Ready()
   {

      if (GetSocketId() != INVALID_SOCKET && !is_connecting() && !IsCloseAndDelete())
      {

         return true;

      }

      return false;

   }


   //void stream_socket::set_maximum_connection_time(int x)
   //{
   //   m_secsConnectionTimeout = x;
   //}


   //::second stream_socket::GetConnectTimeout()
   //{

   //   return m_secsConnectionTimeout;

   //}


   void stream_socket::SetFlushBeforeClose(bool bFlushBeforeClose)
   {

      m_bFlushBeforeClose = bFlushBeforeClose;

   }


   bool stream_socket::GetFlushBeforeClose()
   {

      return m_bFlushBeforeClose;

   }


   int stream_socket::GetMaximumConnectionRetryCount()
   {

      return m_iMaximumConnectionRetryCount;

   }


   void stream_socket::SetMaximumConnectionRetryCount(int x)
   {

      m_iMaximumConnectionRetryCount = x;

   }


   int stream_socket::GetConnectionRetryCount()
   {

      return m_iConnectionRetryCount;

   }


   void stream_socket::IncrementConnectionRetryCount()
   {

      m_iConnectionRetryCount++;

   }


   void stream_socket::ResetConnectionRetryCount()
   {

      m_iConnectionRetryCount = 0;

   }


   void stream_socket::set_call_on_connect()
   {

      ::pointer < ::sockets_bsd::socket_handler > phandler = m_psockethandler;

      phandler->m_socketlistCallOnConnect.add_unique(GetSocketId());

      m_bCallOnConnect = true;

   }


   void stream_socket::clear_call_on_connect()
   {

      ::pointer < ::sockets_bsd::socket_handler > phandler = m_psockethandler;

      phandler->m_socketlistCallOnConnect.erase(GetSocketId());

      m_bCallOnConnect = false;

   }


   bool stream_socket::CallOnConnect()
   {
      
      return m_bCallOnConnect;

   }


   void stream_socket::set_retry_client_connect()
   {

      ::pointer < ::sockets_bsd::socket_handler > phandler = m_psockethandler;

      phandler->m_socketlistRetryClientConnect.add_unique(GetSocketId());

      m_bRetryClientConnect = true;

   }


   void stream_socket::clear_retry_client_connect()
   {

      ::pointer < ::sockets_bsd::socket_handler > phandler = m_psockethandler;

      phandler->m_socketlistRetryClientConnect.erase(GetSocketId());

      m_bRetryClientConnect = false;

   }


   bool stream_socket::RetryClientConnect()
   {

      return m_bRetryClientConnect;

   }


   void stream_socket::SetShutdownStatus(int x)
   {

      m_iShutdownStatus = x;

   }


   int stream_socket::GetShutdownStatus()
   {
      
      return m_iShutdownStatus;

   }


   int stream_socket::protocol()
   {
      
      throw ::interface_only();

      return -1;

   }


} // namespace sockets_bsd



