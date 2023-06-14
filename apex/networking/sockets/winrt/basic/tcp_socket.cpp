#include "framework.h"
//#include "apex/networking/sockets/_sockets.h"


//#include <fcntl.h>
//#include <assert.h>
//#include <stdarg.h>

#ifndef ETIMEDOUT
#define ETIMEDOUT       138
#endif


namespace sockets
{


   // statics
#ifdef HAVE_OPENSSL
   //SSLInitializer tcp_socket::m_ssl_init;
#endif


   // thanks, q
#ifdef _MSC_VER
#pragma warning(disable:4355)
#endif
   tcp_socket::tcp_socket() :
      ::object(h.get_app()),
  //    base_socket(h),
//      socket(h),
//      stream_socket(h),
      ibuf(TCP_BUFSIZE_READ)
      ,m_b_input_buffer_disabled(false)
      ,m_bytes_sent(0)
      ,m_bytes_received(0)
#ifdef SOCKETS_DYNAMIC_TEMP
      ,m_buf(memory_new char[TCP_BUFSIZE_READ + 1])
#endif
      ,m_obuf_top(nullptr)
      ,m_transfer_limit(0)
      ,m_output_length(0)
#ifdef HAVE_OPENSSL
      ,m_ssl_ctx(nullptr)
      ,m_ssl(nullptr)
      ,m_sbio(nullptr)
#endif
      ,m_socks4_state(0)
      ,m_resolver_id(0)
      ,m_bReconnect(false)
      ,m_bTryingReconnect(false)
   {
      m_bCertCommonNameCheckEnabled = true;
   }
#ifdef _MSC_VER
#pragma warning(default:4355)
#endif


#ifdef _MSC_VER
#pragma warning(disable:4355)
#endif
   tcp_socket::tcp_socket(memsize isize,memsize osize) :
      ::object(h.get_app()),
  //    base_socket(h),
//      socket(h),
//      stream_socket(h),
      ibuf(isize)
      ,m_b_input_buffer_disabled(false)
      ,m_bytes_sent(0)
      ,m_bytes_received(0)
#ifdef SOCKETS_DYNAMIC_TEMP
      ,m_buf(memory_new char[TCP_BUFSIZE_READ + 1])
#endif
      ,m_obuf_top(nullptr)
      ,m_transfer_limit(0)
      ,m_output_length(0)
#ifdef HAVE_OPENSSL
      ,m_ssl_ctx(nullptr)
      ,m_ssl(nullptr)
      ,m_sbio(nullptr)
#endif
      ,m_socks4_state(0)
      ,m_resolver_id(0)
      ,m_bReconnect(false)
      ,m_bTryingReconnect(false)
   {
      m_bCertCommonNameCheckEnabled = true;
      UNREFERENCED_PARAMETER(osize);
   }
#ifdef _MSC_VER
#pragma warning(default:4355)
#endif


   tcp_socket::~tcp_socket()
   {
#ifdef SOCKETS_DYNAMIC_TEMP
      delete[] m_buf;
#endif
      
      // %! is_empty m_obuf
      auto pnode = m_obuf.get_head();
      
      while(pnode != nullptr)
      {

         delete pnode->m_value;

         pnode = pnode->m_pnext;

      }

      m_obuf.erase_all();

#ifdef HAVE_OPENSSL
      if (m_ssl)
      {
         SSL_free(m_ssl);
      }
#endif
   }


   /*   bool tcp_socket::open(ipaddr_t ip,port_t port,bool skip_socks)
      {
         ipv4_address ad(get_app(), ip, port);
         ipv4_address local(this);
         return open(ad, local, skip_socks);
      }


      bool tcp_socket::open(in6_addr ip,port_t port,bool skip_socks)
      {
         ipv6_address ad(get_app(), ip, port);
         return open(ad, skip_socks);
      }
      */

   bool tcp_socket::open(::networking::address * ad, bool skip_socks)
   {

      m_bConnecting = true;

      m_streamsocket = ref memory_new ::winrt::Windows::Networking::Sockets::StreamSocket;

      //attach(data);

      create_socket();

      m_event.ResetEvent();

      String ^ strService = as_string(ad.get_service_number());

      try
      {

         m_streamsocket->ConnectAsync(ad.m_hostname, strService)->Completed =
            ref memory_new ::winrt::Windows::Foundation::AsyncActionCompletedHandler
            ([this](::winrt::Windows::Foundation::IAsyncAction ^ action, ::winrt::Windows::Foundation::AsyncStatus status)
               {

                  if (status == ::winrt::Windows::Foundation::AsyncStatus::Completed)
                  {

                     m_bConnected = true;

                     m_bOnConnect = true;

                  }
                  else
                  {

                     SetCloseAndDelete();

                  }

                  m_bConnecting = false;

                  m_event.SetEvent();

               });

      }
      catch (...)
      {

         return false;

      }


      return true;

   }


