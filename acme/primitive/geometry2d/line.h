#pragma once


template < primitive_number NUMBER >
class line_base
{
public:

   using LINE_TYPE = line_base < NUMBER >;
   using UNIT_TYPE = NUMBER;
   //using SIZE_TYPE = typename POINT_TYPE::SIZE_TYPE;
   //using RECTANGLE_TYPE = typename POINT_TYPE::RECTANGLE_TYPE;


   ::point_type < UNIT_TYPE >  m_p1;
   ::point_type < UNIT_TYPE >  m_p2;


   line_base() {}
   line_base(const line_base& line):m_p1(line.m_p1), m_p2(line.m_p2) {}

};



