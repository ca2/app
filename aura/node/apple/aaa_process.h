#pragma once


namespace apple
{


   class CLASS_DECL_AURA process :
      virtual public ::operating_system::process
   {
   public:


      process();
      virtual ~process();


      virtual bool create_child_process(const ::string & pszCmdLine,bool bPiped, const ::string & pszDir = nullptr, ::enum_priority epriority = ::e_priority_normal) override;

      virtual bool has_exited() override;

      virtual bool synch_elevated(const ::string & pszCmdLine,int iShow,const ::duration & durationTimeOut,bool * pbTimeOut) override;

   };


} // namespace apple



