#pragma once


#include "apex/networking/sockets/base/socket_handler.h"


namespace sockets
{


   class base_socket;
   class resolv_server;


   class CLASS_DECL_APEX socket_handler :
      virtual public base_socket_handler
   {
   public:

      

      ::pointer<socket_handler>     m_pcomposite;
      ::pointer<::apex::log>    m_splogger; ///< Registered log class, or nullptr

      //socket_map                 m_socketmap; ///< Active sockets map
      //socket_map                 m_socketmapAdd; ///< Sockets to be added to sockets map
      //socket_pointer_list        m_delete; ///< Sockets to be deleted (failed when add)
      bool                       m_b_use_mutex; ///< ::pointer < ::mutex > correctly initialized
      //socket_id                     m_maxsock; ///< Highest file descriptor + 1 in active sockets list
      //::count                    m_countR;
      //::count                    m_countW;
      //::count                    m_countE;
      //fd_set                     m_rfds; ///< file descriptor set monitored for read events
      //fd_set                     m_wfds; ///< file descriptor set monitored for write events
      //fd_set                     m_efds; ///< file descriptor set monitored for exceptions
      i32                        m_iPreviousError; ///< debug select() error
      class ::time                       m_timeLastError;
      posix_time                     m_tlast; ///< timeout control

      // state lists
      //socket_id_list                m_socketidlist; ///< Active file descriptor list
      //socket_id_list                m_socketidlistErase; ///< File descriptors that are to be erased from m_sockets
      //socket_id_list                m_socketidlistCallOnConnect; ///< checklist CallOnConnect
      //socket_id_list                m_socketidlistDetach; ///< checklist detach
      //socket_id_list                m_socketidlistTimeout; ///< checklist timeout
      //socket_id_list                m_socketidlistRetryClientConnect; ///< checklist retry client connect
      //socket_id_list                m_socketidlistClose; ///< checklist close and delete
      string                    m_socks4_host; ///< Socks4 server host ip
      ::networking::port_t                     m_socks4_port; ///< Socks4 server port number
      string                     m_socks4_userid; ///< Socks4 userid
      bool                       m_bTryDirect; ///< Try direct connection if socks4 server fails
      //i32                        m_resolv_id; ///< Resolver atom counter
      //::task_pointer        m_resolver; ///< Resolver thread pointer
      //::networking::port_t                     m_resolver_port; ///< Resolver listen port
      //socket_flag_map            m_resolve_q; ///< resolve queue
      //bool                       m_bEnablePool; ///< Connection pool enabled if true
      i32                        m_next_trigger_id; ///< Unique trigger atom counter
      //socket_map                 m_trigger_src; ///< mapping trigger atom to source base_socket
      //socket_socket_flag_map     m_trigger_dst; ///< mapping trigger atom to destination sockets
      //bool                       m_slave; ///< Indicates that this is a base_socket_handler run in socket_thread


      //socket_handler(::apex::log * plogger = nullptr);
      socket_handler();
      ~socket_handler() override;

      
      i64 increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
      i64 decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;


      void initialize(::particle * pparticle) override;

      void cleanup_handler();

      bool call_on_connect();

//      synchronization & GetMutex() const override;
      

      //resolv_server * resolver();

      /** add base_socket instance to base_socket map. Removal is always automatic. */
      //void restart_socket(socket_id socket) override;

      //void add2(const socket_pointer & psocket) override;
      //void move2(socket_pointer && psocket) override;
      //void transfer(socket_map::association* passociation, socket_map* psocketmap = nullptr) override;
      //void _move(socket_map::association* passociation, socket_map* psocketmap) override;

      //virtual bool contains(base_socket *) override;

      ///** get status of read/write/exception file descriptor set for a base_socket. */
      //void get(socket_id s,bool& r,bool& w,bool& e) override;

      ///** set read/write/exception file descriptor sets (fd_set). */
      //void set(socket_id s,bool bRead,bool bWrite,bool bException = true) override;

      /** Wait for events, generate callbacks. */
      i32 select(i32 sec, i32 usec) override;

      /** This method will not return until an event has been detected. */
      i32 select() override;

      /** Wait for events, generate callbacks. */
      i32 select(const class time & timeWait) override;

      /** Check that a base_socket really is handled by this base_socket handler. */
      bool Valid(base_socket *) override;

      /** Return number of sockets handled by this handler.  */
      ::count get_count() override;

      /** Override and return false to deny all incoming connections.
      \lparam point_i32 listen_socket class pointer (use GetPort to identify which one) */
      bool OkToAccept(base_socket *point_i32) override;

      ///** Called by base_socket when a base_socket changes state. */
      //socket_id_list& socket_id_list_get(enum_list elist) override;
      //void socket_id_list_modify(socket_id s, enum_list elist, bool bAdd) override;
      //void socket_id_list_add(socket_id s, enum_list elist) override;
      //void socket_id_list_erase(socket_id s, enum_list elist) override;

      //void erase_socket_by_id(socket_id s) override;

      // Connection pool
      /** find available open connection (used by connection pool). */
      //::pointer<pool_socket>FindConnection(i32 type,const string & protocol, ::networking::address * address) override;
      /** enable connection pool (by default disabled). */
      void EnablePool(bool x = true) override;
      /** Check pool status.
      \return true if connection pool is enabled */
      bool PoolEnabled() override;

      // Socks4
      ///** set socks4 server ip that all memory_new tcp sockets should use. */
      //void SetSocks4Host(in_addr addr) override;
      ///** set socks4 server hostname that all memory_new tcp sockets should use. */
      //void SetSocks4Host(const string & ) override;
      ///** set socks4 server port number that all memory_new tcp sockets should use. */
      //void SetSocks4Port(::networking::port_t) override;
      ///** set optional socks4 userid. */
      //void SetSocks4Userid(const string & ) override;
      /** If connection to socks4 server fails, immediately try direct connection to final host. */
      //void SetSocks4TryDirect(bool x = true) override;
      ///** get socks4 server ip.
      //\return socks4 server ip */
      //in_addr GetSocks4Host() override;
      ///** get socks4 port number.
      //\return socks4 port number */
      //::networking::port_t GetSocks4Port() override;
      ///** get socks4 userid (optional).
      //\return socks4 userid */
      //const string & GetSocks4Userid() override;
      ///** Check status of socks4 try direct flag.
      //\return true if direct connection should be tried if connection to socks4 server fails */
      //bool Socks4TryDirect() override;

      // DNS resolve server
      /** enable asynchronous DNS.
      \lparam port Listen port of asynchronous dns server */
      //void EnableResolver(::networking::port_t port = 16667) override;
      /** Check resolver status.
      \return true if resolver is enabled */
      //bool ResolverEnabled() override;
      /** Queue a dns request.
      \lparam host Hostname to be resolved
      \lparam port Port number will be echoed in base_socket::OnResolved callback */
      //i32 Resolve(base_socket *,const string & host,::networking::port_t port) override;
      //i32 Resolve6(base_socket *,const string & host,::networking::port_t port) override;
      /** Do a reverse dns lookup. */
      //i32 Resolve(base_socket *,in_addr a) override;
      //i32 Resolve(base_socket *,in6_addr& a) override;
      /** get listen port of asynchronous dns server. */
      //::networking::port_t GetResolverPort() override;
      /** Resolver thread ready for queries. */
      //bool ResolverReady() override;
      /** Returns true if the base_socket is waiting for a resolve event. */
      //bool Resolving(base_socket *) override;

      /** Fetch unique trigger atom. */
      i32 TriggerID(base_socket *src) override;
      /** Subscribe base_socket to trigger atom. */
      bool Subscribe(i32 atom, base_socket *dst) override;
      /** Unsubscribe base_socket from trigger atom. */
      bool Unsubscribe(i32 atom, base_socket *dst) override;
      /** Execute OnTrigger for subscribed sockets.
      \lparam atom Trigger ID
      \lparam data Data passed from source to destination
      \lparam erase Empty trigger atom source and destination maps if 'true',
      Leave them in place if 'false' - if a trigger should be called many times */
      //void Trigger(i32 atom, base_socket::trigger_data & data, bool erase = true) override;

      /** Indicates that the handler runs under socket_thread. */
      //void SetSlave(bool x = true) override;
      /** Indicates that the handler runs under socket_thread. */
      //bool IsSlave() override;

      /** Sanity check of those accursed lists. */
      void CheckSanity();


      //void CheckList(socket_id_list&,const string &); ///< Used by CheckSanity
      /** erase base_socket from base_socket map, used by base_socket class. */
      // void erase(base_socket *) override;
   };


} // namespace sockets


