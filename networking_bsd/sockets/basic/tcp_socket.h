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


#include "networking_bsd/sockets/basic/stream_socket.h"
#include "apex/networking/sockets/basic/tcp_socket.h"
#include "networking_bsd/sockets/ssl/ticket_key.h"
#include "acme/primitive/collection/list.h"


#define TCP_BUFSIZE_READ (16400)
#define TCP_OUTPUT_CAPACITY 1024000

namespace sockets_bsd
{


   //struct OUTPUT {
   //   OUTPUT() : _b(0), _t(0), _q(0) {}
   //   OUTPUT(const char *buf, memsize len) : _b(0), _t(len), _q(len) {
   //      ::memory_copy(_buf, buf, len);
   //   }
   //   memsize Space() {
   //      return TCP_OUTPUT_CAPACITY - _t;
   //   }
   //   void add(const char *buf, memsize len) {
   //      ::memory_copy(_buf + _t, buf, len);
   //      _t += len;
   //      _q += len;
   //   }
   //   memsize erase(memsize len) {
   //      _b += len;
   //      _q -= len;
   //      return _q;
   //   }
   //   const char *Buf() {
   //      return _buf + _b;
   //   }
   //   memsize Len() {
   //      return _q;
   //   }
   //   memsize _b;
   //   memsize _t;
   //   memsize _q;
   //   char _buf[TCP_OUTPUT_CAPACITY];
   //};


   //typedef ::list < OUTPUT *> output_list;


