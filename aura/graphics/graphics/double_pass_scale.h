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
   unsigned int WindowSize,              // Filter window int_size (of affecting source pixels)
        LineLength;              // Length of line (no. or rows / cols)
   double * matrix;
} LineContribType;               // Contribution information for an entire line (row or column)

typedef int_bool (*ProgressAnbAbortCallBack)(unsigned char bPercentComplete);

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
   //unsigned int        uOrigWidth,
   //unsigned int        uOrigHeight,
   //unsigned int        uNewWidth,
   //unsigned int        uNewHeight);

   ::image32_t *  Scale (
   ::image32_t *  pDstImage,
      color_indexes indexes, 
   unsigned int          uNewWidth,
   unsigned int          uNewHeight,
   unsigned int          uNewScan,
   ::image32_t *  pOrigImage,
   unsigned int          uOrigWidth,
   unsigned int          uOrigHeight,
   unsigned int          uOrigScan
   );

private:

   ProgressAnbAbortCallBack    m_Callback;
   int_bool                     m_bCanceled;

   LineContribType *AllocContributions (   unsigned int uLineLength,
                                           unsigned int uWindowSize);

   void FreeContributions (LineContribType * int_point);

   LineContribType *CalcContributions (    unsigned int    uLineSize,
                                           unsigned int    uSrcSize,
                                          double  dScale);
 
   void ScaleRow (::image32_t *pSrc,
      ::color_indexes indexes, 
                   unsigned int                uSrcWidth,
      ::image32_t*pRes,
                   unsigned int                uResWidth,
                   unsigned int                uRow,
                   LineContribType    *Contrib);

   void HorizScale (::image32_t *pSrc,
      color_indexes indexes,
                       unsigned int                uSrcWidth,
                       unsigned int                uSrcHeight,
      ::image32_t*pDst,
                       unsigned int                uResWidth,
                       unsigned int                uResHeight);

   void ScaleCol (::image32_t *pSrc,
      color_indexes indexes,
                   unsigned int                uSrcWidth,
      ::image32_t *pRes,
                   unsigned int                uResWidth,
                   unsigned int                uResHeight,
                   unsigned int                uCol,
                   LineContribType    *Contrib);

   void VertScale (::image32_t *pSrc,
      color_indexes indexes,
                       unsigned int                uSrcWidth,
                       unsigned int                uSrcHeight,
      ::image32_t*pDst,
                       unsigned int                uResWidth,
                       unsigned int                uResHeight);
};

template <class FilterClass>
LineContribType *
C2PassScale<FilterClass>::
AllocContributions (unsigned int uLineLength, unsigned int uWindowSize)
{
   LineContribType *res = __raw_new LineContribType();
   // Init structure header
   res->WindowSize = uWindowSize;
   res->LineLength = uLineLength;
   // Allocate list of contributions
   res->ContribRow = __raw_new ContributionType[uLineLength];
   res->matrix = __raw_new double[uWindowSize * uLineLength];
   for (unsigned int u = 0 ; u < uLineLength ; u++)
   {
      // Allocate contributions for every pixel
      res->ContribRow[u].Weights = &res->matrix[uWindowSize * u];
   }
   return res;
}

template <class FilterClass>
void
C2PassScale<FilterClass>::
FreeContributions (LineContribType * int_point)
{
   //for (unsigned int u = 0; u < int_point->LineLength; u++)
   //{
   //   // Free contribs for every pixel
   //   delete [] int_point->ContribRow[u].Weights;
   //}
   delete int_point->matrix;
   delete [] int_point->ContribRow;    // Free list of pixels contribs
   delete int_point;                   // Free contribs header
}

