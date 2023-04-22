// From interprocess*.h/*.cpp by camilo on 2022-10-11 00:18 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "communication.h"
#include "target.h"
#include "caller.h"
#include "call.h"
#include "task.h"
////#include "acme/exception/exception.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include "acme/filesystem/filesystem/acme_file.h"
#include "acme/primitive/primitive/url.h"
#include "acme/operating_system/process.h"
#include "acme/parallelization/manual_reset_event.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/node.h"
#include "apex/constant/method.h"
#include "apex/filesystem/filesystem/file_context.h"
#include "apex/platform/app_launcher.h"
#include "apex/platform/application.h"
#include "apex/platform/context.h"
#include "apex/platform/launcher.h"
#include "apex/platform/os_context.h"
#include "apex/platform/system.h"


namespace interprocess
{


   communication::communication()
   {

      m_atom = "::interprocess::communication";

      defer_create_synchronization();


   }


   communication::~communication()
   {


   }


   void communication::initialize_interprocess_communication(::particle * pparticle, const ::string & strApp)
   {

      ::object::initialize(pparticle);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      m_strApp = strApp;

#ifdef UNIVERSAL_WINDOWS

      m_atomApp = strApp;

#else

      m_atomApp = (::i64) acmenode()->current_process_identifier();

#endif

      run_property(ID_CREATE);

      //call_procedures(CREATE_ROUTINE);

      /*estatus = */ __construct(m_ptarget);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      ::process_identifier iPid = m_pcontext->m_papexcontext->os_context()->current_process_identifier();

      //defer_add_module(file()->module(), iPid);

   //      ::file::path path;
   //
   //#ifndef UNIVERSAL_WINDOWS
   //
   //      path = module_path_from_pid(iPid);
   //
   //#endif
   //
   //      defer_add_module(path, iPid);

      m_ptarget->add_handler(this);

      string strKey = key(m_strApp, iPid);

      //if (!m_ptarget->create(strKey))
      m_ptarget->create(strKey);
      //{

      //   throw ::exception(error_resource);

      //}

      //return estatus;

   }


   void communication::destroy()
   {

      ::object::destroy();

      if (m_ptarget)
      {

         m_ptarget->destroy();

      }

      //return ::success;

   }


