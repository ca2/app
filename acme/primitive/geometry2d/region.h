// From aura/graphics/draw2d/region by camilo on 2023-05-26 13:51 <3ThomasBorregaardSorensen!!
#pragma once


//#include "_geometry2d.h"
#include "_collection.h"



namespace geometry2d
{


   class CLASS_DECL_ACME region :
      virtual public ::particle
   {
   public:


      //class CLASS_DECL_ACME item :
      //   virtual public ::particle
      //{
      //public:

      //   virtual void translate(const ::point_i32 & point);
      //   virtual void expand_bounding_box(::rectangle_f64 & rectangle);
      //   virtual bool internal_contains(const ::point_f64 & p);

      //};


      //class CLASS_DECL_ACME rectangle_item :
      //   virtual public item
      //{
      //public:

      //   ::rectangle_f64 m_rectangle;

      //   void translate(const ::point_i32 & point) override;
      //   void expand_bounding_box(::rectangle_f64 & rectangle) override;
      //   bool internal_contains(const ::point_f64 & p) override;

      //};

      //class CLASS_DECL_ACME ellipse_item :
      //   virtual public item
      //{
      //public:


      //   ::rectangle_f64 m_rectangle;

      //   void translate(const ::point_i32 & point) override;
      //   void expand_bounding_box(::rectangle_f64 & rectangle) override;
      //   bool internal_contains(const ::point_f64 & p) override;



      //};

      //class CLASS_DECL_ACME polygon_item :
      //   virtual public item
      //{
      //public:

      //   ::polygon_f64 m_polygon;
      //   ::draw2d::enum_fill_mode            m_efillmode;


      //   void translate(const ::point_i32 & point) override;
      //   void expand_bounding_box(::rectangle_f64 & rectangle) override;
      //   bool internal_contains(const ::point_f64 & p) override;


      //};


      //class CLASS_DECL_ACME poly_polygon_item :
      //   virtual public item
      //{
      //public:

      //   pointer_array < ::polygon_f64 > m_polygona;
      //   ::draw2d::enum_fill_mode            m_efillmode;

      //   void translate(const ::point_i32 & point) override;
      //   void expand_bounding_box(::rectangle_f64 & rectangle) override;
      //   bool internal_contains(const ::point_f64 & p) override;


      //};

      //class CLASS_DECL_ACME combine_item :
      //   virtual public item
      //{
      //public:

      //   pointer_array < ::polygon_f64 >         m_polygon;

      //   ::pointer<::geometry2d::region>     m_pregion1;
      //   ::pointer<::geometry2d::region>     m_pregion2;
      //   ::draw2d::enum_combine              m_ecombine;

      //   void translate(const ::point_i32 & point) override;
      //   void expand_bounding_box(::rectangle_f64 & rectangle) override;
      //   bool internal_contains(const ::point_f64 & p) override;



      //};


      //class CLASS_DECL_ACME round_rectangle_item :
      //   virtual public item
      //{
      //public:


      //   ::rectangle_f64   m_rectangle;
      //   ::size_f64        m_sizeRadius;


      //   void translate(const ::point_i32 & point) override;
      //   void expand_bounding_box(::rectangle_f64 & rectangle) override;
      //   bool internal_contains(const ::point_f64 & p) override;

      //};


      ::pointer<item>                    m_pitem;

      ::point_i32                        m_pointOffset;


      region();
      region(const region & region);
      ~region() override;


      //virtual void destroy() override;


      region & operator = (const region & regionSrc);


      virtual bool create_rectangle(const ::rectangle_f64 & rectangle);

      virtual bool create_ellipse(const ::ellipse_f64 & ellipse);

      virtual bool create_polygon(const ::point_i32 * pPoints, i32 nCount, ::draw2d::enum_fill_mode efillmode = ::draw2d::e_fill_mode_winding);

      virtual bool create_polygon(const ::point_f64 * pPoints, i32 nCount, ::draw2d::enum_fill_mode efillmode = ::draw2d::e_fill_mode_winding);

      virtual bool create_polygon(const polygon_f64 & polygon, ::draw2d::enum_fill_mode efillmode = ::draw2d::e_fill_mode_winding);

      virtual bool create_poly_polygon(const ::point_f64 * pPoints, const i32 * lpPolyCounts, i32 nCount, ::draw2d::enum_fill_mode efillmode);

      virtual bool create_poly_polygon(const ::point_i32 * pPoints, const i32 * lpPolyCounts, i32 nCount, ::draw2d::enum_fill_mode efillmode);

      virtual bool create_poly_polygon(const poly_polygon_f64 & polygon, ::draw2d::enum_fill_mode efillmode = ::draw2d::e_fill_mode_winding);


      virtual bool combine(const ::geometry2d::region * prgn1, const ::geometry2d::region * prgn2, ::draw2d::enum_combine ecombine);
      virtual bool translate(const ::point_f64 & point);
      virtual bool get_bounding_box(::rectangle_f64 & rectangle);



      //virtual bool contains(const ::point_i32 & point);
      virtual bool contains(const ::point_f64 & point);


      bool internal_contains(const ::point_f64 & point);

      bool internal_rectangle_contains(const ::point_f64 & point);

      bool internal_ellipse_contains(const ::point_f64 & point);

      bool internal_polygon_contains(const ::point_f64 & point);

      bool internal_poly_polygon_contains(const ::point_f64 & point);

      bool internal_combine_contains(const ::point_f64 & point);



      //bool internal_contains(const ::point_f64 & point);

 

      //virtual void expand_bounding_box(::rectangle_i32 & rectangle);

    

      virtual void expand_bounding_box(::rectangle_f64 & rectangle);



   };


} // namespace geometry2d



