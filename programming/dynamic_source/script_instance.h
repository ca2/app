#pragma once


namespace dynamic_source
{


   class script;


   class CLASS_DECL_APP_PROGRAMMING script_instance :
      virtual public script_composite
   {
   public:


      u32                                 m_dwCreate;





      script_instance();
      virtual ~script_instance();


      virtual bool ShouldBuild();
      
      
      //void assert_valid(void) const override;
      //void matter::dump(dump_context&) const override;
      //e_status on_initialize_object(void) override;
      //void on_subject(subject::subject*, subject::context*) override;
      //C : \netnode\time - windows\dynamic_source\C\netnodenet\net\system\seed.ds.cpp(76, 33) : error C2385 : ambiguous access of 'get_application'


   };


} // namespace dynamic_source