   bool communication::_handle_uri(const ::string & strUri)
   {

      INFORMATION("::interprocess::communication::on_interprocess_handle " << strUri);


      //   if(!strMessage.begins_eat("call "))
      //   {
      //
      //      return;
      //
      //   }
      //
      //   ::i64 iCall = ::str::consume_natural(strMessage);
      //
      //   if(!strMessage.begins_eat(" from "))
      //   {
      //
      //      return;
      //
      //   }
      //
      //   string strAppFrom;
      //
      //   strMessage.eat_before(strAppFrom, ":");
      //
      //   string strAppPid;
      //
      //   strMessage.eat_before(strAppPid, " ");
      //
      //   if(strAppFrom.is_empty())
      //   {
      //
      //      return;
      //
      //   }
      //
      //   if (strAppPid.is_empty())
      //   {
      //
      //      return;
      //
      //   }
      //
      //#if !defined(UNIVERSAL_WINDOWS)
      //
      //   auto iPid = atoll(strAppPid);
      //
      //   if(iPid == 0)
      //   {
      //
      //      return;
      //
      //   }
      //
      //#endif
      //
      //   auto pFind = strMessage.find(":");
      //
      //   string str1;
      //
      //   string strObject;
      //
      //   string strMember;
      //
      //   string_array stra;
      //
      //   property_set propertyset;
      //
      //   if(::is_set(pFind) && iFind <= 3)
      //   {
      //
      //      return;
      //
      //   }
      //
      //   if(iFind > 3)
      //   {
      //
      //      str1 = strMessage(0, pFind);
      //
      //   }
      //   else
      //   {
      //
      //      str1 = strMessage;
      //
      //   }
      //
      //   str1.trim();
      //
      //   strsize iFind2 = str1.find(".");
      //
      //   if(iFind2 < 0)
      //   {
      //
      //      return;
      //
      //   }
      //
      //   strObject = str1.left(iFind2);
      //
      //   strMember = str1.substr(iFind2 + 1);
      //
      //   if(::is_set(pFind))
      //   {
      //
      //      str1 = strMessage(pFind + 1);
      //
      //      str1.trim();
      //
      //      memory_stream stream;
      //
      //      stream->get_primitive_memory()->from_hex(str1);
      //
      //      stream->seek_to_begin();
      //
      //      stream.set_loading();
      //
      //      __io_array(stream, payloada);
      //
      //   }


      string strObject = acmesystem()->url()->get_server(strUri);

      string strMember = acmesystem()->url()->get_script(strUri);

      strMember.trim_left("/");

      string strNetworkArguments = acmesystem()->url()->get_query(strUri);

      ::property_set propertyset;

      propertyset.parse_network_arguments(strNetworkArguments);

      ::payload payloadReply;

      acmeapplication()->payload("activation.object") = strObject;

      acmeapplication()->payload("activation.member") = strMember;

      acmeapplication()->payload("activation.network_arguments") = strNetworkArguments;

      bool bShouldContinueTryingToHandle = _handle_call(payloadReply, strObject, strMember, propertyset);

      if (bShouldContinueTryingToHandle)
      {

         if (!strMember.case_insensitive_begins("reply."))
         {

            string strOrigin = propertyset["protocol"]["origin"];

            string strOriginObject = propertyset["protocol"]["origin_object"];

            auto iCallId = propertyset["protocol"]["call_id"].as_i64();

            auto pcall = create_call(strOrigin, strOriginObject, "reply." + strMember);

            (*pcall)["protocol"]["call_id"] = iCallId;

            (*pcall)["protocol"]["reply"] = payloadReply;

            //pcall->set_timeout(1_minute);

            fork([pcall, strOriginObject]()
               {

                  pcall->send(strOriginObject);

               });

         }

      }

      return bShouldContinueTryingToHandle;

   }


   void communication::start(const ::string & strApp)
   {

      synchronous_lock sl1(synchronization());

      auto & pmutex = m_mapAppMutex[strApp];

      if (pmutex.is_null())
      {

         __construct(pmutex);

      }

      sl1.unlock();

      synchronous_lock synchronouslock(pmutex);

      auto idaPid = processes_identifiers(strApp);

      if (idaPid.get_count() > 0)
      {

         return;

      }

      if (strApp == "app-core/clockverse")
      {

         ::output_debug_string("app-core/clockverse");

      }

      auto plauncher = __create < ::apex::app_launcher>();

      plauncher->initialize_app_launcher(this, acmenode()->process_platform_name(), strApp);

      atom idPid = -1;

      {

         auto ida = processes_identifiers(strApp);

         if (ida.is_empty())
         {

            branch_procedure(plauncher);

            int iStep = 0;

            int iSubStep;

            while (iStep < 8 && ::task_get_run())
            {

               for (iSubStep = 0; (iSubStep < (iStep + 1) * 10) && ::task_get_run(); iSubStep++)
               {

                  sleep(100_ms);

               }

               iStep++;

               ida = processes_identifiers(strApp);

               if (ida.has_element())
               {

                  goto started;

               }


            }

            throw ::exception(error_failed);

         }

      started:

         idPid = ida[0];

      }

      string strKey = strApp + ":" + idPid;

      if (m_callermap[strKey].is_null())
      {

         m_callermap[strKey] = __create < ::interprocess::caller>();

      }

      m_callermap[strKey]->open(key(strApp, idPid));

   }


