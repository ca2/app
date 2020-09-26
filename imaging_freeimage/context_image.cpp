#include "framework.h"


namespace imaging_freeimage
{


   context_image::context_image()
   {

      FreeImage_Initialise(FALSE);

   }


   context_image::~context_image()
   {

      FreeImage_DeInitialise();

   }


} // namespace imaging_freeimage




