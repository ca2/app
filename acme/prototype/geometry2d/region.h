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

      //   virtual void translate(const ::int_point & point);
      //   virtual void expand_bounding_box(::double_rectangle & rectangle);
      //   virtual bool internal_contains(const ::double_point & p);

      //};


      //class CLASS_DECL_ACME rectangle_item :
      //   virtual public item
      //{
      //public:

      //   ::double_rectangle m_rectangle;

      //   void translate(const ::int_point & point) override;
      //   void expand_bounding_box(::double_rectangle & rectangle) override;
      //   bool internal_contains(const ::double_point & p) override;

      //};

      //class CLASS_DECL_ACME ellipse_item :
      //   virtual public item
      //{
      //public:


      //   ::double_rectangle m_rectangle;

      //   void translate(const ::int_point & point) override;
      //   void expand_bounding_box(::double_rectangle & rectangle) override;
      //   bool internal_contains(const ::double_point & p) override;



      //};

      //class CLASS_DECL_ACME polygon_item :
      //   virtual public item
      //{
      //public:

      //   ::double_polygon m_polygon;
      //   ::draw2d::enum_fill_mode            m_efillmode;


      //   void translate(const ::int_point & point) override;
      //   void expand_bounding_box(::double_rectangle & rectangle) override;
      //   bool internal_contains(const ::double_point & p) override;


      //};


      //class CLASS_DECL_ACME poly_polygon_item :
      //   virtual public item
      //{
      //public:

      //   pointer_array < ::double_polygon > m_polygona;
      //   ::draw2d::enum_fill_mode            m_efillmode;

      //   void translate(const ::int_point & point) override;
      //   void expand_bounding_box(::double_rectangle & rectangle) override;
      //   bool internal_contains(const ::double_point & p) override;


      //};

      //class CLASS_DECL_ACME combine_item :
      //   virtual public item
      //{
      //public:

      //   pointer_array < ::double_polygon >         m_polygon;

      //   ::pointer<::geometry2d::region>     m_pregion1;
      //   ::pointer<::geometry2d::region>     m_pregion2;
      //   ::draw2d::enum_combine              m_ecombine;

      //   void translate(const ::int_point & point) override;
      //   void expand_bounding_box(::double_rectangle & rectangle) override;
      //   bool internal_contains(const ::double_point & p) override;



      //};


      //class CLASS_DECL_ACME round_rectangle_item :
      //   virtual public item
      //{
      //public:


      //   ::double_rectangle   m_rectangle;
      //   ::double_size        m_sizeRadius;


      //   void translate(const ::int_point & point) override;
      //   void expand_bounding_box(::double_rectangle & rectangle) override;
      //   bool internal_contains(const ::double_point & p) override;

      //};


      ::pointer<item>                    m_pitem;

      ::int_point                        m_pointOffset;


      region();
      region(const region & region);
      ~region() override;


      //virtual void destroy() override;


      region & operator = (const region & regionSrc);


      virtual bool create_rectangle(const ::double_rectangle & rectangle);

      virtual bool create_ellipse(const ::double_ellipse & ellipse);

      virtual bool create_polygon(const ::int_point * pPoints, int nCount, ::draw2d::enum_fill_mode efillmode = ::draw2d::e_fill_mode_winding);

      virtual bool create_polygon(const ::double_point * pPoints, int nCount, ::draw2d::enum_fill_mode efillmode = ::draw2d::e_fill_mode_winding);

      virtual bool create_polygon(const double_polygon & polygon, ::draw2d::enum_fill_mode efillmode = ::draw2d::e_fill_mode_winding);

      virtual bool create_poly_polygon(const ::double_point * pPoints, const int * lpPolyCounts, int nCount, ::draw2d::enum_fill_mode efillmode);

      virtual bool create_poly_polygon(const ::int_point * pPoints, const int * lpPolyCounts, int nCount, ::draw2d::enum_fill_mode efillmode);

      virtual bool create_poly_polygon(const double_poly_polygon & polygon, ::draw2d::enum_fill_mode efillmode = ::draw2d::e_fill_mode_winding);


      virtual bool combine(const ::geometry2d::region * prgn1, const ::geometry2d::region * prgn2, ::draw2d::enum_combine ecombine);
      virtual bool translate(const ::double_point & point);
      virtual bool get_bounding_box(::double_rectangle & rectangle);



      //virtual bool contains(const ::int_point & point);
      virtual bool contains(const ::double_point & point);


      bool internal_contains(const ::double_point & point);

      bool internal_rectangle_contains(const ::double_point & point);

      bool internal_ellipse_contains(const ::double_point & point);

      bool internal_polygon_contains(const ::double_point & point);

      bool internal_poly_polygon_contains(const ::double_point & point);

      bool internal_combine_contains(const ::double_point & point);



      //bool internal_contains(const ::double_point & point);

 

      //virtual void expand_bounding_box(::int_rectangle & rectangle);

    

      virtual void expand_bounding_box(::double_rectangle & rectangle);



   };


} // namespace geometry2d



