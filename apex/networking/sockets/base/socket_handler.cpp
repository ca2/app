#include "framework.h" 
#include "socket_handler.h"


namespace sockets
{


   //base_socket_handler::pool_socket::pool_socket(base_socket * src)
   //{

   //   CopyConnection(src);

   //   SetIsClient();

   //}


   //base_socket_handler::pool_socket::~pool_socket()
   //{

   //}


   //void base_socket_handler::pool_socket::OnRead()
   //{
   //   FATAL("OnRead: data on hibernating socket");
   //   SetCloseAndDelete();
   //   SetLost();
   //}

   //void base_socket_handler::pool_socket::OnOptions(int, int, int, socket_id)
   //{

   //}


   base_socket_handler::base_socket_handler() 
   {

      m_p2 = nullptr;

      //m_plogger = plogger;

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

   
   void base_socket_handler::add(const socket_pointer& psocket)
   {
      
      
   }
   
   //void base_socket_handler::__tracef(e_trace_category ecategory, enum_trace_level elevel, const scoped_string & strFunction, const scoped_string & strFile, int iLine, base_socket * psocket, const ::string & strContext, i32 iError, const ::string & strMessage)
   //{

   //   psocket->__tracef(ecategory, elevel, pszFunction, pszFile, iLine, log_this, strContext, iError, strMessage);

   //}


} // namespace sockets