   bool tcp_socket::open(::networking::address * ad, ::networking::address * bind_ad, bool skip_socks)
   {
      /*      if (!ad.IsValid())
            {
               fatal() <<log_this, "open", 0, "Invalid ::networking::address";
               SetCloseAndDelete();
               return false;
            }*/
      /*      if (socket_handler()->get_count() >= FD_SETSIZE)
            {
               fatal() <<log_this, "open", 0, "no space left in fd_set";
               SetCloseAndDelete();
               return false;
            }*/


      m_streamsocket = ref memory_new ::winrt::Windows::Networking::Sockets::StreamSocket;

      ::winrt::Windows::Networking::EndpointPair ^ pair = ref memory_new ::winrt::Windows::Networking::EndpointPair(bind_ad.m_hostname,  ansi_string_from_i64(bind_ad.get_service_number()), ad.m_hostname, ansi_string_from_i64(ad.get_service_number()));
      //::sockets::socket::os_data data;
      //data.o = m_posdata->m_streamsocket;
      //attach(data);

      m_streamsocket->ConnectAsync(pair)->Completed =
      ref memory_new ::winrt::Windows::Foundation::AsyncActionCompletedHandler
      ([this](::winrt::Windows::Foundation::IAsyncAction ^ action, ::winrt::Windows::Foundation::AsyncStatus status)
      {

         if(status == ::winrt::Windows::Foundation::AsyncStatus::Completed)
         {

            OnConnect();

         }

      });


      m_streamsocket = ref memory_new ::winrt::Windows::Networking::Sockets::StreamSocket();

      //data.o = m_posdata->m_streamsocket;
      
      //attach(data);



      set_connecting(false);
      SetSocks4(false);

      return true;
      // check for pooling
      /*if (socket_handler()->PoolEnabled())
      {
         base_socket_handler::PoolSocket *pools = socket_handler()->FindConnection(SOCK_STREAM, "tcp", ad);
         if (pools)
         {
            CopyConnection( pools );
            delete pools;

            SetIsClient();
            SetCallOnConnect(); // base_socket_handler must call OnConnect
            INFO(log_this, "SetCallOnConnect", 0, "Found pooled connection");
            return true;
         }
      }*/
      // if not, create memory_new connection
      //SOCKET s = CreateSocket(ad.GetFamily(), SOCK_STREAM, "tcp");
      //if (s == INVALID_SOCKET)
      //{
      // return false;
      //}
      // socket must be nonblocking for async connect
      /*      if (!SetNonblocking(true, s))
            {
               SetCloseAndDelete();
               ::closesocket(s);
               return false;
            }
            SetIsClient(); // client because we connect
            SetClientRemoteAddress(ad);
            int n = 0;
            if (bind_ad.GetPort() != 0)
            {
               bind(s, bind_ad, bind_ad);
            }
            if (!skip_socks && GetSocks4Host() && GetSocks4Port())
            {
               ipv4_address sa(get_app(), GetSocks4Host(), GetSocks4Port());
               {
                  string sockshost;
                  psession->sockets().net().l2ip(GetSocks4Host(), sockshost);
                  INFO(log_this, "open", 0, "is_connecting to socks4 server @ " + sockshost + ":" + as_string(GetSocks4Port()));
               }
               SetSocks4();
               n = connect(s, sa, sa);
               SetRemoteAddress(sa);
            }
            else
            {
               n = connect(s, ad, ad);
               SetRemoteAddress(ad);
            }
            if (n == -1)
            {
         #ifdef _WIN32
               // check error code that means a connect is in progress
               int iError = ::WSAGetLastError();
               if (iError == WSAEWOULDBLOCK || iError == 0)
         #else
               int iError = Errno;
               if(iError == EINPROGRESS)
         #endif
               {
                  attach(s);
                  set_connecting( true ); // this flag will control fd_set's
               }
               else
               if (Socks4() && socket_handler()->Socks4TryDirect() ) // retry
               {
                  ::closesocket(s);
                  return open(ad, true);
               }
               else
               if (Reconnect())
               {
                  string strError = bsd_socket_error(iError);
                  INFO(log_this, "connect: failed, reconnect pending", iError, bsd_socket_error(iError));
                  attach(s);
                  set_connecting( true ); // this flag will control fd_set's
               }
               else
               {
                  string strError = bsd_socket_error(iError);
                  fatal() <<log_this, "connect: failed", iError, bsd_socket_error(iError);
                  SetCloseAndDelete();
                  ::closesocket(s);
                  return false;
               }
            }
            else
            {
               attach(s);
               SetCallOnConnect(); // base_socket_handler must call OnConnect
            }

            // 'true' means connected or connecting(not yet connected)
            // 'false' means something failed
            return true; //!is_connecting();*/
   }


