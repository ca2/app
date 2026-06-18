//
// Created by camilo on 2026-05-27 05:03 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
//
#pragma once


#include "acme/prototype/geometry2d/angle.h"


namespace nano
{


   namespace graphics
   {


      class CLASS_DECL_ACME path :
         virtual public ::particle
      {
      public:


         path();
         ~path() override;

         
         virtual void add_arc(::f64 x, ::f64 y, ::f64 w, ::f64 h, const ::f64_angle & angleStart, const ::f64_angle & angleSweep);

         virtual void close_figure();

      };


   } // namespace graphics


} // namespace nano



