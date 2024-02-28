//
//  clip.h
//  aura
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 17/06/2023 16:19
//
#pragma once


namespace draw2d
{

   enum enum_clip_item
   {
      e_clip_item_none,
      e_clip_item_rectangle,
      e_clip_item_ellipse,
      e_clip_item_polygon,
   };

   class CLASS_DECL_AURA clip_item :
      public ::particle
   {
   public:

      virtual enum_clip_item clip_item_type() const { return e_clip_item_none; }

   };

   template < typename TYPE, enum_clip_item t_eclipitem >
   class clip_item_base :
      public clip_item
   {
   public:


      TYPE m_item;

      virtual enum_clip_item clip_item_type() const { return t_eclipitem; }

   };

   using clip_rectangle = clip_item_base < ::rectangle_i32, e_clip_item_rectangle >;
   using clip_ellipse = clip_item_base < ::ellipse_f64, e_clip_item_ellipse >;
   using clip_polygon = clip_item_base < ::polygon_f64, e_clip_item_polygon >;


   class CLASS_DECL_AURA clip_group :
      public ::pointer_array < clip_item >
   {
   public:

   };


   class CLASS_DECL_AURA clip :
      public ::pointer_array <  clip_group >
   {
   public:


   };


} // namespace draw2d
