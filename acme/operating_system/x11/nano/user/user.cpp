//
// Created by camilo on 2024-04-19.
//
#include "framework.h"
#include "user.h"
#include "display.h"


namespace x11
{


   namespace nano
   {


      namespace user
      {


         user::user()
         {


         }


         user::~user()
         {


         }


         void user::x11_sync(const ::procedure & procedure)
         {

            ::x11::nano::user::display::_nano_get_x11_display(this)->display_send(procedure);

         }


         void user::x11_async(const ::procedure & procedure)
         {

            ::x11::nano::user::display::_nano_get_x11_display(this)->display_post(procedure);

         }
      }//namespace user
   }//namespace nano


} // namespace x11



