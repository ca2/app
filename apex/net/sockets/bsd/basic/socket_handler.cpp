#include "framework.h"
#include "apex/net/sockets/_.h"
#include <time.h>

#ifdef ANDROID
#undef USE_MISC

#endif

#if defined(__APPLE__)

#define bcopy(src, dest, len) ::memcpy_dup(dest, src, len)

#else

#define FD_COPY(pfdsetSrc, pfdsetDst) (*(pfdsetDst)) = (*(pfdsetSrc))

#endif


namespace sockets
{




   socket_handler::socket_handler(::layered * pobject, ::apex::log *plogger) :
      ::object(pobject),
      base_socket_handler(pobject, plogger),
      m_b_use_mutex(false)
      , m_maxsock(0)
      , m_iPreviousError(-1)
      //,m_errcnt(0)
      , m_tlast(0)
      , m_socks4_port(0)
      , m_bTryDirect(false)
      , m_resolv_id(0)
      , m_b_enable_pool(false)
      , m_next_trigger_id(0)
      , m_slave(false)
   {
      defer_create_mutex();
      xxf_zero(m_socks4_host);
      //m_prfds = new fd_set;
      //m_pwfds = new fd_set;
      //m_pefds = new fd_set;
      FD_ZERO(&m_rfds);
      FD_ZERO(&m_wfds);
      FD_ZERO(&m_efds);
      m_countR = 0;
      m_countW = 0;
      m_countE = 0;

   }


   socket_handler::~socket_handler()
   {

      cleanup_handler();

   }


   void socket_handler::cleanup_handler()
   {

      if (m_resolver.is_set())
      {

         resolver()->Quit();

      }

      {

         auto point = m_sockets.get_start();

         while (point != nullptr)
         {

            if (point->element2().is_set())
            {

               try
               {

                  point->element2()->close();

               }
               catch (...)
               {

               }

               if (m_slave)
               {

                  point->element2().release();

               }

            }

            point = m_sockets.get_next(point);

         }

      }

      m_sockets.remove_all();

      m_resolver.release();

      if (m_b_use_mutex)
      {

         mutex()->unlock();

      }

   }


   //sync & socket_handler::GetMutex() const
   //{

   //   return *mutex();

   //}


   resolv_server * socket_handler::resolver()
   {

      return m_resolver.cast < resolv_server >();

   }


   void socket_handler::SetSlave(bool x)
   {

      m_slave = x;

   }


   bool socket_handler::IsSlave()
   {

      return m_slave;

   }


   void socket_handler::add(base_socket * pbasesocket)
   {

      socket * psocket = dynamic_cast < socket * > (pbasesocket);

      if (psocket->GetSocket() == INVALID_SOCKET)
      {

         WARN(psocket, "add", -1, "Invalid socket");

         if (psocket->IsCloseAndDelete())
         {

            m_delete.add_tail(psocket);

         }

         return;

      }

      socket_pointer plookup;
      if (m_add.lookup(psocket->GetSocket(), plookup))
      {

         INFO(psocket, "add", (i32)psocket->GetSocket(), "Attempt to add socket already in add queue");

         //m_delete.add_tail(psocket);
         return;
      }

      m_add[psocket->GetSocket()] = psocket;

      psocket->m_estatus = ::success;

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

      return select(&timeval);

   }


   i32 socket_handler::select()
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


   bool socket_handler::contains(base_socket * pbasesocket)
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

