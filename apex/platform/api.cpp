// Created by camilo on 2021-11-05 16:12 PM <3ThomasBorregaardS�rensen!!
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


::e_status api::api_login(const ::string & strConfig)
{

   throw interface_only_exception();

   return error_not_implemented;

}


::e_status api::api_get(string strGet, ::payload& payload, property_set& set)
{

   throw interface_only_exception();

   return ::error_interface_only;

}


::e_status api::api_download(string strGet, const ::file::path& path, property_set& set)
{

   throw interface_only_exception();

   return ::error_interface_only;

}


string api::api_token(bool bForce)
{

   throw interface_only_exception();

   return "";

}



