#include "framework.h"
#include "apex/networking/sockets/_sockets.h"


namespace sockets
{


   stream_socket::stream_socket() :
      ::object(h.get_application()),
      base_socket(h),
      socket(h)
      ,m_bConnecting(false)
      ,m_secsConnectionTimeout(5)
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


   void stream_socket::set_connecting(bool x)
   {
      
      if (x != m_bConnecting)
      {
         
         m_bConnecting = x;

         if (x)
         {
            
            SetTimeout( GetConnectTimeout() );

         }
         else
         {
            
            SetTimeout( 0 );

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


   void stream_socket::SetConnectTimeout(int x)
   {
      m_secsConnectionTimeout = x;
   }


   int stream_socket::GetConnectTimeout()
   {
      return m_secsConnectionTimeout;
   }


   void stream_socket::SetFlushBeforeClose(bool x)
   {
      m_bFlushBeforeClose = x;
   }


   bool stream_socket::GetFlushBeforeClose()
   {
      return m_bFlushBeforeClose;
   }


   int stream_socket::GetConnectionRetry()
   {
      return m_iMaximumConnectionRetryCount;
   }


   void stream_socket::SetConnectionRetry(int x)
   {
      m_iMaximumConnectionRetryCount = x;
   }


   int stream_socket::GetConnectionRetryCount()
   {
      return m_iConnectionRetryCount;
   }


   void stream_socket::IncreaseConnectionRetries()
   {
      m_iConnectionRetryCount++;
   }


   void stream_socket::ResetConnectionRetries()
   {
      m_iConnectionRetryCount = 0;
   }


   void stream_socket::SetCallOnConnect(bool x)
   {
      socket_handler()->AddList(GetSocket(), LIST_CALLONCONNECT, x);
      m_bCallOnConnect = x;
   }


   bool stream_socket::CallOnConnect()
   {
      return m_bCallOnConnect;
   }


   void stream_socket::SetRetryClientConnect(bool x)
   {
      socket_handler()->AddList(GetSocket(), LIST_RETRY, x);
      m_bRetryClientConnect = x;
   }


   bool stream_socket::RetryClientConnect()
   {
      return m_bRetryClientConnect;
   }




   void stream_socket::SetShutdown(int x)
   {
      m_iShutdownStatus = x;
   }


   int stream_socket::GetShutdown()
   {
      return m_iShutdownStatus;
   }

   /** Returns IPPROTO_TCP or IPPROTO_SCTP */
   int stream_socket::Protocol()
   {

      throw ::interface_only("stream_socket::Protocol"));

      return -1;

   }


   port_t stream_socket::GetRemotePort()
   {

      return ::apex::get_system()->sockets().net().service_port(m_streamsocket->Information->RemotePort);

   }


   ::net::address stream_socket::GetRemoteAddress()
   {

      return ::net::address(get_application(), m_streamsocket->Information->RemoteAddress->CanonicalName, m_streamsocket->Information->RemotePort);

   }


   port_t stream_socket::GetLocalPort()
   {

      return ::apex::get_system()->sockets().net().service_port(m_streamsocket->Information->LocalPort);

   }


   ::net::address stream_socket::GetLocalAddress()
   {

      return ::net::address(get_application(), m_streamsocket->Information->LocalAddress->CanonicalName, m_streamsocket->Information->LocalPort);

   }


   bool stream_socket::is_connecting()
   {

      return m_bConnecting;

   }


} // namespace sockets