   void communication::connect(const ::string & strApp, const ::atom & idPid)
   {

      string strKey = strApp + ":" + idPid;

      if (m_callermap[strKey].is_null())
      {

         m_callermap[strKey] = __create<::interprocess::caller>();

      }

      if (m_callermap[strKey]->is_caller_ok())
      {

         return;

      }

      m_callermap[strKey]->open(key(strApp, idPid));

   }


   ::interprocess::caller & communication::caller(const ::string & strApp, const ::atom & iPid)
   {

      string strKey = strApp + ":" + iPid;

      if (m_callermap[strKey].is_null())
      {

         m_callermap[strKey] = __create < ::interprocess::caller>();

      }

      if (!m_callermap[strKey]->is_caller_ok())
      {

         connect(strApp, iPid);

      }

      return *m_callermap[strKey];

   }


   string communication::key(const string & strApp, const ::atom & idPid)
   {

      string strKey;

#ifdef WINDOWS

#ifdef UNIVERSAL_WINDOWS

      string strAppId(strApp);

      strAppId.find_replace("\\", "-");

      strAppId.find_replace("/", "-");

      strAppId.find_replace("-", "-");

      strKey = strAppId;

#else

      strKey = "::ca2::account::ccwarehouse::" + strApp + ":" + idPid;

#endif

#else

#if defined(LINUX) || defined(FREEBSD)

      strKey = acmedirectory()->system() / "communication" / strApp / idPid;

#elif defined(__APPLE__)

      string strAppId(strApp);

      strAppId.find_replace("\\", "-");

      strAppId.find_replace("/", "-");

      strAppId.find_replace("-", "-");

      strKey = strAppId;

#ifdef MACOS

      strKey += "/" + ::as_string(idPid.as_i32());

#endif

#else

      strKey = acmedirectory()->system() / "communication" / strApp / ::as_string(idPid);


#endif

#endif

      return strKey;

   }


   string communication::str_from_va(const payload_array & payloada)
   {

      //memory_file memoryfile;

      //binary_stream < FILE > stream(&memoryfile);

      //stream << payloada;

      //return memoryfile.memory()->to_hex();

      throw ::exception(todo);

      return {};

   }


   //bool communication::on_interprocess_handle(::interprocess::handler * pphandler, const ::string & strMessage)
   //{


   //   INFORMATION("::interprocess::communication::on_receive " << strMessage);

   //   string strUrl = strMessage;

   //   //   if(!strMessage.begins_eat("call "))
   //   //   {
   //   //
   //   //      return;
   //   //
   //   //   }
   //   //
   //   //   ::i64 iCall = ::str::consume_natural(strMessage);
   //   //
   //   //   if(!strMessage.begins_eat(" from "))
   //   //   {
   //   //
   //   //      return;
   //   //
   //   //   }
   //   //
   //   //   string strAppFrom;
   //   //
   //   //   strMessage.eat_before(strAppFrom, ":");
   //   //
   //   //   string strAppPid;
   //   //
   //   //   strMessage.eat_before(strAppPid, " ");
   //   //
   //   //   if(strAppFrom.is_empty())
   //   //   {
   //   //
   //   //      return;
   //   //
   //   //   }
   //   //
   //   //   if (strAppPid.is_empty())
   //   //   {
   //   //
   //   //      return;
   //   //
   //   //   }
   //   //
   //   //#if !defined(UNIVERSAL_WINDOWS)
   //   //
   //   //   auto iPid = atoll(strAppPid);
   //   //
   //   //   if(iPid == 0)
   //   //   {
   //   //
   //   //      return;
   //   //
   //   //   }
   //   //
   //   //#endif
   //   //
   //   //   auto pFind = strMessage.find(":");
   //   //
   //   //   string str1;
   //   //
   //   //   string strObject;
   //   //
   //   //   string strMember;
   //   //
   //   //   string_array stra;
   //   //
   //   //   property_set propertyset;
   //   //
   //   //   if(::is_set(pFind) && iFind <= 3)
   //   //   {
   //   //
   //   //      return;
   //   //
   //   //   }
   //   //
   //   //   if(iFind > 3)
   //   //   {
   //   //
   //   //      str1 = strMessage(0, pFind);
   //   //
   //   //   }
   //   //   else
   //   //   {
   //   //
   //   //      str1 = strMessage;
   //   //
   //   //   }
   //   //
   //   //   str1.trim();
   //   //
   //   //   strsize iFind2 = str1.find(".");
   //   //
   //   //   if(iFind2 < 0)
   //   //   {
   //   //
   //   //      return;
   //   //
   //   //   }
   //   //
   //   //   strObject = str1.left(iFind2);
   //   //
   //   //   strMember = str1.substr(iFind2 + 1);
   //   //
   //   //   if(::is_set(pFind))
   //   //   {
   //   //
   //   //      str1 = strMessage(pFind + 1);
   //   //
   //   //      str1.trim();
   //   //
   //   //      memory_stream stream;
   //   //
   //   //      stream->get_primitive_memory()->from_hex(str1);
   //   //
   //   //      stream->seek_to_begin();
   //   //
   //   //      stream.set_loading();
   //   //
   //   //      __io_array(stream, payloada);
   //   //
   //   //   }


