#include "framework.h"
#include "socket_handler.h"
#include "tcp_socket.h"
#include "networking_bsd/networking.h"
#include "acme/acme.h"
#include "acme/parallelization/synchronous_lock.h"
#include "apex/platform/system.h"
#include <time.h>

#ifdef ANDROID
#undef USE_MISC

#endif




#if defined(__APPLE__) || defined(FREEBSD)

#define bcopy(src, dest, len) ::memcpy_dup(dest, src, len)

#else

#define FD_COPY(pfdsetSrc, pfdsetDst) (*(pfdsetDst)) = (*(pfdsetSrc))

#endif


namespace sockets_bsd
{


   ::interlocked_count g_interlockedcountSocketHandler;


   //socket_handler::socket_handler(::particle * pparticle, ::apex::log *plogger) :
   socket_handler::socket_handler() :
      //::object(pparticle),
      //base_socket_handler(plogger),
      m_b_use_mutex(false)
      , m_maxsock(0)
      , m_iPreviousError(-1)
      //,m_errcnt(0)
      , m_tlast(0)
      , m_socks4_port(0)
      , m_bTryDirect(false)
      //, m_resolv_id(0)
      , m_bEnablePool(false)
      , m_next_trigger_id(0)
      //, m_slave(false)
   {

      m_p2 = this;
      defer_create_synchronization();
      __zero(m_socks4_host);
      //m_prfds = memory_new fd_set;
      //m_pwfds = memory_new fd_set;
      //m_pefds = memory_new fd_set;
      FD_ZERO(&m_rfds);
      FD_ZERO(&m_wfds);
      FD_ZERO(&m_efds);
      m_countR = 0;
      m_countW = 0;
      m_countE = 0;

      g_interlockedcountSocketHandler++;

      ::output_debug_string("----socket_handler (count=" + __string((::iptr) g_interlockedcountSocketHandler) + ")\n");

   }


   socket_handler::~socket_handler()
   {

      cleanup_handler();

      g_interlockedcountSocketHandler--;

   }



   i64 socket_handler::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS)
   {

      return ::object::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }


   i64 socket_handler::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS)
   {

      return ::object::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }


   void socket_handler::initialize(::particle * pparticle)
   {

      base_socket_handler::initialize(pparticle);

   }

   void socket_handler::cleanup_handler()
   {

//      if (m_resolver.is_set())
//      {
//
//         resolver()->Quit();
//
//      }

      {

         auto ppair = m_socketmap.get_start();

         while (ppair != nullptr)
         {

            if (ppair->element2().is_set())
            {

               try
               {

                  ppair->element2()->close();

               }
               catch (...)
               {

               }

               //if (m_slave)
               {

                  ppair->element2().release();

               }

            }

            ppair = m_socketmap.get_next(ppair);

         }

      }

      m_socketmap.erase_all();

      //m_resolver.release();

      if (m_b_use_mutex)
      {

         synchronization()->unlock();

      }

   }


   //synchronization & socket_handler::GetMutex() const
   //{

   //   return *mutex();

   //}


