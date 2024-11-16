#pragma once


#include "aura/user/user/user.h"


namespace axis
{


   class CLASS_DECL_AXIS user :
      virtual public ::user::user
   {
   public:

      
      user();
      ~user() override;


      void init() override;
      void term() override;

      
      void init1() override;


      //::user::style* user_style() override;

      ::pointer < ::user::interaction > create_menu_button(::user::menu * pusermenu, ::draw2d::graphics_pointer & pgraphics, ::menu::item * pmenuitem) override;
      
   };


} // namespace axis