   bool socket_handler::call_on_connect()
   {

      // check CallOnConnect - EVENT
      if (m_fds_callonconnect.get_size())
      {
         socket_list tmp = m_fds_callonconnect;
         auto pnode = tmp.get_head();
         for (; pnode != nullptr; pnode = pnode->m_pnext)
         {
            SOCKET socket = pnode->m_value;
            socket_pointer psocket;
            if (!m_sockets.lookup(socket, psocket)) // not found
            {

               WARN(this, "GetSocket/handler/4", (i32)socket, "Did not find expected socket using file descriptor(4)");

               AddList(psocket->GetSocket(), LIST_CALLONCONNECT, false);
            }
            if (psocket != nullptr)
            {
               tcp_socket * ptcpsocket = psocket.cast < tcp_socket >();
               if (ptcpsocket != nullptr)
               {
                  if (ptcpsocket->CallOnConnect() && psocket->Ready())
                  {
                     psocket->SetConnected(); // moved here from inside if (ptcpsocket) check below
                     if (psocket->IsSSL()) // SSL Enabled socket
                        psocket->OnSSLConnect();
                     else if (psocket->Socks4())
                        psocket->OnSocks4Connect();
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
                           psocket->OnReconnect();
                        else
                        {

                           INFO(ptcpsocket, "Calling OnConnect", 0, "Because CallOnConnect");

                           psocket->OnConnect();
                        }
                     }
                     ptcpsocket->SetCallOnConnect(false);
                     AddList(psocket->GetSocket(), LIST_CALLONCONNECT, false);
                  }
               }
            }
         }
         return true;
      }


