/** \file socket_thread.cpp
**   \date  2021-07-26
**   \author grymse@alhem.net
**   \moved to this file by camilosasuketbs@gmail.com
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
#include "socket_thread.h"
#include "socket.h"
#include "networking_bsd/sockets/basic/socket_handler.h"
#ifdef _WIN32
#elif defined(LINUX)
#include <netdb.h>
#include <fcntl.h>
#else
#include <netdb.h>
#include <fcntl.h>
#endif
////#include <ctype.h>
#include <time.h>


#ifdef PARALLELIZATION_PTHREAD


#include "acme/operating_system/ansi/_pthread.h"


#endif


#ifdef BSD_STYLE_SOCKETS
#include <openssl/ssl.h>
#endif


namespace sockets_bsd
{


   ::collection::index g_iSocketThread = 0;


   socket_thread::socket_thread()
   {

      //auto iAllocatedSocketThreadCount = g_iSocketThread++;

      //::information() << "::sockets_bsd::socket_thread currently allocated count = " << iAllocatedSocketThreadCount;

   }


   //void socket_thread::transfer(socket_map::node * pnode, socket_map * psocketmap)
   void socket_thread::initialize_socket_thread(base_socket * psocket)
   {

      initialize(psocket);

      m_psockethandler = __create_new < socket_handler > ();

      __Socket(psocket)->m_psocketthread = this;

      m_psockethandler->SetSlave();

      m_psockethandler->add(psocket);

      branch();

   }


   socket_thread::~socket_thread()
   {

      ::acme::get()->platform()->informationf("--->>>>>socket_thread::~SOCKET_thread\n");

   }

//
//   //void socket_thread::init_thread()
//   //{
//
//   //   if (!::thread::init_thread())
//   //   {
//
//   //      return false;
//
//   //   }
//
//
//   //   return true;
//
//   //}
//
//
//   //void socket_thread::term_thread()
//   //{
//
//   //   ::thread::term_thread();
//
//   //}
//
//
//#ifdef _DEBUG
//
//
//   ::i64 socket_thread::increment_reference_count()
//   {
//
//      return ::task::increment_reference_count();
//
//   }
//
//
//   ::i64 socket_thread::decrement_reference_count()
//   {
//
//      return ::task::decrement_reference_count();
//
//   }
//
//
//#endif


   ::sockets::base_socket* socket_thread::get_socket() const
   {

      if (::is_null(m_psockethandler))
      {

         return nullptr;

      }

      ::pointer < socket_handler > psockethandler = m_psockethandler;

      auto passociation = psockethandler->m_socketmap.m_begin;

      if (passociation.is_null())
      {

         return nullptr;

      }

      return passociation->element2();

   }


//   void socket_thread::run()
//   {
//
//      //if (phandler.get() != m_psocket->m_psockethandler.get())
//      //{
//
//      //   //   ::acme::get()->platform()->informationf("");
//
//      //   //}
//      //   //else
//      //   //{
//
//      //   phandler->add(m_psocket);
//
//      //}
//
//      try
//      {
//
//         while (task_get_run() && m_psockethandler->get_count())
//         {
//
//            try
//            {
//
//               m_psockethandler->select(1, 0);
//
//            }
//            catch (...)
//            {
//
//               break;
//
//            }
//
//         }
//
//      }
//      catch (...)
//      {
//
//      }
//
//      //m_psocket->m_psocketthread.release();
//
//      //m_psocket->destroy();
//
//      m_psockethandler->destroy();
//
//      destroy();
//
//      //return ::success;
//
//   }
//

} // namespace sockets_bsd



