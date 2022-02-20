#pragma once


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
      virtual ::item_pointer hit_test(const ::point_i32 & point) override;

      using ::user::interaction::on_hit_test;
      virtual ::item_pointer on_hit_test(const ::point_i32 & point) override;

      virtual ::size_f64 get_request_size() override;


   };


} // namespace user



