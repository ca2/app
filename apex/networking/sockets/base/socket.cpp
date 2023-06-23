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
////#include "apex/networking/sockets/_sockets.h"
#include "socket.h"
#include "socket_handler.h"
#include "acme/exception/interface_only.h"
//#ifdef _WIN32
//#elif defined(LINUX)
//#include <netdb.h>
//#include <fcntl.h>
//#else
//#include <netdb.h>
//#include <fcntl.h>
//#endif
//////#include <ctype.h>
//#include <time.h>
//
//
//#ifdef PARALLELIZATION_PTHREAD
//
//
//#include "acme/operating_system/ansi/_pthread.h"
//
//
//#endif
//
//
//#ifdef BSD_STYLE_SOCKETS
//#include <openssl/ssl.h>
//#endif

namespace sockets
{


   //::pointer< ::mutex > base_socket::s_pmutex = nullptr;


   base_socket::base_socket() //:
      //m_bDelete(false)
      //,m_bCloseAndDelete(false)
      //,m_timeCreate(time(nullptr))
      //,m_psocketParent(nullptr)
      //,m_bDisableRead(false)
      //,m_bConnected(false)
      //,m_bErasedByHandler(false)
      //,m_timeClose(0)
      //,m_bLost(false)
      //,m_bEnableSsl(false)
      //,m_bSsl(false)
      //,m_bSslServer(false)
      //,m_bIpv6(false)
      //,m_bSocks4(false)
      //,m_b_chunked(false)
      //,m_socket(INVALID_SOCKET)
      ////,m_socks4_host(h.GetSocks4Host())
      ////,m_socks4_port(h.GetSocks4Port())
      ////,m_socks4_userid(h.GetSocks4Userid())
      //,m_socks4_port(0)
      //,m_bDetach(false)
      //,m_bDetached(false)
      //// Line protocol
      //,m_bLineProtocol(false)
      //,m_skip_c(false)
//#if !defined(BSD_STYLE_SOCKETS)
      //,m_event(h.get_())
//#endif
   {

#ifdef WINRT_SOCKETS
      m_bErrorReading = false;
      m_bErrorWriting = false;
      m_bWaitingResponse = false;
      m_bExpectResponse = false;
      m_bExpectRequest = false;
      m_bReading = false;
      m_bWriting = false;
#endif
//      m_pmemfileInput = nullptr;
//      m_iBindPort    = -1;
//      m_timeStart.Now();
//      m_pcallback    = nullptr;
//      m_bEnablePool  = true;
//
//      m_timeConnectionMaximum = 30_s;
//      m_timeMaximum = 30_s;

   }


   base_socket::~base_socket()
   {

   }


   void base_socket::initialize_socket(base_socket_handler* phandler)
   {

      base_socket_composite()->initialize_socket(phandler);

      //::object::initialize(phandler);

      //m_psockethandler = phandler;

      //m_socks4_host = m_psockethandler->GetSocks4Host();
      //m_socks4_port = m_psockethandler->GetSocks4Port();
      //m_socks4_userid = m_psockethandler->GetSocks4Userid();

   }


   base_socket * base_socket::base_socket_composite()
   {

      return nullptr;

   }


   const base_socket * base_socket::base_socket_composite() const
   {

      return nullptr;

   }


   ::networking::networking * base_socket::networking()
   {

      return base_socket_composite()->networking();

   }



   enum_trace_category base_socket::trace_category() const
   {

      return base_socket_composite()->trace_category();

   }


   //void base_socket::on_finalize()
   //{

   //   //__release(m_psocketthread);

   //   ::object::on_finalize();


   //}


   void base_socket::Init()
   {

      base_socket_composite()->Init();

   }


   void base_socket::OnRead()
   {

      base_socket_composite()->OnRead();

   }


   void base_socket::OnWrite()
   {

      base_socket_composite()->OnWrite();

   }


   void base_socket::OnException()
   {
      

#ifdef BSD_STYLE_SOCKETS

      // %! exception doesn't always mean something bad happened, this code should be reworked
      // errno valid here?
      int err = SoError();
      //fatal() <<"exception on select "<< err <<" "<<  bsd_socket_error(err);

#endif

      //SetCloseAndDelete();

      base_socket_composite()->OnException();


   }


   void base_socket::OnDelete()
   {

      //base_socket_composite()->OnDelete();

   }


   void base_socket::OnConnect()
   {

      //base_socket_composite()->OnConnect();

   }


   void base_socket::OnAccept()
   {

      //base_socket_composite()->OnAccept();

   }


   void base_socket::close()
   {

      base_socket_composite()->close();

#ifdef BSD_STYLE_SOCKETS

      //m_psslcontext.release();

#endif

   }

   void base_socket::_001InitSSLServer()
   {



   }


   void base_socket::set_end()
   {

      base_socket_composite()->set_end();

   }


   bool base_socket::is_end() const
   {

      return base_socket_composite()->is_end();

   }


   ::networking::port_t base_socket::get_bind_port() const
   {

      return base_socket_composite()->get_bind_port();

   }



   //i32 base_socket::close_socket(socket_id s)
   //{

   //   UNREFERENCED_PARAMETER(s);

   //   return 0;

   //}


   bool base_socket::is_connecting()
   {
      
      return base_socket_composite()->is_connecting();

   }


   /*   socket_id base_socket::CreateSocket(int af,int iType, const ::string & strProtocol)
   {
   struct protoent *point = nullptr;
   socket_id s;

   m_iSocketType = iType;
   m_strSocketProtocol = strProtocol;
   if (strProtocol.length())
   {
   point = getprotobyname( strProtocol );
   if (!point_i32)
   {
   fatal() <<"getprotobyname" << Errno << ", " << bsd_socket_error(Errno);
   SetCloseAndDelete();
   throw ::exception(::exception(string("getprotobyname() failed: ") + bsd_socket_error(Errno)));
   return INVALID_SOCKET;
   }
   }
   int protno = point_i32 ? point_i32 -> p_proto : 0;

   s = ::base_socket(af, iType, protno);
   if (s == INVALID_SOCKET)
   {
   fatal() <<"base_socket" << Errno << ", " << bsd_socket_error(Errno);
   SetCloseAndDelete();
   throw ::exception(::exception(string("base_socket() failed: ") + bsd_socket_error(Errno)));
   return INVALID_SOCKET;
   }
   attach(s);
   OnOptions(af, iType, protno, s);
   attach(INVALID_SOCKET);
   return s;
   }
   */


   //void base_socket::attach(socket_id s)
   //{

   //   m_socket = s;

   //   if (topic_text() == nullptr)
   //   {
   //      
   //       //string strTopicText;

   //       //strTopicText.format("socket_%d> ", s);

   //       //set_topic_text(strTopicText);

   //   }

   //}


   //iptr base_socket::get_socket_id()
   //{
   //   throw interface_only();

   //   return -1;
   ////   return m_socket;
   //}


   void base_socket::SetDeleteByHandler(bool x)
   {
      //m_bDelete = x;

      base_socket_composite()->SetDeleteByHandler(x);

   }


   bool base_socket::DeleteByHandler()
   {
      //return m_bDelete;
      return base_socket_composite()->DeleteByHandler();

   }


   void base_socket::SetCloseAndDelete(bool bCloseAndDelete)
   {

      base_socket_composite()->SetCloseAndDelete(bCloseAndDelete);

      //if (is_different(bCloseAndDelete, m_bCloseAndDelete))
      //{

      //  if(socket_handler())
      //  {

      //     socket_handler()->socket_id_list_modify(m_socket, e_list_close, bCloseAndDelete);

      //  }

      //  m_bCloseAndDelete = bCloseAndDelete;

      //  if (bCloseAndDelete)
      //  {

      //     m_timeClose = time(nullptr);

      //  }

      //}

   }


   bool base_socket::IsCloseAndDelete()
   {
      
      //return m_bCloseAndDelete;

      return base_socket_composite()->IsCloseAndDelete();

   }


   void base_socket::SetRemoteHostname(::networking::address * paddress) //struct sockaddr* sa, socklen_t l)
   {

      //m_paddressRemote = ad;

      base_socket_composite()->SetRemoteHostname(paddress);

   }


