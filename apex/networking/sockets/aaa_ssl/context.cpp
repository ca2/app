//
//  sockets_ssl_context.cpp
//  apex
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 06/01/18.
//

#include "framework.h"
#include "context.h"
//#include "apex/networking/sockets/_sockets.h"


#ifdef PARALLELIZATION_PTHREAD


#include "acme/operating_system/ansi/_pthread.h"


#endif


//#include <openssl/ssl.h>

namespace sockets
{

   ssl_context::ssl_context():
#ifdef HAVE_OPENSSL
      m_iSslCtxRetry(0)
      //, m_ssl(nullptr)
      //, m_sbio(nullptr)
#endif

   {

   }


   ssl_context::~ssl_context()
   {

      close();

   }

   void ssl_context::close()
   {

//      if (m_ssl)
//      {
//         //#ifdef LINUX
//         //  signal(SIGPIPE, &::sockets::ssl_sigpipe_handle);
//         //#endif
//         /*       struct sigaction m_saPipe;
//                struct sigaction m_saPipeOld;
//                memory_set(&m_saPipe, 0, sizeof(m_saPipe));
//                sigemptyset(&m_saPipe.sa_mask);
//                sigaddset(&m_saPipe.sa_mask, SIGSEGV);
//                m_saPipe.sa_flags = SA_NODEFER | SA_SIGINFO;
//                m_saPipe.sa_sigaction = &::exception_translator::filter_sigpipe;
//                sigaction(SIGPIPE, &m_saPipe, &m_saPipeOld);
//
//                //pthread_t thread;
//                  sigset_t set;
//                  int s;
//         */
//         /* Block SIGQUIT and SIGUSR1; other threads created by main()
//            will inherit a copy of the signal mask. */
//#ifdef LINUX
//         sigset_t set;
//         sigemptyset(&set);
//         sigaddset(&set, SIGPIPE);
//         pthread_sigmask(SIG_BLOCK, &set, nullptr);
//#endif
//         if (SSL_get_shutdown(m_ssl) == 0)
//            SSL_shutdown(m_ssl);
//      }
//
//      if (m_ssl)
//      {
//
//         SSL_free(m_ssl);
//
//         m_ssl = nullptr;
//
//      }
   }

} // namespace sockets

