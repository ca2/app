// First compilation from other files by camilo on 2022-10-07 23:15 <3ThomasBorregaardSorensen!!
#pragma once


template < primitive_point POINT >
inline binary_stream & operator << (binary_stream & s, const POINT & point)
{

   s << point.x;
   s << point.y;

   return s;

}


template < primitive_point POINT >
inline binary_stream & operator >> (binary_stream & s, POINT & point)
{

   s >> point.x;
   s >> point.y;

   return s;

}


template < primitive_size SIZE >
inline binary_stream & operator << (binary_stream & s, const SIZE & size)
{

   s << size.cx;
   s << size.cy;

   return s;

}


template < primitive_size SIZE >
inline binary_stream & operator >> (binary_stream & s, SIZE & size)
{

   s >> size.cx;
   s >> size.cy;

   return s;

}


template < primitive_rectangle RECTANGLE >
inline binary_stream & operator << (binary_stream & s, const RECTANGLE & rectangle)
{

   s << rectangle.left;
   s << rectangle.top;
   s << rectangle.right;
   s << rectangle.bottom;

   return s;

}


template < primitive_rectangle RECTANGLE >
inline binary_stream & operator >> (binary_stream & s, RECTANGLE & rectangle)
{

   s >> rectangle.left;
   s >> rectangle.top;
   s >> rectangle.right;
   s >> rectangle.bottom;

   return s;

}



