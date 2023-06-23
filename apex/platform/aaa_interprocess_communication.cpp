#include "framework.h"
#include "apex/constant/method.h"
#include "apex/platform/launcher.h"
#include "apex/platform/app_launcher.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include "acme/filesystem/filesystem/acme_file.h"


interprocess_intercommunication::interprocess::communication() 
{

   m_atom = "::interprocess::communication";

   defer_create_synchronization();


}


interprocess_intercommunication::~interprocess_intercommunication()
{


}


void interprocess_intercommunication::initialize_interprocess_communication(::particle * pparticle, const ::string & strApp)
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

   m_atomApp = (::i64) ::get_current_process_id();

#endif

   run_property("on_create");

   call_routines_with_id(CREATE_ROUTINE);

   /*estatus = */ __construct(m_prx);

   //if (!estatus)
   //{

   //   return estatus;

   //}

   int iPid = m_pcontext->m_papexcontext->os_context()->get_pid();

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

   m_prx->m_preceiver = this;

   string strKey = key(m_strApp, iPid);

   //if (!m_prx->create(strKey))
   m_prx->create(strKey);
   //{

   //   throw ::exception(error_resource);

   //}

   //return estatus;

}


void interprocess_intercommunication::destroy()
{

   ::object::destroy();

   if(m_prx)
   {

      m_prx->destroy();

   }

   //return ::success;

}


void interprocess_intercommunication::start(const ::string & strApp)
{

   synchronous_lock sl1(mutex());

   auto & pmutex = m_mapAppMutex[strApp];

   if(pmutex.is_null())
   {

      pmutex = __new(::pointer < ::mutex >());

   }

   sl1.unlock();

   synchronous_lock synchronouslock(pmutex);

   auto idaPid = get_pid(strApp);

   if(idaPid.get_count() > 0)
   {

      return;

   }

   if(strApp == "app-core/clockverse")
   {

      ::output_debug_string("app-core/clockverse");

   }

   auto plauncher = __new(::apex::app_launcher);
   
   plauncher->initialize_app_launcher(this, process_platform_name(), strApp);

   atom idPid = -1;

   {

      auto ida = get_pid(strApp);

      if(ida.is_empty())
      {

         branch_procedure(plauncher);

         int iStep = 0;

         int iSubStep;

         while(iStep < 8 && ::task_get_run())
         {

            for(iSubStep = 0; (iSubStep < (iStep + 1) * 10) && ::task_get_run(); iSubStep++)
            {

               sleep(100_ms);

            }

            iStep++;

            ida = get_pid(strApp);

            if(ida.has_element())
            {

               goto started;

            }


         }

         throw ::exception(error_failed);

      }

started:

      idPid = ida[0];

   }

   string strKey = strApp + ":" + as_string(idPid);

   if(m_txmap[strKey].is_null())
   {

      m_txmap[strKey] = __create < ::inteprocess::caller>();

   }

   m_txmap[strKey]->open(key(strApp,idPid));

}


void interprocess_intercommunication::connect(const ::string & strApp, const ::atom & idPid)
{

   string strKey = strApp + ":" + as_string(idPid);

   if(m_txmap[strKey].is_null())
   {

      m_txmap[strKey] = __create<::inteprocess::caller>();

   }

   if(m_txmap[strKey]->is_tx_ok())
   {

      return;

   }

   m_txmap[strKey]->open(key(strApp, idPid));

}


::inteprocess::caller & interprocess_intercommunication::tx(const ::string & strApp, const ::atom & iPid)
{

   string strKey = strApp + ":" + as_string(iPid);

   if(m_txmap[strKey].is_null())
   {

      m_txmap[strKey] = __create < ::inteprocess::caller>();

   }

   if(!m_txmap[strKey]->is_tx_ok())
   {

      connect(strApp, iPid);

   }

   return *m_txmap[strKey];

}


string interprocess_intercommunication::key(const string &strApp, const ::atom & idPid)
{

   string strKey;

#ifdef WINDOWS

#ifdef UNIVERSAL_WINDOWS

   string strAppId(strApp);

   strAppId.find_replace("\\","-");

   strAppId.find_replace("/","-");

   strAppId.find_replace("-","-");

   strKey = strAppId;

#else

   strKey = "::ca2::account::ccwarehouse::" + strApp + ":" + as_string(idPid);

#endif

#else

#if defined(LINUX) || defined(FREEBSD)

   strKey = acmedirectory()->system() / "interprocess_intercommunication" / strApp / as_string(idPid);

#elif defined(__APPLE__)

   string strAppId(strApp);

   strAppId.find_replace("\\","-");

   strAppId.find_replace("/","-");

   strAppId.find_replace("-","-");

   strKey = strAppId;
   
#ifdef MACOS

   strKey += "/" + as_string(idPid.i32());

#endif

#else

   strKey = acmedirectory()->system() / "interprocess_intercommunication" / strApp / as_string(idPid);


#endif

#endif

   return strKey;

}


string interprocess_intercommunication::str_from_va(const payload_array & payloada)
{

   //memory_file memoryfile;

   //binary_stream < FILE > stream(&memoryfile);

   //stream << payloada;

   //return memoryfile.memory()->to_hex();

   throw ::exception(todo);

   return {};

}


