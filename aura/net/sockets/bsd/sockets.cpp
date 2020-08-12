#include "framework.h"
#include "aura/net/sockets/_.h"


namespace sockets
{


   sockets::sockets()
   {

      m_psslinit = nullptr;

      m_pajpaxissocketinit    = nullptr;

   }


   sockets::~sockets()
   {

      m_spnet.release();

      m_spportforward.release();

      ::aura::del(m_psslinit);

      ::aura::del(m_pajpaxissocketinit);

   }


   ::estatus sockets::initialize(::object * pobjectContext)
   {

      auto estatus = sockets_base::initialize(pobjectContext);

      if (!estatus)
      {

         return estatus;

      }

      System.math().random_bytes(m_baTicketKey, sizeof(m_baTicketKey));


      m_psslinit = new ::sockets::SSLInitializer(get_context_object());

      m_spnet = __create_new<::sockets::net>();
      //m_spnet.create(this);

      if(m_spnet.is_null())
      {

         m_iErrorCode = -1986;

         return error_failed;

      }


      if (!m_spnet->initialize(this))
      {
         return error_failed;

      }

      //if (!::aura::department::initialize())
      //{

      //   return error_failed;

      //}


      m_spportforward.create();

      m_pajpaxissocketinit = new AjpBaseSocket::Initializer;

      m_countHttpPostBoundary = 0;

      return ::success;

   }

   
   void sockets::finalize()
   {

      bool bOk = true;

      if (m_spnet)
      {

         try
         {

            if (!m_spnet->gudo_set())
            {

               m_iErrorCode = -87;

            }

         }
         catch (...)
         {

            m_iErrorCode = -87;

         }

      }

      try
      {

         if(m_spportforward.is_set())
         {

            m_spportforward.release();

         }

      }
      catch(...)
      {

         bOk = false;

      }

      try
      {
         m_spportforward.release();
      }
      catch(...)
      {
      }



      if (m_spnet)
      {


         try
         {

            m_spnet->finalize();

         }
         catch (...)
         {

            m_iErrorCode = -87;

         }

         try
         {

            m_spnet.release();

         }
         catch (...)
         {

            m_iErrorCode = -86;

         }

      }

      ::aura::del(m_pajpaxissocketinit);

   }


   ::sockets::net & sockets::net()
   {

      return *m_spnet;

   }
   

} // namespace karaoke





/* Resolve DNS host entry. */
string ip_reverse(string str)
{

#if defined(_UWP) || defined(LINUX) || defined(ANDROID) || defined(__APPLE__)

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




#if defined(_UWP)


#include <openssl/ssl.h>


extern "C"
CLASS_DECL_AURA const SSL_METHOD * TLS_client_method()
{

   return TLSv1_2_client_method();

}


extern "C"
CLASS_DECL_AURA const SSL_METHOD * TLS_server_method()
{

   return TLSv1_2_server_method();

}


#endif



