#pragma once


class CLASS_DECL_ACME oval :
   public ::rectangle_i32
{
public:
   oval() : rectangle_i32() {}
   oval(const ::rectangle_i32& r) : rectangle_i32(r) {}
};


class CLASS_DECL_ACME ovald :
   public ::rectangle_f64
{
public:
   ovald() : rectangle_f64() {}
   ovald(const ::rectangle_f64& r) : rectangle_f64(r) {}

};