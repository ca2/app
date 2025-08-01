#pragma once


#include "networking_bsd/sockets/base/base_socket_handler.h"
#include "apex/networking/sockets/basic/socket_handler.h"
#include "acme/prototype/collection/list.h"
#include "acme/prototype/collection/comparable_eq_list.h"
#include "acme/prototype/collection/comparable_list.h"

//#if defined(FREEBSD) || defined(OPENBSD)
//#include <sys/select.h>
//#endif


namespace sockets_bsd
{


   class base_socket;
   class resolv_server;

   typedef comparable_list < socket_pointer > socket_pointer_list;


   class CLASS_DECL_NETWORKING_BSD socket_handler :
      virtual public base_socket_handler,
      virtual public ::sockets::socket_handler
   {
   public:

      int m_iMaxKeepAliveCount = 0;
      ::pointer<::apex::log>    m_splogger; ///< Registered log class, or nullptr

      socket_map                 m_socketmap; ///< Active sockets map
      socket_map                 m_socketmapAdd; ///< Sockets to be added to sockets map
      socket_pointer_list        m_delete; ///< Sockets to be deleted (failed when add)
      bool                       m_b_use_mutex; ///< ::pointer < ::mutex > correctly initialized
      //SOCKET                     m_maxsock; ///< Highest file descriptor + 1 in active sockets list
      //::collection::count                    m_countR;
      //::collection::count                    m_countW;
      //::collection::count                    m_countE;
      //fd_set                     m_rfds; ///< file descriptor set monitored for read happenings
      //fd_set                     m_wfds; ///< file descriptor set monitored for write happenings
      //fd_set                     m_efds; ///< file descriptor set monitored for exceptions
      //fd_set                     m_rfdsSelect; ///< file descriptor set monitored for read happenings
      //fd_set                     m_wfdsSelect; ///< file descriptor set monitored for write happenings
      //fd_set                     m_efdsSelect; ///< file descriptor set monitored for exceptions
      //fd_set                     m_rfdsSelected; ///< file descriptor set monitored for read happenings
      //fd_set                     m_wfdsSelected; ///< file descriptor set monitored for write happenings
      //fd_set                     m_efdsSelected; ///< file descriptor set monitored for exceptions
      int                        m_iPreviousError; ///< debug select() error
      class ::time                       m_timeLastError;
      ::earth::time                 m_tlast; ///< timeout control

      // state lists
      socket_id_list                m_socketlist; ///< Active file descriptor list
      socket_id_list                m_socketlistErase; ///< File descriptors that are to be erased from m_sockets
      socket_id_list                m_socketlistCallOnConnect; ///< checklist CallOnConnect
      socket_id_list                m_socketlistDetach; ///< checklist detach
      socket_id_list                m_socketlistTimeout; ///< checklist timeout
      socket_id_list                m_socketlistRetryClientConnect; ///< checklist retry client connect
      socket_id_list                m_socketlistClose; ///< checklist close and delete
      string                    m_socks4_host; ///< Socks4 server host ip
      ::networking::port_t                     m_socks4_port; ///< Socks4 server port number
      string                     m_socks4_userid; ///< Socks4 userid
      bool                       m_bTryDirect; ///< Try direct connection if socks4 server fails
      //int                        m_resolv_id; ///< Resolver atom counter
      //::task_pointer        m_resolver; ///< Resolver thread pointer
      //port_t                     m_resolver_port; ///< Resolver listen port
      //socket_flag_map            m_resolve_q; ///< resolve queue
      bool                       m_bEnablePool; ///< Connection pool enabled if true
      int                        m_next_trigger_id; ///< Unique trigger atom counter
      socket_map                 m_trigger_src; ///< mapping trigger atom to source base_socket
      socket_socket_flag_map     m_trigger_dst; ///< mapping trigger atom to destination sockets
      bool                       m_bSlave; ///< Indicates that this is a base_socket_handler run in socket_thread


      //socket_handler(::apex::log * plogger = nullptr);
      socket_handler();
      ~socket_handler() override;


      long long increment_reference_count() override;
      long long decrement_reference_count() override;

      void initialize(::particle * pparticle) override;

      void cleanup_handler();

      bool call_on_connect();

//      synchronization & GetMutex() const override;


      //resolv_server * resolver();

      /** add base_socket instance to base_socket map. Removal is always automatic. */
      void restart_socket(SOCKET socket) override;

      //void add(const ::sockets::socket_pointer & psocket) override;
      void add(::sockets::base_socket * psocket) override;
      //void move2(::sockets::socket_pointer && psocket) override;
      //void transfer(socket_map::node * pnode, socket_map* psocketmap = nullptr) override;
      //void _move(socket_map::association* passociation, socket_map* psocketmap) override;
      void erase(const ::sockets::socket_pointer & psocket) override;


      //void erase(const ::sockets::socket_pointer & psocket) override;
      bool contains_socket_id(socket_id socketid) override;
      bool contains(::sockets::base_socket *) override;

      /** get status of read/write/exception file descriptor set for a base_socket. */
      //void get(SOCKET s,bool& r,bool& w,bool& e) override;
      //virtual void _get(SOCKET s, int& r, int& w, int& e);
      //virtual void get(int& r, int& w, int& e);

      /** set read/write/exception file descriptor sets (fd_set). */
      //void set(SOCKET s,bool bRead,bool bWrite,bool bException = true) override;

      /** Wait for happenings, generate callbacks. */
      int select(int sec, int usec) override;

      /** This method will not return until an happening has been detected. */
      int select() override;

      int select(const class time & timeWait) override;
      /** Wait for happenings, generate callbacks. */
      int _select(struct timeval *tsel) override;

      /** Check that a base_socket really is handled by this base_socket handler. */
      bool Valid(::sockets::base_socket *) override;

      /** Return number of sockets handled by this handler.  */
      ::collection::count get_count() override;

      /** Override and return false to deny all incoming connections.
      \lparam int_point listen_socket class pointer (use GetPort to identify which one) */
      bool OkToAccept(::sockets::base_socket *int_point) override;

      /** Called by base_socket when a base_socket changes state. */
      socket_id_list& socket_id_list_get(enum_list elist) override;
      void socket_id_list_modify(SOCKET s, enum_list elist, bool bAdd) override;
      void socket_id_list_add(SOCKET s, enum_list elist) override;
      void socket_id_list_erase(SOCKET s, enum_list elist) override;

      void erase_socket(SOCKET s) override;

      // Connection pool
      /** find available open connection (used by connection pool). */
      ::pointer<pool_socket>FindConnection(int type,const string & protocol, ::networking::address * address) override;
      /** enable connection pool (by default disabled). */
      void EnablePool(bool x = true) override;
      /** Check pool status.
      \return true if connection pool is enabled */
      bool PoolEnabled() override;

      // Socks4
      /** set socks4 server ip that all ___new tcp sockets should use. */
      //void SetSocks4Host(in_addr addr) override;
      /** set socks4 server hostname that all ___new tcp sockets should use. */
      void SetSocks4Host(const ::scoped_string & scopedstrHost) override;
      /** set socks4 server port number that all ___new tcp sockets should use. */
      void SetSocks4Port(::networking::port_t) override;
      /** set optional socks4 userid. */
      void SetSocks4Userid(const ::scoped_string & scopedstrUserId) override;
      /** If connection to socks4 server fails, immediately try direct connection to final host. */
      void SetSocks4TryDirect(bool x = true) override;
      /** get socks4 server ip.
      \return socks4 server ip */
      string GetSocks4Host() override;
      /** get socks4 port number.
      \return socks4 port number */
      ::networking::port_t GetSocks4Port() override;
      /** get socks4 userid (optional).
      \return socks4 userid */
      const string & GetSocks4Userid() override;
      /** Check status of socks4 try direct flag.
      \return true if direct connection should be tried if connection to socks4 server fails */
      bool Socks4TryDirect() override;

      // DNS resolve server
      /** enable asynchronous DNS.
      \lparam port Listen port of asynchronous dns server */
      //void EnableResolver(port_t port = 16667) override;
      /** Check resolver status.
      \return true if resolver is enabled */
      //bool ResolverEnabled() override;
      /** Queue a dns request.
      \lparam host Hostname to be resolved
      \lparam port Port number will be echoed in base_socket::OnResolved callback */
      //int Resolve(base_socket *,const ::scoped_string & scopedstrHost,port_t port) override;
      //int Resolve6(base_socket *,const ::scoped_string & scopedstrHost,port_t port) override;
      /** Do a reverse dns lookup. */
      //int Resolve(base_socket *,in_addr a) override;
      //int Resolve(base_socket *,in6_addr& a) override;
      /** get listen port of asynchronous dns server. */
      //port_t GetResolverPort() override;
      /** Resolver thread ready for queries. */
      //bool ResolverReady() override;
      /** Returns true if the base_socket is waiting for a resolve happening. */
      //bool Resolving(base_socket *) override;

      /** Fetch unique trigger atom. */
      int TriggerID(::sockets::base_socket *src) override;
      /** Subscribe base_socket to trigger atom. */
      bool Subscribe(int atom, ::sockets::base_socket *dst) override;
      /** Unsubscribe base_socket from trigger atom. */
      bool Unsubscribe(int atom, ::sockets::base_socket *dst) override;
      /** Execute OnTrigger for subscribed sockets.
      \lparam atom Trigger ID
      \lparam data Data passed from source to destination
      \lparam erase Empty trigger atom source and destination maps if 'true',
      Leave them in place if 'false' - if a trigger should be called many times */
      void Trigger(int atom, base_socket::trigger_data & data, bool erase = true) override;

      /** Indicates that the handler runs under socket_thread. */
      void SetSlave(bool x = true) override;
      /** Indicates that the handler runs under socket_thread. */
      bool IsSlave() override;

      /** Sanity check of those accursed lists. */
      void CheckSanity();


      void CheckList(socket_id_list&,const string &); ///< Used by CheckSanity
      /** erase base_socket from base_socket map, used by base_socket class. */
      //void erase(::sockets::base_socket *) override;


   };


} // namespace sockets_bsd


