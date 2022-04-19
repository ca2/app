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
void material_object::handle_command(const ::atom & atom)
{
   
   //return ::success_none;
   
}


void material_object::destroy()
{

   ::property_object::destroy();

   m_pmapPropertyRoutine.release(OBJECT_REFERENCE_COUNT_DEBUG_THIS);

   m_pia.release(OBJECT_REFERENCE_COUNT_DEBUG_THIS);

}


bool material_object::is_branch_current() const
{

   return true;

}


void material_object::post_routine(const ::procedure & procedure)
{

//   th__row ::interface_only_exception();

   //throw ::interface_only();

   throw ::interface_only();

}


void material_object::send_routine(const ::procedure & procedure)
{

   return __send_routine(this, &material_object::post_routine, procedure);

}


::procedure_array * material_object::procedure_array(const ::atom & atom, bool bCreate)
{

   if (!bCreate)
   {

      auto passociation = m_pmapPropertyRoutine->plookup(atom);

      if (::is_null(passociation))
      {

         return nullptr;

      }

      return &passociation->m_element2;

   }

   m_psystem->__defer_construct_new(m_pmapPropertyRoutine);

   return &m_pmapPropertyRoutine->operator[](atom);

}


void material_object::add_procedure(const ::atom & atom, const ::procedure & procedure)
{

   if (!procedure)
   {

      throw ::exception(error_bad_argument);

   }

   auto pprocedurea = procedure_array(atom, true);

   if (!pprocedurea)
   {

      throw ::exception(error_resource);

   }

   pprocedurea->add(procedure);

}



