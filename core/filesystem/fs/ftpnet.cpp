// Created by camilo on 2021-03-22 20:40 <3ThomasBS_!!
#include "framework.h"
#include "core/networking/ftp/_.h"
#include "ftpnet.h"
#include "apex/networking/sockets/_sockets.h"


ftpnet::ftpnet()
{

}


ftpnet::~ftpnet()
{

}


void ftpnet::initialize(::object * pobject)
{

   //auto estatus = 
   
   ::object::initialize(pobject);

   //if (!estatus)
   //{

   //   return estatus;

   //}

   //estatus = 
   
   __construct_new(m_psockethandler);

   //if (!estatus)
   //{

   //   return estatus;

   //}

   //return estatus;

}



