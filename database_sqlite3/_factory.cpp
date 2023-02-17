#include "framework.h"
#include "database.h"


extern "C"
__FACTORY_EXPORT void database_sqlite3_factory(::factory::factory * pfactory)
{

   pfactory->add_factory_item<::sqlite::database, ::database::database>();

}

