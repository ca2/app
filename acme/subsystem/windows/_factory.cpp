//
// Created by camilo on 2026-04-04.
//
#include "framework.h"
#include "thread/GlobalMutex.h"

namespace subsystem
{

CLASS_DECL_ACME void subsystem_factory(::factory::factory * pfactory)
{

   pfactory->add_factory_item<::windows::subsystem::GlobalMutex, ::subsystem::GlobalMutex>();

}


} // namespace subsystem

