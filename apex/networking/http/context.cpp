#include "framework.h"
#include "context.h"
#include "signal.h"
#include "get_socket.h"
////#include "acme/exception/exception.h"
#include "acme/filesystem/file/memory_file.h"
#include "acme/primitive/primitive/url.h"
#include "acme/primitive/primitive/url_domain.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/node.h"
#include "acme/primitive/string/str.h"
#include "apex/constant/idpool.h"
#include "apex/networking/networking.h"
#include "apex/networking/http/message.h"
#include "apex/networking/sockets/http/tunnel.h"
#include "apex/networking/sockets/http/session.h"
#include "apex/networking/sockets/basic/socket_handler.h"
#include "apex/filesystem/filesystem/dir_context.h"
#include "apex/filesystem/filesystem/file_context.h"
#include "apex/platform/application.h"
#include "apex/platform/context.h"
#include "apex/platform/system.h"
#include "apex/progress/listener.h"
#include <time.h>


#include "acme/primitive/time/_text_stream.h"



#define DEBUG_LEVEL_SICK 9
#define DEBUG_LEVEL_NORMAL 4
#define HTTP_DEBUG_LEVEL DEBUG_LEVEL_NORMAL


#define LOG_HTTP_PREFIX "http_get_" << iHttpGetSerial << "> "


namespace http
{


   context::context()
   {

      m_pmutexPac = nullptr;
      m_pmutexProxy = nullptr;
      m_pmutexDownload = nullptr;

   }


   context::~context()
   {

   }


   void context::http_application_destruct()
   {

      message_receiver_destruct();

   }


   property_set & context::process_set(property_set & set, const ::scoped_string & scopedstrUrl)
   {

      set["app"] = get_app();

      auto psystem = acmesystem();

      auto purl = psystem->url();

      string strServer = purl->get_root(scopedstrUrl);

      if (strServer == "server.ca2.software")
      {

         set["raw_http"] = true;

      }
      else if (!strServer.case_insensitive_ends("ca2.software") && strServer != "ca2.software")
      {

         set["raw_http"] = true;

      }

      return set;

   }


   bool context::get(::pointer<::sockets::http_client_socket>& psession, const ::scoped_string & scopedstrUrl, property_set & set, const             ::function < void(double, filesize, filesize) >
 & functionProgress)
   {

      return http_get(psession, scopedstrUrl, process_set(set, scopedstrUrl), functionProgress);

   }


   void context::get(memory_base * pmemory, const ::scoped_string & scopedstrUrl, property_set & set)
   {

      set["get_memory"] = pmemory;

      //auto estatus = _get(scopedstrUrl, process_set(set, scopedstrUrl));

      _get(scopedstrUrl, process_set(set, scopedstrUrl));

      set.erase_by_name("get_memory");

      //return estatus;

   }


   string context::api_get(const ::scoped_string & scopedstrUrl, property_set & set)
   {

      ::file::path url("https://api.ca2.software/");

      url /= scopedstrUrl;

      return get(url, set);

   }


   string context::api_get(const ::scoped_string & scopedstrUrl)
   {

      property_set set;

      set["disable_common_name_cert_check"] = true;

      return api_get(scopedstrUrl, set);

   }


   void context::_get(const ::scoped_string & scopedstrUrl, property_set & set, const ::function < void(double, filesize, filesize) > & functionProgress)
   {

      auto pmessage = __create_new < ::http::message >();

      pmessage->m_ppropertyset = &set;

      pmessage->m_strUrl = scopedstrUrl;
      
      pmessage->m_functionProgress = functionProgress;

      get(pmessage);

      //return set["get_status"].estatus();

   }


   ::payload context::get(const ::scoped_string & scopedstrUrl, property_set & set, const ::function < void(double, filesize, filesize) > & functionProgress)
   {

      set["get_response"] = ""; // create get_response field

      //auto estatus = _get(scopedstrUrl, set);

      _get(scopedstrUrl, set, functionProgress);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      return set["get_response"];

   }


   void context::get(string & str, const ::scoped_string & scopedstrUrl, property_set & set)
   {

      set["get_response"] = "";

      set["bool_result"] = get(scopedstrUrl, process_set(set, scopedstrUrl));

      str = set["get_response"];

      //return set["get_status"].estatus();

   }


   ::file::enum_type context::get_type(const ::scoped_string & scopedstrUrl, ::payload * pvarQuery, property_set & set)
   {

      string strUrl(scopedstrUrl);

      string strFile(strUrl);

      strFile.replace_with("_", ":");

      strFile.replace_with("/", "//");

      strFile.replace_with("%19", "?");

      strFile = dir()->cache() / strFile + ".meta_information";

      string strCache;

      if (!set["nocache"].get_bool())
      {

         file()->as_string(strFile);

         if (strCache.has_char())
         {

            if (strCache == "file")
            {

               return ::file::e_type_file;

            }
            else if (strCache == "folder")
            {

               return ::file::e_type_folder;

            }
            else if (strCache == "matter")
            {

               return ::file::e_type_element;

            }
            else if (strCache == "itdoesntexist")
            {

               return ::file::e_type_doesnt_exist;

            }

         }

      }

      auto psystem = acmesystem();

      auto purl = psystem->url();

      if (::str::find_wwci("ca2", purl->get_server(scopedstrUrl)) < 0 && purl->get_object(scopedstrUrl).case_insensitive_find_index("/matter/") < 0)
      {

         set["raw_http"] = true;

      }

      auto etype = get_type(strUrl, process_set(set, scopedstrUrl));

      if (etype == ::file::e_type_folder)
      {

         strCache = "folder";

      }
      else if (etype == ::file::e_type_file)
      {

         strCache = "file";

      }
      else if (etype == ::file::e_type_element)
      {

         strCache = "matter";

      }
      else
      {

         strCache = "itdoesntexist";

      }

      file()->put_text(strFile, strCache);

      return etype;

   }


   //::payload context::length(const ::scoped_string & scopedstrUrl, property_set & set)
   //{

   //   return length(scopedstrUrl, nullptr, set);

   //}


   ::payload context::length(const ::scoped_string & scopedstrUrl, ::payload * pvarQuery, property_set & set)
   {

      string strUrl(scopedstrUrl);

      string strFile(strUrl);

      strFile.replace_with("_", ":");
      
      strFile.replace_with("/", "//");
      
      strFile.replace_with("%19", "?");

      strFile = dir()->cache() / strFile + ".length_question";

      bool bNoCache = set["nocache"].get_bool();

      string strCache;

      if (!bNoCache)
      {

         strCache = file()->as_string(strFile);

         if (strCache.has_char())
         {

            if (strCache == "-1")
            {

               return -1;

            }
            else if (strCache == "no")
            {

               return ::str::to_i64(strCache);

            }

         }

      }

      ::payload len = length(strUrl, process_set(set, scopedstrUrl));

      if (len.is_empty())
      {

         strCache = "-1";

      }
      else
      {

         strCache = ::as_string(len.as_i64());

      }

      file()->put_text(strFile, strCache);

      return len;

   }


   //bool context::request(const ::scoped_string & scopedstrRequest, const ::scoped_string & scopedstrUrl, property_set & set)
   //{

   //   return request(pszRequest, scopedstrUrl, process_set(set, scopedstrUrl));

   //}


   //bool context::download(::pointer<::sockets::http_session>& psession, const ::scoped_string & scopedstrUrl, ::payload payloadFile, property_set & set)
   //{

   //   return download(psession, scopedstrUrl, payloadFile, process_set(set, scopedstrUrl));

   //}


 /*  bool context::download(const ::scoped_string & scopedstrUrl, ::payload payloadFile, property_set & set)
   {
      return download(scopedstrUrl, payloadFile, process_set(set, scopedstrUrl));
   }*/

   bool context::put(const ::scoped_string & scopedstrUrl, memory_base * pmemory, property_set & set)
   {

      return put(scopedstrUrl, *pmemory, process_set(set, scopedstrUrl));
   }

   //bool context::put(const ::scoped_string & scopedstrUrl, file_pointer  pfile, property_set & set)
   //{
   //   return put(scopedstrUrl, pfile, process_set(set, scopedstrUrl));
   //}



   string context::locale_schema_url(const ::scoped_string & scopedstrUrl, const ::scoped_string & scopedstrLocale, const ::scoped_string & scopedstrSchema)
   {

      string str;

      //      i32 iAttempt = 0;

      string strUrl(scopedstrUrl);

      if (strUrl.contains("?"))
      {

         strUrl += "&";

      }
      else
      {

         strUrl += "?";

      }

      strUrl += "lang=" + string(scopedstrLocale) + "&styl=" + string(scopedstrSchema);

      return strUrl;

   }


