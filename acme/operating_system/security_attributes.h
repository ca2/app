// Created by camilo on 2022-11-01 22:45 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/primitive/primitive/particle.h"


class CLASS_DECL_ACME security_attributes :
   virtual public ::particle
{
public:


   security_attributes();
   ~security_attributes() override;

   
   virtual void * _get_os_security_attributes();
   inline void * get_os_security_attributes() { return ::is_set(this) ? _get_os_security_attributes() : nullptr; }


};



