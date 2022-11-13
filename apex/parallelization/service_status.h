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


   u32       dwServiceType;
   u32       dwServiceState;


   service_status()
   {

      ASSERT(sizeof(*this) == sizeof(service_status));

      __memset(this, 0, sizeof(service_status));

   }

};


#endif