   string context::get_locale_schema(const ::scoped_string & scopedstrUrl, const ::scoped_string & scopedstrLocale, const ::scoped_string & scopedstrSchema)
   {

      //output_error_message("What?!", nullptr, e_message_box_ok);

      output_debug_string("What?!");

      string strUrl = locale_schema_url(scopedstrUrl, scopedstrLocale, scopedstrSchema);

      string str;

      //      int iAttempt = 0;
      //
      //      property_set set;
      //
      //      ::pointer<::sockets::http_session>psession;
      //
      //      string strFontopusServer;
      //
      //      if(atoi(purl->get_param(scopedstrUrl, "authnone")) == 1
      //            || purl->get_param(scopedstrUrl,"sessid").case_insensitive_order("noauth") == 0)
      //      {
      //
      //         strFontopusServer = scopedstrUrl;
      //
      //      }
      //      else
      //      {
      //
      //         strFontopusServer = psession->account()->authenticator()->get_account_server(scopedstrUrl);
      //
      //      }
      //
      //      while(::get_task() == nullptr || task_get_run())
      //      {
      //
      //         {
      //
      //            set["get_response"] = "";
      //
      //            str = get(strUrl, set);
      //
      //            if(str.has_char())
      //               return str;
      //
      //         }
      //
      //         iAttempt++;
      //
      //         if(iAttempt > 11)
      //            return "";
      //
      //         sleep(iAttempt * 840);
      //
      //      }

      return str;

   }


   void context::on_initialize_particle()
   {

      //auto estatus = ::object::on_initialize_particle();

      ::object::on_initialize_particle();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      m_setHttp["max_http_post"] = 5 * 1024 * 1024; // 5MB;

      payload("dw") = ::time::now();
      
      m_pmutexDownload = acmenode()->create_mutex();

      //return estatus;

   }


   void context::http_system_destruct()
   {

      message_receiver_destruct();

   }


   i32 context::auto_config_proxy_count()
   {

      return 4;

   }


   void context::auto_config_proxy(i32 i)
   {

      return;
      //      if(i == 0)
      //      {
      //      }
      //      else if(i == 1)
      //      {
      //         // telmico: no proxy
      //         string str = file()->as_string(dir()->appdata() / "machine/proxy.xml");
      //         if(str.has_char() && str.find("<") >= 0 && str.find(">") > 0)
      //         {
      //            file()->copy(dir()->appdata()/ "proxy_original.xml", dir()->install()/ "proxy.xml", false);
      //         }
      //         if(file()->exists(dir()->appdata()/ "proxy.xml"))
      //         {
      //            try
      //            {
      //               file()->del(dir()->appdata()/ "proxy.xml");
      //            }
      //            catch(...)
      //            {
      //            }
      //         }
      //      }
      //      else if(i == 2)
      //      {
      //         // telmico: original proxy configuration
      //         if(file()->exists(dir()->appdata()/ "proxy_original.xml"))
      //         {
      //            file()->copy(dir()->appdata()/ "proxy.xml", dir()->appdata()/"proxy_original.xml", false);
      //         }
      //      }
      //      else
      //      {
      //         // telmico: simple default proxy configuration : hostname=>proxy - try etc/hosts port=>80  - assume HTTP proxy
      //         string str = file()->as_string(dir()->appdata()/"proxy.xml");
      //         if(str.has_char() && str.find("<") >= 0 && str.find(">") > 0)
      //         {
      //            file()->copy(dir()->appdata()/"proxy_original.xml", dir()->appdata()/"proxy.xml", false);
      //         }
      //         file()->put_contents(dir()->appdata()/"proxy.xml", "proxy");
      //      }
   }


   void context::defer_auto_initialize_proxy_configuration()
   {

      string strHost = file()->as_string(dir()->appdata() / "database\\text\\last_good_known_account_com.txt");

      string_array straRequestingServer;

      straRequestingServer.add("ca2.software");

      if (!straRequestingServer.case_insensitive_contains(strHost))
      {

         strHost = "ca2.software";

      }

      straRequestingServer.erase(strHost);

      straRequestingServer.insert_at(0, strHost);

      bool bOk = false;

      if (bOk)
      {

         return;

      }

      auto_config_proxy(0);

   }

   //context::pac::pac(::particle * pparticle) :
   //   ::object(pparticle)
   //{

   //   throw ::exception(todo, "scripting");
   //   //m_pjs = memory_new tinyjs();

   //}


   context::pac::pac()
   {

      throw ::exception(todo, "scripting");
      //m_pjs = memory_new tinyjs();

   }


   context::pac::~pac()
   {

      //throw ::exception(todo("scripting"));


      //if (m_pjs == nullptr)
      //{

      //   delete m_pjs;

      //}

   }


   context::pac * context::get_pac(const ::scoped_string & scopedstrUrl)
   {

      single_lock synchronouslock(m_pmutexPac, true);

      auto ppair = m_mapPac.plookup(scopedstrUrl);

      if (!ppair || ppair->element2()->m_timeLastChecked.elapsed() > 120_s)
      {
         
         if (ppair)
         {
            
            //            delete ppair->element2();
            m_mapPac.erase_item(scopedstrUrl);
            
         }

         auto ppac = __create_new < class pac >();

         ppac->m_timeLastChecked= ::time::now();

         ppac->m_strUrl = scopedstrUrl;

         ::payload payloadFile;

         payloadFile["url"] = ppac->m_strUrl;
         payloadFile["disable_ca2_sessid"] = true;
         payloadFile["no_proxy_config"] = true;

         ppac->m_strAutoConfigScript = file()->as_string(payloadFile);


         m_mapPac.set_at(scopedstrUrl, ppac);

         if (ppac->m_strAutoConfigScript.is_empty())
         {
            return nullptr;
         }

         //throw ::exception(todo("scripting"));
         //registerFunctions(ppac->m_pjs);
         //registerJavascriptFunctions(ppac->m_pjs);
         //ppac->m_pjs->execute(ppac->m_strAutoConfigScript);

         ppair = m_mapPac.plookup(scopedstrUrl);

         if (!ppair)
         {
            
            return nullptr;
            
         }

      }

      if (ppair->element2()->m_strAutoConfigScript.is_empty())
      {

         return nullptr;

      }

      return ppair->element2();

   }


   //context::proxy::proxy(::particle * pparticle) :
   //   ::object(pparticle)
   //{

   //   m_bDirect = true;

   //}


   context::proxy::proxy()
   {

      m_bDirect = true;

   }


   ::http::context::proxy * context::get_proxy(const ::scoped_string & scopedstrUrl)
   {

      single_lock synchronouslock(m_pmutexProxy, true);

      auto ppair = m_mapProxy.plookup(scopedstrUrl);

      if (!ppair || ppair->element2()->m_timeLastChecked.elapsed() > 120_s)
      {
         
         if (ppair)
         {
            
            //            delete ppair->element2();
            m_mapPac.erase_item(scopedstrUrl);
            
         }

         auto pproxy = __create_new < class ::http::context::proxy >();

         pproxy->m_timeLastChecked= ::time::now();

         pproxy->m_strUrl = scopedstrUrl;

         config_proxy(scopedstrUrl, pproxy);

         m_mapProxy.set_at(scopedstrUrl, pproxy);

         return pproxy;

      }

      return ppair->element2();

   }


   bool context::try_pac_script(const ::scoped_string & scopedstrScriptUrl, const ::scoped_string & scopedstrUrl, proxy * pproxy)
   {

      single_lock synchronouslock(m_pmutexPac, true);

      string strProxyServer;

      string strUrl(scopedstrScriptUrl);

      if (string_begins(scopedstrUrl, strUrl))
      {
         pproxy->m_bDirect = true;
         return true;
      }

      class pac * ppac = get_pac(scopedstrUrl);

      if (ppac == nullptr)
         return false;

      string strHost;

      auto psystem = acmesystem();

      auto purl = psystem->url();

      strHost = purl->get_server(scopedstrUrl);

      i32 port = purl->get_port(scopedstrUrl);

      //::networking::address ad(strHost, port);

      //strHost = ad.get_display_number();

      string payload;
      //throw ::exception(todo("scripting"));
      //try
      //{
      //   payload = ppac->m_pjs->evaluate("FindProxyForURL('" + string(scopedstrUrl) + "', '" + strHost + "');");
      //}
      //catch (...)
      //{
      //   return false;
      //}

      if (payload.case_insensitive_order("DIRECT") == 0)
      {

         pproxy->m_bDirect = true;

      }
      else if (payload.case_insensitive_begins_eat("PROXY"))
      {
         payload.trim();
         string_array stra;
         stra.explode(":", payload);
         pproxy->m_bDirect = false;
         pproxy->m_strProxy = stra[0];
         pproxy->m_iPort = stra.get_size() > 1 ? ::atoi(stra[1]) : 80;
      }
      else
      {
         pproxy->m_bDirect = true;
      }

      return true;

   }


