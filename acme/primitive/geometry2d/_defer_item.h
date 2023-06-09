// From item.h on 2023-06-01 21:00 <3ThomasBorregaardSorensen!!
#pragma once


namespace geometry2d
{


   template < typename TYPE, ::draw2d::enum_item t_eitem >
   class item_type :
      virtual public item
   {
   public:


      TYPE        m_item;


      ::draw2d::enum_item type() const override { return t_eitem; }


      void translate(const ::point_f64 & point) override { m_item.offset(point); }
      bool contains(const ::point_f64 & point) override { return m_item.contains(point); }
      void expand_bounding_box(::rectangle_f64 & rectangle) override { m_item.expand_bounding_box(rectangle.top_left(), rectangle.bottom_right()); }


   };


   using line_item = item_type < ::line_f64, ::draw2d::e_item_line >;
   using rectangle_item = item_type < ::rectangle_f64, ::draw2d::e_item_rectangle >;


   using ellipse_item = item_type < ::ellipse_f64, ::draw2d::e_item_ellipse >;

   using arc_item = item_type < ::arc_f64, ::draw2d::e_item_arc >;

   using lines_item = item_type < ::lines_f64, ::draw2d::e_item_lines >;


} // namespace geometry2d



