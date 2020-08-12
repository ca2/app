#include "framework.h"


namespace sockets
{


   sockets::sockets(::object * pobject) :
      ::object(pobject),
      ::aura::department(pobject),
      
      m_mutexResolvCache(pobject)
   {

      m_pajpbasesocketinit    = nullptr;

   }


   bool sockets::init1()
   {

      m_spnet = __new(::sockets::net(get_object()));
      //m_spnet.create(this);

      if(m_spnet.is_null())
      {

         m_iErrorCode = -1986;

         return false;

      }


      if(!m_spnet->initialize())
         return false;

      if(Application.is_system())
      {

         /*            ::sockets::SSLInitializer ssl_init(m_psystem);*/

         //create_factory <::http::memory_file > ();
         //create_factory < ::sockets::winrt_address  >  (System.template type_info < ::net::address_base > ());
         /*            create_factory < ::sockets::ipv4_address  > ();
                  create_factory < ::sockets::ipv6_address  > ();*/

         m_pajpbasesocketinit = new AjpBaseSocket::Initializer;
      }

      m_countHttpPostBoundary = 0;

      return true;

   }

   bool sockets::finalize()
   {

      bool bOk = true;

      if(Application.is_system())
      {
         if(m_pajpbasesocketinit != nullptr)
         {
            delete m_pajpbasesocketinit;
            m_pajpbasesocketinit = nullptr;
         }
      }

      return bOk;

   }


   void sockets::http_config_proxy(const char * pszUrl, http_tunnel * psocket)
   {
      UNREFERENCED_PARAMETER(pszUrl);
      //UNREFERENCED_PARAMETER(psocket);
      //__throw(not_implemented());
      psocket->m_bDirect = true;
   }


   ::sockets::net & sockets::net()
   {
      return *m_spnet;
   }

} // namespace kar



