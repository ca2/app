#include "framework.h" 
#include "base_socket_handler.h"


namespace sockets
{

   ::interlocked_count g_iSocketHandlerSerial;

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
   //   fatal() <<"OnRead: data on hibernating socket";
   //   SetCloseAndDelete();
   //   SetLost();
   //}

   //void base_socket_handler::pool_socket::OnOptions(int, int, int, socket_id)
   //{

   //}


   base_socket_handler::base_socket_handler() 
   {

      m_iSocketHandlerSerial = g_iSocketHandlerSerial++;

      //m_p2 = nullptr;

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


   ::tracer * base_socket_handler::tracer() const
   {

      return (::tracer *) (const ::tracer *) this;

   }


   ::string base_socket_handler::trace_prefix() const
   {

      auto strTaskName = ::current_task_name();

      ::string str;

      str.formatf("%s skthdlr %" PRIdPTR, strTaskName.c_str(), m_iSocketHandlerSerial);

      return str;

   }


   void base_socket_handler::add(::sockets::base_socket * psocket)
   {
      
      
   }
   
   //void base_socket_handler::__tracef(e_trace_category ecategory, enum_trace_level elevel, const ::scoped_string & scopedstrFunction, const ::scoped_string & scopedstrFile, int iLine, base_socket * psocket, const ::scoped_string & scopedstrContext, int iError, const ::scoped_string & scopedstrMessage)
   //{

   //   psocket->__tracef(ecategory, elevel, pszFunction, pszFile, iLine, log_this, strContext, iError, strMessage);

   //}


} // namespace sockets




