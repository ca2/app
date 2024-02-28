#pragma once


namespace ansios
{


   class CLASS_DECL_ACME process :
      virtual public ::operating_system::process
   {
   public:


      process();
      virtual ~process();


      virtual bool create_child_process(const ::scoped_string & scopedstrCmdLine,bool bPiped,const ::scoped_string & scopedstrDir = nullptr, ::enum_priority epriority = ::e_priority_normal) override;

      virtual bool has_exited() override;

      virtual bool synch_elevated(const ::scoped_string & scopedstrCmdLine,int iShow,const ::duration & durationTimeOut,bool * pbTimeOut) override;

   };


} // namespace ansios



