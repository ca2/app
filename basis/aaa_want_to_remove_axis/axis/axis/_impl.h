#pragma once


//template<class TYPE>
//void dump_elements(dump_context & dumpcontext, const TYPE* pElements, ::count nCount)
//{
//   ENSURE(nCount == 0 || pElements != nullptr);
//   ASSERT(nCount == 0 ||
//      __is_valid_address(pElements, (size_t)nCount * sizeof(TYPE), false));
//#ifdef WINDOWS
//   &dumpcontext; // not used
//   pElements;  // not used
//   nCount; // not used
//#endif
//   // default does nothing
//}
//
//
//template<class TYPE>
//inline void CopyElements(TYPE* pDest, const TYPE* pSrc, ::count nCount)
//{
//   ENSURE(nCount == 0 || pDest != 0 && pSrc != 0);
//   ASSERT(nCount == 0 ||
//      __is_valid_address(pDest, (size_t)nCount * sizeof(TYPE)));
//   ASSERT(nCount == 0 ||
//      __is_valid_address(pSrc, (size_t)nCount * sizeof(TYPE)));
//
//   // default is matter-copy using assignment
//   while (nCount--)
//      *pDest++ = *pSrc++;
//}



#undef new








