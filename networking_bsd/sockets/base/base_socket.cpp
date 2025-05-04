/** \file socket_thread.cpp
**   \date  2021-07-26
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
#include "framework.h"
#include "base_socket.h"
#include "base_socket_handler.h"
#include "acme/exception/interface_only.h"
#include "acme/filesystem/file/memory_file.h"
#include "acme/parallelization/synchronous_lock.h"
#include "networking_bsd/sockets/basic/socket_handler.h"
#include "apex/networking/networking.h"
#include "apex/platform/system.h"
#include "networking_bsd/sockets/basic/socket_handler.h"
#include "networking_bsd/sockets/ssl/context.h"
#include "networking_bsd/sockets/ssl/client_context.h"
#ifdef _WIN32
#elif defined(LINUX)
#include <netdb.h>
#include <fcntl.h>
#else
#define __BSD_VISIBLE 1
#include <netdb.h>
#include <fcntl.h>
#endif
////#include <ctype.h>
#include <time.h>

#if defined(OPENBSD)
#include <sys/ucred.h>
#endif

#ifdef PARALLELIZATION_PTHREAD


#include "acme/operating_system/ansi/_pthread.h"


#endif


#ifdef BSD_STYLE_SOCKETS
#include <openssl/ssl.h>
#endif

namespace sockets_bsd
{


   //::pointer< ::mutex > base_socket::s_pmutex = nullptr;


   base_socket::base_socket() :
      m_bDelete(false)
      ,m_bCloseAndDelete(false)
      , m_timeCreate(now_t{})
      ,m_psocketParent(nullptr)
      ,m_bDisableRead(false)
      ,m_bConnected(false)
      ,m_bErasedByHandler(false)
      , m_timeClose({ posix_time_t{}, 0 })
      ,m_bLost(false)
      ,m_bEnableSsl(false)
      ,m_bSsl(false)
      ,m_bSslServer(false)
      ,m_bIpv6(false)
      ,m_bSocks4(false)
      ,m_b_chunked(false)
      ,m_socketid(INVALID_SOCKET)
      //,m_socks4_host(h.GetSocks4Host())
      //,m_socks4_port(h.GetSocks4Port())
      //,m_socks4_userid(h.GetSocks4Userid())
      ,m_socks4_port(0)
      ,m_bDetach(false)
      ,m_bDetached(false)
      // Line protocol
      ,m_bLineProtocol(false)
      ,m_skip_c(false)
//#if !defined(BSD_STYLE_SOCKETS)
      //,m_happening(h.get_())
//#endif
   {
      m_iSelectRead = 0;
      m_iSelectWrite = 0;
      m_iSelectError = 0;
      //m_p2 = this;
#ifdef WINRT_SOCKETS
      m_bErrorReading = false;
      m_bErrorWriting = false;
      m_bWaitingResponse = false;
      m_bExpectResponse = false;
      m_bExpectRequest = false;
      m_bReading = false;
      m_bWriting = false;
#endif
      m_pmemfileInput = nullptr;
      m_iBindPort    = -1;
      m_timeStart.Now();
      m_timeConnectionLastRead.Now();
      m_timeConnectionLastWrite.Now();
      //m_pcallback    = nullptr;
      m_bEnablePool  = true;

      m_timeConnectionMaximum = 30_s;
      m_timeKeepConnectionAfterLastIO = 30_s;

   }


   base_socket::~base_socket()
   {

   }


   void base_socket::set(bool bRead, bool bWrite, bool bError)
   {

      m_iSelectRead = bRead ? 1 : 0;

      m_iSelectWrite = bWrite ? 1 : 0;

      m_iSelectRead = bError ? 1 : 0;

   }


   void base_socket::SetSocketHandler(::sockets::base_socket_handler* phandler)
   {

      //::object::initialize(phandler);

      if (::is_null(phandler))
      {

         m_phandlerSlave.release();

         m_psockethandler.release();

      }
      else if (IsDetached())
      {

         if (::is_set(phandler) && !phandler->IsSlave())
         {

            throw exception(error_wrong_state);

         }

         m_phandlerSlave = phandler;

      }
      else
      {

         m_psockethandler = phandler;

      }

      //m_socks4_host = m_psockethandler->GetSocks4Host();
      //m_socks4_port = m_psockethandler->GetSocks4Port();
      //m_socks4_userid = m_psockethandler->GetSocks4Userid();

   }


   enum_trace_category base_socket::trace_category() const
   {

      return e_trace_category_socket;

   }


   void base_socket::destroy()
   {

      m_psslcontext.defer_destroy();

      m_psockethandler.release();

      m_paddressRemote.release();

      m_paddressRemoteClient.release();

      m_pfileTrafficMonitor.release();

      m_pmemfileInput.release();

      m_pcallback.release();

      m_psocketParent.release();

      m_phandlerSlave.release();

      ::sockets::base_socket::destroy();

   }


   void base_socket::Init()
   {

   }


   void base_socket::OnRead()
   {
   }


   void base_socket::OnWrite()
   {

   }


   void base_socket::OnException()
   {
      


#ifdef BSD_STYLE_SOCKETS

      // %! exception doesn't always mean something bad happened, this code should be reworked
      // errno valid here?
      int err = SoError();
      fatal() <<"exception on select "<< err <<" "<<  bsd_socket_error(err);

#endif

      SetCloseAndDelete();

   }


   void base_socket::OnDelete()
   {

      if (base_socket_interface())
      {

         base_socket_interface()->OnDelete();

      }

   }


   void base_socket::OnConnect()
   {

      base_socket_interface()->OnConnect();

   }


   void base_socket::OnAccept()
   {

      base_socket_interface()->OnAccept();

   }


   void base_socket::close()
   {

#ifdef BSD_STYLE_SOCKETS

      m_psslcontext.release();

#endif

   }


   void base_socket::set_end()
   {

      m_bEnd = true;

   }


   bool base_socket::is_end() const
   {

      return m_bEnd;

   }


   int base_socket::close_socket(SOCKET s)
   {

      __UNREFERENCED_PARAMETER(s);

      return 0;

   }


   bool base_socket::is_connecting()
   {
      return false;
   }

   //void base_socket::create_sock

   /*   SOCKET base_socket::CreateSocket(int af,int iType, const ::string & strProtocol)
   {
   struct protoent *point = nullptr;
   SOCKET s;

   m_iSocketType = iType;
   m_strSocketProtocol = strProtocol;
   if (strProtocol.length())
   {
   point = getprotobyname( strProtocol );
   if (!int_point)
   {
   fatal() <<"getprotobyname" << networking_last_error() << ", " << bsd_socket_error(networking_last_error());
   SetCloseAndDelete();
   throw ::exception(::exception(string("getprotobyname() failed: ") + bsd_socket_error(networking_last_error())));
   return INVALID_SOCKET;
   }
   }
   int protno = int_point ? int_point -> p_proto : 0;

   s = ::base_socket(af, iType, protno);
   if (s == INVALID_SOCKET)
   {
   fatal() <<"base_socket" << networking_last_error() << ", " << bsd_socket_error(networking_last_error());
   SetCloseAndDelete();
   throw ::exception(::exception(string("base_socket() failed: ") + bsd_socket_error(networking_last_error())));
   return INVALID_SOCKET;
   }
   attach(s);
   OnOptions(af, iType, protno, s);
   attach(INVALID_SOCKET);
   return s;
   }
   */


   void base_socket::attach(SOCKET s)
   {

      m_socketid = s;

      if (topic_text() == nullptr)
      {
         
          //string strTopicText;

          //strTopicText.formatf("socket_%d> ", s);

          //set_topic_text(strTopicText);

      }

   }


   socket_id base_socket::GetSocketId()
   {

      return m_socketid;

   }


   ::networking::port_t base_socket::get_bind_port() const
   {

      return m_iBindPort;

   }


   void base_socket::SetDeleteByHandler(bool x)
   {
      m_bDelete = x;
   }


   bool base_socket::DeleteByHandler()
   {
      return m_bDelete;
   }


   void base_socket::SetCloseAndDelete(bool bCloseAndDelete)
   {

      if (is_different(bCloseAndDelete, m_bCloseAndDelete))
      {

         if(socket_handler())
         {

            ::pointer < ::sockets_bsd::socket_handler > phandler = socket_handler();

            phandler->socket_id_list_modify(m_socketid, e_list_close, bCloseAndDelete);

         }

         if (payload("this_is_a_http_post_socket").is_true())
         {

            output_debug_string("p");

         }

         if (base_socket_interface()->payload("this_is_a_http_post_socket").is_true())
         {

            output_debug_string("p(2)");

         }

         m_bCloseAndDelete = bCloseAndDelete;

         if (bCloseAndDelete)
         {

            m_timeClose.Now();

         }

      }

   }


   bool base_socket::IsCloseAndDelete()
   {
      
      return m_bCloseAndDelete;

   }


   void base_socket::SetRemoteHostname(::networking::address * paddress) //struct sockaddr* sa, socklen_t l)
   {

      m_paddressRemote = paddress;

   }


   ::pointer<::networking::address>base_socket::GetRemoteHostname()
   {

      return m_paddressRemote;

   }


   ::sockets::base_socket_handler* base_socket::socket_handler() const
   {

      if (IsDetached())
      {

         return m_phandlerSlave.m_p;

      }

      return m_psockethandler;

   }


   ::sockets::base_socket_handler* base_socket::master_socket_handler() const
   {
      
      return m_psockethandler;

   }


   memory_file * base_socket::get_input_memory_file()
   {

      return m_pmemfileInput;

   }


   /*   in_addr base_socket::GetRemoteIP4()
   {
   ipaddr_t l = 0;
   if(m_bIpv6)
   {
   warning() <<"GetRemoteIP4", 0, "get ipv4 address for ipv6 base_socket";
   }
   if(m_addressRemote.m_p != nullptr)
   {
   struct sockaddr *point = *m_addressRemote;
   struct sockaddr_in *sa = (struct sockaddr_in *)int_point;
   ::memory_copy(&l, &sa -> sin_addr, sizeof(struct in_addr));
   }
   return l;
   }*/


   /*   struct in6_addr base_socket::GetRemoteIP6()
   {
   if(!m_bIpv6)
   {
   warning() <<"GetRemoteIP6", 0, "get ipv6 address for ipv4 base_socket";
   }
   struct sockaddr_in6 fail;
   if (m_addressRemote.m_p != nullptr)
   {
   struct sockaddr *point = *m_addressRemote;
   ::memory_copy(&fail, point, sizeof(struct sockaddr_in6));
   }
   else
   {
   memory_set(&fail, 0, sizeof(struct sockaddr_in6));
   }
   return fail.sin6_addr;
   }*/


   /*   ::networking::port_t base_socket::GetRemotePort()
   {

   return m_addressRemote.get_service_number();

   }*/


   bool base_socket::SetNonblocking(bool bNb)
   {
      m_bNonBlocking = bNb;

#ifdef BSD_STYLE_SOCKETS
#ifdef _WIN32
      unsigned long l = bNb ? 1 : 0;
      int n = ioctlsocket(m_socketid, FIONBIO, &l);
      if (n != 0)
      {
         information() << "ioctlsocket(FIONBIO) " << networking_last_error();
         return false;
      }
      return true;
#else
      if (bNb)
      {
         if (fcntl(m_socketid, F_SETFL, O_NONBLOCK) == -1)
         {
            error() <<"fcntl(F_SETFL, O_NONBLOCK) " << networking_last_error() << " " << bsd_socket_error(networking_last_error());
            return false;
         }
      }
      else
      {
         if (fcntl(m_socketid, F_SETFL, 0) == -1)
         {
            error() <<"fcntl(F_SETFL, 0)" << networking_last_error() << " " << bsd_socket_error(networking_last_error());
            return false;
         }
      }
      return true;
#endif
#else
      return false;

#endif
   }


   bool base_socket::SetNonblocking(bool bNb, SOCKET s)
   {

      __UNREFERENCED_PARAMETER(bNb);
      __UNREFERENCED_PARAMETER(s);

      return false;

      /*   #ifdef _WIN32
         unsigned long l = bNb ? 1 : 0;
         int n = ioctlsocket(s, FIONBIO, &l);
         if (n != 0)
         {
         ERR(log_this, "ioctlsocket(FIONBIO)", networking_last_error(), "");
         return false;
         }
         return true;
         #else
         if (bNb)
         {
         if (fcntl(s, F_SETFL, O_NONBLOCK) == -1)
         {
         error() <<"fcntl(F_SETFL, O_NONBLOCK)" << networking_last_error() << ", " << bsd_socket_error(networking_last_error();
         return false;
         }
         }
         else
         {
         if (fcntl(s, F_SETFL, 0) == -1)
         {
         error() <<"fcntl(F_SETFL, 0)" << networking_last_error() << ", " << bsd_socket_error(networking_last_error();
         return false;
         }
         }
         return true;
         #endif*/
   }


   //void base_socket::Set(bool bRead, bool bWrite, bool bException)
   //{

   //   ::pointer < sockets_bsd::socket_handler > phandler = this->socket_handler();
   //   
   //   phandler->set(m_socketid, bRead, bWrite, bException);

   //}


   bool base_socket::Ready()
   {
      if (m_socketid != INVALID_SOCKET && !IsCloseAndDelete())
         return true;
      return false;
   }

   bool base_socket::is_valid()
   {

      return Ready();

   }


   void base_socket::OnLine(const string & )
   {
   }

   
   bool base_socket::on_select_idle()
   {
      
      //return base_socket_interface()->on_select_idle();

      return false;

   }


   void base_socket::OnConnectFailed()
   {


   }


   ::sockets::base_socket * base_socket::get_parent_socket()
   {
      
      return m_psocketParent;

   }


   void base_socket::set_parent_socket(::sockets::base_socket * psocketParent)
   {
      
      m_psocketParent = psocketParent;

      on_set_parent_socket();

   }


   ::networking::port_t base_socket::GetPort()
   {

      warning() <<"GetPort only implemented for listen_socket";

      return 0;

   }


   void base_socket::OnOptions(int family, int type, int protocol, SOCKET s)
   {
      
      
   }


   bool base_socket::OnConnectRetry()
   {
      
      return true;
      
   }


   void base_socket::OnReconnect()
   {
   }


   posix_time base_socket::Uptime()
   {

      return m_timeCreate.elapsed();

   }


   void base_socket::SetIpv6(bool bIpv6)
   {
      m_bIpv6 = bIpv6;
   }


   bool base_socket::IsIpv6()
   {
      return m_bIpv6;
   }

   void base_socket::DisableRead(bool x)
   {
      m_bDisableRead = x;
   }


   bool base_socket::IsDisableRead()
   {
      return m_bDisableRead;
   }



   void base_socket::SetConnected(bool bConnected)
   {
      m_bConnected = bConnected;
   }


   bool base_socket::IsConnected()
   {
      return m_bConnected;
   }


   void base_socket::OnDisconnect()
   {
   }


   void base_socket::SetLost()
   {
      m_bLost = true;
   }


   bool base_socket::Lost()
   {
      return m_bLost;
   }


   void base_socket::SetErasedByHandler(bool bErasedByHandler)
   {
      m_bErasedByHandler = bErasedByHandler;
   }


   bool base_socket::ErasedByHandler()
   {
      return m_bErasedByHandler;
   }


   posix_time base_socket::TimeSinceClose()
   {

      return m_timeClose.elapsed();

   }


   void base_socket::SetClientRemoteAddress(::networking::address * paddress)
   {

      /*      if (!ad.IsValid())
      {
      error() <<"SetClientRemoteAddress", 0, "remote address not valid";
      }*/

      m_paddressRemoteClient = paddress;

   }


   ::pointer<::networking::address>base_socket::GetClientRemoteAddress()
   {

      /*      if (m_addressRemoteClient.m_p == nullptr)
      {
      error() <<"GetClientRemoteAddress", 0, "remote address not yet set";
      }*/

      return m_paddressRemoteClient;

   }


   unsigned long long base_socket::GetBytesSent(bool)
   {
      return 0;
   }


   unsigned long long base_socket::GetBytesReceived(bool)
   {
      return 0;
   }


   void base_socket::OnSSLConnect()
   {

      base_socket_interface()->OnSSLConnect();

   }


   void base_socket::OnSSLAccept()
   {

      base_socket_interface()->OnSSLAccept();

   }


   bool base_socket::SSLNegotiate()
   {

      return false;

   }

   void base_socket::OnSSLConnectFailed()
   {
   }


   void base_socket::OnSSLAcceptFailed()
   {
   }


   bool base_socket::IsSSL()
   {
      return m_bEnableSsl;
   }


   void base_socket::EnableSSL(bool bEnable)
   {
      m_bEnableSsl = bEnable;
   }


   bool base_socket::IsSSLNegotiate()
   {
      return m_bSsl;
   }


   void base_socket::SetSSLNegotiate(bool bSslNegotiate)
   {
      m_bSsl = bSslNegotiate;
   }


   bool base_socket::IsSSLServer()
   {
      return m_bSslServer;
   }


   void base_socket::SetSSLServer(bool bSSLServer)
   {
      m_bSslServer = bSSLServer;
   }



   void base_socket::CopyConnection(::sockets::base_socket * psocket)
   {

      ::pointer < ::sockets_bsd::base_socket > psocket2 = psocket;

#ifdef BSD_STYLE_SOCKETS
      m_psslcontext = psocket2->m_psslcontext;
#endif
      //m_ssl_ctx = psocket->m_ssl_ctx; ///< ssl context
      //m_ssl_session = psocket->m_ssl_session; ///< ssl session
      //ssl_method() = psocket->ssl_method(); ///< ssl method
      //m_ssl = psocket->m_ssl; ///< ssl 'socket'
      //m_ssl = psocket->m_ssl; ///< ssl 'socket'
      //m_sbio = psocket->m_sbio; ///< ssl bio
      m_password = psocket2->m_password; ///< ssl password

      attach(psocket2 -> GetSocketId());

      SetIpv6(psocket -> IsIpv6());
      
      SetSocketType(psocket -> GetSocketType());
      
      SetSocketProtocol(psocket -> GetSocketProtocol());

      SetClientRemoteAddress(psocket -> GetClientRemoteAddress());
      
      SetRemoteHostname(psocket -> GetRemoteHostname());

      psocket2->m_socketid = INVALID_SOCKET;

#ifdef BSD_STYLE_SOCKETS
      if (psocket2->m_psslcontext)
      {

         psocket2->m_psslcontext.release();

      }
#endif
      //psocket->m_psslcontext->m_iSslCtxRetry = 0;
      //psocket->m_psslcontext->m_ssl = nullptr;
      //psocket->m_psslcontext->m_sbio = nullptr;
      psocket2->m_password.empty();


   }


   void base_socket::SetIsClient()
   {
      m_bClient = true;
   }


   void base_socket::SetSocketType(int iSocketType)
   {
      m_iSocketType = iSocketType;
   }


   int base_socket::GetSocketType()
   {
      return m_iSocketType;
   }


   void base_socket::SetSocketProtocol(const ::string & strProtocol)
   {
      m_strSocketProtocol = strProtocol;
   }


   string base_socket::GetSocketProtocol()
   {
   
      return m_strSocketProtocol;

   }


   bool base_socket::IsPoolEnabled() const
   {

      return m_bEnablePool;

   }


   void base_socket::EnablePool(bool bEnable)
   {

      m_bEnablePool = bEnable;

   }


   void base_socket::SetRetain()
   {

      if(m_bClient && m_bEnablePool)
      {

         m_bRetain = true;

      }

   }


   bool base_socket::Retain()
   {

      return m_bEnablePool && m_bRetain && (m_timeStart.elapsed() < 30_s);

   }


   void base_socket::OnSocks4Connect()
   {

      information() << "Use with tcp_socket only";

   }


   void base_socket::OnSocks4ConnectFailed()
   {
      information() << "Use with tcp_socket only";

   }


   bool base_socket::OnSocks4Read()
   {
      information() << "Use with tcp_socket only";
      return true;
   }