//   resolv_server * socket_handler::resolver()
//   {
//
//      return m_resolver.cast < resolv_server >();
//
//   }


   //void socket_handler::SetSlave(bool x)
   //{

   //   m_slave = x;

   //}


   //bool socket_handler::IsSlave()
   //{

   //   return m_slave;

   //}
   

   void socket_handler::add(const ::sockets::socket_pointer & psocket)
   {

      auto psocket2 = __Socket(psocket);

      auto passociation = m_socketmapAdd.get_association(psocket2->GetSocketId());

      passociation->m_psocket = psocket2;

      move(passociation, &m_socketmapAdd);

   }

   
   void socket_handler::move2(::sockets::socket_pointer && psocket)
   {

      auto psocket2 = __Socket(psocket);

      auto passociation = m_socketmapAdd.get_association(psocket2->GetSocketId());

      passociation->m_psocket = psocket2;

      move(passociation, &m_socketmapAdd);

   }


   void socket_handler::move(socket_map::association* passociation, socket_map* psocketmap)
   {

      socket* psocket = dynamic_cast <socket*> (passociation->m_psocket.m_p);

      //if (psocket->m_psockethandler.is_set())
      //{

      //   WARN(psocket, "add", -1, "socket is already being handled by another handler");

      //   return;

      //}

      if (psocket->GetSocketId() == INVALID_SOCKET)
      {

         WARNING("add: Invalid socket");

         if (psocket->IsCloseAndDelete())
         {

            m_delete.add_tail(psocket);

         }

         return;

      }

      //socket_pointer plookup;

      //if (m_socketmapAdd.lookup(__Socket(psocket)->GetSocketId(), plookup))
      //{

      //   INFO(psocket, "add", (i32)__Socket(psocket)->GetSocketId(), "Attempt to add socket already in add queue");

      //   //m_delete.add_tail(psocket);
      //   return;

      //}

      if (psocket->is_connecting())
      {

         if (psocket->m_durationConnectionMaximum > 0_s)
         {

            socket_id_list_add(psocket->GetSocketId(), e_list_timeout);

         }

      }
      else
      {

         if (psocket->m_durationMaximum > 0_s)
         {

            socket_id_list_add(__Socket(psocket)->GetSocketId(), e_list_timeout);

         }

      }

      if (psocket->IsDetach())
      {

         socket_id_list_add(__Socket(psocket)->GetSocketId(), e_list_detach);

      }

      psocket->m_psockethandler = this;

      psocket->m_estatus = ::success;

      m_socketmapAdd.move(passociation, psocketmap);

   }


   void socket_handler::restart_socket(SOCKET socket)
   {

      auto passociation = m_socketmap.find_association(socket);

      if (passociation->m_psocket->is_connecting())
      {

         if (passociation->m_psocket->m_durationConnectionMaximum > 0_s)
         {

            socket_id_list_add(passociation->m_psocket->GetSocketId(), e_list_timeout);

         }

      }
      else
      {

         if (passociation->m_psocket->m_durationMaximum > 0_s)
         {

            socket_id_list_add(__Socket(passociation->m_psocket)->GetSocketId(), e_list_timeout);

         }

      }

      passociation->m_psocket->m_estatus = ::success;

      m_socketmapAdd.move(passociation, &m_socketmap);

   }


   void socket_handler::get(SOCKET s, bool& r, bool& w, bool& e)
   {
      if (s >= 0)
      {
         r = FD_ISSET(s, &m_rfds) ? true : false;
         w = FD_ISSET(s, &m_wfds) ? true : false;
         e = FD_ISSET(s, &m_efds) ? true : false;
      }
   }


   void socket_handler::set(SOCKET s, bool bRead, bool bWrite, bool bException)
   {
      if (s >= 0)
      {
         if (bRead)
         {
            if (!FD_ISSET(s, &m_rfds))
            {
               FD_SET(s, &m_rfds);
               m_countR++;
            }
         }
         else
         {
            if (FD_ISSET(s, &m_rfds))
            {
               FD_CLR(s, &m_rfds);
               m_countR--;
            }
         }
         if (bWrite)
         {
            if (!FD_ISSET(s, &m_wfds))
            {
               FD_SET(s, &m_wfds);
               m_countW++;
            }
         }
         else
         {
            if (FD_ISSET(s, &m_wfds))
            {
               FD_CLR(s, &m_wfds);
               m_countW--;
            }
         }
         if (bException)
         {
            if (!FD_ISSET(s, &m_efds))
            {
               FD_SET(s, &m_efds);
               m_countE++;
            }
         }
         else
         {
            if (FD_ISSET(s, &m_efds))
            {
               FD_CLR(s, &m_efds);
               m_countE--;
            }
         }
      }
   }


   i32 socket_handler::select(i32 lSeconds, i32 lMicroseconds)
   {

      struct timeval timeval;

      timeval.tv_sec = lSeconds;
      timeval.tv_usec = lMicroseconds;

      return _select(&timeval);

   }


   i32 socket_handler::select()
   {

      if (m_socketlistCallOnConnect.get_size() ||
            //(!m_slave && m_socketlistDetach.get_size()) ||
            m_socketlistDetach.get_size() ||
            m_socketlistTimeout.get_size() ||
            m_socketlistRetryClientConnect.get_size() ||
            m_socketlistClose.get_size() ||
            m_socketlistErase.get_size())
      {
         return select(0, 200000);
      }

      return _select(nullptr);

   }


   i32 socket_handler::select(const class ::wait & wait)
   {

      struct timeval tsel;

      tsel.tv_sec = (long)::duration(wait).integral_second().m_i;
      tsel.tv_usec = ((long)::duration(wait).integral_microsecond().m_i) % 1'000'000'000;

      return _select(&tsel);

   }


   bool socket_handler::contains(::sockets::base_socket * pbasesocket)
   {

      socket_pointer psocket = pbasesocket;

      if (::contains_value(m_socketmap, psocket))
      {

         return true;

      }

      if (::contains_value(m_socketmapAdd, psocket))
      {

         return true;

      }

      if (m_delete.contains(psocket))
      {

         return true;

      }

      return false;

   }


   bool socket_handler::call_on_connect()
   {

      // check CallOnConnect - EVENT
      if (m_socketlistCallOnConnect.get_size())
      {
         socket_id_list tmp = m_socketlistCallOnConnect;
         auto pnode = tmp.get_head();
         for (; pnode != nullptr; pnode = pnode->m_pnext)
         {
            SOCKET socket = pnode->m_value;
            socket_pointer psocket;
            if (!m_socketmap.lookup(socket, psocket)) // not found
            {

               WARNING("GetSocket/handler/4 " << (i32)socket << " Did not find expected socket using file descriptor(4)");

               socket_id_list_erase(__Socket(psocket)->GetSocketId(), e_list_call_on_connect);

            }

            if (psocket != nullptr)
            {

               auto ptcpsocket = psocket.cast < tcp_socket >();

               if (ptcpsocket != nullptr)
               {

                  if (ptcpsocket->CallOnConnect() && psocket->Ready())
                  {
                     
                     psocket->SetConnected(); // moved here from inside if (ptcpsocket) check below

                     if (psocket->IsSSL()) // SSL Enabled socket
                     {

                        psocket->OnSSLConnect();

                     }
                     else if (psocket->Socks4())
                     {

                        psocket->OnSocks4Connect();

                     }
                     else
                     {

                        if (ptcpsocket)
                        {

                           if (ptcpsocket->GetOutputLength())
                           {

                              psocket->OnWrite();

                           }

                        }

                        if (ptcpsocket && ptcpsocket->IsReconnect())
                        {

                           psocket->OnReconnect();

                        }
                        else
                        {

                           _INFORMATION(ptcpsocket, "Calling OnConnect: Because CallOnConnect");

                           psocket->OnConnect();

                        }

                     }

                     ptcpsocket->SetCallOnConnect(false);

                     socket_id_list_erase(__Socket(psocket)->GetSocketId(), e_list_call_on_connect);

                  }

               }

            }

         }

         return true;

      }

      return false;

   }


   i32 socket_handler::_select(struct timeval *tsel)
   {

      {

         try
         {

            m_socketmap.values().each([](auto & psocket)
            {

               psocket->on_select_idle();

            });

         }
         catch (...)
         {

         }

      }

      ::duration tick1, tick2;

start_processing_adding:

      auto passociationAdd = m_socketmapAdd.get_start();

      if (passociationAdd)
      {

         if (m_socketmap.get_size() >= FD_SETSIZE)
         {

            WARNING("Select " << (i32)m_socketmap.get_size() << " FD_SETSIZE reached");

            goto end_processing_adding;

         }

         SOCKET socket = passociationAdd->m_socket;

         auto & psocket = passociationAdd->m_psocket;

         if (m_socketmap.has(socket))
         {

            _WARNING(psocket, "add" << (i32)__Socket(psocket)->GetSocketId() << "Attempt to add socket already in controlled queue");

            m_socketmapAdd.erase(passociationAdd);

            goto start_processing_adding;

         }

         if (psocket->IsCloseAndDelete())
         {

            _WARNING(psocket, "add " << (i32)__Socket(psocket)->GetSocketId() << " Trying to add socket with SetCloseAndDelete() true");

            m_socketlist.add_tail(socket);

            m_socketmap.move(passociationAdd, &m_socketmapAdd);

            socket_id_list_add(socket, e_list_close);

            goto start_processing_adding;

         }

         auto pstreamsocket = dynamic_cast < stream_socket * > (psocket.m_p);

         if (::is_set(pstreamsocket) && pstreamsocket->is_connecting()) // 'open' called before adding socket
         {

            set(socket, true, true);

         }
         else
         {

            auto ptcpsocket = dynamic_cast < tcp_socket * > (psocket.m_p);

            bool bWrite = ::is_set(ptcpsocket) ? ptcpsocket->GetOutputLength() != 0 || ptcpsocket->CallOnConnect() : false;

            bool bRead = ::is_set(ptcpsocket) ? !ptcpsocket->IsDisableRead() : true;

            set(socket, bRead, bWrite);

         }

         m_maxsock = (socket + 1 > m_maxsock) ? socket + 1 : m_maxsock;

         // only add to m_socketlist (process fd_set events) if
         //  slave handler and detached/detaching socket
         //  master handler and non-detached socket
         //if (!(m_slave ^ psocket->IsDetach()))
         //if (!(m_slave ^ psocket->IsDetach()))
         //{

           // m_socketlist.add_tail(socket);

         //}

         m_socketlist.add_tail(socket);

         m_socketmap.move(passociationAdd, &m_socketmapAdd);

         if (passociationAdd->m_psocket->IsDetach())
         {

            passociationAdd->m_psocket->OnDetached();

         }

         goto start_processing_adding;

      }

end_processing_adding:

      fd_set rfds;
      fd_set wfds;
      fd_set efds;

      FD_COPY(&m_rfds, &rfds);
      FD_COPY(&m_wfds, &wfds);
      FD_COPY(&m_efds, &efds);

      fd_set * psetR = m_countR > 0 ? &rfds : nullptr;
      fd_set * psetW = m_countW > 0 ? &wfds : nullptr;
      fd_set * psetE = m_countE > 0 ? &efds : nullptr;

      i32 n = 0;

      tick1 = ::duration::now();

      ::duration tickRWENull;

      if (psetR == nullptr && psetW == nullptr && psetE == nullptr)
      {

         tickRWENull.Now();

         //INFORMATION("rfds, wfds and efds are null!!"));

      }
      else
      {

         //debug_print(" m_socketmap : %d\n", m_socketmap.size());
         //debug_print(" m_socketmapAdd     : %d\n", m_socketmapAdd.size());
         //debug_print(" m_delete  : %d\n", m_delete.size());

         if (m_b_use_mutex)
         {

            synchronization()->unlock();

            n = ::select((int)m_maxsock, psetR, psetW, psetE, tsel);

            m_iSelectErrno = networking_last_error();

            synchronization()->lock();

         }
         else
         {

            n = ::select((int)m_maxsock, psetR, psetW, psetE, tsel);

            m_iSelectErrno = networking_last_error();

         }

      }

      tick2 = ::duration::now();

      if (n < 0)
      {

         auto tickNow = ::duration::now();

         /*
            EBADF  An invalid file descriptor was given in one of the sets.
            EINTR  A non blocked signal was caught.
            EINVAL n is negative. Or struct timeval contains bad time values (<0).
            ENOMEM select was unable to allocate memory for internal tables.
         */

         if (m_maxsock > 0 && (m_iSelectErrno != m_iPreviousError || tickNow - m_durationLastError > 5_s))
         {

            INFORMATION("select" << m_iSelectErrno << ", " << bsd_socket_error(m_iSelectErrno));

            i32 iError = m_iSelectErrno;

#if defined(LINUX) || defined(MACOS)

            INFORMATION("m_maxsock: " << m_maxsock);
            INFORMATION("networking_bsd::socket_handler select error : "<< strerror(networking_last_error()) <<" ("<< networking_last_error() <<")");

#elif defined(WINDOWS)

            INFORMATION("networking_bsd::socket_handler select error : "<< last_error_message(iError) <<" ("<< iError <<")");

#endif

            if (iError == 10022)
            {

               INFORMATION("WSEINVAL - An invalid argument was supplied");

            }

            // test bad fd
            for (SOCKET socket = 0; socket < m_maxsock; socket++)
            {

               bool bAnySet = false;

               FD_ZERO(&rfds);
               FD_ZERO(&wfds);
               FD_ZERO(&efds);

               if (FD_ISSET(socket, &m_rfds))
               {

                  FD_SET(socket, &rfds);

                  bAnySet = true;

               }

               if (FD_ISSET(socket, &m_wfds))
               {

                  FD_SET(socket, &wfds);

                  bAnySet = true;

               }

               if (FD_ISSET(socket, &m_efds))
               {

                  FD_SET(socket, &efds);

                  bAnySet = true;

               }

               if (bAnySet)
               {

                  auto ppairSocket = m_socketmap.plookup(socket);

                  if (::is_set(ppairSocket) && ::is_set(ppairSocket->m_psocket))
                  {

                     INFORMATION("Bad fd in fd_set: " << socket);

                     INFORMATION("Deleting and removing socket: " << socket);

                     ppairSocket->m_psocket->SetCloseAndDelete();

                  }

               }

            }

         }

         /// \no more todo rebuild fd_set's from active networking_bsd list (m_socketmap) here
         /// done : http://jbmon.googlecode.com/svn/trunk/networking_bsd/SocketHandler.cpp : rebuild fd_set's from active networking_bsd list (m_socketmap) here
         {

            FD_ZERO(&rfds);
            FD_ZERO(&wfds);
            FD_ZERO(&efds);

            ::count countR = 0;
            ::count countW = 0;
            ::count countE = 0;

            auto it = m_socketmap.begin();

            for(; it; it++)
            {

               try
               {

                  if (it->m_socket == __Socket(it->m_psocket)->GetSocketId())
                  {

                     fd_set fds;

                     FD_ZERO(&fds);

                     FD_SET(it->m_socket, &fds);

                     struct timeval tv;

                     tv.tv_sec = 0;

                     tv.tv_usec = 0;

                     i32 n = ::select((i32)(it->m_socket + 1), &fds, nullptr, nullptr, &tv);

                     if (n == -1)
                     {

                        // %! bad fd, erase

                        _ERROR(it->m_psocket, " Select " << (i32)it->m_socket << "Bad fd in fd_set (2)"); // , LOG_LEVEL_ERROR));

                        m_socketlistErase.push_back(it->m_socket);

                     }
                     else
                     {

                        bool bAnySet = false;

                        if (FD_ISSET(it->m_socket, &m_rfds))
                        {

                           FD_SET(it->m_socket, &rfds);

                           countR++;

                           bAnySet = true;

                        }

                        if (FD_ISSET(it->m_socket, &m_wfds))
                        {

                           FD_SET(it->m_socket, &wfds);

                           countW++;

                           bAnySet = true;

                        }

                        if (FD_ISSET(it->m_socket, &m_efds))
                        {

                           FD_SET(it->m_socket, &efds);

                           countE++;

                           bAnySet = true;

                        }

                        if (!bAnySet)
                        {

                           // %! none set

                           _ERROR(it->m_psocket, "Select " << (i32)it->m_socket << " No fd in fd_set"); // , LOG_LEVEL_ERROR));

                           m_socketlistErase.push_back(it->m_socket);

                        }

                     }

                  }
                  else
                  {

                     // %! mismatch

                     _ERROR(it->m_psocket, "Select" << (i32)it->m_socket << "Bad fd in fd_set (3)"); // , LOG_LEVEL_ERROR));

                     m_socketlistErase.push_back(it->m_socket);

                  }

               }
               catch (...)
               {

                  // general error

                  _ERROR(it->m_psocket, "Select" << (i32)it->m_socket << "Bad fd in fd_set (3)"); // , LOG_LEVEL_ERROR));

                  m_socketlistErase.push_back(it->m_socket);

               }

            }

            m_rfds = rfds;
            m_wfds = wfds;
            m_efds = efds;

            m_countR = countR;
            m_countW = countW;
            m_countE = countE;

         }

         m_iPreviousError = m_iSelectErrno;

         m_durationLastError = tickNow;

      }
      else if(n == 0)
      {

         m_iPreviousError = -1;

      }
      else // n > 0
      {

         auto pos = m_socketlist.begin();

         for (; pos && n; pos++)
         {
            
            SOCKET socket = *pos;

            if (FD_ISSET(socket, &rfds))
            {
               
               auto ppairSocket = m_socketmap.plookup(socket);

               if (::is_set(ppairSocket) && ::is_set(ppairSocket->m_psocket)) // found
               {

                  // memory_new SSL negotiate method
                  if (ppairSocket->m_psocket->IsSSLNegotiate())
                  {
                     
                     ppairSocket->m_psocket->SSLNegotiate();

                  }
                  else
                  {
                     
                     ppairSocket->m_psocket->OnRead();

                  }

               }
               else
               {

                  WARNING("GetSocket/handler/1 " << (i32)socket << "Did not find expected socket using file descriptor(1)");

               }

               n--;

            }

            if (FD_ISSET(socket, &wfds))
            {
               
               auto ppairSocket = m_socketmap.plookup(socket);

               if (::is_set(ppairSocket) && ::is_set(ppairSocket->m_psocket)) // found
               {

                  // memory_new SSL negotiate method
                  if (ppairSocket->m_psocket->IsSSLNegotiate())
                  {

                     ppairSocket->m_psocket->SSLNegotiate();

                  }
                  else
                  {

                     ppairSocket->m_psocket->OnWrite();

                  }

               }
               else
               {

                  WARNING("GetSocket/handler/2" << (i32)socket << "Did not find expected socket using file descriptor(2)");

               }

               n--;

            }

            if (FD_ISSET(socket, &efds))
            {

               auto ppairSocket = m_socketmap.plookup(socket);

               if (::is_set(ppairSocket) && ::is_set(ppairSocket->m_psocket)) // found
               {
                  
                  // Out-Of-Band data
                  // recv with MSG_OOB
                  //time_t tnow = time(nullptr);

                  if (ppairSocket->m_psocket->has_timed_out())
                  {
                  
                     if (ppairSocket->m_psocket->is_connecting())
                     {

                        WARNING("GetSocket/handler/3" << (i32)socket << "stream_socket on_connection_timeout (3)");

                        ppairSocket->m_psocket->on_connection_timeout();

                     }
                     else
                     {

                        WARNING("GetSocket/handler/3 " << (i32)socket << " socket on_timeout(3)");

                        ppairSocket->m_psocket->on_timeout();

                     }

                  }
                  else
                  {

                     ppairSocket->m_psocket->OnException();

                  }

               }
               else
               {

                  WARNING("GetSocket/handler/3 " << (i32)socket << " Did not find expected socket using file descripto(3)r");

               }

               n--;

            }

         } // m_socketlist loop

         m_iPreviousError = -1;

      } // if (n > 0)

      call_on_connect();

      bool check_max_fd = false;

      // check detach of socket if master handler - EVENT
      //if (!m_slave && m_socketlistDetach.get_size())
      if(m_socketlistDetach.has_element())
      {

         retry_next_item_in_detach_list:

         auto pos = m_socketlistDetach.begin();

         SOCKET socket = 0;

         for (; pos != m_socketlistDetach.end(); pos++)
         {

            socket = *pos;
            
            auto ppairSocket = m_socketmap.plookup(socket);

            if (::is_set(ppairSocket) && ::is_set(ppairSocket->m_psocket))
            {

               if (ppairSocket->m_psocket->IsDetach()
                  && !ppairSocket->m_psocket->IsDetached())
               {

                  if (socket != INVALID_SOCKET)
                  {

                     set(socket, false, false, false);

                     // After DetachSocket(), all calls to socket_handler() will return a object
                     // to the memory_new slave socket_handler running in the memory_new thread.
                     try
                     {

                        ppairSocket->m_psocket->DetachSocket(ppairSocket, &m_socketmap);

                     }
                     catch (...)
                     {

                     }

                     erase_socket(socket);

                     check_max_fd = true;

                     goto retry_next_item_in_detach_list;

                  }

               }

            }

         }

      }

      // check is_connecting - connection timeout - conditional event
      if (m_socketlistTimeout.get_size())
      {
         
         time_t tnow = time(nullptr);

         if (tnow != m_tlast)
         {

            restartSocketListTimeout:

            socket_id_list tmp = m_socketlistTimeout;

            auto it = tmp.begin();

            for (; it; it++)
            {

               SOCKET socket = *it;

               auto ppairSocket = m_socketmap.plookup(socket);

               if (::is_null(ppairSocket) || ::is_null(ppairSocket->m_psocket)) // not found
               {

                  ppairSocket = m_socketmapAdd.plookup(socket);

                  if (::is_null(ppairSocket) || ::is_null(ppairSocket->m_psocket))
                  {

                     WARNING("GetSocket/handler/6 " << (i32)socket << " Did not find expected socket using file descriptor(f)");

                     m_socketlistTimeout.erase(socket);

                     goto restartSocketListTimeout;

                  }

                  continue;

               }
               
               if (::is_set(ppairSocket) || ::is_set(ppairSocket->m_psocket))
               {

                  if (ppairSocket->m_psocket->has_timed_out())
                  {

                     if (ppairSocket->m_psocket->is_connecting())
                     {

                        WARNING("GetSocket/handler/7 " << (i32)socket << "stream_socket on_connection_timeout (g)");

                        ppairSocket->m_psocket->on_connection_timeout();

                     }
                     else
                     {

                        WARNING("GetSocket/handler/7 " << (i32)socket << " socket on_timeout (g)");

                        ppairSocket->m_psocket->on_timeout();

                     }

                     ppairSocket->m_psocket->SetCloseAndDelete();

                  }

               }

            }

            m_tlast = tnow;

         }

      }

      // check retry client connect - EVENT
      if (m_socketlistRetryClientConnect.get_size())
      {

         socket_id_list tmp = m_socketlistRetryClientConnect;

         auto socket = tmp.begin();

         for (; socket; socket++)
         {

            auto ppairSocket = m_socketmap.plookup(*socket);

            if (::is_null(ppairSocket) || ::is_null(ppairSocket->m_psocket))
            {

               WARNING("GetSocket/handler/7 " << (i32)socket << " Did not find expected socket using file descriptor(g)");

            }

            if (::is_set(ppairSocket) && ::is_set(ppairSocket->m_psocket))
            {

               auto ptcpsocket = dynamic_cast < tcp_socket * > (ppairSocket->m_psocket.m_p);

               if (::is_set(ptcpsocket))
               {

                  if (ptcpsocket->RetryClientConnect())
                  {

                     SOCKET nn = socket; //(*it3).element1();

                     ptcpsocket->SetRetryClientConnect(false);

                     //INFORMATION("close() before retry client connect\n"));

                     ptcpsocket->close(); // erases from m_socketlistRetryClientConnect

                     auto paddress = ptcpsocket->GetClientRemoteAddress();

                     if (paddress->is_valid())
                     {

                        ptcpsocket->open(paddress);

                     }
                     else
                     {

                        _ERROR(ptcpsocket, "RetryClientConnect 0 no address");

                     }

                     move(ppairSocket, &m_socketmap);

                     m_socketlistErase.add_tail(nn);

                  }

               }

            }

         }

      }

      // check close and delete - conditional event
      if (m_socketlistClose.get_size() > 0)
      {

         socket_id_list socketlist = m_socketlistClose;

         auto psocketlist = socketlist.begin();

         for(; psocketlist; psocketlist++)
         {

            SOCKET socket = *psocketlist;

            socket_map* psocketmap = nullptr;

            auto ppairSocket = m_socketmap.plookup(socket);

            if (::is_null(ppairSocket) || ::is_null(ppairSocket->m_psocket)) // not found
            {

               ppairSocket = m_socketmapAdd.plookup(socket);

               if (::is_null(ppairSocket) || ::is_null(ppairSocket->m_psocket))
               {

                  WARNING("GetSocket/handler/8 " << (i32)socket << " Did not find expected socket using file descriptor(8)");

               }
               else
               {

                  psocketmap = &m_socketmapAdd;

               }

            }
            else
            {

               psocketmap = &m_socketmap;

            }

            if (::is_set(ppairSocket) && ::is_set(ppairSocket->m_psocket))
            {

               auto psocket = ppairSocket->m_psocket.m_p;

               if (psocket->IsCloseAndDelete())
               {

                  auto ptcpsocket = dynamic_cast <tcp_socket*> (ppairSocket->m_psocket.m_p);

                  // memory_new graceful ptcpsocket - flush and close timeout 5s
                  if (::is_set(ptcpsocket) && psocket->IsConnected() && ptcpsocket->GetFlushBeforeClose() &&
                        !ptcpsocket->IsSSL() && psocket->TimeSinceClose() < 5)
                  {

                     //INFORMATION(" close(1)\n"));
                     if (ptcpsocket->GetOutputLength())
                     {

                        _INFORMATION(ptcpsocket, "Closing " << (i32)ptcpsocket->GetOutputLength() << " Sending all data before closing");

                     }
                     else // shutdown write when output buffer is is_empty
                        if (!(ptcpsocket->GetShutdownStatus() & SHUT_WR))
                     {

                        if (ptcpsocket->m_socket != INVALID_SOCKET && shutdown(psocket->m_socket, SHUT_WR) == -1)
                        {

                           _ERROR(ptcpsocket, "graceful shutdown " << networking_last_error() << bsd_socket_error(networking_last_error()));

                        }

                        ptcpsocket->SetShutdownStatus(SHUT_WR);

                     }

                  }
                  else if (::is_set(ptcpsocket) && psocket->IsConnected() && ptcpsocket->Reconnect())
                  {

                     //SOCKET nn = *it; //(*it3).element1();
                     //FORMATTED_INFORMATION(" close(2) fd %d\n", socket));

                     ptcpsocket->SetCloseAndDelete(false);

                     ptcpsocket->SetIsReconnect();

                     ptcpsocket->SetConnected(false);

                     //INFORMATION("close() before reconnect\n"));

                     ptcpsocket->close(); // dispose of old file descriptor (open creates a memory_new)

                     ptcpsocket->OnDisconnect();

                     auto paddress = ptcpsocket->GetClientRemoteAddress();

                     if (paddress->is_valid())
                     {

                        ptcpsocket->open(paddress);

                     }
                     else
                     {

                        _ERROR(ptcpsocket, "Reconnect 0 no address");

                     }

                     ptcpsocket->ResetConnectionRetryCount();

                     move(ppairSocket, psocketmap);

                     m_socketlistErase.add_tail(ptcpsocket->m_socket);

                  }
                  else
                  {

                     //FORMATTED_INFORMATION(" close(3) fd %d GetSocket() %d\n", socket, point_i32 -> GetSocket()));

                     if (psocket && psocket->IsConnected() && ptcpsocket->GetOutputLength())
                     {

                        _WARNING(psocket, "Closing " << (i32)ptcpsocket->GetOutputLength() << " Closing socket while data still left to send");

                     }

                     if (psocket->Retain() && !psocket->Lost())
                     {

                        auto psystem = get_system()->m_papexsystem;

                        synchronous_lock synchronouslock(__SystemNetworking(psystem)->m_pmutexPool);

                        auto ppoolsocket = __new(pool_socket(psocket));

                        ppoolsocket->m_psockethandler = this;

                        ppoolsocket->SetDeleteByHandler();

                        auto pnetworking2 = __SystemNetworking(psystem);

                        pnetworking2->m_pool.set_at(ppoolsocket->m_socket, ppoolsocket);

                        ppoolsocket->SetCloseAndDelete(false); // added - erase from m_socketlistClose

                        //point_i32 -> SetCloseAndDelete(false); // added - erase from m_socketlistClose

                     }
                     //else if (psocket.cast < http_session >() != nullptr && !psocket->Lost())
                     //{

                     //   psocket->SetCloseAndDelete(false);

                     //   continue;

                     //}
                     else if(__Socket(psocket)->GetSocketId() != INVALID_SOCKET)
                     {

                        set(__Socket(psocket)->GetSocketId(), false, false, false);

                        //INFORMATION("close() before OnDelete\n"));

                        psocket->close();

                     }

                     psocket->OnDelete();

                     if (psocket->DeleteByHandler())
                     {

                        psocket->SetErasedByHandler();

                     }

                  }

               }

            }

            m_socketlistErase.add_tail(socket);

         }

      }

      // check erased networking_bsd
      while (m_socketlistErase.get_size())
      {

         SOCKET socket = m_socketlistErase.pick_head();

         erase_socket(socket);

         auto ppairSocket = m_socketmap.plookup(socket);

         if (::is_set(ppairSocket) && ::is_set(ppairSocket->m_psocket))
         {

            ppairSocket->m_psocket->m_psockethandler.release();

            //ppairSocket->m_psocket->m_phandlerSlave.release();

            m_socketmap.erase_key(socket);

            m_delete.erase(ppairSocket->m_psocket);

            m_socketmapAdd.erase_key(socket);

         }

         check_max_fd = true;

      }

      // calculate maximum file descriptor for select() call
      if (check_max_fd)
      {

         m_maxsock = m_socketlist.maximum(0) + 1;

      }

      // erase add's that fizzed
      while (m_delete.has_element())
      {

         auto psocket = m_delete.pick_head().m_p;

         psocket->OnDelete();

         //if (psocket->DeleteByHandler() && !(m_slave ^ psocket->IsDetached()))
         if (psocket->DeleteByHandler() && psocket->IsDetached())
         {

            psocket->SetErasedByHandler();

            bool again = false;

            do
            {

               again = false;

               auto p = m_trigger_src.begin();

               for(; p; p++)
               {
                  //SOCKET atom = 0;
                  //socket_pointer src;

                  //iterator->get_pair(atom, src);

                  if (p->m_psocket == psocket)
                  {

                     auto pdst = m_trigger_dst[p->m_socket].begin();

                     for(;pdst; pdst++)
                     {

                        if (Valid(pdst->m_pbasesocket))
                        {

                           pdst->m_pbasesocket->OnCancelled(p->m_socket);

                        }

                     }

                     m_trigger_src.erase_key(p->m_socket);

                     m_trigger_dst.erase_key(p->m_socket);

                     again = true;

                     break;

                  }

               }

            }
            while (again);

         }

      }

      return n;

   }


