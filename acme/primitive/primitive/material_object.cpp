#include "framework.h"


material_object::~material_object()
{

}


//__pointer(task) material_object::branch(
//   ::matter* pmatter,
//   ::enum_priority epriority,
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


::string material_object::get_string() const
{

   return __type_name(this);

}


// <3TBS_!! handle -> command_handler <3TBS_(I need to suck you)!!
void material_object::handle_command(const ::id & id)
{
   
   //return ::success_none;
   
}


bool material_object::is_branch_current() const
{

   return true;

}


void material_object::post_routine(const ::routine & routine)
{

//   th__row ::interface_only_exception();

   //throw ::interface_only_exception();

   throw ::interface_only_exception();

}


void material_object::send_routine(const ::routine & routine)
{

   return __send_routine(this, &material_object::post_routine, routine);

   //return send_object(e_message_system, e_system_message_method, routine, durationTimeout);

}


