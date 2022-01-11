#include "framework.h"
#include "apex/networking/sockets/_sockets.h"


namespace sockets
{


   sockets::sockets()
   {

      //m_pajpbasesocketinit    = nullptr;

   }


   sockets::~sockets()
   {


   }


   void sockets::initialize(::object * pobject)
   {

      auto estatus = ::acme::department::initialize(pobject);

      if (!estatus)
      {

         return estatus;

      }

      //::apex::get_system()->math().random_bytes(m_baTicketKey, sizeof(m_baTicketKey));


      //m_psslinit = new ::sockets::SSLInitializer(this);

      m_spnet = __create_new<::sockets::net>();
      //m_spnet.create(this);

      if (m_spnet.is_null())
      {

         m_iErrorCode = -1986;

         return error_failed;

      }


      if (!m_spnet->initialize(this))
      {

         return error_failed;

      }

      //if (!::acme::department::initialize())
      //{

      //   return error_failed;

      //}


      //m_spportforward.create();

      //m_pajpaxissocketinit = new AjpBaseSocket::Initializer;

      m_countHttpPostBoundary = 0;

      return ::success;

   }


   //bool sockets::init1()
   //{

   //   m_spnet = __new(::sockets::net(this));
   //   //m_spnet.create(this);

   //   if(m_spnet.is_null())
   //   {

   //      m_iErrorCode = -1986;

   //      return false;

   //   }


   //   if(!m_spnet->initialize())
   //      return false;

   //   if(get_application()->is_system())
   //   {

   //      /*            ::sockets::SSLInitializer ssl_init(m_psystem);*/

   //      //add_factory_item <::http::memory_file > ();
   //      //add_factory_item < ::sockets::winrt_address  >  (::apex::get_system()->template type_info < ::net::address_base > ());
   //      /*            add_factory_item < ::sockets::ipv4_address  > ();
   //               add_factory_item < ::sockets::ipv6_address  > ();*/

   //      m_pajpbasesocketinit = new AjpBaseSocket::Initializer;
   //   }

   //   m_countHttpPostBoundary = 0;

   //   return true;

   //}


   void sockets::destroy()
   {

      //bool bOk = true;

      //if(get_application()->is_system())
      //{
      //   if(m_pajpbasesocketinit != nullptr)
      //   {
      //      delete m_pajpbasesocketinit;
      //      m_pajpbasesocketinit = nullptr;
      //   }
      //}

      //return bOk;

   }


   //void sockets::http_config_proxy(const char * pszUrl, http_tunnel * psocket)
   //{
   //   __UNREFERENCED_PARAMETER(pszUrl);
   //   //__UNREFERENCED_PARAMETER(psocket);
   //   //__throw(error_not_implemented);
   //   psocket->m_bDirect = true;
   //}


   ::sockets::net & sockets::net()
   {

      return *m_spnet;

   }


} // namespace kar



