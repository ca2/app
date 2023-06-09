// Injected in acme (camilo) from apex(thomas) by camilo on ThomasMonth19-2021 12:27 BRT
// Changed to extended on 2022-02-04 18:08 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "extended_topic.h"
#include "acme/platform/object_reference_count_debug.h"


extended_topic::extended_topic(const ::atom & atom) :
   ::topic(atom)
{

   m_ptab = nullptr;

}


extended_topic::~extended_topic()
{


}



#ifdef _DEBUG


i64 extended_topic::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
{

return ::property_object::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

}


i64 extended_topic::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
{

return ::property_object::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

}


i64 extended_topic::release(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
{

return ::property_object::release(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

}


#endif







/*namespace user
{


extended_topic::extended_topic()
{

   m_bOk = true;

   m_bRet = false;

   m_puserprimitive = nullptr;

   m_ptab = nullptr;

}


extended_topic::~extended_topic()
{

}*/


//::user::form * extended_topic::get_form()
//{
//
//   auto puserelement = m_puserelement;
//
//   if (::is_null(puserelement))
//   {
//
//      return nullptr;
//
//   }
//
//   return puserelement->get_form();
//
//}


//::user::form * extended_topic::get_parent_form()
//{
//
//   auto puserelement = m_puserelement;
//
//   if (::is_null(puserelement))
//   {
//
//      return nullptr;
//
//   }
//
//   return puserelement->get_parent_form();
//
//}


//
//}
//
//
//const ::extended_topic * extended_topic::get_extended_topic() const
//{
//
//   return this;
//
//}
//
//
//
