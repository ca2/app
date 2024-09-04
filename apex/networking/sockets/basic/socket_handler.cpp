#include "framework.h"
#include "socket_handler.h"
#include "tcp_socket.h"
#include "acme/exception/interface_only.h"
#include "apex/networking/networking.h"

//#include <time.h>
//
//#ifdef ANDROID
//#undef USE_MISC
//
//#endif
//
//#if defined(__APPLE__) || defined(FREEBSD) || defined(OPENBSD)
//
//#define bcopy(src, dest, len) ::memory_copy(dest, src, len)
//
//#else
//
//#define FD_COPY(pfdsetSrc, pfdsetDst) (*(pfdsetDst)) = (*(pfdsetSrc))
//
//#endif


namespace sockets
{


   ::interlocked_count g_interlockedcountSocketHandler;


   //socket_handler::socket_handler(::particle * pparticle, ::apex::log *plogger) :
   socket_handler::socket_handler() :
      //::object(pparticle),
      //base_socket_handler(plogger),
      m_b_use_mutex(false)
      //, m_maxsock(0)
      , m_iPreviousError(-1)
      //,m_errcnt(0)
      , m_tlast({ posix_time_t{}, 0 })
      //, m_socks4_port(0)
      , m_bTryDirect(false)
      //, m_resolv_id(0)
      //, m_bEnablePool(false)
      , m_next_trigger_id(0)
      //, m_slave(false)
   {
      m_p2 = nullptr;
      defer_create_synchronization();
      //zero(m_socks4_host);
      //m_prfds = new fd_set();
      //m_pwfds = new fd_set();
      //m_pefds = new fd_set();
      //FD_ZERO(&m_rfds);
      //FD_ZERO(&m_wfds);
      //FD_ZERO(&m_efds);
      //m_countR = 0;
      //m_countW = 0;
      //m_countE = 0;

      auto iSocketHandler = g_interlockedcountSocketHandler++;

      ::acme::get()->platform()->informationf("::sockets::socket_handler currently allocated count = " + ::as_string((::iptr) iSocketHandler));

   }


   socket_handler::~socket_handler()
   {

      cleanup_handler();

      g_interlockedcountSocketHandler--;

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

      __construct(m_pcomposite);


   }


   void socket_handler::cleanup_handler()
   {

//      if (m_resolver.is_set())
//      {
//
//         resolver()->Quit();
//
//      }

      //{

      //   auto ppair = m_socketmap.get_start();

      //   while (ppair != nullptr)
      //   {

      //      if (ppair->element2().is_set())
      //      {

      //         try
      //         {

      //            ppair->element2()->close();

      //         }
      //         catch (...)
      //         {

      //         }

      //         //if (m_slave)
      //         {

      //            ppair->element2().release();

      //         }

      //      }

      //      ppair = m_socketmap.get_next(ppair);

      //   }

      //}

      //m_socketmap.erase_all();

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

      m_pcomposite->SetSlave(x);
   //   m_slave = x;

   }


   bool socket_handler::IsSlave()
   {

      return m_pcomposite->IsSlave();
//      return m_slave;

   }
   

   //void socket_handler::add2(const socket_pointer & psocket)
   //{

   //   //auto passociation = m_socketmapAdd.get_association(psocket->get_socket_id());

   //   //passociation->m_psocket = psocket;

   //   //transfer(passociation, &m_socketmapAdd);

   //}

   //
   //void socket_handler::move2(socket_pointer && psocket)
   //{

   //   //auto passociation = m_socketmapAdd.get_association(psocket->get_socket_id());

   //   //passociation->m_psocket = ::transfer(psocket);

   //   //transfer(passociation, &m_socketmapAdd);

   //}


   //void socket_handler::transfer(socket_id_map::association* passociation, socket_id_map* psocket_idmap)
   //{

   //   socket_id* psocket = dynamic_cast <socket_id*> (passociation->m_psocket.m_p);

   //   //if (psocket->m_psocket_idhandler.is_set())
   //   //{

   //   //   WARN(psocket, "add", -1, "socket_id is already being handled by another handler");

   //   //   return;

   //   //}

   //   if (psocket->get_socket_id() == INVALID_SOCKET_ID)
   //   {

   //      warning() <<"add: Invalid socket_id";

   //      if (psocket->IsCloseAndDelete())
   //      {

   //         m_delete.add_tail(psocket);

   //      }

   //      return;

   //   }

   //   //socket_pointer plookup;

   //   //if (m_socketmapAdd.lookup(psocket->get_socket_id(), plookup))
   //   //{

   //   //   INFO(psocket, "add", (i32)psocket->get_socket_id(), "Attempt to add socket_id already in add queue");

   //   //   //m_delete.add_tail(psocket);
   //   //   return;

   //   //}

   //   if (psocket->is_connecting())
   //   {

   //      if (psocket->m_timeConnectionMaximum > 0_s)
   //      {

   //         socket_id_list_add(psocket->get_socket_id(), e_list_timeout);

   //      }

   //   }
   //   else
   //   {

   //      if (psocket->m_timeMaximum > 0_s)
   //      {

   //         socket_id_list_add(psocket->get_socket_id(), e_list_timeout);

   //      }

   //   }

   //   if (psocket->IsDetach())
   //   {

   //      socket_id_list_add(psocket->get_socket_id(), e_list_detach);

   //   }

   //   psocket->m_psocket_idhandler = this;

   //   psocket->m_estatus = ::success;

   //   m_socketmapAdd.transfer(passociation, psocket_idmap);

   //}


   //void socket_handler::restart_socket_id(socket_id socket_id)
   //{

   //   auto passociation = m_socketmap.find_association(socket_id);

   //   if (passociation->m_psocket->is_connecting())
   //   {

   //      if (passociation->m_psocket->m_timeConnectionMaximum > 0_s)
   //      {

   //         socket_id_list_add(passociation->m_psocket->get_socket_id(), e_list_timeout);

   //      }

   //   }
   //   else
   //   {

   //      if (passociation->m_psocket->m_timeMaximum > 0_s)
   //      {

   //         socket_id_list_add(passociation->m_psocket->get_socket_id(), e_list_timeout);

   //      }

   //   }

   //   passociation->m_psocket->m_estatus = ::success;