//   bool socket_handler::Resolving(base_socket * p0)
//   {
//
//      return m_resolve_q.plookup(p0) != nullptr;
//
//   }


   bool socket_handler::Valid(::sockets::base_socket * pIsValid)
   {

      auto p = m_socketmap.begin();

      for(; p; p++)
      {

         if (pIsValid == p->m_psocket)
         {

            return true;

         }

      }

      return false;

   }


   bool socket_handler::OkToAccept(::sockets::base_socket *)
   {

      return true;

   }


   ::count socket_handler::get_count()
   {
      /*
      debug_print(" m_socketmap : %d\n", m_socketmap.size());
      debug_print(" m_socketmapAdd     : %d\n", m_socketmapAdd.size());
      debug_print(" m_delete  : %d\n", m_delete.size());
      */

      ::count iSockets = m_socketmap.get_size();

      ::count iAdd = m_socketmapAdd.get_size();

      ::count iDelete = m_delete.get_size();

      return iSockets + iAdd + iDelete;

   }


   //void socket_handler::SetSocks4Host(in_addr a)
   //{
   //   m_socks4_host = a;
   //}


   void socket_handler::SetSocks4Host(const string & host)
   {

      m_socks4_host = host;
      //auto paddressdepartment = ::networking::address_department();

      //paddressdepartment->convert(m_socks4_host, host);

   }


   void socket_handler::SetSocks4Port(::networking::port_t port)
   {
      m_socks4_port = port;
   }


   void socket_handler::SetSocks4Userid(const string & atom)
   {
      m_socks4_userid = atom;
   }


