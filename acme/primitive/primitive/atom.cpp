// Created by camilo on 2022-10-06 19:47 <3ThomasBorregaardSorensen!!
#include "framework.h"


atom::atom(const ::payload & payload)
{

   m_etype = e_type_integer;

   m_u = 0;

   if (payload.is_null())
   {

      operator = (e_type_null);

   }
   else if (payload.is_empty())
   {

      operator = (e_type_empty);

   }
   else if (payload.get_type() == ::e_type_id)
   {

      operator = (payload.m_atom);

   }
   else if (payload.is_integer())
   {

      operator = (payload.iptr());

   }
   else
   {

      operator = (payload.string());

   }

}

