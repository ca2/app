#pragma once


#include "acme/primitive/collection/map.h"
#include "acme/primitive/primitive/concrete.h"
//#include "acme/primitive/primitive/pointer.h"
#include "header.h"


//template < >
//inline u32hash u32_hash < const ::size_i32 & >(const ::size_i32 & size) 
//{ 
//   
//   return (u32hash)(size.cx | size.cy << 16); 
//
//}


//template < >
//inline u32hash u32_hash < ::size_i32 >(::size_i32 size)
//{
//
//   return u32_hash<const ::size_i32& >((const ::size_i32 &) size);
//
//}


//template < >
//inline u32hash u32_hash < const concrete < ::size_i32 > & >(const concrete < ::size_i32 > & size)
//{
//
//   return u32_hash((const ::size_i32 &) size);
//
//}


class image_map :
   virtual public map < enum_image, ::image_pointer >
{
public:

};


class CLASS_DECL_AURA size_image :
   virtual public map < size_i32, ::image_pointer >
{
public:


   ::image_pointer & operator[](const size_i32 & size);
   ::image_pointer & get(const size_i32 & size, bool & bExists);


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


