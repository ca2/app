// Created by camilo on 2023-11-26 20:50 <3ThomasBorregaardSorensen!!
#pragma once


#include "message_queue.h"
#include "acme/prototype/collection/map.h"


using task_message_queue_map = ::map < itask_t, ::pointer < message_queue > >;


class CLASS_DECL_ACME task_message_queue :
   virtual public ::particle
{
public:


   critical_section           m_criticalsection;
   task_message_queue_map     m_map;


   task_message_queue();
   ~task_message_queue() override;


   ::message_queue * get_message_queue(itask_t itask, bool bCreate);
   void erase_message_queue(itask_t itask);
   void clear_message_queue(itask_t itask);


   ::message_queue * current_task_message_queue(bool bCreate);


};



