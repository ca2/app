#include "framework.h"
#include "_.h"
#include "acme/primitive/text/international_locale_schema.h"


namespace dynamic_source
{


   session::session()
   {


   }


   session::~session()
   {
      ::text::international::locale_schema * pls = m_set["locale_schema"].cast < ::text::international::locale_schema > ();
      if(pls != nullptr)
      {
         ::output_debug_string("locale_schema.m_idLocale=" + pls->m_idLocale.str());
      }
      if(m_set.has_property("rsa_n"))
      {
         ::output_debug_string("rsa_n");
      }
   }


   void session::initialize_dynamic_source_session(const string& strSessid, ::dynamic_source::script_manager* pmanager)
   {

      //auto estatus = 
      
      ::object::initialize(pmanager);

      //if (!estatus)
      //{

      //   return estatus;

      //}
      
      m_strSessid = strSessid;

      //estatus = 
      
      __refer(m_pmanager, pmanager);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


#ifdef _DEBUG


   i64 session::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
   {

      return object::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }

   i64 session::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
   {

      return object::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }


#endif


} // namespace dynamic_source





