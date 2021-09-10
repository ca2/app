#pragma once


#ifdef WINDOWS_DESKTOP


namespace user
{


   class CLASS_DECL_AURA message_window_listener:
      virtual public ::object
   {
   public:

      virtual void message_window_message_handler(::message::message * pmessage) { __UNREFERENCED_PARAMETER(pmessage); }

      virtual void install_message_window_routing(::channel* pchannel) {}

   };


} // namespace user


#endif




