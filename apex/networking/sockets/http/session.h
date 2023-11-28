#pragma once


#include "get_socket.h"
#include "post_socket.h"
#include "put_socket.h"


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



      virtual i64 increment_reference_count(REFERENCING_DEBUGGING_PARAMETERS) override
      {

         return http_client_socket::increment_reference_count(REFERENCING_DEBUGGING_ARGS);

      }


      virtual i64 decrement_reference_count(REFERENCING_DEBUGGING_PARAMETERS) override
      {

         return http_client_socket::decrement_reference_count(REFERENCING_DEBUGGING_ARGS);

      }



      using http_client_socket::request;

      virtual void request(const ::string & strMethod, const string & pszRequest);
      virtual void request(e_http_method emethod, const string & pszRequest);


      bool step() override;


      virtual void OnHeaderComplete() override;
      virtual void OnDataComplete() override;


   };




} // namespace sockets


