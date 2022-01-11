#include "framework.h"
#include "apex/constant/method.h"
#include "apex/platform/launcher.h"
#include "apex/platform/app_launcher.h"
#include "acme/filesystem/filesystem/acme_dir.h"
#include "acme/filesystem/filesystem/acme_file.h"


interprocess_intercommunication::interprocess_intercommunication() 
{

   m_id = "::interprocess_intercommunication";

   defer_create_mutex();


}


interprocess_intercommunication::~interprocess_intercommunication()
{


}


void interprocess_intercommunication::initialize_interprocess_communication(::object * pobject, const ::string & strApp)
{

   auto estatus = ::object::initialize(pobject);

   if (!estatus)
   {

      return estatus;

   }

   m_strApp = strApp;

#ifdef _UWP

   m_idApp = strApp;

#else

   m_idApp = (::i64) ::get_current_process_id();

#endif

   run_property("on_create");

   call_routines_with_id(CREATE_ROUTINE);

   estatus = __construct(m_prx);

   if (!estatus)
   {

      return estatus;

   }

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

   m_prx->m_preceiver = this;

   string strKey = key(m_strApp, iPid);

   if (!m_prx->create(strKey))
   {

      __throw(error_resource);

   }

   return estatus;

}


void interprocess_intercommunication::destroy()
{

   ::object::destroy();

   if(m_prx)
   {

      m_prx->destroy();

   }

   return ::success;

}



bool interprocess_intercommunication::start(const ::string & strApp)
{

   synchronous_lock sl1(mutex());

   auto & pmutex = m_mapAppMutex[strApp];

   if(pmutex.is_null())
   {

      pmutex = __new(::mutex());

   }

   sl1.unlock();

   synchronous_lock synchronouslock(pmutex);

   auto idaPid = get_pid(strApp);

   if(idaPid.get_count() > 0)
   {

      return true;

   }

   if(strApp == "app-core/clockverse")
   {

      ::output_debug_string("app-core/clockverse");

   }

   auto plauncher = __new(::apex::app_launcher);
   
   plauncher->initialize_app_launcher(this, process_platform_dir_name2(), strApp);

   id idPid = -1;

   {

      auto ida = get_pid(strApp);

      if(ida.is_empty())
      {

         branch_task(plauncher);

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

         return false;

      }

started:

      idPid = ida[0];

   }

   string strKey = strApp + ":" + __string(idPid);

   if(m_txmap[strKey].is_null())
   {

      m_txmap[strKey] = __create < ::interprocess_communication::tx>();

   }

   return m_txmap[strKey]->open(key(strApp,idPid));

}


bool interprocess_intercommunication::connect(const ::string & strApp, const ::id & idPid)
{

   string strKey = strApp + ":" + __string(idPid);

   if(m_txmap[strKey].is_null())
   {

      m_txmap[strKey] = __create<::interprocess_communication::tx>();

   }

   if(m_txmap[strKey]->is_tx_ok())
   {

      return true;

   }
   else
   {

      return m_txmap[strKey]->open(key(strApp, idPid));

   }

}


::interprocess_communication::tx & interprocess_intercommunication::tx(const ::string & strApp, const ::id & iPid)
{

   string strKey = strApp + ":" + __string(iPid);

   if(m_txmap[strKey].is_null())
   {

      m_txmap[strKey] = __create < ::interprocess_communication::tx>();

   }

   if(!m_txmap[strKey]->is_tx_ok())
   {

      connect(strApp, iPid);

   }

   return *m_txmap[strKey];

}


string interprocess_intercommunication::key(const string &strApp, const ::id & idPid)
{

   string strKey;

#ifdef WINDOWS

#ifdef _UWP

   string strAppId(strApp);

   strAppId.replace("\\","-");

   strAppId.replace("/","-");

   strAppId.replace("-","-");

   strKey = strAppId;

#else

   strKey = "::ca2::account::ccwarehouse::" + strApp + ":" + __string(idPid);

#endif

#else

#ifdef LINUX

   strKey = m_psystem->m_pacmedir->system() / "interprocess_intercommunication" / strApp / __string(idPid);

#elif defined(__APPLE__)

   string strAppId(strApp);

   strAppId.replace("\\","-");

   strAppId.replace("/","-");

   strAppId.replace("-","-");

   strKey = "apex-" + strAppId;

#ifdef MACOS

   strKey += "/" + __string(idPid.i32());

#endif

#else

   strKey = m_psystem->m_pacmedir->system() / "interprocess_intercommunication" / strApp / __string(idPid);


#endif

#endif

   return strKey;

}


string interprocess_intercommunication::str_from_va(const payload_array & payloada)
{

   memory_stream stream;

   stream << payloada;

   return stream->get_primitive_memory()->to_hex();

}