   //   m_socketmapAdd.transfer(passociation, &m_socketmap);

   //}


   //void socket_handler::get(socket_id s, bool& r, bool& w, bool& e)
   //{
   //   if (s >= 0)
   //   {
   //      r = FD_ISSET(s, &m_rfds) ? true : false;
   //      w = FD_ISSET(s, &m_wfds) ? true : false;
   //      e = FD_ISSET(s, &m_efds) ? true : false;
   //   }
   //}


   //void socket_handler::set(socket_id s, bool bRead, bool bWrite, bool bException)
   //{
   //   if (s >= 0)
   //   {
   //      if (bRead)
   //      {
   //         if (!FD_ISSET(s, &m_rfds))
   //         {
   //            FD_SET(s, &m_rfds);
   //            m_countR++;
   //         }
   //      }
   //      else
   //      {
   //         if (FD_ISSET(s, &m_rfds))
   //         {
   //            FD_CLR(s, &m_rfds);
   //            m_countR--;
   //         }
   //      }
   //      if (bWrite)
   //      {
   //         if (!FD_ISSET(s, &m_wfds))
   //         {
   //            FD_SET(s, &m_wfds);
   //            m_countW++;
   //         }
   //      }
   //      else
   //      {
   //         if (FD_ISSET(s, &m_wfds))
   //         {
   //            FD_CLR(s, &m_wfds);
   //            m_countW--;
   //         }
   //      }
   //      if (bException)
   //      {
   //         if (!FD_ISSET(s, &m_efds))
   //         {
   //            FD_SET(s, &m_efds);
   //            m_countE++;
   //         }
   //      }
   //      else
   //      {
   //         if (FD_ISSET(s, &m_efds))
   //         {
   //            FD_CLR(s, &m_efds);
   //            m_countE--;
   //         }
   //      }
   //   }
   //}


   i32 socket_handler::select(i32 lSeconds, i32 lMicroseconds)
   {

      //struct timeval timeval;

      //timeval.tv_sec = lSeconds;
      //timeval.tv_usec = lMicroseconds;

      //return select(&timeval);
      return m_pcomposite->select(lSeconds, lMicroseconds);

   }


   i32 socket_handler::select()
   {

      return -1;

      //if (m_socketidlistCallOnConnect.get_size() ||
      //      //(!m_slave && m_socketidlistDetach.get_size()) ||
      //      m_socketidlistDetach.get_size() ||
      //      m_socketidlistTimeout.get_size() ||
      //      m_socketidlistRetryClientConnect.get_size() ||
      //      m_socketidlistClose.get_size() ||
      //      m_socketidlistErase.get_size())
      //{
      //   return select(0, 200000);
      //}

      //return select(1_s);

   }





   //bool socket_handler::contains(base_socket * pbasesocket_id)
   //{

   //   //socket_pointer psocket = pbasesocket_id;

   //   //if (::contains_payload(m_socketmap, psocket))
   //   //{

   //   //  return true;

   //   //}

   //   //if (::contains_payload(m_socketmapAdd, psocket))
   //   //{

   //   //  return true;

   //   //}

   //   //if (m_delete.contains(psocket))
   //   //{

   //   //  return true;

   //   //}

   //   return false;

   //}


   bool socket_handler::call_on_connect()
   {

      //// check CallOnConnect - EVENT
      //if (m_socketidlistCallOnConnect.get_size())
      //{
      //  socket_id_list tmp = m_socketidlistCallOnConnect;
      //  auto pnode = tmp.get_head();
      //  for (; pnode != nullptr; pnode = pnode->m_pnext)
      //  {
      //     socket_id socket_id = pnode->m_value;
      //     socket_pointer psocket;
      //     if (!m_socketmap.lookup(socket_id, psocket)) // not found
      //     {

      //        warning() <<"get_socket_id/handler/4 " << (i32)socket_id << " Did not find expected socket_id using file descriptor(4)";

      //        socket_id_list_erase(psocket->get_socket_id(), e_list_call_on_connect);

      //     }

      //     if (psocket != nullptr)
      //     {

      //        tcp_socket * ptcpsocket = psocket.cast < tcp_socket >();

      //        if (ptcpsocket != nullptr)
      //        {

      //           if (ptcpsocket->CallOnConnect() && psocket->Ready())
      //           {
      //              
      //              psocket->SetConnected(); // moved here from inside if (ptcpsocket) check below

      //              if (psocket->IsSSL()) // SSL Enabled socket_id
      //              {

      //                 psocket->OnSSLConnect();

      //              }
      //              else if (psocket->Socks4())
      //              {

      //                 psocket->OnSocks4Connect();

      //              }
      //              else
      //              {

      //                 if (ptcpsocket)
      //                 {

      //                    if (ptcpsocket->GetOutputLength())
      //                    {

      //                       psocket->OnWrite();

      //                    }

      //                 }

      //                 if (ptcpsocket && ptcpsocket->IsReconnect())
      //                 {

      //                    psocket->OnReconnect();

      //                 }
      //                 else
      //                 {

      //                    ptcpsocket->information() << "Calling OnConnect: Because CallOnConnect";

      //                    psocket->OnConnect();

      //                 }

      //              }

      //              ptcpsocket->SetCallOnConnect(false);

      //              socket_id_list_erase(psocket->get_socket_id(), e_list_call_on_connect);

      //           }

      //        }

      //     }

      //  }

      //   return true;

      //}

      return false;

   }


