#pragma once


#include "acme/prototype/collection/map.h"
#include "acme/prototype/prototype/concrete.h"
//#include "acme/prototype/prototype/pointer.h"
#include "acme/graphics/image/header.h"


//template < >
//inline u32hash u32_hash < const ::size_i32 & >(const ::size_i32 & size) 
//{ 
//   
//   return (u32hash)(size.cx() | size.cy() << 16); 
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

namespace image
{


   class image_map :
      virtual public map < enum_image, ::image::image_pointer >
   {
   public:

   };


   class CLASS_DECL_AURA size_image :
      virtual public map < size_i32, ::image::image_pointer >
   {
   public:


      ::image::image_pointer & operator[](const size_i32 & size);
      ::image::image_pointer & get(const size_i32 & size, bool & bExists);


   };


   using image_descriptor_map_base = map < image_header, ::image::image_pointer >;


   class CLASS_DECL_AURA image_descriptor_map :
      virtual public image_descriptor_map_base
   {
   public:


      i32 m_iLimitCount;


      image_descriptor_map(i32 iLimitCount = 500)
      {

         m_iLimitCount = iLimitCount;

      }


      ::image::image *operator[](const image_header & key);


      void erase_bigger();

   };


} // namespace image


