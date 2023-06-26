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
#include "apex/networking/sockets/basic/socket_handler.h"
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

namespace sockets
{


   ::index g_iSocketThread = 0;


   socket_thread::socket_thread()
   {

      ::infomration(::as_string(g_iSocketThread++) + " - memory_new socket_thread\n");

   }


   //void socket_thread::transfer(socket_map::association * passociation, socket_map * psocketmap)
   //{

   //   //auto estatus = initialize(passociation->m_psocket);

   //   initialize(passociation->m_psocket);

   //   //if (!estatus)
   //   //{

   //   //   return estatus;

   //   //}

   //   m_psockethandler = ::transfer(__create_new < socket_handler > ());

   //   //psocket->m_psockethandler.release();

   //   passociation->m_psocket->m_psocketthread = this;

   //   //m_psockethandler->SetSlave();

   //   //m_psocket->SetSlaveHandler(m_psockethandler);

   //   m_psockethandler->transfer(passociation, psocketmap);

   //   branch();

   //   //return estatus;

   //}


   socket_thread::~socket_thread()
   {

      ::infomration("--->>>>>socket_thread::~SOCKET_thread\n");

   }


   //void socket_thread::init_thread()
   //{

   //   if (!::thread::init_thread())
   //   {

   //      return false;

   //   }


   //   return true;

   //}


   //void socket_thread::term_thread()
   //{

   //   ::thread::term_thread();

   //}


#ifdef _DEBUG


   ::i64 socket_thread::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
   {

      return ::task::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }


   ::i64 socket_thread::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
   {

      return ::task::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }


#endif

   base_socket* socket_thread::get_socket() const
   {
      if (::is_null(m_psockethandler))
      {

         return nullptr;

      }

      return nullptr;

      ////auto passociation = m_psockethandler->m_socketmap.m_passociationHead;

      ////if (::is_null(passociation))
      ////{

      ////   return nullptr;

      ////}

      //return passociation->m_psocket;

   }

   void socket_thread::run()
   {

      //if (phandler.get() != m_psocket->m_psockethandler.get())
      //{

      //   //   ::infomration("");

      //   //}
      //   //else
      //   //{

      //   phandler->add(m_psocket);

      //}

      try
      {

         while (task_get_run() && m_psockethandler->get_count())
         {

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

      //m_psocket->m_psocketthread.release();

      //m_psocket->destroy();

      m_psockethandler->destroy();

      destroy();

      //return ::success;

   }


} // namespace sockets



