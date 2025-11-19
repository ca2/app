#include "framework.h"
#include "script.h"
#include "script_interface.h"
#include "script_instance.h"
#include "script_main.h"
#include "httpd_socket.h"
#include "exit_exception.h"
#include "acme/exception/interface_only.h"
#include "acme/filesystem/file/memory_file.h"
#include "acme/prototype/prototype/url.h"
#include "acme/platform/system.h"
#include "apex/networking/sockets/httpd/socket_thread.h"
#include "programming/heating_up_exception.h"
#include "_impl.h"


namespace dynamic_source
{


   //script_interface::script_interface()
   //{

   //   m_iDebug = 0;

   //}


   script_interface::~script_interface()
   {

   }


   const_char_pointer script_interface::debug_note() const
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

      //if (pinterface)
      //{

      //   if (!m_pmain)
      //   {

      //      //tracking_note_assign(m_pmain, pinterface->m_pmain.get() REFERENCING_DEBUGGING_COMMA_THIS_NOTE("scptiface:init:referer://"+ m_strNote));

      //   }

      //}

      //return estatus;

   }


   void script_interface::initialize_with_socket_thread(::httpd::socket_thread* psocketthread)
   {

      auto psocket = psocketthread->m_psocket;

      if (psocket)
      {

         ::pointer < ::dynamic_source::httpd_socket > phttpdsocket = psocket;

         if (phttpdsocket)
         {

            auto pscript = phttpdsocket->m_pscript;

            if (pscript)
            {

               m_pscriptmain1 = pscript->m_pscriptmain1;

               if (m_pscriptmain1)
               {

                  m_pscriptmain1->m_interfacea.add_unique(this);

               }

               m_phttpdsocket1 = psocket;

               m_pscriptmanager1 = m_pscriptmain1->m_pscriptmanager1;

               // ... a fair good guess for a parent instance
               m_pinstanceParent1 = m_pscriptmain1->m_pscriptinstanceLastlyInstantiated;

            }

         }

      }

   }


   void script_interface::init1()
   {

      if (!m_pscriptmain1)
      {

         ::pointer < ::httpd::socket_thread > pthread = ::get_task();

         if (pthread)
         {

            initialize_with_socket_thread(pthread);

         }

      }

   }


   void script_interface::on_initialize_particle()
   {

      ::html_file::on_initialize_particle();
      ::file_system_interface::on_initialize_particle();
      ::file_system_real_path_interface::on_initialize_particle();

   }


   void script_interface::destroy()
   {

      m_pscriptmain1 = nullptr;
      m_pinstanceParent1 = nullptr;
      m_pscript1 = nullptr;
      m_varRet.unset();

      ::html_file::destroy();

   }


   void script_interface::run()
   {

   }


   void script_interface::dinit()
   {

   }


   void script_interface::transfer_proper_data_to_data_object(::dynamic_source::data_object * pdataobject)
   {

      // todo :)

   }


   ::file::file* script_interface::output_file()
   {

      if (m_pscriptmain1)
      {

         return m_pscriptmain1->output_file();

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


   ::file_system_cache_item script_interface::netnode_file_path(const ::scoped_string& scopedstrName, ::file_system_interface * pfilesysteminterface)
   {

      return m_pscript1->netnode_file_path(scopedstrName, pfilesysteminterface);

   }


   ::file_system_real_path_interface* script_interface::get_file_system_real_path_interface()
   {

      return this;

   }


   ::file_system_cache_item & script_interface::netnode_include_file_system_cache_item(const ::scoped_string& scopedstrName, const ::unique_index& uniqueindex)
   {

      critical_section_lock criticalsectionlock(&m_pscript1->m_criticalsectionFileSystemCacheItem);
       
      auto& pfilesystemcacheitem = m_pscript1->m_mapFileSystemCacheItem[uniqueindex.index()];

      if (pfilesystemcacheitem.is_ok())
      {

         return pfilesystemcacheitem;

      }

      pfilesystemcacheitem = file_system_item(scopedstrName);

      if (pfilesystemcacheitem.is_ok())
      {

         return pfilesystemcacheitem;

      }

      // as this function has "include" semantic,
      // if name doesn't end with .ds file extension...
      if (!scopedstrName.case_insensitive_ends(".ds"))
      {

         // try with .ds file extension appended
         pfilesystemcacheitem = file_system_item(scopedstrName + ".ds");

         if (pfilesystemcacheitem.is_ok())
         {

            return pfilesystemcacheitem;

         }

      }

      return pfilesystemcacheitem;

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


   void script_interface::set_auth_email(const ::scoped_string & scopedstrEmail)
   {

      set_session_payload("auth_email", scopedstrEmail);

   }


   void script_interface::auth(const ::scoped_string & scopedstrAuth)
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


   ::property_set& script_interface::inattra()
   {

      throw ::interface_only();

      return *(::property_set*)nullptr;

   }


   httpd_socket* script_interface::netnodesocket()
   {

      return m_pmain->m_psocket2;

   }


   script_manager* script_interface::manager()
   {

      return m_pmain->m_pmanager2;

   }


   ::property_set& script_interface::geta()
   {

      throw ::interface_only();

      return *(::property_set*)nullptr;

   }



   ::property_set& script_interface::posta()
   {

      throw ::interface_only();

      return *(::property_set*)nullptr;

   }



   http::cookies& script_interface::cookies()
   {

      throw ::interface_only();

      return *(http::cookies*)nullptr;

   }


   ::property_set& script_interface::requesta()
   {

      throw ::interface_only();

      return *(::property_set*)nullptr;

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



   void script_interface::uri_set_var(string& strUrl, const ::scoped_string & scopedstrUrl, const ::scoped_string & scopedstrKey, ::payload payload)
   {


   }


   void script_interface::uri_set_param(string& strUrl, const ::scoped_string & scopedstrUrl, const ::scoped_string & scopedstrKey, const ::scoped_string & scopedstrParam)
   {


   }


   string script_interface::query_get_param(const ::scoped_string & scopedstrUrl, const ::scoped_string & scopedstrKey)
   {

      return "";

   }


   ::payload script_interface::query_get_var(const ::scoped_string & scopedstrUrl, const ::scoped_string & scopedstrKey)
   {

      return false;

   }


#endif

   void script_interface::dprint_recursive(const ::payload& payload)
   {

      if (m_pscriptmain1 != nullptr && m_pscriptmain1->m_iDebug > 0)
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


   ::property_set& script_interface::geta()
   {

      return netnodesocket()->request().form().get();

   }


   ::property_set& script_interface::posta()
   {

      return netnodesocket()->request().form().post();

   }


   http::cookies& script_interface::cookies()
   {

      return netnodesocket()->request().cookies();

   }


   ::property_set& script_interface::requesta()
   {

      return netnodesocket()->request().form().request();

   }


   ::property_set& script_interface::inattra()
   {

      auto psocket = netnodesocket();

      auto& set = psocket->inattrs();

      return set;

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


   void script_interface::uri_set_var(string& strUrl, const ::scoped_string & scopedstrUrl, const ::scoped_string & scopedstrKey, ::payload payload)
   {

      ::url::parts parts(scopedstrUrl);

      parts.arguments()[scopedstrKey] = payload;

      strUrl = parts.as_string();

   }


   void script_interface::uri_set_param(string& strUrl, const ::scoped_string & scopedstrUrl, const ::scoped_string & scopedstrKey, const ::scoped_string & scopedstrParam)
   {

      ::url::parts parts(scopedstrUrl);

      parts.arguments()[scopedstrKey] = scopedstrParam;

      strUrl = parts.as_string();

   }


   string script_interface::query_get_param(const ::scoped_string & scopedstrUrl, const ::scoped_string & scopedstrKey)
   {

      ::url::parts parts(scopedstrUrl);

      auto str = parts.arguments()[scopedstrKey].as_string();

      return str;

   }


   ::payload script_interface::query_get_var(const ::scoped_string & scopedstrUrl, const ::scoped_string & scopedstrKey)
   {

      ::url::parts parts(scopedstrUrl);

      auto payload = parts.arguments()[scopedstrKey];

      return payload;

   }


   void script_interface::dprint(const ::scoped_string & scopedstr)
   {

      if (is_debug())
      {

         print(scopedstr);

      }

   }



   property& script_interface::gprop(const ::atom& atom)
   {

      auto& set = m_pscriptmain1->property_set();

      return set.property(atom);

   }


   void script_interface::folder_enumerate(::file::listing& listing, int iId, const ::file::path& pathFolder, const ::function < void(::file::listing& listing) >& procedureListing)
   {

      m_pscript1->folder_enumerate(listing, iId, pathFolder, procedureListing);

   }



   //httpd_socket* script_interface::netnodesocket()
   //{

   //   return m_pscriptmain1->m_psocket2;

   //}


   //script_manager* script_interface::manager()
   //{

   //   return m_pmanager2;

   //}


} // namespace dynamic_source