   ::networking::address_pointer base_socket::GetRemoteHostname()
   {

      //return m_paddressRemote;
      return base_socket_composite()->GetRemoteHostname();

   }


   base_socket_handler* base_socket::socket_handler() const
   {

      //if (IsDetached())
      //{

      //   return m_phandlerSlave.m_p;

      //}

      //return m_psockethandler;

      return base_socket_composite()->socket_handler();

   }


   base_socket_handler* base_socket::master_socket_handler() const
   {
      
      //return m_psockethandler;

      return base_socket_composite()->master_socket_handler();

   }


   memory_file * base_socket::get_input_memory_file()
   {

      return base_socket_composite()->get_input_memory_file();

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
   struct sockaddr_in *sa = (struct sockaddr_in *)point_i32;
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

      return base_socket_composite()->SetNonblocking(bNb);

//      m_bNonBlocking = bNb;
//
//#ifdef BSD_STYLE_SOCKETS
//#ifdef _WIN32
//      unsigned long l = bNb ? 1 : 0;
//      int n = ioctlsocket(m_socket, FIONBIO, &l);
//      if (n != 0)
//      {
//         information() << "ioctlsocket(FIONBIO) " << Errno;
//         return false;
//      }
//      return true;
//#else
//      if (bNb)
//      {
//         if (fcntl(m_socket, F_SETFL, O_NONBLOCK) == -1)
//         {
//            error() <<"fcntl(F_SETFL, O_NONBLOCK) " << Errno << " " << bsd_socket_error(Errno);
//            return false;
//         }
//      }
//      else
//      {
//         if (fcntl(m_socket, F_SETFL, 0) == -1)
//         {
//            error() <<"fcntl(F_SETFL, 0)" << Errno << " " << bsd_socket_error(Errno);
//            return false;
//         }
//      }
//      return true;
//#endif
//#else
//      return false;
//
//#endif

      //return false;
   }


   //bool base_socket::SetNonblocking(bool bNb, socket_id s)
   //{

   //   UNREFERENCED_PARAMETER(bNb);
   //   UNREFERENCED_PARAMETER(s);

   //   return false;

   //   /*   #ifdef _WIN32
   //      unsigned long l = bNb ? 1 : 0;
   //      int n = ioctlsocket(s, FIONBIO, &l);
   //      if (n != 0)
   //      {
   //      ERR(log_this, "ioctlsocket(FIONBIO)", Errno, "");
   //      return false;
   //      }
   //      return true;
   //      #else
   //      if (bNb)
   //      {
   //      if (fcntl(s, F_SETFL, O_NONBLOCK) == -1)
   //      {
   //      error() <<"fcntl(F_SETFL, O_NONBLOCK)" << Errno << ", " << bsd_socket_error(Errno;
   //      return false;
   //      }
   //      }
   //      else
   //      {
   //      if (fcntl(s, F_SETFL, 0) == -1)
   //      {
   //      error() <<"fcntl(F_SETFL, 0)" << Errno << ", " << bsd_socket_error(Errno;
   //      return false;
   //      }
   //      }
   //      return true;
   //      #endif*/
   //}


   void base_socket::Set(bool bRead, bool bWrite, bool bException)
   {
      //socket_handler()->set(m_socket, bRead, bWrite, bException);

      base_socket_composite()->Set(bRead, bWrite, bException);

   }


   bool base_socket::Ready()
   {
      //if (m_socket != INVALID_SOCKET && !IsCloseAndDelete())
      //   return true;
      return base_socket_composite()->Ready();

   }


   bool base_socket::is_valid()
   {

      return base_socket_composite()->is_valid();

   }


   void base_socket::OnLine(const string & str)
   {

      base_socket_composite()->OnLine(str);

   }


   bool base_socket::on_select_idle()
   {
      
      return base_socket_composite()->on_select_idle();

   }


   void base_socket::OnConnectFailed()
   {

      base_socket_composite()->OnConnectFailed();

   }


   base_socket *base_socket::get_parent()
   {
      //return m_psocketParent;

      return base_socket_composite()->get_parent();

   }


   void base_socket::set_parent(base_socket * psocketParent)
   {
      //m_psocketParent = psocketParent;

      base_socket_composite()->set_parent(psocketParent);

   }


   ::networking::port_t base_socket::GetPort()
   {

      warning() <<"GetPort only implemented for listen_socket";

      return base_socket_composite()->GetPort();

   }


//   void base_socket::OnOptions(int family, int type, int protocol, SOCKET s)
//   {
//
//
//   }


   bool base_socket::OnConnectRetry()
   {

      return base_socket_composite()->OnConnectRetry();

   }


   void base_socket::OnReconnect()
   {

      base_socket_composite()->OnReconnect();

   }


   time_t base_socket::Uptime()
   {
      
      //return time(nullptr) - m_timeCreate;

      return base_socket_composite()->Uptime();

   }


   void base_socket::SetIpv6(bool bIpv6)
   {
      
      //m_bIpv6 = bIpv6;
      base_socket_composite()->SetIpv6(bIpv6);

   }


   bool base_socket::IsIpv6()
   {
      
      //return m_bIpv6;

      return base_socket_composite()->IsIpv6();

   }


   void base_socket::DisableRead(bool x)
   {

      //m_bDisableRead = x;
      base_socket_composite()->DisableRead(x);

   }


   bool base_socket::IsDisableRead()
   {

      //return m_bDisableRead;

      return base_socket_composite()->IsDisableRead();

   }


   void base_socket::SetConnected(bool bConnected)
   {

      //m_bConnected = bConnected;
      base_socket_composite()->SetConnected(bConnected);

   }


   bool base_socket::IsConnected()
   {

      //return m_bConnected;

      //return;

      return base_socket_composite()->IsConnected();

   }


   void base_socket::OnDisconnect()
   {

      base_socket_composite()->OnDisconnect();

   }


   void base_socket::SetLost()
   {

      //m_bLost = true;
      base_socket_composite()->SetLost();

   }


   bool base_socket::Lost()
   {
      
      //return m_bLost;

      return base_socket_composite()->Lost();

   }


   void base_socket::SetErasedByHandler(bool bErasedByHandler)
   {

      //m_bErasedByHandler = bErasedByHandler;
      base_socket_composite()->SetErasedByHandler(bErasedByHandler);

   }


   bool base_socket::ErasedByHandler()
   {

      //return m_bErasedByHandler;

      return base_socket_composite()->ErasedByHandler();

   }


   time_t base_socket::TimeSinceClose()
   {
      
      //return time(nullptr) - m_timeClose;

      return base_socket_composite()->TimeSinceClose();

   }


   void base_socket::SetClientRemoteAddress(::networking::address *paddress)
   {

      /*      if (!ad.IsValid())
      {
      error() <<"SetClientRemoteAddress", 0, "remote address not valid";
      }*/

      //m_paddressRemoteClient = paddress;

      base_socket_composite()->SetClientRemoteAddress(paddress);

   }


   ::networking::address_pointer base_socket::GetClientRemoteAddress()
   {

      /*      if (m_addressRemoteClient.m_p == nullptr)
      {
      error() <<"GetClientRemoteAddress", 0, "remote address not yet set";
      }*/

      //return m_addressRemoteClient;

      //return m_paddressRemoteClient;
      return base_socket_composite()->GetClientRemoteAddress();

   }


   u64 base_socket::GetBytesSent(bool b)
   {
      
      return base_socket_composite()->GetBytesSent(b);

   }


   u64 base_socket::GetBytesReceived(bool b)
   {
      
      return base_socket_composite()->GetBytesReceived(b);

   }


   void base_socket::OnSSLConnect()
   {

      base_socket_composite()->OnSSLConnect();

   }


   void base_socket::OnSSLAccept()
   {

      base_socket_composite()->OnSSLAccept();

   }


   bool base_socket::SSLNegotiate()
   {

      return base_socket_composite()->SSLNegotiate();

   }


   void base_socket::OnSSLConnectFailed()
   {

      base_socket_composite()->OnSSLConnectFailed();

   }


   void base_socket::OnSSLAcceptFailed()
   {

      base_socket_composite()->OnSSLAcceptFailed();

   }


