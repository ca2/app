#pragma once


#include "image32.h"


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

class CLASS_DECL_ACME image32_array :
   virtual public ::array < ::image32_t >
{
public:


   using ::array < ::image32_t >::array;
   
   ~image32_array() override;

   //void create_web_palette();

   
};



