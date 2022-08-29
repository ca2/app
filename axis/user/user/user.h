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


   };


} // namespace axis



