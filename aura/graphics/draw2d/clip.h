//
//  clip.h
//  aura
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 17/06/2023 16:19
//
#pragma once


#include "acme/prototype/geometry2d/ellipse.h"
#include "acme/prototype/geometry2d/polygon.h"

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
      virtual public ::particle
   {
   public:

      clip_item(){}
      ~clip_item() override{}

      virtual enum_clip_item clip_item_type() const { return e_clip_item_none; }

   };

   template < typename TYPE, enum_clip_item t_eclipitem >
   class clip_item_base :
      virtual public clip_item
   {
   public:


      TYPE m_item;


      clip_item_base(){}
      ~clip_item_base() override{}

      virtual enum_clip_item clip_item_type() const  override { return t_eclipitem; }

   };

   class CLASS_DECL_AURA clip_rectangle :
      virtual public clip_item_base < ::i32_rectangle, e_clip_item_rectangle > {
   public:

      clip_rectangle();
      ~clip_rectangle() override;

   };

   class CLASS_DECL_AURA clip_ellipse :
      virtual public clip_item_base < ::f64_ellipse, e_clip_item_ellipse > {
   public:

      clip_ellipse();
      ~clip_ellipse() override;

   };

   class CLASS_DECL_AURA clip_polygon :
      virtual public clip_item_base < ::f64_polygon, e_clip_item_polygon > {
   public:

      clip_polygon();
      ~clip_polygon() override;

   };


   class CLASS_DECL_AURA clip_group :
      virtual public ::pointer_array < clip_item >
   {
   public:

      bool is_rectangle_only(::i32_rectangle_array_base& rectanglea) const
      {
         for (auto& pclipitem : *this)
         {
            switch (pclipitem->clip_item_type())
            {
            case ::draw2d::e_clip_item_rectangle:
               rectanglea.add(dynamic_cast<::draw2d::clip_rectangle*>(pclipitem.m_p)->m_item);
               break;
            case ::draw2d::e_clip_item_ellipse:
               return false;
            case ::draw2d::e_clip_item_polygon:
               return false;
            default:
               break;
            };
         }

         return true;

      }

      clip_group(){}
      ~clip_group() override {}


   };


   class CLASS_DECL_AURA clip :
      virtual public ::pointer_array <  clip_group >
   {
   public:

      clip(){}
      ~clip() override{}

   };


} // namespace draw2d