  i32 socket_handler::select(const class time & timeWait)
  {

     throw interface_only();

     return -1;
//     i32 n = system()->m_papexsystem->networking()->_select(this, wait);
//
//
//     auto tick2 = ::time::now();
//
//     if (n < 0)
//     {
//
//        auto tickNow = ::time::now();
//
//        /*
//           EBADF  An invalid file descriptor was given in one of the sets.
//           EINTR  A non blocked signal was caught.
//           EINVAL n is negative. Or struct timeval contains bad time values (<0).
//           ENOMEM select was unable to allocate memory for internal tables.
//        */
//
//        if (m_maxsock > 0 && (m_iSelectErrno != m_iPreviousError || tickNow - m_timeLastError > 5_s))
//        {
//
//           information() << "select" << m_iSelectErrno << ", " << bsd_socket_error(m_iSelectErrno);
//
//           i32 iError = m_iSelectErrno;
//
//#if defined(LINUX) || defined(MACOS)
//
//           information() << "m_maxsock: " << m_maxsock;
//           information() << "sockets::socket_handler select error : "<< strerror(Errno) <<" ("<< Errno <<")";
//
//#elif defined(WINDOWS)
//
//           information() << "sockets::socket_handler select error : "<< ::windows::last_error_message(iError) <<" ("<< iError <<")";
//
//#endif
//
//           if (iError == 10022)
//           {
//
//              information() << "WSEINVAL - An invalid argument was supplied";
//
//           }
//
//           // test bad fd
//           for (socket_id socket_id = 0; socket_id < m_maxsock; socket_id++)
//           {
//
//              bool bAnySet = false;
//
//              FD_ZERO(&rfds);
//              FD_ZERO(&wfds);
//              FD_ZERO(&efds);
//
//              if (FD_ISSET(socket_id, &m_rfds))
//              {
//
//                 FD_SET(socket_id, &rfds);
//
//                 bAnySet = true;
//
//              }
//
//              if (FD_ISSET(socket_id, &m_wfds))
//              {
//
//                 FD_SET(socket_id, &wfds);
//
//                 bAnySet = true;
//
//              }
//
//              if (FD_ISSET(socket_id, &m_efds))
//              {
//
//                 FD_SET(socket_id, &efds);
//
//                 bAnySet = true;
//
//              }
//
//              if (bAnySet)
//              {
//
//                 auto ppairsocket_id = m_socketmap.plookup(socket_id);
//
//                 if (::is_set(ppairsocket_id) && ::is_set(ppairsocket_id->m_psocket))
//                 {
//
//                    information() << "Bad fd in fd_set: " << socket_id;
//
//                    information() << "Deleting and removing socket_id: " << socket_id;
//
//                    ppairsocket_id->m_psocket->SetCloseAndDelete();
//
//                 }
//
//              }
//
//           }
//
//        }
//
//        /// \no more todo rebuild fd_set's from active sockets list (m_socketmap) here
//        /// done : http://jbmon.googlecode.com/svn/trunk/sockets/socket_idHandler.cpp : rebuild fd_set's from active sockets list (m_socketmap) here
//        {
//
//           FD_ZERO(&rfds);
//           FD_ZERO(&wfds);
//           FD_ZERO(&efds);
//
//           ::collection::count countR = 0;
//           ::collection::count countW = 0;
//           ::collection::count countE = 0;
//
//           auto it = m_socketmap.begin();
//
//           for(; it; it++)
//           {
//
//              try
//              {
//
//                 if (it->m_socket_id == it->m_psocket->get_socket_id())
//                 {
//
//                    fd_set fds;
//
//                    FD_ZERO(&fds);
//
//                    FD_SET(it->m_socket_id, &fds);
//
//                    struct timeval tv;
//
//                    tv.tv_sec = 0;
//
//                    tv.tv_usec = 0;
//
//                    i32 n = ::select((i32)(it->m_socket_id + 1), &fds, nullptr, nullptr, &tv);
//
//                    if (n == -1)
//                    {
//
//                       // %! bad fd, erase
//
//                       it->m_psocket, " Select " << (i32)it->m_socket_id << "Bad fd in fd_set (2)"); // ->error() << LOG_LEVEL_ERROR);
//
//                       m_socketidlistErase.add(it->m_socket_id);
//
//                    }
//                    else
//                    {
//
//                       bool bAnySet = false;
//
//                       if (FD_ISSET(it->m_socket_id, &m_rfds))
//                       {
//
//                          FD_SET(it->m_socket_id, &rfds);
//
//                          countR++;
//
//                          bAnySet = true;
//
//                       }
//
//                       if (FD_ISSET(it->m_socket_id, &m_wfds))
//                       {
//
//                          FD_SET(it->m_socket_id, &wfds);
//
//                          countW++;
//
//                          bAnySet = true;
//
//                       }
//
//                       if (FD_ISSET(it->m_socket_id, &m_efds))
//                       {
//
//                          FD_SET(it->m_socket_id, &efds);
//
//                          countE++;
//
//                          bAnySet = true;
//
//                       }
//
//                       if (!bAnySet)
//                       {
//
//                          // %! none set
//
//                          it->m_psocket, "Select " << (i32)it->m_socket_id << " No fd in fd_set"); // ->error() << LOG_LEVEL_ERROR);
//
//                          m_socketidlistErase.add(it->m_socket_id);
//
//                       }
//
//                    }
//
//                 }
//                 else
//                 {
//
//                    // %! mismatch
//
//                    it->m_psocket, "Select" << (i32)it->m_socket_id << "Bad fd in fd_set (3)"); // ->error() << LOG_LEVEL_ERROR);
//
//                    m_socketidlistErase.add(it->m_socket_id);
//
//                 }
//
//              }
//              catch (...)
//              {
//
//                 // general error
//
//                 it->m_psocket, "Select" << (i32)it->m_socket_id << "Bad fd in fd_set (3)"); // ->error() << LOG_LEVEL_ERROR);
//
//                 m_socketidlistErase.add(it->m_socket_id);
//
//              }
//
//           }
//
//           m_rfds = rfds;
//           m_wfds = wfds;
//           m_efds = efds;
//
//           m_countR = countR;
//           m_countW = countW;
//           m_countE = countE;
//
//        }
//
//        m_iPreviousError = m_iSelectErrno;
//
//        m_timeLastError = tickNow;
//
//     }
//     else if(n == 0)
//     {
//
//        m_iPreviousError = -1;
//
//     }
//     else // n > 0
//     {
//
//        auto pos = m_socketidlist.begin();
//
//        for (; pos && n; pos++)
//        {
//           
//           socket_id socket_id = *pos;
//
//           if (FD_ISSET(socket_id, &rfds))
//           {
//              
//              auto ppairsocket_id = m_socketmap.plookup(socket_id);
//
//              if (::is_set(ppairsocket_id) && ::is_set(ppairsocket_id->m_psocket)) // found
//              {
//
//                 // new SSL negotiate method
//                 if (ppairsocket_id->m_psocket->IsSSLNegotiate())
//                 {
//                    
//                    ppairsocket_id->m_psocket->SSLNegotiate();
//
//                 }
//                 else
//                 {
//                    
//                    ppairsocket_id->m_psocket->OnRead();
//
//                 }
//
//              }
//              else
//              {
//
//                 warning() <<"get_socket_id/handler/1 " << (i32)socket_id << "Did not find expected socket_id using file descriptor(1)";
//
//              }
//
//              n--;
//
//           }
//
//           if (FD_ISSET(socket_id, &wfds))
//           {
//              
//              auto ppairsocket_id = m_socketmap.plookup(socket_id);
//
//              if (::is_set(ppairsocket_id) && ::is_set(ppairsocket_id->m_psocket)) // found
//              {
//
//                 // new SSL negotiate method
//                 if (ppairsocket_id->m_psocket->IsSSLNegotiate())
//                 {
//
//                    ppairsocket_id->m_psocket->SSLNegotiate();
//
//                 }
//                 else
//                 {
//
//                    ppairsocket_id->m_psocket->OnWrite();
//
//                 }
//
//              }
//              else
//              {
//
//                 warning() <<"get_socket_id/handler/2" << (i32)socket_id << "Did not find expected socket_id using file descriptor(2)";
//
//              }
//
//              n--;
//
//           }
//
//           if (FD_ISSET(socket_id, &efds))
//           {
//
//              auto ppairsocket_id = m_socketmap.plookup(socket_id);
//
//              if (::is_set(ppairsocket_id) && ::is_set(ppairsocket_id->m_psocket)) // found
//              {
//                 
//                 // Out-Of-Band data
//                 // recv with MSG_OOB
//                 //posix_time tnow = time(nullptr);
//
//                 if (ppairsocket_id->m_psocket->has_timed_out())
//                 {
//                 
//                    if (ppairsocket_id->m_psocket->is_connecting())
//                    {
//
//                       warning() <<"get_socket_id/handler/3" << (i32)socket_id << "stream_socket_id on_connection_timeout (3)";
//
//                       ppairsocket_id->m_psocket->on_connection_timeout();
//
//                    }
//                    else
//                    {
//
//                       warning() <<"get_socket_id/handler/3 " << (i32)socket_id << " socket_id on_timeout(3)";
//
//                       ppairsocket_id->m_psocket->on_timeout();
//
//                    }
//
//                 }
//                 else
//                 {
//
//                    ppairsocket_id->m_psocket->OnException();
//
//                 }
//
//              }
//              else
//              {
//
//                 warning() <<"get_socket_id/handler/3 " << (i32)socket_id << " Did not find expected socket_id using file descripto(3)r";
//
//              }
//
//              n--;
//
//           }
//
//        } // m_socketidlist loop
//
//        m_iPreviousError = -1;
//
//     } // if (n > 0)
//
//     call_on_connect();
//
//     bool check_max_fd = false;
//
//     // check detach of socket_id if master handler - EVENT
//     //if (!m_slave && m_socketidlistDetach.get_size())
//     if(m_socketidlistDetach.has_element())
//     {
//
//        retry_next_item_in_detach_list:
//
//        auto pos = m_socketidlistDetach.begin();
//
//        socket_id socket_id = 0;
//
//        for (; pos != m_socketidlistDetach.end(); pos++)
//        {
//
//           socket_id = *pos;
//           
//           auto ppairsocket_id = m_socketmap.plookup(socket_id);
//
//           if (::is_set(ppairsocket_id) && ::is_set(ppairsocket_id->m_psocket))
//           {
//
//              if (ppairsocket_id->m_psocket->IsDetach()
//                 && !ppairsocket_id->m_psocket->IsDetached())
//              {
//
//                 if (socket_id != INVALID_SOCKET_ID)
//                 {
//
//                    set(socket_id, false, false, false);
//
//                    // After Detachsocket_id(), all calls to socket_handler() will return a object
//                    // to the new slave socket_handler running in the new thread.
//                    try
//                    {
//
//                       ppairsocket_id->m_psocket->Detachsocket_id(ppairsocket_id, &m_socketmap);
//
//                    }
//                    catch (...)
//                    {
//
//                    }
//
//                    erase_socket_id(socket_id);
//
//                    check_max_fd = true;
//
//                    goto retry_next_item_in_detach_list;
//
//                 }
//
//              }
//
//           }
//
//        }
//
//     }
//
//     // check is_connecting - connection timeout - conditional event
//     if (m_socketidlistTimeout.get_size())
//     {
//        
//        posix_time tnow = time(nullptr);
//
//        if (tnow != m_tlast)
//        {
//
//           restartsocket_idListTimeout:
//
//           socket_id_list tmp = m_socketidlistTimeout;
//
//           auto it = tmp.begin();
//
//           for (; it; it++)
//           {
//
//              socket_id socket_id = *it;
//
//              auto ppairsocket_id = m_socketmap.plookup(socket_id);
//
//              if (::is_null(ppairsocket_id) || ::is_null(ppairsocket_id->m_psocket)) // not found
//              {
//
//                 ppairsocket_id = m_socketmapAdd.plookup(socket_id);
//
//                 if (::is_null(ppairsocket_id) || ::is_null(ppairsocket_id->m_psocket))
//                 {
//
//                    warning() <<"get_socket_id/handler/6 " << (i32)socket_id << " Did not find expected socket_id using file descriptor(f)";
//
//                    m_socketidlistTimeout.erase(socket_id);
//
//                    goto restartsocket_idListTimeout;
//
//                 }
//
//                 continue;
//
//              }
//              
//              if (::is_set(ppairsocket_id) || ::is_set(ppairsocket_id->m_psocket))
//              {
//
//                 if (ppairsocket_id->m_psocket->has_timed_out())
//                 {
//
//                    if (ppairsocket_id->m_psocket->is_connecting())
//                    {
//
//                       warning() <<"get_socket_id/handler/7 " << (i32)socket_id << "stream_socket_id on_connection_timeout (g)";
//
//                       ppairsocket_id->m_psocket->on_connection_timeout();
//
//                    }
//                    else
//                    {
//
//                       warning() <<"get_socket_id/handler/7 " << (i32)socket_id << " socket_id on_timeout (g)";
//
//                       ppairsocket_id->m_psocket->on_timeout();
//
//                    }
//
//                    ppairsocket_id->m_psocket->SetCloseAndDelete();
//
//                 }
//
//              }
//
//           }
//
//           m_tlast = tnow;
//
//        }
//
//     }
//
//     // check retry client connect - EVENT
//     if (m_socketidlistRetryClientConnect.get_size())
//     {
//
//        socket_id_list tmp = m_socketidlistRetryClientConnect;
//
//        auto socket_id = tmp.begin();
//
//        for (; socket_id; socket_id++)
//        {
//
//           auto ppairsocket_id = m_socketmap.plookup(*socket_id);
//
//           if (::is_null(ppairsocket_id) || ::is_null(ppairsocket_id->m_psocket))
//           {
//
//              warning() <<"get_socket_id/handler/7 " << (i32)socket_id << " Did not find expected socket_id using file descriptor(g)";
//
//           }
//
//           if (::is_set(ppairsocket_id) && ::is_set(ppairsocket_id->m_psocket))
//           {
//
//              auto ptcpsocket = dynamic_cast < tcp_socket * > (ppairsocket_id->m_psocket.m_p);
//
//              if (::is_set(ptcpsocket))
//              {
//
//                 if (ptcpsocket->RetryClientConnect())
//                 {
//
//                    socket_id nn = socket_id; //(*it3).element1();
//
//                    ptcpsocket->SetRetryClientConnect(false);
//
//                    //information() << "close() before retry client connect\n");
//
//                    ptcpsocket->close(); // erases from m_socketidlistRetryClientConnect
//
//                    ::networking::address ad = ptcpsocket->GetClientRemoteAddress();
//
//                    if (ad.is_valid())
//                    {
//
//                       ptcpsocket->open(ad);
//
//                    }
//                    else
//                    {
//
//                       ptcpsocket->error() << "RetryClientConnect 0 no address";
//
//                    }
//
//                    transfer(ppairsocket_id, &m_socketmap);
//
//                    m_socketidlistErase.add_tail(nn);
//
//                 }
//
//              }
//
//           }
//
//        }
//
//     }
//
//     // check close and delete - conditional event
//     if (m_socketidlistClose.get_size() > 0)
//     {
//
//        socket_id_list socket_idlist = m_socketidlistClose;
//
//        auto psocket_idlist = socket_idlist.begin();
//
//        for(; psocket_idlist; psocket_idlist++)
//        {
//
//           socket_id socket_id = *psocket_idlist;
//
//           socket_id_map* psocket_idmap = nullptr;
//
//           auto ppairsocket_id = m_socketmap.plookup(socket_id);
//
//           if (::is_null(ppairsocket_id) || ::is_null(ppairsocket_id->m_psocket)) // not found
//           {
//
//              ppairsocket_id = m_socketmapAdd.plookup(socket_id);
//
//              if (::is_null(ppairsocket_id) || ::is_null(ppairsocket_id->m_psocket))
//              {
//
//                 warning() <<"get_socket_id/handler/8 " << (i32)socket_id << " Did not find expected socket_id using file descriptor(8)";
//
//              }
//              else
//              {
//
//                 psocket_idmap = &m_socketmapAdd;
//
//              }
//
//           }
//           else
//           {
//
//              psocket_idmap = &m_socketmap;
//
//           }
//
//           if (::is_set(ppairsocket_id) && ::is_set(ppairsocket_id->m_psocket))
//           {
//
//              auto psocket = ppairsocket_id->m_psocket.m_p;
//
//              if (psocket->IsCloseAndDelete())
//              {
//
//                 auto ptcpsocket = dynamic_cast <tcp_socket*> (ppairsocket_id->m_psocket.m_p);
//
//                 // new graceful ptcpsocket - flush and close timeout 5s
//                 if (::is_set(ptcpsocket) && psocket->IsConnected() && ptcpsocket->GetFlushBeforeClose() &&
//                       !ptcpsocket->IsSSL() && psocket->TimeSinceClose() < 5)
//                 {
//
//                    //information() << " close(1)\n");
//                    if (ptcpsocket->GetOutputLength())
//                    {
//
//                       ptcpsocket->information() << "Closing " << (i32)ptcpsocket->GetOutputLength() << " Sending all data before closing";
//
//                    }
//                    else // shutdown write when output buffer is is_empty
//                       if (!(ptcpsocket->GetShutdownStatus() & SHUT_WR))
//                    {
//
//                       if (ptcpsocket->m_socket_id != INVALID_SOCKET_ID && shutdown(psocket->m_socket_id, SHUT_WR) == -1)
//                       {
//
//                          ptcpsocket->error() << "graceful shutdown " << Errno << bsd_socket_error(Errno);
//
//                       }
//
//                       ptcpsocket->SetShutdownStatus(SHUT_WR);
//
//                    }
//
//                 }
//                 else if (::is_set(ptcpsocket) && psocket->IsConnected() && ptcpsocket->Reconnect())
//                 {
//
//                    //socket_id nn = *it; //(*it3).element1();
//                    //informationf(" close(2) fd %d\n", socket_id));
//
//                    ptcpsocket->SetCloseAndDelete(false);
//
//                    ptcpsocket->SetIsReconnect();
//
//                    ptcpsocket->SetConnected(false);
//
//                    //information() << "close() before reconnect\n");
//
//                    ptcpsocket->close(); // dispose of old file descriptor (open creates a new)
//
//                    ptcpsocket->OnDisconnect();
//
//                    ::networking::address ad = ptcpsocket->GetClientRemoteAddress();
//
//                    if (ad.is_valid())
//                    {
//
//                       ptcpsocket->open(ad);
//
//                    }
//                    else
//                    {
//
//                       ptcpsocket->error() << "Reconnect 0 no address";
//
//                    }
//
//                    ptcpsocket->ResetConnectionRetryCount();
//
//                    transfer(ppairsocket_id, psocket_idmap);
//
//                    m_socketidlistErase.add_tail(ptcpsocket->m_socket_id);
//
//                 }
//                 else
//                 {
//
//                    //informationf(" close(3) fd %d get_socket_id() %d\n", socket_id, point_i32 -> get_socket_id()));
//
//                    if (psocket && psocket->IsConnected() && ptcpsocket->GetOutputLength())
//                    {
//
//                       psocket->warning() << "Closing " << (i32)ptcpsocket->GetOutputLength() << " Closing socket_id while data still left to send";
//
//                    }
//
//                    if (psocket->Retain() && !psocket->Lost())
//                    {
//
//                       auto psystem = system()->m_papexsystem;
//
//                       synchronous_lock synchronouslock(&psystem->sockets().m_pmutexPool);
//
//                       auto ppoolsocket_id = ::place(new pool_socket_id(psocket));
//
//                       ppoolsocket_id->m_psocket_idhandler = this;
//
//                       ppoolsocket_id->SetDeleteByHandler();
//
//                       psystem->sockets().m_pool.set_at(ppoolsocket_id->m_socket_id, ppoolsocket_id);
//
//                       ppoolsocket_id->SetCloseAndDelete(false); // added - erase from m_socketidlistClose
//
//                       //point_i32 -> SetCloseAndDelete(false); // added - erase from m_socketidlistClose
//
//                    }
//                    //else if (psocket.cast < http_session >() != nullptr && !psocket->Lost())
//                    //{
//
//                    //   psocket->SetCloseAndDelete(false);
//
//                    //   continue;
//
//                    //}
//                    else if(psocket->get_socket_id() != INVALID_SOCKET_ID)
//                    {
//
//                       set(psocket->get_socket_id(), false, false, false);
//
//                       //information() << "close() before OnDelete\n");
//
//                       psocket->close();
//
//                    }
//
//                    psocket->OnDelete();
//
//                    if (psocket->DeleteByHandler())
//                    {
//
//                       psocket->SetErasedByHandler();
//
//                    }
//
//                 }
//
//              }
//
//           }
//
//           m_socketidlistErase.add_tail(socket_id);
//
//        }
//
//     }
//
//     // check erased sockets
//     while (m_socketidlistErase.get_size())
//     {
//
//        socket_id socket_id = m_socketidlistErase.pick_head();
//
//        erase_socket_id(socket_id);
//
//        auto ppairsocket_id = m_socketmap.plookup(socket_id);
//
//        if (::is_set(ppairsocket_id) && ::is_set(ppairsocket_id->m_psocket))
//        {
//
//           ppairsocket_id->m_psocket->m_psocket_idhandler.release();
//
//           //ppairsocket_id->m_psocket->m_phandlerSlave.release();
//
//           m_socketmap.erase_key(socket_id);
//
//           m_delete.erase(ppairsocket_id->m_psocket);
//
//           m_socketmapAdd.erase_key(socket_id);
//
//        }
//
//        check_max_fd = true;
//
//     }
//
//     // calculate maximum file descriptor for select() call
//     if (check_max_fd)
//     {
//
//        m_maxsock = m_socketidlist.maximum(0) + 1;
//
//     }
//
//     // erase add's that fizzed
//     while (m_delete.has_element())
//     {
//
//        auto psocket = m_delete.pick_head().m_p;
//
//        psocket->OnDelete();
//
//        //if (psocket->DeleteByHandler() && !(m_slave ^ psocket->IsDetached()))
//        if (psocket->DeleteByHandler() && psocket->IsDetached())
//        {
//
//           psocket->SetErasedByHandler();
//
//           bool again = false;
//
//           do
//           {
//
//              again = false;
//
//              auto p = m_trigger_src.begin();
//
//              for(; p; p++)
//              {
//                 //socket_id atom = 0;
//                 //socket_pointer src;
//
//                 //iterator->get_pair(atom, src);
//
//                 if (p->m_psocket == psocket)
//                 {
//
//                    auto pdst = m_trigger_dst[p->m_socket_id].begin();
//
//                    for(;pdst; pdst++)
//                    {
//
//                       if (Valid(pdst->m_pbasesocket_id))
//                       {
//
//                          pdst->m_pbasesocket_id->OnCancelled(p->m_socket_id);
//
//                       }
//
//                    }
//
//                    m_trigger_src.erase_key(p->m_socket_id);
//
//                    m_trigger_dst.erase_key(p->m_socket_id);
//
//                    again = true;
//
//                    break;
//
//                 }
//
//              }
//
//           }
//           while (again);
//
//        }
//
//     }
//return-1;
//
//     return n;

  }


