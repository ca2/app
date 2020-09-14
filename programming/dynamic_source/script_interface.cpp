#include "framework.h"
#include "_.h"


namespace dynamic_source
{


   script_interface::script_interface()
   {

      m_posdataNetnodeScriptImpl = nullptr;

      m_posdataNetnodeScriptInterface = nullptr;

      m_iDebug             = 0;

   }


   script_interface::~script_interface()
   {

   }


   const char* script_interface::debug_note() const
   {

      return m_strNote;

   }


   ::estatus script_interface::initialize(::layered * pobjectContext)
   {

      auto estatus = ::html::file::initialize(pobjectContext);

      if (!estatus)
      {

         return estatus;

      }

      __pointer(script_interface) pinterface = pobjectContext;

      if (pinterface)
      {

         if (!m_pmain)
         {

            __note_assign(m_pmain, pinterface->m_pmain.get(), "scptiface:init:referer://"+ m_strNote);

         }

      }

      return estatus;

   }


   ::estatus script_interface::init1()
   {

      ::estatus estatus = ::success_none;

      return estatus;

   }


   void script_interface::finalize()
   {

      ::html::file::finalize();

      m_pmain.release(OBJ_REF_DBG_THIS);
      m_pinstanceParent2.release(OBJ_REF_DBG_THIS);
      m_pscript2.release(OBJ_REF_DBG_THIS);

   }


   ::estatus     script_interface::run()
   {

      return ::success;

   }


   void script_interface::dinit()
   {

   }


   //void script_interface::dprint(const char *)
   //{

   //}


   property & script_interface::get(const char * pszKey)
   {
      return netnodesocket()->m_request.form().get()[pszKey];
   }




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

         __throw(interface_only_exception());

      }

   }


   ::estatus script_interface::on_initialize()
   {

      return ::success;

   }


   //::estatus script_interface::initialize_dynamic_source_script_interface(script_interface * pinterfaceMain, script_interface * pinterfaceParent, httpd_socket * pdssocket, script_manager * pmanager)
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


   void script_interface::set_session_value(id, var)
   {

   }


   var script_interface::get_session_value(id)
   {

      return var(::type_new);

   }

   string script_interface::session_id(const char *)
   {

      return "";

   }
   void script_interface::current_url(string& strUrl)
   {

      strUrl = inattr(__id(http_protocol)) + "://" + inattr(__id(http_host)) + inattr(__id(request_uri));

   }

   void script_interface::print_r(var var)
   {

      print(var.to_r_string());

   }


      bool script_interface::rerun()
   {

      return false;

   }

   var script_interface::call_run()
   {

      bool bRerun = rerun();

      bool bOk = false;

      try
      {

         bOk = run();

      }
      catch (const ::dynamic_source::exit_exception & e)
      {

         finalize();

         throw e;

      }
      catch (...)
      {

         // stop point
         bOk = false;

      }

      var var = m_varRet;

      if (bRerun)
      {

         run();

      }

      if (!bOk)
      {

         return type_empty;

      }

      return var;

   }

#if 0



   void script_interface::dprint(const char *)
   {


   }


   void script_interface::dprint_r(var var)
   {


   }


      property_set& script_interface::inattra()
      {

         __throw(interface_only_exception);

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

         __throw(interface_only_exception);

         return *(property_set *)nullptr;

      }



      property_set& script_interface::posta()
      {

         __throw(interface_only_exception);

         return *(property_set *)nullptr;

      }



      http::cookies& script_interface::cookies()
      {

         __throw(interface_only_exception);

         return *(http::cookies *)nullptr;

      }


      property_set& script_interface::requesta()
      {

         __throw(interface_only_exception);

         return *(property_set *)nullptr;

      }


      property& script_interface::inheader(id id)
      {

         __throw(interface_only_exception);

         return *(property *)nullptr;

      }


      property& script_interface::outheader(id id)
      {

         __throw(interface_only_exception);

         return *(property *)nullptr;

      }


      property& script_interface::inattr(id id)
      {

         __throw(interface_only_exception);

         return *(property *)nullptr;

      }


      property& script_interface::outattr(id id)
      {

         __throw(interface_only_exception);

         return *(property *)nullptr;

      }


      string& script_interface::gstr(id id)
      {

         __throw(interface_only_exception);

         return *(string *)nullptr;

      }


      property& script_interface::gprop(id id)
      {

         __throw(interface_only_exception);

         return *(property *)nullptr;

      }


      property& script_interface::get(id idKey)
      {

         __throw(interface_only_exception);

         return *(property *)nullptr;

      }


      property& script_interface::post(id idKey)
      {

         __throw(interface_only_exception);

         return *(property *)nullptr;

      }


      http::cookie& script_interface::get_cookie(id idKey)
      {

         __throw(interface_only_exception);

         return *(http::cookie *)nullptr;

      }


      http::cookie& script_interface::set_cookie(id idKey)
      {

         __throw(interface_only_exception);

         return *(http::cookie *)nullptr;

      }



      void script_interface::uri_set_var(string& strUrl, const char* pszUrl, const char* pszKey, var var)
      {


      }


      void script_interface::uri_set_param(string& strUrl, const char* pszUrl, const char* pszKey, const string& strParam)
      {


      }


      string script_interface::query_get_param(const char* pszUrl, const char* pszKey)
      {

         return "";

      }


      var script_interface::query_get_var(const char* pszUrl, const char* pszKey)
      {

      return false;

      }


#endif


} // namespace dynamic_source



