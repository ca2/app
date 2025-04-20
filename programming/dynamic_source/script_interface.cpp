#include "framework.h"
#include "script_interface.h"
#include "script_main.h"
#include "httpd_socket.h"
#include "exit_exception.h"
#include "acme/exception/interface_only.h"
#include "acme/filesystem/file/memory_file.h"
#include "acme/prototype/prototype/url.h"
#include "acme/platform/system.h"
#include "apex/networking/sockets/httpd/socket_thread.h"
#include "programming/heating_up_exception.h"

namespace dynamic_source
{


   script_interface::script_interface()
   {

      m_pnetnodescriptimpl = nullptr;

      m_pnetnodescriptinterface = nullptr;

      m_iDebug = 0;

   }


   script_interface::~script_interface()
   {

   }


   const char* script_interface::debug_note() const
   {

      return m_strNote;

   }


   void script_interface::initialize(::particle* pparticle)
   {

      //auto estatus = 

      ::html_file::initialize(pparticle);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      auto pinterface = dynamic_cast <script_interface*>(pparticle);

      if (pinterface)
      {

         if (!m_pmain)
         {

            //tracking_note_assign(m_pmain, pinterface->m_pmain.get() REFERENCING_DEBUGGING_COMMA_THIS_NOTE("scptiface:init:referer://"+ m_strNote));

         }

      }

      //return estatus;

   }


   void script_interface::init1()
      //void script_interface::init1()
   {

      if (!m_pmain)
      {

         ::pointer < ::httpd::socket_thread > pthread = ::get_task();

         if (pthread)
         {

            auto psocket = pthread->m_psocket;

            if (psocket)
            {

               ::pointer < ::dynamic_source::httpd_socket > phttpdsocket = psocket;

               if (phttpdsocket)
               {

                  auto pscript = phttpdsocket->m_pscript;

                  if (pscript)
                  {

                     m_pmain = pscript->m_pmain;

                     if (m_pmain)
                     {

                        m_pmain->m_interfacea.add_unique(this);

                     }

                  }

               }

            }

         }

      }

      //m_pmain = ::dynamic_source::script_interface::m_pmain;
      //m_pinstanceParent2 = ::dynamic_source::script_interface::m_pinstanceParent2;

      // return estatus;

   }


   //void script_interface::destroy()
   //{

   //   auto estatus = ::html_file::destroy();

   //   m_pmain.release();
   //   m_pinstanceParent2.release();
   //   m_pscript2.release();

   //   return estatus;

   //}


   void script_interface::destroy()
   {

      m_pmain.release();
      m_pinstanceParent2.release();
      m_pscript2.release();

      m_varRet.unset();

      ::html_file::destroy();

   }


   //void script_interface::destroy()
   //{

   //   m_pmain.release();
   //   m_pinstanceParent2.release();
   //   m_pscript2.release();

   //   ::html_file::destroy();

   //}