  //bool socket_handler::Resolving(base_socket * p0)
  //{

  //   return m_resolve_q.plookup(p0) != nullptr;

  //}


   bool socket_handler::Valid(base_socket * pIsValid)
   {

      //auto p = m_socketmap.begin();

      //for(; p; p++)
      //{

      //  if (pIsValid == p->m_psocket)
      //  {

      //     return true;

      //  }

      //}

      return false;

   }


   bool socket_handler::OkToAccept(base_socket *)
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

      //::collection::count isocket_ids = m_socketmap.get_size();

      //::collection::count iAdd = m_socketmapAdd.get_size();

      //::collection::count iDelete = m_delete.get_size();

      //return isocket_ids + iAdd + iDelete;

      return m_pcomposite->get_count();

   }


   //void socket_handler::SetSocks4Host(in_addr a)
   //{
   //   m_socks4_host = a;
   //}


   //void socket_handler::SetSocks4Host(const string & host)
   //{

   //   auto paddressdepartment = ::networking::address_department();

   //   paddressdepartment->convert(m_socks4_host, host);

   //}


   //void socket_handler::SetSocks4Port(::networking::port_t port)
   //{
   //   m_socks4_port = port;
   //}


   //void socket_handler::SetSocks4Userid(const string & atom)
   //{
   //   m_socks4_userid = atom;
   //}


