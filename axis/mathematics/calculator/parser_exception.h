#pragma once


#include "acme/exception/parsing.h"
#include "acme/parallelization/task_flag.h"


class CLASS_DECL_AXIS numeric_parsing_exception:
   public ::parsing_exception
{
public:


   numeric_parsing_exception(const ::scoped_string & scopedstrMessage = nullptr);
   ~numeric_parsing_exception() override;


};


CLASS_DECL_AXIS bool should_avoid_numeric_parsing_exception();
CLASS_DECL_AXIS bool throw_numeric_parsing_exception(const ::scoped_string & scopedstrMessage);


class CLASS_DECL_AXIS avoid_numeric_parsing_exception : 
   public ___keep_task_flag
{
public:

   avoid_numeric_parsing_exception() : ___keep_task_flag(e_task_flag_avoid_numeric_parsing_exception) {}
   //virtual ~avoid_numeric_parsing_exception();

};
