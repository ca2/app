#pragma once


inline bool get_bounding_rect(RECT32 * prectBounding, const ::arc* parc)
{

   prectBounding->left = (::i32) (parc->m_pointCenter.x - parc->m_sizeRadius.cx);
   prectBounding->right = (::i32)(parc->m_pointCenter.x + parc->m_sizeRadius.cx);
   prectBounding->top = (::i32)(parc->m_pointCenter.y - parc->m_sizeRadius.cy);
   prectBounding->bottom = (::i32)(parc->m_pointCenter.y + parc->m_sizeRadius.cy);

   return true;

}


inline bool get_bounding_rect(RECTD * prectBounding, const ::arc * parc)
{

   prectBounding->left = parc->m_pointCenter.x - parc->m_sizeRadius.cx;
   prectBounding->right = parc->m_pointCenter.x + parc->m_sizeRadius.cx;
   prectBounding->top = parc->m_pointCenter.y - parc->m_sizeRadius.cy;
   prectBounding->bottom = parc->m_pointCenter.y + parc->m_sizeRadius.cy;

   return true;

}


inline bool get_bounding_rect(RECT32* prectBounding, const line * pline)
{

   prectBounding->left = min(pline->m_p1.x, pline->m_p2.x);
   prectBounding->top = min(pline->m_p1.y, pline->m_p2.y);
   prectBounding->right = max(pline->m_p1.x, pline->m_p2.x);
   prectBounding->bottom = max(pline->m_p1.y, pline->m_p2.y);

   return true;

}


inline bool get_bounding_rect(RECTD* prectBounding, const line* pline)
{

   prectBounding->left = min(pline->m_p1.x, pline->m_p2.x);
   prectBounding->top = min(pline->m_p1.y, pline->m_p2.y);
   prectBounding->right = max(pline->m_p1.x, pline->m_p2.x);
   prectBounding->bottom = max(pline->m_p1.y, pline->m_p2.y);

   return true;

}


inline bool get_bounding_rect(RECT32* prectBounding, const lined* pline)
{

   prectBounding->left = (::i32)min(pline->m_p1.x, pline->m_p2.x);
   prectBounding->top = (::i32)min(pline->m_p1.y, pline->m_p2.y);
   prectBounding->right = (::i32)max(pline->m_p1.x, pline->m_p2.x);
   prectBounding->bottom = (::i32)max(pline->m_p1.y, pline->m_p2.y);

   return true;

}


inline bool get_bounding_rect(RECTD* prectBounding, const lined* pline)
{

   prectBounding->left = min(pline->m_p1.x, pline->m_p2.x);
   prectBounding->top = min(pline->m_p1.y, pline->m_p2.y);
   prectBounding->right = max(pline->m_p1.x, pline->m_p2.x);
   prectBounding->bottom = max(pline->m_p1.y, pline->m_p2.y);

   return true;

}


inline bool get_bounding_rect(RECT32 * prectBounding, const RECT32 * prect)
{

   copy(prectBounding, prect);

   return true;

}


inline bool get_bounding_rect(RECTD* prectBounding, const RECT32 * prect)
{

   copy(prectBounding, prect);

   return true;

}


inline bool get_bounding_rect(RECT32* prectBounding, const RECTD * prect)
{

   copy(prectBounding, prect);

   return true;

}


inline bool get_bounding_rect(RECTD* prectBounding, const RECTD * prect)
{

   copy(prectBounding, prect);

   return true;

}


inline bool get_bounding_rect(RECT32* prectBounding, const oval* prect)
{

   copy(prectBounding, prect);

   return true;

}


inline bool get_bounding_rect(RECTD* prectBounding, const oval* prect)
{

   copy(prectBounding, prect);

   return true;

}


inline bool get_bounding_rect(RECT32* prectBounding, const ovald* prect)
{

   copy(prectBounding, prect);

   return true;

}


inline bool get_bounding_rect(RECTD* prectBounding, const ovald* prect)
{

   copy(prectBounding, prect);

   return true;

}


