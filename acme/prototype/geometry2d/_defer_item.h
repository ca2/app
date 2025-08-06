// From item.h on 2023-06-01 21:00 <3ThomasBorregaardSorensen!!
#pragma once


#include "arc.h"
#include "ellipse.h"
#include "line.h"


namespace geometry2d
{


   template < typename TYPE, ::draw2d::enum_item t_eitem >
   class item_type :
      virtual public item
   {
   public:


      TYPE        m_item;

      item_type()
      {


      }

      ~item_type()
      {



      }


      ::draw2d::enum_item type() const override { return t_eitem; }


      void translate(const ::double_point & point) override { m_item.offset(point); }
      bool contains(const ::double_point & point) override { return m_item.contains(point); }
      void expand_bounding_box(::double_rectangle & rectangle) override { m_item.expand_bounding_box(rectangle.top_left(), rectangle.bottom_right()); }


      ::subparticle_pointer clone() override
      {

         auto pitem = __allocate item_type();

         pitem->m_item = m_item;

         return pitem;

      }


   };


   using line_item = item_type < ::double_line, ::draw2d::e_item_line >;
   using rectangle_item = item_type < ::double_rectangle, ::draw2d::e_item_rectangle >;


   using ellipse_item = item_type < ::double_ellipse, ::draw2d::e_item_ellipse >;

   using arc_item = item_type < ::double_arc, ::draw2d::e_item_arc >;

   using lines_item = item_type < ::double_lines, ::draw2d::e_item_lines >;


} // namespace geometry2d



