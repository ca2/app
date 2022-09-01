#include "framework.h"
#include "database.h"


extern "C"
CLASS_DECL_DATABASE_SQLITE3 void database_sqlite3_factory(::factory::factory * pfactory)
{

   pfactory->add_factory_item<::sqlite::database, ::database::database>();

}

