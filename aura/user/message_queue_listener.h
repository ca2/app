#pragma once


namespace user
{


   class CLASS_DECL_AURA message_queue_listener:
      virtual public ::object
   {
   public:

      virtual void message_queue_message_handler(::message::message * pmessage) { UNREFERENCED_PARAMETER(pmessage); }

      virtual void install_message_queue_routing(::channel* pchannel) {}

   };


} // namespace user









