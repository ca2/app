#pragma once


namespace process
{


   class CLASS_DECL_APEX process :
      virtual public ::object
   {
   public:


      
      ::process::bidirectional_pipe       m_pipe;
      bool                                m_bPiped;
      int                                 m_iPid;
      ::process::exit_status              m_exitstatus;


      process();
      ~process() override;


      virtual bool create_child_process(const ::string & pszCmdLine, bool bPiped = false, const ::string & pszDir = nullptr, ::e_priority epriority = ::priority_none);

      virtual void wait_until_exit(i32 iWaitMax = 0);
      virtual bool has_exited();

      virtual bool write(const ::string & psz);
      virtual string read(bool bUntilExit = false);

      virtual bool synch_elevated(const ::string & pszCmdLine,int iShow,const ::duration & durationTimeOut,bool * pbTimeOut);

      virtual bool kill();

   };


   typedef __pointer(process) process_pointer;


} // namespace process






















