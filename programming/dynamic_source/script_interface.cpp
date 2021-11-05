#include "framework.h"
#include "_.h"
#include "axis/id.h"


namespace dynamic_source
{


   script_interface::script_interface()
   {

      m_pnetnodescriptimpl = nullptr;

      m_pnetnodescriptinterface = nullptr;

      m_iDebug             = 0;

   }


   script_interface::~script_interface()
   {

   }


   const char* script_interface::debug_note() const
   {

      return m_strNote;

   }


   ::e_status script_interface::initialize(::object * pobject)
   {

      auto estatus = ::html::file::initialize(pobject);

      if (!estatus)
      {

         return estatus;

      }

      __pointer(script_interface) pinterface = pobject;

      if (pinterface)
      {

         if (!m_pmain)
         {

            __note_assign(m_pmain, pinterface->m_pmain.get(), OBJECT_REFERENCE_COUNT_DEBUG_COMMA_THIS_NOTE("scptiface:init:referer://"+ m_strNote));

         }

      }

      return estatus;

   }


   ::e_status script_interface::init1()
   {

      ::e_status estatus = ::success_none;

      return estatus;

   }


   //::e_status script_interface::destroy()
   //{

   //   auto estatus = ::html::file::destroy();

   //   m_pmain.release(OBJECT_REFERENCE_COUNT_DEBUG_THIS);
   //   m_pinstanceParent2.release(OBJECT_REFERENCE_COUNT_DEBUG_THIS);
   //   m_pscript2.release(OBJECT_REFERENCE_COUNT_DEBUG_THIS);

   //   return estatus;

   //}

   ::e_status script_interface::destroy()
   {

      auto estatus = ::html::file::destroy();

      m_pmain.release(OBJECT_REFERENCE_COUNT_DEBUG_THIS);
      m_pinstanceParent2.release(OBJECT_REFERENCE_COUNT_DEBUG_THIS);
      m_pscript2.release(OBJECT_REFERENCE_COUNT_DEBUG_THIS);

      return estatus;


   }


   ::e_status     script_interface::run()
   {

      return ::success;

   }


   void script_interface::dinit()
   {

   }


   //void script_interface::dprint(const ::string &)
   //{

   //}


   //property & script_interface::get(const ::string & pszKey)
   //{
   //   return netnodesocket()->m_request.form().get()[pszKey];
   //}


   ::file::file * script_interface::file()
   {

      if(m_pmain)
      {

         return m_pmain->file();

      }
      else if(netnodesocket())
      {

         return netnodesocket()->response().file();

      }
      else
      {

         throw ::interface_only_exception();

      }

   }


   ::e_status script_interface::on_initialize()
   {

      return ::success;

   }


   //::e_status script_interface::initialize_dynamic_source_script_interface(script_interface * pinterfaceMain, script_interface * pinterfaceParent, httpd_socket * pdssocket, script_manager * pmanager)
   //{

   //   auto estatus = initialize(pinterfaceMain);

   //   if (!estatus)
   //   {

   //      return estatus;

   //   }

   //   __refer(m_pinstanceMain2, pinterfaceMain);
   //   __refer(m_pinstanceParent2, pinterfaceParent);
   //   __refer(m_pnetnodesocket2, pdssocket);
   //   __refer(m_pmanager2, pmanager);

   //   estatus = on_initialize();
   //
   //   if(!estatus)
   //   {
   //
   //      return estatus;
   //
   //   }
   //
   //   return estatus;

   //}


   void script_interface::set_session_payload(const ::id & id, const ::payload &)
   {

   }


   ::payload script_interface::get_session_payload(const ::id & id)
   {

      return ::payload(::e_type_new);

   }

   ::id script_interface::session_id(const ::id & id)
   {

      return "";

   }


   void script_interface::current_url(string& strUrl)
   {

      strUrl = inattr(__id(http_protocol)) + "://" + inattr(__id(http_host)) + inattr(__id(request_uri));

   }

   void script_interface::print_r(::payload payload)
   {

      print(payload.string());

   }


      bool script_interface::rerun()
   {

      return false;

   }

   ::payload script_interface::call_run()
   {

      bool bRerun = rerun();

      bool bOk = false;

      try
      {

         bOk = run();

      }
      catch (const ::dynamic_source::exit_exception & e)
      {

         destroy();

         throw e;

      }
      catch (...)
      {

         // stop point_i32
         bOk = false;

      }

      ::payload payload = m_varRet;

      if (bRerun)
      {

         run();

      }

      if (!bOk)
      {

         return e_type_empty;

      }

      return payload;

   }

#if 0



   void script_interface::dprint(const ::string &)
   {


   }


   void script_interface::dprint_r(::payload payload)
   {


   }


      property_set& script_interface::inattra()
      {

         throw ::interface_only_exception();

         return *(property_set *)nullptr;

      }


      httpd_socket* script_interface::netnodesocket()
      {

         return m_pmain->m_psocket2;

      }


      script_manager* script_interface::manager()
      {

         return m_pmain->m_pmanager2;

      }


      property_set& script_interface::geta()
      {

         throw ::interface_only_exception();

         return *(property_set *)nullptr;

      }



      property_set& script_interface::posta()
      {

         throw ::interface_only_exception();

         return *(property_set *)nullptr;

      }



      http::cookies& script_interface::cookies()
      {

         throw ::interface_only_exception();

         return *(http::cookies *)nullptr;

      }


      property_set& script_interface::requesta()
      {

         throw ::interface_only_exception();

         return *(property_set *)nullptr;

      }


      property& script_interface::inheader(id id)
      {

         throw ::interface_only_exception();

         return *(property *)nullptr;

      }


      property& script_interface::outheader(id id)
      {

         throw ::interface_only_exception();

         return *(property *)nullptr;

      }


      property& script_interface::inattr(id id)
      {

         throw ::interface_only_exception();

         return *(property *)nullptr;

      }


      property& script_interface::outattr(id id)
      {

         throw ::interface_only_exception();

         return *(property *)nullptr;

      }


      string& script_interface::gstr(id id)
      {

         throw ::interface_only_exception();

         return *(string *)nullptr;

      }


      property& script_interface::gprop(id id)
      {

         throw ::interface_only_exception();

         return *(property *)nullptr;

      }


      property& script_interface::get(id idKey)
      {

         throw ::interface_only_exception();

         return *(property *)nullptr;

      }


      property& script_interface::post(id idKey)
      {

         throw ::interface_only_exception();

         return *(property *)nullptr;

      }


      http::cookie& script_interface::get_cookie(id idKey)
      {

         throw ::interface_only_exception();

         return *(http::cookie *)nullptr;

      }


      http::cookie& script_interface::set_cookie(id idKey)
      {

         throw ::interface_only_exception();

         return *(http::cookie *)nullptr;

      }



      void script_interface::uri_set_var(string& strUrl, const ::string & pszUrl, const ::string & pszKey, ::payload payload)
      {


      }


      void script_interface::uri_set_param(string& strUrl, const ::string & pszUrl, const ::string & pszKey, const string& strParam)
      {


      }


      string script_interface::query_get_param(const ::string & pszUrl, const ::string & pszKey)
      {

         return "";

      }


      ::payload script_interface::query_get_var(const ::string & pszUrl, const ::string & pszKey)
      {

      return false;

      }


#endif

      void script_interface::dprint_recursive(const ::payload & payload)
      {

         if (m_pmain != nullptr && m_pmain->m_iDebug > 0)
         {

            print_r(payload);

         }

      }



} // namespace dynamic_source



