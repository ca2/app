// Created by CamiloSasukeThomasBorregaardSoerensen 2021-01-23 00
// This is how things starts happening, promise of Life, in a virgin Temple...
// to be or not to be, or will it be or won't, that is the question....
#pragma once


//#include "acme/prototype/geometry2d/_geometry2d.h"
//#include "acme/prototype/prototype/matter.h"


namespace image
{


   class CLASS_DECL_AURA image_drawer :
      virtual public ::matter
   {
   public:


      //template < primitive_point POINT, ::image::image_source_pointer IMAGE_SOURCE_POINTER >
      //inline void draw(const POINT & pointDst, IMAGE_SOURCE_POINTER pimagesource, ::image::image_drawing imagedrawing = nullptr)
      //{

      //   imagedrawing.set(pointDst, pimagesource);

      //   return draw(imagedrawing);

      //}


      //template < ::image::image_source_pointer IMAGE_SOURCE_POINTER >
      //inline void draw(IMAGE_SOURCE_POINTER pimagesource, ::image::image_drawing imagedrawing = nullptr)
      //{

      //   imagedrawing.set(pimagesource);

      //   return draw(imagedrawing);

      //}


      //template < primitive_point POINT, ::image::image_source_pointer IMAGE_SOURCE_POINTER >
      //inline void draw(IMAGE_SOURCE_POINTER pimagesource, const POINT & pointSrc, ::image::image_drawing imagedrawing = nullptr)
      //{

      //   imagedrawing.set(pimagesource, pointSrc);

      //   return draw(imagedrawing);

      //}

      //template < primitive_rectangle RECTANGLE, ::image::image_source_pointer IMAGE_SOURCE_POINTER >
      //inline void draw(IMAGE_SOURCE_POINTER pimagesource, const RECTANGLE & rectangleSource, ::image::image_drawing imagedrawing = nullptr)
      //{

      //   imagedrawing.set(pimagesource, rectangleSource);

      //   return draw(imagedrawing);

      //}


      //template < primitive_size SIZE, ::image::image_source_pointer IMAGE_SOURCE_POINTER, primitive_point POINT >
      //inline void draw(const SIZE & sizeDst, IMAGE_SOURCE_POINTER pimagesource, ::image::image_drawing imagedrawing = nullptr)
      //{

      //   imagedrawing.set(sizeDst, pimagesource);

      //   return draw(imagedrawing);

      //}


      //template < primitive_size SIZE, ::image::image_source_pointer IMAGE_SOURCE_POINTER, primitive_point POINT >
      //inline void draw(const SIZE & sizeDst, IMAGE_SOURCE_POINTER pimagesource, const POINT & pointSrc, ::image::image_drawing imagedrawing = nullptr)
      //{

      //   imagedrawing.set(sizeDst, pimagesource, pointSrc);

      //   return draw(imagedrawing);

      //}


      //template < primitive_rectangle RECTANGLE, ::image::image_source_pointer IMAGE_SOURCE_POINTER >
      //inline void draw(const RECTANGLE & rectangleTarget, IMAGE_SOURCE_POINTER pimagesource, ::image::image_drawing imagedrawing = nullptr)
      //{

      //   imagedrawing.set(rectangleTarget, pimagesource);

      //   return draw(imagedrawing);

      //}


      //template < primitive_rectangle RECTANGLE, ::image::image_source_pointer IMAGE_SOURCE_POINTER, primitive_point POINT >
      //inline void draw(const RECTANGLE & rectangleTarget, IMAGE_SOURCE_POINTER pimagesource, const POINT & pointSrc, ::image::image_drawing imagedrawing = nullptr)
      //{

      //   imagedrawing.set(rectangleTarget, pimagesource, pointSrc);

      //   return draw(imagedrawing);

      //}


      //template < primitive_size SIZE, ::image::image_source_pointer IMAGE_SOURCE_POINTER >
      //inline void draw(const SIZE & sizeDst, IMAGE_SOURCE_POINTER pimagesource, ::image::image_drawing imagedrawing = nullptr)
      //{

      //   imagedrawing.set(sizeDst, pimagesource);

      //   return draw(imagedrawing);

      //}


      //template < ::image::image_source_pointer IMAGE_SOURCE_POINTER, primitive_rectangle RECTANGLE >
      //inline void stretch(IMAGE_SOURCE_POINTER pimagesource, const RECTANGLE & rectangleSource, enum_image_selection eimageselection = e_image_selection_default, ::image::image_drawing imagedrawing = nullptr)
      //{

      //   imagedrawing.set(get_image_drawer_size(), pimagesource, rectangleSource, eimageselection);

      //   return draw(imagedrawing);

      //}


      //template < ::image::image_source_pointer IMAGE_SOURCE_POINTER, primitive_size SIZE_SRC >
      //inline void stretch(IMAGE_SOURCE_POINTER pimagesource, const SIZE_SRC & sizeSrc, ::image::image_drawing imagedrawing = nullptr)
      //{

      //   imagedrawing.set(get_image_drawer_size(), pimagesource, sizeSrc);

      //   return draw(imagedrawing);

      //}


      //template < primitive_size SIZE, ::image::image_source_pointer IMAGE_SOURCE_POINTER >
      //inline void stretch(const SIZE & sizeDst, IMAGE_SOURCE_POINTER pimagesource, ::image::image_drawing imagedrawing = nullptr)
      //{

      //   imagedrawing.set(sizeDst, pimagesource, pimagesource->size());

      //   return draw(imagedrawing);

      //}


      //template < primitive_size SIZE, ::image::image_source_pointer IMAGE_SOURCE_POINTER, primitive_rectangle RECTANGLE >
      //inline void stretch(const SIZE & sizeDst, IMAGE_SOURCE_POINTER pimagesource, const RECTANGLE & rectangleSource, enum_image_selection eimageselection = e_image_selection_default, ::image::image_drawing imagedrawing = nullptr)
      //{

      //   imagedrawing.set(sizeDst, pimagesource, rectangleSource, eimageselection);

      //   return draw(imagedrawing);

      //}


      //template < primitive_rectangle RECTANGLE, ::image::image_source_pointer IMAGE_SOURCE_POINTER >
      //inline void stretch(const RECTANGLE & rectangleTarget, IMAGE_SOURCE_POINTER pimagesource, enum_image_selection eimageselection = e_image_selection_default, ::image::image_drawing imagedrawing = nullptr)
      //{

      //   imagedrawing.set(rectangleTarget, pimagesource, eimageselection);

      //   return draw(imagedrawing);

      //}


      //template < primitive_rectangle RECTANGLE_DST, ::image::image_source_pointer IMAGE_SOURCE_POINTER, primitive_rectangle RECTANGLE_SRC >
      //inline void stretch(const RECTANGLE_DST & rectangleTarget, IMAGE_SOURCE_POINTER pimagesource, const RECTANGLE_SRC & rectangleSource, ::image::image_drawing imagedrawing = nullptr)
      //{

      //   imagedrawing.set(rectangleTarget, pimagesource, rectangleSource);

      //   return draw(imagedrawing);

      //}


      //template < primitive_size SIZE_DST, ::image::image_source_pointer IMAGE_SOURCE_POINTER, primitive_size SIZE_SRC >
      //inline void stretch(const SIZE_DST & sizeDst, IMAGE_SOURCE_POINTER pimagesource, const SIZE_SRC & sizeSrc, ::image::image_drawing imagedrawing = nullptr)
      //{

      //   imagedrawing.set(sizeDst, pimagesource, sizeSrc);

      //   return draw(imagedrawing);

      //}


      virtual ::int_size get_image_drawer_size() const = 0;


      virtual void draw(const ::image::image_drawing & imagedrawing);

      //virtual void stretch(const ::image::image_source & imagesource);


      virtual bool has_blender() const;

      virtual bool _draw_blend(const ::image::image_drawing & imagedrawing) = 0;
      virtual void _draw_raw(const ::image::image_drawing & imagedrawing);


      virtual void _draw_raw(const ::double_rectangle & rectangleTarget, ::image::image *pimage, const ::image::image_drawing_options & imagedrawingoptions, const ::double_point & pointSrc);
      virtual void _stretch_raw(const ::double_rectangle & rectangleTarget, ::image::image *pimage, const ::image::image_drawing_options & imagedrawingoptions, const ::double_rectangle & rectangleSource);


   };


} // namespace image



