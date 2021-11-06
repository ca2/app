#include "framework.h"


extern "C"
void database_sqlite3_factory_exchange(::factory_map * pfactorymap)
{

   pfactorymap->create_factory<::sqlite::database, ::database::database>();

}

