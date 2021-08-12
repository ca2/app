/** \file socket_handler.cpp
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
#include "framework.h"
#include "apex/networking/sockets/_sockets.h"


namespace sockets
{


   socket_handler::socket_handler(::object * pobject, ::apex::log * plog) :
      ::object(pobject),
      base_socket_handler(pobject, plog),
      m_b_use_mutex(false)
      ,m_maxsock(0)
      ,m_preverror(-1)
      ,m_errcnt(0)
      ,m_tlast(0)
      ,m_socks4_port(0)
      ,m_bTryDirect(false)
      ,m_resolv_id(0)
      ,m_resolver(nullptr)
      ,m_b_enable_pool(false)
      ,m_next_trigger_id(0)
      ,m_slave(false)
   {

      __memset(&m_socks4_host, 0, sizeof(m_socks4_host));

      /*      FD_ZERO(&m_rfds);
            FD_ZERO(&m_wfds);
            FD_ZERO(&m_efds);*/
   }


   //socket_handler::socket_handler(::object * pobject, ::apex::log *plog) :
   //   ::object(pobject),
   //   base_socket_handler(pobject, plog)
   //   ,m_b_use_mutex(true)
   //   ,m_maxsock(0)
   //   ,m_preverror(-1)
   //   ,m_errcnt(0)
   //   ,m_tlast(0)
   //   ,m_socks4_port(0)
   //   ,m_bTryDirect(false)
   //   ,m_resolv_id(0)
   //   ,m_resolver(nullptr)
   //   ,m_b_enable_pool(false)
   //   ,m_next_trigger_id(0)
   //   ,m_slave(false)
   //{

   //   __memset(&m_socks4_host, 0, sizeof(m_socks4_host));

   //   //m_mutex.lock();

   //   /*      FD_ZERO(&m_rfds);
   //         FD_ZERO(&m_wfds);
   //         FD_ZERO(&m_efds);*/
   //}


   socket_handler::~socket_handler()
   {
      if (m_resolver)
      {
         m_resolver -> Quit();
      }
      {
         auto ppair = m_sockets.get_start();
         //SOCKET s;
         while(ppair != nullptr)
         {
            //socket_pointer p;
            ///.get_next_assoc(pos, s, p);
            auto p = ppair->element2();
            if(p)
            {
               try
               {
                  p->close();
               }
               catch(...)
               {
               }
               if(m_slave)
               {
                  try
                  {
                     delete p;
                  }
                  catch(...)
                  {
                  }
               }
            }
            ppair = ppair->m_pnext;
         }
      }
      m_sockets.erase_all();
      if (m_resolver)
      {
         delete m_resolver;
      }
      if (m_b_use_mutex)
      {
         //m_mutex.unlock();
      }
   }


   ::synchronization_object& socket_handler::GetMutex() const
   {
      
      return *mutex();

   }


   void socket_handler::SetSlave(bool x)
   {
      m_slave = x;
   }


   bool socket_handler::IsSlave()
   {
      return m_slave;
   }


   void socket_handler::add(base_socket * p)
   {
      if (p -> GetSocket() == INVALID_SOCKET)
      {
         WARN(p, "add", -1, "Invalid socket");
         if (p -> IsCloseAndDelete())
         {
            m_delete.add_tail(p->GetSocket());
         }
         return;
      }
      
      socket_pointer plookup;

      if (m_add.lookup(p -> GetSocket(), plookup))
      {
         
         //FATAL(log_this, p, "add", (int)p -> GetSocket(), "Attempt to add socket already in add queue");

         m_delete.add_tail(p->GetSocket());

         return;

      }
      
      m_add[p -> GetSocket()] = p;
      
      p->m_estatus = ::success;

   }


   void socket_handler::get(SOCKET s,bool& r,bool& w,bool& e)
   {
      if (s >= 0)
      {
         /*         r = FD_ISSET(s, &m_rfds) ? true : false;
                  w = FD_ISSET(s, &m_wfds) ? true : false;
                  e = FD_ISSET(s, &m_efds) ? true : false;*/
      }
   }


   void socket_handler::set(SOCKET s,bool bRead,bool bWrite,bool bException)
   {
      //TRACE("Set(%d, %s, %s, %s)\n", s, bRead ? "true" : "false", bWrite ? "true" : "false", bException ? "true" : "false");
      if (s >= 0)
      {
         /*         if (bRead)
                  {
                     if (!FD_ISSET(s, &m_rfds))
                     {
                        FD_SET(s, &m_rfds);
                     }
                  }
                  else
                  {
                     FD_CLR(s, &m_rfds);
                  }
                  if (bWrite)
                  {
                     if (!FD_ISSET(s, &m_wfds))
                     {
                        FD_SET(s, &m_wfds);
                     }
                  }
                  else
                  {
                     FD_CLR(s, &m_wfds);
                  }
                  if (bException)
                  {
                     if (!FD_ISSET(s, &m_efds))
                     {
                        FD_SET(s, &m_efds);
                     }
                  }
                  else
                  {
                     FD_CLR(s, &m_efds);
                  }*/
      }
   }


   int socket_handler::select(i32 lSeconds, i32 lMicroseconds)
   {

      struct timeval timeval;

      timeval.tv_sec    = lSeconds;
      timeval.tv_usec   = lMicroseconds;

      //return 0;

      return select(&timeval);

   }


   int socket_handler::select()
   {
      if (m_fds_callonconnect.get_size() ||
            (!m_slave && m_fds_detach.get_size()) ||
            m_fds_timeout.get_size() ||
            m_fds_retry.get_size() ||
            m_fds_close.get_size() ||
            m_fds_erase.get_size())
      {
         return select(0, 200000);
      }
      return select(nullptr);
   }


   int socket_handler::select(struct timeval *tsel)
   {

      auto ppair = m_add.get_start();
      SOCKET s;
      socket_pointer psocket;
      while(ppair != nullptr)
      {

         s = 0;

         psocket = ppair->element2();

         //m_add.get_next_assoc(pos, s, psocket);

         if(psocket != nullptr)
         {

            m_sockets.set_at(s, psocket);

            m_add.erase_key(s);

            break;

         }

         ppair = ppair->m_pnext;

      }

      ppair = m_sockets.get_start();



      while(ppair != nullptr)
      {
         s = 0;
         psocket = ppair->element2();
         //m_sockets.get_next_assoc(pos, s, psocket);
         if(psocket != nullptr)
         {
            psocket->m_event.wait(seconds(tsel->tv_sec));
            if(psocket->is_connecting())
            {
               psocket->m_estatus = ::error_timeout;
               erase(psocket);
               break;
            }
            psocket->run();
            __pointer(stream_socket) pstreamsocket = psocket;
            if(pstreamsocket != nullptr)
            {
               if(pstreamsocket->m_writer != nullptr)
               {

                  auto writer = pstreamsocket->m_writer;

                  psocket->m_event.ResetEvent();

                  writer->StoreAsync()->Completed = ref new ::Windows::Foundation::AsyncOperationCompletedHandler < unsigned int > ([=]
                                                    (::Windows::Foundation::IAsyncOperation < unsigned int > ^ action, ::Windows::Foundation::AsyncStatus status)
                  {
                     writer->DetachStream();
                     psocket->m_event.SetEvent();
                  });

                  pstreamsocket->m_writer = nullptr;

               }

            }

            if(psocket->m_bClose)
            {

               erase(psocket);

//               delete psocket;

               break;

            }

//            psocket->step();

         }

      }

      return 0;

   }


   bool socket_handler::Resolving(base_socket * p0)
   {

      return m_resolve_q.plookup(p0) != nullptr;

   }


   bool socket_handler::Valid(base_socket * p0)
   {
      auto ppair = m_sockets.get_start();
      while(ppair != nullptr)
      {
         if (p0 == ppair->element2())
            return true;
         ppair = ppair->m_pnext;
      }
      return false;
   }


   bool socket_handler::OkToAccept(base_socket *)
   {
      return true;
   }


   memsize socket_handler::get_count()
   {
      /*
      printf(" m_sockets : %d\n", m_sockets.size());
      printf(" m_add     : %d\n", m_add.size());
      printf(" m_delete  : %d\n", m_delete.size());
      */
      return m_sockets.get_size() + m_add.get_size() + m_delete.get_size();
   }