#if defined(BSD_STYLE_SOCKETS)


   void base_socket::SetSocks4Host(const string & host)
   {

      //auto pnetworking = system()->networking();

      //paddressdepartment->convert(m_socks4_host, host);

      m_socks4_host = host;

   }


#endif


   bool base_socket::Socks4()
   {
      
      return m_bSocks4;

   }


   void base_socket::SetSocks4(bool x)
   {
      m_bSocks4 = x;
   }


   //void base_socket::SetSocks4Host(const ::string & a)
   //{
   //   m_socks4_host = a;
   //}


   void base_socket::SetSocks4Port(::networking::port_t port)
   {

      m_socks4_port = port;

   }


   void base_socket::SetSocks4Userid(const string & x)
   {
      m_socks4_userid = x;
   }


   string base_socket::GetSocks4Host()
   {

      return m_socks4_host;

   }


   ::networking::port_t base_socket::GetSocks4Port()
   {
      
      return m_socks4_port;

   }


   const string & base_socket::GetSocks4Userid()
   {
      
      return m_socks4_userid;

   }


   bool base_socket::prepare_for_detach()
   {

#if 0

      information() << "prepare_for_detach";

#endif

      if (!DeleteByHandler())
      {

         throw "debug delete by handler";

         return false;

      }

      if (m_psocketthread)
      {

         throw "debug m_psocketthread";

         return false;

      }

      if (m_bDetached)
      {

         throw "debug detach";

         return false;

      }

      SetDetach();

      return true;

   }


   //void base_socket::DetachSocket()
   //{

   //   SetDetached();

   //   auto psocketthread = __allocate socket_thread();

   //   psocketthread->initialize_socket_thread(this);

   //}


   void base_socket::OnDetached()
   {

      //base_socket_interface()->OnDetached();

   }


   void base_socket::SetDetach(bool bDetach)
   {

      m_bDetach = bDetach;

   }


   bool base_socket::IsDetach()
   {

      return m_bDetach;

   }


   void base_socket::SetDetached(bool x)
   {
      
      m_bDetached = x;

   }


   const bool base_socket::IsDetached() const
   {

      return m_bDetached;

   }


   void base_socket::SetSlaveHandler(::sockets::base_socket_handler * phandler)
   {

      m_phandlerSlave = phandler;

   }

   //


