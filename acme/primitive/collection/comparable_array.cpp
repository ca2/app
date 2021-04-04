#include "framework.h"

#ifdef UNIT_TEST

void unit_test_base_comparable_array_debug();

void unit_test_base_comparable_array_debug()
{

   comparable_array<i32,i32> ia;

   i32 i = 1;

   ia.find_first(i);

   ia.erase_first(i);
   
}

#endif