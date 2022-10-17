﻿// From interprocess*.h/*.cpp by camilo on 2022-10-11 00:18 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "communication.h"
#include "target.h"
#include "caller.h"
#include "call.h"
#include "task.h"
#include "apex/constant/method.h"
#include "apex/platform/launcher.h"
#include "apex/platform/app_launcher.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include "acme/filesystem/filesystem/acme_file.h"


namespace interprocess
{


   communication::communication()
   {

      m_atom = "::interprocess::communication";

      defer_create_mutex();


   }


   communication::~communication()
   {


   }


   void communication::initialize_interprocess_communication(::object * pobject, const ::string & strApp)
   {

      ::object::initialize(pobject);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      m_strApp = strApp;

#ifdef _UWP

      m_atomApp = strApp;

#else

      m_atomApp = (::i64) ::get_current_process_id();

#endif

      run_property("on_create");

      call_routines_with_id(CREATE_ROUTINE);

      /*estatus = */ __construct(m_ptarget);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      int iPid = m_pcontext->m_papexcontext->os_context()->get_pid();

      //defer_add_module(m_pcontext->m_papexcontext->file().module(), iPid);

   //      ::file::path path;
   //
   //#ifndef _UWP
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


   bool communication::_handle_uri(const ::block & blockUri)
   {

      string strUri = blockUri;

      INFORMATION("::interprocess::communication::on_interprocess_handle " << strUri);


      //   if(!::str().begins_eat(strMessage, "call "))
      //   {
      //
      //      return;
      //
      //   }
      //
      //   ::i64 iCall = ::str().consume_natural(strMessage);
      //
      //   if(!::str().begins_eat(strMessage, " from "))
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
      //#if !defined(_UWP)
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
      //   strsize iFind = strMessage.find(":");
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
      //   if(iFind >= 0 && iFind <= 3)
      //   {
      //
      //      return;
      //
      //   }
      //
      //   if(iFind > 3)
      //   {
      //
      //      str1 = strMessage.Left(iFind);
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
      //   strObject = str1.Left(iFind2);
      //
      //   strMember = str1.Mid(iFind2 + 1);
      //
      //   if(iFind >= 0)
      //   {
      //
      //      str1 = strMessage.Mid(iFind + 1);
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


      string strObject = m_psystem->url()->get_server(strUri);

      string strMember = m_psystem->url()->get_script(strUri);

      strMember.trim_left("/");

      string strNetworkArguments = m_psystem->url()->get_query(strUri);

      ::property_set propertyset;

      propertyset.parse_network_arguments(strNetworkArguments);

      ::payload payloadReply;

      bool bShouldContinueTryingToHandle = _handle_call(payloadReply, strObject, strMember, propertyset);

      if (bShouldContinueTryingToHandle)
      {

         if (!strMember.begins_ci("reply."))
         {

            string strOrigin = propertyset["protocol"]["origin"].get_string();

            string strOriginObject = propertyset["protocol"]["origin_object"].get_string();

            auto iCallId = propertyset["protocol"]["call_id"].i64();

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

      synchronous_lock sl1(mutex());

      auto & pmutex = m_mapAppMutex[strApp];

      if (pmutex.is_null())
      {

         pmutex = __new(::mutex());

      }

      sl1.unlock();

      synchronous_lock synchronouslock(pmutex);

      auto idaPid = get_pid(strApp);

      if (idaPid.get_count() > 0)
      {

         return;

      }

      if (strApp == "app-core/clockverse")
      {

         ::output_debug_string("app-core/clockverse");

      }

      auto plauncher = __new(::apex::app_launcher);

      plauncher->initialize_app_launcher(this, process_platform_dir_name2(), strApp);

      atom idPid = -1;

      {

         auto ida = get_pid(strApp);

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

               ida = get_pid(strApp);

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

      string strKey = strApp + ":" + __string(idPid);

      if (m_callermap[strKey].is_null())
      {

         m_callermap[strKey] = __create < ::interprocess::caller>();

      }

      m_callermap[strKey]->open(key(strApp, idPid));

   }


   void communication::connect(const ::string & strApp, const ::atom & idPid)
   {

      string strKey = strApp + ":" + __string(idPid);

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

      string strKey = strApp + ":" + __string(iPid);

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

#ifdef _UWP

      string strAppId(strApp);

      strAppId.find_replace("\\", "-");

      strAppId.find_replace("/", "-");

      strAppId.find_replace("-", "-");

      strKey = strAppId;

#else

      strKey = "::ca2::account::ccwarehouse::" + strApp + ":" + __string(idPid);

#endif

#else

#if defined(LINUX) || defined(FREEBSD)

      strKey = m_psystem->m_pacmedirectory->system() / "communication" / strApp / __string(idPid);

#elif defined(__APPLE__)

      string strAppId(strApp);

      strAppId.find_replace("\\", "-");

      strAppId.find_replace("/", "-");

      strAppId.find_replace("-", "-");

      strKey = strAppId;

#ifdef MACOS

      strKey += "/" + __string(idPid.i32());

#endif

#else

      strKey = m_psystem->m_pacmedirectory->system() / "communication" / strApp / __string(idPid);


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

   //   //   if(!::str().begins_eat(strMessage, "call "))
   //   //   {
   //   //
   //   //      return;
   //   //
   //   //   }
   //   //
   //   //   ::i64 iCall = ::str().consume_natural(strMessage);
   //   //
   //   //   if(!::str().begins_eat(strMessage, " from "))
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
   //   //#if !defined(_UWP)
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
   //   //   strsize iFind = strMessage.find(":");
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
   //   //   if(iFind >= 0 && iFind <= 3)
   //   //   {
   //   //
   //   //      return;
   //   //
   //   //   }
   //   //
   //   //   if(iFind > 3)
   //   //   {
   //   //
   //   //      str1 = strMessage.Left(iFind);
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
   //   //   strObject = str1.Left(iFind2);
   //   //
   //   //   strMember = str1.Mid(iFind2 + 1);
   //   //
   //   //   if(iFind >= 0)
   //   //   {
   //   //
   //   //      str1 = strMessage.Mid(iFind + 1);
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


   //   string strObject = m_psystem->url()->get_server(strUrl);

   //   string strMember = m_psystem->url()->get_script(strUrl);

   //   strMember.trim_left("/");

   //   string strNetworkArguments = m_psystem->url()->get_query(strUrl);

   //   ::property_set propertyset;

   //   propertyset.parse_network_arguments(strNetworkArguments);

   //   ::payload payloadReply;

   //   bool bShouldContinueTryingToHandle = on_interprocess_handle(payloadReply, strObject, strMember, propertyset);

   //   if (bShouldContinueTryingToHandle)
   //   {

   //      if (!strMember.begins_ci("reply."))
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

      synchronous_lock synchronouslock(mutex());

      m_mapTask[pobjectTask->m_iTask] = pobjectTask;

      pcall->m_mapTask[pobjectTask->m_iTask] = pobjectTask;

      return pobjectTask;

   }


   ::pointer<::interprocess::task>communication::get_task(i64 iTask)
   {

      synchronous_lock synchronouslock(mutex());

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


   bool communication::_handle_call(::payload & payload, const ::block & blockObject, const ::block & blockMember, ::property_set & propertyset)
   {

      string strObject(blockObject);

      string strMember(blockMember);

      if (strObject == "application")
      {

         if (::str().begins_ci(strMember, "reply."))
         {

            ::i64 iTask = propertyset["protocol:call_id"];

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
               (bool &)payload["handled"],
               strModule,
               propertyset["pid"].i32(),
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

            papp->_handle_call(payload, blockObject, blockMember, propertyset);

         }

      }

      return false;

   }


   void communication::on_new_instance(const ::string & strModule, const ::atom & idPid)
   {

      defer_add_module(strModule, idPid);

      get_app()->m_papexapplication->on_new_instance(strModule, idPid);

   }


   id_array communication::get_pid(const ::string & strApp)
   {

      id_array idaPid;

#if defined(LINUX) || defined(MACOS) || defined(FREEBSD)

      auto psystem = m_psystem;

      auto pnode = psystem->node();

      ::file::path path = pnode->get_application_path(strApp, nullptr, nullptr);

      idaPid = pnode->module_path_get_pid(path, false);

#else

#if defined(_UWP)

      idaPid.add(strApp);

#else

      string_array stra;

      ::file::path pathModule;

      pathModule = m_psystem->m_pacmedirectory->system() / "communication";

      pathModule /= strApp + ".module_list";

      string strModuleList = m_psystem->m_pacmefile->as_string(pathModule);

      stra.add_lines(strModuleList);

   repeat:

      if (stra.get_count() > 32)
      {

         stra.erase_at(0, 16);

      }

      string_array stra2;

      int_array iaPid2;

      auto psystem = m_psystem;

      auto pnode = psystem->node();

      for (auto & str : stra)
      {

         if (str.has_char())
         {

            string_array a;

            a.explode("|", str);

            if (a.get_size() >= 2)
            {

               stra2.add_unique_ci(a[0]);

               string strPath = pnode->module_path_from_pid(ansi_to_i32(a[1]));

               if (strPath.has_char())
               {

                  if (strPath.compare_ci(a[0]) == 0)
                  {

                     idaPid.add(ansi_to_i32(a[1]));

                  }

               }

            }

         }

      }

      if (idaPid.get_count() <= 0 && stra.get_size() > 32)
      {

         goto repeat;

      }
      //for(auto & str : stra2)
      //{

      //   if(str.has_char())
      //   {

      //          iaPid.add_unique(module_path_get_pid(str));
   //
      //   }

      //}

#endif
#endif
      return idaPid;

   }


   void communication::defer_add_module(const ::string & strModule, const ::atom & idPid)
   {

      auto psystem = m_psystem;

      auto pnode = psystem->node();

#if !defined(_UWP) && !defined(APPLE_IOS)

      ::file::path pathModule;

      m_straModule.erase_all();

      pathModule = m_psystem->m_pacmedirectory->system() / "communication";

      pathModule /= m_strApp + ".module_list";

      ::file::path pathPid = pnode->module_path_from_pid((::u32)idPid.i64());

      string strModuleList = m_psystem->m_pacmefile->as_string(pathModule);

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

               string strPath = pnode->module_path_from_pid(ansi_to_i32(a[1]));

               if (strPath.has_char())
               {

                  if (strPath.compare_ci(a[0]) == 0)
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

      forallref(m_straModule)
      {

         straUnique.add_unique_ci(item);

      }

      m_straModule = straUnique;

      ::file::path pathThisModule = m_pcontext->m_papexcontext->file().module();

      string strItem;

      if (pathPid.has_char())
      {

         strItem = pathPid + "|" + __string(idPid);

      }
      else
      {

         strItem = strModule + "|" + __string(idPid);
      }


      m_straModule.add_unique_ci(strItem);

      strModuleList = m_straModule.implode("\n");

      m_pcontext->m_papexcontext->file().put_text(pathModule, strModuleList);

#endif

   }


} // namespace interprocess




