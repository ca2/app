// From _component.h (::collection::index include file) by camilo 2022-08-27 00:32 <3ThomasBorregaardSorensen!!
#pragma once





namespace user
{


   class CLASS_DECL_AURA alpha_source :
      virtual public ::particle
   {
   public:


      virtual double get_alpha(::user::interaction * puiTarget);
      virtual void on_alpha_target_initial_frame_position();


   };


} // namespace user



