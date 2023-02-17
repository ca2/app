#include "framework.h"
#include "database.h"


__FACTORY_EXPORT void database_sqlite3_factory(::factory::factory * pfactory)
{

   pfactory->add_factory_item<::sqlite::database, ::database::database>();

}



