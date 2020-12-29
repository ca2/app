#pragma once


namespace axis
{


   class CLASS_DECL_AXIS user :
      virtual public ::user::user
   {
   public:

      


      user();
      virtual ~user();


      virtual ::e_status init() override;
      virtual void term() override;


      virtual ::user::style* get_user_style() override;


   };


} // namespace axis



