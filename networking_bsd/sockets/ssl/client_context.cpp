#include "platform.h"
#include "client_context.h"
#if defined(WINDOWS_DESKTOP)
#include <wincrypt.h>
#pragma comment(lib, "Crypt32.lib")
#elif defined(MACOS)
#include <CoreFoundation/CoreFoundation.h>
#include <Security/SecCertificate.h>
#include <Security/SecTrust.h>
#endif


namespace sockets_bsd
{

#if defined(WINDOWS_DESKTOP)
   static void load_windows_root_certificates(SSL_CTX * psslcontext)
   {

      if (!psslcontext)
      {

         return;

      }

      X509_STORE * pstore = SSL_CTX_get_cert_store(psslcontext);

      if (!pstore)
      {

         return;

      }

      HCERTSTORE hStore = CertOpenSystemStoreW(0, L"ROOT");

      if (!hStore)
      {

         return;

      }

      PCCERT_CONTEXT pCertContext = nullptr;

      while ((pCertContext = CertEnumCertificatesInStore(hStore, pCertContext)) != nullptr)
      {

         const unsigned char * pEncoded = pCertContext->pbCertEncoded;

         X509 * pX509 = d2i_X509(nullptr, &pEncoded, (long)pCertContext->cbCertEncoded);

         if (pX509)
         {

            X509_STORE_add_cert(pstore, pX509);

            X509_free(pX509);

         }

      }

      // Clear any duplicate-cert errors pushed by X509_STORE_add_cert.
      ERR_clear_error();

      CertCloseStore(hStore, 0);

   }
#elif defined(MACOS)
   static void add_macos_certificates_to_store(X509_STORE * pstore, CFArrayRef cfCerts)
   {

      if (!pstore || !cfCerts)
      {

         return;

      }

      CFIndex count = CFArrayGetCount(cfCerts);

      for (CFIndex i = 0; i < count; i++)
      {

         SecCertificateRef certRef = (SecCertificateRef)CFArrayGetValueAtIndex(cfCerts, i);

         if (!certRef)
         {

            continue;

         }

         CFDataRef cfDer = SecCertificateCopyData(certRef);

         if (!cfDer)
         {

            continue;

         }

         const unsigned char * pEncoded = CFDataGetBytePtr(cfDer);

         long length = (long)CFDataGetLength(cfDer);

         if (pEncoded && length > 0)
         {

            X509 * pX509 = d2i_X509(nullptr, &pEncoded, length);

            if (pX509)
            {

               X509_STORE_add_cert(pstore, pX509);

               X509_free(pX509);

            }

         }

         CFRelease(cfDer);

      }

   }


   static void load_macos_root_certificates(SSL_CTX * psslcontext)
   {

      if (!psslcontext)
      {

         return;

      }

      X509_STORE * pstore = SSL_CTX_get_cert_store(psslcontext);

      if (!pstore)
      {

         return;

      }

      CFArrayRef cfAnchors = nullptr;

      if (SecTrustCopyAnchorCertificates(&cfAnchors) == errSecSuccess && cfAnchors != nullptr)
      {

         add_macos_certificates_to_store(pstore, cfAnchors);

         CFRelease(cfAnchors);

      }

      // Clear any duplicate-cert errors pushed by X509_STORE_add_cert.
      ERR_clear_error();

   }
#endif


   ssl_client_context::ssl_client_context(const SSL_METHOD * pmethod)
   {

      defer_create_synchronization();

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


   void ssl_client_context::set_context(const ::scoped_string & scopedstrContext)
   {

      __UNREFERENCED_PARAMETER(scopedstrContext);

   }

   void ssl_client_context::set_context(const ::scoped_string & scopedstrFontopus, const ::scoped_string & scopedstrSessId)
   {

      __UNREFERENCED_PARAMETER(scopedstrFontopus);

      __UNREFERENCED_PARAMETER(scopedstrSessId);

   }


   void ssl_client_context::InitializeContext(const SSL_METHOD *meth_in)
   {

      free_ssl_client_context();
      
      const SSL_METHOD *meth = meth_in;

if(::is_null(meth))
{

#if OPENSSL_VERSION_NUMBER >= 0x10100000L

meth = TLS_client_method();

#else

meth = SSLv23_client_method();

#endif

}
      
//       != nullptr ? meth_in : TLS_client_method();

      m_psslcontext = SSL_CTX_new(meth);

      ::i8 buf[255];

      ulong err = ERR_get_error();

      ERR_error_string(err, buf);

      if (m_psslcontext)
      {

         SSL_CTX_set_mode(m_psslcontext, SSL_MODE_AUTO_RETRY | SSL_MODE_RELEASE_BUFFERS);

         SSL_CTX_set_options(m_psslcontext, SSL_OP_NO_COMPRESSION | SSL_CTX_get_options(m_psslcontext));

         SSL_CTX_set_default_verify_paths(m_psslcontext);

#if defined(WINDOWS_DESKTOP)
         load_windows_root_certificates(m_psslcontext);
#elif defined(MACOS)
         load_macos_root_certificates(m_psslcontext);
#endif

      }

   }


} // namespace sockets_bsd



