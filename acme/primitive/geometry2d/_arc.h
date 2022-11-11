#pragma once


#include "_angle.h"
#include "_point.h"
#include "_size.h"


class CLASS_DECL_ACME arc
{
public:


   point_f64      m_pointCenter;
   ::size_f64     m_sizeRadius;
   point_f64      m_pointBegin;
   point_f64      m_pointEnd;
   angle          m_angleBeg;
   angle          m_angleExt;
   angle          m_angleEnd2;
   angle          m_angleRotation;


};



