#pragma once


#include "acme/prototype/collection/map.h"
#include "acme/prototype/prototype/concrete.h"
//#include "acme/prototype/prototype/pointer.h"
#include "acme/graphics/image/header.h"


//template < >
//inline hash32 as_hash32 < const ::int_size & >(const ::int_size & size) 
//{ 
//   
//   return (hash32)(size.cx() | size.cy() << 16); 
//
//}


//template < >
//inline hash32 as_hash32 < ::int_size >(::int_size size)
//{
//
//   return as_hash32<const ::int_size& >((const ::int_size &) size);
//
//}


//template < >
//inline hash32 as_hash32 < const concrete < ::int_size > & >(const concrete < ::int_size > & size)
//{
//
//   return as_hash32((const ::int_size &) size);
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
      virtual public map < int_size, ::image::image_pointer >
   {
   public:


      ::image::image_pointer & operator[](const int_size & size);
      ::image::image_pointer & get(const int_size & size, bool & bExists);


   };


   using image_descriptor_map_base = map < image_header, ::image::image_pointer >;


   class CLASS_DECL_AURA image_descriptor_map :
      virtual public image_descriptor_map_base
   {
   public:


      int m_iLimitCount;


      image_descriptor_map(int iLimitCount = 500)
      {

         m_iLimitCount = iLimitCount;

      }


      ::image::image *operator[](const image_header & key);


      void erase_bigger();

   };


} // namespace image