//   i32 socket_handler::Resolve(base_socket * pbasesocket, const string & host, port_t port)
//   {
//
//      // check cache
//
//      ::pointer<resolv_socket>presolvsocket = __new(resolv_socket(pbasesocket, host, port));
//
//      presolvsocket->m_psockethandler = this;
//
//      presolvsocket->SetId(++m_resolv_id);
//
//      presolvsocket->SetDeleteByHandler();
//
//      in_addr addrLocal;
//
//      auto paddressdepartment = ::networking::address_department();
//
//      paddressdepartment->convert(addrLocal, "127.0.0.1");
//
//      if (!presolvsocket->open(::networking::address(addrLocal, m_resolver_port)))
//      {
//
//         FATAL(presolvsocket, "Resolve", -1, "Can't connect to local resolve server");
//
//      }
//
//      add(presolvsocket);
//
//      m_resolve_q[pbasesocket] = true;
//
//      FORMATTED_INFORMATION(" *** Resolve '%s:%d' atom#%d  m_resolve_q size_i32: %d  base_socket: %p\n", host.c_str(), port, presolvsocket->GetId(), m_resolve_q.get_size(), pbasesocket));
//
//      return presolvsocket->GetId();
//
//   }


//   i32 socket_handler::Resolve6(base_socket * pbasesocket, const string & host, port_t port)
//   {
//
//      // check cache
//
//      ::pointer<resolv_socket>resolv = __new(resolv_socket(pbasesocket, host, port, true));
//
//      resolv->m_psockethandler = this;
//
//      resolv->SetId(++m_resolv_id);
//
//      resolv->SetDeleteByHandler();
//
//      in_addr addrLocal;
//
//      auto paddressdepartment = ::networking::address_department();
//
//      paddressdepartment->convert(addrLocal, "127.0.0.1");
//
//      if (!resolv->open(::networking::address(addrLocal, m_resolver_port)))
//      {
//
//         FATAL(resolv, "Resolve", -1, "Can't connect to local resolve server");
//
//      }
//
//      add(resolv);
//
//      m_resolve_q[pbasesocket] = true;
//
//      return resolv->GetId();
//
//   }


