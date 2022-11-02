// Created by camilo on 2022-11-01 22:46 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "security_attributes.h"


security_attributes::security_attributes(void * pOsSecurityAttributes)
{

   m_pOsSecurityAttributes = pOsSecurityAttributes;

}


security_attributes::security_attributes(nullptr_t) :
   security_attributes()
{

}


security_attributes::security_attributes(const security_attributes & securityattributes)
{

   m_pOsSecurityAttributes = securityattributes.m_pOsSecurityAttributes;

}