   void context::config_proxy(const ::scoped_string & scopedstrUrl, ::sockets::http_tunnel * psocket)
   {

#ifdef _UWP

      psocket->m_bDirect = true;

#else

      ::http::context::proxy * pproxy = get_proxy(scopedstrUrl);

      if (pproxy == nullptr)
         return;

      if (pproxy->m_bDirect)
      {
         psocket->m_bDirect = true;
      }
      else
      {
         psocket->m_bDirect = false;
         psocket->m_strProxy = pproxy->m_strProxy;
         psocket->m_iProxyPort = pproxy->m_iPort;
      }

#endif

   }


   void context::config_proxy(const ::scoped_string & scopedstrUrl, ::http::context::proxy * pproxy)
   {

      //throw ::exception(todo("xml"));

      //xml::document doc;

      //::file::path pathProxyXml = dir()->appdata() / "proxy.xml";

      //if (!file()->exists(pathProxyXml))
      //{

      //   pproxy->m_bDirect = true;

      //   return;

      //}

      //string str = file()->as_string(pathProxyXml);

      //if (str.has_char() && str.find("<") < 0 && str.find(">") < 0)
      //{

      //   string_array stra;

      //   stra.explode(":", str);

      //   if (stra.get_size() > 0 && stra[0].has_char())
      //   {

      //      pproxy->m_bDirect = false;

      //      pproxy->m_strProxy = stra[0];

      //      if (stra.get_size() >= 2)
      //      {

      //         pproxy->m_iPort = atoi(stra[1]);

      //      }
      //      else
      //      {

      //         pproxy->m_iPort = 80;

      //      }

      //      return;

      //   }

      //}

      //if (!doc.load(str))
      //{

      //   pproxy->m_bDirect = true;

      //   return;

      //}

      //bool bOk = true;

      //string strHost = purl->get_server(scopedstrUrl);

      //i32 iHostPort = purl->get_port(scopedstrUrl);

      //::networking::address ipHost(strHost, iHostPort);
      //for (i32 iNode = 0; iNode < doc.root()->get_children_count(); iNode++)
      //{
      //   ::pointer<::xml::node>pnode = doc.root()->child_at(iNode);
      //   if (pnode->get_name() == "proxy")
      //   {

      //      ::networking::address ipAddress(pnode->attribute("address").as_string(), 0);

      //      ::networking::address ipMask(pnode->attribute("mask").as_string(), 0);

      //      if (ipHost.is_in_same_net(ipAddress, ipMask))
      //      {

      //         if (pnode->attribute("server") == "DIRECT")
      //         {

      //            pproxy->m_bDirect = true;

      //            return;

      //         }
      //         else
      //         {

      //            pproxy->m_bDirect = false;

      //            pproxy->m_strProxy = pnode->attribute("server");

      //            pproxy->m_iPort = pnode->attribute("port");

      //            FORMATTED_TRACE("Select Proxy : address %s mask %s server %s port %d", pnode->attribute("address").as_string().c_str(),
      //               pnode->attribute("mask").as_string().c_str(), pproxy->m_strProxy.c_str(), pproxy->m_iPort);

      //            return;

      //         }

      //      }

      //   }

      //}

      //if (doc.attribute("server") == "DIRECT")
      //{

      //   pproxy->m_bDirect = true;

      //   return;

      //}
      //else
      //{

      //   pproxy->m_bDirect = false;
      //   pproxy->m_strProxy = doc.root()->attribute("server");
      //   pproxy->m_iPort = doc.root()->attribute("port");
      //   return;

      //}


      ////      if(!bOk)
      ////      {
      ////
      ////         //bool bAutoDetect = m_pcontext->m_papexcontext->os().connection_settings_get_auto_detect();
      ////
      ////         //if(bAutoDetect)
      ////         //{
      ////
      ////         //   TRACE("proxy auto_detect true");
      ////
      ////         //   string strUrl = m_pcontext->m_papexcontext->os().connection_settings_get_auto_config_url();
      ////
      ////         //   if(strUrl.has_char())
      ////         //   {
      ////
      ////         //      FORMATTED_TRACE("get_auto_config_url : %s",strUrl);
      ////
      ////         //      if(try_pac_script(strUrl,scopedstrUrl,pproxy))
      ////         //         return;
      ////
      ////         //   }
      ////
      ////         //}
      ////         //else
      ////         //{
      ////
      ////         //   TRACE("proxy auto_detect false");
      ////
      ////         //   string strUrl = m_pcontext->m_papexcontext->os().connection_settings_get_auto_config_url();
      ////
      ////         //   if(strUrl.has_char())
      ////         //   {
      ////
      ////         //      FORMATTED_TRACE("get_auto_config_url : %s",strUrl);
      ////
      ////         //      if(try_pac_script(strUrl,scopedstrUrl,pproxy))
      ////         //         return;
      ////
      ////         //   }
      ////
      ////         //   if(try_pac_script("http://wpad/wpad.dat",scopedstrUrl,pproxy))
      ////         //      return;
      ////
      ////         //}
      ////
      ////
      ////         pproxy->m_bDirect = true;
      ////
      ////      }

   }


   //void context::on_auth(property_set & set, ::apex::application *      papp, string & strUrl, string & strSessId, ::pointer<::account::user>& puser)
   //{

   //   if (::is_null(papp))
   //   {

   //      return;

   //   }

   //   if (set.is_true("raw_http"))
   //   {

   //      return;

   //   }

   //   if (!Sess(papp).account()->url_requires_auth(strUrl))
   //   {

   //      return;

   //   }

   //   string strWorkUrl;

   //   bool bInteractive = set.is_set_false("noninteractive");

   //   puser = App(papp).get_user(strUrl, true, bInteractive);

   //   if (puser.is_null())
   //   {

   //      return;

   //   }

   //   strSessId = puser->m_strSessId;

   //   if (strSessId.is_empty())
   //   {

   //      purl->string_set(strUrl, "authnone", 1);

   //      return;

   //   }

   //   //purl->string_set(strUrl, "sessid", strSessId);

   //}


   bool context::open(::pointer<::sockets::http_session>& psession, const ::string & strHost, const ::string & strProtocolParam, property_set & set, const string &strVersionParam)
   {

      auto tickTimeProfile1 = ::time::now();

      string strVersion(strVersionParam);

      string strServer = strHost;

      string strProtocol = strProtocolParam;

      ::pointer<::apex::application>papp = set["app"].cast < ::apex::application >();

      //i32 iPort;

      //if (strProtocol == "https")
      //{

      //   iPort = 443;

      //}
      //else
      //{

      //   iPort = 80;

      //}

      if (strVersion.is_empty())
      {

         strVersion = "HTTP/1.1";

      }

      string strUrl(strProtocol + "://" + strServer);

      // Format of script name example "context://server.com/the rain.mp3" => "context://server.com/the%20rain.mp3"
      {

         auto psystem = acmesystem();

         auto purl = psystem->url();

         string strScript = ::url::encode(::url::decode(purl->get_script(strUrl)));

         strScript.replace_with("%20", "+");

         strScript.replace_with("/", "%2F");

         strUrl = purl->set_script(strUrl, strScript);

      }

      property_set setQuery;

      auto psystem = acmesystem();

      auto purl = psystem->url();

      setQuery.parse_network_arguments(purl->get_query(strUrl));

      string strIp;

      string strSessId;

      psession = __new(::sockets::http_session(strProtocol, strHost));

      /*::pointer<::account::user>puser;

      on_auth(set, papp, strUrl, strSessId, puser);*/

      if (strProtocol == "https")
      {

         psession->EnableSSL();

      }

      auto tick1 = ::time::now();

      bool bConfigProxy = set.is_set_false("no_proxy_config");

      if (strIp.has_char())
      {

         psession->set_connect_host(strIp);

      }

      ERROR("just before open open http_session ::http::apex::context::open " << tick1.elapsed().integral_second());

      if (!psession->open(bConfigProxy))
      {

         INFORMATION("Not Opened/Connected Result Total time ::http::apex::context::get(\"" << strUrl.left(minimum(255, strUrl.length()))  << "\") " << tick1.elapsed().integral_second());

         return false;

      }

      INFORMATION("context::get open time " << tick1.elapsed().integral_second());

      return true;

   }


