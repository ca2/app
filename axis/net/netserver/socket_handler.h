#pragma once


namespace netserver
{


   class CLASS_DECL_AXIS socket_handler :
      virtual public ::sockets::socket_handler
   {
   public:


      socket_handler(::object * pobject, ::aura::log * plogger = nullptr);
      virtual ~socket_handler();


   };


} // namespace netserver


