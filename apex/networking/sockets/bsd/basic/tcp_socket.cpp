#include "framework.h"
#include "apex/networking/sockets/_sockets.h"


#ifdef PARALLELIZATION_PTHREAD


#include "acme/node/operating_system/ansi/_pthread.h"


#endif


#include <openssl/ssl.h>
#include <openssl/safestack.h>
#include <openssl/x509v3.h>
#include <openssl/rsa.h>


#ifdef LINUX
#undef USE_MISC
#include <unistd.h>
#endif


#include <fcntl.h>
//#include <assert.h>
#include <openssl/rand.h>
#include <openssl/err.h>
#include <openssl/evp.h>

static int SSL_app_data2_idx = -1;
static int SSL_app_data3_idx = -1;



void SSL_init_app_data2_3_idx(void)
{
   int i;

   if (SSL_app_data2_idx > -1)
   {
      return;
   }

   /* we _do_ need to call this twice */
   for (i = 0; i <= 1; i++)
   {
      SSL_app_data2_idx =
      SSL_get_ex_new_index(0,
                           (void *) "Second papplication Data for SSL",
                           nullptr, nullptr, nullptr);
   }

   if (SSL_app_data3_idx > -1)
   {
      return;
   }

   SSL_app_data3_idx =
   SSL_get_ex_new_index(0,
                        (void *) "Third papplication Data for SSL",
                        nullptr, nullptr, nullptr);

}
void *SSL_get_app_data2(SSL *ssl)
{
   return (void *)SSL_get_ex_data(ssl, SSL_app_data2_idx);
}

void SSL_set_app_data2(SSL *ssl, void *arg)
{
   SSL_set_ex_data(ssl, SSL_app_data2_idx, (char *)arg);
   return;
}





static int current_session_key(::sockets::tcp_socket * c, ssl_ticket_key *key)
{
   int result = false;
   synchronous_lock synchronouslock(c->mutex());
   if (c->m_ticketkeya.has_elements())
   {
      *key = c->m_ticketkeya.first();
      result = true;
   }
   //apr_thread_rwlock_unlock(c->::mutex);
   return result;
}
static int find_session_key(::sockets::tcp_socket *c, unsigned char key_name[16], ssl_ticket_key *key, int *is_current_key)
{
   int result = false;
   synchronous_lock synchronouslock(c->mutex());
   for (auto & ticketkey : c->m_ticketkeya)
   {
      // Check if we have a match for tickets.
      if (__memcmp(ticketkey.key_name, key_name, 16) == 0)
      {
         *key = ticketkey;
         result = true;
         *is_current_key = &c->m_ticketkeya.first() == &ticketkey;
         break;
      }
   }
   return result;
}

static int ssl_tlsext_ticket_key_cb(SSL *s, unsigned char key_name[16], unsigned char *iv, EVP_CIPHER_CTX *ctx, HMAC_CTX *hctx, int enc)
{
   ::sockets::tcp_socket *c = (::sockets::tcp_socket *) SSL_get_app_data2(s);
   ssl_ticket_key key;
   int is_current_key;
   if (enc)   /* create new session */
   {
      if (current_session_key(c, &key))
      {
         if (RAND_bytes(iv, EVP_MAX_IV_LENGTH) <= 0)
         {
            return -1; /* insufficient random */
         }
         ::memcpy_dup(key_name, key.key_name, 16);
         EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), nullptr, key.aes_key, iv);
         HMAC_Init_ex(hctx, key.hmac_key, 16, EVP_sha256(), nullptr);
         return 1;
      }
      // No ticket configured
      return 0;
   }
   else   /* retrieve session */
   {
      if (find_session_key(c, key_name, &key, &is_current_key))
      {
         HMAC_Init_ex(hctx, key.hmac_key, 16, EVP_sha256(), nullptr);
         EVP_DecryptInit_ex(ctx, EVP_aes_128_cbc(), nullptr, key.aes_key, iv);
         if (!is_current_key)
         {
            return 2;
         }
         return 1;
      }
      // No ticket
      return 0;
   }
}

#ifndef ETIMEDOUT
#define ETIMEDOUT       138
#endif

#if defined(LINUX)
#include <signal.h>
#undef USE_MISC

#endif


namespace sockets
{

#ifdef MACOS
   bool tcp_socket::s_bReuseSession = false;
#else
   bool tcp_socket::s_bReuseSession = true;
#endif

#ifdef LINUX
   // ssl_sigpipe_handle ---------------------------------------------------------
   void ssl_sigpipe_handle(int x);
#endif

   //
   //#define DEB(x) x
   //#else
   //#define DEB(x)
   //#endif


   // statics
#ifdef HAVE_OPENSSL
   //SSLInitializer tcp_socket::m_ssl_init;
#endif


// thanks, q
#ifdef _MSC_VER
#pragma warning(disable:4355)
#endif
   tcp_socket::tcp_socket():
      //::object(&h),
      //base_socket(h),
      //socket(h),
      //stream_socket(h)
      //,
      ibuf(TCP_BUFSIZE_READ)
      ,m_b_input_buffer_disabled(false)
      ,m_bytes_sent(0)
      ,m_bytes_received(0)
      ,m_transfer_limit(0)
      ,m_output_length(0)
      ,m_socks4_state(0)
      ,m_resolver_id(0)
      ,m_bReconnect(false)
      ,m_bTryingReconnect(false)
   {
      m_bReuseSession = s_bReuseSession;
      SSL_init_app_data2_3_idx();
      m_bClientSessionSet = false;
      m_memRead.set_size(TCP_BUFSIZE_READ + 1);
      m_bCertCommonNameCheckEnabled = true;
      //m_pmutexSslCtx = nullptr;
   }
#ifdef _MSC_VER
#pragma warning(default:4355)
#endif


#ifdef _MSC_VER
#pragma warning(disable:4355)
#endif
   tcp_socket::tcp_socket(memsize isize,memsize osize):
      //::object(&h),
  //    base_socket(h),
//      socket(h),
//      stream_socket(h),
      ibuf(isize)
      ,m_b_input_buffer_disabled(false)
      ,m_bytes_sent(0)
      ,m_bytes_received(0)
      ,m_transfer_limit(0)
      ,m_output_length(0)
      ,m_socks4_state(0)
      ,m_resolver_id(0)
      ,m_bReconnect(false)
      ,m_bTryingReconnect(false)
   {
      m_bReuseSession = s_bReuseSession;
      SSL_init_app_data2_3_idx();
      m_bClientSessionSet = false;
      m_memRead.set_size(TCP_BUFSIZE_READ + 1);
      m_bCertCommonNameCheckEnabled = true;
      //m_pmutexSslCtx = nullptr;
      UNREFERENCED_PARAMETER(osize);
   }
#ifdef _MSC_VER
#pragma warning(default:4355)
#endif


   tcp_socket::~tcp_socket()
   {

      if(m_socket != INVALID_SOCKET) // this could happen
      {

         close();

      }


   }


   /*
   bool tcp_socket::open(in_addr ip,port_t port,bool skip_socks)
   {
      address ad(get_application(), ip, port);
      address local(this);
      return open(ad, local, skip_socks);
   }


   bool tcp_socket::open(in6_addr ip,port_t port,bool skip_socks)
   {
      address ad(get_application(), ip, port);
      return open(ad, skip_socks);
   }
   */

