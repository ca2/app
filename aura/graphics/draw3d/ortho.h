#pragma once


////#include "acme/prototype/prototype/object.h"



namespace draw3d
{


   class CLASS_DECL_AURA ortho:
      virtual public ::object
   {
   public:


      ::draw2d::graphics * m_pdc;


      ::i32_array draw_ortho_plain_wire_frame(::box_f64 * pbox, int iHint,int bA,bool bFirst);
      ::i32_array draw_ortho_plain_fill(::box_f64* pbox, int iHint,int bA,bool bFirst,::image::image *pimage);


   };


} // namespace draw3d
