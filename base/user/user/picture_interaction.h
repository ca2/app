#pragma once


namespace user
{


   class CLASS_DECL_BASE picture_interaction :
      virtual public ::user::picture,
      virtual public ::user::interaction
   {
   public:


      picture_interaction();
      virtual ~picture_interaction();

      using ::user::interaction::hit_test;
      virtual void hit_test(::user::item & item, const ::point_i32 & point) override;

      using ::user::interaction::on_hit_test;
      virtual void on_hit_test(::user::item & item) override;

      virtual ::size_f64 get_request_size() override;


   };


} // namespace user



