#pragma once


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


      //::user::style* user_style() override;


   };


} // namespace axis



