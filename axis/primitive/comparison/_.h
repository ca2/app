#pragma once


#include "equals.h"
#include "less.h"
#include "compare.h"
#include "hash.h"
#include "binary.h"


#define unequal(a, b, n) ((a - n < b && b < a + n) || (b - n < a && a < b + n))


template < typename ARG_KEY >
inline iptr CompareElements(ARG_KEY element1, ARG_KEY element2)
{

   return element2 - element1;
}



template <  >
inline iptr CompareElements<string>(string element1, string  element2)
{

   return element1.compare(element2);

}

template <  >
inline iptr CompareElements<void *>(void * element1, void *  element2)
{

   return (u8 *)element2 - (u8 *)element1;

}

