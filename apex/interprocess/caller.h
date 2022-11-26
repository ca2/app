// Created by camilo on 2022-10-11 00:04 <3ThomasBorregaardSorensen!! (Thomas Likes Number 5!!)
#pragma once


#include "base.h"


namespace interprocess
{


   class CLASS_DECL_APEX caller :
      virtual public base
   {
   public:


      caller();
      ~caller() override;



      virtual void open(const ::string & strChannel, ::launcher * plauncher = nullptr);
      virtual void close();


      virtual void call(const ::string & strUri, const class time & timeTimeout);
      //virtual void send(int message,void * pdata,int len, const class time & timeTimeout);


      virtual bool is_caller_ok();


   };


} // namespace interprocess