   void     script_interface::run()
   {

      //return ::success;

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


   ::file::file* script_interface::output_file()
   {

      if (m_pmain)
      {

         return m_pmain->output_file();

      }
      else if (netnodesocket())
      {

         return netnodesocket()->response().file();

      }
      else
      {

         throw ::interface_only();

      }

   }


   void script_interface::on_initialize()
   {

      //return ::success;

   }


   //void script_interface::initialize_dynamic_source_script_interface(script_interface * pinterfaceMain, script_interface * pinterfaceParent, httpd_socket * pdssocket, script_manager * pmanager)
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


   void script_interface::set_session_payload(const ::atom& atom, const ::payload&)
   {

   }


   ::payload script_interface::get_session_payload(const ::atom& atom)
   {

      return ::payload(::e_type_new);

   }

   
   ::string script_interface::session_id(bool bForceCreateNew)
   {

      return "";

   }


   void script_interface::set_session_id(const ::scoped_string& scopedstrSessionId)
   {


   }


   string script_interface::get_auth_email()
   {

      return get_session_payload("auth_email");

   }


   void script_interface::set_auth_email(const string& strEmail)
   {

      set_session_payload("auth_email", strEmail);

   }


   void script_interface::auth(const string& strAuth)
   {

      exit(401);

   }

   void script_interface::current_url(string& strUrl)
   {

      strUrl = inattr("http_protocol") + "://" + inattr("http_host") + inattr("request_uri");

   }


   void script_interface::print_r(::payload payload)
   {

      print(payload.as_string());

   }


   bool script_interface::rerun()
   {

      return false;

   }


   ::payload script_interface::run_script()
   {

      bool bRerun = rerun();

      bool bOk = true;

      try
      {

         run();

      }
      catch (const ::heating_up_exception& e)
      {

         destroy();

         throw e;

      }
      catch (const ::dynamic_source::exit_exception& e)
      {

         destroy();

         throw e;

      }
      catch (...)
      {

         // stop int_point
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



   void script_interface::dprint(const ::string&)
   {


   }


   void script_interface::dprint_r(::payload payload)
   {


   }


   property_set& script_interface::inattra()
   {

      throw ::interface_only();

      return *(property_set*)nullptr;

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

      throw ::interface_only();

      return *(property_set*)nullptr;

   }



   property_set& script_interface::posta()
   {

      throw ::interface_only();

      return *(property_set*)nullptr;

   }



   http::cookies& script_interface::cookies()
   {

      throw ::interface_only();

      return *(http::cookies*)nullptr;

   }


   property_set& script_interface::requesta()
   {

      throw ::interface_only();

      return *(property_set*)nullptr;

   }


   property& script_interface::inheader(atom atom)
   {

      throw ::interface_only();

      return *(property*)nullptr;

   }


   property& script_interface::outheader(atom atom)
   {

      throw ::interface_only();

      return *(property*)nullptr;

   }


   property& script_interface::inattr(atom atom)
   {

      throw ::interface_only();

      return *(property*)nullptr;

   }


   property& script_interface::outattr(atom atom)
   {

      throw ::interface_only();

      return *(property*)nullptr;

   }


   string& script_interface::gstr(atom atom)
   {

      throw ::interface_only();

      return *(string*)nullptr;

   }


   property& script_interface::gprop(atom atom)
   {

      throw ::interface_only();

      return *(property*)nullptr;

   }


   property& script_interface::get(atom idKey)
   {

      throw ::interface_only();

      return *(property*)nullptr;

   }


   property& script_interface::post(atom idKey)
   {

      throw ::interface_only();

      return *(property*)nullptr;

   }


   http::cookie& script_interface::get_cookie(atom idKey)
   {

      throw ::interface_only();

      return *(http::cookie*)nullptr;

   }


   http::cookie& script_interface::set - cookie(atom idKey)
   {

      throw ::interface_only();

      return *(http::cookie*)nullptr;

   }



   void script_interface::uri_set_var(string& strUrl, const ::string& pszUrl, const ::string& pszKey, ::payload payload)
   {


   }


   void script_interface::uri_set_param(string& strUrl, const ::string& pszUrl, const ::string& pszKey, const string& strParam)
   {


   }


   string script_interface::query_get_param(const ::string& pszUrl, const ::string& pszKey)
   {

      return "";

   }


   ::payload script_interface::query_get_var(const ::string& pszUrl, const ::string& pszKey)
   {

      return false;

   }


#endif

   void script_interface::dprint_recursive(const ::payload& payload)
   {

      if (m_pmain != nullptr && m_pmain->m_iDebug > 0)
      {

         print_r(payload);

      }

   }

   property& script_interface::get(const ::atom& atom)
   {

      return netnodesocket()->request().form().get()[atom];

   }


   property& script_interface::post(const ::atom& atom)
   {

      return netnodesocket()->request().form().post()[atom];

   }


   http::cookie& script_interface::get_cookie(const ::scoped_string& scopedstr)
   {

      return netnodesocket()->request().cookies().cookie(scopedstr);

   }


   http::cookie& script_interface::set_cookie(const ::scoped_string& scopedstr)
   {

      return netnodesocket()->response().cookies().cookie(scopedstr);

   }


   property& script_interface::request(const ::atom& atom)
   {

      return netnodesocket()->request().form().request()[atom];

   }


   property_set& script_interface::geta()
   {

      return netnodesocket()->request().form().get();

   }


   property_set& script_interface::posta()
   {

      return netnodesocket()->request().form().post();

   }


   http::cookies& script_interface::cookies()
   {

      return netnodesocket()->request().cookies();

   }


   property_set& script_interface::requesta()
   {

      return netnodesocket()->request().form().request();

   }


   property_set& script_interface::inattra()
   {

      return netnodesocket()->inattrs();

   }


   property& script_interface::inheader(const ::atom& atom)
   {

      return netnodesocket()->inheader(atom);

   }


   property& script_interface::outheader(const ::atom& atom)
   {

      return netnodesocket()->outheader(atom);

   }


   property& script_interface::inattr(const ::atom& atom)
   {

      return netnodesocket()->inattr(atom);

   }


   property& script_interface::outattr(const ::atom& atom)
   {

      return netnodesocket()->outattr(atom);

   }




   string& script_interface::gstr(const ::atom& atom)
   {

      return gprop(atom).string_reference();

   }


   void script_interface::uri_set_var(string& strUrl, const ::string& pszUrl, const ::string& pszKey, ::payload payload)
   {

      ::url::parts parts(pszUrl);

      parts.arguments()[pszKey] = payload;

      strUrl = parts.as_string();

   }


   void script_interface::uri_set_param(string& strUrl, const ::string& pszUrl, const ::string& pszKey, const string& strParam)
   {

      ::url::parts parts(pszUrl);

      parts.arguments()[pszKey] = strParam;

      strUrl = parts.as_string();

   }


   string script_interface::query_get_param(const ::string& pszUrl, const ::string& pszKey)
   {

      ::url::parts parts(pszUrl);

      auto str = parts.arguments()[pszKey].as_string();

      return str;

   }


   ::payload script_interface::query_get_var(const ::string& pszUrl, const ::string& pszKey)
   {

      ::url::parts parts(pszUrl);

      auto payload = parts.arguments()[pszKey];

      return payload;

   }


   void script_interface::dprint(const ::string& psz)
   {

      if (m_pmain && m_pmain->m_iDebug > 0)
      {

         print(psz);

      }

   }



   property& script_interface::gprop(const ::atom& atom)
   {

      auto& set = m_pmain->property_set();

      return set.property(atom);

   }


   httpd_socket* script_interface::netnodesocket()
   {


      return m_pmain->m_psocket2;

   }


   script_manager* script_interface::manager()
   {

      return m_pmain->m_pmanager2;

   }



} // namespace dynamic_source