template <class FilterClass>
LineContribType *
C2PassScale<FilterClass>::
CalcContributions (unsigned int uLineSize, unsigned int uSrcSize, double dScale)
{

   ::auto_pointer < FilterClass > pCurFilter;

   if (m_dFilterWidth < 0.0)
   {

      pCurFilter = __raw_new FilterClass(m_dFilterWidth);

   }
   else
   {

      pCurFilter = __raw_new FilterClass();

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

   // Window int_size is the number of sampled pixels
   int iWindowSize = 2 * (int)ceil(dWidth) + 1;

   // Allocate a ___new line contributions strucutre
   LineContribType *res = AllocContributions (uLineSize, iWindowSize);

   for (unsigned int u = 0; u < uLineSize; u++)
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
            // Normalize int_point
            res->ContribRow[u].Weights[iSrc-iLeft] /= dTotalWeight;
         }
      }
   }
   return res;
}


template <class FilterClass>
void
C2PassScale<FilterClass>::
ScaleRow (::image32_t*pSrc,
   ::color_indexes indexes,
            unsigned int                uSrcWidth,
   ::image32_t*pRes,
            unsigned int                uResWidth,
            unsigned int                uRow,
            LineContribType    *Contrib)
{
   ::image32_t*pSrcRow = &(pSrc[uRow * uSrcWidth]);
   ::image32_t*pDstRow = &(pRes[uRow * uResWidth]);
   for (unsigned int x = 0; x < uResWidth; x++)
   {
      // Loop through row
      unsigned char r = 0;
      unsigned char g = 0;
      unsigned char b = 0;
      int iLeft = Contrib->ContribRow[x].Left;    // Retrieve left boundries
      int iRight = Contrib->ContribRow[x].Right;  // Retrieve right boundries
      for (int i = iLeft; i <= iRight; i++)
      {
         // Scan between boundries
         // Accumulate weighted effect of each neighboring pixel
         r += (unsigned char)(Contrib->ContribRow[x].Weights[i-iLeft] * (double)(pSrcRow[i].byte_red(indexes)));
         g += (unsigned char)(Contrib->ContribRow[x].Weights[i-iLeft] * (double)(pSrcRow[i].byte_green(indexes)));
         b += (unsigned char)(Contrib->ContribRow[x].Weights[i-iLeft] * (double)(pSrcRow[i].byte_blue(indexes)));
      }
      pDstRow[x].assign(rgb(r, g, b), indexes); // Place result in destination pixel
   }
}

