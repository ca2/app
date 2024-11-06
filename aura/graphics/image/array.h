#pragma once


//#include "acme/prototype/collection/pointer_array.h"
//#include "acme/prototype/geometry2d/_geometry2d.h"
//#include "acme/prototype/prototype/matter.h"

namespace image
{


   class CLASS_DECL_AURA image_array :
      virtual public ::matter
   {
   public:


      DECLARE_ARRAY_OF(image_array, image, ::image::image);


      image_array();
      ~image_array() override;



      virtual bool explode(::particle * pparticle, ::payload payloadFile, int cols, int rows, bool bCache = true, bool bCreateHelperMaps = false);

      virtual bool explode(::particle * pparticle, const ::int_size & size, ::payload payloadFile, int cols, int rows, bool bCache = true, bool bCreateHelperMaps = false);


   };


} // namespace image



