#pragma once


#include "acme/operating_system/bidirectional_pipe.h"
#include "acme/primitive/primitive/object.h"


namespace operating_system
{


   class CLASS_DECL_APEX process :
      virtual public ::object
   {
   public:

      
      ::operating_system::bidirectional_pipe       m_pipe;
      bool                                         m_bPiped;
      int                                          m_iPid;
      ::operating_system::exit_status              m_exitstatus;


      process();
      ~process() override;


      virtual bool create_child_process(const ::string & pszCmdLine, bool bPiped = false, const ::string & pszDir = nullptr, ::enum_priority epriority = ::e_priority_none);

      virtual void wait_until_exit(const class ::wait & wait);
      virtual bool has_exited();

      virtual bool write(const ::string & psz);
      virtual string read(bool bUntilExit = false);

      virtual bool synch_elevated(const ::string & pszCmdLine,int iShow,const ::duration & durationTimeOut,bool * pbTimeOut);

      virtual bool kill();

   };


   typedef ::pointer<process>process_pointer;


} // namespace operating_system



