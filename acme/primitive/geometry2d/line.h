#pragma once


template < typename POINT_TYPE >
class line_base
{
public:

   using LINE_BASE_TYPE = line_base < POINT_TYPE >;
   using POINT_BASE_TYPE = typename POINT_TYPE::POINT_BASE_TYPE;
   using UNIT_TYPE = typename POINT_TYPE::UNIT_TYPE;
   using SIZE_TYPE = typename POINT_TYPE::SIZE_TYPE;
   using RECT_TYPE = typename POINT_TYPE::RECT_TYPE;
   using RECT_BASE_TYPE = typename RECT_TYPE::RECT_BASE_TYPE;


   POINT_TYPE  m_p1;
   POINT_TYPE  m_p2;


   line_base() {}
   line_base(const line_base& line):m_p1(line.m_p1), m_p2(line.m_p2) {}

};


using line = line_base < ::point >;
using line64 = line_base < ::point64 >;
using linef = line_base < ::pointf >;
using lined = line_base < ::pointd >;


