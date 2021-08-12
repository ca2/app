// Created by CamiloSasukeThomasBorregaardSoerensen 2021-01-23 01:07
// This is how things starts happening, promise of Life, in a virgin Temple...
// to be or not to be, or will it be or won't, that is the question....
#pragma once


enum enum_placement
{

   e_placement_stretch,
   e_placement_source, // align is meaningful
   e_placement_aspect_fit, // align is meaninful

};


class CLASS_DECL_AURA image_drawing_options :
   public color_filter
{
public:


   using color_filter::color_filter;
   using color_filter::operator=;


   enum_placement       m_eplacement;
   point_f64            m_pointAlign;
   ::rectangle_f64      m_rectangleTarget;


   image_drawing_options(const image_drawing_options & imagedrawingoptions) :
      ::color_filter(imagedrawingoptions),
      m_eplacement(imagedrawingoptions.m_eplacement),
      m_pointAlign(imagedrawingoptions.m_pointAlign),
      m_rectangleTarget(imagedrawingoptions.m_rectangleTarget)
   {

   }

   
   image_drawing_options(const ::rectangle_f64 & rectangleTarget, const ::enum_placement & eplacement = e_placement_stretch, const ::point_f64 & pointAlign = ::point_f64(0., 0.)) :
      m_rectangleTarget(rectangleTarget),
      m_eplacement(eplacement),
      m_pointAlign(pointAlign)
   {

   }


};


using image_drawing_options_pointer = __pointer(image_drawing_options);


class CLASS_DECL_AURA image_drawing :
   public ::image_drawing_options,
   public ::image_source
{
public:


   using image_drawing_options::operator=;


   image_drawing(const image_drawing & imagedrawing) :
      image_drawing_options(imagedrawing),
      image_source(imagedrawing)
   {

   }


   image_drawing(image_drawing && imagedrawing) :
      image_drawing_options(::move(imagedrawing)),
      image_source(::move(imagedrawing))
   {

   }


   image_drawing(const image_drawing_options & imagedrawingoptions, const image_source & imagesource) :
      image_drawing_options(::move(imagedrawingoptions)),
      image_source(::move(imagesource))
   {

   }


};


using image_drawing_pointer = __pointer(image_drawing);



