//
// Created by camilo on 30/12/2021. 14:56 BRT <ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "meta.h"


namespace image
{


   image_meta::~image_meta()
   {

      //::release(m_pbitmap);
      //::release(m_pgraphics);

   }


   void image_meta::set_exif_orientation(::i32 iExifOrientation)
   {

      m_iExifOrientation = iExifOrientation;


   }


} // namespace image



