#pragma once


#include "acme/primitive/collection/array_base.h"


class CLASS_DECL_AURA image_array :
   virtual public ::matter
{
public:

   
   DECLARE_ARRAY_OF(image_array, image, ::image);
   
   
   image_array();
   ~image_array() override;



   virtual bool explode(::object * pobject, ::payload payloadFile, int cols, int rows, bool bCache = true, bool bCreateHelperMaps = false);

   virtual bool explode(::object * pobject, const ::size_i32 & size, ::payload payloadFile, int cols, int rows, bool bCache = true, bool bCreateHelperMaps = false);


};



