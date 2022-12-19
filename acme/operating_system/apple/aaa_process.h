#pragma once


namespace apple
{


   class CLASS_DECL_ACME process :
      virtual public ::operating_system::process
   {
   public:


      process();
      virtual ~process();


      virtual bool create_child_process(const scoped_string & strCmdLine,bool bPiped,const scoped_string & strDir = nullptr, ::enum_priority epriority = ::e_priority_normal) override;

      virtual bool has_exited() override;

      virtual bool synch_elevated(const scoped_string & strCmdLine,int iShow,const ::duration & durationTimeOut,bool * pbTimeOut) override;

   };


} // namespace apple



