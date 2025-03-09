// Created by camilo on 2025-03-08 23:53 <3ThomasBorregaardSorensen!!
#pragma once


#include "aura/graphics/image/image.h"


namespace image
{


   class transformation :
      virtual public ::particle
   {
   public:


      virtual void transform(::image::image * pimage) = 0;


   };


} // namespace image