   bool context::request(::pointer<::sockets::http_session>& psession, const ::scoped_string & scopedstrRequest, property_set & set)
   {

//      INFORMATION("http context request : " << pszRequest);
//
//      ::time tick1;
//
//      ::time tick2;
//
//      bool bSeemsOk;
//
//      i32 iTry = 0;
//
//      i32 iTryCount;
//
//      if (set.has_property("try"))
//      {
//
//         set["try"].as(iTryCount);
//
//         if (iTryCount > 5)
//         {
//
//            iTryCount = 5;
//
//         }
//
//      }
//      else
//      {
//
//         iTryCount = 2;
//
//      }
//
//   retry:
//
//      iTry++;
//
//      bSeemsOk = true;
//
//      try
//      {
//
//         if (psession == nullptr)
//         {
//
//            bSeemsOk = false;
//
//         }
//         else if (!psession->is_valid())
//         {
//
//            //handler.erase(psession);
//
//            psession->SetCloseAndDelete();
//
//            bSeemsOk = false;
//
//         }
//
//      }
//      catch (...)
//      {
//
//         bSeemsOk = false;
//
//      }
//
//      auto psystem = acmesystem();
//
//      auto purl = psystem->url();
//
//      if (!bSeemsOk)
//      {
//
//         try
//         {
//
//            auto tickBeg = ::time::now();
//
//            if (!open(psession, purl->get_server(pszRequest), purl->get_protocol(pszRequest), set, set["http_protocol_version"]))
//            {
//
//               return false;
//
//            }
//
//            FORMATTED_INFORMATION("opening context::request time(%d) = ", tickBeg.elapsed().integral_second().m_i);
//
//         }
//         catch (...)
//         {
//
//            return false;
//
//         }
//
//      }
//
//      auto tickBegA = ::time::now();
//
//      try
//      {
//
//         auto tickTimeProfile1 = ::time::now();
//
//         auto papplication = psession->m_psockethandler->get_app()->m_papexapplication;
//
//         string strRequest = purl->get_object(pszRequest);
//
//         string strServer = purl->get_server(pszRequest);
//
//         string strUrl = psession->m_strProtocol + "://" + strServer + strRequest;
//
//         // Format of script name example "context://server.com/the rain.mp3" => "context://server.com/the%20rain.mp3"
//         {
//
//            string strScript = ::url::encode(::url::decode(purl->get_script(strUrl)));
//
//            strScript.replace_with("%20", "+");
//
//            strScript.replace_with("/", "%2F");
//
//            strUrl = purl->set_script(strUrl, strScript);
//
//         }
//
//         property_set setQuery;
//
//         setQuery.parse_network_arguments(purl->get_query(strUrl));
//
//         string strSessId;
//
//         //::pointer<::account::user>puser;
//
//         //on_auth(set, papp, strUrl, strSessId, puser);
//
//         strRequest = purl->get_object(strUrl);
//
//         psession->inheaders().clear();
//
//         psession->outheaders().clear();
//
//         psession->inattrs().clear();
//
//         psession->outattrs().clear();
//
//         psession->m_memoryfile.set_size(0);
//
//         psession->inheaders() = set["headers"].propset();
//
//         if (set.has_property("minimal_headers") && set["minimal_headers"].is_true())
//         {
//
//            psession->m_request.attrs()["minimal_headers"] = true;
//
//         }
//
//         if (set.has_property("file"))
//         {
//
//            psession->m_pfile = set["file"].cast < ::file::file >();
//
//         }
//
//         if (set.has_property("int_scalar_source_listener"))
//         {
//
//            psession->::int_scalar_source::m_plistener = set["int_scalar_source_listener"].cast < int_scalar_source::listener >();
//
//         }
//         else
//         {
//
//            psession->::int_scalar_source::m_plistener = nullptr;
//
//         }
//
//         if (set["cookies"].cast < ::http::cookies >() != nullptr && set["cookies"].cast < ::http::cookies >()->get_size() > 0)
//         {
//
//            psession->request().header("cookie") = set["cookies"].cast < ::http::cookies >()->get_cookie_header();
//
//         }
//
//         //if (set["user"].cast < ::account::user >() != nullptr && set["user"].cast < ::account::user >()->m_phttpcookies != nullptr && !(bool)set["disable_ca2_user_cookies"])
//         //{
//
//         //   psession->request().header("cookie") = set["user"].cast < ::account::user >()->m_phttpcookies->get_cookie_header();
//
//         //}
//
//         if (set.has_property("cookie") && set["cookie"].string().has_char())
//         {
//
//            psession->request().header("cookie") = set["cookie"];
//
//         }
//
//         psession->m_host = purl->get_server(pszRequest);
//
//         psession->m_strHost = purl->get_server(pszRequest);
//
//         psession->m_request.m_propertysetHeader["host"] = psession->m_host;
//
//         set["http_body_size_downloaded"] = &psession->m_body_size_downloaded;
//
//         psession->m_scalarsourceDownloadedRate.m_plistener = set["http_downloaded_rate_listener"].cast < ::double_scalar_source::listener >();
//
//         psession->m_scalarsourceDownloadedRate.m_atom = set["http_downloaded_rate_id"].atom();
//
//         psession->m_scalarsourceDownloaded.m_plistener = set["http_downloaded_listener"].cast < ::int_scalar_source::listener >();
//
//         psession->m_scalarsourceDownloaded.m_atom = set["http_downloaded_id"].atom();
//
//         bool bPost;
//
//         bool bPut;
//
//         if (set["put"].cast < ::file::file >() || set("http_method") == "PUT")
//         {
//
//            bPost = false;
//
//            bPut = true;
//
//            psession.cast < ::sockets::http_put_socket>()->m_file = set["put"].cast < ::file::file >();
//
//            psession->request("PUT", strRequest);
//
//         }
//         else if (set["post"].propset().has_element() || set("http_method") == "POST")
//         {
//
//            bPost = true;
//
//            bPut = false;
//
//            psession.cast < ::sockets::http_post_socket>()->m_fields = set["post"].propset();
//
//            if (set.has_property("multipart"))
//            {
//
//               psession.cast < ::sockets::http_post_socket>()->m_pmultipart = set["multipart"].cast < ::sockets::multipart >();
//
//            }
//
//            psession->request("POST", strRequest);
//
//         }
//         else
//         {
//
//            bPost = false;
//
//            bPut = false;
//
//            psession->request("GET", strRequest);
//
//         }
//
//         //psession->m_psockethandler->restart_socket(psession->get_socket_id());
//
//         i32 iIteration = 0;
//
//         //::apex::live_signal keeplive;
//
//         //if (papp != nullptr)
//         //{
//
//         //   keeplive.keep(papp);
//
//         //   keeplive.keep(&Sess(papp));
//
//         //   keeplive.keep(&Sys(papp));
//
//         //}
//
//         FORMATTED_INFORMATION("opening preparation context::request time(%d) = ", tickBegA.elapsed().integral_second().m_i);
//
//         tick1 = payload("dw").time();
//
//         tick2.Now();
//
//         INFORMATION("Higher Level Diagnosis : iNTERTIMe context::request " << iIteration << tick1.integral_second() << tick2.integral_second() << (tick2 - tick1).integral_second());
//
//         while ((psession->m_psockethandler->get_count() > 0 && !psession->m_bRequestComplete) && (::get_task() == nullptr || ::task_get_run()))
//            //while(psession->get_count() > 0 && !psession->m_bRequestComplete) // should only exit in case of process exit signal
//         {
//
//            tick1 = ::time::now();
//
//            psession->m_psockethandler->select(240, 0);
//
////            keeplive.keep-alive();
//
//            set["http_content_length"] = psession->m_content_length;
//
//            if (set.has_property("cancel"))
//            {
//
//               if (set["cancel"].get_bool())
//               {
//
//                  break;
//
//               }
//
//            }
//
//            double dRateDownloaded = 0.0;
//
//            i64 iContentLength = set["http_content_length"].as_i64();
//
//            i64 iBodySizeDownloaded = set["http_body_size_downloaded"].as_i64();
//
//            if (iContentLength > 0)
//            {
//
//               if (iBodySizeDownloaded > 0.0)
//               {
//
//                  dRateDownloaded = (double)iBodySizeDownloaded / (double)iContentLength;
//
//               }
//
//            }
//
//            set["http_rate_downloaded"] = dRateDownloaded;
//
//            psession->m_scalarsourceDownloadedRate.set_scalar(::scalar_none, dRateDownloaded);
//
//            psession->m_scalarsourceDownloaded.set_scalar(::scalar_none, iBodySizeDownloaded);
//
//            if (psession->m_estatus == error_connection_timed_out
//               || psession->m_estatus == error_on_connection_timeout)
//            {
//
//               break;
//
//            }
//
//            INFORMATION("context::request " << tick1.elapsed().integral_second());
//
//            iIteration++;
//
//         }
//
/////         keeplive.keep-alive();
//
//         (*this)["dw"].time().Now();
//
//         set["get_headers"] = psession->outheaders();
//
//         set["get_attrs"] = psession->outattrs();
//
//         string strCookie = psession->response().cookies().get_cookie_header();
//
//         set["cookie"] = strCookie;
//
//         i32 iStatusCode;
//
//         psession->outattr("http_status_code").as(iStatusCode);
//
//         if (set.has_property("cancel") && set["cancel"].get_bool())
//         {
//
//            psession->m_estatus = error_connection_cancelled;
//
//         }
//         else if (iStatusCode == 0)
//         {
//
////#if defined(BSD_STYLE_SOCKETS)
////
////            if (psession.is_set()
////               && psession->m_psslcontext != nullptr
////               && psession->m_psslcontext->m_pclientcontext != nullptr
////               && psession->m_psslcontext->m_pclientcontext->m_psslcontext != nullptr
////               && psession->m_psslcontext->m_iSslCtxRetry == 1 && iTry < iTryCount)
////            {
////
////               goto retry;
////
////            }
////
////#endif
//
//         }
//         else if (iStatusCode != 200)
//         {
//
//            if (iTry < iTryCount)
//            {
//
//               psession = nullptr;
//
//               goto retry;
//
//            }
//
//         }
//
//         ::e_status estatus;
//
//         if (::failed(psession->m_estatus))
//         {
//
//            estatus = psession->m_estatus;
//
//         }
//         else if ((iStatusCode >= 200 && iStatusCode <= 299) || (psession != nullptr && psession->outattr("http_status_code").is_empty()))
//         {
//
//            estatus = ::success;
//
//         }
//         else if (iStatusCode >= 300 && iStatusCode <= 399)
//         {
//
//            string strRedirectUrl = psession->inheader("location");
//
//            if (psession != nullptr)
//            {
//
//               string strCa2Realm;
//               
//               strCa2Realm = psession->outheader("ca2realm-x");
//
//               if (string_begins_ci(strCa2Realm, "n7ot licensed: "))
//               {
//
//                  INFORMATION("Not Licensed Result Total time ::http::apex::context::get(\"" << strUrl.left(minimum(255, strUrl.length())) << "\") " << tick1.elapsed().integral_second());
//
//                  string strLocation;
//                  
//                  strLocation = psession->outheader("Location");
//
//                  psession.release();
//
//                  throw ::exception(error_licensing, "realm:" + strCa2Realm + ",location:" + strLocation);
//
//                  return false;
//
//               }
//
//            }
//
//         }
//         else
//         {
//
//            estatus = error_http;
//
//         }
//
//         set["get_status"] = estatus;
//
//         FORMATTED_INFORMATION("Total time ::http::apex::context::get(\"%s\") %d ms ", strUrl.left(minimum(255, strUrl.length())).c_str(), tick1.elapsed().integral_second().m_i);
//
//      }
//      catch (...)
//      {
//
//         if (iTry >= iTryCount)
//         {
//
//            return false;
//
//         }
//
//         goto retry;
//
//      }
//
//      if (psession != nullptr)
//      {
//
//         if (set.has_property("get_response"))
//         {
//
//            set["get_response"] = string((const char *)psession->GetDataPtr(), psession->GetContentLength());
//
//         }
//
//         if (set.has_property("get_memory"))
//         {
//
//            memory_base * pmemory = set.cast < memory_base >("get_memory");
//
//            if (pmemory != nullptr)
//            {
//
//               pmemory->assign(psession->GetDataPtr(), psession->GetContentLength());
//
//            }
//            else
//            {
//
//               set["get_memory"] = __new(memory(psession->GetDataPtr(), psession->GetContentLength()));
//
//            }
//
//         }
//
//      }

      return true;

   }


