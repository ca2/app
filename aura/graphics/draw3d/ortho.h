#pragma once


////#include "acme/prototype/prototype/object.h"



namespace draw3d
{


   class CLASS_DECL_AURA ortho:
      virtual public ::object
   {
   public:


      ::draw2d::graphics * m_pdc;


      ::int_array draw_ortho_plain_wire_frame(::box_double * pbox, int iHint,int bA,bool bFirst);
      ::int_array draw_ortho_plain_fill(::box_double* pbox, int iHint,int bA,bool bFirst,::image::image *pimage);


   };


} // namespace draw3d
