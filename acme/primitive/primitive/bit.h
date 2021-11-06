#pragma once


namespace acme
{

   namespace bit
   {

      CLASS_DECL_ACME void int_aligned_copy(i32 * pDest, i32 iDest, i32 * pSrc, i32 iSrc, i32 iCount);
      CLASS_DECL_ACME void int_aligned_copy(i32 * pDest, i32 * pSrc, i32 start, i32 end);
      CLASS_DECL_ACME void set(void * pDest, bool b, i32 start, i32 end);
      CLASS_DECL_ACME void byte_set(uchar * pDest, bool b, i32 start, i32 end);

   } // namespace bit


} // namespace primitive