//   i32 socket_handler::Resolve(base_socket * pbasesocket, in_addr a)
//   {
//
//      // check cache
//
//      ::pointer<resolv_socket>resolv = __new(resolv_socket(pbasesocket, a));
//
//      resolv->m_psockethandler = this;
//
//      resolv->SetId(++m_resolv_id);
//
//      resolv->SetDeleteByHandler();
//
//      in_addr addrLocal;
//
//      auto paddressdepartment = ::networking::address_department();
//
//      paddressdepartment->convert(addrLocal, "127.0.0.1");
//
//      if (!resolv->open(::networking::address(addrLocal, m_resolver_port)))
//      {
//
//         FATAL(resolv, "Resolve", -1, "Can't connect to local resolve server");
//
//      }
//
//      add(resolv);
//
//      m_resolve_q[pbasesocket] = true;
//
//      return resolv->GetId();
//
//   }


//   i32 socket_handler::Resolve(base_socket * pbasesocket, in6_addr& a)
//   {
//
//      // check cache
//
//      ::pointer<resolv_socket>resolv = __new(resolv_socket(pbasesocket, a));
//
//      resolv->m_psockethandler = this;
//
//      resolv->SetId(++m_resolv_id);
//
//      resolv->SetDeleteByHandler();
//
//      in_addr addrLocal;
//
//      auto paddressdepartment = ::networking::address_department();
//
//      paddressdepartment->convert(addrLocal, "127.0.0.1");
//
//      if (!resolv->open(::networking::address(addrLocal, m_resolver_port)))
//      {
//
//         FATAL(resolv, "Resolve", -1, "Can't connect to local resolve server");
//
//      }
//
//      add(resolv);
//
//      m_resolve_q[pbasesocket] = true;
//
//      return resolv->GetId();
//
//   }


