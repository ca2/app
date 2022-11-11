#include "framework.h" 
#include "socket_handler.h"
#include "acme/exception/interface_only.h"


namespace sockets_bsd
{


   base_socket_handler::pool_socket::pool_socket(base_socket * src)
   {

      CopyConnection(src);

      SetIsClient();

   }


   base_socket_handler::pool_socket::~pool_socket()
   {

   }


   void base_socket_handler::pool_socket::OnRead()
   {
      FATAL("OnRead: data on hibernating socket");
      SetCloseAndDelete();
      SetLost();
   }

   void base_socket_handler::pool_socket::OnOptions(int, int, int, SOCKET)
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

   
   //void base_socket_handler::__tracef(e_trace_category ecategory, enum_trace_level elevel, const char * pszFunction, const char * pszFile, int iLine, base_socket * psocket, const ::string & strContext, i32 iError, const ::string & strMessage)
   //{

   //   psocket->__tracef(ecategory, elevel, pszFunction, pszFile, iLine, log_this, strContext, iError, strMessage);

   //}


   int base_socket_handler::TriggerID(::sockets::base_socket * src)
   {

      throw interface_only();

      return -1;

   }


} // namespace sockets




