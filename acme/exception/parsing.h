﻿#pragma once


#include "exception.h"


class CLASS_DECL_ACME parsing_exception:
   public ::exception
{
public:


   parsing_exception(const char * pszMessage);
   ~parsing_exception() override;


};




class CLASS_DECL_ACME avoid_parsing_exception :
   public ___keep_task_flag
{
public:

   
   avoid_parsing_exception() : ___keep_task_flag(e_task_flag_avoid_parsing_exception) {}
   

};



class network_payload_parsing_exception :
   public ::parsing_exception
{
public:

   network_payload_parsing_exception(const char * pszMessage = nullptr);
   virtual ~network_payload_parsing_exception();

};


