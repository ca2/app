//
// a recreation(from control_event_listener) by camilo on 28/06/2021 22:23 BRT <3ThomasBS_!!
//
#pragma once


namespace user
{


   class CLASS_DECL_AURA callback :
      virtual public ::subject::manager,
      virtual public ::conversation
   {
   public:


      callback();
      ~callback() override;


      virtual void on_control_event(::user::control_event* pevent);


   };


} // namespace user