   bool tcp_socket::open(const string &host,port_t port)
   {

      return open(::networking::address(host, port));

      /*if (IsIpv6())
      {
         if (!socket_handler()->ResolverEnabled() || psession->sockets().net().isipv6(host) )
         {
            in6_addr a;
            if (!psession->sockets().net().u2ip(host, a))
            {
               SetCloseAndDelete();
               return false;
            }
            ipv6_address ad(get_app(), a, port);
            ipv6_address local(this);
            if(!open(ad, local))
               return false;
            m_strHost = host;
            return true;
         }
         m_resolver_id = Resolve6(host, port);
         m_strHost = host;
         return true;
      }
      if (!socket_handler()->ResolverEnabled() || psession->sockets().net().isipv4(host) )
      {
         ipaddr_t l;
         if (!psession->sockets().net().u2ip(host, l))
         {
            SetCloseAndDelete();
            return false;
         }
         ipv4_address ad(get_app(), l, port);
         ipv4_address local(this);
         m_strHost = host;
         if(!open(ad, local))
            return false;
         m_strHost = host;
         return true;
      }
      // resolve using async resolver thread
      m_resolver_id = Resolve(host, port);
      m_strHost = host;
      return true;*/
   }


   void tcp_socket::OnResolved(int atom, ::networking::address * addr)
   {
      information("tcp_socket::OnResolved atom %d addr %x port %d\n", atom, addr.get_display_number(), addr.get_service_number());
      if (atom == m_resolver_id)
      {
         if(open(addr))
         {
            if (!socket_handler()->Valid(this))
            {
               socket_handler()->add(this);
            }
         }
         else
         {
            fatal() <<log_this, "OnResolved", 0, "Resolver failed";
            SetCloseAndDelete();
         }
      }
      else
      {
         fatal() <<log_this, "OnResolved", atom, "Resolver returned wrong job atom";
         SetCloseAndDelete();
      }
   }


   /*   void tcp_socket::OnResolved(int atom,in6_addr& a,port_t port)
      {
         if (atom == m_resolver_id)
         {
            ipv6_address ad(get_app(), a, port);
            if (ad.IsValid())
            {
               ipv6_address local(this);
               if (open(ad, local))
               {
                  if (!socket_handler()->Valid(this))
                  {
                     socket_handler()->add(this);
                  }
               }
            }
         }
         else
         {
            fatal() <<log_this, "OnResolved", atom, "Resolver returned wrong job atom";
            SetCloseAndDelete();
         }
      }*/


   void tcp_socket::OnRead()
   {

      m_bReading = true;
      m_bExpectRequest = false;
      m_bExpectResponse = false;

      ::winrt::Windows::Storage::Streams::IInputStream ^ inputstream = m_streamsocket->InputStream;

      //if(inputstream->UnconsumedBufferLength > 0)
      //{

      //   Array < unsigned char, 1U > ^ ucha = ref memory_new Array < unsigned char, 1U >(reader->UnconsumedBufferLength);

      //   reader->ReadBytes(ucha);

      //   on_read((char *) ucha->Data, ucha->Length);

      //   return ;

      //}

      //reader->InputStreamOptions = ::winrt::Windows::Storage::Streams::InputStreamOptions::Partial;


      //::winrt::Windows::Storage::Streams::DataReaderLoadOperation ^ op  = nullptr;

      m_memoryRead.set_size(16 * 1024);

      m_bufferRead = m_memoryRead.get_os_buffer();
      m_event.ResetEvent();

      try
      {

         auto res = wait(inputstream->ReadAsync(m_bufferRead, m_memoryRead.get_size(), ::winrt::Windows::Storage::Streams::InputStreamOptions::Partial));

         m_memoryRead.set_os_buffer(res);

      }
      catch(...)
      {

         SetCloseAndDelete();

         m_event.SetEvent();

         return;

      }

      m_event.SetEvent();

      on_read((char*)m_memoryRead.get_data(), m_memoryRead.get_size());

      



      //op->Completed =
      //ref memory_new ::winrt::Windows::Foundation::AsyncOperationCompletedHandler < unsigned int >([=]
      //      (::winrt::Windows::Foundation::IAsyncOperation<unsigned int> ^ asyncInfo, ::winrt::Windows::Foundation::AsyncStatus asyncStatus)
      //{
      //   if(IsCloseAndDelete())
      //   {
      //      information("Close and delete set");
      //   }
      //   else if(asyncStatus == ::winrt::Windows::Foundation::AsyncStatus::Completed)
      //   {
      //      //int n = reader->UnconsumedBufferLength;
      //      Array < unsigned char, 1U > ^ ucha = ref memory_new Array < unsigned char, 1U >(reader->UnconsumedBufferLength);
      //      reader->ReadBytes(ucha);
      //      memory mem;
      //      mem.assign(ucha->Data, ucha->Length);
      //      on_read((char *) mem.get_data(), mem.get_size());
      //   }
      //   else
      //   {
      //      SetCloseAndDelete();
      //   }
      //   //delete reader;
      //   reader->DetachStream();
      //   m_bReading = false;
      //   m_event.SetEvent();
      //});

   }


