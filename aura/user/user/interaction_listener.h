// From aura/user by camilo on 2023-04-06 19:53 <3ThomasBorregaardSorensen!!
// From message_window_listener to interaction_listener by camilo on 2023-04-10 21:05 <3ThomasBorregaardSorensen!!
#pragma once





namespace user
{


   class CLASS_DECL_AURA interaction_listener:
      virtual public ::particle
   {
   public:

      
      virtual void interaction_message_handler(::message::message * pmessage);

      virtual void install_interaction_message_routing(::channel * pchannel);


   };


} // namespace user



