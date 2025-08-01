#include "framework.h"
#include "department.h"
#include "acme/operating_system/process.h"
#include "acme/platform/node.h"
#include "acme/platform/system.h"
#include "acme/prototype/string/command_line.h"


void install_sigchld_handler();


namespace operating_system
{


   department::department()
   {

   }


   department::~department()
   {

   }


   void department::initialize(::particle * pparticle)
   {

      //auto estatus = 
      ::acme::department::initialize(pparticle);

      //if(!estatus)
      //{

      //   return estatus;

      //}

#ifndef WINDOWS

      auto psystem = system();

      auto pnode = psystem->node();

      pnode->install_sigchld_handler();

#endif

      //return estatus;

   }


   ::payload department::get_output(const ::scoped_string & scopedstrCmdLine,const class time & time,::e_display edisplay, bool * pbPotentialTimeout)
   {

      string strRead;
      
      auto pprocessor = __create_new < process_processor >();
      
      pprocessor->process(scopedstrCmdLine, time, pbPotentialTimeout, &strRead);

      return strRead;

   }



   exit_status department::retry(const ::scoped_string & scopedstrCmdLine,const class time & time,::e_display edisplay, bool * pbPotentialTimeout)
   {

      //process_processor proc(scopedstrCmdLine, dur, pbPotentialTimeout);
      
      auto pprocessor = __create_new < process_processor >();
      
      pprocessor->process(scopedstrCmdLine, time, pbPotentialTimeout);

      return pprocessor->m_exitstatus;

   }


   exit_status department::synch(const ::scoped_string & scopedstrCmdLine, ::e_display edisplay, const class time & time, bool * pbPotentialTimeout)
   {

      auto pprocessor = __create_new < process_processor >();
      
      pprocessor->process(scopedstrCmdLine, time, pbPotentialTimeout);

      return pprocessor->m_exitstatus;

   }


   bool department::launch(const ::scoped_string & scopedstrCmdLine,::e_display edisplay, const ::scoped_string & scopedstrDir)
   {

      const_char_pointer pszEnd = nullptr;

      string strBin = consume_command_line_parameter(scopedstrCmdLine,&pszEnd);

#ifndef UNIVERSAL_WINDOWS

      auto psystem = system();

      auto pnode = psystem->node();

      //auto estatus =
      pnode->call_async(strBin,pszEnd, scopedstrDir,edisplay, false);

      //return ::succeeded(estatus);

#else

      throw ::exception(todo);

#endif

      return false;

   }


   exit_status department::elevated_synch(const ::scoped_string & scopedstrCmdLine,::e_display edisplay,const class time & time,bool * pbPotentialTimeout)
   {

//      process_processor proc(scopedstrCmdLine,dur,pbPotentialTimeout, nullptr, true);
//
//      return proc.m_exitstatus;
      
      auto pprocessor = __create_new < process_processor >();
      
      pprocessor->process(scopedstrCmdLine, time, pbPotentialTimeout, nullptr, true);

      return pprocessor->m_exitstatus;

   }


   department::process_thread::process_thread()
   {

   }


   void department::process_thread::construct_process_thread(const ::scoped_string & scopedstrCmdLine, const class time & time, bool * pbPotentialTimeout, string * pstrRead, bool bElevated)
   {

      //initialize(pobjectParent);

      m_strCmdLine = scopedstrCmdLine;
      
      __øconstruct(m_pprocess);

      m_pstrRead = pstrRead;

      if(time.is_infinite())
      {

         m_timeTimeout = 0_s;

      }
      else
      {

         m_timeTimeout = time;

      }


      m_pbPotentialTimeout    = pbPotentialTimeout;
      m_pbInitFailure         = nullptr;
      m_bElevated             = bElevated;

   }


   void department::process_thread::run()
   {

      if(m_bElevated)
      {

         run_elevated();

      }
      else
      {

         run_normal();

      }

      //return ::success;

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

            m_pevReady->set_happening();

         }

         //m_result.add(error_failed);

         return;

      }

      m_timeStart.Now();

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

         m_pevReady->set_happening();

      }

   }


   void department::process_thread::run_elevated()
   {

      m_pprocess->synch_elevated(m_strCmdLine,e_display_none,m_timeTimeout,m_pbPotentialTimeout);

      ///m_result.add((void    ) m_pprocess->m_exitstatus.m_iExitCode);

      if(m_pexitstatus != nullptr)
      {

         *m_pexitstatus = m_pprocess->m_exitstatus;

      }

      if(m_pevReady != nullptr)
      {

         m_pevReady->set_happening();

      }

   }


   bool department::process_thread::retry()
   {

      if(m_timeTimeout > 0_s && m_timeStart.elapsed() > m_timeTimeout)
      {

         if(m_pbPotentialTimeout != nullptr)
         {

            *m_pbPotentialTimeout = true;

         }

         return false;

      }

      return true;

   }


   department::process_processor::process_processor()
   {
    
      m_bInitFailure = false;

      m_bPotentialTimeout = false;

      m_pbPotentialTimeout = nullptr;

      m_bElevated = false;
      
   }


   department::process_processor::~process_processor()
   {

      if(m_pbPotentialTimeout != nullptr)
      {

         *m_pbPotentialTimeout = m_bPotentialTimeout;

      }

   }


   void department::process_processor::process(const ::scoped_string & scopedstrCmdLine,const class time & dur,bool * pbPotentialTimeout,string * pstrRead,bool bElevated)
   {

      m_pbPotentialTimeout = pbPotentialTimeout;

      m_bElevated = bElevated;

      m_pthread = __create_new < process_thread > ();

      m_pthread->construct_process_thread(scopedstrCmdLine, dur, &m_bPotentialTimeout, pstrRead, bElevated);

      //m_pthread->m_bAutoDelete = true;

      m_pthread->m_pbInitFailure = &m_bInitFailure;

      m_pthread->m_pbPotentialTimeout = &m_bPotentialTimeout;

      m_pthread->m_pevReady = &m_happeningReady;

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
   //         m_happeningReady.reset_happening();
   //
   //         m_pthread->begin();
   //
   //         m_happeningReady.wait();
   //
   //      }

      //return ::success;

   }


} // namespace operating_system




