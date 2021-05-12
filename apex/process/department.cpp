#include "framework.h"


void install_sigchld_handler();


namespace process
{


   department::department()
   {

   }


   department::~department()
   {

   }


   ::e_status department::initialize(::object * pobject)
   {

      auto estatus = ::acme::department::initialize(pobject);

      if(!estatus)
      {

         return estatus;

      }

#ifndef WINDOWS

      auto psystem = m_psystem;

      auto pnode = psystem->node();

      pnode->install_sigchld_handler();

#endif

      return estatus;

   }


   ::payload department::get_output(const char * pszCmdLine,const ::duration & dur,::e_display edisplay, bool * pbPotentialTimeout)
   {

      string strRead;

      process_processor proc(pszCmdLine, dur, pbPotentialTimeout, &strRead);

      return strRead;

   }



   exit_status department::retry(const char * pszCmdLine,const ::duration & dur,::e_display edisplay, bool * pbPotentialTimeout)
   {

      process_processor proc(pszCmdLine, dur, pbPotentialTimeout);

      return proc.m_exitstatus;

   }


   exit_status department::synch(const char * pszCmdLine, ::e_display edisplay, const ::duration & dur, bool * pbPotentialTimeout)
   {

      process_processor proc(pszCmdLine, dur, pbPotentialTimeout);

      return proc.m_exitstatus;

   }


   bool department::launch(const char * pszCmdLine,::e_display edisplay, const char * pszDir)
   {

      const char * pszEnd = nullptr;

      string strBin = consume_param(pszCmdLine,&pszEnd);

#ifndef _UWP

      auto estatus = call_async(strBin,pszEnd,pszDir,edisplay, false);

      return ::succeeded(estatus);

#else

      __throw(todo);

#endif

   }


   exit_status department::elevated_synch(const char * pszCmdLine,::e_display edisplay,const ::duration & dur,bool * pbPotentialTimeout)
   {

      process_processor proc(pszCmdLine,dur,pbPotentialTimeout, nullptr, true);

      return proc.m_exitstatus;

   }


   department::process_thread::process_thread()
   {

   }


   void department::process_thread::construct_process_thread(const string & strCmdLine, const ::duration & dur, bool * pbPotentialTimeout, string * pstrRead, bool bElevated)
   {

      //initialize(pobjectParent);

      m_strCmdLine = strCmdLine;
      
      m_pprocess.create();

      m_pstrRead = pstrRead;

      if(dur.is_pos_infinity())
      {

         m_millisTimeout.Null();

      }
      else
      {

         m_millisTimeout = (millis) dur.u32_millis();

      }


      m_pbPotentialTimeout    = pbPotentialTimeout;
      m_pbInitFailure         = nullptr;
      m_bElevated             = bElevated;

   }


   ::e_status     department::process_thread::run()
   {

      if(m_bElevated)
      {

         run_elevated();

      }
      else
      {

         run_normal();

      }

      return ::success;

   }


   void department::process_thread::run_normal()
   {

      if(!m_pprocess->create_child_process(m_strCmdLine,true))
      {

         if(m_pbInitFailure != nullptr)
         {

            *m_pbInitFailure = true;

         }

         if(m_pevReady != nullptr)
         {

            m_pevReady->SetEvent();

         }

         m_result.add(error_failed);

         return;

      }

      m_millisStart.Now();

      string strRead;

      while(!m_pprocess->has_exited())
      {

         strRead = m_pprocess->m_pipe.m_ppipeOut->read();

         if(m_pstrRead != nullptr)
         {

            *m_pstrRead += strRead;

         }

         if(!retry())
         {

            break;

         }

         sleep(100_ms);

      }

      if(m_pexitstatus)
      {

         *m_pexitstatus = m_pprocess->m_exitstatus;

      }

      while(task_get_run())
      {

         strRead = m_pprocess->m_pipe.m_ppipeOut->read();

         if(strRead.is_empty())
         {

            break;

         }
         else
         {

            if(m_pstrRead != nullptr)
            {

               *m_pstrRead += strRead;

            }

         }

      }

      if(m_pevReady != nullptr)
      {

         m_pevReady->SetEvent();

      }

   }


   void department::process_thread::run_elevated()
   {

      m_pprocess->synch_elevated(m_strCmdLine,e_display_none,m_millisTimeout,m_pbPotentialTimeout);

      m_result.add((::e_status    ) m_pprocess->m_exitstatus.m_iExitCode);

      if(m_pexitstatus != nullptr)
      {

         *m_pexitstatus = m_pprocess->m_exitstatus;

      }

      if(m_pevReady != nullptr)
      {

         m_pevReady->SetEvent();

      }

   }


   bool department::process_thread::retry()
   {

      if(m_millisTimeout > 0 && m_millisStart.elapsed() > m_millisTimeout)
      {

         if(m_pbPotentialTimeout != nullptr)
         {

            *m_pbPotentialTimeout = true;

         }

         return false;

      }

      return true;

   }


   department::process_processor::process_processor(const string & strCmdLine,const duration & dur,bool * pbPotentialTimeout,string * pstrRead,bool bElevated)
   {

      m_bInitFailure = false;

      m_bPotentialTimeout = false;

      m_pbPotentialTimeout = pbPotentialTimeout;

      m_bElevated = bElevated;

      m_pthread = new process_thread;

      m_pthread->construct_process_thread(strCmdLine, dur, &m_bPotentialTimeout, pstrRead, bElevated);

      //m_pthread->m_bAutoDelete = true;

      m_pthread->m_pbInitFailure = &m_bInitFailure;

      m_pthread->m_pbPotentialTimeout = &m_bPotentialTimeout;

      m_pthread->m_pevReady = &m_evReady;

      if(m_pthread->m_pexitstatus != nullptr)
      {

         *m_pthread->m_pexitstatus = m_exitstatus;

      }

      //if(dur.is_pos_infinity())
      {

         m_pthread->run();

         m_pthread.release();

      }
//      else
//      {
//
//         m_evReady.ResetEvent();
//
//         m_pthread->begin();
//
//         m_evReady.wait();
//
//      }

   }

   department::process_processor::~process_processor()
   {

      if(m_pbPotentialTimeout != nullptr)
      {

         *m_pbPotentialTimeout = m_bPotentialTimeout;

      }

   }



} // namespace process




