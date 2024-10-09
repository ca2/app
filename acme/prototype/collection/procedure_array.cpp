// Created by camilo on 2024-10-08 23:32 <3ThomasBorregaardSorensen!!
#include "framework.h"


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

   for (auto & procedure : *this)
   {

      procedure();

   }

}
