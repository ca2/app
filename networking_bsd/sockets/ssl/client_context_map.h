#pragma once


namespace sockets_bsd
{


   class CLASS_DECL_NETWORKING_BSD ssl_client_context_map :
      virtual public object
   {
   public:


      string_map < map < const SSL_METHOD *, __pointer(ssl_client_context) > > m_map;


      ssl_client_context_map();
      virtual ~ssl_client_context_map();


      __pointer(ssl_client_context) get_context(string strContext, const SSL_METHOD * pmethod);


   };


} // namespace sockets_bsd



