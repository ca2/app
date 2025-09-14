#include "framework.h"
#include "socket_handler.h"
#include "tcp_socket.h"
#include "networking_bsd/networking.h"
#include "acme/acme.h"
#include "acme/parallelization/synchronous_lock.h"
#include "apex/platform/system.h"
#include "_____debug_counters_001.h"

#include "acme/_operating_system.h"
#if defined(OPENBSD)
#include <signal.h>
#endif

int __is_ok_socket(socket_id fd) {
    struct sockaddr sa{};
    socklen_t len = sizeof(sa);
    if (getsockname(fd, &sa, &len) == 0) {
        return 1; // Valid socket
    } else if (errno == ENOTSOCK) {
        return 0; // Valid FD, but not a socket
    } else {
        return -1; // Invalid FD or other error
    }
}

#include <time.h>

#ifdef __ANDROID__
#undef USE_MISC

#endif


#define THIS_FILE_DEBUG_LEVEL 1


#if defined(__APPLE__) || defined(FREEBSD) || defined(OPENBSD)

#define bcopy(src, dest, len) ::memory_copy(dest, src, len)

#else

#define FD_COPY(pfdsetSrc, pfdsetDst) (*(pfdsetDst)) = (*(pfdsetSrc))

#endif
#include "acme/_finish.h"


namespace sockets_bsd
{

#if COUNTERS_001
   ::interlocked_count g_interlockedcountSocketHandler;
#endif

   //socket_handler::socket_handler(::particle * pparticle, ::apex::log *plogger) :
   socket_handler::socket_handler() :
      //::object(pparticle),
      //base_socket_handler(plogger),
      m_b_use_mutex(false)
//      , m_maxsock(0)
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

      //m_p2 = this;
      defer_create_synchronization();
      zero(m_socks4_host);
      //m_prfds = ___new fd_set();
      //m_pwfds = ___new fd_set();
      //m_pefds = ___new fd_set();
      //FD_ZERO(&m_rfdsSelect);
      //FD_ZERO(&m_wfdsSelect);
      //FD_ZERO(&m_efdsSelect);
      //FD_ZERO(&m_rfdsSelected);
      //FD_ZERO(&m_wfdsSelected);
      //FD_ZERO(&m_efdsSelected);
      //m_countR = 0;
      //m_countW = 0;
      //m_countE = 0;

#if COUNTERS_001

      g_interlockedcountSocketHandler++;

