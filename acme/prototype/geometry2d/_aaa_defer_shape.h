// From _defer.h by camilo on 2022-06-28 21:20 <3ThomasBorregaardSorensen!! (Mummi and bilbo in ca2HQ)
#pragma once


template < typename SHAPE, enum_shape ESHAPE, typename HOLDEE >
inline bool _shape < SHAPE, ESHAPE, HOLDEE >::get_bounding_box(::int_rectangle & rectangle) const
{

   return ::get_bounding_box(rectangle, m_shape);

}


template < typename SHAPE, enum_shape ESHAPE, typename HOLDEE >
inline bool _shape < SHAPE, ESHAPE, HOLDEE >::get_bounding_box(::double_rectangle & rectangle) const
{

   return ::get_bounding_box(rectangle, m_shape);

}


template < typename SHAPE, enum_shape ESHAPE, typename HOLDEE >
bool _shape < SHAPE, ESHAPE, HOLDEE >::expand_bounding_rect(::double_rectangle & rectangle) const
{

   ::double_rectangle r;

   if (!this->get_bounding_box(r))
   {

      return false;

   }

   ::unite(rectangle, r);

   return true;

}


template < typename SHAPE, enum_shape ESHAPE, typename HOLDEE >
bool _shape < SHAPE, ESHAPE, HOLDEE >::expand_bounding_rect(::int_rectangle & rectangle) const
{

   ::int_rectangle r;

   if (!this->get_bounding_box(r))
   {

      return false;

   }

   ::unite(rectangle, r);

   return true;

}


template < typename SHAPE, enum_shape ESHAPE, typename HOLDEE >
inline bool _shape < SHAPE, ESHAPE, HOLDEE >::contains(const ::int_point & point) const
{

   return ::shape_contains(m_shape, point);

}


template < typename SHAPE, enum_shape ESHAPE, typename HOLDEE >
inline bool _shape < SHAPE, ESHAPE, HOLDEE >::contains(const ::double_point & point) const
{

   return ::shape_contains(m_shape, point);

}


template < typename HOLDEE >
template < typename GEOMETRY >
inline void shape_array < HOLDEE >::add_shape(const GEOMETRY & geometry)
{

   this->add(__create_shape(geometry, holdee < HOLDEE >()));

}


