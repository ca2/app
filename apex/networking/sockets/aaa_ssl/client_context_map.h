#pragma once



namespace sockets
{


   class CLASS_DECL_APEX ssl_client_context_map :
      virtual public object
   {
   public:


//      string_map < map < const SSL_METHOD *, __pointer(ssl_client_context) > > m_map;


      ssl_client_context_map();
      ~ssl_client_context_map() override;


//      __pointer(ssl_client_context) get_context(string strContext, const SSL_METHOD * pmethod);


   };


} // namespace sockets