void interprocess_intercommunication::on_interprocess_receive(::interprocess_communication::rx * prx, ::string && strMessage)
{

   INFORMATION("::interprocess_intercommunication::on_receive " << strMessage);

   if(!::str::begins_eat(strMessage, "call "))
   {

      return;

   }

   ::i64 iCall = ::str::consume_natural(strMessage);

   if(!::str::begins_eat(strMessage, " from "))
   {

      return;

   }

   string strAppFrom;
   
   strMessage.eat_before(strAppFrom, ":");

   string strAppPid;
   
   strMessage.eat_before(strAppPid, " ");

   if(strAppFrom.is_empty())
   {

      return;

   }

   if (strAppPid.is_empty())
   {

      return;

   }

#if !defined(_UWP)

   auto iPid = atoll(strAppPid);

   if(iPid == 0)
   {

      return;

   }

#endif

   strsize iFind = strMessage.find(":");

   string str1;

   string strObject;

   string strMember;

   string_array stra;

   payload_array payloada;

   if(iFind >= 0 && iFind <= 3)
   {

      return;

   }

   if(iFind > 3)
   {

      str1 = strMessage.Left(iFind);

   }
   else
   {

      str1 = strMessage;

   }

   str1.trim();

   strsize iFind2 = str1.find(".");

   if(iFind2 < 0)
   {

      return;

   }

   strObject = str1.Left(iFind2);

   strMember = str1.Mid(iFind2 + 1);

   if(iFind >= 0)
   {

      str1 = strMessage.Mid(iFind + 1);

      str1.trim();

      memory_stream stream;

      stream->get_primitive_memory()->from_hex(str1);

      stream->seek_to_begin();

      stream.set_loading();

      __io_array(stream, payloada);

   }

   ::payload varRet;

   on_interprocess_call(varRet, strObject, strMember, payloada);

   if(!strMember.begins_ci("reply."))
   {

      auto pcall = create_call(strAppFrom, strObject, "reply." + strMember);

      pcall->add_arg(iCall);

      pcall->add_arg(varRet);

      pcall->set_timeout(1_minute);

      pcall->post(strAppPid);

   }

}


__pointer(interprocess_task) interprocess_intercommunication::create_task(interprocess_call * pcall, const ::id & idPid)
{

   auto pobjectTask = __new(interprocess_task(pcall, idPid, m_iTaskSeed++));

   synchronous_lock synchronouslock(mutex());

   m_mapTask[pobjectTask->m_iTask] = pobjectTask;

   pcall->m_mapTask[pobjectTask->m_iTask] = pobjectTask;

   return pobjectTask;

}


__pointer(interprocess_task) interprocess_intercommunication::get_task(i64 iTask)
{

   synchronous_lock synchronouslock(mutex());

   return m_mapTask[iTask];

}


__pointer(interprocess_call) interprocess_intercommunication::create_call(const ::string & strApp, const ::string & strObject, const ::string & strMember)
{

   return __new(interprocess_call(this, strApp, strObject, strMember));

}


__pointer(interprocess_call) interprocess_intercommunication::create_call(const ::string & strObject, const ::string & strMember)
{

   return create_call(m_strApp, strObject, strMember);

}


void interprocess_intercommunication::on_interprocess_call(::payload & payload, const ::string & strObject, const ::string & strMember, payload_array & payloada)
{

   if(strObject == "application")
   {

      if(::str::begins_ci(strMember, "reply."))
      {

         ::i64 iTask = payloada[0].i64();

         auto pobjectTask = get_task(iTask);

         pobjectTask->m_var = payloada[1];

         pobjectTask->m_pevReady->set_event();

      }
      else if(strMember == "on_additional_local_instance")
      {

         string strModule;
         
         strModule = payloada[0];

         string strCommandLine;

         strCommandLine = payloada[2];

         auto papplication = get_application();

         payload["continue"] = papplication->on_additional_local_instance(
            payload["handled"].as_bool(),
            strModule, 
            payloada[1].i32(), 
            strCommandLine);

      }
      else if (strMember == "on_new_instance")
      {

         on_new_instance(payloada[0], payloada[1]);

      }

   }

}


void interprocess_intercommunication::on_new_instance(const ::string & strModule, const ::id & idPid)
{

   defer_add_module(strModule, idPid);

   get_application()->on_new_instance(strModule, idPid);

}


id_array interprocess_intercommunication::get_pid(const ::string & strApp)
{

   id_array idaPid;

#if defined(LINUX) || defined(MACOS)

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

   pathModule = m_psystem->m_pacmedir->system() / "interprocess_intercommunication";

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


void interprocess_intercommunication::defer_add_module(const ::string & strModule, const ::id & idPid)
{
   
   auto psystem = m_psystem;
   
   auto pnode = psystem->node();

#ifndef _UWP

   ::file::path pathModule;

   m_straModule.erase_all();

   pathModule = m_psystem->m_pacmedir->system() / "interprocess_intercommunication";

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

   m_pcontext->m_papexcontext->file().put_text(pathModule,strModuleList);

#endif

}