   void tcp_socket::on_read(const void * pdata, iptr n)
   {

      char * buf = (char *) pdata;

      // unbuffered
      if (n > 0)
      {
         stream_socket::on_read(buf, n);
      }
      if (m_b_input_buffer_disabled)
      {
         return;
      }
      // further processing: socks4
      if (Socks4())
      {
         bool need_more = false;
         while (GetInputLength() && !need_more && !IsCloseAndDelete())
         {
            need_more = OnSocks4Read();
         }
      }
      if(IsCloseAndDelete())
      {
         m_bExpectRequest = false;
         m_bExpectResponse = false;
         m_event.SetEvent();
      }
      else if(m_bExpectRequest || m_bExpectResponse)
      {
         m_event.SetEvent();
      }
      else
      {
         m_event.SetEvent();
         SetCloseAndDelete();
      }
   }


   void tcp_socket::OnWriteComplete()
   {
   }


   void tcp_socket::OnWrite()
   {
      if (is_connecting())
      {
         int err = SoError();

         // don't reset connecting flag on error here, we want the OnConnectFailed timeout later on
         if (!err) // ok
         {
            Set(!IsDisableRead(), false);
            set_connecting(false);
            SetCallOnConnect();
            return;
         }
#ifdef BSD_STYLE_SOCKETS
         fatal() <<log_this, "tcp: connect failed", err, bsd_socket_error(err);
#endif
         Set(false, false); // no more monitoring because connection failed

         // failed
         if (Socks4())
         {
            // %! leave 'is_connecting' flag set?
            OnSocks4ConnectFailed();
            return;
         }
         if (GetConnectionRetry() == -1 ||
               (GetConnectionRetry() && GetConnectionRetryCount() < GetConnectionRetry()) )
         {
            // even though the connection failed at once, only retry after
            // the connection timeout.
            // should we even try to connect again, when CheckConnect returns
            // false it's because of a connection error - not a timeout...
            return;
         }
         set_connecting(false);
         SetCloseAndDelete( true );
         /// \todo state reason why connect failed
         OnConnectFailed();
         return;
      }
      // try send next block in buffer
      // if full block is sent, repeat
      // if all blocks are sent, reset m_wfds

      bool repeat = false;
      memsize sz = m_transfer_limit ? GetOutputLength() : 0;
      do
      {
         auto pnode = m_obuf.get_head();
         if(pnode == nullptr)
            return;
         OUTPUT * p = pnode->m_value;
         repeat = false;
         int n = TryWrite(p -> Buf(), p -> Len());
         if (n > 0)
         {
            memsize left = p -> erase(n);
            m_output_length -= n;
            if (!left)
            {
               delete p;
               m_obuf.erase_item(pnode);
               if (!m_obuf.get_size())
               {
                  m_obuf_top = nullptr;
                  OnWriteComplete();
               }
               else
               {
                  repeat = true;
               }
            }
         }
      }
      while (repeat);

      if (m_transfer_limit && sz > m_transfer_limit && GetOutputLength() < m_transfer_limit)
      {
         OnTransferLimit();
      }

      // check output buffer set, set/reset m_wfds accordingly
      {
         bool br;
         bool bw;
         bool bx;
         socket_handler()->get(GetSocket(), br, bw, bx);
         if (m_obuf.get_size())
            Set(br, true);
         else
            Set(br, false);
      }
   }


   int tcp_socket::TryWrite(const char *buf, memsize len)
   {

      m_memoryWrite.append(buf, len);

      m_bufferWrite = m_memoryWrite.get_os_buffer();

      m_bErrorWriting = false;

      m_streamsocket->OutputStream->WriteAsync(m_bufferWrite)
         ->Completed = ref memory_new ::winrt::Windows::Foundation::AsyncOperationWithProgressCompletedHandler <unsigned int, unsigned int >([this](::winrt::Windows::Foundation::IAsyncOperationWithProgress <unsigned int, unsigned int >^ operation, ::winrt::Windows::Foundation::AsyncStatus status)
            {

               if (status == ::winrt::Windows::Foundation::AsyncStatus::Completed)
               {

                  if (m_bWaitingResponse)
                  {

                     m_bWaitingResponse = false;

                     m_bExpectResponse = true;

                  }

               }
               else
               {

                  m_bErrorWriting = true;

               }

            });


      if (m_bWaitingResponse)
      {



      }

      //int n = reader->UnconsumedBufferLength;

      /*if(ucha != nullptr)
      {
         OnRawData(ucha->Data, ucha->Length);
      }*/

      return len;

   }


   void tcp_socket::buffer(const char *buf, memsize len)
   {

      memsize ptr = 0;

      m_output_length += len;

      while (ptr < len)
      {
         // buf/len => pbuf/sz
         memsize space = 0;
         if (m_obuf_top && (space = m_obuf_top -> Space()) > 0)
         {
            const char *pbuf = buf + ptr;
            memsize sz = len - ptr;
            if (space >= sz)
            {
               m_obuf_top -> add(pbuf, sz);
               ptr += sz;
            }
            else
            {
               m_obuf_top -> add(pbuf, space);
               ptr += space;
            }
         }
         else
         {
            m_obuf_top = memory_new OUTPUT;
            m_obuf.add_tail( m_obuf_top );
         }
      }
   }