   bool base_socket::IsSSL()
   {

      return base_socket_composite()->IsSSL();

   }


   void base_socket::EnableSSL(bool bEnable)
   {

      base_socket_composite()->EnableSSL(bEnable);

   }


   bool base_socket::IsSSLNegotiate()
   {

      return base_socket_composite()->IsSSLNegotiate();

   }


   void base_socket::SetSSLNegotiate(bool bSslNegotiate)
   {
      
      base_socket_composite()->SetSSLNegotiate(bSslNegotiate);

   }


   bool base_socket::IsSSLServer()
   {
      
      return base_socket_composite()->IsSSLServer();

   }


   void base_socket::SetSSLServer(bool bSSLServer)
   {
      
      base_socket_composite()->SetSSLServer(bSSLServer);

   }


   void base_socket::CopyConnection(base_socket * psocket)
   {
//
//#ifdef BSD_STYLE_SOCKETS
//      //m_psslcontext = psocket->m_psslcontext;
//#endif
      //m_ssl_ctx = psocket->m_ssl_ctx; ///< ssl context
      //m_ssl_session = psocket->m_ssl_session; ///< ssl session
      //ssl_method() = psocket->ssl_method(); ///< ssl method
      //m_ssl = psocket->m_ssl; ///< ssl 'socket'
      //m_ssl = psocket->m_ssl; ///< ssl 'socket'
      //m_sbio = psocket->m_sbio; ///< ssl bio
      //m_password = psocket->m_password; ///< ssl password

      //attach(psocket -> get_socket_id());

      SetIpv6(psocket -> IsIpv6());
      
      SetSocketType(psocket -> GetSocketType());
      
      SetSocketProtocol(psocket -> GetSocketProtocol());

      SetClientRemoteAddress(psocket -> GetClientRemoteAddress());
      
      SetRemoteHostname(psocket -> GetRemoteHostname());

//      psocket->m_socket = INVALID_SOCKET;
//
//#ifdef BSD_STYLE_SOCKETS
//      if (psocket->m_psslcontext)
//      {
//
//         psocket->m_psslcontext.release();
//
//      }
//#endif
      //psocket->m_psslcontext->m_iSslCtxRetry = 0;
      //psocket->m_psslcontext->m_ssl = nullptr;
      //psocket->m_psslcontext->m_sbio = nullptr;
      //psocket->m_password.empty();

   }


   void base_socket::SetIsClient()
   {
      
      base_socket_composite()->SetIsClient();

   }


   void base_socket::SetSocketType(int iSocketType)
   {
      
      base_socket_composite()->SetSocketType(iSocketType);

   }


   int base_socket::GetSocketType()
   {

      return base_socket_composite()->GetSocketType();

   }


   void base_socket::SetSocketProtocol(const ::string & strProtocol)
   {

      base_socket_composite()->SetSocketProtocol(strProtocol);

   }


   string base_socket::GetSocketProtocol()
   {

      return base_socket_composite()->GetSocketProtocol();

   }

   
   bool base_socket::IsPoolEnabled() const
   {

      return base_socket_composite()->IsPoolEnabled();

   }


   void base_socket::EnablePool(bool bEnable)
   {

      base_socket_composite()->EnablePool(bEnable);

   }


   void base_socket::SetRetain()
   {

      base_socket_composite()->SetRetain();

   }


   bool base_socket::Retain()
   {

      return base_socket_composite()->Retain();

   }


   void base_socket::OnSocks4Connect()
   {

      information() << "Use with tcp_socket only";

      base_socket_composite()->OnSocks4Connect();

   }


   void base_socket::OnSocks4ConnectFailed()
   {
      information() << "Use with tcp_socket only";

      base_socket_composite()->OnSocks4ConnectFailed();

   }


   bool base_socket::OnSocks4Read()
   {
      information() << "Use with tcp_socket only";
      return base_socket_composite()->OnSocks4Read();
   }
//
//
//#if defined(BSD_STYLE_SOCKETS)
//
//
//   void base_socket::SetSocks4Host(const string & host)
//   {
//
//      //auto paddressdepartment = ::networking::address_department();
//
//      //paddressdepartment->convert(m_socks4_host, host);
//
//   }
//
//
//#endif


   bool base_socket::Socks4()
   {

      return base_socket_composite()->Socks4();
      //return m_bSocks4;
   }


   void base_socket::SetSocks4(bool x)
   {

      return base_socket_composite()->SetSocks4(x);
      //m_bSocks4 = x;
   }


   void base_socket::SetSocks4Host(const ::string & a)
   {
   return base_socket_composite()->SetSocks4Host(a);
   }


   void base_socket::SetSocks4Port(::networking::port_t port)
   {

      return base_socket_composite()->SetSocks4Port(port);

   }


   void base_socket::SetSocks4Userid(const string & x)
   {
      return base_socket_composite()->SetSocks4Userid(x);
   }


   ::string base_socket::GetSocks4Host()
   {
      return base_socket_composite()->GetSocks4Host();
   }


   ::networking::port_t base_socket::GetSocks4Port()
   {
      return base_socket_composite()->GetSocks4Port();
   }


   const string & base_socket::GetSocks4Userid()
   {
      return base_socket_composite()->GetSocks4Userid();
   }

   bool base_socket::prepare_for_detach()
   {

      return base_socket_composite()->prepare_for_detach();

      //if (!DeleteByHandler())
      //{

      //   return false;

      //}

      ////if (m_psocketthread)
      ////{

      ////   return false;

      ////}

      ////if (m_bDetached)
      ////{

      ////   return false;

      ////}

      //SetDetach();

      //return true;

   }


   //void base_socket::DetachSocket(socket_map::association * passociation, socket_map * psocketmap)
   //{

   //   SetDetached();

   //   auto psocketthread = __new(socket_thread);

   //   psocketthread->transfer(passociation, psocketmap);

   //}


   void base_socket::OnDetached()
   {

      base_socket_composite()->OnDetached();

   }


   void base_socket::SetDetach(bool bDetach)
   {

      base_socket_composite()->SetDetach(bDetach);

   }


   bool base_socket::IsDetach()
   {

      return base_socket_composite()->IsDetach();

   }


   void base_socket::SetDetached(bool x)
   {
      
      base_socket_composite()->SetDetached(x);

   }


   const bool base_socket::IsDetached() const
   {

      return base_socket_composite()->IsDetached();

   }


   void base_socket::SetSlaveHandler(base_socket_handler * phandler)
   {

      //m_phandlerSlave = phandler;

      base_socket_composite()->SetSlaveHandler(phandler);

   }



   /** write traffic to an IFile. base_socket will not delete this object. */
   void base_socket::SetTrafficMonitor(file_pointer p)
   {

      //return nullptr;
      base_socket_composite()->SetTrafficMonitor(p);

   }


