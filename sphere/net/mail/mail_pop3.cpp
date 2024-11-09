#include "framework.h" // from "aura/net/net_sockets.h"
#include "aura/net/net_sockets.h"
#include "pop3_socket.h"
#include "simple_pop3.h"



namespace mail
{


   pop3::pop3(::particle * pparticle) :
      ::object(pparticle)
   {

      m_phandler = __allocate ::sockets::socket_handler(pparticle);

   }


   pop3::~pop3()
   {

   }




   void     pop3::run()
   {

      m_psocket = __allocate pop3_socket(*m_phandler);

      m_psocket->m_ppop3 = this;

      int iPort = 995;

      if(iPort == 995)
      {

         m_psocket->m_bSsl = true;

         m_psocket->EnableSSL();

      }

      m_psocket->open(::networking::address(get_host(), (port_t) iPort));

      m_phandler->add(m_psocket);

      m_phandler->select(240,0);

      while(task_get_run() && m_psocket->m_estate != pop3_socket::state_finished)
      {

         m_phandler->select(240,0);

      }

      m_happeningFinish.set_happening();

      return ::success;

   }





   void pop3::filter_id()
   {
   }


   void pop3::store()
   {
   }


   void pop3::update_lists()
   {
   }


   string pop3::get_user()
   {
      return "";
   }

   string pop3::get_pass()
   {
      return "";
   }

   string pop3::get_host()
   {
      return "";
   }

   string pop3::get_transaction()
   {
      return "STAT";
   }

   void pop3::set_stat_count(int iCount)
   {
      __UNREFERENCED_PARAMETER(iCount);
   }

   void pop3::set_stat_size(int iSize)
   {
      __UNREFERENCED_PARAMETER(iSize);
   }

   void pop3::set_list_size(int iSize)
   {
      __UNREFERENCED_PARAMETER(iSize);
   }

   void pop3::on_finished_transaction()
   {
   }

} // namespace mail
