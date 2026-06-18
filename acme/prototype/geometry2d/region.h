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

      //   virtual void translate(const ::i32_point & point);
      //   virtual void expand_bounding_box(::f64_rectangle & rectangle);
      //   virtual bool internal_contains(const ::f64_point & p);

      //};


      //class CLASS_DECL_ACME rectangle_item :
      //   virtual public item
      //{
      //public:

      //   ::f64_rectangle m_rectangle;

      //   void translate(const ::i32_point & point) override;
      //   void expand_bounding_box(::f64_rectangle & rectangle) override;
      //   bool internal_contains(const ::f64_point & p) override;

      //};

      //class CLASS_DECL_ACME ellipse_item :
      //   virtual public item
      //{
      //public:


      //   ::f64_rectangle m_rectangle;

      //   void translate(const ::i32_point & point) override;
      //   void expand_bounding_box(::f64_rectangle & rectangle) override;
      //   bool internal_contains(const ::f64_point & p) override;



      //};

      //class CLASS_DECL_ACME polygon_item :
      //   virtual public item
      //{
      //public:

      //   ::f64_polygon m_polygon;
      //   ::draw2d::enum_fill_mode            m_efillmode;


      //   void translate(const ::i32_point & point) override;
      //   void expand_bounding_box(::f64_rectangle & rectangle) override;
      //   bool internal_contains(const ::f64_point & p) override;


      //};


      //class CLASS_DECL_ACME poly_polygon_item :
      //   virtual public item
      //{
      //public:

      //   pointer_array < ::f64_polygon > m_polygona;
      //   ::draw2d::enum_fill_mode            m_efillmode;

      //   void translate(const ::i32_point & point) override;
      //   void expand_bounding_box(::f64_rectangle & rectangle) override;
      //   bool internal_contains(const ::f64_point & p) override;


      //};

      //class CLASS_DECL_ACME combine_item :
      //   virtual public item
      //{
      //public:

      //   pointer_array < ::f64_polygon >         m_polygon;

      //   ::pointer<::geometry2d::region>     m_pregion1;
      //   ::pointer<::geometry2d::region>     m_pregion2;
      //   ::draw2d::enum_combine              m_ecombine;

      //   void translate(const ::i32_point & point) override;
      //   void expand_bounding_box(::f64_rectangle & rectangle) override;
      //   bool internal_contains(const ::f64_point & p) override;



      //};


      //class CLASS_DECL_ACME round_rectangle_item :
      //   virtual public item
      //{
      //public:


      //   ::f64_rectangle   m_rectangle;
      //   ::f64_size        m_sizeRadius;


      //   void translate(const ::i32_point & point) override;
      //   void expand_bounding_box(::f64_rectangle & rectangle) override;
      //   bool internal_contains(const ::f64_point & p) override;

      //};


      ::pointer<item>                    m_pitem;

      ::i32_point                        m_pointOffset;


      region();
      region(const region & region);
      ~region() override;


      //virtual void destroy() override;


      region & operator = (const region & regionSrc);


      virtual bool create_rectangle(const ::f64_rectangle & rectangle);

      virtual bool create_ellipse(const ::f64_ellipse & ellipse);

      virtual bool create_polygon(const ::i32_point * pPoints, ::i32 nCount, ::draw2d::enum_fill_mode efillmode = ::draw2d::e_fill_mode_winding);

      virtual bool create_polygon(const ::f64_point * pPoints, ::i32 nCount, ::draw2d::enum_fill_mode efillmode = ::draw2d::e_fill_mode_winding);

      virtual bool create_polygon(const f64_polygon & polygon, ::draw2d::enum_fill_mode efillmode = ::draw2d::e_fill_mode_winding);

      virtual bool create_poly_polygon(const ::f64_point * pPoints, const ::i32 * lpPolyCounts, ::i32 nCount, ::draw2d::enum_fill_mode efillmode);

      virtual bool create_poly_polygon(const ::i32_point * pPoints, const ::i32 * lpPolyCounts, ::i32 nCount, ::draw2d::enum_fill_mode efillmode);

      virtual bool create_poly_polygon(const f64_poly_polygon & polygon, ::draw2d::enum_fill_mode efillmode = ::draw2d::e_fill_mode_winding);


      virtual bool combine(const ::geometry2d::region * prgn1, const ::geometry2d::region * prgn2, ::draw2d::enum_combine ecombine);
      virtual bool translate(const ::f64_point & point);
      virtual bool get_bounding_box(::f64_rectangle & rectangle);



      //virtual bool contains(const ::i32_point & point);
      virtual bool contains(const ::f64_point & point);


      bool internal_contains(const ::f64_point & point);

      bool internal_rectangle_contains(const ::f64_point & point);

      bool internal_ellipse_contains(const ::f64_point & point);

      bool internal_polygon_contains(const ::f64_point & point);

      bool internal_poly_polygon_contains(const ::f64_point & point);

      bool internal_combine_contains(const ::f64_point & point);



      //bool internal_contains(const ::f64_point & point);

 

      //virtual void expand_bounding_box(::i32_rectangle & rectangle);

    

      virtual void expand_bounding_box(::f64_rectangle & rectangle);



   };


} // namespace geometry2d



