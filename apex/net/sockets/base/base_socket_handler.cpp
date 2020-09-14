#include "framework.h" 
#include "apex/net/sockets/_.h"


namespace sockets
{


   base_socket_handler::pool_socket::pool_socket(base_socket_handler& h, base_socket * src) :
      ::object(h.get_context_application()),
      base_socket(h),
      socket(h)
   {

      CopyConnection(src);

      SetIsClient();

   }


   base_socket_handler::pool_socket::~pool_socket()
   {

   }


   void base_socket_handler::pool_socket::OnRead()
   {
      FATAL(log_this, "OnRead", 0, "data on hibernating socket");
      SetCloseAndDelete();
      SetLost();
   }

   void base_socket_handler::pool_socket::OnOptions(int, int, int, SOCKET)
   {

   }


   base_socket_handler::base_socket_handler(::layered * pobject, ::apex::log * plogger) :
      ::object(pobject)
   {

      if(plogger == nullptr)
      {

         ::apex::application * papp = ::get_context_application(pobject);

         if(papp != nullptr && papp->get_context_system() != nullptr)
         {

            m_splogger = &papp->get_context_system()->log();

         }

      }

   }

   base_socket_handler::~base_socket_handler()
   {

   }


   bool base_socket_handler::socket_get_run() const
   {

      return ((base_socket_handler *)this)->get_count() > 0 && ::thread_get_run();

   }

   void base_socket_handler::set_logger(::apex::log * plogger)
   {

      m_splogger = plogger;

   }

   
   //void base_socket_handler::__tracef(e_trace_category ecategory, e_trace_level elevel, const char * pszFunction, const char * pszFile, int iLine, base_socket * psocket, const string & strContext, i32 iError, const string & strMessage)
   //{

   //   psocket->__tracef(ecategory, elevel, pszFunction, pszFile, iLine, log_this, strContext, iError, strMessage);

   //}


} // namespace sockets