   void tcp_socket::write(const void * pdata, memsize len)
   {

      const char * buf = (const char * ) pdata;

      //if (!Ready() && !is_connecting())
      //{
      //   //log("SendBuf", -1, "Attempt to write to a non-ready socket" ); // warning
      //   if (GetSocket() == INVALID_SOCKET)
      //      INFO(log_this, "SendBuf", 0, " * GetSocket() == INVALID_SOCKET");
      //   if (is_connecting())
      //      INFO(log_this, "SendBuf", 0, " * is_connecting()");
      //   if (IsCloseAndDelete())
      //      INFO(log_this, "SendBuf", 0, " * IsCloseAndDelete()");
      //   return;
      //}
      //if (!IsConnected())
      //{
      //   //log("SendBuf", -1, "Attempt to write to a non-connected socket, will be sent on connect" ); // warning
      //   buffer(buf, len);
      //   return;
      //}
      //if (m_obuf_top)
      //{
      //   buffer(buf, len);
      //   return;
      //}
      int n = TryWrite(buf, len);
      if (n >= 0 && n < (int)len)
      {
         buffer(buf + n, len - n);
      }
      // if ( data in buffer || !IsConnected )
      // {
      //   add to buffer
      // }
      // else
      // try_send
      // if any data is unsent, buffer it and set m_wfds

      // check output buffer set, set/reset m_wfds accordingly
      {
         bool br;
         bool bw;
         bool bx;
         socket_handler()->get(GetSocket(), br, bw, bx);
         if (m_obuf.get_size())
            Set(br, true);
         else
            Set(br, false);
      }
   }


   void tcp_socket::OnLine(const string & )
   {
   }


#if defined(BSD_STYLE_SOCKETS)


   void tcp_socket::OnSocks4Connect()
   {

      char request[1000];
      memory_set(request, 0, sizeof(request));
      request[0] = 4; // socks v4
      request[1] = 1; // command code: CONNECT
      {
         ::networking::address ad = GetClientRemoteAddress();
         if(ad.is_ipv4())
         {
            port_t port = ad.get_service_number();
            in_addr addr;
            ::apexacmesystem()->sockets().net().convert(addr, ad.get_display_number());
            ::memory_copy(request + 2, &port, sizeof(port_t)); // nwbo is ok here
            ::memory_copy(request + 2 + sizeof(port_t), &addr, sizeof(in_addr));
         }
         else
         {
            /// \todo warn
         }
      }
      strcpy(request + 8, GetSocks4Userid());
      memsize length = GetSocks4Userid().get_length() + 8 + 1;
      write(request, length);
      m_socks4_state = 0;
   }


   void tcp_socket::OnSocks4ConnectFailed()
   {
      warning() <<"OnSocks4ConnectFailed",0,"connection to socks4 server failed, trying direct connection";
      if (!socket_handler()->Socks4TryDirect())
      {
         set_connecting(false);
         SetCloseAndDelete();
         OnConnectFailed(); // just in case
      }
      else
      {
         SetRetryClientConnect();
      }
   }


   bool tcp_socket::OnSocks4Read()
   {
      switch (m_socks4_state)
      {
      case 0:
         ibuf.read(&m_socks4_vn, 1);
         m_socks4_state = 1;
         break;
      case 1:
         ibuf.read(&m_socks4_cd, 1);
         m_socks4_state = 2;
         break;
      case 2:
         if (GetInputLength() > 1)
         {
            ibuf.read( (char *)&m_socks4_dstport, 2);
            m_socks4_state = 3;
         }
         else
         {
            return true;
         }
         break;
      case 3:
         if (GetInputLength() > 3)
         {
            ibuf.read( (char *)&m_socks4_dstip, 4);
            SetSocks4(false);

            switch (m_socks4_cd)
            {
            case 90:
               OnConnect();
               INFO(log_this, "OnSocks4Read", 0, "Connection established");
               break;
            case 91:
            case 92:
            case 93:
               fatal() <<log_this, "OnSocks4Read",m_socks4_cd,"socks4 server reports connect failed";
               set_connecting(false);
               SetCloseAndDelete();
               OnConnectFailed();
               break;
            default:
               fatal() <<log_this, "OnSocks4Read",m_socks4_cd,"socks4 server unrecognized response";
               SetCloseAndDelete();
               break;
            }
         }
         else
         {
            return true;
         }
         break;
      }
      return false;
   }


#endif


