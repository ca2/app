//
//  drawing.cpp
//  aura
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 23/05/23.
//
#include "framework.h"
#include "drawing.h"


image_drawing_options::image_drawing_options() :
   m_eimageselection(e_image_selection_default),
   m_eplacement(e_placement_stretch)
{


}



image_drawing_options::image_drawing_options(const image_drawing_options & imagedrawingoptions) :
   color_filter(imagedrawingoptions),
   m_eimageselection(imagedrawingoptions.m_eimageselection),
   m_rectangleTarget(imagedrawingoptions.m_rectangleTarget),
   m_eplacement(imagedrawingoptions.m_eplacement),
   m_pointAlign(imagedrawingoptions.m_pointAlign),
   m_bIntegerPlacement(imagedrawingoptions.m_bIntegerPlacement)
{


}


image_drawing_options::image_drawing_options(const ::rectangle_f64 & rectangleTarget, const ::enum_placement & eplacement, const ::point_f64 & pointAlign, enum_image_selection eimageselection) :
   m_rectangleTarget(rectangleTarget),
   m_eplacement(eplacement),
   m_pointAlign(pointAlign),
   m_eimageselection(eimageselection)
{

}



image_drawing::image_drawing(const ::image_drawing & imagedrawing) :
   image_drawing_options(imagedrawing),
   image_source(imagedrawing)
{

}


image_drawing::image_drawing(::image_drawing && imagedrawing) noexcept:
   image_drawing_options(::transfer(imagedrawing)),
   image_source(::transfer(imagedrawing))
{

}



image_drawing::image_drawing(const ::image_drawing_options & imagedrawingoptions, const ::image_source & imagesource) :
   ::image_drawing_options(imagedrawingoptions),
   ::image_source(imagesource)
{

}



image_drawing::image_drawing(const ::image_source & imagesource) :
   ::image_source(imagesource)
{

}

::rectangle_f64 image_drawing::source_rectangle() const
{

   if (m_esubimage == e_sub_image_rate)
   {

      auto sizeTarget = m_rectangleTarget.size() / m_rectangleSubImage.size();

      auto size = m_pimagesource->image_source_size(sizeTarget, m_eimageselection);

      return ::rectangle_f64(
         m_rectangleSubImage.left * size.cx(),
         m_rectangleSubImage.top * size.cy(),
         m_rectangleSubImage.right * size.cx(),
         m_rectangleSubImage.bottom * size.cy());

   }
   else if (m_esubimage == e_sub_image_coordinates)
   {

      // I hope you know you are doing

      return m_rectangleSubImage;

   }
   else
   {

      auto sizeTarget(m_rectangleTarget.size());

      return ::rectangle_f64(m_pimagesource->image_source_size(sizeTarget, m_eimageselection));

   }

}



::rectangle_f64 image_drawing::target_rectangle() const
{

   if (m_eplacement == e_placement_stretch)
   {

      return m_rectangleTarget;

   }
   else if (m_eplacement == e_placement_source)
   {

      auto rectangle = source_rectangle();

      rectangle.align_rate(m_pointAlign.x(), m_pointAlign.y(), m_rectangleTarget);

      return rectangle;

   }
   else if (m_eplacement == e_placement_aspect_fit)
   {

      auto rectangle = source_rectangle();

      rectangle.aspect_align_fit(m_pointAlign.x(), m_pointAlign.y(), m_rectangleTarget);

      return rectangle;

   }
   else
   {

      throw "invalid image_drawing::m_eplacement";

   }

}




::image_pointer image_drawing::image() const
{

   if (m_esubimage == e_sub_image_rate)
   {

      auto sizeTarget = m_rectangleTarget.size() / m_rectangleSubImage.size();

      auto concreteSize = m_pimagesource->image_source_size(sizeTarget, m_eimageselection);

      return m_pimagesource->image_source_image(concreteSize);

   }
   else if (m_esubimage == e_sub_image_coordinates)
   {

      auto concreteSize = m_pimagesource->image_source_size();

      return m_pimagesource->image_source_image(concreteSize);

   }
   else
   {

      auto sizeTarget = m_rectangleTarget.size();

      auto concreteSize = m_pimagesource->image_source_size(sizeTarget, m_eimageselection);

      return m_pimagesource->image_source_image(concreteSize);

   }

}