   bool tcp_socket::open(const ::net::address & ad,bool skip_socks)
   {
      ::net::address bind_ad("0.0.0.0",0);
      return open(ad,bind_ad,skip_socks);
   }


   bool tcp_socket::open(const ::net::address & ad,const ::net::address & bind_ad,bool skip_socks)
   {

      string strIp = ad.get_display_number();

      int iPort = ad.get_service_number();

      INFO(log_this, "open", 0, "address = " + strIp + ":" + __str(iPort));

      if(!ad.is_valid())
      {


         FATAL(log_this, "open", 0, "Invalid ::net::address");

         SetCloseAndDelete();

         return false;

      }

//      if(socket_handler()->get_count() >= FD_SETSIZE)
//      {
//
//
//         FATAL(log_this, "open",0,"no space left in fd_set");
//
//         SetCloseAndDelete();
//         return false;
//
//      }

      set_connecting(false);
      SetSocks4(false);

//      if(socket_handler()->PoolEnabled())
//      {
//
//         __pointer(base_socket_handler::pool_socket) ppoolsocket = socket_handler()->FindConnection(SOCK_STREAM,"tcp",ad);
//
//         if(ppoolsocket)
//         {
//
//            CopyConnection(ppoolsocket);
//
//            SetIsClient();
//
//            SetCallOnConnect(); // base_socket_handler must call OnConnect
//
//            (*this)["from_pool"] = true;
//
//            INFO(log_this, "SetCallOnConnect",0,"Found pooled connection");
//
//            return true;
//
//         }
//
//      }

      // if not, create new connection
      SOCKET s = CreateSocket(ad.get_family(),SOCK_STREAM,"tcp");
      if(s == INVALID_SOCKET)
      {
         return false;
      }
      // socket must be nonblocking for async connect
      if(!SetNonblocking(true,s))
      {
         SetCloseAndDelete();
         ::closesocket(s);
         return false;
      }
      SetIsClient(); // client because we connect
      SetClientRemoteAddress(ad);
      i32 n = 0;
      if(bind_ad.get_service_number() != 0)
      {
         bind(s,bind_ad.sa(),bind_ad.sa_len());
      }
      in_addr addrSocks4 = GetSocks4Host();
      if(!skip_socks && !__is_zero(addrSocks4) && GetSocks4Port())
      {
         
         ::net::address sa(GetSocks4Host(),GetSocks4Port());

         {
            
            string sockshost;

            auto paddressdepartment = ::net::address_department();

            paddressdepartment->convert(sockshost,GetSocks4Host());

            INFO(log_this, "open",0,"is_connecting to socks4 server @ " + sockshost + ":" + __str(GetSocks4Port()));

         }

         SetSocks4();

         n = connect(s,sa.sa(),sa.sa_len());

         SetRemoteHostname(sa);

      }
      else
      {
         n = connect(s,ad.sa(),ad.sa_len());
         SetRemoteHostname(ad);
      }
      if(n == -1)
      {
#ifdef _WIN32
         // check error code that means a connect is in progress
         i32 iError = ::WSAGetLastError();
         if(iError == WSAEWOULDBLOCK || iError == 0)
#else
         i32 iError = Errno;
         if(iError == EINPROGRESS)
#endif
         {
            attach(s);
            set_connecting(true); // this flag will control fd_set's
         }
         else if(Socks4() && socket_handler()->Socks4TryDirect()) // retry
         {
            ::closesocket(s);
            return open(ad,true);
         }
         else if(Reconnect())
         {
            string strError = bsd_socket_error(iError);

            INFO(log_this, "connect: failed, reconnect pending",iError,bsd_socket_error(iError));

            attach(s);
            set_connecting(true); // this flag will control fd_set's
         }
         else
         {
            string strError = bsd_socket_error(iError);

            FATAL(log_this, "connect: failed",iError,bsd_socket_error(iError));

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
      return true; //!is_connecting();
   }


   bool tcp_socket::open(const string &host,port_t port)
   {

      SetCloseAndDelete(false);

      if(IsIpv6())
      {

         auto paddressdepartment = ::net::address_department();

         //if(!socket_handler()->ResolverEnabled() || paddressdepartment->isipv6(host))
         if(paddressdepartment->isipv6(host))
         {

            in6_addr a;

            if(!paddressdepartment->convert(a,host))
            {

               SetCloseAndDelete();

               return false;

            }

            ::net::address ad(a,port);

            ::net::address addrLocal;

            if (!open(ad, addrLocal))
            {

               return false;

            }

            return true;

         }

         //m_resolver_id = Resolve6(host,port);

         return true;

      }

      auto paddressdepartment = ::net::address_department();

      //if(!socket_handler()->ResolverEnabled() || paddressdepartment->isipv4(host))
      ///if( paddressdepartment->isipv4(host))
      {

         in_addr l;

         if (!paddressdepartment->convert(l, host))
         {
            
            WARN("paddressdepartment->convert failed");
            
            SetCloseAndDelete();
            
            return false;

         }
         
         ::net::address ad(l, port);
         
         ::net::address addrLocal;

         if (!open(ad, addrLocal))
         {

            return false;

         }

         return true;

      }

      // resolve using async resolver thread

      //m_resolver_id = Resolve(host,port);

      return true;

   }


//   void tcp_socket::OnResolved(i32 id,const ::net::address & a)
//   {
//
//      auto paddressdepartment = ::net::address_department();
//
//      INFO("OnResolved id %d addr %s port %d\n",id,paddressdepartment->canonical_name(a).c_str(),a.u.s.m_port);
//
//      if(id == m_resolver_id)
//      {
//         if(a.is_valid() && a.u.s.m_port)
//         {
//            ::net::address addrLocal;
//            if(open(a,addrLocal))
//            {
//               if(!socket_handler()->Valid(this))
//               {
//                  socket_handler()->add(this);
//               }
//            }
//         }
//         else
//         {
//
//            FATAL(log_this, "OnResolved",0,"Resolver failed");
//
//            SetCloseAndDelete();
//         }
//      }
//      else
//      {
//
//         FATAL(log_this, "OnResolved",id,"Resolver returned wrong job id");
//
//         SetCloseAndDelete();
//      }
//   }




   int tcp_socket::recv(void * buf, int nBufSize)
   {

      int n = nBufSize;

#ifdef HAVE_OPENSSL

      if(IsSSL())
      {

         try
         {

            if (!Ready())
            {

               TRACE("tcp_socket::recv not ready");
               return 0;

            }

            if (m_psslcontext->m_ssl == nullptr)
            {



               ERR("tcp_socket::recv(ssl)", (int)n, "SSL context is nullptr");



               TRACE("tcp_socket::recv ssl SSL context is nullptr(0)");

               OnDisconnect();
               SetCloseAndDelete(true);
               SetFlushBeforeClose(false);
               SetLost();

            }
            else
            {

               n = SSL_read(m_psslcontext->m_ssl, buf, (int)nBufSize);

               if (n <= 0)
               {
                  n = SSL_get_error(m_psslcontext->m_ssl, (int)n);
                  switch (n)
                  {
                  case SSL_ERROR_NONE:
                  case SSL_ERROR_WANT_READ:
                  case SSL_ERROR_WANT_WRITE:
                     break;
                  case SSL_ERROR_ZERO_RETURN:
                     //if(SSL_m_psslcontext->m_pclientcontext->m_psslsession)
                     TRACE("SSL_read() returns zero - closing socket\n");
                     OnDisconnect();
                     SetCloseAndDelete(true);
                     SetFlushBeforeClose(false);
                     SetLost();
                     break;
                  case SSL_ERROR_SYSCALL:
                     TRACE("SSL read problem, errcode = %d (SSL_ERROR_SYSCALL) errno = %d \n", n, errno);
                     OnDisconnect();
                     SetCloseAndDelete(true);
                     SetFlushBeforeClose(false);
                     SetLost();
                     break;
                  default:
                     TRACE("SSL read problem, errcode = %d\n", n);
                     OnDisconnect();
                     SetCloseAndDelete(true);
                     SetFlushBeforeClose(false);
                     SetLost();
                  }
                  TRACE("tcp_socket::recv ssl error(1)");
               }
               //else if (!n)
               //{
               //   OnDisconnect();
               //   SetCloseAndDelete(true);
               //   SetFlushBeforeClose(false);
               //   SetLost();
               //   SetShutdownStatus(SHUT_WR);
               //   //TRACE("tcp_socket::recv ssl disconnect(2)");

               //}
               else if (n > 0 && n <= nBufSize)
               {
                  return n;
               }
               else
               {



                  ERR("tcp_socket::recv(ssl)", (int)n, "abnormal value from SSL_read");



                  TRACE("tcp_socket::recv ssl abnormal value from SSL_read(3)");

               }

            }

         }
         catch(...)
         {

            OnDisconnect();
            SetCloseAndDelete(true);
            SetFlushBeforeClose(false);
            SetLost();

         }

      }
      else
#endif // HAVE_OPENSSL
      {
#if defined(__APPLE__) || defined(SOLARIS)
         //         n = (i32) recv(GetSocket(), buf, nBufSize, SO_NOSIGPIPE);
         n = (i32) ::recv(GetSocket(),buf,nBufSize,0);

#else
         n = ::recv(GetSocket(),(char *)buf,(int)nBufSize,MSG_NOSIGNAL);
#endif
         if(n == -1)
         {

            FATAL(log_this, "recv",Errno,bsd_socket_error(Errno));

            OnDisconnect();
            SetCloseAndDelete(true);
            SetFlushBeforeClose(false);
            SetLost();
            TRACE("tcp_socket::recv (B1) recv error(" + string(bsd_socket_error(Errno)) + ")");
         }
         else if(!n)
         {
//            i32 iError = get_error();
//            #ifdef WINDOWS
//            if (iError == WSAEWOULDBLOCK)
//            #else
//            #endif
//            {
//               TRACE("tcp_socket::recv 0 No Error or WOULD BLOCK");
//            }
//            else
            {
               TRACE("tcp_socket::recv (B2) recv disconnect");
               OnDisconnect();
               SetCloseAndDelete(true);
               SetFlushBeforeClose(false);
               SetLost();
               SetShutdownStatus(SHUT_WR);
            }

         }
         else if(n > 0 && n <= nBufSize)
         {
            return n;
         }
         else
         {



            ERR("tcp_socket::recv",(i32)n,"abnormal value from recv");



            TRACE("tcp_socket::recv (B3) recv abnormal value from recv");

         }

      }

      return n;

   }


   int tcp_socket::read(void * buf, int nBufSize)
   {

      int n = (int) nBufSize;

      n = recv(buf,nBufSize);

      if(n > 0 && n <= nBufSize)
      {

         m_bytes_received += n;

         if(GetTrafficMonitor())
         {

            GetTrafficMonitor()->write(buf,n);

         }

         if(!m_b_input_buffer_disabled)
         {

            try
            {


               ibuf.write(buf,n);

            }
            catch(...)
            {


               WARN("tcp_socket::read",0,"ibuf overflow");


            }
         }

      }
      else if(n < 0)
      {



         ERR("tcp_socket::read",(i32)n,"abnormal value from rcv");



      }

      return n;

   }

   void tcp_socket::OnRead()
   {

      char *buf = (char *) m_memRead.get_data();


      int n = 0;

      try
      {

         n = read(buf,TCP_BUFSIZE_READ);

      }
      catch(...)
      {

         return;

      }

      on_read(buf,n);

   }


   void tcp_socket::on_read(const void * buf, memsize n)
   {

      // unbuffered
      if(n > 0)
      {

         stream_socket::on_read(buf,n);

      }

      if(m_b_input_buffer_disabled)
      {

         return;

      }


      // further processing: socks4
      if(Socks4())
      {

         bool need_more = false;

         while(GetInputLength() && !need_more && !IsCloseAndDelete())
         {

            need_more = OnSocks4Read();

         }

      }

   }


   void tcp_socket::OnWriteComplete()
   {
   }


   void tcp_socket::OnWrite()
   {

      if (is_true("from_pool") && CallOnConnect())
      {

         SetCallOnConnect(false);
         SetConnected(true);
         OnConnect();

         return;
      }
      if(is_connecting())
      {
         i32 err = SoError();

         // don't reset connecting flag on error here, we want the OnConnectFailed timeout later on
         if(!err) // ok
         {
            set(!IsDisableRead(),false);
            set_connecting(false);
            SetCallOnConnect();
            return;
         }

         FATAL(log_this, "tcp: connect failed",err,bsd_socket_error(err));

         set(false,false); // no more monitoring because connection failed

         // failed
         if(Socks4())
         {
            // %! leave 'is_connecting' flag set?
            OnSocks4ConnectFailed();
            return;
         }

         if(GetMaximumConnectionRetryCount() == -1 ||
               (GetMaximumConnectionRetryCount() && GetConnectionRetryCount() < GetMaximumConnectionRetryCount()))
         {
            // even though the connection failed at once, only retry after
            // the connection timeout.
            // should we even try to connect again, when CheckConnect returns
            // false it's because of a connection error - not a timeout...
            return;
         }
         set_connecting(false);
         SetCloseAndDelete(true);
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
         
         auto it = m_obuf.begin();

         if (!it)
         {

            return;

         }

         auto & poutput = *it;

         repeat = false;

         i32 n = (i32)try_write(poutput->Buf(), poutput->Len());

         if(n > 0)
         {

            memsize left = poutput->erase(n);

            m_output_length -= n;

            if(!left)
            {

               erase(it);

               if(!m_obuf.get_size())
               {
                  
                  OnWriteComplete();

               }
               else
               {
                  
                  repeat = true;

               }

            }

         }

      }
      while(repeat);

      if(m_transfer_limit && sz > m_transfer_limit && GetOutputLength() < m_transfer_limit)
      {

         OnTransferLimit();

      }

      // check output buffer set, set/reset m_wfds accordingly
      {
         bool br;
         bool bw;
         bool bx;
         socket_handler()->get(GetSocket(),br,bw,bx);
         if(m_obuf.get_size())
            set(br,true);
         else
            set(br,false);
      }
   }


   int tcp_socket::try_write(const void * buf,int len)
   {

      int n = 0;

#ifdef HAVE_OPENSSL

      if(IsSSL())
      {

         n = SSL_write(m_psslcontext->m_ssl,buf,(i32)len);

         if(n == -1)
         {
            i32 errnr = SSL_get_error(m_psslcontext->m_ssl,(i32)n);
            if(errnr != SSL_ERROR_WANT_READ && errnr != SSL_ERROR_WANT_WRITE)
            {
               if(errnr == SSL_ERROR_SYSCALL)
               {
                  int iError = errno;

                  const char * pszError = strerror(iError);
                  TRACE(pszError);
               }
               OnDisconnect();
               SetCloseAndDelete(true);
               SetFlushBeforeClose(false);
               SetLost();
               const char *errbuf = ERR_error_string(errnr,nullptr);

               FATAL(log_this, "OnWrite/SSL_write",errnr,errbuf);

               //__throw(io_exception(errbuf));
            }
            //return 0;
         }
         else if(!n)
         {
            OnDisconnect();
            SetCloseAndDelete(true);
            SetFlushBeforeClose(false);
            SetLost();
            i32 errnr = SSL_get_error(m_psslcontext->m_ssl,(i32)n);
            const char *errbuf = ERR_error_string(errnr,nullptr);
            TRACE("SSL_write() returns 0: %d : %s\n",errnr,errbuf);
            //__throw(io_exception(errbuf));
         }
      }
      else
#endif // HAVE_OPENSSL
      {
//         retry:
#if defined(__APPLE__)
         int iSocket = GetSocket();
         n = (int) (::send(iSocket,buf,len,SO_NOSIGPIPE));
#elif defined(SOLARIS)
         n = ::send(GetSocket(),(const char *)buf,(int)len,0);
#else
         n = ::send(GetSocket(),(const char *)buf,(int)len,MSG_NOSIGNAL);
#endif
         if(n == -1)
         {
            int iError = Errno;
            // normal error codes:
            // WSAEWOULDBLOCK
            //       EAGAIN or EWOULDBLOCK
#ifdef _WIN32
            if(iError != WSAEWOULDBLOCK) // 10035L
#else
            if(iError != EWOULDBLOCK)
#endif
            {

               FATAL(log_this, "send",Errno,bsd_socket_error(Errno));

               OnDisconnect();
               SetCloseAndDelete(true);
               SetFlushBeforeClose(false);
               SetLost();
               //__throw(io_exception(bsd_socket_error(Errno)));
            }
            //else
            //{
            //   fd_set w;
            //   fd_set e;
            //   FD_ZERO(&e);
            //   FD_ZERO(&w);
            //   FD_SET(GetSocket(), &e);
            //   FD_SET(GetSocket(), &w);
            //   struct timeval tv;
            //   tv.tv_sec = 1;
            //   tv.tv_usec = 0;
            //   ::select((int) (GetSocket() + 1), nullptr, &w, &e, &tv);
            //   goto retry;
            //}

            //return 0;
         }
      }
      if(n > 0)
      {
         m_bytes_sent += n;
         if(GetTrafficMonitor())
         {
            GetTrafficMonitor() -> write(buf,n);
         }
      }
      return (i32)n;
   }


   void tcp_socket::buffer(const void * pdata,int len)
   {

      const char * buf = (const char *)pdata;

      memsize ptr = 0;

      m_output_length += len;

      while(::comparison::lt(ptr, len))
      {
         // buf/len => pbuf/sz
         i32 space = 0;
         
         if(m_obuf_top && (space = m_obuf_top -> Space()) > 0)
         {
            const char *pbuf = buf + ptr;
            i32 sz = (i32)(len - ptr);
            if(space >= sz)
            {
               m_obuf_top -> add(pbuf,sz);
               ptr += sz;
            }
            else
            {
               m_obuf_top -> add(pbuf,space);
               ptr += space;
            }
         }
         else
         {
            
            if (m_obuf_top)
            {

               m_obuf.add_tail(m_obuf_top);

            }

            m_obuf_top = __new(output(TCP_OUTPUT_CAPACITY));

         }

      }

   }


   /*
      void tcp_socket::write(const string &str)
      {
         write(str,  (i32) str.get_length());
      }
   */

   void tcp_socket::write(const void * pdata,memsize len)
   {

      const u8 * buf = (const u8 *)pdata;

      if(!Ready() && !is_connecting())
      {

         WARN(log_this, "write",-1,"Attempt to write to a non-ready socket"); // warning

         if (GetSocket() == INVALID_SOCKET)
         {

            INFO(log_this, "write", 0, " * GetSocket() == INVALID_SOCKET");


         }
         if (is_connecting())
         {


            INFO(log_this, "write", 0, " * is_connecting()");

         }
         if (IsCloseAndDelete())
         {


            INFO(log_this, "write", 0, " * IsCloseAndDelete()");



         }
         return;
      }
      if(!IsConnected())
      {


         WARN(log_this, "write",-1,"Attempt to write to a non-connected socket, will be sent on connect"); // warning

         buffer(buf,(int) len);
         return;
      }
      if(m_obuf_top)
      {
         buffer(buf,(int) len);
         return;
      }
      else
      {
         i32 n = (i32)try_write(buf,(int) len);
         if(n >= 0 && n < (i32)len)
         {
            buffer(buf + n,(int) (len - n));
         }
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
         socket_handler()->get(GetSocket(),br,bw,bx);
         if(m_obuf.get_size())
            set(br,true);
         else
            set(br,false);
      }
   }


   void tcp_socket::OnLine(const string &)
   {
   }



   void tcp_socket::OnSocks4Connect()
   {
      char request[1000];
      __memset(request,0,sizeof(request));
      request[0] = 4; // socks v4
      request[1] = 1; // command code: CONNECT
      {
         ::net::address ad = GetClientRemoteAddress();
         if(ad.is_valid())
         {
            struct sockaddr * psockaddr = (struct sockaddr *)ad.sa();
            struct sockaddr_in *psockaddrin = (struct sockaddr_in *)psockaddr;
            if(psockaddrin->sin_family == AF_INET)
            {
               ::memcpy_dup(request + 2,&psockaddrin->sin_port,2); // nwbo is ok here
               ::memcpy_dup(request + 4,&psockaddrin->sin_addr,sizeof(struct in_addr));
            }
            else
            {
               /// \todo warn
            }
         }
         else
         {
            /// \todo warn
         }
      }
      strcpy(request + 8,GetSocks4Userid());
      ::count length = GetSocks4Userid().get_length() + 8 + 1;
      write(request,length);
      m_socks4_state = 0;
   }


   void tcp_socket::OnSocks4ConnectFailed()
   {


      WARN(this,"OnSocks4ConnectFailed",0,"connection to socks4 server failed, trying direct connection");


      if(!socket_handler()->Socks4TryDirect())
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
      switch(m_socks4_state)
      {
      case 0:
         ibuf.read(&m_socks4_vn,1);
         m_socks4_state = 1;
         break;
      case 1:
         ibuf.read(&m_socks4_cd,1);
         m_socks4_state = 2;
         break;
      case 2:
         if(GetInputLength() > 1)
         {
            ibuf.read((char *)&m_socks4_dstport,2);
            m_socks4_state = 3;
         }
         else
         {
            return true;
         }
         break;
      case 3:
         if(GetInputLength() > 3)
         {
            ibuf.read((char *)&m_socks4_dstip,4);
            SetSocks4(false);

            switch(m_socks4_cd)
            {
            case 90:
               OnConnect();


               INFO(log_this, "OnSocks4Read",0,"Connection established");

               break;
            case 91:
            case 92:
            case 93:


               FATAL(log_this, "OnSocks4Read",m_socks4_cd,"socks4 server reports connect failed");

               set_connecting(false);
               SetCloseAndDelete();
               OnConnectFailed();
               break;
            default:


               FATAL(log_this, "OnSocks4Read",m_socks4_cd,"socks4 server unrecognized response");

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




   void tcp_socket::OnSSLConnect()
   {

      SetNonblocking(true);

      //synchronous_lock slMap(psystem->sockets().m_clientcontextmap.m_mutex);

      if (is_true("from_pool"))
         return;

      //{

      //   if(m_ssl_ctx)
      //   {

      //      TRACE("SSL Context already initialized - closing socket\n");

      //      SetCloseAndDelete(true);

      //      return;

      //   }

      //   InitSSLClient();

      //}

//      if(!m_ssl_ctx)
      //    {

      int iError = 0;

//retry_init_ssl_client:

      InitSSLClient();

      //  }

      //slMap.unlock();

      if(m_psslcontext->m_pclientcontext.is_set()
            && m_psslcontext->m_pclientcontext->m_psslcontext != nullptr)
      {

         /* Connect the SSL socket */

         m_psslcontext->m_ssl = SSL_new(m_psslcontext->m_pclientcontext->m_psslcontext);

         if(!m_psslcontext->m_ssl)
         {

            TRACE(" m_ssl is nullptr\n");

            SetCloseAndDelete(true);

            return;

         }

         if (m_bClientSessionSet || m_psslcontext->m_pclientcontext->m_psslsession == nullptr)
         {

            if (m_strTlsHostName.has_char())
            {

               SSL_set_tlsext_host_name(m_psslcontext->m_ssl, (char *)(const char *)m_strTlsHostName);

            }

            //SSL_set_mode(m_ssl, SSL_MODE_AUTO_RETRY);

         }

         m_psslcontext->m_sbio = BIO_new_socket((i32)GetSocket(),BIO_NOCLOSE);

         if(!m_psslcontext->m_sbio)
         {

            TRACE(" m_sbio is nullptr\n");

            SetCloseAndDelete(true);

            return;

         }

         SSL_set_bio(m_psslcontext->m_ssl,m_psslcontext->m_sbio,m_psslcontext->m_sbio);


         if(!SSLNegotiate())
         {

            SetSSLNegotiate();

         }

      }
      else
      {

         SetCloseAndDelete();

      }

   }


   void tcp_socket::OnSSLAccept()
   {

      SetNonblocking(true);

      //synchronous_lock slMap(psystem->sockets().m_servercontextmap.m_mutex);

      {
         if(m_psslcontext.is_set()
               && m_psslcontext->m_pclientcontext.is_set()
               && m_psslcontext->m_pclientcontext->m_psslcontext != nullptr)
         {
            TRACE("SSL Context already initialized - closing socket\n");
            SetCloseAndDelete(true);
            return;
         }
         InitSSLServer();
         SetSSLServer();
      }


      //synchronous_lock synchronouslock(m_pmutexSslCtx);

      //slMap.unlock();


      if(m_psslcontext->m_pclientcontext->m_psslcontext)
      {
         m_psslcontext->m_ssl = SSL_new(m_psslcontext->m_pclientcontext->m_psslcontext);
         if(!m_psslcontext->m_ssl)
         {
            TRACE(" m_ssl is nullptr\n");
            SetCloseAndDelete(true);
            return;
         }
         SSL_set_app_data2(m_psslcontext->m_ssl, this);
         //SSL_set_mode(m_psslcontext->m_ssl,SSL_MODE_AUTO_RETRY);
         m_psslcontext->m_sbio = BIO_new_socket((i32)GetSocket(),BIO_NOCLOSE);
         if(!m_psslcontext->m_sbio)
         {
            TRACE(" m_sbio is nullptr\n");
            SetCloseAndDelete(true);
            return;
         }
         SSL_set_bio(m_psslcontext->m_ssl,m_psslcontext->m_sbio,m_psslcontext->m_sbio);
         //      if (!SSLNegotiate())
         {
            SetSSLNegotiate();
         }
      }
   }


   bool tcp_socket::SSLNegotiate()
   {

      if(!IsSSLServer()) // client
      {

         INFO(log_this, "SSLNegotiate", 0, "SSL_connect");

         if (m_bReuseSession && !m_bClientSessionSet && m_psslcontext->m_pclientcontext->m_psslsession != nullptr)
         {

            SSL_set_session(m_psslcontext->m_ssl, m_psslcontext->m_pclientcontext->m_psslsession);

            m_bClientSessionSet = true;

         }

         i32 r = SSL_connect(m_psslcontext->m_ssl);

         if(r > 0)
         {

            SetSSLNegotiate(false);

            if (SSL_session_reused(m_psslcontext->m_ssl))
            {

               INFO("REUSED SESSION");

            }
            else
            {

               INFO("NEW SESSION");

            }

            long x509_err = cert_common_name_check(m_strHost);

            if(x509_err != X509_V_OK
                  && x509_err != X509_V_ERR_SELF_SIGNED_CERT_IN_CHAIN
                  && x509_err != X509_V_ERR_UNABLE_TO_GET_ISSUER_CERT_LOCALLY)
            {


               INFO(log_this, "SSLNegotiate/cert_common_name_check",0,"cert_common_name_check failed (error="+__str((int)x509_err)+",url=" + m_strUrl + ")");

               SetSSLNegotiate(false);
               SetCloseAndDelete();
               OnSSLConnectFailed();
               return false;

            }

            if (m_bReuseSession)
            {

               if (m_psslcontext && m_psslcontext->m_pclientcontext && m_psslcontext->m_pclientcontext->m_psslsession)
               {

                  destroy_ssl_session();

               }

               if (!m_psslcontext || !m_psslcontext->m_pclientcontext || !m_psslcontext->m_pclientcontext->m_psslsession)
               {

                  get_ssl_session();

               }

            }

            /// \todo: resurrect certificate check... client
            //         CheckCertificateChain( "");//ServerHOST);
            SetNonblocking(false);
            //
            {
               SetConnected();
               if(GetOutputLength())
               {
                  OnWrite();
               }
            }
            if(IsReconnect())
               OnReconnect();
            else
            {
               OnConnect();
            }


            INFO(log_this, "SSLNegotiate/SSL_connect",0,"Connection established");

            return true;

         }
         else if(!r)
         {

            long error = ERR_get_error();
            const char* error_str = ERR_error_string(error, nullptr);
            printf("could not SSL_connect: %s\n", error_str);

            int iErrorSsl = SSL_get_error(m_psslcontext->m_ssl,r);

            //if(m_spsslclientcontext.is_set() &&
            if (m_psslcontext->m_pclientcontext->m_psslcontext != nullptr &&
                  iErrorSsl == SSL_ERROR_ZERO_RETURN
                  && (m_psslcontext->m_pclientcontext->m_psslmethod == TLS_client_method()))
            {

               TRACE("ssl_error_zero_return");

            }

            else
            {

               if (m_bReuseSession)
               {

                  if (m_psslcontext->m_pclientcontext->m_psslsession != nullptr)
                  {

                     if (m_psslcontext->m_iSslCtxRetry == 0)
                     {

                        m_psslcontext->m_iSslCtxRetry = 1;

                        destroy_ssl_session();

                        SSL_clear(m_psslcontext->m_ssl);

                     }
                     else
                     {

                        m_psslcontext->m_iSslCtxRetry = 0;

                     }

                  }

               }

               if (m_psslcontext->m_iSslCtxRetry == 0)
               {


                  INFO(log_this, "SSLNegotiate/SSL_connect", 0, "Connection failed");


                  SetSSLNegotiate(false);
                  SetCloseAndDelete();
                  OnSSLConnectFailed();

               }

            }

         }
         else
         {
            r = SSL_get_error(m_psslcontext->m_ssl,r);
            if(r == SSL_ERROR_WANT_READ || r == SSL_ERROR_WANT_WRITE)
            {
            }
            else if(r == SSL_ERROR_WANT_CONNECT || r == SSL_ERROR_WANT_ACCEPT)
            {
            }
            else
            {


               INFO(log_this, "SSLNegotiate", -1, "SSL_connect() failed");

               SetSSLNegotiate(false);
               SetCloseAndDelete(true);
               OnSSLConnectFailed();
            }
         }
      }
      else // server
      {
         i32 r = SSL_accept(m_psslcontext->m_ssl);
         int iError = Errno;
         if(r > 0)
         {
            SetSSLNegotiate(false);
            /// \todo: resurrect certificate check... server
            //         CheckCertificateChain( "");//ClientHOST);
            SetNonblocking(false);
            //
            {
               SetConnected();
               if(GetOutputLength())
               {
                  OnWrite();
               }
            }
            OnAccept();


            INFO(log_this, "SSLNegotiate/SSL_accept",0,"Connection established");

            return true;

         }
         else if(!r)
         {


            INFO(log_this, "SSLNegotiate/SSL_accept",0,"Connection failed");

            SetSSLNegotiate(false);
            SetCloseAndDelete();
            OnSSLAcceptFailed();
         }
         else
         {
            r = SSL_get_error(m_psslcontext->m_ssl,r);
            if(r == SSL_ERROR_WANT_READ || r == SSL_ERROR_WANT_WRITE)
            {
            }
            else if(r == SSL_ERROR_WANT_CONNECT || r == SSL_ERROR_WANT_ACCEPT)
            {
            }
            else
            {


               if (r == SSL_ERROR_SYSCALL)
               {
                  
                  output_debug_string("SSL_ERROR_SYSCALL: Errno = " + __str(iError));

               }

               INFO(log_this, "SSLNegotiate", r, "SSL_accept() failed");


               SetSSLNegotiate(false);
               SetCloseAndDelete(true);
               OnSSLAcceptFailed();
            }
         }
      }
      return false;
   }


   void tcp_socket::InitSSLClient()
   {
      //InitializeContext(m_strInitSSLClientContext,SSLv23_method());
      //InitializeContext(m_strInitSSLClientContext,TLSv1_client_method());

      InitializeContext(m_strInitSSLClientContext,TLS_client_method());

   }


   void tcp_socket::InitSSLServer()
   {


      FATAL(log_this, "InitSSLServer",0,"You MUST implement your own InitSSLServer method");

      SetCloseAndDelete();
   }


   void tcp_socket::InitializeContext(const string & context, const SSL_METHOD * pmethod)
   {

      auto psystem = get_system()->m_papexsystem;

      ssl_client_context_map & clientcontextmap = psystem->sockets().m_clientcontextmap;

      __pointer(ssl_client_context) psslclientcontext = clientcontextmap.get_context(context, pmethod);

      m_psslcontext = __new(ssl_context());

      m_psslcontext->m_pclientcontext = psslclientcontext;

   }


   void tcp_socket::InitializeContext(const string & context,const string & keyfile,const string & password,const SSL_METHOD *meth_in)
   {

      if (m_psslcontext.is_null())
      {

         m_psslcontext = __new(ssl_context());

      }

      if (m_psslcontext->m_pclientcontext.is_null())
      {

         m_psslcontext->m_pclientcontext = __new (ssl_client_context(meth_in != nullptr ? meth_in : TLS_server_method()));

         m_psslcontext->m_pclientcontext->initialize(get_application());

      }

      //m_psslcontext->m_pclientcontext->m_psslcontext = SSL_CTX_new(m_psslcontext->m_pclientcontext->m_psslmethod);
      SSL_CTX_set_mode(m_psslcontext->m_pclientcontext->m_psslcontext, SSL_MODE_AUTO_RETRY | SSL_MODE_RELEASE_BUFFERS) ;
      SSL_CTX_set_options(m_psslcontext->m_pclientcontext->m_psslcontext, SSL_OP_NO_COMPRESSION | SSL_CTX_get_options(m_psslcontext->m_pclientcontext->m_psslcontext));
      // session id
      int iSetSessionResult = -1;
      u32 uSessionIdMaxLen = SSL_MAX_SSL_SESSION_ID_LENGTH;
      if (context.get_length())
         iSetSessionResult = SSL_CTX_set_session_id_context(m_psslcontext->m_pclientcontext->m_psslcontext, (const uchar *)(const  char *)context, minimum((u32)context.get_length(), uSessionIdMaxLen));
      else
         iSetSessionResult = SSL_CTX_set_session_id_context(m_psslcontext->m_pclientcontext->m_psslcontext, (const uchar *)"--is_empty--", 9);

      if (keyfile.begins_ci("cat://") || keyfile.ends_ci(".cat"))
      {

         string strCert;

         if (keyfile.ends_ci(".cat"))
         {

            strCert = m_pcontext->m_papexcontext->file().as_string(keyfile);

         }
         else
         {

            strCert = keyfile;

            ::str::begins_eat_ci(strCert, "cat://");

         }

         BIO *bio;

         bio = BIO_new(BIO_s_mem());
         BIO_puts(bio, strCert);


            //if (!(SSL_CTX_use_RSAPrivateKey(m_psslcontext->m_pclientcontext->m_psslcontext, key)))
            //{

            //   ERR("tcp_socket InitializeContext,0,Couldn't read private key file %s e_trace_level_fatal", keyfile.c_str());

            //}


         //}

           // {

         X509 * certificate;

         certificate = PEM_read_bio_X509(bio, nullptr, nullptr, nullptr);

         if (certificate)
         {

            //            if (!SSL_CTX_use_certificate(m_psslcontext->m_pclientcontext->m_psslcontext, certificate))

                     //}

            m_password = password;
            SSL_CTX_set_default_passwd_cb(m_psslcontext->m_pclientcontext->m_psslcontext, tcp_socket_SSL_password_cb);
            SSL_CTX_set_default_passwd_cb_userdata(m_psslcontext->m_pclientcontext->m_psslcontext, (socket *)this);
            EVP_PKEY * key = PEM_read_bio_PrivateKey(bio, nullptr, nullptr, nullptr);
            array < X509 * > xa;
            if (key)
            {

               STACK_OF(X509) * pchain = nullptr;

               while (true)
               {

                  X509 * chainItem = PEM_read_bio_X509(bio, nullptr, nullptr, nullptr);

                  if (!chainItem)
                  {

                     break;

                  }

                  xa.add(chainItem);

                  if (pchain == nullptr)
                  {

                     pchain = sk_X509_new_null();

                  }

                  sk_X509_push(pchain, chainItem);

               }

#if OPENSSL_VERSION_NUMBER >= 0x10101000L 

               if (!SSL_CTX_use_cert_and_key(m_psslcontext->m_pclientcontext->m_psslcontext, certificate, key, pchain, 1))
               {

                  ERR("tcp_socket InitializeContext,-1,Couldn't read certificate string %s e_trace_level_fatal", keyfile.c_str());

               }

#else

               if (!SSL_CTX_use_certificate(m_psslcontext->m_pclientcontext->m_psslcontext, certificate))
               {

                  ERR("tcp_socket InitializeContext,-1,Couldn't read certificate string %s e_trace_level_fatal", keyfile.c_str());

               }

               if (!SSL_CTX_use_PrivateKey(m_psslcontext->m_pclientcontext->m_psslcontext, key))
               {

                  ERR("tcp_socket InitializeContext,-1,Couldn't read certificate string %s e_trace_level_fatal", keyfile.c_str());

               }

               for (auto x : xa)
               {

                  if (!SSL_CTX_add_extra_chain_cert(m_psslcontext->m_pclientcontext->m_psslcontext, x))
                  {

                     ERR("tcp_socket InitializeContext,-1,Couldn't read certificate string %s e_trace_level_fatal", keyfile.c_str());

                  }

               }

#endif

               if(pchain != nullptr)
               {

                  sk_X509_free(pchain);
                  
               }

               EVP_PKEY_free(key);

            }

            X509_free(certificate);

         }


         BIO_free(bio);

      }
      else
      {
         if (!SSL_CTX_use_certificate_chain_file(m_psslcontext->m_pclientcontext->m_psslcontext, keyfile))
         {
            /* Load our keys and certificates*/
            if (!(SSL_CTX_use_certificate_file(m_psslcontext->m_pclientcontext->m_psslcontext, keyfile, SSL_FILETYPE_PEM)))
            {
               ERR("tcp_socket InitializeContext,0,Couldn't read certificate file %s e_trace_level_fatal", keyfile.c_str());
            }
         }
         m_password = password;
         SSL_CTX_set_default_passwd_cb(m_psslcontext->m_pclientcontext->m_psslcontext, tcp_socket_SSL_password_cb);
         SSL_CTX_set_default_passwd_cb_userdata(m_psslcontext->m_pclientcontext->m_psslcontext, (socket *) this);

         if (!(SSL_CTX_use_PrivateKey_file(m_psslcontext->m_pclientcontext->m_psslcontext, keyfile, SSL_FILETYPE_PEM)))
         {
            ERR("tcp_socket InitializeContext,0,Couldn't read private key file %s e_trace_level_fatal", keyfile.c_str());
         }
      }


      {
         synchronous_lock synchronouslock(mutex());
         int i;

         auto psystem = get_system()->m_papexsystem;

         int cnt = sizeof(psystem->sockets().m_baTicketKey) / SSL_SESSION_TICKET_KEY_SIZE;
         m_ticketkeya.set_size(cnt);
         int j;
         for (i = 0; i < cnt; ++i)
         {
            j = (SSL_SESSION_TICKET_KEY_SIZE * i);
            ::memcpy_dup(m_ticketkeya[i].key_name, psystem->sockets().m_baTicketKey + j, 16);
            ::memcpy_dup(m_ticketkeya[i].hmac_key, psystem->sockets().m_baTicketKey + j + 16, 16);
            ::memcpy_dup(m_ticketkeya[i].aes_key, psystem->sockets().m_baTicketKey + j + 32, 16);
         }
      }

      SSL_CTX_set_tlsext_ticket_key_cb(m_psslcontext->m_pclientcontext->m_psslcontext, ssl_tlsext_ticket_key_cb);

   }


   void tcp_socket::InitializeContext(const string & context,const string & certfile,const string & keyfile,const string & password,const SSL_METHOD *meth_in)
   {

      /* create our context*/
      m_psslcontext->m_pclientcontext->m_psslmethod = meth_in != nullptr ? meth_in : TLS_client_method();
      m_psslcontext->m_pclientcontext->m_psslcontext = SSL_CTX_new(m_psslcontext->m_pclientcontext->m_psslmethod);
      SSL_CTX_set_mode(m_psslcontext->m_pclientcontext->m_psslcontext, SSL_MODE_AUTO_RETRY | SSL_MODE_RELEASE_BUFFERS);
      SSL_CTX_set_options(m_psslcontext->m_pclientcontext->m_psslcontext, SSL_OP_NO_COMPRESSION | SSL_CTX_get_options(m_psslcontext->m_pclientcontext->m_psslcontext));
      // session id
      if (context.get_length())
         SSL_CTX_set_session_id_context(m_psslcontext->m_pclientcontext->m_psslcontext, (const uchar *)(const  char *)context, (u32)context.get_length());
      else
         SSL_CTX_set_session_id_context(m_psslcontext->m_pclientcontext->m_psslcontext, (const uchar *)"--is_empty--", 9);

      /* Load our keys and certificates*/
      if (!(SSL_CTX_use_certificate_file(m_psslcontext->m_pclientcontext->m_psslcontext, certfile, SSL_FILETYPE_PEM)))
      {
         FATAL(log_this, "InitializeContext", 0, "Couldn't read certificate file " + keyfile);
      }

      m_password = password;
      SSL_CTX_set_default_passwd_cb(m_psslcontext->m_pclientcontext->m_psslcontext, tcp_socket_SSL_password_cb);
      SSL_CTX_set_default_passwd_cb_userdata(m_psslcontext->m_pclientcontext->m_psslcontext, (socket *) this);
      if (!(SSL_CTX_use_PrivateKey_file(m_psslcontext->m_pclientcontext->m_psslcontext, keyfile, SSL_FILETYPE_PEM)))
      {
         FATAL(log_this, "InitializeContext", 0, "Couldn't read private key file " + keyfile);
         //TRACE(string("tcp_socket InitializeContext(2),0,Couldn't read private key file ") + keyfile + string("e_trace_level_fatal"));
      }

   }


   i32 tcp_socket_SSL_password_cb(char *buf,i32 num,i32 rwflag,void *userdata)
   {

      UNREFERENCED_PARAMETER(rwflag);

      socket * psocket = static_cast<socket *>(userdata);

      tcp_socket * ptcpsocket = dynamic_cast<tcp_socket *>(psocket);

      string strPassword = ptcpsocket ? ptcpsocket->GetPassword().c_str() : "";

      if(num < strPassword.get_length() + 1)
      {

         return 0;

      }

      strcpy(buf, strPassword);

      return (i32)strPassword.get_length();

   }


   void tcp_socket::close()
   {

      if (GetSocket() == INVALID_SOCKET) // this could happen
      {


         WARN("socket::close", 0, "file descriptor invalid");

         return;

      }

      i32 n;

      SetNonblocking(true);

      if (!Lost() && IsConnected() && !(GetShutdownStatus() & SHUT_WR))
      {

         if (shutdown(GetSocket(), SHUT_WR) == -1)
         {

            // failed...


            ERR("shutdown", Errno, bsd_socket_error(Errno));



         }

      }

      char tmp[1000];

      if (!Lost() && (n = (i32) ::recv(GetSocket(), tmp, 1000, 0)) >= 0)
      {

         if (n)
         {


            WARN("read() after shutdown", n, "bytes read");

         }

      }

#ifdef HAVE_OPENSSL

      m_psslcontext.release();

#endif

      socket::close();

   }



#ifdef HAVE_OPENSSL
   SSL_CTX *tcp_socket::GetSslContext()
   {
      if (!m_psslcontext->m_pclientcontext->m_psslcontext)
      {


         WARN("GetSslContext", 0, "SSL Context is nullptr; check InitSSLServer/InitSSLClient");

      }
      return m_psslcontext->m_pclientcontext->m_psslcontext;
   }

   SSL *tcp_socket::GetSsl()
   {
      if (!m_psslcontext->m_ssl)
      {


         WARN("GetSsl", 0, "SSL is nullptr; check InitSSLServer/InitSSLClient");

      }
      return m_psslcontext->m_ssl;
   }
#endif


   void tcp_socket::SetReconnect(bool bReconnect)
   {
      m_bReconnect = bReconnect;
   }


   void tcp_socket::OnRawData(char * buf_in, memsize len)
   {

      socket::OnRawData(buf_in,len);

   }


   memsize tcp_socket::GetInputLength()
   {
      return (memsize)ibuf.get_length();
   }


   memsize tcp_socket::GetOutputLength()
   {
      return m_output_length;
   }


   u64 tcp_socket::GetBytesReceived(bool clear)
   {
      u64 z = m_bytes_received;
      if(clear)
         m_bytes_received = 0;
      return z;
   }


   u64 tcp_socket::GetBytesSent(bool clear)
   {
      u64 z = m_bytes_sent;
      if(clear)
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


   void tcp_socket::OnOptions(i32 family,i32 type,i32 protocol,SOCKET s)
   {

      UNREFERENCED_PARAMETER(family);
      UNREFERENCED_PARAMETER(type);
      UNREFERENCED_PARAMETER(protocol);
      UNREFERENCED_PARAMETER(s);
      //TRACE("socket::OnOptions()\n");
#ifdef SO_NOSIGPIPE
      SetSoNosigpipe(true);
#endif
      SetSoReuseaddr(true);
      SetSoKeepalive(true);
   }


   void tcp_socket::SetLineProtocol(bool x)
   {
      stream_socket::SetLineProtocol(x);
      DisableInputBuffer(x);
   }


   bool tcp_socket::SetTcpNodelay(bool x)
   {
#ifdef TCP_NODELAY
      i32 optval = x ? 1 : 0;
      if(setsockopt(GetSocket(),IPPROTO_TCP,TCP_NODELAY,(char *)&optval,sizeof(optval)) == -1)
      {


         FATAL(log_this, "setsockopt(IPPROTO_TCP, TCP_NODELAY)",Errno,bsd_socket_error(Errno));

         return false;
      }
      return true;
#else

      INFO(log_this, "socket option not available",0,"TCP_NODELAY");

      return false;
#endif
   }


   void tcp_socket::on_connection_timeout()
   {

      FATAL(log_this, "connect",-1,"connect timeout");

      m_estatus = error_connection_timed_out;

      if(Socks4())
      {

         OnSocks4ConnectFailed();
         // retry direct connection
      }
      else if(GetMaximumConnectionRetryCount() == -1 ||
              (GetMaximumConnectionRetryCount() && GetConnectionRetryCount() < GetMaximumConnectionRetryCount()))
      {

         IncrementConnectionRetryCount();

         // ask socket via OnConnectRetry callback if we should continue trying
         if(OnConnectRetry())
         {

            SetRetryClientConnect();

         }
         else
         {

            SetCloseAndDelete(true);

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
      
      set_connecting(false);

   }


#ifdef _WIN32

   void tcp_socket::OnException()
   {

      if(is_connecting())
      {

         i32 iError = this->socket_handler()->m_iSelectErrno;

         if(iError == ETIMEDOUT)
         {

            m_estatus = error_connection_timed_out;

         }
         else
         {
            //m_estatus = status_failed;
         }

         int iGetConnectionRetry = GetMaximumConnectionRetryCount();

         int iGetConnectionRetries = GetConnectionRetryCount();

         if (Socks4())
         {

            OnSocks4ConnectFailed();

         }
         else if(iGetConnectionRetry == -1 ||
                 (iGetConnectionRetry &&
                    iGetConnectionRetries < iGetConnectionRetry))
         {

            const int nBufSize = 1024;

            char buf[nBufSize];

            SOCKET iGetSocket = GetSocket();

            int n = ::recv(iGetSocket, (char*)buf, (int)nBufSize, MSG_OOB);

            output_debug_string("got " + __str(n) + " bytes of Out of Band Data");

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
      i32 err = SoError();

      FATAL(log_this, "exception on select",err,bsd_socket_error(err));

      SetCloseAndDelete();
   }
#endif // _WIN32


   i32 tcp_socket::Protocol()
   {
      return IPPROTO_TCP;
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


   string tcp_socket::get_short_description()
   {
      return get_url();
   }


   long tcp_socket::cert_common_name_check(const ::string & common_name)
   {

      if(!m_bCertCommonNameCheckEnabled)
      {

         return X509_V_OK;

      }

      ::X509 *cert = nullptr;
      ::X509_name_st *subject = nullptr;

      cert = SSL_get_peer_certificate(m_psslcontext->m_ssl);
      bool ok = false;
      if(cert != nullptr && strlen(common_name) > 0)
      {
         char data[256];
         if((subject = X509_get_subject_name(cert)) != nullptr && X509_NAME_get_text_by_NID(subject,NID_commonName,data,256) > 0)
         {
            data[255] = 0;
            if(ansi_count_compare_ci(data,common_name,255) == 0)
            {
               ok = true;
            }
            else
            {
               string str = data;
               if(::str::begins_eat(str,"*."))
               {
                  string strCommon = common_name;
                  if(strCommon == str)
                  {
                     ok = true;
                  }
                  else
                  {

                     strsize iFind = strCommon.find('.');

                     if(iFind >= 0)
                     {
                        if(str == strCommon.Mid(iFind + 1))
                        {
                           ok = true;
                        }
                     }

                  }


               }
            }
         }
         if (!ok)
         {

            int i;
            int san_names_nb = -1;
            STACK_OF(GENERAL_NAME) *san_names = nullptr;
            // Try to extract the names within the SAN extension from the certificate
            san_names = (STACK_OF(GENERAL_NAME) *) X509_get_ext_d2i((X509 *)cert, NID_subject_alt_name, nullptr, nullptr);
            if (san_names == nullptr)
            {
            }
            else
            {
               san_names_nb = sk_GENERAL_NAME_num(san_names);

               // Check each name within the extension
               for (i = 0; i < san_names_nb; i++)
               {
                  const GENERAL_NAME *current_name = sk_GENERAL_NAME_value(san_names, i);

                  if (current_name->type == GEN_DNS)
                  {
                     // Current name is a DNS name, let's check it

#if (defined(_UWP) || defined(LINUX)) && (OPENSSL_API_COMPAT < 0x10100000L)
                     string strDnsName((const char *)ASN1_STRING_data(current_name->d.dNSName), ASN1_STRING_length(current_name->d.dNSName));
#else
                     string strDnsName((const char *)ASN1_STRING_get0_data(current_name->d.dNSName), ASN1_STRING_length(current_name->d.dNSName));
#endif

                     if(strDnsName.compare_ci(common_name) == 0)
                     {
                        ok = true;
                        break;

                     }

                  }
               }
               sk_GENERAL_NAME_pop_free(san_names, GENERAL_NAME_free);
            }
         }
      }

      if(cert)
      {
         X509_free(cert);
      }

      if(ok)
      {
         return SSL_get_verify_result(m_psslcontext->m_ssl);
      }

      return X509_V_ERR_APPLICATION_VERIFICATION;

   }


   void tcp_socket::enable_cert_common_name_check(bool bEnable)
   {

      m_bCertCommonNameCheckEnabled = bEnable;

   }


   string tcp_socket::get_connect_host()
   {

      return m_strConnectHost;

   }


   port_t tcp_socket::get_connect_port()
   {

      return m_iConnectPort;

   }

   void tcp_socket::InitializeContextTLSClientMethod()
   {

#if defined(HAVE_OPENSSL)

      InitializeContext("", TLS_client_method());

#endif

   }


} // namespace sockets





