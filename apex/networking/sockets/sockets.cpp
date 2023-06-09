#include "framework.h"
#include "sockets.h"
#include "acme/parallelization/task_flag.h"


#ifdef PARALLELIZATION_PTHREAD


#include "acme/operating_system/ansi/_pthread.h"


#endif

//namespace net
//{
//
//   extern class address_department * g_paddressdepartment;
//
//}

namespace sockets
{


   sockets::sockets()
   {

      //::net::g_paddressdepartment = nullptr;

      //m_psslinit = nullptr;

      //m_pajpaxissocketinit    = nullptr;

   }


   sockets::~sockets()
   {

      //::acme::del(::net::g_paddressdepartment);
      //::acme::del(m_psslinit);

      //::acme::del(m_pajpaxissocketinit);

   }


   void sockets::initialize(::particle * pparticle)
   {

      //auto estatus = sockets_base::initialize(pparticle);

      object::initialize(pparticle);

      //if (!estatus)
      //{

      //   return estatus;

      //}

//      auto paddressdepartment = pparticle->__create<class ::networking::networking>();
//
//      paddressdepartment->increment_reference_count();
//
//      ::net::g_paddressdepartment = paddressdepartment;
//
//      generate_random_bytes(m_baTicketKey, sizeof(m_baTicketKey));
//
      //m_psslinit = __create<::sockets::SSLInitializer>();
//
//      //estatus = __construct_new(m_pnet);
//
//      __construct_new(m_pnet);
//
//      if (!m_pnet)
//      {
//
//         m_iErrorCode = -1;
//
//         //return error_failed;
//
//         return;
//
//      }
//
//      //if (!m_pnet->initialize(this))
//      m_pnet->initialize(this);
//      /*{
//
//         return error_failed;
//
//      }*/
//
//      //if (!::acme::department::initialize())
//      //{
//
//      //   return error_failed;
//
//      //}
//
////      try
////      {
////
////#ifdef WINDOWS
////         __construct(m_pportforward);
////#endif
////
////      }
////      catch (...)
////      {
////
////      }
//
//
//      //m_pajpaxissocketinit = memory_new AjpBaseSocket::Initializer;
//
//      m_countHttpPostBoundary = 0;
//
//      // return ::success;

   }


   void sockets::destroy()
   {

      ::object::destroy();

      bool bOk = true;

//      if (m_pnet)
//      {
//
//         //try
//         //{
//
//         //   //if (!m_pnet->gudo_set())
//
//         //   //m_pnet->gudo_set()
//         //   //{
//
//         //   //   m_iErrorCode = -87;
//
//         //   //}
//
//         //}
//         //catch (...)
//         //{
//
//         //   m_iErrorCode = -87;
//
//         //}
//
//      }
//
//#ifdef WINDOWS
//
//      try
//      {
//
//         if(m_pportforward.is_set())
//         {
//
//            m_pportforward.release();
//
//         }
//
//      }
//      catch(...)
//      {
//
//         bOk = false;
//
//      }
//
//      try
//      {
//         
//         m_pportforward.release();
//
//      }
//      catch(...)
//      {
//
//      }
//
//#endif

      //if (m_pnet)
      //{

      //   try
      //   {

      //      m_pnet->destroy();

      //   }
      //   catch (...)
      //   {

      //      m_iErrorCode = -87;

      //   }

      //   try
      //   {

      //      m_pnet.release();

      //   }
      //   catch (...)
      //   {

      //      m_iErrorCode = -86;

      //   }

      //}

      /////::acme::del(m_pajpaxissocketinit);

      ////return ::success;

   }


   ::networking::networking * sockets::networking()
   {

      return m_pnetworking;

   }


   //string sockets::get_http_post_boundary()
   //{

   //   auto psystem = acmesystem()->m_papexsystem;

   //   single_lock lock(m_pmutexHttpPostBoundary, true);

   //   string strBoundary = "----";

   //   for (int i = 0; i < 12; i++)
   //   {

   //      char c = m_countHttpPostBoundary++ % 128;

   //      while (!character_isalnum((unsigned char)c))
   //      {

   //         c = m_countHttpPostBoundary++ % 128;

   //      }

   //      strBoundary += c;

   //   }

   //   strBoundary += "__" + as_string(m_countHttpPostBoundary++);

   //   return strBoundary;

   //}


   ::pointer<::networking::address>sockets::create_address(const ::string & strHostname)
   {

      return nullptr;

    }



   //sockets_base::sockets_base()
   //{

   //   m_iErrorCode = -1;

   //}


   //sockets_base::~sockets_base()
   //{



   //}


   //void sockets_base::initialize(::particle * pparticle)
   //{

   //   //auto estatus = object::initialize(pparticle);

   //   object::initialize(pparticle);

   //   //if (!estatus)
   //   //{

   //   //   return estatus;

   //   //}

   //   //return ::success;

   //}


   //void sockets_base::destroy()
   //{

   //   ::object::destroy();

   //   //return ::success;

   //}


} // namespace sockets





///* Resolve DNS host entry. */
//string ip_reverse(string str)
//{
//
//#if defined(UNIVERSAL_WINDOWS) || defined(LINUX) || defined(ANDROID) || defined(__APPLE__) || defined(FREEBSD)
//
//   return c_gethostbyname(str);
//
//#else
//
//   hostent * pent = gethostbyname(str);
//
//   if (pent == nullptr)
//   {
//
//      return "";
//
//   }
//
//   return pent->h_name;
//
//#endif
//
//}




//#if defined(UNIVERSAL_WINDOWS)
//
//
//#include <openssl/ssl.h>
//
//
////#if !defined(UNIVERSAL_WINDOWS)
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


CLASS_DECL_APEX bool thread_has_sockets() 
{
   
   return task_flag().is_set(e_task_flag_using_sockets); 

}





