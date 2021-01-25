// Created by CamiloSasukeThomasBorregaardSoerensen 2021-01-23 00
// This is how things starts happening, promise of Life, in a virgin Temple...
// to be or not to be, or will it be or won't, that is the question....
#pragma once


class CLASS_DECL_AURA image_drawer :
   virtual public ::matter
{
public:


   template < primitive_point POINT, image_source_pointer IMAGE_SOURCE_POINTER >
   inline bool draw(const POINT & pointDst, IMAGE_SOURCE_POINTER pimagesource)
   {

      image_drawing imagedrawing(pointDst, pimagesource);

      return draw(imagedrawing);

   }


   template < image_source_pointer IMAGE_SOURCE_POINTER >
   inline bool draw(IMAGE_SOURCE_POINTER pimagesource)
   {

      image_drawing imagedrawing(pimagesource);

      return draw(imagedrawing);

   }


   template < primitive_point POINT, image_source_pointer IMAGE_SOURCE_POINTER >
   inline bool draw(IMAGE_SOURCE_POINTER pimagesource, const POINT & pointSrc, enum_image_selection eimageselection = ::e_image_selection_default)
   {

      image_drawing imagedrawing(pimagesource, pointSrc, eimageselection);

      return draw(imagedrawing);

   }


   template < primitive_size SIZE, image_source_pointer IMAGE_SOURCE_POINTER >
   inline bool stretch(const SIZE & sizeDst, IMAGE_SOURCE_POINTER pimagesource, enum_image_selection eimageselection = e_image_selection_default)
   {

      image_drawing imagedrawing(sizeDst, pimagesource, eimageselection);

      return draw(imagedrawing);

   }


   template < primitive_size SIZE, image_source_pointer IMAGE_SOURCE_POINTER, primitive_point POINT >
   inline bool stretch(const SIZE & sizeDst, IMAGE_SOURCE_POINTER pimagesource, const POINT & pointSrc, enum_image_selection eimageselection)
   {

      image_drawing imagedrawing(sizeDst, pimagesource, pointSrc, eimageselection);

      return draw(imagedrawing);

   }


   template < primitive_size SIZE, image_source_pointer IMAGE_SOURCE_POINTER, primitive_rectangle RECTANGLE >
   inline bool stretch(const SIZE & sizeDst, IMAGE_SOURCE_POINTER pimagesource, const RECTANGLE & rectSrc, enum_image_selection eimageselection = e_image_selection_default)
   {

      image_drawing imagedrawing(sizeDst, pimagesource, rectSrc, eimageselection);

      return draw(imagedrawing);

   }


   template < primitive_size SIZE, image_source_pointer IMAGE_SOURCE_POINTER, primitive_point POINT >
   inline bool draw(const SIZE & sizeDst, IMAGE_SOURCE_POINTER pimagesource, const POINT & pointSrc, enum_image_selection eimageselection = e_image_selection_default)
   {

      image_drawing imagedrawing(sizeDst, pimagesource, pointSrc, eimageselection);

      return draw(imagedrawing);

   }


   template < primitive_rectangle RECTANGLE, image_source_pointer IMAGE_SOURCE_POINTER >
   inline bool draw(const RECTANGLE & rectDst, IMAGE_SOURCE_POINTER pimagesource)
   {
      
      image_drawing imagedrawing(rectDst, pimagesource);

      return draw(imagedrawing);

   }


   template < primitive_rectangle RECTANGLE, image_source_pointer IMAGE_SOURCE_POINTER >
   inline bool stretch(const RECTANGLE & rectDst, IMAGE_SOURCE_POINTER pimagesource, enum_image_selection eimageselection = e_image_selection_default)
   {

      image_drawing imagedrawing(rectDst, pimagesource, eimageselection);

      return draw(imagedrawing);

   }


   template < primitive_rectangle RECTANGLE, image_source_pointer IMAGE_SOURCE_POINTER, primitive_point POINT >
   inline bool draw(const RECTANGLE & rectDst, IMAGE_SOURCE_POINTER pimagesource, const POINT & pointSrc)
   {

      image_drawing imagedrawing(rectDst, pimagesource, pointSrc);

      return draw(imagedrawing);

   }


   template < primitive_rectangle RECTANGLE_DST, image_source_pointer IMAGE_SOURCE_POINTER, primitive_rectangle RECTANGLE_SRC >
   inline bool stretch(const RECTANGLE_DST & rectDst, IMAGE_SOURCE_POINTER pimagesource, const RECTANGLE_SRC & rectSrc)
   {

      image_drawing imagedrawing(rectDst, pimagesource, rectSrc);

      return draw(imagedrawing);

   }


   template < primitive_size SIZE_DST, image_source_pointer IMAGE_SOURCE_POINTER, primitive_size SIZE_SRC >
   inline bool stretch(const SIZE_DST & sizeDst, IMAGE_SOURCE_POINTER pimagesource, const SIZE_SRC & sizeSrc)
   {

      image_drawing imagedrawing(sizeDst, pimagesource, sizeSrc);

      return draw(imagedrawing);

   }


   virtual bool draw(const image_drawing & imagedrawing);


   virtual bool _draw_blend(const image_drawing & imagedrawing) = 0;
   virtual bool _draw_raw(const image_drawing & imagedrawing);

   
   virtual bool _draw_raw(const ::rectd & rectDst, image * pimage, const image_drawing_options & imagedrawingoptions, const ::pointd & pointSrc);
   virtual bool _stretch_raw(const ::rectd & rectDst, image * pimage, const image_drawing_options & imagedrawingoptions, const ::rectd & rectSrc);


};



