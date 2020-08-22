#ifndef _2_PASS_SCALE_H_
#define _2_PASS_SCALE_H_

#include <math.h>

#include "filters.h"

typedef struct
{
   double *Weights;  // Normalized weights of neighboring pixels
   int Left,Right;   // Bounds of source pixels window
} ContributionType;  // Contirbution information for a single pixel

typedef struct
{
   ContributionType *ContribRow; // Row (or column) of contribution weights
   UINT WindowSize,              // Filter window size (of affecting source pixels)
        LineLength;              // Length of line (no. or rows / cols)
   double * matrix;
} LineContribType;               // Contribution information for an entire line (row or column)

typedef WINBOOL (*ProgressAnbAbortCallBack)(BYTE bPercentComplete);

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

   //COLORREF * AllocAndScale (
   //COLORREF   *pOrigImage,
   //UINT        uOrigWidth,
   //UINT        uOrigHeight,
   //UINT        uNewWidth,
   //UINT        uNewHeight);

   COLORREF * Scale (
   COLORREF   *pDstImage,
   UINT        uNewWidth,
   UINT        uNewHeight,
   UINT        uNewScan,
   COLORREF   *pOrigImage,
   UINT        uOrigWidth,
   UINT        uOrigHeight,
   UINT        uOrigScan
   );

private:

   ProgressAnbAbortCallBack    m_Callback;
   WINBOOL                     m_bCanceled;

   LineContribType *AllocContributions (   UINT uLineLength,
                                           UINT uWindowSize);

   void FreeContributions (LineContribType * point);

   LineContribType *CalcContributions (    UINT    uLineSize,
                                           UINT    uSrcSize,
                                           double  dScale);

   void ScaleRow ( COLORREF           *pSrc,
                   UINT                uSrcWidth,
                   COLORREF           *pRes,
                   UINT                uResWidth,
                   UINT                uRow,
                   LineContribType    *Contrib);

   void HorizScale (   COLORREF           *pSrc,
                       UINT                uSrcWidth,
                       UINT                uSrcHeight,
                       COLORREF           *pDst,
                       UINT                uResWidth,
                       UINT                uResHeight);

   void ScaleCol ( COLORREF           *pSrc,
                   UINT                uSrcWidth,
                   COLORREF           *pRes,
                   UINT                uResWidth,
                   UINT                uResHeight,
                   UINT                uCol,
                   LineContribType    *Contrib);

   void VertScale (    COLORREF           *pSrc,
                       UINT                uSrcWidth,
                       UINT                uSrcHeight,
                       COLORREF           *pDst,
                       UINT                uResWidth,
                       UINT                uResHeight);
};

template <class FilterClass>
LineContribType *
C2PassScale<FilterClass>::
AllocContributions (UINT uLineLength, UINT uWindowSize)
{
   LineContribType *res = new LineContribType;
   // Init structure header
   res->WindowSize = uWindowSize;
   res->LineLength = uLineLength;
   // Allocate list of contributions
   res->ContribRow = new ContributionType[uLineLength];
   res->matrix = new double[uWindowSize * uLineLength];
   for (UINT u = 0 ; u < uLineLength ; u++)
   {
      // Allocate contributions for every pixel
      res->ContribRow[u].Weights = &res->matrix[uWindowSize * u];
   }
   return res;
}

template <class FilterClass>
void
C2PassScale<FilterClass>::
FreeContributions (LineContribType * point)
{
   //for (UINT u = 0; u < point->LineLength; u++)
   //{
   //   // Free contribs for every pixel
   //   delete [] point->ContribRow[u].Weights;
   //}
   delete point->matrix;
   delete [] point->ContribRow;    // Free list of pixels contribs
   delete point;                   // Free contribs header
}

