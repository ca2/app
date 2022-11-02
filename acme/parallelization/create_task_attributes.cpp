// Created by camilo on 2022-11-01 22:25 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "create_task_attributes.h"


create_task_attributes::create_task_attributes(::enum_priority epriority, ::u32 uStackSize, ::u32 uCreateFlags, void * pOsCreateTaskAttributes)
{
   
   m_epriority = epriority;
   m_uStackSize = uStackSize;
   m_uCreateFlags = uCreateFlags;
   m_pOsCreateTaskAttributes = pOsCreateTaskAttributes;

}


create_task_attributes::create_task_attributes(nullptr_t) :
   create_task_attributes()
{

}


create_task_attributes::create_task_attributes(const create_task_attributes & createtaskattributes)
{

   m_epriority = create_task_attributes.m_epriority;
   m_uStackSize = create_task_attributes.m_uStackSize;
   m_uCreateFlags = create_task_attributes.m_uCreateFlags;
   m_pOsCreateTaskAttributes = create_task_attributes.m_pOsCreateTaskAttributes;

}



