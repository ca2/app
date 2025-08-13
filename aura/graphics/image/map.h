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


   class CLASS_DECL_AURA image_map_base :
      public map_base < enum_image, ::image::image_pointer >
   {
   public:


      using BASE_MAP = map_base < enum_image, ::image::image_pointer >;


      using BASE_MAP::BASE_MAP;
      using BASE_MAP::operator =;


   };


   class CLASS_DECL_AURA image_map :
      virtual public map_particle < image_map_base >
   {
   public:


      using BASE_MAP = map_particle < image_map_base >;


      using BASE_MAP::BASE_MAP;
      using BASE_MAP::operator =;


   };


   class CLASS_DECL_AURA size_image_base :
      public map_base < int_size, ::image::image_pointer >
   {
   public:


      ::image::image_pointer & operator[](const int_size & size);
      ::image::image_pointer & get(const int_size & size, bool & bExists);


   };


   class CLASS_DECL_AURA size_image :
      virtual public map_particle < size_image_base >
   {
   public:


      using BASE_MAP = map_particle < size_image_base >;


      using BASE_MAP::BASE_MAP;
      using BASE_MAP::operator =;


   };


   class CLASS_DECL_AURA image_descriptor_map_base :
      virtual public map_base < image_header, ::image::image_pointer >
   {
   public:


      using BASE_PAIR_MAP = map_base < image_header, ::image::image_pointer >;


      int m_iLimitCount;


      image_descriptor_map_base(int iLimitCount = 500)
      {

         m_iLimitCount = iLimitCount;

      }


      ::image::image_pointer & operator[](const image_header & key);


      void erase_bigger();


   };


   class CLASS_DECL_AURA image_descriptor_map :
      virtual public map_particle < image_descriptor_map_base >
   {
   public:


      using BASE_MAP = map_particle < image_descriptor_map_base >;


      using BASE_MAP::BASE_MAP;
      using BASE_MAP::operator =;


   };




} // namespace image


