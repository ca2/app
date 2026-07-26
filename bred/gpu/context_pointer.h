// Created by camilo on 2026-07-23 23:17 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
#pragma once


#include "bred/gpu/context.h"


namespace gpu
{


   class CLASS_DECL_BRED context_pointer :
      public ::pointer <  ::gpu::context  >
   {
   public:

      using BASE_POINTER = ::pointer <  ::gpu::context  >;

      using BASE_POINTER::BASE_POINTER;
      using BASE_POINTER::operator = ;

      context_pointer();
      ~context_pointer();


   };


} // namespace gpu