//   int base_socket::Resolve(const string & host,::networking::port_t port)
//   {
//
//      return socket_handler()->Resolve(this, host, port);
//
//   }


//   int base_socket::Resolve6(const string & host,::networking::port_t port)
//   {
//
//      return socket_handler()->Resolve6(this, host, port);
//
//   }


//   int base_socket::Resolve(in_addr a)
//   {
//
//      return socket_handler()->Resolve(this, a);
//
//   }


//   int base_socket::Resolve(in6_addr& a)
//   {
//
//      return socket_handler()->Resolve(this, a);
//
//   }


//   void base_socket::OnResolved(int, ::networking::address * address)
//   {
//
//   }


//   void base_socket::OnReverseResolved(int,const string &)
//   {
//
//   }


//   void base_socket::OnResolveFailed(int)
//   {
//
//   }


   bool base_socket::SetIpOptions(const void *point, socklen_t len)
   {

#if defined(IP_OPTIONS) && defined(BSD_STYLE_SOCKETS)

      if (setsockopt(GetSocketId(), IPPROTO_IP, IP_OPTIONS, (char *)point, len) == -1)
      {

         fatal() <<"setsockopt(IPPROTO_IP, IP_OPTIONS)" << networking_last_error() << ", " << bsd_socket_error(networking_last_error());

         return false;

      }

      return true;

#else

      information() << "ip option not available, IP_OPTIONS";

      return false;

#endif

   }


