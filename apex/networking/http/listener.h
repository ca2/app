#pragma once


namespace http
{


   class CLASS_DECL_APEX listener:
      virtual public object
   {
   public:


      void on_http_complete(::sockets::http_socket * psocket,const void & estatus);


   };
   

} // namespace sockets