   bool context::get(::http::session & session, const ::scoped_string & scopedstrUrl, string & str, property_set & set, const ::function < void(double, filesize, filesize) > & functionProgress)
   {

      bool bOk = http_get(session.m_psocket, scopedstrUrl, set, functionProgress);

      if (bOk)
      {

         const char * pszData = (const char *)session.m_psocket->GetDataPtr();

         strsize iSize = session.m_psocket->GetContentLength();

         str = string(pszData, iSize);

      }

      return bOk;

   }


   string context::get(::http::session & session, const ::scoped_string & scopedstrUrl, property_set & set)
   {

      string str;

      if (!get(session, scopedstrUrl, str, set))
      {

         return "";

      }

      return str;

   }



   bool context::http_get(::pointer<::sockets::http_client_socket>& psocket, const ::scoped_string & scopedstrUrl1, property_set & set, const ::function < void(double, filesize, filesize) > & functionProgress = nullptr)
   {

      //auto ptask = ::get_task();

      //KEEP(ptask->payload("work_url"), scopedstrUrl);

      auto psystem = acmesystem()->m_papexsystem;

      if (!psystem->networking())
      {

         return false;

      }

      auto purl = psystem->url();

      i64 iHttpGetSerial = ++psystem->networking()->m_lHttpGetSerial;

      //TRACE("");
      //TRACE("");
      set["http_get_serial"] = iHttpGetSerial;

      auto tickStart = ::time::now();

      int iTry = 0;

      int iTryCount;

      if (set.has_property("try"))
      {

         iTryCount = set["try"].as_i32();

         if (iTryCount > 5)
         {

            iTryCount = 5;

         }

      }
      else
      {

         iTryCount = 2;

      }
      INFORMATION("------------------------------------------------------");

      string strUrl;

      strUrl = scopedstrUrl1;

      string strRedirect;
//#ifdef BSD_STYLE_SOCKETS
      retry :
//#endif
      if (iTry > 0)
      {

         if (strRedirect.has_char())
         {

            INFORMATION("Redirect: " << iHttpGetSerial << strRedirect);

            strUrl = strRedirect;

            strRedirect.empty();

         }
         else
         {

            INFORMATION("Redirect: " << iHttpGetSerial << strUrl);

         }

      }
      else
      {

         INFORMATION("Start: " << iHttpGetSerial << strUrl);

      }

      iTry++;

      auto tickTimeProfile1 = ::time::now();

      string strServer = purl->get_root(strUrl);

      string strProtocol = purl->get_protocol(strUrl);

      string strObject = purl->get_object(strUrl);

      ::pointer<::apex::application>papp = set["app"].cast < ::apex::application >();

      ::pointer<::apex::application>pappAgent = papp;

      i32 iPort;

      if (strProtocol == "https")
      {

         iPort = 443;

      }
      else
      {

         iPort = 80;

      }

      string strVersion;
      
      strVersion = set["http_protocol_version"];

      if (strVersion.is_empty())
      {

         strVersion = "HTTP/1.1";

      }

//      bool bSessionAccount = !set.is_true("raw_http") && ::is_set(get_session()) && ::is_set(psession->account());

      bool bSessionAccount = !set.is_true("raw_http") && ::is_set(acmesession()) ;

//      single_lock slFontopus(bSessionAccount ? psession->account()->mutex() : nullptr);

      string strIp;

      string strSessId;

      int iRetrySession = 0;

   //retry_session:

   //   ::pointer<::account::user>puser;

      ::pointer<::object>pobjectCreator = pappAgent;

      if (pobjectCreator.is_null())
      {

         pobjectCreator = m_pcontext;

      }

      if (bSessionAccount)
      {

//         on_auth(set, papp, strUrl, strSessId, puser);

         if (strSessId.has_char())
         {

            string strCookie = set["cookie"];

            set["cookie"] = ::str::has_char(strCookie, "", "; ") + "sessid=" + strSessId;

         }

         // Format of script name example "context://server.com/the rain.mp3" => "context://server.com/the%20rain.mp3"
         {

            string strScript = ::url::encode(::url::decode(purl->get_script(strUrl)));

            strScript.replace_with("%20", "+");

            strScript.replace_with("/", "%2F");

            strUrl = purl->set_script(strUrl, strScript);

         }

      }

      bool bPost;

      bool bPut;

      if (set["put"].cast < ::file::file >() || set("http_method") == "PUT")
      {

         bPost = false;

         bPut = true;

         auto psocketPut = pobjectCreator->__create_new < ::sockets::http_put_socket>();

         psocketPut->initialize_http_put_socket(strUrl);

         psocket = psocketPut;

         dynamic_cast <::sockets::http_put_socket *> (psocket.m_p)->m_file = set["put"].cast < ::file::file >();

         psocket->m_emethod = ::sockets::http_method_put;

      }
      else if (set["post"].propset().has_element() || set("http_method") == "POST")
      {

         bPost = true;

         bPut = false;

         auto psocketPost = pobjectCreator->__create_new < ::sockets::http_post_socket >();

         psocketPost->initialize_http_post_socket(strUrl);

         psocket = psocketPost;

         dynamic_cast <::sockets::http_post_socket *> (psocket.m_p)->m_fields = set["post"].propset();

         if (set.has_property("multipart"))
         {

            psocket.cast < ::sockets::http_post_socket>()->m_pmultipart = set["multipart"].cast < ::sockets::multipart >();

         }

         psocket->m_emethod = ::sockets::http_method_post;

      }
      else
      {

         bPost = false;

         bPut = false;

         auto psocketGet = pobjectCreator->__create_new < ::http::get_socket>();

         psocketGet->initialize_get_socket(strUrl);

         psocket = psocketGet;

         psocket->m_emethod = ::sockets::string_http_method(set("http_method", "GET"));

      }

      ::pointer<::sockets::base_socket_handler>psockethandler = psocket->socket_handler();

      if (!psockethandler)
      {

         psockethandler = __create < ::sockets::socket_handler >();

         psocket->initialize_socket(psockethandler);

      }

      string strTopicText;

      strTopicText.format(__prhttpget, iHttpGetSerial);

      //psocket->set_topic_text(strTopicText);

      psocket->m_functionProgress = functionProgress;

      psocket->EnablePool(psockethandler->PoolEnabled());

      if (set["disable_common_name_cert_check"].is_true())
      {

         psocket->enable_cert_common_name_check(false);

      }

      if (strProtocol == "https")
      {

         psocket->set_tls_hostname(purl->get_server(strUrl));

      }

      if (set["http_listener"].cast < ::http::listener >() != nullptr)
      {

         psocket->::sockets::http_socket::m_plistener = set["http_listener"].cast < ::http::listener >();

      }

      psocket->inheaders().merge(set["headers"]);

      if (set.has_property("progress_listener"))
      {

         psocket->m_progressinteger.m_plistener = set["progress_listener"].cast < ::progress::listener >();

      }

      //if (set.has_property("int_scalar_source_listener"))
      //{

      //   psocket->::int_scalar_manager::m_plistener = set["int_scalar_source_listener"].cast < int_scalar_source::listener >();

      //}

      if (set.has_property("minimal_headers") && set["minimal_headers"].is_true())
      {

         psocket->m_request.attrs()["minimal_headers"] = true;

      }

      if (set.has_property("only_headers") && set["only_headers"].is_true())
      {

         psocket->m_bOnlyHeaders = true;

      }

      if (set.has_property("noclose") && set["noclose"].is_false())
      {

         psocket->m_bNoClose = false;

      }

      if (set.has_property("file"))
      {

         psocket->m_pfile = set["file"].cast < ::file::file >();

      }

      if (set["cookies"].cast < ::http::cookies >() != nullptr && set["cookies"].cast < ::http::cookies >()->get_size() > 0)
      {

         if (set["cookies"].cast < ::http::cookies >()->find_cookie("sessid") >= 0)
         {

            set["cookies"].cast < ::http::cookies >()->set_cookie("sessid", strSessId);

         }

         psocket->request().header("cookie") = set["cookies"].cast < ::http::cookies >()->get_cookie_header();

      }

      //if (set["user"].cast < ::account::user >() != nullptr && set["user"].cast < ::account::user >()->m_phttpcookies != nullptr && !(bool)set["disable_ca2_user_cookies"])
      //{

      //   if (set["user"].cast < ::account::user >()->m_phttpcookies->find_cookie("sessid") >= 0)
      //   {

      //      set["user"].cast < ::account::user >()->m_phttpcookies->set-cookie("sessid", strSessId);

      //   }

      //   psocket->request().header("cookie") = set["user"].cast < ::account::user >()->m_phttpcookies->get_cookie_header();

      //}

      if (set.has_property("cookie") && set["cookie"].has_char())
      {

         psocket->request().header("cookie") = set["cookie"];

      }

      if (!psocket->m_bNoClose)
      {

         psocket->SetCloseOnComplete();

      }

      if (strProtocol == "https")
      {

         psocket->EnableSSL();

      }

      auto tick1 = ::time::now();

      bool bConfigProxy = !set.has_property("no_proxy_config") || set["no_proxy_config"].is_false();

      class ::time tickTotalTimeout = set["timeout"].time();

      set["http_body_size_downloaded"] = &psocket->m_body_size_downloaded;

      {

         auto plistener = set["http_downloaded_rate_listener"].cast < ::scalar_source::listener >();

         if (::is_set(plistener))
         {

            psocket->m_scalarlistenera.add(plistener);

         }

      }

      //psocket->m_realscalarDownloadedRate.m_atom = set["http_downloaded_rate_id"].atom();

      {

         auto plistener = set["http_downloaded_listener"].cast < ::scalar_source::listener >();

         if (::is_set(plistener))
         {

            psocket->m_scalarlistenera.add(plistener);

         }

      }

      //psocket->m_integerscalarDownloaded.m_atom = set["http_downloaded_id"].atom();

      if (tickTotalTimeout <= 0_s)
      {

         tickTotalTimeout = 30_s;

      }

      if (strIp.has_char())
      {

         psocket->set_connect_host(strIp);

      }

      string_array straProxy;

      if (set.has_property("proxy"))
      {

         straProxy.explode(":", set["proxy"]);

         if (straProxy.get_count() != 2 || !psocket->proxy_open(straProxy[0], atoi(straProxy[1])))
         {

            set["get_status"] = (i64)error_http;

            auto tick2 = ::time::now();

            INFORMATION(LOG_HTTP_PREFIX << "> Not Opened/Connected Result Total time ::http::apex::context::get(\"" << strUrl.left(minimum(255, strUrl.length())) << "\") " << tick1.elapsed().integral_second());

            return false;

         }

      }
      else if (!psocket->open(bConfigProxy))
      {

         set["get_status"] = (i64)error_http;

         INFORMATION(LOG_HTTP_PREFIX << "> Not Opened/Connected Result Total time ::http::apex::context::get(\"" << strUrl.left(minimum(255, strUrl.length())) << "\") " << tick1.elapsed().integral_second());

         return false;

      }

      //auto passociation = psockethandler->new_association(psocket);

      psockethandler->add(psocket);

      i32 iIteration = 1;

      //::apex::live_signal keeplive;

      if (set["noloop"].is_true())
      {

         return true;

      }

      if (set.has_property("maximum_connection_retry_count"))
      {

         psocket->SetMaximumConnectionRetryCount(set["maximum_connection_retry_count"].as_i32());

      }
      //else
      //{

      //   psocket->SetConnectionRetry(3);

      //}

      //if (papp != nullptr)
      //{

      //   keeplive.keep(papp);
      //   keeplive.keep(&Sess(papp));
      //   keeplive.keep(&Sys(papp));

      //}

      if (psocket->IsPoolEnabled())
      {

         psocket->SetRetain();

      }

      i64 iContentLength = -1;

      i64 iBodySizeDownloaded = -1;

      int iEnteredLoop = 0;

      tick1 = ::time::now();

      while (psockethandler->get_count() > 0 && (::get_task() == nullptr || ::task_get_run()))
      {

         if (tickStart.elapsed() > tickTotalTimeout)
         {

            INFORMATION(LOG_HTTP_PREFIX << "> FAILING BY time_out after " << iIteration << " steps " << tick1.elapsed().integral_second());

            break;

         }

         iEnteredLoop = 1;

         auto iSelectTimeoutMillis = minimum(tickTotalTimeout, (tickTotalTimeout - tickStart.elapsed()));

         auto iSelectTimeoutSeconds = iSelectTimeoutMillis.integral_second();

         iSelectTimeoutSeconds = maximum(1, iSelectTimeoutSeconds);

         iContentLength = psocket->m_content_length;

         psocket->socket_handler()->select((i32)iSelectTimeoutSeconds, 0);

         set["http_content_length"] = iContentLength;

         double dRateDownloaded = 0.0;

         i64 iBodySizeDownloadedNow = set["http_body_size_downloaded"].as_i64();

         if (iBodySizeDownloadedNow > iBodySizeDownloaded)
         {

            iBodySizeDownloaded = iBodySizeDownloadedNow;

            if (iBodySizeDownloaded > 0)
            {

               tickStart = ::time::now();

            }

         }

         if (set.has_property("cancel") && set["cancel"].get_bool())
         {

            INFORMATION(LOG_HTTP_PREFIX << "> FAILING BY Cancellation at step " << iIteration << " " << tick1.elapsed().integral_second());

            break;

         }

         if (iContentLength > 0)
         {

            if (iBodySizeDownloaded > 0.0)
            {

               dRateDownloaded = (double)iBodySizeDownloaded / (double)iContentLength;

            }

         }

         set["http_rate_downloaded"] = dRateDownloaded;

         psocket->set_scalar(::e_scalar_download_progress_rate, dRateDownloaded);

         psocket->set_scalar(::e_scalar_download_size, iBodySizeDownloaded);

//         keeplive.keep-alive();

         if (psocket->m_estatus == error_connection_timed_out
            || psocket->m_estatus == error_on_connection_timeout)
         {

            INFORMATION(LOG_HTTP_PREFIX << "FAILING BY Connection time_out after " << iIteration << " steps " << tick1.elapsed().integral_second());

            break;

         }

         if (psocket->m_b_complete)
         {

            INFORMATION(LOG_HTTP_PREFIX << "Complete! in "<< iIteration <<" steps " << tick1.elapsed().integral_second());

            break;

         }

         if (iContentLength >= 0)
         {

            INFORMATION(LOG_HTTP_PREFIX << iIteration << ". step " << tick1.elapsed().integral_second() << " Content-Length: " << (integral_byte)(memsize) iContentLength);

         }
         else
         {

            INFORMATION(LOG_HTTP_PREFIX << iIteration << ". step " << tick1.elapsed().integral_second());

         }


         if (HTTP_DEBUG_LEVEL >= DEBUG_LEVEL_SICK)
         {

            INFORMATION(LOG_HTTP_PREFIX << "iSelectTimeoutSeconds=" << iSelectTimeoutSeconds);

         }

         iIteration++;

      }

//      keeplive.keep-alive();

      set["get_headers"] = psocket->outheaders();

      set["get_attrs"] = psocket->outattrs();

      string strCookie = psocket->response().cookies().get_cookie_header();

      set["cookie"] = strCookie;

      ::e_status estatus = error_failed;

      i32 iStatusCode;

      iStatusCode = psocket->outattr("http_status_code").as_i32();

      set["http_status_code"] = iStatusCode;

      string strStatus;
      
      strStatus = psocket->outattr("http_status");

      set["http_status"] = strStatus;
      
      set["chunked"] = psocket->m_bChunked;

      bool bChunked = psocket->m_bChunked;
      
      set["chunk_size"] = psocket->m_chunk_size;

      memsize iChunkSize = psocket->m_chunk_size;
      
      set["http_content_length"] = psocket->m_content_length;

      iContentLength = psocket->m_content_length;
      
      set["http_body_size_downloaded"] = psocket->m_body_size_downloaded;

      iBodySizeDownloaded = psocket->m_body_size_downloaded;

      INFORMATION(LOG_HTTP_PREFIX
         << strUrl
         << " Status: "
         << iStatusCode
         << " - "
         << strStatus
         << (bChunked ? " Chunk Size : " : " Content Length : ")
         << (bChunked ? (memsize)iChunkSize :(memsize)iContentLength)
         << ", Body Download : "
         << iBodySizeDownloaded
         << ", Loop : "
         << iEnteredLoop
         << ", "
         << (psocket->m_b_complete ? "Finished!" : "Incomplete!"));
         //iHttpGetSerial,
         //.c_str(),
         //,
         //strStatus.c_str(),
         //iContentLength,
         //iBodySizeDownloaded,
         //iEnteredLoop,
         
      //);

      if (set.has_property("cancel") && set["cancel"].get_bool())
      {

         psocket->m_estatus = error_connection_cancelled;

      }
      else if (iStatusCode == 0)
      {

         class ::time tickElapse = tickStart.elapsed();

         if (iTry < iTryCount && tickElapse < tickTotalTimeout)
         {

            task_sleep(300_ms);

            if (::task_get_run())
            {

               goto retry;

            }

         }

         INFORMATION(LOG_HTTP_PREFIX << "URL: " << strUrl << " Too much tries("<< iTry <<")");

         estatus = error_http;

      }
      else if ((iStatusCode >= 200 && iStatusCode <= 299) || psocket->outattr("http_status_code").is_empty())
      {

         estatus = ::success;

      }
      else if (iStatusCode >= 300 && iStatusCode <= 399)
      {

         string strCa2Realm;
         
         strCa2Realm = psocket->outheader("ca2realm-x");

         if (string_begins_ci(strCa2Realm, "not licensed: "))
         {

            auto tick2 = ::time::now();

            INFORMATION(LOG_HTTP_PREFIX << "Not Licensed Result Total time ::http::apex::context::get(\"" << strUrl.left(minimum(255, strUrl.length())) << "\") " << tick1.elapsed().integral_second());

            string strLocation;
            
            strLocation = psocket->outheader("Location");

            throw ::exception(error_licensing, "realm:"+strCa2Realm+",location:"+ strLocation);

            return false;

         }

         string strLocation;
         
         strLocation = psocket->outheader("location");

         if (set.has_property("redirect_location"))
         {

            set["redirect_location"] = strLocation;

            estatus = ::success_http_redirection;

         }
         else if (strLocation.has_char())
         {


            if (strLocation.case_insensitive_find("http://") == 0 || strLocation.case_insensitive_find("https://") == 0)
            {

               strRedirect = strLocation;

               goto retry;

            //   return http_get(psocket, strLocation, set);

            }
            else
            {

               ::file::path pathBase = purl->get_protocol(strUrl) + purl->get_server(strUrl);

               strLocation = pathBase / strLocation;

               goto retry;

            }

         }

      }
      else if (::failed(psocket->m_estatus))
      {

         estatus = psocket->m_estatus;

      }
      else if (iStatusCode == 401)
      {

         //if (strSessId.has_char() && puser.is_set() && iRetrySession < 3)
         //{

         //   psession->account()->not_auth(scopedstrUrl);

         //   iRetrySession++;

         //   goto retry_session;

         //}

         estatus = error_http;

      }
      else
      {

         estatus = error_http;

      }

      set["get_status"] = estatus;

      if (set["http_listener"].cast < ::http::listener >() != nullptr)
      {

         set["http_listener"].cast < ::http::listener >()->on_http_complete(psocket, estatus);

      }

      if (set.has_property("get_response"))
      {

         const char *pszData = (const char *)psocket->GetDataPtr();

         strsize iSize = psocket->GetContentLength();

         string strResponse(pszData, iSize);

         set["get_response"] = strResponse;

      }

      if (set.has_property("get_memory"))
      {

         memory_base * pmemory = set.cast < memory_base >("get_memory");

         if (pmemory != nullptr)
         {

            pmemory->assign(psocket->GetDataPtr(), psocket->GetContentLength());

         }
         else
         {

            set["get_memory"] = __new(memory(psocket->GetDataPtr(), psocket->GetContentLength()));

         }

      }

      INFORMATION(LOG_HTTP_PREFIX << "Total time " << tick1.elapsed().integral_second());

      return true;

   }