//   i32 socket_handler::Resolve(base_socket * pbasesocket_id, const string & host, ::networking::port_t port)
//   {
//
//      // check cache
//
//      ::pointer<resolv_socket_id>presolvsocket_id = ::place(new resolv_socket_id(pbasesocket_id, host, port));
//
//      presolvsocket_id->m_psocket_idhandler = this;
//
//      presolvsocket_id->SetId(++m_resolv_id);
//
//      presolvsocket_id->SetDeleteByHandler();
//
//      in_addr addrLocal;
//
//      auto paddressdepartment = ::networking::address_department();
//
//      paddressdepartment->convert(addrLocal, "127.0.0.1");
//
//      if (!presolvsocket_id->open(::networking::address(addrLocal, m_resolver_port)))
//      {
//
//         fatal() <<presolvsocket_id, "Resolve", -1, "Can't connect to local resolve server";
//
//      }
//
//      add(presolvsocket_id);
//
//      m_resolve_q[pbasesocket_id] = true;
//
//      informationf(" *** Resolve '%s:%d' atom#%d  m_resolve_q size_i32: %d  base_socket: %p\n", host.c_str(), port, presolvsocket_id->GetId(), m_resolve_q.get_size(), pbasesocket_id));
//
//      return presolvsocket_id->GetId();
//
//   }


