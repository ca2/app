#pragma once


#if defined(WINDOWS_DESKTOP)

#include "windows/_windows_impl.h"

#endif


#if defined(LINUX)

#include "cairo/_impl.h"

#endif






//CLASS_DECL_CORE inline ::core::user* get_context_user(::object* pobject)
//{
//
//   if (pobject->get_context_user())
//   {
//
//      return (::core::user*) pobject->get_context_user()->m_pObjectThis;
//
//   }
//
//   return ::get_context_user();
//
//}
//
//
//CLASS_DECL_CORE inline ::core::user* get_context_user(::aura::application* papp)
//{
//
//   return get_context_user((::object*) papp);
//
//}
