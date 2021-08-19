// created2021-01-22 by camilo <3ThomasBS!!
#pragma once


template < typename IMAGE_SOURCE_POINTER >
concept image_source_pointer = requires(IMAGE_SOURCE_POINTER p, const concrete < ::size_i32 > & concreteSize, const ::size_f64 & sizeDst, enum_image_selection eimageselection)
{


   { p->get_image(concreteSize) } -> ::std::same_as < image * >;


   { p->size(sizeDst, eimageselection) } -> ::std::same_as < concrete < ::size_i32 > >;
   { p->size() } -> ::std::same_as < concrete < ::size_i32 > >;


};




class CLASS_DECL_AURA image_source
{
public:


   ::rectangle_f64                     m_rectangleSource;
   image_pointer                       m_pimage;

   image_source() {}

   image_source(const ::rectangle_f64 & rectangle, ::image * pimage) :
      m_rectangleSource(rectangle),
      m_pimage(pimage)
   {

   }

   image_source(const image_source & imagesource) :
      m_rectangleSource(imagesource.m_rectangleSource),
      m_pimage(imagesource.m_pimage)
   {


   }


   image_source(image_source && imagedrawing) :
      m_rectangleSource(::move(imagedrawing.m_rectangleSource)),
      m_pimage(::move(imagedrawing.m_pimage))
   {


   }

   template < image_source_pointer IMAGE_SOURCE_POINTER >
   image_source(IMAGE_SOURCE_POINTER pimagesource)
   {

      auto concreteSize = pimagesource->size();

      m_pimage = pimagesource->get_image(concreteSize);

      m_rectangleSource.set(concreteSize);

   }


   template < image_source_pointer IMAGE_SOURCE_POINTER, primitive_point POINT >
   image_source(IMAGE_SOURCE_POINTER pimagesource, const POINT & pointSrc)
   {

      auto concreteSize = pimagesource->size();

      auto sizeSrc = pimagesource->size() - pointSrc;

      m_pimage = pimagesource->get_image(concreteSize);

      m_rectangleSource.set(pointSrc, sizeSrc);

   }


   template < image_source_pointer IMAGE_SOURCE_POINTER, primitive_rectangle RECTANGLE >
   image_source(IMAGE_SOURCE_POINTER pimagesource, const RECTANGLE & rectSrc)
   {

      auto concreteSize = pimagesource->size();

      //auto sizeSrc = rectSrc.size();

      m_pimage = pimagesource->get_image(concreteSize);

      m_rectangleSource.set(rectSrc);

   }

   template < image_source_pointer IMAGE_SOURCE_POINTER, primitive_size SIZE >
   image_source(IMAGE_SOURCE_POINTER pimagesource, const SIZE & sizeSrc)
   {

      auto concreteSize = pimagesource->size();

      m_pimage = pimagesource->get_image(concreteSize);

      m_rectangleSource.set(sizeSrc);

   }


};


