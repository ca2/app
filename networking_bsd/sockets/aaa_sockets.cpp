#include "framework.h"
#include "apex/networking/networking_bsd/_sockets.h"


#ifdef PARALLELIZATION_PTHREAD


#include "acme/operating_system/ansi/_pthread.h"


#endif

namespace net
{

   extern class address_department * g_paddressdepartment;

}

namespace networking_bsd
{


   networking_bsd::networking_bsd()
   {

      ::net::g_paddressdepartment = nullptr;

      m_psslinit = nullptr;

      //m_pajpaxissocketinit    = nullptr;

   }


   networking_bsd::~networking_bsd()
   {

      ::acme::del(::net::g_paddressdepartment);
      //::acme::del(m_psslinit);

      //::acme::del(m_pajpaxissocketinit);

   }


   void networking_bsd::initialize(::object * pobject)
   {

      //auto estatus = sockets_base::initialize(pobject);

      sockets_base::initialize(pobject);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      auto paddressdepartment = pobject->__create_new<class ::networking::address_department>();

      paddressdepartment->increment_reference_count();

      ::net::g_paddressdepartment = paddressdepartment;

      generate_random_bytes(m_baTicketKey, sizeof(m_baTicketKey));

      m_psslinit = __create_new<::networking_bsd::SSLInitializer>();

      //estatus = __construct_new(m_pnet);

      __construct_new(m_pnet);

      if (!m_pnet)
      {

         m_iErrorCode = -1;

         //return error_failed;

         return;

      }

      //if (!m_pnet->initialize(this))
      m_pnet->initialize(this);
      /*{

         return error_failed;

      }*/

      //if (!::acme::department::initialize())
      //{

      //   return error_failed;

      //}

//      try
//      {
//
//#ifdef WINDOWS
//         __construct(m_pportforward);
//#endif
//
//      }
//      catch (...)
//      {
//
//      }


      //m_pajpaxissocketinit = memory_new AjpBaseSocket::Initializer;

      m_countHttpPostBoundary = 0;

      // return ::success;

   }


   void networking_bsd::destroy()
   {

      sockets_base::destroy();

      bool bOk = true;

      if (m_pnet)
      {

         //try
         //{

         //   //if (!m_pnet->gudo_set())

         //   //m_pnet->gudo_set()
         //   //{

         //   //   m_iErrorCode = -87;

         //   //}

         //}
         //catch (...)
         //{

         //   m_iErrorCode = -87;

         //}

      }

#ifdef WINDOWS

      try
      {

         if(m_pportforward.is_set())
         {

            m_pportforward.release();

         }

      }
      catch(...)
      {

         bOk = false;

      }

      try
      {
         
         m_pportforward.release();

      }
      catch(...)
      {

      }

#endif

      if (m_pnet)
      {

         try
         {

            m_pnet->destroy();

         }
         catch (...)
         {

            m_iErrorCode = -87;

         }

         try
         {

            m_pnet.release();

         }
         catch (...)
         {

            m_iErrorCode = -86;

         }

      }

      ///::acme::del(m_pajpaxissocketinit);

      //return ::success;

   }


   ::networking_bsd::net & networking_bsd::net()
   {

      return *m_pnet;

   }


   string networking_bsd::get_http_post_boundary()
   {

      auto psystem = get_system()->m_papexsystem;

      single_lock lock(&m_mutexHttpPostBoundary, true);

      string strBoundary = "----";

      for (int i = 0; i < 12; i++)
      {

         char c = m_countHttpPostBoundary++ % 128;

         while (!ansi_char_is_alphanumeric((unsigned char)c))
         {

            c = m_countHttpPostBoundary++ % 128;

         }

         strBoundary += c;

      }

      strBoundary += "__" + __string(m_countHttpPostBoundary++);

      return strBoundary;

   }


   __pointer(::networking::address) networking_bsd::create_address(const ::string & strHostname)
   {

      return __new(address(strHostname));

   }




} // namespace networking_bsd





/* Resolve DNS host entry. */
string ip_reverse(string str)
{

#if defined(_UWP) || defined(LINUX) || defined(ANDROID) || defined(__APPLE__) || defined(FREEBSD)

   return c_gethostbyname(str);

#else

   hostent * pent = gethostbyname(str);

   if (pent == nullptr)
   {

      return "";

   }

   return pent->h_name;

#endif

}




//#if defined(_UWP)
//
//
//#include <openssl/ssl.h>
//
//
////#if !defined(_UWP)
//
//extern "C"
//CLASS_DECL_APEX const SSL_METHOD * TLS_client_method()
//{
//
//   return TLSv1_2_client_method();
//
//}
//
//
//extern "C"
//CLASS_DECL_APEX const SSL_METHOD * TLS_server_method()
//{
//
//   return TLSv1_2_server_method();
//
//}
//
//
////#endif
//
//
//#endif



