#include "framework.h"



layered::~layered()
{


}


void layered::set_os_data(byte bIndex, void* p)
{

   if (bIndex >= MAX_LAYERED_COUNT)
   {

      __throw(index_out_of_bounds("layered::set_os_data"));

   }

   if (m_osdataa[bIndex])
   {

      __throw(exception::exception("layered collision!!"));

   }

   m_osdataa[bIndex] = p;

}

