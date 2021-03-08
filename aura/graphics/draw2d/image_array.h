#pragma once


class CLASS_DECL_AURA image_array :
   virtual public __pointer_array(::image)
{
public:


   image_array();
   virtual ~image_array();


   ::aura::application * application() { return (::aura::application *) m_papplication->layer(LAYERED_AURA); }


   virtual bool explode(::object * pobject, ::payload varFile, int cols, int rows, bool bCache = true, bool bCreateHelperMaps = false);

   virtual bool explode(::object * pobject, const ::size_i32 & size, ::payload varFile, int cols, int rows, bool bCache = true, bool bCreateHelperMaps = false);


};



