// Injected in acme (camilo) from apex(thomas) by camilo on ThomasMonth19-2021 12:27 BRT
// Changed to extended on 2022-02-04 18:08 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "extended_topic.h"
//#include "acme/platform/reference_count_debug.h"


extended_topic::extended_topic(const ::atom & atom) :
   ::topic(atom)
{

   m_ptab = nullptr;

}


extended_topic::~extended_topic()
{


}



#ifdef _DEBUG


long long extended_topic::increment_reference_count()
{

return ::property_object::increment_reference_count();

}


long long extended_topic::decrement_reference_count()
{

return ::property_object::decrement_reference_count();

}


long long extended_topic::release()
{

return ::property_object::release();

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
