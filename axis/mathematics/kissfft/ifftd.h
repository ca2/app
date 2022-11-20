#pragma once


//#include "acme/primitive/primitive/object.h"
#include "ifft.h"


namespace kissfft
{


   class CLASS_DECL_AXIS ifftd :
      virtual public ::object
   {
   public:


      i32                     m_iSize;
      kiss_fftr_cfg           m_cfg;


      ifftd(i32 iSize);
      ~ifftd() override;


      void ifft(COMPLEXD * pIn, double * pOut);


   };


} // namespace kissfft



