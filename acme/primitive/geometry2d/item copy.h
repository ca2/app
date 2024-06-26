// From aura/graphics/draw2d/region by camilo on 2023-06-01 06:28 <3ThomasBorregaardSorensen!!
#pragma once


//#include "_geometry2d.h"
//#include "_collection.h"


//template < primitive_rectangle RECTANGLE >
//inline void expand_bounding_box(RECTANGLE & rectangle, const ::point_f64 & p)
//{
//
//   rectangle.left() = (decltype(rectangle.left()))minimum(rectangle.left(), p.x());
//   rectangle.right() = (decltype(rectangle.right()))maximum(rectangle.right(), p.x());
//   rectangle.top() = (decltype(rectangle.top()))minimum(rectangle.top(), p.y());
//   rectangle.bottom() = (decltype(rectangle.bottom()))maximum(rectangle.bottom(), p.y());
//
//}

//template < primitive_rectangle RECTANGLE >
//inline void expand_bounding_box(RECTANGLE & rectangle, ::point_f64 * p, ::collection::count c)
//{
//
//   for (::collection::index i = 0; i < c; i++)
//   {
//
//      expand_bounding_box(rectangle, *p);
//
//      p++;
//
//   }
//
//}


namespace geometry2d
{


   //class CLASS_DECL_ACME region :
   //   virtual public ::particle
   //{
   //public:


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


      };


      class CLASS_DECL_ACME close_figure_item :
         virtual public item
      {
      public:


         ::draw2d::enum_item type() const override;


      };



      class CLASS_DECL_ACME end_figure_item :
         virtual public item
      {
      public:


         ::draw2d::enum_item type() const override;


      };


      class CLASS_DECL_ACME intersect_clip_item :
         virtual public item
      {
      public:


         ::draw2d::enum_item type() const override;


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


      };


   //   ::draw2d::enum_region              m_eregion;
   //   ::pointer<item>                    m_pitem;

   //   ::point_i32                        m_pointOffset;


   //   region();
   //   region(const region & region);
   //   ~region() override;


   //   virtual void destroy() override;


   //   region & operator = (const region & regionSrc);


   //   virtual bool create_rectangle(const ::rectangle_i32 & rectangle);

   //   virtual bool create_ellipse(const ::rectangle_i32 & rectangle);

   //   virtual bool create_polygon(const ::point_i32 * pPoints, i32 nCount, ::draw2d::enum_fill_mode efillmode = ::draw2d::e_fill_mode_winding);

   //   virtual bool create_polygon(const ::point_f64 * pPoints, i32 nCount, ::draw2d::enum_fill_mode efillmode = ::draw2d::e_fill_mode_winding);

   //   virtual bool create_polygon(const polygon_f64 & polygon, ::draw2d::enum_fill_mode efillmode = ::draw2d::e_fill_mode_winding);

   //   virtual bool create_poly_polygon(const ::point_f64 * pPoints, const i32 * lpPolyCounts, i32 nCount, ::draw2d::enum_fill_mode efillmode);

   //   virtual bool create_poly_polygon(const ::point_i32 * pPoints, const i32 * lpPolyCounts, i32 nCount, ::draw2d::enum_fill_mode efillmode);


   //   virtual bool combine(const ::geometry2d::region * prgn1, const ::geometry2d::region * prgn2, ::draw2d::enum_combine ecombine);
   //   virtual bool translate(const ::point_i32 & point);
   //   virtual bool get_bounding_box(::rectangle_i32 & rectangle);



   //   virtual bool contains(const ::point_i32 & point);
   //   virtual bool contains(const ::point_f64 & point);


   //   bool contains(const ::point_i32 & point);

   //   bool internal_rectangle_contains(const ::point_i32 & point);

   //   bool internal_oval_contains(const ::point_i32 & point);

   //   bool internal_polygon_contains(const ::point_i32 & point);

   //   bool internal_poly_polygon_contains(const ::point_i32 & point);

   //   bool internal_combine_contains(const ::point_i32 & point);



   //   bool contains(const ::point_f64 & point);



   //   virtual void expand_bounding_box(::rectangle_i32 & rectangle);



   //   virtual void expand_bounding_box(::rectangle_f64 & rectangle);



   //};


} // namespace geometry2d



