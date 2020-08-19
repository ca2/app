//
//  sockets_ssl_context.hpp
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 06/01/18.
//
#pragma once


//typedef struct ssl_st SSL;
//typedef struct ssl_ctx_st SSL_CTX;
//typedef struct ssl_method_st SSL_METHOD;
//typedef struct ssl_session_st SSL_SESSION;


namespace sockets
{


   class CLASS_DECL_AURA ssl_context :
      virtual public ::object
   {
   public:


      int                              m_iSslCtxRetry;

      __pointer(ssl_client_context)    m_pclientcontext;
      SSL *                            m_ssl; ///< ssl 'socket'
      BIO *                            m_sbio; ///< ssl bio


      ssl_context();
      virtual ~ssl_context();


      void close();


   };


} // namespace sockets



