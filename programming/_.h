#pragma once


#include "axis/_.h"


#if defined(_programming_project)
#define CLASS_DECL_APP_PROGRAMMING  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_APP_PROGRAMMING  CLASS_DECL_IMPORT
#endif


#include "programming/_.h"

#include "dynamic_source/_.h"

#include "introjection/_.h"

//#define DS_INCLUDE(NAME) \
//{       \
//   static auto s_uniqueindex = create_unique_index(); \
//   auto pfilesystemcacheitem = netnode_include_file_system_cache_item(NAME, s_uniqueindex); \
//   include(pfilesystemcacheitem); \
//}      


namespace programming
{

   
   class file_system_cache;
   class real_path;


} // namespace programming

