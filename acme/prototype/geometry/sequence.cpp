// Created by camilo on 2026-07-29 08:29 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
#include "framework.h"
#include "sequence.h"
#include "acme/prototype/geometry2d/size.h"


SELF_TEST(main, i32_size_ceil_and_floor_transform_each)
{

   ::i32_size sizeControl{010, 75 };

   ::i32_size sizeTarget1;

   sizeTarget1.set_size(ceil(sizeControl));

   ::i32_size sizeTarget2;

   sizeTarget2.set_size(floor(sizeControl));

   return ::success;

}