      ::informationf("%s currently allocated count = %lld", typeid(*this).name(), g_interlockedcountSocketHandler.operator long long);

#endif

   }


   socket_handler::~socket_handler()
   {

      cleanup_handler();
#if COUNTERS_001
      g_interlockedcountSocketHandler--;
#endif
   }



   long long socket_handler::increment_reference_count()
   {

      return ::object::increment_reference_count();

   }


   long long socket_handler::decrement_reference_count()
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

         warning() << "socket_handler add " << (int)psocket->GetSocketId() << " socket is already being handled by another handler";

         return;

      }

      if (psocket->GetSocketId() == INVALID_SOCKET)
      {

         warning() <<"add: Invalid socket";

         if (psocket->IsCloseAndDelete())
         {

            m_socketlistDelete.add_tail(psocket);

         }

         return;

      }

      socket_pointer find;

      if (m_socketmapAdd.find((int)psocket->GetSocketId(), find))
      {

         information() << "add: Invalid socket " << (int)psocket->GetSocketId() << " Attempt to add socket already in add queue";

         //m_delete.add_tail(psocket);
         return;

      }

      if (psocket->is_connecting())
      {

         ::pointer < ::sockets_bsd::base_socket > psocketImpl = psocket->base_socket_impl();

         if (psocketImpl->m_timeConnectionMaximum > 0_s)
         {

            socket_id_list_add(psocket->GetSocketId(), e_list_timeout);

         }

      }
      else
      {

         ::pointer < ::sockets_bsd::base_socket > psocketImpl = psocket->base_socket_impl();

         if (psocketImpl->m_timeKeepConnectionAfterLastIO > 0_s)
         {

            socket_id_list_add(psocket->GetSocketId(), e_list_timeout);

         }
         else
         {

            socket_id_list_erase(psocket->GetSocketId(), e_list_timeout);

         }

      }

      if (psocket->IsDetach())
      {

         socket_id_list_add(psocket->GetSocketId(), e_list_detach);

      }

      psocket->SetSocketHandler(this);

      psocket->m_estatus = ::success;

      auto& a = m_socketmapAdd[(int) psocket->GetSocketId()];

       a= psocket;


      auto xxx = m_socketmapAdd[(int) psocket->GetSocketId()];

   }


   void socket_handler::restart_socket(SOCKET socket)
   {

      auto iterator = m_socketmap.find(socket);

      if (iterator->m_psocket->is_connecting())
      {
         
         ::pointer < ::sockets_bsd::base_socket > psocketImpl = iterator->m_psocket;

         if (psocketImpl->m_timeConnectionMaximum > 0_s)
         {

            socket_id_list_add(iterator->m_psocket->GetSocketId(), e_list_timeout);

         }

      }
      else
      {

         ::pointer < ::sockets_bsd::base_socket > psocketImpl = iterator->m_psocket;

         if (psocketImpl->m_timeKeepConnectionAfterLastIO > 0_s)
         {

            ::pointer < ::sockets_bsd::base_socket > psocket2 = iterator->m_psocket;

            socket_id_list_add(psocket2->GetSocketId(), e_list_timeout);

         }

      }

      iterator->m_psocket->m_estatus = ::success;

      m_socketmapAdd[iterator->element1()] = iterator->element2();

      auto xxx = m_socketmapAdd[iterator->element1()];

   }


   //void socket_handler::get(SOCKET s, bool& r, bool& w, bool& e)
   //{

   //   if (s >= 0)
   //   {

   //      r = FD_ISSET(s, &m_rfds) ? true : false;

   //      w = FD_ISSET(s, &m_wfds) ? true : false;

   //      e = FD_ISSET(s, &m_efds) ? true : false;

   //   }

   //}


   //void socket_handler::_get(SOCKET s, int& r, int& w, int& e)
   //{

   //   if (s >= 0)
   //   {

   //      if (FD_ISSET(s, &m_rfds))
   //      {

   //         r++;

   //      }

   //      if (FD_ISSET(s, &m_wfds))
   //      {

   //         w++;

   //      }

   //      if (FD_ISSET(s, &m_efds))
   //      {

   //         e++;

   //      }

   //   }

   //}


   //void socket_handler::get(int& r, int& w, int& e)
   //{

   //   r = 0;
   //   w = 0;
   //   e = 0;

   //   for (auto& s : m_socketlist)
   //   {

   //      _get(s, r, w, e);

   //   }

   //}


   //void socket_handler::set(SOCKET s, bool bRead, bool bWrite, bool bException)
   //{

   //   if (s >= 0)
   //   {

   //      if (bRead)
   //      {

   //         if (!FD_ISSET(s, &m_rfds))
   //         {

   //            FD_SET(s, &m_rfds);

   //            //m_countR++;

   //         }

   //      }
   //      else
   //      {

   //         if (FD_ISSET(s, &m_rfds))
   //         {

   //            FD_CLR(s, &m_rfds);

   //            //m_countR--;

   //         }

   //      }

   //      if (bWrite)
   //      {

   //         if (!FD_ISSET(s, &m_wfds))
   //         {

   //            FD_SET(s, &m_wfds);

   //            //m_countW++;

   //         }

   //      }
   //      else
   //      {

   //         if (FD_ISSET(s, &m_wfds))
   //         {

   //            FD_CLR(s, &m_wfds);

   //            //m_countW--;

   //         }

   //      }

   //      if (bException)
   //      {

   //         if (!FD_ISSET(s, &m_efds))
   //         {

   //            FD_SET(s, &m_efds);

   //            //m_countE++;

   //         }

   //      }
   //      else
   //      {

   //         if (FD_ISSET(s, &m_efds))
   //         {

   //            FD_CLR(s, &m_efds);

   //            //m_countE--;

   //         }

   //      }

   //   }

   //}


   int socket_handler::select(int lSeconds, int lMicroseconds)
   {

      struct timeval timeval;

      timeval.tv_sec = lSeconds;

      timeval.tv_usec = lMicroseconds;

      return _select(&timeval);

   }


   int socket_handler::select()
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


   int socket_handler::select(const class time & timeWait)
   {

      struct timeval tsel;

      tsel.tv_sec = (long)timeWait.integral_second();

      tsel.tv_usec = ((long)timeWait.integral_microsecond()) % 1'000'000;

      return _select(&tsel);

   }


   bool socket_handler::contains_socket_id(socket_id socketid)
   {

      return m_socketmap.find(socketid);

   }


   bool socket_handler::contains(::sockets::base_socket * pbasesocket)
   {

      socket_pointer psocket = pbasesocket;

      if (::generic::map_base::contains_payload(m_socketmap, psocket))
      {

         return true;

      }

      if (::generic::map_base::contains_payload(m_socketmapAdd, psocket))
      {

         return true;

      }

      if (m_socketlistDelete.contains(psocket))
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

            if (!m_socketmap.find(socket, psocket)) // not found
            {

               warning() <<"socket_handler " << (int)socket << " Did not find expected socket using file descriptor(4)";

               socket_id_list_erase(psocket->GetSocketId(), e_list_call_on_connect);

            }

            if (psocket != nullptr)
            {

               ::cast < sockets::tcp_socket > ptcpsocket = psocket;

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

                     socket_id_list_erase(psocket->GetSocketId(), e_list_call_on_connect);

                  }

               }

            }

         }

         return true;

      }

      return false;

   }


   int socket_handler::_select(struct timeval *tsel)
   {

      fd_set rfds{};
      fd_set wfds{};
      fd_set efds{};
      
      SOCKET maxsock{};

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

            warning() <<"Select " << (int)m_socketmap.get_size() << " FD_SETSIZE reached";

            goto end_processing_adding;

         }

         SOCKET socket = passociationAdd->m_socketid;

         auto psocket = passociationAdd->m_psocket;

         if (m_socketmap.has(socket))
         {

            psocket->warning() << "add" << (int)psocket->GetSocketId() << "Attempt to add socket already in controlled queue";

            m_socketmapAdd.erase(passociationAdd);

            goto start_processing_adding;

         }

         if (psocket->IsCloseAndDelete())
         {

            psocket->warning() << "add " << (int)psocket->GetSocketId() << " Trying to add socket with SetCloseAndDelete() true";

            m_socketlist.add_tail(socket);

            m_socketmap[passociationAdd->element1()] = passociationAdd->element2();

            socket_id_list_add(socket, e_list_close);

            goto start_processing_adding;

         }

         ::cast < ::sockets::stream_socket > pstreamsocket = psocket;

         if (pstreamsocket && pstreamsocket->is_connecting()) // 'open' called before adding socket
         {

            psocket->set(true, true);

         }
         else
         {

            ::cast < ::sockets::tcp_socket > ptcpsocket = psocket;

            bool bWrite = ::is_set(ptcpsocket) ? ptcpsocket->GetOutputLength() != 0 || ptcpsocket->CallOnConnect() : false;

            bool bRead = ::is_set(ptcpsocket) ? !ptcpsocket->IsDisableRead() : true;

            psocket->set(bRead, bWrite);

         }

         //m_maxsock = (socket + 1 > m_maxsock) ? socket + 1 : m_maxsock;

         // only add to m_socketlist (process fd_set happenings) if
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

         m_socketmapAdd.erase(socket);

         if (m_bSlave && psocket->IsDetach())
         {

            psocket->OnDetached();

         }

         goto start_processing_adding;

      }

