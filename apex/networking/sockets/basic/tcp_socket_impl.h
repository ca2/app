/** \file tcp_socket.h
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


#include "tcp_socket.h"


#define TCP_BUFSIZE_READ (16400)
#define TCP_OUTPUT_CAPACITY 1024000

//namespace sockets
//{
//
//
//
//   /** socket implementation for TCP.
//   \ingroup basic */
//   class CLASS_DECL_APEX tcp_socket_impl :
//      virtual public tcp_socket
//   {
//      /** \defgroup internal Internal utility */
//   public:
//
//      /*   array < ssl_ticket_key >   m_ticketkeya;
//   */
//
//      static bool s_bReuseSession; // Default psystem Wide Setting
//
//      /** Output buffer struct.
//      \ingroup internal */
//      string m_strTlsHostName;
//
//      struct output :
//         virtual public object
//      {
//
//
//         int _b;
//         int _t;
//         int _q;
//         char * _buf;
//         memory m_memory;
//         int m_iTcpOuputCapacity;
//
//
//         output(int iTcpOutputCapacity) :
//            m_iTcpOuputCapacity(iTcpOutputCapacity),
//            _b(0), _t(0), _q(0)
//         {
//            m_memory.set_size(m_iTcpOuputCapacity);
//            _buf = (char *)m_memory.get_data();
//         }
//
//         output(int iTcpOutputCapacity, const_char_pointer buf, int len) :
//            m_iTcpOuputCapacity(iTcpOutputCapacity),
//            _b(0), _t(len), _q(len)
//         {
//            m_memory.set_size(m_iTcpOuputCapacity);
//            _buf = (char *)m_memory.get_data();
//            ::memory_copy(_buf, buf, len);
//         }
//
//         virtual ~output()
//         {
//         }
//
//         int Space()
//         {
//            return m_iTcpOuputCapacity - _t;
//         }
//         void add(const_char_pointer buf, int len)
//         {
//            ::memory_copy(_buf + _t, buf, len);
//            _t += len;
//            _q += len;
//         }
//         int erase(int len)
//         {
//            _b += len;
//            _q -= len;
//            return _q;
//         }
//         const_char_pointer Buf()
//         {
//            return _buf + _b;
//         }
//         int Len()
//         {
//            return _q;
//         }
//      };
//      typedef list<::pointer<output >> output_list;
//
//      ::file::circular_file ibuf; ///< Circular input buffer
//      string m_strUrl;
//      ::pointer< ::mutex > m_pmutexSslCtx;
//      //
//      //bool m_b_input_buffer_disabled;
//      //unsigned long long m_bytes_sent;
//      //unsigned long long m_bytes_received;
//      //memory         m_memRead;
//      //output_list m_obuf; ///< output buffer
//      //::pointer<output>m_obuf_top; ///< output buffer on top
//      //memsize m_transfer_limit;
//      //memsize m_output_length;
//
//      //bool     m_bReuseSession;
//      //int m_socks4_state; ///< socks4 support
//      //char m_socks4_vn; ///< socks4 support, temporary ::payload
//      //char m_socks4_cd; ///< socks4 support, temporary ::payload
//      //unsigned short m_socks4_dstport; ///< socks4 support
//      //unsigned int m_socks4_dstip; ///< socks4 support
//
//      //string m_strConnectHost;
//      //::networking::port_t m_iConnectPort;
//
//      //int m_resolver_id; ///< Resolver atom (if any) for current open call
//
//      //bool m_bReconnect; ///< Reconnect on lost connection flag
//      //bool m_bTryingReconnect; ///< Trying to reconnect
//      //string m_strHost;
//      //bool m_bImpl;
//
//      //bool m_bCertCommonNameCheckEnabled;
//
//      //bool                       m_bClientSessionSet;
//      //string                     m_strInitSSLClientContext;
//
//      /** Constructor with standard values on input/output buffers. */
//      tcp_socket_impl();
//      /** Constructor with custom values for i/o buffer.
//      \lparam h base_socket_handler object
//      \lparam isize Input buffer int_size
//      \lparam osize Output buffer int_size */
//      //tcp_socket(memsize isize, memsize osize);
//      ~tcp_socket_impl() override;
//
//
//      //using ::sockets::stream_socket::open;
//      bool open(::networking::address * address, bool skip_socks = false);
//      bool open(::networking::address * address, ::networking::address * addressBind, bool skip_socks = false);
//      /** open connection.
//      \lparam host Hostname
//      \lparam port Port number */
//      bool open(const ::scoped_string & scopedstrHost, ::networking::port_t port);
//
//      /** Connect timeout callback. */
//      void on_connection_timeout() override;
//#ifdef _WIN32
//      /** Connection failed reported as exception on win32 */
//      void OnException();
//#endif
//
//      /** close file descriptor - internal use only.
//      \sa SetCloseAndDelete */
//      void close() override;
//
//      /** Send buffer of bytes.
//      \lparam buf buffer pointer
//      \lparam len Length of data
//      \lparam f Dummy flags -- not used */
//      //using ::file::file::write;
//      //using ::streaobject::write;
//      virtual void write(const void * buf, memsize c) override;
//
//      /** This callback is executed after a successful read from the socket.
//      \lparam buf Pointer to the data
//      \lparam len Length of the data */
//      virtual void OnRawData(char * buf, memsize len) override;
//
//      /** Called when output buffer has been sent.
//      Note: Will only be called IF the output buffer has been used.
//      Send's that was successful without needing the output buffer
//      will not generate a call to this method. */
//      virtual void OnWriteComplete();
//      /** Number of bytes in input buffer. */
//      memsize GetInputLength();
//      /** Number of bytes in output buffer. */
//      memsize GetOutputLength();
//
//      /** Callback fires when a socket in line protocol has read one full line.
//      \lparam line Line read */
//      void OnLine(const ::scoped_string & scopedstrLine) override;
//      /** get counter of number of bytes received. */
//      unsigned long long GetBytesReceived(bool clear = false) override;
//      /** get counter of number of bytes sent. */
//      unsigned long long GetBytesSent(bool clear = false) override;
//
//      //#if defined(BSD_STYLE_SOCKETS)
//      //      /** Socks4 specific callback. */
//      //      void OnSocks4Connect() override;
//      //      /** Socks4 specific callback. */
//      //      void OnSocks4ConnectFailed() override;
//      //      /** Socks4 specific callback.
//      //      \return 'need_more' */
//      //      bool OnSocks4Read() override;
//      //#endif
//
//            /** Callback executed when resolver thread has finished a resolve request. */
//            //void OnResolved(int atom, ::networking::address * addr) override;
//            /** Callback for 'New' ssl support - replaces SSLSocket. Internal use. */
//      void OnSSLConnect() override;
//      /** Callback for 'New' ssl support - replaces SSLSocket. Internal use. */
//      void OnSSLAccept() override;
//      /** This method must be implemented to initialize
//      the ssl action_context for an outgoing connection. */
//      virtual void InitSSLClient();
//      /** This method must be implemented to initialize
//      the ssl action_context for an incoming connection. */
//      virtual void InitSSLServer();
//
//      /** Flag that says a broken connection will try to reconnect. */
//      void SetReconnect(bool = true);
//      /** Check reconnect on lost connection flag status. */
//      bool Reconnect();
//      /** Flag to determine if a reconnect is in progress. */
//      void SetIsReconnect(bool x = true);
//      /** socket is reconnecting. */
//      bool IsReconnect();
//
//      void DisableInputBuffer(bool = true);
//
//      //void OnOptions(int,int,int,socket_id) override;
//
//      void SetLineProtocol(bool = true) override;
//
//      // TCP options
//      bool SetTcpNodelay(bool = true);
//
//      virtual string get_connect_host();
//      virtual ::networking::port_t get_connect_port();
//
//      virtual int Protocol() override;
//
//      /** Trigger limit for callback OnTransferLimit. */
//      void SetTransferLimit(memsize sz);
//      /** This callback fires when the output buffer drops below the value
//      set by SetTransferLimit. Default: 0 (disabled). */
//      virtual void OnTransferLimit();
//
//
//      void OnRead() override;
//      //using ::file::file::read;
//      //using ::object::read;
//      virtual int read(void * buf, int n);
//      virtual int recv(void * buf, int n);
//      void on_read(const void * buf, memsize n) override;
//      void OnWrite() override;
//
//
//      virtual long cert_common_name_check(const ::string & common_name);
//      virtual void enable_cert_common_name_check(bool bEnable = true);
//
//      ///** SSL; Initialize ssl action_context for a client socket.
//      //\lparam meth_in SSL method */
//      //void InitializeContext(const string & action_context, const SSL_METHOD *meth_in = nullptr);
//      ///** SSL; Initialize ssl action_context for a server socket.
//      //\lparam keyfile Combined private key/certificate file
//      //\lparam password Password for private key
//      //\lparam meth_in SSL method */
//      //void InitializeContext(const string & action_context, const string & keyfile, const string & password, const SSL_METHOD *meth_in = nullptr);
//      ///** SSL; Initialize ssl action_context for a server socket.
//      //\lparam certfile Separate certificate file
//      //\lparam keyfile Combined private key/certificate file
//      //\lparam password Password for private key
//      //\lparam meth_in SSL method */
//      //void InitializeContext(const string & action_context, const string & certfile, const string & keyfile, const string & password, const SSL_METHOD *meth_in = nullptr);
//      ///** SSL; Password callback method. */
//      ///** SSL; get pointer to ssl action_context structure. */
//      //virtual SSL_CTX *GetSslContext() override;
//      ///** SSL; get pointer to ssl structure. */
//      //virtual SSL *GetSsl() override;
//      /** ssl; still negotiating connection. */
//      bool SSLNegotiate() override;
//      /** SSL; get ssl password. */
//      string GetPassword();
//
//
//      virtual string get_url();
//
//      virtual string get_short_description() override;
//
//
//      /** the actual send() */
//      int try_write(const void * buf, int len);
//      /** add data to output buffer top */
//      void buffer(const void * buf, int len);
//
//      void InitializeContextTLSClientMethod();
//
//   };
//
//   extern "C"
//      int tcp_socket_SSL_password_cb(char * buf, int num, int rwflag, void * userdata);
//
//
//} // namespace sockets
//
//
//
