// Created by camilo on 2022-11-01 22:24 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/operating_system/security_attributes.h"
//#include "acme/prototype/prototype/pointer.h"


class CLASS_DECL_ACME create_task_attributes
{
public:


   ::enum_priority                        m_epriority;
   unsigned int                                  m_uStackSize;
   unsigned int                                  m_uCreateFlags;
   ::pointer < security_attributes >      m_psecurityattributes;


   create_task_attributes(::enum_priority epriority = e_priority_normal, unsigned int uStackSize = 0, unsigned int uCreateFlags = 0, security_attributes * psecurityattributes = nullptr);
   create_task_attributes(nullptr_t);
   create_task_attributes(const create_task_attributes & createtaskattributes);


};