   /** socket implementation for TCP.
   \ingroup basic */
   class CLASS_DECL_NETWORKING_BSD tcp_socket :
      virtual public stream_socket,
      virtual public ::sockets::tcp_socket
   {
      /** \defgroup internal Internal utility */
   public:

      array < ssl_ticket_key >   m_ticketkeya;


      static bool s_bReuseSession; // Default psystem Wide Setting

      /** Output buffer struct.
      \ingroup internal */
      string m_strTlsHostName;
      
      typedef list<::pointer<output >> output_list;

      ::file::circular_file ibuf; ///< Circular input buffer
      string m_strUrl;

      ::pointer< ::mutex >        m_pmutexSslCtx;
      //
      bool m_b_input_buffer_disabled;
      u64 m_bytes_sent;
      u64 m_bytes_received;
      memory         m_memRead;
      output_list m_obuf; ///< output buffer
      ::pointer<output>m_obuf_top; ///< output buffer on top
      memsize m_transfer_limit;
      memsize m_output_length;

      bool     m_bReuseSession;
      i32 m_socks4_state; ///< socks4 support
      char m_socks4_vn; ///< socks4 support, temporary ::payload
      char m_socks4_cd; ///< socks4 support, temporary ::payload
      u16 m_socks4_dstport; ///< socks4 support
      u32 m_socks4_dstip; ///< socks4 support

      string m_strConnectHost;
      ::networking::port_t m_iConnectPort;

      i32 m_resolver_id; ///< Resolver atom (if any) for current open call

      bool m_bReconnect; ///< Reconnect on lost connection flag
      bool m_bTryingReconnect; ///< Trying to reconnect
      string m_strHost;

      bool m_bCertCommonNameCheckEnabled;

      bool                       m_bClientSessionSet;
      string                     m_strInitSSLClientContext;

      /** Constructor with standard values on input/output buffers. */
      tcp_socket();
      /** Constructor with custom values for i/o buffer.
      \lparam h base_socket_handler object
      \lparam isize Input buffer size_i32
      \lparam osize Output buffer size_i32 */
      tcp_socket(memsize isize,memsize osize);
      virtual ~tcp_socket();


      void initialize(::particle * pparticle) override;


      //using ::sockets::stream_socket::open;
      bool open(::networking::address * address, bool skip_socks = false) override;
      bool open(::networking::address * address, ::networking::address * addressBind,bool skip_socks = false) override;
      /** open connection.
      \lparam host Hostname
      \lparam port Port number */
      bool open(const string &host,::networking::port_t port) override;


      void set_host(const ::string & strHost) override;
      ::string get_host() const override;


      void set_tls_hostname(const ::string & strTlsHostname) override;


      void set_connect_host(const ::string & strConnectHost) override;
      ::string get_connect_host() const override;
      void set_connect_port(const ::networking::port_t portConnect) override;
      ::networking::port_t get_connect_port() const override;


      void set_url(const ::string & strUrl) override;
      string get_url() const override;


      /** Connect timeout callback. */
      void on_connection_timeout() override;
#ifdef _WIN32
      /** Connection failed reported as exception on win32 */
      void OnException();
#endif

      /** close file descriptor - internal use only.
      \sa SetCloseAndDelete */
      void close() override;

      /** Send buffer of bytes.
      \lparam buf buffer pointer
      \lparam len Length of data
      \lparam f Dummy flags -- not used */
      //using ::file::file::write;
      //using ::streaobject::write;
      using ::sockets::tcp_socket::write;
      void write(const void * p, ::memsize s) override;

      /** This callback is executed after a successful read from the socket.
      \lparam buf Pointer to the data
      \lparam len Length of the data */
      void OnRawData(char *buf, memsize len) override;

      /** Called when output buffer has been sent.
      Note: Will only be called IF the output buffer has been used.
      Send's that was successful without needing the output buffer
      will not generate a call to this method. */
      virtual void OnWriteComplete() override;
      /** Number of bytes in input buffer. */
      memsize GetInputLength() override;
      /** Number of bytes in output buffer. */
      memsize GetOutputLength() override;

      /** Callback fires when a socket in line protocol has read one full line.
      \lparam line Line read */
      void OnLine(const string & line) override;
      /** get counter of number of bytes received. */
      u64 GetBytesReceived(bool clear = false) override;
      /** get counter of number of bytes sent. */
      u64 GetBytesSent(bool clear = false) override;


      output * top_output_buffer() override;

      
#if defined(BSD_STYLE_SOCKETS)
      /** Socks4 specific callback. */
      void OnSocks4Connect() override;
      /** Socks4 specific callback. */
      void OnSocks4ConnectFailed() override;
      /** Socks4 specific callback.
      \return 'need_more' */
      bool OnSocks4Read() override;
#endif

      /** Callback executed when resolver thread has finished a resolve request. */
      //void OnResolved(i32 atom, ::networking::address * addr) override;
      /** Callback for 'New' ssl support - replaces SSLSocket. Internal use. */
      void OnSSLConnect() override;
      /** Callback for 'New' ssl support - replaces SSLSocket. Internal use. */
      void OnSSLAccept() override;
      /** This method must be implemented to initialize
      the ssl action_context for an outgoing connection. */
      void InitSSLClient()override;

      void set_init_ssl_client_context(const ::string & strInitSSLClientContext) override;

      /** This method must be implemented to initialize
      the ssl action_context for an incoming connection. */
      virtual void InitSSLServer()override;

      void _001InitSSLServer() override;

      /** Flag that says a broken connection will try to reconnect. */
      void SetReconnect(bool = true)override;
      /** Check reconnect on lost connection flag status. */
      bool Reconnect()override;
      /** Flag to determine if a reconnect is in progress. */
      void SetIsReconnect(bool x = true)override;
      /** socket is reconnecting. */
      bool IsReconnect() override;

      void DisableInputBuffer(bool = true) override;

      void OnOptions(int, int, int, SOCKET s) override;

      void SetLineProtocol(bool = true) override;

      // TCP options
      bool SetTcpNodelay(bool = true) override;

      virtual string get_connect_host() override;
      virtual ::networking::port_t get_connect_port() override;

      virtual i32 Protocol() override;

      /** Trigger limit for callback OnTransferLimit. */
      void SetTransferLimit(memsize sz) override;
      /** This callback fires when the output buffer drops below the value
      set by SetTransferLimit. Default: 0 (disabled). */
      void OnTransferLimit() override;


      void OnRead() override;
      //using ::file::file::read;
      //using ::object::read;
      int read(void * buf, int n) override;
      int recv(void * buf, int n) override;
      void on_read(const void * buf, memsize n ) override;
      void OnWrite() override;


      long cert_common_name_check(const ::string & common_name) override;
      void enable_cert_common_name_check(bool bEnable = true) override;

      /** SSL; Initialize ssl action_context for a client socket.
      \lparam meth_in SSL method */
      void InitializeContext(const string & action_context, const SSL_METHOD *meth_in = nullptr);
      /** SSL; Initialize ssl action_context for a server socket.
      \lparam keyfile Combined private key/certificate file
      \lparam password Password for private key
      \lparam meth_in SSL method */
      void InitializeContext(const string & action_context, const string & keyfile, const string & password, const SSL_METHOD *meth_in = nullptr);
      /** SSL; Initialize ssl action_context for a server socket.
      \lparam certfile Separate certificate file
      \lparam keyfile Combined private key/certificate file
      \lparam password Password for private key
      \lparam meth_in SSL method */
      void InitializeContext(const string & action_context, const string & certfile, const string & keyfile, const string & password, const SSL_METHOD *meth_in = nullptr);
      /** SSL; Password callback method. */
      /** SSL; get pointer to ssl action_context structure. */
      virtual SSL_CTX *GetSslContext() override;
      /** SSL; get pointer to ssl structure. */
      virtual SSL *GetSsl() override;
      /** ssl; still negotiating connection. */
      bool SSLNegotiate() override;
      /** SSL; get ssl password. */
      string GetPassword() override;


      string get_url() override;

      virtual string get_short_description() override;


      /** the actual send() */
      int try_write(const void * buf, int len);
      /** add data to output buffer top */
      void buffer(const void * buf, int len) override;

      void InitializeContextTLSClientMethod() override;

   };

   extern "C"
   i32 tcp_socket_SSL_password_cb(char *buf,i32 num,i32 rwflag,void *userdata);


} // namespace sockets_bsd



