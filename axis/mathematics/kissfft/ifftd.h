#pragma once


////#include "acme/prototype/prototype/object.h"
#include "ifft.h"


namespace kissfft
{


   class CLASS_DECL_AXIS ifftd :
      virtual public ::object
   {
   public:


      int                     m_iSize;
      kiss_fftr_cfg           m_cfg;


      ifftd(int iSize);
      ~ifftd() override;


      void ifft(COMPLEXD * pIn, double * pOut);


   };


} // namespace kissfft



