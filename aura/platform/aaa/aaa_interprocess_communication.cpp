#include "framework.h"
#include "aura/const/procedure.h"


namespace aura
{



   interprocess_communication::task::task(class call * pcall, const ::id & idPid, i64 iTask) :
         ::object(pcall),
         m_pcall(pcall),
         m_idPid(idPid),
         m_pevReady(__new(manual_reset_event)),
         m_iTask(iTask)
   {

   }


   interprocess_communication::task::~task()
   {

   }


   void interprocess_communication::task::do_task(const string & strObject, const string & strMember, const var_array & vara)
   {

      ::aura::ipc::tx & txc = m_pcall->m_pinterprocessintercommunication->tx(m_pcall->m_strApp, m_idPid);

      string strVara = m_pcall->m_pinterprocessintercommunication->str_from_va(vara);

      m_iTask = atomic_increment(&m_pcall->m_pinterprocessintercommunication->m_iTaskSeed);

      string strSource;

      string strPid = __str(m_pcall->m_pinterprocessintercommunication->m_idApp);

      strSource.Format(" from %s:%s ", m_pcall->m_pinterprocessintercommunication->m_strApp.c_str(), strPid.c_str());

      string str = "call " + __str(m_iTask) + strSource + strObject + "." + strMember + ": " + strVara;

      bool bSendOk = txc.send(str, m_pcall->m_duration);

      if (!bSendOk)
      {

         m_var = false;

         m_pevReady->set_event();

      }
      else if (strMember.begins_ci("reply."))
      {

         m_var = true;

         m_pevReady->set_event();

      }

   }


   interprocess_communication::call::call(interprocess_communication * pipi, const string & strApp, const string & strObject, const string & strMember) :
      ::object(pipi),
      m_pinterprocessintercommunication(pipi),
      m_strApp(strApp),
      m_strObject(strObject),
      m_strMember(strMember),
      m_bAutoLaunch(false)
   {

      m_duration = one_minute();

   }


   interprocess_communication::call::~call()
   {

   }


   void interprocess_communication::call::add_arg(const ::payload & payload)
   {

      m_varaArgs.add(payload);

   }


   void interprocess_communication::call::add_args(const var_array & vara)
   {

      ::papaya::array::add(m_varaArgs, vara);

   }


   void interprocess_communication::call::set_timeout(const duration & duration)
   {

      m_duration = duration;

   }


   void interprocess_communication::call::set_auto_launch(bool bSet)
   {

      m_bAutoLaunch = bSet;

   }


   bool interprocess_communication::call::is_auto_launch() const
   {

      return m_bAutoLaunch;

   }


   void interprocess_communication::call::exclude_this_app()
   {

      m_iaExclude.add(pcontext->m_papexcontext->os().get_pid());

   }


   void interprocess_communication::call::post(const ::id & idPid)
   {

      fork([this, idPid]()
      {

         auto & pobjectTask = m_mapTask[idPid];

         if (pobjectTask)
         {

            return;

         }

         pobjectTask = m_pinterprocessintercommunication->create_task(this, idPid);

         pobjectTask->do_task(m_strObject, m_strMember, m_varaArgs);

      });

   }


   __pointer(synchronization_array) interprocess_communication::call::synca()
   {

      auto psynca = __new(synchronization_array);

      for (auto & task : this->tasks())
      {

         psynca->add(task.m_pevReady);

      }

      return psynca;

   }


   ::synchronization_result interprocess_communication::call::wait()
   {

      auto psynca = synca();

      synchronous_lock synchronouslock(psynca);

      return synchronouslock.wait(m_duration);

   }


   void interprocess_communication::call::announce()
   {

      exclude_this_app();

      auto iaPid = m_pinterprocessintercommunication->get_pid(m_strApp);

      if (iaPid.is_empty())
      {

         if (!is_auto_launch())
         {

            return;

         }

         m_pinterprocessintercommunication->start(m_strApp);

         iaPid = m_pinterprocessintercommunication->get_pid(m_strApp);

      }

      iaPid -= m_iaExclude;

      for (auto & idPid : iaPid)
      {

         post(idPid);

      }

   }


   interprocess_communication::interprocess_communication(const string & strApp) :
      m_strApp(strApp)
   {

      m_iTaskSeed = 0;

      m_id = "::interprocess_intercommunication";

      defer_create_mutex();

#ifdef _UWP

      m_idApp = strApp;

#else

      m_idApp = (::i64) ::get_current_process_id();

#endif

   }


   interprocess_communication::~interprocess_communication()
   {


   }


