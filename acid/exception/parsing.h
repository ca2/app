#pragma once


//#include "exception.h"
#include "acid/parallelization/task_flag.h"


class CLASS_DECL_ACID parsing_exception:
   public ::exception
{
public:


   parsing_exception(const ::scoped_string & scopedstrMessage);
   ~parsing_exception() override;


};


class CLASS_DECL_ACID avoid_parsing_exception :
   public ___keep_task_flag
{
public:

   
   avoid_parsing_exception() : ___keep_task_flag(e_task_flag_avoid_parsing_exception) {}
   

};


class network_payload_parsing_exception :
   public ::parsing_exception
{
public:

   network_payload_parsing_exception(const ::scoped_string & scopedstrMessage = nullptr);
   virtual ~network_payload_parsing_exception();

};


