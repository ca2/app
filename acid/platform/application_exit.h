// Created on 2021-07-08 13:18 BRT <3ThomasBorregaardSorensen!!
#pragma once


////#include "acid/primitive/primitive/object.h"


class CLASS_DECL_ACID application_exit :
   virtual public object
{
public:


   bool                             m_bProcessingApplicationExitRequest : 1;

   
   application_exit();
   ~application_exit() override;


   virtual void request_exit_application();
   virtual bool can_exit_application();
   virtual void exit_application();


};



