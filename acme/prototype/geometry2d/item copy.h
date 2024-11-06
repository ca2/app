// From aura/graphics/draw2d/region by camilo on 2023-06-01 06:28 <3ThomasBorregaardSorensen!!
#pragma once


//#include "_geometry2d.h"
//#include "_collection.h"


//template < primitive_rectangle RECTANGLE >
//inline void expand_bounding_box(RECTANGLE & rectangle, const ::double_point & p)
//{
//
//   rectangle.left() = (decltype(rectangle.left()))minimum(rectangle.left(), p.x());
//   rectangle.right() = (decltype(rectangle.right()))maximum(rectangle.right(), p.x());
//   rectangle.top() = (decltype(rectangle.top()))minimum(rectangle.top(), p.y());
//   rectangle.bottom() = (decltype(rectangle.bottom()))maximum(rectangle.bottom(), p.y());
//
//}

//template < primitive_rectangle RECTANGLE >
//inline void expand_bounding_box(RECTANGLE & rectangle, ::double_point * p, ::collection::count c)
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


         virtual void translate(const ::double_point & point);
         //virtual void expand_bounding_box(::double_rectangle & rectangle);
         virtual bool contains(const ::double_point & point);
         virtual void expand_bounding_box(::double_rectangle & rectangle);

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


      };


      // using poly_polygon_item_base = item_type < ::double_poly_polygon, ::draw2d::e_item_poly_polygon >;


      class CLASS_DECL_ACME poly_polygon_item :
         virtual public item
      {
      public:

         
         ::double_poly_polygon                  m_polypolygon;
         ::draw2d::enum_fill_mode            m_efillmode;


         //::draw2d::enum_item type() const override;


         void translate(const ::double_point & point) override;
         //void expand_bounding_box(::double_rectangle & rectangle) override;
         bool contains(const ::double_point & pooint) override;
         void expand_bounding_box(::double_rectangle & rectangle) override;


      };


      class CLASS_DECL_ACME combine_item :
         virtual public item
      {
      public:

         
         ///pointer_array < ::double_polygon >        m_polygon;

         ::pointer < ::geometry2d::region >     m_pregion1;
         ::pointer < ::geometry2d::region >     m_pregion2;
         ::draw2d::enum_combine                 m_ecombine;


         ::draw2d::enum_item type() const override;


         void translate(const ::double_point & point) override;
         bool contains(const ::double_point & point) override;
         void expand_bounding_box(::double_rectangle & rectangle) override;


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


      };


   //   ::draw2d::enum_region              m_eregion;
   //   ::pointer<item>                    m_pitem;

   //   ::int_point                        m_pointOffset;


   //   region();
   //   region(const region & region);
   //   ~region() override;


   //   virtual void destroy() override;


   //   region & operator = (const region & regionSrc);


   //   virtual bool create_rectangle(const ::int_rectangle & rectangle);

   //   virtual bool create_ellipse(const ::int_rectangle & rectangle);

   //   virtual bool create_polygon(const ::int_point * pPoints, int nCount, ::draw2d::enum_fill_mode efillmode = ::draw2d::e_fill_mode_winding);

   //   virtual bool create_polygon(const ::double_point * pPoints, int nCount, ::draw2d::enum_fill_mode efillmode = ::draw2d::e_fill_mode_winding);

   //   virtual bool create_polygon(const double_polygon & polygon, ::draw2d::enum_fill_mode efillmode = ::draw2d::e_fill_mode_winding);

   //   virtual bool create_poly_polygon(const ::double_point * pPoints, const int * lpPolyCounts, int nCount, ::draw2d::enum_fill_mode efillmode);

   //   virtual bool create_poly_polygon(const ::int_point * pPoints, const int * lpPolyCounts, int nCount, ::draw2d::enum_fill_mode efillmode);


   //   virtual bool combine(const ::geometry2d::region * prgn1, const ::geometry2d::region * prgn2, ::draw2d::enum_combine ecombine);
   //   virtual bool translate(const ::int_point & point);
   //   virtual bool get_bounding_box(::int_rectangle & rectangle);



   //   virtual bool contains(const ::int_point & point);
   //   virtual bool contains(const ::double_point & point);


   //   bool contains(const ::int_point & point);

   //   bool internal_rectangle_contains(const ::int_point & point);

   //   bool internal_oval_contains(const ::int_point & point);

   //   bool internal_polygon_contains(const ::int_point & point);

   //   bool internal_poly_polygon_contains(const ::int_point & point);

   //   bool internal_combine_contains(const ::int_point & point);



   //   bool contains(const ::double_point & point);



   //   virtual void expand_bounding_box(::int_rectangle & rectangle);



   //   virtual void expand_bounding_box(::double_rectangle & rectangle);



   //};


} // namespace geometry2d