#if defined(IP_PKTINFO) && defined(BSD_STYLE_SOCKETS)

   bool base_socket::SetIpPktinfo(bool x)
   {

      int optval = x ? 1 : 0;

      if (setsockopt(GetSocketId(), IPPROTO_IP, IP_PKTINFO, (char *)&optval, sizeof(optval)) == -1)
      {
      
         fatal() <<"setsockopt(IPPROTO_IP, IP_PKTINFO) " << networking_last_error() << ", " << bsd_socket_error(networking_last_error());
      
         return false;

      }

      return true;

   }

#endif


#if defined(IP_RECVTOS) && defined(BSD_STYLE_SOCKETS)
   

   bool base_socket::SetIpRecvTOS(bool x)
   {
      
      int optval = x ? 1 : 0;
      
      if (setsockopt(GetSocketId(), IPPROTO_IP, IP_RECVTOS, (char *)&optval, sizeof(optval)) == -1)
      {
      
         fatal() <<"setsockopt(IPPROTO_IP, IP_RECVTOS) " << networking_last_error() << ", " << bsd_socket_error(networking_last_error());
      
         return false;

      }

      return true;

   }


#endif


#if defined(IP_RECVTTL) && defined(BSD_STYLE_SOCKETS)
   

   bool base_socket::SetIpRecvTTL(bool x)
   {
      
      int optval = x ? 1 : 0;
      
      if (setsockopt(GetSocketId(), IPPROTO_IP, IP_RECVTTL, (char *)&optval, sizeof(optval)) == -1)
      {
         
         fatal() <<"setsockopt(IPPROTO_IP, IP_RECVTTL) " << networking_last_error() << ", " << bsd_socket_error(networking_last_error());
         
         return false;

      }

      return true;

   }


#endif


#if defined(IP_RECVOPTS) && defined(BSD_STYLE_SOCKETS)
   

   bool base_socket::SetIpRecvopts(bool x)
   {
   
      int optval = x ? 1 : 0;

      if (setsockopt(GetSocketId(), IPPROTO_IP, IP_RECVOPTS, (char *)&optval, sizeof(optval)) == -1)
      {

         fatal() <<"setsockopt(IPPROTO_IP, IP_RECVOPTS) " << networking_last_error() << ", " << bsd_socket_error(networking_last_error());

         return false;

      }

      return true;

   }

#endif


#if defined(IP_RETOPTS) && defined(BSD_STYLE_SOCKETS)
   

   bool base_socket::SetIpRetopts(bool x)
   {
   
      int optval = x ? 1 : 0;

      if (setsockopt(GetSocketId(), IPPROTO_IP, IP_RETOPTS, (char *)&optval, sizeof(optval)) == -1)
      {

         fatal() <<"setsockopt(IPPROTO_IP, IP_RETOPTS) " << networking_last_error() << ", " << bsd_socket_error(networking_last_error());

         return false;

      }

      return true;

   }


#endif


   bool base_socket::SetIpTOS(unsigned char tos)
   {

#if defined(IP_TOS) && defined(BSD_STYLE_SOCKETS)
      
      if (setsockopt(GetSocketId(), IPPROTO_IP, IP_TOS, (char *)&tos, sizeof(tos)) == -1)
      {
      
         fatal() <<"setsockopt(IPPROTO_IP, IP_TOS) " << networking_last_error() << ", " << bsd_socket_error(networking_last_error());

         return false;

      }

      return true;

#else
      
      INFO(log_this, "ip option not available", 0, "IP_TOS");

      return false;

#endif

   }


   unsigned char base_socket::IpTOS()
   {

      unsigned char tos = 0;

#if defined(IP_TOS) && defined(BSD_STYLE_SOCKETS)

      socklen_t len = sizeof(tos);

      if (getsockopt(GetSocketId(), IPPROTO_IP, IP_TOS, (char *)&tos, &len) == -1)
      {
      
         fatal() <<"getsockopt(IPPROTO_IP, IP_TOS) " << networking_last_error() << ", " << bsd_socket_error(networking_last_error());

      }

#else

      information() << "ip option not available: IP_TOS";

#endif

      return tos;

   }


   bool base_socket::SetIpTTL(int ttl)
   {

#if defined(IP_TTL) && defined(BSD_STYLE_SOCKETS)

      if (setsockopt(GetSocketId(), IPPROTO_IP, IP_TTL, (char *)&ttl, sizeof(ttl)) == -1)
      {

         fatal() <<"setsockopt(IPPROTO_IP, IP_TTL) " << networking_last_error() << ", " << bsd_socket_error(networking_last_error());

         return false;

      }

      return true;

#else

      information() << "ip option not available: IP_TTL";

      return false;

#endif

   }


   int base_socket::IpTTL()
   {
      
      int ttl = 0;

#if defined(IP_TTL) && defined(BSD_STYLE_SOCKETS)

      socklen_t len = sizeof(ttl);

      if (getsockopt(GetSocketId(), IPPROTO_IP, IP_TTL, (char *)&ttl, &len) == -1)
      {

         fatal() <<"getsockopt(IPPROTO_IP, IP_TTL) " << networking_last_error() << ", " << bsd_socket_error(networking_last_error());

      }

#else

      information() << "ip option not available: IP_TTL";

#endif

      return ttl;

   }


   bool base_socket::SetIpHdrincl(bool x)
   {

#if defined(IP_HDRINCL) && defined(BSD_STYLE_SOCKETS)
      
      int optval = x ? 1 : 0;
      
      if (setsockopt(GetSocketId(), IPPROTO_IP, IP_HDRINCL, (char *)&optval, sizeof(optval)) == -1)
      {

         fatal() <<"setsockopt(IPPROTO_IP, IP_HDRINCL) " << networking_last_error() << ", " << bsd_socket_error(networking_last_error());

         return false;

      }

      return true;

#else

      information() << "ip option not available: IP_HDRINCL";

      return false;

#endif

   }


#if defined(IP_RECVERR) && defined(BSD_STYLE_SOCKETS)
   
   bool base_socket::SetIpRecverr(bool x)
   {

      int optval = x ? 1 : 0;

      if (setsockopt(GetSocketId(), IPPROTO_IP, IP_RECVERR, (char *)&optval, sizeof(optval)) == -1)
      {

         fatal() <<"setsockopt(IPPROTO_IP, IP_RECVERR)" << networking_last_error() << ", " << bsd_socket_error(networking_last_error());

         return false;

      }

      return true;

   }

#endif


#if defined(IP_MTU_DISCOVER) && defined(BSD_STYLE_SOCKETS)
   
   bool base_socket::SetIpMtudiscover(bool x)
   {
   
      int optval = x ? 1 : 0;

      if (setsockopt(GetSocketId(), IPPROTO_IP, IP_MTU_DISCOVER, (char *)&optval, sizeof(optval)) == -1)
      {

         fatal() <<"setsockopt(IPPROTO_IP, IP_MTU_DISCOVER) " << networking_last_error() << ", " << bsd_socket_error(networking_last_error());

         return false;

      }

      return true;

   }

#endif


