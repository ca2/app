#pragma once


template < primitive_number NUMBER >
class lines_base :
   virtual public point_array_base < NUMBER >
{
public:


   //using POLYGON_BASE_TYPE = point_array_base < POINT_TYPE >;
   //using POINT_BASE_TYPE = POINT_TYPE;
   using UNIT_TYPE = NUMBER;
   //using SIZE_TYPE = typename POINT_TYPE::SIZE_TYPE;
   //using RECTANGLE_TYPE = typename POINT_TYPE::RECTANGLE_TYPE;
   //using RECTANGLE_BASE_TYPE = typename RECTANGLE_TYPE::RECTANGLE_BASE_TYPE;


   lines_base();
   lines_base(const lines_base& lines);
   lines_base(lines_base&& lines);
   ~lines_base() override;


};


template < primitive_number NUMBER >
lines_base < NUMBER >::lines_base()
{

}


template < primitive_number NUMBER >
inline lines_base < NUMBER >::lines_base(const lines_base& lines) :
   point_array_base < NUMBER >(lines)
{

}


template < primitive_number NUMBER >
inline lines_base < NUMBER >::lines_base(lines_base&& lines) :
   point_array_base < NUMBER >(::transfer(lines))
{


}


template < primitive_number NUMBER >
lines_base < NUMBER >::~lines_base()

{

}

