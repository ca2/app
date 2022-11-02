// Created by camilo on 2022-11-01 22:24 <3ThomasBorregaardSorensen!!
#pragma once


class CLASS_DECL_ACME create_task_attributes
{
public:


   void *                     m_pOsCreateTaskAttributes;
   ::enum_priority            m_epriority;
   ::u32                      m_uStackSize;
   ::u32                      m_uCreateFlags;


   create_task_attributes(::enum_priority epriority = e_priority_normal, ::u32 uStackSize = 0, ::u32 uCreateFlags = 0, void * pOsCreateTaskAttributes = nullptr);
   create_task_attributes(nullptr_t);
   create_task_attributes(const create_task_attributes & createtaskattributes);


};



