#pragma once


template < primitive_number NUMBER >
class line_type
{
public:

   using LINE_TYPE = line_type < NUMBER >;
   using UNIT_TYPE = NUMBER;
   //using SIZE_TYPE = typename POINT_TYPE::SIZE_TYPE;
   //using RECTANGLE_TYPE = typename POINT_TYPE::RECTANGLE_TYPE;


   ::point_type < UNIT_TYPE >  m_p1;
   ::point_type < UNIT_TYPE >  m_p2;


   line_type() {}
   line_type(const line_type& line):m_p1(line.m_p1), m_p2(line.m_p2) {}


   bool contains(const ::point_type <NUMBER > & point, float epsilon = 0.001f)
   {

      return segment_contains(m_p1, m_p2, point, epsilon);

   }


   line_type & offset(const ::point_type < NUMBER > & point)
   {

      m_p1.offset(point);

      m_p2.offset(point);

      return *this;

   }
   
   
   void expand_bounding_box(::point_type < UNIT_TYPE > & top_left, ::point_type < UNIT_TYPE > & bottom_right)
   {
      
      m_p1.expand_bounding_box(top_left, bottom_right);
      
      m_p2.expand_bounding_box(top_left, bottom_right);
      
   }


};



