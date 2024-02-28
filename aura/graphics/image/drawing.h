// Created by CamiloSasukeThomasBorregaardSoerensen 2021-01-23 01:07
// This is how things starts happening, promise of Life, in a virgin Temple...
// to be or not to be, or will it be or won't, that is the question....
#pragma once


#include "aura/graphics/draw2d/color_filter.h"
#include "source.h"
//#include "image.h"


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


   enum_image_selection    m_eimageselection;
   enum_placement          m_eplacement;
   point_f64               m_pointAlign;
   ::rectangle_f64         m_rectangleTarget;
   bool                    m_bIntegerPlacement = false;


   image_drawing_options();
   image_drawing_options(const image_drawing_options & imagedrawingoptions);
   
   explicit image_drawing_options(const ::rectangle_f64 & rectangleTarget, const ::enum_placement & eplacement = e_placement_stretch, const ::point_f64 & pointAlign = ::point_f64(0., 0.), enum_image_selection eimageselection = e_image_selection_default);


};


class CLASS_DECL_AURA image_drawing :
   public ::image_drawing_options,
   public ::image_source
{
public:

   bool m_bDoForAllFrames = false;


   using ::image_drawing_options::operator=;


   image_drawing(const ::image_drawing & imagedrawing) ;


   image_drawing(::image_drawing && imagedrawing) noexcept;


   image_drawing(const ::image_drawing_options & imagedrawingoptions, const ::image_source & imagesource);
   
   image_drawing(const ::image_source & imagesource);
   
   ::rectangle_f64 source_rectangle() const;

   ::rectangle_f64 target_rectangle() const;
   

   ::image_pointer image() const;


};


using image_drawing_pointer = ::pointer<image_drawing>;



