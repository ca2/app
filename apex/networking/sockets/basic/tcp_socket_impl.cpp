#include "framework.h"
//#include "tcp_socket_impl.h"
//#include "tcp_socket_impl.h"
//
//
//namespace sockets
//{
//
//#ifdef MACOS
//   bool tcp_socket_impl::s_bReuseSession = false;
//#else
//   bool tcp_socket_impl::s_bReuseSession = true;
//#endif
//
//   tcp_socket_impl::tcp_socket_impl():
//      //::object(&h),
//      //base_socket(h),
//      //socket(h),
//      //stream_socket(h)
//      //,
//      ibuf(TCP_BUFSIZE_READ)
//      ,m_b_input_buffer_disabled(false)
//      ,m_bytes_sent(0)
//      ,m_bytes_received(0)
//      ,m_transfer_limit(0)
//      ,m_output_length(0)
//      ,m_socks4_state(0)
//      ,m_resolver_id(0)
//      ,m_bReconnect(false)
//      ,m_bTryingReconnect(false)
//   {
//      m_bReuseSession = s_bReuseSession;
////      SSL_init_app_data2_3_idx();
//      m_bClientSessionSet = false;
//      m_memRead.set_size(TCP_BUFSIZE_READ + 1);
//      m_bCertCommonNameCheckEnabled = true;
//      //m_pmutexSslCtx = nullptr;
//   }
//#ifdef _MSC_VER
//#pragma warning(default:4355)
//#endif
//
//
////#ifdef _MSC_VER
////#pragma warning(disable:4355)
////#endif
////   tcp_socket_impl::tcp_socket_impl(memsize isize,memsize osize):
////      //::object(&h),
////  //    base_socket(h),
//////      socket(h),
//////      stream_socket(h),
////      ibuf(isize)
////      ,m_b_input_buffer_disabled(false)
////      ,m_bytes_sent(0)
////      ,m_bytes_received(0)
////      ,m_transfer_limit(0)
////      ,m_output_length(0)
////      ,m_socks4_state(0)
////      ,m_resolver_id(0)
////      ,m_bReconnect(false)
////      ,m_bTryingReconnect(false)
////   {
////      m_bReuseSession = s_bReuseSession;
////      //SSL_init_app_data2_3_idx();
////      m_bClientSessionSet = false;
////      m_memRead.set_size(TCP_BUFSIZE_READ + 1);
////      m_bCertCommonNameCheckEnabled = true;
////      //m_pmutexSslCtx = nullptr;
////      UNREFERENCED_PARAMETER(osize);
////   }
////#ifdef _MSC_VER
////#pragma warning(default:4355)
////#endif
////
////
//   tcp_socket_impl::~tcp_socket_impl()
//   {
//
//      //if(m_socket != INVALID_SOCKET) // this could happen
//      //{
//
//      //   close();
//
//      //}
//
//
//   }
//
//
//   /*
//   bool tcp_socket_impl::open(in_addr ip,::networking::port_t port,bool skip_socks)
//   {
//      address ad(get_app(), ip, port);
//      address local(this);
//      return open(ad, local, skip_socks);
//   }
//
//
//   bool tcp_socket_impl::open(in6_addr ip,::networking::port_t port,bool skip_socks)
//   {
//      address ad(get_app(), ip, port);
//      return open(ad, skip_socks);
//   }
//   */
//
//   bool tcp_socket_impl::open(::networking::address * ad,bool skip_socks)
//   {
//      //::networking::address bind_ad("0.0.0.0",0);
//      //return open(ad,bind_ad,skip_socks);
//
//      return false;
//   }
//
//
//   bool tcp_socket_impl::open(::networking::address * ad,::networking::address * bind_ad,bool skip_socks)
//   {
//      //return m_pimpl->open(ad, bind_ad, skip_socks);
//      //string strIp = ad.get_display_number();
//
//      //int iPort = ad.get_service_number();
//
//      //information() << "open address = " << strIp << ":" << iPort;
//
//      //if(!ad.is_valid())
//      //{
//
//
//      //   fatal() <<"open Invalid ::networking::address";
//
//      //   SetCloseAndDelete();
//
//      //   return false;
//
//      //}
//
//
//
//
////      if(socket_handler()->get_count() >= FD_SETSIZE)
////      {
////
////
////         fatal() <<log_this, "open",0,"no space left in fd_set";
////
////         SetCloseAndDelete();
////         return false;
////
////      }
//
//      //set_connecting(false);
//      //SetSocks4(false);
//
////      if(socket_handler()->PoolEnabled())
////      {
////
////         ::pointer<base_socket_handler::pool_socket>ppoolsocket = socket_handler()->FindConnection(SOCK_STREAM,"tcp",ad);
////
////         if(ppoolsocket)
////         {
////
////            CopyConnection(ppoolsocket);
////
////            SetIsClient();
////
////            SetCallOnConnect(); // base_socket_handler must call OnConnect
////
////            (*this)["from_pool"] = true;
////
////            INFO(log_this, "SetCallOnConnect",0,"Found pooled connection");
////
////            return true;
////
////         }
////
////      }
//
////      // if not, create new connection
////      socket_id s = CreateSocket(ad.get_family(),SOCK_STREAM,"tcp");
////      if(s == INVALID_SOCKET)
////      {
////         return false;
////      }
////      // socket must be nonblocking for async connect
////      if(!SetNonblocking(true,s))
////      {
////         SetCloseAndDelete();
////         ::closesocket(s);
////         return false;
////      }
////      SetIsClient(); // client because we connect
////      SetClientRemoteAddress(ad);
////      i32 n = 0;
////      if(bind_ad.get_service_number() != 0)
////      {
////         bind(s,bind_ad.sa(),bind_ad.sa_len());
////      }
////      in_addr addrSocks4 = GetSocks4Host();
////      if(!skip_socks && !__is_zero(addrSocks4) && GetSocks4Port())
////      {
////         
////         ::networking::address sa(GetSocks4Host(),GetSocks4Port());
////
////         {
////            
////            string sockshost;
////
////            auto paddressdepartment = ::networking::address_department();
////
////            paddressdepartment->convert(sockshost,GetSocks4Host());
////
////            information() << "open: is_connecting to socks4 server @ " << sockshost << ":" << GetSocks4Port();
////
////         }
////
////         SetSocks4();
////
////         n = connect(s,sa.sa(),sa.sa_len());
////
////         SetRemoteHostname(sa);
////
////      }
////      else
////      {
////         n = connect(s,ad.sa(),ad.sa_len());
////         SetRemoteHostname(ad);
////      }
////      if(n == -1)
////      {
////#ifdef _WIN32
////         // check error code that means a connect is in progress
////         i32 iError = ::WSAGetLastError();
////         if(iError == WSAEWOULDBLOCK || iError == 0)
////#else
////         i32 iError = Errno;
////         if(iError == EINPROGRESS)
////#endif
////         {
////            attach(s);
////            set_connecting(true); // this flag will control fd_set's
////         }
////         else if(Socks4() && socket_handler()->Socks4TryDirect()) // retry
////         {
////            ::closesocket(s);
////            return open(ad,true);
////         }
////         else if(Reconnect())
////         {
////            string strError = bsd_socket_error(iError);
////
////            information() << "connect: failed, reconnect pending " << iError << bsd_socket_error(iError);
////
////            attach(s);
////            set_connecting(true); // this flag will control fd_set's
////         }
////         else
////         {
////            string strError = bsd_socket_error(iError);
////
////            fatal() <<"connect: failed " << iError << bsd_socket_error(iError);
////
////            SetCloseAndDelete();
////            ::closesocket(s);
////            return false;
////         }
////      }
////      else
////      {
////         attach(s);
////         SetCallOnConnect(); // base_socket_handler must call OnConnect
////      }
////
////      // 'true' means connected or connecting(not yet connected)
////      // 'false' means something failed
//      //return true; //!is_connecting();
//
//return true;
//
//   }
//
//
//   bool tcp_socket_impl::open(const string &host,::networking::port_t port)
//   {
//
//      SetCloseAndDelete(false);
//
//      if(IsIpv6())
//      {
//
//         //auto paddressdepartment = ::networking::address_department();
//
//         ////if(!socket_handler()->ResolverEnabled() || paddressdepartment->isipv6(host))
//         //if(paddressdepartment->isipv6(host))
//         //{
//
//         //   in6_addr a;
//
//         //   if(!paddressdepartment->convert(a,host))
//         //   {
//
//         //      SetCloseAndDelete();
//
//         //      return false;
//
//         //   }
//
//         //   ::networking::address ad(a,port);
//
//         //   ::networking::address addrLocal;
//
//         //   if (!open(ad, addrLocal))
//         //   {
//
//         //      return false;
//
//         //   }
//
//         //   return true;
//
//         //}
//
//         ////m_resolver_id = Resolve6(host,port);
//
//         return true;
//
//      }
//
//      //auto paddressdepartment = ::networking::address_department();
//
//      ////if(!socket_handler()->ResolverEnabled() || paddressdepartment->isipv4(host))
//      /////if( paddressdepartment->isipv4(host))
//      //{
//
//      //   in_addr l;
//
//      //   if (!paddressdepartment->convert(l, host))
//      //   {
//      //      
//      //      warning() <<"paddressdepartment->convert failed";
//      //      
//      //      SetCloseAndDelete();
//      //      
//      //      return false;
//
//      //   }
//      //   
//      //   ::networking::address ad(l, port);
//      //   
//      //   ::networking::address addrLocal;
//
//      //   if (!open(ad, addrLocal))
//      //   {
//
//      //      return false;
//
//      //   }
//
//      //   return true;
//
//      //}
//
//      // resolve using async resolver thread
//
//      //m_resolver_id = Resolve(host,port);
//
//      return true;
//
//   }
//
//
////   void tcp_socket_impl::OnResolved(i32 atom,::networking::address * a)
////   {
////
////      auto paddressdepartment = ::networking::address_department();
////
////      informationf("OnResolved atom %d addr %s port %d\n",atom,paddressdepartment->canonical_name(a).c_str(),a.u.s.m_port);
////
////      if(atom == m_resolver_id)
////      {
////         if(a.is_valid() && a.u.s.m_port)
////         {
////            ::networking::address addrLocal;
////            if(open(a,addrLocal))
////            {
////               if(!socket_handler()->Valid(this))
////               {
////                  socket_handler()->add(this);
////               }
////            }
////         }
////         else
////         {
////
////            fatal() <<log_this, "OnResolved",0,"Resolver failed";
////
////            SetCloseAndDelete();
////         }
////      }
////      else
////      {
////
////         fatal() <<log_this, "OnResolved",atom,"Resolver returned wrong job atom";
////
////         SetCloseAndDelete();
////      }
////   }
//
//
//
//
//   int tcp_socket_impl::recv(void * buf, int nBufSize)
//   {
//      return -1;
////
////      int n = nBufSize;
////
////#ifdef HAVE_OPENSSL
////
////      if(IsSSL())
////      {
////
////         try
////         {
////
////            if (!Ready())
////            {
////
////               information() << "tcp_socket_impl::recv not ready";
////
////               return 0;
////
////            }
////
////            if (m_psslcontext->m_ssl == nullptr)
////            {
////
////               error() <<"tcp_socket_impl::recv(ssl)" << (int)n << "SSL context is nullptr";
////
////               information() << "tcp_socket_impl::recv ssl SSL context is nullptr(0)";
////
////               OnDisconnect();
////               SetCloseAndDelete(true);
////               SetFlushBeforeClose(false);
////               SetLost();
////
////            }
////            else
////            {
////
////               n = SSL_read(m_psslcontext->m_ssl, buf, (int)nBufSize);
////
////               if (n <= 0)
////               {
////                  n = SSL_get_error(m_psslcontext->m_ssl, (int)n);
////                  switch (n)
////                  {
////                  case SSL_ERROR_NONE:
////                  case SSL_ERROR_WANT_READ:
////                  case SSL_ERROR_WANT_WRITE:
////                     break;
////                  case SSL_ERROR_ZERO_RETURN:
////                     //if(SSL_m_psslcontext->m_pclientcontext->m_psslsession)
////                     information() << "SSL_read() returns zero - closing socket";
////                     OnDisconnect();
////                     SetCloseAndDelete(true);
////                     SetFlushBeforeClose(false);
////                     SetLost();
////                     break;
////                  case SSL_ERROR_SYSCALL:
////                     informationf("SSL read problem, errcode = %d (SSL_FORMATTED_ERROR_SYSCALL) errno = %d ", n , errno);
////                     OnDisconnect();
////                     SetCloseAndDelete(true);
////                     SetFlushBeforeClose(false);
////                     SetLost();
////                     break;
////                  default:
////                     informationf("SSL read problem, errcode = %d", n);
////                     OnDisconnect();
////                     SetCloseAndDelete(true);
////                     SetFlushBeforeClose(false);
////                     SetLost();
////                  }
////                  information() << "tcp_socket_impl::recv ssl error(1)";
////               }
////               //else if (!n)
////               //{
////               //   OnDisconnect();
////               //   SetCloseAndDelete(true);
////               //   SetFlushBeforeClose(false);
////               //   SetLost();
////               //   SetShutdownStatus(SHUT_WR);
////               //   //informationf("tcp_socket_impl::recv ssl disconnect(2)");
////
////               //}
////               else if (n > 0 && n <= nBufSize)
////               {
////                  set_connection_last_activity();
////                  return n;
////               }
////               else
////               {
////
////
////
////                  error() <<"tcp_socket_impl::recv(ssl) " <<  (int)n <<  " abnormal value from SSL_read";
////
////
////
////                  information() << "tcp_socket_impl::recv ssl abnormal value from SSL_read(3)";
////
////               }
////
////            }
////
////         }
////         catch(...)
////         {
////
////            OnDisconnect();
////            SetCloseAndDelete(true);
////            SetFlushBeforeClose(false);
////            SetLost();
////
////         }
////
////      }
////      else
////#endif // HAVE_OPENSSL
////      {
////#if defined(__APPLE__) || defined(SOLARIS)
////         //         n = (i32) recv(get_socket_id(), buf, nBufSize, SO_NOSIGPIPE);
////         n = (i32) ::recv(get_socket_id(),buf,nBufSize,0);
////
////#else
////         n = ::recv(get_socket_id(),(char *)buf,(int)nBufSize,MSG_NOSIGNAL);
////#endif
////         if(n == -1)
////         {
////
////            fatal() <<"recv " << Errno << bsd_socket_error(Errno);
////
////            OnDisconnect();
////            SetCloseAndDelete(true);
////            SetFlushBeforeClose(false);
////            SetLost();
////            information() << "tcp_socket_impl::recv (B1) recv errorf(" << bsd_socket_error(Errno) << ")";
////         }
////         else if(!n)
////         {
//////            i32 iError = get_error();
//////            #ifdef WINDOWS
//////            if (iError == WSAEWOULDBLOCK)
//////            #else
//////            #endif
//////            {
//////               informationf("tcp_socket_impl::recv 0 No Error or WOULD BLOCK");
//////            }
//////            else
////            {
////               information() << "tcp_socket_impl::recv (B2) recv disconnect";
////               OnDisconnect();
////               SetCloseAndDelete(true);
////               SetFlushBeforeClose(false);
////               SetLost();
////               SetShutdownStatus(SHUT_WR);
////            }
////
////         }
////         else if(n > 0 && n <= nBufSize)
////         {
////            set_connection_last_activity();
////            return n;
////         }
////         else
////         {
////
////
////
////            error() <<"tcp_socket_impl::recv " << (i32)n << " abnormal value from recv";
////
////
////
////            information() << "tcp_socket_impl::recv (B3) recv abnormal value from recv";
////
////         }
////
////      }
////
////      return n;
//
//   }
//
//
//   int tcp_socket_impl::read(void * buf, int nBufSize)
//   {
//
//      int n = (int) nBufSize;
//
//      n = recv(buf,nBufSize);
//
//      if(n > 0 && n <= nBufSize)
//      {
//
//         m_bytes_received += n;
//
//         if(GetTrafficMonitor())
//         {
//
//            GetTrafficMonitor()->write(buf,n);
//
//         }
//
//         if(!m_b_input_buffer_disabled)
//         {
//
//            try
//            {
//
//
//               ibuf.write(buf,n);
//
//            }
//            catch(...)
//            {
//
//
//               warning() << "tcp_socket_impl::read : ibuf overflow";
//
//
//            }
//         }
//
//      }
//      else if(n < 0)
//      {
//
//         error() <<"tcp_socket_impl::read " << (i32)n << " abnormal value from rcv";
//
//      }
//
//      return n;
//
//   }
//
//
//   void tcp_socket_impl::OnRead()
//   {
//
//      char * buf = (char *) m_memRead.get_data();
//
//      int n = 0;
//
//      try
//      {
//
//         n = read(buf,TCP_BUFSIZE_READ);
//
//      }
//      catch(...)
//      {
//
//         return;
//
//      }
//
//      on_read(buf,n);
//
//   }
//
//
//   void tcp_socket_impl::on_read(const void * buf, memsize n)
//   {
//
//
//      set_connection_last_activity();
//
//      // unbuffered
//      if(n > 0)
//      {
//
//         stream_socket::on_read(buf,n);
//
//      }
//
//      if(m_b_input_buffer_disabled)
//      {
//
//         return;
//
//      }
//
//
//      //// further processing: socks4
//      //if(Socks4())
//      //{
//
//      //   bool need_more = false;
//
//      //   while(GetInputLength() && !need_more && !IsCloseAndDelete())
//      //   {
//
//      //      need_more = OnSocks4Read();
//
//      //   }
//
//      //}
//
//   }
//
//
//   void tcp_socket_impl::OnWriteComplete()
//   {
//   }
//
//
//   void tcp_socket_impl::OnWrite()
//   {
//
//      //if (is_true("from_pool") && CallOnConnect())
//      //{
//
//      //   SetCallOnConnect(false);
//      //   SetConnected(true);
//      //   OnConnect();
//
//      //   return;
//      //}
//      //if(is_connecting())
//      //{
//      //   i32 err = SoError();
//
//      //   // don't reset connecting flag on error here, we want the OnConnectFailed timeout later on
//      //   if(!err) // ok
//      //   {
//      //      set(!IsDisableRead(),false);
//      //      set_connecting(false);
//      //      SetCallOnConnect();
//      //      return;
//      //   }
//
//      //   fatal() <<"tcp: connect failed " << err << bsd_socket_error(err);
//
//      //   set(false,false); // no more monitoring because connection failed
//
//      //   // failed
//      //   if(Socks4())
//      //   {
//      //      // %! leave 'is_connecting' flag set?
//      //      OnSocks4ConnectFailed();
//      //      return;
//      //   }
//
//      //   if(GetMaximumConnectionRetryCount() == -1 ||
//      //         (GetMaximumConnectionRetryCount() && GetConnectionRetryCount() < GetMaximumConnectionRetryCount()))
//      //   {
//      //      // even though the connection failed at once, only retry after
//      //      // the connection timeout.
//      //      // should we even try to connect again, when CheckConnect returns
//      //      // false it's because of a connection error - not a timeout...
//      //      return;
//      //   }
//      //   set_connecting(false);
//      //   SetCloseAndDelete(true);
//      //   /// \todo state reason why connect failed
//      //   OnConnectFailed();
//      //   return;
//      //}
//      //// try send next block in buffer
//      //// if full block is sent, repeat
//      //// if all blocks are sent, reset m_wfds
//
//      //bool repeat = false;
//      //memsize sz = m_transfer_limit ? GetOutputLength() : 0;
//      //do
//      //{
//      //   
//      //   auto it = m_obuf.begin();
//
//      //   if (!it)
//      //   {
//
//      //      return;
//
//      //   }
//
//      //   auto & poutput = *it;
//
//      //   repeat = false;
//
//      //   i32 n = (i32)try_write(poutput->Buf(), poutput->Len());
//
//      //   if(n > 0)
//      //   {
//
//      //      memsize left = poutput->erase(n);
//
//      //      m_output_length -= n;
//
//      //      if(!left)
//      //      {
//
//      //         erase(it);
//
//      //         if(!m_obuf.get_size())
//      //         {
//      //            
//      //            OnWriteComplete();
//
//      //         }
//      //         else
//      //         {
//      //            
//      //            repeat = true;
//
//      //         }
//
//      //      }
//
//      //   }
//
//      //}
//      //while(repeat);
//
//      //if(m_transfer_limit && sz > m_transfer_limit && GetOutputLength() < m_transfer_limit)
//      //{
//
//      //   OnTransferLimit();
//
//      //}
//
//      //// check output buffer set, set/reset m_wfds accordingly
//      //{
//      //   bool br;
//      //   bool bw;
//      //   bool bx;
//      //   socket_handler()->get(get_socket_id(),br,bw,bx);
//      //   if(m_obuf.get_size())
//      //      set(br,true);
//      //   else
//      //      set(br,false);
//      //}
//   }
//
//
//   int tcp_socket_impl::try_write(const void * buf,int len)
//   {
//
//      int n = 0;
//
////
////#ifdef HAVE_OPENSSL
////
////      if(IsSSL())
////      {
////
////         n = SSL_write(m_psslcontext->m_ssl,buf,(i32)len);
////
////         if(n == -1)
////         {
////            i32 errnr = SSL_get_error(m_psslcontext->m_ssl,(i32)n);
////            if(errnr != SSL_ERROR_WANT_READ && errnr != SSL_ERROR_WANT_WRITE)
////            {
////               if(errnr == SSL_ERROR_SYSCALL)
////               {
////                  int iError = errno;
////
////                  const ::scoped_string & scopedstrError = strerror(iError);
////                  information() << pszError;
////               }
////               OnDisconnect();
////               SetCloseAndDelete(true);
////               SetFlushBeforeClose(false);
////               SetLost();
////               const char *errbuf = ERR_error_string(errnr,nullptr);
////
////               fatal() <<"OnWrite / SSL_write " << errnr << errbuf;
////
////               //throw ::exception(io_exception(errbuf));
////            }
////            //return 0;
////         }
////         else if(!n)
////         {
////            OnDisconnect();
////            SetCloseAndDelete(true);
////            SetFlushBeforeClose(false);
////            SetLost();
////            i32 errnr = SSL_get_error(m_psslcontext->m_ssl,(i32)n);
////            const char *errbuf = ERR_error_string(errnr,nullptr);
////            information() << "SSL_write() returns 0: " << errnr << ", " << errbuf;
////            //throw ::exception(io_exception(errbuf));
////         }
////
////      }
////      else
////#endif // HAVE_OPENSSL
////      {
//////         retry:
////#if defined(__APPLE__)
////         int iSocket = get_socket_id();
////         n = (int) (::send(iSocket,buf,len,SO_NOSIGPIPE));
////#elif defined(SOLARIS)
////         n = ::send(get_socket_id(),(const char *)buf,(int)len,0);
////#else
////         n = ::send(get_socket_id(),(const char *)buf,(int)len,MSG_NOSIGNAL);
////#endif
////         if(n == -1)
////         {
////            int iError = Errno;
////            // normal error codes:
////            // WSAEWOULDBLOCK
////            //       EAGAIN or EWOULDBLOCK
////#ifdef _WIN32
////            if(iError != WSAEWOULDBLOCK) // 10035L
////#else
////            if(iError != EWOULDBLOCK)
////#endif
////            {
////
////               fatal() <<"send " << Errno << bsd_socket_error(Errno);
////
////               OnDisconnect();
////               SetCloseAndDelete(true);
////               SetFlushBeforeClose(false);
////               SetLost();
////               //throw ::exception(io_exception(bsd_socket_error(Errno)));
////            }
////            //else
////            //{
////            //   fd_set w;
////            //   fd_set e;
////            //   FD_ZERO(&e);
////            //   FD_ZERO(&w);
////            //   FD_SET(get_socket_id(), &e);
////            //   FD_SET(get_socket_id(), &w);
////            //   struct timeval tv;
////            //   tv.tv_sec = 1;
////            //   tv.tv_usec = 0;
////            //   ::select((int) (get_socket_id() + 1), nullptr, &w, &e, &tv);
////            //   goto retry;
////            //}
////
////            //return 0;
////         }
////      }
////      if(n > 0)
////      {
////         m_bytes_sent += n;
////         if(GetTrafficMonitor())
////         {
////            GetTrafficMonitor() -> write(buf,n);
////         }
////         set_connection_last_activity();
////      }
//      return (i32)n;
//   }
//
//
//   void tcp_socket_impl::buffer(const void * pdata,int len)
//   {
//
//      const char * buf = (const char *)pdata;
//
//      memsize ptr = 0;
//
//      m_output_length += len;
//
//      while(::comparison::lt(ptr, len))
//      {
//         // buf/len => pbuf/sz
//         i32 space = 0;
//         
//         if(m_obuf_top && (space = m_obuf_top -> Space()) > 0)
//         {
//            const char *pbuf = buf + ptr;
//            i32 sz = (i32)(len - ptr);
//            if(space >= sz)
//            {
//               m_obuf_top -> add(pbuf,sz);
//               ptr += sz;
//            }
//            else
//            {
//               m_obuf_top -> add(pbuf,space);
//               ptr += space;
//            }
//         }
//         else
//         {
//            
//            if (m_obuf_top)
//            {
//
//               m_obuf.add_tail(m_obuf_top);
//
//            }
//
//            m_obuf_top = __allocate< output >(TCP_OUTPUT_CAPACITY);
//
//         }
//
//      }
//
//   }
//
//
//   /*
//      void tcp_socket_impl::write(const string &str)
//      {
//         write(str,  (i32) str.length());
//      }
//   */
//
//   void tcp_socket_impl::write(const void * pdata,memsize len)
//   {
//
//      //const u8 * buf = (const u8 *)pdata;
//
//      //if(!Ready() && !is_connecting())
//      //{
//
//      //   warning() <<"write: Attempt to write to a non-ready socket"; // warning
//
//      //   if (get_socket_id() == INVALID_SOCKET)
//      //   {
//
//      //      information() << "write: * get_socket_id() == INVALID_SOCKET";
//
//
//      //   }
//      //   if (is_connecting())
//      //   {
//
//
//      //      information() << "write: * is_connecting()";
//
//      //   }
//      //   if (IsCloseAndDelete())
//      //   {
//
//
//      //      information() << "write: * IsCloseAndDelete()";
//
//
//
//      //   }
//      //   return;
//      //}
//      //if(!IsConnected())
//      //{
//
//
//      //   warning() <<"write: Attempt to write to a non-connected socket, will be sent on connect"; // warning
//
//      //   buffer(buf,(int) len);
//      //   return;
//      //}
//      //if(m_obuf_top)
//      //{
//      //   buffer(buf,(int) len);
//      //   return;
//      //}
//      //else
//      //{
//      //   i32 n = (i32)try_write(buf,(int) len);
//      //   if(n >= 0 && n < (i32)len)
//      //   {
//      //      buffer(buf + n,(int) (len - n));
//      //   }
//      //}
//      //// if ( data in buffer || !IsConnected )
//      //// {
//      ////   add to buffer
//      //// }
//      //// else
//      //// try_send
//      //// if any data is unsent, buffer it and set m_wfds
//
//      //// check output buffer set, set/reset m_wfds accordingly
//      //{
//      //   bool br;
//      //   bool bw;
//      //   bool bx;
//      //   socket_handler()->get(get_socket_id(),br,bw,bx);
//      //   if(m_obuf.get_size())
//      //      set(br,true);
//      //   else
//      //      set(br,false);
//      //}
//   }
//
//
//   void tcp_socket_impl::OnLine(const string &)
//   {
//   }
//
//
//
//   //void tcp_socket_impl::OnSocks4Connect()
//   //{
//   //   char request[1000];
//   //   memory_set(request,0,sizeof(request));
//   //   request[0] = 4; // socks v4
//   //   request[1] = 1; // command code: CONNECT
//   //   {
//   //      ::networking::address ad = GetClientRemoteAddress();
//   //      if(ad.is_valid())
//   //      {
//   //         struct sockaddr * psockaddr = (struct sockaddr *)ad.sa();
//   //         struct sockaddr_in *psockaddrin = (struct sockaddr_in *)psockaddr;
//   //         if(psockaddrin->sin_family == AF_INET)
//   //         {
//   //            ::memory_copy(request + 2,&psockaddrin->sin_port,2); // nwbo is ok here
//   //            ::memory_copy(request + 4,&psockaddrin->sin_addr,sizeof(struct in_addr));
//   //         }
//   //         else
//   //         {
//   //            /// \todo warn
//   //         }
//   //      }
//   //      else
//   //      {
//   //         /// \todo warn
//   //      }
//   //   }
//   //   strcpy(request + 8,GetSocks4Userid());
//   //   ::count length = GetSocks4Userid().get_length() + 8 + 1;
//   //   write(request,length);
//   //   m_socks4_state = 0;
//   //}
//
//
//   //void tcp_socket_impl::OnSocks4ConnectFailed()
//   //{
//
//
//   //   warning() <<"OnSocks4ConnectFailed: connection to socks4 server failed, trying direct connection";
//
//
//   //   if(!socket_handler()->Socks4TryDirect())
//   //   {
//   //      set_connecting(false);
//   //      SetCloseAndDelete();
//   //      OnConnectFailed(); // just in case
//   //   }
//   //   else
//   //   {
//   //      SetRetryClientConnect();
//   //   }
//   //}
//
//
//   //bool tcp_socket_impl::OnSocks4Read()
//   //{
//   //   switch(m_socks4_state)
//   //   {
//   //   case 0:
//   //      ibuf.read(&m_socks4_vn,1);
//   //      m_socks4_state = 1;
//   //      break;
//   //   case 1:
//   //      ibuf.read(&m_socks4_cd,1);
//   //      m_socks4_state = 2;
//   //      break;
//   //   case 2:
//   //      if(GetInputLength() > 1)
//   //      {
//   //         ibuf.read((char *)&m_socks4_dstport,2);
//   //         m_socks4_state = 3;
//   //      }
//   //      else
//   //      {
//   //         return true;
//   //      }
//   //      break;
//   //   case 3:
//   //      if(GetInputLength() > 3)
//   //      {
//   //         ibuf.read((char *)&m_socks4_dstip,4);
//   //         SetSocks4(false);
//
//   //         switch(m_socks4_cd)
//   //         {
//   //         case 90:
//   //            OnConnect();
//
//
//   //            information() << "OnSocks4Read: Connection established";
//
//   //            break;
//   //         case 91:
//   //         case 92:
//   //         case 93:
//
//
//   //            fatal() <<"OnSocks4Read: socks4 server reports connect failed";
//
//   //            set_connecting(false);
//   //            SetCloseAndDelete();
//   //            OnConnectFailed();
//   //            break;
//   //         default:
//
//
//   //            fatal() <<"OnSocks4Read: socks4 server unrecognized response";
//
//   //            SetCloseAndDelete();
//   //            break;
//   //         }
//   //      }
//   //      else
//   //      {
//   //         return true;
//   //      }
//   //      break;
//   //   }
//   //   return false;
//   //}
//
//
//
//
//   void tcp_socket_impl::OnSSLConnect()
//   {
//
//      SetNonblocking(true);
//
//      //synchronous_lock slMap(psystem->sockets().m_clientcontextmap.m_pmutex);
//
//      if (is_true("from_pool"))
//         return;
//
//      //{
//
//      //   if(m_ssl_ctx)
//      //   {
//
//      //      informationf("SSL Context already initialized - closing socket");
//
//      //      SetCloseAndDelete(true);
//
//      //      return;
//
//      //   }
//
//      //   InitSSLClient();
//
//      //}
//
////      if(!m_ssl_ctx)
//      //    {
//
//      int iError = 0;
//
////retry_init_ssl_client:
//
//      InitSSLClient();
//
//      //  }
//
//      //slMap.unlock();
//
//      //if(m_psslcontext->m_pclientcontext.is_set()
//      //      && m_psslcontext->m_pclientcontext->m_psslcontext != nullptr)
//      //{
//
//      //   /* Connect the SSL socket */
//
//      //   m_psslcontext->m_ssl = SSL_new(m_psslcontext->m_pclientcontext->m_psslcontext);
//
//      //   if(!m_psslcontext->m_ssl)
//      //   {
//
//      //      information() << "m_ssl is nullptr";
//
//      //      SetCloseAndDelete(true);
//
//      //      return;
//
//      //   }
//
//      //   if (m_bClientSessionSet || m_psslcontext->m_pclientcontext->m_psslsession == nullptr)
//      //   {
//
//      //      if (m_strTlsHostName.has_char())
//      //      {
//
//      //         SSL_set_tlsext_host_name(m_psslcontext->m_ssl, (char *)(const char *)m_strTlsHostName);
//
//      //      }
//
//      //      //SSL_set_mode(m_ssl, SSL_MODE_AUTO_RETRY);
//
//      //   }
//
//      //   m_psslcontext->m_sbio = BIO_new_socket((i32)get_socket_id(),BIO_NOCLOSE);
//
//      //   if(!m_psslcontext->m_sbio)
//      //   {
//
//      //      information() << "m_sbio is nullptr";
//
//      //      SetCloseAndDelete(true);
//
//      //      return;
//
//      //   }
//
//      //   SSL_set_bio(m_psslcontext->m_ssl,m_psslcontext->m_sbio,m_psslcontext->m_sbio);
//
//
//      //   if(!SSLNegotiate())
//      //   {
//
//      //      SetSSLNegotiate();
//
//      //   }
//
//      //}
//      //else
//      //{
//
//      //   SetCloseAndDelete();
//
//      //}
//
//   }
//
//
//   void tcp_socket_impl::OnSSLAccept()
//   {
//
//      SetNonblocking(true);
//
//      //synchronous_lock slMap(psystem->sockets().m_servercontextmap.m_pmutex);
//
//      //{
//      //   if(m_psslcontext.is_set()
//      //         && m_psslcontext->m_pclientcontext.is_set()
//      //         && m_psslcontext->m_pclientcontext->m_psslcontext != nullptr)
//      //   {
//      //      information() << "SSL Context already initialized - closing socket";
//      //      SetCloseAndDelete(true);
//      //      return;
//      //   }
//      //   InitSSLServer();
//      //   SetSSLServer();
//      //}
//
//
//      //synchronous_lock synchronouslock(m_pmutexSslCtx);
//
//      //slMap.unlock();
//
//
//      //if(m_psslcontext->m_pclientcontext->m_psslcontext)
//      //{
//      //   m_psslcontext->m_ssl = SSL_new(m_psslcontext->m_pclientcontext->m_psslcontext);
//      //   if(!m_psslcontext->m_ssl)
//      //   {
//      //      information() << "m_ssl is nullptr";
//      //      SetCloseAndDelete(true);
//      //      return;
//      //   }
//      //   SSL_set_app_data2(m_psslcontext->m_ssl, this);
//      //   //SSL_set_mode(m_psslcontext->m_ssl,SSL_MODE_AUTO_RETRY);
//      //   m_psslcontext->m_sbio = BIO_new_socket((i32)get_socket_id(),BIO_NOCLOSE);
//      //   if(!m_psslcontext->m_sbio)
//      //   {
//      //      information() << "m_sbio is nullptr";
//      //      SetCloseAndDelete(true);
//      //      return;
//      //   }
//      //   SSL_set_bio(m_psslcontext->m_ssl,m_psslcontext->m_sbio,m_psslcontext->m_sbio);
//      //   //      if (!SSLNegotiate())
//      //   {
//      //      SetSSLNegotiate();
//      //   }
//      //}
//   }
//
//
//   bool tcp_socket_impl::SSLNegotiate()
//   {
//
//      //if(!IsSSLServer()) // client
//      //{
//
//      //   information() << "SSLNegotiate: SSL_connect";
//
//      //   if (m_bReuseSession && !m_bClientSessionSet && m_psslcontext->m_pclientcontext->m_psslsession != nullptr)
//      //   {
//
//      //      SSL_set_session(m_psslcontext->m_ssl, m_psslcontext->m_pclientcontext->m_psslsession);
//
//      //      m_bClientSessionSet = true;
//
//      //   }
//
//      //   i32 r = SSL_connect(m_psslcontext->m_ssl);
//
//      //   if(r > 0)
//      //   {
//
//      //      SetSSLNegotiate(false);
//
//      //      if (SSL_session_reused(m_psslcontext->m_ssl))
//      //      {
//
//      //         information() << "REUSED SESSION";
//
//      //      }
//      //      else
//      //      {
//
//      //         information() << "NEW SESSION";
//
//      //      }
//
//      //      long x509_err = cert_common_name_check(m_strHost);
//
//      //      if(x509_err != X509_V_OK
//      //            && x509_err != X509_V_ERR_SELF_SIGNED_CERT_IN_CHAIN
//      //            && x509_err != X509_V_ERR_UNABLE_TO_GET_ISSUER_CERT_LOCALLY)
//      //      {
//
//
//      //         information() << "SSLNegotiate/cert_common_name_check: cert_common_name_check failed (error=" << x509_err << ",url=" << m_strUrl << ")";
//
//      //         SetSSLNegotiate(false);
//      //         SetCloseAndDelete();
//      //         OnSSLConnectFailed();
//      //         return false;
//
//      //      }
//
//      //      if (m_bReuseSession)
//      //      {
//
//      //         if (m_psslcontext && m_psslcontext->m_pclientcontext && m_psslcontext->m_pclientcontext->m_psslsession)
//      //         {
//
//      //            destroy_ssl_session();
//
//      //         }
//
//      //         if (!m_psslcontext || !m_psslcontext->m_pclientcontext || !m_psslcontext->m_pclientcontext->m_psslsession)
//      //         {
//
//      //            get_ssl_session();
//
//      //         }
//
//      //      }
//
//      //      /// \todo: resurrect certificate check... client
//      //      //         CheckCertificateChain( "");//ServerHOST);
//      //      SetNonblocking(false);
//      //      //
//      //      {
//      //         SetConnected();
//      //         if(GetOutputLength())
//      //         {
//      //            OnWrite();
//      //         }
//      //      }
//      //      if(IsReconnect())
//      //         OnReconnect();
//      //      else
//      //      {
//      //         OnConnect();
//      //      }
//
//
//      //      information() << "SSLNegotiate/SSL_connect: Connection established";
//
//      //      return true;
//
//      //   }
//      //   else if(!r)
//      //   {
//
//      //      long error = ERR_get_error();
//      //      const char* error_str = ERR_error_string(error, nullptr);
//      //      warning() <<"could not SSL_connect: " << error_str;
//
//      //      int iErrorSsl = SSL_get_error(m_psslcontext->m_ssl,r);
//
//      //      //if(m_spsslclientcontext.is_set() &&
//      //      if (m_psslcontext->m_pclientcontext->m_psslcontext != nullptr &&
//      //            iErrorSsl == SSL_ERROR_ZERO_RETURN
//      //            && (m_psslcontext->m_pclientcontext->m_psslmethod == TLS_client_method()))
//      //      {
//
//      //         warning() <<"ssl_error_zero_return";
//
//      //      }
//
//      //      else
//      //      {
//
//      //         if (m_bReuseSession)
//      //         {
//
//      //            if (m_psslcontext->m_pclientcontext->m_psslsession != nullptr)
//      //            {
//
//      //               if (m_psslcontext->m_iSslCtxRetry == 0)
//      //               {
//
//      //                  m_psslcontext->m_iSslCtxRetry = 1;
//
//      //                  destroy_ssl_session();
//
//      //                  SSL_clear(m_psslcontext->m_ssl);
//
//      //               }
//      //               else
//      //               {
//
//      //                  m_psslcontext->m_iSslCtxRetry = 0;
//
//      //               }
//
//      //            }
//
//      //         }
//
//      //         if (m_psslcontext->m_iSslCtxRetry == 0)
//      //         {
//
//      //            information() << "SSLNegotiate/SSL_connect: Connection failed";
//
//      //            SetSSLNegotiate(false);
//      //            SetCloseAndDelete();
//      //            OnSSLConnectFailed();
//
//      //         }
//
//      //      }
//
//      //   }
//      //   else
//      //   {
//      //      r = SSL_get_error(m_psslcontext->m_ssl,r);
//      //      if(r == SSL_ERROR_WANT_READ || r == SSL_ERROR_WANT_WRITE)
//      //      {
//      //      }
//      //      else if(r == SSL_ERROR_WANT_CONNECT || r == SSL_ERROR_WANT_ACCEPT)
//      //      {
//      //      }
//      //      else
//      //      {
//
//      //         char msg[1024];
//
//      //         ERR_error_string_n(ERR_get_error(), msg, sizeof(msg));
//
//      //         if (r == SSL_ERROR_SYSCALL)
//      //         {
//
//      //            auto last_error = networking_last_error();
//
//      //            // informationf("");
//      //          
//      //         }
//
//
//      //         information() << "SSLNegotiate: SSL_connect() failed";
//
//      //         SetSSLNegotiate(false);
//      //         SetCloseAndDelete(true);
//      //         OnSSLConnectFailed();
//      //      }
//      //   }
//      //}
//      //else // server
//      //{
//      //   i32 r = SSL_accept(m_psslcontext->m_ssl);
//      //   int iError = Errno;
//      //   if(r > 0)
//      //   {
//      //      SetSSLNegotiate(false);
//      //      /// \todo: resurrect certificate check... server
//      //      //         CheckCertificateChain( "");//ClientHOST);
//      //      SetNonblocking(false);
//      //      //
//      //      {
//      //         SetConnected();
//      //         if(GetOutputLength())
//      //         {
//      //            OnWrite();
//      //         }
//      //      }
//      //      OnAccept();
//
//
//      //      information() << "SSLNegotiate/SSL_accept: Connection established";
//
//      //      return true;
//
//      //   }
//      //   else if(!r)
//      //   {
//
//
//      //      information() << "SSLNegotiate/SSL_accept: Connection failed";
//
//      //      SetSSLNegotiate(false);
//      //      SetCloseAndDelete();
//      //      OnSSLAcceptFailed();
//      //   }
//      //   else
//      //   {
//      //      r = SSL_get_error(m_psslcontext->m_ssl,r);
//      //      if(r == SSL_ERROR_WANT_READ || r == SSL_ERROR_WANT_WRITE)
//      //      {
//      //      }
//      //      else if(r == SSL_ERROR_WANT_CONNECT || r == SSL_ERROR_WANT_ACCEPT)
//      //      {
//      //      }
//      //      else
//      //      {
//
//
//      //         if (r == SSL_ERROR_SYSCALL)
//      //         {
//      //            
//      //            error() <<"SSL_ERROR_SYSCALL: Errno = " << iError;
//
//      //         }
//
//      //         information() << "SSLNegotiate " << r << " SSL_accept() failed";
//
//
//      //         SetSSLNegotiate(false);
//      //         SetCloseAndDelete(true);
//      //         OnSSLAcceptFailed();
//      //      }
//      //   }
//      //}
//      return false;
//   }
//
//
//   void tcp_socket_impl::InitSSLClient()
//   {
//      //InitializeContext(m_strInitSSLClientContext,SSLv23_method());
//      //InitializeContext(m_strInitSSLClientContext,TLSv1_client_method());
//
//      //InitializeContext(m_strInitSSLClientContext,TLS_client_method());
//
//   }
//
//
//   void tcp_socket_impl::InitSSLServer()
//   {
//
//
//      fatal() <<"InitSSLServer: You MUST implement your own InitSSLServer method";
//
//      SetCloseAndDelete();
//   }
//
//
//   //void tcp_socket_impl::InitializeContext(const string & context, const SSL_METHOD * pmethod)
//   //{
//
//   //   auto psystem = system()->m_papexsystem;
//
//   //   ssl_client_context_map & clientcontextmap = psystem->sockets().m_clientcontextmap;
//
//   //   ::pointer<ssl_client_context>psslclientcontext = clientcontextmap.get_context(context, pmethod);
//
//   //   m_psslcontext = __allocate< ssl_context >();
//
//   //   m_psslcontext->m_pclientcontext = psslclientcontext;
//
//   //}
//
//
////   void tcp_socket_impl::InitializeContext(const string & context,const string & keyfile,const string & password,const SSL_METHOD *meth_in)
////   {
////
////      if (m_psslcontext.is_null())
////      {
////
////         m_psslcontext = __allocate< ssl_context >();
////
////      }
////
////      if (m_psslcontext->m_pclientcontext.is_null())
////      {
////
////         m_psslcontext->m_pclientcontext = __allocate(ssl_client_context(meth_in != nullptr ? meth_in : TLS_server_method()));
////
////         m_psslcontext->m_pclientcontext->initialize(get_app());
////
////      }
////
////      //m_psslcontext->m_pclientcontext->m_psslcontext = SSL_CTX_new(m_psslcontext->m_pclientcontext->m_psslmethod);
////      SSL_CTX_set_mode(m_psslcontext->m_pclientcontext->m_psslcontext, SSL_MODE_AUTO_RETRY | SSL_MODE_RELEASE_BUFFERS) ;
////      SSL_CTX_set_options(m_psslcontext->m_pclientcontext->m_psslcontext, SSL_OP_NO_COMPRESSION | SSL_CTX_get_options(m_psslcontext->m_pclientcontext->m_psslcontext));
////      // session atom
////      int iSetSessionResult = -1;
////      u32 uSessionIdMaxLen = SSL_MAX_SSL_SESSION_ID_LENGTH;
////      if (context.get_length())
////         iSetSessionResult = SSL_CTX_set_session_id_context(m_psslcontext->m_pclientcontext->m_psslcontext, (const uchar *)(const  char *)context, minimum((u32)context.get_length(), uSessionIdMaxLen));
////      else
////         iSetSessionResult = SSL_CTX_set_session_id_context(m_psslcontext->m_pclientcontext->m_psslcontext, (const uchar *)"--is_empty--", 9);
////
////      if (keyfile.case_insensitive_begins("cat://") || keyfile.case_insensitive_ends(".cat"))
////      {
////
////         string strCert;
////
////         if (keyfile.case_insensitive_ends(".cat"))
////         {
////
////            strCert = file()->as_string(keyfile);
////
////         }
////         else
////         {
////
////            strCert = keyfile;
////
////            strCert.case_insensitive_begins_eat("cat://");
////
////         }
////
////         BIO *bio;
////
////         bio = BIO_new(BIO_s_mem());
////         BIO_puts(bio, strCert);
////
////
////            //if (!(SSL_CTX_use_RSAPrivateKey(m_psslcontext->m_pclientcontext->m_psslcontext, key)))
////            //{
////
////            //   errorf("tcp_socket_impl InitializeContext,0,Couldn't read private key file %s e_trace_level_fatal", keyfile.c_str());
////
////            //}
////
////
////         //}
////
////           // {
////
////         X509 * certificate;
////
////         certificate = PEM_read_bio_X509(bio, nullptr, nullptr, nullptr);
////
////         if (certificate)
////         {
////
////            //            if (!SSL_CTX_use_certificate(m_psslcontext->m_pclientcontext->m_psslcontext, certificate))
////
////                     //}
////
////            m_password = password;
////            SSL_CTX_set_default_passwd_cb(m_psslcontext->m_pclientcontext->m_psslcontext, tcp_socket_SSL_password_cb);
////            SSL_CTX_set_default_passwd_cb_userdata(m_psslcontext->m_pclientcontext->m_psslcontext, (socket *)this);
////            EVP_PKEY * key = PEM_read_bio_PrivateKey(bio, nullptr, nullptr, nullptr);
////            array < X509 * > xa;
////            if (key)
////            {
////
////               STACK_OF(X509) * pchain = nullptr;
////
////               while (true)
////               {
////
////                  X509 * chainItem = PEM_read_bio_X509(bio, nullptr, nullptr, nullptr);
////
////                  if (!chainItem)
////                  {
////
////                     break;
////
////                  }
////
////                  xa.add(chainItem);
////
////                  if (pchain == nullptr)
////                  {
////
////                     pchain = sk_X509_new_null();
////
////                  }
////
////                  sk_X509_push(pchain, chainItem);
////
////               }
////
////#if OPENSSL_VERSION_NUMBER >= 0x10101000L 
////
////               if (!SSL_CTX_use_cert_and_key(m_psslcontext->m_pclientcontext->m_psslcontext, certificate, key, pchain, 1))
////               {
////
////                  fatal() <<"tcp_socket_impl InitializeContext,-1,Couldn't read certificate string " << keyfile;
////
////               }
////
////#else
////
////               if (!SSL_CTX_use_certificate(m_psslcontext->m_pclientcontext->m_psslcontext, certificate))
////               {
////
////                  fatal() <<"tcp_socket_impl InitializeContext: Couldn't read certificate string " << keyfile;
////
////               }
////
////               if (!SSL_CTX_use_PrivateKey(m_psslcontext->m_pclientcontext->m_psslcontext, key))
////               {
////
////                  fatal() <<"tcp_socket_impl InitializeContext: Couldn't read certificate string " << keyfile;
////
////               }
////
////               for (auto x : xa)
////               {
////
////                  if (!SSL_CTX_add_extra_chain_cert(m_psslcontext->m_pclientcontext->m_psslcontext, x))
////                  {
////
////                     fatal() <<"tcp_socket_impl InitializeContext: Couldn't read certificate string " + keyfile;
////
////                  }
////
////               }
////
////#endif
////
////               if(pchain != nullptr)
////               {
////
////                  sk_X509_free(pchain);
////                  
////               }
////
////               EVP_PKEY_free(key);
////
////            }
////
////            X509_free(certificate);
////
////         }
////
////
////         BIO_free(bio);
////
////      }
////      else
////      {
////         if (!SSL_CTX_use_certificate_chain_file(m_psslcontext->m_pclientcontext->m_psslcontext, keyfile))
////         {
////            /* Load our keys and certificates*/
////            if (!(SSL_CTX_use_certificate_file(m_psslcontext->m_pclientcontext->m_psslcontext, keyfile, SSL_FILETYPE_PEM)))
////            {
////               fatal() <<"tcp_socket_impl InitializeContext: Couldn't read certificate file " << keyfile;
////            }
////         }
////         m_password = password;
////         SSL_CTX_set_default_passwd_cb(m_psslcontext->m_pclientcontext->m_psslcontext, tcp_socket_SSL_password_cb);
////         SSL_CTX_set_default_passwd_cb_userdata(m_psslcontext->m_pclientcontext->m_psslcontext, (socket *) this);
////
////         if (!(SSL_CTX_use_PrivateKey_file(m_psslcontext->m_pclientcontext->m_psslcontext, keyfile, SSL_FILETYPE_PEM)))
////         {
////
////            fatalf("tcp_socket_impl InitializeContext: Couldn't read private key file %s ", keyfile.c_str());
////
////         }
////
////      }
////
////
////      {
////         synchronous_lock synchronouslock(this->synchronization());
////         int i;
////
////         auto psystem = system()->m_papexsystem;
////
////         int cnt = sizeof(psystem->sockets().m_baTicketKey) / SSL_SESSION_TICKET_KEY_SIZE;
////         m_ticketkeya.set_size(cnt);
////         int j;
////         for (i = 0; i < cnt; ++i)
////         {
////            j = (SSL_SESSION_TICKET_KEY_SIZE * i);
////            ::memory_copy(m_ticketkeya[i].key_name, psystem->sockets().m_baTicketKey + j, 16);
////            ::memory_copy(m_ticketkeya[i].hmac_key, psystem->sockets().m_baTicketKey + j + 16, 16);
////            ::memory_copy(m_ticketkeya[i].aes_key, psystem->sockets().m_baTicketKey + j + 32, 16);
////         }
////      }
////
////#if OPENSSL_VERSION_NUMBER >= 0x30000000
////
////      SSL_CTX_set_tlsext_ticket_key_evp_cb(m_psslcontext->m_pclientcontext->m_psslcontext, &ssl_tlsext_ticket_key_evp_cb);
////
////#else
////
////      SSL_CTX_set_tlsext_ticket_key_cb(m_psslcontext->m_pclientcontext->m_psslcontext, ssl_tlsext_ticket_key_cb);
////
////#endif
////
////   }
//
//
//   //void tcp_socket_impl::InitializeContext(const string & context,const string & certfile,const string & keyfile,const string & password,const SSL_METHOD *meth_in)
//   //{
//
//   //   /* create our context*/
//   //   m_psslcontext->m_pclientcontext->m_psslmethod = meth_in != nullptr ? meth_in : TLS_client_method();
//   //   m_psslcontext->m_pclientcontext->m_psslcontext = SSL_CTX_new(m_psslcontext->m_pclientcontext->m_psslmethod);
//   //   SSL_CTX_set_mode(m_psslcontext->m_pclientcontext->m_psslcontext, SSL_MODE_AUTO_RETRY | SSL_MODE_RELEASE_BUFFERS);
//   //   SSL_CTX_set_options(m_psslcontext->m_pclientcontext->m_psslcontext, SSL_OP_NO_COMPRESSION | SSL_CTX_get_options(m_psslcontext->m_pclientcontext->m_psslcontext));
//   //   // session atom
//   //   if (context.get_length())
//   //      SSL_CTX_set_session_id_context(m_psslcontext->m_pclientcontext->m_psslcontext, (const uchar *)(const  char *)context, (u32)context.get_length());
//   //   else
//   //      SSL_CTX_set_session_id_context(m_psslcontext->m_pclientcontext->m_psslcontext, (const uchar *)"--is_empty--", 9);
//
//   //   /* Load our keys and certificates*/
//   //   if (!(SSL_CTX_use_certificate_file(m_psslcontext->m_pclientcontext->m_psslcontext, certfile, SSL_FILETYPE_PEM)))
//   //   {
//   //      fatal() <<"InitializeContext: Couldn't read certificate file " << keyfile;
//   //   }
//
//   //   m_password = password;
//   //   SSL_CTX_set_default_passwd_cb(m_psslcontext->m_pclientcontext->m_psslcontext, tcp_socket_SSL_password_cb);
//   //   SSL_CTX_set_default_passwd_cb_userdata(m_psslcontext->m_pclientcontext->m_psslcontext, (socket *) this);
//   //   if (!(SSL_CTX_use_PrivateKey_file(m_psslcontext->m_pclientcontext->m_psslcontext, keyfile, SSL_FILETYPE_PEM)))
//   //   {
//   //      fatal() <<"InitializeContext: Couldn't read private key file " << keyfile;
//   //      //information(string("tcp_socket_impl InitializeContext(2),0,Couldn't read private key file ") + keyfile + string("e_trace_level_fatal"));
//   //   }
//
//   //}
//
//
//   //i32 tcp_socket_SSL_password_cb(char *buf,i32 num,i32 rwflag,void *userdata)
//   //{
//
//   //   UNREFERENCED_PARAMETER(rwflag);
//
//   //   socket * psocket = static_cast<socket *>(userdata);
//
//   //   tcp_socket_impl * ptcpsocket = dynamic_cast<tcp_socket_impl *>(psocket);
//
//   //   string strPassword = ptcpsocket ? ptcpsocket->GetPassword().c_str() : "";
//
//   //   if(num < strPassword.length() + 1)
//   //   {
//
//   //      return 0;
//
//   //   }
//
//   //   strcpy(buf, strPassword);
//
//   //   return (i32)strPassword.length();
//
//   //}
//
//
//   void tcp_socket_impl::close()
//   {
//      m_pimpl->close();
//
////      if (get_socket_id() == INVALID_SOCKET) // this could happen
////      {
////
////
////         warning() <<"socket::close: file descriptor invalid";
////
////         return;
////
////      }
////
////      i32 n;
////
////      SetNonblocking(true);
////
////      if (!Lost() && IsConnected() && !(GetShutdownStatus() & SHUT_WR))
////      {
////
////         if (shutdown(get_socket_id(), SHUT_WR) == -1)
////         {
////
////            // failed...
////
////
////            error() <<"shutdown " << Errno << bsd_socket_error(Errno);
////
////
////
////         }
////
////      }
////
////      char tmp[1000];
////
////      if (!Lost() && (n = (i32) ::recv(get_socket_id(), tmp, 1000, 0)) >= 0)
////      {
////
////         if (n)
////         {
////
////
////            warning() <<"read() after shutdown: bytes read";
////
////         }
////
////      }
////
////#ifdef HAVE_OPENSSL
////
////      m_psslcontext.release();
////
////#endif
////
////      socket::close();
//
//   }
//
//
//
////#ifdef HAVE_OPENSSL
////   SSL_CTX *tcp_socket_impl::GetSslContext()
////   {
////      if (!m_psslcontext->m_pclientcontext->m_psslcontext)
////      {
////
////
////         warning() <<"GetSslContext: SSL Context is nullptr; check InitSSLServer/InitSSLClient";
////
////      }
////      return m_psslcontext->m_pclientcontext->m_psslcontext;
////   }
////
////   SSL *tcp_socket_impl::GetSsl()
////   {
////      if (!m_psslcontext->m_ssl)
////      {
////
////
////         warning() <<"GetSsl: SSL is nullptr; check InitSSLServer/InitSSLClient";
////
////      }
////      return m_psslcontext->m_ssl;
////   }
////#endif
////
////
//   void tcp_socket_impl::SetReconnect(bool bReconnect)
//   {
//      //m_bReconnect = bReconnect;
//
//      m_pimpl->m_bReconnect;
//   }
//
//
//   void tcp_socket_impl::OnRawData(char * buf_in, memsize len)
//   {
//
//      socket::OnRawData(buf_in,len);
//
//   }
//
//
//   memsize tcp_socket_impl::GetInputLength()
//   {
//      return (memsize)ibuf.get_length();
//   }
//
//
//   memsize tcp_socket_impl::GetOutputLength()
//   {
//      return m_output_length;
//   }
//
//
//   u64 tcp_socket_impl::GetBytesReceived(bool clear)
//   {
//      u64 z = m_bytes_received;
//      if(clear)
//         m_bytes_received = 0;
//      return z;
//   }
//
//
//   u64 tcp_socket_impl::GetBytesSent(bool clear)
//   {
//      u64 z = m_bytes_sent;
//      if(clear)
//         m_bytes_sent = 0;
//      return z;
//   }
//
//
//   bool tcp_socket_impl::Reconnect()
//   {
//      return m_bReconnect;
//   }
//
//
//   void tcp_socket_impl::SetIsReconnect(bool bTryingReconnect)
//   {
//
//      m_bTryingReconnect = bTryingReconnect;
//
//   }
//
//
//   bool tcp_socket_impl::IsReconnect()
//   {
//
//      return m_bTryingReconnect;
//
//   }
//
//
//   string tcp_socket_impl::GetPassword()
//   {
//
//      //return m_password;
//
//      return m_ptcpsocketComposite->GetPassword();
//
//   }
//
//
//   void tcp_socket_impl::DisableInputBuffer(bool x)
//   {
//
//      m_b_input_buffer_disabled = x;
//
//   }
//
//
////   void tcp_socket_impl::OnOptions(i32 family,i32 type,i32 protocol,socket_id s)
////   {
////
////      UNREFERENCED_PARAMETER(family);
////      UNREFERENCED_PARAMETER(type);
////      UNREFERENCED_PARAMETER(protocol);
////      UNREFERENCED_PARAMETER(s);
////      //informationf("socket::OnOptions()");
////#ifdef SO_NOSIGPIPE
////      SetSoNosigpipe(true);
////#endif
////      SetSoReuseaddr(true);
////      SetSoKeepalive(true);
////   }
//
//
//   void tcp_socket_impl::SetLineProtocol(bool x)
//   {
//      stream_socket::SetLineProtocol(x);
//      DisableInputBuffer(x);
//   }
//
//
//   bool tcp_socket_impl::SetTcpNodelay(bool x)
//   {
//#ifdef TCP_NODELAY
//      i32 optval = x ? 1 : 0;
//      if(setsockopt(get_socket_id(),IPPROTO_TCP,TCP_NODELAY,(char *)&optval,sizeof(optval)) == -1)
//      {
//
//
//         fatal() <<"setsockopt(IPPROTO_TCP, TCP_NODELAY) " << Errno << bsd_socket_error(Errno);
//
//         return false;
//      }
//      return true;
//#else
//
//      information() << "socket option not available: TCP_NODELAY";
//
//      return false;
//#endif
//   }
//
//
//   void tcp_socket_impl::on_connection_timeout()
//   {
//
//      fatal() <<"connect: connect timeout";
//
//      m_estatus = error_connection_timed_out;
//
//      //if(Socks4())
//      //{
//
//      //   OnSocks4ConnectFailed();
//      //   // retry direct connection
//      //}
//      //else if(GetMaximumConnectionRetryCount() == -1 ||
//      //        (GetMaximumConnectionRetryCount() && GetConnectionRetryCount() < GetMaximumConnectionRetryCount()))
//      //{
//
//      //   IncrementConnectionRetryCount();
//
//      //   // ask socket via OnConnectRetry callback if we should continue trying
//      //   if(OnConnectRetry())
//      //   {
//
//      //      SetRetryClientConnect();
//
//      //   }
//      //   else
//      //   {
//
//      //      SetCloseAndDelete(true);
//
//      //      /// \todo state reason why connect failed
//      //      OnConnectFailed();
//
//      //   }
//
//      //}
//      //else
//      //{
//
//      //   SetCloseAndDelete(true);
//      //   /// \todo state reason why connect failed
//      //   OnConnectFailed();
//
//      //}
//      //
//      //set_connecting(false);
//
//   }
//
//
//#ifdef _WIN32
//
//
//   void tcp_socket_impl::OnException()
//   {
//
//      if(is_connecting())
//      {
//
//         //i32 iError = this->socket_handler()->m_iSelectErrno;
//
//         //if(iError == ETIMEDOUT)
//         //{
//
//         //   m_estatus = error_connection_timed_out;
//
//         //}
//         //else
//         //{
//         //   //m_estatus = status_failed;
//         //}
//
//         //int iGetConnectionRetry = GetMaximumConnectionRetryCount();
//
//         //int iGetConnectionRetries = GetConnectionRetryCount();
//
//         //if (Socks4())
//         //{
//
//         //   OnSocks4ConnectFailed();
//
//         //}
//         //else if(iGetConnectionRetry == -1 ||
//         //        (iGetConnectionRetry &&
//         //           iGetConnectionRetries < iGetConnectionRetry))
//         //{
//
//         //   const int nBufSize = 1024;
//
//         //   char buf[nBufSize];
//
//         //   socket_id iGetSocket = get_socket_id();
//
//         //   int n = ::recv(iGetSocket, (char*)buf, (int)nBufSize, MSG_OOB);
//
//         //   information() << "got " << n << " bytes of Out of Band Data";
//
//         //   // even though the connection failed at once, only retry after
//         //   // the connection timeout
//         //   // should we even try to connect again, when CheckConnect returns
//         //   // false it's because of a connection error - not a timeout...
//         //}
//         //else
//         //{
//         //   set_connecting(false); // tnx snibbe
//         //   SetCloseAndDelete();
//         //   OnConnectFailed();
//         //}
//         return;
//      }
//      //// %! exception doesn't always mean something bad happened, this code should be reworked
//      //// errno valid here?
//      //i32 err = SoError();
//
//      //fatal() <<"exception on select " << err << bsd_socket_error(err);
//
//      SetCloseAndDelete();
//   }
//
//
//#endif // _WIN32
//
//
//   i32 tcp_socket_impl::Protocol()
//   {
//
//      //return IPPROTO_TCP;
//
//      return 0;
//
//   }
//
//
//   void tcp_socket_impl::SetTransferLimit(memsize sz)
//   {
//
//      m_transfer_limit = sz;
//
//   }
//
//
//   void tcp_socket_impl::OnTransferLimit()
//   {
//
//   }
//
//
//   string tcp_socket_impl::get_url()
//   {
//
//      return m_strUrl;
//
//   }
//
//
//   string tcp_socket_impl::get_short_description()
//   {
//
//      return get_url();
//
//   }
//
//
//   long tcp_socket_impl::cert_common_name_check(const ::string & common_name)
//   {
//
////      if(!m_bCertCommonNameCheckEnabled)
////      {
////
////         return X509_V_OK;
////
////      }
////
////      ::X509 *cert = nullptr;
////
////      ::X509_name_st *topic = nullptr;
////
////#if OPENSSL_VERSION_NUMBER >= 0x30000000L
////
////      cert = SSL_get1_peer_certificate(m_psslcontext->m_ssl);
////
////#else
////
////      cert = SSL_get_peer_certificate(m_psslcontext->m_ssl);
////
////#endif
////
////      bool ok = false;
////
////      if(cert != nullptr && strlen(common_name) > 0)
////      {
////
////         char data[256];
////
////         if((topic = X509_get_subject_name(cert)) != nullptr && X509_NAME_get_text_by_NID(topic,NID_commonName,data,256) > 0)
////         {
////
////            data[255] = 0;
////
////            if(ansi_count_compare_ci(data,common_name,255) == 0)
////            {
////
////               ok = true;
////
////            }
////            else
////            {
////
////               string str = data;
////
////               if(str.begins_eat("*."))
////               {
////
////                  string strCommon = common_name;
////
////                  if(strCommon == str)
////                  {
////
////                     ok = true;
////
////                  }
////                  else
////                  {
////
////                     auto pFind = strCommon.find('.');
////
////                     if(::is_set(pFind))
////                     {
////
////                        if(str == strCommon(pFind + 1))
////                        {
////
////                           ok = true;
////
////                        }
////
////                     }
////
////                  }
////
////               }
////
////            }
////
////         }
////
////         if (!ok)
////         {
////
////            int i;
////
////            int san_names_nb = -1;
////
////            STACK_OF(GENERAL_NAME) *san_names = nullptr;
////
////            // Try to extract the names within the SAN extension from the certificate
////            san_names = (STACK_OF(GENERAL_NAME) *) X509_get_ext_d2i((X509 *)cert, NID_subject_alt_name, nullptr, nullptr);
////
////            if (san_names == nullptr)
////            {
////
////            }
////            else
////            {
////
////               san_names_nb = sk_GENERAL_NAME_num(san_names);
////
////               // Check each name within the extension
////               for (i = 0; i < san_names_nb; i++)
////               {
////
////                  const GENERAL_NAME *current_name = sk_GENERAL_NAME_value(san_names, i);
////
////                  if (current_name->type == GEN_DNS)
////                  {
////                     // Current name is a DNS name, let's check it
////
////#if (defined(LINUX)) && (OPENSSL_API_COMPAT < 0x10100000L)
////
////                     string strDnsName((const char *)ASN1_STRING_data(current_name->d.dNSName), ASN1_STRING_length(current_name->d.dNSName));
////
////#else
////
////                     string strDnsName((const char *)ASN1_STRING_get0_data(current_name->d.dNSName), ASN1_STRING_length(current_name->d.dNSName));
////
////#endif
////
////                     if(strDnsName.case_insensitive_order(common_name) == 0)
////                     {
////
////                        ok = true;
////
////                        break;
////
////                     }
////                     else
////                     {
////
////                        string str = strDnsName;
////
////                        if (str.begins_eat("*."))
////                        {
////
////                           string strCommon = common_name;
////
////                           if (strCommon == str)
////                           {
////
////                              ok = true;
////
////                              break;
////
////                           }
////                           else
////                           {
////
////                              auto pFind = strCommon.find('.');
////
////                              if (::is_set(pFind))
////
////                              {
////                                 if (str == strCommon(pFind + 1))
////                                 {
////
////                                    ok = true;
////
////                                    break;
////
////                                 }
////
////                              }
////
////                           }
////
////                        }
////
////                     }
////
////                  }
////
////               }
////
////               sk_GENERAL_NAME_pop_free(san_names, GENERAL_NAME_free);
////
////            }
////
////         }
////
////      }
////
////      if(cert)
////      {
////
////         X509_free(cert);
////
////      }
////
////      if(ok)
////      {
////
////         return SSL_get_verify_result(m_psslcontext->m_ssl);
////
////      }
////
////      return X509_V_ERR_APPLICATION_VERIFICATION;
//
//      return 0;
//
//   }
//
//
//   void tcp_socket_impl::enable_cert_common_name_check(bool bEnable)
//   {
//
//      m_bCertCommonNameCheckEnabled = bEnable;
//
//   }
//
//
//   string tcp_socket_impl::get_connect_host()
//   {
//
//      return m_strConnectHost;
//
//   }
//
//
//   ::networking::port_t tcp_socket_impl::get_connect_port()
//   {
//
//      return m_iConnectPort;
//
//   }
//
//
//   void tcp_socket_impl::InitializeContextTLSClientMethod()
//   {
//
////#if defined(HAVE_OPENSSL)
////
////      InitializeContext("", TLS_client_method());
////
////#endif
//
//   }
//
//
//} // namespace sockets
//
//
////
////#ifdef WINDOWS
////
////
////i64 networking_last_error()
////{
////
////   return WSAGetLastError();
////
////}
////
////
////#else
////
////
////i64 networking_last_error()
////{
////
////   return errno;
////
////}
////
////
////#endif
//
//
//
