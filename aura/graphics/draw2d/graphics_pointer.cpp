// Created by camilo on 2026-07-22 19:46 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
#include "framework.h"
#include "graphics_pointer.h"


namespace draw2d
{


   graphics_pointer::graphics_pointer(const ::draw2d::graphics_pointer &p) : 
      BASE_POINTER(p)
   {

   }


   graphics_pointer::graphics_pointer(::pointer <  ::draw2d::graphics  > && p): 
      BASE_POINTER(::transfer(p))
   {


   }


   graphics_pointer::~graphics_pointer()
   {

   }


   graphics_pointer &graphics_pointer::operator=(::pointer <  ::draw2d::graphics  > && p)
   {

      BASE_POINTER::operator=(::transfer(p));

      return *this;

   }


   graphics_pointer &graphics_pointer::operator=(const ::pointer<  ::draw2d::graphics  > & p)
   {

      BASE_POINTER::operator=(p);

      return *this;

   }


} // namespace draw2d
