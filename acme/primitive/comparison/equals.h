#pragma once


template < class ARG_TYPE >
inline bool EqualElements(ARG_TYPE element1, ARG_TYPE element2)
{
   return element1 == element2;
}


template < typename TYPE >
inline bool EqualElements(const __pointer(TYPE) & element1, const TYPE * element2)
{
   return element1 == element2;
}