#if defined(IP_MTU) && defined(BSD_STYLE_SOCKETS)
   
   int base_socket::IpMtu()
   {
   
      int mtu = 0;

      socklen_t len = sizeof(mtu);

      if (getsockopt(GetSocketId(), IPPROTO_IP, IP_MTU, (char *)&mtu, &len) == -1)
      {

         fatal() <<"getsockopt(IPPROTO_IP, IP_MTU) " << networking_last_error() << ", " << bsd_socket_error(networking_last_error());

      }

      return mtu;

   }

#endif


#if defined(IP_ROUTER_ALERT) && defined(BSD_STYLE_SOCKETS)
   
   bool base_socket::SetIpRouterAlert(bool x)
   {
   
      int optval = x ? 1 : 0;
   
      if (setsockopt(GetSocketId(), IPPROTO_IP, IP_ROUTER_ALERT, (char *)&optval, sizeof(optval)) == -1)
      {
   
         fatal() <<"setsockopt(IPPROTO_IP, IP_ROUTER_ALERT) " << networking_last_error() << ", " << bsd_socket_error(networking_last_error());
   
         return false;

      }

      return true;

   }

#endif


   bool base_socket::SetIpMulticastTTL(int ttl)
   {

#if defined(IP_MULTICAST_TTL) && defined(BSD_STYLE_SOCKETS)

      if (setsockopt(GetSocketId(), IPPROTO_IP, IP_MULTICAST_TTL, (char *)&ttl, sizeof(ttl)) == -1)
      {

         fatal() <<"setsockopt(IPPROTO_IP, IP_MULTICAST_TTL) " << networking_last_error() << ", " << bsd_socket_error(networking_last_error());

         return false;

      }

      return true;

#else
      
      information() << "ip option not available: IP_MULTICAST_TTL";
      
      return false;

#endif

   }


   int base_socket::IpMulticastTTL()
   {

      int ttl = 0;

#if defined(IP_MULTICAST_TTL) && defined(BSD_STYLE_SOCKETS)

      socklen_t len = sizeof(ttl);

      if (getsockopt(GetSocketId(), IPPROTO_IP, IP_MULTICAST_TTL, (char *)&ttl, &len) == -1)
      {

         fatal() <<"getsockopt(IPPROTO_IP, IP_MULTICAST_TTL)" << networking_last_error() << ", " << bsd_socket_error(networking_last_error());

      }

#else
      
      INFO(log_this, "ip option not available", 0, "IP_MULTICAST_TTL");

#endif

      return ttl;

   }


   bool base_socket::SetMulticastLoop(bool x)
   {

#if defined(IP_MULTICAST_LOOP) && defined(BSD_STYLE_SOCKETS)

      int optval = x ? 1 : 0;

      if (setsockopt(GetSocketId(), IPPROTO_IP, IP_MULTICAST_LOOP, (char *)&optval, sizeof(optval)) == -1)
      {

         fatal() <<"setsockopt(IPPROTO_IP, IP_MULTICAST_LOOP)" << networking_last_error() << ", " << bsd_socket_error(networking_last_error());

         return false;

      }

      return true;

#else
      
      INFO(log_this, "ip option not available", 0, "IP_MULTICAST_LOOP");

      return false;

#endif

   }


#ifdef LINUX

   bool base_socket::IpAddMembership(struct ip_mreqn& ref)
   {

#if defined(IP_ADD_MEMBERSHIP) && defined(BSD_STYLE_SOCKETS)

      if (setsockopt(GetSocketId(), IPPROTO_IP, IP_ADD_MEMBERSHIP, (char *)&ref, sizeof(struct ip_mreqn)) == -1)
      {

         fatal() <<"setsockopt(IPPROTO_IP, IP_ADD_MEMBERSHIP)" << networking_last_error() << ", " << bsd_socket_error(networking_last_error());

         return false;

      }

      return true;

#else

      INFO(log_this, "ip option not available", 0, "IP_ADD_MEMBERSHIP");

      return false;

#endif

   }

#endif


   bool base_socket::IpAddMembership(struct ip_mreq& ref)
   {

#if defined(IP_ADD_MEMBERSHIP) && defined(BSD_STYLE_SOCKETS)
      
      if (setsockopt(GetSocketId(), IPPROTO_IP, IP_ADD_MEMBERSHIP, (char *)&ref, sizeof(struct ip_mreq)) == -1)
      {

         fatal() <<"setsockopt(IPPROTO_IP, IP_ADD_MEMBERSHIP)" << networking_last_error() << ", " << bsd_socket_error(networking_last_error());

         return false;

      }

      return true;

#else

      INFO(log_this, "ip option not available", 0, "IP_ADD_MEMBERSHIP");

      return false;

#endif

   }


#ifdef LINUX

   bool base_socket::IpDropMembership(struct ip_mreqn& ref)
   {

#if defined(IP_DROP_MEMBERSHIP) && defined(BSD_STYLE_SOCKETS)
      
      if (setsockopt(GetSocketId(), IPPROTO_IP, IP_DROP_MEMBERSHIP, (char *)&ref, sizeof(struct ip_mreqn)) == -1)
      {
      
         fatal() <<"setsockopt(IPPROTO_IP, IP_DROP_MEMBERSHIP)" << networking_last_error() << ", " << bsd_socket_error(networking_last_error());

         return false;

      }

      return true;

#else

      INFO(log_this, "ip option not available", 0, "IP_DROP_MEMBERSHIP");

      return false;

#endif

   }

#endif


   bool base_socket::IpDropMembership(struct ip_mreq& ref)
   {

#if defined(IP_DROP_MEMBERSHIP) && defined(BSD_STYLE_SOCKETS)
      
      if (setsockopt(GetSocketId(), IPPROTO_IP, IP_DROP_MEMBERSHIP, (char *)&ref, sizeof(struct ip_mreq)) == -1)
      {

         fatal() <<"setsockopt(IPPROTO_IP, IP_DROP_MEMBERSHIP)" << networking_last_error() << ", " << bsd_socket_error(networking_last_error());

         return false;

      }

      return true;

#else

      INFO(log_this, "ip option not available", 0, "IP_DROP_MEMBERSHIP");

      return false;

#endif

   }


   /* SOCKET options */
bool base_socket::SetSoReuseaddr(bool x)
{
   return _SetSoReuseaddr(GetSocketId(), x);
}

   bool base_socket::_SetSoReuseaddr(SOCKET s, bool x)
   {

#if defined(SO_REUSEADDR) && defined(BSD_STYLE_SOCKETS)

      int optval = x ? 1 : 0;

      if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR, (char *)&optval, sizeof(optval)) == -1)
      {

         fatal() <<"setsockopt(SOL_SOCKET, SO_REUSEADDR)" << networking_last_error() << ", " << bsd_socket_error(networking_last_error());

         return false;

      }

      return true;

#else
      
      INFO(log_this, "base_socket option not available", 0, "SO_REUSEADDR");

      return false;

#endif

   }

bool base_socket::SetSoKeepalive(bool x)
{
   
   return _SetSoKeepalive(GetSocketId(), x);
}
   bool base_socket::_SetSoKeepalive(SOCKET s,bool x)
   {

#if defined(SO_KEEPALIVE) && defined(BSD_STYLE_SOCKETS)

      int optval = x ? 1 : 0;

      if (setsockopt(s, SOL_SOCKET, SO_KEEPALIVE, (char *)&optval, sizeof(optval)) == -1)
      {

         fatal() <<"setsockopt(SOL_SOCKET, SO_KEEPALIVE)" << networking_last_error() << ", " << bsd_socket_error(networking_last_error());

         return false;

      }

      return true;

#else

      INFO(log_this, "base_socket option not available", 0, "SO_KEEPALIVE");

      return false;

#endif

   }


