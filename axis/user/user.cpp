#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "axis/user/_user.h"
#endif


namespace axis
{


   user::user()
   {


   }


   user::~user()
   {


   }

   ::estatus user::init()
   {

      if (!::user::user::init())
      {

         return false;

      }

      create_factory <::user::still >();
      create_factory < ::user::button >();
      create_factory < ::user::check_box >();
      create_factory <::user::combo_list >();
      create_factory <::user::combo_box >();

      return ::success;

   }

   
   void user::term()
   {

   }


   ::user::style* user::get_user_style()
   {

      return m_pstyle;

   }


} // namespace axis



