#pragma once


namespace process
{


   class CLASS_DECL_AURA process :
      virtual public ::object
   {
   public:


      
      bidi_pipe               m_pipe;
      bool                    m_bPiped;
      int                     m_iPid;
      exit_status             m_exitstatus;


      process();
      virtual ~process();


      virtual bool create_child_process(const char * pszCmdLine, bool bPiped = false, const char * pszDir = nullptr, ::e_priority epriority = ::priority_none);

      virtual void wait_until_exit(i32 iWaitMax = 0);
      virtual bool has_exited();

      virtual bool write(const char * psz);
      virtual string read(bool bUntilExit = false);

      virtual bool synch_elevated(const char * pszCmdLine,int iShow,const ::duration & durationTimeOut,bool * pbTimeOut);

      virtual bool kill();

   };


   typedef __pointer(process) process_pointer;


} // namespace process






















