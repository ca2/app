// First compilation from other files by camilo on 2022-10-07 23:15 <3ThomasBorregaardSorensen!!
#pragma once


template < typename FILE, primitive_point POINT >
inline binary_stream < FILE > & operator << (binary_stream < FILE > & s, const POINT & point)
{

   s << point.x;
   s << point.y;

   return s;

}


template < typename FILE, primitive_point POINT >
inline binary_stream < FILE > & operator >> (binary_stream < FILE > & s, POINT & point)
{

   s >> point.x;
   s >> point.y;

   return s;

}


template < typename FILE, primitive_size SIZE >
inline binary_stream < FILE > & operator << (binary_stream < FILE > & s, const SIZE & size)
{

   s << size.cx;
   s << size.cy;

   return s;

}


template < typename FILE, primitive_size SIZE >
inline binary_stream < FILE > & operator >> (binary_stream < FILE > & s, SIZE & size)
{

   s >> size.cx;
   s >> size.cy;

   return s;

}


template < typename FILE, primitive_rectangle RECTANGLE >
inline binary_stream < FILE > & operator << (binary_stream < FILE > & s, const RECTANGLE & rectangle)
{

   s << rectangle.left;
   s << rectangle.top;
   s << rectangle.right;
   s << rectangle.bottom;

   return s;

}


template < typename FILE, primitive_rectangle RECTANGLE >
inline binary_stream < FILE > & operator >> (binary_stream < FILE > & s, RECTANGLE & rectangle)
{

   s >> rectangle.left;
   s >> rectangle.top;
   s >> rectangle.right;
   s >> rectangle.bottom;

   return s;

}



