#pragma once


#pragma once


namespace user
{


   class CLASS_DECL_AURA callback :
      virtual public ::object
   {
   public:


      callback();
      virtual ~callback();


      virtual void on_control_event(::user::control_event* pevent);

      



   };


} // namespace user