//   i32 socket_handler::Resolve6(base_socket * pbasesocket_id, const string & host, ::networking::port_t port)
//   {
//
//      // check cache
//
//      ::pointer<resolv_socket_id>resolv = ::place(new resolv_socket_id(pbasesocket_id, host, port, true));
//
//      resolv->m_psocket_idhandler = this;
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
//      m_resolve_q[pbasesocket_id] = true;
//
//      return resolv->GetId();
//
//   }


//   i32 socket_handler::Resolve(base_socket * pbasesocket_id, in_addr a)
//   {
//
//      // check cache
//
//      ::pointer<resolv_socket_id>resolv = ::place(new resolv_socket_id(pbasesocket_id, a));
//
//      resolv->m_psocket_idhandler = this;
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
//      m_resolve_q[pbasesocket_id] = true;
//
//      return resolv->GetId();
//
//   }


//   i32 socket_handler::Resolve(base_socket * pbasesocket_id, in6_addr& a)
//   {
//
//      // check cache
//
//      ::pointer<resolv_socket_id>resolv = ::place(new resolv_socket_id(pbasesocket_id, a));
//
//      resolv->m_psocket_idhandler = this;
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
//      m_resolve_q[pbasesocket_id] = true;
//
//      return resolv->GetId();
//
//   }


