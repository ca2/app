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
   virtual void on_end_procedure();

};


template < typename CONTEXT_TYPE >
class procedure_array_with_context :
   virtual public ::procedure_array
{
public:

   procedure_array_with_context() {}
   procedure_array_with_context(const procedure_array & procedurea) :
      procedure_array(procedurea)
   {

   }
   procedure_array_with_context(procedure_array && procedurea) :
      procedure_array(::transfer(procedurea))
   {

   }


   procedure_array_with_context & operator = (const procedure_array & procedurea)
   {
      ::procedure_array::operator =(procedurea);
      return *this;

   }


   void run() override;


};



