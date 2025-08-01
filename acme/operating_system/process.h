#pragma once


#include "acme/operating_system/bidirectional_pipe.h"
////#include "acme/prototype/prototype/object.h"
#include "acme/operating_system/exit_status.h"


namespace operating_system
{


   class CLASS_DECL_ACME process :
      virtual public ::object
   {
   public:

      
      ::operating_system::bidirectional_pipe       m_pipe;
      bool                                         m_bPiped;
      int                                          m_iPid;
      ::operating_system::exit_status              m_exitstatus;


      process();
      ~process() override;


      virtual bool create_child_process(const ::scoped_string & scopedstrCmdLine, bool bPiped = false, const ::scoped_string & scopedstrDir = nullptr, ::enum_priority epriority = ::e_priority_none);

      virtual void wait_until_exit(const class time & timeWait);
      virtual bool has_exited();

      virtual bool write(const ::scoped_string & scopedstr);
      virtual string read(bool bUntilExit = false);

      virtual bool synch_elevated(const ::scoped_string & scopedstrCmdLine,int iShow,const class ::time & timeTimeOut,bool * pbTimeOut);

      virtual bool kill();

   };


   typedef ::pointer<process>process_pointer;


} // namespace operating_system



