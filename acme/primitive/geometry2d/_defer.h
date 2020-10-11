#pragma once


template < typename SHAPE, enum_shape ESHAPE >
bool _shape < SHAPE, ESHAPE >::get_bounding_rect(RECT* prect) const
   {

      return ::get_bounding_rect(prect, &m_shape);

   }


template < typename SHAPE, enum_shape ESHAPE >
bool _shape < SHAPE, ESHAPE >::get_bounding_rect(RECTD* prect) const

   {

      return ::get_bounding_rect(prect, &m_shape);

   }


   template < typename SHAPE, enum_shape ESHAPE >
bool _shape < SHAPE, ESHAPE >::contains(const ::POINT & point) const

   {

      return ::shape_contains(&m_shape, point);

   }


      template < typename SHAPE, enum_shape ESHAPE >
bool _shape < SHAPE, ESHAPE >::contains(const ::POINTD & point) const

   {

      return ::shape_contains(&m_shape, point);

   }

