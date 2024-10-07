//
// Created by camilo on 9/26/24.
//
#include "framework.h"
#include "window_base.h"


namespace windowing
{


   window_base::window_base()
   {


   }


   window_base::~window_base()
   {


   }


   void window_base::destroy()
   {

      ::nano::windowing::window::destroy();
      ::channel::destroy();

   }


} // namespace windowing



