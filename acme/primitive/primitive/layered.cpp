#include "framework.h"



layered::~layered()
{


}


void layered::set_layer(byte bLayeredIndex, void* p)
{

   if (bLayeredIndex >= MAX_LAYERED_COUNT)
   {

      __throw(error_index_out_of_bounds, "layered::set_layer");

   }

   if (m_pa[bLayeredIndex])
   {

      __throw(exception::exception("layered layer collision!!"));

   }

   m_pa[bLayeredIndex] = p;

}


void layered::set_os_data(byte b, void * p)
{

   if (b >= MAX_LAYERED_COUNT)
   {

      __throw(error_index_out_of_bounds, "layered::set_os_data");

   }

   if (m_osdataa[b])
   {

      __throw(exception::exception("layered os_data collision!!"));

   }

   m_osdataa[b] = p;

}



