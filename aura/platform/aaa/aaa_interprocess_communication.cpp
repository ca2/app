#include "framework.h"
#include "aura/const/procedure.h"


namespace aura
{



   inteprocess_channel::task::task(class call * pcall, const ::atom & idPid, i64 iTask) :
         ::object(pcall),
         m_pcall(pcall),
         m_atomPid(idPid),
         m_pevReady(__new(manual_reset_event)),
         m_iTask(iTask)
   {

   }


   inteprocess_channel::task::~task()
   {

   }


   void inteprocess_channel::task::do_task(const ::string & strObject, const ::string & strMember, const payload_array & payloada)
   {

      ::aura::ipc::tx & txc = m_pcall->m_pinterprocesscommunication->tx(m_pcall->m_strApp, m_atomPid);

      string strVara = m_pcall->m_pinterprocesscommunication->str_from_va(payloada);

      m_iTask = atomic_increment(&m_pcall->m_pinterprocesscommunication->m_iTaskSeed);

      string strSource;

      string strPid = as_string(m_pcall->m_pinterprocesscommunication->m_atomApp);

      strSource.format(" from %s:%s ", m_pcall->m_pinterprocesscommunication->m_strApp.c_str(), strPid.c_str());

      string str = "call " + as_string(m_iTask) + strSource + strObject + "." + strMember + ": " + strVara;

      bool bSendOk = txc.send(str, m_pcall->m_duration);

      if (!bSendOk)
      {

         m_var = false;

         m_pevReady->set_event();

      }
      else if (strMember.case_insensitive_begins("reply."))
      {

         m_var = true;

         m_pevReady->set_event();

      }

   }


   inteprocess_channel::call::call(inteprocess_channel * pipi, const ::string & strApp, const ::string & strObject, const ::string & strMember) :
      ::object(pipi),
      m_pinterprocesscommunication(pipi),
      m_strApp(strApp),
      m_strObject(strObject),
      m_strMember(strMember),
      m_bAutoLaunch(false)
   {

      m_duration = one_minute();

   }


   inteprocess_channel::call::~call()
   {

   }


   void inteprocess_channel::call::add_arg(const ::payload & payload)
   {

      m_varaArgs.add(payload);

   }


   void inteprocess_channel::call::add_args(const payload_array & payloada)
   {

      ::papaya::array::add(m_varaArgs, payloada);

   }


   void inteprocess_channel::call::set_timeout(const duration & duration)
   {

      m_duration = duration;

   }


   void inteprocess_channel::call::set_auto_launch(bool bSet)
   {

      m_bAutoLaunch = bSet;

   }


   bool inteprocess_channel::call::is_auto_launch() const
   {

      return m_bAutoLaunch;

   }


   void inteprocess_channel::call::exclude_this_app()
   {

      m_iaExclude.add(pcontext->m_papexcontext->os().get_pid());

   }


   void inteprocess_channel::call::post(const ::atom & idPid)
   {

      fork([this, idPid]()
      {

         auto & pobjectTask = m_mapTask[idPid];

         if (pobjectTask)
         {

            return;

         }

         pobjectTask = m_pinterprocesscommunication->create_task(this, idPid);

         pobjectTask->do_task(m_strObject, m_strMember, m_varaArgs);

      });

   }


   ::pointer<synchronization_array>inteprocess_channel::call::synca()
   {

      auto psynca = __new(synchronization_array);

      for (auto & task : this->tasks())
      {

         psynca->add(task.m_pevReady);

      }

      return psynca;

   }


   ::synchronization_result inteprocess_channel::call::wait()
   {

      auto psynca = synca();

      synchronous_lock synchronouslock(psynca);

      return synchronouslock.wait(m_duration);

   }


   void inteprocess_channel::call::announce()
   {

      exclude_this_app();

      auto iaPid = m_pinterprocesscommunication->get_pid(m_strApp);

      if (iaPid.is_empty())
      {

         if (!is_auto_launch())
         {

            return;

         }

         m_pinterprocesscommunication->start(m_strApp);

         iaPid = m_pinterprocesscommunication->get_pid(m_strApp);

      }

      iaPid -= m_iaExclude;

      for (auto & idPid : iaPid)
      {

         post(idPid);

      }

   }


