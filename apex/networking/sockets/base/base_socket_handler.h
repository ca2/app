/** \file base_socket_handler.h
**   \date  2004-02-13
**   \author grymse@alhem.net
**/
/*
Copyright (C) 2004-2007  Anders Hedstrom

This library is made available under the terms of the GNU GPL.

If you would like to use this library in a closed-source application,
a separate license agreement is available. For information about
the closed-source license agreement for the C++ sockets library,
please visit http://www.alhem.net/Sockets/license.html and/or
email license@alhem.net.

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/
#pragma once


#include "apex/networking/sockets/basic/socket.h"
#include "apex/platform/log.h"


namespace sockets
{




   /** socket container class, happening generator.
   \ingroup basic */
   class CLASS_DECL_APEX base_socket_handler:
      virtual public ::object
   {
   public:


      //void * m_p2;


      friend class base_socket;
      friend class socket;

      ///** Connection pool class for internal use by the base_socket_handler.
      //\ingroup internal */
      //class CLASS_DECL_APEX pool_socket : public socket
      //{
      //public:

      //   
      //   pool_socket(base_socket * src);
      //   ~pool_socket() override;

      //   
      //   void OnRead() override;
      //   //void OnOptions(int, int, int, socket_id) override;


      //};


      int                           m_iSelectErrno;
      ::pointer<::apex::log>       m_plogger; ///< Registered log class, or nullptr


      //base_socket_handler(::apex::log * plogger = nullptr);
      base_socket_handler();
      ~base_socket_handler() override;

      ///** get ::pointer < ::mutex > object for threadsafe operations. */
      //virtual clasync & GetMutex() const = 0;

      virtual void set_logger(::apex::log * plog);

      /** Log error to log class for print out / storage. */
      //virtual void log(base_socket *point,const string & user_text,int err,const string & sys_err, enum_trace_level elevel = e_trace_level_warning);

      // -------------------------------------------------------------------------
      // socket stuff
      // -------------------------------------------------------------------------
      /** add socket instance to socket ::map. Removal is always automatic. */
      virtual void add(base_socket * psocket);
      //virtual void move2(socket_pointer && psocket) = 0;
      //virtual void transfer(socket_map::association * passociation, socket_map * psocketmap = nullptr) = 0;
      //virtual void restart_socket(socket_id socket) = 0;
      //virtual socket_map::association* new_association(socket_pointer && psocket) = 0;
   //private:
      /** erase socket from socket ::map, used by socket class. */
      virtual void erase(const socket_pointer & psocket) = 0;
   public:

      virtual bool contains(base_socket *) = 0;
      virtual bool contains_socket_id(socket_id socket) = 0;

      ///** get status of read/write/exception file descriptor set for a socket. */
      //virtual void get(socket_id s,bool& r,bool& w,bool& e) = 0;
      ///** Set read/write/exception file descriptor sets (fd_set). */
      //virtual void set(socket_id s,bool bRead,bool bWrite,bool bException = true) = 0;
      /** Wait for happenings, generate callbacks. */
      virtual int select(int sec, int usec) = 0;
      /** This method will not return until an happening has been detected. */
      virtual int select() = 0;
      /** Wait for happenings, generate callbacks. */
      virtual int select(const class time & timeWait) = 0;

      /** Check that a socket really is handled by this socket handler. */
      virtual bool Valid(base_socket *) = 0;
      /** Return number of sockets handled by this handler.  */
      virtual ::collection::count get_count() = 0;

      virtual bool socket_get_run() const;

      /** Override and return false to deny all incoming connections.
      \lparam int_point listen_socket class pointer (use GetPort to identify which one) */
      virtual bool OkToAccept(base_socket *int_point) = 0;

      ///** Called by socket when a socket changes state. */
      //virtual socket_id_list& socket_id_list_get(enum_list elist) = 0;
      //virtual void socket_id_list_modify(socket_id s, enum_list elist, bool bAdd) = 0;
      //virtual void socket_id_list_add(socket_id s, enum_list elist) = 0;
      //virtual void socket_id_list_erase(socket_id s, enum_list elist) = 0;

      //virtual void erase_socket_by_id(socket_id s) = 0;
      // -------------------------------------------------------------------------
      // Connection pool
      // -------------------------------------------------------------------------
      /** find available open connection (used by connection pool). */
      //virtual ::pointer<pool_socket>FindConnection(int type,const string & protocol, ::networking::address * address) = 0;

      /** enable connection pool (by default disabled). */
      virtual void EnablePool(bool = true) = 0;
      /** Check pool status.
      \return true if connection pool is enabled */
      virtual bool PoolEnabled() = 0;

      // -------------------------------------------------------------------------
      // Socks4
      // -------------------------------------------------------------------------
//#if defined(BSD_STYLE_SOCKETS)
//      /** Set socks4 server ip that all ___new tcp sockets should use. */
//      virtual void SetSocks4Host(in_addr) = 0;
//      /** Set socks4 server hostname that all ___new tcp sockets should use. */
//      virtual void SetSocks4Host(const ::scoped_string & scopedstrHost) = 0;
//#endif
      /** Set socks4 server port number that all ___new tcp sockets should use. */
      //virtual void SetSocks4Port(::networking::port_t) = 0;
      ///** Set optional socks4 userid. */
      //virtual void SetSocks4Userid(const ::scoped_string & scopedstrUserId) = 0;
      ///** If connection to socks4 server fails, immediately try direct connection to final host. */
      //virtual void SetSocks4TryDirect(bool = true) = 0;
      ///** get socks4 server ip.
      //\return socks4 server ip */
      //virtual in_addr GetSocks4Host() = 0;
      ///** get socks4 port number.
      //\return socks4 port number */
      //virtual ::networking::port_t GetSocks4Port() = 0;
      ///** get socks4 userid (optional).
      //\return socks4 userid */
      //virtual const string & GetSocks4Userid() = 0;
      /** Check status of socks4 try direct flag.
      \return true if direct connection should be tried if connection to socks4 server fails */
      //virtual bool Socks4TryDirect() = 0;
      // -------------------------------------------------------------------------
      // DNS resolve server
      // -------------------------------------------------------------------------
      /** enable asynchronous DNS.
      \lparam port Listen port of asynchronous dns server */
      //virtual void EnableResolver(::networking::port_t = 16667) = 0;
      /** Check resolver status.
      \return true if resolver is enabled */
      //virtual bool ResolverEnabled() = 0;
      /** Queue a dns request.
      \lparam host Hostname to be resolved
      \lparam port Port number will be echoed in socket::OnResolved callback */
      //virtual int Resolve(base_socket *,const ::scoped_string & scopedstrHost,::networking::port_t port) = 0;
      //virtual int Resolve6(base_socket *,const ::scoped_string & scopedstrHost,::networking::port_t port) = 0;
      /** Do a reverse dns lookup. */
      //virtual int Resolve(base_socket *,in_addr a) = 0;
      //virtual int Resolve(base_socket *,in6_addr& a) = 0;
      /** get listen port of asynchronous dns server. */
      //virtual ::networking::port_t GetResolverPort() = 0;
      /** Resolver thread ready for queries. */
      //virtual bool ResolverReady() = 0;
      /** Returns true if socket waiting for a resolve happening. */
      //virtual bool Resolving(base_socket *) = 0;
      /** Fetch unique trigger atom. */
      virtual int TriggerID(base_socket *src) = 0;
      /** Subscribe socket to trigger atom. */
      virtual bool Subscribe(int atom, base_socket *dst) = 0;
      /** Unsubscribe socket from trigger atom. */
      virtual bool Unsubscribe(int atom, base_socket *dst) = 0;
      /** Execute OnTrigger for subscribed sockets.
      \lparam atom Trigger ID
      \lparam data Data passed from source to destination
      \lparam erase Empty trigger atom source and destination maps if 'true',
      Leave them in place if 'false' - if a trigger should be called many times */
      //virtual void Trigger(int atom, base_socket::trigger_data & data, bool erase = true) = 0;
      /** Indicates that the handler runs under socket_thread. */
      virtual void SetSlave(bool x = true) = 0;
      /** Indicates that the handler runs under socket_thread. */
      virtual bool IsSlave() = 0;

      //virtual void __tracef(e_trace_category ecategory, enum_trace_level elevel, const ::scoped_string & scopedstrFunction, const ::scoped_string & scopedstrFile, int iLine, base_socket * psocket, const ::scoped_string & scopedstrContext, int err, const ::scoped_string & scopedstrMessage);


   };


} // namespace sockets