   //   string strObject = acmesystem()->url()->get_server(strUrl);

   //   string strMember = acmesystem()->url()->get_script(strUrl);

   //   strMember.trim_left("/");

   //   string strNetworkArguments = acmesystem()->url()->get_query(strUrl);

   //   ::property_set propertyset;

   //   propertyset.parse_network_arguments(strNetworkArguments);

   //   ::payload payloadReply;

   //   bool bShouldContinueTryingToHandle = on_interprocess_handle(payloadReply, strObject, strMember, propertyset);

   //   if (bShouldContinueTryingToHandle)
   //   {

   //      if (!strMember.case_insensitive_begins("reply."))
   //      {

   //         string strOrigin = propertyset["protocol"]["origin"].get_string();

   //         string strOriginObject = propertyset["protocol"]["origin_object"].get_string();

   //         auto iCallId = propertyset["protocol"]["call_id"].i64();

   //         auto pcall = create_call(strOrigin, strOriginObject, "reply." + strMember);

   //         (*pcall)["protocol"]["call_id"] = iCallId;

   //         (*pcall)["protocol"]["reply"] = payloadReply;

   //         //pcall->set_timeout(1_minute);

   //         fork([pcall, strOriginObject]()
   //            {

   //               pcall->send(strOriginObject);

   //            });

   //      }

   //   }

   //   return bShouldContinueTryingToHandle;

   //}


   ::pointer<::interprocess::task>communication::create_task(::interprocess::call * pcall, const ::atom & idPid)
   {

      auto pobjectTask = __new(::interprocess::task(pcall, idPid, m_iTaskSeed++));

      synchronous_lock synchronouslock(this->synchronization());

      m_mapTask[pobjectTask->m_iTask] = pobjectTask;

      pcall->m_mapTask[pobjectTask->m_iTask] = pobjectTask;

      return pobjectTask;

   }


   ::pointer<::interprocess::task>communication::get_task(i64 iTask)
   {

      synchronous_lock synchronouslock(this->synchronization());

      return m_mapTask[iTask];

   }


   ::pointer<::interprocess::call>communication::create_call(const ::string & strApp, const ::string & strObject, const ::string & strMember)
   {

      return __new(::interprocess::call(this, strApp, strObject, strMember));

   }


   ::pointer<::interprocess::call>communication::create_call(const ::string & strObject, const ::string & strMember)
   {

      return create_call(m_strApp, strObject, strMember);

   }