   ::e_status interprocess_communication::initialize(::object * pobject)
   {

      auto estatus = ::object::initialize(pobject);

      if (!estatus)
      {

         return estatus;

      }

      run_property("on_create");

      runall(CREATE_ROUTINE);

      estatus = __construct_new(m_prx);

      if (!estatus)
      {

         return estatus;

      }

      int iPid = pcontext->m_papexcontext->os().get_pid();

      //defer_add_module(pcontext->m_papexcontext->file().module(), iPid);

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

         __throw(::resource_exception());

      }



      return estatus;

   }


   ::e_status interprocess_communication::finalize()
   {

      ::object::finalize();

      m_prx->finalize();

   }



   bool interprocess_communication::start(const string & strApp)
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

      ::aura::app_launcher launcher(process_platform_dir_name2(), strApp);

      id idPid = -1;

      {

         auto ida = get_pid(strApp);

         if(ida.is_empty())
         {

            launcher.start();

            int iStep = 0;

            int iSubStep;

            while(iStep < 8 && ::task_get_run())
            {

               iStep++;

               ida = get_pid(strApp);

               if(ida.has_element())
               {

                  goto started;

               }

               for(iSubStep = 0; (iSubStep < (iStep + 1) * 10) && ::task_get_run(); iSubStep++)
               {

                  sleep(100_ms);

               }

            }

            return false;

         }

started:

         idPid = ida[0];

      }

      string strKey = strApp + ":" + __str(idPid);

      if(m_txmap[strKey].is_null())
      {

         m_txmap[strKey] = __new(::aura::ipc::tx);

      }

      return m_txmap[strKey]->open(key(strApp,idPid));

   }


   bool interprocess_communication::connect(const string & strApp, const ::id & idPid)
   {

      string strKey = strApp + ":" + __str(idPid);

      if(m_txmap[strKey].is_null())
      {

         m_txmap[strKey] = __new(::aura::ipc::tx);

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


   ::aura::ipc::tx & interprocess_communication::tx(const string & strApp, const ::id & iPid)
   {

      string strKey = strApp + ":" + __str(iPid);

      if(m_txmap[strKey].is_null())
      {

         m_txmap[strKey] = __new(::aura::ipc::tx);

      }

      if(!m_txmap[strKey]->is_tx_ok())
      {

         connect(strApp, iPid);

      }

      return *m_txmap[strKey];

   }


   string interprocess_communication::key(const string &strApp, const ::id & idPid)
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

      strKey = "::ca2::account::ccwarehouse::" + strApp + ":" + __str(idPid);

#endif

#else

#ifdef LINUX

      strKey = pacmedir->system() / "interprocess_communication" / strApp / __str(idPid);

#elif defined(__APPLE__)

      string strAppId(strApp);

      strAppId.replace("\\","-");

      strAppId.replace("/","-");

      strAppId.replace("-","-");

      strKey = "aura-" + strAppId;

#ifdef MACOS

      strKey += "/" + __str(idPid.i32());

#endif

#else

      strKey = pacmedir->system() / "interprocess_communication" / strApp / __str(idPid);


#endif

#endif

      return strKey;

   }


   string interprocess_communication::str_from_va(const var_array & vara)
   {

      memory_stream stream;

      stream << vara;

      return stream->get_primitive_memory()->to_hex();

   }


   void interprocess_communication::on_ipc_receive(::aura::ipc::rx * prx, const char * pszMessage)
   {

      string str(pszMessage);

      INFO("interprocess_intercommunication::on_receive %s", pszMessage);

      if(!::str::begins_eat(str, "call "))
      {

         return;

      }

      ::i64 iCall = ::str::consume_natural(str);

      if(!::str::begins_eat(str, " from "))
      {

         return;

      }

      string strFrom = ::str::consume_non_spaces(str);

      string strAppFrom = ::str::token(strFrom, ":");

      if(strAppFrom.is_empty())
      {

         return;

      }

      ::id idPidFrom = strFrom;

      if(idPidFrom.is_empty() || (idPidFrom.is_integer() && idPidFrom.i64() == 0))
      {

         return;

      }

      strsize iFind = str.find(":");

      string str1;

      string strObject;

      string strMember;

      string_array stra;

      var_array vara;

      if(iFind >= 0 && iFind <= 3)
      {

         return;

      }

      if(iFind > 3)
      {

         str1 = str.Left(iFind);

      }
      else
      {

         str1 = str;

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

         str1 = str.Mid(iFind + 1);

         str1.trim();

         memory_stream stream;

         stream->get_primitive_memory()->from_hex(str1);

         stream->seek_to_begin();

         stream.set_loading();

         __io_array(stream, vara);

      }

      ::payload varRet;

      on_interprocess_call(varRet, strObject, strMember, vara);

      if(!strMember.begins_ci("reply."))
      {

         auto pcall = create_call(strAppFrom, strObject, "reply." + strMember);

         pcall->add_arg(iCall);

         pcall->add_arg(varRet);

         pcall->set_timeout(1_min);

         pcall->post(idPidFrom);

      }

   }


   __pointer(class interprocess_communication::task) interprocess_communication::create_task(call * pcall, const ::id & idPid)
   {

      auto pobjectTask = __new(class task(pcall, idPid, atomic_increment(&m_iTaskSeed)));

      synchronous_lock synchronouslock(mutex());

      m_mapTask[pobjectTask->m_iTask] = pobjectTask;

      pcall->m_mapTask[pobjectTask->m_iTask] = pobjectTask;

      return pobjectTask;

   }


   __pointer(class interprocess_communication::task) interprocess_communication::get_task(i64 iTask)
   {

      synchronous_lock synchronouslock(mutex());

      return m_mapTask[iTask];

   }


   __pointer(class interprocess_communication::call) interprocess_communication::create_call(const string & strApp, const string & strObject, const string & strMember)
   {

      return __new(class call(this, strApp, strObject, strMember));

   }


   __pointer(class interprocess_communication::call) interprocess_communication::create_call(const string & strObject, const string & strMember)
   {

      return create_call(m_strApp, strObject, strMember);

   }


   void interprocess_communication::on_interprocess_call(::payload & payload, const string & strObject, const string & strMember, var_array & vara)
   {

      if(strObject == "application")
      {

         if(::str::begins_ci(strMember, "reply."))
         {

            ::i64 iTask = vara[0].i64();

            auto pobjectTask = get_task(iTask);

            pobjectTask->m_var = vara[1];

            pobjectTask->m_pevReady->set_event();

         }
         else if(strMember == "on_additional_local_instance")
         {

            payload["continue"] = papplication->on_additional_local_instance(payload["handled"], vara[0], vara[1], vara[2]);

         }
         else if (strMember == "on_new_instance")
         {

            on_new_instance(vara[0], vara[1]);

         }

      }

   }


   void interprocess_communication::on_new_instance(const string & strModule, const ::id & idPid)
   {

      defer_add_module(strModule, idPid);

      papplication->on_new_instance(strModule, idPid);

   }


   id_array interprocess_communication::get_pid(const string & strApp)
   {

      id_array idaPid;

#if defined(LINUX) || defined(MACOS)


      idaPid = app_get_pid(strApp);


#else

#if defined(_UWP)

      idaPid.add(strApp);

#else

      string_array stra;

      ::file::path pathModule;

      pathModule = pacmedir->system() / "interprocess_communication";

      pathModule /= strApp + ".module_list";

      string strModuleList = file_as_string(pathModule);

      stra.add_lines(strModuleList);

repeat:

      if (stra.get_count() > 32)
      {

         stra.remove_at(0, 16);

      }

      string_array stra2;

      int_array iaPid2;

      for (auto & str : stra)
      {

         if (str.has_char())
         {

            string_array a;

            a.explode("|", str);

            if (a.get_size() >= 2)
            {

               stra2.add_unique_ci(a[0]);

               string strPath = module_path_from_pid(ansi_to_i32(a[1]));

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


   void interprocess_communication::defer_add_module(const string & strModule, const ::id & idPid)
   {

#ifndef _UWP

      ::file::path pathModule;

      m_straModule.remove_all();

      pathModule = pacmedir->system() / "interprocess_communication";

      pathModule /= m_strApp + ".module_list";

      ::file::path pathPid = module_path_from_pid((::u32)idPid.i64());

      string strModuleList = file_as_string(pathModule);

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

               string strPath = module_path_from_pid(ansi_to_i32(a[1]));

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

            m_straModule.remove_at(i);

         }

      }

      string_array straUnique;

      forallref(m_straModule)
      {

         straUnique.add_unique_ci(item);

      }

      m_straModule = straUnique;

      ::file::path pathThisModule = pcontext->m_papexcontext->file().module();

      string strItem;

      if (pathPid.has_char())
      {

         strItem = pathPid + "|" + __str(idPid);

      }
      else
      {

         strItem = strModule + "|" + __str(idPid);
      }


      m_straModule.add_unique_ci(strItem);

      strModuleList = m_straModule.implode("\n");

      pcontext->m_papexcontext->file().put_contents(pathModule,strModuleList);

#endif

   }

} // namespace aura


