﻿#pragma once


#include "axis/_.h"


// dnf install sqlite-devel
// zypper install sqlite3-devel
#include <sqlite3.h>


#ifdef _database_sqlite3_project
#define CLASS_DECL_DATABASE_SQLITE3 CLASS_DECL_EXPORT
#else
#define CLASS_DECL_DATABASE_SQLITE3 CLASS_DECL_IMPORT
#endif