#if defined(BSD_STYLE_SOCKETS)


   void socket_handler::SetSocks4Host(in_addr a)
   {

      m_socks4_host = a;

   }


//#if defined(BSD_STYLE_SOCKETS)

   void socket_handler::SetSocks4Host(const string & host)
   {

      ::apex::get_system()->sockets().net().convert(m_socks4_host, host);

   }

#endif


   void socket_handler::SetSocks4Port(port_t port)
   {

      m_socks4_port = port;

   }


   void socket_handler::SetSocks4Userid(const string & id)
   {

      m_socks4_userid = id;

   }


   int socket_handler::Resolve(base_socket * p,const string & host,port_t port)
   {
      // check cache
      resolv_socket *resolv = new resolv_socket(*this, p, host, port);
      resolv -> SetId(++m_resolv_id);
      resolv -> SetDeleteByHandler();
      ::net::address addressLocal("127.0.0.1", m_resolver_port);
      //psession->sockets().net().convert(local, "127.0.0.1");
      if(!resolv -> open(addressLocal))
      {
         //FATAL(log_this, resolv, "Resolve", -1, "Can't connect to local resolve server");
      }
      add(resolv);
      m_resolve_q[p] = true;
      TRACE(" *** Resolve '%s:%d' id#%d  m_resolve_q size_i32: %d  p: %p\n", host, port, resolv -> GetId(), m_resolve_q.get_size(), p);
      return resolv -> GetId();
   }


   int socket_handler::Resolve6(base_socket * p,const string & host,port_t port)
   {
      // check cache
      resolv_socket *resolv = new resolv_socket(*this, p, host, port, true);
      resolv -> SetId(++m_resolv_id);
      resolv -> SetDeleteByHandler();
      ::net::address addressLocal("127.0.0.1",m_resolver_port);
      if(!resolv -> open(addressLocal))
      {
         //FATAL(log_this, resolv, "Resolve", -1, "Can't connect to local resolve server");
      }
      add(resolv);
      m_resolve_q[p] = true;
      return resolv -> GetId();
   }


   int socket_handler::Resolve(base_socket * p, in_addr a)
   {
      // check cache
      resolv_socket *resolv = new resolv_socket(*this, p, a);
      resolv -> SetId(++m_resolv_id);
      resolv -> SetDeleteByHandler();
//      ipaddr_t local;
      ::net::address addressLocal("127.0.0.1",m_resolver_port);
      if(!resolv -> open(addressLocal))
      {
         //FATAL(log_this, resolv, "Resolve", -1, "Can't connect to local resolve server");
      }
      add(resolv);
      m_resolve_q[p] = true;
      return resolv -> GetId();
   }


   int socket_handler::Resolve(base_socket * p,in6_addr& a)
   {
      // check cache
      resolv_socket *resolv = new resolv_socket(*this, p, a);
      resolv -> SetId(++m_resolv_id);
      resolv -> SetDeleteByHandler();
      //ipaddr_t local;
      ::net::address addressLocal("127.0.0.1",m_resolver_port);
      if(!resolv -> open(addressLocal))
      {
         //FATAL(log_this, resolv, "Resolve", -1, "Can't connect to local resolve server");
      }
      add(resolv);
      m_resolve_q[p] = true;
      return resolv -> GetId();
   }


   void socket_handler::EnableResolver(port_t port)
   {
      if (!m_resolver)
      {
         m_resolver_port = port;
         m_resolver = new resolv_server(get_application(), port);
      }
   }


   bool socket_handler::ResolverReady()
   {
      return m_resolver ? m_resolver -> Ready() : false;
   }

   void socket_handler::SetSocks4TryDirect(bool x)
   {
      m_bTryDirect = x;
   }


   in_addr socket_handler::GetSocks4Host()
   {
      return m_socks4_host;
   }


   port_t socket_handler::GetSocks4Port()
   {
      return m_socks4_port;
   }


   const string & socket_handler::GetSocks4Userid()
   {
      return m_socks4_userid;
   }


   bool socket_handler::Socks4TryDirect()
   {
      return m_bTryDirect;
   }

   bool socket_handler::ResolverEnabled()
   {
      return m_resolver ? true : false;
   }


   port_t socket_handler::GetResolverPort()
   {
      return m_resolver_port;
   }

   __pointer(base_socket_handler::pool_socket) socket_handler::FindConnection(int type,const string & protocol, const ::net::address & ad)
   {
      auto ppair = m_sockets.get_start();
      while(ppair != nullptr)
      {
         __pointer(pool_socket) pools = ppair->element2();
         if (pools)
         {
            if (pools -> GetSocketType() == type &&
                  pools -> GetSocketProtocol() == protocol &&
                  // %!             pools -> GetClientRemoteAddress() &&
                  pools -> GetClientRemoteAddress() == ad)
            {
               m_sockets.erase_key(ppair->element1());
               pools -> SetRetain(); // avoid close in socket destructor
               return pools; // Caller is responsible that this socket is deleted
            }
         }
         //ppair = m_sockets.get_next(ppair);
         ppair->m_pnext;
      }
      return nullptr;
   }


   void socket_handler::EnablePool(bool x)
   {
      m_b_enable_pool = x;
   }


   bool socket_handler::PoolEnabled()
   {
      return m_b_enable_pool;
   }


   void socket_handler::erase(base_socket * p)
   {
      bool b;
      if(m_resolve_q.lookup(p, b))
         m_resolve_q.erase_key(p);
      if(p -> ErasedByHandler())
      {
         return;
      }
      auto ppair = m_sockets.get_start();
      while(ppair != nullptr)
      {
         if(ppair->element2() == p)
         {
            WARN(p, "erase", -1, "socket destructor called while still in use");
            m_sockets.erase_key(ppair->element1());
            return;
         }
         ppair = ppair->m_pnext;
      }
      auto ppair2 = m_add.get_start();
      while(ppair2 != nullptr)
      {
         if (ppair2->element2() == p)
         {
            WARN(p, "erase", -2, "socket destructor called while still in use");
            m_add.erase_key(ppair2->element1());
            return;
         }
         ppair2 = ppair2->m_pnext;
      }
      if(m_delete.erase(p->GetSocket()) > 0)
      {
         WARN(p, "erase", -3, "socket destructor called while still in use");
         return;
      }
   }


   void socket_handler::CheckSanity()
   {
      CheckList(m_fds, "active sockets"); // active sockets
      CheckList(m_fds_erase, "sockets to be erased"); // should always be is_empty anyway
      CheckList(m_fds_callonconnect, "checklist CallOnConnect");
      CheckList(m_fds_detach, "checklist detach");
      CheckList(m_fds_timeout, "checklist Timeout");
      CheckList(m_fds_retry, "checklist retry client connect");
      CheckList(m_fds_close, "checklist close and delete");
   }


   void socket_handler::CheckList(socket_list& ref,const string & listname)
   {
      auto pnode = ref.get_head();
      while(pnode != nullptr)
      {
         if(m_sockets.plookup(pnode->m_value) != nullptr)
            continue;
         if(m_add.plookup(pnode->m_value) != nullptr)
            continue;
         bool found = false;
         auto pos = m_delete.get_head();
         while(pos != nullptr)
         {
            if(pos->m_value == pnode->m_value)
            {
               found = true;
               break;
            }
         }
         if (!found)
         {
            //TRACE("CheckList failed for \"%s\": fd %d\n", listname, s);
            TRACE("CheckList failed for \"%s\"\n", listname);
         }
      }
   }


   void socket_handler::AddList(SOCKET s,list_t which_one,bool add)
   {
      if (s == INVALID_SOCKET)
      {
         TRACE("AddList:  invalid_socket\n");
         return;
      }
      socket_list& ref =
      (which_one == LIST_CALLONCONNECT) ? m_fds_callonconnect :
      (which_one == LIST_DETACH) ? m_fds_detach :
      (which_one == LIST_TIMEOUT) ? m_fds_timeout :
      (which_one == LIST_RETRY) ? m_fds_retry :
      (which_one == LIST_CLOSE) ? m_fds_close : m_fds_close;
      if (add)
      {
         /*         TRACE("AddList;  %5d: %s: %s\n", s, (which_one == LIST_CALLONCONNECT) ? "CallOnConnect" :
                     (which_one == LIST_DETACH) ? "detach" :
                     (which_one == LIST_TIMEOUT) ? "Timeout" :
                     (which_one == LIST_RETRY) ? "Retry" :
                     (which_one == LIST_CLOSE) ? "close" : "<undef>",
                     add ? "add" : "erase");*/
      }
      if (add)
      {
         ref.add_tail_unique(s);
         return;
      }
      // erase
      ref.erase(s);
      //TRACE("/AddList\n");
   }


   bool socket_handler::contains(base_socket* pbasesocket)
   {

      socket_pointer psocket = pbasesocket;

      if (::contains_value(m_sockets, psocket))
      {

         return true;

      }

      if (::contains_value(m_add, psocket))
      {

         return true;

      }

      if (m_delete.contains(psocket))
      {

         return true;

      }

      return false;

   }


   int socket_handler::TriggerID(base_socket *src)
   {
      int id = m_next_trigger_id++;
      m_trigger_src[id] = src;
      return id;
   }


   bool socket_handler::Subscribe(int id, base_socket *dst)
   {
      if(m_trigger_src.plookup(id) != nullptr)
      {
         if(m_trigger_dst[id].plookup(dst) != nullptr)
         {
            m_trigger_dst[id][dst] = true;
            return true;
         }
         //INFO(log_this, dst, "Subscribe", id, "Already subscribed");
         return false;
      }
      //INFO(log_this, dst, "Subscribe", id, "Trigger id not found");
      return false;
   }


   bool socket_handler::Unsubscribe(int id, base_socket *dst)
   {
      if (m_trigger_src.plookup(id) != nullptr)
      {
         if(m_trigger_dst[id].plookup(dst) != nullptr)
         {
            m_trigger_dst[id].erase_key(dst);
            return true;
         }
         //INFO(log_this, dst, "Unsubscribe", id, "Not subscribed");
         return false;
      }
      //INFO(log_this, dst, "Unsubscribe", id, "Trigger id not found");
      return false;
   }


   void socket_handler::Trigger(int id, socket::trigger_data& data, bool erase)
   {
      
      if(m_trigger_src.plookup(id) != nullptr)
      {
         
         data.SetSource( m_trigger_src[id]);

         auto ppair = m_trigger_dst[id].get_start();

         while(ppair != nullptr)
         {
            
            socket_pointer dst = ppair->element1();

            if (Valid(dst))
            {
               
               dst->OnTrigger(id, data);

            }
            
            ppair = ppair->m_pnext;

         }

         if (erase)
         {

            m_trigger_src.erase_key(id);

            m_trigger_dst.erase_key(id);

         }

      }
      else
      {
         
         //INFO(log_this, nullptr, "Trigger", id, "Trigger id not found");

      }

   }


}



