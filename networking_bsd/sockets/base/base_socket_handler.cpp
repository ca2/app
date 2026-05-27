#include "framework.h" 
#include "base_socket_handler.h"
#include "acme/exception/interface_only.h"


namespace sockets_bsd
{


   base_socket_handler::pool_socket::pool_socket(::sockets::base_socket * src)
   {

      CopyConnection(src);

      SetIsClient();

   }


   base_socket_handler::pool_socket::~pool_socket()
   {

   }


   void base_socket_handler::pool_socket::OnRead()
   {
      fatal() <<"OnRead: data on hibernating socket";
      SetCloseAndDelete();
      SetLost();
   }

   void base_socket_handler::pool_socket::OnOptions(::i32, ::i32, ::i32, SOCKET)
   {

   }


   base_socket_handler::base_socket_handler() 
   {

      ///m_plogger = plogger;

     /* if (plogger == nullptr)
      {

         ::application* papp = ::get_app(pparticle);

         if (psystem != nullptr)
         {

            m_plogger = &psystem->log();

         }

      }*/

   }

   base_socket_handler::~base_socket_handler()
   {

   }


   bool base_socket_handler::socket_get_run() const
   {

      return ((base_socket_handler *)this)->get_count() > 0 && ::task_get_run();

   }

   void base_socket_handler::set_logger(::apex::log * plogger)
   {

      m_plogger = plogger;

   }

   
   //void base_socket_handler::__tracef(e_trace_category ecategory, enum_trace_level elevel, const ::scoped_string & scopedstrFunction, const ::scoped_string & scopedstrFile, ::i32 iLine, base_socket * psocket, const ::scoped_string & scopedstrContext, ::i32 iError, const ::scoped_string & scopedstrMessage)
   //{

   //   psocket->__tracef(ecategory, elevel, pszFunction, pszFile, iLine, log_this, strContext, iError, strMessage);

   //}


   ::i32 base_socket_handler::TriggerID(::sockets::base_socket * src)
   {

      throw interface_only();

      return -1;

   }


} // namespace sockets




