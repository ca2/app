// Moved by camilo on 2021-07-26 02:20 BRT <3ThomasBorregaardS�rensen!!
#pragma once


namespace sockets
{


   /** \defgroup basic Basic sockets */
   /** base_socket base class.
   \ingroup basic */
   class CLASS_DECL_APEX base_socket :
      virtual public ::object
   {
   public:


      class CLASS_DECL_APEX callback
      {
      public:
         virtual void OnRawData(base_socket * psocket, void * pdata, memsize len) = 0;
      };

      friend class base_socket_handler;




      /** Data pass class from source to destination. */
      class trigger_data
      {
      public:


         base_socket *m_src;


         trigger_data() : m_src(nullptr) {}
         virtual ~trigger_data() {}

         base_socket *GetSource() const { return m_src; }
         void SetSource(base_socket *x) { m_src = x; }

      };

#ifdef BSD_STYLE_SOCKETS
      __pointer(ssl_context)  m_psslcontext;
#endif
      string                  m_password; ///< ssl password

      __pointer(base_socket_handler)   m_psockethandler; /// |-xxx-Reference-xxx-> 2021-03-08pointer of base_socket_handler in control of this socket
      SOCKET                  m_socket; ///< File descriptor

      static ::mutex *        s_pmutex;

      ::net::address          m_addressRemote; ///< Remote end ::net::address
      ::net::address          m_addressRemoteClient; ///< Address of last connect()
      file_pointer            m_pfileTrafficMonitor;

      bool                    m_b_chunked;


      ::memory_file *         m_pmemfileInput;
      bool                    m_bEnd; // should finish by not sending no more writes
      string                  m_strCat;
      string                  m_strCipherList;
      callback *              m_pcallback;
      time_t                  m_timeCreate; ///< time in seconds when this base_socket was created
      bool                    m_bDisableRead; ///< Disable checking for read events
      bool                    m_bConnected; ///< base_socket is connected (tcp/udp)
      bool                    m_bLost; ///< connection lost
      bool                    m_bErasedByHandler; ///< Set by handler before delete
      time_t                  m_timeClose; ///< time in seconds when ordered to close
      int                     m_iBindPort;
      bool                    m_bDelete; ///< Delete by handler flag
      bool                    m_bCloseAndDelete; ///< close and delete flag
      base_socket *           m_psocketParent; ///< Pointer to listen_socket class, valid for incoming sockets
      time_t                  m_timeConnectionStart; ///< Set by SetTimeout
      time_t                  m_timeConnectionMaximum; ///< Defined by SetTimeout
      time_t                  m_timeStart; ///< Set by SetTimeout
      time_t                  m_timeMaximum; ///< Defined by SetTimeout
      bool                    m_bNonBlocking;
      //    unsigned long           m_flags; ///< boolean flags, replacing old 'bool' members

#if !defined(BSD_STYLE_SOCKETS)
      manual_reset_event      m_event;
#endif

      bool                    m_bEnableSsl; ///< enable SSL for this tcp_socket
      bool                    m_bSsl; ///< ssl negotiation mode (tcp_socket)
      bool                    m_bSslServer; ///< True if this is an incoming ssl tcp_socket connection

      bool                    m_bIpv6; ///< This is an ipv6 base_socket if this one is true

      int                     m_iSocketType; ///< Type of base_socket, from base_socket() call
      string                  m_strSocketProtocol; ///< Protocol, from base_socket() call
      bool                    m_bClient; ///< only client connections are pooled
      bool                    m_bRetain; ///< keep connection on close
      bool                    m_bEnablePool; ///< true if this socket may enter in a pool

      bool                             m_bSocks4; ///< socks4 negotiation mode (tcp_socket)
      in_addr                          m_socks4_host; ///< socks4 server ::net::address
      port_t                           m_socks4_port; ///< socks4 server port number
      string                           m_socks4_userid; ///< socks4 server usedid

      bool                             m_bDetach; ///< base_socket ordered to detach flag
      bool                             m_bDetached; ///< base_socket has been detached
      __pointer(::sockets::socket_thread)         m_psocketthread; ///< detach base_socket thread class pointer
      //__pointer(base_socket_handler)   m_phandlerSlave; ///< Actual sockethandler while detached


      // LineProtocol
      bool                    m_bLineProtocol; ///< Line protocol mode flag
      bool                    m_skip_c; ///< Skip element2() char of CRLF or LFCR sequence in OnRead
      char                    m_c; ///< First char in CRLF or LFCR sequence
      string                  m_line; ///< Current line in line protocol mode

      ::e_status                    m_estatus;
      ::duration m_durationStart;

#if !defined(BSD_STYLE_SOCKETS)
      bool                    m_bErrorWriting;
      bool                    m_bErrorReading;
      bool                    m_bWaitingResponse;
      bool                    m_bExpectResponse;
      bool                    m_bExpectRequest;
      bool                    m_bReading;
      bool                    m_bWriting;
#endif

      /** base_socket mode flags. */
      /*
      enum {
      // base_socket
      SOCK_DEL =          0x01, ///< Delete by handler flag
      SOCK_CLOSE =          0x02, ///< close and delete flag
      SOCK_DISABLE_READ =       0x04, ///< Disable checking for read events
      SOCK_CONNECTED =       0x08, ///< base_socket is connected (tcp/udp)

      SOCK_ERASED_BY_HANDLER =    0x10, ///< Set by handler before delete
      // HAVE_OPENSSL
      SOCK_ENABLE_SSL =       0x20, ///< enable SSL for this tcp_socket
      SOCK_SSL =          0x40, ///< ssl negotiation mode (tcp_socket)
      SOCK_SSL_SERVER =       0x80, ///< True if this is an incoming ssl tcp_socket connection

      // ENABLE_IPV6
      SOCK_IPV6 =          0x0100, ///< This is an ipv6 base_socket if this one is true
      SOCK_CLIENT =          0x0200, ///< only client connections are pooled
      SOCK_RETAIN =          0x0400, ///< keep connection on close
      SOCK_LOST =          0x0800, ///< connection lost

      // ENABLE_SOCKS4
      SOCK_SOCKS4 =          0x1000, ///< socks4 negotiation mode (tcp_socket)
      SOCK_DETACH =          0x2000, ///< base_socket ordered to detach flag
      SOCK_DETACHED =       0x4000, ///< base_socket has been detached
      // stream_socket
      STREAMSOCK_CONNECTING =      0x8000, ///< Flag indicating connection in progress

      STREAMSOCK_FLUSH_BEFORE_CLOSE = 0x010000L, ///< Send all data before closing (default true)
      STREAMSOCK_CALL_ON_CONNECT =   0x020000L, ///< OnConnect will be called next base_socket_handler cycle if true
      STREAMSOCK_RETRY_CONNECT =   0x040000L, ///< Try another connection attempt next base_socket_handler cycle
      STREAMSOCK_LINE_PROTOCOL =   0x080000L, ///< Line protocol mode flag

      };
      */

      /** "Default" constructor */
      base_socket();

      virtual ~base_socket();


      virtual ::e_status initialize_socket(base_socket_handler* phandler);


      /** base_socket class instantiation method. Used when a "non-standard" constructor
      * needs to be used for the base_socket class. Note: the base_socket class still needs
      * the "default" constructor with one as input parameter.
      */
      virtual base_socket *new_listen_socket() { return nullptr; }

      /** Returns object to sockethandler that owns the base_socket.
      If the base_socket is detached, this is a object to the slave sockethandler.
      */
      base_socket_handler * socket_handler() const;

      /** Returns object to sockethandler that owns the base_socket.
      This one always returns the object to the original sockethandler,
      even if the base_socket is detached.
      */
      base_socket_handler * master_socket_handler() const;

      virtual void destroy_ssl_session();

      virtual void get_ssl_session();


      /** Called by listen_socket after accept but before base_socket is added to handler.
      * CTcpSocket uses this to create its ICrypt member payload.
      * The ICrypt member ::payload is created by a virtual method, therefore
      * it can't be called directly from the CTcpSocket constructor.
      * Also used to determine if incoming HTTP connection is normal (port 80)
      * or ssl (port 443).
      */
      virtual void Init();


      /** Assign this socket a file descriptor created
      by a call to socket() or otherwise. */
      void create_socket();

      /** Return file descriptor assigned to this base_socket. */
      SOCKET GetSocket();

      /** close connection immediately - internal use.
      \sa SetCloseAndDelete */
      virtual void close();


      virtual i32 close_socket(SOCKET s);


      virtual bool is_connecting();

      /** add file descriptor to sockethandler fd_set's. */
      void Set(bool bRead,bool bWrite,bool bException = true);

      /** Returns true when base_socket file descriptor is valid
      and base_socket is not about to be closed. */
      virtual bool Ready();

      virtual bool is_valid();

      /** Returns pointer to listen_socket that created this instance
      * on an incoming connection. */
      base_socket *get_parent();

      /** Used by listen_socket to set parent pointer of newly created
      * base_socket instance. */
      void set_parent(base_socket *);

      /** get listening port from listen_socket<>. */
      virtual port_t GetPort();

      /** Set base_socket non-block operation. */
      bool SetNonblocking(bool);

      /** Set base_socket non-block operation. */
      bool SetNonblocking(bool, SOCKET);

      /** Total lifetime of instance. */
      time_t Uptime();

      /** Set address/port of last connect() call. */
      void SetClientRemoteAddress(const ::net::address & address);

      /** get address/port of last connect() call. */
      ::net::address GetClientRemoteAddress();


      /** Outgoing traffic counter. */
      virtual u64 GetBytesSent(bool clear = false);

      /** Incoming traffic counter. */
      virtual u64 GetBytesReceived(bool clear = false);

      // LIST_TIMEOUT

      /** enable timeout control. 0=disable timeout check. */
      virtual void set_connection_start_time();

      virtual void set_maximum_connection_time(time_t second);

      virtual void set_start_time();

      virtual void set_maximum_time(time_t second);

      /** Check timeout. \return true if time limit reached */
      bool has_timed_out();

      /** Used by listen_socket. ipv4 and ipv6 */
      void SetRemoteHostname(const ::net::address & address);

      /** \name Event callbacks */
      //@{

      /** Called when there is something to be read from the file descriptor. */
      virtual void OnRead();
      /** Called when there is room for another write on the file descriptor. */
      virtual void OnWrite();
      /** Called on base_socket exception. */
      virtual void OnException();
      /** Called before a base_socket class is deleted by the base_socket_handler. */
      virtual void OnDelete();
      /** Called when a connection has completed. */
      virtual void OnConnect();
      /** Called when an incoming connection has been completed. */
      virtual void OnAccept();
      //void OnAccept(::winrt::Windows::Foundation::IAsyncAction ^ action, ::winrt::Windows::Foundation::AsyncStatus status);
      /** Called when a complete line has been read and the base_socket is in
      * line protocol mode. */
      virtual void OnLine(const string & );


      virtual bool on_select_idle();

      //virtual memsize read(void * buf, memsize c);

      virtual void on_read(const void * buf, memsize c);
      virtual void OnRawData(char * buf, memsize len);

      /** Called on connect timeout (5s). */
      virtual void OnConnectFailed();
      /** Called when a client base_socket is created, to set base_socket options.
      \lparam family AF_INET, AF_INET6, etc
      \lparam type SOCK_STREAM, SOCK_DGRAM, etc
      \lparam protocol Protocol number (tcp, udp, sctp, etc)
      \lparam s base_socket file descriptor
      */
      virtual void OnOptions(int family,int type,int protocol,SOCKET s) = 0;
      /** Connection retry callback - return false to abort connection attempts */
      virtual bool OnConnectRetry();
      /** a reconnect has been made */
      virtual void OnReconnect();
      /** tcp_socket: When a disconnect has been detected (recv/SSL_read returns 0 bytes). */
      virtual void OnDisconnect();
      /** time_out callback. */
      virtual void on_timeout();
      /** Connection timeout. */
      virtual void on_connection_timeout();
      //@}

      /** \name base_socket mode flags, set/reset */
      //@{
      /** Set delete by handler true when you want the sockethandler to
      delete the base_socket instance after use. */
      void SetDeleteByHandler(bool = true);
      /** Check delete by handler flag.
      \return true if this instance should be deleted by the sockethandler */
      bool DeleteByHandler();

      // LIST_CLOSE - conditional event queue

      /** Set close and delete to terminate the connection. */
      void SetCloseAndDelete(bool = true);
      /** Check close and delete flag.
      \return true if this base_socket should be closed and the instance erased */
      bool IsCloseAndDelete();

      /** Return number of seconds since base_socket was ordered to close. \sa SetCloseAndDelete */
      time_t TimeSinceClose();

      /** Ignore read events for an output only base_socket. */
      void DisableRead(bool x = true);
      /** Check ignore read events flag.
      \return true if read events should be ignored */
      bool IsDisableRead();

      /** Set connected status. */
      void SetConnected(bool = true);
      /** Check connected status.
      \return true if connected */
      bool IsConnected();

      /** Connection lost - error while reading/writing from a base_socket - tcp_socket only. */
      void SetLost();
      /** Check connection lost status flag, used by tcp_socket only.
      \return true if there was an error while r/w causing the base_socket to close */
      bool Lost();

      /** Set flag indicating the base_socket is being actively deleted by the sockethandler. */
      void SetErasedByHandler(bool x = true);
      /** get value of flag indicating base_socket is deleted by sockethandler. */
      bool ErasedByHandler();

      //@}

      /** \name Information about remote connection */
      //@{
      /** Returns address/port of remote end. */
      //::net::address GetRemoteSocketAddress();
      /** Returns address/port of remote end: ipv4. */
      //string GetRemoteIP4();
      /** Returns address/port of remote end: ipv6. */
      //struct in6_addr GetRemoteIP6();
      /** Returns remote port number: ipv4 and ipv6. */
      virtual port_t GetRemotePort();
      /** Returns remote ip as string? ipv4 and ipv6. */
      virtual ::net::address GetRemoteAddress();
      /** ipv4 and ipv6(not implemented) */
      virtual ::net::address GetRemoteHostname();
      //@}

      /** Returns local port number for bound base_socket file descriptor. */
      virtual port_t GetLocalPort();
      /** Returns local ipv4 address/port for bound base_socket file descriptor. */
      //ipaddr_t GetSockIP4();
      /** Returns local ipv4 address/port as text for bound base_socket file descriptor. */
      virtual ::net::address GetLocalAddress();
      /** Returns local ipv6 address/port for bound base_socket file descriptor. */
      //struct in6_addr GetSockIP6();
      /** Returns local ipv6 address/port as text for bound base_socket file descriptor. */
      //string GetSockAddress6();










      // --------------------------------------------------------------------------
      /** @name IP options
      When an ip or base_socket option is available on all of the operating systems
      I'm testing on (linux 2.4.x, _win32, macosx, solaris9 intel) they are not
      checked with an #ifdef below.
      This might cause a compile error on other operating systems. */
      // --------------------------------------------------------------------------

      // IP options
      //@{

      bool SetIpOptions(const void *point, socklen_t len);
      bool SetIpTOS(unsigned char tos);
      unsigned char IpTOS();
      bool SetIpTTL(int ttl);
      int IpTTL();
      bool SetIpHdrincl(bool x = true);
      bool SetIpMulticastTTL(int);
      int IpMulticastTTL();
      bool SetMulticastLoop(bool x = true);
      bool IpAddMembership(struct ip_mreq&);
      bool IpDropMembership(struct ip_mreq&);

#ifdef IP_PKTINFO
      bool SetIpPktinfo(bool x = true);
#endif
#ifdef IP_RECVTOS
      bool SetIpRecvTOS(bool x = true);
#endif
#ifdef IP_RECVTTL
      bool SetIpRecvTTL(bool x = true);
#endif
#ifdef IP_RECVOPTS
      bool SetIpRecvopts(bool x = true);
#endif
#ifdef IP_RETOPTS
      bool SetIpRetopts(bool x = true);
#endif
#ifdef IP_RECVERR
      bool SetIpRecverr(bool x = true);
#endif
#ifdef IP_MTU_DISCOVER
      bool SetIpMtudiscover(bool x = true);
#endif
#ifdef IP_MTU
      int IpMtu();
#endif
#ifdef IP_ROUTER_ALERT
      bool SetIpRouterAlert(bool x = true);
#endif
#ifdef LINUX
      bool IpAddMembership(struct ip_mreqn&);
#endif
#ifdef LINUX
      bool IpDropMembership(struct ip_mreqn&);
#endif
      //@}

      // SOCKET options
      /** @name base_socket Options */
      //@{

      bool SoAcceptconn();
      bool SetSoBroadcast(bool x = true);
      bool SetSoDebug(bool x = true);
      int SoError();
      bool SetSoDontroute(bool x = true);
      bool SetSoLinger(int onoff, int linger);
      bool SetSoOobinline(bool x = true);
      bool SetSoRcvlowat(int);
      bool SetSoSndlowat(int);
      bool SetSoRcvtimeo(struct timeval&);
      bool SetSoSndtimeo(struct timeval&);
      bool SetSoRcvbuf(int);
      int SoRcvbuf();
      bool SetSoSndbuf(int);
      int SoSndbuf();
      int SoType();
      bool SetSoReuseaddr(bool x = true);
      bool SetSoKeepalive(bool x = true);

#ifdef SO_BSDCOMPAT
      bool SetSoBsdcompat(bool x = true);
#endif
#ifdef SO_BINDTODEVICE
      bool SetSoBindtodevice(const string & intf);
#endif
#ifdef SO_PASSCRED
      bool SetSoPasscred(bool x = true);
#endif
#ifdef SO_PEERCRED
      bool SoPeercred(ucred & );
#endif
#ifdef SO_PRIORITY
      bool SetSoPriority(int);
#endif
#ifdef SO_RCVBUFFORCE
      bool SetSoRcvbufforce(int);
#endif
#ifdef SO_SNDBUFFORCE
      bool SetSoSndbufforce(int);
#endif
#ifdef SO_TIMESTAMP
      bool SetSoTimestamp(bool x = true);
#endif
#ifdef SO_NOSIGPIPE
      bool SetSoNosigpipe(bool x = true);
#endif
      //@}

      // TCP options in tcp_socket.h/tcp_socket.cpp


      string get_string() const override;


      virtual void attach(SOCKET s);

      /** Called after OnRead if base_socket is in line protocol mode.
      \sa SetLineProtocol */
      /** enable the OnLine callback. Do not create your own OnRead
      * callback when using this. */
      virtual void SetLineProtocol(bool = true);

      /** Check line protocol mode.
      \return true if base_socket is in line protocol mode */
      bool LineProtocol();






      /** @name SSL Support */
      //@{
      /** SSL client/server support - internal use. \sa tcp_socket */
      virtual void OnSSLConnect();
      /** SSL client/server support - internal use. \sa tcp_socket */
      virtual void OnSSLAccept();
      /** SSL negotiation failed for client connect. */
      virtual void OnSSLConnectFailed();
      /** SSL negotiation failed for server accept. */
      virtual void OnSSLAcceptFailed();
      /** new SSL support */
      virtual bool SSLNegotiate();
      /** Check if SSL is Enabled for this tcp_socket.
      \return true if this is a tcp_socket with SSL enabled */
      bool IsSSL();
      /** enable SSL operation for a tcp_socket. */
      void EnableSSL(bool x = true);
      /** Still negotiating ssl connection.
      \return true if ssl negotiating is still in progress */
      bool IsSSLNegotiate();
      /** Set flag indicating ssl handshaking still in progress. */
      void SetSSLNegotiate(bool x = true);
      /** OnAccept called with SSL Enabled.
      \return true if this is a tcp_socket with an incoming SSL connection */
      bool IsSSLServer();
      /** Set flag indicating that this is a tcp_socket with incoming SSL connection. */
      void SetSSLServer(bool x = true);
      /** SSL; get pointer to ssl action_context structure. */
      //         virtual SSL_CTX *GetSslContext() { return nullptr; }
      /** SSL; get pointer to ssl structure. */
      //       virtual SSL *GetSsl() { return nullptr; }
      //@}
      /** enable ipv6 for this base_socket. */
      void SetIpv6(bool x = true);
      /** Check ipv6 base_socket.
      \return true if this is an ipv6 base_socket */
      bool IsIpv6();
      /** @name Connection Pool */
      //@{
      /** Client = connecting tcp_socket. */
      void SetIsClient();
      /** base_socket type from base_socket() call. */
      void SetSocketType(int x);
      /** base_socket type from base_socket() call. */
      int GetSocketType();
      /** Protocol type from base_socket() call. */
      void SetSocketProtocol(const string & x);
      /** Protocol type from base_socket() call. */
      const string & GetSocketProtocol();
      /** Instruct a client base_socket to stay open in the connection pool after use.
      If you have connected to a server using tcp, you can call SetRetain
      to leave the connection open after your base_socket instance has been deleted.
      The next connection you make to the same server will reuse the already
      opened connection, if it is still available.
      */
      void SetRetain();
      /** Check retain flag.
      \return true if the base_socket should be moved to connection pool after use */
      bool Retain();
      /** copy connection parameters from sock. */
      void CopyConnection(base_socket *sock);
      //@}
      /** \name Socks4 support */
      //@{
      /** Socks4 client support internal use. \sa tcp_socket */
      virtual void OnSocks4Connect();
      /** Socks4 client support internal use. \sa tcp_socket */
      virtual void OnSocks4ConnectFailed();
      /** Socks4 client support internal use. \sa tcp_socket */
      virtual bool OnSocks4Read();
      /** Called when the last write caused the tcp output buffer to
      * become is_empty. */
      /** base_socket still in socks4 negotiation mode */
      bool Socks4();
      /** Set flag indicating Socks4 handshaking in progress */
      void SetSocks4(bool x = true);

      /** Set socks4 server host address/port to use */
      void SetSocks4Host(in_addr a);
#if defined(BSD_STYLE_SOCKETS)
      /** Set socks4 server hostname to use. */
      void SetSocks4Host(const string & );
#endif
      /** Socks4 server port to use. */
      void SetSocks4Port(port_t point_i32);
      /** Provide a socks4 userid if required by the socks4 server. */
      void SetSocks4Userid(const string & x);
      /** get the ip address/port of socks4 server to use.
      \return socks4 server host address/port */
      in_addr GetSocks4Host();
      /** get the socks4 server port to use.
      \return socks4 server port */
      port_t GetSocks4Port();
      /** get socks4 userid.
      \return Socks4 userid */
      const string & GetSocks4Userid();
      //@}
      /** \name Asynchronous Resolver */
      //@{
      /** Request an asynchronous dns resolution.
      \lparam host hostname to be resolved
      \lparam port port number passed along for the ride
      \return Resolve ID */
      //int Resolve(const string & host,port_t port = 0);
      //int Resolve6(const string & host, port_t port = 0);
      /** Callback returning a resolved ::net::address.
      \lparam id Resolve ID from Resolve call
      \lparam a resolved ip address/port
      \lparam port port number passed to Resolve */
      //virtual void OnResolved(int id, const ::net::address & addr);
      //virtual void OnResolved(int id, in6_addr & a, port_t port);
      /** Request asynchronous reverse dns lookup.
      \lparam a in_addr to be translated */
      //int Resolve(in_addr a);
      //int Resolve(in6_addr& a);
      /** Callback returning reverse resolve results.
      \lparam id Resolve ID
      \lparam name Resolved hostname */
      //virtual void OnReverseResolved(int id,const string & name);
      /** Callback indicating failed dns lookup.
      \lparam id Resolve ID */
      //virtual void OnResolveFailed(int id);
      //@}
      /** \name Thread Support */
      //@{
      /** Callback fires when a new base_socket thread has started and this
      base_socket is ready for operation again.
      \sa resolv_socket */
      virtual void OnDetached();

      // LIST_DETACH

      /** Internal use. */
      void SetDetach(bool x = true);
      /** Check detach flag.
      \return true if the base_socket should detach to its own thread */
      bool IsDetach();

      /** Internal use. */
      void SetDetached(bool x = true);
      /** Check detached flag.
      \return true if the base_socket runs in its own thread. */
      const bool IsDetached() const;
      /** Order this base_socket to start its own thread and call OnDetached
      when ready for operation. */
      bool prepare_for_detach();
      /** Store the slave sockethandler pointer. */
      void SetSlaveHandler(base_socket_handler *);
      /** create new thread for this base_socket to run detached in. */
      void DetachSocket(socket_map::association * passociation, socket_map * psocketmap);
      //@}


      virtual void write(const void * buf, memsize c);
      void inline print(const ::string & str) { write(str.c_str(), str.get_length()); }


      /** write traffic to an IFile. base_socket will not delete this object. */
      void SetTrafficMonitor(file_pointer p) { m_pfileTrafficMonitor = p; }
      /** All traffic will be written to this IFile, if set. */
      file_pointer GetTrafficMonitor() { return m_pfileTrafficMonitor; }

      /** \name Triggers */
      //@{
      /** Subscribe to trigger id. */
      void Subscribe(int id);
      /** Unsubscribe from trigger id. */
      void Unsubscribe(int id);
      /** Trigger callback, with data passed from source to destination. */
      virtual void OnTrigger(int id, const trigger_data & data);
      /** Trigger cancelled because source has been deleted (as in delete). */
      virtual void OnCancelled(SOCKET id);
      //@}


      virtual ::e_status run() override;
      virtual ::e_status step() override;

      //virtual void __tracef(object * pobject, enum_trace_level elevel, const char * pszFunction, const char * pszFile, int iLine, const char * pszFormat, ...);
      //virtual void __tracef(object * pobject, enum_trace_level elevel, const char * pszFunction, const char * pszFile, int iLine, e_log elog, const ::string & strContext, i32 err, const ::string & strMessage);

      virtual string get_short_description();


      virtual enum_trace_category trace_category() const override;

      //virtual void on_finalize() override;


   };



   typedef comparable_list < socket_pointer > socket_pointer_list;


} // namespace sockets


#ifdef CPP17
__declare_pair_tuple_size(::sockets::socket_flag_map);
__declare_pair_tuple_size(::sockets::socket_socket_flag_map);
__declare_pair_tuple_size(::sockets::socket_map);
#endif


using socket_list = ::comparable_list < SOCKET >;




