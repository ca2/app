// Created int_to_string_bases_table.dynamically_generated generator by camilo on 2023-02-02 14:38 <3ThomasBorregaardSorensen!!
#include "framework.h"
//#include <math.h>


::i64 ceil_div(i64 num, i64 den)
{
   i64 quo = num / den;
   if ((num % den) > 0)
      quo++;
   return quo;
}


double tri(double angle)
{

   angle = fmod(angle, 3.1415 * 2.0) * 2.0 / 3.1415;

   if (angle < 1.0)
      return angle;
   else if (angle >= 1.0 && angle < 3.0)
      return 2.0 - angle;
   else
      return angle - 4.0;


}


CLASS_DECL_ACME extern const char log2_LogTable256[256] =
{
#define LT(n) n, n, n, n, n, n, n, n, n, n, n, n, n, n, n, n
   (char)-1, 0, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3,
   LT(4), LT(5), LT(5), LT(6), LT(6), LT(6), LT(6),
   LT(7), LT(7), LT(7), LT(7), LT(7), LT(7), LT(7), LT(7)
};


CLASS_DECL_ACME void simple_generate_random_bytes(void* p, memsize s)
{

   ::u8* puch = (::u8*)p;

   while (s > 0)
   {

      *puch = rand() % 255;

      puch++;

      s--;

   }

}


PFN_GENERATE_RANDOM_BYTES g_pfngeneraterandombytes = &simple_generate_random_bytes;


CLASS_DECL_ACME void set_generate_random_bytes(PFN_GENERATE_RANDOM_BYTES pfngeneraterandombytes)
{

   g_pfngeneraterandombytes = pfngeneraterandombytes;

}


//CLASS_DECL_ACME void generate_random_bytes(void* p, memsize s)
//{
//
//   return g_pfngeneraterandombytes(p, s);
//
//}
//





#include "int_to_string_bases_table.dynamically_generated"


int type_maximum_digits(enum_integer_type etype, int iBase)
{
   if (iBase < 2)
   {

      throw ::exception(error_bad_argument, "base should be greater or equal 2");

   }
   else if (iBase > 36)
   {

      throw ::exception(error_bad_argument, "base should be lesser than or equal 36");

   }
   if(etype < 0 || etype >= 8)
   {
      throw ::exception(error_bad_argument, "not yet supported integer type");
   }
   return iaBaseLog[iBase - 2][etype];

}

//int i8_maximum_digits(int iBase) { return type_maximum_digits(e_integer_type_i8, iBase); }
//int u8_maximum_digits(int iBase) { return type_maximum_digits(e_integer_type_u8, iBase); }
//
//int i16_maximum_digits(int iBase) { return type_maximum_digits(e_integer_type_i16, iBase); }
//int u16_maximum_digits(int iBase) { return type_maximum_digits(e_integer_type_u16, iBase); }
//
//int i32_maximum_digits(int iBase) { return type_maximum_digits(e_integer_type_i32, iBase); }
//int u32_maximum_digits(int iBase) { return type_maximum_digits(e_integer_type_u32, iBase); }
//
//int i64_maximum_digits(int iBase) { return type_maximum_digits(e_integer_type_i64, iBase); }
//int u64_maximum_digits(int iBase) { return type_maximum_digits(e_integer_type_u64, iBase); }
//
