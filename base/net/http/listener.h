#pragma once


namespace http
{


   class CLASS_DECL_AURA listener:
      virtual public object
   {
   public:


      void on_http_complete(::sockets::http_socket * psocket,const ::estatus & estatus);


   };
   

} // namespace sockets





