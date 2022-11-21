#include "framework.h"
#include "context_image.h"


#include <FreeImage.h>


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