template <class FilterClass>
LineContribType *
C2PassScale<FilterClass>::
CalcContributions (UINT uLineSize, UINT uSrcSize, double dScale)
{

   ap(FilterClass) pCurFilter;

   if (m_dFilterWidth < 0.0)
   {

      pCurFilter = new FilterClass(m_dFilterWidth);

   }
   else
   {

      pCurFilter = new FilterClass();

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

   // Window size is the number of sampled pixels
   int iWindowSize = 2 * (int)ceil(dWidth) + 1;

   // Allocate a new line contributions strucutre
   LineContribType *res = AllocContributions (uLineSize, iWindowSize);

   for (UINT u = 0; u < uLineSize; u++)
   {
      // Scan through line of contributions
      double dCenter = (double)u / dScale;   // Reverse mapping
      // Find the significant edge points that affect the pixel
      int iLeft = MAX (0, (int)floor (dCenter - dWidth));
      res->ContribRow[u].Left = iLeft;
      int iRight = MIN ((int)ceil (dCenter + dWidth), int(uSrcSize) - 1);
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
            // Normalize point
            res->ContribRow[u].Weights[iSrc-iLeft] /= dTotalWeight;
         }
      }
   }
   return res;
}


template <class FilterClass>
void
C2PassScale<FilterClass>::
ScaleRow (  COLORREF           *pSrc,
            UINT                uSrcWidth,
            COLORREF           *pRes,
            UINT                uResWidth,
            UINT                uRow,
            LineContribType    *Contrib)
{
   COLORREF *pSrcRow = &(pSrc[uRow * uSrcWidth]);
   COLORREF *pDstRow = &(pRes[uRow * uResWidth]);
   for (UINT x = 0; x < uResWidth; x++)
   {
      // Loop through row
      BYTE r = 0;
      BYTE g = 0;
      BYTE b = 0;
      int iLeft = Contrib->ContribRow[x].Left;    // Retrieve left boundries
      int iRight = Contrib->ContribRow[x].Right;  // Retrieve right boundries
      for (int i = iLeft; i <= iRight; i++)
      {
         // Scan between boundries
         // Accumulate weighted effect of each neighboring pixel
         r += (BYTE)(Contrib->ContribRow[x].Weights[i-iLeft] * (double)(GetRValue(pSrcRow[i])));
         g += (BYTE)(Contrib->ContribRow[x].Weights[i-iLeft] * (double)(GetGValue(pSrcRow[i])));
         b += (BYTE)(Contrib->ContribRow[x].Weights[i-iLeft] * (double)(GetBValue(pSrcRow[i])));
      }
      pDstRow[x] = RGB(r,g,b); // Place result in destination pixel
   }
}

