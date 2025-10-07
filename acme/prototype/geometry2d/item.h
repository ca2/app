// From aura/graphics/draw2d/region by camilo on 2023-06-01 06:28 <3ThomasBorregaardSorensen!!
#pragma once


//#include "_geometry2d.h"
//#include "_collection.h"
#include "polygon.h"


namespace geometry2d
{


   class CLASS_DECL_ACME item :
      virtual public ::subparticle
   {
   public:


      item();
      ~item() override;


      virtual ::draw2d::enum_item type() const;


      virtual void translate(const ::double_point & point);
      //virtual void expand_bounding_box(::double_rectangle & rectangle);
      virtual bool contains(const ::double_point & point);
      virtual void expand_bounding_box(::double_rectangle & rectangle);

   };


   class CLASS_DECL_ACME begin_figure_item :
      virtual public item
   {
   public:


      begin_figure_item();
      ~begin_figure_item() override;
      
      ::draw2d::enum_item type() const override;


      ::subparticle_pointer clone() override
      {

         auto pitem = øallocate begin_figure_item();

         return pitem;

      }



   };


   class CLASS_DECL_ACME close_figure_item :
      virtual public item
   {
   public:


      close_figure_item();
      ~close_figure_item() override;

      ::draw2d::enum_item type() const override;


      ::subparticle_pointer clone() override
      {

         auto pitem = øallocate close_figure_item();

         return pitem;

      }


   };



   class CLASS_DECL_ACME end_figure_item :
      virtual public item
   {
   public:


      end_figure_item();
      ~end_figure_item() override;

      ::draw2d::enum_item type() const override;


      ::subparticle_pointer clone() override
      {

         auto pitem = øallocate end_figure_item();

         return pitem;

      }


   };


   class CLASS_DECL_ACME intersect_clip_item :
      virtual public item
   {
   public:


      intersect_clip_item();
      ~intersect_clip_item() override;

      ::draw2d::enum_item type() const override;


      ::subparticle_pointer clone() override
      {

         auto pitem = øallocate intersect_clip_item();

         return pitem;

      }


   };


   class CLASS_DECL_ACME polygon_item :
      virtual public item
   {
   public:

      polygon_item();
      ~polygon_item() override;

      
      ::double_polygon                          m_polygon;
      ::draw2d::enum_fill_mode               m_efillmode;


      ::draw2d::enum_item type() const override;


      //void translate(const ::int_point & point) override;
      //void expand_bounding_box(::double_rectangle & rectangle) override;
      void translate(const ::double_point & point) override;
      bool contains(const ::double_point & p) override;
      //virtual bool contains(const ::double_point & point) { m_item.contains(point); }
      void expand_bounding_box(::double_rectangle & rectangle)override;
      //void expand_bounding_box(::double_rectangle & rectangle) override;


      ::subparticle_pointer clone() override
      {

         auto pitem = øallocate polygon_item();

         pitem->m_polygon = m_polygon;

         pitem->m_efillmode = m_efillmode;

         return pitem;

      }


   };


   // using poly_polygon_item_base = item_type < ::double_poly_polygon, ::draw2d::e_item_poly_polygon >;


   class CLASS_DECL_ACME poly_polygon_item :
      virtual public item
   {
   public:

      
      ::double_poly_polygon                  m_polypolygon;
      ::draw2d::enum_fill_mode            m_efillmode;

      poly_polygon_item();
      ~poly_polygon_item() override;
      //::draw2d::enum_item type() const override;


      void translate(const ::double_point & point) override;
      //void expand_bounding_box(::double_rectangle & rectangle) override;
      bool contains(const ::double_point & pooint) override;
      void expand_bounding_box(::double_rectangle & rectangle) override;


      ::subparticle_pointer clone() override
      {

         auto pitem = øallocate poly_polygon_item();

         pitem->m_polypolygon = m_polypolygon;

         pitem->m_efillmode = m_efillmode;

         return pitem;

      }




   };


   class CLASS_DECL_ACME combine_item :
      virtual public item
   {
   public:

      
      ///pointer_array < ::double_polygon >        m_polygon;

      ::pointer < ::geometry2d::region >     m_pregion1;
      ::pointer < ::geometry2d::region >     m_pregion2;
      ::draw2d::enum_combine                 m_ecombine;
      combine_item();
      ~combine_item() override;

      ::draw2d::enum_item type() const override;


      void translate(const ::double_point & point) override;
      bool contains(const ::double_point & point) override;
      void expand_bounding_box(::double_rectangle & rectangle) override;


      ::subparticle_pointer clone() override;


   };


   class CLASS_DECL_ACME round_rectangle_item :
      virtual public item
   {
   public:


      ::double_rectangle   m_rectangle;
      ::double_size        m_sizeRadius;


      void translate(const ::double_point & point) override;
      bool contains(const ::double_point & point) override;
      void expand_bounding_box(::double_rectangle & rectangle) override;


      ::subparticle_pointer clone() override
      {

         auto pitem = øallocate round_rectangle_item();

         pitem->m_rectangle = m_rectangle;

         pitem->m_sizeRadius = m_sizeRadius;

         return pitem;

      }


   };


} // namespace geometry2d



