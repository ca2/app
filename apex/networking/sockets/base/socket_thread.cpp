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
#include "apex/networking/networking.h"
#include "apex/networking/sockets/basic/socket_handler.h"
#include "apex/networking/sockets/basic/listen_socket.h"
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
//

#include "_____debug_counters_001.h"

namespace sockets
{

#if COUNTERS_001
   ::interlocked_count g_iSocketThread = 0;
#endif

   socket_thread::socket_thread()
   {
#if COUNTERS_001
      m_iAllocatedCount = g_iSocketThread++;
#endif

   }


   socket_thread::~socket_thread()
   {

#if COUNTERS_001
      g_iSocketThread--;

      informationf("--->>>>>socket_thread::~SOCKET_thread\n");
#endif
   }


   void socket_thread::initialize_socket_thread(base_socket* psocket)
   {

      initialize(psocket);

      m_psockethandler = create_socket_handler();

      auto pszType = typeid(*m_psockethandler.m_p).name();

      psocket->m_psocketthread = this;

      m_psockethandler->SetSlave();

      m_psockethandler->add(psocket);

      branch();

   }


   ::pointer < ::sockets::socket_handler > socket_thread::create_socket_handler()
   {

      if (m_typeSocketHandler.is_empty())
      {

         return øcreate < ::sockets::socket_handler >(m_pfactorySocketHandler);

      }
      else
      {

         return øid_create(m_typeSocketHandler, m_pfactorySocketHandler);

      }

   }


   void socket_thread::on_initialize_particle()
   {

      ::task::on_initialize_particle();

#if COUNTERS_001

      information() << "::sockets::socket_thread currently allocated count = " << m_iAllocatedCount;

#endif

   }


#ifdef _DEBUG


   long long socket_thread::increment_reference_count()
   {

      return ::task::increment_reference_count();

   }


   long long socket_thread::decrement_reference_count()
   {

      return ::task::decrement_reference_count();

   }


#endif


   base_socket* socket_thread::get_socket() const
   {

      if (::is_null(m_psockethandler))
      {

         return nullptr;

      }

      return nullptr;

   }


   void socket_thread::on_socket_thread_start()
   {

      system()->networking()->on_socket_thread_start();

   }


   void socket_thread::run()
   {

      on_socket_thread_start();

      try
      {

         while (true)
         {

            if (!task_get_run())
            {

               break;

            }

            if (m_psockethandler->get_count() <= 0)
            {

               break;

            }

            try
            {

               m_psockethandler->select(1, 0);

            }
            catch (...)
            {

               break;

            }

         }

      }
      catch (...)
      {

      }

      destroy();

   }


   void socket_thread::destroy()
   {

      m_psockethandler.defer_destroy();

      m_pfactorySocketHandler.release();

      ::task::destroy();

   }


} // namespace sockets



