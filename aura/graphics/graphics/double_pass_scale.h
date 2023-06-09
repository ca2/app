#ifndef _2_PASS_SCALE_H_
#define _2_PASS_SCALE_H_

#include <math.h>

#include "filters.h"
#include "acme/platform/auto_pointer.h"
//#include "aura/graphics/image/_image.h"

typedef struct
{
   double *Weights;  // Normalized weights of neighboring pixels
   int Left,Right;   // Bounds of source pixels window
} ContributionType;  // Contirbution information for a single pixel

typedef struct
{
   ContributionType *ContribRow; // Row (or column) of contribution weights
   ::u32 WindowSize,              // Filter window size_i32 (of affecting source pixels)
        LineLength;              // Length of line (no. or rows / cols)
   double * matrix;
} LineContribType;               // Contribution information for an entire line (row or column)

typedef int_bool (*ProgressAnbAbortCallBack)(byte bPercentComplete);

template <class FilterClass>
class C2PassScale
{
public:


   double m_dFilterWidth;


   C2PassScale (double dFilterWidth = -1.0, ProgressAnbAbortCallBack callback = nullptr) :
      m_dFilterWidth(dFilterWidth),
      m_Callback (callback)
   {

   }

   virtual ~C2PassScale() {}

   //::color::color * AllocAndScale (
   //::color::color   *pOrigImage,
   //::u32        uOrigWidth,
   //::u32        uOrigHeight,
   //::u32        uNewWidth,
   //::u32        uNewHeight);

   ::color32_t *  Scale (
   ::color32_t *  pDstImage,
   ::u32          uNewWidth,
   ::u32          uNewHeight,
   ::u32          uNewScan,
   ::color32_t *  pOrigImage,
   ::u32          uOrigWidth,
   ::u32          uOrigHeight,
   ::u32          uOrigScan
   );

private:

   ProgressAnbAbortCallBack    m_Callback;
   int_bool                     m_bCanceled;

   LineContribType *AllocContributions (   ::u32 uLineLength,
                                           ::u32 uWindowSize);

   void FreeContributions (LineContribType * point_i32);

   LineContribType *CalcContributions (    ::u32    uLineSize,
                                           ::u32    uSrcSize,
                                           double  dScale);

   void ScaleRow (::color32_t*pSrc,
                   ::u32                uSrcWidth,
      ::color32_t*pRes,
                   ::u32                uResWidth,
                   ::u32                uRow,
                   LineContribType    *Contrib);

   void HorizScale (::color32_t*pSrc,
                       ::u32                uSrcWidth,
                       ::u32                uSrcHeight,
      ::color32_t*pDst,
                       ::u32                uResWidth,
                       ::u32                uResHeight);

   void ScaleCol (::color32_t*pSrc,
                   ::u32                uSrcWidth,
      ::color32_t*pRes,
                   ::u32                uResWidth,
                   ::u32                uResHeight,
                   ::u32                uCol,
                   LineContribType    *Contrib);

   void VertScale (::color32_t*pSrc,
                       ::u32                uSrcWidth,
                       ::u32                uSrcHeight,
      ::color32_t*pDst,
                       ::u32                uResWidth,
                       ::u32                uResHeight);
};

template <class FilterClass>
LineContribType *
C2PassScale<FilterClass>::
AllocContributions (::u32 uLineLength, ::u32 uWindowSize)
{
   LineContribType *res = memory_new LineContribType;
   // Init structure header
   res->WindowSize = uWindowSize;
   res->LineLength = uLineLength;
   // Allocate list of contributions
   res->ContribRow = memory_new ContributionType[uLineLength];
   res->matrix = memory_new double[uWindowSize * uLineLength];
   for (::u32 u = 0 ; u < uLineLength ; u++)
   {
      // Allocate contributions for every pixel
      res->ContribRow[u].Weights = &res->matrix[uWindowSize * u];
   }
   return res;
}

