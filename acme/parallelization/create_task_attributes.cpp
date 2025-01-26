// Created by camilo on 2022-11-01 22:25 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "create_task_attributes.h"


create_task_attributes::create_task_attributes(::enum_priority epriority, unsigned int uStackSize, unsigned int uCreateFlags, ::task_handler * ptaskhandler, security_attributes * psecurityattributes)
{
   
   m_epriority = epriority;
   m_uStackSize = uStackSize;
   m_uCreateFlags = uCreateFlags;
   m_ptaskhandler = ptaskhandler;
   m_psecurityattributes = psecurityattributes;

}


create_task_attributes::create_task_attributes(nullptr_t) :
   create_task_attributes()
{

}


create_task_attributes::create_task_attributes(const create_task_attributes_t & createtaskattributes)
{

   m_epriority = createtaskattributes.m_epriority;
   m_uStackSize = createtaskattributes.m_uStackSize;
   m_uCreateFlags = createtaskattributes.m_uCreateFlags;
   m_ptaskhandler = createtaskattributes.m_ptaskhandler;
   m_psecurityattributes = createtaskattributes.m_psecurityattributes;

}



