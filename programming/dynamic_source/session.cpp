#include "framework.h"
#include "_.h"


namespace dynamic_source
{


   session::session()
   {


   }


   session::~session()
   {
      ::str::international::locale_schema * pls = m_set["locale_schema"].cast < ::str::international::locale_schema > ();
      if(pls != nullptr)
      {
         ::output_debug_string("locale_schema.m_idLocale=" + pls->m_idLocale.str());
      }
      if(m_set.has_property("rsa_n"))
      {
         ::output_debug_string("rsa_n");
      }
   }


   ::e_status session::initialize_dynamic_source_session(const string& strSessid, ::dynamic_source::script_manager* pmanager)
   {

      auto estatus = ::object::initialize(pmanager);

      if (!estatus)
      {

         return estatus;

      }
      
      m_strSessid = strSessid;

      estatus = __refer(m_pmanager, pmanager);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   i64 session::add_ref(OBJ_REF_DBG_PARAMS_DEF)
   {

      return object::add_ref(OBJ_REF_DBG_ARGS);

   }

   i64 session::release(OBJ_REF_DBG_PARAMS_DEF)
   {

      return object::dec_ref(OBJ_REF_DBG_ARGS);

   }


} // namespace dynamic_source





