// Created by camilo on 2021-11-05 16:10 PM <3ThomasBorregaardSørensen!!
#pragma once


class CLASS_DECL_APEX api :
   virtual public ::object
{
public:


   api();
   ~api() override;

   
   ::e_status initialize(::object* pobject) override;


   virtual string api_token(bool bForce);


};



