#pragma once


inline bool get_bounding_rect(RECT* prectBounding, const text_out* ptextout)
{

   //__copy(prect, pdrawtext->m_rect);

   return true;

}


inline bool get_bounding_rect(RECTD* prectBounding, const text_out* ptextout)
{

   //__copy(prect, pdrawtext->m_rect);

   return true;

}


inline bool get_bounding_rect(RECT* prectBounding, const draw_text* pdrawtext)
{

   copy(prectBounding, pdrawtext->m_rect);

   return true;

}


inline bool get_bounding_rect(RECTD* prectBounding, const draw_text* pdrawtext)
{

   copy(prectBounding, pdrawtext->m_rect);

   return true;

}



