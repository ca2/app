#include "framework.h"
#include "stream_socket.h"
#include "acme/exception/interface_only.h"
#include "apex/networking/sockets/base/socket_handler.h"


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

   //void stream_socket::set_maximum_connection_time(i32 x)
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


   i32 stream_socket::GetMaximumConnectionRetryCount()
   {

      return stream_socket_impl()->GetMaximumConnectionRetryCount();


   }


   void stream_socket::SetMaximumConnectionRetryCount(i32 x)
   {

      stream_socket_impl()->SetMaximumConnectionRetryCount(x);

   }


   i32 stream_socket::GetConnectionRetryCount()
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


   void stream_socket::SetCallOnConnect(bool bCallOnConnect)
   {

      //socket_handler()->socket_id_list_modify(get_socket_id(), e_list_call_on_connect, bCallOnConnect);

      return stream_socket_impl()->SetCallOnConnect(bCallOnConnect);

   }


   bool stream_socket::CallOnConnect()
   {

      return stream_socket_impl()->CallOnConnect();

   }


   void stream_socket::SetRetryClientConnect(bool bSetRetryClientConnect)
   {

      //socket_handler()->socket_id_list_modify(get_socket_id(), e_list_retry_client_connect, bSetRetryClientConnect);

      stream_socket_impl()->SetRetryClientConnect(bSetRetryClientConnect);

   }


   bool stream_socket::RetryClientConnect()
   {

      return stream_socket_impl()->RetryClientConnect();

   }


   void stream_socket::SetShutdownStatus(i32 x)
   {

      stream_socket_impl()->SetShutdownStatus(x);

   }


   i32 stream_socket::GetShutdownStatus()
   {
      
      return stream_socket_impl()->GetShutdownStatus();

   }


   i32 stream_socket::Protocol()
   {
      
      return stream_socket_impl()->Protocol();

   }


} // namespace sockets



