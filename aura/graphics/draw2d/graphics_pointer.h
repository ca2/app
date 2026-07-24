// Created by camilo on 2026-07-22 19:24 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
#pragma once


#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/draw2d/graphics_pointer.h"


namespace draw2d
{


   class CLASS_DECL_AURA graphics_pointer :
      public ::pointer <  ::draw2d::graphics  >
   {
   public:

      
      using BASE_POINTER = ::pointer <  ::draw2d::graphics  >;


      using BASE_POINTER::BASE_POINTER;


      graphics_pointer(const ::draw2d::graphics_pointer & p);
      graphics_pointer(::pointer<  ::draw2d::graphics  > && p);
      ~graphics_pointer();


      graphics_pointer &operator=(::pointer <  ::draw2d::graphics  > && p);
      graphics_pointer &operator=(const ::pointer <  ::draw2d::graphics  > &p);



   };


} // namespace draw2d








