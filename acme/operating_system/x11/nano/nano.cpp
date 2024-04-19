//
// Created by camilo on 2024-04-19.
//
#include "framework.h"
#include "nano.h"
#include "display.h"


namespace x11
{


   nano::nano()
   {


   }


   nano::~nano()
   {


   }


   void nano::x11_sync(const ::procedure & procedure)
   {

      ::x11::display::get(this)->display_send(procedure);

   }


   void nano::x11_async(const ::procedure & procedure)
   {

      ::x11::display::get(this)->display_post(procedure);

   }


} // namespace x11



