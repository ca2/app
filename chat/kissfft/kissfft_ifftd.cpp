#include "framework.h"

namespace kissfft
{

   ifftd::ifftd(int iSize)
   {
      m_iSize = iSize;
      m_cfg = kiss_fftr_alloc(iSize, 1, nullptr, nullptr);
   }

   ifftd::~ifftd()
   {
      free(m_cfg);
   }

   void ifftd::ifft(kiss_fft_cpx * pIn, double * pOut)
   {
      kiss_fftri(m_cfg, pIn, pOut);
   }


} // namespace _vmskissfft