   inteprocess_channel::inteprocess_channel(const ::string & strApp) :
      m_strApp(strApp)
   {

      m_iTaskSeed = 0;

      m_atom = "::interprocess::communication";

      defer_create_synchronization();

#ifdef UNIVERSAL_WINDOWS

      m_atomApp = strApp;

#else

      m_atomApp = (::i64) ::get_current_process_id();

#endif

   }


   inteprocess_channel::~inteprocess_channel()
   {


   }


   void inteprocess_channel::initialize(::particle * pparticle)
   {

      auto estatus = ::object::initialize(pparticle);

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

      //defer_add_module(pcontext->m_papexcontext->file()->module(), iPid);

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

      if (!m_prx->create(strKey))
      {

         throw ::exception(::resource_exception());

      }



      return estatus;

   }


   void inteprocess_channel::destroy()
   {

      ::object::destroy();

      m_prx->destroy();

   }



   bool inteprocess_channel::start(const ::string & strApp)
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

         return true;

      }

      ::aura::app_launcher launcher(process_platform_name(), strApp);

      atom idPid = -1;

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

      string strKey = strApp + ":" + as_string(idPid);

      if(m_txmap[strKey].is_null())
      {

         m_txmap[strKey] = __new(::aura::ipc::tx);

      }

      return m_txmap[strKey]->open(key(strApp,idPid));

   }


   bool inteprocess_channel::connect(const ::string & strApp, const ::atom & idPid)
   {

      string strKey = strApp + ":" + as_string(idPid);

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


   ::aura::ipc::tx & inteprocess_channel::caller(const ::string & strApp, const ::atom & iPid)
   {

      string strKey = strApp + ":" + as_string(iPid);

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


   string inteprocess_channel::key(const string &strApp, const ::atom & idPid)
   {

      string strKey;

#ifdef WINDOWS

#ifdef UNIVERSAL_WINDOWS

      string strAppId(strApp);

      strAppId.replace("\\","-");

      strAppId.replace("/","-");

      strAppId.replace("-","-");

      strKey = strAppId;

#else

      strKey = "::ca2::account::ccwarehouse::" + strApp + ":" + as_string(idPid);

#endif

#else

#ifdef LINUX

      strKey =          auto psystem = acmesystem();

         auto pacmedirectory = psystem->m_pacmedirectory;

pacmedirectory->system() / "inteprocess_channel" / strApp / as_string(idPid);

#elif defined(__APPLE__)

      string strAppId(strApp);

      strAppId.replace("\\","-");

      strAppId.replace("/","-");

      strAppId.replace("-","-");

      strKey = "aura-" + strAppId;

#ifdef MACOS

      strKey += "/" + as_string(idPid.i32());

#endif

#else

      strKey =          auto psystem = acmesystem();

         auto pacmedirectory = psystem->m_pacmedirectory;

pacmedirectory->system() / "inteprocess_channel" / strApp / as_string(idPid);


#endif

#endif

      return strKey;

   }


   string inteprocess_channel::str_from_va(const payload_array & payloada)
   {

      memory_stream stream;

      stream << payloada;

      return stream->get_primitive_memory()->to_hex();

   }


   void inteprocess_channel::on_ipc_receive(::aura::ipc::rx * prx, const ::string & pszMessage)
   {

      string str(pszMessage);

      FORMATTED_INFORMATION("interprocess_intercommunication::on_receive %s", pszMessage);

      if(!str.begins_eat("call "))
      {

         return;

      }

      ::i64 iCall = ::str::consume_natural(str);

      if(!str.begins_eat(" from "))
      {

         return;

      }

      string strFrom = ::str::consume_non_spaces(str);

      string strAppFrom = ::str::token(strFrom, ":");

      if(strAppFrom.is_empty())
      {

         return;

      }

      ::atom idPidFrom = strFrom;

      if(idPidFrom.is_empty() || (idPidFrom.is_integer() && idPidFrom.i64() == 0))
      {

         return;

      }

      auto pFind = str.find(":");

      string str1;

      string strObject;

      string strMember;

      string_array stra;

      payload_array payloada;

      if(::is_set(pFind) && iFind <= 3)
      {

         return;

      }

      if(iFind > 3)
      {

         str1 = str(0, pFind);

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

      strObject = str1.left(iFind2);

      strMember = str1.substr(iFind2 + 1);

      if(::is_set(pFind))
      {

         str1 = str(pFind + 1);

         str1.trim();

         memory_stream stream;

         stream->get_primitive_memory()->from_hex(str1);

         stream->seek_to_begin();

         stream.set_loading();

         __io_array(stream, payloada);

      }

      ::payload varRet;

      on_interprocess_call(varRet, strObject, strMember, payloada);

      if(!strMember.case_insensitive_begins("reply."))
      {

         auto pcall = create_call(strAppFrom, strObject, "reply." + strMember);

         pcall->add_arg(iCall);

         pcall->add_arg(varRet);

         pcall->set_timeout(1_min);

         pcall->post(idPidFrom);

      }

   }


   ::pointer<class inteprocess_channel::task> inteprocess_channel::create_task(call * pcall, const ::atom & idPid)
   {

      auto pobjectTask = __new(class task(pcall, idPid, atomic_increment(&m_iTaskSeed)));

      synchronous_lock synchronouslock(this->synchronization());

      m_mapTask[pobjectTask->m_iTask] = pobjectTask;

      pcall->m_mapTask[pobjectTask->m_iTask] = pobjectTask;

      return pobjectTask;

   }


   ::pointer<class inteprocess_channel::task> inteprocess_channel::get_task(i64 iTask)
   {

      synchronous_lock synchronouslock(this->synchronization());

      return m_mapTask[iTask];

   }


   ::pointer<class inteprocess_channel::call> inteprocess_channel::create_call(const ::string & strApp, const ::string & strObject, const ::string & strMember)
   {

      return __new(class call(this, strApp, strObject, strMember));

   }


   ::pointer<class inteprocess_channel::call> inteprocess_channel::create_call(const ::string & strObject, const ::string & strMember)
   {

      return create_call(m_strApp, strObject, strMember);

   }


   void inteprocess_channel::on_interprocess_call(::payload & payload, const ::string & strObject, const ::string & strMember, payload_array & payloada)
   {

      if(strObject == "application")
      {

         if(string_begins_ci(strMember, "reply."))
         {

            ::i64 iTask = payloada[0].i64();

            auto pobjectTask = get_task(iTask);

            pobjectTask->m_var = payloada[1];

            pobjectTask->m_pevReady->set_event();

         }
         else if(strMember == "on_additional_local_instance")
         {

            payload["continue"] = papp->on_additional_local_instance(payload["handled"], payloada[0], payloada[1], payloada[2]);

         }
         else if (strMember == "on_new_instance")
         {

            on_new_instance(payloada[0], payloada[1]);

         }

      }

   }


   void inteprocess_channel::on_new_instance(const ::string & strModule, const ::atom & idPid)
   {

      defer_add_module(strModule, idPid);

      papp->on_new_instance(strModule, idPid);

   }


   atom_array inteprocess_channel::get_pid(const ::string & strApp)
   {

      atom_array idaPid;

#if defined(LINUX) || defined(MACOS)


      idaPid = app_get_pid(strApp);


#else

#if defined(UNIVERSAL_WINDOWS)

      idaPid.add(strApp);

#else

      string_array stra;

      ::file::path pathModule;

      pathModule = pacmedirectory->system() / "inteprocess_channel";

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

      for (auto & str : stra)
      {

         if (str.has_char())
         {

            string_array a;

            a.explode("|", str);

            if (a.get_size() >= 2)
            {

               stra2.case_insensitive_add_unique(a[0]);

               string strPath = module_path_from_pid(ansi_to_i32(a[1]));

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


   void inteprocess_channel::defer_add_module(const ::string & strModule, const ::atom & idPid)
   {

#ifndef UNIVERSAL_WINDOWS

      ::file::path pathModule;

      m_straModule.erase_all();

      pathModule = pacmedirectory->system() / "inteprocess_channel";

      pathModule /= m_strApp + ".module_list";

      ::file::path pathPid = module_path_from_pid((::u32)idPid.i64());

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

               string strPath = module_path_from_pid(ansi_to_i32(a[1]));

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

      ::file::path pathThisModule = pcontext->m_papexcontext->file()->module();

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

      pcontext->m_papexcontext->file()->put_contents(pathModule,strModuleList);

#endif

   }

} // namespace aura


