#include "platform.h"
#include "dynamic.h"


namespace image
{


   image_dynamic::image_dynamic()
   {

      m_bStart = false;

      m_iFrame = -1;

   }


   image_dynamic::image_dynamic(image_dynamic&& imagedynamic)
   {

      imagedynamic.m_bStart = false;

      imagedynamic.m_iFrame = -1;

   }


   image_dynamic::~image_dynamic()
   {


   }

} // namespace image