end_processing_adding:

      //fd_set rfds;
      //fd_set wfds;
      //fd_set efds;

      int countR = 0;
      int countW = 0;
      int countE = 0;

      //get(countR, countW, countE);

      //FD_COPY(&m_rfdsSelect, &m_rfdsSelected);
      //FD_COPY(&m_wfdsSelect, &m_wfdsSelected);
      //FD_COPY(&m_efdsSelect, &m_efdsSelected);
      
      FD_ZERO(&rfds);
      FD_ZERO(&wfds);
      FD_ZERO(&efds);
      maxsock = 0;

      for (auto& pair : m_socketmap)
      {

         auto socketid = pair.m_socketid;

         ::pointer < ::sockets_bsd::base_socket > psocketImpl = pair.m_psocket->base_socket_impl();

         if (psocketImpl)
         {
            
            if(__is_ok_socket(socketid))
            {
               
#if THIS_FILE_DEBUG_LEVEL >= 9
            
               printf_line("socket_handler socket %d is OK!!", socketid);
            
#endif
               
            }
            else
            {
               
#if THIS_FILE_DEBUG_LEVEL >= 9
            
               printf_line("socket_handler socket %d is BAD!!", socketid);
            
#endif

               continue;
               
            }

            if (psocketImpl->m_iSelectRead)
            {

               FD_SET(socketid, &rfds);
               
#if THIS_FILE_DEBUG_LEVEL >= 9
            
               printf_line("socket_handler FD_SET READ %d", socketid);
            
#endif

               countR++;

            }

            if (psocketImpl->m_iSelectWrite)
            {

               FD_SET(socketid, &wfds);

#if THIS_FILE_DEBUG_LEVEL >= 9
            
               printf_line("socket_handler FD_SET WRITE %d", socketid);
            
#endif

               countW++;

            }
               
            if(psocketImpl->m_iSelectError)
            {
             
#if THIS_FILE_DEBUG_LEVEL >= 9
            
               printf_line("socket_handler FD_SET ERROR %d", socketid);
            
#endif

               FD_SET(socketid, &efds);

               countE++;

            }
            
            if (psocketImpl->m_iSelectRead
            || psocketImpl->m_iSelectWrite
            || psocketImpl->m_iSelectError)
            {
              
              maxsock = maximum(maxsock, socketid); 
               
            }

         }

      }


      fd_set * prfds = countR > 0 ? &rfds : nullptr;
      fd_set * pwfds = countW > 0 ? &wfds : nullptr;
      fd_set * pefds = countE > 0 ? &efds : nullptr;

      int n = 0;

      tick1 = ::time::now();

      class ::time tickRWENull;

      //if (psetR == nullptr && psetW == nullptr && psetE == nullptr)
      if (countR <= 0 && countW <= 0 && countE <= 0)
      {

         tickRWENull.Now();
         
#if THIS_FILE_DEBUG_LEVEL >= 9

         printf_line("Each rfds, wfds and efds are empty!!");
         
#endif

      }
      else
      {

         //debug_print(" m_socketmap : %d\n", m_socketmap.size());
         //debug_print(" m_socketmapAdd     : %d\n", m_socketmapAdd.size());
         //debug_print(" m_delete  : %d\n", m_delete.size());
         
         timeval timevalSelect{};
         
         timevalSelect.tv_sec = tsel->tv_sec;
         timevalSelect.tv_usec = tsel->tv_usec;

         if (m_b_use_mutex)
         {

            synchronization()->unlock();
            
#if THIS_FILE_DEBUG_LEVEL > 6
            
            printf_line("socket_handler(mutex) select max_sock : %d", maxsock);
            
#endif

            //n = ::select((int)m_maxsock, psetR, psetW, psetE, tsel);
            
#if defined(OPENBSD)

            auto nfds = maximum(countR, maximum(countW, countE));

            n = ::select(nfds, prfds, pwfds, pefds, &timevalSelect);
            
#else
            
            n = ::select((int)maxsock + 1, prfds, pwfds, pefds, &timevalSelect);
            
#endif

            m_iSelectErrno = networking_last_error();

            synchronization()->lock();

         }
         else
         {
            
#if THIS_FILE_DEBUG_LEVEL > 6
            
            printf_line("socket_handler select time : %ds %dus", timevalSelect.tv_sec, timevalSelect.tv_usec);
            printf_line("socket_handler select psetR : 0x%016llX %% 8 = %d", prfds, ((::uptr) prfds) % 8);
            printf_line("socket_handler select psetW : 0x%016llX %% 8 = %d", pwfds, ((::uptr) pwfds) % 8);
            printf_line("socket_handler select psetE : 0x%016llX %% 8 = %d", pefds, ((::uptr) pefds) % 8);
            printf_line("socket_handler select thread %s(%d)", ::task_get_name().c_str(), ::current_task_index());
            
#endif

            //n = ::select((int)m_maxsock, psetR, psetW, psetE, tsel);
            
#if defined(OPENBSD)

            //auto nfds = maximum(countR, maximum(countW, countE));
            
            auto nfds = maxsock + 1;

            printf_line("socket_handler select nfds : %d", nfds);
            
            //n = ::select(nfds, prfds, pwfds, pefds, &timevalSelect);
            
            timespec timespec{};
            
            timespec.tv_sec = timevalSelect.tv_sec;
            
            timespec.tv_nsec = timevalSelect.tv_usec * 1'000;
            
            sigset_t sigset;
            
            sigemptyset(&sigset);
            
            n = ::pselect(nfds, prfds, pwfds, pefds, &timespec, &sigset);
            
#else

            printf_line("socket_handler select maxsock + 1 : %d", (int)maxsock + 1);
            
            n = ::select((int)maxsock + 1, prfds, pwfds, pefds, &timevalSelect);
            
#endif

#if THIS_FILE_DEBUG_LEVEL > 6
            
            printf_line("socket_handler select result n : %d", n);
            
#endif

            //if (m_iMaxKeepAliveCount > 0)
            //{

            //   output_debug_string("m_iMaxKeepAliveCount > 0");

            //}

            m_iSelectErrno = networking_last_error();

         }

      }

      tick2 = ::time::now();

      if (n < 0)
      {
         
         printf_line("::networking_bsd::socket_handler::_select n < 0");

         auto tickNow = ::time::now();

         /*
            EBADF  An invalid file descriptor was given in one of the sets.
            EINTR  A non blocked signal was caught.
            EINVAL n is negative. Or struct timeval contains bad time values (<0).
            ENOMEM select was unable to allocate memory for internal tables.
         */

         //if (m_iMaxKeepAliveCount > 0)
         //{

         //   output_debug_string("m_iMaxKeepAliveCount > 0");

         //}

//         if (m_maxsock > 0 && (m_iSelectErrno != m_iPreviousError || tickNow - m_timeLastError > 5_s))
         if (maxsock > 0 && (m_iSelectErrno != m_iPreviousError || tickNow - m_timeLastError > 5_s))
         {

            information() << "select" << m_iSelectErrno << ", " << bsd_socket_error(m_iSelectErrno);

            int iError = m_iSelectErrno;

//#if defined(LINUX) || defined(MACOS)

  //          information() << "m_maxsock: " << m_maxsock;
            information() << "networking_bsd::socket_handler select error : "<< networking()->last_error_message(networking()->last_error()) <<" ("<< networking()->last_error() <<")";

// #elif defined(WINDOWS)
//
//             information() << "networking_bsd::socket_handler select error : "<< ::windows::last_error_message(iError) <<" ("<< iError <<")";
//
// #endif
//
// #if defined(LINUX) || defined(MACOS)
//
//             information() << "m_maxsock: " << m_maxsock;
//             information() << "networking_bsd::socket_handler select error : "<< strerror(networking_last_error()) <<" ("<< networking_last_error() <<")";
//
// #elif defined(WINDOWS)
//
//             information() << "networking_bsd::socket_handler select error : "<< ::windows::last_error_message(iError) <<" ("<< iError <<")";
//
// #endif

            if (iError == 10022)
            {

               information() << "WSEINVAL - An invalid argument was supplied";

            }

            //// test bad fd
            //for (SOCKET socket = 0; socket < m_maxsock; socket++)
            //{

            //   bool bAnySet = false;

            //   if (FD_ISSET(socket, &m_rfdsSelected))
            //   {

            //      bAnySet = true;

            //   }

            //   if (FD_ISSET(socket, &m_wfdsSelected))
            //   {

            //      bAnySet = true;

            //   }

            //   if (FD_ISSET(socket, &m_efdsSelected))
            //   {
 
            //      bAnySet = true;

            //   }

            //   if (bAnySet)
            //   {

            //      auto iteratorSocket = m_socketmap.find(socket);

            //      if (::is_set(iteratorSocket) && ::is_set(iteratorSocket->m_psocket))
            //      {

            //         information() << "Bad fd in fd_set: " << socket;

            //         information() << "Deleting and removing socket: " << socket;

            //         iteratorSocket->m_psocket->SetCloseAndDelete();

            //      }

            //   }

            //}

         }

         /// \no more todo rebuild fd_set's from active networking_bsd list_base (m_socketmap) here
         /// done : http://jbmon.googlecode.com/svn/trunk/networking_bsd/SocketHandler.cpp : rebuild fd_set's from active networking_bsd list_base (m_socketmap) here
         {

            //FD_ZERO(&rfds);
            //FD_ZERO(&wfds);
            //FD_ZERO(&efds);

            //::collection::count countR = 0;
            //::collection::count countW = 0;
            //::collection::count countE = 0;

            auto p = m_socketmap.begin();

            for(; p.is_ok(); p++)
            {

               try
               {

                  if (p->m_socketid == p->m_psocket->GetSocketId())
                  {

                     fd_set fds;

                     FD_ZERO(&fds);

                     FD_SET(p->m_socketid, &fds);

                     struct timeval tv;

                     tv.tv_sec = 1;

                     tv.tv_usec = 0;

                     int n = ::select((int)(p->m_socketid + 1), &fds, nullptr, nullptr, &tv);

                     if (n == -1)
                     {

                        // %! bad fd, erase

                        p->m_psocket->error() << " Select " << (int)p->m_socketid << "Bad fd in fd_set (2)"; // ->error() << LOG_LEVEL_ERROR);

                        m_socketlistErase.add(p->m_socketid);

                     }
                     //else
                     //{

                     //   bool bAnySet = false;

                     //   if (FD_ISSET(p->m_socketid, &m_rfdsSelect))
                     //   {

                     //      //FD_SET(p->m_socketid, &rfds);

                     //      //countR++;

                     //      bAnySet = true;

                     //   }

                     //   if (FD_ISSET(p->m_socketid, &m_wfdsSelect))
                     //   {

                     //      //FD_SET(p->m_socketid, &wfds);

                     //      //countW++;

                     //      bAnySet = true;

                     //   }

                     //   if (FD_ISSET(p->m_socketid, &m_efdsSelect))
                     //   {

                     //      //FD_SET(p->m_socketid, &efds);

                     //      //countE++;

                     //      bAnySet = true;

                     //   }

                     //   if (!bAnySet)
                     //   {

                     //      // %! none set

                     //      p->m_psocket->error() << "Select " << (int)p->m_socketid << " No fd in fd_set"; // ->error() << LOG_LEVEL_ERROR);

                     //      m_socketlistErase.add(p->m_socketid);

                     //   }

                     //}

                  }
                  else
                  {

                     // %! mismatch

                     p->m_psocket->error() << "Select" << (int)p->m_socketid << "Bad fd in fd_set (3)"; // ->error() << LOG_LEVEL_ERROR);

                     m_socketlistErase.add(p->m_socketid);

                  }

               }
               catch (...)
               {

                  // general error

                  p->m_psocket->error() << "Select" << (int)p->m_socketid << "Bad fd in fd_set (3)"; // ->error() << LOG_LEVEL_ERROR);

                  m_socketlistErase.add(p->m_socketid);

               }

            }

            //m_rfds = rfds;
            //m_wfds = wfds;
            //m_efds = efds;

            //m_countR = countR;
            //m_countW = countW;
            //m_countE = countE;

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
         
#if THIS_FILE_DEBUG_LEVEL > 6
         
         printf("socket_handler select n (%d) > 0", n);
         
#endif

         auto p = m_socketlist.begin();

         for (; p.is_ok() && n; p++)
         {
            
            SOCKET socket = *p;

            if (FD_ISSET(socket, &rfds))
            {
               
               auto iteratorSocket = m_socketmap.find(socket);

               //if (m_iMaxKeepAliveCount > 0)
               //{

               //   output_debug_string("m_iMaxKeepAliveCount > 0");

               //}

               if (::is_set(iteratorSocket) && ::is_set(iteratorSocket->m_psocket)) // found
               {

                  //if (iteratorSocket->m_psocket->m_iKeepAliveCount > 0)
                  //{

                  //   output_debug_string("iteratorSocket->m_psocket->m_iKeepAliveCount > 0");

                  //}

                  //if (iteratorSocket->m_psocket->base_socket_composite() && iteratorSocket->m_psocket->base_socket_composite()->m_iKeepAliveCount > 0)
                  //{

                  //   output_debug_string("iteratorSocket->m_psocket->base_socket_composite()->m_iKeepAliveCount > 0");

                  //}

                  // ___new SSL negotiate method
                  if (iteratorSocket->m_psocket->IsSSLNegotiate())
                  {

                     //iteratorSocket->m_psocket->information() << "SSLNegotiate";
                     
                     iteratorSocket->m_psocket->SSLNegotiate();

                  }
                  else
                  {

                     //iteratorSocket->m_psocket->information() << "OnRead";
                     
                     iteratorSocket->m_psocket->OnRead();

                  }

                  if (iteratorSocket->m_psocket->m_iKeepAliveCount > 0)
                  {

                     //output_debug_string("iteratorSocket->m_psocket->m_iKeepAliveCount > 0");

                     m_iMaxKeepAliveCount = maximum(m_iMaxKeepAliveCount, iteratorSocket->m_psocket->m_iKeepAliveCount);

                  }

                  if (iteratorSocket->m_psocket && iteratorSocket->m_psocket->m_iKeepAliveCount > 0)
                  {

                     //output_debug_string("iteratorSocket->m_psocket->base_socket_composite()->m_iKeepAliveCount > 0");

                     m_iMaxKeepAliveCount = maximum(m_iMaxKeepAliveCount, iteratorSocket->m_psocket->m_iKeepAliveCount);

                  }

               }
               else
               {

                  warning() << "socket_handler " << (int)socket << "Did not find expected socket using file descriptor(1)";

               }

               n--;

            }

            if (FD_ISSET(socket, &wfds))
            {
               
               auto iteratorSocket = m_socketmap.find(socket);

               if (::is_set(iteratorSocket) && ::is_set(iteratorSocket->m_psocket)) // found
               {

                  // ___new SSL negotiate method
                  if (iteratorSocket->m_psocket->IsSSLNegotiate())
                  {

                     //iteratorSocket->m_psocket->information() << "SSLNegotiate";

                     iteratorSocket->m_psocket->SSLNegotiate();

                  }
                  else
                  {

                     iteratorSocket->m_psocket->information() << "OnWrite";

                     iteratorSocket->m_psocket->OnWrite();

                  }

               }
               else
               {

                  warning() << "socket_handler " << (int)socket << " Did not find expected socket using file descriptor(2)";

               }

               n--;

            }

            if (FD_ISSET(socket, &efds))
            {

               auto iteratorSocket = m_socketmap.find(socket);

               if (::is_set(iteratorSocket) && ::is_set(iteratorSocket->m_psocket)) // found
               {
                  
                  // Out-Of-Band data
                  // recv with MSG_OOB
                  //posix_time tnow = time(nullptr);

                  if (iteratorSocket->m_psocket->has_timed_out())
                  {
                  
                     if (iteratorSocket->m_psocket->is_connecting())
                     {

                        warning() << "socket_handler " << (int)socket << " stream_socket on_connection_timeout (3)";

                        iteratorSocket->m_psocket->on_connection_timeout();

                     }
                     else
                     {

                        warning() << "socket_handler " << (int)socket << " socket on_timeout(3)";

                        iteratorSocket->m_psocket->on_timeout();

                     }

                  }
                  else
                  {

                     iteratorSocket->m_psocket->OnException();

                  }

               }
               else
               {

                  warning() << "socket_handler " << (int)socket << " Did not find expected socket using file descripto(3)r";

               }

               n--;

            }

         } // m_socketlist loop

         m_iPreviousError = -1;

      } // if (n > 0)

      call_on_connect();

      bool check_max_fd = false;

      // check detach of socket if master handler - EVENT
      if (!m_bSlave && m_socketlistDetach.has_element())
      //if(m_socketlistDetach.has_element())
      {

         auto it = m_socketlistDetach.begin();

         //SOCKET socket = 0;

         while(m_socketlistDetach.is_iterator_ok(it))
         {

            auto socket = *it;

            it++;
            
            auto iteratorSocket = m_socketmap.find(socket);

            if (::is_set(iteratorSocket) && ::is_set(iteratorSocket->m_psocket))
            {

               auto psocket = iteratorSocket->m_psocket;

               if (psocket->IsDetach() && !psocket->IsDetached())
               {

                  erase_socket(socket);

                  m_socketmap.erase(socket);

                  // After DetachSocket(), all calls to socket_handler() will return a object
                  // to the ___new slave socket_handler running in the ___new thread.
                  try
                  {

                     psocket->DetachSocket();

                  }
                  catch (...)
                  {

                  }

                  check_max_fd = true;

               }

            }

         }

      }

      // check is_connecting - connection timeout - conditional happening
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

               auto iteratorSocket = m_socketmap.find(socket);

               if (iteratorSocket.is_null() || ::is_null(iteratorSocket->m_psocket)) // not found
               {

                  iteratorSocket = m_socketmapAdd.find(socket);

                  if (iteratorSocket.is_null() || ::is_null(iteratorSocket->m_psocket))
                  {

                     warning() << "socket_handler " << (int)socket << " Did not find expected socket using file descriptor(f)";

                     m_socketlistTimeout.erase(socket);

                     goto restartSocketListTimeout;

                  }

                  continue;

               }
               
               if (iteratorSocket.is_ok() && ::is_set(iteratorSocket->m_psocket))
               {

                  if (iteratorSocket->m_psocket->has_timed_out())
                  {

                     if (iteratorSocket->m_psocket->is_connecting())
                     {

                        warning() << "socket_handler " << (int)socket << " stream_socket on_connection_timeout (g)";

                        iteratorSocket->m_psocket->on_connection_timeout();

                     }
                     else
                     {

                        warning() << "socket_handler " << (int)socket << " socket on_timeout (g)";

                        iteratorSocket->m_psocket->on_timeout();

                     }

                     iteratorSocket->m_psocket->SetCloseAndDelete();

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

            auto iteratorSocket = m_socketmap.find(*p);

            if (iteratorSocket.is_null() || ::is_null(iteratorSocket->m_psocket))
            {

               warning() << "socket_handler " << (int)*p << " Did not find expected socket using file descriptor(g)";

            }

            if (iteratorSocket.is_ok() && ::is_set(iteratorSocket->m_psocket))
            {

               ::cast < ::sockets::tcp_socket > ptcpsocket = iteratorSocket->m_psocket;

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

                     m_socketmap[ptcpsocket->GetSocketId()] = ptcpsocket.m_p;

                     m_socketlistErase.add_tail(nn);

                  }

               }

            }

         }

      }

      // check close and delete - conditional happening
      if (m_socketlistClose.get_size() > 0)
      {

         socket_id_list socketlist = m_socketlistClose;

         auto psocketlist = socketlist.begin();

         for(; psocketlist.is_ok(); psocketlist++)
         {

            SOCKET socket = *psocketlist;

            socket_map* psocketmap = nullptr;

            auto iteratorSocket = m_socketmap.find(socket);

            if (iteratorSocket.is_null() || ::is_null(iteratorSocket->m_psocket)) // not found
            {

               iteratorSocket = m_socketmapAdd.find(socket);

               if (iteratorSocket.is_null() || ::is_null(iteratorSocket->m_psocket))
               {

                  warning() << "socket_handler " << (int)socket << " Did not find expected socket using file descriptor(8)";

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

            if (iteratorSocket.is_ok() && ::is_set(iteratorSocket->m_psocket))
            {

               auto psocket = iteratorSocket->m_psocket;

               if (psocket->IsCloseAndDelete())
               {

                  auto ptcpsocket = psocket.cast < ::sockets::tcp_socket >();

                  // ___new graceful ptcpsocket - flush and close timeout 5s
                  if (::is_set(ptcpsocket) && psocket->IsConnected() && ptcpsocket->GetFlushBeforeClose() &&
                        !ptcpsocket->IsSSL() && psocket->TimeSinceClose().m_iSecond < 5)
                  {

                     //information() << " close(1)\n");
                     if (ptcpsocket->GetOutputLength())
                     {

                        ptcpsocket->information() << "Closing " << (int)ptcpsocket->GetOutputLength() << " Sending all data before closing";

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

                     ptcpsocket->close(); // dispose of old file descriptor (open creates a ___new)

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

                     m_socketlistErase.add_tail((::socket_id &&) ptcpsocket->GetSocketId());

                  }
                  else
                  {

                     //informationf(" close(3) fd %d GetSocket() %d\n", socket, int_point -> GetSocket()));

                     if (psocket && psocket->IsConnected() && ptcpsocket->GetOutputLength())
                     {

                        psocket->warning() << "Closing " << (int)ptcpsocket->GetOutputLength() << " Closing socket while data still left to send";

                     }

                     if (psocket->Retain() && !psocket->Lost())
                     {

                        auto psystem = system();

                        synchronous_lock synchronouslock(__SystemNetworking(psystem)->m_pmutexPool, DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

                        auto ppoolsocket = øallocate pool_socket(psocket);

                        ppoolsocket->m_psockethandler = this;

                        ppoolsocket->SetDeleteByHandler();

                        auto pnetworking2 = __SystemNetworking(psystem);

                        pnetworking2->m_pool.set_at(ppoolsocket->m_socketid, ppoolsocket);

                        ppoolsocket->SetCloseAndDelete(false); // added - erase from m_socketlistClose

                        //int_point -> SetCloseAndDelete(false); // added - erase from m_socketlistClose

                     }
                     //else if (psocket.cast < http_session >() != nullptr && !psocket->Lost())
                     //{

                     //   psocket->SetCloseAndDelete(false);

                     //   continue;

                     //}
                     else if(psocket->GetSocketId() != INVALID_SOCKET)
                     {

                        psocket->set(false, false, false);

                        //information() << "close() before OnDelete\n");

                        psocket->close();

                     }

                     //psocket->OnDelete();

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

         auto p = m_socketmap.find(socket);

         if (::is_set(p) && ::is_set(p->m_psocket))
         {

            auto psocket = p->m_psocket;

            psocket->SetSocketHandler(nullptr);

            //iteratorSocket->m_psocket->m_phandlerSlave.release();

            m_socketmap.erase(p);

            m_socketlistDelete.add_tail(psocket);

            m_socketmapAdd.erase(socket);

         }

         check_max_fd = true;

      }

//      // calculate maximum file descriptor for select() call
//      if (check_max_fd)
//      {
//
//         m_maxsock = m_socketlist.maximum(0) + 1;
//
//      }

      // erase add's that fizzed
      while (m_socketlistDelete.has_element())
      {

         //bool bReallyHasElementLetsCheck = m_socketlistDelete.has_element();

         auto psocket = ::transfer(m_socketlistDelete.pick_head());

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

                     auto pdst = m_trigger_dst[p->m_socketid].begin();

                     for(;pdst.is_ok(); pdst++)
                     {

                        if (Valid(pdst->m_pbasesocket))
                        {

                           pdst->m_pbasesocket->OnCancelled(p->m_socketid);

                        }

                     }

                     m_trigger_src.erase(p->m_socketid);

                     m_trigger_dst.erase(p->m_socketid);

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
//      return m_resolve_q.find(p0) != nullptr;
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


   ::collection::count socket_handler::get_count()
   {
      /*
      debug_print(" m_socketmap : %d\n", m_socketmap.size());
      debug_print(" m_socketmapAdd     : %d\n", m_socketmapAdd.size());
      debug_print(" m_delete  : %d\n", m_delete.size());
      */

      ::collection::count iSockets = m_socketmap.get_size();

      ::collection::count iAdd = m_socketmapAdd.get_size();

      ::collection::count iDelete = m_socketlistDelete.get_size();

      return iSockets + iAdd + iDelete;

   }


   //void socket_handler::SetSocks4Host(in_addr a)
   //{
   //   m_socks4_host = a;
   //}


   void socket_handler::SetSocks4Host(const ::scoped_string & scopedstrHost)
   {

      m_socks4_host = scopedstrHost;
      //auto paddressdepartment = ::networking::address_department();

      //paddressdepartment->convert(m_socks4_host, host);

   }


   void socket_handler::SetSocks4Port(::networking::port_t port)
   {
      m_socks4_port = port;
   }


   void socket_handler::SetSocks4Userid(const ::scoped_string & scopedstrUserId)
   {

      m_socks4_userid = scopedstrUserId;

   }


//   int socket_handler::Resolve(base_socket * pbasesocket, const ::scoped_string & scopedstrHost, port_t port)
//   {
//
//      // check cache
//
//      ::pointer<resolv_socket>presolvsocket = øallocate resolv_socket(pbasesocket, host, port);
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
//      informationf(" *** Resolve '%s:%d' atom#%d  m_resolve_q int_size: %d  base_socket: %p\n", host.c_str(), port, presolvsocket->GetId(), m_resolve_q.get_size(), pbasesocket));
//
//      return presolvsocket->GetId();
//
//   }


//   int socket_handler::Resolve6(base_socket * pbasesocket, const ::scoped_string & scopedstrHost, port_t port)
//   {
//
//      // check cache
//
//      ::pointer<resolv_socket>resolv = øallocate resolv_socket(pbasesocket, host, port, true);
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


//   int socket_handler::Resolve(base_socket * pbasesocket, in_addr a)
//   {
//
//      // check cache
//
//      ::pointer<resolv_socket>resolv = øallocate resolv_socket(pbasesocket, a);
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


//   int socket_handler::Resolve(base_socket * pbasesocket, in6_addr& a)
//   {
//
//      // check cache
//
//      ::pointer<resolv_socket>resolv = øallocate resolv_socket(pbasesocket, a);
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
//         auto presolvserver = øallocate resolv_server();
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


   ::pointer<base_socket_handler::pool_socket>socket_handler::FindConnection(int type, const string & protocol, ::networking::address * ad)
   {

      auto pnetworking2 = __SystemNetworking(system());

      synchronous_lock synchronouslock(pnetworking2->m_pmutexPool, DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

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

               pnetworking2->m_pool.erase(p->m_socketid);

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

      if(m_socketmap.erase_first_payload(psocketRemove))
      {

         psocketRemove->warning() << "erase -1 socket destructor called while still in use";

         return;

      }

      if (m_socketmapAdd.erase_first_payload(psocketRemove))
      {

         psocketRemove->warning() << "erase -2 socket destructor called while still in use";

         return;

      }

      if (m_socketlistDelete.erase(psocketRemove))
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


   void socket_handler::CheckList(socket_id_list & list_base, const string & listname)
   {

      auto p = list_base.begin();

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
      //               (which_one == aaa_e_list_detach) ? "detach" :
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
         //               (which_one == aaa_e_list_detach) ? "detach" :
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

      //set(s, false, false, false); // erase from fd_set's

      int iSocketList = 0;
      auto psocketlistCallOnConnect = &m_socketlistCallOnConnect;
      psocketlistCallOnConnect->erase(s);

      iSocketList = 1;
      auto psocketlistDetach = &m_socketlistDetach;
      psocketlistDetach->erase(s);

      iSocketList = 2;
      auto psocketlistTimeout = &m_socketlistTimeout;
      psocketlistTimeout->erase(s);

      iSocketList = 3;
      auto psocketlistRetryClientConnect = &m_socketlistRetryClientConnect;
      psocketlistRetryClientConnect->erase(s);

      iSocketList = 4;
      auto psocketlistClose = &m_socketlistClose;
      psocketlistClose->erase(s);

   }


   int socket_handler::TriggerID(::sockets::base_socket * src)
   {

      int atom = m_next_trigger_id++;

      m_trigger_src[atom] = src;

      return atom;

   }


   bool socket_handler::Subscribe(int atom, ::sockets::base_socket * psocketDst)
   {

      if (m_trigger_src.find(atom))
      {

         ::pointer < ::sockets_bsd::base_socket > psocketDst2 = psocketDst;

         if (m_trigger_dst[atom].find(psocketDst2))
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


   bool socket_handler::Unsubscribe(int atom, ::sockets::base_socket * psocketDst)
   {

      if (m_trigger_src.find(atom))
      {

         ::pointer < ::sockets_bsd::base_socket > psocketDst2 = psocketDst;

         if (m_trigger_dst[atom].find(psocketDst2))
         {

            m_trigger_dst[atom].erase(psocketDst2);

            return true;

         }

         psocketDst->information() << "Unsubscribe " << atom << " Not subscribed";

         return false;
      }

      psocketDst->information() << "Unsubscribe " << atom << " Trigger atom not found";

      return false;
      
   }


   void socket_handler::Trigger(int atom, socket::trigger_data& data, bool bErase)
   {

      if (m_trigger_src.contains(atom))
      {

         data.SetSource(dynamic_cast < base_socket * > (m_trigger_src[atom].m_p));

         auto & map_base = m_trigger_dst[atom];

         for(auto & pair : map_base)
         {

            if (this->Valid(pair.m_pbasesocket))
            {

               pair.m_pbasesocket->OnTrigger(atom, data);

            }

         }

         if (bErase)
         {

            m_trigger_src.erase(atom);

            m_trigger_dst.erase(atom);

         }

      }
      else
      {

         information() << "Trigger " << atom << " Trigger atom not found";

      }

   }


}




