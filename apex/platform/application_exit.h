// Created on 2021-07-08 13:18 BRT <3ThomasBorregaardS�rensen!!
#pragma once



class CLASS_DECL_APEX application_exit :
   virtual public object
{
public:


   bool                             m_bProcessingApplicationExitRequest : 1;

   
   application_exit();
   ~application_exit() override;


   virtual void request_exit_application();
   virtual void can_exit_application();
   virtual void exit_application();


};



