#pragma once


#include "_angle.h"
#include "_point.h"
#include "_size.h"


template < primitive_number NUMBER >
class arc_type
{
public:

   using UNIT_TYPE = NUMBER;

   ::point_type < UNIT_TYPE >      m_pointCenter;
   ::size_type < UNIT_TYPE>     m_sizeRadius;
   ::point_type < UNIT_TYPE >      m_pointBegin;
   ::point_type < UNIT_TYPE >      m_pointEnd;
   angle          m_angleBeg;
   angle          m_angleExt;
   angle          m_angleEnd2;
   angle          m_angleRotation;


};



