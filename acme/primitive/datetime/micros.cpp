// cs<3tbs!! 2020-11-28 23:37 BRT
#include "framework.h"


void micros::sleep() const
{

   ::sleep(*this);

}


void micros::Now()
{

   m_i = ::get_micros();

}

