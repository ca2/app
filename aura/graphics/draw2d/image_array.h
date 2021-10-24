#pragma once


class CLASS_DECL_AURA image_array :
   virtual public __pointer_array(::image)
{
public:


   image_array();
   virtual ~image_array();


   //::aura::application * application() { return m_papplication.cast < ::aura::application > (); }


   virtual bool explode(::object * pobject, ::payload payloadFile, int cols, int rows, bool bCache = true, bool bCreateHelperMaps = false);

   virtual bool explode(::object * pobject, const ::size_i32 & size, ::payload payloadFile, int cols, int rows, bool bCache = true, bool bCreateHelperMaps = false);


};



