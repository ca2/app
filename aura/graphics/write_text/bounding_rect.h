#pragma once


inline bool get_bounding_rectangle(::rectangle_i32 & rectangleBounding, const ::write_text::text_out & textout)
{

   //copy(prectangle, pdrawtext->m_rectangle);

   return true;

}


inline bool get_bounding_rectangle(::rectangle_f64 & rectangleBounding, const ::write_text::text_out & textout)
{

   //copy(prectangle, pdrawtext->m_rectangle);

   return true;

}


inline bool get_bounding_rectangle(::rectangle_i32 & rectangleBounding, const ::write_text::draw_text & drawtext)
{

   rectangleBounding = drawtext.m_rectangle;

   return true;

}


inline bool get_bounding_rectangle(::rectangle_f64 & rectangleBounding, const ::write_text::draw_text & drawtext)
{

   copy(rectangleBounding, drawtext.m_rectangle);

   return true;

}



