// Split to _defer_shape.h by camilo on 2022-06-28 21:20 <3ThomasBorregaardSorensen!! (Mummi and bilbo in ca2HQ)
#pragma once


template < typename BASE_TYPE, typename POINT_BASE_TYPE, typename SIZE_BASE_TYPE >
inline void rectangle_type < BASE_TYPE, POINT_BASE_TYPE, SIZE_BASE_TYPE >::normalize() noexcept
{

   __sort(this->left, this->right);

   __sort(this->top, this->bottom);

}