   void tcp_socket::OnSSLConnect()
   {

      ::wait(m_streamsocket->UpgradeToSslAsync(::winrt::Windows::Networking::Sockets::SocketProtectionLevel::Tls10, m_addressRemote.m_hostname));

      /*      SetNonblocking(true);
            {
               if (m_ssl_ctx)
               {
         information("SSL Context already initialized - closing socket\n");
                  SetCloseAndDelete(true);
                  return;
               }
               InitSSLClient();
            }
            if (m_ssl_ctx)
            {
               /* Connect the SSL socket */
      /*       m_ssl = SSL_new(m_ssl_ctx);
             if (!m_ssl)
             {
       information(" m_ssl is nullptr\n");
                SetCloseAndDelete(true);
                return;
             }
             SSL_set_mode(m_ssl, SSL_MODE_AUTO_RETRY);
             m_sbio = BIO_new_socket((int)GetSocket(), BIO_NOCLOSE);
             if (!m_sbio)
             {
       information(" m_sbio is nullptr\n");
                SetCloseAndDelete(true);
                return;
             }
             SSL_set_bio(m_ssl, m_sbio, m_sbio);
             if (!SSLNegotiate())
             {
                SetSSLNegotiate();
             }
          }
          else
          {
             SetCloseAndDelete();
          }*/
   }


   void tcp_socket::OnSSLAccept()
   {
      SetNonblocking(true);
      /*      {
               if (m_ssl_ctx)
               {
         information("SSL Context already initialized - closing socket\n");
                  SetCloseAndDelete(true);
                  return;
               }
               InitSSLServer();
               SetSSLServer();
            }
            if (m_ssl_ctx)
            {
               m_ssl = SSL_new(m_ssl_ctx);
               if (!m_ssl)
               {
         information(" m_ssl is nullptr\n");
                  SetCloseAndDelete(true);
                  return;
               }
               SSL_set_mode(m_ssl, SSL_MODE_AUTO_RETRY);
               m_sbio = BIO_new_socket((int)GetSocket(), BIO_NOCLOSE);
               if (!m_sbio)
               {
         information(" m_sbio is nullptr\n");
                  SetCloseAndDelete(true);
                  return;
               }
               SSL_set_bio(m_ssl, m_sbio, m_sbio);
         //      if (!SSLNegotiate())
               {
                  SetSSLNegotiate();
               }
            }*/
   }


   bool tcp_socket::SSLNegotiate()
   {
      /*      if(!IsSSLServer()) // client
            {
               if(m_spsslclientcontext->m_psession != nullptr)
               {
                  SSL_set_session(m_ssl, m_spsslclientcontext->m_psession);
               }
               int r = SSL_connect(m_ssl);
               if (r > 0)
               {
                  SetSSLNegotiate(false);

                  long x509_err = cert_common_name_check(m_strHost);
                  if(x509_err != X509_V_OK
                  && x509_err != X509_V_ERR_SELF_SIGNED_CERT_IN_CHAIN
                  && x509_err != X509_V_ERR_APPLICATION_VERIFICATION
                  && x509_err != X509_V_ERR_UNABLE_TO_GET_ISSUER_CERT_LOCALLY)
                  {
                     INFO(log_this, "SSLNegotiate/cert_common_name_check", 0, "cert_common_name_check failed");
                     SetSSLNegotiate(false);
                     SetCloseAndDelete();
                     OnSSLConnectFailed();
                     return false;
                  }

                  /// \todo: resurrect certificate check... client
         //         CheckCertificateChain( "");//ServerHOST);
                  SetNonblocking(false);
                  //
                  {
                     SetConnected();
                     if (GetOutputLength())
                     {
                        OnWrite();
                     }
                  }
                  if (IsReconnect())
                     OnReconnect();
                  else
                  {
                     OnConnect();
                  }
                  INFO(log_this, "SSLNegotiate/SSL_connect", 0, "Connection established");
                  if(m_spsslclientcontext->m_psession == nullptr)
                  {
                     m_spsslclientcontext->m_psession = SSL_get1_session(m_ssl);
                  }
                  return true;
               }
               else if(!r)
               {
                  if(m_spsslclientcontext->m_psession != nullptr)
                  {

                     if(m_spsslclientcontext->m_iRetry == 0)
                     {
                        m_spsslclientcontext->m_iRetry = 1;
                        SSL_clear(m_ssl);
                        SSL_SESSION_free(m_spsslclientcontext->m_psession);
                        m_spsslclientcontext->m_psession = nullptr;
                        goto skip;
                     }
                     else
                     {
                        m_spsslclientcontext->m_iRetry = 0;
                     }
                  }
                  r = SSL_get_error(m_ssl, rectangle);
                  INFO(log_this, "SSLNegotiate/SSL_connect", 0, "Connection failed");
                  SetSSLNegotiate(false);
                  SetCloseAndDelete();
                  OnSSLConnectFailed();
                  skip:;
               }
               else
               {
                  r = SSL_get_error(m_ssl, rectangle);
                  if (r != SSL_ERROR_WANT_READ && r != SSL_ERROR_WANT_WRITE)
                  {
                     INFO(log_this, "SSLNegotiate/SSL_connect", -1, "Connection failed");
         information("SSL_connect() failed - closing socket, return code: %d\n",r);
                     SetSSLNegotiate(false);
                     SetCloseAndDelete(true);
                     OnSSLConnectFailed();
                  }
               }
            }
            else // server
            {
               int r = SSL_accept(m_ssl);
               if (r > 0)
               {
                  SetSSLNegotiate(false);
                  /// \todo: resurrect certificate check... server
         //         CheckCertificateChain( "");//ClientHOST);
                  SetNonblocking(false);
                  //
                  {
                     SetConnected();
                     if (GetOutputLength())
                     {
                        OnWrite();
                     }
                  }
                  OnAccept();
                  INFO(log_this, "SSLNegotiate/SSL_accept", 0, "Connection established");
                  return true;
               }
               else
               if (!r)
               {
                  INFO(log_this, "SSLNegotiate/SSL_accept", 0, "Connection failed");
                  SetSSLNegotiate(false);
                  SetCloseAndDelete();
                  OnSSLAcceptFailed();
               }
               else
               {
                  r = SSL_get_error(m_ssl, rectangle);
                  if (r != SSL_ERROR_WANT_READ && r != SSL_ERROR_WANT_WRITE)
                  {
                     INFO(log_this, "SSLNegotiate/SSL_accept", -1, "Connection failed");
         information("SSL_accept() failed - closing socket, return code: %d\n",r);
                     SetSSLNegotiate(false);
                     SetCloseAndDelete(true);
                     OnSSLAcceptFailed();
                  }
               }
            }
            return false;*/

      return false;
   }


