#include "framework.h"

db_stra_set::db_stra_set(db_server * pserver, ::database::key & id) :
   m_id(id)
{
   __UNREFERENCED_PARAMETER(pserver);
   m_iMaximumCount = 32;
}

void db_stra_set::get_data(string_array & stra)
{
   data_get(m_id, stra);
}


// return the number of set directories
::count db_stra_set::set_data(string_array & stra)
{
   data_set(m_id, stra);
   return stra.get_size();
}


