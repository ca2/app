// From image32_array.cpp by camilo on 2023-06-13 15:50 <3ThomasBorregaardSorensen!!
#pragma once


//#include "acme/primitive/collection/numeric_array.h"


//class CLASS_DECL_ACME image32_array :
//   virtual public ::array < ::image32_t >
//{
//public:
//
//
//   image32_array();
//   ~image32_array() override;
//
//
//   void create_web_palette();
//
//
//};

class CLASS_DECL_ACME color_array :
   virtual public ::array < ::color::color >
{
public:


   using ::array < ::color::color >::array;
   
   ~color_array() override;

   void create_web_palette();

   
};



