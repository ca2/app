#pragma once


namespace sockets
{


   /** SOCK_STREAM socket axis class.
   \ingroup basic */
   class CLASS_DECL_APEX stream_socket :
      virtual public socket
   {
   public:


      bool m_bConnecting; ///< Flag indicating connection in progress
      i32 m_connect_timeout; ///< Connection timeout (seconds)
      bool m_flush_before_close; ///< Send all data before closing (default true)
      i32 m_connection_retry; ///< Maximum connection retries (tcp)
      i32 m_retries; ///< Actual number of connection retries (tcp)
      bool m_call_on_connect; ///< OnConnect will be called next base_socket_handler cycle if true
      bool m_b_retry_connect; ///< Try another connection attempt next base_socket_handler cycle
      i32 m_shutdown; ///< Shutdown status

      stream_socket(base_socket_handler& );
      virtual ~stream_socket();


      /** socket should Check Connect on next write event from select(). */
      void SetConnecting(bool = true);

      /** Check connecting flag.
      \return true if the socket is still trying to connect */
      bool Connecting();

      /** Returns true when socket file descriptor is valid,
      socket connection is established, and socket is not about to
      be closed. */
      bool Ready();

      /** set timeout to use for connection attempt.
      \lparam x Timeout in seconds */
      void SetConnectTimeout(i32 x);

      /** Return number of seconds to wait for a connection.
      \return Connection timeout (seconds) */
      i32 GetConnectTimeout();

      /** set flush before close to make a tcp socket completely is_empty its
      output buffer before closing the connection. */
      void SetFlushBeforeClose(bool = true);

      /** Check flush before status.
      \return true if the socket should send all data before closing */
      bool GetFlushBeforeClose();

      /** Define number of connection retries (tcp only).
      n = 0 - no retry
      n > 0 - number of retries
      n = -1 - unlimited retries */
      void SetConnectionRetry(i32 n);

      /** get number of maximum connection retries (tcp only). */
      i32 GetConnectionRetry();

      /** Increase number of actual connection retries (tcp only). */
      void IncreaseConnectionRetries();

      /** get number of actual connection retries (tcp only). */
      i32 GetConnectionRetries();

      /** Reset actual connection retries (tcp only). */
      void ResetConnectionRetries();

      // LIST_CALLONCONNECT

      /** Instruct socket to call OnConnect callback next sockethandler cycle. */
      void SetCallOnConnect(bool x = true);

      /** Check call on connect flag.
      \return true if OnConnect() should be called a.s.a.point_i32 */
      bool CallOnConnect();

      // LIST_RETRY

      /** set flag to initiate a connection attempt after a connection timeout. */
      void SetRetryClientConnect(bool x = true);

      /** Check if a connection attempt should be made.
      \return true when another attempt should be made */
      bool RetryClientConnect();


      /** set shutdown status. */
      void SetShutdown(i32);

      /** get shutdown status. */
      i32 GetShutdown();

      /** Returns IPPROTO_TCP or IPPROTO_SCTP */
      virtual i32 Protocol();

   };


} // namespace sockets


