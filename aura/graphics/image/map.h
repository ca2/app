#pragma once


#include "acme/prototype/collection/map.h"
#include "acme/prototype/prototype/concrete.h"
//#include "acme/prototype/prototype/pointer.h"
#include "acme/graphics/image/header.h"


//template < >
//inline hash32 as_hash32 < const ::i32_size & >(const ::i32_size & size) 
//{ 
//   
//   return (hash32)(size.cx | size.cy << 16); 
//
//}


//template < >
//inline hash32 as_hash32 < ::i32_size >(::i32_size size)
//{
//
//   return as_hash32<const ::i32_size& >((const ::i32_size &) size);
//
//}


//template < >
//inline hash32 as_hash32 < const concrete < ::i32_size > & >(const concrete < ::i32_size > & size)
//{
//
//   return as_hash32((const ::i32_size &) size);
//
//}

namespace image
{


   class CLASS_DECL_AURA image_map :
      public ::map < enum_image, ::image::image_pointer >
   {
   public:


      using BASE_MAP = ::map < enum_image, ::image::image_pointer >;



   };



   class CLASS_DECL_AURA size_image :
      public ::map < i32_size, ::image::image_pointer >
   {
   public:

      
      ::pointer< ::draw2d::domain > m_pdraw2ddomain;
      

      ::image::image_pointer & operator[](const i32_size & size);
      ::image::image_pointer & get(const i32_size & size, bool & bExists);

   };





   class CLASS_DECL_AURA image_descriptor_map :
      public ::map < image_header, ::image::image_pointer >
   {
   public:


      using BASE_PAIR_MAP = ::map < image_header, ::image::image_pointer >;


      ::i32 m_iLimitCount;
      ::pointer< ::draw2d::domain > m_pdraw2ddomain;


      image_descriptor_map(::i32 iLimitCount = 500)
      {

         m_iLimitCount = iLimitCount;

      }


      ::image::image_pointer & operator[](const image_header & key);


      void erase_bigger();


   };


} // namespace image



