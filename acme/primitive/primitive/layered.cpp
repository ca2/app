#include "framework.h"



layered::~layered()
{


}


void layered::set_layer(byte bLayeredIndex, void* p)
{

   if (bLayeredIndex >= MAX_LAYERED_COUNT)
   {

      __throw(index_out_of_bounds("layered::set_os_data"));

   }

   if (m_pa[bLayeredIndex])
   {

      __throw(exception::exception("layered layer collision!!"));

   }

   m_pa[bLayeredIndex] = p;

}

