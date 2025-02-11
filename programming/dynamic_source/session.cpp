#include "framework.h"
#include "session.h"
#include "script_manager.h"
#include "acme/prototype/text/international_locale_schema.h"
#include "acme/crypto/rsa.h"


namespace dynamic_source
{


   interlocked_count g_interlockedcountDynamicSourceSession;


   session::session()
   {

      m_pmanager = nullptr;

      g_interlockedcountDynamicSourceSession++;

      ::informationf("%s currently allocated count = %lld", typeid(*this).name(), g_interlockedcountDynamicSourceSession.operator long long());

   }


   session::~session()
   {

      g_interlockedcountDynamicSourceSession--;

      ::text::international::locale_schema * pls = m_set["locale_schema"].cast < ::text::international::locale_schema > ();
      if(pls != nullptr)
      {
         informationf("locale_schema.m_atomLocale=" + pls->m_strLocale);
      }
      if(m_set.has_property("rsa_n"))
      {
         informationf("rsa_n");
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


   long long session::increment_reference_count()
   {

      return ::particle::increment_reference_count();

   }

   long long session::decrement_reference_count()
   {

      return ::particle::decrement_reference_count();

   }


#endif


} // namespace dynamic_source