   void tcp_socket::InitSSLClient()
   {
//      InitializeContext(m_strInitSSLClientContext, SSLv23_method());
   }


   void tcp_socket::InitSSLServer()
   {
//      fatal() <<log_this, "InitSSLServer", 0, "You MUST implement your own InitSSLServer method";
      //    SetCloseAndDelete();
   }


   void tcp_socket::close()
   {
      /*      if (GetSocket() == INVALID_SOCKET) // this could happen
            {
               warning() <<"socket::close", 0, "file descriptor invalid";
               return 0;
            }
            int n;
            SetNonblocking(true);
            if (!Lost() && IsConnected() && !(GetShutdown() & SHUT_WR))
            {
               if (shutdown(GetSocket(), SHUT_WR) == -1)
               {
                  // failed...
                  __error("shutdown", Errno, bsd_socket_error(Errno));
               }
            }
            //
            char tmp[1000];
            if (!Lost() && (n = recv(GetSocket(),tmp,1000,0)) >= 0)
            {
               if (n)
               {
                  warning() <<"read() after shutdown", n, "bytes read";
               }
            }
         #ifdef HAVE_OPENSSL
            if (IsSSL() && m_ssl)
               SSL_shutdown(m_ssl);
            if (m_ssl)
            {
               SSL_free(m_ssl);
               m_ssl = nullptr;
            }
         #endif*/
      //return stream_socket::close();
      stream_socket::close();

   }


#ifdef HAVE_OPENSSL
   SSL_CTX *tcp_socket::GetSslContext()
   {
      if (!m_ssl_ctx)
         warning() <<"GetSslContext", 0, "SSL Context is nullptr; check InitSSLServer/InitSSLClient";
      return m_ssl_ctx;
   }

   SSL *tcp_socket::GetSsl()
   {
      if (!m_ssl)
         warning() <<"GetSsl", 0, "SSL is nullptr; check InitSSLServer/InitSSLClient";
      return m_ssl;
   }
#endif


   void tcp_socket::SetReconnect(bool bReconnect)
   {
      m_bReconnect = bReconnect;
   }

   void tcp_socket::OnRawData(char * buf_in, memsize len)
   {
      socket::OnRawData(buf_in, len);
   }


   memsize tcp_socket::GetInputLength()
   {
      return (memsize) ibuf.get_length();
   }


   memsize tcp_socket::GetOutputLength()
   {
      return m_output_length;
   }


   u64 tcp_socket::GetBytesReceived(bool clear)
   {
      u64 z = m_bytes_received;
      if (clear)
         m_bytes_received = 0;
      return z;
   }


   u64 tcp_socket::GetBytesSent(bool clear)
   {
      u64 z = m_bytes_sent;
      if (clear)
         m_bytes_sent = 0;
      return z;
   }


   bool tcp_socket::Reconnect()
   {
      return m_bReconnect;
   }


   void tcp_socket::SetIsReconnect(bool bTryingReconnect)
   {
      m_bTryingReconnect = bTryingReconnect;
   }

   bool tcp_socket::IsReconnect()
   {
      return m_bTryingReconnect;
   }

   const string & tcp_socket::GetPassword()
   {
      return m_password;
   }

   void tcp_socket::DisableInputBuffer(bool x)
   {
      m_b_input_buffer_disabled = x;
   }


   void tcp_socket::OnOptions(int family, int type, int protocol, SOCKET s)
   {
      UNREFERENCED_PARAMETER(family);
      UNREFERENCED_PARAMETER(type);
      UNREFERENCED_PARAMETER(protocol);
      UNREFERENCED_PARAMETER(s);
      //information("socket::OnOptions()\n");
#ifdef SO_NOSIGPIPE
      _SetSoNosigpipe(s, true);
#endif
      _SetSoReuseaddr(s, true);
      _SetSoKeepalive(s, true);
   }


