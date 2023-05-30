#pragma once


#include "angle.h"
#include "point.h"
#include "size.h"


template < primitive_number NUMBER >
class arc_type
{
public:

   using UNIT_TYPE = NUMBER;

   ::point_type < UNIT_TYPE >       m_pointCenter;
   ::size_type < UNIT_TYPE>         m_sizeRadius;
   ::point_type < UNIT_TYPE >       m_pointBegin;
   ::point_type < UNIT_TYPE >       m_pointEnd;
   ::angle_f64                      m_angleBeg;
   ::angle_f64                      m_angleExt;
   ::angle_f64                      m_angleEnd2;
   ::angle_f64                      m_angleRotation;


};



