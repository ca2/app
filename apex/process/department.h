#pragma once


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
         __pointer(::operating_system::process)    m_pprocess;
         string *                                  m_pstrRead;
         manual_reset_event *                      m_pevReady;
         millis                                    m_millisTimeout;
         millis                                    m_millisStart;
         bool *                                    m_pbInitFailure;
         bool *                                    m_pbPotentialTimeout;
         ::operating_system::exit_status *         m_pexitstatus;
         bool                                      m_bElevated;


         process_thread();


         virtual void construct_process_thread(const ::string & strCmdLine, const ::duration & dur, bool * pbPotentialTimeout = nullptr, string * pstrRead = nullptr, bool bElevated = false);

         virtual ::e_status     run() override;

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
         __pointer(process_thread)        m_pthread;
         exit_status                      m_exitstatus;
         bool                             m_bElevated;


         process_processor();
         virtual ~process_processor();
         
         
         ::e_status process(const ::string & strCmdLine, const ::duration & dur, bool * pbPotentialTimeout = nullptr, string * pstrRead = nullptr, bool bElevated = false);
         

      };


      department();
      ~department() override;


      ::e_status initialize(::object * pobject) override;


      // run process and get output
      virtual ::payload get_output(const char * pszCmdLine, const ::duration & dur = ::duration::infinite(), edisplay edisplay = e_display_default, bool * pbPotentialTimeout = nullptr);
      virtual exit_status retry(const char * pszCmdLine, const ::duration & dur, edisplay edisplay = e_display_default, bool * pbPotentialTimeout = nullptr);
      virtual exit_status synch(const char * pszCmdLine, edisplay edisplay = e_display_default, const ::duration & dur = ::duration::infinite(), bool * pbPotentialTimeout = nullptr);
      virtual bool launch(const char * pszCmdLine, edisplay edisplay = e_display_default, const char * pszDir = nullptr);
      virtual exit_status elevated_synch(const char * pszCmdLine, edisplay edisplay = e_display_default, const ::duration & dur = ::duration::infinite(), bool * pbPotentialTimeout = nullptr);

   };


} // namespace operating_system


