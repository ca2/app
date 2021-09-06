#pragma once



namespace process
{


   struct CLASS_DECL_ACME exit_status
   {


      int      m_iExitCode;
      int      m_iExitSignal;
      int      m_iExitStop;

      exit_status();


   };


   CLASS_DECL_ACME bool set_priority(::enum_priority epriority);

   //CLASS_DECL_ACME string app_id_to_app_name(string strId);


} // namespace process