bool interprocess_intercommunication::on_interprocess_receive(::inteprocess::handler * prx, const ::string & strMessage)
{


   information() << "::interprocess::communication::on_receive " << strMessage;
   
   string strUrl = strMessage;

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
   
   
   string strObject = acmesystem()->url()->get_server(strUrl);
   
   string strMember = acmesystem()->url()->get_script(strUrl);
   
   strMember.trim_left("/");
   
   string strNetworkArguments = acmesystem()->url()->get_query(strUrl);
   
   ::property_set propertyset;
   
   propertyset.parse_network_arguments(strNetworkArguments);

   ::payload payloadReply;

   bool bShouldContinueTryingToHandle = on_interprocess_call(payloadReply, strObject, strMember, propertyset);

   if (bShouldContinueTryingToHandle)
   {

      if (!strMember.case_insensitive_begins("reply."))
      {

         string strOrigin = propertyset["protocol"]["origin"].get_string();

         string strOriginObject = propertyset["protocol"]["origin_object"].get_string();

         ::index iCallId = propertyset["protocol"]["call_id"].i64();

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


::pointer<::interprocess::task>interprocess_intercommunication::create_task(::interprocess::call * pcall, const ::atom & idPid)
{

   auto pobjectTask = __new(::interprocess::task(pcall, idPid, m_iTaskSeed++));

   synchronous_lock synchronouslock(this->synchronization());

   m_mapTask[pobjectTask->m_iTask] = pobjectTask;

   pcall->m_mapTask[pobjectTask->m_iTask] = pobjectTask;

   return pobjectTask;

}


::pointer<::interprocess::task>interprocess_intercommunication::get_task(i64 iTask)
{

   synchronous_lock synchronouslock(this->synchronization());

   return m_mapTask[iTask];

}


::pointer<::interprocess::call>interprocess_intercommunication::create_call(const ::string & strApp, const ::string & strObject, const ::string & strMember)
{

   return __new(::interprocess::call(this, strApp, strObject, strMember));

}


::pointer<::interprocess::call>interprocess_intercommunication::create_call(const ::string & strObject, const ::string & strMember)
{

   return create_call(m_strApp, strObject, strMember);

}


bool interprocess_intercommunication::on_interprocess_call(::payload & payload, const ::string & strObject, const ::string & strMember, ::property_set & propertyset)
{

   if(strObject == "application")
   {

      if(string_begins_ci(strMember, "reply."))
      {

         ::i64 iTask = propertyset["protocol:call_id"];

         auto pinterprocesstask = get_task(iTask);

         pinterprocesstask->m_payload = propertyset["protocol:reply"];

         pinterprocesstask->m_pevReady->set_event();

         return true;

      }
      else if(strMember == "on_additional_local_instance")
      {

         string strModule;
         
         strModule = propertyset["module"];

         string strCommandLine;

         strCommandLine = propertyset["command_line"];

         auto papp = get_app();

         papp->m_papexapplication->on_additional_local_instance(
            (bool &) payload["handled"],
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

   }

}


void interprocess_intercommunication::on_new_instance(const ::string & strModule, const ::atom & idPid)
{

   defer_add_module(strModule, idPid);

   get_app()->m_papexapplication->on_new_instance(strModule, idPid);

}


atom_array interprocess_intercommunication::get_pid(const ::string & strApp)
{

   atom_array idaPid;

#if defined(LINUX) || defined(MACOS) || defined(FREEBSD)

   auto psystem = acmesystem();
   
   auto pnode = psystem->node();
   
   ::file::path path = pnode->get_application_path(strApp, nullptr, nullptr);

   idaPid = pnode->module_path_get_pid(path, false);

#else

#if defined(UNIVERSAL_WINDOWS)

   idaPid.add(strApp);

#else

   string_array stra;

   ::file::path pathModule;

   pathModule = acmedirectory()->system() / "interprocess_intercommunication";

   pathModule /= strApp + ".module_list";

   string strModuleList = acmefile()->as_string(pathModule);

   stra.add_lines(strModuleList);

repeat:

   if (stra.get_count() > 32)
   {

      stra.erase_at(0, 16);

   }

   string_array stra2;

   int_array iaPid2;

   auto psystem = acmesystem();

   auto pnode = psystem->node();

   for (auto & str : stra)
   {

      if (str.has_char())
      {

         string_array a;

         a.explode("|", str);

         if (a.get_size() >= 2)
         {

            stra2.case_insensitive_add_unique(a[0]);

            string strPath = pnode->module_path_from_pid(ansi_to_i32(a[1]));

            if (strPath.has_char())
            {

               if (strPath.case_insensitive_order(a[0]) == 0)
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


void interprocess_intercommunication::defer_add_module(const ::string & strModule, const ::atom & idPid)
{
   
   auto psystem = acmesystem();
   
   auto pnode = psystem->node();

#if !defined(UNIVERSAL_WINDOWS) && !defined(APPLE_IOS)

   ::file::path pathModule;

   m_straModule.erase_all();

   pathModule = acmedirectory()->system() / "interprocess_intercommunication";

   pathModule /= m_strApp + ".module_list";
   
   ::file::path pathPid = pnode->module_path_from_pid((::u32)idPid.i64());

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

            stra2.case_insensitive_add_unique(a[0]);

            string strPath = pnode->module_path_from_pid(ansi_to_i32(a[1]));

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

   forallref(m_straModule)
   {

      straUnique.case_insensitive_add_unique(item);

   }

   m_straModule = straUnique;

   ::file::path pathThisModule = file()->module();

   string strItem;

   if (pathPid.has_char())
   {

      strItem = pathPid + "|" + as_string(idPid);

   }
   else
   {

      strItem = strModule + "|" + as_string(idPid);
   }


   m_straModule.case_insensitive_add_unique(strItem);

   strModuleList = m_straModule.implode("\n");

   file()->put_text(pathModule,strModuleList);

#endif

}



