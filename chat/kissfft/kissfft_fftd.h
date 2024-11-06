#pragma once


namespace kissfft
{


   class CLASS_DECL_CA2_MATH fftd :
      virtual public ::object
   {
   public:


      int                           m_iSize;
      kiss_fftr_cfg                 m_cfg;


      fftd(int iSize);
      virtual ~fftd();

      void fft(double * pIn, kiss_fft_cpx * pOut);


   };


} // namespace kissfft

