#pragma once


namespace axis
{


   class CLASS_DECL_AXIS user :
      virtual public ::user::user
   {
   public:

      
      user();
      ~user() override;


      ::e_status init() override;
      ::e_status term() override;


      //::user::style* user_style() override;


   };


} // namespace axis



