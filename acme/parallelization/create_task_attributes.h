// Created by camilo on 2022-11-01 22:24 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/operating_system/security_attributes.h"
//#include "acme/primitive/primitive/pointer.h"


class CLASS_DECL_ACME create_task_attributes
{
public:


   ::enum_priority                        m_epriority;
   ::u32                                  m_uStackSize;
   ::u32                                  m_uCreateFlags;
   ::pointer < security_attributes >      m_psecurityattributes;


   create_task_attributes(::enum_priority epriority = e_priority_normal, ::u32 uStackSize = 0, ::u32 uCreateFlags = 0, security_attributes * psecurityattributes = nullptr);
   create_task_attributes(nullptr_t);
   create_task_attributes(const create_task_attributes & createtaskattributes);


};



