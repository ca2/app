// Created by camilo on 2024-10-08 23:31 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/prototype/prototype/function.h"
#include "acme/prototype/collection/array_base.h"
#include "acme/prototype/collection/comparable_eq_array.h"
#include "acme/prototype/collection/comparable_array.h"


class CLASS_DECL_ACME procedure_array : 
   virtual public ::array_particle<::procedure_array_base>
{
public:


   using BASE_ARRAY = ::array_particle<::procedure_array_base>;


   using BASE_ARRAY::BASE_ARRAY;

   using BASE_ARRAY::operator =;

   procedure_array(procedure_array&& procedurea) :
      BASE_ARRAY(::transfer(procedurea))
   {

   }

   procedure_array(const procedure_array& procedurea) :
      BASE_ARRAY(procedurea)
   {

   }


   void run() override;
   virtual void on_end_procedure();


   procedure_array & operator=(const procedure_array& procedurea)
   {
      BASE_ARRAY::operator=(procedurea);
      return *this;
   }

   procedure_array & operator=(procedure_array&& procedurea)
   {
      BASE_ARRAY::operator=(::transfer(procedurea));
      return *this;
   }


};


template < typename CONTEXT_TYPE >
class procedure_array_with_context :
   virtual public ::procedure_array
{
public:

   procedure_array_with_context() {}
   procedure_array_with_context(const procedure_array_base &procedurea) :
      procedure_array(procedurea), 
      ::array_particle<::procedure_array_base>(procedurea)
   {

   }
   procedure_array_with_context(procedure_array_base &&procedurea) :
      procedure_array(::transfer(procedurea)), 
      ::array_particle<::procedure_array_base>(::transfer(procedurea))
   {

   }


   procedure_array_with_context &operator=(const procedure_array_base &procedurea)
   {
      ::procedure_array_base::operator=(procedurea);
      return *this;

   }


   void run() override;


};


