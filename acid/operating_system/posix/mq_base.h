#pragma once


class CLASS_DECL_ACID mq_base :
   public ::matter
{
public:



   virtual bool has_message_in_queue() const = 0;


};



