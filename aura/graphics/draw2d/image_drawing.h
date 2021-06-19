// Created by CamiloSasukeThomasBorregaardSoerensen 2021-01-23 01:07
// This is how things starts happening, promise of Life, in a virgin Temple...
// to be or not to be, or will it be or won't, that is the question....
#pragma once


class CLASS_DECL_AURA image_drawing_options :
   public color_filter
{
public:


   using color_filter::color_filter;
   using color_filter::operator=;


};


using image_drawing_options_pointer = __pointer(image_drawing_options);


class CLASS_DECL_AURA image_drawing :
   public ::image_drawing_options
{
public:


   ::rectangle_f64                     m_rectDst;
   ::rectangle_f64                     m_rectSrc;
   image_pointer                       m_pimage;


   using image_drawing_options::image_drawing_options;
   using image_drawing_options::operator=;


   template < primitive_point POINT, image_source_pointer IMAGE_SOURCE_POINTER >
   void set(const POINT & pointDst, IMAGE_SOURCE_POINTER pimagesource)
   {

      auto concreteSize = pimagesource->size();

      m_pimage = pimagesource->get_image(concreteSize);

      m_rectDst.set(pointDst, concreteSize);

      m_rectSrc.set(concreteSize);

   }


   template < image_source_pointer IMAGE_SOURCE_POINTER >
   void set(IMAGE_SOURCE_POINTER pimagesource)
   {

      auto concreteSize = pimagesource->size();

      m_pimage = pimagesource->get_image(concreteSize);

      m_rectDst.set(concreteSize);

      m_rectSrc.set(concreteSize);

   }


   template < image_source_pointer IMAGE_SOURCE_POINTER, primitive_point POINT >
   void set(IMAGE_SOURCE_POINTER pimagesource, const POINT & pointSrc)
   {

      auto concreteSize = pimagesource->size();

      auto sizeSrc = pimagesource->size() - pointSrc;

      m_pimage = pimagesource->get_image(concreteSize);

      m_rectDst.set(sizeSrc);

      m_rectSrc.set(pointSrc, sizeSrc);

   }


   template < image_source_pointer IMAGE_SOURCE_POINTER, primitive_rectangle RECTANGLE >
   void set(IMAGE_SOURCE_POINTER pimagesource, const RECTANGLE & rectSrc)
   {

      auto concreteSize = pimagesource->size();

      auto sizeSrc = rectSrc.size();

      m_pimage = pimagesource->get_image(concreteSize);

      m_rectDst.set(sizeSrc);

      m_rectSrc.set(rectSrc);

   }


   template < primitive_size SIZE, image_source_pointer IMAGE_SOURCE_POINTER >
   void set(const SIZE & sizeDst, IMAGE_SOURCE_POINTER pimagesource)
   {

      auto concreteSize = pimagesource->size();

      m_pimage = pimagesource->get_image(concreteSize);

      m_rectDst.set(sizeDst);

      m_rectSrc.set(sizeDst);

   }


   template < primitive_size SIZE, image_source_pointer IMAGE_SOURCE_POINTER, primitive_point POINT >
   void set(const SIZE & sizeDst, IMAGE_SOURCE_POINTER pimagesource, const POINT & pointSrc)
   {

      auto concreteSize = pimagesource->size();

      auto sizeSrc = sizeDst;

      m_pimage = pimagesource->get_image(concreteSize);

      m_rectDst.set(sizeDst);

      m_rectSrc.set(pointSrc, sizeSrc);

   }


   template < primitive_size SIZE, image_source_pointer IMAGE_SOURCE_POINTER, primitive_rectangle RECTANGLE >
   void set(const SIZE & sizeDst, IMAGE_SOURCE_POINTER pimagesource, const RECTANGLE & rectSrc, enum_image_selection eimageselection = e_image_selection_default)
   {

      auto concreteSize = pimagesource->size();

      m_pimage = pimagesource->get_image(concreteSize);

      m_rectDst.set(sizeDst);

      m_rectSrc.set(rectSrc);

   }


   template < primitive_rectangle RECTANGLE, image_source_pointer IMAGE_SOURCE_POINTER >
   void set(const RECTANGLE & rectDst, IMAGE_SOURCE_POINTER pimagesource)
   {

      auto concreteSize = pimagesource->size();

      auto sizeDst = ::size_i32(rectDst);

      m_pimage = pimagesource->get_image(concreteSize);

      m_rectDst.set(rectDst);

      m_rectSrc.set(sizeDst);

   }


   template < primitive_rectangle RECTANGLE, image_source_pointer IMAGE_SOURCE_POINTER >
   void set(const RECTANGLE & rectDst, IMAGE_SOURCE_POINTER pimagesource, enum_image_selection eimageselection)
   {

      auto sizeDst = ::size_i32(rectDst);

      auto concreteSize = pimagesource->size(sizeDst, eimageselection);

      m_pimage = pimagesource->get_image(concreteSize);

      m_rectDst.set(rectDst);

      m_rectSrc.set(concreteSize);

   }


   template < primitive_rectangle RECTANGLE, image_source_pointer IMAGE_SOURCE_POINTER, primitive_point POINT >
   void set(const RECTANGLE & rectDst, IMAGE_SOURCE_POINTER pimagesource, const POINT & pointSrc)
   {

      auto concreteSize = pimagesource->size();

      m_pimage = pimagesource->get_image(concreteSize);

      m_rectDst.set(rectDst);

      m_rectSrc.set(pointSrc, rectDst.size());

   }


   template < primitive_rectangle RECTANGLE_DST, image_source_pointer IMAGE_SOURCE_POINTER, primitive_rectangle RECTANGLE_SRC >
   void set(const RECTANGLE_DST & rectDst, IMAGE_SOURCE_POINTER pimagesource, const RECTANGLE_SRC & rectSrc)
   {

      auto concreteSize = pimagesource->size();

      //auto sizeDst = ::size_i32(rectSrc);

      m_pimage = pimagesource->get_image(concreteSize);

      m_rectDst.set(rectDst);

      m_rectSrc.set(rectSrc);

   }


   template < primitive_size SIZE_DST, image_source_pointer IMAGE_SOURCE_POINTER, primitive_size SIZE_SRC >
   void set(const SIZE_DST & sizeDst, IMAGE_SOURCE_POINTER pimagesource, const SIZE_SRC & sizeSrc)
   {

      auto concreteSize = pimagesource->size();

      m_pimage = pimagesource->get_image(concreteSize);

      m_rectDst.set(sizeDst);

      m_rectSrc.set(sizeSrc);

   }


};


using image_drawing_pointer = __pointer(image_drawing);



