//
// Created by camilo on 31/01/2022 05:00 PM <3ThomasBorregaardSørensen!! Thomas Likes Number 5!!
//
#pragma once


#include "acme/primitive/primitive/matter.h"


class CLASS_DECL_ACME nano_object :
   virtual public ::matter
{
public:


   bool              m_bModified;
   void *            m_pthis;


   nano_object();
   ~nano_object();


   virtual void destroy();


   virtual void * operating_system_data();


   virtual void update(nano_device * pnanodevice);


};



