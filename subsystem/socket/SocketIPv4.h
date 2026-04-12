// Copyright (C) 2008,2009,2010,2011,2012 GlavSoft LLC.
// All rights reserved.
//
//-------------------------------------------------------------------------
// This file is part of the TightVNC software.  Please visit our Web site:
//
//                       http://www.tightvnc.com/
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, w_rite to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//-------------------------------------------------------------------------
//

//#ifndef SOCKET_IPV4_H
#pragma once
//#define SOCKET_IPV4_H

#include "sockdefs.h"

#include "SocketIPv4.h"
#include "SocketAddressIPv4.h"
#include "SocketException.h"

#include "subsystem/io/Channel.h"
#include "acme/exception/io.h"
///#include "remoting/remoting_common/win_system/WsaStartup.h"
//#include "subsystem/thread/critical_section.h"

namespace subsystem
{
   /**
    * IPv4 Socket class.
    *
    * @fixme refactor this class to avoid usage of SocketAddressIPv4 class.
    */
   class SocketIPv4Interface :
      virtual public ::subsystem::particle_interface<SocketIPv4Interface >
   {
   public:
      /**
       * Creates new socket.
       */
      //SocketIPv4();
      /**
       * Deletes and closes socket.
       */
      //virtual ~SocketIPv4Interface() = 0;

      /**
       * Connects to remote host.
       * @param host host to connect.
       * @param port port to connect.
       * @throws SocketException on fail.
       */
      virtual void connect(const ::scoped_string & scopedstrHost, unsigned short port) = 0;
      /**
       * Connects to remote host.
       * @param addr address to connect.
       * @throws SocketException on fail.
       */
      virtual void connect(const ::subsystem::SocketAddressIPv4Interface * paddress) = 0;
      /**
       * Closes socket.
       * @throws SocketException on fail.
       */
      virtual void close() = 0;
      /**
       * Shutdowns socket.
       * @param how how to shutdown socket (SD_RECEIVE|SD_SEND|SD_BOTH).
       * @throws SocketException on fail.
       */
      virtual void shutdown(int how) = 0;
      /**
       * Binds socket to specified address.
       * @param bindHost host to bind.
       * @param bindPort port to bind.
       * @throws SocketException on fail.
       */
      virtual void bind(const ::scoped_string & scopedstrBindHost, unsigned int bindPort) = 0;
      /**
       * Binds socket to socket address.
       * @throws SocketException on fail.
       */
      virtual void bind(const ::subsystem::SocketAddressIPv4Interface * paddress) = 0;
      /**
       * Checks if this socket is bound and used for server needs.
       * @return true if socket used as server and successfully bounded, false otherwise.
       */
      virtual bool isBound() = 0;
      /**
       * Socket listen method.
       * @param backlog max count of connections in pool.
       * @throws SocketException on fail.
       */
      virtual void listen(int backlog) = 0;

      /**
       * Accepts incoming connection.
       * @throws SocketException on fail.
       * @return newly allocated socket that contain incoming connections.
       */
      virtual ::pointer < SocketIPv4Interface > accept() = 0;

      /**
       * Sends data to socket.
       *
       * @param data buffer to send.
       * @param size bytes to send.
       * @param [optional] flags socket flags.
       * @return count to sent bytes.
       * @throw ::io_exception on error.
       */
      virtual int send(const char *data, int size, int flags = 0) = 0;
      /**
       * Receives data from socket.
       *
       * @param buffer buffer to receive data.
       * @param size count of bytes to read from socket.
       * @param flags recv flags.
       * @return count of read bytes.
       * @throws ::io_exception on fail.
       */
      virtual int recv(char *buffer, int size, int flags = 0) = 0;

      virtual int available() = 0;

      /**
       * Returns local address of socket (for listening socket).
       * @param addr output parameter that will contain socket address.
       * @return true on success, false on fail.
       */
      virtual ::pointer < ::subsystem::SocketAddressIPv4Interface > getLocalAddr() = 0;
      /**
       * Returns peer address.
       * @param addr output parameter that will contain socket address.
       * @return true on success, false on fail.
       */
      virtual ::pointer < ::subsystem::SocketAddressIPv4Interface > getPeerAddr(SocketAddressIPv4 *addr) = 0;

      /* Auxiliary */
      virtual void setSocketOptions(int level, int name, void *value, socklen_t len) = 0;
      virtual void getSocketOptions(int level, int name, void *value, socklen_t *len) = 0;

      /* Socket options */
      virtual void enableNaggleAlgorithm(bool enabled) = 0;
      virtual void setExclusiveAddrUse() = 0;

   // private:
   //    //WsaStartup m_wsaStartup;
   //
   // protected:
   //    // Returns a SOCKET object with performed accept operation.
   //    // Throws SocketException on an error.
   //    virtual SOCKET getAcceptedSocket(struct sockaddr_in *addr) = 0;
   //
   //    // Closes old socket and sets handler to new one
   //    virtual void set(SOCKET socket) = 0;
   //
   //    /**
   //     * Mutex for thread-safety.
   //     */
   //    critical_section m_mutex;
   //
   //    /**
   //     * WinSock socket.
   //     */
   //    SOCKET m_socket;
   //    bool m_isClosed;
   //
   //    SocketAddressIPv4 *m_localAddr;
   //    SocketAddressIPv4 *m_peerAddr;
   //
   //    /**
   //     * Flag determinating if socket is server or client socket.
   //     */
   //    bool m_isBound;
   };



