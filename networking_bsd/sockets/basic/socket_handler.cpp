#include "framework.h"
#include "socket_handler.h"
#include "tcp_socket.h"
#include "networking_bsd/networking.h"
#include "acme/acme.h"
#include "acme/parallelization/synchronous_lock.h"
#include "apex/platform/system.h"


#include "acme/_operating_system.h"


#include <time.h>

#ifdef ANDROID
#undef USE_MISC

#endif




#if defined(__APPLE__) || defined(FREEBSD)

#define bcopy(src, dest, len) ::memory_copy(dest, src, len)

#else

#define FD_COPY(pfdsetSrc, pfdsetDst) (*(pfdsetDst)) = (*(pfdsetSrc))

#endif


namespace sockets_bsd
{


   //::interlocked_count g_interlockedcountSocketHandler;


   //socket_handler::socket_handler(::particle * pparticle, ::apex::log *plogger) :
   socket_handler::socket_handler() :
      //::object(pparticle),
      //base_socket_handler(plogger),
      m_b_use_mutex(false)
      , m_maxsock(0)
      , m_iPreviousError(-1)
      //,m_errcnt(0)
      , m_tlast{}
      , m_socks4_port(0)
      , m_bTryDirect(false)
      //, m_resolv_id(0)
      , m_bEnablePool(false)
      , m_next_trigger_id(0)
      , m_bSlave(false)
   {

      m_p2 = this;
      defer_create_synchronization();
      zero(m_socks4_host);
      //m_prfds = __new< fd_set >();
      //m_pwfds = __new< fd_set >();
      //m_pefds = __new< fd_set >();
      FD_ZERO(&m_rfds);
      FD_ZERO(&m_wfds);
      FD_ZERO(&m_efds);
      m_countR = 0;
      m_countW = 0;
      m_countE = 0;

      //g_interlockedcountSocketHandler++;

      //::information() << "socket_handler allocated count = " << (::i64) g_interlockedcountSocketHandler;

   }


   socket_handler::~socket_handler()
   {

      cleanup_handler();

      //g_interlockedcountSocketHandler--;

   }



   i64 socket_handler::increment_reference_count()
   {

      return ::object::increment_reference_count();

   }