   bool communication::_handle_call(::payload & payload, const ::string & strObject, const ::string & strMember, ::property_set & propertyset)
   {

      if (strObject == "application")
      {

         if (strMember.case_insensitive_begins("reply."))
         {

            ::i64 iTask = propertyset["protocol:call_id"].as_i64();

            auto pinterprocesstask = get_task(iTask);

            pinterprocesstask->m_payload = propertyset["protocol:reply"];

            pinterprocesstask->m_pevReady->set_event();

            return true;

         }
         else if (strMember == "on_additional_local_instance")
         {

            string strModule;

            strModule = propertyset["module"];

            string strCommandLine;

            strCommandLine = propertyset["command_line"];

            auto papp = get_app();

            papp->m_papexapplication->on_additional_local_instance(
               payload["handled"].bool_reference(),
               strModule,
               propertyset["pid"].as_i32(),
               strCommandLine);

            propertyset["continue"] = true;

            return false;

         }
         else if (strMember == "on_new_instance")
         {

            on_new_instance(propertyset["module"], propertyset["pid"]);

         }
         else
         {

            auto papp = get_app();

            papp->_handle_call(payload, strObject, strMember, propertyset);

         }

      }

      return false;

   }


   void communication::on_new_instance(const ::string & strModule, const ::atom & idPid)
   {

      defer_add_module(strModule, idPid);

      get_app()->m_papexapplication->on_new_instance(strModule, idPid);

   }


   ::atom_array communication::get_pid(const ::string & strApp)
   {

      ::atom_array idaPid;

      auto psystem = acmesystem();

      auto pnode = psystem->node();

#if defined(LINUX) || defined(MACOS) || defined(FREEBSD)

      ::file::path path = pnode->get_application_path(strApp, nullptr, nullptr);

      idaPid = pnode->module_path_processes_identifiers(path, false);

#else

//#if 0

      auto pids = pnode->module_list_file_processes_identifiers(strApp);

      for (auto & pid : pids)
      {

         idaPid.add(pid);

      }

//#else
//
//      ::file::path path = pnode->get_application_path(strApp, nullptr, nullptr);
//
//      idaPid = pnode->module_path_get_pid(path, false);
//
//#endif

#endif
      return idaPid;

   }


   void communication::defer_add_module(const ::string & strModule, const ::atom & idPid)
   {

      auto psystem = acmesystem();

      auto pnode = psystem->node();

#if !defined(UNIVERSAL_WINDOWS) && !defined(APPLE_IOS)

      ::file::path pathModule;

      m_straModule.erase_all();

      pathModule = acmedirectory()->roaming() / m_strApp;

      pathModule /= "module_list.txt";

      ::file::path pathPid = pnode->process_identifier_module_path((::u32)idPid.as_i64());

      string strModuleList = acmefile()->as_string(pathModule);

      m_straModule.add_lines(strModuleList);

      string_array stra2;

      int_array iaPid2;

      for (index i = 0; i < m_straModule.get_count();)
      {

         string str = m_straModule[i];

         str.trim();

         bool bOk = false;

         if (str.has_char())
         {

            string_array a;

            a.explode("|", str);

            if (a.get_size() >= 2)
            {

               stra2.add_unique_ci(a[0]);

               string strPath = pnode->process_identifier_module_path(atoi(a[1]));

               if (strPath.has_char())
               {

                  if (strPath.case_insensitive_order(a[0]) == 0)
                  {

                     bOk = true;

                  }

               }

            }

         }

         if (bOk)
         {

            i++;

         }
         else
         {

            m_straModule.erase_at(i);

         }

      }

      string_array straUnique;

      for(auto & strItem : m_straModule)
      {

         straUnique.add_unique_ci(strItem);

      }

      m_straModule = straUnique;

      ::file::path pathThisModule = file()->module();

      string strItem;

      if (pathPid.has_char())
      {

         strItem = pathPid + "|" + idPid;

      }
      else
      {

         strItem = strModule + "|" + idPid;
      }


      m_straModule.add_unique_ci(strItem);

      strModuleList = m_straModule.implode("\n");

      file()->put_text(pathModule, strModuleList);

#endif

   }


} // namespace interprocess





