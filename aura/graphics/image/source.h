// created2021-01-22 by camilo <3ThomasBS!!
#pragma once


//#include "acme/prototype/geometry2d/_geometry2d.h"
#include "acme/prototype/geometry2d/rectangle.h"
#include "acme/prototype/prototype/concrete.h"
//#include "acme/prototype/prototype/matter.h"


namespace image
{


   template < typename IMAGE_SOURCE_POINTER >
   concept image_source_pointer = requires(IMAGE_SOURCE_POINTER p, const ::size_i32 & size, const ::size_f64 & sizeDst, enum_image_selection eimageselection)
   {


      { p->get_image(size) } -> ::std::same_as < ::image::image *>;


      { p->size(sizeDst, eimageselection) } -> ::std::same_as < ::size_i32 >;
      { p->size() } -> ::std::same_as < ::size_i32 >;


   };


   class image_source_interface :
      virtual public ::matter
   {
   public:


      virtual image_pointer image_source_image(const ::size_i32 & size) = 0;


      virtual ::size_i32 image_source_size(const ::size_f64 & sizeTarget, enum_image_selection eimageselection) const = 0;
      virtual ::size_i32 image_source_size() const = 0;


   };


   class CLASS_DECL_AURA image_source
   {
   public:



      enum_sub_image                      m_esubimage;
      ::rectangle_f64                     m_rectangleSubImage;
      ::pointer<image_source_interface>  m_pimagesource;


      image_source() :
         m_esubimage(e_sub_image_entire)
      {

      }


      image_source(const ::image::image_source & imagesource) :
         m_esubimage(imagesource.m_esubimage),
         m_rectangleSubImage(imagesource.m_rectangleSubImage),
         m_pimagesource(imagesource.m_pimagesource)
      {

      }


      image_source(::image::image_source && imagesource) :
         m_esubimage(imagesource.m_esubimage),
         m_rectangleSubImage(::transfer(imagesource.m_rectangleSubImage)),
         m_pimagesource(::transfer(imagesource.m_pimagesource))
      {


      }


      image_source(image_source_interface * pimagesource) :
         m_esubimage(e_sub_image_entire),
         m_pimagesource(pimagesource)
      {


      }


      image_source(image_source_interface * pimagesource, const ::rectangle_f64 & rectangleSubImage, enum_sub_image esubimage = e_sub_image_coordinates) :
         m_esubimage(esubimage),
         m_pimagesource(pimagesource),
         m_rectangleSubImage(rectangleSubImage)
      {

      }


      ::rectangle_f64 source_rectangle() const
      {

         if (m_esubimage == e_sub_image_coordinates)
         {

            auto size = m_pimagesource->image_source_size();

            return ::rectangle_f64(
               m_rectangleSubImage.left() * size.cx(),
               m_rectangleSubImage.top() * size.cy(),
               m_rectangleSubImage.right() * size.cx(),
               m_rectangleSubImage.bottom() * size.cy());

         }
         else if (m_esubimage == e_sub_image_coordinates)
         {

            return m_rectangleSubImage;

         }
         else
         {

            return ::rectangle_f64(m_pimagesource->image_source_size());

         }

      }


   };


   class CLASS_DECL_AURA image_payload :
      public ::image::image_source
   {
   public:


      image_payload(::particle * pparticle, const ::payload & payload);


   };



   class CLASS_DECL_AURA icon_payload :
      public ::image::image_source
   {
   public:


      icon_payload(::particle * pparticle, const ::payload & payload);


   };


} // namespace image



