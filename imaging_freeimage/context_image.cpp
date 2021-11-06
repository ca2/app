#include "framework.h"
#include "_imaging_freeimage.h"


namespace imaging_freeimage
{


   context_image::context_image()
   {

      FreeImage_Initialise(false);

   }


   context_image::~context_image()
   {

      FreeImage_DeInitialise();

   }


} // namespace imaging_freeimage




