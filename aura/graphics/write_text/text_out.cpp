// Created by camilo on 2021-06-08 03:00 BRT <3ThomasBorregaardSørensen__!!
#include "framework.h"


namespace write_text
{


   text_out::text_out()
   {


   }


   text_out::~text_out()
   {


   }


   bool text_out::hit_test(const ::point_f64& point)
   {

      return point.x >= m_point.x
         && point.x <= (m_point.x + m_size.cx)
         && point.y >= m_point.y
         && point.y <= (m_point.y + m_size.cy);

   }


} // namespace write_text



