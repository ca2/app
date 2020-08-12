#include "framework.h"


namespace imaging_freeimage
{


   imaging::imaging()
   {

      FreeImage_Initialise(FALSE);

   }


   imaging::~imaging()
   {

      FreeImage_DeInitialise();

   }


} // namespace imaging_freeimage




