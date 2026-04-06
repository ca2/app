//
// Created by camilo on 2026-04-04.
//
#include "framework.h"
#include "subsystem.h"
#include "thread/GlobalMutex.h"
#include "node/Shell.h"

namespace subsystem
{

CLASS_DECL_ACME void subsystem_factory(::factory::factory * pfactory)
{

   pfactory->add_factory_item<::windows::subsystem::GlobalMutex, ::subsystem::GlobalMutex>();
   pfactory->add_factory_item<::windows::subsystem::Shell, ::subsystem::Shell>();


   pfactory->add_factory_item<::windows::subsystem::subsystem, ::subsystem::subsystem>();

}


} // namespace subsystem