#if defined(SO_NOSIGPIPE) && defined(BSD_STYLE_SOCKETS)
   
   
   bool base_socket::SetSoNosigpipe(bool x)
   {
   
      return _SetSoNosigpipe(GetSocketId(), x);
   
   }
   
   
   bool base_socket::_SetSoNosigpipe(SOCKET s, bool x)
   {

      int optval = x ? 1 : 0;

      if (setsockopt(s, SOL_SOCKET, SO_NOSIGPIPE, (char *)&optval, sizeof(optval)) == -1)
      {

         fatal() <<"setsockopt(SOL_SOCKET, SO_NOSIGPIPE)" << networking_last_error() << ", " << bsd_socket_error(networking_last_error());

         return false;

      }

      return true;

   }

#endif


   bool base_socket::SoAcceptconn()
   {

      int value = 0;

#if defined(SO_ACCEPTCONN) && defined(BSD_STYLE_SOCKETS)

      socklen_t len = sizeof(value);

      if (getsockopt(GetSocketId(), SOL_SOCKET, SO_ACCEPTCONN, (char *)&value, &len) == -1)
      {

         fatal() <<"getsockopt(SOL_SOCKET, SO_ACCEPTCONN)" << networking_last_error() << ", " << bsd_socket_error(networking_last_error());

      }

#else

      INFO(log_this, "base_socket option not available", 0, "SO_ACCEPTCONN");

#endif

      return value ? true : false;

   }


#if defined(SO_BSDCOMPAT) && defined(BSD_STYLE_SOCKETS)
   
   bool base_socket::SetSoBsdcompat(bool x)
   {
   
      int optval = x ? 1 : 0;
   
      if (setsockopt(GetSocketId(), SOL_SOCKET, SO_BSDCOMPAT, (char *)&optval, sizeof(optval)) == -1)
      {

         fatal() <<"setsockopt(SOL_SOCKET, SO_BSDCOMPAT)" << networking_last_error() << ", " << bsd_socket_error(networking_last_error());

         return false;

      }

      return true;

   }

#endif


#if defined(SO_BINDTODEVICE) && defined(BSD_STYLE_SOCKETS)
   
   bool base_socket::SetSoBindtodevice(const string & intf)
   {
   
      if (setsockopt(GetSocketId(), SOL_SOCKET, SO_BINDTODEVICE, (char *) (const char *)intf, (unsigned int) intf.length()) == -1)
      {

         fatal() <<"setsockopt(SOL_SOCKET, SO_BINDTODEVICE)" << networking_last_error() << ", " << bsd_socket_error(networking_last_error());

         return false;

      }

      return true;

   }

#endif


   bool base_socket::SetSoBroadcast(bool x)
   {

#if defined(SO_BROADCAST) && defined(BSD_STYLE_SOCKETS)
      
      int optval = x ? 1 : 0;
      
      if (setsockopt(GetSocketId(), SOL_SOCKET, SO_BROADCAST, (char *)&optval, sizeof(optval)) == -1)
      {

         fatal() <<"setsockopt(SOL_SOCKET, SO_BROADCAST)" << networking_last_error() << ", " << bsd_socket_error(networking_last_error());

         return false;

      }

      return true;

#else
      
      INFO(log_this, "base_socket option not available", 0, "SO_BROADCAST");
      
      return false;

#endif

   }


   bool base_socket::SetSoDebug(bool x)
   {

#if defined(SO_DEBUG) && defined(BSD_STYLE_SOCKETS)
      
      int optval = x ? 1 : 0;
      
      if (setsockopt(GetSocketId(), SOL_SOCKET, SO_DEBUG, (char *)&optval, sizeof(optval)) == -1)
      {

         fatal() <<"setsockopt(SOL_SOCKET, SO_DEBUG)" << networking_last_error() << ", " << bsd_socket_error(networking_last_error());

         return false;

      }

      return true;

#else
      
      INFO(log_this, "base_socket option not available", 0, "SO_DEBUG");

      return false;

#endif

   }


   int base_socket::SoError()
   {

      int value = 0;

#if defined(SO_ERROR) && defined(BSD_STYLE_SOCKETS)
      
      socklen_t len = sizeof(value);

      if (getsockopt(GetSocketId(), SOL_SOCKET, SO_ERROR, (char *)&value, &len) == -1)
      {

         fatal() <<"getsockopt(SOL_SOCKET, SO_ERROR)" << networking_last_error() << ", " << bsd_socket_error(networking_last_error());

      }

#else

      INFO(log_this, "base_socket option not available", 0, "SO_ERROR");

#endif

      return value;

   }


   bool base_socket::SetSoDontroute(bool x)
   {

#if defined(SO_DONTROUTE) && defined(BSD_STYLE_SOCKETS)
      
      int optval = x ? 1 : 0;

      if (setsockopt(GetSocketId(), SOL_SOCKET, SO_DONTROUTE, (char *)&optval, sizeof(optval)) == -1)
      {

         fatal() <<"setsockopt(SOL_SOCKET, SO_DONTROUTE)" << networking_last_error() << ", " << bsd_socket_error(networking_last_error());

         return false;

      }
      
      return true;

#else
      
      INFO(log_this, "base_socket option not available", 0, "SO_DONTROUTE");
      
      return false;

#endif

   }


   bool base_socket::SetSoLinger(int onoff, int linger)
   {

#if defined(SO_LINGER) && defined(BSD_STYLE_SOCKETS)

      struct linger stl;

      stl.l_onoff = (u_short) onoff;

      stl.l_linger = (u_short) linger;

      if (setsockopt(GetSocketId(), SOL_SOCKET, SO_LINGER, (char *)&stl, sizeof(stl)) == -1)
      {

         fatal() <<"setsockopt(SOL_SOCKET, SO_LINGER)" << networking_last_error() << ", " << bsd_socket_error(networking_last_error());

         return false;

      }

      return true;

#else
      
      INFO(log_this, "base_socket option not available", 0, "SO_LINGER");
      
      return false;

#endif

   }


   bool base_socket::SetSoOobinline(bool x)
   {

#if defined(SO_OOBINLINE) && defined(BSD_STYLE_SOCKETS)
      
      int optval = x ? 1 : 0;

      if (setsockopt(GetSocketId(), SOL_SOCKET, SO_OOBINLINE, (char *)&optval, sizeof(optval)) == -1)
      {

         fatal() <<"setsockopt(SOL_SOCKET, SO_OOBINLINE)" << networking_last_error() << ", " << bsd_socket_error(networking_last_error());

         return false;

      }

      return true;

#else

      INFO(log_this, "base_socket option not available", 0, "SO_OOBINLINE");

      return false;

#endif

   }


#if defined(SO_PASSCRED) && defined(BSD_STYLE_SOCKETS)

   bool base_socket::SetSoPasscred(bool x)
   {
      int optval = x ? 1 : 0;

      if (setsockopt(GetSocketId(), SOL_SOCKET, SO_PASSCRED, (char *)&optval, sizeof(optval)) == -1)
      {
      
         fatal() <<"setsockopt(SOL_SOCKET, SO_PASSCRED)" << networking_last_error() << ", " << bsd_socket_error(networking_last_error());
         
         return false;

      }

      return true;

   }

#endif


#if defined(SO_PEERCRED) && defined(BSD_STYLE_SOCKETS)

   bool base_socket::SoPeercred(struct ::ucred & ucr)
   {

      if (setsockopt(GetSocketId(), SOL_SOCKET, SO_PEERCRED, (char *)&ucr, sizeof(ucr)) == -1)
      {
      
         fatal() <<"setsockopt(SOL_SOCKET, SO_PEERCRED)" << networking_last_error() << ", " << bsd_socket_error(networking_last_error());
         
         return false;

      }

      return true;

   }

#endif


#if defined(SO_PRIORITY) && defined(BSD_STYLE_SOCKETS)

   bool base_socket::SetSoPriority(int x)
   {
      
      if (setsockopt(GetSocketId(), SOL_SOCKET, SO_PRIORITY, (char *)&x, sizeof(x)) == -1)
      {
      
         fatal() <<"setsockopt(SOL_SOCKET, SO_PRIORITY)" << networking_last_error() << ", " << bsd_socket_error(networking_last_error());
         
         return false;

      }

      return true;

   }

