#pragma once


//#include "acme/primitive/collection/pointer_array.h"
//#include "acme/primitive/geometry2d/_geometry2d.h"
//#include "acme/primitive/primitive/matter.h"


class CLASS_DECL_AURA image_array :
   virtual public ::matter
{
public:

   
   DECLARE_ARRAY_OF(image_array, image, ::image);
   
   
   image_array();
   ~image_array() override;



   virtual bool explode(::particle * pparticle, ::payload payloadFile, int cols, int rows, bool bCache = true, bool bCreateHelperMaps = false);

   virtual bool explode(::particle * pparticle, const ::size_i32 & size, ::payload payloadFile, int cols, int rows, bool bCache = true, bool bCreateHelperMaps = false);


};



