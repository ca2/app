//
// Created by camilo on 2024-04-19
//
#include "framework.h"
#include "acme/platform/node.h"
#include "acme/platform/system.h"
#include "acme/user/nano/nano.h"

#if defined(WITH_X11)


namespace acme
{


   void system::x11_async(const ::procedure &procedure)
   {

      node()->x11_async(procedure);

   }


   void system::x11_sync(const ::procedure &procedure)
   {

      node()->x11_sync(procedure);

   }


} // namespace acme


void x11_sync(const ::procedure & procedure)
{

   ::platform::get()->system()->x11_sync(procedure);

}


void x11_async(const ::procedure & procedure)
{

   ::platform::get()->system()->x11_async(procedure);

}


#endif



