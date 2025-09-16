#include "framework.h"
#include "stream_socket.h"
#include "acme/exception/interface_only.h"
#include "apex/networking/sockets/base/base_socket_handler.h"


namespace sockets
{


   stream_socket::stream_socket() //: 
      //::object(&h)
      //,
      //base_socket(h)
      //,socket(h)
      //,
      //m_bConnecting(false)
      //,m_secsConnectionTimeout(5)
      //m_bFlushBeforeClose(true)
      //,m_iMaximumConnectionRetryCount(0)
      //,m_iConnectionRetryCount(0)
      //,m_bCallOnConnect(false)
      //,m_bRetryClientConnect(false)
      //,m_iShutdownStatus(0)
   {

   }


   stream_socket::~stream_socket()
   {

   }


   //void stream_socket::set_connecting(bool bConnecting)
   //{

   //   if (::is_different(bConnecting, m_bConnecting))
   //   {

   //      m_bConnecting = bConnecting;

   //      if (bConnecting)
   //      {

   //         set_connection_start_time();

   //      }
   //      else
   //      {

   //         set_start_time();

   //      }

   //   }

   //}


   //bool stream_socket::is_connecting()
   //{

   //   return m_bConnecting;

   //}


   bool stream_socket::Ready()
   {

      return stream_socket_impl()->Ready();

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

      return stream_socket_impl()->SetFlushBeforeClose(bFlushBeforeClose);

   }


   bool stream_socket::GetFlushBeforeClose()
   {

      return stream_socket_impl()->GetFlushBeforeClose();

   }


   int stream_socket::GetMaximumConnectionRetryCount()
   {

      return stream_socket_impl()->GetMaximumConnectionRetryCount();


   }


   void stream_socket::SetMaximumConnectionRetryCount(int x)
   {

      stream_socket_impl()->SetMaximumConnectionRetryCount(x);

   }


   int stream_socket::GetConnectionRetryCount()
   {

      return stream_socket_impl()->GetConnectionRetryCount();

   }


   void stream_socket::IncrementConnectionRetryCount()
   {

      stream_socket_impl()->IncrementConnectionRetryCount();
      

   }


   void stream_socket::ResetConnectionRetryCount()
   {

      stream_socket_impl()->ResetConnectionRetryCount();
      

   }


   void stream_socket::set_call_on_connect()
   {

      return stream_socket_impl()->set_call_on_connect();

   }


   void stream_socket::clear_call_on_connect()
   {

      return stream_socket_impl()->clear_call_on_connect();

   }


   bool stream_socket::CallOnConnect()
   {

      return stream_socket_impl()->CallOnConnect();

   }


   void stream_socket::set_retry_client_connect()
   {

      stream_socket_impl()->set_retry_client_connect();

   }


   void stream_socket::clear_retry_client_connect()
   {

      stream_socket_impl()->clear_retry_client_connect();

   }


   bool stream_socket::RetryClientConnect()
   {

      return stream_socket_impl()->RetryClientConnect();

   }


   void stream_socket::SetShutdownStatus(int x)
   {

      stream_socket_impl()->SetShutdownStatus(x);

   }


   int stream_socket::GetShutdownStatus()
   {
      
      return stream_socket_impl()->GetShutdownStatus();

   }


   int stream_socket::protocol()
   {
      
      return stream_socket_impl()->protocol();

   }


} // namespace sockets