template <class FilterClass>
void
C2PassScale<FilterClass>::
FreeContributions (LineContribType * point_i32)
{
   //for (::u32 u = 0; u < point_i32->LineLength; u++)
   //{
   //   // Free contribs for every pixel
   //   delete [] point_i32->ContribRow[u].Weights;
   //}
   delete point_i32->matrix;
   delete [] point_i32->ContribRow;    // Free list of pixels contribs
   delete point_i32;                   // Free contribs header
}

template <class FilterClass>
LineContribType *
C2PassScale<FilterClass>::
CalcContributions (::u32 uLineSize, ::u32 uSrcSize, double dScale)
{

   ::auto_pointer < FilterClass > pCurFilter;

   if (m_dFilterWidth < 0.0)
   {

      pCurFilter = memory_new FilterClass(m_dFilterWidth);

   }
   else
   {

      pCurFilter = memory_new FilterClass();

   }

   double dWidth;
   double dFScale = 1.0;
   double dFilterWidth = pCurFilter->GetWidth();

   if (dScale < 1.0)
   {
      // Minification
      dWidth = dFilterWidth / dScale;
      dFScale = dScale;
   }
   else
   {
      // Magnification
      dWidth= dFilterWidth;
   }

   // Window size_i32 is the number of sampled pixels
   int iWindowSize = 2 * (int)ceil(dWidth) + 1;

   // Allocate a memory_new line contributions strucutre
   LineContribType *res = AllocContributions (uLineSize, iWindowSize);

   for (::u32 u = 0; u < uLineSize; u++)
   {
      // Scan through line of contributions
      double dCenter = (double)u / dScale;   // Reverse mapping
      // Find the significant edge points that affect the pixel
      int iLeft = maximum (0, (int)floor (dCenter - dWidth));
      res->ContribRow[u].Left = iLeft;
      int iRight = minimum ((int)ceil (dCenter + dWidth), int(uSrcSize) - 1);
      res->ContribRow[u].Right = iRight;

      // Cut edge points to fit in filter window in case of spill-off
      if (iRight - iLeft + 1 > iWindowSize)
      {
         if (iLeft < (int(uSrcSize) - 1 / 2))
         {
            iLeft++;
         }
         else
         {
            iRight--;
         }
      }
      double dTotalWeight = 0.0;  // Zero sum of weights
      for (int iSrc = iLeft; iSrc <= iRight; iSrc++)
      {
         // Calculate weights
         dTotalWeight += (res->ContribRow[u].Weights[iSrc-iLeft] =
                          dFScale * pCurFilter->Filter (dFScale * (dCenter - (double)iSrc)));
      }
      ASSERT (dTotalWeight >= -0.001);   // An error in the filter function can cause this
      if (dTotalWeight > 0.0)
      {
         // Normalize weight of neighbouring points
         for (int iSrc = iLeft; iSrc <= iRight; iSrc++)
         {
            // Normalize point_i32
            res->ContribRow[u].Weights[iSrc-iLeft] /= dTotalWeight;
         }
      }
   }
   return res;
}


template <class FilterClass>
void
C2PassScale<FilterClass>::
ScaleRow (::color32_t*pSrc,
            ::u32                uSrcWidth,
   ::color32_t*pRes,
            ::u32                uResWidth,
            ::u32                uRow,
            LineContribType    *Contrib)
{
   ::color32_t*pSrcRow = &(pSrc[uRow * uSrcWidth]);
   ::color32_t*pDstRow = &(pRes[uRow * uResWidth]);
   for (::u32 x = 0; x < uResWidth; x++)
   {
      // Loop through row
      byte r = 0;
      byte g = 0;
      byte b = 0;
      int iLeft = Contrib->ContribRow[x].Left;    // Retrieve left boundries
      int iRight = Contrib->ContribRow[x].Right;  // Retrieve right boundries
      for (int i = iLeft; i <= iRight; i++)
      {
         // Scan between boundries
         // Accumulate weighted effect of each neighboring pixel
         r += (byte)(Contrib->ContribRow[x].Weights[i-iLeft] * (double)(red(pSrcRow[i])));
         g += (byte)(Contrib->ContribRow[x].Weights[i-iLeft] * (double)(green(pSrcRow[i])));
         b += (byte)(Contrib->ContribRow[x].Weights[i-iLeft] * (double)(blue(pSrcRow[i])));
      }
      pDstRow[x] = rgb(r,g,b); // Place result in destination pixel
   }
}

