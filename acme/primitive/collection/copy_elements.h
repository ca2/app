// From _impl.h by camilo on 2022-10-23 00:25 <3ThomasBorregaardSørensen!!
#pragma once


template<class TYPE>
inline void CopyElements(TYPE * pDest, const TYPE * pSrc, ::count nCount)
{

   ENSURE((nCount == 0) || ((pDest != 0) && (pSrc != 0)));
   ASSERT((nCount == 0) || __is_valid_address(pDest, (size_t)nCount * sizeof(TYPE)));
   ASSERT((nCount == 0) || __is_valid_address(pSrc, (size_t)nCount * sizeof(TYPE)));

   // default is matter-copy using assignment
   while (nCount--)
   {

      *pDest++ = *pSrc++;

   }

}




