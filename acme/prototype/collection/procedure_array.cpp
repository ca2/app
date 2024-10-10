// Created by camilo on 2024-10-08 23:32 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "acme/exception/cancel.h"


procedure_array::procedure_array()
{
}


procedure_array::procedure_array(const procedure_array & procedurea) :
   comparable_array<::procedure>(procedurea)
{
}


procedure_array::procedure_array(procedure_array && procedurea) :
   comparable_array<::procedure>(::transfer(procedurea))
{

}


procedure_array & procedure_array::operator = (const procedure_array & procedurea)
{

   comparable_array<::procedure>::operator=(procedurea);

   return *this;

}


void procedure_array::run()
{

   ::task * ptask = ::get_task();

   for (auto & procedure : *this)
   {

      if (procedure.m_pbase == ptask)
      {

         continue;

      }

      procedure();

      on_end_procedure();

   }

}


void procedure_array::on_end_procedure()
{
}

