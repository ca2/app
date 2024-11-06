//*****************************************************************************
//
//      Class:          service_status
//      Author:         Kenny Kerr
//      Date created:   10 April 2004
//      Description:    Provides default initialization for SERVICE_STATUS.
//
//*****************************************************************************
// Recreated on ~2021 by camilo <3ThomasBS_!!
#pragma once


#ifdef WINDOWS_DESKTOP


class CLASS_DECL_APEX service_status :
   public SERVICE_STATUS
{
public:

   
   char sz[80];


   service_status()
   {

      zero(this);

   }


};


#else


class CLASS_DECL_APEX service_status
{
public:


   unsigned int       dwServiceType;
   unsigned int       dwServiceState;


   service_status()
   {

      ASSERT(sizeof(*this) == sizeof(service_status));

      memory_set(this, 0, sizeof(service_status));

   }

};


#endif



