#pragma once


//#include "acme/primitive/collection/numeric_array.h"


class CLASS_DECL_ACME colorref_array :
   virtual public ::array < ::color32_t >
{
public:


   colorref_array();
   ~colorref_array() override;


   void create_web_palette();


};
