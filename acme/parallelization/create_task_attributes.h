// Created by camilo on 2022-11-01 22:24 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/operating_system/security_attributes.h"
//#include "acme/prototype/prototype/pointer.h"


class task_handler;

struct create_task_attributes_t
{
public:


   ::enum_priority                        m_epriority = e_priority_normal;
   ::u32                           m_uStackSize = 0;
   ::u32                           m_uCreateFlags = 0;
   ::task_handler *                       m_ptaskhandler = nullptr;
   ::pointer < security_attributes >      m_psecurityattributes;


};


class CLASS_DECL_ACME create_task_attributes :
   public create_task_attributes_t
{
public:

   create_task_attributes(::enum_priority epriority = e_priority_normal, ::u32 uStackSize = 0, ::u32 uCreateFlags = 0, ::task_handler * ptaskhandler = nullptr, security_attributes * psecurityattributes = nullptr);
   create_task_attributes(nullptr_t);
   create_task_attributes(const create_task_attributes_t & createtaskattributes);


};



