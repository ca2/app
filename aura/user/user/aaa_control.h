// Recreated by camilo on 2023-06-28 14:39 <3ThomasBorregaardSorensen!!
#pragma once


#include "interaction.h"


namespace user
{


   class CLASS_DECL_AURA control :
      virtual public ::user::interaction
   {
   public:





      control();
      ~control() override;


      void user_control_construct();



      void on_perform_top_down_layout(::draw2d::graphics_pointer & pgraphics) override;


   };


} // namespace user



