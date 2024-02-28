#include "framework.h"
#include "user.h"
#include "combo_box.h"
#include "list_box.h"
#include "line_layout.h"
#include "aura/user/user/check_box.h"
#include "aura/user/user/button.h"
#include "aura/user/user/still.h"


#ifdef FREEBSD
#include <stdio.h>
#endif


namespace axis
{


   user::user()
   {

      printf("axis::user::user\n");

      m_paxisuser = this;

   }


   user::~user()
   {


   }


   void user::init()
   {

      ::user::user::init();

   }


   void user::init1() 
   {

      ::user::user::init1();

      factory()->add_factory_item <::user::list_box >();
      factory()->add_factory_item <::user::combo_box >();

   }

   
   void user::term()
   {

   }


} // namespace axis



