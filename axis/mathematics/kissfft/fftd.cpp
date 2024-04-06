#include "framework.h"
#include "fftd.h"
#include "ifft.h"


namespace kissfft
{


   fftd::fftd(i32 iSize)
   {

      m_iSize = iSize;

      m_cfg = kiss_fftr_alloc(iSize, 0, nullptr, nullptr);

   }


   fftd::~fftd()
   {
      free(m_cfg);
   }

   void fftd::fft(double * pIn, COMPLEXD * pOut)
   {
      kiss_fftr(m_cfg, pIn, pOut);
   }


} // namespace kissfft