   void tcp_socket::SetLineProtocol(bool x)
   {
      stream_socket::SetLineProtocol(x);
      DisableInputBuffer(x);
   }


   bool tcp_socket::SetTcpNodelay(bool x)
   {
#if defined(TCP_NODELAY) && defined(BSD_STYLE_SOCKETS)
      int optval = x ? 1 : 0;
      if (setsockopt(GetSocket(), IPPROTO_TCP, TCP_NODELAY, (char *)&optval, sizeof(optval)) == -1)
      {
         fatal() <<log_this, "setsockopt(IPPROTO_TCP, TCP_NODELAY)", Errno, bsd_socket_error(Errno);
         return false;
      }
      return true;
#else
      INFO(log_this, "socket option not available", 0, "TCP_NODELAY");
      return false;
#endif
   }



   void tcp_socket::on_connection_timeout()
   {
      
      fatal() <<log_this, "connect", -1, "connect timeout";

      m_estatus = ::error_timeout;

      if (Socks4())
      {
         OnSocks4ConnectFailed();
         // retry direct connection
      }
      else if (GetConnectionRetry() == -1 ||
               (GetConnectionRetry() && GetConnectionRetryCount() < GetConnectionRetry()) )
      {
         IncreaseConnectionRetries();
         // ask socket via OnConnectRetry callback if we should continue trying
         if (OnConnectRetry())
         {
            SetRetryClientConnect();
         }
         else
         {
            SetCloseAndDelete( true );
            /// \todo state reason why connect failed
            OnConnectFailed();
         }
      }
      else
      {
         SetCloseAndDelete(true);
         /// \todo state reason why connect failed
         OnConnectFailed();
      }
      //
      set_connecting(false);
   }


#ifdef _WIN32
   void tcp_socket::OnException()
   {
      if (is_connecting())
      {
         
         int iError = this->socket_handler()->m_iSelectErrno;

         if(iError == ETIMEDOUT)
         {

            m_estatus = ::error_timeout;

         }
         else
         {
            //m_estatus = status_failed;
         }
         if (Socks4())
            OnSocks4ConnectFailed();
         else if (GetConnectionRetry() == -1 ||
                  (GetConnectionRetry() &&
                   GetConnectionRetryCount() < GetConnectionRetry() ))
         {
            // even though the connection failed at once, only retry after
            // the connection timeout
            // should we even try to connect again, when CheckConnect returns
            // false it's because of a connection error - not a timeout...
         }
         else
         {
            set_connecting(false); // tnx snibbe
            SetCloseAndDelete();
            OnConnectFailed();
         }
         return;
      }
      // %! exception doesn't always mean something bad happened, this code should be reworked
      // errno valid here?
      int err = SoError();
#ifdef BSD_STYLE_SOCKETS
      fatal() <<log_this, "exception on select", err, bsd_socket_error(err);
#endif
      SetCloseAndDelete();
   }
#endif // _WIN32


   int tcp_socket::Protocol()
   {
      //return IPPROTO_TCP;
      return 0;
   }


   void tcp_socket::SetTransferLimit(memsize sz)
   {
      m_transfer_limit = sz;
   }


   void tcp_socket::OnTransferLimit()
   {
   }

   string tcp_socket::get_url()
   {
      return m_strUrl;
   }

   long tcp_socket::cert_common_name_check(const char * common_name)
   {

      if(!m_bCertCommonNameCheckEnabled)
      {
         return 0; // no_error
//         return X509_V_OK;
      }

      //X509 *cert = nullptr;
      //X509_NAME *topic = nullptr;

      //cert = SSL_get_peer_certificate(m_ssl);
      //bool ok = false;
      //if (cert != nullptr && strlen(common_name) > 0)
      //{
      //   char data[256];
      //   if ((topic = X509_get_subject_name(cert)) != nullptr && X509_NAME_get_text_by_NID(topic, NID_commonName, data, 256) > 0)
      //   {
      //      data[255] = 0;
      //      if (ansi_count_compare_ci(data, common_name, 255) == 0)
      //      {
      //         ok = true;
      //      }
      //   }
      //}

      //if(cert)
      //{
      //   X509_free(cert);
      //}

      //if(ok)
      //{
      //   return SSL_get_verify_result(m_ssl);
      //}

      //return X509_V_ERR_APPLICATION_VERIFICATION;
      return 1; //  error
   }
   void tcp_socket::enable_cert_common_name_check(bool bEnable)
   {
      m_bCertCommonNameCheckEnabled = bEnable;
   }

   /*
   void tcp_socket::OnConnected(::winrt::Windows::Foundation::IAsyncAction ^ action, ::winrt::Windows::Foundation::AsyncStatus status)
   {

      if(status == ::winrt::Windows::Foundation::Completed)
      {
         OnConnected();
      }

   }
   */
   string tcp_socket::get_connect_host()
   {

      return m_strConnectHost;

   }


   port_t tcp_socket::get_connect_port()
   {

      return m_iConnectPort;

   }


} // namespace sockets



