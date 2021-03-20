#include "framework.h"
#include "axis/user/_user.h"


namespace axis
{


   user::user()
   {

      m_paxisuser = this;

   }


   user::~user()
   {


   }

   ::e_status user::init()
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

      return m_puserstyle;

   }


} // namespace axis



