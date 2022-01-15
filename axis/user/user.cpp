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

   void user::init()
   {

      ::user::user::init();
      //if (!::user::user::init())
      //{

      //   return false;

      //}

      ::factory::add_factory_item <::user::still >();
      ::factory::add_factory_item < ::user::button >();
      ::factory::add_factory_item < ::user::check_box >();
      ::factory::add_factory_item <::user::list_box >();
      ::factory::add_factory_item <::user::combo_box >();

      //return ::success;

   }

   
   void user::term()
   {

      //return ::success;

   }


   //::user::style* user::_user_style()
   //{

   //   return m_puserstyle;

   //}


} // namespace axis



