#include "framework.h"
#include "client_context.h"


namespace sockets_bsd
{


   ssl_client_context::ssl_client_context(const SSL_METHOD * pmethod)
   {

      defer_create_mutex();

      m_psslsession = nullptr;
      m_psslcontext = nullptr;

      if(pmethod == nullptr)
         pmethod = SSLv23_method();

      m_psslmethod = pmethod;

      InitializeContext(pmethod);

      m_iSslRetry = 0;

   }


   ssl_client_context::~ssl_client_context()
   {

      free_ssl_client_context();

   }


   void ssl_client_context::free_ssl_client_context()
   {

      if (m_psslsession != nullptr)
      {

         SSL_SESSION_free(m_psslsession);

         m_psslsession = nullptr;

      }

      if (m_psslcontext != nullptr)
      {

         SSL_CTX_free(m_psslcontext);

         m_psslcontext = nullptr;

      }

      m_psslmethod = nullptr;


   }


   void ssl_client_context::set_context(const char * pszContext)
   {

      __UNREFERENCED_PARAMETER(pszContext);

   }

   void ssl_client_context::set_context(const char * pszFontopus, const char * pszSessId)
   {

      __UNREFERENCED_PARAMETER(pszFontopus);

      __UNREFERENCED_PARAMETER(pszSessId);

   }


   void ssl_client_context::InitializeContext(const SSL_METHOD *meth_in)
   {

      free_ssl_client_context();

      const SSL_METHOD *meth = meth_in != nullptr ? meth_in : TLS_client_method();

      m_psslcontext = SSL_CTX_new(meth);

      char buf[255];

      unsigned long err = ERR_get_error();

      ERR_error_string(err, buf);

      SSL_CTX_set_mode(m_psslcontext, SSL_MODE_AUTO_RETRY | SSL_MODE_RELEASE_BUFFERS);

      SSL_CTX_set_options(m_psslcontext, SSL_OP_NO_COMPRESSION | SSL_CTX_get_options(m_psslcontext));

   }


} // namespace sockets_bsd



