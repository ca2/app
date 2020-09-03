#pragma once


//#include "sockets_http_get_socket.h"
//#include "sockets_http_post_socket.h"
//#include "sockets_http_put_socket.h"


namespace sockets
{



   class CLASS_DECL_AXIS http_session :
      virtual public http_get_socket,
      virtual public http_post_socket,
      virtual public http_put_socket
   {
   public:


      string                              m_strProtocol;
      bool                                m_bRequestComplete;




      http_session(::sockets::base_socket_handler & phandler, const string & protocol, const string & host);
      ~http_session();



      virtual i64 add_ref(OBJ_REF_DBG_PARAMS)
      {

         return http_client_socket::add_ref(OBJ_REF_DBG_ARGS);

      }


      virtual i64 dec_ref(OBJ_REF_DBG_PARAMS)
      {

         return http_client_socket::dec_ref(OBJ_REF_DBG_ARGS);

      }



      using http_client_socket::request;

      virtual void request(const string & strMethod, const string & pszRequest);
      virtual void request(e_http_method emethod, const string & pszRequest);

      virtual void step();

      virtual void OnHeaderComplete();
      virtual void OnDataComplete();


   };




} // namespace sockets


