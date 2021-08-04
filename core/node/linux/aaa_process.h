#pragma once


namespace ansios
{


   class CLASS_DECL_CORE process :
      virtual public ::process::process
   {
   public:


      process();
      virtual ~process();


      virtual bool create_child_process(const ::string & pszCmdLine,bool bPiped, const ::string & pszDir = nullptr, ::e_priority epriority = ::priority_normal) override;

      virtual bool has_exited() override;

      virtual bool synch_elevated(const ::string & pszCmdLine,int iShow,const ::duration & durationTimeOut,bool * pbTimeOut) override;

   };


} // namespace ansios



