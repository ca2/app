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
      //::secs m_secsConnectionTimeout; ///< Connection timeout (seconds)
      bool m_bFlushBeforeClose; ///< Send all data before closing (default true)
      i32 m_iMaximumConnectionRetryCount; ///< Maximum connection retries (tcp)
      i32 m_iConnectionRetryCount; ///< Actual number of connection retries (tcp)
      bool m_bCallOnConnect; ///< OnConnect will be called next base_socket_handler cycle if true
      bool m_bRetryClientConnect; ///< Try another connection attempt next base_socket_handler cycle
      i32 m_iShutdownStatus; ///< Shutdown status


      stream_socket();
      ~stream_socket() override;


      /** socket should Check Connect on next write event from select(). */
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
      //void set_maximum_connection_time(i32 x);

      /** Return number of seconds to wait for a connection.
      \return Connection timeout (seconds) */
      //::secs GetConnectTimeout();

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
      void SetMaximumConnectionRetryCount(i32 n);

      /** get number of maximum connection retries (tcp only). */
      i32 GetMaximumConnectionRetryCount();

      /** Increase number of actual connection retries (tcp only). */
      void IncrementConnectionRetryCount();

      /** get number of actual connection retries (tcp only). */
      i32 GetConnectionRetryCount();

      /** Reset actual connection retries (tcp only). */
      void ResetConnectionRetryCount();

      // e_list_call_on_connect

      /** Instruct socket to call OnConnect callback next sockethandler cycle. */
      void SetCallOnConnect(bool x = true);

      /** Check call on connect flag.
      \return true if OnConnect() should be called a.s.a.point_i32 */
      bool CallOnConnect();

      // e_list_retry

      /** set flag to initiate a connection attempt after a connection timeout. */
      void SetRetryClientConnect(bool x = true);

      /** Check if a connection attempt should be made.
      \return true when another attempt should be made */
      bool RetryClientConnect();


      /** set shutdown status. */
      void SetShutdownStatus(i32);

      /** get shutdown status. */
      i32 GetShutdownStatus();

      /** Returns IPPROTO_TCP or IPPROTO_SCTP */
      virtual i32 Protocol();

   };


} // namespace sockets


