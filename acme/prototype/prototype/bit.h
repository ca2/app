#pragma once


namespace acme
{

   namespace bit
   {

      CLASS_DECL_ACME void int_aligned_copy(int * pDest, int iDest, int * pSrc, int iSrc, int iCount);
      CLASS_DECL_ACME void int_aligned_copy(int * pDest, int * pSrc, int start, int end);
      CLASS_DECL_ACME void set(void * pDest, bool b, int start, int end);
      CLASS_DECL_ACME void byte_set(uchar * pDest, bool b, int start, int end);

   } // namespace bit


} // namespace prototype



