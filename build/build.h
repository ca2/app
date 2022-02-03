//
// Created by camilo on 12/12/21 05:08 PM <3ThomasBorregaardSorensen!!
//
#pragma once


namespace app_core_build
{



   class CLASS_DECL_APP_BUILD build :
      virtual public ::thread
   {
   public:


      bool     m_bStdout;
      //__pointer(::user::interaction)      m_puserinteraction;


      build();
      ~build() override;


      virtual void prepare_build();

      virtual void do_build();

      void run() override;


      void write_log(const ::string &str);


      void run_command(const ::string & strCommand);


   };



} // namespace app_build
