// Moved by camilo on 2021-07-26 02:20 BRT <3ThomasBorregaardSørensen!!
#pragma once


////#include "acme/primitive/primitive/object.h"
#include "acme/filesystem/file/streamable.h"


namespace sockets
{


   /** \defgroup basic Basic sockets */
   /** base_socket base class.
   \ingroup basic */
   class CLASS_DECL_APEX base_socket :
      virtual public ::object,
      virtual public ::file::writable
   {
   public:

      void * m_p2;
//      class CLASS_DECL_APEX callback
//      {
//      public:
//         virtual void OnRawData(base_socket * psocket, void * pdata, memsize len) = 0;
//      };
//
//      friend class base_socket_handler;
//
//
//
//
//      /** Data pass class from source to destination. */
//      class trigger_data
//      {
//      public:
//
//
//         base_socket *m_src;
//
//
//         trigger_data() : m_src(nullptr) {}
//         virtual ~trigger_data() {}
//
//         base_socket *GetSource() const { return m_src; }
//         void SetSource(base_socket *x) { m_src = x; }
//
//      };
//
////#ifdef BSD_STYLE_SOCKETS
////      ::pointer<ssl_context> m_psslcontext;
////#endif
     //string                  m_password; ///< ssl password

//
      //::pointer<base_socket_handler>  m_psockethandler; /// |-xxx-Reference-xxx-> 2021-03-08pointer of base_socket_handler in control of this socket
      //socket_id                  m_socket; ///< File descriptor
//
//      static ::pointer< ::mutex >        s_pmutex;
//
      //::networking::address_pointer          m_paddressRemote; ///< Remote end ::networking::address
      //::networking::address_pointer          m_paddressRemoteClient; ///< Address of last connect()
//      file_pointer            m_pfileTrafficMonitor;
//
//      bool                    m_b_chunked;
//
//
//::pointer<::memory_file>m_pmemfileInput;
  //    bool                    m_bEnd; // should finish by not sending no more writes
//      string                  m_strCat;
//      string                  m_strCipherList;
//      callback *              m_pcallback;
//      time_t                  m_timeCreate; ///< time in seconds when this base_socket was created
//      bool                    m_bDisableRead; ///< Disable checking for read events
//      bool                    m_bConnected; ///< base_socket is connected (tcp/udp)
//      bool                    m_bLost; ///< connection lost
//      bool                    m_bErasedByHandler; ///< Set by handler before delete
//      time_t                  m_timeClose; ///< time in seconds when ordered to close
//      int                     m_iBindPort;
//      bool                    m_bDelete; ///< Delete by handler flag
      //bool                    m_bCloseAndDelete; ///< close and delete flag
      //::pointer<base_socket>          m_psocketParent; ///< Pointer to listen_socket class, valid for incoming sockets
      //class ::time              m_timeConnectionStart; ///< Set by SetTimeout
      //class ::time              m_timeConnectionLastActivity; ///< Set by SetTimeout
      //class ::time              m_timeConnectionMaximum; ///< Defined by SetTimeout
      //class ::time              m_timeStart; ///< Set by SetTimeout
      //class ::time              m_timeMaximum; ///< Defined by SetTimeout
//      bool                    m_bNonBlocking;
//      //    unsigned long           m_flags; ///< tristate flags, replacing old 'bool' members
//
//#if !defined(BSD_STYLE_SOCKETS)
//      manual_reset_event      m_event;
//#endif
//
//      bool                    m_bEnableSsl; ///< enable SSL for this tcp_socket
//      bool                    m_bSsl; ///< ssl negotiation mode (tcp_socket)
//      bool                    m_bSslServer; ///< True if this is an incoming ssl tcp_socket connection
//
//      bool                    m_bIpv6; ///< This is an ipv6 base_socket if this one is true
//
//      int                     m_iSocketType; ///< Type of base_socket, from base_socket() call
//      string                  m_strSocketProtocol; ///< Protocol, from base_socket() call
//      bool                    m_bClient; ///< only client connections are pooled
//      bool                    m_bRetain; ///< keep connection on close
//      bool                    m_bEnablePool; ///< true if this socket may enter in a pool
//
//      bool                             m_bSocks4; ///< socks4 negotiation mode (tcp_socket)
//      //in_addr                          m_socks4_host; ///< socks4 server ::networking::address
//      //::networking::port_t                           m_socks4_port; ///< socks4 server port number
//      //string                           m_socks4_userid; ///< socks4 server usedid
//
//      bool                             m_bDetach; ///< base_socket ordered to detach flag
//      bool                             m_bDetached; ///< base_socket has been detached
//      ::pointer<::sockets::socket_thread>        m_psocketthread; ///< detach base_socket thread class pointer
//::pointer<base_socket_handler>  m_phandlerSlave; ///< Actual sockethandler while detached
//
//
//      // LineProtocol
//      bool                    m_bLineProtocol; ///< Line protocol mode flag
//      bool                    m_skip_c; ///< Skip element2() char of CRLF or LFCR sequence in OnRead
//      char                    m_c; ///< First char in CRLF or LFCR sequence
//      string                  m_line; ///< Current line in line protocol mode
//
//      ::e_status             m_estatus;
//      //class ::time              m_timeStart;
//#ifdef WINRT_SOCKETS
//      bool                    m_bErrorWriting;
//      bool                    m_bErrorReading;
//      bool                    m_bWaitingResponse;
//      bool                    m_bExpectResponse;
//      bool                    m_bExpectRequest;
//      bool                    m_bReading;
//      bool                    m_bWriting;
//#endif
//
//      /** base_socket mode flags. */
//      /*
//      enum {
//      // base_socket
//      SOCK_DEL =          0x01, ///< Delete by handler flag
//      SOCK_CLOSE =          0x02, ///< close and delete flag
//      SOCK_DISABLE_READ =       0x04, ///< Disable checking for read events
//      SOCK_CONNECTED =       0x08, ///< base_socket is connected (tcp/udp)
//
//      SOCK_ERASED_BY_HANDLER =    0x10, ///< Set by handler before delete
//      // HAVE_OPENSSL
//      SOCK_ENABLE_SSL =       0x20, ///< enable SSL for this tcp_socket
//      SOCK_SSL =          0x40, ///< ssl negotiation mode (tcp_socket)
//      SOCK_SSL_SERVER =       0x80, ///< True if this is an incoming ssl tcp_socket connection
//
//      // ENABLE_IPV6
//      SOCK_IPV6 =          0x0100, ///< This is an ipv6 base_socket if this one is true
//      SOCK_CLIENT =          0x0200, ///< only client connections are pooled
//      SOCK_RETAIN =          0x0400, ///< keep connection on close
//      SOCK_LOST =          0x0800, ///< connection lost
//
//      // ENABLE_SOCKS4
//      SOCK_SOCKS4 =          0x1000, ///< socks4 negotiation mode (tcp_socket)
//      SOCK_DETACH =          0x2000, ///< base_socket ordered to detach flag
//      SOCK_DETACHED =       0x4000, ///< base_socket has been detached
//      // stream_socket
//      STREAMSOCK_CONNECTING =      0x8000, ///< Flag indicating connection in progress
//
//      STREAMSOCK_FLUSH_BEFORE_CLOSE = 0x010000L, ///< Send all data before closing (default true)
//      STREAMSOCK_CALL_ON_CONNECT =   0x020000L, ///< OnConnect will be called next base_socket_handler cycle if true
//      STREAMSOCK_RETRY_CONNECT =   0x040000L, ///< Try another connection attempt next base_socket_handler cycle
//      STREAMSOCK_LINE_PROTOCOL =   0x080000L, ///< Line protocol mode flag
//
//      };
//      */
//
      /** "Default" constructor */
      base_socket();

      ~base_socket() override;


      virtual void initialize_socket(base_socket_handler* phandler);


      virtual base_socket * base_socket_composite();
      virtual const base_socket * base_socket_composite() const;

      virtual ::networking::networking * networking();
      /** base_socket class instantiation method. Used when a "non-standard" constructor
      * needs to be used for the base_socket class. Note: the base_socket class still needs
      * the "default" constructor with one as input parameter.
      */
      virtual base_socket *new_listen_socket() { return nullptr; }

      /** Returns object to sockethandler that owns the base_socket.
      If the base_socket is detached, this is a object to the slave sockethandler.
      */
      virtual base_socket_handler * socket_handler() const;

      /** Returns object to sockethandler that owns the base_socket.
      This one always returns the object to the original sockethandler,
      even if the base_socket is detached.
      */
      virtual base_socket_handler * master_socket_handler() const;


      virtual memory_file * get_input_memory_file();


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
      //virtual void create_socket();

      /** Return file descriptor assigned to this base_socket. */
      //virtual iptr get_socket_id();

      /** close connection immediately - internal use.
      \sa SetCloseAndDelete */
      virtual void close();

      virtual void _001InitSSLServer();
      virtual void set_end();


      virtual bool is_end() const;


      //virtual i32 close_socket(socket_id s);


      virtual ::networking::port_t get_bind_port() const;

      virtual bool is_connecting();

      /** add file descriptor to sockethandler fd_set's. */
      virtual void Set(bool bRead,bool bWrite,bool bException = true);

      /** Returns true when base_socket file descriptor is valid
      and base_socket is not about to be closed. */
      virtual bool Ready();

      virtual bool is_valid();

      /** Returns pointer to listen_socket that created this instance
      * on an incoming connection. */
      virtual base_socket *get_parent();

      /** Used by listen_socket to set parent pointer of newly created
      * base_socket instance. */
      virtual void set_parent(base_socket *);

      /** get listening port from listen_socket<>. */
      virtual ::networking::port_t GetPort();

      /** Set base_socket non-block operation. */
      virtual bool SetNonblocking(bool);

      /** Set base_socket non-block operation. */
      //bool SetNonblocking(bool, socket_id);

      /** Total lifetime of instance. */
      virtual time_t Uptime();

      /** Set address/port of last connect() call. */
      virtual void SetClientRemoteAddress(::networking::address * address);

      /** get address/port of last connect() call. */
      virtual ::networking::address_pointer GetClientRemoteAddress();


      /** Outgoing traffic counter. */
      virtual u64 GetBytesSent(bool clear = false);

      /** Incoming traffic counter. */
      virtual u64 GetBytesReceived(bool clear = false);

      // LIST_TIMEOUT

      /** enable timeout control. 0=disable timeout check. */
      virtual void set_connection_start_time();

      virtual void set_connection_last_activity();

      virtual void set_maximum_connection_time(const class time & time);

      virtual void set_start_time();

      virtual void set_maximum_time(const class ::time& time);

      /** Check timeout. \return true if time limit reached */
      virtual bool has_timed_out();

      /** Used by listen_socket. ipv4 and ipv6 */
      virtual void SetRemoteHostname(::networking::address * address);

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
      //virtual void OnOptions(int family,int type,int protocol,socket_id s) = 0;
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
      virtual void SetDeleteByHandler(bool = true);
      /** Check delete by handler flag.
      \return true if this instance should be deleted by the sockethandler */
      virtual bool DeleteByHandler();

      // LIST_CLOSE - conditional event queue

      /** Set close and delete to terminate the connection. */
      virtual void SetCloseAndDelete(bool = true);
      /** Check close and delete flag.
      \return true if this base_socket should be closed and the instance erased */
      virtual bool IsCloseAndDelete();

      /** Return number of seconds since base_socket was ordered to close. \sa SetCloseAndDelete */
      virtual time_t TimeSinceClose();

      /** Ignore read events for an output only base_socket. */
      virtual void DisableRead(bool x = true);
      /** Check ignore read events flag.
      \return true if read events should be ignored */
      virtual bool IsDisableRead();

      /** Set connected status. */
      virtual void SetConnected(bool = true);
      /** Check connected status.
      \return true if connected */
      virtual bool IsConnected();

      /** Connection lost - error while reading/writing from a base_socket - tcp_socket only. */
      virtual void SetLost();
      /** Check connection lost status flag, used by tcp_socket only.
      \return true if there was an error while r/w causing the base_socket to close */
      virtual bool Lost();

      /** Set flag indicating the base_socket is being actively deleted by the sockethandler. */
      virtual void SetErasedByHandler(bool x = true);
      /** get value of flag indicating base_socket is deleted by sockethandler. */
      virtual bool ErasedByHandler();

      //@}

      /** \name Information about remote connection */
      //@{
      /** Returns address/port of remote end. */
      //::networking::address GetRemoteSocketAddress();
      /** Returns address/port of remote end: ipv4. */
      //string GetRemoteIP4();
      /** Returns address/port of remote end: ipv6. */
      //struct in6_addr GetRemoteIP6();
      /** Returns remote port number: ipv4 and ipv6. */
      virtual ::networking::port_t GetRemotePort();
      /** Returns remote ip as string? ipv4 and ipv6. */
      virtual ::networking::address_pointer GetRemoteAddress();
      /** ipv4 and ipv6(not implemented) */
      virtual ::networking::address_pointer GetRemoteHostname();
      //@}

      /** Returns local port number for bound base_socket file descriptor. */
      virtual ::networking::port_t GetLocalPort();
      /** Returns local ipv4 address/port for bound base_socket file descriptor. */
      //ipaddr_t GetSockIP4();
      /** Returns local ipv4 address/port as text for bound base_socket file descriptor. */
      virtual ::networking::address_pointer GetLocalAddress();
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

      //bool SetIpOptions(const void *point, socklen_t len);
      virtual bool SetIpTOS(unsigned char tos);
      virtual unsigned char IpTOS();
      virtual bool SetIpTTL(int ttl);
      virtual int IpTTL();
      virtual bool SetIpHdrincl(bool x = true);
      virtual bool SetIpMulticastTTL(int);
      virtual int IpMulticastTTL();
      virtual bool SetMulticastLoop(bool x = true);
      //virtual bool IpAddMembership(struct ip_mreq&);
      //virtual bool IpDropMembership(struct ip_mreq&);

//#ifdef IP_PKTINFO
      virtual bool SetIpPktinfo(bool x = true);
//#endif
//#ifdef IP_RECVTOS
      virtual bool SetIpRecvTOS(bool x = true);
//#endif
//#ifdef IP_RECVTTL
      virtual bool SetIpRecvTTL(bool x = true);
//#endif
//#ifdef IP_RECVOPTS
     virtual bool SetIpRecvopts(bool x = true);
//#endif
//#ifdef IP_RETOPTS
      virtual bool SetIpRetopts(bool x = true);
//#endif
//#ifdef IP_RECVERR
      virtual bool SetIpRecverr(bool x = true);
//#endif
//#ifdef IP_MTU_DISCOVER
      virtual bool SetIpMtudiscover(bool x = true);
//#endif
//#ifdef IP_MTU
      virtual int IpMtu();
//#endif
//#ifdef IP_ROUTER_ALERT
      virtual bool SetIpRouterAlert(bool x = true);
//#endif
//#ifdef LINUX
      //virtual bool IpAddMembership(struct ip_mreqn&);
//#endif
//#ifdef LINUX
//      virtual bool IpDropMembership(struct ip_mreqn&);
//#endif
//      //@}
//
//      // socket_id options
//      /** @name base_socket Options */
//      //@{

      virtual bool SoAcceptconn();
      virtual bool SetSoBroadcast(bool x = true);
      virtual bool SetSoDebug(bool x = true);
      virtual int SoError();
      virtual bool SetSoDontroute(bool x = true);
      virtual bool SetSoLinger(int onoff, int linger);
      virtual bool SetSoOobinline(bool x = true);
      virtual bool SetSoRcvlowat(int);
      virtual bool SetSoSndlowat(int);
      //virtual bool SetSoRcvtimeo(struct timeval&);
      //virtual bool SetSoSndtimeo(struct timeval&);
      virtual bool SetSoRcvbuf(int);
      virtual int SoRcvbuf();
      virtual bool SetSoSndbuf(int);
      virtual int SoSndbuf();
      virtual int SoType();
      virtual bool SetSoReuseaddr(bool x = true);
      virtual bool SetSoKeepalive(bool x = true);

//#ifdef SO_BSDCOMPAT
      virtual bool SetSoBsdcompat(bool x = true);
//#endif
//#ifdef SO_BINDTODEVICE
      virtual bool SetSoBindtodevice(const string & intf);
//#endif
//#ifdef SO_PASSCRED
      virtual bool SetSoPasscred(bool x = true);
//#endif
//#ifdef SO_PEERCRED
      //virtual bool SoPeercred(ucred & );
//#endif
//#ifdef SO_PRIORITY
      virtual bool SetSoPriority(int);
//#endif
//#ifdef SO_RCVBUFFORCE
     virtual bool SetSoRcvbufforce(int);
//#endif
//#ifdef SO_SNDBUFFORCE
      virtual bool SetSoSndbufforce(int);
//#endif
//#ifdef SO_TIMESTAMP
      virtual bool SetSoTimestamp(bool x = true);
//#endif
//#ifdef SO_NOSIGPIPE
      virtual bool SetSoNosigpipe(bool x = true);
//#endif
      //@}

      // TCP options in tcp_socket.h/tcp_socket.cpp


      string as_string() const override;


      //virtual void attach(socket_id s);

      /** Called after OnRead if base_socket is in line protocol mode.
      \sa SetLineProtocol */
      /** enable the OnLine callback. Do not create your own OnRead
      * callback when using this. */
      virtual void SetLineProtocol(bool = true);

      /** Check line protocol mode.
      \return true if base_socket is in line protocol mode */
      virtual bool LineProtocol();






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
      /** memory_new SSL support */
      virtual bool SSLNegotiate();
      /** Check if SSL is Enabled for this tcp_socket.
      \return true if this is a tcp_socket with SSL enabled */
      virtual bool IsSSL();
      /** enable SSL operation for a tcp_socket. */
      virtual void EnableSSL(bool x = true);
      /** Still negotiating ssl connection.
      \return true if ssl negotiating is still in progress */
      virtual bool IsSSLNegotiate();
      /** Set flag indicating ssl handshaking still in progress. */
      virtual void SetSSLNegotiate(bool x = true);
      /** OnAccept called with SSL Enabled.
      \return true if this is a tcp_socket with an incoming SSL connection */
      virtual bool IsSSLServer();
      /** Set flag indicating that this is a tcp_socket with incoming SSL connection. */
      virtual void SetSSLServer(bool x = true);
      /** SSL; get pointer to ssl action_context structure. */
      //         virtual SSL_CTX *GetSslContext() { return nullptr; }
      /** SSL; get pointer to ssl structure. */
      //       virtual SSL *GetSsl() { return nullptr; }
      //@}
      /** enable ipv6 for this base_socket. */
      virtual void SetIpv6(bool x = true);
      /** Check ipv6 base_socket.
      \return true if this is an ipv6 base_socket */
      virtual bool IsIpv6();
      /** @name Connection Pool */
      //@{
      /** Client = connecting tcp_socket. */
      virtual void SetIsClient();
      /** base_socket type from base_socket() call. */
      virtual void SetSocketType(int x);
      /** base_socket type from base_socket() call. */
      virtual int GetSocketType();
      /** Protocol type from base_socket() call. */
      virtual void SetSocketProtocol(const string & x);
      /** Protocol type from base_socket() call. */
      virtual string GetSocketProtocol();

      virtual bool IsPoolEnabled() const;
      virtual void EnablePool(bool bEnable);
      /** Instruct a client base_socket to stay open in the connection pool after use.
      If you have connected to a server using tcp, you can call SetRetain
      to leave the connection open after your base_socket instance has been deleted.
      The next connection you make to the same server will reuse the already
      opened connection, if it is still available.
      */
      virtual void SetRetain();
      /** Check retain flag.
      \return true if the base_socket should be moved to connection pool after use */
      virtual bool Retain();
      /** copy connection parameters from sock. */
      virtual void CopyConnection(base_socket *sock);
      //@}
      /** \name Socks4 support */
      //@{
      ///** Socks4 client support internal use. \sa tcp_socket */
      virtual void OnSocks4Connect();
      ///** Socks4 client support internal use. \sa tcp_socket */
      virtual void OnSocks4ConnectFailed();
      ///** Socks4 client support internal use. \sa tcp_socket */
      virtual bool OnSocks4Read();
      /** Called when the last write caused the tcp output buffer to
      * become is_empty. */
      /** base_socket still in socks4 negotiation mode */
      virtual bool Socks4();
      ///** Set flag indicating Socks4 handshaking in progress */
      virtual void SetSocks4(bool x = true);

////      /** Set socks4 server host address/port to use */
////      //void SetSocks4Host(in_addr a);
////#if defined(BSD_STYLE_SOCKETS)
////      /** Set socks4 server hostname to use. */
virtual      void SetSocks4Host(const string & );
////#endif
////      /** Socks4 server port to use. */
virtual      void SetSocks4Port(::networking::port_t point_i32);
////      /** Provide a socks4 userid if required by the socks4 server. */
virtual       void SetSocks4Userid(const string & x);
////      /** get the ip address/port of socks4 server to use.
//      //\return socks4 server host address/port */
virtual string GetSocks4Host();
//      /////** get the socks4 server port to use.
//      ////\return socks4 server port */
         virtual ::networking::port_t GetSocks4Port();
//      /////** get socks4 userid.
//      ////\return Socks4 userid */
      virtual const string & GetSocks4Userid();
//      ////@}
//      ///** \name Asynchronous Resolver */
//      ////@{
//      ///** Request an asynchronous dns resolution.
//      //\lparam host hostname to be resolved
//      \lparam port port number passed along for the ride
//      \return Resolve ID */
//      //int Resolve(const string & host,::networking::port_t port = 0);
//      //int Resolve6(const string & host, ::networking::port_t port = 0);
//      /** Callback returning a resolved ::networking::address.
//      \lparam atom Resolve ID from Resolve call
//      \lparam a resolved ip address/port
//      \lparam port port number passed to Resolve */
//      //virtual void OnResolved(int atom, ::networking::address * addr);
//      //virtual void OnResolved(int atom, in6_addr & a, ::networking::port_t port);
//      /** Request asynchronous reverse dns lookup.
//      \lparam a in_addr to be translated */
//      //int Resolve(in_addr a);
//      //int Resolve(in6_addr& a);
//      /** Callback returning reverse resolve results.
//      \lparam atom Resolve ID
//      \lparam name Resolved hostname */
//      //virtual void OnReverseResolved(int atom,const string & name);
//      /** Callback indicating failed dns lookup.
//      \lparam atom Resolve ID */
//      //virtual void OnResolveFailed(int atom);
//      //@}
//      /** \name Thread Support */
      //@{
      /** Callback fires when a memory_new base_socket thread has started and this
      base_socket is ready for operation again.
      \sa resolv_socket */
      virtual void OnDetached();

      // LIST_DETACH

      /** Internal use. */
      virtual void SetDetach(bool x = true);
      /** Check detach flag.
      \return true if the base_socket should detach to its own thread */
      virtual bool IsDetach();

      /** Internal use. */
      virtual void SetDetached(bool x = true);
      /** Check detached flag.
      \return true if the base_socket runs in its own thread. */
      virtual const bool IsDetached() const;
      /** Order this base_socket to start its own thread and call OnDetached
      when ready for operation. */
      virtual bool prepare_for_detach();
      /** Store the slave sockethandler pointer. */
      virtual void SetSlaveHandler(base_socket_handler *);
      /** create memory_new thread for this base_socket to run detached in. */
      //void DetachSocket(socket_map::association * passociation, socket_map * psocketmap);
      ////@}


      using ::file::writable::write;
      void write(const void * p, ::memsize s) override;


      inline void print(const ::string & str) { write(str); }


      /** write traffic to an IFile. base_socket will not delete this object. */
      virtual void SetTrafficMonitor(file_pointer p);
      /** All traffic will be written to this IFile, if set. */
      virtual file_pointer GetTrafficMonitor();

      /** \name Triggers */
      //@{
      /** Subscribe to trigger atom. */
      virtual void Subscribe(int atom);
      /** Unsubscribe from trigger atom. */
      virtual void Unsubscribe(int atom);
      /** Trigger callback, with data passed from source to destination. */
      //virtual void OnTrigger(int atom, const trigger_data & data);
      /** Trigger cancelled because source has been deleted (as in delete). */
      //virtual void OnCancelled(socket_id atom);
      //@}


      virtual void run() override;
      virtual bool step() override;

      //virtual void __tracef(object * pparticle, enum_trace_level elevel, const ::scoped_string & scopedstrFunction, const ::scoped_string & scopedstrFile, int iLine, const ::scoped_string & scopedstrFormat, ...);
      //virtual void __tracef(object * pparticle, enum_trace_level elevel, const ::scoped_string & scopedstrFunction, const ::scoped_string & scopedstrFile, int iLine, e_log elog, const ::string & strContext, i32 err, const ::string & strMessage);

      virtual string get_short_description();


      virtual enum_trace_category trace_category() const override;

      //virtual void on_finalize() override;


   };




} // namespace sockets


#ifdef CPP17
__declare_pair_tuple_size(::sockets::socket_flag_map);
__declare_pair_tuple_size(::sockets::socket_socket_flag_map);
__declare_pair_tuple_size(::sockets::socket_map);
#endif







