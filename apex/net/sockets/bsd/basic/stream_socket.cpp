#include "framework.h"
#include "apex/net/sockets/_sockets.h"


namespace sockets
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

      if (GetSocket() != INVALID_SOCKET && !is_connecting() && !IsCloseAndDelete())
      {

         return true;

      }

      return false;

   }


   //void stream_socket::set_maximum_connection_time(i32 x)
   //{
   //   m_secsConnectionTimeout = x;
   //}


   //::secs stream_socket::GetConnectTimeout()
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


   i32 stream_socket::GetMaximumConnectionRetryCount()
   {

      return m_iMaximumConnectionRetryCount;

   }


   void stream_socket::SetMaximumConnectionRetryCount(i32 x)
   {

      m_iMaximumConnectionRetryCount = x;

   }


   i32 stream_socket::GetConnectionRetryCount()
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


   void stream_socket::SetCallOnConnect(bool bCallOnConnect)
   {

      socket_handler()->socketlist_modify(GetSocket(), e_list_call_on_connect, bCallOnConnect);

      m_bCallOnConnect = bCallOnConnect;

   }


   bool stream_socket::CallOnConnect()
   {
      
      return m_bCallOnConnect;

   }


   void stream_socket::SetRetryClientConnect(bool bSetRetryClientConnect)
   {

      socket_handler()->socketlist_modify(GetSocket(), e_list_retry_client_connect, bSetRetryClientConnect);

      m_bRetryClientConnect = bSetRetryClientConnect;

   }


   bool stream_socket::RetryClientConnect()
   {

      return m_bRetryClientConnect;

   }


   void stream_socket::SetShutdownStatus(i32 x)
   {

      m_iShutdownStatus = x;

   }


   i32 stream_socket::GetShutdownStatus()
   {
      
      return m_iShutdownStatus;

   }


   i32 stream_socket::Protocol()
   {
      
      __throw(error_interface_only);

   }


} // namespace sockets