template <class FilterClass>
void
C2PassScale<FilterClass>::
HorizScale (::color32_t*pSrc,
                ::u32                uSrcWidth,
                ::u32                uSrcHeight,
   ::color32_t*pDst,
                ::u32                uResWidth,
                ::u32                uResHeight)
{
//   TRACE ("Performing horizontal scaling...\n");
   if (uResWidth == uSrcWidth)
   {
      // No scaling required, just copy
      ::memory_copy (pDst, pSrc, sizeof (::color::color) * uSrcHeight * uSrcWidth);
   }
   // Allocate and calculate the contributions
   LineContribType * Contrib = CalcContributions (uResWidth, uSrcWidth, double(uResWidth) / double(uSrcWidth));
   for (::u32 u = 0; u < uResHeight; u++)
   {
      // Step through rows
      if (nullptr != m_Callback)
      {
         //
         // Progress and report callback supplied
         //
         if (!m_Callback (byte(double(u) / double (uResHeight) * 50.0)))
         {
            //
            // User wished to abort now
            //
            m_bCanceled = true;
            FreeContributions (Contrib);  // Free contributions structure
            return;
         }
      }

      ScaleRow (  pSrc,
                  uSrcWidth,
                  pDst,
                  uResWidth,
                  u,
                  Contrib);    // Scale each row
   }
   FreeContributions (Contrib);  // Free contributions structure
}

template <class FilterClass>
void
C2PassScale<FilterClass>::
ScaleCol (::color32_t*pSrc,
            ::u32                uSrcWidth,
   ::color32_t*pRes,
            ::u32                uResWidth,
            ::u32                uResHeight,
            ::u32                uCol,
            LineContribType    *Contrib)
{
   for (::u32 y = 0; y < uResHeight; y++)
   {
      // Loop through column
      byte r = 0;
      byte g = 0;
      byte b = 0;
      int iLeft = Contrib->ContribRow[y].Left;    // Retrieve left boundries
      int iRight = Contrib->ContribRow[y].Right;  // Retrieve right boundries
      for (int i = iLeft; i <= iRight; i++)
      {
         // Scan between boundries
         // Accumulate weighted effect of each neighboring pixel
         ::color::color pCurSrc = pSrc[i * uSrcWidth + uCol];
         r += byte(Contrib->ContribRow[y].Weights[i-iLeft] * (double)(red(pCurSrc)));
         g += byte(Contrib->ContribRow[y].Weights[i-iLeft] * (double)(green(pCurSrc)));
         b += byte(Contrib->ContribRow[y].Weights[i-iLeft] * (double)(blue(pCurSrc)));
      }
      pRes[y * uResWidth + uCol] = rgb (r,g,b);   // Place result in destination pixel
   }
}


