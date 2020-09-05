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

      create_factory < ::user::button >();

      return ::success;

   }

   
   void user::term()
   {

   }


} // namespace axis



