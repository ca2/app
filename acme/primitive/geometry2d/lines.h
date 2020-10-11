#pragma once


template < typename POINT_TYPE >
class lines_base :
   virtual public point_array_base < POINT_TYPE >
{
public:

   using POLYGON_BASE_TYPE = point_array_base < POINT_TYPE >;
   using POINT_BASE_TYPE = typename POINT_TYPE::POINT_BASE_TYPE;
   using UNIT_TYPE = typename POINT_TYPE::UNIT_TYPE;
   using SIZE_TYPE = typename POINT_TYPE::SIZE_TYPE;
   using RECT_TYPE = typename POINT_TYPE::RECT_TYPE;
   using RECT_BASE_TYPE = typename RECT_TYPE::RECT_BASE_TYPE;


   lines_base();
   lines_base(const lines_base& lines);
   lines_base(lines_base&& lines);
   ~lines_base();



};




template < typename POINT_TYPE >
lines_base < POINT_TYPE >::lines_base()
{

}




template < typename POINT_TYPE >
inline lines_base < POINT_TYPE >::lines_base(const lines_base& lines) :
   point_array_base < POINT_TYPE >(lines)
{

}


template < typename POINT_TYPE >
inline lines_base < POINT_TYPE >::lines_base(lines_base&& lines) :
   point_array_base < POINT_TYPE >(::move(lines))
{


}



template < typename POINT_TYPE >
lines_base < POINT_TYPE >::~lines_base()

{

}


using lines = lines_base < point >;
using lines64 = lines_base < point64 >;
using linesf = lines_base < pointf >;
using linesd = lines_base < pointd >;



