// Created by camilo on 2021-03-22 20:40 <3ThomasBS_!!
#include "framework.h"
#include "ftpnet.h"
#include "apex/networking/sockets/basic/socket_handler.h"


ftpnet::ftpnet()
{

}


ftpnet::~ftpnet()
{

}


void ftpnet::initialize(::particle * pparticle)
{

   //auto estatus = 
   
   ::object::initialize(pparticle);

   //if (!estatus)
   //{

   //   return estatus;

   //}

   //estatus = 
   
   __construct(m_psockethandler);

   //if (!estatus)
   //{

   //   return estatus;

   //}

   //return estatus;

}



