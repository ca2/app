#include "framework.h"
#include "apex/net/sockets/_.h"


namespace http
{


   application::application(::object * pobject) :
      ::object(pobject)
   {

      m_setHttp["max_http_post"] = 5 * 1024 * 1024; // 5MB;

   }


   application::~application()
   {

   }


   void application::http_application_destruct()
   {

      message_receiver_destruct();

   }


   property_set & application::process_set(property_set & set, const char * pszUrl)
   {

      set["app"] = get_application();

      return set;

   }


   bool application::get(::sockets::socket_handler & handler, __pointer(::sockets::http_client_socket) & psession, const char * pszUrl,property_set & set)
   {

      return pcontext->m_papexcontext->http().http_get(handler, psession, pszUrl, process_set(set, pszUrl));

   }


   void application::get(::message::message * pmessage)
   {

      __pointer(message) pmessage(pmessage);

      ::url_domain domain;

      domain.create(::apex::get_system()->url().get_server(pmessage->m_strUrl));

      if(domain.m_strRadix == "ca2" && ::str::begins(::apex::get_system()->url().get_object(pmessage->m_strUrl),astr.MatterUri))
      {

         string strUrl(pmessage->m_strUrl);

         property_set set;

         set = pmessage->m_set;

         single_lock synchronouslock(pcontext->m_papexcontext->http().m_pmutexDownload, true);

         if (!(pcontext->m_papexcontext->http().m_straDownloading.contains(strUrl)) && !exists(pmessage->m_strUrl, set))
         {

            synchronouslock.unlock();

            pmessage->m_estatusRet = error_http;

            pmessage->m_bRet = false;

            return;

         }

      }

      pmessage->m_set = process_set(pmessage->m_set, pmessage->m_strUrl);

      pcontext->m_papexcontext->http().get(pmessage);

   }


   ::e_status application::get(memory_base & memory, const char * pszUrl, property_set & set)
   {

      set["get_memory"] = &memory;

      auto estatus = pcontext->m_papexcontext->http().get(pszUrl, process_set(set, pszUrl));

      set.erase_by_name("get_memory");

      return estatus;

   }


//   ::e_status application::get(string & str, const char * pszUrl, property_set & set)
//   {
//
//      set["get_response"].get_value() = &str;
//
//      return pcontext->m_papexcontext->http().get(pszUrl, process_set(set, pszUrl));
//
//   }
//
//
   string application::api_get(const char * pszUrl, property_set & set)
   {

      ::file::path url("https://api.ca2.software/");

      url /= pszUrl;

      return get(url, set);

   }


   string application::api_get(const char * pszUrl)
   {

      property_set set;

      set["disable_common_name_cert_check"] = true;

      return api_get(pszUrl, set);

   }


   ::e_status application::_get(const char * pszUrl, property_set & set)
   {

      set["get_response"] = "";

      set["bool_result"] = pcontext->m_papexcontext->http().get(pszUrl, process_set(set,pszUrl));

      return set["get_estatus"].estatus();

   }


   string application::get(const char * pszUrl, property_set & set)
   {

      auto estatus = _get(pszUrl, set);

      if(!estatus)
      {

         return "";

      }

      return set["get_response"].get_string();

   }


   ::e_status application::get(string & str, const char * pszUrl, property_set & set)
   {

      set["get_response"] = "";

      set["bool_result"] = pcontext->m_papexcontext->http().get(pszUrl, process_set(set, pszUrl));

      str = set["get_response"].get_string();

      return set["get_status"].estatus();

   }


   bool application::exists(const char * pszUrl, property_set & set)
   {

      ::file::enum_type etype = ::file::e_type_none;

      bool bExists = is_file_or_dir(pszUrl, nullptr, &etype, set);

      return bExists && etype != ::file::e_type_none;

   }


