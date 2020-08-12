#pragma once


#include "aura/_.h"


#if defined(_PROGRAMMING_LIBRARY)
#define CLASS_DECL_PROGRAMMING  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_PROGRAMMING  CLASS_DECL_IMPORT
#endif




namespace programming
{


   class application;


} // namespace netnode

#undef APP_TYPE
#define APP_TYPE ::programming::application


#include "app/programming/dynamic_source/dynamic_source.h"

#include "app/programming/introjection/introjection.h"



#include "programming_application.h"
