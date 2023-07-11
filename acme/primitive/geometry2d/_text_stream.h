//
// Created by camilo on 27/11/2022 15:02 <3ThomasBorregaardSorensen!!
//
#pragma once



template < primitive_point POINT >
inline ::write_text_stream & operator <<(::write_text_stream & textstream, const POINT & point)
{

   return textstream << "(" << point.x()  << ", " << point.y() << ")";

}


template < primitive_size SIZE >
inline ::write_text_stream & operator <<(::write_text_stream  & textstream, const SIZE & size)
{

   return textstream << "(" << size.cx()  << ", " << size.cy() << ")";

}



template <  primitive_rectangle RECTANGLE >
inline ::write_text_stream & operator <<(::write_text_stream & textstream, const RECTANGLE & rectangle)
{

   return textstream << "xy(" << rectangle.left  << ", " << rectangle.top << ")-wh(" << rectangle.width() << ", " << rectangle.height() << ")";

}


