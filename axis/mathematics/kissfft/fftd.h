#pragma once


namespace kissfft
{


   class CLASS_DECL_AXIS fftd :
      virtual public ::object
   {
   public:


      i32                           m_iSize;
      kiss_fftr_cfg                 m_cfg;


      fftd(i32 iSize);
      virtual ~fftd();

      void fft(double * pIn, COMPLEXD * pOut);


   };


} // namespace kissfft

