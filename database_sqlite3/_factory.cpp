#include "framework.h"
#include "database.h"


IMPLEMENT_FACTORY(database_sqlite3)
{

   pfactory->add_factory_item<::sqlite::database, ::database::database>();

}