      return false;
   }


   i32 socket_handler::select(struct timeval *tsel)
   {

      {

         try
         {

            m_sockets.values().each([](auto & psocket)
               {

                  psocket->on_select_idle();

               });

         }
         catch (...)
         {

         }

      }

      tick tick1, tick2;

start_processing_adding:

      auto p = m_add.begin();

      if (p)
      {

         if (m_sockets.get_size() >= FD_SETSIZE)
         {


            WARN(this, "Select", (i32)m_sockets.get_size(), "FD_SETSIZE reached");


            goto end_processing_adding;

         }

         SOCKET socket = p->m_socket;

         auto & psocket = p->m_psocket;

         if (m_sockets.has(psocket->GetSocket()))
         {

            FATAL(psocket, "add", (i32)psocket->GetSocket(), "Attempt to add socket already in controlled queue");

            m_add.remove_key(socket);

            goto start_processing_adding;

         }

         if (!psocket->IsCloseAndDelete())
         {

            auto pstreamsocket = psocket.cast < stream_socket >();

            if (pstreamsocket && pstreamsocket->Connecting()) // 'open' called before adding socket
            {

               set(socket, false, true);

            }
            else
            {

               auto ptcpsocket = psocket.cast < tcp_socket >();

               bool bWrite = ptcpsocket ? ptcpsocket->GetOutputLength() != 0 || ptcpsocket->CallOnConnect() : false;

               bool bRead = ptcpsocket ? !ptcpsocket->IsDisableRead() : true;

               set(socket, bRead, bWrite);

            }

            m_maxsock = (socket + 1 > m_maxsock) ? socket + 1 : m_maxsock;

         }
         else
         {

            WARN(psocket, "add", (i32)psocket->GetSocket(), "Trying to add socket with SetCloseAndDelete() true");

         }

         // only add to m_fds (process fd_set events) if
         //  slave handler and detached/detaching socket
         //  master handler and non-detached socket
         if (!(m_slave ^ psocket->IsDetach()))
         {

            m_fds.add_tail(socket);

         }

         m_sockets[socket] = psocket;

         m_add.remove_key(socket);

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

      tick1 = ::tick::now();

      tick tickRWENull;

      if (psetR == nullptr && psetW == nullptr && psetE == nullptr)
      {

         tickRWENull.Now();

         //TRACE("rfds, wfds and efds are null!!");

      }
      else
      {

         if (m_b_use_mutex)
         {

            mutex()->unlock();

            n = ::select((int)m_maxsock, psetR, psetW, psetE, tsel);

            m_iSelectErrno = Errno;

            mutex()->lock();

         }
         else
         {

            n = ::select((int)m_maxsock, psetR, psetW, psetE, tsel);

            m_iSelectErrno = Errno;

         }

      }

      tick2 = ::get_tick();

      if (n < 0)
      {

         auto tickNow = ::tick::now();

         /*
            EBADF  An invalid file descriptor was given in one of the sets.
            EINTR  A non blocked signal was caught.
            EINVAL n is negative. Or struct timeval contains bad time values (<0).
            ENOMEM select was unable to allocate memory for internal tables.
         */

         if (m_maxsock > 0 && (m_iSelectErrno != m_iPreviousError || tickNow - m_tickLastError > 5000))
         {


            INFO(log_this, "select", m_iSelectErrno, bsd_socket_error(m_iSelectErrno));


            i32 iError = m_iSelectErrno;
#ifdef LINUX
            TRACE("m_maxsock: %d\n", m_maxsock);
            TRACE("sockets::socket_handler select error : %s (%d)", strerror(Errno), Errno);
#else
            TRACE("sockets::socket_handler select error : %s (%d)", get_system_error_message(iError).c_str(), iError);
#endif

            if (iError == 10022)
            {

               TRACE("WSEINVAL - An invalid argument was supplied");

            }

            // test bad fd
            for (SOCKET i = 0; i < m_maxsock; i++)
            {
               bool t = false;
               FD_ZERO(&rfds);
               FD_ZERO(&wfds);
               FD_ZERO(&efds);
               if (FD_ISSET(i, &m_rfds))
               {
                  FD_SET(i, &rfds);
                  t = true;
               }
               if (FD_ISSET(i, &m_wfds))
               {
                  FD_SET(i, &wfds);
                  t = true;
               }
               if (FD_ISSET(i, &m_efds))
               {
                  FD_SET(i, &efds);
                  t = true;
               }

               socket_pointer psocket;

               if (t && m_sockets.lookup(i, psocket))
               {

                  TRACE("Bad fd in fd_set: %d\n", i);

                  TRACE("Deleting and removing socket: %d\n", i);

                  psocket->SetCloseAndDelete();

                  m_sockets.remove_key(i);

               }

            }

         }

         /// \no more todo rebuild fd_set's from active sockets list (m_sockets) here
         /// done : http://jbmon.googlecode.com/svn/trunk/sockets/SocketHandler.cpp : rebuild fd_set's from active sockets list (m_sockets) here
         {

            FD_ZERO(&rfds);
            FD_ZERO(&wfds);
            FD_ZERO(&efds);
            ::count countR = 0;
            ::count countW = 0;
            ::count countE = 0;

            auto it = m_sockets.begin();

            for(; it; it++)
            {

               try
               {

                  if (it->m_socket == it->m_psocket->GetSocket())
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

                        // %! bad fd, remove

                        ERR(it->m_psocket, "Select", (i32)it->m_socket, "Bad fd in fd_set (2)"); // , LOG_LEVEL_ERROR);

                        m_fds_erase.push_back(it->m_socket);

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

                           ERR(it->m_psocket, "Select", (i32)it->m_socket, "No fd in fd_set"); // , LOG_LEVEL_ERROR);

                           m_fds_erase.push_back(it->m_socket);

                        }

                     }

                  }
                  else
                  {

                     // %! mismatch

                     ERR(it->m_psocket, "Select", (i32)it->m_socket, "Bad fd in fd_set (3)"); // , LOG_LEVEL_ERROR);

                     m_fds_erase.push_back(it->m_socket);

                  }

               }
               catch (...)
               {

                  // general error

                  ERR(it->m_psocket, "Select", (i32)it->m_socket, "Bad fd in fd_set (3)"); // , LOG_LEVEL_ERROR);

                  m_fds_erase.push_back(it->m_socket);

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

         m_tickLastError = tickNow;

      }
      else if (n == 0)
      {

         m_iPreviousError = -1;

      }
      else
      {
         auto pos = m_fds.begin();
         for (; pos && n; pos++)
         {
            SOCKET socket = *pos;
            if (FD_ISSET(socket, &rfds))
            {
               socket_pointer psocket;
               if (m_sockets.lookup(socket, psocket)) // found
               {
                  // new SSL negotiate method
                  if (psocket->IsSSLNegotiate())
                  {
                     psocket->SSLNegotiate();
                  }
                  else
                  {
                     psocket->OnRead();
                  }
               }
               else
               {

                  WARN(this, "GetSocket/handler/1", (i32)socket, "Did not find expected socket using file descriptor(1)");

               }
               n--;
            }
            if (FD_ISSET(socket, &wfds))
            {
               socket_pointer psocket;
               if (m_sockets.lookup(socket, psocket)) // found
               {
                  // new SSL negotiate method
                  if (psocket->IsSSLNegotiate())
                  {
                     psocket->SSLNegotiate();
                  }
                  else
                  {
                     psocket->OnWrite();
                  }
               }
               else
               {

                  WARN(this, "GetSocket/handler/2", (i32)socket, "Did not find expected socket using file descriptor(2)");

               }
               n--;
            }
            if (FD_ISSET(socket, &efds))
            {
               socket_pointer psocket;
               if (m_sockets.lookup(socket, psocket)) // found
               {
                  time_t tnow = time(nullptr);
                  if (psocket->Timeout(tnow))
                  {
                     __pointer(stream_socket) pstreamsocket = (psocket);
                     if (pstreamsocket != nullptr && pstreamsocket->Connecting())
                        psocket->OnConnectTimeout();
                     else
                        psocket->OnTimeout();
                     psocket->SetTimeout(0);
                  }
                  else
                  {
                     psocket->OnException();
                  }
               }
               else
               {

                  WARN(this, "GetSocket/handler/3", (i32)socket, "Did not find expected socket using file descripto(3)r");

               }
               n--;
            }
         } // m_fds loop
         m_iPreviousError = -1;
      } // if (n > 0)

      call_on_connect();

      bool check_max_fd = false;

      // check detach of socket if master handler - EVENT
      if (!m_slave && m_fds_detach.get_size())
      {

         auto pos = m_fds_detach.begin();

         socket_pointer psocket;

         bool bRemove = false;

         SOCKET socket = 0;

         for (; pos; pos++)
         {

            if (bRemove)
            {

               m_fds_detach.remove(socket);

            }

            bRemove = false;

            socket = *pos;

            if (m_sockets.lookup(socket, psocket) && psocket)
            {

               if (psocket->IsDetach())
               {

                  if (socket != INVALID_SOCKET)
                  {

                     set(socket, false, false, false);

                     // After DetachSocket(), all calls to Handler() will return a context_object
                     // to the new slave socket_handler running in the new thread.
                     try
                     {

                        psocket->DetachSocket();

                     }
                     catch (...)
                     {

                     }

                     // Adding the file descriptor to m_fds_erase will now also remove the
                     // socket from the detach queue - tnx knightmad
                     m_fds_erase.add_tail(socket);

                     m_fds.remove(socket);

                     m_sockets.remove_key(socket);

                     bRemove = true;

                     check_max_fd = true;

                  }

               }

            }

         }

      }

      // check Connecting - connection timeout - conditional event
      if (m_fds_timeout.get_size())
      {
         time_t tnow = time(nullptr);
         if (tnow != m_tlast)
         {
            socket_list tmp = m_fds_timeout;
            //TRACE("Checking %d socket(s) for timeout\n", tmp.get_size());
            auto it = tmp.begin();
            for (; it; it++)
            {

               socket_pointer psocket;

               SOCKET socket = *it;

               if (!m_sockets.lookup(socket, psocket)) // not found
               {

                  if (!m_add.lookup(socket, psocket))
                  {

                     WARN(this, "GetSocket/handler/6", (i32)socket, "Did not find expected socket using file descriptor(6)");

                     AddList(socket, LIST_TIMEOUT, false);
                  }
               }
               if (psocket)
               {
                  if (psocket->Timeout(tnow))
                  {
                     __pointer(stream_socket) pstreamsocket = psocket;
                     if (pstreamsocket && pstreamsocket->Connecting())
                        psocket->OnConnectTimeout();
                     else
                        psocket->OnTimeout();
                     psocket->SetTimeout(0);
                  }
               }
            }
            m_tlast = tnow;
         } // tnow != tlast
      }
      // check retry client connect - EVENT
      if (m_fds_retry.get_size())
      {

         socket_list tmp = m_fds_retry;

         auto socket = tmp.begin();

         for (; socket; socket++)
         {

            socket_pointer psocket;

            if (m_sockets.lookup(*socket, psocket))
            {

               WARN(this, "GetSocket/handler/7", (i32)socket, "Did not find expected socket using file descriptor(7)");

            }

            if (psocket)
            {

               __pointer(tcp_socket)ptcpsocket = psocket;

               if (ptcpsocket != nullptr)
               {

                  if (ptcpsocket->RetryClientConnect())
                  {

                     SOCKET nn = socket; //(*it3).element1();

                     ptcpsocket->SetRetryClientConnect(false);

                     //TRACE("close() before retry client connect\n");

                     psocket->close(); // removes from m_fds_retry

                     ::net::address ad = psocket->GetClientRemoteAddress();

                     if (ad.is_valid())
                     {

                        ptcpsocket->open(ad);

                     }
                     else
                     {

                        ERR(psocket, "RetryClientConnect", 0, "no address");

                     }

                     add(psocket);

                     m_fds_erase.add_tail(nn);

                  }

               }

            }

         }

      }

      // check close and delete - conditional event
      if (m_fds_close.get_size() > 0)
      {

         socket_list socketlist = m_fds_close;

         auto psocketlist = socketlist.begin();

         for(; psocketlist; psocketlist++)
         {

            SOCKET socket = *psocketlist;

            socket_pointer psocket;

            if (!m_sockets.lookup(socket, psocket)) // not found
            {

               if (!m_add.lookup(socket, psocket))
               {

                  WARN(psocket, "GetSocket/handler/8", (i32)socket, "Did not find expected socket using file descriptor(8)");

               }

            }

            if (psocket)
            {

               if (psocket->IsCloseAndDelete())
               {

                  __pointer(tcp_socket) ptcpsocket = psocket;

                  // new graceful ptcpsocket - flush and close timeout 5s
                  if (ptcpsocket && psocket->IsConnected() && ptcpsocket->GetFlushBeforeClose() &&
                        !ptcpsocket->IsSSL() && psocket->TimeSinceClose() < 5)
                  {

                     //TRACE(" close(1)\n");
                     if (ptcpsocket->GetOutputLength())
                     {

                        INFO(psocket, "Closing", (i32)ptcpsocket->GetOutputLength(), "Sending all data before closing");

                     }
                     else // shutdown write when output buffer is is_empty
                        if (!(ptcpsocket->GetShutdown() & SHUT_WR))
                     {

                        if (psocket->m_socket != INVALID_SOCKET && shutdown(psocket->m_socket, SHUT_WR) == -1)
                        {

                           ERR(psocket, "graceful shutdown", Errno, bsd_socket_error(Errno));

                        }

                        ptcpsocket->SetShutdown(SHUT_WR);

                     }

                  }
                  else if (ptcpsocket && psocket->IsConnected() && ptcpsocket->Reconnect())
                  {

                     //SOCKET nn = *it; //(*it3).element1();
                     //TRACE(" close(2) fd %d\n", socket);

                     psocket->SetCloseAndDelete(false);

                     ptcpsocket->SetIsReconnect();

                     psocket->SetConnected(false);

                     //TRACE("close() before reconnect\n");

                     psocket->close(); // dispose of old file descriptor (open creates a new)

                     psocket->OnDisconnect();

                     ::net::address ad = psocket->GetClientRemoteAddress();

                     if (ad.is_valid())
                     {

                        ptcpsocket->open(ad);

                     }
                     else
                     {

                        ERR(psocket, "Reconnect", 0, "no address");

                     }

                     ptcpsocket->ResetConnectionRetries();

                     add(psocket);

                     m_fds_erase.add_tail(psocket->m_socket);

                  }
                  else
                  {

                     //TRACE(" close(3) fd %d GetSocket() %d\n", socket, point -> GetSocket());

                     if (ptcpsocket && psocket->IsConnected() && ptcpsocket->GetOutputLength())
                     {

                        WARN(psocket, "Closing", (i32)ptcpsocket->GetOutputLength(), "Closing socket while data still left to send");

                     }

                     if (psocket->Retain() && !psocket->Lost())
                     {

                        sync_lock sl(&System.sockets().m_mutexPool);

                        __pointer(pool_socket) ppoolsocket = __new(pool_socket(*this, psocket));

                        ppoolsocket->SetDeleteByHandler();

                        System.sockets().m_pool.set_at(ppoolsocket->m_socket, ppoolsocket);

                        ppoolsocket->SetCloseAndDelete(false); // added - remove from m_fds_close

                        //point -> SetCloseAndDelete(false); // added - remove from m_fds_close

                     }
                     else if (psocket.cast < http_session >() != nullptr && !psocket->Lost())
                     {

                        psocket->SetCloseAndDelete(false);

                        continue;

                     }
                     else if(psocket->GetSocket() != INVALID_SOCKET)
                     {

                        set(psocket->GetSocket(), false, false, false);

                        //TRACE("close() before OnDelete\n");

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

            m_fds_erase.add_tail(socket);

         }

      }

      // check erased sockets
      while (m_fds_erase.get_size())
      {

         SOCKET socket = m_fds_erase.pop_head();

         m_fds_detach.remove(socket);

         m_fds.remove(socket);

         m_fds_close.remove(socket);

         socket_pointer psocket;

         if (m_sockets.lookup(socket, psocket))
         {

            if (psocket.cast < pool_socket >() == nullptr)
            {

               m_sockets.remove_key(socket);

            }
            else
            {

               m_delete.remove(psocket);

            }

            if (m_add[socket].cast < pool_socket >() == nullptr)
            {

               m_add.remove_key(socket);

            }

         }

         check_max_fd = true;

      }

      // calculate MAX file descriptor for select() call
      if (check_max_fd)
      {

         m_maxsock = m_fds.maximum(0) + 1;

      }

      // remove add's that fizzed
      while (m_delete.get_size() > 0)
      {

         __pointer(socket) psocket = m_delete.pop_head();

         psocket->OnDelete();

         if (psocket->DeleteByHandler() && !(m_slave ^ psocket->IsDetached()))
         {

            psocket->SetErasedByHandler();

            bool again = false;

            do
            {

               again = false;

               auto p = m_trigger_src.begin();

               for(; p; p++)
               {
                  //SOCKET id = 0;
                  //socket_pointer src;

                  //iterator->get_pair(id, src);

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

                     m_trigger_src.remove_key(p->m_socket);

                     m_trigger_dst.remove_key(p->m_socket);

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


   bool socket_handler::Resolving(base_socket * p0)
   {

      return m_resolve_q.plookup(p0) != nullptr;

   }


   bool socket_handler::Valid(base_socket * pIsValid)
   {

      auto p = m_sockets.begin();

      for(; p; p++)
      {

         if (pIsValid == p->m_psocket)
         {

            return true;

         }

      }

      return false;

   }


   bool socket_handler::OkToAccept(base_socket *)
   {

      return true;

   }


   ::count socket_handler::get_count()
   {
      /*
      debug_print(" m_sockets : %d\n", m_sockets.size());
      debug_print(" m_add     : %d\n", m_add.size());
      debug_print(" m_delete  : %d\n", m_delete.size());
      */

      ::count iSockets = m_sockets.get_size();

      ::count iAdd = m_add.get_size();

      ::count iDelete = m_delete.get_size();

      return iSockets + iAdd + iDelete;

   }


   void socket_handler::SetSocks4Host(in_addr a)
   {
      m_socks4_host = a;
   }


   void socket_handler::SetSocks4Host(const string & host)
   {
      System.sockets().net().convert(m_socks4_host, host);
   }


   void socket_handler::SetSocks4Port(port_t port)
   {
      m_socks4_port = port;
   }


   void socket_handler::SetSocks4Userid(const string & id)
   {
      m_socks4_userid = id;
   }


   i32 socket_handler::Resolve(base_socket * point, const string & host, port_t port)
   {
      // check cache
      __pointer(resolv_socket) resolv = __new(resolv_socket(*this, point, host, port));
      resolv->SetId(++m_resolv_id);
      resolv->SetDeleteByHandler();
      in_addr addrLocal;
      System.sockets().net().convert(addrLocal, "127.0.0.1");
      if (!resolv->open(::net::address(addrLocal, m_resolver_port)))
      {

         FATAL(resolv, "Resolve", -1, "Can't connect to local resolve server");

      }
      add(resolv);
      m_resolve_q[point] = true;
      TRACE(" *** Resolve '%s:%d' id#%d  m_resolve_q size: %d  point: %point\n", host.c_str(), port, resolv->GetId(), m_resolve_q.get_size(), point);
      return resolv->GetId();
   }


   i32 socket_handler::Resolve6(base_socket * point, const string & host, port_t port)
   {
      // check cache
      __pointer(resolv_socket) resolv = __new(resolv_socket(*this, point, host, port, true));
      resolv->SetId(++m_resolv_id);
      resolv->SetDeleteByHandler();
      in_addr addrLocal;
      System.sockets().net().convert(addrLocal, "127.0.0.1");
      if (!resolv->open(::net::address(addrLocal, m_resolver_port)))
      {

         FATAL(resolv, "Resolve", -1, "Can't connect to local resolve server");

      }
      add(resolv);
      m_resolve_q[point] = true;
      return resolv->GetId();
   }


   i32 socket_handler::Resolve(base_socket * point, in_addr a)
   {
      // check cache
      __pointer(resolv_socket) resolv = __new(resolv_socket(*this, point, a));
      resolv->SetId(++m_resolv_id);
      resolv->SetDeleteByHandler();
      in_addr addrLocal;
      System.sockets().net().convert(addrLocal, "127.0.0.1");
      if (!resolv->open(::net::address(addrLocal, m_resolver_port)))
      {

         FATAL(resolv, "Resolve", -1, "Can't connect to local resolve server");

      }
      add(resolv);
      m_resolve_q[point] = true;
      return resolv->GetId();
   }


   i32 socket_handler::Resolve(base_socket * point, in6_addr& a)
   {
      // check cache
      __pointer(resolv_socket) resolv = __new(resolv_socket(*this, point, a));
      resolv->SetId(++m_resolv_id);
      resolv->SetDeleteByHandler();
      in_addr addrLocal;
      System.sockets().net().convert(addrLocal, "127.0.0.1");
      if (!resolv->open(::net::address(addrLocal, m_resolver_port)))
      {

         FATAL(resolv, "Resolve", -1, "Can't connect to local resolve server");

      }
      add(resolv);
      m_resolve_q[point] = true;
      return resolv->GetId();
   }


   void socket_handler::EnableResolver(port_t port)
   {

      if (!m_resolver)
      {

         m_resolver_port = port;

         auto presolvserver = __new(resolv_server());

         m_resolver = presolvserver;

         presolvserver->initialize_resolv_server(this, port);

      }

   }


   bool socket_handler::ResolverReady()
   {
      return m_resolver ? resolver()->Ready() : false;
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


   __pointer(base_socket_handler::pool_socket) socket_handler::FindConnection(i32 type, const string & protocol, const ::net::address & ad)
   {

      sync_lock sl(&System.sockets().m_mutexPool);

      auto p = System.sockets().m_pool.begin();

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

               System.sockets().m_pool.remove_key(p->m_socket);

               psocket->SetRetain(); // avoid close in socket destructor

               return psocket; // Caller is responsible that this socket is deleted

            }

         }

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


   void socket_handler::remove(base_socket * psocketRemove)
   {

      if (m_resolve_q.has(psocketRemove))
      {

         m_resolve_q.remove_key(psocketRemove);

      }

      if (psocketRemove->ErasedByHandler())
      {

         return;

      }

      if(::remove_value(m_sockets, psocketRemove))
      {

         WARN(psocketRemove, "remove", -1, "socket destructor called while still in use");

         return;

      }

      if (::remove_value(m_add, psocketRemove))
      {

         WARN(psocketRemove, "remove", -2, "socket destructor called while still in use");

         return;

      }

      if (::remove_value(m_delete, psocketRemove))
      {

         WARN(psocketRemove, "remove", -3, "socket destructor called while still in use");

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


   void socket_handler::CheckList(socket_list & list, const string & listname)
   {

      auto p = list.begin();

      for(; (bool) p ; p++)
      {

         if (m_sockets.has(*p))
         {

            continue;

         }

         if (m_add.has(*p))
         {

            continue;

         }

         if (!::contains_value(m_delete, *p))
         {

            TRACE("CheckList failed for \"%s\": fd %d\n", listname.c_str(), *p);

         }

      }

   }


   void socket_handler::AddList(SOCKET s, list_t which_one, bool add)
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
                     add ? "add" : "remove");*/
      }
      if (add)
      {
         ref.add_tail_unique(s);
         if (which_one == LIST_CLOSE)
         {

            //INFO(output_debug_string("list_close");
         }
         return;
      }
      // remove
      ref.remove(s);
      //TRACE("/AddList\n");
   }


   i32 socket_handler::TriggerID(base_socket * src)
   {
      i32 id = m_next_trigger_id++;
      m_trigger_src[id] = src;
      return id;
   }


   bool socket_handler::Subscribe(i32 id, base_socket * psocketDst)
   {
      if (m_trigger_src.plookup(id) != nullptr)
      {
         if (m_trigger_dst[id].plookup(psocketDst) != nullptr)
         {
            m_trigger_dst[id][psocketDst] = true;
            return true;
         }

         INFO(psocketDst, "Subscribe", id, "Already subscribed");

         return false;
      }

      INFO(psocketDst, "Subscribe", id, "Trigger id not found");

      return false;
   }


   bool socket_handler::Unsubscribe(i32 id, base_socket * psocketDst)
   {
      if (m_trigger_src.plookup(id) != nullptr)
      {
         if (m_trigger_dst[id].plookup(psocketDst) != nullptr)
         {
            m_trigger_dst[id].remove_key(psocketDst);
            return true;
         }

         INFO(psocketDst, "Unsubscribe", id, "Not subscribed");

         return false;
      }

      INFO(psocketDst, "Unsubscribe", id, "Trigger id not found");

      return false;
   }


   void socket_handler::Trigger(i32 id, socket::trigger_data& data, bool bErase)
   {

      if (m_trigger_src.contains(id))
      {

         data.SetSource(m_trigger_src[id]);

         m_trigger_dst[id].pairs().each([&](auto & pair)
            {

               if (this->Valid(pair.m_pbasesocket))
               {

                  pair.m_pbasesocket->OnTrigger(id, data);

               }

            });

         if (bErase)
         {

            m_trigger_src.remove_key(id);
            m_trigger_dst.remove_key(id);

         }

      }
      else
      {

         INFO(log_this, "Trigger", id, "Trigger id not found");

      }

   }


}




