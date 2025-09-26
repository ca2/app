#pragma once


#include "networking_bsd/sockets/basic/socket.h"
#include "apex/networking/sockets/basic/stream_socket.h"


namespace sockets_bsd
{


   /** SOCK_STREAM socket axis class.
   \ingroup basic */
   class CLASS_DECL_NETWORKING_BSD stream_socket :
      virtual public ::sockets_bsd::socket,
      virtual public ::sockets::stream_socket
   {
   public:


      bool m_bConnecting; ///< Flag indicating connection in progress
      //::second m_secsConnectionTimeout; ///< Connection timeout (seconds)
      bool m_bFlushBeforeClose; ///< Send all data before closing (default true)
      int m_iMaximumConnectionRetryCount; ///< Maximum connection retries (tcp)
      int m_iConnectionRetryCount; ///< Actual number of connection retries (tcp)
      bool m_bCallOnConnect; ///< OnConnect will be called next base_socket_handler cycle if true
      bool m_bRetryClientConnect; ///< Try another connection attempt next base_socket_handler cycle
      int m_iShutdownStatus; ///< Shutdown status


      stream_socket();
      ~stream_socket() override;


      /** socket should Check Connect on next write happening from select(). */
      void set_connecting(bool bSet = true);

      /** Check connecting flag.
      \return true if the socket is still trying to connect */
      bool is_connecting() override;

      /** Returns true when socket file descriptor is valid,
      socket connection is established, and socket is not about to
      be closed. */
      bool Ready() override;

      /** set timeout to use for connection attempt.
      \lparam x time_out in seconds */
      //void set_maximum_connection_time(int x);

      /** Return number of seconds to wait for a connection.
      \return Connection timeout (seconds) */
      //::second GetConnectTimeout();

      /** set flush before close to make a tcp socket completely is_empty its
      output buffer before closing the connection. */
      void SetFlushBeforeClose(bool = true) override;

      /** Check flush before status.
      \return true if the socket should send all data before closing */
      bool GetFlushBeforeClose() override;

      /** Define number of connection retries (tcp only).
      n = 0 - no retry
      n > 0 - number of retries
      n = -1 - unlimited retries */
      void SetMaximumConnectionRetryCount(int n) override;

      /** get number of maximum connection retries (tcp only). */
      int GetMaximumConnectionRetryCount() override;

      /** Increase number of actual connection retries (tcp only). */
      void IncrementConnectionRetryCount() override;

      /** get number of actual connection retries (tcp only). */
      int GetConnectionRetryCount() override;

      /** Reset actual connection retries (tcp only). */
      void ResetConnectionRetryCount() override;

      // e_list_call_on_connect

      /** Instruct socket to call OnConnect callback next sockethandler cycle. */
      void set_call_on_connect() override;

      void clear_call_on_connect() override;

      /** Check call on connect flag.
      \return true if OnConnect() should be called a.s.a.int_point */
      bool CallOnConnect() override;

      // e_list_retry

      /** set flag to initiate a connection attempt after a connection timeout. */
      void set_retry_client_connect() override;

      void clear_retry_client_connect() override;

      /** Check if a connection attempt should be made.
      \return true when another attempt should be made */
      bool RetryClientConnect() override;


      /** set shutdown status. */
      void SetShutdownStatus(int) override;

      /** get shutdown status. */
      int GetShutdownStatus() override;

      /** Returns IPPROTO_TCP or IPPROTO_SCTP */
      int protocol() override;

   };


} // namespace sockets_bsd


