#pragma once


namespace apple
{


   class CLASS_DECL_ACME process :
      virtual public ::operating_system::process
   {
   public:


      process();
      virtual ~process();


      virtual bool create_child_process(const char * pszCmdLine,bool bPiped,const char * pszDir = nullptr, ::enum_priority epriority = ::e_priority_normal) override;

      virtual bool has_exited() override;

      virtual bool synch_elevated(const char * pszCmdLine,int iShow,const ::duration & durationTimeOut,bool * pbTimeOut) override;

   };


} // namespace apple



