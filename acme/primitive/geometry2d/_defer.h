#pragma once


template < typename SHAPE, enum_shape ESHAPE, typename HOLDEE >
inline bool _shape < SHAPE, ESHAPE, HOLDEE >::get_bounding_rectangle(RECTANGLE_I32* prectangle) const
{

   return ::get_bounding_rectangle(prectangle, &m_shape);

}


template < typename SHAPE, enum_shape ESHAPE, typename HOLDEE >
inline bool _shape < SHAPE, ESHAPE, HOLDEE >::get_bounding_rectangle(RECTANGLE_F64* prectangle) const
{

   return ::get_bounding_rectangle(prectangle, &m_shape);

}


template < typename SHAPE, enum_shape ESHAPE, typename HOLDEE >
bool _shape < SHAPE, ESHAPE, HOLDEE >::expand_bounding_rect(RECTANGLE_F64 * prectangle) const
{

   ::RECTANGLE_F64 r;

   if (!this->get_bounding_rectangle(&r))
   {

      return false;

   }

   ::union_rect(prectangle, prectangle, &r);

   return true;

}


template < typename SHAPE, enum_shape ESHAPE, typename HOLDEE >
bool _shape < SHAPE, ESHAPE, HOLDEE >::expand_bounding_rect(RECTANGLE_I32 * prectangle) const
{

   ::RECTANGLE_I32 r;

   if (!this->get_bounding_rectangle(&r))
   {

      return false;

   }

   ::union_rect(prectangle, prectangle, &r);

   return true;

}


template < typename BASE_TYPE, typename POINT_BASE_TYPE, typename SIZE_BASE_TYPE >
inline void rectangle_type < BASE_TYPE, POINT_BASE_TYPE, SIZE_BASE_TYPE >::normalize() noexcept
{

   __sort(this->left, this->right);

   __sort(this->top, this->bottom);

}


template < typename SHAPE, enum_shape ESHAPE, typename HOLDEE >
inline bool _shape < SHAPE, ESHAPE, HOLDEE >::contains(const ::POINT_I32 & point) const
{

   return ::shape_contains(&m_shape, point);

}


template < typename SHAPE, enum_shape ESHAPE, typename HOLDEE >
inline bool _shape < SHAPE, ESHAPE, HOLDEE >::contains(const ::POINT_F64 & point) const
{

   return ::shape_contains(&m_shape, point);

}


template < typename HOLDEE >
template < typename GEOMETRY >
inline void shape_array < HOLDEE >::add_shape(const GEOMETRY & geometry)
{

   this->add(__create_shape(geometry, holdee < HOLDEE >()));

}



