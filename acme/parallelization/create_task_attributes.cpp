// Created by camilo on 2022-11-01 22:25 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "create_task_attributes.h"


create_task_attributes::create_task_attributes(::enum_priority epriority, ::u32 uStackSize, ::u32 uCreateFlags, const security_attributes & security_attributes) :
   m_securityattributes(security_attributes)
{
   
   m_epriority = epriority;
   m_uStackSize = uStackSize;
   m_uCreateFlags = uCreateFlags;

}


create_task_attributes::create_task_attributes(nullptr_t) :
   create_task_attributes()
{

}


create_task_attributes::create_task_attributes(const create_task_attributes & createtaskattributes) :
   m_securityattributes(createtaskattributes.m_securityattributes)
{

   m_epriority = createtaskattributes.m_epriority;
   m_uStackSize = createtaskattributes.m_uStackSize;
   m_uCreateFlags = createtaskattributes.m_uCreateFlags;

}