//   void socket_handler::EnableResolver(::networking::port_t port)
//   {
//
//      if (!m_resolver)
//      {
//
//         m_resolver_port = port;
//
//         auto presolvserver = ::place(new resolv_server());
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


   //void socket_handler::SetSocks4TryDirect(bool x)
   //{

   //   m_bTryDirect = x;

   //}


   //in_addr socket_handler::GetSocks4Host()
   //{

   //   return m_socks4_host;

   //}


   //::networking::port_t socket_handler::GetSocks4Port()
   //{

   //   return m_socks4_port;

   //}


   //const string & socket_handler::GetSocks4Userid()
   //{

   //   return m_socks4_userid;

   //}


   //bool socket_handler::Socks4TryDirect()
   //{

   //   return m_bTryDirect;

   //}


//   bool socket_handler::ResolverEnabled()
//   {
//
//      return m_resolver ? true : false;
//
//   }


//   ::networking::port_t socket_handler::GetResolverPort()
//   {
//
//      return m_resolver_port;
//
//   }


   //::pointer<base_socket_handler::pool_socket_id>socket_handler::FindConnection(i32 type, const string & protocol, ::networking::address * ad)
   //{

   //   auto psystem = system()->m_papexsystem;

   //   synchronous_lock synchronouslock(&psystem->sockets().m_pmutexPool);

   //   auto p = psystem->sockets().m_pool.begin();

   //   for(; p; p++)
   //   {

   //      auto psocket = p->m_psocket;

   //      if (psocket)
   //      {

   //         if (psocket->Getsocket_idType() == type &&
   //               psocket->Getsocket_idProtocol() == protocol &&
   //               // %!             pools -> GetClientRemoteAddress() &&
   //               psocket->GetClientRemoteAddress() == ad)
   //         {

   //            psystem->sockets().m_pool.erase_key(p->m_socket_id);

   //            psocket->SetRetain(); // avoid close in socket_id destructor

   //            return psocket; // Caller is responsible that this socket_id is deleted

   //         }

   //      }

   //   }

   //   return nullptr;

   //}


   void socket_handler::EnablePool(bool x)
   {
      //m_bEnablePool = x;
      m_pcomposite->EnablePool(x);
   }


   bool socket_handler::PoolEnabled()
   {

      return m_pcomposite->PoolEnabled();

   }


//   void socket_handler::erase(base_socket * psocket_idRemove)
//   {
//
////      if (m_resolve_q.has(psocket_idRemove))
////      {
////
////         m_resolve_q.erase_key(psocket_idRemove);
////
////      }
//
//      if (psocket_idRemove->ErasedByHandler())
//      {
//
//         return;
//
//      }
//
//      //if(::erase_value(m_socketmap, psocket_idRemove))
//      //{
//
//      //   psocket_idRemove->warning() << "erase -1 socket_id destructor called while still in use";
//
//      //   return;
//
//      //}
//
//      //if (::erase_value(m_socketmapAdd, psocket_idRemove))
//      //{
//
//      //   psocket_idRemove->warning() << "erase -2 socket_id destructor called while still in use";
//
//      //   return;
//
//      //}
//
//      //if (::erase_value(m_delete, psocket_idRemove))
//      //{
//
//      //   psocket_idRemove->warning() << "erase -3 socket_id destructor called while still in use";
//
//      //   return;
//
//      //}
//
//   }


   void socket_handler::CheckSanity()
   {

      //CheckList(m_socketidlist, "active sockets"); // active sockets
      //CheckList(m_socketidlistErase, "sockets to be erased"); // should always be is_empty anyway
      //CheckList(m_socketidlistCallOnConnect, "checklist CallOnConnect");
      //CheckList(m_socketidlistDetach, "checklist detach");
      //CheckList(m_socketidlistTimeout, "checklist time_out");
      //CheckList(m_socketidlistRetryClientConnect, "checklist retry client connect");
      //CheckList(m_socketidlistClose, "checklist close and delete");

   }


