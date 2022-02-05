// Injected in acme (camilo) from apex(thomas) by camilo on ThomasMonth19-2021 12:27 BRT
// Changed to extended on 2022-02-04 18:08 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "acme/platform/object_reference_count_debug.h"
#include "acme/user/check.h"
#include "acme/user/text.h"
#include "acme/user/element.h"


extended_topic::extended_topic(const ::atom & atom) :
   ::material_object(atom),
   ::property_object(atom),
   ::object(atom)
{

   m_bOk = true;
   m_bRet = false;
   m_ptab = nullptr;
   m_bRet = false;

}


extended_topic::~extended_topic()
{

   m_pmatter.release(OBJECT_REFERENCE_COUNT_DEBUG_THIS_FUNCTION_LINE);

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


::user::form * extended_topic::get_form()
{

   auto puserelement = m_puserelement;

   if (::is_null(puserelement))
   {

      return nullptr;

   }

   return puserelement->get_form();

}


::user::form * extended_topic::get_parent_form()
{

   auto puserelement = m_puserelement;

   if (::is_null(puserelement))
   {

      return nullptr;

   }

   return puserelement->get_parent_form();

}


::user::interaction * extended_topic::user_interaction()
{

   if (::is_null(m_puserelement))
   {

      return nullptr;

   }

   return m_puserelement->m_puserinteraction;

}


void extended_topic::Nok()
{

   m_bOk = false;

   m_bRet = true;

}

void extended_topic::Ret()
{

   m_bRet = true;

}

void extended_topic::Ok()
{

   m_bOk = true;

   m_bRet = true;

}


::atom extended_topic::user_element_id() const
{

   if (::is_null(m_puserelement))
   {

      return ::atom::e_type_null;

   }

   return m_puserelement->m_id;

}


//impact * extended_topic::get_view()
//{

//   return dynamic_cast <::user::impact *> (m_puserinteraction);

//}

//document * extended_topic::get_document()
//{

//   impact * pimpact = get_view();

//   if(pimpact == nullptr)
//      return nullptr;

//   return pimpact->get_document();

//}

//impact_system * extended_topic::get_impact_system()
//{

//   document * pdocument = get_document();

//   if(pdocument == nullptr)
//      return nullptr;

//   return pdocument->get_document_template();

//}

//string extended_topic::get_impact_matter()
//{

//   impact_system * psystem = get_impact_system();

//   if(psystem == nullptr)
//      return "";

//   return psystem->m_strMatter;

//}


//} // namespace extended_topic



