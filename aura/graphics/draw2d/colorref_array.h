#pragma once


class CLASS_DECL_AURA colorref_array :
   virtual public numeric_array < COLORREF >
{
public:


   colorref_array();
   virtual ~colorref_array();


   void create_web_palette();


};
