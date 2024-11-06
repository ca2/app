// from region.h byy camilo on 2023-06-01 06:54 <3ThomasBorregaardSorensen!!
#pragma once


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

template < primitive_rectangle RECTANGLE >
inline void expand_bounding_box(RECTANGLE & rectangle, ::double_point * p, ::collection::count c)
{

   for (::collection::index i = 0; i < c; i++)
   {

      expand_bounding_box(rectangle, *p);

      p++;

   }

}



