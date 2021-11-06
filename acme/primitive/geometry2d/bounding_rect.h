#pragma once


inline bool get_bounding_rectangle(RECTANGLE_I32 * prectangleBounding, const ::arc* parc)
{

   prectangleBounding->left = (::i32) (parc->m_pointCenter.x - parc->m_sizeRadius.cx);
   prectangleBounding->right = (::i32)(parc->m_pointCenter.x + parc->m_sizeRadius.cx);
   prectangleBounding->top = (::i32)(parc->m_pointCenter.y - parc->m_sizeRadius.cy);
   prectangleBounding->bottom = (::i32)(parc->m_pointCenter.y + parc->m_sizeRadius.cy);

   return true;

}


inline bool get_bounding_rectangle(RECTANGLE_F64 * prectangleBounding, const ::arc * parc)
{

   prectangleBounding->left = parc->m_pointCenter.x - parc->m_sizeRadius.cx;
   prectangleBounding->right = parc->m_pointCenter.x + parc->m_sizeRadius.cx;
   prectangleBounding->top = parc->m_pointCenter.y - parc->m_sizeRadius.cy;
   prectangleBounding->bottom = parc->m_pointCenter.y + parc->m_sizeRadius.cy;

   return true;

}


inline bool get_bounding_rectangle(RECTANGLE_I32* prectangleBounding, const line * pline)
{

   prectangleBounding->left = (::i32) minimum(pline->m_p1.x, pline->m_p2.x);
   prectangleBounding->top = (::i32) minimum(pline->m_p1.y, pline->m_p2.y);
   prectangleBounding->right = (::i32) maximum(pline->m_p1.x, pline->m_p2.x);
   prectangleBounding->bottom = (::i32) maximum(pline->m_p1.y, pline->m_p2.y);

   return true;

}


inline bool get_bounding_rectangle(RECTANGLE_F64* prectangleBounding, const line* pline)
{

   prectangleBounding->left = minimum(pline->m_p1.x, pline->m_p2.x);
   prectangleBounding->top = minimum(pline->m_p1.y, pline->m_p2.y);
   prectangleBounding->right = maximum(pline->m_p1.x, pline->m_p2.x);
   prectangleBounding->bottom = maximum(pline->m_p1.y, pline->m_p2.y);

   return true;

}


//inline bool get_bounding_rectangle(RECTANGLE_I32* prectangleBounding, const line * pline)
//{
//
//   prectangleBounding->left = (::i32)minimum(pline->m_p1.x, pline->m_p2.x);
//   prectangleBounding->top = (::i32)minimum(pline->m_p1.y, pline->m_p2.y);
//   prectangleBounding->right = (::i32)maximum(pline->m_p1.x, pline->m_p2.x);
//   prectangleBounding->bottom = (::i32)maximum(pline->m_p1.y, pline->m_p2.y);
//
//   return true;
//
//}


//inline bool get_bounding_rectangle(RECTANGLE_F64* prectangleBounding, const line * pline)
//{
//
//   prectangleBounding->left = minimum(pline->m_p1.x, pline->m_p2.x);
//   prectangleBounding->top = minimum(pline->m_p1.y, pline->m_p2.y);
//   prectangleBounding->right = maximum(pline->m_p1.x, pline->m_p2.x);
//   prectangleBounding->bottom = maximum(pline->m_p1.y, pline->m_p2.y);
//
//   return true;
//
//}


inline bool get_bounding_rectangle(RECTANGLE_I32 * prectangleBounding, const RECTANGLE_I32 * prectangle)
{

   copy(prectangleBounding, prectangle);

   return true;

}


inline bool get_bounding_rectangle(RECTANGLE_F64* prectangleBounding, const RECTANGLE_I32 * prectangle)
{

   copy(prectangleBounding, prectangle);

   return true;

}


inline bool get_bounding_rectangle(RECTANGLE_I32* prectangleBounding, const RECTANGLE_F64 * prectangle)
{

   copy(prectangleBounding, prectangle);

   return true;

}


inline bool get_bounding_rectangle(RECTANGLE_F64* prectangleBounding, const RECTANGLE_F64 * prectangle)
{

   copy(prectangleBounding, prectangle);

   return true;

}


inline bool get_bounding_rectangle(RECTANGLE_I32* prectangleBounding, const ellipse * pellipse)
{

   copy(prectangleBounding, pellipse);

   return true;

}


inline bool get_bounding_rectangle(RECTANGLE_F64* prectangleBounding, const ellipse * pellipse)
{

   copy(prectangleBounding, pellipse);

   return true;

}


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
