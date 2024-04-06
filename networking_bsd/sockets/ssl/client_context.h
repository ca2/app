#pragma once


typedef struct ssl_st SSL;
typedef struct ssl_ctx_st SSL_CTX;
typedef struct ssl_method_st SSL_METHOD;
typedef struct ssl_session_st SSL_SESSION;
////#include "acme/primitive/primitive/object.h"



namespace sockets_bsd
{


   class CLASS_DECL_NETWORKING_BSD ssl_client_context :
      virtual public ::object
   {
   public:


      SSL_CTX *            m_psslcontext;
      SSL_SESSION *        m_psslsession;
      const SSL_METHOD *   m_psslmethod;
      i32                  m_iSslRetry;


      ssl_client_context(const SSL_METHOD * pmethod = nullptr);
      virtual ~ssl_client_context();


      void set_context(const ::scoped_string & scopedstrContext);
      void set_context(const ::scoped_string & scopedstrFontopus, const ::scoped_string & scopedstrSessId);


      void InitializeContext(const SSL_METHOD *meth_in);

      void free_ssl_client_context();

   };



} // namespace sockets_bsd



