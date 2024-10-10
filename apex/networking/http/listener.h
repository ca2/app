#pragma once


//#include "acme/prototype/prototype/matter.h"


namespace http
{


   class CLASS_DECL_APEX listener:
      virtual public matter
   {
   public:


      void on_http_complete(::sockets::http_socket * psocket,const ::e_status & estatus);


   };
   

} // namespace sockets





