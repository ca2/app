// Created by CamiloSasukeThomasBorregaardSoerensen 2021-01-23 01:07
// This is how things starts happening, promise of Life, in a virgin Temple...
// to be or not to be, or will it be or won't, that is the question....
#pragma once


class CLASS_DECL_AURA image_drawing_options :
   virtual public ::matter
{
public:

   
   color_filter_pointer       m_pcolorfilter;


   inline double opacity() const { return m_pcolorfilter.is_set() && m_pcolorfilter->opacity(); }
   inline bool is_color_matrix_filter() const { return m_pcolorfilter.is_set() && m_pcolorfilter->is_color_matrix_filter(); };


   bool get_color_matrix(color_matrix & matrix) const;


};


using image_drawing_options_pointer = __pointer(image_drawing_options);


class CLASS_DECL_AURA image_drawing :
   virtual public ::image_drawing_options
{
public:


   ::rectd                    m_rectDst;
   ::rectd                    m_rectSrc;
   image_pointer              m_pimage;

   
   image_drawing() {}
   virtual ~image_drawing();


   template < primitive_point POINT, image_source_pointer IMAGE_SOURCE_POINTER >
   image_drawing(const POINT & pointDst, IMAGE_SOURCE_POINTER pimagesource)
   {

      auto concreteSize = pimagesource->size();

      m_pimage = pimagesource->get_image(m_rectSrc.size());

      m_rectDst.set(pointDst, concreteSize);

      m_rectSrc.set(concreteSize);

   }


   template < image_source_pointer IMAGE_SOURCE_POINTER >
   image_drawing(IMAGE_SOURCE_POINTER pimagesource)
   {

      auto concreteSize = pimagesource->size();

      m_pimage = pimagesource->get_image(concreteSize);

      m_rectDst.set(concreteSize);

      m_rectSrc.set(concreteSize);

   }


   template < image_source_pointer IMAGE_SOURCE_POINTER, primitive_point POINT >
   image_drawing(IMAGE_SOURCE_POINTER pimagesource, const POINT & pointSrc, enum_image_selection eimageselection = ::e_image_selection_default)
   {

      auto concreteSize = pimagesource->size();

      auto sizeSrc = pimagesource->size() - pointSrc;

      m_pimage = pimagesource->get_image(concreteSize);

      m_rectDst.set(sizeSrc);

      m_rectSrc.set(pointSrc, sizeSrc);

   }


   template < primitive_size SIZE, image_source_pointer IMAGE_SOURCE_POINTER >
   image_drawing(const SIZE & sizeDst, IMAGE_SOURCE_POINTER pimagesource, enum_image_selection eimageselection = e_image_selection_default)
   {

      auto concreteSize = pimagesource->size(sizeDst, eimageselection);

      m_pimage = pimagesource->get_image(concreteSize);

      m_rectDst.set(sizeDst);

      m_rectSrc.set(concreteSize);

   }


   template < primitive_size SIZE, image_source_pointer IMAGE_SOURCE_POINTER, primitive_point POINT >
   image_drawing(const SIZE & sizeDst, IMAGE_SOURCE_POINTER pimagesource, const POINT & pointSrc, enum_image_selection eimageselection)
   {

      auto concreteSize = pimagesource->size();

      auto sizeSrc = sizeDst;

      m_pimage = pimagesource->get_image(concreteSize);

      m_rectDst.set(sizeDst);

      m_rectSrc.set(pointSrc, sizeSrc);

   }


   template < primitive_size SIZE, image_source_pointer IMAGE_SOURCE_POINTER, primitive_rectangle RECTANGLE >
   image_drawing(const SIZE & sizeDst, IMAGE_SOURCE_POINTER pimagesource, const RECTANGLE & rectSrc, enum_image_selection eimageselection = e_image_selection_default)
   {

      auto concreteSize = pimagesource->size();

      m_pimage = pimagesource->get_image(concreteSize);

      m_rectDst.set(sizeDst);

      m_rectSrc.set(rectSrc);

   }


   template < primitive_size SIZE, image_source_pointer IMAGE_SOURCE_POINTER, primitive_point POINT >
   image_drawing(const SIZE & sizeDst, IMAGE_SOURCE_POINTER pimagesource, const POINT & pointSrc)
   {

      auto concreteSize = pimagesource->size();

      auto sizeSrc = concreteSize - pointSrc;

      m_pimage = pimagesource->get_image(concreteSize);

      m_rectDst.set(sizeDst);

      m_rectSrc.set(sizeSrc);

   }


   template < primitive_rectangle RECTANGLE, image_source_pointer IMAGE_SOURCE_POINTER >
   image_drawing(const RECTANGLE & rectDst, IMAGE_SOURCE_POINTER pimagesource)
   {

      auto concreteSize = pimagesource->size();

      auto sizeDst = ::size(rectDst);

      m_pimage = pimagesource->get_image(concreteSize);

      m_rectDst.set(rectDst);

      m_rectSrc.set(sizeDst);

   }


   template < primitive_rectangle RECTANGLE, image_source_pointer IMAGE_SOURCE_POINTER >
   image_drawing(const RECTANGLE & rectDst, IMAGE_SOURCE_POINTER pimagesource, enum_image_selection eimageselection)
   {

      auto sizeDst = ::size(rectDst);

      auto concreteSize = pimagesource->size(sizeDst, eimageselection);

      m_pimage = pimagesource->get_image(concreteSize);

      m_rectDst.set(rectDst);

      m_rectSrc.set(concreteSize);

   }


   template < primitive_rectangle RECTANGLE, image_source_pointer IMAGE_SOURCE_POINTER, primitive_point POINT >
   image_drawing(const RECTANGLE & rectDst, IMAGE_SOURCE_POINTER pimagesource, const POINT & pointSrc)
   {

      auto concreteSize = pimagesource->size();

      m_pimage = pimagesource->get_image(concreteSize);

      m_rectDst.set(rectDst);

      m_rectSrc.set(pointSrc, concreteSize);

   }


   template < primitive_rectangle RECTANGLE_DST, image_source_pointer IMAGE_SOURCE_POINTER, primitive_rectangle RECTANGLE_SRC >
   image_drawing(const RECTANGLE_DST & rectDst, IMAGE_SOURCE_POINTER pimagesource, const RECTANGLE_SRC & rectSrc)
   {

      auto concreteSize = pimagesource->size();

      auto sizeDst = ::size(rectSrc);

      m_pimage = pimagesource->get_image(concreteSize);

      m_rectDst.set(rectDst);

      m_rectSrc.set(rectSrc);

   }


   template < primitive_size SIZE_DST, image_source_pointer IMAGE_SOURCE_POINTER, primitive_size SIZE_SRC >
   image_drawing(const SIZE_DST & sizeDst, IMAGE_SOURCE_POINTER pimagesource, const SIZE_SRC & sizeSrc)
   {

      auto concreteSize = pimagesource->size();

      m_pimage = pimagesource->get_image(concreteSize);

      m_rectDst.set(sizeDst);

      m_rectSrc.set(sizeSrc);

   }


};


using image_drawing_pointer = __pointer(image_drawing);



