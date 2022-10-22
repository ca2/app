#pragma once


class CLASS_DECL_ACME colorref_array :
   virtual public numeric_array < ::color32_t >
{
public:


   colorref_array();
   ~colorref_array() override;


   void create_web_palette();


};
