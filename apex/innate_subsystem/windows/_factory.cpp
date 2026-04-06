//
// Created by camilo on 2026-04-06 10:57 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "subsystem.h"


CLASS_DECL_APEX void innate_subsystem_factory(::factory::factory * pfactory)
{

   pfactory->add_factory_item<::windows::innate_subsystem::subsystem, ::subsystem::subsystem>();

}
