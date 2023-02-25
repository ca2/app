#pragma once

#include "ace/_ace.h"

#if defined(CUBE) || !defined(_WIN32)
#define CLASS_DECL_EXPORT
#define CLASS_DECL_IMPORT
#else
#define CLASS_DECL_EXPORT CLASS_DECL_EXPORT
#define CLASS_DECL_IMPORT CLASS_DECL_IMPORT
#endif

#if defined(_axis_rdpclient_project)

#define CLASS_DECL_AXIS_RDPCLIENT CLASS_DECL_EXPORT

#else 

#define CLASS_DECL_AXIS_RDPCLIENT CLASS_DECL_IMPORT

#endif


