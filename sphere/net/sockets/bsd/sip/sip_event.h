#pragma once


namespace sockets
{


   class CLASS_DECL_AURA sip_event :
      virtual public axis_object
   {
   public:
      enum e_happening
      {
         event_invite, 
      };

      e_happening     m_ehappening;

      sip_event(::particle * pparticle);
   };


} // namespace sockets