   void context::get(::message::message * pmessage)
   {

      ::pointer<message>pmessageMessage(pmessage);

      if (pmessageMessage == nullptr)
      {

         return;

      }

      //::pointer<message>pmessage(pmessage);

      ::url_domain domain;

      auto psystem = acmesystem();

      auto purl = psystem->url();

      domain.create(purl->get_server(pmessageMessage->m_strUrl));

      if (domain.m_strRadix == "ca2" && string_begins(purl->get_object(pmessageMessage->m_strUrl), "/matter/"))
      {

         string strUrl(pmessageMessage->m_strUrl);

         property_set& set = pmessage->get_property_set();

         single_lock synchronouslock(m_pmutexDownload, true);

         if (!(m_straDownloading.contains(strUrl)) && !exists(pmessageMessage->m_strUrl, set))
         {

            synchronouslock.unlock();

            pmessageMessage->m_estatusRet = error_http;

            pmessage->m_bRet = false;

            return;

         }

      }

      pmessage->get_property_set() = process_set(*pmessage->m_ppropertyset, pmessageMessage->m_strUrl);

      //auto phandler = __create< ::sockets::socket_handler >();

      property_set & set = pmessage->get_property_set();

      if (pmessageMessage->m_setPost.get_count() > 0)
      {

         set["post"] = pmessageMessage->m_setPost;

      }

      if (pmessageMessage->m_setHeaders.get_count() > 0)
      {

         set["headers"] = pmessageMessage->m_setHeaders;

      }

      if (pmessageMessage->m_pcookies != nullptr && pmessageMessage->m_pcookies->get_count() > 0)
      {

         set["cookies"] = pmessageMessage->m_pcookies;

      }

      if (pmessageMessage->m_strVersion.has_char())
      {

         set["http_protocol_version"] = pmessageMessage->m_strVersion;

      }

      ::pointer<::sockets::http_client_socket>psocket;

      if (!http_get(psocket, pmessageMessage->m_strUrl, set, pmessageMessage->m_functionProgress))
      {

         pmessageMessage->m_estatusRet = (::e_status) set["get_status"].as_i64();

         pmessageMessage->m_bRet = false;

         return;

      }

      if (::is_null(psocket))
      {

         throw exception(error_wrong_state);

      }

      pmessageMessage->m_estatusRet = (::e_status) set["get_status"].as_i64();

      pmessageMessage->m_setHeaders = psocket->outheaders();

      i32 iStatusCode;

      iStatusCode = psocket->outattr("http_status_code").as_i32();

      pmessage->m_bRet = iStatusCode == 200;

      return;

   }


