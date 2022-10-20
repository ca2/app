// From _defer.h by camilo on 2022-06-28 21:20 <3ThomasBorregaardSorensen!! (Mummi and bilbo in ca2HQ)
#pragma once


template < typename SHAPE, enum_shape ESHAPE, typename HOLDEE >
inline bool _shape < SHAPE, ESHAPE, HOLDEE >::get_bounding_rectangle(RECTANGLE_I32 & rectangle) const
{

   return ::get_bounding_rectangle(rectangle, m_shape);

}


template < typename SHAPE, enum_shape ESHAPE, typename HOLDEE >
inline bool _shape < SHAPE, ESHAPE, HOLDEE >::get_bounding_rectangle(RECTANGLE_F64 & rectangle) const
{

   return ::get_bounding_rectangle(rectangle, m_shape);

}


template < typename SHAPE, enum_shape ESHAPE, typename HOLDEE >
bool _shape < SHAPE, ESHAPE, HOLDEE >::expand_bounding_rect(RECTANGLE_F64 & rectangle) const
{

   ::RECTANGLE_F64 r;

   if (!this->get_bounding_rectangle(r))
   {

      return false;

   }

   ::unite(rectangle, r);

   return true;

}


template < typename SHAPE, enum_shape ESHAPE, typename HOLDEE >
bool _shape < SHAPE, ESHAPE, HOLDEE >::expand_bounding_rect(RECTANGLE_I32 & rectangle) const
{

   ::RECTANGLE_I32 r;

   if (!this->get_bounding_rectangle(r))
   {

      return false;

   }

   ::unite(rectangle, r);

   return true;

}


template < typename SHAPE, enum_shape ESHAPE, typename HOLDEE >
inline bool _shape < SHAPE, ESHAPE, HOLDEE >::contains(const ::POINT_I32 & point) const
{

   return ::shape_contains(m_shape, point);

}


template < typename SHAPE, enum_shape ESHAPE, typename HOLDEE >
inline bool _shape < SHAPE, ESHAPE, HOLDEE >::contains(const ::POINT_F64 & point) const
{

   return ::shape_contains(m_shape, point);

}


template < typename HOLDEE >
template < typename GEOMETRY >
inline void shape_array < HOLDEE >::add_shape(const GEOMETRY & geometry)
{

   this->add(__create_shape(geometry, holdee < HOLDEE >()));

}


