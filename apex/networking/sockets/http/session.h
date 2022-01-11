#pragma once


//#include "sockets_http_get_socket.h"
//#include "sockets_http_post_socket.h"
//#include "sockets_http_put_socket.h"


namespace sockets
{



   class CLASS_DECL_APEX http_session :
      virtual public http_get_socket,
      virtual public http_post_socket,
      virtual public http_put_socket
   {
   public:


      string                              m_strProtocol;
      bool                                m_bRequestComplete;




      http_session(const string & protocol, const string & host);
      ~http_session();



      virtual i64 increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override
      {

         return http_client_socket::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

      }


      virtual i64 decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override
      {

         return http_client_socket::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

      }



      using http_client_socket::request;

      virtual void request(const ::string & strMethod, const string & pszRequest);
      virtual void request(e_http_method emethod, const string & pszRequest);


      virtual void step() override;


      virtual void OnHeaderComplete() override;
      virtual void OnDataComplete() override;


   };




} // namespace sockets