//  void socket_handler::CheckList(socket_id_list & list, const string & listname)
//  {
//
//     auto p = list.begin();
//
//     for(; (bool) p ; p++)
//     {
//
//        if (m_socketmap.has(*p))
//        {
//
//           continue;
//
//        }
//
//        if (m_socketmapAdd.has(*p))
//        {
//
//           continue;
//
//        }
//
////         if (!::contains_payload(m_delete, *p))
////         {
////
////            informationf("CheckList failed for \"%s\": fd %d\n", listname.c_str(), *p));
////
////         }
//
//     }
//
//  }

   //socket_id_list& socket_handler::socket_id_list_get(enum_list elist)
   //{

   //  switch (elist)
   //  {
   //  case e_list_call_on_connect:
   //     return m_socketidlistCallOnConnect;
   //  case e_list_detach:
   //     return m_socketidlistDetach;
   //  case e_list_timeout:
   //     return m_socketidlistTimeout;
   //  case  e_list_retry_client_connect:
   //     return m_socketidlistRetryClientConnect;
   //  case e_list_close:
   //     return m_socketidlistClose;
   //  default:
   //     return m_socketidlistClose;
   //  }

   //}


   //void socket_handler::socket_id_list_modify(socket_id s, enum_list elist, bool bAdd)
   //{

   //  if (bAdd)
   //  {

   //     socket_id_list_add(s, elist);

   //  }
   //  else
   //  {

   //     socket_id_list_erase(s, elist);

   //  }

   //}


   //void socket_handler::socket_id_list_add(socket_id s, enum_list elist)
   //{

   //  if (s == INVALID_SOCKET_ID)
   //  {
   //     information() << "AddList:  invalid_socket_id";
   //     return;
   //  }

   //  auto& socket_idlist = socket_id_list_get(elist);

   //  //if (add)
   //  //{
   //  //   /*         informationf("AddList);  %5d: %s: %s\n", s, (which_one == e_list_call_on_connect) ? "CallOnConnect" :
   //  //               (which_one == e_list_detach) ? "detach" :
   //  //               (which_one == e_list_timeout) ? "time_out" :
   //  //               (which_one == e_list_retry) ? "Retry" :
   //  //               (which_one == e_list_close) ? "close" : "<undef>",
   //  //               add ? "add" : "erase");*/
   //  //}
   //  //if (add)
   //  //{
   //  socket_idlist.add_tail_unique(s);
   //     //if (which_one == e_list_close)
   //     //{

   //     //   //INFO(informationf("list_close");
   //     //}
   //     //return;
   //  //}
   //  // erase
   //  //ref.erase(s);
   //  //information() << "/AddList\n");
   //}


   //void socket_handler::socket_id_list_erase(socket_id s, enum_list elist)
   //{

   //  if (s == INVALID_SOCKET_ID)
   //  {
   //     information() << "AddList:  invalid_socket_id";
   //     return;
   //  }

   //  auto& socket_idlist = socket_id_list_get(elist);

   //     //if (add)
   //     //{
   //     //   /*         informationf("AddList);  %5d: %s: %s\n", s, (which_one == e_list_call_on_connect) ? "CallOnConnect" :
   //     //               (which_one == e_list_detach) ? "detach" :
   //     //               (which_one == e_list_timeout) ? "time_out" :
   //     //               (which_one == e_list_retry) ? "Retry" :
   //     //               (which_one == e_list_close) ? "close" : "<undef>",
   //     //               add ? "add" : "erase");*/
   //     //}
   //     //if (add)
   //     //{
   //  socket_idlist.erase(s);
   //  //if (which_one == e_list_close)
   //  //{

   //  //   //INFO(informationf("list_close");
   //  //}
   //  //return;
   ////}
   //// erase
   ////ref.erase(s);
   ////information() << "/AddList\n");
   //}


   //void socket_handler::erase_socket_id(socket_id s)
   //{

   //  set(s, false, false, false); // erase from fd_set's

   //  m_socketidlistCallOnConnect.erase(s);
   //  m_socketidlistDetach.erase(s);
   //  m_socketidlistTimeout.erase(s);
   //  m_socketidlistRetryClientConnect.erase(s);
   //  m_socketidlistClose.erase(s);


   //}



   i32 socket_handler::TriggerID(base_socket * src)
   {
      //i32 atom = m_next_trigger_id++;
      //m_trigger_src[atom] = src;
      // return atom;
      return -1;

   }


   bool socket_handler::Subscribe(i32 atom, base_socket * psocket_idDst)
   {
      //if (m_trigger_src.plookup(atom) != nullptr)
      //{
      //   if (m_trigger_dst[atom].plookup(psocket_idDst) != nullptr)
      //   {
      //      m_trigger_dst[atom][psocket_idDst] = true;
      //      return true;
      //   }

      //   psocket_idDst->information() << "Subscribe " << atom << " Already subscribed";

      //   return false;
      //}

      //psocket_idDst->information() << "Subscribe " << atom << " Trigger atom not found";

      return false;

   }


   bool socket_handler::Unsubscribe(i32 atom, base_socket * psocket_idDst)
   {

      //if (m_trigger_src.plookup(atom) != nullptr)
      //{

      //   if (m_trigger_dst[atom].plookup(psocket_idDst) != nullptr)
      //   {

      //      m_trigger_dst[atom].erase_key(psocket_idDst);

      //      return true;

      //   }

      //   psocket_idDst->information() << "Unsubscribe " << atom << " Not subscribed";

      //   return false;
      //}

      //psocket_idDst->information() << "Unsubscribe " << atom << " Trigger atom not found";

      return false;
      
   }


   //void socket_handler::Trigger(i32 atom, socket_id::trigger_data& data, bool bErase)
   //{

   //   //if (m_trigger_src.contains(atom))
   //   //{

   //   //   data.SetSource(m_trigger_src[atom]);

   //   //   m_trigger_dst[atom].pairs().each([&](auto & pair)
   //   //      {

   //   //         if (this->Valid(pair.m_pbasesocket_id))
   //   //         {

   //   //            pair.m_pbasesocket_id->OnTrigger(atom, data);

   //   //         }

   //   //      });

   //   //   if (bErase)
   //   //   {

   //   //      m_trigger_src.erase_key(atom);
   //   //      m_trigger_dst.erase_key(atom);

   //   //   }

   //   //}
   //   //else
   //   //{

   //   //   information() << "Trigger " << atom << " Trigger atom not found";

   //   //}

   //}


}