   bool context::download(::pointer<::sockets::http_session>& psession, const ::scoped_string & scopedstrRequest, ::payload payloadFile, property_set & set)
   {

      file_pointer spfile = file()->get_file(payloadFile,
         ::file::e_open_binary | ::file::e_open_create | ::file::e_open_read_write | ::file::e_open_defer_create_directory);

      set["file"] = spfile;

      bool bOk = request(psession, scopedstrRequest, set);

      set["file"].null();

      return bOk;

   }


   bool context::download(const ::scoped_string & scopedstrUrl, ::payload payloadFile, property_set & set)
   {

      auto phandler = __create < ::sockets::socket_handler >();

      ::pointer<::sockets::http_client_socket>psocket;

      bool bOk = false;

      {

         auto rfile = file()->get_file(payloadFile,
            ::file::e_open_binary | ::file::e_open_create | ::file::e_open_read_write | ::file::e_open_defer_create_directory);

         if (!rfile)
         {

            return false;

         }

         set["file"] = (::file_pointer) rfile;

         bOk = http_get(psocket, scopedstrUrl, set);

         set["file"].null();

      }

      if (!bOk)
      {

         return false;

      }

      return true;

   }


   bool context::exists(const ::scoped_string & scopedstrUrl, ::property_set & set)
   {

      auto etype = get_type(scopedstrUrl, set);

      return ::exists(etype);

   }


