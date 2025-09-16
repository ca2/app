#pragma once


#include "socket.h"


namespace sockets
{


   /** SOCK_STREAM socket axis class.
   \ingroup basic */
   class CLASS_DECL_APEX stream_socket :
      virtual public socket
   {
   public:

      ////bool m_bConnecting; ///< Flag indicating connection in progress
      ////::second m_secsConnectionTimeout; ///< Connection timeout (seconds)
      //bool m_bFlushBeforeClose; ///< Send all data before closing (default true)
      //int m_iMaximumConnectionRetryCount; ///< Maximum connection retries (tcp)
      //int m_iConnectionRetryCount; ///< Actual number of connection retries (tcp)
      //bool m_bCallOnConnect; ///< OnConnect will be called next base_socket_handler cycle if true
      //bool m_bRetryClientConnect; ///< Try another connection attempt next base_socket_handler cycle
      //int m_iShutdownStatus; ///< Shutdown status

      stream_socket();
      ~stream_socket() override;


      /** socket should Check Connect on next write happening from select(). */
      //void set_connecting(bool bSet = true);

      /** Check connecting flag.
      \return true if the socket is still trying to connect */
      //bool is_connecting() override;

      /** Returns true when socket file descriptor is valid,
      socket connection is established, and socket is not about to
      be closed. */
      bool Ready() override;
      

      //virtual stream_socket * stream_socket_interface();
      //virtual const stream_socket * stream_socket_interface() const;

      
      /** set timeout to use for connection attempt.
      \lparam x time_out in seconds */
      //void set_maximum_connection_time(int x);

      /** Return number of seconds to wait for a connection.
      \return Connection timeout (seconds) */
      //::second GetConnectTimeout();

      /** set flush before close to make a tcp socket completely is_empty its
      output buffer before closing the connection. */
      virtual void SetFlushBeforeClose(bool = true);

      /** Check flush before status.
      \return true if the socket should send all data before closing */
      virtual bool GetFlushBeforeClose();

      /** Define number of connection retries (tcp only).
      n = 0 - no retry
      n > 0 - number of retries
      n = -1 - unlimited retries */
      virtual void SetMaximumConnectionRetryCount(int n);

      /** get number of maximum connection retries (tcp only). */
      virtual int GetMaximumConnectionRetryCount();

      /** Increase number of actual connection retries (tcp only). */
      virtual void IncrementConnectionRetryCount();

      /** get number of actual connection retries (tcp only). */
      virtual int GetConnectionRetryCount();

      /** Reset actual connection retries (tcp only). */
      virtual void ResetConnectionRetryCount();

      // e_list_call_on_connect

      /** Instruct socket to call OnConnect callback next sockethandler cycle. */
      virtual void set_call_on_connect();
      virtual void clear_call_on_connect();

      /** Check call on connect flag.
      \return true if OnConnect() should be called a.s.a.int_point */
      virtual bool CallOnConnect();

      // e_list_retry

      /** set flag to initiate a connection attempt after a connection timeout. */
      virtual void set_retry_client_connect();

      virtual void clear_retry_client_connect();

      /** Check if a connection attempt should be made.
      \return true when another attempt should be made */
      virtual bool RetryClientConnect();


      /** set shutdown status. */
      virtual void SetShutdownStatus(int);

      /** get shutdown status. */
      virtual int GetShutdownStatus();

      /** Returns IPPROTO_TCP or IPPROTO_SCTP */
      virtual int protocol();

   };


} // namespace sockets