   i64 socket_handler::decrement_reference_count()
   {

      return ::object::decrement_reference_count();

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

         auto iterator = m_socketmap.begin();

         while (iterator.is_set())
         {

            if (iterator->element2().is_set())
            {

               try
               {

                  iterator->element2()->close();

               }
               catch (...)
               {

               }

               if (m_bSlave)
               {

                  iterator->element2().release();

               }

            }

            iterator++;

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


   void socket_handler::SetSlave(bool x)
   {

      m_bSlave = x;

   }


   bool socket_handler::IsSlave()
   {

      return m_bSlave;

   }
   

   //void socket_handler::add(::sockets::base_socket * psocket)
   //{

   //   auto psocket2 = __Socket(psocket);

   //   auto iterator = m_socketmapAdd.get_item(psocket2->GetSocketId());

   //   iterator->m_psocket = psocket2;

   //   psocket2->m_psockethandler = this;

   //   iterator.get();

   //}

   
   //void socket_handler::move2(::sockets::socket_pointer && psocket)
   //{

   //   //auto psocket2 = __Socket(psocket);

   //   //auto iterator = m_socketmapAdd.get_item(psocket2->GetSocketId());

   //   //iterator->m_psocket = psocket2;

   //   //transfer(iterator.get(), &m_socketmapAdd);

   //   transfer(psocket, &m_socketmapAdd);

   //}


   //void socket_handler::transfer(socket_map::node* passociation, socket_map* psocketmap)
   void socket_handler::add(::sockets::base_socket * psocket)
   {

      //::pointer < socket > psocket = pbasesocket;

      if (::is_set(psocket->socket_handler()))
      {

         warning() << "socket_handler add " << (i32)psocket->GetSocketId() << " socket is already being handled by another handler";

         return;

      }

      if (psocket->GetSocketId() == INVALID_SOCKET)
      {

         warning() <<"add: Invalid socket";

         if (psocket->IsCloseAndDelete())
         {

            m_delete.add_tail(psocket);

         }

         return;

      }

      socket_pointer plookup;

      if (m_socketmapAdd.lookup(__Socket(psocket)->GetSocketId(), plookup))
      {

         information() << "add: Invalid socket " << (i32) __Socket(psocket)->GetSocketId() << " Attempt to add socket already in add queue";

         //m_delete.add_tail(psocket);
         return;

      }

      if (psocket->is_connecting())
      {

         if (psocket->m_timeConnectionMaximum > 0_s)
         {

            socket_id_list_add(psocket->GetSocketId(), e_list_timeout);

         }

      }
      else
      {

         if (psocket->m_timeMaximum > 0_s)
         {

            socket_id_list_add(__Socket(psocket)->GetSocketId(), e_list_timeout);

         }

      }

      if (psocket->IsDetach())
      {

         socket_id_list_add(__Socket(psocket)->GetSocketId(), e_list_detach);

      }

      psocket->SetSocketHandler(this);

      psocket->m_estatus = ::success;

      auto& a = m_socketmapAdd[psocket->GetSocketId()];

       a= psocket;


      auto xxx = m_socketmapAdd[psocket->GetSocketId()];

   }


   void socket_handler::restart_socket(SOCKET socket)
   {

      auto passociation = m_socketmap.find_item(socket);

      if (passociation->m_psocket->is_connecting())
      {

         if (passociation->m_psocket->m_timeConnectionMaximum > 0_s)
         {

            socket_id_list_add(passociation->m_psocket->GetSocketId(), e_list_timeout);

         }

      }
      else
      {

         if (passociation->m_psocket->m_timeMaximum > 0_s)
         {

            socket_id_list_add(__Socket(passociation->m_psocket)->GetSocketId(), e_list_timeout);

         }

      }

      passociation->m_psocket->m_estatus = ::success;

      m_socketmapAdd[passociation->element1()] = passociation->element2();

      auto xxx = m_socketmapAdd[passociation->element1()];

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
            (!m_bSlave && m_socketlistDetach.get_size()) ||
            //m_socketlistDetach.get_size() ||
            m_socketlistTimeout.get_size() ||
            m_socketlistRetryClientConnect.get_size() ||
            m_socketlistClose.get_size() ||
            m_socketlistErase.get_size())
      {

         return select(0, 200000);

      }

      return _select(nullptr);

   }


   i32 socket_handler::select(const class time & timeWait)
   {

      struct timeval tsel;

      tsel.tv_sec = (long)timeWait.integral_second();

      tsel.tv_usec = ((long)timeWait.integral_microsecond()) % 1'000'000;

      return _select(&tsel);

   }


   bool socket_handler::contains(::sockets::base_socket * pbasesocket)
   {

      socket_pointer psocket = pbasesocket;

      if (::generic::map::contains_payload(m_socketmap, psocket))
      {

         return true;

      }

      if (::generic::map::contains_payload(m_socketmapAdd, psocket))
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

         auto p = tmp.begin();

         for (; p.is_ok(); p++)
         {

            SOCKET socket = *p;

            socket_pointer psocket;

            if (!m_socketmap.lookup(socket, psocket)) // not found
            {

               warning() <<"socket_handler " << (i32)socket << " Did not find expected socket using file descriptor(4)";

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

                        ptcpsocket->information() << "OnSSLConnect";

                        psocket->OnSSLConnect();

                     }
                     else if (psocket->Socks4())
                     {

                        ptcpsocket->information() << "OnSocks4Connect";

                        psocket->OnSocks4Connect();

                     }
                     else
                     {

                        if (ptcpsocket)
                        {

                           if (ptcpsocket->GetOutputLength())
                           {

                              ptcpsocket->information() << "OnWrite";

                              psocket->OnWrite();

                           }

                        }

                        if (ptcpsocket && ptcpsocket->IsReconnect())
                        {

                           ptcpsocket->information() << "OnReconnect";

                           psocket->OnReconnect();

                        }
                        else
                        {

                           ptcpsocket->information() << "Calling OnConnect: Because CallOnConnect";

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

      try
      {

         for(auto & p : m_socketmap)
         {

            p.m_psocket->on_select_idle();

         }

      }
      catch (...)
      {

      }

      class ::time tick1, tick2;

start_processing_adding:

      auto passociationAdd = m_socketmapAdd.begin();

      if (passociationAdd.is_ok())
      {

         if (m_socketmap.get_size() >= FD_SETSIZE)
         {

            warning() <<"Select " << (i32)m_socketmap.get_size() << " FD_SETSIZE reached";

            goto end_processing_adding;

         }

         SOCKET socket = passociationAdd->m_socket;

         auto psocket = passociationAdd->m_psocket;

         if (m_socketmap.has(socket))
         {

            psocket->warning() << "add" << (i32)__Socket(psocket)->GetSocketId() << "Attempt to add socket already in controlled queue";

            m_socketmapAdd.erase(passociationAdd);

            goto start_processing_adding;

         }

         if (psocket->IsCloseAndDelete())
         {

            psocket->warning() << "add " << (i32)__Socket(psocket)->GetSocketId() << " Trying to add socket with SetCloseAndDelete() true";

            m_socketlist.add_tail(socket);

            m_socketmap[passociationAdd->element1()] = passociationAdd->element2();

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
         if (is_equivalent(m_bSlave, psocket->IsDetach()))
         {

           // m_socketlist.add_tail(socket);
            m_socketlist.add_tail(socket);

         }

         //m_socketlist.add_tail(socket);

         m_socketmap[socket] = psocket;

         m_socketmapAdd.erase_item(socket);

         if (m_bSlave && psocket->IsDetach())
         {

            psocket->OnDetached();

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

      tick1 = ::time::now();

      class ::time tickRWENull;

      if (psetR == nullptr && psetW == nullptr && psetE == nullptr)
      {

         tickRWENull.Now();

         //information() << "rfds, wfds and efds are null!!");

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

      tick2 = ::time::now();

      if (n < 0)
      {

         auto tickNow = ::time::now();

         /*
            EBADF  An invalid file descriptor was given in one of the sets.
            EINTR  A non blocked signal was caught.
            EINVAL n is negative. Or struct timeval contains bad time values (<0).
            ENOMEM select was unable to allocate memory for internal tables.
         */

         if (m_maxsock > 0 && (m_iSelectErrno != m_iPreviousError || tickNow - m_timeLastError > 5_s))
         {

            information() << "select" << m_iSelectErrno << ", " << bsd_socket_error(m_iSelectErrno);

            i32 iError = m_iSelectErrno;

#if defined(LINUX) || defined(MACOS)

            information() << "m_maxsock: " << m_maxsock;
            information() << "networking_bsd::socket_handler select error : "<< strerror(networking_last_error()) <<" ("<< networking_last_error() <<")";

#elif defined(WINDOWS)

            information() << "networking_bsd::socket_handler select error : "<< ::windows::last_error_message(iError) <<" ("<< iError <<")";

#endif

            if (iError == 10022)
            {

               information() << "WSEINVAL - An invalid argument was supplied";

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

                     information() << "Bad fd in fd_set: " << socket;

                     information() << "Deleting and removing socket: " << socket;

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

            auto p = m_socketmap.begin();

            for(; p.is_ok(); p++)
            {

               try
               {

                  if (p->m_socket == __Socket(p->m_psocket)->GetSocketId())
                  {

                     fd_set fds;

                     FD_ZERO(&fds);

                     FD_SET(p->m_socket, &fds);

                     struct timeval tv;

                     tv.tv_sec = 0;

                     tv.tv_usec = 0;

                     i32 n = ::select((i32)(p->m_socket + 1), &fds, nullptr, nullptr, &tv);

                     if (n == -1)
                     {

                        // %! bad fd, erase

                        p->m_psocket->error() << " Select " << (i32)p->m_socket << "Bad fd in fd_set (2)"; // ->error() << LOG_LEVEL_ERROR);

                        m_socketlistErase.add(p->m_socket);

                     }
                     else
                     {

                        bool bAnySet = false;

                        if (FD_ISSET(p->m_socket, &m_rfds))
                        {

                           FD_SET(p->m_socket, &rfds);

                           countR++;

                           bAnySet = true;

                        }

                        if (FD_ISSET(p->m_socket, &m_wfds))
                        {

                           FD_SET(p->m_socket, &wfds);

                           countW++;

                           bAnySet = true;

                        }

                        if (FD_ISSET(p->m_socket, &m_efds))
                        {

                           FD_SET(p->m_socket, &efds);

                           countE++;

                           bAnySet = true;

                        }

                        if (!bAnySet)
                        {

                           // %! none set

                           p->m_psocket->error() << "Select " << (i32)p->m_socket << " No fd in fd_set"; // ->error() << LOG_LEVEL_ERROR);

                           m_socketlistErase.add(p->m_socket);

                        }

                     }

                  }
                  else
                  {

                     // %! mismatch

                     p->m_psocket->error() << "Select" << (i32)p->m_socket << "Bad fd in fd_set (3)"; // ->error() << LOG_LEVEL_ERROR);

                     m_socketlistErase.add(p->m_socket);

                  }

               }
               catch (...)
               {

                  // general error

                  p->m_psocket->error() << "Select" << (i32)p->m_socket << "Bad fd in fd_set (3)"; // ->error() << LOG_LEVEL_ERROR);

                  m_socketlistErase.add(p->m_socket);

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

         m_timeLastError = tickNow;

      }
      else if(n == 0)
      {

         m_iPreviousError = -1;

      }
      else // n > 0
      {

         auto p = m_socketlist.begin();

         for (; p.is_ok() && n; p++)
         {
            
            SOCKET socket = *p;

            if (FD_ISSET(socket, &rfds))
            {
               
               auto ppairSocket = m_socketmap.plookup(socket);

               if (::is_set(ppairSocket) && ::is_set(ppairSocket->m_psocket)) // found
               {

                  // new SSL negotiate method
                  if (ppairSocket->m_psocket->IsSSLNegotiate())
                  {

                     //ppairSocket->m_psocket->information() << "SSLNegotiate";
                     
                     ppairSocket->m_psocket->SSLNegotiate();

                  }
                  else
                  {

                     //ppairSocket->m_psocket->information() << "OnRead";
                     
                     ppairSocket->m_psocket->OnRead();

                  }

               }
               else
               {

                  warning() << "socket_handler " << (i32)socket << "Did not find expected socket using file descriptor(1)";

               }

               n--;

            }

            if (FD_ISSET(socket, &wfds))
            {
               
               auto ppairSocket = m_socketmap.plookup(socket);

               if (::is_set(ppairSocket) && ::is_set(ppairSocket->m_psocket)) // found
               {

                  // new SSL negotiate method
                  if (ppairSocket->m_psocket->IsSSLNegotiate())
                  {

                     //ppairSocket->m_psocket->information() << "SSLNegotiate";

                     ppairSocket->m_psocket->SSLNegotiate();

                  }
                  else
                  {

                     ppairSocket->m_psocket->information() << "OnWrite";

                     ppairSocket->m_psocket->OnWrite();

                  }

               }
               else
               {

                  warning() << "socket_handler " << (i32)socket << " Did not find expected socket using file descriptor(2)";

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
                  //posix_time tnow = time(nullptr);

                  if (ppairSocket->m_psocket->has_timed_out())
                  {
                  
                     if (ppairSocket->m_psocket->is_connecting())
                     {

                        warning() << "socket_handler " << (i32)socket << " stream_socket on_connection_timeout (3)";

                        ppairSocket->m_psocket->on_connection_timeout();

                     }
                     else
                     {

                        warning() << "socket_handler " << (i32)socket << " socket on_timeout(3)";

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

                  warning() << "socket_handler " << (i32)socket << " Did not find expected socket using file descripto(3)r";

               }

               n--;

            }

         } // m_socketlist loop

         m_iPreviousError = -1;

      } // if (n > 0)

      call_on_connect();

      bool check_max_fd = false;

      // check detach of socket if master handler - EVENT
      if (!m_bSlave && m_socketlistDetach.get_size())
      //if(m_socketlistDetach.has_element())
      {

         auto it = m_socketlistDetach.begin();

         SOCKET socket = 0;

         while(it != m_socketlistDetach.end())
         {

            auto socket = *it;

            it++;
            
            auto ppairSocket = m_socketmap.plookup(socket);

            if (::is_set(ppairSocket) && ::is_set(ppairSocket->m_psocket))
            {

               auto psocket = ppairSocket->m_psocket;

               if (psocket->IsDetach() && !psocket->IsDetached())
               {

                  erase_socket(socket);

                  // After DetachSocket(), all calls to socket_handler() will return a object
                  // to the new slave socket_handler running in the new thread.
                  try
                  {

                     psocket->DetachSocket();

                  }
                  catch (...)
                  {

                  }

                  m_socketmap.erase_item(socket);

                  check_max_fd = true;

               }

            }

         }

      }

      // check is_connecting - connection timeout - conditional event
      if (m_socketlistTimeout.get_size())
      {
         
         ::earth::time tnow(now_t{});
         
         //= time(nullptr);

         if (tnow != m_tlast)
         {

            restartSocketListTimeout:

            socket_id_list tmp = m_socketlistTimeout;

            auto p = tmp.begin();

            for (; p.is_ok(); p++)
            {

               SOCKET socket = *p;

               auto ppairSocket = m_socketmap.plookup(socket);

               if (ppairSocket.is_null() || ::is_null(ppairSocket->m_psocket)) // not found
               {

                  ppairSocket = m_socketmapAdd.plookup(socket);

                  if (ppairSocket.is_null() || ::is_null(ppairSocket->m_psocket))
                  {

                     warning() << "socket_handler " << (i32)socket << " Did not find expected socket using file descriptor(f)";

                     m_socketlistTimeout.erase_item(socket);

                     goto restartSocketListTimeout;

                  }

                  continue;

               }
               
               if (ppairSocket.is_ok() && ::is_set(ppairSocket->m_psocket))
               {

                  if (ppairSocket->m_psocket->has_timed_out())
                  {

                     if (ppairSocket->m_psocket->is_connecting())
                     {

                        warning() << "socket_handler " << (i32)socket << " stream_socket on_connection_timeout (g)";

                        ppairSocket->m_psocket->on_connection_timeout();

                     }
                     else
                     {

                        warning() << "socket_handler " << (i32)socket << " socket on_timeout (g)";

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

         auto p = tmp.begin();

         for (; p.is_ok(); p++)
         {

            auto ppairSocket = m_socketmap.plookup(*p);

            if (ppairSocket.is_null() || ::is_null(ppairSocket->m_psocket))
            {

               warning() << "socket_handler " << (i32)*p << " Did not find expected socket using file descriptor(g)";

            }

            if (ppairSocket.is_ok() && ::is_set(ppairSocket->m_psocket))
            {

               auto ptcpsocket = ppairSocket->m_psocket.cast < tcp_socket >();

               if (::is_set(ptcpsocket))
               {

                  if (ptcpsocket->RetryClientConnect())
                  {

                     SOCKET nn = *p; //(*it3).element1();

                     ptcpsocket->SetRetryClientConnect(false);

                     //information() << "close() before retry client connect\n");

                     ptcpsocket->close(); // erases from m_socketlistRetryClientConnect

                     auto paddress = ptcpsocket->GetClientRemoteAddress();

                     if (paddress->is_valid())
                     {

                        ptcpsocket->open(paddress);

                     }
                     else
                     {

                        ptcpsocket->error() << "RetryClientConnect 0 no address";

                     }

                     m_socketmap[ptcpsocket->GetSocketId()] = ptcpsocket;

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

         for(; psocketlist.is_ok(); psocketlist++)
         {

            SOCKET socket = *psocketlist;

            socket_map* psocketmap = nullptr;

            auto ppairSocket = m_socketmap.plookup(socket);

            if (ppairSocket.is_null() || ::is_null(ppairSocket->m_psocket)) // not found
            {

               ppairSocket = m_socketmapAdd.plookup(socket);

               if (ppairSocket.is_null() || ::is_null(ppairSocket->m_psocket))
               {

                  warning() << "socket_handler " << (i32)socket << " Did not find expected socket using file descriptor(8)";

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

            if (ppairSocket.is_ok() && ::is_set(ppairSocket->m_psocket))
            {

               auto psocket = ppairSocket->m_psocket.m_p;

               if (psocket->IsCloseAndDelete())
               {

                  auto ptcpsocket = dynamic_cast <tcp_socket*> (psocket);

                  // new graceful ptcpsocket - flush and close timeout 5s
                  if (::is_set(ptcpsocket) && psocket->IsConnected() && ptcpsocket->GetFlushBeforeClose() &&
                        !ptcpsocket->IsSSL() && psocket->TimeSinceClose().m_iSecond < 5)
                  {

                     //information() << " close(1)\n");
                     if (ptcpsocket->GetOutputLength())
                     {

                        ptcpsocket->information() << "Closing " << (i32)ptcpsocket->GetOutputLength() << " Sending all data before closing";

                     }
                     else // shutdown write when output buffer is is_empty
                        if (!(ptcpsocket->GetShutdownStatus() & SHUT_WR))
                     {

                        if (ptcpsocket->GetSocketId() != INVALID_SOCKET && shutdown(psocket->GetSocketId(), SHUT_WR) == -1)
                        {

                           ptcpsocket->error() << "graceful shutdown " << networking_last_error() << bsd_socket_error(networking_last_error());

                        }

                        ptcpsocket->SetShutdownStatus(SHUT_WR);

                     }

                  }
                  else if (::is_set(ptcpsocket) && psocket->IsConnected() && ptcpsocket->Reconnect())
                  {

                     //SOCKET nn = *it; //(*it3).element1();
                     //informationf(" close(2) fd %d\n", socket));

                     ptcpsocket->SetCloseAndDelete(false);

                     ptcpsocket->SetIsReconnect();

                     ptcpsocket->SetConnected(false);

                     //information() << "close() before reconnect\n");

                     ptcpsocket->close(); // dispose of old file descriptor (open creates a new)

                     ptcpsocket->OnDisconnect();

                     auto paddress = ptcpsocket->GetClientRemoteAddress();

                     if (paddress->is_valid())
                     {

                        ptcpsocket->open(paddress);

                     }
                     else
                     {

                        ptcpsocket->error() << "Reconnect 0 no address";

                     }

                     ptcpsocket->ResetConnectionRetryCount();

                     psocketmap->set_at(ptcpsocket->GetSocketId(), ptcpsocket);

                     m_socketlistErase.add_tail(ptcpsocket->m_socket);

                  }
                  else
                  {

                     //informationf(" close(3) fd %d GetSocket() %d\n", socket, point_i32 -> GetSocket()));

                     if (psocket && psocket->IsConnected() && ptcpsocket->GetOutputLength())
                     {

                        psocket->warning() << "Closing " << (i32)ptcpsocket->GetOutputLength() << " Closing socket while data still left to send";

                     }

                     if (psocket->Retain() && !psocket->Lost())
                     {

                        auto psystem = system()->m_papexsystem;

                        synchronous_lock synchronouslock(__SystemNetworking(psystem)->m_pmutexPool);

                        auto ppoolsocket = __allocate< pool_socket >(psocket);

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

                        //information() << "close() before OnDelete\n");

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

         SOCKET socket = ::transfer(m_socketlistErase.pick_head());

         erase_socket(socket);

         auto ppairSocket = m_socketmap.plookup(socket);

         if (::is_set(ppairSocket) && ::is_set(ppairSocket->m_psocket))
         {

            ppairSocket->m_psocket->SetSocketHandler(nullptr);

            //ppairSocket->m_psocket->m_phandlerSlave.release();

            m_socketmap.erase_item(socket);

            m_delete.erase_item(ppairSocket->m_psocket);

            m_socketmapAdd.erase_item(socket);

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

         auto socket = ::transfer(m_delete.pick_head());

         auto psocket = socket.m_p;

         psocket->OnDelete();

         if (psocket->DeleteByHandler() && is_equivalent(m_bSlave, psocket->IsDetached()))
         //if (psocket->DeleteByHandler() && psocket->IsDetached())
         {

            psocket->SetErasedByHandler();

            bool again = false;

            do
            {

               again = false;

               auto p = m_trigger_src.begin();

               for(; p.is_ok(); p++)
               {
                  //SOCKET atom = 0;
                  //socket_pointer src;

                  //iterator->get_pair(atom, src);

                  if (p->m_psocket == psocket)
                  {

                     auto pdst = m_trigger_dst[p->m_socket].begin();

                     for(;pdst.is_ok(); pdst++)
                     {

                        if (Valid(pdst->m_pbasesocket))
                        {

                           pdst->m_pbasesocket->OnCancelled(p->m_socket);

                        }

                     }

                     m_trigger_src.erase_item(p->m_socket);

                     m_trigger_dst.erase_item(p->m_socket);

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

      for(; p.is_ok(); p++)
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
//      ::pointer<resolv_socket>presolvsocket = __allocate< resolv_socket >(pbasesocket, host, port);
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
//         fatal() <<presolvsocket, "Resolve", -1, "Can't connect to local resolve server";
//
//      }
//
//      add(presolvsocket);
//
//      m_resolve_q[pbasesocket] = true;
//
//      informationf(" *** Resolve '%s:%d' atom#%d  m_resolve_q size_i32: %d  base_socket: %p\n", host.c_str(), port, presolvsocket->GetId(), m_resolve_q.get_size(), pbasesocket));
//
//      return presolvsocket->GetId();
//
//   }


//   i32 socket_handler::Resolve6(base_socket * pbasesocket, const string & host, port_t port)
//   {
//
//      // check cache
//
//      ::pointer<resolv_socket>resolv = __allocate< resolv_socket >(pbasesocket, host, port, true);
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
//         fatal() <<resolv, "Resolve", -1, "Can't connect to local resolve server";
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
//      ::pointer<resolv_socket>resolv = __allocate< resolv_socket >(pbasesocket, a);
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
//         fatal() <<resolv, "Resolve", -1, "Can't connect to local resolve server";
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
//      ::pointer<resolv_socket>resolv = __allocate< resolv_socket >(pbasesocket, a);
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
//         fatal() <<resolv, "Resolve", -1, "Can't connect to local resolve server";
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
//         auto presolvserver = __allocate< resolv_server >();
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

      auto pnetworking2 = __SystemNetworking(system());

      synchronous_lock synchronouslock(pnetworking2->m_pmutexPool);

      auto p = pnetworking2->m_pool.begin();

      for(; p.is_ok(); p++)
      {

         auto psocket = p->m_psocket;

         if (psocket)
         {

            if (psocket->GetSocketType() == type &&
                  psocket->GetSocketProtocol() == protocol &&
                  // %!             pools -> GetClientRemoteAddress() &&
                  psocket->GetClientRemoteAddress() == ad)
            {

               pnetworking2->m_pool.erase_item(p->m_socket);

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

      if(m_socketmap.erase_payload(psocketRemove))
      {

         psocketRemove->warning() << "erase -1 socket destructor called while still in use";

         return;

      }

      if (m_socketmapAdd.erase_payload(psocketRemove))
      {

         psocketRemove->warning() << "erase -2 socket destructor called while still in use";

         return;

      }

      if (m_delete.erase_item(psocketRemove))
      {

         psocketRemove->warning() << "erase -3 socket destructor called while still in use";

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

      for(; p.is_ok() ; p++)
      {

         if (m_socketmap.has(*p))
         {

            continue;

         }

         if (m_socketmapAdd.has(*p))
         {

            continue;

         }

//         if (!::contains_payload(m_delete, *p))
//         {
//
//            informationf("CheckList failed for \"%s\": fd %d\n", listname.c_str(), *p));
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
         information() << "AddList:  invalid_socket";
         return;
      }

      auto& socketlist = socket_id_list_get(elist);

      //if (add)
      //{
      //   /*         informationf("AddList);  %5d: %s: %s\n", s, (which_one == e_list_call_on_connect) ? "CallOnConnect" :
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

         //   //INFO(informationf("list_close");
         //}
         //return;
      //}
      // erase
      //ref.erase(s);
      //information() << "/AddList\n");
   }


   void socket_handler::socket_id_list_erase(SOCKET s, enum_list elist)
   {

      if (s == INVALID_SOCKET)
      {
         information() << "AddList:  invalid_socket";
         return;
      }

      auto& socketlist = socket_id_list_get(elist);

         //if (add)
         //{
         //   /*         informationf("AddList);  %5d: %s: %s\n", s, (which_one == e_list_call_on_connect) ? "CallOnConnect" :
         //               (which_one == e_list_detach) ? "detach" :
         //               (which_one == e_list_timeout) ? "time_out" :
         //               (which_one == e_list_retry) ? "Retry" :
         //               (which_one == e_list_close) ? "close" : "<undef>",
         //               add ? "add" : "erase");*/
         //}
         //if (add)
         //{
      socketlist.erase_item(s);
      //if (which_one == e_list_close)
      //{

      //   //INFO(informationf("list_close");
      //}
      //return;
   //}
   // erase
   //ref.erase(s);
   //information() << "/AddList\n");
   }


   void socket_handler::erase_socket(SOCKET s)
   {

      set(s, false, false, false); // erase from fd_set's

      m_socketlistCallOnConnect.erase_item(s);
      m_socketlistDetach.erase_item(s);
      m_socketlistTimeout.erase_item(s);
      m_socketlistRetryClientConnect.erase_item(s);
      m_socketlistClose.erase_item(s);


   }


   i32 socket_handler::TriggerID(::sockets::base_socket * src)
   {

      i32 atom = m_next_trigger_id++;

      m_trigger_src[atom] = src;

      return atom;

   }


   bool socket_handler::Subscribe(i32 atom, ::sockets::base_socket * psocketDst)
   {

      if (m_trigger_src.plookup(atom))
      {

         auto psocketDst2 = __Socket(psocketDst);

         if (m_trigger_dst[atom].plookup(psocketDst2))
         {

            m_trigger_dst[atom][psocketDst2] = true;

            return true;

         }

         psocketDst->information() << "Subscribe " << atom << " Already subscribed";

         return false;
      }

      psocketDst->information() << "Subscribe " << atom << " Trigger atom not found";

      return false;

   }


   bool socket_handler::Unsubscribe(i32 atom, ::sockets::base_socket * psocketDst)
   {

      if (m_trigger_src.plookup(atom))
      {

         auto psocketDst2 = __Socket(psocketDst);

         if (m_trigger_dst[atom].plookup(psocketDst2))
         {

            m_trigger_dst[atom].erase_item(psocketDst2);

            return true;

         }

         psocketDst->information() << "Unsubscribe " << atom << " Not subscribed";

         return false;
      }

      psocketDst->information() << "Unsubscribe " << atom << " Trigger atom not found";

      return false;
      
   }


   void socket_handler::Trigger(i32 atom, socket::trigger_data& data, bool bErase)
   {

      if (m_trigger_src.contains(atom))
      {

         data.SetSource(dynamic_cast < base_socket * > (m_trigger_src[atom].m_p));

         auto & map = m_trigger_dst[atom];

         for(auto & pair : map)
         {

            if (this->Valid(pair.m_pbasesocket))
            {

               pair.m_pbasesocket->OnTrigger(atom, data);

            }

         }

         if (bErase)
         {

            m_trigger_src.erase_item(atom);

            m_trigger_dst.erase_item(atom);

         }

      }
      else
      {

         information() << "Trigger " << atom << " Trigger atom not found";

      }

   }


}




