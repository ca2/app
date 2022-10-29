#pragma once


#include "acme/primitive/collection/map.h"
#include "header.h"


class image_map :
   virtual public map < enum_image, ::image_pointer >
{
public:

};


class CLASS_DECL_AURA size_image :
   virtual public map < concrete < size_i32 >, ::image_pointer >
{
public:


   ::image_pointer & operator[](const concrete < size_i32 > & size);
   ::image_pointer & get(const concrete < size_i32 > & size, bool & bExists);


};


using image_descriptor_map_base = map < image_header, ::image_pointer >;


class CLASS_DECL_AURA image_descriptor_map :
   virtual public image_descriptor_map_base
{
public:


   i32 m_iLimitCount;


   image_descriptor_map(i32 iLimitCount = 500) 
   {

      m_iLimitCount = iLimitCount;

   }


   ::image * operator[](const image_header & key);


   void erase_bigger();

};


