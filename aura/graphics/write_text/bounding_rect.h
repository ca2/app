#pragma once


inline bool get_bounding_rectangle(RECTANGLE_I32 & rectangleBounding, const ::write_text::text_out* ptextout)
{

   //__copy(prectangle, pdrawtext->m_rectangle);

   return true;

}


inline bool get_bounding_rectangle(RECTANGLE_F64 & rectangleBounding, const ::write_text::text_out* ptextout)
{

   //__copy(prectangle, pdrawtext->m_rectangle);

   return true;

}


inline bool get_bounding_rectangle(RECTANGLE_I32 & rectangleBounding, const ::write_text::draw_text* pdrawtext)
{

   copy(rectangleBounding, pdrawtext->m_rectangle);

   return true;

}


inline bool get_bounding_rectangle(RECTANGLE_F64 & rectangleBounding, const ::write_text::draw_text* pdrawtext)
{

   copy(rectangleBounding, pdrawtext->m_rectangle);

   return true;

}