   bool application::is_file_or_dir(const char * pszUrl, ::payload * pvarQuery, ::file::enum_type * petype, property_set & set)
   {

      string strUrl(pszUrl);

      string strFile(strUrl);

      strFile.replace(":", "_");
      strFile.replace("//", "/");
      strFile.replace("?", "%19");
      strFile = pcontext->m_papexcontext->dir().cache() / strFile + ".meta_information";

      string strCache;

      if (!set["nocache"].get_bool())
      {

         pcontext->m_papexcontext->file().as_string(strFile);

         if (strCache.has_char())
         {

            if (strCache == "file")
            {

               if (::is_set(petype))
               {

                  *petype = ::file::e_type_file;

               }

               return true;

            }
            else if (strCache == "folder")
            {

               if (::is_set(petype))
               {

                  *petype = ::file::e_type_folder;

               }

               return true;

            }
            else if (strCache == "matter")
            {

               if (::is_set(petype))
               {

                  *petype = ::file::e_type_element;

               }

               return true;

            }
            else if (strCache == "itdoesntexist")
            {

               if (::is_set(petype))
               {

                  *petype = ::file::e_type_none;

               }

               return false;

            }

         }

      }

      if(::str::find_wwci("ca2", ::apex::get_system()->url().get_server(pszUrl)) < 0 && ::apex::get_system()->url().get_object(pszUrl).find_ci("/matter/") < 0)
      {

         set["raw_http"] = true;

      }

      ::file::enum_type etype = ::file::e_type_none;

      bool bExists = pcontext->m_papexcontext->http().is_file_or_dir(strUrl, process_set(set, pszUrl), &etype);

      if (bExists)
      {

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

      }
      else
      {

         strCache = "itdoesntexist";

      }

      pcontext->m_papexcontext->file().put_contents(strFile, strCache);

      if (::is_set(petype))
      {

         *petype = etype;

      }

      return bExists;

   }


   ::payload application::length(const char * pszUrl, property_set & set)
   {

      return length(pszUrl, nullptr, set);

   }


   ::payload application::length(const char * pszUrl, ::payload * pvarQuery, property_set & set)
   {

      string strUrl(pszUrl);

      string strFile(strUrl);

      strFile.replace(":", "_");
      strFile.replace("//", "/");
      strFile.replace("?", "%19");
      strFile = pcontext->m_papexcontext->dir().cache() / strFile + ".length_question";

      bool bNoCache = set["nocache"].get_bool();

      string strCache;

      if (!bNoCache)
      {

         strCache = pcontext->m_papexcontext->file().as_string(strFile);

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

      ::payload len = pcontext->m_papexcontext->http().length(strUrl, process_set(set, pszUrl));

      if (len.is_empty())
      {

         strCache = "-1";

      }
      else
      {

         strCache = __str(len.i64());

      }

      pcontext->m_papexcontext->file().put_contents(strFile, strCache);

      return len;

   }


   bool application::request(const char * pszRequest, const char * pszUrl, property_set & set)
   {

      return pcontext->m_papexcontext->http().request(pszRequest, pszUrl, process_set(set, pszUrl));

   }


   bool application::download(::sockets::socket_handler & handler, __pointer(::sockets::http_session) & psession,const char * pszUrl,::payload varFile,property_set & set)
   {

      return pcontext->m_papexcontext->http().download(handler, psession, pszUrl,varFile,process_set(set,pszUrl));

   }


   bool application::download(const char * pszUrl, ::payload varFile, property_set & set)
   {
      return pcontext->m_papexcontext->http().download(pszUrl, varFile, process_set(set, pszUrl));
   }

   bool application::put(const char * pszUrl, memory & memory, property_set & set)
   {

      return pcontext->m_papexcontext->http().put(pszUrl, memory, process_set(set, pszUrl));
   }

   bool application::put(const char * pszUrl, file_pointer  pfile, property_set & set)
   {
      return pcontext->m_papexcontext->http().put(pszUrl, pfile, process_set(set, pszUrl));
   }



   string application::locale_schema_url(const char * pszUrl, const char * pszLocale, const char * pszSchema)
   {

      string str;

//      i32 iAttempt = 0;

      string strUrl(pszUrl);

      if (strUrl.find("?") >= 0)
      {

         strUrl += "&";

      }
      else
      {

         strUrl += "?";

      }

      strUrl += "lang=" + string(pszLocale) + "&styl=" + string(pszSchema);

      return strUrl;

   }


   string application::get_locale_schema(const char * pszUrl,const char * pszLocale,const char * pszSchema)
   {

      get_application()->message_box(nullptr, "What?!", e_message_box_ok);

      string strUrl = locale_schema_url(pszUrl, pszLocale, pszSchema);

      string str;

//      int iAttempt = 0;
//
//      property_set set;
//
//      __pointer(::sockets::http_session) psession;
//
//      string strFontopusServer;
//
//      if(atoi(::apex::get_system()->url().get_param(pszUrl, "authnone")) == 1
//            || ::apex::get_system()->url().get_param(pszUrl,"sessid").compare_ci("noauth") == 0)
//      {
//
//         strFontopusServer = pszUrl;
//
//      }
//      else
//      {
//
//         strFontopusServer = psession->account()->authenticator()->get_account_server(pszUrl);
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
//            str = pcontext->m_papexcontext->http().get(strUrl, set);
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


} // namespace http


