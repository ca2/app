// Created by camilo on 2022-10-23 09:29 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "rectangle.h"

#if 0

#include "acme/platform/uint32_muldiv.h"
#include "acme/platform/uint64_muldiv.h"


CLASS_DECL_ACME i32_rectangle & muldiv(i32_rectangle & rectangle, ::i32 numerator, ::i32 denominator)
{

   rectangle.left    = ::MulDiv32(rectangle.left     , numerator, denominator);
   rectangle.top     = ::MulDiv32(rectangle.top      , numerator, denominator);
   rectangle.right   = ::MulDiv32(rectangle.right    , numerator, denominator);
   rectangle.bottom  = ::MulDiv32(rectangle.bottom   , numerator, denominator);

   return rectangle;

}



CLASS_DECL_ACME i64_rectangle & muldiv(i64_rectangle & rectangle, ::i64 numerator, ::i64 denominator)
{

   rectangle.left    = ::uint64_muldiv(rectangle.left     , (::i32)numerator, denominator);
   rectangle.top     = ::uint64_muldiv(rectangle.top      , (::i32)numerator, denominator);
   rectangle.right   = ::uint64_muldiv(rectangle.right    , (::i32)numerator, denominator);
   rectangle.bottom  = ::uint64_muldiv(rectangle.bottom   , (::i32)numerator, denominator);

   return rectangle;

}




#endif



   
   
