#include "framework.h"
#include "image_context.h"

#if defined(USE_PORT_FREEIMAGE)
#include <port_freeimage/FreeImage.h>
#else
#include <FreeImage.h>
#endif


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




