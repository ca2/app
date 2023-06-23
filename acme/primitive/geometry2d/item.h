// From aura/graphics/draw2d/region by camilo on 2023-06-01 06:28 <3ThomasBorregaardSorensen!!
#pragma once


//#include "_geometry2d.h"
//#include "_collection.h"
#include "polygon.h"


namespace geometry2d
{


   class CLASS_DECL_ACME item :
      virtual public ::particle
   {
   public:


      virtual ::draw2d::enum_item type() const;


      virtual void translate(const ::point_f64 & point);
      //virtual void expand_bounding_box(::rectangle_f64 & rectangle);
      virtual bool contains(const ::point_f64 & point);
      virtual void expand_bounding_box(::rectangle_f64 & rectangle);

   };


   class CLASS_DECL_ACME begin_figure_item :
      virtual public item
   {
   public:

      
      ::draw2d::enum_item type() const override;


      ::particle_pointer clone() const override
      {

         auto pitem = __new(begin_figure_item);

         return pitem;

      }



   };


   class CLASS_DECL_ACME close_figure_item :
      virtual public item
   {
   public:


      ::draw2d::enum_item type() const override;


      ::particle_pointer clone() const override
      {

         auto pitem = __new(close_figure_item);

         return pitem;

      }


   };



   class CLASS_DECL_ACME end_figure_item :
      virtual public item
   {
   public:


      ::draw2d::enum_item type() const override;


      ::particle_pointer clone() const override
      {

         auto pitem = __new(end_figure_item);

         return pitem;

      }


   };


   class CLASS_DECL_ACME intersect_clip_item :
      virtual public item
   {
   public:


      ::draw2d::enum_item type() const override;


      ::particle_pointer clone() const override
      {

         auto pitem = __new(intersect_clip_item);

         return pitem;

      }


   };


   class CLASS_DECL_ACME polygon_item :
      virtual public item
   {
   public:

      
      ::polygon_f64                          m_polygon;
      ::draw2d::enum_fill_mode               m_efillmode;


      ::draw2d::enum_item type() const override;


      //void translate(const ::point_i32 & point) override;
      //void expand_bounding_box(::rectangle_f64 & rectangle) override;
      void translate(const ::point_f64 & point) override;
      bool contains(const ::point_f64 & p) override;
      //virtual bool contains(const ::point_f64 & point) { m_item.contains(point); }
      void expand_bounding_box(::rectangle_f64 & rectangle)override;
      //void expand_bounding_box(::rectangle_f64 & rectangle) override;


      ::particle_pointer clone() const override
      {

         auto pitem = __new(polygon_item);

         pitem->m_polygon = m_polygon;

         pitem->m_efillmode = m_efillmode;

         return pitem;

      }


   };


   // using poly_polygon_item_base = item_type < ::poly_polygon_f64, ::draw2d::e_item_poly_polygon >;


   class CLASS_DECL_ACME poly_polygon_item :
      virtual public item
   {
   public:

      
      ::poly_polygon_f64                  m_polypolygon;
      ::draw2d::enum_fill_mode            m_efillmode;


      //::draw2d::enum_item type() const override;


      void translate(const ::point_f64 & point) override;
      //void expand_bounding_box(::rectangle_f64 & rectangle) override;
      bool contains(const ::point_f64 & pooint) override;
      void expand_bounding_box(::rectangle_f64 & rectangle) override;


      ::particle_pointer clone() const override
      {

         auto pitem = __new(poly_polygon_item);

         pitem->m_polypolygon = m_polypolygon;

         pitem->m_efillmode = m_efillmode;

         return pitem;

      }




   };


   class CLASS_DECL_ACME combine_item :
      virtual public item
   {
   public:

      
      ///pointer_array < ::polygon_f64 >        m_polygon;

      ::pointer < ::geometry2d::region >     m_pregion1;
      ::pointer < ::geometry2d::region >     m_pregion2;
      ::draw2d::enum_combine                 m_ecombine;


      ::draw2d::enum_item type() const override;


      void translate(const ::point_f64 & point) override;
      bool contains(const ::point_f64 & point) override;
      void expand_bounding_box(::rectangle_f64 & rectangle) override;


      ::particle_pointer clone() const override;


   };


   class CLASS_DECL_ACME round_rectangle_item :
      virtual public item
   {
   public:


      ::rectangle_f64   m_rectangle;
      ::size_f64        m_sizeRadius;


      void translate(const ::point_f64 & point) override;
      bool contains(const ::point_f64 & point) override;
      void expand_bounding_box(::rectangle_f64 & rectangle) override;


      ::particle_pointer clone() const override
      {

         auto pitem = __new(round_rectangle_item);

         pitem->m_rectangle = m_rectangle;

         pitem->m_sizeRadius = m_sizeRadius;

         return pitem;

      }

   };


} // namespace geometry2d



