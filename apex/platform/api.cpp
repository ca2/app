// Created by camilo on 2021-11-05 16:12 PM <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "api.h"


api::api()
{


}


api::~api()
{


}


::e_status api::initialize(::object* pobject)
{

   auto estatus = ::object::initialize(pobject);

   if (!estatus)
   {

      return estatus;

   }

   return estatus;

}


string api::api_token(bool bForce)
{

   throw interface_only_exception();

   return "";

}



