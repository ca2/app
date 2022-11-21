#include "framework.h"
//#include "material_object.h"
////#include "acme/primitive/primitive/function.h"
//#include "acme/parallelization/asynchronous.h"
//#include "acme/primitive/primitive/type.h"
//#include "acme/exception/interface_only.h"
//#include "acme/platform/system.h"
////#include "acme/platform/synchronized_predicate_routine.h"
////#include "acme/primitive/primitive/payload.h"
//#include "acme/parallelization/synchronous_lock.h"
//
//
//material_object::material_object(const material_object & materialobject) :
//   ::PARTICLE(materialobject),
//   ::particle(materialobject),
//   ::element(materialobject),
//   ::matter(materialobject),
//   ::property_object(materialobject),
//   m_pmapPropertyProcedure(materialobject.m_pmapPropertyProcedure),
//   m_pia(materialobject.m_pia)
//{
//
//}
//
//
//
//material_object::~material_object()
//{
//
//}
//
//
////::pointer<task>material_object::branch(
////   ::matter* pmatter,
////   ::enum_priority epriority,
////   u32 nStackSize,
////   u32 dwCreateFlags
////   ARG_SEC_ATTRS)
////{
////
////   auto ptask = fork(
////      [pmatter](){ pmatter->operator()();},
////      epriority,
////      nStackSize,
////      dwCreateFlags
////      ADD_PARAM_SEC_ATTRS
////      );
////
////   return ptask;
////
////}
//
//
//::string material_object::as_string() const
//{
//
//   return __type_name(this);
//
//}
//
//
//// <3TBS_!! handle -> command_handler <3TBS_(I need to suck you)!!
//void material_object::handle_command(const ::atom & atom)
//{
//   
//   //return ::success_none;
//   
//}
//
//
//void material_object::destroy()
//{
//
//   ::property_object::destroy();
//
//   m_pmapPropertyProcedure.release(OBJECT_REFERENCE_COUNT_DEBUG_THIS);
//
//   m_pia.release(OBJECT_REFERENCE_COUNT_DEBUG_THIS);
//
//}
//
//
//bool material_object::is_branch_current() const
//{
//
//   return true;
//
//}
//
//
//void material_object::post_procedure(const ::procedure & procedure)
//{
//
//   throw ::interface_only();
//
//}
//
//
//void material_object::send_procedure(const ::procedure & procedure)
//{
//
//   __material_send_procedure(this, this, &material_object::post_procedure, procedure);
//
//}
//
//
//::procedure_array * material_object::procedure_array(const ::atom & atom, bool bCreate)
//{
//
//   if (!bCreate)
//   {
//
//      auto passociation = m_pmapPropertyProcedure->plookup(atom);
//
//      if (::is_null(passociation))
//      {
//
//         return nullptr;
//
//      }
//
//      return &passociation->m_element2;
//
//   }
//
//   m_pcontext->__defer_construct_new(m_pmapPropertyProcedure);
//
//   return &m_pmapPropertyProcedure->operator[](atom);
//
//}
//
//
//void material_object::add_procedure(const ::atom & atom, const ::procedure & procedure)
//{
//
//   if (!procedure)
//   {
//
//      throw ::exception(error_bad_argument);
//
//   }
//
//   auto pprocedurea = procedure_array(atom, true);
//
//   if (!pprocedurea)
//   {
//
//      throw ::exception(error_resource);
//
//   }
//
//   pprocedurea->add(procedure);
//
//}
//
//
//
//
//::i64_array & material_object::idarray() const
//{
//
//   m_pcontext->__defer_construct_new(((material_object *)this)->m_pia); return *m_pia;
//
//
//}
//
//
//
