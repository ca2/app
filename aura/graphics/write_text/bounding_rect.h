#pragma once


inline bool get_bounding_rect(RECTANGLE_I32* prectBounding, const ::write_text::text_out* ptextout)
{

   //__copy(prectangle, pdrawtext->m_rectangle);

   return true;

}


inline bool get_bounding_rect(RECTANGLE_F64* prectBounding, const ::write_text::text_out* ptextout)
{

   //__copy(prectangle, pdrawtext->m_rectangle);

   return true;

}


inline bool get_bounding_rect(RECTANGLE_I32* prectBounding, const ::write_text::draw_text* pdrawtext)
{

   copy(prectBounding, pdrawtext->m_rectangle);

   return true;

}


inline bool get_bounding_rect(RECTANGLE_F64* prectBounding, const ::write_text::draw_text* pdrawtext)
{

   copy(prectBounding, pdrawtext->m_rectangle);

   return true;

}