      /**
    * IPv4 Socket class.
    *
    * @fixme refactor this class to avoid usage of SocketAddressIPv4 class.
    */
   class CLASS_DECL_SUBSYSTEM SocketIPv4 :
      virtual public ::subsystem::composite<SocketIPv4Interface >
   {
   public:
      /**
       * Creates new socket.
       */
      SocketIPv4();
      /**
       * Deletes and closes socket.
       */
      virtual ~SocketIPv4() override;

      /**
       * Connects to remote host.
       * @param host host to connect.
       * @param port port to connect.
       * @throws SocketException on fail.
       */
      void connect(const ::scoped_string & scopedstrHost, unsigned short port)  override;
      /**
       * Connects to remote host.
       * @param addr address to connect.
       * @throws SocketException on fail.
       */
      void connect(::subsystem::SocketAddressIPv4Interface * paddress)  override;
      /**
       * Closes socket.
       * @throws SocketException on fail.
       */
      void close()  override;
      /**
       * Shutdowns socket.
       * @param how how to shutdown socket (SD_RECEIVE|SD_SEND|SD_BOTH).
       * @throws SocketException on fail.
       */
      void shutdown(int how)  override;
      /**
       * Binds socket to specified address.
       * @param bindHost host to bind.
       * @param bindPort port to bind.
       * @throws SocketException on fail.
       */
      void bind(const ::scoped_string & scopedstrBindHost, unsigned int bindPort) override;
      /**
       * Binds socket to socket address.
       * @throws SocketException on fail.
       */
      void bind(::subsystem::SocketAddressIPv4Interface * paddress) override;
      /**
       * Checks if this socket is bound and used for server needs.
       * @return true if socket used as server and successfully bounded, false otherwise.
       */
      bool isBound() override;
      /**
       * Socket listen method.
       * @param backlog max count of connections in pool.
       * @throws SocketException on fail.
       */
      void listen(int backlog) override;

      /**
       * Accepts incoming connection.
       * @throws SocketException on fail.
       * @return newly allocated socket that contain incoming connections.
       */
      ::pointer < ::subsystem::SocketIPv4Interface > accept() override;

      /**
       * Sends data to socket.
       *
       * @param data buffer to send.
       * @param size bytes to send.
       * @param [optional] flags socket flags.
       * @return count to sent bytes.
       * @throw ::io_exception on error.
       */
      int send(const char *data, int size, int flags = 0) override;
      /**
       * Receives data from socket.
       *
       * @param buffer buffer to receive data.
       * @param size count of bytes to read from socket.
       * @param flags recv flags.
       * @return count of read bytes.
       * @throws ::io_exception on fail.
       */
      int recv(char *buffer, int size, int flags = 0) override;

      int available() override;

      /**
       * Returns local address of socket (for listening socket).
       * @param addr output parameter that will contain socket address.
       * @return true on success, false on fail.
       */
      ::pointer < ::subsystem::SocketIPv4Interface > getLocalAddr() override;
      /**
       * Returns peer address.
       * @param addr output parameter that will contain socket address.
       * @return true on success, false on fail.
       */
      ::pointer < ::subsystem::SocketIPv4Interface > getPeerAddr() override;

      /* Auxiliary */
      void setSocketOptions(int level, int name, void *value, socklen_t len) override;
      void getSocketOptions(int level, int name, void *value, socklen_t *len) override;

      /* Socket options */
      void enableNaggleAlgorithm(bool enabled) override;
      void setExclusiveAddrUse() override;

   // private:
   //    //WsaStartup m_wsaStartup;
   //
   // protected:
   //    // Returns a SOCKET object with performed accept operation.
   //    // Throws SocketException on an error.
   //    SOCKET getAcceptedSocket(struct sockaddr_in *addr) override;
   //
   //    // Closes old socket and sets handler to new one
   //    void set(SOCKET socket) override;
   //
   //    // /**
   //    //  * Mutex for thread-safety.
   //    //  */
   //    // critical_section m_mutex;
   //    //
   //    // /**
   //    //  * WinSock socket.
   //    //  */
   //    // SOCKET m_socket;
   //    // bool m_isClosed;
   //    //
   //    // SocketAddressIPv4 *m_localAddr;
   //    // SocketAddressIPv4 *m_peerAddr;
   //    //
   //    // /**
   //    //  * Flag determinating if socket is server or client socket.
   //    //  */
   //    // bool m_isBound;
   };

} // namespace subsystem