//
//  sockets_ssl_context.hpp
//  apex
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 06/01/18.
//
#pragma once


//#include "acme/primitive/primitive/object.h"
//typedef struct ssl_st SSL;
//typedef struct ssl_ctx_st SSL_CTX;
//typedef struct ssl_method_st SSL_METHOD;
//typedef struct ssl_session_st SSL_SESSION;


namespace sockets_bsd
{


   class CLASS_DECL_NETWORKING_BSD ssl_context :
      virtual public ::object
   {
   public:


      int                              m_iSslCtxRetry;

      ::pointer<ssl_client_context>   m_pclientcontext;
      SSL *                            m_ssl; ///< ssl 'socket'
      BIO *                            m_sbio; ///< ssl bio


      ssl_context();
      virtual ~ssl_context();


      void close();


   };


} // namespace sockets_bsd



