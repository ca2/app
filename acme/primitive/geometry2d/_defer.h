#pragma once


template < typename SHAPE, enum_shape ESHAPE >
inline bool _shape < SHAPE, ESHAPE >::get_bounding_rectangle(RECTANGLE_I32* prectangle) const
{

   return ::get_bounding_rectangle(prectangle, &m_shape);

}


template < typename SHAPE, enum_shape ESHAPE >
inline bool _shape < SHAPE, ESHAPE >::get_bounding_rectangle(RECTANGLE_F64* prectangle) const
{

   return ::get_bounding_rectangle(prectangle, &m_shape);

}


template < typename SHAPE, enum_shape ESHAPE >
inline bool _shape < SHAPE, ESHAPE >::contains(const ::POINT_I32 & point) const
{

   return ::shape_contains(&m_shape, point);

}


template < typename SHAPE, enum_shape ESHAPE >
inline bool _shape < SHAPE, ESHAPE >::contains(const ::POINT_F64 & point) const
{

   return ::shape_contains(&m_shape, point);

}


