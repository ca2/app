#pragma once


#include "picture.h"
#include "aura/user/user/interaction.h"


namespace user
{


   class CLASS_DECL_BASE picture_interaction :
      virtual public ::user::picture,
      virtual public ::user::interaction
   {
   public:


      picture_interaction();
      ~picture_interaction() override;


      using ::user::interaction::hit_test;
      virtual ::item_pointer parent_client_hit_test(const ::point_i32 & point, ::user::e_zorder ezorder) override;

      using ::user::interaction::on_hit_test;
      virtual ::item_pointer parent_client_on_hit_test(const ::point_i32 & point, ::user::e_zorder ezorder) override;

      virtual ::size_f64 get_request_size() override;


   };


} // namespace user



