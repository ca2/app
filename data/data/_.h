#pragma once


#include "axis/_.h"


#if defined(_CA2_DATA_DLL)
#define CLASS_DECL_CA2_DATA  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_CA2_DATA  CLASS_DECL_IMPORT
#endif


CLASS_DECL_CA2_DATA int_bool init_data_library();


#include <mysql/mysql.h>
//#include "app/data/mysql/mysql_result.h"
#include "app/data/mysql/mysql_database.h"



