#pragma once


#include "acme/_.h"
#include "acme/operating_system.h"


#if defined(_NODE_ANSIOS_LIBRARY)
   #define CLASS_DECL_NODE_ANSIOS  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_NODE_ANSIOS  CLASS_DECL_IMPORT
#endif


namespace node_ansios
{


   class node;


} // namespace node_gnome


#include "app/acme/node/posix/file_memory_map.h"


#include "node.h"


#include "factory_exchange.h"



