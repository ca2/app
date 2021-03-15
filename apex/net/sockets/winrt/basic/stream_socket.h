#pragma once


   namespace sockets
   {


      /** SOCK_STREAM socket base class.
      \ingroup basic */
      class CLASS_DECL_APEX stream_socket :
         virtual public socket
      {
      public:


         ::Windows::Networking::Sockets::StreamSocket ^  m_streamsocket;
         ::Windows::Storage::Streams::DataWriter ^       m_writer;


         bool m_bConnecting; ///< Flag indicating connection in progress
         int m_connect_timeout; ///< Connection timeout (seconds)
         bool m_flush_before_close; ///< Send all data before closing (default true)
         int m_connection_retry; ///< Maximum connection retries (tcp)
         int m_retries; ///< Actual number of connection retries (tcp)
         bool m_call_on_connect; ///< OnConnect will be called next base_socket_handler cycle if true
         bool m_b_retry_connect; ///< Try another connection attempt next base_socket_handler cycle
         int m_shutdown; ///< Shutdown status


         stream_socket();
         ~stream_socket();


         /** socket should Check Connect on next write event from select(). */
         void SetConnecting(bool = true);

         /** Check connecting flag.
         \return true if the socket is still trying to connect */
         bool Connecting();

         /** Returns true when socket file descriptor is valid,
         socket connection is established, and socket is not about to
         be closed. */
         bool Ready();

         /** Set timeout to use for connection attempt.
         \param x Timeout in seconds */
         void SetConnectTimeout(int x);

         /** Return number of seconds to wait for a connection.
         \return Connection timeout (seconds) */
         int GetConnectTimeout();

         /** Set flush before close to make a tcp socket completely is_empty its
         output buffer before closing the connection. */
         void SetFlushBeforeClose(bool = true);

         /** Check flush before status.
         \return true if the socket should send all data before closing */
         bool GetFlushBeforeClose();

         /** Define number of connection retries (tcp only).
         n = 0 - no retry
         n > 0 - number of retries
         n = -1 - unlimited retries */
         void SetConnectionRetry(int n);

         /** get number of maximum connection retries (tcp only). */
         int GetConnectionRetry();

         /** Increase number of actual connection retries (tcp only). */
         void IncreaseConnectionRetries();

         /** get number of actual connection retries (tcp only). */
         int GetConnectionRetries();

         /** Reset actual connection retries (tcp only). */
         void ResetConnectionRetries();

         // LIST_CALLONCONNECT

         /** Instruct socket to call OnConnect callback next sockethandler cycle. */
         void SetCallOnConnect(bool x = true);

         /** Check call on connect flag.
         \return true if OnConnect() should be called a.s.a.p */
         bool CallOnConnect();

         // LIST_RETRY

         /** Set flag to initiate a connection attempt after a connection timeout. */
         void SetRetryClientConnect(bool x = true);

         /** Check if a connection attempt should be made.
         \return true when another attempt should be made */
         bool RetryClientConnect();


         /** Set shutdown status. */
         void SetShutdown(int);

         /** get shutdown status. */
         int GetShutdown();

         /** Returns IPPROTO_TCP or IPPROTO_SCTP */
         virtual int Protocol();

         virtual port_t GetRemotePort();
         virtual ::net::address GetRemoteAddress();
         virtual port_t GetLocalPort();
         virtual ::net::address GetLocalAddress();

         virtual bool is_connecting();

      };


   } // namespace sockets


