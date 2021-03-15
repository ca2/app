#pragma once


class CLASS_DECL_AURA image_array :
   virtual public __pointer_array(::image)
{
public:


   image_array();
   virtual ~image_array();


   //::aura::application * application() { return m_papplication.cast < ::aura::application > (); }


   virtual bool explode(::context_object * pobject, ::payload varFile, int cols, int rows, bool bCache = true, bool bCreateHelperMaps = false);

   virtual bool explode(::context_object * pobject, const ::size_i32 & size, ::payload varFile, int cols, int rows, bool bCache = true, bool bCreateHelperMaps = false);


};



