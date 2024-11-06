// Created by camilo on 2022-10-23 09:29 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "rectangle.h"

#if 0

#include "acme/platform/uint32_muldiv.h"
#include "acme/platform/uint64_muldiv.h"


CLASS_DECL_ACME rectangle_i32 & muldiv(rectangle_i32 & rectangle, int numerator, int denominator)
{

   rectangle.left()    = ::MulDiv32(rectangle.left()     , numerator, denominator);
   rectangle.top()     = ::MulDiv32(rectangle.top()      , numerator, denominator);
   rectangle.right()   = ::MulDiv32(rectangle.right()    , numerator, denominator);
   rectangle.bottom()  = ::MulDiv32(rectangle.bottom()   , numerator, denominator);

   return rectangle;

}



CLASS_DECL_ACME rectangle_i64 & muldiv(rectangle_i64 & rectangle, ::i64 numerator, ::i64 denominator)
{

   rectangle.left()    = ::uint64_muldiv(rectangle.left()     , (int)numerator, denominator);
   rectangle.top()     = ::uint64_muldiv(rectangle.top()      , (int)numerator, denominator);
   rectangle.right()   = ::uint64_muldiv(rectangle.right()    , (int)numerator, denominator);
   rectangle.bottom()  = ::uint64_muldiv(rectangle.bottom()   , (int)numerator, denominator);

   return rectangle;

}




#endif



   
   
