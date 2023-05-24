// From _defer.h by camilo on 2022-06-28 21:20 <3ThomasBorregaardSørensen!! (Mummi and bilbo in ca2HQ)
#pragma once


template < typename SHAPE, enum_shape ESHAPE, typename HOLDEE >
inline bool _shape < SHAPE, ESHAPE, HOLDEE >::get_bounding_rectangle(::rectangle_i32 & rectangle) const
{

   return ::get_bounding_rectangle(rectangle, m_shape);

}


template < typename SHAPE, enum_shape ESHAPE, typename HOLDEE >
inline bool _shape < SHAPE, ESHAPE, HOLDEE >::get_bounding_rectangle(::rectangle_f64 & rectangle) const
{

   return ::get_bounding_rectangle(rectangle, m_shape);

}


template < typename SHAPE, enum_shape ESHAPE, typename HOLDEE >
bool _shape < SHAPE, ESHAPE, HOLDEE >::expand_bounding_rect(::rectangle_f64 & rectangle) const
{

   ::rectangle_f64 r;

   if (!this->get_bounding_rectangle(r))
   {

      return false;

   }

   ::unite(rectangle, r);

   return true;

}


template < typename SHAPE, enum_shape ESHAPE, typename HOLDEE >
bool _shape < SHAPE, ESHAPE, HOLDEE >::expand_bounding_rect(::rectangle_i32 & rectangle) const
{

   ::rectangle_i32 r;

   if (!this->get_bounding_rectangle(r))
   {

      return false;

   }

   ::unite(rectangle, r);

   return true;

}


template < typename SHAPE, enum_shape ESHAPE, typename HOLDEE >
inline bool _shape < SHAPE, ESHAPE, HOLDEE >::contains(const ::point_i32 & point) const
{

   return ::shape_contains(m_shape, point);

}


template < typename SHAPE, enum_shape ESHAPE, typename HOLDEE >
inline bool _shape < SHAPE, ESHAPE, HOLDEE >::contains(const ::point_f64 & point) const
{

   return ::shape_contains(m_shape, point);

}


template < typename HOLDEE >
template < typename GEOMETRY >
inline void shape_array < HOLDEE >::add_shape(const GEOMETRY & geometry)
{

   this->add(__create_shape(geometry, holdee < HOLDEE >()));

}


