#pragma once


#include "script_composite.h"
#include "acme/_information_n.h"


namespace dynamic_source
{


   class CLASS_DECL_APP_PROGRAMMING script_instance :
      virtual public script_composite
   {
   public:


      class ::time                  m_timeCreate;

      item_n40585                   m_itemN40585;
      //class ::time               m_timeCreate;
      //class ::time               m_timeLockElapsed;
      //class ::time               m_timeLookUpElapsed;
      //class ::time               m_timeLock2Elapsed;
      //class ::time               m_timeShouldBuildElapsed;


      script_instance();
      ~script_instance() override;


      virtual bool ShouldBuild();
      
      
      //void assert_ok(void) const override;
      //void matter::dump(dump_context&) const override;
      //e_status on_initialize_particle(void) override;
      //void on_subject(topic::topic*, topic::handler_context*) override;
      //C : \netnode\time - windows\dynamic_source\C\netnodenet\net\system\seed.ds.cpp(76, 33) : error C2385 : ambiguous access of 'get_app'


   };


} // namespace dynamic_source