   ::file::enum_type context::get_type(const ::scoped_string & scopedstrUrl, ::property_set & set)
   {

      single_lock synchronouslock(m_pmutexDownload, true);

      i32 iStatusCode = 0;

      try
      {

         while (m_straExists.contains(scopedstrUrl))
         {

            synchronouslock.unlock();

            sleep(100_ms);

            synchronouslock.lock();

         }

         m_straExists.add(scopedstrUrl);

         synchronouslock.unlock();

         auto phandler = __create < ::sockets::socket_handler >();

         set["only_headers"] = true;

         ::url_domain domain;

         auto psystem = acmesystem();

         auto purl = psystem->url();

         domain.create(purl->get_server(scopedstrUrl));

         if (string_begins(purl->get_object(scopedstrUrl), "/matter/"))
         {

            set["raw_http"] = true;

         }

         ::pointer<::sockets::http_client_socket>psocket;

         if (!http_get(psocket, scopedstrUrl, set))
         {

            synchronouslock.lock();

            m_straExists.erase(scopedstrUrl);

            return ::file::e_type_doesnt_exist;

         }

         iStatusCode = psocket->outattr("http_status_code").as_i32();

         synchronouslock.lock();

      }
      catch (...)
      {

      }

      m_straExists.erase(scopedstrUrl);

      bool bExists = iStatusCode == 200;

      return ::file::e_type_element;

   }


   ::payload context::length(const ::scoped_string & scopedstrUrl, ::property_set & set)
   {

      set["only_headers"] = true;

      set["minimal_headers"] = true;

      ::url_domain domain;

      auto psystem = acmesystem();

      auto purl = psystem->url();

      domain.create(purl->get_server(scopedstrUrl));

      if (string_begins(purl->get_object(scopedstrUrl), "/matter/"))
      {

         set["disable_ca2_sessid"] = true;

      }

      ::pointer<::sockets::http_client_socket>psocket;

      if (http_get(psocket, scopedstrUrl, set))
      {

         return false;

      }

      i32 iStatusCode;

      iStatusCode = psocket->outattr("http_status_code").as_i32();

      if (iStatusCode == 200)
      {

         return psocket->outheader("content-length");

      }
      else
      {

         return ::payload(::e_type_null);

      }

   }


   string context::gmdate(time_t t)
   {

      if (t == 0)
      {

         t = ::time(nullptr);

      }

      struct tm tp;

#ifdef _WIN32

      ::memory_copy(&tp, gmtime(&t), sizeof(tp));

#else

      gmtime_r(&t, &tp);

#endif

      const char * days[7] = { "Sunday", "Monday",
                             "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"
      };

      const char * months[12] = { "Jan", "Feb", "Mar", "Apr", "May",
                                "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
      };

      char strDateTime[1024];

      sprintf(strDateTime, "%s, %02d-%s-%04d %02d:%02d:%02d GMT",
         days[tp.tm_wday],
         tp.tm_mday,
         months[tp.tm_mon],
         tp.tm_year + 1900,
         tp.tm_hour,
         tp.tm_min,
         tp.tm_sec);

      return strDateTime;

   }


   //void context::set_proxy_auth(::account::user * puser, ::sockets::http_client_socket * psocket)
   //{

   //   string strUserName;
   //   string strPassword;
   //   string strUserNameFile;
   //   string strPasswordFile;
   //   string strSection;

   //   strSection.format("proxy_auth\\%s.%s", puser->m_strLogin.c_str(), "proxy_auth");

   //   strUserNameFile = dir()->appdata() / strSection + "_1";

   //   strPasswordFile = dir()->appdata() / strSection + "_2";

   //   bool bOk = true;

   //   if (!psystem->crypto().file_get(strUserNameFile, strUserName, nullptr, get_app()) || strUserName.is_empty())
   //   {

   //      bOk = false;

   //   }

   //   if (!psystem->crypto().file_get(strPasswordFile, strPassword, nullptr, get_app()) || strPassword.is_empty())
   //   {

   //      bOk = false;

   //   }

   //   if (bOk)
   //   {

   //      psocket->m_strUserNameFile = strUserNameFile;

   //      psocket->m_strPasswordFile = strPasswordFile;

   //   }
   //   else
   //   {

   //      if (psession->get_auth("context/account/proxy_authenticate.xhtml", strUserName, strPassword))
   //      {

   //         psystem->crypto().file_set(strUserNameFile, strUserName, nullptr, get_app());

   //         psystem->crypto().file_set(strPasswordFile, strPassword, nullptr, get_app());

   //         psocket->m_strUserNameFile = strUserNameFile;

   //         psocket->m_strPasswordFile = strPasswordFile;

   //      }

   //   }

   //}


   //void context::clean_proxy_auth(::account::user * puser)
   //{

   //   string strSection;

   //   strSection.format("proxy_auth\\%s.%s", puser->m_strLogin.c_str(), "proxy_auth");

   //   file()->del(dir()->appdata() / strSection + "_1");

   //   file()->del(dir()->appdata() / strSection + "_2");

   //}


   bool context::put(const ::scoped_string & scopedstrUrl, memory_base & memory, property_set & set, const ::function < void(double, filesize, filesize) > & functionProgress)
   {

      auto pfile = create_memory_file(memory);

      return put(scopedstrUrl, pfile, set, functionProgress);

   }


   bool context::put(const ::scoped_string & scopedstrUrl, file_pointer  pfile, property_set & set, const ::function < void(double, filesize, filesize) > & functionProgress)
   {

      set["put"] = pfile;

      set["noclose"] = false;

      return get(scopedstrUrl, set, functionProgress).is_true();

   }


   bool context::request(const ::scoped_string & scopedstrMethod, const ::scoped_string & scopedstrUrl, property_set & set)
   {

      set["http_method"] = scopedstrMethod;

      return get(scopedstrUrl, set).is_true();

   }


} // namespace http



