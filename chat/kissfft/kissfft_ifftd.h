#pragma once


namespace kissfft
{


   class CLASS_DECL_CA2_MATH ifftd :
      virtual public ::object
   {
   public:

      int                     m_iSize;
      kiss_fftr_cfg           m_cfg;


      ifftd(int iSize);
      virtual ~ifftd();

      void ifft(kiss_fft_cpx * pIn, double * pOut);

   };


} // namespace kissfft