//   void socket_handler::EnableResolver(port_t port)
//   {
//
//      if (!m_resolver)
//      {
//
//         m_resolver_port = port;
//
//         auto presolvserver = __new(resolv_server());
//
//         m_resolver = presolvserver;
//
//         presolvserver->initialize_resolv_server(this, port);
//
//      }
//
//   }


//   bool socket_handler::ResolverReady()
//   {
//
//      return m_resolver ? resolver()->Ready() : false;
//
//   }


   void socket_handler::SetSocks4TryDirect(bool x)
   {

      m_bTryDirect = x;

   }


   string socket_handler::GetSocks4Host()
   {

      return m_socks4_host;

   }


   ::networking::port_t socket_handler::GetSocks4Port()
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


//   bool socket_handler::ResolverEnabled()
//   {
//
//      return m_resolver ? true : false;
//
//   }


//   port_t socket_handler::GetResolverPort()
//   {
//
//      return m_resolver_port;
//
//   }


   ::pointer<base_socket_handler::pool_socket>socket_handler::FindConnection(i32 type, const string & protocol, ::networking::address * ad)
   {

      auto pnetworking2 = __SystemNetworking(acmesystem());

      synchronous_lock synchronouslock(pnetworking2->m_pmutexPool);

      auto p = pnetworking2->m_pool.begin();

      for(; p; p++)
      {

         auto psocket = p->m_psocket;

         if (psocket)
         {

            if (psocket->GetSocketType() == type &&
                  psocket->GetSocketProtocol() == protocol &&
                  // %!             pools -> GetClientRemoteAddress() &&
                  psocket->GetClientRemoteAddress() == ad)
            {

               pnetworking2->m_pool.erase_key(p->m_socket);

               psocket->SetRetain(); // avoid close in socket destructor

               return psocket; // Caller is responsible that this socket is deleted

            }

         }

      }

      return nullptr;

   }


   void socket_handler::EnablePool(bool x)
   {
      m_bEnablePool = x;
   }


   bool socket_handler::PoolEnabled()
   {

      return m_bEnablePool;

   }


   void socket_handler::erase(const ::sockets::socket_pointer & psocketRemove)
   {

//      if (m_resolve_q.has(psocketRemove))
//      {
//
//         m_resolve_q.erase_key(psocketRemove);
//
//      }

      if (psocketRemove->ErasedByHandler())
      {

         return;

      }

      if(::erase_value(m_socketmap, psocketRemove))
      {

         _WARNING(psocketRemove, "erase -1 socket destructor called while still in use");

         return;

      }

      if (::erase_value(m_socketmapAdd, psocketRemove))
      {

         _WARNING(psocketRemove, "erase -2 socket destructor called while still in use");

         return;

      }

      if (::erase_value(m_delete, psocketRemove))
      {

         _WARNING(psocketRemove, "erase -3 socket destructor called while still in use");

         return;

      }

   }


   void socket_handler::CheckSanity()
   {

      CheckList(m_socketlist, "active networking_bsd"); // active networking_bsd
      CheckList(m_socketlistErase, "networking_bsd to be erased"); // should always be is_empty anyway
      CheckList(m_socketlistCallOnConnect, "checklist CallOnConnect");
      CheckList(m_socketlistDetach, "checklist detach");
      CheckList(m_socketlistTimeout, "checklist time_out");
      CheckList(m_socketlistRetryClientConnect, "checklist retry client connect");
      CheckList(m_socketlistClose, "checklist close and delete");

   }


   void socket_handler::CheckList(socket_id_list & list, const string & listname)
   {

      auto p = list.begin();

      for(; (bool) p ; p++)
      {

         if (m_socketmap.has(*p))
         {

            continue;

         }

         if (m_socketmapAdd.has(*p))
         {

            continue;

         }

//         if (!::contains_value(m_delete, *p))
//         {
//
//            FORMATTED_INFORMATION("CheckList failed for \"%s\": fd %d\n", listname.c_str(), *p));
//
//         }

      }

   }

   socket_id_list& socket_handler::socket_id_list_get(enum_list elist)
   {

      switch (elist)
      {
      case e_list_call_on_connect:
         return m_socketlistCallOnConnect;
      case e_list_detach:
         return m_socketlistDetach;
      case e_list_timeout:
         return m_socketlistTimeout;
      case  e_list_retry_client_connect:
         return m_socketlistRetryClientConnect;
      case e_list_close:
         return m_socketlistClose;
      default:
         return m_socketlistClose;
      }

   }


   void socket_handler::socket_id_list_modify(SOCKET s, enum_list elist, bool bAdd)
   {

      if (bAdd)
      {

         socket_id_list_add(s, elist);

      }
      else
      {

         socket_id_list_erase(s, elist);

      }

   }


   void socket_handler::socket_id_list_add(SOCKET s, enum_list elist)
   {

      if (s == INVALID_SOCKET)
      {
         INFORMATION("AddList:  invalid_socket");
         return;
      }

      auto& socketlist = socket_id_list_get(elist);

      //if (add)
      //{
      //   /*         FORMATTED_INFORMATION("AddList);  %5d: %s: %s\n", s, (which_one == e_list_call_on_connect) ? "CallOnConnect" :
      //               (which_one == e_list_detach) ? "detach" :
      //               (which_one == e_list_timeout) ? "time_out" :
      //               (which_one == e_list_retry) ? "Retry" :
      //               (which_one == e_list_close) ? "close" : "<undef>",
      //               add ? "add" : "erase");*/
      //}
      //if (add)
      //{
      socketlist.add_tail_unique(s);
         //if (which_one == e_list_close)
         //{

         //   //INFO(output_debug_string("list_close");
         //}
         //return;
      //}
      // erase
      //ref.erase(s);
      //INFORMATION("/AddList\n"));
   }


   void socket_handler::socket_id_list_erase(SOCKET s, enum_list elist)
   {

      if (s == INVALID_SOCKET)
      {
         INFORMATION("AddList:  invalid_socket");
         return;
      }

      auto& socketlist = socket_id_list_get(elist);

         //if (add)
         //{
         //   /*         FORMATTED_INFORMATION("AddList);  %5d: %s: %s\n", s, (which_one == e_list_call_on_connect) ? "CallOnConnect" :
         //               (which_one == e_list_detach) ? "detach" :
         //               (which_one == e_list_timeout) ? "time_out" :
         //               (which_one == e_list_retry) ? "Retry" :
         //               (which_one == e_list_close) ? "close" : "<undef>",
         //               add ? "add" : "erase");*/
         //}
         //if (add)
         //{
      socketlist.erase(s);
      //if (which_one == e_list_close)
      //{

      //   //INFO(output_debug_string("list_close");
      //}
      //return;
   //}
   // erase
   //ref.erase(s);
   //INFORMATION("/AddList\n"));
   }


   void socket_handler::erase_socket(SOCKET s)
   {

      set(s, false, false, false); // erase from fd_set's

      m_socketlistCallOnConnect.erase(s);
      m_socketlistDetach.erase(s);
      m_socketlistTimeout.erase(s);
      m_socketlistRetryClientConnect.erase(s);
      m_socketlistClose.erase(s);


   }


   i32 socket_handler::TriggerID(::sockets::base_socket * src)
   {

      i32 atom = m_next_trigger_id++;

      m_trigger_src[atom] = src;

      return atom;

   }


   bool socket_handler::Subscribe(i32 atom, ::sockets::base_socket * psocketDst)
   {

      if (m_trigger_src.plookup(atom) != nullptr)
      {

         auto psocketDst2 = __Socket(psocketDst);

         if (m_trigger_dst[atom].plookup(psocketDst2) != nullptr)
         {

            m_trigger_dst[atom][psocketDst2] = true;

            return true;

         }

         _INFORMATION(psocketDst, "Subscribe " << atom << " Already subscribed");

         return false;
      }

      _INFORMATION(psocketDst, "Subscribe " << atom << " Trigger atom not found");

      return false;

   }


   bool socket_handler::Unsubscribe(i32 atom, ::sockets::base_socket * psocketDst)
   {

      if (m_trigger_src.plookup(atom) != nullptr)
      {

         auto psocketDst2 = __Socket(psocketDst);

         if (m_trigger_dst[atom].plookup(psocketDst2) != nullptr)
         {

            m_trigger_dst[atom].erase_key(psocketDst2);

            return true;

         }

         _INFORMATION(psocketDst, "Unsubscribe " << atom << " Not subscribed");

         return false;
      }

      _INFORMATION(psocketDst, "Unsubscribe " << atom << " Trigger atom not found");

      return false;
      
   }


   void socket_handler::Trigger(i32 atom, socket::trigger_data& data, bool bErase)
   {

      if (m_trigger_src.contains(atom))
      {

         data.SetSource(m_trigger_src[atom]);

         m_trigger_dst[atom].pairs().each([&](auto & pair)
            {

               if (this->Valid(pair.m_pbasesocket))
               {

                  pair.m_pbasesocket->OnTrigger(atom, data);

               }

            });

         if (bErase)
         {

            m_trigger_src.erase_key(atom);
            m_trigger_dst.erase_key(atom);

         }

      }
      else
      {

         INFORMATION("Trigger " << atom << " Trigger atom not found");

      }

   }


}




