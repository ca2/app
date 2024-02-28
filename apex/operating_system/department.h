#pragma once


#include "acme/platform/department.h"
#include "acme/operating_system/exit_status.h"
#include "acme/parallelization/manual_reset_event.h"
#include "apex/parallelization/thread.h"


namespace operating_system
{


   class CLASS_DECL_APEX department:
      public ::acme::department
   {
   public:


      class process_thread :
         virtual public ::thread
      {
      public:

         string                                    m_strCmdLine;
         ::pointer<::operating_system::process>   m_pprocess;
         string *                                  m_pstrRead;
         manual_reset_event *                      m_pevReady;
         class ::time                                m_timeTimeout;
         class ::time                                m_timeStart;
         bool *                                    m_pbInitFailure;
         bool *                                    m_pbPotentialTimeout;
         ::operating_system::exit_status *         m_pexitstatus;
         bool                                      m_bElevated;


         process_thread();


         virtual void construct_process_thread(const ::string & strCmdLine, const class ::time & dur, bool * pbPotentialTimeout = nullptr, string * pstrRead = nullptr, bool bElevated = false);

         virtual void     run() override;

         void run_normal();

         void run_elevated();

         bool retry();

      };


      class process_processor :
         virtual public object
      {
      public:


         manual_reset_event               m_evReady;
         bool                             m_bInitFailure;
         bool                             m_bPotentialTimeout;
         bool *                           m_pbPotentialTimeout;
         ::pointer<process_thread>       m_pthread;
         exit_status                      m_exitstatus;
         bool                             m_bElevated;


         process_processor();
         virtual ~process_processor();
         
         
         void process(const ::string & strCmdLine, const class ::time & dur, bool * pbPotentialTimeout = nullptr, string * pstrRead = nullptr, bool bElevated = false);
         

      };


      department();
      ~department() override;


      void initialize(::particle * pparticle) override;


      // run process and get output
      virtual ::payload get_output(const ::scoped_string & scopedstrCmdLine, const class ::time & dur = ::time::infinity(), e_display edisplay = e_display_default, bool * pbPotentialTimeout = nullptr);
      virtual exit_status retry(const ::scoped_string & scopedstrCmdLine, const class ::time & dur, e_display edisplay = e_display_default, bool * pbPotentialTimeout = nullptr);
      virtual exit_status synch(const ::scoped_string & scopedstrCmdLine, e_display edisplay = e_display_default, const class ::time & dur = ::time::infinity(), bool * pbPotentialTimeout = nullptr);
      virtual bool launch(const ::scoped_string & scopedstrCmdLine, e_display edisplay = e_display_default, const ::scoped_string & scopedstrDir = nullptr);
      virtual exit_status elevated_synch(const ::scoped_string & scopedstrCmdLine, e_display edisplay = e_display_default, const class ::time & dur = ::time::infinity(), bool * pbPotentialTimeout = nullptr);

   };


} // namespace operating_system


