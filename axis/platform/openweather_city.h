#pragma once


//#include "acme/primitive/primitive/object.h"


class CLASS_DECL_AXIS openweather_city :
   virtual public ::object
{
public:

   index    m_iIndex;
   string   m_strCnt;
   string   m_strCit;
   i64  m_iId;
   double   m_dLat;
   double   m_dLon;

};



