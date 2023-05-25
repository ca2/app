#pragma once


template < typename POINT_TYPE >
class line_base
{
public:

   using LINE_TYPE = line_base < POINT_TYPE >;
   using UNIT_TYPE = typename POINT_TYPE::UNIT_TYPE;
   using SIZE_TYPE = typename POINT_TYPE::SIZE_TYPE;
   using RECTANGLE_TYPE = typename POINT_TYPE::RECTANGLE_TYPE;


   POINT_TYPE  m_p1;
   POINT_TYPE  m_p2;


   line_base() {}
   line_base(const line_base& line):m_p1(line.m_p1), m_p2(line.m_p2) {}

};



