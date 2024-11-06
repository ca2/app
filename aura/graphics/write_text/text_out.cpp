// Created by camilo on 2021-06-08 03:00 BRT <3ThomasBorregaardSorensen__!!
#include "framework.h"
#include "text_out.h"
#include "draw_text.h"


namespace write_text
{


   text_out::text_out()
   {


   }


   text_out::~text_out()
   {


   }


   void text_out::offset(const ::double_point & point)
   {

      m_point.offset(point);

   }


   bool text_out::hit_test(const ::double_point& point)
   {

      return contains(point);

   }


   bool text_out::contains(const ::double_point & point)
   {

      return point.x() >= m_point.x()
         && point.x() <= (m_point.x() + m_size.cx())
         && point.y() >= m_point.y()
         && point.y() <= (m_point.y() + m_size.cy());

   }


} // namespace write_text