#endif


   bool base_socket::SetSoRcvlowat(int x)
   {

#if defined(SO_RCVLOWAT) && defined(BSD_STYLE_SOCKETS)

      if (setsockopt(GetSocketId(), SOL_SOCKET, SO_RCVLOWAT, (char *)&x, sizeof(x)) == -1)
      {

         fatal() <<"setsockopt(SOL_SOCKET, SO_RCVLOWAT)" << networking_last_error() << ", " << bsd_socket_error(networking_last_error());

         return false;

      }

      return true;

#else
      
      INFO(log_this, "base_socket option not available", 0, "SO_RCVLOWAT");
      
      return false;

#endif

   }


   bool base_socket::SetSoSndlowat(int x)
   {

#if defined(SO_SNDLOWAT) && defined(BSD_STYLE_SOCKETS)

      if (setsockopt(GetSocketId(), SOL_SOCKET, SO_SNDLOWAT, (char *)&x, sizeof(x)) == -1)
      {

         fatal() <<"setsockopt(SOL_SOCKET, SO_SNDLOWAT)" << networking_last_error() << ", " << bsd_socket_error(networking_last_error());

         return false;

      }

      return true;

#else
      
      INFO(log_this, "base_socket option not available", 0, "SO_SNDLOWAT");
      
      return false;

#endif

   }


   bool base_socket::SetSoRcvtimeo(struct timeval& tv)
   {

#if defined(SO_RCVTIMEO) && defined(BSD_STYLE_SOCKETS)

      if (setsockopt(GetSocketId(), SOL_SOCKET, SO_RCVTIMEO, (char *)&tv, sizeof(tv)) == -1)
      {

         fatal() <<"setsockopt(SOL_SOCKET, SO_RCVTIMEO)" << networking_last_error() << ", " << bsd_socket_error(networking_last_error());

         return false;

      }

      return true;

#else
      
      INFO(log_this, "base_socket option not available", 0, "SO_RCVTIMEO");
      
      return false;

#endif

   }


   bool base_socket::SetSoSndtimeo(struct timeval& tv)
   {

#if defined(SO_SNDTIMEO) && defined(BSD_STYLE_SOCKETS)

      if (setsockopt(GetSocketId(), SOL_SOCKET, SO_SNDTIMEO, (char *)&tv, sizeof(tv)) == -1)
      {

         fatal() <<"setsockopt(SOL_SOCKET, SO_SNDTIMEO)" << networking_last_error() << ", " << bsd_socket_error(networking_last_error());

         return false;

      }

      return true;

#else
      
      INFO(log_this, "base_socket option not available", 0, "SO_SNDTIMEO");
      
      return false;

#endif

   }


   bool base_socket::SetSoRcvbuf(int x)
   {

#if defined(SO_RCVBUF) && defined(BSD_STYLE_SOCKETS)

      if (setsockopt(GetSocketId(), SOL_SOCKET, SO_RCVBUF, (char *)&x, sizeof(x)) == -1)
      {

         fatal() <<"setsockopt(SOL_SOCKET, SO_RCVBUF)" << networking_last_error() << ", " << bsd_socket_error(networking_last_error());

         return false;

      }

      return true;

#else
      
      INFO(log_this, "base_socket option not available", 0, "SO_RCVBUF");
      
      return false;

#endif

   }


   int base_socket::SoRcvbuf()
   {
      int value = 0;

#if defined(SO_RCVBUF) && defined(BSD_STYLE_SOCKETS)
      
      socklen_t len = sizeof(value);

      if (getsockopt(GetSocketId(), SOL_SOCKET, SO_RCVBUF, (char *)&value, &len) == -1)
      {

         fatal() <<"getsockopt(SOL_SOCKET, SO_RCVBUF)" << networking_last_error() << ", " << bsd_socket_error(networking_last_error());

      }

#else

      INFO(log_this, "base_socket option not available", 0, "SO_RCVBUF");

#endif

      return value;

   }


#if defined(SO_RCVBUFFORCE) && defined(BSD_STYLE_SOCKETS)

   bool base_socket::SetSoRcvbufforce(int x)
   {

      if (setsockopt(GetSocketId(), SOL_SOCKET, SO_RCVBUFFORCE, (char *)&x, sizeof(x)) == -1)
      {

         fatal() <<"setsockopt(SOL_SOCKET, SO_RCVBUFFORCE)" << networking_last_error() << ", " << bsd_socket_error(networking_last_error());
         
         return false;

      }

      return true;

   }

#endif


   bool base_socket::SetSoSndbuf(int x)
   {

#if defined(SO_SNDBUF) && defined(BSD_STYLE_SOCKETS)

      if (setsockopt(GetSocketId(), SOL_SOCKET, SO_SNDBUF, (char *)&x, sizeof(x)) == -1)
      {

         fatal() <<"setsockopt(SOL_SOCKET, SO_SNDBUF)" << networking_last_error() << ", " << bsd_socket_error(networking_last_error());

         return false;

      }

      return true;

#else
      
      INFO(log_this, "base_socket option not available", 0, "SO_SNDBUF");

      return false;

#endif

   }


   int base_socket::SoSndbuf()
   {
      
      int value = 0;

#if defined(SO_SNDBUF) && defined(BSD_STYLE_SOCKETS)
      
      socklen_t len = sizeof(value);

      if (getsockopt(GetSocketId(), SOL_SOCKET, SO_SNDBUF, (char *)&value, &len) == -1)
      {

         fatal() <<"getsockopt(SOL_SOCKET, SO_SNDBUF)" << networking_last_error() << ", " << bsd_socket_error(networking_last_error());

      }

#else

      INFO(log_this, "base_socket option not available", 0, "SO_SNDBUF");

#endif

      return value;

   }


#if defined(SO_SNDBUFFORCE) && defined(BSD_STYLE_SOCKETS)

   bool base_socket::SetSoSndbufforce(int x)
   {

      if (setsockopt(GetSocketId(), SOL_SOCKET, SO_SNDBUFFORCE, (char *)&x, sizeof(x)) == -1)
      {

         fatal() <<"setsockopt(SOL_SOCKET, SO_SNDBUFFORCE)" << networking_last_error() << ", " << bsd_socket_error(networking_last_error());
         
         return false;

      }

      return true;

   }

#endif


#if defined(SO_TIMESTAMP) && defined(BSD_STYLE_SOCKETS)
   
   bool base_socket::SetSoTimestamp(bool x)
   {
   
      int optval = x ? 1 : 0;
   
      if (setsockopt(GetSocketId(), SOL_SOCKET, SO_TIMESTAMP, (char *)&optval, sizeof(optval)) == -1)
      {

         fatal() <<"setsockopt(SOL_SOCKET, SO_TIMESTAMP)" << networking_last_error() << ", " << bsd_socket_error(networking_last_error());

         return false;

      }

      return true;

   }

