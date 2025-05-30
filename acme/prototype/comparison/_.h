#pragma once


#include "equals.h"
#include "less.h"
#include "compare.h"
#include "hash.h"
#include "binary.h"
#include "sign.h"


#define unequal(a, b, n) ((a - n < b && b < a + n) || (b - n < a && a < b + n))


template < typename ARG_KEY >
inline iptr CompareElements(ARG_KEY element1, ARG_KEY element2)
{

   return element2 - element1;
}


template <  >
CLASS_DECL_ACME iptr CompareElements<const string & >(const string &  element1, const string &  element2);


template <  >
inline iptr CompareElements<void *>(void * element1, void *  element2)
{

   return (unsigned char *)element2 - (unsigned char *)element1;

}