   /** All traffic will be written to this IFile, if set. */
   file_pointer base_socket::GetTrafficMonitor()
   {

      //return nullptr;

      return base_socket_composite()->GetTrafficMonitor();

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
//
//
//   bool base_socket::SetIpOptions(const void *point, socklen_t len)
//   {
//
//#if defined(IP_OPTIONS) && defined(BSD_STYLE_SOCKETS)
//
//      if (setsockopt(get_socket_id(), IPPROTO_IP, IP_OPTIONS, (char *)point, len) == -1)
//      {
//
//         fatal() <<"setsockopt(IPPROTO_IP, IP_OPTIONS)" << Errno << ", " << bsd_socket_error(Errno);
//
//         return false;
//
//      }
//
//      return true;
//
//#else
//
//      information() << "ip option not available, IP_OPTIONS";
//
//      return false;
//
//#endif
//
//   }


//#if defined(IP_PKTINFO) && defined(BSD_STYLE_SOCKETS)
//
   bool base_socket::SetIpPktinfo(bool x)
   {

      throw interface_only();

      return false;

   /*   int optval = x ? 1 : 0;

      if (setsockopt(get_socket_id(), IPPROTO_IP, IP_PKTINFO, (char *)&optval, sizeof(optval)) == -1)
      {

         fatal() <<"setsockopt(IPPROTO_IP, IP_PKTINFO) " << Errno << ", " << bsd_socket_error(Errno);

         return false;

      }

      return true;*/

   }
//
//#endif
//
//
//#if defined(IP_RECVTOS) && defined(BSD_STYLE_SOCKETS)
//
//
   bool base_socket::SetIpRecvTOS(bool x)
   {

      throw interface_only();

      return false;
//
//      int optval = x ? 1 : 0;
//
//      if (setsockopt(get_socket_id(), IPPROTO_IP, IP_RECVTOS, (char *)&optval, sizeof(optval)) == -1)
//      {
//
//         fatal() <<"setsockopt(IPPROTO_IP, IP_RECVTOS) " << Errno << ", " << bsd_socket_error(Errno);
//
//         return false;
//
//      }
//
//      return true;

   }
//
//
//#endif
//
//
//#if defined(IP_RECVTTL) && defined(BSD_STYLE_SOCKETS)
//
//
   bool base_socket::SetIpRecvTTL(bool x)
   {

      throw interface_only();
      return false;
//
//      int optval = x ? 1 : 0;
//
//      if (setsockopt(get_socket_id(), IPPROTO_IP, IP_RECVTTL, (char *)&optval, sizeof(optval)) == -1)
//      {
//
//         fatal() <<"setsockopt(IPPROTO_IP, IP_RECVTTL) " << Errno << ", " << bsd_socket_error(Errno);
//
//         return false;
//
//      }
//
//      return true;
//
   }
//
//
//#endif


//#if defined(IP_RECVOPTS) && defined(BSD_STYLE_SOCKETS)
//
//
   bool base_socket::SetIpRecvopts(bool x)
   {

      throw interface_only();

      return false;
//
//      int optval = x ? 1 : 0;
//
//      if (setsockopt(get_socket_id(), IPPROTO_IP, IP_RECVOPTS, (char *)&optval, sizeof(optval)) == -1)
//      {
//
//         fatal() <<"setsockopt(IPPROTO_IP, IP_RECVOPTS) " << Errno << ", " << bsd_socket_error(Errno);
//
//         return false;
//
//      }
//
//      return true;
//
   }
//
//#endif
//
//
//#if defined(IP_RETOPTS) && defined(BSD_STYLE_SOCKETS)
//
//
   bool base_socket::SetIpRetopts(bool x)
   {

      throw interface_only();

      return false;
//
//      int optval = x ? 1 : 0;
//
//      if (setsockopt(get_socket_id(), IPPROTO_IP, IP_RETOPTS, (char *)&optval, sizeof(optval)) == -1)
//      {
//
//         fatal() <<"setsockopt(IPPROTO_IP, IP_RETOPTS) " << Errno << ", " << bsd_socket_error(Errno);
//
//         return false;
//
//      }
//
//      return true;
//
   }
//
//
//#endif


   bool base_socket::SetIpTOS(unsigned char tos)
   {

      return base_socket_composite()->SetIpTOS(tos);
//#if defined(IP_TOS) && defined(BSD_STYLE_SOCKETS)
//      
//      if (setsockopt(get_socket_id(), IPPROTO_IP, IP_TOS, (char *)&tos, sizeof(tos)) == -1)
//      {
//      
//         fatal() <<"setsockopt(IPPROTO_IP, IP_TOS) " << Errno << ", " << bsd_socket_error(Errno);
//
//         return false;
//
//      }
//
//      return true;
//
//#else
//      
//      INFO(log_this, "ip option not available", 0, "IP_TOS");
//
//      return false;
//
//#endif

      //return false;

   }


   unsigned char base_socket::IpTOS()
   {

      //unsigned char tos = 0;

//#if defined(IP_TOS) && defined(BSD_STYLE_SOCKETS)
//
//      socklen_t len = sizeof(tos);
//
//      if (getsockopt(get_socket_id(), IPPROTO_IP, IP_TOS, (char *)&tos, &len) == -1)
//      {
//      
//         fatal() <<"getsockopt(IPPROTO_IP, IP_TOS) " << Errno << ", " << bsd_socket_error(Errno);
//
//      }
//
//#else
//
//      information() << "ip option not available: IP_TOS";
//
//#endif
//
      return base_socket_composite()->IpTOS();

   }


   bool base_socket::SetIpTTL(int ttl)
   {

//#if defined(IP_TTL) && defined(BSD_STYLE_SOCKETS)
//
//      if (setsockopt(get_socket_id(), IPPROTO_IP, IP_TTL, (char *)&ttl, sizeof(ttl)) == -1)
//      {
//
//         fatal() <<"setsockopt(IPPROTO_IP, IP_TTL) " << Errno << ", " << bsd_socket_error(Errno);
//
//         return false;
//
//      }
//
//      return true;
//
//#else
//
//      information() << "ip option not available: IP_TTL";
//
//      return false;
//
//#endif

      return base_socket_composite()->SetIpTTL(ttl);

   }


   int base_socket::IpTTL()
   {
      
      //int ttl = 0;

//#if defined(IP_TTL) && defined(BSD_STYLE_SOCKETS)
//
//      socklen_t len = sizeof(ttl);
//
//      if (getsockopt(get_socket_id(), IPPROTO_IP, IP_TTL, (char *)&ttl, &len) == -1)
//      {
//
//         fatal() <<"getsockopt(IPPROTO_IP, IP_TTL) " << Errno << ", " << bsd_socket_error(Errno);
//
//      }
//
//#else
//
//      information() << "ip option not available: IP_TTL";
//
//#endif

      return base_socket_composite()->IpTTL();

   }


   bool base_socket::SetIpHdrincl(bool x)
   {

      //throw interface_only();

      //return false;

//#if defined(IP_HDRINCL) && defined(BSD_STYLE_SOCKETS)
//      
//      int optval = x ? 1 : 0;
//      
//      if (setsockopt(get_socket_id(), IPPROTO_IP, IP_HDRINCL, (char *)&optval, sizeof(optval)) == -1)
//      {
//
//         fatal() <<"setsockopt(IPPROTO_IP, IP_HDRINCL) " << Errno << ", " << bsd_socket_error(Errno);
//
//         return false;
//
//      }
//
//      return true;
//
//#else
//
//      information() << "ip option not available: IP_HDRINCL";
//
//      return false;
//
//#endif

      return base_socket_composite()->SetIpHdrincl(x);

   }


//#if defined(IP_RECVERR) && defined(BSD_STYLE_SOCKETS)
   
   bool base_socket::SetIpRecverr(bool x)
   {

      return base_socket_composite()->SetIpRecverr(x);

      //int optval = x ? 1 : 0;

      //if (setsockopt(get_socket_id(), IPPROTO_IP, IP_RECVERR, (char *)&optval, sizeof(optval)) == -1)
      //{

      //   fatal() <<"setsockopt(IPPROTO_IP, IP_RECVERR)" << Errno << ", " << bsd_socket_error(Errno);

      //   return false;

      //}

      //return true;

   }

//#endif


//#if defined(IP_MTU_DISCOVER) && defined(BSD_STYLE_SOCKETS)
   
   bool base_socket::SetIpMtudiscover(bool x)
   {

      return base_socket_composite()->SetIpMtudiscover(x);
   
      //int optval = x ? 1 : 0;

      //if (setsockopt(get_socket_id(), IPPROTO_IP, IP_MTU_DISCOVER, (char *)&optval, sizeof(optval)) == -1)
      //{

      //   fatal() <<"setsockopt(IPPROTO_IP, IP_MTU_DISCOVER) " << Errno << ", " << bsd_socket_error(Errno);

      //   return false;

      //}

      //return true;

   }

//#endif


//#if defined(IP_MTU) && defined(BSD_STYLE_SOCKETS)
   
   int base_socket::IpMtu()
   {

      return base_socket_composite()->IpMtu();
   
      //int mtu = 0;

      //socklen_t len = sizeof(mtu);

      //if (getsockopt(get_socket_id(), IPPROTO_IP, IP_MTU, (char *)&mtu, &len) == -1)
      //{

      //   fatal() <<"getsockopt(IPPROTO_IP, IP_MTU) " << Errno << ", " << bsd_socket_error(Errno);

      //}

      //return mtu;

   }

//#endif


//#if defined(IP_ROUTER_ALERT) && defined(BSD_STYLE_SOCKETS)
   
   bool base_socket::SetIpRouterAlert(bool x)
   {

      return base_socket_composite()->SetIpRouterAlert(x);
   
      //int optval = x ? 1 : 0;
   
      //if (setsockopt(get_socket_id(), IPPROTO_IP, IP_ROUTER_ALERT, (char *)&optval, sizeof(optval)) == -1)
      //{
   
      //   fatal() <<"setsockopt(IPPROTO_IP, IP_ROUTER_ALERT) " << Errno << ", " << bsd_socket_error(Errno);
   
      //   return false;

      //}

      //return true;

   }

//#endif


   bool base_socket::SetIpMulticastTTL(int ttl)
   {

      return base_socket_composite()->SetIpMulticastTTL(ttl);

//#if defined(IP_MULTICAST_TTL) && defined(BSD_STYLE_SOCKETS)
//
//      if (setsockopt(get_socket_id(), IPPROTO_IP, IP_MULTICAST_TTL, (char *)&ttl, sizeof(ttl)) == -1)
//      {
//
//         fatal() <<"setsockopt(IPPROTO_IP, IP_MULTICAST_TTL) " << Errno << ", " << bsd_socket_error(Errno);
//
//         return false;
//
//      }
//
//      return true;
//
//#else
//
//      information() << "ip option not available: IP_MULTICAST_TTL";
//
//      return false;
//
//#endif
//
   }


   int base_socket::IpMulticastTTL()
   {

      //int ttl = 0;
//
//#if defined(IP_MULTICAST_TTL) && defined(BSD_STYLE_SOCKETS)
//
//      socklen_t len = sizeof(ttl);
//
//      if (getsockopt(get_socket_id(), IPPROTO_IP, IP_MULTICAST_TTL, (char *)&ttl, &len) == -1)
//      {
//
//         fatal() <<"getsockopt(IPPROTO_IP, IP_MULTICAST_TTL)" << Errno << ", " << bsd_socket_error(Errno);
//
//      }
//
//#else
//      
//      INFO(log_this, "ip option not available", 0, "IP_MULTICAST_TTL");
//
//#endif

      return base_socket_composite()->IpMulticastTTL();

   }


   bool base_socket::SetMulticastLoop(bool x)
   {
//
//#if defined(IP_MULTICAST_LOOP) && defined(BSD_STYLE_SOCKETS)
//
//      int optval = x ? 1 : 0;
//
//      if (setsockopt(get_socket_id(), IPPROTO_IP, IP_MULTICAST_LOOP, (char *)&optval, sizeof(optval)) == -1)
//      {
//
//         fatal() <<"setsockopt(IPPROTO_IP, IP_MULTICAST_LOOP)" << Errno << ", " << bsd_socket_error(Errno);
//
//         return false;
//
//      }
//
//      return true;
//
//#else
//      
//      INFO(log_this, "ip option not available", 0, "IP_MULTICAST_LOOP");
//
//      return false;
//
//#endif
      return base_socket_composite()->SetMulticastLoop(x);

   }


//#ifdef LINUX
//
//   bool base_socket::IpAddMembership(struct ip_mreqn& ref)
//   {
//
//#if defined(IP_ADD_MEMBERSHIP) && defined(BSD_STYLE_SOCKETS)
//
//      if (setsockopt(get_socket_id(), IPPROTO_IP, IP_ADD_MEMBERSHIP, (char *)&ref, sizeof(struct ip_mreqn)) == -1)
//      {
//
//         fatal() <<"setsockopt(IPPROTO_IP, IP_ADD_MEMBERSHIP)" << Errno << ", " << bsd_socket_error(Errno);
//
//         return false;
//
//      }
//
//      return true;
//
//#else
//
//      INFO(log_this, "ip option not available", 0, "IP_ADD_MEMBERSHIP");
//
//      return false;
//
//#endif
//
//   }
//
//#endif


//   bool base_socket::IpAddMembership(struct ip_mreq& ref)
//   {
////
////#if defined(IP_ADD_MEMBERSHIP) && defined(BSD_STYLE_SOCKETS)
////      
////      if (setsockopt(get_socket_id(), IPPROTO_IP, IP_ADD_MEMBERSHIP, (char *)&ref, sizeof(struct ip_mreq)) == -1)
////      {
////
////         fatal() <<"setsockopt(IPPROTO_IP, IP_ADD_MEMBERSHIP)" << Errno << ", " << bsd_socket_error(Errno);
////
////         return false;
////
////      }
////
////      return true;
////
////#else
////
////      INFO(log_this, "ip option not available", 0, "IP_ADD_MEMBERSHIP");
////
////      return false;
////
////#endif
//      return false;
//
//   }
//
//
//#ifdef LINUX
//
//   bool base_socket::IpDropMembership(struct ip_mreqn& ref)
//   {
//
//#if defined(IP_DROP_MEMBERSHIP) && defined(BSD_STYLE_SOCKETS)
//      
//      if (setsockopt(get_socket_id(), IPPROTO_IP, IP_DROP_MEMBERSHIP, (char *)&ref, sizeof(struct ip_mreqn)) == -1)
//      {
//      
//         fatal() <<"setsockopt(IPPROTO_IP, IP_DROP_MEMBERSHIP)" << Errno << ", " << bsd_socket_error(Errno);
//
//         return false;
//
//      }
//
//      return true;
//
//#else
//
//      INFO(log_this, "ip option not available", 0, "IP_DROP_MEMBERSHIP");
//
//      return false;
//
//#endif
//
//   }
//
//#endif
//
//
//   bool base_socket::IpDropMembership(struct ip_mreq& ref)
//   {
////
////#if defined(IP_DROP_MEMBERSHIP) && defined(BSD_STYLE_SOCKETS)
////      
////      if (setsockopt(get_socket_id(), IPPROTO_IP, IP_DROP_MEMBERSHIP, (char *)&ref, sizeof(struct ip_mreq)) == -1)
////      {
////
////         fatal() <<"setsockopt(IPPROTO_IP, IP_DROP_MEMBERSHIP)" << Errno << ", " << bsd_socket_error(Errno);
////
////         return false;
////
////      }
////
////      return true;
////
////#else
////
////      INFO(log_this, "ip option not available", 0, "IP_DROP_MEMBERSHIP");
////
////      return false;
////
////#endif
//      return false;
//
//   }
//
//
//   /* socket_id options */


   bool base_socket::SetSoReuseaddr(bool x)
   {
      
      ///return false;
      
      //return _SetSoReuseaddr(socket_i)
//
//#if defined(SO_REUSEADDR) && defined(BSD_STYLE_SOCKETS)
//
//      int optval = x ? 1 : 0;
//
//      if (setsockopt(get_socket_id(), SOL_SOCKET, SO_REUSEADDR, (char *)&optval, sizeof(optval)) == -1)
//      {
//
//         fatal() <<"setsockopt(SOL_SOCKET, SO_REUSEADDR)" << Errno << ", " << bsd_socket_error(Errno);
//
//         return false;
//
//      }
//
//      return true;
//
//#else
//      
//      INFO(log_this, "base_socket option not available", 0, "SO_REUSEADDR");
//
//      return false;
//
//#endif
      return base_socket_composite()->SetSoReuseaddr(x);

   }


   bool base_socket::SetSoKeepalive(bool x)
   {
//
//#if defined(SO_KEEPALIVE) && defined(BSD_STYLE_SOCKETS)
//
//      int optval = x ? 1 : 0;
//
//      if (setsockopt(get_socket_id(), SOL_SOCKET, SO_KEEPALIVE, (char *)&optval, sizeof(optval)) == -1)
//      {
//
//         fatal() <<"setsockopt(SOL_SOCKET, SO_KEEPALIVE)" << Errno << ", " << bsd_socket_error(Errno);
//
//         return false;
//
//      }
//
//      return true;
//
//#else
//
//      INFO(log_this, "base_socket option not available", 0, "SO_KEEPALIVE");
//
//      return false;
//
//#endif
      return base_socket_composite()->SetSoKeepalive(x);

   }


//#if defined(SO_NOSIGPIPE) && defined(BSD_STYLE_SOCKETS)

   bool base_socket::SetSoNosigpipe(bool x)
   {

      return base_socket_composite()->SetSoNosigpipe(x);

//      int optval = x ? 1 : 0;
//
//      if (setsockopt(get_socket_id(), SOL_SOCKET, SO_NOSIGPIPE, (char *)&optval, sizeof(optval)) == -1)
//      {
//
//         fatal() <<"setsockopt(SOL_SOCKET, SO_NOSIGPIPE)" << Errno << ", " << bsd_socket_error(Errno);
//
//         return false;
//
//      }
//
//      return true;
//
   }

//#endif


   bool base_socket::SoAcceptconn()
   {

      //int value = 0;
//
//#if defined(SO_ACCEPTCONN) && defined(BSD_STYLE_SOCKETS)
//
//      socklen_t len = sizeof(value);
//
//      if (getsockopt(get_socket_id(), SOL_SOCKET, SO_ACCEPTCONN, (char *)&value, &len) == -1)
//      {
//
//         fatal() <<"getsockopt(SOL_SOCKET, SO_ACCEPTCONN)" << Errno << ", " << bsd_socket_error(Errno);
//
//      }
//
//#else
//
//      INFO(log_this, "base_socket option not available", 0, "SO_ACCEPTCONN");
//
//#endif

      return base_socket_composite()->SoAcceptconn();

   }


//#if defined(SO_BSDCOMPAT) && defined(BSD_STYLE_SOCKETS)
   
   bool base_socket::SetSoBsdcompat(bool x)
   {

      return base_socket_composite()->SetSoBsdcompat(x);
   
      //int optval = x ? 1 : 0;
   
      //if (setsockopt(get_socket_id(), SOL_SOCKET, SO_BSDCOMPAT, (char *)&optval, sizeof(optval)) == -1)
      //{

      //   fatal() <<"setsockopt(SOL_SOCKET, SO_BSDCOMPAT)" << Errno << ", " << bsd_socket_error(Errno);

      //   return false;

      //}

      //return true;

   }

//#endif


//#if defined(SO_BINDTODEVICE) && defined(BSD_STYLE_SOCKETS)
   
   bool base_socket::SetSoBindtodevice(const string & intf)
   {
      return base_socket_composite()->SetSoBindtodevice(intf);
   
      //if (setsockopt(get_socket_id(), SOL_SOCKET, SO_BINDTODEVICE, (char *) (const char *)intf, intf.get_length()) == -1)
      //{

      //   fatal() <<"setsockopt(SOL_SOCKET, SO_BINDTODEVICE)" << Errno << ", " << bsd_socket_error(Errno);

      //   return false;

      //}

      //return true;

   }

//#endif


   bool base_socket::SetSoBroadcast(bool x)
   {
//
//#if defined(SO_BROADCAST) && defined(BSD_STYLE_SOCKETS)
//      
//      int optval = x ? 1 : 0;
//      
//      if (setsockopt(get_socket_id(), SOL_SOCKET, SO_BROADCAST, (char *)&optval, sizeof(optval)) == -1)
//      {
//
//         fatal() <<"setsockopt(SOL_SOCKET, SO_BROADCAST)" << Errno << ", " << bsd_socket_error(Errno);
//
//         return false;
//
//      }
//
//      return true;
//
//#else
//      
//      INFO(log_this, "base_socket option not available", 0, "SO_BROADCAST");
//      
//      return false;
//
//#endif
      return base_socket_composite()->SetSoBroadcast(x);

   }


   bool base_socket::SetSoDebug(bool x)
   {
//
//#if defined(SO_DEBUG) && defined(BSD_STYLE_SOCKETS)
//      
//      int optval = x ? 1 : 0;
//      
//      if (setsockopt(get_socket_id(), SOL_SOCKET, SO_DEBUG, (char *)&optval, sizeof(optval)) == -1)
//      {
//
//         fatal() <<"setsockopt(SOL_SOCKET, SO_DEBUG)" << Errno << ", " << bsd_socket_error(Errno);
//
//         return false;
//
//      }
//
//      return true;
//
//#else
//      
//      INFO(log_this, "base_socket option not available", 0, "SO_DEBUG");
//
//      return false;
//
//#endif

      return base_socket_composite()->SetSoDebug(x);
   }


   int base_socket::SoError()
   {

      //int value = 0;

//#if defined(SO_ERROR) && defined(BSD_STYLE_SOCKETS)
//      
//      socklen_t len = sizeof(value);
//
//      if (getsockopt(get_socket_id(), SOL_SOCKET, SO_ERROR, (char *)&value, &len) == -1)
//      {
//
//         fatal() <<"getsockopt(SOL_SOCKET, SO_ERROR)" << Errno << ", " << bsd_socket_error(Errno);
//
//      }
//
//#else
//
//      INFO(log_this, "base_socket option not available", 0, "SO_ERROR");
//
//#endif

      return base_socket_composite()->SoError();

   }


   bool base_socket::SetSoDontroute(bool x)
   {

//#if defined(SO_DONTROUTE) && defined(BSD_STYLE_SOCKETS)
//      
//      int optval = x ? 1 : 0;
//
//      if (setsockopt(get_socket_id(), SOL_SOCKET, SO_DONTROUTE, (char *)&optval, sizeof(optval)) == -1)
//      {
//
//         fatal() <<"setsockopt(SOL_SOCKET, SO_DONTROUTE)" << Errno << ", " << bsd_socket_error(Errno);
//
//         return false;
//
//      }
//      
//      return true;
//
//#else
//      
//      INFO(log_this, "base_socket option not available", 0, "SO_DONTROUTE");
//      
//      return false;
//
//#endif
      return base_socket_composite()->SetSoDontroute(x);
   }


   bool base_socket::SetSoLinger(int onoff, int linger)
   {
//
//#if defined(SO_LINGER) && defined(BSD_STYLE_SOCKETS)
//
//      struct linger stl;
//
//      stl.l_onoff = (u_short) onoff;
//
//      stl.l_linger = (u_short) linger;
//
//      if (setsockopt(get_socket_id(), SOL_SOCKET, SO_LINGER, (char *)&stl, sizeof(stl)) == -1)
//      {
//
//         fatal() <<"setsockopt(SOL_SOCKET, SO_LINGER)" << Errno << ", " << bsd_socket_error(Errno);
//
//         return false;
//
//      }
//
//      return true;
//
//#else
//      
//      INFO(log_this, "base_socket option not available", 0, "SO_LINGER");
//      
//      return false;
//
//#endif

      return base_socket_composite()->SetSoLinger(onoff, linger);
   }


   bool base_socket::SetSoOobinline(bool x)
   {

//#if defined(SO_OOBINLINE) && defined(BSD_STYLE_SOCKETS)
//      
//      int optval = x ? 1 : 0;
//
//      if (setsockopt(get_socket_id(), SOL_SOCKET, SO_OOBINLINE, (char *)&optval, sizeof(optval)) == -1)
//      {
//
//         fatal() <<"setsockopt(SOL_SOCKET, SO_OOBINLINE)" << Errno << ", " << bsd_socket_error(Errno);
//
//         return false;
//
//      }
//
//      return true;
//
//#else
//
//      INFO(log_this, "base_socket option not available", 0, "SO_OOBINLINE");
//
//      return false;
//
//#endif

      return base_socket_composite()->SetSoOobinline(x);
   }


//#if defined(SO_PASSCRED) && defined(BSD_STYLE_SOCKETS)

   bool base_socket::SetSoPasscred(bool x)
   {

      return base_socket_composite()->SetSoPasscred(x);
      //int optval = x ? 1 : 0;

      //if (setsockopt(get_socket_id(), SOL_SOCKET, SO_PASSCRED, (char *)&optval, sizeof(optval)) == -1)
      //{
      //
      //   fatal() <<"setsockopt(SOL_SOCKET, SO_PASSCRED)" << Errno << ", " << bsd_socket_error(Errno);
      //   
      //   return false;

      //}

      //return true;

   }

//#endif


#if defined(SO_PEERCRED) && defined(BSD_STYLE_SOCKETS)

   bool base_socket::SoPeercred(struct ::ucred & ucr)
   {

      if (setsockopt(get_socket_id(), SOL_SOCKET, SO_PEERCRED, (char *)&ucr, sizeof(ucr)) == -1)
      {
      
         fatal() <<"setsockopt(SOL_SOCKET, SO_PEERCRED)" << Errno << ", " << bsd_socket_error(Errno);
         
         return false;

      }

      return true;

   }

#endif


//#if defined(SO_PRIORITY) && defined(BSD_STYLE_SOCKETS)

   bool base_socket::SetSoPriority(int x)
   {

      return base_socket_composite()->SetSoPriority(x);
      
      //if (setsockopt(get_socket_id(), SOL_SOCKET, SO_PRIORITY, (char *)&x, sizeof(x)) == -1)
      //{
      //
      //   fatal() <<"setsockopt(SOL_SOCKET, SO_PRIORITY)" << Errno << ", " << bsd_socket_error(Errno);
      //   
      //   return false;

      //}

      //return true;

   }

//#endif


   bool base_socket::SetSoRcvlowat(int x)
   {

//#if defined(SO_RCVLOWAT) && defined(BSD_STYLE_SOCKETS)
//
//      if (setsockopt(get_socket_id(), SOL_SOCKET, SO_RCVLOWAT, (char *)&x, sizeof(x)) == -1)
//      {
//
//         fatal() <<"setsockopt(SOL_SOCKET, SO_RCVLOWAT)" << Errno << ", " << bsd_socket_error(Errno);
//
//         return false;
//
//      }
//
//      return true;
//
//#else
//      
//      INFO(log_this, "base_socket option not available", 0, "SO_RCVLOWAT");
//      
//      return false;
//
//#endif

      return base_socket_composite()->SetSoRcvlowat(x);
   }


   bool base_socket::SetSoSndlowat(int x)
   {

//#if defined(SO_SNDLOWAT) && defined(BSD_STYLE_SOCKETS)
//
//      if (setsockopt(get_socket_id(), SOL_SOCKET, SO_SNDLOWAT, (char *)&x, sizeof(x)) == -1)
//      {
//
//         fatal() <<"setsockopt(SOL_SOCKET, SO_SNDLOWAT)" << Errno << ", " << bsd_socket_error(Errno);
//
//         return false;
//
//      }
//
//      return true;
//
//#else
//      
//      INFO(log_this, "base_socket option not available", 0, "SO_SNDLOWAT");
//      
//      return false;
//
//#endif

      return base_socket_composite()->SetSoSndlowat(x);
   }


//   bool base_socket::SetSoRcvtimeo(struct timeval& tv)
//   {
//
////#if defined(SO_RCVTIMEO) && defined(BSD_STYLE_SOCKETS)
////
////      if (setsockopt(get_socket_id(), SOL_SOCKET, SO_RCVTIMEO, (char *)&tv, sizeof(tv)) == -1)
////      {
////
////         fatal() <<"setsockopt(SOL_SOCKET, SO_RCVTIMEO)" << Errno << ", " << bsd_socket_error(Errno);
////
////         return false;
////
////      }
////
////      return true;
////
////#else
////      
////      INFO(log_this, "base_socket option not available", 0, "SO_RCVTIMEO");
////      
////      return false;
////
////#endif
//
//      return false;
//   }
//
//
//   bool base_socket::SetSoSndtimeo(struct timeval& tv)
//   {
//
////#if defined(SO_SNDTIMEO) && defined(BSD_STYLE_SOCKETS)
////
////      if (setsockopt(get_socket_id(), SOL_SOCKET, SO_SNDTIMEO, (char *)&tv, sizeof(tv)) == -1)
////      {
////
////         fatal() <<"setsockopt(SOL_SOCKET, SO_SNDTIMEO)" << Errno << ", " << bsd_socket_error(Errno);
////
////         return false;
////
////      }
////
////      return true;
////
////#else
////      
////      INFO(log_this, "base_socket option not available", 0, "SO_SNDTIMEO");
////      
////      return false;
////
////#endif
//
//      return false;
//   }


   bool base_socket::SetSoRcvbuf(int x)
   {

//#if defined(SO_RCVBUF) && defined(BSD_STYLE_SOCKETS)
//
//      if (setsockopt(get_socket_id(), SOL_SOCKET, SO_RCVBUF, (char *)&x, sizeof(x)) == -1)
//      {
//
//         fatal() <<"setsockopt(SOL_SOCKET, SO_RCVBUF)" << Errno << ", " << bsd_socket_error(Errno);
//
//         return false;
//
//      }
//
//      return true;
//
//#else
//      
//      INFO(log_this, "base_socket option not available", 0, "SO_RCVBUF");
//      
//      return false;
//
//#endif

      return base_socket_composite()->SetSoRcvbuf(x);
   }


   int base_socket::SoRcvbuf()
   {
    //  int value = 0;

//#if defined(SO_RCVBUF) && defined(BSD_STYLE_SOCKETS)
//      
//      socklen_t len = sizeof(value);
//
//      if (getsockopt(get_socket_id(), SOL_SOCKET, SO_RCVBUF, (char *)&value, &len) == -1)
//      {
//
//         fatal() <<"getsockopt(SOL_SOCKET, SO_RCVBUF)" << Errno << ", " << bsd_socket_error(Errno);
//
//      }
//
//#else
//
//      INFO(log_this, "base_socket option not available", 0, "SO_RCVBUF");
//
//#endif

      return base_socket_composite()->SoRcvbuf();

   }


//#if defined(SO_RCVBUFFORCE) && defined(BSD_STYLE_SOCKETS)

   bool base_socket::SetSoRcvbufforce(int x)
   {

      return base_socket_composite()->SetSoRcvbufforce(x);

      //if (setsockopt(get_socket_id(), SOL_SOCKET, SO_RCVBUFFORCE, (char *)&x, sizeof(x)) == -1)
      //{

      //   fatal() <<"setsockopt(SOL_SOCKET, SO_RCVBUFFORCE)" << Errno << ", " << bsd_socket_error(Errno);
      //   
      //   return false;

      //}

      //return true;

   }

//#endif


   bool base_socket::SetSoSndbuf(int x)
   {

//#if defined(SO_SNDBUF) && defined(BSD_STYLE_SOCKETS)
//
//      if (setsockopt(get_socket_id(), SOL_SOCKET, SO_SNDBUF, (char *)&x, sizeof(x)) == -1)
//      {
//
//         fatal() <<"setsockopt(SOL_SOCKET, SO_SNDBUF)" << Errno << ", " << bsd_socket_error(Errno);
//
//         return false;
//
//      }
//
//      return true;
//
//#else
//      
//      INFO(log_this, "base_socket option not available", 0, "SO_SNDBUF");
//
//      return false;
//
//#endif

      return base_socket_composite()->SetSoSndbuf(x);
   }


   int base_socket::SoSndbuf()
   {
      
      //int value = 0;

//#if defined(SO_SNDBUF) && defined(BSD_STYLE_SOCKETS)
//      
//      socklen_t len = sizeof(value);
//
//      if (getsockopt(get_socket_id(), SOL_SOCKET, SO_SNDBUF, (char *)&value, &len) == -1)
//      {
//
//         fatal() <<"getsockopt(SOL_SOCKET, SO_SNDBUF)" << Errno << ", " << bsd_socket_error(Errno);
//
//      }
//
//#else
//
//      INFO(log_this, "base_socket option not available", 0, "SO_SNDBUF");
//
//#endif

      return base_socket_composite()->SoSndbuf();

   }


//#if defined(SO_SNDBUFFORCE) && defined(BSD_STYLE_SOCKETS)

   bool base_socket::SetSoSndbufforce(int x)
   {

      return base_socket_composite()->SetSoSndbufforce(x);

      //if (setsockopt(get_socket_id(), SOL_SOCKET, SO_SNDBUFFORCE, (char *)&x, sizeof(x)) == -1)
      //{

      //   fatal() <<"setsockopt(SOL_SOCKET, SO_SNDBUFFORCE)" << Errno << ", " << bsd_socket_error(Errno);
      //   
      //   return false;

      //}

      //return true;

   }

//#endif


//#if defined(SO_TIMESTAMP) && defined(BSD_STYLE_SOCKETS)
   
   bool base_socket::SetSoTimestamp(bool x)
   {

      return base_socket_composite()->SetSoTimestamp(x);
   
//      int optval = x ? 1 : 0;
//   
//      if (setsockopt(get_socket_id(), SOL_SOCKET, SO_TIMESTAMP, (char *)&optval, sizeof(optval)) == -1)
//      {
//
//         fatal() <<"setsockopt(SOL_SOCKET, SO_TIMESTAMP)" << Errno << ", " << bsd_socket_error(Errno);
//
//         return false;
//
//      }
//
//      return true;
//
   }

//#endif


   int base_socket::SoType()
   {
      //int value = 0;

//#if defined(SO_TYPE) && defined(BSD_STYLE_SOCKETS)
//      
//      socklen_t len = sizeof(value);
//      
//      if (getsockopt(get_socket_id(), SOL_SOCKET, SO_TYPE, (char *)&value, &len) == -1)
//      {
//
//         fatal() <<"getsockopt(SOL_SOCKET, SO_TYPE)" << Errno << ", " << bsd_socket_error(Errno);
//
//      }
//
//#else
//
//      INFO(log_this, "base_socket option not available", 0, "SO_TYPE");
//
//#endif

      return base_socket_composite()->SoType();

   }


   void base_socket::Subscribe(int atom)
   {
      //socket_handler()->Subscribe(atom, this);
      base_socket_composite()->Subscribe(atom);
   }


   void base_socket::Unsubscribe(int atom)
   {
      //socket_handler()->Unsubscribe(atom, this);
      base_socket_composite()->Unsubscribe(atom);
   }


   //void base_socket::OnTrigger(int, const trigger_data&)
   //{
   //}


   /*void base_socket::OnCancelled(socket_id)
   {
   }*/


   class ::time base_socket::get_last_interaction_time() const
   {

      return base_socket_composite()->get_last_interaction_time();
      
   }


   void base_socket::set_connection_start_time()
   {

      base_socket_composite()->set_connection_start_time();

      //m_timeConnectionStart.Now();

      //set_connection_last_activity();

   }


   void base_socket::set_connection_last_activity()
   {

      base_socket_composite()->set_connection_start_time();
      //m_timeConnectionLastActivity.Now();

   }



   void base_socket::set_maximum_connection_time(const class time & time)
   {

      //m_timeConnectionMaximum = time;
      base_socket_composite()->set_maximum_connection_time(time);

   }


   void base_socket::set_start_time()
   {

      base_socket_composite()->set_start_time();

      //m_timeStart.Now();

      //set_connection_last_activity();

   }


   void base_socket::set_maximum_time(const class time & time)
   {

      //m_timeMaximum = time;
      base_socket_composite()->set_maximum_time(time);

   }


   void base_socket::on_timeout()
   {

      //m_estatus = error_on_connection_timeout;
      base_socket_composite()->on_timeout();

   }


   void base_socket::on_connection_timeout()
   {

      base_socket_composite()->on_connection_timeout();

   }


   bool base_socket::has_timed_out()
   {

      return base_socket_composite()->has_timed_out();

      //if (is_connecting())
      //{

      //   if (m_timeConnectionMaximum > 0_s)
      //   {

      //      auto tElapsed = m_timeConnectionStart.elapsed();

      //      if (tElapsed > m_timeConnectionMaximum)
      //      {

      //         return true;

      //      }

      //   }

      //}
      //else if(m_timeMaximum > 0_s)
      //{

      //   auto tElapsed = m_timeConnectionLastActivity.elapsed();

      //   if (tElapsed > m_timeMaximum)
      //   {

      //      return true;

      //   }

      //}

      //return false;

   }


   void base_socket::on_read(const void * pdata, memsize n )
   {

      base_socket_composite()->on_read(pdata, n);
      //char * buf = (char *) pdata;

      //if (m_pmemfileInput != nullptr)
      //{

      //   m_pmemfileInput->write(buf, n);

      //}

      //if (LineProtocol())
      //{
      //   buf[n] = 0;
      //   int i = 0;
      //   if (m_skip_c && (buf[i] == 13 || buf[i] == 10) && buf[i] != m_c)
      //   {
      //      m_skip_c = false;
      //      i++;
      //   }
      //   int x = i;
      //   for (; i < n && LineProtocol(); i++)
      //   {
      //      while ((buf[i] == 13 || buf[i] == 10) && LineProtocol())
      //      {
      //         char c = buf[i];
      //         buf[i] = 0;
      //         if (buf[x])
      //         {
      //            m_line += (buf + x);
      //         }
      //         OnLine( m_line );
      //         if(IsCloseAndDelete())
      //            break;
      //         i++;
      //         m_skip_c = true;
      //         m_c = c;
      //         if (i < n && (buf[i] == 13 || buf[i] == 10) && buf[i] != c)
      //         {
      //            m_skip_c = false;
      //            i++;
      //         }
      //         x = i;
      //         m_line = "";
      //      }
      //      if (!LineProtocol())
      //      {

      //         break;

      //      }
      //      
      //      if(IsCloseAndDelete())
      //      {
      //      
      //         break;

      //      }

      //   }

      //   if(IsCloseAndDelete())
      //   {

      //      return;

      //   }

      //   if (!LineProtocol())
      //   {

      //      if (i < n)
      //      {

      //         OnRawData(buf + i, n - i);

      //      }

      //   }
      //   else if (buf[x])
      //   {

      //      m_line += (buf + x);

      //   }

      //}
      //else
      //{

      //   OnRawData(buf, n);

      //}

   }


   void base_socket::SetLineProtocol(bool x)
   {

      base_socket_composite()->SetLineProtocol(x);
      //m_bLineProtocol = x;

   }


   bool base_socket::LineProtocol()
   {

      //return m_bLineProtocol;
      return base_socket_composite()->LineProtocol();

   }


   string base_socket::as_string() const
   {

      return base_socket_composite()->as_string();

   }


   void base_socket::OnRawData(char * buf, memsize len)
   {

      base_socket_composite()->OnRawData(buf, len);

      //if(m_pcallback != nullptr)
      //{

      //   m_pcallback->OnRawData(this, buf, len);

      //}

   }


   ::networking::port_t base_socket::GetRemotePort()
   {

      //return m_paddressRemote->get_service_number();

      return base_socket_composite()->GetRemotePort();

   }


   ::networking::address_pointer base_socket::GetRemoteAddress()
   {

      //return m_paddressRemote;
      return base_socket_composite()->GetRemoteAddress();

   }


   ::networking::port_t base_socket::GetLocalPort()
   {

      //throw ::interface_only();

      //return 0;

      return base_socket_composite()->GetLocalPort();

   }


   ::networking::address_pointer base_socket::GetLocalAddress()
   {

      /*throw ::interface_only();

      return nullptr;*/
      return base_socket_composite()->GetLocalAddress();

   }


   void     base_socket::run()
   {

      base_socket_composite()->run();

   }


   bool base_socket::step()
   {

      //return ::e_status_no_work;

      return base_socket_composite()->step();

   }


   string base_socket::get_short_description()
   {


      return base_socket_composite()->get_short_description();

      //auto paddressdepartment = ::networking::address_department();

      //return paddressdepartment->canonical_name(GetRemoteAddress());

   }


   void base_socket::destroy_ssl_session()
   {
      base_socket_composite()->destroy_ssl_session();

//#ifdef BSD_STYLE_SOCKETS
//
//      synchronous_lock synchronouslock(this->synchronization());
//
//      if (m_psslcontext->m_pclientcontext->get_session() != nullptr)
//      {
//
//         m_psslcontext->m_pclientcontext.release();
//
//      }
//
//#endif

   }


   void base_socket::get_ssl_session()
   {

      //synchronous_lock synchronouslock(this->synchronization());

      base_socket_composite()->get_ssl_session();

//#ifdef BSD_STYLE_SOCKETS
//      if (m_psslcontext->m_pclientcontext->m_psslsession == nullptr)
//      {
//
//         m_psslcontext->m_pclientcontext->m_psslsession = SSL_get1_session(m_psslcontext->m_ssl);
//
//      }
//#endif

   }

   
   void base_socket::write(const void * p, ::memsize s)
   {

      base_socket_composite()->write(p, s);

   }


} // namespace sockets



