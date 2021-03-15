#pragma once


namespace sockets
{


   class CLASS_DECL_AURA sip_event :
      virtual public axis_object
   {
   public:
      enum e_event
      {
         event_invite, 
      };

      e_event     m_eevent;

      sip_event(::context_object * pcontextobject);
   };


} // namespace sockets



