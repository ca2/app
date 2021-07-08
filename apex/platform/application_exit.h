// Created on 2021-07-08 13:18 BRT <3ThomasBorregaardSørensen!!
#pragma once



class CLASS_DECL_APEX application_exit :
   virtual public object
{
public:


   bool                             m_bProcessingApplicationExitRequest : 1;

   
   application_exit();
   ~application_exit() override;


   virtual ::e_status request_exit_application();
   virtual ::e_status can_exit_application();
   virtual ::e_status exit_application();


};



