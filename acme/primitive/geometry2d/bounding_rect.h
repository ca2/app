#pragma once


template < primitive_rectangle RECTANGLE >
inline bool get_bounding_rectangle(RECTANGLE & rectangleBounding, const ::arc & arc)
{

   rectangleBounding.left = (decltype(rectangleBounding.left)) (arc.m_pointCenter.x - arc.m_sizeRadius.cx);
   rectangleBounding.right = (decltype(rectangleBounding.right))(arc.m_pointCenter.x + arc.m_sizeRadius.cx);
   rectangleBounding.top = (decltype(rectangleBounding.top))(arc.m_pointCenter.y - arc.m_sizeRadius.cy);
   rectangleBounding.bottom = (decltype(rectangleBounding.bottom))(arc.m_pointCenter.y + arc.m_sizeRadius.cy);

   return true;

}


//inline bool get_bounding_rectangle(RECTANGLE_F64 * prectangleBounding, const ::arc * parc)
//{
//
//   rectangleBounding.left = arc.m_pointCenter.x - arc.m_sizeRadius.cx;
//   rectangleBounding.right = arc.m_pointCenter.x + arc.m_sizeRadius.cx;
//   rectangleBounding.top = arc.m_pointCenter.y - arc.m_sizeRadius.cy;
//   rectangleBounding.bottom = arc.m_pointCenter.y + arc.m_sizeRadius.cy;
//
//   return true;
//
//}

template < primitive_rectangle RECTANGLE >
inline bool get_bounding_rectangle(RECTANGLE & rectangleBounding, const line & line)
{

   rectangleBounding.left = (decltype(rectangleBounding.left)) minimum(line.m_p1.x, line.m_p2.x);
   rectangleBounding.top = (decltype(rectangleBounding.top)) minimum(line.m_p1.y, line.m_p2.y);
   rectangleBounding.right = (decltype(rectangleBounding.right)) maximum(line.m_p1.x, line.m_p2.x);
   rectangleBounding.bottom = (decltype(rectangleBounding.bottom)) maximum(line.m_p1.y, line.m_p2.y);

   return true;

}


//inline bool get_bounding_rectangle(RECTANGLE_F64* prectangleBounding, const line* pline)
//{
//
//   rectangleBounding.left = minimum(line.m_p1.x, line.m_p2.x);
//   rectangleBounding.top = minimum(line.m_p1.y, line.m_p2.y);
//   rectangleBounding.right = maximum(line.m_p1.x, line.m_p2.x);
//   rectangleBounding.bottom = maximum(line.m_p1.y, line.m_p2.y);
//
//   return true;
//
//}


//inline bool get_bounding_rectangle(RECTANGLE_I32* prectangleBounding, const line * pline)
//{
//
//   rectangleBounding.left = (::i32)minimum(line.m_p1.x, line.m_p2.x);
//   rectangleBounding.top = (::i32)minimum(line.m_p1.y, line.m_p2.y);
//   rectangleBounding.right = (::i32)maximum(line.m_p1.x, line.m_p2.x);
//   rectangleBounding.bottom = (::i32)maximum(line.m_p1.y, line.m_p2.y);
//
//   return true;
//
//}


//inline bool get_bounding_rectangle(RECTANGLE_F64* prectangleBounding, const line * pline)
//{
//
//   rectangleBounding.left = minimum(line.m_p1.x, line.m_p2.x);
//   rectangleBounding.top = minimum(line.m_p1.y, line.m_p2.y);
//   rectangleBounding.right = maximum(line.m_p1.x, line.m_p2.x);
//   rectangleBounding.bottom = maximum(line.m_p1.y, line.m_p2.y);
//
//   return true;
//
//}

template < primitive_rectangle RECTANGLE >
inline bool get_bounding_rectangle(RECTANGLE & rectangleBounding, const ellipse & ellipse)
{

   copy(rectangleBounding, ellipse);

   return true;

}


//inline bool get_bounding_rectangle(RECTANGLE_F64* prectangleBounding, const ellipse * pellipse)
//{
//
//   copy(prectangleBounding, pellipse);
//
//   return true;
//
//}


//inline bool get_bounding_rectangle(RECTANGLE_I32* prectangleBounding, const ellipse* poval)
//{
//
//   copy(prectangleBounding, poval);
//
//   return true;
//
//}


//inline bool get_bounding_rectangle(RECTANGLE_F64* prectangleBounding, const ellipse* prectangle)
//{
//
//   copy(prectangleBounding, prectangle);
//
//   return true;
//
//}
//
//