template <class FilterClass>
void
C2PassScale<FilterClass>::
HorizScale (::image32_t*pSrc,
   color_indexes indexes,
                unsigned int                uSrcWidth,
                unsigned int                uSrcHeight,
   ::image32_t*pDst,
                unsigned int                uResWidth,
                unsigned int                uResHeight)
{
//   information ("Performing horizontal scaling...\n");
   if (uResWidth == uSrcWidth)
   {
      // No scaling required, just copy
      ::memory_copy (pDst, pSrc, sizeof (::color::color) * uSrcHeight * uSrcWidth);
   }
   // Allocate and calculate the contributions
   LineContribType * Contrib = CalcContributions (uResWidth, uSrcWidth, double(uResWidth) / double(uSrcWidth));
   for (unsigned int u = 0; u < uResHeight; u++)
   {
      // Step through rows
      if (nullptr != m_Callback)
      {
         //
         // Progress and report callback supplied
         //
         if (!m_Callback ((unsigned char)(double(u) / double (uResHeight) * 50.0)))
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
                  indexes,
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
ScaleCol (::image32_t*pSrc,
   color_indexes indexes,
            unsigned int                uSrcWidth,
   ::image32_t*pRes,
            unsigned int                uResWidth,
            unsigned int                uResHeight,
            unsigned int                uCol,
            LineContribType    *Contrib)
{
   for (unsigned int y = 0; y < uResHeight; y++)
   {
      // Loop through column
      unsigned char r = 0;
      unsigned char g = 0;
      unsigned char b = 0;
      int iLeft = Contrib->ContribRow[y].Left;    // Retrieve left boundries
      int iRight = Contrib->ContribRow[y].Right;  // Retrieve right boundries
      for (int i = iLeft; i <= iRight; i++)
      {
         // Scan between boundries
         // Accumulate weighted effect of each neighboring pixel
         ::color::color pCurSrc = pSrc[i * uSrcWidth + uCol].color(indexes);
         r += (unsigned char)(Contrib->ContribRow[y].Weights[i-iLeft] * (double)(pCurSrc.byte_red()));
         g += (unsigned char)(Contrib->ContribRow[y].Weights[i-iLeft] * (double)(pCurSrc.byte_green()));
         b += (unsigned char)(Contrib->ContribRow[y].Weights[i-iLeft] * (double)(pCurSrc.byte_blue()));
      }
      pRes[y * uResWidth + uCol].assign(rgb(r, g, b), indexes);   // Place result in destination pixel
   }
}


template <class FilterClass>
void
C2PassScale<FilterClass>::
VertScale (::image32_t*pSrc,
   color_indexes indexes,
            unsigned int                uSrcWidth,
            unsigned int                uSrcHeight,
   ::image32_t*pDst,
            unsigned int                uResWidth,
            unsigned int                uResHeight)
{
//   information ("Performing vertical scaling...");

   if (uSrcHeight == uResHeight)
   {
      // No scaling required, just copy
      ::memory_copy (pDst, pSrc, sizeof (::color::color) * uSrcHeight * uSrcWidth);
   }
   // Allocate and calculate the contributions
   LineContribType * Contrib = CalcContributions (uResHeight, uSrcHeight, double(uResHeight) / double(uSrcHeight));
   for (unsigned int u = 0; u < uResWidth; u++)
   {
      // Step through columns
      if (nullptr != m_Callback)
      {
         //
         // Progress and report callback supplied
         //
         if (!m_Callback ((unsigned char)(double(u) / double (uResWidth) * 50.0) + 50))
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
         indexes,
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
//unsigned int        uOrigWidth,
//unsigned int        uOrigHeight,
//unsigned int        uNewWidth,
//unsigned int        uNewHeight)
//{
   // Scale source image horizontally into temporary image
//   m_bCanceled = false;
//   ::color::color *pTemp = ___new ::color::color[uNewWidth * uOrigHeight];
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
//   ::color::color *pRes = ___new ::color::color[uNewWidth * uNewHeight];
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
::image32_t *
C2PassScale<FilterClass>::
Scale (
::image32_t *pDstImage,
color_indexes indexes,
unsigned int        uNewWidth,
unsigned int        uNewHeight,
unsigned int        uNewScan,
::image32_t *pOrigImage,
unsigned int        uOrigWidth,
unsigned int        uOrigHeight,
unsigned int uOrigScan)
{

   // Scale source image horizontally into temporary image
   m_bCanceled = false;

   acme::malloc < ::image32_t * > pTemp;

   pTemp.alloc(sizeof(::image32_t) * uNewWidth * uOrigHeight);

   {

      ::acme::malloc < ::image32_t* > pOrig;

      pOrig.alloc(sizeof(::image32_t) * uOrigWidth * uOrigHeight);

      pOrig->copy(uOrigWidth, uOrigHeight, uOrigWidth * sizeof(::image32_t), pOrigImage, uOrigScan);

      HorizScale(pOrig,
         indexes,
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

      ::acme::malloc < ::image32_t * > pDest;

      pDest.alloc(sizeof(::image32_t) * uNewWidth * uNewHeight);
      // Scale temporary image vertically into result image
      VertScale(pTemp,
         indexes,
                uNewWidth,
                uOrigHeight,
                pDest,
                uNewWidth,
                uNewHeight);

      if (m_bCanceled)
      {

         return nullptr;

      }

      pDstImage->copy(uNewWidth, uNewHeight, uNewScan, pDest, uNewWidth * sizeof(::image32_t));

   }

   return pDstImage;

}



#endif //   _2_PASS_SCALE_H_

