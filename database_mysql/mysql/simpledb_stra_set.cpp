#include "framework.h"


db_stra_set::db_stra_set(db_server * pserver, ::database::key & atom) :
   id()(atom)
{
   __UNREFERENCED_PARAMETER(pserver);
   m_iMaximumCount = 32;
}

void db_stra_set::get_data(string_array_base & stra)
{
   datastream()->get(id(), stra);
}


// return the number of set directories
::collection::count db_stra_set::set_data(string_array_base & stra)
{
   datastream()->set(id(), stra);
   return stra.get_size();
}


