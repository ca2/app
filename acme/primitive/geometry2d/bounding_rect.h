#pragma once


template < primitive_rectangle RECTANGLE >
inline bool get_bounding_rectangle(RECTANGLE & rectangleBounding, const ::arc* parc)
{

   rectangleBounding.left = (decltype(rectangleBounding.left)) (parc->m_pointCenter.x - parc->m_sizeRadius.cx);
   rectangleBounding.right = (decltype(rectangleBounding.right))(parc->m_pointCenter.x + parc->m_sizeRadius.cx);
   rectangleBounding.top = (decltype(rectangleBounding.top))(parc->m_pointCenter.y - parc->m_sizeRadius.cy);
   rectangleBounding.bottom = (decltype(rectangleBounding.bottom))(parc->m_pointCenter.y + parc->m_sizeRadius.cy);

   return true;

}


//inline bool get_bounding_rectangle(RECTANGLE_F64 * prectangleBounding, const ::arc * parc)
//{
//
//   rectangleBounding.left = parc->m_pointCenter.x - parc->m_sizeRadius.cx;
//   rectangleBounding.right = parc->m_pointCenter.x + parc->m_sizeRadius.cx;
//   rectangleBounding.top = parc->m_pointCenter.y - parc->m_sizeRadius.cy;
//   rectangleBounding.bottom = parc->m_pointCenter.y + parc->m_sizeRadius.cy;
//
//   return true;
//
//}

template < primitive_rectangle RECTANGLE >
inline bool get_bounding_rectangle(RECTANGLE & rectangleBounding, const line * pline)
{

   rectangleBounding.left = (decltype(rectangleBounding.left)) minimum(pline->m_p1.x, pline->m_p2.x);
   rectangleBounding.top = (decltype(rectangleBounding.top)) minimum(pline->m_p1.y, pline->m_p2.y);
   rectangleBounding.right = (decltype(rectangleBounding.right)) maximum(pline->m_p1.x, pline->m_p2.x);
   rectangleBounding.bottom = (decltype(rectangleBounding.bottom)) maximum(pline->m_p1.y, pline->m_p2.y);

   return true;

}


//inline bool get_bounding_rectangle(RECTANGLE_F64* prectangleBounding, const line* pline)
//{
//
//   rectangleBounding.left = minimum(pline->m_p1.x, pline->m_p2.x);
//   rectangleBounding.top = minimum(pline->m_p1.y, pline->m_p2.y);
//   rectangleBounding.right = maximum(pline->m_p1.x, pline->m_p2.x);
//   rectangleBounding.bottom = maximum(pline->m_p1.y, pline->m_p2.y);
//
//   return true;
//
//}


//inline bool get_bounding_rectangle(RECTANGLE_I32* prectangleBounding, const line * pline)
//{
//
//   rectangleBounding.left = (::i32)minimum(pline->m_p1.x, pline->m_p2.x);
//   rectangleBounding.top = (::i32)minimum(pline->m_p1.y, pline->m_p2.y);
//   rectangleBounding.right = (::i32)maximum(pline->m_p1.x, pline->m_p2.x);
//   rectangleBounding.bottom = (::i32)maximum(pline->m_p1.y, pline->m_p2.y);
//
//   return true;
//
//}


//inline bool get_bounding_rectangle(RECTANGLE_F64* prectangleBounding, const line * pline)
//{
//
//   rectangleBounding.left = minimum(pline->m_p1.x, pline->m_p2.x);
//   rectangleBounding.top = minimum(pline->m_p1.y, pline->m_p2.y);
//   rectangleBounding.right = maximum(pline->m_p1.x, pline->m_p2.x);
//   rectangleBounding.bottom = maximum(pline->m_p1.y, pline->m_p2.y);
//
//   return true;
//
//}

template < primitive_rectangle RECTANGLE >
inline bool get_bounding_rectangle(RECTANGLE & rectangleBounding, const ellipse * pellipse)
{

   copy(rectangleBounding, pellipse);

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
