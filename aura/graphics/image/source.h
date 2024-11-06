// created2021-01-22 by camilo <3ThomasBS!!
#pragma once


//#include "acme/prototype/geometry2d/_geometry2d.h"
#include "acme/prototype/geometry2d/rectangle.h"
#include "acme/prototype/prototype/concrete.h"
//#include "acme/prototype/prototype/matter.h"


namespace image
{


   template < typename IMAGE_SOURCE_POINTER >
   concept image_source_pointer = requires(IMAGE_SOURCE_POINTER p, const ::int_size & size, const ::double_size & sizeDst, enum_image_selection eimageselection)
   {


      { p->get_image(size) } -> ::std::same_as < ::image::image *>;


      { p->size(sizeDst, eimageselection) } -> ::std::same_as < ::int_size >;
      { p->size() } -> ::std::same_as < ::int_size >;


   };


   class image_source_interface :
      virtual public ::matter
   {
   public:


      virtual image_pointer image_source_image(const ::int_size & size) = 0;


      virtual ::int_size image_source_size(const ::double_size & sizeTarget, enum_image_selection eimageselection) const = 0;
      virtual ::int_size image_source_size() const = 0;


   };


   class CLASS_DECL_AURA image_source
   {
   public:



      enum_sub_image                      m_esubimage;
      ::double_rectangle                     m_rectangleSubImage;
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


      image_source(image_source_interface * pimagesource, const ::double_rectangle & rectangleSubImage, enum_sub_image esubimage = e_sub_image_coordinates) :
         m_esubimage(esubimage),
         m_pimagesource(pimagesource),
         m_rectangleSubImage(rectangleSubImage)
      {

      }


      ::double_rectangle source_rectangle() const
      {

         if (m_esubimage == e_sub_image_coordinates)
         {

            auto size = m_pimagesource->image_source_size();

            return ::double_rectangle(
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

            return ::double_rectangle(m_pimagesource->image_source_size());

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



