// Created by camilo on 2021-03-22 20:40 <3ThomasBS_!!
#include "framework.h"
#include "core/networking/ftp/_.h"
#include "ftpnet.h"


ftpnet::ftpnet()
{

}


ftpnet::~ftpnet()
{

}


::e_status ftpnet::initialize(::object * pobject)
{

   auto estatus = ::object::initialize(pobject);

   if (!estatus)
   {

      return estatus;

   }

   estatus = __construct_new(m_psockethandler);

   if (!estatus)
   {

      return estatus;

   }

   return estatus;

}



