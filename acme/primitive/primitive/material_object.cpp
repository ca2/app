#include "framework.h"


material_object::~material_object()
{

}


//__transport(task) material_object::branch(
//   ::matter* pmatter,
//   ::e_priority epriority,
//   u32 nStackSize,
//   u32 dwCreateFlags
//   ARG_SEC_ATTRS)
//{
//
//   auto ptask = fork(
//      [pmatter](){ pmatter->operator()();},
//      epriority,
//      nStackSize,
//      dwCreateFlags
//      ADD_PARAM_SEC_ATTRS
//      );
//
//   return ptask;
//
//}


::string material_object::to_string() const
{

   return type_c_str();

}


// <3TBS_!! handle -> command_handler <3TBS_(I need to suck you)!!
::e_status material_object::command_handler(const ::id & id)
{
   
   return ::success_none;
   
}

