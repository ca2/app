//
// Created by camilo on 2025-01-25 05:55 <3ThomasBorregaardSorensen!!
//
#pragma once


class CLASS_DECL_ACME task_handler :
   virtual public ::particle
{
public:


   ::task_pointer m_ptask;


   task_handler();
   ~task_handler() override;


   virtual void __task_prefix(::task * ptask);
   virtual void __task_handle();
   virtual void __task_suffix();


};



