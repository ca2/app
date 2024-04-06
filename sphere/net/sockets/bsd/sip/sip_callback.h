#pragma once


namespace sockets
{


   class sip_socket;


   class CLASS_DECL_AURA sip_callback :
      virtual public axis_object
   {
   public:

      void on_sip_event(sip_socket * psocket, sip_event * pevent);
   };


} // namespace sockets



