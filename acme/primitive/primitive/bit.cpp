#include "framework.h"
#include "acme/primitive/primitive/bit.h"
#include "acme/exception/exception.h"


#define BYTE_ALIGN (8)
#define INT_ALIGN (BYTE_ALIGN * sizeof(i32))


namespace acme
{
   namespace bit
   {

      void int_aligned_copy(i32 * pDest, i32 iDest, i32 * pSrc, i32 iSrc, i32 iCount)
      {
         
         if((iDest % INT_ALIGN) != (iSrc %INT_ALIGN))
         {

            throw ::exception(error_bad_argument, "i32 aligned only");

         }

         i32 * pFullDest = &pDest[iDest / INT_ALIGN];
         i32 * pFullSrc = &pSrc[iSrc / INT_ALIGN];
         if((iDest % INT_ALIGN) > 0)
         {
            pFullDest++;            
            pFullSrc++;
         }
         i32 iFullCount1 = iCount - (iDest % INT_ALIGN);
         i32 iFullCount2 = iFullCount1 / INT_ALIGN;
         ::memcpy_dup(pFullDest, pFullSrc, iFullCount2);
         if(pFullDest > pDest)
         {
            int_aligned_copy(pFullDest - 1, pFullSrc - 1, iDest % INT_ALIGN, INT_ALIGN - 1);
         }
         if((iFullCount1 % INT_ALIGN) > 0)
         {
            int_aligned_copy(pFullDest + iFullCount2, pFullSrc + iFullCount2, 0, (iFullCount1 % INT_ALIGN) - 1);
         }
      }

      void int_aligned_copy(i32 * pDest, i32 * pSrc, i32 start, i32 end)
      {
         for(i32 i = start; i <= end; i++)
         {
            if((*pSrc >> i) & 1)
            {
               *pDest |= (i32) (1 << i);
            }
            else
            {
               *pDest &= (i32) ~(1 << i);
            }
         }
      }

      void set(void * p, bool b, i32 start, i32 end)
      {
         uchar * pDest = (uchar *) p;
         uchar * pFullDestStart = &pDest[start / BYTE_ALIGN];
         uchar * pFullDestEnd = &pDest[end / BYTE_ALIGN];
         if((start % BYTE_ALIGN) > 0)
         {
            pFullDestStart++;            
         }
         if(((end + 1) % BYTE_ALIGN) > 0)
         {
            pFullDestEnd--;            
         }
         __memset(pFullDestStart, b ? 0xFF : 0, (pFullDestEnd - pFullDestStart + 1) / BYTE_ALIGN);
         if((start % BYTE_ALIGN) > 0)
         {
            byte_set(pFullDestStart - 1, b, start % BYTE_ALIGN, BYTE_ALIGN - 1);
         }
         if(((end + 1) % BYTE_ALIGN) > 0)
         {
            byte_set(pFullDestEnd + 1, b, 0, end % BYTE_ALIGN);
         }
      }

      void byte_set(uchar * pDest, bool b, i32 start, i32 end)
      {
         if(b)
         {
            for(i32 i = start; i <= end; i++)
            {
               *pDest |= (i32) (1 << i);
            }
         }
         else
         {
            for(i32 i = start; i <= end; i++)
            {
               *pDest &= (i32) ~(1 << i);
            }
         }
      }

   } // namespace bit

} // namespace acme


