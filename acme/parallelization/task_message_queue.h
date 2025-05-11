// Created by camilo on 2023-11-26 20:50 <3ThomasBorregaardSorensen!!
#pragma once


#include "message_queue.h"
#include "acme/prototype/collection/map.h"


//using task_message_queue_map = ::map < ::task_index, ::pointer < message_queue > >;


class CLASS_DECL_ACME task_message_queue :
   virtual public ::particle
{
public:


   //critical_section           m_criticalsection;
   //task_message_queue_map     m_map;


   task_message_queue();
   ~task_message_queue() override;


   ::message_queue * get_message_queue(const ::task_index & taskindex, bool bCreate);
   void erase_message_queue(const ::task_index & taskindex);
   void clear_message_queue(const ::task_index & taskindex);


   ::message_queue * current_task_message_queue(bool bCreate);


};



