//
// From integration.h by camilo on 2024-03-24 03:25 <3ThomasBorregaardSørensen!!
//
#pragma once



namespace coding
{


   class integration;


   class CLASS_DECL_CODING integration_command :
      virtual public ::particle
   {
   public:


      integration *m_pintegration;
      ::string m_strLabel;
      ::string m_strCommand;
      ::string m_strPlainLabel;

      class ::time m_timeTimeout;

      trace_function m_tracefunction;

      int     m_iStep;
      int    m_iExitCode;
      ::file_pointer m_pfileLog;


      integration_command();
      ~integration_command() override;


      virtual ::string get_step_text();
      virtual ::string get_plain_label();

      void run() override;


   };


} // namespace coding