#endif


   int base_socket::SoType()
   {
      int value = 0;

#if defined(SO_TYPE) && defined(BSD_STYLE_SOCKETS)
      
      socklen_t len = sizeof(value);
      
      if (getsockopt(GetSocketId(), SOL_SOCKET, SO_TYPE, (char *)&value, &len) == -1)
      {

         fatal() <<"getsockopt(SOL_SOCKET, SO_TYPE)" << networking_last_error() << ", " << bsd_socket_error(networking_last_error());

      }

#else

      INFO(log_this, "base_socket option not available", 0, "SO_TYPE");

#endif

      return value;

   }


   void base_socket::Subscribe(int atom)
   {
      socket_handler()->Subscribe(atom, this);
   }


   void base_socket::Unsubscribe(int atom)
   {
      socket_handler()->Unsubscribe(atom, this);
   }


   void base_socket::OnTrigger(int, const trigger_data&)
   {
   }


   void base_socket::OnCancelled(SOCKET)
   {
   }


   class ::time base_socket::get_last_interaction_time() const
   {

      return maximum(maximum(m_timeLastRead, m_timeLastWrite), m_timeConnectionStart);
   
   }


   void base_socket::set_connection_start_time()
   {
      
      m_timeConnectionStart.Now();

   }


   void base_socket::set_connection_last_read_time()
   {

      m_timeConnectionLastRead.Now();

   }


   void base_socket::set_connection_last_write_time()
   {

      m_timeConnectionLastWrite.Now();

   }


   void base_socket::set_maximum_connection_time(const class time & time)
   {

      m_timeConnectionMaximum = time;

   }


   void base_socket::set_start_time()
   {

      m_timeStart.Now();
      m_timeConnectionLastRead.Now();
      m_timeConnectionLastWrite.Now();

      //set_connection_last_operation();

   }


   void base_socket::set_keep_connection_after_last_io_time(const class time & time)
   {

      m_timeKeepConnectionAfterLastIO = time;

      ::pointer < ::sockets_bsd::socket_handler > phandler = socket_handler();

      if (phandler)
      {

         if (m_timeKeepConnectionAfterLastIO > 0_s)
         {

            phandler->socket_id_list_add(GetSocketId(), e_list_timeout);

         }
         else
         {

            phandler->socket_id_list_erase(GetSocketId(), e_list_timeout);

         }

      }

   }


   //void base_socket::set_keep_connection_after_last_write_time(const class time& time)
   //{

   //   m_timeKeepConnectionAfterLastWrite = time;

   //   ::pointer < ::sockets_bsd::socket_handler > phandler = socket_handler();

   //   if (phandler)
   //   {

   //      if (m_timeKeepConnectionAfterLastRead > 0_s
   //         || m_timeKeepConnectionAfterLastWrite > 0_s)
   //      {

   //         phandler->socket_id_list_add(GetSocketId(), e_list_timeout);

   //      }
   //      else
   //      {

   //         phandler->socket_id_list_erase(GetSocketId(), e_list_timeout);

   //      }

   //   }

   //}

   void base_socket::on_timeout()
   {

      m_estatus = error_on_connection_timeout;

   }


   void base_socket::on_connection_timeout()
   {

   }


   bool base_socket::has_timed_out()
   {

      if (is_connecting())
      {

         if (m_timeConnectionMaximum > 0_s)
         {

            auto tElapsed = m_timeConnectionStart.elapsed();

            if (tElapsed > m_timeConnectionMaximum)
            {

               return true;

            }

         }

      }
      else
      {
         
         if (m_timeKeepConnectionAfterLastIO > 0_s)
         {

            auto tIO = maximum(
               m_timeConnectionLastRead,
               m_timeConnectionLastWrite);

            auto tElapsed = tIO.elapsed();

            if (tElapsed > m_timeKeepConnectionAfterLastIO)
            {

               return true;

            }

         }

         //if (m_timeKeepConnectionAfterLastWrite > 0_s
         //   && m_timeConnectionLastWrite > 0_s)
         //{

         //   auto tElapsed = m_timeConnectionLastWrite.elapsed();

         //   if (tElapsed > m_timeKeepConnectionAfterLastWrite)
         //   {

         //      return true;

         //   }

         //}

      }

      return false;

   }


   void base_socket::on_read(const void * pdata, memsize n )
   {

      char * buf = (char *) pdata;

      if (m_pmemfileInput != nullptr)
      {

         m_pmemfileInput->write({ buf, n });

      }

      //if (m_iKeepAliveCount > 0)
      //{

      //   output_debug_string("m_iKeepAliveCount > 0");

      //}

      //if (base_socket_interface() && base_socket_interface()->m_iKeepAliveCount > 0)
      //{

      //   output_debug_string("base_socket_interface()->m_iKeepAliveCount > 0");

      //}

      if (LineProtocol())
      {
         buf[n] = 0;
         int i = 0;
         if (m_skip_c && (buf[i] == 13 || buf[i] == 10) && buf[i] != m_c)
         {
            m_skip_c = false;
            i++;
         }
         int x = i;
         for (; i < n && LineProtocol(); i++)
         {
            while ((buf[i] == 13 || buf[i] == 10) && LineProtocol())
            {
               char c = buf[i];
               buf[i] = 0;
               if (buf[x])
               {
                  m_line += (buf + x);
               }
               OnLine( m_line );
               if(IsCloseAndDelete())
                  break;
               i++;
               m_skip_c = true;
               m_c = c;
               if (i < n && (buf[i] == 13 || buf[i] == 10) && buf[i] != c)
               {
                  m_skip_c = false;
                  i++;
               }
               x = i;
               m_line = "";
            }
            if (!LineProtocol())
            {

               break;

            }
            
            if(IsCloseAndDelete())
            {
            
               break;

            }

         }

         if(IsCloseAndDelete())
         {

            return;

         }

         if (!LineProtocol())
         {

            if (i < n)
            {

               OnRawData(buf + i, n - i);

            }

         }
         else if (buf[x])
         {

            m_line += (buf + x);

         }

      }
      else
      {

         OnRawData(buf, n);

      }

   }


   void base_socket::SetLineProtocol(bool x)
   {

      m_bLineProtocol = x;

   }


   bool base_socket::LineProtocol()
   {

      return m_bLineProtocol;

   }


   string base_socket::as_string() const
   {

      return ::object::as_string();

   }


   void base_socket::OnRawData(char * buf, memsize len)
   {

      if(m_pcallback != nullptr)
      {

         m_pcallback->OnRawData(this, buf, len);

      }

      base_socket_interface()->OnRawData(buf, len);

   }


   ::networking::port_t base_socket::GetRemotePort()
   {

      return m_paddressRemote->get_service_number();

   }


   ::pointer<::networking::address>base_socket::GetRemoteAddress()
   {

      return m_paddressRemote;

   }


   ::networking::port_t base_socket::GetLocalPort()
   {

      throw ::interface_only();

      return 0;

   }


   ::pointer<::networking::address>base_socket::GetLocalAddress()
   {

      throw ::interface_only();

      return nullptr;

   }


   void     base_socket::run()
   {

      //return ::success;

   }


   //bool base_socket::step()
   //{

   //   //return ::e_status_no_work;

   //   return false;

   //}


   string base_socket::get_short_description()
   {

      auto pnetworking = system()->networking();

      return pnetworking->canonical_name(GetRemoteAddress());

   }


   void base_socket::destroy_ssl_session()
   {

#ifdef BSD_STYLE_SOCKETS

      _synchronous_lock synchronouslock(this->synchronization());

      if (m_psslcontext->m_pclientcontext->session() != nullptr)
      {

         m_psslcontext->m_pclientcontext.release();

      }

#endif

   }


   void base_socket::get_ssl_session()
   {

      _synchronous_lock synchronouslock(this->synchronization());

#ifdef BSD_STYLE_SOCKETS
      if (m_psslcontext->m_pclientcontext->m_psslsession == nullptr)
      {

         m_psslcontext->m_pclientcontext->m_psslsession = SSL_get1_session(m_psslcontext->m_ssl);

      }
#endif

   }


   ::string_array & base_socket::debugstra()
   {

      return m_straDebug;

   }


   //virtual ::string debug_text();


   
   void base_socket::write(const void * p, ::memsize s)
   {


   }


   void base_socket::SetTrafficMonitor(file_pointer p)
   {
      
      m_pfileTrafficMonitor = p; 
   
   }


   /** All traffic will be written to this IFile, if set. */
   file_pointer base_socket::GetTrafficMonitor() 
   {
      
      return m_pfileTrafficMonitor; 
   
   }


} // namespace sockets_bsd



