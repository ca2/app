#include "framework.h"
#include "ifftd.h"
#include "ifft.h"


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

   void ifftd::ifft(COMPLEXD * pIn, double * pOut)
   {
      kiss_fftri(m_cfg, pIn, pOut);
   }


} // namespace _vmskissfft
