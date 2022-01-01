// Injected in acme (camilo) from apex(thomas) by camilo on ThomasMonth19-2021 12:27 BRT
#include "framework.h"
#include "acme/platform/object_reference_count_debug.h"
#include "acme/user/check.h"
#include "acme/user/text.h"
#include "acme/user/element.h"


subject::subject(const ::id & id) :
   ::material_object(id),
   ::property_object(id),
   ::object(id)
{

   m_bOk = true;
   m_bRet = false;
   //m_puserelement = nullptr;
   m_ptab = nullptr;
   m_esubject = e_subject_handle;
   m_bRet = false;

}


subject::~subject()
{

   m_pmatter.release(OBJECT_REFERENCE_COUNT_DEBUG_THIS_FUNCTION_LINE);

}



#ifdef _DEBUG


i64 subject::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
{

return ::property_object::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

}


i64 subject::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
{

return ::property_object::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

}


i64 subject::release(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
{

return ::property_object::release(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

}


#endif







/*namespace user
{


subject::subject()
{

   m_bOk = true;

   m_bRet = false;

   m_puserprimitive = nullptr;

   m_ptab = nullptr;

}


subject::~subject()
{

}*/


::user::form * subject::get_form()
{

   auto puserelement = m_puserelement;

   if (::is_null(puserelement))
   {

      return nullptr;

   }

   return puserelement->get_form();

}


::user::form * subject::get_parent_form()
{

   auto puserelement = m_puserelement;

   if (::is_null(puserelement))
   {

      return nullptr;

   }

   return puserelement->get_parent_form();

}


::user::interaction * subject::user_interaction()
{

   if (::is_null(m_puserelement))
   {

      return nullptr;

   }

   return m_puserelement->m_puserinteraction;

}


void subject::Nok()
{

   m_bOk = false;

   m_bRet = true;

}

void subject::Ret()
{

   m_bRet = true;

}

void subject::Ok()
{

   m_bOk = true;

   m_bRet = true;

}


::id subject::user_element_id() const
{

   if (::is_null(m_puserelement))
   {

      return ::id::e_type_null;

   }

   return m_puserelement->m_id;

}


//impact * subject::get_view()
//{

//   return dynamic_cast <::user::impact *> (m_puserinteraction);

//}

//document * subject::get_document()
//{

//   impact * pimpact = get_view();

//   if(pimpact == nullptr)
//      return nullptr;

//   return pimpact->get_document();

//}

//impact_system * subject::get_impact_system()
//{

//   document * pdocument = get_document();

//   if(pdocument == nullptr)
//      return nullptr;

//   return pdocument->get_document_template();

//}

//string subject::get_impact_matter()
//{

//   impact_system * psystem = get_impact_system();

//   if(psystem == nullptr)
//      return "";

//   return psystem->m_strMatter;

//}


//} // namespace subject



