#pragma once


class CLASS_DECL_AURA image_array :
   public __pointer_array(::image)
{
public:


   bool explode(::object * pobject, ::payload payloadFile, int cols, int rows, bool bCache = true, bool bCreateHelperMaps = false);

   bool explode(::object * pobject, const ::size_i32 & size, ::payload payloadFile, int cols, int rows, bool bCache = true, bool bCreateHelperMaps = false);


};



