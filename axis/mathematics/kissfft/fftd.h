#pragma once


#include "ifft.h"



namespace kissfft
{


   class CLASS_DECL_AXIS fftd :
      virtual public ::particle
   {
   public:


      i32                           m_iSize;
      kiss_fftr_cfg                 m_cfg;


      fftd(i32 iSize);
      ~fftd() override;

      void fft(double * pIn, COMPLEXD * pOut);


   };


} // namespace kissfft

