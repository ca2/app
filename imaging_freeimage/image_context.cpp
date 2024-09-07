#include "framework.h"
#include "image_context.h"


#include <FreeImage.h>


namespace imaging_freeimage
{


   image_context::image_context()
   {

      FreeImage_Initialise(false);

   }


   image_context::~image_context()
   {

      FreeImage_DeInitialise();

   }


} // namespace imaging_freeimage




