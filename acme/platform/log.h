// Created by camilo on 2021-07-17 23:24 BRT <3ThomasBorregaardSørensen!!
#pragma once


namespace trace
{


   class CLASS_DECL_ACME log :
      virtual public ::object
   {
   public:


      bool                       m_bLog : 1;
      bool                       m_bExtendedLog : 1;
      bool                       m_bLogFileName : 1;
      bool                       m_bLogFunctionName : 1;
      bool                       m_bLogThreadName : 1;


      log();
      ~log() override;


      ::e_status initialize(::object* pobject) override;
      

      virtual ::e_status initialize_log(enum_trace_level etracelevelMin, const ::id& id);


      virtual void print(const char* pszFormat, ...);
      virtual void print_v(const char* pszFormat, va_list valist);

      
      virtual ::e_status process_init();

      virtual void set_extended_log(bool bSet = true);
      virtual bool get_extended_log();

   };


} // namespace trace



