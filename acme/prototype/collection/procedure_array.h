// Created by camilo on 2024-10-08 23:31 <3ThomasBorregaardSorensen!!
#pragma once


class CLASS_DECL_ACME procedure_array :
   virtual public ::comparable_array < ::procedure >
{
public:

   procedure_array();
   procedure_array(const procedure_array & procedurea);
   procedure_array(procedure_array && procedurea);


   procedure_array & operator = (const procedure_array & procedurea);


   void run() override;


};
