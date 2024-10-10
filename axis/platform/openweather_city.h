#pragma once


////#include "acme/prototype/prototype/object.h"


class CLASS_DECL_AXIS openweather_city :
   virtual public ::object
{
public:

   ::collection::index    m_iIndex;
   string   m_strCnt;
   string   m_strCit;
   i64  m_iId;
   double   m_dLat;
   double   m_dLon;

};



