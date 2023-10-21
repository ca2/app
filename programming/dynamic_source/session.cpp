#include "framework.h"
#include "session.h"
#include "script_manager.h"
#include "acme/primitive/text/international_locale_schema.h"
#include "acme/crypto/rsa.h"


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
         ::informationf("locale_schema.m_atomLocale=" + pls->m_atomLocale);
      }
      if(m_set.has_property("rsa_n"))
      {
         ::informationf("rsa_n");
      }
   }


   void session::initialize_dynamic_source_session(const string& strSessid, ::dynamic_source::script_manager* pmanager)
   {

      //auto estatus = 
      
      ::particle::initialize(pmanager);

      //if (!estatus)
      //{

      //   return estatus;

      //}
      
      m_strSessid = strSessid;

      //estatus = 
      
      m_pmanager = pmanager;

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


#ifdef _DEBUG


   i64 session::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
   {

      return ::particle::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }

   i64 session::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
   {

      return ::particle::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }


#endif


} // namespace dynamic_source