template <class FilterClass>
void
C2PassScale<FilterClass>::
HorizScale (    COLORREF           *pSrc,
                UINT                uSrcWidth,
                UINT                uSrcHeight,
                COLORREF           *pDst,
                UINT                uResWidth,
                UINT                uResHeight)
{
//   TRACE ("Performing horizontal scaling...\n");
   if (uResWidth == uSrcWidth)
   {
      // No scaling required, just copy
      ::memcpy_dup (pDst, pSrc, sizeof (COLORREF) * uSrcHeight * uSrcWidth);
   }
   // Allocate and calculate the contributions
   LineContribType * Contrib = CalcContributions (uResWidth, uSrcWidth, double(uResWidth) / double(uSrcWidth));
   for (UINT u = 0; u < uResHeight; u++)
   {
      // Step through rows
      if (nullptr != m_Callback)
      {
         //
         // Progress and report callback supplied
         //
         if (!m_Callback (BYTE(double(u) / double (uResHeight) * 50.0)))
         {
            //
            // User wished to abort now
            //
            m_bCanceled = TRUE;
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
ScaleCol (  COLORREF           *pSrc,
            UINT                uSrcWidth,
            COLORREF           *pRes,
            UINT                uResWidth,
            UINT                uResHeight,
            UINT                uCol,
            LineContribType    *Contrib)
{
   for (UINT y = 0; y < uResHeight; y++)
   {
      // Loop through column
      BYTE r = 0;
      BYTE g = 0;
      BYTE b = 0;
      int iLeft = Contrib->ContribRow[y].Left;    // Retrieve left boundries
      int iRight = Contrib->ContribRow[y].Right;  // Retrieve right boundries
      for (int i = iLeft; i <= iRight; i++)
      {
         // Scan between boundries
         // Accumulate weighted effect of each neighboring pixel
         COLORREF pCurSrc = pSrc[i * uSrcWidth + uCol];
         r += BYTE(Contrib->ContribRow[y].Weights[i-iLeft] * (double)(GetRValue(pCurSrc)));
         g += BYTE(Contrib->ContribRow[y].Weights[i-iLeft] * (double)(GetGValue(pCurSrc)));
         b += BYTE(Contrib->ContribRow[y].Weights[i-iLeft] * (double)(GetBValue(pCurSrc)));
      }
      pRes[y * uResWidth + uCol] = RGB (r,g,b);   // Place result in destination pixel
   }
}


template <class FilterClass>
void
C2PassScale<FilterClass>::
VertScale ( COLORREF           *pSrc,
            UINT                uSrcWidth,
            UINT                uSrcHeight,
            COLORREF           *pDst,
            UINT                uResWidth,
            UINT                uResHeight)
{
//   TRACE ("Performing vertical scaling...");

   if (uSrcHeight == uResHeight)
   {
      // No scaling required, just copy
      ::memcpy_dup (pDst, pSrc, sizeof (COLORREF) * uSrcHeight * uSrcWidth);
   }
   // Allocate and calculate the contributions
   LineContribType * Contrib = CalcContributions (uResHeight, uSrcHeight, double(uResHeight) / double(uSrcHeight));
   for (UINT u = 0; u < uResWidth; u++)
   {
      // Step through columns
      if (nullptr != m_Callback)
      {
         //
         // Progress and report callback supplied
         //
         if (!m_Callback (BYTE(double(u) / double (uResWidth) * 50.0) + 50))
         {
            //
            // User wished to abort now
            //
            m_bCanceled = TRUE;
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
//COLORREF *
//C2PassScale<FilterClass>::
//AllocAndScale (
//COLORREF   *pOrigImage,
//UINT        uOrigWidth,
//UINT        uOrigHeight,
//UINT        uNewWidth,
//UINT        uNewHeight)
//{
   // Scale source image horizontally into temporary image
//   m_bCanceled = FALSE;
//   COLORREF *pTemp = new COLORREF [uNewWidth * uOrigHeight];
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
//   COLORREF *pRes = new COLORREF [uNewWidth * uNewHeight];
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
COLORREF *
C2PassScale<FilterClass>::
Scale (

COLORREF   *pDstImage,
UINT        uNewWidth,
UINT        uNewHeight,
UINT uNewScan,
COLORREF   *pOrigImage,
UINT        uOrigWidth,
UINT        uOrigHeight,
UINT uOrigScan)
{

   // Scale source image horizontally into temporary image
   m_bCanceled = FALSE;

   aura::malloc < COLORREF * > pTemp;

   pTemp.alloc(sizeof(COLORREF) * uNewWidth * uOrigHeight);

   {

      ::aura::malloc < COLORREF * > pOrig;

      pOrig.alloc(sizeof(COLORREF) * uOrigWidth * uOrigHeight);

      ::copy_colorref(pOrig, uOrigWidth, uOrigHeight, uOrigWidth * sizeof(COLORREF), pOrigImage, uOrigScan);


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

      ::aura::malloc < COLORREF * > pDest;

      pDest.alloc(sizeof(COLORREF) * uNewWidth * uNewHeight);
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

      ::copy_colorref(pDstImage, uNewWidth, uNewHeight, uNewScan, pDest, uNewWidth * sizeof(COLORREF));

   }

   return pDstImage;

}


#endif //   _2_PASS_SCALE_H_