template <class FilterClass>
void
C2PassScale<FilterClass>::
VertScale (::color32_t*pSrc,
            ::u32                uSrcWidth,
            ::u32                uSrcHeight,
   ::color32_t*pDst,
            ::u32                uResWidth,
            ::u32                uResHeight)
{
//   TRACE ("Performing vertical scaling...");

   if (uSrcHeight == uResHeight)
   {
      // No scaling required, just copy
      ::memory_copy (pDst, pSrc, sizeof (::color::color) * uSrcHeight * uSrcWidth);
   }
   // Allocate and calculate the contributions
   LineContribType * Contrib = CalcContributions (uResHeight, uSrcHeight, double(uResHeight) / double(uSrcHeight));
   for (::u32 u = 0; u < uResWidth; u++)
   {
      // Step through columns
      if (nullptr != m_Callback)
      {
         //
         // Progress and report callback supplied
         //
         if (!m_Callback (byte(double(u) / double (uResWidth) * 50.0) + 50))
         {
            //
            // User wished to abort now
            //
            m_bCanceled = true;
            FreeContributions (Contrib);  // Free contributions structure
            return;
         }
      }
      ScaleCol (  pSrc,
                  uSrcWidth,
                  pDst,
                  uResWidth,
                  uResHeight,
                  u,
                  Contrib);   // Scale each column
   }
   FreeContributions (Contrib);     // Free contributions structure
}

//template <class FilterClass>
//::color::color *
//C2PassScale<FilterClass>::
//AllocAndScale (
//::color::color   *pOrigImage,
//::u32        uOrigWidth,
//::u32        uOrigHeight,
//::u32        uNewWidth,
//::u32        uNewHeight)
//{
   // Scale source image horizontally into temporary image
//   m_bCanceled = false;
//   ::color::color *pTemp = memory_new ::color::color [uNewWidth * uOrigHeight];
//   HorizScale (pOrigImage,
//               uOrigWidth,
//               uOrigHeight,
//               pTemp,
//               uNewWidth,
//               uOrigHeight);
//   if (m_bCanceled)
//   {
//      delete [] pTemp;
//      return nullptr;
//   }
   // Scale temporary image vertically into result image
//   ::color::color *pRes = memory_new ::color::color [uNewWidth * uNewHeight];
//   VertScale ( pTemp,
//               uNewWidth,
//               uOrigHeight,
//               pRes,
//               uNewWidth,
//               uNewHeight);
//   if (m_bCanceled)
//   {
//      delete [] pTemp;
//      delete [] pRes;
//      return nullptr;
//   }
//   delete [] pTemp;
//   return pRes;
//}

template <class FilterClass>
::color32_t *
C2PassScale<FilterClass>::
Scale (
::color32_t *pDstImage,
::u32        uNewWidth,
::u32        uNewHeight,
::u32        uNewScan,
::color32_t *pOrigImage,
::u32        uOrigWidth,
::u32        uOrigHeight,
::u32 uOrigScan)
{

   // Scale source image horizontally into temporary image
   m_bCanceled = false;

   acme::malloc < ::color32_t * > pTemp;

   pTemp.alloc(sizeof(::color32_t) * uNewWidth * uOrigHeight);

   {

      ::acme::malloc < ::color32_t* > pOrig;

      pOrig.alloc(sizeof(::color32_t) * uOrigWidth * uOrigHeight);

      ::copy_colorref(pOrig, uOrigWidth, uOrigHeight, uOrigWidth * sizeof(::color32_t), pOrigImage, uOrigScan);

      HorizScale(pOrig,
                 uOrigWidth,
                 uOrigHeight,
                 pTemp,
                 uNewWidth,
                 uOrigHeight);

      if (m_bCanceled)
      {

         return nullptr;

      }

   }

   {

      ::acme::malloc < ::color32_t * > pDest;

      pDest.alloc(sizeof(::color32_t) * uNewWidth * uNewHeight);
      // Scale temporary image vertically into result image
      VertScale(pTemp,
                uNewWidth,
                uOrigHeight,
                pDest,
                uNewWidth,
                uNewHeight);

      if (m_bCanceled)
      {

         return nullptr;

      }

      ::copy_colorref(pDstImage, uNewWidth, uNewHeight, uNewScan, pDest, uNewWidth * sizeof(::color32_t));

   }

   return pDstImage;

}



#endif //   _2_PASS_SCALE_H_

